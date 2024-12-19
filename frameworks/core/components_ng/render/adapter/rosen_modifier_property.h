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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_MODIFIER_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_MODIFIER_PROPERTY_H

#include "render_service_client/core/modifier/rs_property_modifier.h"
#include "render_service_client/core/ui/rs_node.h"

namespace OHOS::Ace::NG {
template<typename T>
bool CreateOrSetModifierValue(std::shared_ptr<Rosen::RSAnimatableProperty<T>>& property, const T& value);

void AddOrChangeScaleModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSScaleModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value);

void AddOrChangeSkewModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSSkewModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value);

void AddOrChangeTranslateZModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSTranslateZModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float value);

void AddOrChangePerspectiveModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSPerspModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value);

void AddOrChangeTranslateModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSTranslateModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value);

void AddOrChangeQuaternionModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSQuaternionModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Quaternion>>& property, const Rosen::Quaternion& value);

void AddOrChangePivotModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSPivotModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>>& property, const Rosen::Vector2f& value);

struct TransformMatrixModifier {
    std::shared_ptr<Rosen::RSPerspModifier> perspectiveXY;
    std::shared_ptr<Rosen::RSTranslateModifier> translateXY;
    std::shared_ptr<Rosen::RSTranslateZModifier> translateZ;
    std::shared_ptr<Rosen::RSScaleModifier> scaleXY;
    std::shared_ptr<Rosen::RSSkewModifier> skewXY;
    std::shared_ptr<Rosen::RSPivotModifier> pivotXY;
    std::shared_ptr<Rosen::RSQuaternionModifier> quaternion;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> perspectiveXYValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> translateXYValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> translateZValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> scaleXYValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> skewXYValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> pivotXYValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Quaternion>> quaternionValue;
};

struct SharedTransitionModifier {
    std::shared_ptr<Rosen::RSTranslateModifier> translateXY;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> translateXYValue;
};

struct WindowBlurModifier {
    std::shared_ptr<Rosen::RSBehindWindowFilterRadiusModifier> radius;
    std::shared_ptr<Rosen::RSBehindWindowFilterSaturationModifier> saturation;
    std::shared_ptr<Rosen::RSBehindWindowFilterBrightnessModifier> brightness;
    std::shared_ptr<Rosen::RSBehindWindowFilterMaskColorModifier> maskColor;

    std::shared_ptr<Rosen::RSAnimatableProperty<float>> radiusValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> saturationValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<float>> brightnessValue;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::RSColor>> maskColorValue;

    static void AddOrChangeRadiusModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterRadiusModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float& value);
    static void AddOrChangeSaturationModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterSaturationModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float& value);
    static void AddOrChangeBrightnessModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterBrightnessModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<float>>& property, const float& value);
    static void AddOrChangeMaskColorModifier(std::shared_ptr<Rosen::RSNode>& rsNode,
    std::shared_ptr<Rosen::RSBehindWindowFilterMaskColorModifier>& modifier,
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::RSColor>>& property, const Rosen::RSColor& value);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_MODIFIER_PROPERTY_H