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

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

struct SelectHandleInfo {
    RectF paintRect;

    bool operator==(const SelectHandleInfo& info) const
    {
        return paintRect == info.paintRect;
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

    // handle move callback.
    std::function<void(const RectF&, bool isFirst)> onHandleMove;
    std::function<void(const RectF&, bool isFirst)> onHandleMoveDone;
    std::function<void(bool)> onHandleReverse;

    // menu info.
    SelectMenuInfo menuInfo;
    SelectMenuCallback menuCallback;

    // force hide callback, which may be called when other textOverlay shows.
    std::function<void()> onClose;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_PROPERTY_H
