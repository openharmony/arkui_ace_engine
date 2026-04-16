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

#include "core/components_ng/pattern/image/image_render_property.h"

namespace OHOS::Ace::NG {

void ImagePaintStyle::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
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
    json->PutExtAttr("antiAlias", propAntiAlias.value_or(false) ? "true" : "false", filter);
}

RefPtr<PaintProperty> ImageRenderProperty::Clone() const
{
    auto renderProperty = MakeRefPtr<ImageRenderProperty>();
    renderProperty->UpdatePaintProperty(this);
    renderProperty->propImagePaintStyle_ = CloneImagePaintStyle();
    renderProperty->propNeedBorderRadius_ = CloneNeedBorderRadius();
    renderProperty->propImageFit_ = CloneImageFit();
    renderProperty->propImageMatrix_ = CloneImageMatrix();
    return renderProperty;
}

void ImageRenderProperty::Reset()
{
    ResetImagePaintStyle();
    ResetNeedBorderRadius();
}

void ImageRenderProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    PaintProperty::ToJsonValue(json, filter);
    ACE_PROPERTY_TO_JSON_VALUE(propImagePaintStyle_, ImagePaintStyle);
}

} // namespace OHOS::Ace::NG