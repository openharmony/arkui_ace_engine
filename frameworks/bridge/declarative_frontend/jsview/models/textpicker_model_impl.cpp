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
void TextPickerModelImpl::Create(RefPtr<PickerTheme> pickerTheme)
{
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

void TextPickerModelImpl::SetRange(const std::vector<std::string>& value)
{
    JSViewSetProperty(&PickerTextComponent::SetRange, value);
}

void TextPickerModelImpl::SetOnChange(TextChangeEvent&& onChange)
{
    JSViewSetProperty(&PickerBaseComponent::SetOnTextChange, std::move(onChange));
}
} // namespace OHOS::Ace::Framework
