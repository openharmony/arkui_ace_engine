/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/shadow.h"

#include "core/animation/evaluator.h"
#include "core/common/container.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace {

Shadow Shadow::Blend(const Shadow& to, const Shadow& from, float progress)
{
    auto offset = from.offset_ + (to.offset_ - from.offset_) * progress;
    auto blurRadius = from.blurRadius_ + (to.blurRadius_ - from.blurRadius_) * progress;
    auto spreadRadius = from.spreadRadius_ + (to.spreadRadius_ - from.spreadRadius_) * progress;
    LinearEvaluator<Color> evaluator;
    auto color = evaluator.Evaluate(from.color_, to.color_, progress);
    return Shadow(blurRadius, spreadRadius, offset, color);
}

void Shadow::RegisterShadowResourceObj(Shadow& shadow,
    RefPtr<ResourceObject>& radiusObj, RefPtr<ResourceObject>& colorObj,
    RefPtr<ResourceObject>& offsetXObj, RefPtr<ResourceObject>& offsetYObj)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    if (radiusObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
            double radius = 0.0;
            ResourceParseUtils::ParseResDouble(resObj, radius);
            if (LessNotEqual(radius, 0.0)) {
                radius = 0.0;
            }
            shadow.SetBlurRadius(radius);
        };
        shadow.AddResource("shadow.radius", radiusObj, std::move(updateFunc));
    }
    if (colorObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& colorResObj, Shadow& shadow) {
            Color colorValue;
            ResourceParseUtils::ParseResColor(colorResObj, colorValue);
            shadow.SetColor(colorValue);
        };
        shadow.AddResource("shadow.colorValue", colorObj, std::move(updateFunc));
    }
    if (offsetXObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
            CalcDimension offsetX;
            if (ResourceParseUtils::ParseResResource(resObj, offsetX)) {
                shadow.SetOffsetX(offsetX.Value());
            }
        };
        shadow.AddResource("shadow.offsetX", offsetXObj, std::move(updateFunc));
    }
    if (offsetYObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
            CalcDimension offsetY;
            if (ResourceParseUtils::ParseResResource(resObj, offsetY)) {
                shadow.SetOffsetY(offsetY.Value());
            }
        };
        shadow.AddResource("shadow.offsetY", offsetYObj, std::move(updateFunc));
    }
}

Shadow Shadow::CreateShadow(ShadowStyle style)
{
    auto colorMode = Container::CurrentColorMode();
    if (colorMode == ColorMode::DARK) {
        switch (style) {
            case ShadowStyle::OuterDefaultXS:
                return ShadowConfig::DefaultShadowXSDark;
            case ShadowStyle::OuterDefaultSM:
                return ShadowConfig::DefaultShadowSDark;
            case ShadowStyle::OuterDefaultMD:
                return ShadowConfig::DefaultShadowMDark;
            case ShadowStyle::OuterDefaultLG:
                return ShadowConfig::DefaultShadowLDark;
            case ShadowStyle::OuterFloatingSM:
                return ShadowConfig::FloatingShadowSDark;
            case ShadowStyle::OuterFloatingMD:
                return ShadowConfig::FloatingShadowMDark;
            default:
                return ShadowConfig::NoneShadow;
        }
    }
    switch (style) {
        case ShadowStyle::OuterDefaultXS:
            return ShadowConfig::DefaultShadowXS;
        case ShadowStyle::OuterDefaultSM:
            return ShadowConfig::DefaultShadowS;
        case ShadowStyle::OuterDefaultMD:
            return ShadowConfig::DefaultShadowM;
        case ShadowStyle::OuterDefaultLG:
            return ShadowConfig::DefaultShadowL;
        case ShadowStyle::OuterFloatingSM:
            return ShadowConfig::FloatingShadowS;
        case ShadowStyle::OuterFloatingMD:
            return ShadowConfig::FloatingShadowM;
        default:
            return ShadowConfig::NoneShadow;
    }
    return ShadowConfig::NoneShadow;
}
} // namespace OHOS::Ace