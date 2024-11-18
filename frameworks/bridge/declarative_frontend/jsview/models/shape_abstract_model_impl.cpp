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

#include "bridge/declarative_frontend/jsview/models/shape_abstract_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/shape/shape_component.h"

namespace OHOS::Ace::Framework {

void ShapeAbstractModelImpl::SetStroke(const Color& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStroke(color, option);
    }
}

void ShapeAbstractModelImpl::SetFill(const Color& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetFill(color, option);
}

void ShapeAbstractModelImpl::SetForegroundColor(const Color& color)
{
    SetFill(color);
}

void ShapeAbstractModelImpl::SetStrokeDashOffset(const Ace::Dimension& dashOffset)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeDashOffset(dashOffset, option);
    }
}

void ShapeAbstractModelImpl::SetStrokeLineCap(int lineCapStyle)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    if (static_cast<int>(LineCapStyle::SQUARE) == lineCapStyle) {
        component->SetStrokeLineCap(LineCapStyle::SQUARE);
    } else if (static_cast<int>(LineCapStyle::ROUND) == lineCapStyle) {
        component->SetStrokeLineCap(LineCapStyle::ROUND);
    } else {
        component->SetStrokeLineCap(LineCapStyle::BUTT);
    }
}

void ShapeAbstractModelImpl::SetStrokeLineJoin(int lineJoinStyle)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    if (static_cast<int>(LineJoinStyle::BEVEL) == lineJoinStyle) {
        component->SetStrokeLineJoin(LineJoinStyle::BEVEL);
    } else if (static_cast<int>(LineJoinStyle::ROUND) == lineJoinStyle) {
        component->SetStrokeLineJoin(LineJoinStyle::ROUND);
    } else {
        component->SetStrokeLineJoin(LineJoinStyle::MITER);
    }
}

void ShapeAbstractModelImpl::SetStrokeMiterLimit(double miterLimit)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    component->SetStrokeMiterLimit(miterLimit);
}

void ShapeAbstractModelImpl::SetStrokeOpacity(double opacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeOpacity(opacity, option);
    }
}

void ShapeAbstractModelImpl::SetFillOpacity(double opacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetFillOpacity(opacity, option);
    }
}

void ShapeAbstractModelImpl::SetStrokeWidth(const Ace::Dimension& lineWidth)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetStrokeWidth(lineWidth, option);
}

void ShapeAbstractModelImpl::SetStrokeDashArray(const std::vector<Ace::Dimension>& dashArray)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }
    component->SetStrokeDashArray(dashArray);
}
void ShapeAbstractModelImpl::SetAntiAlias(bool antiAlias)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (component) {
        component->SetAntiAlias(antiAlias);
    }
}

void ShapeAbstractModelImpl::SetWidth(Dimension& width)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetWidth(width, option);
}

void ShapeAbstractModelImpl::SetHeight(Dimension& height)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetHeight(height, option);
}

} // namespace OHOS::Ace::Framework