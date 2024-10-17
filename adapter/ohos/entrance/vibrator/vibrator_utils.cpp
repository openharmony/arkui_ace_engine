/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/common/vibrator/vibrator_utils.h"
#include <vector>

#include "vibrator_agent.h"

using namespace OHOS::Sensors;

namespace OHOS::Ace::NG {
namespace {
    static std::vector<const char*> effectIdNames = {
        VIBRATOR_TYPE_SLIDE,
        VIBRATOR_TYPE_SLIDE_LIGHT,
        VIBRATOR_TYPE_CHARGING,
        VIBRATOR_TYPE_CLOCK_TIMER
    };

    const char* VIBRATOR_TYPE_INVALID = "vibrator.type.invalid";
    const char* GetVibratorType(const std::string& vibratorType)
    {
        if (vibratorType == "longPress.light") {
            return VIBRATOR_TYPE_LONG_PRESS_LIGHT;
        } else if (vibratorType == "slide") {
            return VIBRATOR_TYPE_SLIDE;
        } else if (vibratorType == "slide.light") {
            return VIBRATOR_TYPE_SLIDE_LIGHT;
        }
        return VIBRATOR_TYPE_INVALID;
    }
};

const char* VibratorUtils::supportedEffectId = nullptr;

const char* VibratorUtils::GetFirstSupportedId()
{
    bool state = false;
    for (auto item : effectIdNames) {
        Sensors::IsSupportEffect(item, &state);
        if (state) {
            return item;
        }
    }
    return nullptr;
}

void VibratorUtils::StartVibraFeedback()
{
#ifdef INDEXER_SUPPORT_VIBRATOR
    if (supportedEffectId == nullptr) {
        supportedEffectId = VibratorUtils::GetFirstSupportedId();
    }
    if (supportedEffectId != nullptr) {
        Sensors::StartVibrator(supportedEffectId);
    }
#endif
}

void VibratorUtils::StartVibraFeedback(const std::string& vibratorType)
{
    const char* realVibratorType = GetVibratorType(vibratorType);
    if (strcmp(realVibratorType, VIBRATOR_TYPE_INVALID) == 0) {
        return;
    }
    bool state = false;
    Sensors::IsSupportEffect(realVibratorType, &state);
    if (state) {
        Sensors::StartVibrator(realVibratorType);
    }
}
} // namespace OHOS::Ace::NG