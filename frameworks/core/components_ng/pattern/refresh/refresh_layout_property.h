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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline/base/sole_child_component.h"
#include "core/components_ng/pattern/refresh/refresh_theme_styles.h"
namespace OHOS::Ace::NG {

enum class RefreshStatus {
    // The default status.
    INACTIVE = 0,
    // While being dragged but not enough to trig refresh.
    DRAG,
    // Dragging enough to refresh, and less than the max distance.
    OVER_DRAG,
    // While it is refreshing.
    REFRESH,
    // While it will scroll back to the top after refreshing.
    DONE,
};

class ACE_EXPORT RefreshLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(RefreshLayoutProperty, LayoutProperty);

public:
    RefreshLayoutProperty() = default;

    ~RefreshLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<RefreshLayoutProperty>();
        value->propIsRefreshing_ = CloneIsRefreshing();
        value->propRefreshDistance_ = CloneRefreshDistance();
        value->propIsUseOffset_ = CloneIsUseOffset();
        value->propIndicatorOffset_ = CloneIndicatorOffset();
        value->propShowTimeOffset_ = CloneShowTimeOffset();
        value->propFriction_ = CloneFriction();
        value->propIsRefresh_ = CloneIsRefresh();
        value->propIsShowLastTime_ = CloneIsShowLastTime();
        value->propRefreshStatus_ = CloneRefreshStatus();
        value->propScrollableOffset_ = CloneScrollableOffset();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetRefreshStyle();
        ResetIsRefreshing();
        ResetRefreshDistance();
        ResetIsUseOffset();
        ResetIndicatorOffset();
        ResetShowTimeOffset();
        ResetFriction();
        ResetIsRefresh();
        ResetIsShowLastTime();
        ResetRefreshStatus();
        ResetScrollableOffset();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsRefreshing, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RefreshDistance, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsUseOffset, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorOffset, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowTimeOffset, OffsetF, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Friction, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsRefresh, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowLastTime, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RefreshStatus, RefreshStatus, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollableOffset, OffsetF, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(RefreshStyle, RefreshStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, LoadingDistance, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, ProgressDistance, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, ProgressDiameter, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, MaxDistance, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, ShowTimeDistance, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, TextStyle, TextStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, ProgressColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RefreshStyle, BackgroundColor, Color, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(RefreshLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H
