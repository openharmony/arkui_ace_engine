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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_PROPERTY_H

#include "base/geometry/ng/offset_t.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT BubbleLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(BubbleLayoutProperty, LayoutProperty);

public:
    BubbleLayoutProperty() = default;
    ~BubbleLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<BubbleLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propEnableArrow_ = CloneEnableArrow();
        value->propUseCustom_ = CloneUseCustom();
        value->propPlacement_ = ClonePlacement();
        value->propShowInSubWindow_ = CloneShowInSubWindow();
        value->propDisplayWindowOffset_ = CloneDisplayWindowOffset();
        value->propTargetSpace_ = CloneTargetSpace();
        value->propBlockEvent_ = CloneBlockEvent();
        value->propPositionOffset_ = ClonePositionOffset();
        value->propArrowHeight_ = CloneArrowHeight();
        value->propArrowWidth_ = CloneArrowWidth();
        value->propRadius_ = CloneRadius();
        value->propIsCaretMode_ = CloneIsCaretMode();
        value->propEnableHoverMode_ = CloneEnableHoverMode();
        value->propFollowTransformOfTarget_ = CloneFollowTransformOfTarget();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetEnableArrow();
        ResetPlacement();
        ResetUseCustom();
        ResetShowInSubWindow();
        ResetDisplayWindowOffset();
        ResetTargetSpace();
        ResetBlockEvent();
        ResetPositionOffset();
        ResetArrowHeight();
        ResetArrowWidth();
        ResetRadius();
        ResetIsCaretMode();
        ResetEnableHoverMode();
        ResetFollowTransformOfTarget();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableArrow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseCustom, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Placement, Placement, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowInSubWindow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayWindowOffset, OffsetF, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TargetSpace, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BlockEvent, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PositionOffset, OffsetF, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowHeight, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowWidth, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Radius, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsCaretMode, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableHoverMode, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FollowTransformOfTarget, bool, PROPERTY_UPDATE_LAYOUT);

private:
    ACE_DISALLOW_COPY_AND_MOVE(BubbleLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_PROPERTY_H
