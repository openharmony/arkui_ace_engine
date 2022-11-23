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

#include "bridge/declarative_frontend/jsview/models/divider_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/box/box_component.h"
#include "core/components/divider/divider_component.h"
#include "core/components/divider/divider_theme.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void DividerModelImpl::Create()
{
    RefPtr<Component> dividerComponent = AceType::MakeRefPtr<OHOS::Ace::DividerComponent>();
    auto theme = JSViewAbstract::GetTheme<DividerTheme>();
    if (theme) {
        auto component = AceType::DynamicCast<OHOS::Ace::DividerComponent>(dividerComponent);
        component->SetDividerColor(theme->GetColor());
    }
    ViewStackProcessor::GetInstance()->ClaimElementId(dividerComponent);
    ViewStackProcessor::GetInstance()->Push(dividerComponent);
}
void DividerModelImpl::Vertical(bool value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::DividerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetVertical(value);
    }

    auto box = stack->GetBoxComponent();
    if (value) {
        box->SetFlex(BoxFlex::FLEX_Y);
    } else {
        box->SetFlex(BoxFlex::FLEX_X);
    }
}
void DividerModelImpl::DividerColor(const Color& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::DividerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetDividerColor(value);
    }
}
void DividerModelImpl::StrokeWidth(const Dimension& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::DividerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetStrokeWidth(value);
    }
}
void DividerModelImpl::LineCap(const enum LineCap& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::DividerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetLineCap(value);
    }
}

} // namespace OHOS::Ace::Framework