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
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SvgFillColor, Color);
    void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        static const char* OBJECTREPEATVALUE[] = { "ImageRepeat.NoRepeat", "ImageRepeat.X", "ImageRepeat.Y",
            "ImageRepeat.XY" };
        static const char* INTERPOLATIONVALUE[] = { "ImageInterpolation.None", "ImageInterpolation.Low",
            "ImageInterpolation.Medium", "ImageInterpolation.High" };
        static const char* RENDERMODEVALUE[] = { "ImageRenderMode.Original", "ImageRenderMode.Template" };
        json->Put(
            "objectRepeat", OBJECTREPEATVALUE[static_cast<int32_t>(propImageRepeat.value_or(ImageRepeat::NO_REPEAT))]);
        json->Put("interpolation",
            INTERPOLATIONVALUE[static_cast<int32_t>(propImageInterpolation.value_or(ImageInterpolation::NONE))]);
        json->Put("renderMode",
            RENDERMODEVALUE[static_cast<int32_t>(propImageRenderMode.value_or(ImageRenderMode::ORIGINAL))]);
        json->Put("matchTextDirection", propMatchTextDirection.value_or(false) ? "true" : "false");
        json->Put("fillColor", propSvgFillColor.value_or(Color::BLACK).ColorToString().c_str());
        std::string colorFilter;
        for (auto& num : propColorFilter.value_or(std::vector<float>())) {
            colorFilter += std::to_string(num) + " ";
        }
        json->Put("colorFilter", colorFilter.c_str());
    }
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
        renderProperty->propNeedBorderRadius_ = CloneNeedBorderRadius();
        renderProperty->propImageFit_ = CloneImageFit();
        return renderProperty;
    }

    void Reset() override
    {
        ResetImagePaintStyle();
        ResetNeedBorderRadius();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        PaintProperty::ToJsonValue(json);
        ACE_PROPERTY_TO_JSON_VALUE(propImagePaintStyle_, ImagePaintStyle);
    }

    ACE_DEFINE_PROPERTY_GROUP(ImagePaintStyle, ImagePaintStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ImageRenderMode, ImageRenderMode, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ImagePaintStyle, ImageInterpolation, ImageInterpolation, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ImageRepeat, ImageRepeat, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ColorFilter, std::vector<float>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, MatchTextDirection, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, SvgFillColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedBorderRadius, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageFit, ImageFit, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_RENDER_PROPERTY_H
