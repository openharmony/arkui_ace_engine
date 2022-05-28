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

#include "core/components_ng/layout/layout_property.h"

#include <memory>

#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void LayoutProperty::Reset()
{
    layoutConstraint_.reset();
    calLayoutConstraint_.reset();
    padding_.reset();
    magicItemProperty_.reset();
    positionProperty_.reset();
    measureType_.reset();
    CleanDirty();
}

RefPtr<LayoutProperty> LayoutProperty::Clone() const
{
    auto layoutProperty = MakeRefPtr<LayoutProperty>();
    layoutProperty->layoutConstraint_ = layoutConstraint_;
    if (calLayoutConstraint_) {
        layoutProperty->calLayoutConstraint_ = std::make_unique<MeasureProperty>(*calLayoutConstraint_);
    }
    if (padding_) {
        layoutProperty->padding_ = std::make_unique<PaddingProperty>(*padding_);
    }
    if (magicItemProperty_) {
        layoutProperty->magicItemProperty_ = std::make_unique<MagicItemProperty>(*magicItemProperty_);
    }
    if (positionProperty_) {
        layoutProperty->positionProperty_ = std::make_unique<PositionProperty>(*positionProperty_);
    }
    layoutProperty->measureType_ = measureType_;
    layoutProperty->propertyChangeFlag_ = propertyChangeFlag_;
    return layoutProperty;
}

void LayoutProperty::UpdateCalcLayoutProperty(const MeasureProperty& constraint)
{
    if (!calLayoutConstraint_) {
        calLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        return;
    }
    if (*calLayoutConstraint_ == constraint) {
        return;
    }
    calLayoutConstraint_->selfIdealSize = constraint.selfIdealSize;
    calLayoutConstraint_->maxSize = constraint.maxSize;
    calLayoutConstraint_->minSize = constraint.minSize;
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
}

void LayoutProperty::UpdateLayoutConstraint(const LayoutConstraintF& parentConstraint, bool updateFlag)
{
    if (!layoutConstraint_) {
        layoutConstraint_ = LayoutConstraintF();
    }
    LOGE("UpdateLayoutConstraint: %{public}s", parentConstraint.ToString().c_str());
    auto changed = false;
    if (calLayoutConstraint_) {
        if (calLayoutConstraint_->maxSize.has_value()) {
            changed = layoutConstraint_->UpdateMaxSizeWithCheck(ConvertToSize(calLayoutConstraint_->maxSize.value(),
                          parentConstraint.scaleProperty, parentConstraint.selfIdealSize.value_or(SizeF(-1, -1)))) ||
                      changed;
        }
        if (calLayoutConstraint_->minSize.has_value()) {
            changed = layoutConstraint_->UpdateMinSizeWithCheck(ConvertToSize(calLayoutConstraint_->minSize.value(),
                          parentConstraint.scaleProperty, parentConstraint.selfIdealSize.value_or(SizeF(-1, -1)))) ||
                      changed;
        }
        if (calLayoutConstraint_->selfIdealSize.has_value()) {
            changed = layoutConstraint_->UpdateSelfIdealSizeWithCheck(
                          ConvertToSize(calLayoutConstraint_->selfIdealSize.value(), parentConstraint.scaleProperty,
                              parentConstraint.selfIdealSize.value_or(SizeF(-1, -1)))) ||
                      changed;
        }
    }
    changed = layoutConstraint_->UpdateMaxSizeWithCheck(parentConstraint.maxSize) || changed;
    changed = layoutConstraint_->UpdateMinSizeWithCheck(parentConstraint.minSize) || changed;
    if (parentConstraint.selfIdealSize.has_value()) {
        changed = layoutConstraint_->UpdateParentIdealSizeWithCheck(parentConstraint.selfIdealSize.value()) || changed;
    }
    if (layoutConstraint_->scaleProperty != parentConstraint.scaleProperty) {
        layoutConstraint_->scaleProperty = parentConstraint.scaleProperty;
        changed = true;
    }
    CheckSelfIdealSize(updateFlag);
    LOGE("UpdateLayoutConstraint: %{public}s", layoutConstraint_->ToString().c_str());
    if (!changed || !updateFlag) {
        return;
    }
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
}

void LayoutProperty::CheckSelfIdealSize(bool updateFlag)
{
    if (measureType_ == MeasureType::MATCH_PARENT && layoutConstraint_->parentIdealSize.has_value()) {
        if (layoutConstraint_->UpdateSelfIdealSizeWithCheck(layoutConstraint_->parentIdealSize.value()) && updateFlag) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }
}

void LayoutProperty::UpdateContentConstraint(const std::optional<LayoutConstraintF>& replace, bool updateFlag)
{
    if (replace) {
        if (replace == contentConstraint_) {
            return;
        }
        contentConstraint_ = replace;
        if (updateFlag) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
        return;
    }
    auto contentConstraint = layoutConstraint_.value_or(LayoutConstraintF());
    if (padding_) {
        auto paddingF = ConvertToPaddingPropertyF(
            *padding_, contentConstraint.scaleProperty, contentConstraint.selfIdealSize.value_or(SizeF(0, 0)));
        contentConstraint.MinusPadding(paddingF.left, paddingF.right, paddingF.top, paddingF.bottom);
    }
    if (contentConstraint_ == contentConstraint) {
        return;
    }
    contentConstraint_ = contentConstraint;
    if (updateFlag) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

PaddingPropertyF LayoutProperty::CreatePaddingPropertyF()
{
    auto layoutConstraint = layoutConstraint_.value_or(LayoutConstraintF());
    auto sizeF = SizeF(0, 0);
    if (layoutConstraint_.has_value()) {
        sizeF = layoutConstraint_->selfIdealSize.value_or(SizeF(0, 0));
    }
    return ConvertToPaddingPropertyF(padding_, layoutConstraint.scaleProperty, sizeF);
}

} // namespace OHOS::Ace::NG
