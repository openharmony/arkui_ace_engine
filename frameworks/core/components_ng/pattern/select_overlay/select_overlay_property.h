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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_PROPERTY_H

#include <cstdint>
#include <functional>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"

namespace OHOS::Ace::NG {

constexpr int32_t MENU_SHOW_ANIMATION_DURATION = 250;
constexpr int32_t MENU_HIDE_ANIMATION_DURATION = 200;
constexpr int32_t HANDLE_ANIMATION_DURATION = 150;

struct SelectHandleInfo {
    bool isShow = true;
    bool needLayout = false;
    // in Global coordinates.
    RectF paintRect;

    bool operator==(const SelectHandleInfo& info) const
    {
        return (isShow == info.isShow) && (paintRect == info.paintRect);
    }

    bool operator!=(const SelectHandleInfo& info) const
    {
        return !(*this == info);
    }

    static Dimension GetDefaultLineWidth();
};

struct SelectMenuInfo {
    bool menuDisable = false;
    bool menuIsShow = false;
    bool showCopy = true;
    bool showPaste = true;
    bool showCopyAll = true;
    bool showCut = true;
    std::optional<OffsetF> menuOffset;

    bool IsIconChanged(const SelectMenuInfo& info) const
    {
        return !((showCopy == info.showCopy) && (showPaste == info.showPaste) && (showCopyAll == info.showCopyAll) &&
                 (showCut == info.showCut));
    }
};

struct SelectMenuCallback {
    std::function<void()> onCopy;
    std::function<void()> onPaste;
    std::function<void()> onSelectAll;
    std::function<void()> onCut;
};

struct SelectOverlayInfo {
    bool isUsingMouse = false;
    bool isSingleHandle = false;
    // when handleReverse is true, The first one is on the right side of the second.
    bool handleReverse = false;
    // Used to determine the range of judgment that is parallel to the first and second handles.
    float singleLineHeight = 10.0f;
    SelectHandleInfo firstHandle;
    SelectHandleInfo secondHandle;
    HitTestMode hitTestMode = HitTestMode::HTMTRANSPARENT_SELF;

    // show area
    bool useFullScreen = true;
    RectF showArea;

    OffsetF rightClickOffset;

    // handle touch event
    std::function<void(const TouchEventInfo&)> onTouchDown;
    std::function<void(const TouchEventInfo&)> onTouchUp;
    std::function<void(const TouchEventInfo&)> onTouchMove;

    // handle move callback.
    std::function<void(bool isFirst)> onHandleMoveStart;
    std::function<void(const RectF&, bool isFirst)> onHandleMove;
    std::function<void(const RectF&, bool isFirst)> onHandleMoveDone;
    std::function<void(bool)> onHandleReverse;

    // menu info.
    SelectMenuInfo menuInfo;
    SelectMenuCallback menuCallback;

    std::vector<MenuOptionsParam> menuOptionItems;

    // force hide callback, which may be called when other textOverlay shows.
    std::function<void(bool)> onClose;

    OHOS::Ace::WeakPtr<FrameNode> callerFrameNode;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_PROPERTY_H
