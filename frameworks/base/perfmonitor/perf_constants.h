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

    // volume bar show
    static constexpr char VOLUME_BAR_SHOW[] = "VOLUME_BAR_SHOW";

    // PC app center gesture operation
    static constexpr char PC_APP_CENTER_GESTURE_OPERATION[] = "PC_APP_CENTER_GESTURE_OPERATION";

    // PC gesture to recent
    static constexpr char PC_GESTURE_TO_RECENT[] = "PC_GESTURE_TO_RECENT";

    // PC shortcut show desktop
    static constexpr char PC_SHORTCUT_SHOW_DESKTOP[] = "PC_SHORTCUT_SHOW_DESKTOP";

    // PC shortcut restore desktop
    static constexpr char PC_SHORTCUT_RESTORE_DESKTOP[] = "PC_SHORTCUT_RESTORE_DESKTOP";

    // PC show desktop gesture operation
    static constexpr char PC_SHOW_DESKTOP_GESTURE_OPERATION[] = "PC_SHOW_DESKTOP_GESTURE_OPERATION";

    // PC alt + tab to recent
    static constexpr char PC_ALT_TAB_TO_RECENT[] = "PC_ALT_TAB_TO_RECENT";

    // PC shortcut to recent
    static constexpr char PC_SHORTCUT_TO_RECENT[] = "PC_SHORTCUT_TO_RECENT";

    // PC esc exit recent
    static constexpr char PC_ESC_EXIT_RECENT[] = "PC_ESC_EXIT_RECENT";

    // PC shoutcut to app center
    static constexpr char PC_SHORTCUT_TO_APP_CENTER[] = "PC_SHORTCUT_TO_APP_CENTER";

    // PC shoutcut exit app center
    static constexpr char PC_SHORTCUT_EXIT_APP_CENTER[] = "PC_SHORTCUT_EXIT_APP_CENTER";
};
} // namespace OHOS::Ace
#endif // ARKUI_PERF_SCENE_ID_H
