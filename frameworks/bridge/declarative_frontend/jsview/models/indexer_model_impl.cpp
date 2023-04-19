/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void IndexerModelImpl::Create(std::vector<std::string>& indexerArray, int32_t selectedVal)
{
    auto indexerComponent = AceType::MakeRefPtr<V2::IndexerComponent>(indexerArray, selectedVal);
    ViewStackProcessor::GetInstance()->ClaimElementId(indexerComponent);
    ViewStackProcessor::GetInstance()->Push(indexerComponent);
}

void IndexerModelImpl::SetFocusable(bool focusable)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    CHECK_NULL_VOID(focusableComponent);
    focusableComponent->SetFocusable(focusable);
}

void IndexerModelImpl::SetFocusNode(bool isFocusNode)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    CHECK_NULL_VOID(focusableComponent);
    focusableComponent->SetFocusNode(isFocusNode);
}

void IndexerModelImpl::SetSelectedColor(const Color& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        auto textStyle = indexerComponent->GetActiveTextStyle();
        textStyle.SetTextColor(color);
        indexerComponent->SetActiveTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetColor(const Color& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        auto textStyle = indexerComponent->GetNormalTextStyle();
        textStyle.SetTextColor(color);
        indexerComponent->SetNormalTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetPopupColor(const Color& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        auto textStyle = indexerComponent->GetBubbleTextStyle();
        textStyle.SetTextColor(color);
        indexerComponent->SetBubbleTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetSelectedBackgroundColor(const Color& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetSelectedBackgroundColor(color);
    }
}

void IndexerModelImpl::SetPopupBackground(const Color& color)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetBubbleBackgroundColor(color);
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

void IndexerModelImpl::SetSelectedFont(const TextStyle& textStyle)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetActiveTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetPopupFont(const TextStyle& textStyle)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetBubbleTextStyle(std::move(textStyle));
    }
}

void IndexerModelImpl::SetFont(const TextStyle& textStyle)
{
    auto indexerComponent =
        AceType::DynamicCast<V2::IndexerComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (indexerComponent) {
        indexerComponent->SetNormalTextStyle(std::move(textStyle));
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
} // namespace OHOS::Ace::Framework
