/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_LAYOUT_PROPERTY_H
#define COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_LAYOUT_PROPERTY_H

#include "movingphoto_styles.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MovingPhotoLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(MovingPhotoLayoutProperty, LayoutProperty);

public:
    MovingPhotoLayoutProperty() = default;

    ~MovingPhotoLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<MovingPhotoLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propMovingPhotoStyle_ = CloneMovingPhotoStyle();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetMovingPhotoStyle();
    }

    ACE_DEFINE_PROPERTY_GROUP(MovingPhotoStyle, MovingPhotoStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, ObjectFit, ImageFit, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, VideoSource, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, ImageSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, VideoSize, SizeF, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, MovingPhotoUri, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, XmageHeight, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, ImageSize, SizeF, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, XmageOffset, SizeF, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(MovingPhotoStyle, XmageRawSize, SizeF, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(MovingPhotoLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_LAYOUT_PROPERTY_H
