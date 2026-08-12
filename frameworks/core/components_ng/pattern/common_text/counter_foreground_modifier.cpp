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

#include "core/components_ng/pattern/common_text/counter_foreground_modifier.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
namespace {
}

CounterForegroundModifier::CounterForegroundModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern)
    : pattern_(pattern)
{
    innerBorderWidth_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    innerBorderColor_ = AceType::MakeRefPtr<PropertyColor>(Color());
    AttachProperty(innerBorderWidth_);
    AttachProperty(innerBorderColor_);
}

std::vector<RSPoint> CounterForegroundModifier::MakeRRadius(
    const BorderRadiusProperty& border, float borderWidth) const
{
    std::vector<RSPoint> rectRadii;
    rectRadii.resize(RSRoundRect::CORNER_NUMBER);
    auto topLeft = static_cast<float>(border.radiusTopLeft.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::TOP_LEFT_POS] = RSPoint(topLeft, topLeft);
    auto topRight = static_cast<float>(border.radiusTopRight.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::TOP_RIGHT_POS] = RSPoint(topRight, topRight);
    auto bottomRight =
        static_cast<float>(border.radiusBottomRight.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::BOTTOM_RIGHT_POS] = RSPoint(bottomRight, bottomRight);
    auto bottomLeft = static_cast<float>(border.radiusBottomLeft.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::BOTTOM_LEFT_POS] = RSPoint(bottomLeft, bottomLeft);
    return rectRadii;
}

} // namespace OHOS::Ace::NG
