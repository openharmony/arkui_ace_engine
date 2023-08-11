/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef ARKUI_PERF_SCENE_ID_H
#define ARKUI_PERF_SCENE_ID_H

#include <string>

namespace OHOS::Ace {
class PerfConstants {
public:
    // start app from launcher icon sceneid
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_ICON[] = "LAUNCHER_APP_LAUNCH_FROM_ICON";

    // app ablitity page switch
    static constexpr char ABILITY_OR_PAGE_SWITCH[] = "ABILITY_OR_PAGE_SWITCH";

    // app exit to home by geturing slide out
    static constexpr char LAUNCHER_APP_SWIPE_TO_HOME[] = "LAUNCHER_APP_SWIPE_TO_HOME";

    // app list fling
    static constexpr char APP_LIST_FLING[] = "APP_LIST_FLING";
};
} // namespace OHOS::Ace
#endif // ARKUI_PERF_SCENE_ID_H
