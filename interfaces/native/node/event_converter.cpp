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
#include "node/basic_types.h"
#include "securec.h"

#include "base/log/log_wrapper.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NodeModel {

ArkUI_Int32 ConvertOriginEventType(ArkUI_NodeEventType type)
{
    switch (type) {
        case NODE_SCROLL_EVENT:
            return ON_SCROLL;
        case NODE_TEXT_INPUT_ON_CHANGE:
            return ON_TEXTINPUT_CHANGE;
        default:
            return -1;
    }
}

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_NodeEvent* event)
{
    switch (origin->kind) {
        case ON_SCROLL: {
            if (memcpy_sp(event->componentEvent.data, MAX_COMPONENT_EVENT_ARG_NUM, origin->componentAsyncEvent.data,
                MAX_COMPONENT_EVENT_ARG_NUM) != 0) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event data");
                return false;
            }
            event->kind = NODE_SCROLL_EVENT;
            event->eventId = origin->eventId;
            return true;
        }
        case ON_TEXTINPUT_CHANGE: {
            if (memcpy_sp(&event->stringEvent.pStr, sizeof(ArkUI_CharPtr), &origin->stringAsyncEvent.pStr,
                sizeof(ArkUI_CharPtr)) != 0) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event data");
                return false;
            }
            event->kind = NODE_TEXT_INPUT_ON_CHANGE;
            event->eventId = origin->eventId;
            return true;
        }
        default: {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event. %{public}d", origin->kind);
            return false;
        }
    }
}

}; // namespace OHOS::Ace::NodeModel
