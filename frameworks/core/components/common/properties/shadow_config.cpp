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

#include "core/components/common/properties/shadow_config.h"

namespace OHOS::Ace {
const Shadow ShadowConfig::NoneShadow = Shadow(0.0f, Offset(), Color(), ShadowStyle::None);

const Shadow ShadowConfig::DefaultShadowXS =
    Shadow(5.0f, Offset(0.0, 0.0), Color(0x32000000), ShadowStyle::OuterDefaultXS);
const Shadow ShadowConfig::DefaultShadowS =
    Shadow(100.0f, Offset(0.0, 0.0), Color(0x0b000000), ShadowStyle::OuterDefaultSM);
const Shadow ShadowConfig::DefaultShadowM =
    Shadow(185.0f, Offset(0.0, 60.0), Color(0x28000000), ShadowStyle::OuterDefaultMD);
const Shadow ShadowConfig::DefaultShadowL =
    Shadow(200.0f, Offset(0.0, 10.0), Color(0x26000000), ShadowStyle::OuterDefaultLG);
const Shadow ShadowConfig::FloatingShadowS =
    Shadow(230.0f, Offset(0.0, 50.0), Color(0x15000000), ShadowStyle::OuterFloatingSM);
const Shadow ShadowConfig::FloatingShadowM =
    Shadow(215.0f, Offset(0.0, 30.0), Color(0x31000000), ShadowStyle::OuterFloatingMD);

const Shadow ShadowConfig::DefaultShadowXSDark =
    Shadow(5.0f, Offset(0.0, 0.0), Color(0x4c000000), ShadowStyle::OuterDefaultXS);
const Shadow ShadowConfig::DefaultShadowSDark =
    Shadow(130.0f, Offset(0.0, 0.0), Color(0x2b000000), ShadowStyle::OuterDefaultSM);
const Shadow ShadowConfig::DefaultShadowMDark =
    Shadow(120.0f, Offset(0.0, 45.0), Color(0x60000000), ShadowStyle::OuterDefaultMD);
const Shadow ShadowConfig::DefaultShadowLDark =
    Shadow(200.0f, Offset(0.0, 60.0), Color(0x59000000), ShadowStyle::OuterDefaultLG);
const Shadow ShadowConfig::FloatingShadowSDark =
    Shadow(150.0f, Offset(0.0, 30.0), Color(0x3c000000), ShadowStyle::OuterFloatingSM);
const Shadow ShadowConfig::FloatingShadowMDark =
    Shadow(200.0f, Offset(0.0, 30.0), Color(0x38000000), ShadowStyle::OuterFloatingMD);

const Shadow& ShadowConfig::GetShadowConfig(int shadowLevel)
{
    switch (static_cast<ShadowStyle>(shadowLevel)) {
        case ShadowStyle::OuterDefaultXS:
            return DefaultShadowXS;
        case ShadowStyle::OuterDefaultSM:
            return DefaultShadowS;
        case ShadowStyle::OuterDefaultMD:
            return DefaultShadowM;
        case ShadowStyle::OuterDefaultLG:
            return DefaultShadowL;
        case ShadowStyle::OuterFloatingSM:
            return FloatingShadowS;
        case ShadowStyle::OuterFloatingMD:
            return FloatingShadowM;
        default: {
            return NoneShadow;
        }
    }
}
} // namespace OHOS::Ace
