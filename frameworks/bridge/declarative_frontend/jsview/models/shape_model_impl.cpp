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

#include "bridge/declarative_frontend/jsview/models/shape_model_impl.h"

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/models/shape_abstract_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/shape/shape_component.h"
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

void ShapeModelImpl::SetBitmapMesh(std::vector<double>& mesh, int32_t column, int32_t row)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetBitmapMesh(mesh, column, row);
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

void ShapeModelImpl::SetWidth(Dimension& /*width*/)
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

void ShapeModelImpl::SetHeight(Dimension& /*height*/)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (!box->GetHeight().IsValid()) {
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetHeightFlag(true);
    }
}

void ShapeModelImpl::InitBox(RefPtr<PixelMap>& pixMap)
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

} // namespace OHOS::Ace::Framework