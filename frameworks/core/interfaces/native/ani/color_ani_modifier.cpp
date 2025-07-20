/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "color_ani_modifier.h"
#include "ui/properties/color.h"

namespace OHOS::Ace::NG {
bool ParseColorString(std::string src, uint32_t& color)
{
    Color colorObj;
    if (!Color::ParseColorString(src, colorObj)) {
        return false;
    }
    color = colorObj.GetValue();
    return true;
}

const ArkUIColorModifier* GetColorAniModifier()
{
    static const ArkUIColorModifier impl = {
        .parseColorString = OHOS::Ace::NG::ParseColorString,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
