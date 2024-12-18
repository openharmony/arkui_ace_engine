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

#include "core/components_ng/pattern/ui_extension/platform_event_proxy.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
namespace {
const std::map<uint32_t, std::string> PAN_GESTURE_MAP = {
    { PanDirection::LEFT, "Left" },
    { PanDirection::RIGHT, "Right" },
    { PanDirection::UP, "Up" },
    { PanDirection::DOWN, "Down" },
};
}

void PlatformEventProxy::SetHostNode(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

bool PlatformEventProxy::HasEventProxy(int32_t flag)
{
    uint64_t uFlag = static_cast<uint64_t>(flag);
    if ((uFlag & EventProxyFlag::EVENT_CLICK) && clickEvent_ == nullptr) {
        return false;
    }

    if ((uFlag & EventProxyFlag::EVENT_LONG_PRESS) && longPressEvent_ == nullptr) {
        return false;
    }

    auto panFlag = GetPanDirection(static_cast<uint64_t>(uFlag));
    if (panFlag != 0) {
        if (panEvent_ == nullptr) {
            return false;
        }

        if (!(panDirection_ & panFlag)) {
            return false;
        }
    }

    return true;
}

void PlatformEventProxy::SetEventProxyFlag(int32_t flag)
{
    auto host = host_.Upgrade();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    uint64_t uFlag = static_cast<uint64_t>(flag);
    EventProxyResultCode clickResultCode = SetClickEventProxy(
        gestureHub, uFlag & EventProxyFlag::EVENT_CLICK);
    EventProxyResultCode longPressResultCode = SetLongPressEventProxy(
        gestureHub, uFlag & EventProxyFlag::EVENT_LONG_PRESS);
    EventProxyResultCode panGestureResultCode = SetPanGestureEventProxy(
        gestureHub, GetPanDirection(uFlag));
    LOGI("SetEventProxyFlag flag: %{public}d, clickResult: %{public}d, "
        "longPressResultCode: %{public}d, panGestureResultCode: %{public}d",
        flag, clickResultCode, longPressResultCode, panGestureResultCode);
}

uint32_t PlatformEventProxy::GetPanDirection(uint64_t flag)
{
    return flag & 0xF;
}

EventProxyResultCode PlatformEventProxy::SetClickEventProxy(
    const RefPtr<GestureEventHub>& gestureHub, bool addEvent)
{
    CHECK_NULL_RETURN(gestureHub, EventProxyResultCode::CHECK_POINTER_NULL);
    if (!addEvent) {
        if (clickEvent_ == nullptr) {
            return EventProxyResultCode::NO_EXIST_WHEN_DELETE;
        }

        gestureHub->RemoveClickEvent(clickEvent_);
        clickEvent_ = nullptr;
        return EventProxyResultCode::REMOVE_WHEN_DELETE;
    }

    if (clickEvent_ != nullptr) {
        return EventProxyResultCode::EXIST_WHEN_ADDING;
    }

    auto clickCallback = [wp = WeakClaim(this)](GestureEvent& info) {
        LOGI("ClickEventProxy");
    };
    clickEvent_ = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickEvent_);
    return EventProxyResultCode::ADD_WHEN_ADDING;
}

EventProxyResultCode PlatformEventProxy::SetLongPressEventProxy(
    const RefPtr<GestureEventHub>& gestureHub, bool addEvent)
{
    CHECK_NULL_RETURN(gestureHub, EventProxyResultCode::CHECK_POINTER_NULL);
    if (!addEvent) {
        if (longPressEvent_ == nullptr) {
            return EventProxyResultCode::NO_EXIST_WHEN_DELETE;
        }

        gestureHub->SetLongPressEvent(nullptr);
        longPressEvent_ = nullptr;
        return EventProxyResultCode::REMOVE_WHEN_DELETE;
    }

    if (longPressEvent_ != nullptr) {
        return EventProxyResultCode::EXIST_WHEN_ADDING;
    }

    auto longPressCallback = [](const GestureEvent& info) {
        LOGI("LongPressEventEventProxy");
    };
    longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gestureHub->SetLongPressEvent(longPressEvent_);
    return EventProxyResultCode::ADD_WHEN_ADDING;
}

EventProxyResultCode PlatformEventProxy::SetPanGestureEventProxy(
    const RefPtr<GestureEventHub>& gestureHub, uint32_t panDirection)
{
    CHECK_NULL_RETURN(gestureHub, EventProxyResultCode::CHECK_POINTER_NULL);
    if (panDirection_ == panDirection) {
        return panDirection_ == PanDirection::NONE ?
            EventProxyResultCode::NO_EXIST_WHEN_DELETE : EventProxyResultCode::EXIST_WHEN_ADDING;
    }

    if (panDirection_ != PanDirection::NONE) {
        gestureHub->RemovePanEvent(panEvent_);
        panEvent_ = nullptr;
    }

    if (panDirection == PanDirection::NONE) {
        panDirection_ = PanDirection::NONE;
        return EventProxyResultCode::REMOVE_WHEN_DELETE;
    }

    panDirection_ = panDirection;
    PanDirection temPanDirection;
    temPanDirection.type = panDirection_;
    auto onActionStart = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGI("PanGestureEventProxy");
    };
    auto onActionUpdate = [](const GestureEvent& info) {};
    auto onActionEnd = [weak = WeakClaim(this)](const GestureEvent& info) {};
    auto onActionCancel = [weak = WeakClaim(this)]() {};
    panEvent_ = MakeRefPtr<PanEvent>(std::move(onActionStart), std::move(onActionUpdate),
        std::move(onActionEnd), std::move(onActionCancel));
    gestureHub->AddPanEvent(panEvent_, temPanDirection, 1, DEFAULT_PAN_DISTANCE);
    return EventProxyResultCode::ADD_WHEN_ADDING;
}

std::string PlatformEventProxy::GetCurEventProxyToString()
{
    std::string eventProxyStr = "[";
    bool hasPre = false;
    if (clickEvent_) {
        eventProxyStr.append("Click");
        hasPre = true;
    }

    if (longPressEvent_) {
        if (hasPre) {
            eventProxyStr.append(", ");
        }
        eventProxyStr.append("LongPress");
        hasPre = true;
    }

    if (panEvent_) {
        for (const auto item : PAN_GESTURE_MAP) {
            if (!(panDirection_ & item.first)) {
                continue;
            }

            if (hasPre) {
                eventProxyStr.append(", ");
            }

            eventProxyStr.append(item.second);
            hasPre = true;
        }
    }

    eventProxyStr.append("]");
    return eventProxyStr;
}
} // namespace OHOS::Ace::NG
