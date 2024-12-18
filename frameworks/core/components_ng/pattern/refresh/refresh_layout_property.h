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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_REFRESH_LAYOUT_PROPERTY_H

#include "core/components_ng/base/inspector_filter.h"
#include "frameworks/core/components_ng/layout/layout_property.h"
#include "frameworks/core/components_ng/property/property.h"

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
        value->UpdateLayoutProperty(this);
        value->propIsRefreshing_ = CloneIsRefreshing();
        value->propIndicatorOffset_ = CloneIndicatorOffset();
        value->propFriction_ = CloneFriction();
        value->propLoadingText_ = CloneLoadingText();
        value->propPullToRefresh_ = ClonePullToRefresh();
        value->propRefreshOffset_ = CloneRefreshOffset();
        value->propPullDownRatio_ = ClonePullDownRatio();
        value->propIsCustomBuilderExist_ = CloneIsCustomBuilderExist();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetIsRefreshing();
        ResetIndicatorOffset();
        ResetFriction();
        ResetLoadingText();
        ResetPullToRefresh();
        ResetRefreshOffset();
        ResetPullDownRatio();
        ResetIsCustomBuilderExist();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr(
            "offset", propIndicatorOffset_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr(
            "refreshOffset", propRefreshOffset_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("pullToRefresh", propPullToRefresh_.value_or(true), filter);
        json->PutExtAttr("friction", propFriction_.value_or(1), filter);
        json->PutExtAttr("promptText", propLoadingText_.value_or(std::string()).c_str(), filter);
        if (propPullDownRatio_.has_value()) {
            json->PutExtAttr("pullDownRatio", propPullDownRatio_.value(), filter);
        } else {
            json->PutExtAttr("pullDownRatio", "", filter);
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsRefreshing, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IndicatorOffset, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Friction, int32_t, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LoadingText, std::string, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PullToRefresh, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RefreshOffset, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PullDownRatio, float, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsCustomBuilderExist, bool, PROPERTY_UPDATE_LAYOUT);

private:
    ACE_DISALLOW_COPY_AND_MOVE(RefreshLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_LAYOUT_PROPERTY_H
