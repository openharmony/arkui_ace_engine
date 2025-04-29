/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXTPICKER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXTPICKER_MODEL_IMPL_H

#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"

namespace OHOS::Ace::Framework {
class TextPickerModelImpl : public TextPickerModel {
public:
    TextPickerModelImpl() = default;
    ~TextPickerModelImpl() override = default;

    void Create(RefPtr<PickerTheme> pickerTheme, uint32_t columnKind) override;
    void SetSelected(uint32_t value) override;
    void SetRange(const std::vector<NG::RangeContent>& value) override;
    void SetValue(const std::string& value) override {}
    void SetDefaultPickerItemHeight(const Dimension& value) override;
    void SetCanLoop(const bool value) override {};
    void SetDigitalCrownSensitivity(int32_t value) override {};
    void SetDefaultAttributes(const RefPtr<PickerTheme>& pickerTheme) override {}
    void SetDisappearTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override {};
    void SetNormalTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override {};
    void SetSelectedTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override {};
    void HasUserDefinedDisappearFontFamily(bool isUserDefined) override {};
    void HasUserDefinedNormalFontFamily(bool isUserDefined) override {};
    void HasUserDefinedSelectedFontFamily(bool isUserDefined) override {};
    void MultiInit(const RefPtr<PickerTheme> pickerTheme) override {};
    void SetColumns(const std::vector<NG::TextCascadePickerOptions>& options) override {};
    void SetIsCascade(bool isCascade) override {};
    void SetOnCascadeChange(TextCascadeChangeEvent&& onChange) override;
    void SetOnScrollStop(TextCascadeChangeEvent&& onScrollStop) override;
    void SetOnEnterSelectedArea(TextCascadeChangeEvent&& onEnterSelectedArea) override;
    void SetValues(const std::vector<std::string>& values) override {};
    void SetSelecteds(const std::vector<uint32_t>& values) override {};
    void SetColumnWidths(const std::vector<Dimension>& widths) override {};
    void SetBackgroundColor(const Color& color) override;
    void HasUserDefinedOpacity() override {};
    bool IsSingle() override
    {
        return true;
    }
    bool GetSingleRange(std::vector<NG::RangeContent>& rangeValue) override
    {
        return false;
    }
    bool IsCascade() override
    {
        return false;
    }
    uint32_t GetMaxCount() override
    {
        return 0;
    }
    void SetMaxCount(uint32_t maxCount) override {};
    bool GetMultiOptions(std::vector<NG::TextCascadePickerOptions>& options) override
    {
        return false;
    }
    void SetHasSelectAttr(bool value) override {};
    void SetOnValueChangeEvent(TextCascadeValueChangeEvent&& onChange) override {};
    void SetOnSelectedChangeEvent(TextCascadeSelectedChangeEvent&& onChange) override {};
    void SetSingleRange(bool isSingleRange) override {};
    bool GetSingleRange() override
    {
        return true;
    }

    void SetDisableTextStyleAnimation(const bool value) override {};
    void SetDefaultTextStyle(const RefPtr<TextTheme>& textTheme, const NG::PickerTextStyle& value) override {};
    void SetEnableHapticFeedback(bool isEnableHapticFeedback) override {};
    void UpdateUserSetSelectColor() override {};
};

class ACE_EXPORT TextPickerDialogModelImpl : public TextPickerDialogModel {
public:
    RefPtr<AceType> CreateObject() override;
    void SetTextPickerDialogShow(RefPtr<AceType>& PickerText, NG::TextPickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange, std::function<void(const std::string&)>&& onScrollStop,
        std::function<void(const std::string&)>&& onEnterSelectedArea, TextPickerDialog& textPickerDialog,
        TextPickerDialogEvent& textPickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos) override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXTPICKER_MODEL_IMPL_H
