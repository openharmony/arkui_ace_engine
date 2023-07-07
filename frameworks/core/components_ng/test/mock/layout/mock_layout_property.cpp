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

bool LayoutProperty::HasFixedWidth() const
{
    return false;
}

bool LayoutProperty::HasFixedHeight() const
{
    return false;
}

bool LayoutProperty::HasAspectRatio() const
{
    return false;
}

float LayoutProperty::GetAspectRatio() const
{
    return 0.0f;
}

void LayoutProperty::UpdateAspectRatio(float ratio) {}

void LayoutProperty::UpdateGeometryTransition(const std::string& id) {}

void LayoutProperty::UpdateLayoutDirection(TextDirection value) {}

void LayoutProperty::UpdateLayoutWeight(float value) {}

void LayoutProperty::UpdateBorderWidth(const BorderWidthProperty& value) {}

void LayoutProperty::UpdateAlignment(Alignment value) {}

void LayoutProperty::UpdateMargin(const MarginProperty& value) {}

void LayoutProperty::UpdatePadding(const PaddingProperty& value) {}

void LayoutProperty::UpdateUserDefinedIdealSize(const CalcSize& value) {}

void LayoutProperty::ClearUserDefinedIdealSize(bool clearWidth, bool clearHeight) {}

void LayoutProperty::UpdateCalcMinSize(const CalcSize& value) {}

void LayoutProperty::UpdateCalcMaxSize(const CalcSize& value) {}

void LayoutProperty::UpdateMarginSelfIdealSize(const SizeF& value) {}

void LayoutProperty::ResetCalcMinSize() {}

void LayoutProperty::UpdateFlexGrow(float flexGrow) {}

void LayoutProperty::ResetFlexGrow() {}

void LayoutProperty::UpdateFlexShrink(float flexShrink) {}

void LayoutProperty::ResetFlexShrink() {}

void LayoutProperty::UpdateFlexBasis(const Dimension& flexBasis) {}

void LayoutProperty::UpdateAlignSelf(const FlexAlign& flexAlign) {}

void LayoutProperty::ResetAlignSelf() {}

void LayoutProperty::UpdateAlignRules(const std::map<AlignDirection, AlignRule>& alignRules) {}

void LayoutProperty::UpdateDisplayIndex(int32_t displayIndex) {}

LayoutConstraintF LayoutProperty::CreateContentConstraint() const
{
    return {};
}

void LayoutProperty::UpdateLayoutConstraint(const RefPtr<LayoutProperty>& layoutProperty) {}

void LayoutProperty::UpdateVisibility(const VisibleType& value, bool allowTransition) {}

void LayoutProperty::SetOverlayOffset(
    const std::optional<Dimension>& overlayOffsetX, const std::optional<Dimension>& overlayOffsetY)
{}

void LayoutProperty::GetOverlayOffset(Dimension& overlayOffsetX, Dimension& overlayOffsetY) {}
} // namespace OHOS::Ace::NG
