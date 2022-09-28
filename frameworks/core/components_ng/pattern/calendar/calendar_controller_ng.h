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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_CONTROLLER_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_CONTROLLER_NG_H

#include "base/memory/ace_type.h"
#include "core/components/swiper/swiper_controller.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CalendarControllerNg : public AceType {
    DECLARE_ACE_TYPE(CalendarControllerNg, AceType);

public:
    CalendarControllerNg() = default;
    ~CalendarControllerNg() override = default;

    void SetSwiperController(const RefPtr<SwiperController>& swiperController)
    {
        swiperController_ = swiperController;
    }

private:
    RefPtr<SwiperController> swiperController_;

    ACE_DISALLOW_COPY_AND_MOVE(CalendarControllerNg);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_CALENDAR_CONTROLLER_NG_H
