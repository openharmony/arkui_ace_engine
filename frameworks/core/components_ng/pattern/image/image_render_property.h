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

#include "base/image/drawing_color_filter.h"
#include "base/image/drawing_lattice.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {

namespace RenderConstants {
    constexpr float DEFAULT_HDR_BRIGHTNESS = 1.0f;
} // namespace

struct ImagePaintStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageResizableSlice, ImageResizableSlice);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageRenderMode, ImageRenderMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageInterpolation, ImageInterpolation);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageRepeat, ImageRepeat);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ColorFilter, std::vector<float>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DrawingColorFilter, RefPtr<DrawingColorFilter>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageResizableLattice, RefPtr<DrawingLattice>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MatchTextDirection, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SvgFillColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SmoothEdge, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DynamicMode, DynamicRangeMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(HdrBrightness, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ContentTransition, ContentTransitionType);
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        static const char* OBJECTREPEATVALUE[] = { "ImageRepeat.NoRepeat", "ImageRepeat.X", "ImageRepeat.Y",
            "ImageRepeat.XY" };
        static const char* INTERPOLATIONVALUE[] = { "ImageInterpolation.None", "ImageInterpolation.Low",
            "ImageInterpolation.Medium", "ImageInterpolation.High" };
        static const char* RENDERMODEVALUE[] = { "ImageRenderMode.Original", "ImageRenderMode.Template" };
        json->PutExtAttr("objectRepeat",
            OBJECTREPEATVALUE[static_cast<int32_t>(propImageRepeat.value_or(ImageRepeat::NO_REPEAT))], filter);
        json->PutExtAttr("interpolation",
            INTERPOLATIONVALUE[static_cast<int32_t>(propImageInterpolation.value_or(ImageInterpolation::NONE))],
            filter);
        json->PutExtAttr("renderMode",
            RENDERMODEVALUE[static_cast<int32_t>(propImageRenderMode.value_or(ImageRenderMode::ORIGINAL))], filter);
        json->PutExtAttr("matchTextDirection", propMatchTextDirection.value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("fillColor", propSvgFillColor.value_or(Color::BLACK).ColorToString().c_str(), filter);
        std::string colorFilter;
        for (auto& num : propColorFilter.value_or(std::vector<float>())) {
            colorFilter += std::to_string(num) + " ";
        }
        json->PutExtAttr("colorFilter", colorFilter.c_str(), filter);
        json->PutExtAttr("hdrBrightness", propHdrBrightness.value_or(RenderConstants::DEFAULT_HDR_BRIGHTNESS), filter);
        static const char* CONTENTTRANSITIONVALUE[] = { "ContentTransitionEffect.IDENTITY",
            "ContentTransitionEffect.OPACITY" };
        json->PutExtAttr("contentTransition",
            CONTENTTRANSITIONVALUE[static_cast<int32_t>(
                propContentTransition.value_or(ContentTransitionType::IDENTITY))],
            filter);
    }
};

// PaintProperty are used to set render properties.
class ImageRenderProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ImageRenderProperty, PaintProperty);

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
        renderProperty->propImageMatrix_ = CloneImageMatrix();
        return renderProperty;
    }

    void Reset() override
    {
        ResetImagePaintStyle();
        ResetNeedBorderRadius();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        ACE_PROPERTY_TO_JSON_VALUE(propImagePaintStyle_, ImagePaintStyle);
    }

    ACE_DEFINE_PROPERTY_GROUP(ImagePaintStyle, ImagePaintStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ImageRenderMode, ImageRenderMode, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ImagePaintStyle, ImageInterpolation, ImageInterpolation, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ImageRepeat, ImageRepeat, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, ColorFilter, std::vector<float>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ImagePaintStyle, DrawingColorFilter, RefPtr<DrawingColorFilter>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ImagePaintStyle, ImageResizableLattice, RefPtr<DrawingLattice>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, MatchTextDirection, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, SvgFillColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, SmoothEdge, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, DynamicMode, DynamicRangeMode, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(ImagePaintStyle, HdrBrightness, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ImagePaintStyle, ImageResizableSlice, ImageResizableSlice, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        ImagePaintStyle, ContentTransition, ContentTransitionType, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedBorderRadius, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderRadius, BorderRadiusProperty, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageFit, ImageFit, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageMatrix, Matrix4, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_RENDER_PROPERTY_H
