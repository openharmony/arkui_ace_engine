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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_OVERLAY_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_OVERLAY_CALLBACK_H

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/gesture_info.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/event/ace_events.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

struct TouchPointInfo {
    std::optional<PointF> point;
    int32_t id = -1;
    Offset offset;

    void Reset()
    {
        point.reset();
        id = -1;
        offset.Reset();
    }

    operator bool() const
    {
        return point.has_value();
    }

    bool IsAwayFromPoint(const TouchEvent& point)
    {
        CHECK_NULL_RETURN(id == point.id, false);
        auto deltaOffset = point.GetOffset() - offset;
        auto deltaDistance = deltaOffset.GetDistance();
        return GreatNotEqual(deltaDistance, Dimension(5.0f, DimensionUnit::VP).ConvertToPx());
    }
};

struct OverlayInfo : public virtual AceType {
    DECLARE_ACE_TYPE(OverlayInfo, AceType);

public:
    bool isSingleHandle = false;
    bool isShowMenu = false;
    bool isHiddenHandle = false;

    bool CanBackPressed()
    {
        return isSingleHandle && !isShowMenu && isHiddenHandle;
    }
};

class ACE_EXPORT SelectOverlayCallback : public virtual AceType {
    DECLARE_ACE_TYPE(SelectOverlayCallback, AceType);

public:
    SelectOverlayCallback() = default;
    ~SelectOverlayCallback() override = default;
    virtual void OnAfterSelectOverlayShow(bool isCreate) {}
    virtual void OnMenuItemAction(OptionMenuActionId id, OptionMenuType type) {}
    virtual void OnMenuItemAction(OptionMenuActionId id, OptionMenuType type, const std::string& labelInfo) {}

    virtual void OnOverlayTouchDown(const TouchEventInfo& event) {}
    virtual void OnOverlayTouchUp(const TouchEventInfo& event) {}
    virtual void OnOverlayTouchMove(const TouchEventInfo& event) {}
    virtual void OnOverlayClick(const GestureEvent& event, bool isClickCaret) {}
    virtual void OnHandleMouseEvent(const MouseInfo& event) {}
    virtual bool IsRegisterTouchCallback()
    {
        return false;
    }

    virtual void OnHandleMoveStart(const GestureEvent& event, bool isFirst) {}
    virtual void OnHandleMove(const RectF& rect, bool isFirst) {}
    virtual void OnHandleMoveDone(const RectF& rect, bool isFirst) {}
    virtual void OnHandleReverse(bool isReverse) {}
    virtual bool IsRegisterHandleCallback()
    {
        return true;
    }
    virtual void OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info = nullptr) {}
    virtual bool CheckTouchInHostNode(const PointF& touchPoint) = 0;
    virtual void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside = true) {};
    virtual void OnHandleGlobalEvent(const PointF& touchPoint, const PointF& localPoint, const TouchEvent& event)
    {
        bool touchInside = CheckTouchInHostNode(localPoint);
        if (event.type == TouchType::DOWN) {
            isIntercept_ = event.sourceType != SourceType::MOUSE && touchInside;
        }
        CHECK_NULL_VOID(!isIntercept_);
        if (event.type == TouchType::UP) {
            isIntercept_ = false;
        }
        if (event.sourceType == SourceType::MOUSE && event.type == TouchType::DOWN) {
            OnHandleGlobalTouchEvent(SourceType::MOUSE, TouchType::DOWN, touchInside);
            return;
        }
        if (event.sourceType == SourceType::TOUCH || event.sourceType == SourceType::TOUCH_PAD) {
            if (event.type == TouchType::DOWN) {
                downPointInfo_ = { touchPoint, event.id, event.GetOffset() };
                return;
            }
            if (event.type == TouchType::MOVE && downPointInfo_ &&
                downPointInfo_.IsAwayFromPoint(event)) {
                downPointInfo_.Reset();
                return;
            }
            if (event.type == TouchType::UP && downPointInfo_) {
                OnHandleGlobalTouchEvent(event.sourceType, TouchType::UP);
                downPointInfo_.Reset();
            }
        }
    }

    void OnUnbind()
    {
        downPointInfo_.Reset();
        isIntercept_ = false;
    }

    virtual void OnHandleLevelModeChanged(HandleLevelMode mode) {}
    virtual bool CheckSwitchToMode(HandleLevelMode mode) {
        return true;
    }
    virtual void OnHandleIsHidden() {}

private:
    bool isIntercept_ = false;
    TouchPointInfo downPointInfo_;
    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayCallback);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_OVERLAY_CALLBACK_H
