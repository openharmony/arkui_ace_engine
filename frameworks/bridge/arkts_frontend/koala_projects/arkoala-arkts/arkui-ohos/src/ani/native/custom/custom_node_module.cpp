/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <memory>
#include "custom_node_module.h"
#include "load.h"
#include "ani_measure_layout.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"
#include "core/components_ng/pattern/custom/custom_node_static.h"
#include "arkoala_api_generated.h"

const OH_AnyAPI* GetAnyImpl(int kind, int version, std::string *result = nullptr);

static const GENERATED_ArkUIBasicNodeAPI* GetArkUIBasicNodeAPI()
{
    return reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI *>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_BASIC),
            GENERATED_ARKUI_BASIC_NODE_API_VERSION, nullptr));
}

namespace OHOS::Ace::Ani {

ani_status NativeCustomComponent::BindNativeCustomComponent(ani_env *env)
{
    ani_class cls;
    static const char *className =
        "arkui.ani.arkts.ArkUIAniCustomNodeModule.ArkUIAniCustomNodeModule";
    auto ani_status = env->FindClass(className, &cls);
    if (ani_status != ANI_OK) {
        HILOGE("BindNativeCustomComponent FindClass failed, className: %{public}s", className);
        return ANI_ERROR;
    }

    std::array staticMethods = {
        ani_native_function {
            "_CustomNode_Construct",
            nullptr,
            reinterpret_cast<void*>(ConstructCustomNode)
        },
        ani_native_function {
            "_CustomNode_SetBuildFunction",
            nullptr,
            reinterpret_cast<void*>(CustomNodeSetBuildFunction)
        },
        ani_native_function {
            "_CustomNode_AddChild",
            nullptr,
            reinterpret_cast<void*>(CustomNodeAddChild)
        },
        ani_native_function {
            "_CustomNode_CallDefaultMeasure",
            nullptr,
            reinterpret_cast<void*>(CustomNodeCallDefaultMeasure)
        },
        ani_native_function {
            "_CustomNode_CallDefaultLayout",
            nullptr,
            reinterpret_cast<void*>(CustomNodeCallDefaultLayout)
        },
        ani_native_function {
            "_CustomNode_EnvFunction",
            nullptr,
            reinterpret_cast<void*>(EnvBuildFunction)
        },
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, staticMethods.data(), staticMethods.size())) {
        HILOGE("BindNativeCustomComponentComponent Class_BindStaticNativeMethods failed,"
            " className: %{public}s", className);
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_object NativeCustomComponent::CustomNodeCallDefaultMeasure(
    ani_env *env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    auto uiNode = AceType::Claim(reinterpret_cast<NG::UINode *>(ptr));
    CHECK_NULL_RETURN(uiNode, AniUtils::GetUndefined(env));
    auto frameNode = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(uiNode);
    CHECK_NULL_RETURN(frameNode, AniUtils::GetUndefined(env));
    auto frameSize = NG::CustomNodeStatic::DidDefaultMeasure(frameNode);
    return AniMeasureLayoutParamNG::GenMeasureResult(env, frameSize);
}

void NativeCustomComponent::CustomNodeCallDefaultLayout(
    ani_env *env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    auto uiNode = AceType::Claim(reinterpret_cast<NG::UINode *>(ptr));
    CHECK_NULL_VOID(uiNode);
    auto frameNode = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(uiNode);
    CHECK_NULL_VOID(frameNode);
    NG::CustomNodeStatic::DidDefaultLayout(frameNode);
    return;
}

struct WeakRefGuard {
    ani_wref ref = nullptr;
    ani_vm* vm = nullptr;
    ~WeakRefGuard()
    {
        if (ref && vm) {
            ani_env *env = nullptr;
            if (ANI_OK == vm->GetEnv(ANI_VERSION_1, &env)) {
                env->WeakReference_Delete(ref);
            }
        }
    }
};

void NativeCustomComponent::CustomNodeSetBuildFunction(
    ani_env *env, [[maybe_unused]] ani_object aniClass, ani_long ptr,
    ani_fn_object buildFunc, ani_fn_object reloadFunc)
{
    ani_vm *vm = nullptr;
    env->GetVM(&vm);

    auto buildGuard = std::make_shared<WeakRefGuard>();
    buildGuard->vm = vm;
    if (ANI_OK != env->WeakReference_Create(buildFunc, &buildGuard->ref)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "Failed to create weak reference for buildFunc!");
        return;
    }

    auto reloadGuard = std::make_shared<WeakRefGuard>();
    reloadGuard->vm = vm;
    if (ANI_OK != env->WeakReference_Create(reloadFunc, &reloadGuard->ref)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "Failed to create weak reference for reloadFunc!");
        return;
    }

    auto node = AceType::Claim(reinterpret_cast<NG::UINode *>(ptr));
    auto base = AceType::DynamicCast<NG::CustomNodeBase>(node);
    NG::RenderFunction renderFunction = [vm, buildGuard](int64_t, bool&) -> RefPtr<NG::UINode> {
        ACE_SCOPED_TRACE("CustomNode renderFunction");

        ani_env *env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return nullptr;
        }
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return nullptr;
        }
        ani_boolean released;
        ani_ref localRef;
        if (ANI_OK != env->WeakReference_GetReference(buildGuard->ref, &released, &localRef) || released) {
            env->DestroyLocalScope();
            return nullptr;
        }

        ani_ref resRef;
        if (ANI_OK != env->FunctionalObject_Call(static_cast<ani_fn_object>(localRef), 0, nullptr, &resRef)) {
            env->DestroyLocalScope();
            return nullptr;
        }

        ani_long ptr;
        if (ANI_OK != env->Object_CallMethodByName_Long(static_cast<ani_object>(resRef), "toLong", ":l", &ptr)) {
            env->DestroyLocalScope();
            return nullptr;
        }
        env->DestroyLocalScope();
        return AceType::Claim(reinterpret_cast<NG::UINode *>(ptr));
    };

    NG::RenderFunction completeReloadFunc = [vm, buildGuard, reloadGuard](int64_t, bool&) -> RefPtr<NG::UINode> {
        ACE_SCOPED_TRACE("CustomNode completeReloadFunc");

        ani_env *env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return nullptr;
        }
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return nullptr;
        }

        // Step 1: call reloadFunc to trigger ArkTS-side armRebuild + rebuildPage
        ani_boolean reloadReleased;
        ani_ref reloadLocalRef;
        if (ANI_OK == env->WeakReference_GetReference(
            reloadGuard->ref, &reloadReleased, &reloadLocalRef) && !reloadReleased) {
            ani_ref reloadRes;
            if (ANI_OK != env->FunctionalObject_Call(static_cast<ani_fn_object>(reloadLocalRef), 0, nullptr,
                &reloadRes)) {
                env->DestroyLocalScope();
                return nullptr;
            }
        }

        // Step 2: call buildFunc to get child pointer (updated by rebuildPage)
        ani_boolean released;
        ani_ref localRef;
        if (ANI_OK != env->WeakReference_GetReference(buildGuard->ref, &released, &localRef) || released) {
            env->DestroyLocalScope();
            return nullptr;
        }

        ani_ref resRef;
        if (ANI_OK != env->FunctionalObject_Call(static_cast<ani_fn_object>(localRef), 0, nullptr, &resRef)) {
            env->DestroyLocalScope();
            return nullptr;
        }

        ani_long ptr;
        if (ANI_OK != env->Object_CallMethodByName_Long(static_cast<ani_object>(resRef), "toLong", ":l", &ptr)) {
            env->DestroyLocalScope();
            return nullptr;
        }
        env->DestroyLocalScope();
        return AceType::Claim(reinterpret_cast<NG::UINode *>(ptr));
    };

    TAG_LOGI(AceLogTag::ACE_LAYOUT,
        "HotReload CustomNodeSetBuildFunction: install render and complete reload callbacks");
    base->SetRenderFunction(renderFunction);
    base->SetCompleteReloadFunc(std::move(completeReloadFunc));
}

void NativeCustomComponent::EnvBuildFunction(
    ani_env *env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_fn_object envFunc)
{
    ani_vm *vm = nullptr;
    env->GetVM(&vm);

    std::shared_ptr<ani_wref> weakRef(new ani_wref, [vm](ani_wref *wref) {
        ani_env *env = nullptr;
        if (ANI_OK == vm->GetEnv(ANI_VERSION_1, &env)) {
            env->WeakReference_Delete(*wref);
        }
    });

    if (ANI_OK != env->WeakReference_Create(envFunc, weakRef.get())) {
        return;
    }

    auto node = AceType::Claim(reinterpret_cast<NG::UINode *>(ptr));
    if (!node) {
        return;
    }
    node->RegisterUpdateJSInstanceCallback([vm, weakRef](int32_t instanceId) -> void {
        ACE_SCOPED_TRACE("Env Build Function");

        ani_env *env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        ani_boolean released;
        ani_ref localRef;
        if (ANI_OK != env->WeakReference_GetReference(*weakRef, &released, &localRef) || released) {
            env->DestroyLocalScope();
            return;
        }

        ani_object valueObject = AniUtils::CreateInt32(env, instanceId);
        ani_ref valueRef = static_cast<ani_ref>(valueObject);
        ani_ref resRef;
        if (ANI_OK != env->FunctionalObject_Call(static_cast<ani_fn_object>(localRef), 1, &valueRef, &resRef)) {
            env->DestroyLocalScope();
            return;
        }

        env->DestroyLocalScope();
    });
}

ani_long NativeCustomComponent::ConstructCustomNode(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_int id, ani_object obj)
{
    ani_vm* vm = nullptr;
    env->GetVM(&vm);

    std::shared_ptr<ani_wref> weakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        env->WeakReference_Delete(*wref);
    });

    env->WeakReference_Create(obj, weakRef.get());

    ani_type type;
    env->Object_GetType(obj, &type);

    static ani_ref customComponentObj = nullptr;
    if (!customComponentObj) {
        if (env->GlobalReference_Create(type, &customComponentObj) != ANI_OK) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "Failed to create global reference.");
        }
    }

    static ani_method onMeasureSizeMethod = nullptr;
    std::function<void(NG::LayoutWrapper* layoutWrapper)> onMeasureSize = nullptr;

    if (!onMeasureSizeMethod) {
        if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "onMeasureSize", nullptr,
            &onMeasureSizeMethod)) {
            return 0;
        }
    }

    onMeasureSize = [vm, weakRef](OHOS::Ace::NG::LayoutWrapper* layoutWrapper) {
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        if (layoutWrapper == nullptr) {
            env->DestroyLocalScope();
            return;
        }

        auto aniParam = AniMeasureLayoutParamNG::GetInstance(layoutWrapper, env);
        if (!aniParam) {
            layoutWrapper->GetGeometryNode()->SetFrameSize({ -1.0f, -1.0f });
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "GetInstance return val in onMeasureSize API is null");
            env->DestroyLocalScope();
            return;
        }
        auto selfLayoutInfo = aniParam->GetSelfLayoutInfo(env);
        auto constraint = aniParam->GetConstraint(env);
        auto childArray = aniParam->GetChildArray(env);

        ani_boolean released;
        ani_ref localRef;

        if (ANI_OK != env->WeakReference_GetReference(*weakRef, &released, &localRef)) {
            env->DestroyLocalScope();
            return;
        }
        ani_ref result_obj = nullptr;

        if (released) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "The wref is GC collected.");
            env->DestroyLocalScope();
            return;
        }
        if (ANI_OK != env->Object_CallMethod_Ref(static_cast<ani_object>(localRef), onMeasureSizeMethod,
            &result_obj, selfLayoutInfo, childArray, constraint)) {
            env->DestroyLocalScope();
            return;
        }
        if (AniUtils::IsUndefined(env, static_cast<ani_object>(result_obj))||!result_obj) {
            layoutWrapper->GetGeometryNode()->SetFrameSize({ -1.0f, -1.0f });
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "app return val of onMeasureSize API is empty or undefined");
            env->DestroyLocalScope();
            return;
        }

        CalcDimension measureWidth;
        CalcDimension measureHeight;

        ani_double widthValue = -1.0f;
        if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(result_obj), "width",
            &widthValue)) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "app return width val of onMeasureSize API is empty or undefined");
        }
        ani_object width_obj = AniUtils::CreateDouble(env, widthValue);

        ani_double heightValue = -1.0f;
        if (ANI_OK != env->Object_GetPropertyByName_Double(static_cast<ani_object>(result_obj), "height",
            &heightValue)) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "app return height val of onMeasureSize API is empty or undefined");
        }
        ani_object height_obj = AniUtils::CreateDouble(env, heightValue);

        if (!OHOS::Ace::Ani::ParseAniDimensionVp(env, width_obj, measureWidth)) {
            measureWidth = { -1.0f };
        }
        if (!OHOS::Ace::Ani::ParseAniDimensionVp(env, height_obj, measureHeight)) {
            measureHeight = { -1.0f };
        }

        NG::SizeF frameSize = { measureWidth.ConvertToPx(), measureHeight.ConvertToPx() };
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
        env->DestroyLocalScope();
    };

    static ani_method onPlaceChildrenMethod = nullptr;
    std::function<void(NG::LayoutWrapper* layoutWrapper)> onPlaceChildren = nullptr;

    if (!onPlaceChildrenMethod) {
        if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(customComponentObj), "onPlaceChildren", nullptr,
            &onPlaceChildrenMethod)) {
            return 0;
        }
    }

    onPlaceChildren = [vm, weakRef](OHOS::Ace::NG::LayoutWrapper* layoutWrapper) {
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        if (layoutWrapper == nullptr) {
            env->DestroyLocalScope();
            return;
        }

        auto aniParam = AniMeasureLayoutParamNG::GetInstance(layoutWrapper, env);

        auto selfLayoutInfo = aniParam->GetSelfLayoutInfo(env);
        auto constraint = aniParam->GetPlaceChildrenConstraint(env);
        auto childArray = aniParam->GetChildArray(env);

        ani_boolean released;
        ani_ref localRef;

        if (ANI_OK != env->WeakReference_GetReference(*weakRef, &released, &localRef)) {
            env->DestroyLocalScope();
            return;
        }

        if (released) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "The wref is GC collected.");
            env->DestroyLocalScope();
            return;
        }
        if (ANI_OK != env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onPlaceChildrenMethod,
            selfLayoutInfo, childArray, constraint)) {
            env->DestroyLocalScope();
            return;
        }
        env->DestroyLocalScope();
    };
    
    std::function<void(NG::LayoutWrapper* layoutWrapper)> updateParamFunc = nullptr;
    updateParamFunc = [vm](NG::LayoutWrapper* layoutWrapper) {
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }
        AniMeasureLayoutParamNG::GetInstance(layoutWrapper, env);
    };

    auto customNode = NG::CustomNodeStatic::ConstructCustomNode(id,
        std::move(onMeasureSize), std::move(onPlaceChildren), std::move(updateParamFunc));
    if (customNode) {
        return reinterpret_cast<ani_long>(customNode);
    }
    return 0;
}

void NativeCustomComponent::CustomNodeAddChild(ani_env* env, [[maybe_unused]] ani_object obj,
    ani_long parent, ani_long child)
{
    Ark_NodeHandle parentNode = reinterpret_cast<Ark_NodeHandle>(parent);
    Ark_NodeHandle childNode = reinterpret_cast<Ark_NodeHandle>(child);
    auto basicNodeAPI = GetArkUIBasicNodeAPI();
    if (basicNodeAPI) {
        basicNodeAPI->addChild(parentNode, childNode);
        basicNodeAPI->markDirty(parentNode, 0);
    }
}

} // namespace OHOS::Ace::Ani

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        HILOGE("GetEnv failed when ANI_Constructor");
        return ANI_ERROR;
    }

    auto ani_status = OHOS::Ace::Ani::NativeCustomComponent::BindNativeCustomComponent(env);
    if (ani_status != ANI_OK) {
        HILOGE("BindNativeCustomComponent failed when ANI_Constructor");
        return ani_status;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
