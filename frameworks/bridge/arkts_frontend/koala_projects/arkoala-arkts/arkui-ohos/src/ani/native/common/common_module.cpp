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

#include "common_module.h"

#if !defined(PREVIEW)
#define OHOS_AAFWK_HILOG_TAG_WRAPPER_H
#include "ani_base_context.h"
#include "canvas_ani/ani_canvas.h"
#endif

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "ani.h"
#include "load.h"

#include "base/utils/utils.h"
#include "core/interfaces/ani/ani_api.h"
#include "arkoala-arkts/framework/native/src/resource_color_helper.h"
#ifndef __linux__
#include "pixel_map_taihe_ani.h"
#endif
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
const int32_t FLAG_DRAW_FRONT = 1;
const int32_t FLAG_DRAW_CONTENT = 1 << 1;
const int32_t FLAG_DRAW_BEHIND = 1 << 2;
const int32_t FLAG_DRAW_FOREGROUND = 1 << 3;
}
ani_status GetAniEnv(ani_vm* vm, ani_env** env)
{
    CHECK_NULL_RETURN(vm, ANI_ERROR);
    ani_options aniOpt {0, nullptr};
    auto status = vm->AttachCurrentThread(&aniOpt, ANI_VERSION_1, env);
    if (status != ANI_OK) {
        vm->GetEnv(ANI_VERSION_1, env);
    }
    return status;
}

CommonModuleCallbackAni::CommonModuleCallbackAni(ani_env* env, ani_ref func)
{
    CHECK_NULL_VOID(env);
    env->GetVM(&vm_);
    env->GlobalReference_Create(func, &func_);
}

CommonModuleCallbackAni::~CommonModuleCallbackAni()
{
    CHECK_NULL_VOID(vm_);
    CHECK_NULL_VOID(func_);
    ani_env* env = nullptr;
    auto attachCurrentThreadStatus = GetAniEnv(vm_, &env);
    if (attachCurrentThreadStatus == ANI_OK && env != nullptr) {
        env->GlobalReference_Delete(func_);
        vm_->DetachCurrentThread();
    }
}

void CommonModuleCallbackAni::Call(ani_env* env, ani_size argc, ani_ref* argv, ani_ref* result)
{
    CHECK_NULL_VOID(env);
    env->FunctionalObject_Call(static_cast<ani_fn_object>(func_), argc, argv, result);
}

ani_object GetHostContext([[maybe_unused]] ani_env* env, ani_object obj, ani_int key)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    ani_ref* context = modifier->getCommonAniModifier()->getHostContext(key);
    if (context) {
        ani_object context_object = reinterpret_cast<ani_object>(*context);
        return context_object;
    }
    return nullptr;
}

void SetFrameRateRange([[maybe_unused]] ani_env* env, ani_object obj, ani_long key, ani_object value, ani_int type)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->setFrameRateRange(env, key, value, type);
}

void SyncInstanceId([[maybe_unused]] ani_env* env, ani_object obj, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->syncInstanceId(id);
}

void RestoreInstanceId([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->restoreInstanceId();
}

ani_int GetCurrentInstanceId([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return -1;
    }
    return modifier->getCommonAniModifier()->getCurrentInstanceId();
}

ani_int GetFocusedInstanceId([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return -1;
    }
    return modifier->getCommonAniModifier()->getFocusedInstanceId();
}

ani_object CreateSizeObject(ani_env* env, const NG::DrawingContext& context)
{
    ani_status status;
    ani_class sizeClass;
    if ((status = env->FindClass("arkui.Graphics.SizeInternal", &sizeClass)) != ANI_OK) {
        HILOGE("FindClass Size failed, %{public}d", status);
        return nullptr;
    }
    ani_method sizeCtor;
    if ((status = env->Class_FindMethod(sizeClass, "<ctor>", "dd:", &sizeCtor)) != ANI_OK) {
        HILOGE("Class_FindMethod sizeClass ctor failed, %{public}d", status);
        return nullptr;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier()) {
        return nullptr;
    }
    ani_object sizeObject;
    ani_float width = modifier->getCommonAniModifier()->getPx2VpWithCurrentDensity(context.width);
    ani_float height = modifier->getCommonAniModifier()->getPx2VpWithCurrentDensity(context.height);
    if ((status = env->Object_New(sizeClass, sizeCtor, &sizeObject, width, height)) != ANI_OK) {
        HILOGE("New Size object failed, %{public}d", status);
        return nullptr;
    }
    return sizeObject;
}

ani_object CreateSizeInPixelObject(ani_env* env, const NG::DrawingContext& context)
{
    ani_status status;
    ani_class sizeInPixelClass;
    if ((status = env->FindClass("arkui.Graphics.SizeInternal", &sizeInPixelClass)) != ANI_OK) {
        HILOGE("FindClass Size failed, %{public}d", status);
        return nullptr;
    }
    ani_method sizeInPixelCtor;
    if ((status = env->Class_FindMethod(sizeInPixelClass, "<ctor>", "dd:", &sizeInPixelCtor)) != ANI_OK) {
        HILOGE("Class_FindMethod sizeInPixelClass ctor failed, %{public}d", status);
        return nullptr;
    }
    ani_object sizeInPixelObject;
    ani_float widthInPixel = context.width;
    ani_float heightInPixel = context.height;
    if ((status = env->Object_New(
        sizeInPixelClass, sizeInPixelCtor, &sizeInPixelObject, widthInPixel, heightInPixel)) != ANI_OK) {
        HILOGE("New SizeInPixel object failed, %{public}d", status);
        return nullptr;
    }
    return sizeInPixelObject;
}

ani_object CreateDrawingContext(ani_env* env, const NG::DrawingContext& context)
{
    ani_status status;
    ani_object result = nullptr;

    // DrawContext object
    ani_class drawContextClass;
    if ((status = env->FindClass("arkui.Graphics.DrawContext", &drawContextClass)) != ANI_OK) {
        HILOGE("FindClass DrawContext failed, %{public}d", status);
        return nullptr;
    }
    ani_method drawContextCtor;
    if ((status = env->Class_FindMethod(drawContextClass, "<ctor>", ":", &drawContextCtor)) != ANI_OK) {
        HILOGE("Class_FindMethod drawContextClass ctor failed, %{public}d", status);
        return nullptr;
    }
    if ((status = env->Object_New(drawContextClass, drawContextCtor, &result)) != ANI_OK) {
        HILOGE("New DrawContext object failed, %{public}d", status);
        return nullptr;
    }

    // Size object
    ani_object sizeObject = CreateSizeObject(env, context);
    env->Object_SetPropertyByName_Ref(result, "size_", (ani_ref)sizeObject);

    // sizeInPixel Object
    ani_object sizeInPixelObject = CreateSizeInPixelObject(env, context);
    env->Object_SetPropertyByName_Ref(result, "sizeInPixel_", (ani_ref)sizeInPixelObject);

    // canvas Object
#if !defined(PREVIEW)
    ani_object aniCanvas = OHOS::Rosen::Drawing::AniCanvas::CreateAniCanvas(env, &context.canvas);
    if (!aniCanvas) {
        HILOGE("Create AniCanvas failed !");
    }
    env->Object_SetPropertyByName_Ref(result, "canvas_", (ani_ref)aniCanvas);
#endif

    return result;
}

std::function<void(NG::DrawingContext& drawingContext)> ConvertFnObjDrawCallbackFun(ani_vm* vm,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    return [vm, callbackAni](const NG::DrawingContext& context) -> void {
            CHECK_NULL_VOID(vm);
            CHECK_NULL_VOID(callbackAni);
            ani_env* env = nullptr;
            auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
            CHECK_NULL_VOID(env);

            auto drawingContext = CreateDrawingContext(env, context);
            if (!drawingContext) {
                HILOGW("Create drawing context failed !");
                return;
            }
            std::vector<ani_ref> params = {};
            params.emplace_back((ani_ref)drawingContext);
            ani_ref ret = nullptr;
            callbackAni->Call(env, params.size(), params.data(), &ret);
            if (attachCurrentThreadStatus == ANI_OK) {
                vm->DetachCurrentThread();
            }
        };
}

void SetDrawCallback(ani_env* env, ani_object obj, ani_long ptr, ani_fn_object fnObj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    ani_ref fnObjGlobalRef = static_cast<ani_ref>(fnObj);
    auto fndDrawCallbackAni = std::make_shared<CommonModuleCallbackAni>(env, fnObjGlobalRef);
    std::function<void(NG::DrawingContext& drawingContext)> drawCallbackFun =
        ConvertFnObjDrawCallbackFun(vm, fndDrawCallbackAni);
    void* fnDrawCallbackFun = &drawCallbackFun;

    modifier->getCommonAniModifier()->setDrawCallback(env, ptr, fnDrawCallbackFun);
}

void SetFrameNodeDrawCallback(ani_env* env, ani_object obj, ani_long ptr, ani_fn_object fnObj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    void* fnDrawCallbackFun = nullptr;
    std::function<void(NG::DrawingContext& drawingContext)> drawCallbackFun = nullptr;
    ani_ref fnObjGlobalRef = static_cast<ani_ref>(fnObj);
    auto fndDrawCallbackAni = std::make_shared<CommonModuleCallbackAni>(env, fnObjGlobalRef);
    drawCallbackFun = ConvertFnObjDrawCallbackFun(vm, fndDrawCallbackAni);
    if (drawCallbackFun != nullptr) {
        fnDrawCallbackFun = &drawCallbackFun;
    }
    modifier->getCommonAniModifier()->setFrameNodeDrawCallback(env, ptr, fnDrawCallbackFun);
}

std::function<void(NG::DrawingContext& drawingContext)> ConvertFnObjDrawBehindFun(
    ani_vm* vm, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni, ani_ref modifier)
{
    return [vm, callbackAni, object = modifier](const NG::DrawingContext& context) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        auto drawingContext = CreateDrawingContext(env, context);
        if (!drawingContext) {
            return;
        }
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(object), "drawBehind", "C{arkui.Graphics.DrawContext}:", drawingContext);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

std::function<void(NG::DrawingContext& drawingContext)> ConvertFnObjDrawContentFun(
    ani_vm* vm, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni, ani_ref modifier)
{
    return [vm, callbackAni, object = modifier](const NG::DrawingContext& context) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        auto drawingContext = CreateDrawingContext(env, context);
        if (!drawingContext) {
            return;
        }
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(object), "drawContent", "C{arkui.Graphics.DrawContext}:", drawingContext);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

std::function<void(NG::DrawingContext& drawingContext)> ConvertFnObjDrawFrontFun(
    ani_vm* vm, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni, ani_ref modifier)
{
    return [vm, callbackAni, object = modifier](const NG::DrawingContext& context) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        auto drawingContext = CreateDrawingContext(env, context);
        if (!drawingContext) {
            return;
        }
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(object), "drawFront", "C{arkui.Graphics.DrawContext}:", drawingContext);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

std::function<void(NG::DrawingContext& drawingContext)> ConvertFnObjDrawForeGroundFun(
    ani_vm* vm, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni, ani_ref modifier)
{
    return [vm, callbackAni, object = modifier](const NG::DrawingContext& context) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        auto drawingContext = CreateDrawingContext(env, context);
        if (!drawingContext) {
            return;
        }
        env->Object_CallMethodByName_Void(reinterpret_cast<ani_fn_object>(object), "drawForeground",
            "C{arkui.Graphics.DrawContext}:", drawingContext);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void SetDrawModifier(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, uint32_t flag, ani_object drawModifier)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getArkUIAniDrawModifier() || !env) {
        return;
    }
    if (drawModifier == nullptr) {
        // fnObj should not be nullptr;
        HILOGE("DrawModifier is undefined.");
        return;
    }
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    ani_ref drawModifierRef;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(drawModifier), &drawModifierRef);
    void* fnDrawBehindFun = nullptr;
    void* fnDrawContentFun = nullptr;
    void* fnDrawFrontFun = nullptr;
    void* fnDrawForegroundFun = nullptr;
    std::function<void(NG::DrawingContext & drawingContext)> drawBehindFun = nullptr;
    std::function<void(NG::DrawingContext & drawingContext)> drawContentFun = nullptr;
    std::function<void(NG::DrawingContext & drawingContext)> drawFrontFun = nullptr;
    std::function<void(NG::DrawingContext & drawingContext)> drawForegroundFun = nullptr;
    if (flag & FLAG_DRAW_BEHIND) {
        auto fnDrawBehindAni = std::make_shared<CommonModuleCallbackAni>(env, drawModifierRef);
        drawBehindFun = ConvertFnObjDrawBehindFun(vm, fnDrawBehindAni, drawModifierRef);
    }
    if (flag & FLAG_DRAW_CONTENT) {
        auto fnDrawContentAni = std::make_shared<CommonModuleCallbackAni>(env, drawModifierRef);
        drawContentFun = ConvertFnObjDrawContentFun(vm, fnDrawContentAni, drawModifierRef);
    }
    if (flag & FLAG_DRAW_FRONT) {
        auto fnDrawFrontAni = std::make_shared<CommonModuleCallbackAni>(env, drawModifierRef);
        drawFrontFun = ConvertFnObjDrawFrontFun(vm, fnDrawFrontAni, drawModifierRef);
    }
    if (flag & FLAG_DRAW_FOREGROUND) {
        auto fnDrawForegroundAni = std::make_shared<CommonModuleCallbackAni>(env, drawModifierRef);
        drawForegroundFun = ConvertFnObjDrawForeGroundFun(vm, fnDrawForegroundAni, drawModifierRef);
    }
    if (drawBehindFun != nullptr) {
        fnDrawBehindFun = &drawBehindFun;
    }
    if (drawContentFun != nullptr) {
        fnDrawContentFun = &drawContentFun;
    }
    if (drawFrontFun != nullptr) {
        fnDrawFrontFun = &drawFrontFun;
    }
    if (drawForegroundFun != nullptr) {
        fnDrawForegroundFun = &drawForegroundFun;
    }
    modifier->getArkUIAniDrawModifier()->setDrawModifier(
        ptr, flag, fnDrawBehindFun, fnDrawContentFun, fnDrawFrontFun, fnDrawForegroundFun);
}

ani_object CreateLayoutConstraintF(ani_env* env, const NG::LayoutConstraintF& constraintF)
{
    ani_status status;
    ani_object result = nullptr;
    ani_class layoutConstraintFClass;
    if ((status = env->FindClass("arkui.FrameNode.LayoutConstraintImpl", &layoutConstraintFClass)) != ANI_OK) {
        HILOGE("FindClass LayoutConstraint failed, %{public}d", status);
        return nullptr;
    }
    ani_method layoutConstraintFCtor;
    if ((status = env->Class_FindMethod(layoutConstraintFClass, "<ctor>", "dddddd:", &layoutConstraintFCtor)) !=
        ANI_OK) {
        HILOGE("Class_FindMethod CreateLayoutConstraintF ctor failed, %{public}d", status);
        return nullptr;
    }
    auto minSize = constraintF.minSize;
    auto maxSize = constraintF.maxSize;
    auto percentReference = constraintF.percentReference;
    if ((status = env->Object_New(layoutConstraintFClass, layoutConstraintFCtor, &result, maxSize.Width(),
        maxSize.Height(), minSize.Width(), minSize.Height(), percentReference.Width(),
        percentReference.Height())) != ANI_OK) {
        HILOGE("Create layoutConstraintFClass object failed, %{public}d", status);
        return nullptr;
    }
    return result;
}

std::function<void(NG::LayoutConstraintF& layoutConstraint)> ConvertFunOnMeasureFun(
    ani_vm* vm, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni, std::shared_ptr<ani_wref> frameNdoeWeakRef)
{
    return [vm, callbackAni, frameNdoeWeakRef](const NG::LayoutConstraintF& constraint) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        CHECK_NULL_VOID(env);
        auto layoutConstraintAni = CreateLayoutConstraintF(env, constraint);
        if (!layoutConstraintAni) {
            return;
        }
        ani_boolean released;
        ani_ref localFrameNodeRef;
        if (env->WeakReference_GetReference(*frameNdoeWeakRef, &released, &localFrameNodeRef) != ANI_OK) {
            HILOGE("get frameNodeRef fail GetReference failed");
            return;
        }
        if (released) {
            HILOGE("localFrameNodeRef released convert onMeasure function fail");
            return;
        }
        auto status = env->Object_CallMethodByName_Void(reinterpret_cast<ani_object>(localFrameNodeRef), "onMeasure",
            "C{arkui.FrameNode.LayoutConstraint}:", layoutConstraintAni);
        if (status != ANI_OK) {
            HILOGE("ConvertFunOnMeasureFun invoke fail status is %{public}d", status);
        }
    };
}

ani_object CreateLayoutOffset(ani_env* env, const NG::OffsetF& offset)
{
    ani_status status;
    ani_class nodePositionClass;
    if ((status = env->FindClass("arkui.FrameNode.NodePositionImpl", &nodePositionClass)) != ANI_OK) {
        HILOGE("FindClass Size failed, %{public}d", status);
        return nullptr;
    }
    ani_method nodePositionCtr;
    if ((status = env->Class_FindMethod(nodePositionClass, "<ctor>", "dd:", &nodePositionCtr)) != ANI_OK) {
        HILOGE("Class_FindMethod NodePositionImpl ctor failed, %{public}d", status);
        return nullptr;
    }
    ani_double x = offset.GetX();
    ani_double y = offset.GetY();
    ani_object offsetObj;
    if ((status = env->Object_New(nodePositionClass, nodePositionCtr, &offsetObj, x, y)) != ANI_OK) {
        HILOGE("Create Size object failed, %{public}d", status);
        return nullptr;
    }
    return offsetObj;
}

std::function<void(const NG::OffsetF& offset)> ConvertFunOnLayoutFun(
    ani_vm* vm, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni, std::shared_ptr<ani_wref> frameNdoeWeakRef)
{
    return [vm, callbackAni, frameNdoeWeakRef](const NG::OffsetF& offset) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);
        auto offsetAni = CreateLayoutOffset(env, offset);
        if (!offsetAni) {
            return;
        }
        ani_boolean released;
        ani_ref localFrameNodeRef;
        if (env->WeakReference_GetReference(*frameNdoeWeakRef, &released, &localFrameNodeRef) != ANI_OK) {
            HILOGE("get frameNodeRef fail GetReference failed");
            return;
        }
        if (released) {
            HILOGE("localFrameNodeRef released convert onDraw function fail");
            return;
        }
        auto callOnlayoutState = env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(localFrameNodeRef), "onLayout", "C{arkui.Graphics.Vector2}:", offsetAni);
        if (callOnlayoutState != ANI_OK) {
            HILOGE("call onLayout callback fail status is %{public}d", callOnlayoutState);
        }
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

std::function<void(NG::DrawingContext& drawingContext)> ConvertFnObjDrawCallbackFunInner(ani_vm* vm,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni, std::shared_ptr<ani_wref> frameNdoeWeakRef,
    ani_method onDrawMethod, ani_method onDrawWrapperMethod)
{
    return [vm, callbackAni, frameNdoeWeakRef, onDraw = onDrawMethod,
               onDrawWrapper = onDrawWrapperMethod](const NG::DrawingContext& context) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        CHECK_NULL_VOID(env);
        auto drawingContext = CreateDrawingContext(env, context);
        if (!drawingContext) {
            HILOGW("Create drawing context failed !");
            return;
        }
        ani_boolean released;
        ani_ref localFrameNodeRef;
        if (env->WeakReference_GetReference(*frameNdoeWeakRef, &released, &localFrameNodeRef) != ANI_OK) {
            HILOGE("get frameNodeRef fail GetReference failed");
            return;
        }
        if (released) {
            HILOGE("localFrameNodeRef released convert onDraw function fail");
            return;
        }
        env->Object_CallMethod_Void(reinterpret_cast<ani_object>(localFrameNodeRef), onDrawWrapper, drawingContext);
        env->Object_CallMethod_Void(reinterpret_cast<ani_object>(localFrameNodeRef), onDraw, drawingContext);
    };
}

void SetCustomCallbackWithCheck(ani_env* env, ani_object obj, ani_long ptr, ani_object frameNode)
{
    if (frameNode == nullptr) {
        HILOGE("frameNdoe is undefined.");
        return;
    }
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    ani_status status = ANI_OK;
    ani_type frameNodeType = nullptr;
    std::shared_ptr<ani_wref> frameNodeWeakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        env->WeakReference_Delete(*wref);
    });
    env->WeakReference_Create(frameNode, frameNodeWeakRef.get());
    if ((status = env->Object_GetType(frameNode, &frameNodeType)) != ANI_OK) {
        HILOGI("FrameNode Object_GetType fail");
        return;
    }
    auto frameNodeClass = static_cast<ani_class>(frameNodeType);
    ani_method getterMethod = nullptr;
    ani_method onDrawMethod = nullptr;
    if ((status = env->Class_FindMethod(frameNodeClass, "onDraw", "C{arkui.Graphics.DrawContext}:", &onDrawMethod)) !=
        ANI_OK) {
        HILOGI("Class_FindMethod onDraw failed, status : %{public}d", status);
    } else {
        ani_method onDrawWrapperMethod = nullptr;
        env->Class_FindMethod(frameNodeClass, "onDrawWrapper", "C{arkui.Graphics.DrawContext}:", &onDrawWrapperMethod);
        auto funcOnDrawAni = std::make_shared<CommonModuleCallbackAni>(env, frameNode);
        std::function<void(NG::DrawingContext & drawingContext)> onDrawFunc =
        ConvertFnObjDrawCallbackFunInner(vm, funcOnDrawAni, frameNodeWeakRef, onDrawMethod, onDrawWrapperMethod);
        void* fnDrawCallbackFun = &onDrawFunc;
        modifier->getCommonAniModifier()->setFrameNodeDrawCallback(env, ptr, fnDrawCallbackFun);
    }
    if ((status = env->Class_FindMethod(frameNodeClass, "onLayout", "C{arkui.Graphics.Vector2}:", &getterMethod)) !=
        ANI_OK) {
        HILOGI("Class_FindMethod onLayout failed, status : %{public}d", status);
        return;
    }
    if ((status = env->Class_FindMethod(
        frameNodeClass, "onMeasure", "C{arkui.FrameNode.LayoutConstraint}:", &getterMethod)) != ANI_OK) {
        HILOGI("Class_FindMethod onMeasure failed, status : %{public}d", status);
        return;
    }
    void* fnMeasureFun = nullptr;
    void* fnLayoutFun = nullptr;
    std::function<void(NG::LayoutConstraintF & layoutConstraint)> fnObjMeasureFun = nullptr;
    std::function<void(NG::OffsetF & position)> fnObjLayoutFun = nullptr;
    auto fnMeasureAni = std::make_shared<CommonModuleCallbackAni>(env, frameNode);
    fnObjMeasureFun = ConvertFunOnMeasureFun(vm, fnMeasureAni, frameNodeWeakRef);
    fnObjLayoutFun = ConvertFunOnLayoutFun(vm, fnMeasureAni, frameNodeWeakRef);
    fnMeasureFun = &fnObjMeasureFun;
    fnLayoutFun = &fnObjLayoutFun;
    modifier->getCommonAniModifier()->setCustomCallback(ptr, fnMeasureFun, fnLayoutFun);
    return;
}

void Invalidate(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getArkUIAniDrawModifier()->invalidate(env, ptr);
}

ani_long BuilderProxyNodeConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id)
{
    auto nodeId = reinterpret_cast<ArkUI_Int32>(id);
    ani_long nativeObj {};
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nativeObj);
    auto builderProxyNode = modifier->getCommonAniModifier()->builderProxyNodeConstruct(nodeId);
    CHECK_NULL_RETURN(builderProxyNode, nativeObj);
    return reinterpret_cast<ani_long>(builderProxyNode);
}

void RemoveComponentFromFrameNode(ani_env* env, ani_object obj, ani_long node, ani_long content)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getArkUIAniComponentConentModifier() || !env) {
        return;
    }
    modifier->getArkUIAniComponentConentModifier()->removeComponentFromFrameNode(node, content);
}

void AddComponentToFrameNode(ani_env* env, ani_object obj, ani_long node, ani_long content)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getArkUIAniComponentConentModifier() || !env) {
        return;
    }
    modifier->getArkUIAniComponentConentModifier()->addComponentToFrameNode(node, content);
}

ani_object GetSharedLocalStorage([[maybe_unused]] ani_env* env)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return nullptr;
    }
    ani_ref storage = modifier->getCommonAniModifier()->getSharedLocalStorage();
    if (storage) {
        ani_object storage_object = reinterpret_cast<ani_object>(storage);
        return storage_object;
    }
    return nullptr;
}

void SetBackgroundImagePixelMap([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object node,
    ani_object pixelMap, ani_int repeat)
{
#ifndef __linux__
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    auto pixelMapValue = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMap);
    if (!pixelMapValue) {
        return;
    }
    auto pixelMapPtr = reinterpret_cast<void*>(&pixelMapValue);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->setBackgroundImagePixelMap(
        env, arkNode, reinterpret_cast<ani_ref>(pixelMapPtr), repeat);
#endif
}
std::function<void(NG::LayoutConstraintF & layoutConstraint)> ConvertFnObjMeasureFun(ani_vm* vm,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    return [vm, callbackAni](const NG::LayoutConstraintF& context) -> void {
            CHECK_NULL_VOID(vm);
            CHECK_NULL_VOID(callbackAni);
            ani_env* env = nullptr;
            auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
            CHECK_NULL_VOID(env);

            std::vector<ani_ref> params = {};
            auto width1 = AniUtils::FloatToNumberObject(env, context.maxSize.Width());
            auto height1 = AniUtils::FloatToNumberObject(env, context.maxSize.Height());
            auto width2 = AniUtils::FloatToNumberObject(env, context.minSize.Width());
            auto height2 = AniUtils::FloatToNumberObject(env, context.minSize.Height());
            auto width3 = AniUtils::FloatToNumberObject(env, context.percentReference.Width());
            auto height3 = AniUtils::FloatToNumberObject(env, context.percentReference.Height());
            params.emplace_back((ani_ref)width1);
            params.emplace_back((ani_ref)height1);
            params.emplace_back((ani_ref)width2);
            params.emplace_back((ani_ref)height2);
            params.emplace_back((ani_ref)width3);
            params.emplace_back((ani_ref)height3);
            ani_ref ret = nullptr;
            callbackAni->Call(env, params.size(), params.data(), &ret);
            if (attachCurrentThreadStatus == ANI_OK) {
                vm->DetachCurrentThread();
            }
        };
}

std::function<void(NG::OffsetF& position)> ConvertFnObjLayoutFun(ani_vm* vm,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    return [vm, callbackAni](const NG::OffsetF& context) -> void {
            CHECK_NULL_VOID(vm);
            CHECK_NULL_VOID(callbackAni);
            ani_env* env = nullptr;
            auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
            CHECK_NULL_VOID(env);

            std::vector<ani_ref> params = {};
            params.emplace_back((ani_ref)AniUtils::CreateDoubleObject(env, context.GetX()));
            params.emplace_back((ani_ref)AniUtils::CreateDoubleObject(env, context.GetY()));
            ani_ref ret = nullptr;
            callbackAni->Call(env, params.size(), params.data(), &ret);
            if (attachCurrentThreadStatus == ANI_OK) {
                vm->DetachCurrentThread();
            }
        };
}

void SetCustomCallback(ani_env* env, ani_object obj, ani_long ptr,
    ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    auto customFuncExisted = false;
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    void* fnMeasureFun = nullptr;
    void* fnLayoutFun = nullptr;
    std::function<void(NG::LayoutConstraintF & layoutConstraint)> fnObjMeasureFun = nullptr;
    std::function<void(NG::OffsetF& position)> fnObjLayoutFun = nullptr;
    if (fnObjMeasure != nullptr) {
        customFuncExisted = true;
        ani_ref fnObjMeasureAniRef = static_cast<ani_ref>(fnObjMeasure);
        auto fnObjMeasureAni = std::make_shared<CommonModuleCallbackAni>(env, fnObjMeasureAniRef);
        fnObjMeasureFun = ConvertFnObjMeasureFun(vm, fnObjMeasureAni);
    }
    if (fnObjLayout != nullptr) {
        customFuncExisted = true;
        ani_ref fnObjLayoutAniRef = static_cast<ani_ref>(fnObjLayout);
        auto fnObjLayoutAni = std::make_shared<CommonModuleCallbackAni>(env, fnObjLayoutAniRef);
        fnObjLayoutFun = ConvertFnObjLayoutFun(vm, fnObjLayoutAni);
    }
    if (!customFuncExisted) {
        return;
    }
    if (fnObjMeasureFun != nullptr) {
        fnMeasureFun = &fnObjMeasureFun;
    }
    if (fnObjLayoutFun != nullptr) {
        fnLayoutFun = &fnObjLayoutFun;
    }
    modifier->getCommonAniModifier()->setCustomCallback(ptr, fnMeasureFun, fnLayoutFun);
}

ani_int RequireArkoalaNodeId(ani_env* env, ani_object obj, ani_int capacity)
{
    auto idCapacity = reinterpret_cast<ArkUI_Int32>(capacity);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, -1);
    auto cursor = modifier->getCommonAniModifier()->requireArkoalaNodeId(idCapacity);
    return cursor;
}

ani_long GetNodePtrWithPeerPtr(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, -1);
    auto ret = modifier->getCommonAniModifier()->getNodePtrWithPeerPtr(ptr);
    return ret;
}
ani_int GetNodeIdWithNodePtr(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, -1);
    auto ret = modifier->getCommonAniModifier()->getNodeIdWithNodePtr(ptr);
    return ret;
}

ani_int GetNodeIdWithPeerPtr(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, -1);
    auto ret = modifier->getCommonAniModifier()->getNodeIdWithPeerPtr(ptr);
    return ret;
}

ani_long CreateRenderNodePeerWithNodePtr(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, -1);
    auto peerPtr = modifier->getCommonAniModifier()->createRenderNodePeerWithNodePtr(ptr);
    return peerPtr;
}

ani_long ToColorLong(ani_env* env, ani_object obj, ani_int color)
{
    unsigned int uClr = static_cast<unsigned int>(color);
    int64_t clr = static_cast<int64_t>(uClr);
    return clr;
}
ani_int ToColorInt(ani_env* env, ani_object obj, ani_long color)
{
    unsigned int uClr = static_cast<unsigned int>(color);
    int32_t clr = static_cast<int32_t>(uClr);
    return clr;
}

ani_int CreateWindowFreeContainer(ani_env *env, [[maybe_unused]]ani_object object, ani_object context)
{
#if !defined(PREVIEW)
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return -1;
    }
    auto nativeContext = OHOS::AbilityRuntime::GetStageModeContext(env, context);
    return modifier->getCommonAniModifier()->createWindowFreeContainer(env, nativeContext);
#else
    return -1;
#endif
}

void DestroyWindowFreeContainer([[maybe_unused]]ani_env *env, [[maybe_unused]]ani_object object, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->destroyWindowFreeContainer(id);
}

ani_int CheckIsUIThread([[maybe_unused]] ani_env* env, ani_object obj, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    return modifier->getCommonAniModifier()->checkIsUIThread(id);
}

ani_int IsDebugMode([[maybe_unused]] ani_env* env, ani_object obj, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return false;
    }
    return modifier->getCommonAniModifier()->isDebugMode(id);
}
void OnMeasureInnerMeasure(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->onMeasureInnerMeasure(ptr);
}

void OnLayoutInnerLayout(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->onLayoutInnerLayout(ptr);
}

void SetParallelScoped(ani_env* env, ani_object obj, ani_boolean parallel)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->setParallelScoped(parallel);
}

void ConvertRemoveCallbackFun(
    ani_vm* vm, std::function<void()>& callback, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    callback = [vm, callbackAni]() {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        std::vector<ani_ref> args = {};
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void ConvertGetCallbackFun(ani_vm* vm, std::function<std::string(const std::string&)>& callback,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    callback = [vm, callbackAni](const std::string& key) -> std::string {
        std::string value;
        CHECK_NULL_RETURN(vm, value);
        CHECK_NULL_RETURN(callbackAni, value);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_RETURN(env, value);
        auto keyAni = AniUtils::StdStringToANIString(env, key);
        std::vector<ani_ref> args = { *keyAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
            ani_string resultRef = static_cast<ani_string>(ret);
            value = AniUtils::ANIStringToStdString(env, resultRef);
            return value;
        } else {
            return value;
        }
    };
}

void SetCustomPropertyCallBack(
    ani_env* env, ani_object aniClass, ani_long node, ani_fn_object removeCallback, ani_fn_object getCallback)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    ArkUINodeHandle frameNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(frameNode);

    ani_ref removeCallbackAniRef = static_cast<ani_ref>(removeCallback);
    ani_ref getCallbackAniRef = static_cast<ani_ref>(getCallback);
    auto removeCallbackAni = std::make_shared<CommonModuleCallbackAni>(env, removeCallbackAniRef);
    auto getCallbackAni = std::make_shared<CommonModuleCallbackAni>(env, getCallbackAniRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    std::function<void()> removeCallbackFun = nullptr;
    std::function<std::string(const std::string&)> getCallbackFun = nullptr;
    ConvertRemoveCallbackFun(vm, removeCallbackFun, removeCallbackAni);
    ConvertGetCallbackFun(vm, getCallbackFun, getCallbackAni);

    modifier->getCommonAniModifier()->setCustomPropertyCallBack(
        frameNode, std::move(removeCallbackFun), std::move(getCallbackFun));
}

ani_string GetCustomProperty(
    ani_env* env, ani_object aniClass, ani_long node, ani_string aniKey)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    ArkUINodeHandle frameNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto strKey = AniUtils::ANIStringToStdString(env, aniKey);
    auto ret = modifier->getCommonAniModifier()->getCustomProperty(env, frameNode, strKey);
    if (ret.has_value()) {
        auto retValue = AniUtils::StdStringToANIString(env, ret.value());
        if (retValue) {
            return *retValue;
        }
    }
    return nullptr;
}

void GetAlignmentEnum(ani_env* env, ani_object align, AniOverlayOptions& opt)
{
    ani_enum enumType;
    if (ANI_OK != env->FindEnum("arkui.component.enums.Alignment", &enumType)) {
        return;
    }

    ani_boolean isAlignment = ANI_FALSE;
    if (ANI_OK != env->Object_InstanceOf(align, enumType, &isAlignment)) {
        return;
    }

    if (!isAlignment) {
        return;
    }

    ani_enum_item enumItem = static_cast<ani_enum_item>(align);
    ani_int value;
    if (ANI_OK != env->EnumItem_GetValue_Int(enumItem, &value)) {
        return;
    }
    opt.alignment = static_cast<int32_t>(value);
}

void ParseOverlayOptions(ani_env* env, ani_object options, AniOverlayOptions& opt)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(options, &isUndefined);
    if (isUndefined) {
        return;
    }
    ani_ref align;
    env->Object_GetPropertyByName_Ref(options, "align", &align);
    env->Reference_IsUndefined(align, &isUndefined);
    if (!isUndefined) {
        GetAlignmentEnum(env, static_cast<ani_object>(align), opt);
    }
    ani_ref overlayOffset;
    env->Object_GetPropertyByName_Ref(options, "offset", &overlayOffset);
    env->Reference_IsUndefined(overlayOffset, &isUndefined);
    if (!isUndefined) {
        ani_object offset = static_cast<ani_object>(overlayOffset);
        ani_ref x;
        if (ANI_OK == env->Object_GetPropertyByName_Ref(offset, "x", &x)) {
            ani_double param_value;
            env->Object_CallMethodByName_Double(static_cast<ani_object>(x), "toDouble", ":d", &param_value);
            opt.x = static_cast<float>(param_value);
        }
        ani_ref y;
        if (ANI_OK == env->Object_GetPropertyByName_Ref(offset, "y", &y)) {
            ani_double param_value;
            env->Object_CallMethodByName_Double(static_cast<ani_object>(y), "toDouble", ":d", &param_value);
            opt.y = static_cast<float>(param_value);
        }
    }
}

void SetOverlayComponentContent(ani_env* env, ani_object obj, ani_long ptr, ani_long buildNodePtr, ani_object options)
{
    const auto* modifier = GetNodeAniModifier();
    if (!env || !modifier) {
        return;
    }
    AniOverlayOptions opt;
    ParseOverlayOptions(env, options, opt);
    modifier->getCommonAniModifier()->setOverlayComponent(ptr, buildNodePtr, opt);
}
ani_double Vp2px(ani_env* env, ani_object obj, ani_double value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->vp2px(value, instanceId);
}

ani_double Px2vp(ani_env* env, ani_object obj, ani_double value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->px2vp(value, instanceId);
}

ani_double Fp2px(ani_env* env, ani_object obj, ani_double value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->fp2px(value, instanceId);
}

ani_double Px2fp(ani_env* env, ani_object obj, ani_double value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->px2fp(value, instanceId);
}

ani_double Lpx2px(ani_env* env, ani_object obj, ani_double value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->lpx2px(value, instanceId);
}

ani_double Px2lpx(ani_env* env, ani_object obj, ani_double value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->px2lpx(value, instanceId);
}

ani_string getWindowName(ani_env* env, ani_object obj, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    auto ret = modifier->getCommonAniModifier()->getWindowName(instanceId);
    if (ret.has_value()) {
        auto retValue = AniUtils::StdStringToANIString(env, ret.value());
        if (retValue) {
            return *retValue;
        }
    }
    return nullptr;
}

ani_int getWindowWidthBreakpoint(ani_env* env, ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return -1;
    }
    return modifier->getCommonAniModifier()->getWindowWidthBreakpoint();
}

ani_int getWindowHeightBreakpoint(ani_env* env, ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return -1;
    }
    return modifier->getCommonAniModifier()->getWindowHeightBreakpoint();
}

void* TransferKeyEventPointer(ani_env* env, ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->transferKeyEventPointer(pointer);
}
void* CreateKeyEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->createKeyEventAccessorWithPointer(pointer);
}
void* CreateEventTargetInfoAccessor(ani_env* env, [[maybe_unused]] ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->createEventTargetInfoAccessor();
}
void EventTargetInfoAccessorWithId(ani_env* env, [[maybe_unused]] ani_object obj, ani_long input, ani_string id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    auto idValue = AniUtils::ANIStringToStdString(env, id);
    return modifier->getCommonAniModifier()->eventTargetInfoAccessorWithId(env, input, idValue);
}
void* CreateScrollableTargetInfoAccessor(ani_env* env, [[maybe_unused]] ani_object obj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->createScrollableTargetInfoAccessor();
}
void ScrollableTargetInfoAccessorWithId(ani_env* env, [[maybe_unused]] ani_object obj, ani_long input, ani_string id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    auto idValue = AniUtils::ANIStringToStdString(env, id);
    return modifier->getCommonAniModifier()->scrollableTargetInfoAccessorWithId(env, input, idValue);
}
void ScrollableTargetInfoAccessorWithPointer(
    ani_env* env, [[maybe_unused]] ani_object obj, ani_long input, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    return modifier->getCommonAniModifier()->scrollableTargetInfoAccessorWithPointer(input, pointer);
}
void* TransferScrollableTargetInfoPointer(ani_env* env, ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->transferScrollableTargetInfoPointer(pointer);
}
void* CreateDragEventAccessorWithPointer(ani_env* env, ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->createDragEventAccessor(pointer);
}

void* GetDragEventPointer(ani_env* env, ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return 0;
    }
    return modifier->getCommonAniModifier()->getDragEventPointer(pointer);
}
void* CreateTouchEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->transferTouchEventPointer(pointer);
}

void* CreateMouseEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->transferMouseEventPointer(pointer);
}

void* CreateAxisEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->transferAxisEventPointer(pointer);
}

void* CreateClickEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->transferClickEventPointer(pointer);
}

void* CreateHoverEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->transferHoverEventPointer(pointer);
}

void* GetTouchEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long touchEventPeer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->getTouchEventPointer(touchEventPeer);
}

void* GetMouseEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long mouseEventPeer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->getMouseEventPointer(mouseEventPeer);
}

void* GetAxisEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long axisEventPeer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->getAxisEventPointer(axisEventPeer);
}

void* GetClickEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long clickEventPeer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->getMouseEventPointer(clickEventPeer);
}

void* GetHoverEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long hoverEventPeer)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return nullptr;
    }
    return modifier->getCommonAniModifier()->getMouseEventPointer(hoverEventPeer);
}

void FrameNodeMarkDirtyNode(ani_env* env, ani_object obj, ani_long ptr)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getCommonAniModifier() || !env) {
        return;
    }
    modifier->getCommonAniModifier()->frameNodeMarkDirtyNode(env, ptr);
}

ani_int GetStringColorValue(ani_env* env, ani_object aniClass, ani_string src)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    auto srcString = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(src));
    return modifier->getCommonAniModifier()->getColorValueByString(srcString);
}

ani_int GetNumberColorValue(ani_env* env, ani_object aniClass, ani_double src)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    return modifier->getCommonAniModifier()->getColorValueByNumber(static_cast<uint32_t>(src));
}

void SendThemeToNative(ani_env* env, ani_object aniClass, ani_long thisArray, ani_double thisLength, ani_int id)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    std::vector<Ark_ResourceColor> colors = GetResourceColorArray(thisArray, thisLength);
    modifier->getCommonAniModifier()->sendThemeToNative(env, colors, id);
}

void RemoveThemeInNative(ani_env* env, ani_object aniClass, ani_int withThemeId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->removeThemeInNative(env, withThemeId);
}

void SetDefaultTheme(ani_env* env, ani_object aniClass, ani_long thisArray, ani_double thisLength, ani_boolean isDark)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    std::vector<Ark_ResourceColor> colorArray = GetResourceColorArray(thisArray, thisLength);
    modifier->getCommonAniModifier()->setDefaultTheme(env, colorArray, isDark);
}

void UpdateColorMode(ani_env* env, ani_object aniClass, ani_int colorMode)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->updateColorMode(colorMode);
}

void RestoreColorMode(ani_env* env, ani_object aniClass)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->restoreColorMode();
}

void SetThemeScopeId(ani_env* env, ani_object aniClass, ani_int themeScopeId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->setThemeScopeId(env, themeScopeId);
}

std::function<void()> ConvertOnThemeScopeDestroyFun(
    ani_vm* vm, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    return [vm, callbackAni]() {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        std::vector<ani_ref> args = {};
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void CreateAndBindTheme(ani_env* env, ani_object aniClass, ani_int themeScopeId, ani_int themeId, ani_long thisArray,
    ani_double thisLength, ani_int colorMode, ani_fn_object onThemeScopeDestroy)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    std::vector<Ark_ResourceColor> colors = GetResourceColorArray(thisArray, thisLength);
    void* fnOnThemeScopeDestroyFun = nullptr;
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    std::function<void()> onThemeScopeDestroyFun = nullptr;
    if (onThemeScopeDestroy) {
        ani_ref onThemeScopeDestroyAniRef = static_cast<ani_ref>(onThemeScopeDestroy);
        auto onThemeScopeDestroyAni = std::make_shared<CommonModuleCallbackAni>(env, onThemeScopeDestroyAniRef);
        onThemeScopeDestroyFun = ConvertOnThemeScopeDestroyFun(vm, onThemeScopeDestroyAni);
    }
    if (onThemeScopeDestroyFun != nullptr) {
        fnOnThemeScopeDestroyFun = &onThemeScopeDestroyFun;
    }
    modifier->getCommonAniModifier()->createAndBindTheme(
        env, themeScopeId, themeId, colors, colorMode, fnOnThemeScopeDestroyFun);
}

void ApplyParentThemeScopeId(ani_env* env, ani_object aniClass, ani_long self, ani_long parent)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->applyParentThemeScopeId(env, self, parent);
}

void SetImageCacheCount(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_int value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->setImageCacheCount(value, instanceId);
}

void SetImageRawDataCacheSize(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_int value, ani_int instanceId)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return;
    }
    modifier->getCommonAniModifier()->setImageRawDataCacheSize(value, instanceId);
}

ani_long ExtractorsToDrawContextPtr(ani_env* env, ani_object aniClass, ani_object ptr)
{
    return {};
}
ani_object ExtractorsFromDrawContextPtr(ani_env* env, ani_object aniClass, ani_long ptr)
{
    auto contextPtr = reinterpret_cast<NG::DrawingContext *>(ptr);
    CHECK_NULL_RETURN(contextPtr, {});
    return CreateDrawingContext(env, *contextPtr);
}
} // namespace OHOS::Ace::Ani
