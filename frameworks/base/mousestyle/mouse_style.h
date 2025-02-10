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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_MOUSESTYLE_MOUSE_STYLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_MOUSESTYLE_MOUSE_STYLE_MANAGER_H

#include <list>

#include "base/memory/ace_type.h"
#include "base/image/pixel_map.h"

namespace OHOS::Ace {

enum class MouseFormat : int32_t {
    DEFAULT = 0,        // Default mouse style
    EAST = 1,           // Eastwards arrow
    WEST = 2,           // Westwards arrow
    SOUTH = 3,          // Southwards arrow
    NORTH = 4,          // Northwards arrow
    WEST_EAST = 5,      // Drag left-right mouse style
    NORTH_SOUTH = 6,    // Drag up-down mouse style
    NORTH_EAST = 7,
    NORTH_WEST = 8,
    SOUTH_EAST = 9,
    SOUTH_WEST = 10,
    NORTH_EAST_SOUTH_WEST = 11,
    NORTH_WEST_SOUTH_EAST = 12,
    CROSS = 13,
    CURSOR_COPY = 14,
    CURSOR_FORBID = 15,
    COLOR_SUCKER = 16,
    HAND_GRABBING = 17,
    HAND_OPEN = 18,
    HAND_POINTING = 19, // Hyperlink mouse style
    HELP = 20,
    CURSOR_MOVE = 21,
    RESIZE_LEFT_RIGHT = 22,
    RESIZE_UP_DOWN = 23,
    SCREENSHOT_CHOOSE = 24,
    SCREENSHOT_CURSOR = 25,
    TEXT_CURSOR = 26,   // Text editing mouse style
    ZOOM_IN = 27,
    ZOOM_OUT = 28,
    MIDDLE_BTN_EAST = 29,
    MIDDLE_BTN_WEST = 30,
    MIDDLE_BTN_SOUTH = 31,
    MIDDLE_BTN_NORTH = 32,
    MIDDLE_BTN_NORTH_SOUTH = 33,
    MIDDLE_BTN_NORTH_EAST = 34,
    MIDDLE_BTN_NORTH_WEST = 35,
    MIDDLE_BTN_SOUTH_EAST = 36,
    MIDDLE_BTN_SOUTH_WEST = 37,
    MIDDLE_BTN_NORTH_SOUTH_WEST_EAST = 38,
    HORIZONTAL_TEXT_CURSOR = 39,
    CURSOR_CROSS = 40,
    CURSOR_CIRCLE = 41,
    LOADING = 42,
    RUNNING = 43,
    CURSOR_NONE = 46,
    CONTEXT_MENU = 47,
    ALIAS = 48,
};

class ACE_EXPORT MouseStyle : public AceType {
    DECLARE_ACE_TYPE(MouseStyle, AceType)

public:
    static RefPtr<MouseStyle> CreateMouseStyle();

    virtual bool SetPointerStyle(int32_t windowId, MouseFormat pointerStyle) const = 0;
    virtual int32_t GetPointerStyle(int32_t windowId, int32_t& pointerStyle) const = 0;
    virtual void SetMouseIcon(
        int32_t windowId, MouseFormat pointerStyle, std::shared_ptr<Media::PixelMap> pixelMap) const {};
    virtual void SetCustomCursor(
        int32_t windowId, int32_t focusX, int32_t focusY, std::shared_ptr<Media::PixelMap> pixelMap) const {};
    virtual void SetPointerVisible(MouseFormat pointerStyle) const {};
};

enum class MouseStyleChangeReason {
    INNER_SET_MOUSESTYLE = 0, // inner frameNode call mouseStyle change
    USER_SET_MOUSESTYLE = 1, // user call setCursor change mouseStyle
    WINDOW_DESTROY_RESET_MOUSESTYLE = 2, // window is destroyed, reset mouse style
};

struct MouseStyleChangeLog {
    int32_t windowId; // the id of window which change mouseStyle
    int32_t changeNodeId; // the id of node which change mouseStyle
    MouseFormat beforeMouseStyle; // before this change, the mouseFormat of mouseStyle
    MouseFormat afterMouseStyle; // after this change, the mouseFormat of mouseStyle
    MouseStyleChangeReason reason; // the reason of this mouseStyle change
};

class ACE_EXPORT MouseStyleManager : public AceType {
    DECLARE_ACE_TYPE(MouseStyleManager, AceType)

public:
    MouseStyleManager() = default;

    bool SetMouseFormat(int32_t windowId, int32_t nodeId, MouseFormat mouseFormat,
        bool isByPass, MouseStyleChangeReason reason);
    
    void VsyncMouseFormat();
    void DumpMouseStyleChangeLog();

    bool SetMouseStyleHoldNode(int32_t id)
    {
        if (!mouseStyleNodeId_.has_value()) {
            mouseStyleNodeId_ = id;
            return true;
        } else {
            return false;
        }
    }

    bool FreeMouseStyleHoldNode(int32_t id)
    {
        if (mouseStyleNodeId_.has_value() && mouseStyleNodeId_.value() == id) {
            mouseStyleNodeId_.reset();
            return true;
        } else {
            return false;
        }
    }

    bool FreeMouseStyleHoldNode()
    {
        CHECK_NULL_RETURN(mouseStyleNodeId_.has_value(), false);
        mouseStyleNodeId_.reset();
        return true;
    }

    void SetUserSetCursor(bool userSetCursor)
    {
        userSetCursor_ = userSetCursor;
    }

private:
    bool userSetCursor_ = false;
    std::optional<int32_t> mouseStyleNodeId_;
    MouseFormat lastVsyncMouseFormat_ = MouseFormat::DEFAULT;
    MouseFormat mouseFormat_ = MouseFormat::DEFAULT;
    std::list<MouseStyleChangeLog> vsyncMouseStyleChanges_;
    std::list<MouseStyleChangeLog> mouseStyleChangeLogs_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_MOUSESTYLE_MOUSE_STYLE_MANAGER_H