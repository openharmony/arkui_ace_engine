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

#include "bridge/declarative_frontend/jsview/models/rect_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void RectModelImpl::Create()
{
    RefPtr<ShapeComponent> rectComponent = AceType::MakeRefPtr<OHOS::Ace::ShapeComponent>(ShapeType::RECT);
    ViewStackProcessor::GetInstance()->ClaimElementId(rectComponent);
    ViewStackProcessor::GetInstance()->Push(rectComponent);
}

void RectModelImpl::SetRadiusWidth(const Dimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("shapeComponent is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetRadiusWidth(value, option);
}

void RectModelImpl::SetRadiusHeight(const Dimension& value)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("shapeComponent is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetRadiusHeight(value, option);
}

void RectModelImpl::SetRadiusValue(const Dimension& radiusX, const Dimension& radiusY, int32_t index)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    Radius newRadius = Radius(AnimatableDimension(radiusX, option), AnimatableDimension(radiusY, option));
    switch (index) {
        case TOP_LEFT_RADIUS:
            component->SetTopLeftRadius(newRadius);
            break;
        case TOP_RIGHT_RADIUS:
            component->SetTopRightRadius(newRadius);
            break;
        case BOTTOM_RIGHT_RADIUS:
            component->SetBottomRightRadius(newRadius);
            break;
        case BOTTOM_LEFT_RADIUS:
            component->SetBottomLeftRadius(newRadius);
            break;
        default:
            break;
    }
}

} // namespace OHOS::Ace::Framework