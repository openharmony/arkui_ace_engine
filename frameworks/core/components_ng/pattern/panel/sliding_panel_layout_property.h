/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_LAYOUT_PROPERTY_H

#include <string>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SlidingPanelLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SlidingPanelLayoutProperty, LayoutProperty);

public:
    SlidingPanelLayoutProperty() = default;

    ~SlidingPanelLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SlidingPanelLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propPanelType_ = ClonePanelType();
        value->propPanelMode_ = ClonePanelMode();
        value->propHasDragBar_ = CloneHasDragBar();
        value->propCustomHeight_ = CloneCustomHeight();
        value->propMiniHeight_ = CloneMiniHeight();
        value->propHalfHeight_ = CloneHalfHeight();
        value->propFullHeight_ = CloneFullHeight();
        value->propIsShow_ = CloneIsShow();
        value->propShowCloseIcon_ = CloneShowCloseIcon();
        value->propBackgroundColor_ = CloneBackgroundColor();
        value->propBackgroundMask_ = CloneBackgroundMask();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetPanelType();
        ResetPanelMode();
        ResetHasDragBar();
        ResetCustomHeight();
        ResetMiniHeight();
        ResetHalfHeight();
        ResetFullHeight();
        ResetIsShow();
        ResetShowCloseIcon();
        ResetBackgroundColor();
        ResetBackgroundMask();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PanelType, PanelType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PanelMode, PanelMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HasDragBar, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CustomHeight, CalcDimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MiniHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HalfHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FullHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCloseIcon, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundMask, Color, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(SlidingPanelLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_LAYOUT_PROPERTY_H