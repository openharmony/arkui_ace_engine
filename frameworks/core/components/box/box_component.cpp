/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/box/box_component.h"

#include "core/components/box/box_element.h"
#include "core/components/box/render_box.h"
#include "core/components/common/properties/decoration.h"

namespace OHOS::Ace {

RefPtr<Element> BoxComponent::CreateElement()
{
    return AceType::MakeRefPtr<BoxElement>();
}

RefPtr<RenderNode> BoxComponent::CreateRenderNode()
{
    return RenderBox::Create();
}

RefPtr<Decoration> BoxComponent::GetBackDecoration() const
{
    return backDecoration_;
}

RefPtr<Decoration> BoxComponent::GetFrontDecoration() const
{
    return frontDecoration_;
}

void BoxComponent::SetBackDecoration(const RefPtr<Decoration>& decoration)
{
    backDecoration_ = decoration;
    SetDecorationUpdateFlag(true);
}

void BoxComponent::SetFrontDecoration(const RefPtr<Decoration>& decoration)
{
    frontDecoration_ = decoration;
    SetDecorationUpdateFlag(true);
}

const Color& BoxComponent::GetColor() const
{
    if (backDecoration_) {
        return backDecoration_->GetBackgroundColor();
    }
    return Color::TRANSPARENT;
}

void BoxComponent::SetColor(const Color& color, const AnimationOption& option)
{
    if (!backDecoration_) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    backDecoration_->SetBackgroundColor(color, option);
}

void BoxComponent::SetColor(const AnimatableColor& color)
{
    if (!backDecoration_) {
        backDecoration_ = AceType::MakeRefPtr<Decoration>();
    }
    backDecoration_->SetBackgroundColor(color);
}

} // namespace OHOS::Ace
