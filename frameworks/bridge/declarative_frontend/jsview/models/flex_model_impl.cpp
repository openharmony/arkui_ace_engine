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
#include "core/components/wrap/wrap_component.h"

namespace OHOS::Ace::Framework {

void FlexModelImpl::SetFillParent()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetMainAxisSize(MainAxisSize::MAX);
    }
}

void FlexModelImpl::SetWrapContent()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetMainAxisSize(MainAxisSize::MIN);
    }
}

void FlexModelImpl::SetJustifyContent(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetMainAxisAlign((FlexAlign)value);
    } else {
        auto wrap = AceType::DynamicCast<WrapComponent>(component);
        if (wrap) {
            wrap->SetMainAlignment((WrapAlignment)value);
        }
    }
}

void FlexModelImpl::SetAlignItems(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto flex = AceType::DynamicCast<FlexComponent>(component);
    if (flex) {
        flex->SetCrossAxisAlign((FlexAlign)value);
    } else {
        auto wrap = AceType::DynamicCast<WrapComponent>(component);
        if (wrap) {
            wrap->SetCrossAlignment((WrapAlignment)value);
        }
    }
}

void FlexModelImpl::SetAlignContent(int32_t value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto wrap = AceType::DynamicCast<WrapComponent>(component);
    if (wrap) {
        wrap->SetAlignment((WrapAlignment)value);
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
