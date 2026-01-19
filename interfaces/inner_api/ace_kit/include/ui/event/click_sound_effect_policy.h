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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_EVENT_CLICK_SOUND_EFFECT_POLICY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_EVENT_CLICK_SOUND_EFFECT_POLICY_H
#include "ui/base/ace_type.h"

namespace OHOS::Ace::Kit {

class ACE_EXPORT ClickSoundEffectPolicy : public AceType {
public:
    virtual int32_t InteractiveSoundEffects(int32_t type, int32_t index, int32_t abscissa, int32_t ordinate) = 0;
    virtual ~ClickSoundEffectPolicy() {}
};

void* GetClickSoundEffectPolicyInstance();
} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_EVENT_CLICK_SOUND_EFFECT_POLICY_H