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

#include "bridge/declarative_frontend/jsview/models/textpicker_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components/picker/picker_text_component.h"

namespace OHOS::Ace::Framework {
void TextPickerModelImpl::Create(RefPtr<PickerTheme> pickerTheme, uint32_t columnKind)
{
    (void)columnKind;
    auto textPicker = AceType::MakeRefPtr<PickerTextComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(textPicker);

    textPicker->SetIsDialog(false);
    textPicker->SetHasButtons(false);
    textPicker->SetTheme(pickerTheme);
    ViewStackProcessor::GetInstance()->Push(textPicker);
}

void TextPickerModelImpl::SetDefaultPickerItemHeight(const Dimension& value)
{
    auto textPicker = AceType::DynamicCast<PickerTextComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    textPicker->SetDefaultHeight(true);
    JSViewSetProperty(&PickerTextComponent::SetColumnHeight, value);
}

void TextPickerModelImpl::SetSelected(uint32_t value)
{
    JSViewSetProperty(&PickerTextComponent::SetSelected, value);
}

void TextPickerModelImpl::SetRange(const std::vector<NG::RangeContent>& value)
{
    if (!value.size()) {
        return;
    }
    std::vector<std::string> textRange;
    for (auto& range : value) {
        textRange.emplace_back(range.text_);
    }
    JSViewSetProperty(&PickerTextComponent::SetRange, textRange);
}

void TextPickerModelImpl::SetOnCascadeChange(TextCascadeChangeEvent&& onChange)
{
    auto func = onChange;
    auto onChangeEvent = [func](const std::string& value, const double& index) {
        std::vector<std::string> changeValue { value };
        std::vector<double> changeIndex { index };
        func(changeValue, changeIndex);
    };
    JSViewSetProperty(&PickerBaseComponent::SetOnTextChange, std::move(onChangeEvent));
}

void TextPickerModelImpl::SetOnScrollStop(TextCascadeChangeEvent&& onScrollStop) {}

void TextPickerModelImpl::SetBackgroundColor(const Color& color)
{
    auto pickerBase = AceType::DynamicCast<PickerBaseComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!pickerBase) {
        LOGE("PickerBaseComponent is null");
        return;
    }

    pickerBase->SetHasBackgroundColor(true);
}

RefPtr<AceType> TextPickerDialogModelImpl::CreateObject()
{
    return AceType::MakeRefPtr<PickerTextComponent>();
}

void TextPickerDialogModelImpl::SetTextPickerDialogShow(RefPtr<AceType>& PickerText,
    NG::TextPickerSettingData& settingData, std::function<void()>&& onCancel,
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onChange,
    std::function<void(const std::string&)>&& onScrollStop, TextPickerDialog& textPickerDialog,
    TextPickerDialogEvent& textPickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pickerText = AceType::DynamicCast<PickerTextComponent>(PickerText);
    pickerText->SetIsDialog(true);
    pickerText->SetIsCreateDialogComponent(true);
    if (textPickerDialog.isDefaultHeight == true) {
        pickerText->SetColumnHeight(textPickerDialog.height);
        pickerText->SetDefaultHeight(true);
    }
    pickerText->SetSelected(textPickerDialog.selectedValue);
    pickerText->SetRange(textPickerDialog.getRangeVector);

    DialogProperties properties {};
    properties.alignment = Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) ? DialogAlignment::CENTER
                                                                                          : DialogAlignment::DEFAULT;
    properties.customComponent = pickerText;
    properties.customStyle = true;
    auto acceptId = EventMarker(std::move(onAccept));
    pickerText->SetDialogAcceptEvent(acceptId);
    auto cancelId = EventMarker(std::move(onCancel));
    pickerText->SetDialogCancelEvent(cancelId);
    auto changeId = EventMarker(std::move(onChange));
    pickerText->SetDialogChangeEvent(changeId);
    pickerText->SetDialogName("pickerTextDialog");
    pickerText->OpenDialog(properties);
}
} // namespace OHOS::Ace::Framework
