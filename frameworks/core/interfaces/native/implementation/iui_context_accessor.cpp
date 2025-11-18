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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/bind_sheet_utils.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr int32_t INVALID_ID = -1;
std::optional<std::string> ConvertString(const Ark_Union_Number_String& src)
{
    std::optional<std::string> value;
    auto selector = src.selector;
    if (selector == 1) {
        value = OHOS::Ace::NG::Converter::OptConvert<std::string>(src.value1);
    }
    return value;
}
std::optional<int32_t> ConvertNumber(const Ark_Union_Number_String& src)
{
    std::optional<int32_t> value;
    auto selector = src.selector;
    if (selector == 0) {
        value = OHOS::Ace::NG::Converter::OptConvert<int32_t>(src.value0);
    }
    return value;
}
} // namespace
namespace IUIContextAccessor {
void FreezeUINode0Impl(const Ark_String* id, Ark_Boolean isFrozen)
{
    CHECK_NULL_VOID(id);
    ViewAbstract::FreezeUINodeById(Converter::Convert<std::string>(*id), Converter::Convert<bool>(isFrozen));
}
void FreezeUINode1Impl(const Ark_Number* id, Ark_Boolean isFrozen)
{
    CHECK_NULL_VOID(id);
    ViewAbstract::FreezeUINodeByUniqueId(Converter::Convert<int32_t>(*id), Converter::Convert<bool>(isFrozen));
}
Ark_Boolean DispatchKeyEventImpl(const Ark_Union_Number_String* node, Ark_KeyEvent event)
{
    auto result = false;
    RefPtr<NG::FrameNode> frameNode = nullptr;
    auto convId = ConvertString(*node);
    if (convId) {
        frameNode = NG::Inspector::GetFrameNodeByKey(*convId);
    } else {
        auto numberId = ConvertNumber(*node);
        if (numberId) {
            auto node = ElementRegister::GetInstance()->GetNodeById(*numberId);
            frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        }
    }
    CHECK_NULL_RETURN(frameNode, Converter::ArkValue<Ark_Boolean>(result));
    auto focusHub = frameNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, Converter::ArkValue<Ark_Boolean>(result));

    CHECK_NULL_RETURN(event, Converter::ArkValue<Ark_Boolean>(result));
    const auto info = event->GetEventInfo();
    CHECK_NULL_RETURN(info, Converter::ArkValue<Ark_Boolean>(result));
    KeyEvent keyEvent;
    info->ParseKeyEvent(keyEvent);
    result = focusHub->HandleEvent(keyEvent);
    return Converter::ArkValue<Ark_Boolean>(result);
}
void OpenBindSheetImpl(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker, Ark_NativePointer bindSheetContent,
    const Opt_SheetOptions* sheetOptions, const Opt_Int32* targetId,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showInPage = false;
    BindSheetUtil::SheetCallbacks cbs;
    auto options = Converter::OptConvertPtr<Ark_SheetOptions>(sheetOptions);
    if (options) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, options.value());
        BindSheetUtil::ParseFunctionalCallbacks(cbs, options.value());
        Converter::VisitUnion(
            options->title,
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
            },
            []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, options.value());
    }

    int32_t id = Converter::OptConvert<int32_t>(targetId->value).value_or(INVALID_ID);

    ViewContextModel::GetInstance()->OpenBindSheet(sheetContentRefptr, std::move(cbs.titleBuilder), sheetStyle,
        std::move(cbs.onAppear), std::move(cbs.onDisappear), std::move(cbs.shouldDismiss), std::move(cbs.onWillDismiss),
        std::move(cbs.onWillAppear), std::move(cbs.onWillDisappear), std::move(cbs.onHeightDidChange),
        std::move(cbs.onDetentsDidChange), std::move(cbs.onWidthDidChange), std::move(cbs.onTypeDidChange),
        std::move(cbs.sheetSpringBack), Container::CurrentId(), id);
}
void UpdateBindSheetImpl(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker, Ark_NativePointer bindSheetContent,
    const Ark_SheetOptions* sheetOptions, const Opt_Boolean* partialUpdate,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);

    auto partialUpdateVal = Converter::OptConvertPtr<bool>(partialUpdate).value_or(false);

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = NG::SheetMode::LARGE;
    sheetStyle.showDragBar = true;
    sheetStyle.showInPage = false;
    auto options = Converter::OptConvertPtr<Ark_SheetOptions>(sheetOptions);
    BindSheetUtil::SheetCallbacks cbs;
    if (options) {
        BindSheetUtil::ParseLifecycleCallbacks(cbs, options.value());
        BindSheetUtil::ParseFunctionalCallbacks(cbs, options.value());
        Converter::VisitUnion(
            options->title,
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
            },
            []() {});
        BindSheetUtil::ParseSheetParams(sheetStyle, options.value());
        BindSheetUtil::ModifySheetStyle(sheetContentRefptr, sheetStyle, partialUpdateVal);
    }

    auto ret = ViewContextModel::GetInstance()->UpdateBindSheet(
        sheetContentRefptr, sheetStyle, partialUpdateVal, Container::CurrentId());
}
void CloseBindSheetImpl(Ark_VMContext vmContext, Ark_AsyncWorkerPtr asyncWorker, Ark_NativePointer bindSheetContent,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    FrameNodePeer* sheetContentNode = bindSheetContent ? reinterpret_cast<FrameNodePeer*>(bindSheetContent) : nullptr;
    RefPtr<NG::FrameNode> sheetContentRefptr = FrameNodePeer::GetFrameNodeByPeer(sheetContentNode);
    auto ret = ViewContextModel::GetInstance()->CloseBindSheet(sheetContentRefptr, Container::CurrentId());
}
} // namespace IUIContextAccessor
const GENERATED_ArkUIIUIContextAccessor* GetIUIContextAccessor()
{
    static const GENERATED_ArkUIIUIContextAccessor IUIContextAccessorImpl {
        IUIContextAccessor::FreezeUINode0Impl,
        IUIContextAccessor::FreezeUINode1Impl,
        IUIContextAccessor::DispatchKeyEventImpl,
        IUIContextAccessor::OpenBindSheetImpl,
        IUIContextAccessor::UpdateBindSheetImpl,
        IUIContextAccessor::CloseBindSheetImpl,
    };
    return &IUIContextAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
