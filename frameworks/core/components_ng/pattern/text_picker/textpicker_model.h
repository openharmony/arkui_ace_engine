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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_MODEL_H

#include <functional>
#include <mutex>

#include "base/geometry/dimension.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace {
struct TextPickerDialog {
    CalcDimension height;
    uint32_t selectedValue;
    std::vector<std::string> getRangeVector;
    bool isDefaultHeight;
    std::optional<DialogAlignment> alignment;
    std::optional<DimensionOffset> offset;
    std::optional<DimensionRect> maskRect;
};
using TextChangeEvent = std::function<void(const std::string&, double)>;
using TextCascadeChangeEvent = std::function<void(const std::vector<std::string>&, const std::vector<double>&)>;
using TextCascadeValueChangeEvent = std::function<void(const std::vector<std::string>&)>;
using TextCascadeSelectedChangeEvent = std::function<void(const std::vector<double>&)>;
class TextPickerModel {
public:
    static TextPickerModel* GetInstance();
    virtual ~TextPickerModel() = default;

    virtual void Create(RefPtr<PickerTheme> pickerTheme, uint32_t columnKind) = 0;
    virtual void SetSelected(uint32_t value) = 0;
    virtual void SetRange(const std::vector<NG::RangeContent>& value) = 0;
    virtual void SetValue(const std::string& value) = 0;
    virtual void SetDefaultPickerItemHeight(const Dimension& value) = 0;
    virtual void SetCanLoop(const bool value) = 0;
    virtual void SetDefaultAttributes(const RefPtr<PickerTheme>& pickerTheme) = 0;
    virtual void SetDisappearTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) = 0;
    virtual void SetNormalTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) = 0;
    virtual void SetSelectedTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) = 0;
    virtual void MultiInit(const RefPtr<PickerTheme> pickerTheme) = 0;
    virtual void SetColumns(const std::vector<NG::TextCascadePickerOptions>& options) = 0;
    virtual void SetIsCascade(bool isCascade) = 0;
    virtual void SetOnCascadeChange(TextCascadeChangeEvent&& onChange) = 0;
    virtual void SetValues(const std::vector<std::string>& values) = 0;
    virtual void SetSelecteds(const std::vector<uint32_t>& values) = 0;
    virtual bool IsSingle() = 0;
    virtual bool GetSingleRange(std::vector<NG::RangeContent>& rangeValue) = 0;
    virtual bool IsCascade() = 0;
    virtual uint32_t GetMaxCount() = 0;
    virtual void SetMaxCount(uint32_t maxCount) = 0;
    virtual bool GetMultiOptions(std::vector<NG::TextCascadePickerOptions>& options) = 0;
    virtual void SetBackgroundColor(const Color& color) = 0;
    virtual void SetHasSelectAttr(bool value) = 0;
    virtual void SetOnValueChangeEvent(TextCascadeValueChangeEvent&& onChange) = 0;
    virtual void SetOnSelectedChangeEvent(TextCascadeSelectedChangeEvent&& onChange) = 0;

private:
    static std::unique_ptr<TextPickerModel> textPickerInstance_;
    static std::mutex mutex_;
};

class TextPickerDialogModel {
public:
    static TextPickerDialogModel* GetInstance();
    virtual ~TextPickerDialogModel() = default;

    virtual RefPtr<AceType> CreateObject() = 0;
    virtual void SetTextPickerDialogShow(RefPtr<AceType>& PickerText, NG::TextPickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange, TextPickerDialog& textPickerDialog) = 0;

private:
    static std::unique_ptr<TextPickerDialogModel> textPickerDialogInstance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_MODEL_H
