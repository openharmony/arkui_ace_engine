/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef SCROLLABLE_COMPONENT_COMMON_ARKUISCROLLEVENTS_H
#define SCROLLABLE_COMPONENT_COMMON_ARKUISCROLLEVENTS_H

#include <cstdint>
#include <arkui/native_node.h>

/**
 * 滚动事件掩码
 */
enum : uint32_t {
    SCROLL_EVT_FRAME_BEGIN = 1u << 0,
    SCROLL_EVT_START = 1u << 1,
    SCROLL_EVT_STOP = 1u << 2,
    SCROLL_EVT_REACH_START = 1u << 3,
    SCROLL_EVT_REACH_END = 1u << 4,
    SCROLL_EVT_WILL_STOP_DRAG = 1u << 5,
    SCROLL_EVT_ALL = SCROLL_EVT_FRAME_BEGIN | SCROLL_EVT_START | SCROLL_EVT_STOP | SCROLL_EVT_REACH_START |
                     SCROLL_EVT_REACH_END | SCROLL_EVT_WILL_STOP_DRAG
};

/**
 * 事件 map
 */
struct ScrollEvtMap {
    uint32_t bit;
    ArkUI_NodeEventType evt;
};

inline constexpr ScrollEvtMap kScrollEvtMap[] = {
    {SCROLL_EVT_FRAME_BEGIN, NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN},
    {SCROLL_EVT_START, NODE_SCROLL_EVENT_ON_SCROLL_START},
    {SCROLL_EVT_STOP, NODE_SCROLL_EVENT_ON_SCROLL_STOP},
    {SCROLL_EVT_REACH_START, NODE_SCROLL_EVENT_ON_REACH_START},
    {SCROLL_EVT_REACH_END, NODE_SCROLL_EVENT_ON_REACH_END},
    {SCROLL_EVT_WILL_STOP_DRAG, NODE_SCROLL_EVENT_ON_WILL_STOP_DRAGGING},
};

template <class F> inline void ForEachScrollEvt(uint32_t mask, F &&fn)
{
    for (const auto &m : kScrollEvtMap) {
        if (mask & m.bit) {
            fn(m.evt);
        }
    }
}

/**
 * 批量注册事件
 */
inline void RegisterScrollEvents(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, void *userData,
                                 uint32_t mask = SCROLL_EVT_ALL)
{
    if (!api || !node) {
        return;
    }
    ForEachScrollEvt(mask, [&](ArkUI_NodeEventType evt) { api->registerNodeEvent(node, evt, 0, userData); });
}

/**
 * 批量取消注册事件
 */
inline void UnregisterScrollEvents(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, uint32_t mask = SCROLL_EVT_ALL)
{
    if (!api || !node) {
        return;
    }
    ForEachScrollEvt(mask, [&](ArkUI_NodeEventType evt) { api->unregisterNodeEvent(node, evt); });
}

/**
 * 滚动事件自动注册/注销
 */
class ScrollEventGuard {
public:
    ScrollEventGuard() = default;

    ScrollEventGuard(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, void *userData, uint32_t mask = SCROLL_EVT_ALL)
    {
        Bind(api, node, userData, mask);
    }

    void Bind(ArkUI_NativeNodeAPI_1 *api, ArkUI_NodeHandle node, void *userData, uint32_t mask = SCROLL_EVT_ALL)
    {
        api_ = api;
        node_ = node;
        user_ = userData;
        mask_ = mask;
        RegisterScrollEvents(api_, node_, user_, mask_);
        armed_ = true;
    }

    void Release()
    {
        if (armed_) {
            UnregisterScrollEvents(api_, node_, mask_);
            armed_ = false;
        }
    }

    ~ScrollEventGuard()
    {
        if (armed_) {
            UnregisterScrollEvents(api_, node_, mask_);
        }
    }

private:
    ArkUI_NativeNodeAPI_1 *api_ = nullptr;
    ArkUI_NodeHandle node_ = nullptr;
    void *user_ = nullptr;
    uint32_t mask_ = SCROLL_EVT_ALL;
    bool armed_ = false;
};

#endif // SCROLLABLE_COMPONENT_COMMON_ARKUISCROLLEVENTS_H
