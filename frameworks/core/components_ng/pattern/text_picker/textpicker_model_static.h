/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_STATIC_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_properties.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT TextPickerModelStatic {
public:
    static void SetTextPickerSingeRange(bool isSingleRange)
    {
        std::lock_guard<std::shared_mutex> lock(isSingleMutex_);
        isSingleRange_ = isSingleRange;
    }

    static bool GetTextPickerSingeRange()
    {
        std::lock_guard<std::shared_mutex> lock(isSingleMutex_);
        return isSingleRange_;
    }

    static void InitialSetupSinglePicker(FrameNode* frameNode, uint32_t columnKind);
    static void SetCanLoop(FrameNode* frameNode, const bool value);
    static void SetDigitalCrownSensitivity(FrameNode* frameNode, const std::optional<int32_t>& crownSensitivity);
    static void SetSelected(FrameNode* frameNode, uint32_t value);
    static void SetSelecteds(FrameNode* frameNode, const std::vector<uint32_t>& values);
    static void SetHasSelectAttr(FrameNode* frameNode, bool value);
    static void SetIsCascade(FrameNode* frameNode, bool isCascade);
    static void SetColumnKind(FrameNode* frameNode, uint32_t columnKind);
    static void SetNormalTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value);
    static void SetSelectedTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value);
    static void SetDisappearTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value);
    static void SetDefaultTextStyle(
        FrameNode* frameNode, const RefPtr<TextTheme>& textTheme, const NG::PickerTextStyle& value);
    static void SetDefaultTextStyle(FrameNode* frameNode, const NG::PickerTextStyle& value);
    static void SetSelectedBackgroundStyle(FrameNode* frameNode, const NG::PickerBackgroundStyle& value);
    static void SetDefaultPickerItemHeight(FrameNode* frameNode, std::optional<Dimension> valueOpt);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& color);
    static bool IsSingle(FrameNode* frameNode);
    static bool GetSingleRange(FrameNode* frameNode, std::vector<NG::RangeContent>& rangeValue);
    static bool IsCascade(FrameNode* frameNode);
    static bool GetMultiOptions(FrameNode* frameNode, std::vector<NG::TextCascadePickerOptions>& options);
    static uint32_t GetMaxCount(FrameNode* frameNode);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetRange(FrameNode* frameNode, const std::vector<NG::RangeContent>& value);
    static void SetValue(FrameNode* frameNode, const std::string& value);
    static void SetValues(FrameNode* frameNode, const std::vector<std::string>& values);
    static void SetColumns(FrameNode* frameNode, const std::vector<NG::TextCascadePickerOptions>& options);
    static void SetDefaultAttributes(RefPtr<FrameNode>& frameNode, const RefPtr<PickerTheme>& pickerTheme);
    static void SetDivider(FrameNode* frameNode, const ItemDivider& divider);
    static PickerTextStyle getSelectedTextStyle(FrameNode* frameNode);
    static PickerTextStyle getNormalTextStyle(FrameNode* frameNode);
    static PickerTextStyle getDisappearTextStyle(FrameNode* frameNode);
    static int32_t getTextPickerSelectedIndex(FrameNode* frameNode);
    static std::string getTextPickerValue(FrameNode* frameNode);
    static std::string getTextPickerRange(FrameNode* frameNode);
    static void SetGradientHeight(FrameNode* frameNode, std::optional<Dimension> valueOpt);
    static void SetDisableTextStyleAnimation(FrameNode* frameNode, const bool value);
    static void SetOnCascadeChange(FrameNode* frameNode, TextCascadeChangeEvent&& onChange);
    static void SetOnScrollStop(FrameNode* frameNode, TextCascadeChangeEvent&& onScrollStop);
    static void SetOnEnterSelectedArea(FrameNode* frameNode, TextCascadeChangeEvent&& onEnterSelectedArea);
    static int32_t GetSelectedSize(FrameNode* frameNode);
    static int32_t GetColumnWidthsSize(FrameNode* frameNode);
    static std::string getTextPickerValues(FrameNode* frameNode);
    static std::vector<uint32_t> getTextPickerSelecteds(FrameNode* frameNode);
    static int32_t GetCanLoop(FrameNode* frameNode);
    static Dimension GetDefaultPickerItemHeight(FrameNode* frameNode);
    static void SetTextPickerRangeType(FrameNode* frameNode, int32_t rangeType);
    static int32_t GetTextPickerRangeType(FrameNode* frameNode);
    static const Dimension ConvertFontScaleValue(const Dimension& fontSizeValue);
    static const std::string GetSelectedObjectStr(FrameNode* frameNode,
        const std::string value, const uint32_t index);
    static void SetOnValueChangeEvent(FrameNode* frameNode, TextCascadeValueChangeEvent&& onChange);
    static void SetOnSelectedChangeEvent(FrameNode* frameNode, TextCascadeSelectedChangeEvent&& onChange);
    static void SetColumnWidths(FrameNode* frameNode, const std::vector<Dimension>& widths);
    static std::vector<Dimension> GetColumnWidths(FrameNode* frameNode);
    static void SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& isEnableHapticFeedback);
    static bool GetEnableHapticFeedback(FrameNode* frameNode);

private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
    static RefPtr<FrameNode> CreateColumnNode(uint32_t columnKind, uint32_t showCount);
    static void SetUnCascadeColumnsNode(FrameNode* frameNode, const std::vector<NG::TextCascadePickerOptions>& options);
    static void SetCascadeColumnsNode(FrameNode* frameNode, const std::vector<NG::TextCascadePickerOptions>& options);
    static void ValidateData(
        NG::TextCascadePickerOptions& options, const std::vector<std::string>& values, uint32_t index,
        std::vector<std::string>& selectedValues, std::vector<uint32_t>& valuesIndex);

    static inline bool isSingleRange_ = true;
    static inline uint32_t showCount_ = 0;
    static inline std::shared_mutex showCountMutex_;
    static inline std::shared_mutex isSingleMutex_;
    static inline uint32_t columnKind_ = TEXT;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_STATIC_H
