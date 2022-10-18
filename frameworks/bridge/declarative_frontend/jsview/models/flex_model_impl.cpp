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

#include "bridge/declarative_frontend/jsview/models/flex_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/flex/flex_component.h"
#include "core/components/flex/flex_component_v2.h"
#include "core/components/wrap/wrap_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

void FlexModelImpl::CreateFlexRow()
{
    std::list<RefPtr<Component>> children;
    RefPtr<FlexComponentV2> row = AceType::MakeRefPtr<OHOS::Ace::FlexComponentV2>(
        FlexDirection::ROW, FlexAlign::FLEX_START, FlexAlign::STRETCH, children);
    row->SetInspectorTag("FlexComponentV2");
    ViewStackProcessor::GetInstance()->ClaimElementId(row);
    ViewStackProcessor::GetInstance()->Push(row);
}

void FlexModelImpl::CreateWrap()
{
    std::list<RefPtr<Component>> children;
    auto wrapComponent = AceType::MakeRefPtr<WrapComponent>(children);
    wrapComponent->SetMainAlignment(WrapAlignment::START);
    wrapComponent->SetCrossAlignment(WrapAlignment::STRETCH);
    ViewStackProcessor::GetInstance()->ClaimElementId(wrapComponent);
    ViewStackProcessor::GetInstance()->Push(wrapComponent);
}

void FlexModelImpl::SetFlexWidth()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto widthVal = box->GetWidth();
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(mainComponent);
    if (flex) {
        if (flex->GetDirection() == FlexDirection::ROW || flex->GetDirection() == FlexDirection::ROW_REVERSE) {
            flex->SetMainAxisSize(widthVal.Value() < 0.0 ? MainAxisSize::MIN : MainAxisSize::MAX);
        } else {
            flex->SetCrossAxisSize(widthVal.Value() < 0.0 ? CrossAxisSize::MIN : CrossAxisSize::MAX);
        }
    } else {
        auto wrap = AceType::DynamicCast<WrapComponent>(mainComponent);
        if (wrap) {
            wrap->SetHorizontalMeasure(widthVal.Value() < 0.0 ? MeasureType::CONTENT : MeasureType::PARENT);
        }
    }
}

void FlexModelImpl::SetFlexHeight()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto heightVal = box->GetHeight();
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(mainComponent);
    if (flex) {
        if (flex->GetDirection() == FlexDirection::COLUMN || flex->GetDirection() == FlexDirection::COLUMN_REVERSE) {
            flex->SetMainAxisSize(heightVal.Value() < 0.0 ? MainAxisSize::MIN : MainAxisSize::MAX);
        } else {
            flex->SetCrossAxisSize(heightVal.Value() < 0.0 ? CrossAxisSize::MIN : CrossAxisSize::MAX);
        }
    } else {
        auto wrap = AceType::DynamicCast<WrapComponent>(mainComponent);
        if (wrap) {
            wrap->SetVerticalMeasure(heightVal.Value() < 0.0 ? MeasureType::CONTENT : MeasureType::PARENT);
        }
    }
}

void FlexModelImpl::SetJustifyContent(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetMainAxisAlign(static_cast<FlexAlign>(value));
    } else {
        auto wrap = AceType::DynamicCast<WrapComponent>(component);
        if (wrap) {
            wrap->SetMainAlignment(static_cast<WrapAlignment>(value));
        }
    }
}

void FlexModelImpl::SetAlignItems(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetCrossAxisAlign(static_cast<FlexAlign>(value));
    } else {
        auto wrap = AceType::DynamicCast<WrapComponent>(component);
        if (wrap) {
            wrap->SetCrossAlignment(static_cast<WrapAlignment>(value));
        }
    }
}

void FlexModelImpl::SetAlignContent(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto wrap = AceType::DynamicCast<WrapComponent>(component);
    if (wrap) {
        wrap->SetAlignment(static_cast<WrapAlignment>(value));
    }
}

void FlexModelImpl::SetWrapDirection(WrapDirection direction)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto wrap = AceType::DynamicCast<WrapComponent>(component);
    if (wrap) {
        wrap->SetDirection(direction);
    }
}

void FlexModelImpl::SetDirection(FlexDirection direction)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetDirection(direction);
    }
}

void FlexModelImpl::SetMainAxisAlign(FlexAlign flexAlign)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetMainAxisAlign(flexAlign);
    }
}

void FlexModelImpl::SetWrapMainAlignment(WrapAlignment value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto wrap = AceType::DynamicCast<WrapComponent>(component);
    if (wrap) {
        wrap->SetMainAlignment(static_cast<WrapAlignment>(value));
    }
}

void FlexModelImpl::SetCrossAxisAlign(FlexAlign flexAlign)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetCrossAxisAlign(flexAlign);
    }
}

void FlexModelImpl::SetWrapCrossAlignment(WrapAlignment value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto wrap = AceType::DynamicCast<WrapComponent>(component);
    if (wrap) {
        wrap->SetCrossAlignment(static_cast<WrapAlignment>(value));
    }
}

void FlexModelImpl::SetWrapAlignment(WrapAlignment value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto wrap = AceType::DynamicCast<WrapComponent>(component);
    if (wrap) {
        wrap->SetAlignment(static_cast<WrapAlignment>(value));
    }
}

void FlexModelImpl::SetHasHeight()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto columComponent = AceType::DynamicCast<ColumnComponent>(component);
    auto rowComponent = AceType::DynamicCast<RowComponent>(component);
    if (columComponent) {
        columComponent->SetMainAxisSize(MainAxisSize::MAX);
    }
    if (rowComponent) {
        rowComponent->SetCrossAxisSize(CrossAxisSize::MAX);
    }
}

void FlexModelImpl::SetHasWidth()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto columComponent = AceType::DynamicCast<ColumnComponent>(component);
    auto rowComponent = AceType::DynamicCast<RowComponent>(component);
    if (columComponent) {
        columComponent->SetCrossAxisSize(CrossAxisSize::MAX);
    }
    if (rowComponent) {
        rowComponent->SetMainAxisSize(MainAxisSize::MAX);
    }
}

} // namespace OHOS::Ace::Framework
