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

#include "core/common/container.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/interfaces/native/implementation/ui_context_accessor_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline/pipeline_base.h"
#include "global_scope_animation_helper.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/bind_sheet_utils.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIContextAccessor {
void DestroyPeerImpl(Ark_UIContext peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_UIContext ConstructImpl()
{
    return PeerUtils::CreatePeer<UIContextPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_drawing_Font GetFontImpl(Ark_UIContext peer)
{
    return {};
}
Ark_String GetFilteredInspectorTreeImpl(Ark_VMContext vmContext,
                                        Ark_UIContext peer,
                                        const Opt_Array_String* filters)
{
    return {};
}
Ark_String GetFilteredInspectorTreeByIdImpl(Ark_VMContext vmContext,
                                            Ark_UIContext peer,
                                            const Ark_String* id,
                                            const Ark_Number* depth,
                                            const Opt_Array_String* filters)
{
    return {};
}
void AnimateToImpl(Ark_UIContext peer,
                   const Ark_AnimateParam* value,
                   const Callback_Void* event)
{
    AnimateToInner(value, event, false);
}
void ShowTextPickerDialogImpl(Ark_UIContext peer,
                              const Ark_TextPickerDialogOptions* options)
{
}
void RunScopedTaskImpl(Ark_UIContext peer,
                       const Callback_Void* callback_)
{
}
void AnimateToImmediatelyImpl(Ark_UIContext peer,
                              const Ark_AnimateParam* param,
                              const Callback_Void* event)
{
    AnimateToInner(param, event, true);
}
Opt_FrameNode GetFrameNodeByIdImpl(Ark_UIContext peer,
                                   const Ark_String* id)
{
    return {};
}
Opt_FrameNode GetAttachedFrameNodeByIdImpl(Ark_UIContext peer,
                                           const Ark_String* id)
{
    return {};
}
Opt_FrameNode GetFrameNodeByUniqueIdImpl(Ark_UIContext peer,
                                         const Ark_Number* id)
{
    return {};
}
Ark_Number Vp2pxImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    auto invalid = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(value, invalid);
    double vpValue = Converter::Convert<double>(*value);
    double density = PipelineBase::GetCurrentDensity();
    double pxValue = vpValue * density;
    return Converter::ArkValue<Ark_Number>(pxValue);
}
Ark_Number Px2vpImpl(Ark_UIContext peer,
                     const Ark_Number* value)
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
Ark_Number Fp2pxImpl(Ark_UIContext peer,
                     const Ark_Number* value)
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
Ark_Number Px2fpImpl(Ark_UIContext peer,
                     const Ark_Number* value)
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
Ark_Number Lpx2pxImpl(Ark_UIContext peer,
                      const Ark_Number* value)
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
Ark_Number Px2lpxImpl(Ark_UIContext peer,
                      const Ark_Number* value)
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
Opt_common_Context GetHostContextImpl(Ark_UIContext peer)
{
    return {};
}
void SetDynamicDimmingImpl(Ark_UIContext peer,
                           const Ark_String* id,
                           const Ark_Number* value)
{
}
Opt_String GetWindowNameImpl(Ark_UIContext peer)
{
#ifdef WRONG_CODE
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, {});
    auto window = context->GetWindow();
    CHECK_NULL_RETURN(window, {});
    ContainerScope cope(Converter::Convert<int32_t>(*instanceId));
    std::string windowName = window->GetWindowName();
    return Converter::ArkValue<Ark_String>(windowName, Converter::FC);
#else
    return {};
#endif
}
Ark_WidthBreakpoint GetWindowWidthBreakpointImpl(Ark_UIContext peer)
{
#ifdef WRONG_CODE
    ContainerScope cope(Converter::Convert<int32_t>(*instanceId));
    int32_t windowWidthBreakpoint = ViewAbstractModelStatic::GetWindowWidthBreakpoint();
    return Converter::ArkValue<Ark_Number>(windowWidthBreakpoint);
#else
    return {};
#endif
}
Ark_HeightBreakpoint GetWindowHeightBreakpointImpl(Ark_UIContext peer)
{
#ifdef WRONG_CODE
    ContainerScope cope(Converter::Convert<int32_t>(*instanceId));
    int32_t windowHeightBreakpoint = ViewAbstractModelStatic::GetWindowHeightBreakpoint();
    return Converter::ArkValue<Ark_Number>(windowHeightBreakpoint);
#else
    return {};
#endif
}
void OpenBindSheetImpl(Ark_VMContext vmContext,
                       Ark_AsyncWorkerPtr asyncWorker,
                       Ark_UIContext peer,
                       Ark_ComponentContent bindSheetContent,
                       const Opt_SheetOptions* sheetOptions,
                       const Opt_Number* targetId,
                       const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
#ifdef WRONG_GEN
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showInPage = false;
    BindSheetUtil::SheetCallbacks cbs;
    auto sheetOptions = Converter::OptConvertPtr<Ark_SheetOptions>(options);
    if (sheetOptions) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, sheetOptions.value());
        BindSheetUtil::ParseFunctionalCallbacks(cbs, sheetOptions.value());
        Converter::VisitUnion(sheetOptions->title,
            [&sheetStyle](const Ark_SheetTitleOptions& value) {
                sheetStyle.isTitleBuilder = false;
                sheetStyle.sheetTitle = Converter::OptConvert<std::string>(value.title);
                sheetStyle.sheetSubtitle = Converter::OptConvert<std::string>(value.subtitle);
            },
            [&sheetStyle, bindSheetContent, &cbs](const CustomNodeBuilder& value) {
                sheetStyle.isTitleBuilder = true;
                cbs.titleBuilder = [callback = CallbackHelper(value), bindSheetContent]() {
                    auto uiNode = callback.BuildSync(bindSheetContent);
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
            }, []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, sheetOptions.value());
    }
    auto id = targetId->value.i32;

    ViewContextModel::GetInstance()->OpenBindSheet(sheetContentRefptr,
        std::move(cbs.titleBuilder), sheetStyle, std::move(cbs.onAppear), std::move(cbs.onDisappear),
        std::move(cbs.shouldDismiss), std::move(cbs.onWillDismiss),  std::move(cbs.onWillAppear),
        std::move(cbs.onWillDisappear), std::move(cbs.onHeightDidChange),
        std::move(cbs.onDetentsDidChange), std::move(cbs.onWidthDidChange),
        std::move(cbs.onTypeDidChange), std::move(cbs.sheetSpringBack), Container::CurrentId(), id);
#endif
}
void UpdateBindSheetImpl(Ark_VMContext vmContext,
                         Ark_AsyncWorkerPtr asyncWorker,
                         Ark_UIContext peer,
                         Ark_ComponentContent bindSheetContent,
                         const Ark_SheetOptions* sheetOptions,
                         const Opt_Boolean* partialUpdate,
                         const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
#ifdef WRONG_GEN
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);

    auto partialUpdateVal = Converter::OptConvertPtr<bool>(partialUpdate).value_or(false);

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showInPage = false;
    auto sheetOptions = Converter::OptConvertPtr<Ark_SheetOptions>(options);
    BindSheetUtil::SheetCallbacks cbs;
    if (sheetOptions) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, sheetOptions.value());
        BindSheetUtil::ParseFunctionalCallbacks(cbs, sheetOptions.value());
        Converter::VisitUnion(sheetOptions->title,
            [&sheetStyle](const Ark_SheetTitleOptions& value) {
                sheetStyle.isTitleBuilder = false;
                sheetStyle.sheetTitle = Converter::OptConvert<std::string>(value.title);
                sheetStyle.sheetSubtitle = Converter::OptConvert<std::string>(value.subtitle);
            },
            [&sheetStyle, bindSheetContent, &cbs](const CustomNodeBuilder& value) {
                sheetStyle.isTitleBuilder = true;
                cbs.titleBuilder = [callback = CallbackHelper(value), bindSheetContent]() {
                    auto uiNode = callback.BuildSync(bindSheetContent);
                    ViewStackProcessor::GetInstance()->Push(uiNode);
                };
            }, []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, sheetOptions.value());
        BindSheetUtil::ModifySheetStyle(sheetContentRefptr, sheetStyle, partialUpdateVal);
    }

    auto ret = ViewContextModel::GetInstance()->UpdateBindSheet(
        sheetContentRefptr, sheetStyle, partialUpdateVal, Container::CurrentId());
#endif
}
void CloseBindSheetImpl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        Ark_UIContext peer,
                        Ark_ComponentContent bindSheetContent,
                        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);
    auto ret =
        ViewContextModel::GetInstance()->CloseBindSheet(sheetContentRefptr, Container::CurrentId());
}
void ClearResourceCacheImpl(Ark_VMContext vmContext,
                            Ark_UIContext peer)
{
}
Ark_Boolean IsFollowingSystemFontScaleImpl(Ark_UIContext peer)
{
    return {};
}
Ark_Number GetMaxFontScaleImpl(Ark_UIContext peer)
{
    return {};
}
} // UIContextAccessor
const GENERATED_ArkUIUIContextAccessor* GetUIContextAccessor()
{
    static const GENERATED_ArkUIUIContextAccessor UIContextAccessorImpl {
        UIContextAccessor::DestroyPeerImpl,
        UIContextAccessor::ConstructImpl,
        UIContextAccessor::GetFinalizerImpl,
        UIContextAccessor::GetFontImpl,
        UIContextAccessor::GetFilteredInspectorTreeImpl,
        UIContextAccessor::GetFilteredInspectorTreeByIdImpl,
        UIContextAccessor::AnimateToImpl,
        UIContextAccessor::ShowTextPickerDialogImpl,
        UIContextAccessor::RunScopedTaskImpl,
        UIContextAccessor::AnimateToImmediatelyImpl,
        UIContextAccessor::GetFrameNodeByIdImpl,
        UIContextAccessor::GetAttachedFrameNodeByIdImpl,
        UIContextAccessor::GetFrameNodeByUniqueIdImpl,
        UIContextAccessor::Vp2pxImpl,
        UIContextAccessor::Px2vpImpl,
        UIContextAccessor::Fp2pxImpl,
        UIContextAccessor::Px2fpImpl,
        UIContextAccessor::Lpx2pxImpl,
        UIContextAccessor::Px2lpxImpl,
        UIContextAccessor::GetHostContextImpl,
        UIContextAccessor::SetDynamicDimmingImpl,
        UIContextAccessor::GetWindowNameImpl,
        UIContextAccessor::GetWindowWidthBreakpointImpl,
        UIContextAccessor::GetWindowHeightBreakpointImpl,
    };
    return &UIContextAccessorImpl;
}

}
