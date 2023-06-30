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

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
void LayoutProperty::Reset() {}
void LayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const {}
void LayoutProperty::FromJson(const std::unique_ptr<JsonValue>& json) {}

RefPtr<LayoutProperty> LayoutProperty::Clone() const
{
    return nullptr;
}

void LayoutProperty::SetHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

void LayoutProperty::Clone(RefPtr<LayoutProperty> layoutProperty) const {}

void LayoutProperty::UpdateCalcLayoutProperty(const MeasureProperty& constraint)
{
    if (!calcLayoutConstraint_) {
        calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        return;
    }
    if (*calcLayoutConstraint_ == constraint) {
        return;
    }
    calcLayoutConstraint_->selfIdealSize = constraint.selfIdealSize;
    calcLayoutConstraint_->maxSize = constraint.maxSize;
    calcLayoutConstraint_->minSize = constraint.minSize;
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
}

void LayoutProperty::UpdateLayoutProperty(const LayoutProperty* layoutProperty) {}

void LayoutProperty::UpdateLayoutConstraint(const LayoutConstraintF& parentConstraint)
{
    layoutConstraint_ = parentConstraint;
}

void LayoutProperty::OnVisibilityUpdate(VisibleType visible, bool allowTransition) {}

RefPtr<FrameNode> LayoutProperty::GetHost() const
{
    return nullptr;
}

LayoutConstraintF CreateChildConstraint()
{
    return {};
}

void BuildGridProperty(const RefPtr<FrameNode>& host) {}

void UpdateContentConstraint() {}

MarginPropertyF CreateMargin()
{
    return {};
}

PaddingPropertyF CreatePaddingAndBorder()
{
    return {};
}
} // namespace OHOS::Ace::NG
