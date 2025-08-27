/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_RESOURCE_INTERNAL_RESOURCE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_RESOURCE_INTERNAL_RESOURCE_H

#include <cstddef>
#include <cstdint>

#include "base/utils/singleton.h"

namespace OHOS::Ace {

class InternalResource final : public Singleton<InternalResource> {
    DECLARE_SINGLETON(InternalResource);

public:
    enum class ResourceId : uint32_t {
        NO_ID = 0,
        SELECT_ARROW_NORMAL_PNG,
        SELECT_ARROW_DISABLED_PNG,
        INDEXER_ARROW_PNG,
        FA_CLOCK_WIDGET_HOUR,
        FA_CLOCK_WIDGET_MINUTE,
        FA_CLOCK_WIDGET_SECOND,
        FA_BLACK_CLOCK_WIDGET_HOUR,
        FA_BLACK_CLOCK_WIDGET_MINUTE,
        FA_BLACK_CLOCK_WIDGET_SECOND,
        CONTAINER_MODAL_WINDOW_SPLIT_LEFT,
        CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE,
        CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE,
        CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE,
        CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER,
        CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT,

        // 10000 - 20000 is reserved for SVG resource.
        SVG_START = 10000,
        CORRECT_SVG,
        WRONG_SVG,
        SEARCH_SVG,
        CLOSE_SVG,
        PLAY_SVG,
        PAUSE_SVG,
        FULLSCREEN_SVG,
        QUIT_FULLSCREEN_SVG,
        UP_ARROW_SVG,
        WATCH_UP_ARROW_SVG,
        DOWN_ARROW_SVG,
        WATCH_DOWN_ARROW_SVG,
        SHOW_PASSWORD_SVG,
        HIDE_PASSWORD_SVG,
        SEMI_MODAL_BAR_MIDDLE_SVG,
        SEMI_MODAL_BAR_DOWN_SVG,
        LEFT_ARROW_SVG,
        RIGHT_ARROW_SVG,
        STEPPER_BACK_ARROW,
        STEPPER_NEXT_ARROW,
        PIECE_DELETE_SVG,
        RATE_STAR_BIG_OFF_SVG,
        RATE_STAR_BIG_ON_SVG,
        RATE_STAR_SMALL_OFF_SVG,
        RATE_STAR_SMALL_ON_SVG,
        TV_RATE_STAR_BIG_OFF_SVG,
        TV_RATE_STAR_BIG_ON_SVG,
        TV_RATE_STAR_SMALL_OFF_SVG,
        TV_RATE_STAR_SMALL_ON_SVG,
        TITLEBAR_BACK,
        IC_BACK,
        IC_MORE,
        IC_MORE_DARK,
        IC_MORE_TRANSPARENT,
        IC_WINDOW_MENU_FULLSCREEN,
        IC_WINDOW_MENU_MAXIMIZE,
        IC_WINDOW_MENU_OK,
        IC_WINDOW_MENU_SCREEN_L,
        IC_WINDOW_MENU_SCREEN_N,
        TRANSLATE_C2E_SVG,
        SHARE_SVG,
        SIDE_BAR,
        SPINNER,
        INPUT_SEARCH_SVG,
        APP_BAR_BACK_SVG,
        APP_BAR_FA_SVG,
        APP_BAR_MENU_SVG,
        APP_BAR_CLOSE_SVG,
        MENU_OK_SVG,
        SPINNER_DISABLE,
        LOCATION_BUTTON_FILLED_SVG,
        LOCATION_BUTTON_LINE_SVG,
        PASTE_BUTTON_LINE_SVG,
        SAVE_BUTTON_FILLED_SVG,
        SAVE_BUTTON_LINE_SVG,
        SAVE_BUTTON_PICTURE_SVG,
        IC_PUBLIC_ARROW_LEFT_SVG,
        IC_PUBLIC_ARROW_RIGHT_SVG,
        IC_PUBLIC_ARROW_UP_SVG,
        IC_PUBLIC_ARROW_DOWN_SVG,
        IC_PUBLIC_DOUBLE_ARROW_LEFT_SVG,
        IC_PUBLIC_DOUBLE_ARROW_RIGHT_SVG,
        IC_CUT_SVG,
        IC_COPY_SVG,
        IC_PASTE_SVG,
        IC_SELECT_ALL_SVG,
        IC_SHARE_SVG,
        IC_TRANSLATE_SVG,
        IC_SEARCH_SVG,
        IC_AI_WRITE_SVG,
        IC_BOTTOMSHEET_CLOSE_SVG,
        IC_CANCEL_SVG,
        RADIO_TICK_SVG,
        RADIO_DOT_SVG,
        IC_TAKEPHOTO_SVG,
        APP_LOCK_SVG,
        IC_TIME_LIMIT_SVG,
        CONTAINER_MODAL_WINDOW_CLOSE,
        CONTAINER_MODAL_WINDOW_MAXIMIZE,
        CONTAINER_MODAL_WINDOW_MINIMIZE,
        CONTAINER_MODAL_WINDOW_RECOVER,
        IC_PERSON_FILL_SVG,
        IC_LINK_SVG,
        IC_LOACTION_SVG,
        SVG_END = 20000,

        // 20001 - 30000 is reserved for i18n resource.
        I18N_START = 20001,
        INDEXLETTER_BAR_JSON,
        ERRORINFO_JSON,
        ENTRY_JSON,
        I18N_END = 30000,
    };

    const uint8_t* GetResource(const ResourceId id, size_t& size) const;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_RESOURCE_INTERNAL_RESOURCE_H
