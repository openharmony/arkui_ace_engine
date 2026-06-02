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
#include "core/components_ng/property/border_property.h"

namespace OHOS::Ace::NG {
void BorderRadiusProperty::SetRadius(const Dimension& borderRadius)
{
    radiusTopLeft = borderRadius;
    radiusTopRight = borderRadius;
    radiusBottomRight = borderRadius;
    radiusBottomLeft = borderRadius;
}

bool BorderRadiusProperty::operator==(const BorderRadiusProperty& other) const
{
    return radiusTopLeft == other.radiusTopLeft &&
           radiusTopRight == other.radiusTopRight &&
           radiusBottomRight == other.radiusBottomRight &&
           radiusBottomLeft == other.radiusBottomLeft;
}

void BorderWidthProperty::SetBorderWidth(const Dimension& width)
{
    leftDimen = width;
    rightDimen = width;
    topDimen = width;
    bottomDimen = width;
}

bool BorderWidthProperty::operator==(const BorderWidthProperty& other) const
{
    return leftDimen == other.leftDimen &&
           rightDimen == other.rightDimen &&
           topDimen == other.topDimen &&
           bottomDimen == other.bottomDimen;
}
} // namespace OHOS::Ace::NG
