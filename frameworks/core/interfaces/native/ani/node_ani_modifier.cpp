/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common_ani_modifier.h"
#include "content_slot_ani_modifier.h"
#include "image_ani_modifier.h"
#include "web_ani_modifier.h"

extern "C" {
const ArkUIAniModifiers* GetArkUIAniModifiers()
{
    static const ArkUIAniModifiers impl = {
        .version = ARKUI_ANI_API_VERSION,
        .getImageAniModifier = OHOS::Ace::NG::GetImageAniModifier,
        .getWebAniModifier = OHOS::Ace::NG::GetWebAniModifier,
        .getCommonAniModifier = OHOS::Ace::NG::GetCommonAniModifier,
        .getContentSlotAniModifier = OHOS::Ace::NG::GetContentSlotAniModifier,
        .getArkUIAniDrawModifier = OHOS::Ace::NG::GetArkUIAniDrawModifier,
    };
    return &impl;
}
}