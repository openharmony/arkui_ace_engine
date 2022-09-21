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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_RENDER_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/render/paint_property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

struct ImagePaintStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageRenderMode, ImageRenderMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageInterpolation, ImageInterpolation);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageRepeat, ImageRepeat);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ColorFilter, std::vector<float>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MatchTextDirection, bool);
};

// PaintProperty are used to set render properties.
class ImageRenderProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ImageRenderProperty, PaintProperty)

public:
    ImageRenderProperty() = default;
    ~ImageRenderProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto renderProperty = MakeRefPtr<ImageRenderProperty>();
        renderProperty->UpdatePaintProperty(this);
        renderProperty->propImagePaintStyle_ = CloneImagePaintStyle();
        return renderProperty;
    }

    void Reset() override
    {
        ResetImagePaintStyle();
    }

    ACE_DEFINE_PROPERTY_GROUP(ImagePaintStyle, ImagePaintStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ImageRenderMode, ImageRenderMode, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ImagePaintStyle, ImageInterpolation, ImageInterpolation, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ImageRepeat, ImageRepeat, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ColorFilter, std::vector<float>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, MatchTextDirection, bool, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_RENDER_PROPERTY_H
