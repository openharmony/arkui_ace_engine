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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_PROPERTY_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/vector.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/property/clip_path.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {
enum class BlurStyle;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

struct BackgroundProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackgroundImage, ImageSourceInfo);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackgroundImageRepeat, ImageRepeat);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackgroundImageSize, BackgroundImageSize);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackgroundImagePosition, BackgroundImagePosition);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackgroundBlurStyle, BlurStyle);
};

struct BorderProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BorderRadius, BorderRadiusProperty);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BorderColor, BorderColorProperty);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BorderStyle, BorderStyleProperty);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        static const char* BORDER_STYLE[] = {
            "BorderStyle.Solid",
            "BorderStyle.Dashed",
            "BorderStyle.Dotted",
        };
        json->Put("borderStyle",
            BORDER_STYLE[static_cast<int>(
                propBorderStyle.value_or(BorderStyleProperty()).styleLeft.value_or(BorderStyle::SOLID))]);
        json->Put("borderColor",
            propBorderColor.value_or(BorderColorProperty()).leftColor.value_or(Color()).ColorToString().c_str());
        json->Put("borderRadius", propBorderRadius.value_or(BorderRadiusProperty())
                                      .radiusTopLeft.value_or(Dimension(0.0, DimensionUnit::VP)).ToString().c_str());
    }
};

struct TransformProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TransformScale, VectorF);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TransformCenter, DimensionOffset);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TransformTranslate, Vector3F);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TransformRotate, Vector4F);
};

struct DecorationProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlurRadius, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlurStyle, BlurStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FrontBlurRadius, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackShadow, Shadow);
};

struct RenderPositionProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Position, OffsetT<Dimension>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Offset, OffsetT<Dimension>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Anchor, OffsetT<Dimension>);
};

struct ClipProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ClipShape, ClipPathNG);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ClipEdge, bool);
};

struct GradientProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LinearGradient, NG::Gradient);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SweepGradient, NG::Gradient);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(RadialGradient, NG::Gradient);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_PROPERTY_H
