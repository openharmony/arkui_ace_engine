/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_NG_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_properties.h"
namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT TextPickerModelNG : public TextPickerModel {
public:
    void Create(RefPtr<PickerTheme> pickerTheme, uint32_t columnKind) override;
    void SetSelected(uint32_t value) override;
    void SetRange(const std::vector<NG::RangeContent>& value) override;
    void SetValue(const std::string& value) override;
    void SetDefaultPickerItemHeight(const Dimension& value) override;
    void SetGradientHeight(const Dimension& value) override;
    void SetCanLoop(const bool value) override;
    void SetDefaultAttributes(const RefPtr<PickerTheme>& pickerTheme) override;
    void SetDisappearTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override;
    void SetNormalTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override;
    void SetSelectedTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override;
    void HasUserDefinedDisappearFontFamily(bool isUserDefined) override;
    void HasUserDefinedNormalFontFamily(bool isUserDefined) override;
    void HasUserDefinedSelectedFontFamily(bool isUserDefined) override;
    void MultiInit(const RefPtr<PickerTheme> pickerTheme) override;
    void SetColumns(const std::vector<NG::TextCascadePickerOptions>& options) override;
    void SetIsCascade(bool isCascade) override;
    void SetOnCascadeChange(TextCascadeChangeEvent&& onChange) override;
    void SetValues(const std::vector<std::string>& values) override;
    void SetSelecteds(const std::vector<uint32_t>& values) override;
    void SetBackgroundColor(const Color& color) override;
    bool IsSingle() override;
    bool GetSingleRange(std::vector<NG::RangeContent>& rangeValue) override;
    bool IsCascade() override
    {
        return isCascade_;
    }

    void SetMaxCount(uint32_t maxCount) override
    {
        maxCount_ = maxCount;
    }

    uint32_t GetMaxCount() override
    {
        return maxCount_;
    }

    void SetSingleRange(bool isSingleRange) override
    {
        isSingleRange_ = isSingleRange;
    }

    bool GetSingleRange() override
    {
        return isSingleRange_;
    }

    static void SetTextPickerSingeRange(bool isSingleRange)
    {
        isSingleRange_ = isSingleRange;
    }

    static bool GetTextPickerSingeRange()
    {
        return isSingleRange_;
    }

    void SetHasSelectAttr(bool value) override;
    bool GetMultiOptions(std::vector<NG::TextCascadePickerOptions>& options) override;
    void SetOnValueChangeEvent(TextCascadeValueChangeEvent&& onChange) override;
    void SetOnSelectedChangeEvent(TextCascadeSelectedChangeEvent&& onChange) override;
    void SetDivider(const ItemDivider& divider) override;
    void HasUserDefinedOpacity() override;

    static void SetCanLoop(FrameNode* frameNode, const bool value);
    static void SetSelected(FrameNode* frameNode, uint32_t value);
    static void SetSelecteds(FrameNode* frameNode, const std::vector<uint32_t>& values);
    static void SetHasSelectAttr(FrameNode* frameNode, bool value);
    static void SetNormalTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value);
    static void SetSelectedTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value);
    static void SetDisappearTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value);
    static void SetDefaultPickerItemHeight(FrameNode* frameNode, const Dimension& value);
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
    static void SetGradientHeight(FrameNode* frameNode, const Dimension& value);
    static void SetOnCascadeChange(FrameNode* frameNode, TextCascadeChangeEvent&& onChange);
    static int32_t GetSelectedSize(FrameNode* frameNode);
    static std::string getTextPickerValues(FrameNode* frameNode);
    static std::vector<uint32_t> getTextPickerSelecteds(FrameNode* frameNode);
    static int32_t GetCanLoop(FrameNode* frameNode);
    static Dimension GetDefaultPickerItemHeight(FrameNode* frameNode);
    static void SetTextPickerRangeType(FrameNode* frameNode, int32_t rangeType);
    static int32_t GetTextPickerRangeType(FrameNode* frameNode);
    static const Dimension ConvertFontScaleValue(const Dimension& fontSizeValue);
private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
    static RefPtr<FrameNode> CreateColumnNode(uint32_t columnKind, uint32_t showCount);
    void SetUnCascadeColumns(const std::vector<NG::TextCascadePickerOptions>& options);
    void SetCascadeColumns(const std::vector<NG::TextCascadePickerOptions>& options);
    static void SetUnCascadeColumnsNode(FrameNode* frameNode, const std::vector<NG::TextCascadePickerOptions>& options);
    static void SetCascadeColumnsNode(FrameNode* frameNode, const std::vector<NG::TextCascadePickerOptions>& options);

    static inline uint32_t showCount_ = 0;
    std::vector<uint32_t> kinds_;
    static inline bool isCascade_ = false;
    static inline std::vector<NG::RangeContent> rangeValue_;
    static inline std::vector<NG::TextCascadePickerOptions> options_;
    uint32_t maxCount_ = 0;
    static inline bool isSingleRange_ = true;
};

class ACE_EXPORT TextPickerDialogModelNG : public TextPickerDialogModel {
public:
    RefPtr<AceType> CreateObject() override;
    void SetTextPickerDialogShow(RefPtr<AceType>& PickerText, NG::TextPickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange, TextPickerDialog& textPickerDialog,
        TextPickerDialogEvent& textPickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_NG_H
