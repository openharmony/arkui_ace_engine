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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_H

#include "core/components/text_clock/text_clock_controller.h"

namespace OHOS::Ace {
class TextClockModel {
public:
    static TextClockModel* GetInstance();
    virtual ~TextClockModel() = default;

    virtual RefPtr<TextClockController> Create() = 0;
    virtual void SetFormat(const std::string& format) = 0;
    virtual void SetHoursWest(const int32_t& hoursWest) = 0;
    virtual void SetOnDateChange(std::function<void(const std::string)>&& onChange) = 0;

private:
    static std::unique_ptr<TextClockModel> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_H
