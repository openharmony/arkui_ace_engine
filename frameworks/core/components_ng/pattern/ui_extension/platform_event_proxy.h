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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_EVENT_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_EVENT_PROXY_H

#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {
enum EventProxyFlag : uint64_t {
    EVENT_NONE = 0X00000000,
    EVENT_CLICK = 0X00000001,
    EVENT_LONG_PRESS = 0X00000002,
    EVENT_PAN_GESTURE_VERTICAL = 0X00000004,
    EVENT_PAN_GESTURE_HORIZONTAL = 0X00000008
};

enum EventProxyResultCode : int32_t {
    NO_ERRORS = 0,
    CHECK_POINTER_NULL,
    NO_EXIST_WHEN_DELETE,
    REMOVE_WHEN_DELETE,
    EXIST_WHEN_ADDING,
    ADD_WHEN_ADDING,
};

class PlatformEventProxy : public AceType {
    DECLARE_ACE_TYPE(PlatformEventProxy, AceType);

public:
    virtual ~PlatformEventProxy() = default;

    void SetHostNode(const WeakPtr<FrameNode>& host);
    void SetEventProxyFlag(int32_t flag);
    bool HasEventProxy(int32_t flag);
    std::string GetCurEventProxyToString();

    EventProxyResultCode SetClickEventProxy(
        const RefPtr<GestureEventHub>& gestureHub, bool addEvent);
    EventProxyResultCode SetLongPressEventProxy(
        const RefPtr<GestureEventHub>& gestureHub, bool addEvent);
    EventProxyResultCode SetPanGestureEventProxy(
        const RefPtr<GestureEventHub>& gestureHub, uint32_t panDirection);
    uint32_t GetPanDirection(uint64_t flag);

private:
    RefPtr<ClickEvent> clickEvent_;
    RefPtr<LongPressEvent> longPressEvent_;
    RefPtr<PanEvent> panEvent_;
    uint32_t panDirection_ = PanDirection::NONE;
    WeakPtr<FrameNode> host_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_PLATFORM_EVENT_PROXY_H
