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

#include "core/components_ng/base/frame_node.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

struct GlobalScopePeer {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GlobalScope_commonAccessor {
void DestroyPeerImpl(GlobalScope_commonPeer* peer)
{
    auto commonPeer = reinterpret_cast<GlobalScopePeer*>(peer);
    if (commonPeer) {
        delete commonPeer;
    }
}
Ark_NativePointer CtorImpl()
{
    return new GlobalScopePeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer GetContextImpl(const Opt_CustomObject* component)
{
    return nullptr;
}
void PostCardActionImpl(const Ark_CustomObject* component,
                        const Ark_CustomObject* action)
{
}
Ark_NativePointer Dollar_rImpl(const Ark_String* value,
                               const Array_CustomObject* params)
{
    return nullptr;
}
Ark_NativePointer Dollar_rawfileImpl(const Ark_String* value)
{
    return nullptr;
}
void AnimateToImpl(const Ark_AnimateParam* value,
                   const Callback_Void* event)
{
}
void AnimateToImmediatelyImpl(const Ark_AnimateParam* value,
                              const Callback_Void* event)
{
}
Ark_Int32 Vp2pxImpl(const Ark_Number* value)
{
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Int32>(0));
    double vpValue = Converter::Convert<double>(*value);
    double density = PipelineBase::GetCurrentDensity();
    double pxValue = vpValue * density;
    return static_cast<Ark_Int32>(pxValue);
}
Ark_Int32 Px2vpImpl(const Ark_Number* value)
{
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Int32>(0));
    double pxValue = Converter::Convert<double>(*value);
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density) || density == 0) {
        return Converter::ArkValue<Ark_Int32>(0);
    }
    double vpValue = pxValue / density;
    return static_cast<Ark_Int32>(vpValue);
}
Ark_Int32 Fp2pxImpl(const Ark_Number* value)
{
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Int32>(0));
    double density = PipelineBase::GetCurrentDensity();
    double fpValue = Converter::Convert<double>(*value);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, Converter::ArkValue<Ark_Int32>(0));
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double pxValue = fpValue * density * fontScale;
    return static_cast<Ark_Int32>(pxValue);
}
Ark_Int32 Px2fpImpl(const Ark_Number* value)
{
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Int32>(0));
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return Converter::ArkValue<Ark_Int32>(0);
    }
    double pxValue = Converter::Convert<double>(*value);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, Converter::ArkValue<Ark_Int32>(0));
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double ratio = density * fontScale;
    double fpValue = pxValue / ratio;
    return static_cast<Ark_Int32>(fpValue);
}
Ark_Int32 Lpx2pxImpl(const Ark_Number* value)
{
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Int32>(0));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, Converter::ArkValue<Ark_Int32>(0));

    auto pipelineContext = container->GetPipelineContext();
#ifdef ARKUI_CAPI_UNITTEST
    CHECK_NULL_RETURN(pipelineContext, Converter::ArkValue<Ark_Int32>(0));
    auto width = pipelineContext->GetCurrentWindowRect().Width();
    static WindowConfig windowConfig;
#else
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, Converter::ArkValue<Ark_Int32>(0));
    auto width = window->GetCurrentWindowRect().Width();
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, Converter::ArkValue<Ark_Int32>(0));
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
    return static_cast<Ark_Int32>(pxValue);
}
Ark_Int32 Px2lpxImpl(const Ark_Number* value)
{
    CHECK_NULL_RETURN(value, Converter::ArkValue<Ark_Int32>(0));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, Converter::ArkValue<Ark_Int32>(0));

    auto pipelineContext = container->GetPipelineContext();
#ifdef ARKUI_CAPI_UNITTEST
    CHECK_NULL_RETURN(pipelineContext, Converter::ArkValue<Ark_Int32>(0));
    auto width = pipelineContext->GetCurrentWindowRect().Width();
    static WindowConfig windowConfig;
#else
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, Converter::ArkValue<Ark_Int32>(0));
    auto width = window->GetCurrentWindowRect().Width();
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, Converter::ArkValue<Ark_Int32>(0));
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
    return static_cast<Ark_Int32>(lpxValue);
}
Ark_Boolean RequestFocusImpl(const Ark_String* value)
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
void SetCursorImpl(Ark_PointerStyle value)
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
void RestoreDefaultImpl()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (!pipelineContext->GetTaskExecutor()) {
        return;
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext]() { pipelineContext->RestoreDefault(); },
        TaskExecutor::TaskType::UI, "ArkUIJsRestoreDefault");
}
} // GlobalScope_commonAccessor
const GENERATED_ArkUIGlobalScope_commonAccessor* GetGlobalScope_commonAccessor()
{
    static const GENERATED_ArkUIGlobalScope_commonAccessor GlobalScope_commonAccessorImpl {
        GlobalScope_commonAccessor::DestroyPeerImpl,
        GlobalScope_commonAccessor::CtorImpl,
        GlobalScope_commonAccessor::GetFinalizerImpl,
        GlobalScope_commonAccessor::GetContextImpl,
        GlobalScope_commonAccessor::PostCardActionImpl,
        GlobalScope_commonAccessor::Dollar_rImpl,
        GlobalScope_commonAccessor::Dollar_rawfileImpl,
        GlobalScope_commonAccessor::AnimateToImpl,
        GlobalScope_commonAccessor::AnimateToImmediatelyImpl,
        GlobalScope_commonAccessor::Vp2pxImpl,
        GlobalScope_commonAccessor::Px2vpImpl,
        GlobalScope_commonAccessor::Fp2pxImpl,
        GlobalScope_commonAccessor::Px2fpImpl,
        GlobalScope_commonAccessor::Lpx2pxImpl,
        GlobalScope_commonAccessor::Px2lpxImpl,
        GlobalScope_commonAccessor::RequestFocusImpl,
        GlobalScope_commonAccessor::SetCursorImpl,
        GlobalScope_commonAccessor::RestoreDefaultImpl,
    };
    return &GlobalScope_commonAccessorImpl;
}

struct GlobalScope_commonPeer {
    virtual ~GlobalScope_commonPeer() = default;
};
}
