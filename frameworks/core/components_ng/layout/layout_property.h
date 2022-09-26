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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H

#include <memory>
#include <optional>

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/flex_property.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

class FrameNode;

class ACE_EXPORT LayoutProperty : public Property {
    DECLARE_ACE_TYPE(LayoutProperty, Property);

public:
    LayoutProperty() = default;

    ~LayoutProperty() override = default;

    virtual RefPtr<LayoutProperty> Clone() const;

    virtual void Reset();

    const std::optional<LayoutConstraintF>& GetLayoutConstraint() const
    {
        return layoutConstraint_;
    }

    const std::optional<LayoutConstraintF>& GetContentLayoutConstraint() const
    {
        return contentConstraint_;
    }

    const std::unique_ptr<MagicItemProperty>& GetMagicItemProperty() const
    {
        return magicItemProperty_;
    }

    const std::unique_ptr<PaddingProperty>& GetPaddingProperty() const
    {
        return padding_;
    }

    const std::unique_ptr<BorderWidthProperty>& GetBorderWidthProperty() const
    {
        return borderWidth_;
    }

    const std::unique_ptr<PositionProperty>& GetPositionProperty() const
    {
        return positionProperty_;
    }

    const std::unique_ptr<MeasureProperty>& GetCalcLayoutConstraint() const
    {
        return calcLayoutConstraint_;
    }

    const std::unique_ptr<FlexItemProperty>& GetFlexItemProperty() const
    {
        return flexItemProperty_;
    }
    MeasureType GetMeasureType(MeasureType defaultType = MeasureType::MATCH_CONTENT) const
    {
        return measureType_.value_or(defaultType);
    }

    void UpdatePadding(const PaddingProperty& value)
    {
        if (!padding_) {
            padding_ = std::make_unique<PaddingProperty>();
        }
        if (padding_->UpdateWithCheck(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateBorderWidth(const BorderWidthProperty& value)
    {
        if (!borderWidth_) {
            borderWidth_ = std::make_unique<BorderWidthProperty>();
        }
        if (borderWidth_->UpdateWithCheck(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateAlignment(Alignment value)
    {
        if (!positionProperty_) {
            positionProperty_ = std::make_unique<PositionProperty>();
        }
        if (positionProperty_->UpdateAlignment(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT;
        }
    }

    void UpdateLayoutWeight(float value)
    {
        if (!magicItemProperty_) {
            magicItemProperty_ = std::make_unique<MagicItemProperty>();
        }
        if (magicItemProperty_->UpdateLayoutWeight(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateAspectRatio(float ratio)
    {
        if (!magicItemProperty_) {
            magicItemProperty_ = std::make_unique<MagicItemProperty>();
        }
        if (magicItemProperty_->UpdateAspectRatio(ratio)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateMeasureType(MeasureType measureType)
    {
        if (measureType_ == measureType) {
            return;
        }
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        measureType_ = measureType;
    }

    // user defined max, min, self size.
    void UpdateCalcLayoutProperty(const MeasureProperty& constraint);

    void UpdateUserDefinedIdealSize(const CalcSize& value)
    {
        if (!calcLayoutConstraint_) {
            calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
        }
        if (calcLayoutConstraint_->UpdateSelfIdealSizeWithCheck(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateCalcMinSize(const CalcSize& value)
    {
        if (!calcLayoutConstraint_) {
            calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
        }
        if (calcLayoutConstraint_->UpdateMinSizeWithCheck(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateCalcMaxSize(const CalcSize& value)
    {
        if (!calcLayoutConstraint_) {
            calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
        }
        if (calcLayoutConstraint_->UpdateMaxSizeWithCheck(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateLayoutConstraint(const LayoutConstraintF& parentConstraint);

    void UpdateSelfIdealSize(const SizeF& value)
    {
        if (!layoutConstraint_.has_value()) {
            layoutConstraint_ = LayoutConstraintF();
        }
        if (layoutConstraint_->UpdateSelfIdealSizeWithCheck(OptionalSizeF(value))) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateFlexGrow(const float flexGrow)
    {
        if (!flexItemProperty_) {
            flexItemProperty_ = std::make_unique<FlexItemProperty>();
        }
        if (flexItemProperty_->UpdateFlexGrow(flexGrow)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateFlexShrink(const float flexShrink)
    {
        if (!flexItemProperty_) {
            flexItemProperty_ = std::make_unique<FlexItemProperty>();
        }
        if (flexItemProperty_->UpdateFlexShrink(flexShrink)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateAlignSelf(const FlexAlign& flexAlign)
    {
        if (!flexItemProperty_) {
            flexItemProperty_ = std::make_unique<FlexItemProperty>();
        }
        if (flexItemProperty_->UpdateAlignSelf(flexAlign)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateDisplayIndex(int32_t displayIndex)
    {
        if (!flexItemProperty_) {
            flexItemProperty_ = std::make_unique<FlexItemProperty>();
        }
        if (flexItemProperty_->UpdateDisplayIndex(displayIndex)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateContentConstraint();

    LayoutConstraintF CreateChildConstraint() const;

    LayoutConstraintF CreateContentConstraint() const
    {
        auto layoutConstraint = contentConstraint_.value_or(LayoutConstraintF());
        layoutConstraint.maxSize.UpdateSizeWhenSmaller(layoutConstraint.selfIdealSize.ConvertToSizeT());
        return layoutConstraint;
    }

    PaddingPropertyF CreatePaddingWithoutBorder();
    PaddingPropertyF CreatePaddingAndBorder();

    void SetHost(const WeakPtr<FrameNode>& host);
    RefPtr<FrameNode> GetHost() const;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(Visibility, VisibleType, PROPERTY_UPDATE_MEASURE);
    void OnVisibilityUpdate(VisibleType visible) const;

protected:
    void UpdateLayoutProperty(const LayoutProperty* layoutProperty);

    virtual void Clone(RefPtr<LayoutProperty> layoutProperty) const;

private:
    // This will call after ModifyLayoutConstraint.
    void CheckSelfIdealSize();

    void CheckAspectRatio();

    std::optional<LayoutConstraintF> layoutConstraint_;
    std::optional<LayoutConstraintF> contentConstraint_;

    std::unique_ptr<MeasureProperty> calcLayoutConstraint_;
    std::unique_ptr<PaddingProperty> padding_;
    std::unique_ptr<BorderWidthProperty> borderWidth_;
    std::unique_ptr<MagicItemProperty> magicItemProperty_;
    std::unique_ptr<PositionProperty> positionProperty_;
    std::unique_ptr<FlexItemProperty> flexItemProperty_;
    std::optional<MeasureType> measureType_;

    WeakPtr<FrameNode> host_;
    ACE_DISALLOW_COPY_AND_MOVE(LayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H
