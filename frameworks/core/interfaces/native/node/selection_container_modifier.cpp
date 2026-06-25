/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/node/selection_container_modifier.h"

#include <functional>
#include <vector>

#include "bridge/common/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/selection_container/selection_container_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
} // namespace

void Create()
{
    SelectionContainerModelNG::Create();
}

void SetCopyOption(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetCopyOption(frameNode, static_cast<CopyOptions>(value));
}

void ResetCopyOption(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::ResetCopyOption(frameNode);
}

void SetEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetEnableHapticFeedback(frameNode, value);
}

void ResetEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::ResetEnableHapticFeedback(frameNode);
}

void SetTextJoinStyle(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetTextJoinStyle(
        frameNode, static_cast<SelectionContainerTextJoinStyle>(value));
}

void ResetTextJoinStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::ResetTextJoinStyle(frameNode);
}

void SetCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resourceRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetCaretColor(frameNode, Color(color));
}

void ResetCaretColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::ResetCaretColor(frameNode);
}

void SetSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resourceRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto selectedBackgroundColor = Color(color);
    if (selectedBackgroundColor.GetAlpha() == 255) {
        selectedBackgroundColor = selectedBackgroundColor.ChangeOpacity(0.2);
    }
    SelectionContainerModelNG::SetSelectedBackgroundColor(frameNode, selectedBackgroundColor);
}

void ResetSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::ResetSelectedBackgroundColor(frameNode);
}


void SetOnWillCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (!callback) {
        SelectionContainerModelNG::SetOnWillCopy(frameNode, nullptr);
        return;
    }
    auto cb = *(reinterpret_cast<std::function<bool(const std::u16string&)>*>(callback));
    SelectionContainerModelNG::SetOnWillCopy(frameNode, std::move(cb));
}

void ResetOnWillCopy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetOnWillCopy(frameNode, nullptr);
}

void SetOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (!callback) {
        SelectionContainerModelNG::SetOnCopy(frameNode, nullptr);
        return;
    }
    auto cb = *(reinterpret_cast<std::function<void(const std::u16string&)>*>(callback));
    SelectionContainerModelNG::SetOnCopy(frameNode, std::move(cb));
}

void ResetOnCopy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetOnCopy(frameNode, nullptr);
}

void SetSelectionContainerOnTextSelectionChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (!callback) {
        SelectionContainerModelNG::SetOnTextSelectionChange(frameNode, nullptr);
        return;
    }
    auto cb = *(reinterpret_cast<std::function<void(const std::vector<std::u16string>&)>*>(callback));
    SelectionContainerModelNG::SetOnTextSelectionChange(frameNode, std::move(cb));
}

void ResetSelectionContainerOnTextSelectionChange(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetOnTextSelectionChange(frameNode, nullptr);
}

void SetSelectionMenuOptions(
    ArkUINodeHandle node, void* onCreateMenu, void* onMenuItemClick, void* onPrepareMenu)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (onMenuItemClick) {
        auto onMenuItemClickCb =
            *(reinterpret_cast<std::function<bool(const NG::MenuItemParam&, const std::u16string&)>*>(
                onMenuItemClick));
        SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(
            frameNode, std::move(onMenuItemClickCb));
    } else {
        SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(frameNode, nullptr);
    }
    auto onCreateMenuCb = onCreateMenu
        ? std::move(*(reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenu)))
        : NG::OnCreateMenuCallback();
    auto onPrepareMenuCb = onPrepareMenu
        ? std::move(*(reinterpret_cast<NG::OnPrepareMenuCallback*>(onPrepareMenu)))
        : NG::OnPrepareMenuCallback();
    SelectionContainerModelNG::SetSelectionMenuOptions(frameNode,
        std::move(onCreateMenuCb), nullptr, std::move(onPrepareMenuCb));
}

void ResetSelectionMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SelectionContainerModelNG::SetSelectionMenuOptions(frameNode, nullptr, nullptr, nullptr);
    SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(frameNode, nullptr);
}

void SetBindSelectionMenu(
    ArkUINodeHandle node, ArkUI_Int32 spanType, ArkUI_Int32 responseType, void* buildFunc, void* menuParam)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::function<void()> buildCallback;
    if (buildFunc) {
        buildCallback = std::move(*(reinterpret_cast<std::function<void()>*>(buildFunc)));
    }
    NG::SelectMenuParam menuCallback;
    if (menuParam) {
        menuCallback = std::move(*(reinterpret_cast<NG::SelectMenuParam*>(menuParam)));
    }
    SelectionContainerModelNG::BindSelectionMenu(frameNode,
        static_cast<NG::TextSpanType>(spanType),
        static_cast<NG::TextResponseType>(responseType),
        buildCallback, menuCallback);
}

void ResetBindSelectionMenu(ArkUINodeHandle node, ArkUI_Int32 spanType, ArkUI_Int32 responseType)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::function<void()> buildFunc;
    NG::SelectMenuParam menuParam;
    menuParam.isValid = true;
    SelectionContainerModelNG::BindSelectionMenu(frameNode,
        static_cast<NG::TextSpanType>(spanType),
        static_cast<NG::TextResponseType>(responseType),
        buildFunc, menuParam);
}

const ArkUISelectionContainerModifier* GetSelectionContainerDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN();
    static const ArkUISelectionContainerModifier modifier = {
        .create = Create,
        .setCopyOption = SetCopyOption,
        .resetCopyOption = ResetCopyOption,
        .setEnableHapticFeedback = SetEnableHapticFeedback,
        .resetEnableHapticFeedback = ResetEnableHapticFeedback,
        .setTextJoinStyle = SetTextJoinStyle,
        .resetTextJoinStyle = ResetTextJoinStyle,
        .setCaretColor = SetCaretColor,
        .resetCaretColor = ResetCaretColor,
        .setSelectedBackgroundColor = SetSelectedBackgroundColor,
        .resetSelectedBackgroundColor = ResetSelectedBackgroundColor,
        .setOnWillCopy = SetOnWillCopy,
        .resetOnWillCopy = ResetOnWillCopy,
        .setOnCopy = SetOnCopy,
        .resetOnCopy = ResetOnCopy,
        .setOnTextSelectionChange = SetSelectionContainerOnTextSelectionChange,
        .resetOnTextSelectionChange = ResetSelectionContainerOnTextSelectionChange,
        .setSelectionMenuOptions = SetSelectionMenuOptions,
        .resetSelectionMenuOptions = ResetSelectionMenuOptions,
        .setBindSelectionMenu = SetBindSelectionMenu,
        .resetBindSelectionMenu = ResetBindSelectionMenu,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0);
    return &modifier;
}

namespace NodeModifier {
const ArkUISelectionContainerModifier* GetSelectionContainerModifier()
{
    return GetSelectionContainerDynamicModifier();
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
