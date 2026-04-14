/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components/common/properties/depth_option.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DepthComponentLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(DepthComponentLayoutProperty, LayoutProperty);

public:
    DepthComponentLayoutProperty() = default;
    ~DepthComponentLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<DepthComponentLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propBackgroundSource_ = CloneBackgroundSource();
        value->propCameraParams_ = CloneCameraParams();
        value->propLightParams_ = CloneLightParams();
        value->propBackgroundOffset_ = CloneBackgroundOffset();
        value->propBackgroundScale_ = CloneBackgroundScale();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBackgroundSource();
        ResetCameraParams();
        ResetLightParams();
        ResetBackgroundOffset();
        ResetBackgroundScale();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundSource, OHOS::Ace::DepthBackgroundSource, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraParams, OHOS::Ace::DepthCameraParams, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LightParams, OHOS::Ace::DepthLightParams, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundOffset, OHOS::Ace::DepthBackgroundOffset, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundScale, std::optional<NG::VectorF>, PROPERTY_UPDATE_NORMAL);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DEPTH_COMPONENT_DEPTH_COMPONENT_LAYOUT_PROPERTY_H
