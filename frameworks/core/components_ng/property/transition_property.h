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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_TRANSITION_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_TRANSITION_PROPERTY_H

#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "core/animation/animation_pub.h"
#include "core/components_ng/property/property.h"


namespace OHOS::Ace::NG {

struct TranslateOptions {
    Dimension x;
    Dimension y;
    Dimension z;
    bool operator==(const TranslateOptions& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
    std::string ToString() const
    {
        return "translate:[" + x.ToString() + ", " + y.ToString() + ", " + z.ToString() + "]";
    }
};
struct ScaleOptions {
    float xScale = 1.0f;
    float yScale = 1.0f;
    float zScale = 1.0f;
    Dimension centerX;
    Dimension centerY;
    ScaleOptions(float xScale, float yScale, float zScale, const Dimension& centerX, const Dimension& centerY)
        : xScale(xScale), yScale(yScale), zScale(zScale), centerX(centerX), centerY(centerY)
    {}
    ScaleOptions() = default;
    bool operator==(const ScaleOptions& other) const
    {
        return NearEqual(xScale, other.xScale) && NearEqual(yScale, other.yScale) &&
               NearEqual(zScale, other.zScale) && NearEqual(centerX, other.centerX) &&
               NearEqual(centerY, other.centerY);
    }
    std::string ToString() const
    {
        return "scale:[" + std::to_string(xScale) + "," + std::to_string(yScale) + "," + std::to_string(zScale) +
               "," + centerX.ToString() + "," + centerY.ToString() + "]";
    }
};
struct RotateOptions {
    float xDirection = 0.0f;
    float yDirection = 0.0f;
    float zDirection = 0.0f;
    // angle in degree unit
    float angle = 0.0f;
    Dimension centerX;
    Dimension centerY;
    RotateOptions(float xDirection, float yDirection, float zDirection, float angle, const Dimension& centerX,
        const Dimension& centerY)
        : xDirection(xDirection), yDirection(yDirection), zDirection(zDirection), angle(angle), centerX(centerX),
          centerY(centerY)
    {}
    RotateOptions() = default;
    bool operator==(const RotateOptions& other) const
    {
        return NearEqual(angle, other.angle) && NearEqual(xDirection, other.xDirection) &&
               NearEqual(yDirection, other.yDirection) && NearEqual(zDirection, other.zDirection) &&
               NearEqual(centerX, other.centerX) && NearEqual(centerY, other.centerY);
    }
    std::string ToString() const
    {
        return "rotate:[" + std::to_string(xDirection) + "," + std::to_string(yDirection) + "," +
               std::to_string(zDirection) + "," + centerX.ToString() + "," + centerY.ToString() +
               ", angle:" + std::to_string(angle) + "]";
    }
};
struct TransitionOptions {
    TransitionType Type = TransitionType::ALL;
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Opacity, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Translate, TranslateOptions);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Scale, ScaleOptions);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Rotate, RotateOptions);
    static TransitionOptions GetDefaultTransition(TransitionType type)
    {
        TransitionOptions options;
        options.Type = type;
        options.UpdateOpacity(0.0f);
        return options;
    }
    bool operator==(const TransitionOptions& other) const
    {
        return NearEqual(Type, other.Type) && NearEqual(propOpacity, other.propOpacity) &&
               NearEqual(propTranslate, other.propTranslate) && NearEqual(propScale, other.propScale) &&
               NearEqual(propRotate, other.propRotate);
    }
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "type:"
           << (Type == TransitionType::ALL ? "all" : (Type == TransitionType::APPEARING ? "appear" : "disappear"))
           << ", opacity:" << (HasOpacity() ? std::to_string(GetOpacityValue()) : "none") << ", "
           << (HasTranslate() ? GetTranslate()->ToString() : "translate: none") << ", "
           << (HasScale() ? GetScale()->ToString() : "scale: none") << ", "
           << (HasRotate() ? GetRotate()->ToString() : "rotate: none");
        return ss.str();
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_TRANSITION_PROPERTY_H