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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_MARQUEE_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_MARQUEE_OPTION_H

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {

struct MarqueeOption {
    bool start = true;
    double step = 4.0;
    int32_t loop = -1;
    MarqueeDirection direction = MarqueeDirection::DEFAULT;
    int32_t delay = 0;
    bool fadeout = false;
    MarqueeStartPolicy startPolicy = MarqueeStartPolicy::DEFAULT;

    bool operator==(const MarqueeOption& other) const
    {
        return start == other.start && NearEqual(step, other.step) && loop == other.loop &&
               direction == other.direction && delay == other.delay && fadeout == other.fadeout &&
               startPolicy == other.startPolicy;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_MARQUEE_OPTION_H
