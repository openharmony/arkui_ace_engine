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
#include "node/event_converter.h"

#include "basic_node.h"
#include "securec.h"

#include "base/log/log_wrapper.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NodeModel {

ArkUI_Int32 ConvertOriginEventType(ArkUI_NodeEventType type)
{
    switch (type) {
        case NODE_TEXT_INPUT_ON_CHANGE:
            return ON_TEXTINPUT_CHANGE;
        case NODE_SCROLL_EVENT_ON_SCROLL:
            return ON_SCROLL;
        case NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN:
            return ON_SCROLL_FRAME_BEGIN;
        case NODE_SCROLL_EVENT_ON_SCROLL_START:
            return ON_SCROLL_START;
        case NODE_SCROLL_EVENT_ON_SCROLL_STOP:
            return ON_SCROLL_STOP;
        case NODE_EVENT_ON_APPEAR:
            return ON_APPEAR;
        case NODE_ON_FOCUS:
            return ON_FOCUS;
        case NODE_ON_BLUR:
            return ON_BLUR;
        case NODE_TEXT_INPUT_ON_SUBMIT:
            return ON_TEXTINPUT_SUBMIT;
        case NODE_REFRESH_STATE_CHANGE:
            return ON_REFRESH_STATE_CHANGE;
        case NODE_REFRESH_ON_REFRESH:
            return ON_REFRESH_REFRESHING;
        case NODE_SCROLL_EVENT_EDGE:
            return ON_SCROLL_EDGE;
        default:
            return -1;
    }
}

ArkUI_Int32 ConvertToNodeEventType(ArkUIAsyncEventKind type)
{
    switch (type) {
        case ON_TEXTINPUT_CHANGE:
            return NODE_TEXT_INPUT_ON_CHANGE;
        case ON_SCROLL:
            return NODE_SCROLL_EVENT_ON_SCROLL;
        case ON_SCROLL_FRAME_BEGIN:
            return NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN;
        case ON_SCROLL_START:
            return NODE_SCROLL_EVENT_ON_SCROLL_START;
        case ON_SCROLL_STOP:
            return NODE_SCROLL_EVENT_ON_SCROLL_STOP;
        case ON_APPEAR:
            return NODE_EVENT_ON_APPEAR;
        case ON_FOCUS:
            return NODE_ON_FOCUS;
        case ON_BLUR:
            return NODE_ON_BLUR;
        case ON_TEXTINPUT_SUBMIT:
            return NODE_TEXT_INPUT_ON_SUBMIT;
        case ON_REFRESH_STATE_CHANGE:
            return NODE_REFRESH_STATE_CHANGE;
        case ON_REFRESH_REFRESHING:
            return NODE_REFRESH_ON_REFRESH;
        case NODE_SCROLL_EVENT_EDGE:
            return ON_SCROLL_EDGE;
        default:
            return -1;
    }
}

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_NodeEvent* event)
{
    if (memcpy_sp(event->componentEvent.data, MAX_COMPONENT_EVENT_ARG_NUM, origin->componentAsyncEvent.data,
            MAX_COMPONENT_EVENT_ARG_NUM) != 0) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event data");
        return false;
    }
    event->kind = ConvertToNodeEventType(static_cast<ArkUIAsyncEventKind>(origin->kind));
    if (event->kind == -1) {
        TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event. %{public}d", origin->kind);
        return false;
    }
    event->eventId = origin->eventId;
    return true;
}
}; // namespace OHOS::Ace::NodeModel
