/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/shape_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/shape/shape_container_component.h"

namespace OHOS::Ace::Framework {

void ShapeModelImpl::Create()
{
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    RefPtr<OHOS::Ace::ShapeContainerComponent> component =
        AceType::MakeRefPtr<OHOS::Ace::ShapeContainerComponent>(componentChildren);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
}

void ShapeModelImpl::SetBitmapMesh(const std::vector<float>& mesh, int32_t column, int32_t row)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetBitmapMesh(std::vector<double>(mesh.begin(), mesh.end()), column, row);
    }
}

void ShapeModelImpl::SetViewPort(
    const Dimension& dimLeft, const Dimension& dimTop, const Dimension& dimWidth, const Dimension& dimHeight)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("shape is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    ShapeViewBox viewBox;
    viewBox.SetLeft(dimLeft, option);
    viewBox.SetTop(dimTop, option);
    viewBox.SetWidth(dimWidth, option);
    viewBox.SetHeight(dimHeight, option);
    component->SetViewBox(viewBox);
}

void ShapeModelImpl::SetWidth()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (!box) {
        return;
    }
    if (!box->GetWidth().IsValid()) {
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetWidthFlag(true);
    }
}

void ShapeModelImpl::SetHeight()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (!box) {
        return;
    }
    if (!box->GetHeight().IsValid()) {
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetHeightFlag(true);
    }
}

void ShapeModelImpl::InitBox(const RefPtr<PixelMap>& pixMap)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetOverflow(Overflow::FORCE_CLIP);
    auto clipPath = AceType::MakeRefPtr<ClipPath>();
    clipPath->SetGeometryBoxType(GeometryBoxType::BORDER_BOX);
    box->SetClipPath(clipPath);
    if (pixMap) {
        box->SetPixelMap(pixMap);
    }
}

void ShapeModelImpl::SetStroke(const Color& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStroke(color, option);
    }
}

void ShapeModelImpl::SetFill(const Color& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    component->SetFill(color, option);
}

void ShapeModelImpl::SetStrokeDashOffset(const Ace::Dimension& dashOffset)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeDashOffset(dashOffset, option);
    }
}

void ShapeModelImpl::SetStrokeLineCap(int lineCapStyle)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
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

void ShapeModelImpl::SetStrokeLineJoin(int lineJoinStyle)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
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

void ShapeModelImpl::SetStrokeMiterLimit(double miterLimit)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    component->SetStrokeMiterLimit(miterLimit);
}

void ShapeModelImpl::SetStrokeOpacity(double opacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeOpacity(opacity, option);
    }
}

void ShapeModelImpl::SetFillOpacity(double opacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetFillOpacity(opacity, option);
    }
}

void ShapeModelImpl::SetStrokeWidth(const Ace::Dimension& lineWidth)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    if (GreatOrEqual(lineWidth.Value(), 0.0)) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeWidth(lineWidth, option);
    }
}

void ShapeModelImpl::SetStrokeDashArray(const std::vector<Ace::Dimension>& dashArray)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }
    component->SetStrokeDashArray(dashArray);
}

void ShapeModelImpl::SetAntiAlias(bool antiAlias)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetAntiAlias(antiAlias);
    }
}

} // namespace OHOS::Ace::Framework