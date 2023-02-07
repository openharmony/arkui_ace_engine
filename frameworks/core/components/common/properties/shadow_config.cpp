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

const Shadow ShadowConfig::DefaultShadowXS = Shadow(4.0f, Offset(0.0, 0.0), Color(0x26000000));
const Shadow ShadowConfig::DefaultShadowS = Shadow(20.0f, Offset(0.0, 0.0), Color(0x14000000));
const Shadow ShadowConfig::DefaultShadowM = Shadow(50.0f, Offset(0.0, 10.0), Color(0x26000000));
const Shadow ShadowConfig::DefaultShadowL = Shadow(50.0f, Offset(0.0, 10.0), Color(0x4D000000));
const Shadow ShadowConfig::FloatingShadowS = Shadow(55.0f, Offset(0.0, 10.0), Color(0x40000000));
const Shadow ShadowConfig::FloatingShadowM = Shadow(70.0f, Offset(0.0, 10.0), Color(0x73000000));

const Shadow ShadowConfig::DefaultShadowXSDark = Shadow(4.0f, Offset(0.0, 0.0), Color(0x4d000000));
const Shadow ShadowConfig::DefaultShadowSDark = Shadow(20.0f, Offset(0.0, 0.0), Color(0x33000000));
const Shadow ShadowConfig::DefaultShadowMDark = Shadow(50.0f, Offset(0.0, 10.0), Color(0x80000000));
const Shadow ShadowConfig::DefaultShadowLDark = Shadow(50.0f, Offset(0.0, 10.0), Color(0xcc000000));
const Shadow ShadowConfig::FloatingShadowSDark = Shadow(55.0f, Offset(0.0, 10.0), Color(0x4d000000));
const Shadow ShadowConfig::FloatingShadowMDark = Shadow(70.0f, Offset(0.0, 10.0), Color(0x80000000));
} // namespace OHOS::Ace
