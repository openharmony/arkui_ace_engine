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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_RENDER_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

// PaintProperty are used to set render properties.
class BubbleRenderProperty : public PaintProperty {
    DECLARE_ACE_TYPE(BubbleRenderProperty, PaintProperty)
public:
    BubbleRenderProperty() = default;
    ~BubbleRenderProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<BubbleRenderProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propAutoCancel_ = CloneAutoCancel();
        paintProperty->propMaskColor_ = CloneMaskColor();
        paintProperty->propEnableArrow_ = CloneEnableArrow();
        paintProperty->propUseCustom_ = CloneUseCustom();
        paintProperty->propIsTips_ = CloneIsTips();
        paintProperty->propBackgroundColor_ = CloneBackgroundColor();
        paintProperty->propArrowOffset_ = CloneArrowOffset();
        paintProperty->propPlacement_ = ClonePlacement();
        paintProperty->propPrimaryButtonShow_ = ClonePrimaryButtonShow();
        paintProperty->propSecondaryButtonShow_ = CloneSecondaryButtonShow();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetAutoCancel();
        ResetBackgroundColor();
        ResetEnableArrow();
        ResetMaskColor();
        ResetUseCustom();
        ResetIsTips();
        ResetPlacement();
        ResetArrowOffset();
        ResetPrimaryButtonShow();
        ResetSecondaryButtonShow();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoCancel, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaskColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Placement, Placement, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableArrow, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(UseCustom, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsTips, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PrimaryButtonShow, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SecondaryButtonShow, bool, PROPERTY_UPDATE_RENDER);

    ACE_DISALLOW_COPY_AND_MOVE(BubbleRenderProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_RENDER_PROPERTY_H