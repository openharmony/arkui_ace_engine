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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "global_scope_animation_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScopeAccessor {
Ark_Context GetContextImpl(const Opt_CustomObject* component)
{
    return {};
}
void PostCardActionImpl(const Ark_CustomObject* component,
                        const Ark_CustomObject* action)
{
}
Ark_Resource Dollar_rImpl(const Ark_String* value,
                          const Array_CustomObject* params)
{
    return {};
}
Ark_Resource Dollar_rawfileImpl(const Ark_String* value)
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
Ark_Number Vp2pxImpl(const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    double vpValue = Converter::Convert<double>(*value);
    double density = PipelineBase::GetCurrentDensity();
    double pxValue = vpValue * density;
    return Converter::ArkValue<Ark_Number>(pxValue);
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
Ark_Number Fp2pxImpl(const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    double density = PipelineBase::GetCurrentDensity();
    double fpValue = Converter::Convert<double>(*value);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, invalid);
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double pxValue = fpValue * density * fontScale;
    return Converter::ArkValue<Ark_Number>(pxValue);
}
Ark_Number Px2fpImpl(const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return Converter::ArkValue<Ark_Number>(0);
    }
    double pxValue = Converter::Convert<double>(*value);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, invalid);
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double ratio = density * fontScale;
    double fpValue = pxValue / ratio;
    return Converter::ArkValue<Ark_Number>(fpValue);
}
Ark_Number Lpx2pxImpl(const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, invalid);

    auto pipelineContext = container->GetPipelineContext();
#ifdef ARKUI_CAPI_UNITTEST
    CHECK_NULL_RETURN(pipelineContext, invalid);
    auto width = pipelineContext->GetCurrentWindowRect().Width();
    static WindowConfig windowConfig;
#else
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, invalid);
    auto width = window->GetCurrentWindowRect().Width();
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, invalid);
    auto windowConfig = frontend->GetWindowConfig();
#endif // ARKUI_CAPI_UNITTEST
    if (pipelineContext && pipelineContext->IsContainerModalVisible()) {
        int32_t multiplier = 2;
        width -= multiplier * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx();
    }
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }
    double lpxValue = Converter::Convert<double>(*value);
    double pxValue = lpxValue * windowConfig.designWidthScale;
    return Converter::ArkValue<Ark_Number>(pxValue);
}
Ark_Number Px2lpxImpl(const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, invalid);

    auto pipelineContext = container->GetPipelineContext();
#ifdef ARKUI_CAPI_UNITTEST
    CHECK_NULL_RETURN(pipelineContext, invalid);
    auto width = pipelineContext->GetCurrentWindowRect().Width();
    static WindowConfig windowConfig;
#else
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, invalid);
    auto width = window->GetCurrentWindowRect().Width();
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, invalid);
    auto windowConfig = frontend->GetWindowConfig();
#endif // ARKUI_CAPI_UNITTEST
    if (pipelineContext && pipelineContext->IsContainerModalVisible()) {
        int32_t multiplier = 2;
        width -= multiplier * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx();
    }
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }
    double pxValue = Converter::Convert<double>(*value);
    double lpxValue = pxValue / windowConfig.designWidthScale;
    return Converter::ArkValue<Ark_Number>(lpxValue);
}
Ark_CustomObject GetInspectorNodesImpl()
{
    return {};
}
Ark_CustomObject GetInspectorNodeByIdImpl(const Ark_Number* id)
{
    return {};
}
void SetAppBgColorImpl(const Ark_String* value)
{
}
void Profiler_registerVsyncCallbackImpl(const Profiler_Callback_String_Void* callback_)
{
}
void Profiler_unregisterVsyncCallbackImpl()
{
}
void CursorControl_setCursorImpl(Ark_PointerStyle value)
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
void CursorControl_restoreDefaultImpl()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    // pipelineContext->GetTaskExecutor()->PostSyncTask(
    //     [pipelineContext]() { pipelineContext->RestoreDefault(); },
    //     TaskExecutor::TaskType::UI, "ArkUIJsRestoreDefault");
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
} // GlobalScopeAccessor
const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor()
{
    static const GENERATED_ArkUIGlobalScopeAccessor GlobalScopeAccessorImpl {
        GlobalScopeAccessor::GetContextImpl,
        GlobalScopeAccessor::PostCardActionImpl,
        GlobalScopeAccessor::Dollar_rImpl,
        GlobalScopeAccessor::Dollar_rawfileImpl,
        GlobalScopeAccessor::AnimateToImpl,
        GlobalScopeAccessor::AnimateToImmediatelyImpl,
        GlobalScopeAccessor::Vp2pxImpl,
        GlobalScopeAccessor::Px2vpImpl,
        GlobalScopeAccessor::Fp2pxImpl,
        GlobalScopeAccessor::Px2fpImpl,
        GlobalScopeAccessor::Lpx2pxImpl,
        GlobalScopeAccessor::Px2lpxImpl,
        GlobalScopeAccessor::GetInspectorNodesImpl,
        GlobalScopeAccessor::GetInspectorNodeByIdImpl,
        GlobalScopeAccessor::SetAppBgColorImpl,
        GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
        GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
        GlobalScopeAccessor::CursorControl_setCursorImpl,
        GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
        GlobalScopeAccessor::FocusControl_requestFocusImpl,
    };
    return &GlobalScopeAccessorImpl;
}

struct GlobalScopePeer {
    virtual ~GlobalScopePeer() = default;
};
}
