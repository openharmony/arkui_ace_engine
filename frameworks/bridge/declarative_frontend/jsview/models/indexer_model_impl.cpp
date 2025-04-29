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

#include "bridge/declarative_frontend/jsview/models/indexer_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void IndexerModelImpl::Create(std::vector<std::string>& indexerArray, int32_t selectedVal, bool isArc)
{
    if (static_cast<int32_t>(indexerArray.size()) <= 0) {
        return;
    }
    auto indexerComponent = AceType::MakeRefPtr<V2::IndexerComponent>(indexerArray, selectedVal);
    ViewStackProcessor::GetInstance()->ClaimElementId(indexerComponent);
    ViewStackProcessor::GetInstance()->Push(indexerComponent);
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    CHECK_NULL_VOID(focusableComponent);
    focusableComponent->SetFocusable(true);
    focusableComponent->SetFocusNode(true);
}

void IndexerModelImpl::SetSelectedColor(const std::optional<Color>& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent && color.has_value()) {
        auto textStyle = indexerComponent->GetActiveTextStyle();
        textStyle.SetTextColor(color.value());
        indexerComponent->SetActiveTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetColor(const std::optional<Color>& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent && color.has_value()) {
        auto textStyle = indexerComponent->GetNormalTextStyle();
        textStyle.SetTextColor(color.value());
        indexerComponent->SetNormalTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetPopupColor(const std::optional<Color>& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent && color.has_value()) {
        auto textStyle = indexerComponent->GetBubbleTextStyle();
        textStyle.SetTextColor(color.value());
        indexerComponent->SetBubbleTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetSelectedBackgroundColor(const std::optional<Color>& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent && color.has_value()) {
        indexerComponent->SetSelectedBackgroundColor(color.value());
    }
}

void IndexerModelImpl::SetPopupBackground(const std::optional<Color>& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent && color.has_value()) {
        indexerComponent->SetBubbleBackgroundColor(color.value());
    }
}

void IndexerModelImpl::SetUsingPopup(bool state)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetBubbleEnabled(state);
    }
}

void IndexerModelImpl::SetSelectedFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
    std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        TextStyle textStyle;
        SetTextStyle(textStyle, fontSize, fontWeight, fontFamily, fontStyle);
        indexerComponent->SetActiveTextStyle(textStyle);
    }
}

void IndexerModelImpl::SetPopupFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
    std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        TextStyle textStyle;
        SetTextStyle(textStyle, fontSize, fontWeight, fontFamily, fontStyle);
        indexerComponent->SetBubbleTextStyle(textStyle);
    }
}

void IndexerModelImpl::SetFont(std::optional<Dimension>& fontSize, std::optional<FontWeight>& fontWeight,
    std::optional<std::vector<std::string>>& fontFamily, std::optional<FontStyle>& fontStyle)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        TextStyle textStyle;
        SetTextStyle(textStyle, fontSize, fontWeight, fontFamily, fontStyle);
        indexerComponent->SetNormalTextStyle(textStyle);
    }
}

void IndexerModelImpl::SetItemSize(const Dimension& value)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetItemSize(value);
    }
}

void IndexerModelImpl::SetAlignStyle(int32_t value)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetAlignStyle(ALIGN_STYLE[value]);
    }
}

void IndexerModelImpl::SetOnSelected(std::function<void(const int32_t selected)>&& onSelect)
{
    auto fun = onSelect;
    auto onSelectEvent = [fun](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<V2::IndexerEventInfo>(info);
        if (!eventInfo) {
            return;
        }
        fun(eventInfo->GetSelectedIndex());
    };

    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    auto eventMarker = EventMarker(std::move(onSelectEvent));
    if (indexerComponent) {
        indexerComponent->SetSelectedEvent(eventMarker);
    }
}

void IndexerModelImpl::SetOnRequestPopupData(
    std::function<std::vector<std::string>(const int32_t selected)>&& RequestPopupData)
{
    auto fun = RequestPopupData;
    auto onSelectEvent = [fun](std::shared_ptr<V2::IndexerEventInfo> info) -> std::vector<std::string> {
        return fun(info->GetSelectedIndex());
    };

    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetRequestPopupDataFunc(std::move(onSelectEvent));
    }
}

void IndexerModelImpl::SetOnPopupSelected(std::function<void(const int32_t selected)>&& onPopupSelected)
{
    auto fun = onPopupSelected;
    auto onPopupSelectedEvent = [fun](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<V2::IndexerEventInfo>(info);
        if (!eventInfo) {
            return;
        }
        fun(eventInfo->GetSelectedIndex());
    };

    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    auto eventMarker = EventMarker(std::move(onPopupSelectedEvent));
    if (indexerComponent) {
        indexerComponent->SetPopupSelectedEvent(eventMarker);
    }
}

void IndexerModelImpl::SetTextStyle(TextStyle& textStyle, std::optional<Dimension>& fontSize,
    std::optional<FontWeight>& fontWeight, std::optional<std::vector<std::string>>& fontFamily,
    std::optional<FontStyle>& fontStyle)
{
    if (fontSize.has_value()) {
        textStyle.SetFontSize(fontSize.value());
    }
    if (fontWeight.has_value()) {
        textStyle.SetFontWeight(fontWeight.value());
    }
    if (fontFamily.has_value()) {
        textStyle.SetFontFamilies(fontFamily.value());
    }
    if (fontStyle.has_value()) {
        textStyle.SetFontStyle(fontStyle.value());
    }
}
} // namespace OHOS::Ace::Framework
