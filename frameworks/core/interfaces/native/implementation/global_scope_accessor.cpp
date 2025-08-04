/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "global_scope_animation_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScopeAccessor {
Ark_Resource $rImpl(const Ark_String* value,
                    const Array_Opt_Object* params)
{
    return {};
}
Ark_Resource $rawfileImpl(const Ark_String* value)
{
    return {};
}
void AnimateToImpl(const Ark_AnimateParam* value,
                   const Callback_Void* event)
{
    AnimateToInner(value, event, false);
}
void AnimateToImmediatelyImpl(const Ark_AnimateParam* value,
                              const Callback_Void* event)
{
    AnimateToInner(value, event, true);
}
Ark_BorderRadiuses BorderRadiusesImpl(const Ark_Number* all)
{
    return {};
}
Ark_Edges BorderStylesImpl(Ark_BorderStyle all)
{
    return {};
}
void CursorControl_restoreDefaultImpl()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext]() { pipelineContext->RestoreDefault(0, MouseStyleChangeReason::USER_SET_MOUSESTYLE); },
        TaskExecutor::TaskType::UI, "ArkUIJsRestoreDefault");
}
void CursorControl_setCursorImpl(Ark_pointer_PointerStyle value)
{
    int32_t intValue = static_cast<int32_t>(value);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, intValue]() { pipelineContext->SetCursor(intValue); },
        TaskExecutor::TaskType::UI, "ArkUIJsSetCursor");
}
Ark_curves_ICurve Curves_cubicBezierCurveImpl(const Ark_Number* x1,
                                              const Ark_Number* y1,
                                              const Ark_Number* x2,
                                              const Ark_Number* y2)
{
    return {};
}
Ark_curves_ICurve Curves_customCurveImpl(const curves_Callback_Number_Number* interpolate)
{
    return {};
}
Ark_curves_ICurve Curves_initCurveImpl(const Opt_curves_Curve* curve)
{
    return {};
}
Ark_curves_ICurve Curves_interpolatingSpringImpl(const Ark_Number* velocity,
                                                 const Ark_Number* mass,
                                                 const Ark_Number* stiffness,
                                                 const Ark_Number* damping)
{
    return {};
}
Ark_curves_ICurve Curves_responsiveSpringMotionImpl(const Opt_Number* response,
                                                    const Opt_Number* dampingFraction,
                                                    const Opt_Number* overlapDuration)
{
    return {};
}
Ark_curves_ICurve Curves_springCurveImpl(const Ark_Number* velocity,
                                         const Ark_Number* mass,
                                         const Ark_Number* stiffness,
                                         const Ark_Number* damping)
{
    return {};
}
Ark_curves_ICurve Curves_springMotionImpl(const Opt_Number* response,
                                          const Opt_Number* dampingFraction,
                                          const Opt_Number* overlapDuration)
{
    return {};
}
Ark_curves_ICurve Curves_stepsCurveImpl(const Ark_Number* count,
                                        Ark_Boolean end)
{
    return {};
}
Ark_Edges EdgeColorsImpl(const Ark_Number* all)
{
    return {};
}
Ark_Edges EdgeWidthsImpl(const Ark_Number* all)
{
    return {};
}
Ark_Boolean FocusControl_requestFocusImpl(const Ark_String* value)
{
    bool result = false;
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Boolean>(result));
    std::string inspectorKey = Converter::Convert<std::string>(*value);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, Converter::ArkValue<Ark_Boolean>(result));
    if (!pipelineContext->GetTaskExecutor()) {
        return Converter::ArkValue<Ark_Boolean>(result);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, inspectorKey, &result]() { result = pipelineContext->RequestFocus(inspectorKey); },
        TaskExecutor::TaskType::UI, "ArkUIJsRequestFocus");
    return Converter::ArkValue<Ark_Boolean>(result);
}
Ark_font_UIFontConfig Font_getUIFontConfigImpl()
{
    FontConfigJsonInfo fontConfigJsonInfo;
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->GetUIFontConfig(fontConfigJsonInfo);
    }
    return Converter::ArkValue<Ark_font_UIFontConfig>(fontConfigJsonInfo, Converter::FC);
}
Ark_ComponentInfo GetRectangleByIdImpl(const Ark_String* id)
{
    return {};
}
void PostCardActionImpl(const Ark_Object* component,
                        const Ark_Object* action)
{
}
void Profiler_registerVsyncCallbackImpl(const Profiler_Callback_String_Void* callback_)
{
    CHECK_NULL_VOID(callback_);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto onVsyncFunc = [arkCallback = CallbackHelper(*callback_)](const std::string& value) {
        auto arkStringValue = Converter::ArkValue<Ark_String>(value);
        arkCallback.Invoke(arkStringValue);
    };
    pipelineContext->SetOnVsyncProfiler(onVsyncFunc);
}
void Profiler_unregisterVsyncCallbackImpl()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->ResetOnVsyncProfiler();
}
Ark_Number Px2vpImpl(const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    double pxValue = Converter::Convert<double>(*value);
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density) || density == 0) {
        return Converter::ArkValue<Ark_Number>(0);
    }
    double vpValue = pxValue / density;
    return Converter::ArkValue<Ark_Number>(vpValue);
}
void SetAppBgColorImpl(const Ark_String* value)
{
    CHECK_NULL_VOID(value);
    auto backgroundColorStr = Converter::Convert<std::string>(*value);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetAppBgColor(Color::ColorFromString(backgroundColorStr));
}
void Text_getFontDescriptorByFullNameImpl(Ark_VMContext vmContext,
                                          Ark_AsyncWorkerPtr asyncWorker,
                                          const Ark_String* fullName,
                                          Ark_text_SystemFontType fontType,
                                          const Callback_Opt_FontDescriptor_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void Text_getSystemFontFullNamesByTypeImpl(Ark_VMContext vmContext,
                                           Ark_AsyncWorkerPtr asyncWorker,
                                           Ark_text_SystemFontType fontType,
                                           const Callback_Opt_Array_String_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void Text_matchFontDescriptorsImpl(Ark_VMContext vmContext,
                                   Ark_AsyncWorkerPtr asyncWorker,
                                   const Ark_text_FontDescriptor* desc,
                                   const Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
Ark_uiEffect_BrightnessBlender UiEffect_createBrightnessBlenderImpl(const Ark_uiEffect_BrightnessBlenderParam* param)
{
    return {};
}
Ark_uiEffect_VisualEffect UiEffect_createEffectImpl()
{
    return {};
}
Ark_Number Vp2pxImpl(const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    double vpValue = Converter::Convert<double>(*value);
    double density = PipelineBase::GetCurrentDensity();
    double pxValue = vpValue * density;
    return Converter::ArkValue<Ark_Number>(pxValue);
}
} // GlobalScopeAccessor
const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor()
{
    static const GENERATED_ArkUIGlobalScopeAccessor GlobalScopeAccessorImpl {
        GlobalScopeAccessor::$rImpl,
        GlobalScopeAccessor::$rawfileImpl,
        GlobalScopeAccessor::AnimateToImpl,
        GlobalScopeAccessor::AnimateToImmediatelyImpl,
        GlobalScopeAccessor::BorderRadiusesImpl,
        GlobalScopeAccessor::BorderStylesImpl,
        GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
        GlobalScopeAccessor::CursorControl_setCursorImpl,
        GlobalScopeAccessor::Curves_cubicBezierCurveImpl,
        GlobalScopeAccessor::Curves_customCurveImpl,
        GlobalScopeAccessor::Curves_initCurveImpl,
        GlobalScopeAccessor::Curves_interpolatingSpringImpl,
        GlobalScopeAccessor::Curves_responsiveSpringMotionImpl,
        GlobalScopeAccessor::Curves_springCurveImpl,
        GlobalScopeAccessor::Curves_springMotionImpl,
        GlobalScopeAccessor::Curves_stepsCurveImpl,
        GlobalScopeAccessor::EdgeColorsImpl,
        GlobalScopeAccessor::EdgeWidthsImpl,
        GlobalScopeAccessor::FocusControl_requestFocusImpl,
        GlobalScopeAccessor::Font_getUIFontConfigImpl,
        GlobalScopeAccessor::GetRectangleByIdImpl,
        GlobalScopeAccessor::PostCardActionImpl,
        GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
        GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
        GlobalScopeAccessor::Px2vpImpl,
        GlobalScopeAccessor::SetAppBgColorImpl,
        GlobalScopeAccessor::Text_getFontDescriptorByFullNameImpl,
        GlobalScopeAccessor::Text_getSystemFontFullNamesByTypeImpl,
        GlobalScopeAccessor::Text_matchFontDescriptorsImpl,
        GlobalScopeAccessor::UiEffect_createBrightnessBlenderImpl,
        GlobalScopeAccessor::UiEffect_createEffectImpl,
        GlobalScopeAccessor::Vp2pxImpl,
    };
    return &GlobalScopeAccessorImpl;
}

}
