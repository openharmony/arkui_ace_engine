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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_MODEL_NG_H

#include <functional>
#include "base/utils/macros.h"
#include "core/components_ng/pattern/selection_container/selection_container_model.h"

namespace OHOS::Ace::NG {
class FrameNode;

class ACE_EXPORT SelectionContainerModelNG : public SelectionContainerModel {
public:
    static void Create();
    void SetCopyOption(CopyOptions copyOption) override;
    void SetEnableHapticFeedback(bool isEnabled) override;
    void SetTextJoinStyle(NG::SelectionContainerTextJoinStyle style) override;
    void SetCaretColor(const Color& caretColor) override;
    void SetSelectedBackgroundColor(const Color& selectedBackgroundColor) override;
    void ResetCopyOption() override;
    void ResetEnableHapticFeedback() override;
    void ResetTextJoinStyle() override;
    void ResetCaretColor() override;
    void ResetSelectedBackgroundColor() override;
    void SetOnWillCopy(std::function<bool(const std::u16string&)>&& func) override;
    void SetOnCopy(std::function<void(const std::u16string&)>&& func) override;
    void SetOnTextSelectionChange(
        std::function<void(const std::vector<std::u16string>&)>&& func) override;
    void SetSelectionMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick,
        const NG::OnPrepareMenuCallback&& onPrepareMenuCallback) override;
    void SetSelectionMenuItemClickWithTextCallback(
        std::function<bool(const NG::MenuItemParam&, const std::u16string&)>&& func) override;
    void BindSelectionMenu(TextSpanType spanType, TextResponseType responseType,
        std::function<void()>& menuBuilder, const SelectMenuParam& menuParam) override;

    // Node-specific static methods (bypass ViewStackProcessor)
    static void SetCopyOption(FrameNode* frameNode, CopyOptions copyOption);
    static void ResetCopyOption(FrameNode* frameNode);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool isEnabled);
    static void ResetEnableHapticFeedback(FrameNode* frameNode);
    static void SetTextJoinStyle(FrameNode* frameNode, NG::SelectionContainerTextJoinStyle style);
    static void ResetTextJoinStyle(FrameNode* frameNode);
    static void SetCaretColor(FrameNode* frameNode, const Color& caretColor);
    static void ResetCaretColor(FrameNode* frameNode);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& selectedBackgroundColor);
    static void ResetSelectedBackgroundColor(FrameNode* frameNode);
    static void SetOnWillCopy(FrameNode* frameNode, std::function<bool(const std::u16string&)>&& func);
    static void SetOnCopy(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func);
    static void SetOnTextSelectionChange(
        FrameNode* frameNode, std::function<void(const std::vector<std::u16string>&)>&& func);
    static void SetSelectionMenuOptions(FrameNode* frameNode,
        const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick,
        const NG::OnPrepareMenuCallback&& onPrepareMenuCallback);
    static void SetSelectionMenuItemClickWithTextCallback(
        FrameNode* frameNode,
        std::function<bool(const NG::MenuItemParam&, const std::u16string&)>&& func);
    static void BindSelectionMenu(FrameNode* frameNode, TextSpanType spanType,
        TextResponseType responseType, std::function<void()>& menuBuilder,
        const SelectMenuParam& menuParam);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_MODEL_NG_H
