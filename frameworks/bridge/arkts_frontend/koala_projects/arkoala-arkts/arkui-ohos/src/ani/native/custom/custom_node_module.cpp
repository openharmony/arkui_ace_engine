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

namespace OHOS::Ace::Ani {

ani_status NativeCustomComponent::BindNativeCustomComponent(ani_env *env)
{
    ani_class cls;
    static const char *className =
        "Larkui/ani/arkts/ArkUIAniCustomNodeModule/ArkUIAniCustomNodeModule;";
    auto ani_status = env->FindClass(className, &cls);
    if (ani_status != ANI_OK) {
        HILOGE("BindNativeCustomComponent FindClass failed, className: %{public}s", className);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {
            "_CustomNode_Construct",
            nullptr,
            reinterpret_cast<void*>(ConstructCustomNode)
        },
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        HILOGE("BindNativeCustomComponentComponent Class_BindNativeMethods failed,"
            " className: %{public}s", className);
        return ANI_ERROR;
    };
    return ANI_OK;
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

    ani_method onMeasureSizeMethod;
    if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(type), "onMeasureSize", nullptr, &onMeasureSizeMethod)) {
        return 0;
    }

    auto&& onMeasureSize = [vm, weakRef, onMeasureSizeMethod](OHOS::Ace::NG::LayoutWrapper* layoutWrapper) {
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }

        if (layoutWrapper == nullptr) {
            return;
        }

        auto jsParam = JSMeasureLayoutParamNG::GetInstance(layoutWrapper, env);
        if (!jsParam) {
            layoutWrapper->GetGeometryNode()->SetFrameSize({ -1.0f, -1.0f });
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "GetInstance return val in onMeasureSize API is null");
            return;
        }
        auto selfLayoutInfo = jsParam->GetSelfLayoutInfo(env);
        auto constraint = jsParam->GetConstraint(env);
        auto childArray = jsParam->GetChildArray(env);

        ani_boolean released;
        ani_ref localRef;
        
        if (ANI_OK != env->WeakReference_GetReference(*weakRef, &released, &localRef)) {
            return;
        }
        ani_ref result_obj = nullptr;

        if (!released) {
            if (ANI_OK != env->Object_CallMethod_Ref(static_cast<ani_object>(localRef), onMeasureSizeMethod,
                &result_obj, selfLayoutInfo, childArray, constraint)) {
                return;
            }
        }
        if (AniUtils::IsUndefined(env, static_cast<ani_object>(result_obj))||!result_obj) {
            layoutWrapper->GetGeometryNode()->SetFrameSize({ -1.0f, -1.0f });
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "app return val of onMeasureSize API is empty or undefined");
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
    };

    ani_method onPlaceChildrenMethod;
    if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(type), "onPlaceChildren", nullptr,
        &onPlaceChildrenMethod)) {
        return 0;
    }

    auto&& onPlaceChildren = [vm, weakRef, onPlaceChildrenMethod](OHOS::Ace::NG::LayoutWrapper* layoutWrapper) {
        ani_env* env = nullptr;
        if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
            return;
        }

        if (layoutWrapper == nullptr) {
            return;
        }

        auto jsParam = JSMeasureLayoutParamNG::GetInstance(layoutWrapper, env);

        auto selfLayoutInfo = jsParam->GetSelfLayoutInfo(env);
        auto constraint = jsParam->GetPlaceChildrenConstraint(env);
        auto childArray = jsParam->GetChildArray(env);

        ani_boolean released;
        ani_ref localRef;

        if (ANI_OK != env->WeakReference_GetReference(*weakRef, &released, &localRef)) {
            return;
        }

        if (!released) {
            if (ANI_OK != env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onPlaceChildrenMethod,
                selfLayoutInfo, childArray, constraint)) {
                return;
            }
        }
    };

    auto customNode = NG::CustomNodeStatic::ConstructCustomNode(id,
        std::move(onMeasureSize), std::move(onPlaceChildren));
    if (customNode) {
        return reinterpret_cast<ani_long>(customNode);
    }
    return 0;
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