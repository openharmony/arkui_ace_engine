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

    // start app from notificationbar
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_NOTIFICATIONBAR[] = "LAUNCHER_APP_LAUNCH_FROM_NOTIFICATIONBAR";

    // start app from lockscreen
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_NOTIFICATIONBAR_IN_LOCKSCREEN[] =
        "LAUNCHER_APP_LAUNCH_FROM_NOTIFICATIONBAR_IN_LOCKSCREEN";

    // start app from recent
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_RECENT[] = "LAUNCHER_APP_LAUNCH_FROM_RECENT";

    // start app from Card
    static constexpr char START_APP_ANI_FORM[] = "START_APP_ANI_FORM";

    // into home ani
    static constexpr char INTO_HOME_ANI[] = "INTO_HOME_ANI";

    // screenlock screen off ani
    static constexpr char SCREENLOCK_SCREEN_OFF_ANIM[] = "SCREENLOCK_SCREEN_OFF_ANIM";

    // password unlock ani
    static constexpr char PASSWORD_UNLOCK_ANI[] = "PASSWORD_UNLOCK_ANI";

    // facial fling unlock ani
    static constexpr char FACIAL_FLING_UNLOCK_ANI[] = "FACIAL_FLING_UNLOCK_ANI";

    // facial unlock ani
    static constexpr char FACIAL_UNLOCK_ANI[] = "FACIAL_UNLOCK_ANI";

    // fingerprint unlock ani
    static constexpr char FINGERPRINT_UNLOCK_ANI[] = "FINGERPRINT_UNLOCK_ANI";

    // charging dynamic ani
    static constexpr char META_BALLS_TURBO_CHARGING_ANIMATION[] = "META_BALLS_TURBO_CHARGING_ANIMATION";

    // app ablitity page switch
    static constexpr char ABILITY_OR_PAGE_SWITCH[] = "ABILITY_OR_PAGE_SWITCH";

    // app exit to home by geturing slide out
    static constexpr char LAUNCHER_APP_SWIPE_TO_HOME[] = "LAUNCHER_APP_SWIPE_TO_HOME";

    // app list fling
    static constexpr char APP_LIST_FLING[] = "APP_LIST_FLING";

    // app swiper fling
    static constexpr char APP_SWIPER_FLING[] = "APP_SWIPER_FLING";

    // app swiper scroll
    static constexpr char APP_SWIPER_SCROLL[] = "APP_SWIPER_SCROLL";

    // auto app swiper fling
    static constexpr char AUTO_APP_SWIPER_FLING[] = "AUTO_APP_SWIPER_FLING";

    // app tab switch
    static constexpr char APP_TAB_SWITCH[] = "APP_TAB_SWITCH";

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

    // PC exit recent
    static constexpr char PC_EXIT_RECENT[] = "PC_EXIT_RECENT";

    // PC shoutcut to app center
    static constexpr char PC_SHORTCUT_TO_APP_CENTER[] = "PC_SHORTCUT_TO_APP_CENTER";

    // PC shoutcut to app center on recent
    static constexpr char PC_SHORTCUT_TO_APP_CENTER_ON_RECENT[] = "PC_SHORTCUT_TO_APP_CENTER_ON_RECENT";

    // PC shoutcut exit app center
    static constexpr char PC_SHORTCUT_EXIT_APP_CENTER[] = "PC_SHORTCUT_EXIT_APP_CENTER";

    // A app jump to another app
    static constexpr char APP_TRANSITION_TO_OTHER_APP[] = "APP_TRANSITION_TO_OTHER_APP";

    // another app jamps back to A app
    static constexpr char APP_TRANSITION_FROM_OTHER_APP[] = "APP_TRANSITION_FROM_OTHER_APP";

    // mutitask scroll
    static constexpr char SNAP_RECENT_ANI[] = "SNAP_RECENT_ANI";

    // start app from dock
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_DOCK[] = "LAUNCHER_APP_LAUNCH_FROM_DOCK";

    // start app from misson
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_MISSON[] = "LAUNCHER_APP_LAUNCH_FROM_MISSON";

    // app exit from back to home
    static constexpr char LAUNCHER_APP_BACK_TO_HOME[] = "LAUNCHER_APP_BACK_TO_HOME";

    // app exit from multitasking
    static constexpr char EXIT_RECENT_2_HOME_ANI[] = "EXIT_RECENT_2_HOME_ANI";

    // PC window resize
    static constexpr char WINDOW_RECT_RESIZE[] = "WINDOW_RECT_RESIZE";

    // PC window move
    static constexpr char WINDOW_RECT_MOVE[] = "WINDOW_RECT_MOVE";

    // input method show
    static constexpr char SHOW_INPUT_METHOD_ANIMATION[] = "SHOW_INPUT_METHOD_ANIMATION";

    // input method hide
    static constexpr char HIDE_INPUT_METHOD_ANIMATION[] = "HIDE_INPUT_METHOD_ANIMATION";

    // screen rotation
    static constexpr char SCREEN_ROTATION_ANI[] = "SCREEN_ROTATION_ANI";

    // folder close
    static constexpr char CLOSE_FOLDER_ANI[] = "CLOSE_FOLDER_ANI";

    // launcher spring back scroll
    static constexpr char LAUNCHER_SPRINGBACK_SCROLL[] = "LAUNCHER_SPRINGBACK_SCROLL";

    // window title bar minimized
    static constexpr char WINDOW_TITLE_BAR_MINIMIZED[] = "WINDOW_TITLE_BAR_MINIMIZED";

    // window title bar closed
    static constexpr char APP_EXIT_FROM_WINDOW_TITLE_BAR_CLOSED[] = "APP_EXIT_FROM_WINDOW_TITLE_BAR_CLOSED";

    // PC start app from other
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_OTHER[] = "LAUNCHER_APP_LAUNCH_FROM_OTHER";

    // scroller animation
    static constexpr char SCROLLER_ANIMATION[] = "SCROLLER_ANIMATION";

    // pc title bar maximized
    static constexpr char WINDOW_TITLE_BAR_MAXIMIZED[] = "WINDOW_TITLE_BAR_MAXIMIZED";

    // pc title bar recover
    static constexpr char WINDOW_TITLE_BAR_RECOVER[] = "WINDOW_TITLE_BAR_RECOVER";

    // PC start app from transition
    static constexpr char LAUNCHER_APP_LAUNCH_FROM_TRANSITION[] = "LAUNCHER_APP_LAUNCH_FROM_TRANSITION";

    // navigation interactive animation
    static constexpr char ABILITY_OR_PAGE_SWITCH_INTERACTIVE[] = "ABILITY_OR_PAGE_SWITCH_INTERACTIVE";
};
} // namespace OHOS::Ace
#endif // ARKUI_PERF_SCENE_ID_H
