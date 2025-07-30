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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline/pipeline_base.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/bind_sheet_utils.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIContextAccessor {
void DestroyPeerImpl(Ark_UIContext peer)
{
}
Ark_UIContext CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Font GetFontImpl(Ark_UIContext peer)
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
}
Ark_Union_FrameNode_Undefined GetFrameNodeByIdImpl(Ark_UIContext peer,
                                                   const Ark_String* id)
{
    return {};
}
Ark_Union_FrameNode_Undefined GetAttachedFrameNodeByIdImpl(Ark_UIContext peer,
                                                           const Ark_String* id)
{
    return {};
}
Ark_Union_FrameNode_Undefined GetFrameNodeByUniqueIdImpl(Ark_UIContext peer,
                                                         const Ark_Number* id)
{
    return {};
}
Ark_Number Vp2pxImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Px2vpImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Fp2pxImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Px2fpImpl(Ark_UIContext peer,
                     const Ark_Number* value)
{
    return {};
}
Ark_Number Lpx2pxImpl(Ark_UIContext peer,
                      const Ark_Number* value)
{
    return {};
}
Ark_Number Px2lpxImpl(Ark_UIContext peer,
                      const Ark_Number* value)
{
    return {};
}
Ark_Union_Context_Undefined GetHostContextImpl(Ark_UIContext peer)
{
    return {};
}
void SetDynamicDimmingImpl(Ark_UIContext peer,
                           const Ark_String* id,
                           const Ark_Number* value)
{
}
void OpenBindSheetImpl(Ark_VMContext vmContext,
                       Ark_NativePointer bindSheetContent,
                       const Opt_SheetOptions* options,
                       const Opt_Number* targetId)
{
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
}
void UpdateBindSheetImpl(Ark_VMContext vmContext,
                         Ark_NativePointer bindSheetContent,
                         const Opt_SheetOptions* options,
                         const Opt_Boolean* partialUpdate)
{
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
}
void CloseBindSheetImpl(Ark_VMContext vmContext,
                        Ark_NativePointer bindSheetContent)
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
Ark_String GetWindowNameImpl(const Ark_Number* instanceId)
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, {});
    auto window = context->GetWindow();
    CHECK_NULL_RETURN(window, {});
    ContainerScope cope(Converter::Convert<int32_t>(*instanceId));
    std::string windowName = window->GetWindowName();
    return Converter::ArkValue<Ark_String>(windowName, Converter::FC);
}
Ark_Number GetWindowWidthBreakpoint(const Ark_Number* instanceId)
{
    ContainerScope cope(Converter::Convert<int32_t>(*instanceId));
    int32_t windowWidthBreakpoint = ViewAbstractModelStatic::GetWindowWidthBreakpoint();
    return Converter::ArkValue<Ark_Number>(windowWidthBreakpoint);
}
Ark_Number GetWindowHeightBreakpoint(const Ark_Number* instanceId)
{
    ContainerScope cope(Converter::Convert<int32_t>(*instanceId));
    int32_t windowHeightBreakpoint = ViewAbstractModelStatic::GetWindowHeightBreakpoint();
    return Converter::ArkValue<Ark_Number>(windowHeightBreakpoint);
}
} // UIContextAccessor
const GENERATED_ArkUIUIContextAccessor* GetUIContextAccessor()
{
    static const GENERATED_ArkUIUIContextAccessor UIContextAccessorImpl {
        UIContextAccessor::DestroyPeerImpl,
        UIContextAccessor::CtorImpl,
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
        UIContextAccessor::OpenBindSheetImpl,
        UIContextAccessor::UpdateBindSheetImpl,
        UIContextAccessor::CloseBindSheetImpl,
        UIContextAccessor::ClearResourceCacheImpl,
        UIContextAccessor::IsFollowingSystemFontScaleImpl,
        UIContextAccessor::GetMaxFontScaleImpl,
        UIContextAccessor::GetWindowNameImpl,
        UIContextAccessor::GetWindowWidthBreakpoint,
        UIContextAccessor::GetWindowHeightBreakpoint,
    };
    return &UIContextAccessorImpl;
}

}
