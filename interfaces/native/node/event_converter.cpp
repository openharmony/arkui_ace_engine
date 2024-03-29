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

#include <cstdint>

#include "native_event.h"
#include "native_node.h"
#include "node/gesture_impl.h"
#include "node/node_model.h"
#include "securec.h"
#include "node_extened.h"
#include "base/log/log_wrapper.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NodeModel {

ArkUI_Int32 ConvertOriginEventType(ArkUI_NodeEventType type, int32_t nodeType)
{
    auto arkUINodeType = static_cast<ArkUI_NodeType>(nodeType);
    switch (type) {
        case NODE_TEXT_INPUT_ON_CHANGE:
            return ON_TEXT_INPUT_CHANGE;
        case NODE_SCROLL_EVENT_ON_SCROLL:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL;
            }
            return ON_SCROLL;
        case NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL_FRAME_BEGIN;
            }
            return ON_SCROLL_FRAME_BEGIN;
        case NODE_SCROLL_EVENT_ON_SCROLL_START:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL_START;
            }
            return ON_SCROLL_START;
        case NODE_SCROLL_EVENT_ON_SCROLL_STOP:
            if (arkUINodeType == ARKUI_NODE_LIST) {
                return ON_LIST_SCROLL_STOP;
            }
            return ON_SCROLL_STOP;
        case NODE_EVENT_ON_APPEAR:
            return ON_APPEAR;
        case NODE_EVENT_ON_DISAPPEAR:
            return ON_DISAPPEAR;
        case NODE_EVENT_ON_AREA_CHANGE:
            return ON_AREA_CHANGE;
        case NODE_TEXT_AREA_ON_CHANGE:
            return ON_TEXTAREA_CHANGE;
        case NODE_ON_FOCUS:
            return ON_FOCUS;
        case NODE_ON_BLUR:
            return ON_BLUR;
        case NODE_TEXT_INPUT_ON_SUBMIT:
            return ON_TEXT_INPUT_SUBMIT;
        case NODE_REFRESH_STATE_CHANGE:
            return ON_REFRESH_STATE_CHANGE;
        case NODE_REFRESH_ON_REFRESH:
            return ON_REFRESH_REFRESHING;
        case NODE_SCROLL_EVENT_ON_SCROLL_EDGE:
            return ON_SCROLL_EDGE;
        case NODE_TOGGLE_ON_CHANGE:
            return ON_TOGGLE_CHANGE;
        case NODE_IMAGE_ON_COMPLETE:
            return ON_IMAGE_COMPLETE;
        case NODE_IMAGE_ON_ERROR:
            return ON_IMAGE_ERROR;
        case NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE:
            return ON_DATE_PICKER_DATE_CHANGE;
        case NODE_TIME_PICKER_EVENT_ON_CHANGE:
            return ON_TIME_PICKER_CHANGE;
        case NODE_CALENDAR_PICKER_EVENT_ON_CHANGE:
            return ON_CALENDAR_PICKER_CHANGE;
        case NODE_TOUCH_EVENT:
            return ON_TOUCH;
        case NODE_ON_CLICK:
            return ON_CLICK;
        case NODE_CHECKBOX_EVENT_ON_CHANGE:
            return ON_CHECKBOX_CHANGE;
        case NODE_SLIDER_EVENT_ON_CHANGE:
            return ON_SLIDER_CHANGE;
        case NODE_TEXT_INPUT_ON_CUT:
            return ON_TEXT_INPUT_CUT;
        case NODE_TEXT_INPUT_ON_PASTE:
            return ON_TEXT_INPUT_PASTE;
        case NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE:
            return ON_TEXT_INPUT_TEXT_SELECTION_CHANGE;
        case NODE_TEXT_AREA_ON_PASTE:
            return ON_TEXTAREA_PASTE;
        case NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE:
            return ON_TEXTAREA_TEXT_SELECTION_CHANGE;
        case NODE_SWIPER_EVENT_ON_CHANGE:
            return ON_SWIPER_CHANGE;
        case NODE_SWIPER_EVENT_ON_ANIMATION_START:
            return ON_SWIPER_ANIMATION_START;
        case NODE_SWIPER_EVENT_ON_ANIMATION_END:
            return ON_SWIPER_ANIMATION_END;
        case NODE_SWIPER_EVENT_ON_GESTURE_SWIPE:
            return ON_SWIPER_GESTURE_SWIPE;
        case NODE_ON_WILL_SCROLL:
            return ON_WILL_SCROLL;
        default:
            return -1;
    }
}

ArkUI_Int32 ConvertToNodeEventType(ArkUIEventSubKind type)
{
    switch (type) {
        case ON_TEXT_INPUT_CHANGE:
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
        case ON_DISAPPEAR:
            return NODE_EVENT_ON_DISAPPEAR;
        case ON_AREA_CHANGE:
            return NODE_EVENT_ON_AREA_CHANGE;
        case ON_TEXTAREA_CHANGE:
            return NODE_TEXT_AREA_ON_CHANGE;
        case ON_FOCUS:
            return NODE_ON_FOCUS;
        case ON_BLUR:
            return NODE_ON_BLUR;
        case ON_TEXT_INPUT_SUBMIT:
            return NODE_TEXT_INPUT_ON_SUBMIT;
        case ON_REFRESH_STATE_CHANGE:
            return NODE_REFRESH_STATE_CHANGE;
        case ON_REFRESH_REFRESHING:
            return NODE_REFRESH_ON_REFRESH;
        case ON_SCROLL_EDGE:
            return NODE_SCROLL_EVENT_ON_SCROLL_EDGE;
        case ON_TOGGLE_CHANGE:
            return NODE_TOGGLE_ON_CHANGE;
        case ON_IMAGE_COMPLETE:
            return NODE_IMAGE_ON_COMPLETE;
        case ON_IMAGE_ERROR:
            return NODE_IMAGE_ON_ERROR;
        case ON_DATE_PICKER_DATE_CHANGE:
            return NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE;
        case ON_TIME_PICKER_CHANGE:
            return NODE_TIME_PICKER_EVENT_ON_CHANGE;
        case ON_CALENDAR_PICKER_CHANGE:
            return NODE_CALENDAR_PICKER_EVENT_ON_CHANGE;
        case ON_TOUCH:
            return NODE_TOUCH_EVENT;
        case ON_CLICK:
            return NODE_ON_CLICK;
        case ON_CHECKBOX_CHANGE:
            return NODE_CHECKBOX_EVENT_ON_CHANGE;
        case ON_SLIDER_CHANGE:
            return NODE_SLIDER_EVENT_ON_CHANGE;
        case ON_TEXT_INPUT_CUT:
            return NODE_TEXT_INPUT_ON_CUT;
        case ON_TEXT_INPUT_PASTE:
            return NODE_TEXT_INPUT_ON_PASTE;
        case ON_TEXT_INPUT_TEXT_SELECTION_CHANGE:
            return NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE;
        case ON_TEXTAREA_PASTE:
            return NODE_TEXT_AREA_ON_PASTE;
        case ON_TEXTAREA_TEXT_SELECTION_CHANGE:
            return NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE;
        case ON_SWIPER_CHANGE:
            return NODE_SWIPER_EVENT_ON_CHANGE;
        case ON_SWIPER_ANIMATION_START:
            return NODE_SWIPER_EVENT_ON_ANIMATION_START;
        case ON_SWIPER_ANIMATION_END:
            return NODE_SWIPER_EVENT_ON_ANIMATION_END;
        case ON_SWIPER_GESTURE_SWIPE:
            return NODE_SWIPER_EVENT_ON_GESTURE_SWIPE;
        case ON_LIST_SCROLL:
            return NODE_SCROLL_EVENT_ON_SCROLL;
        case ON_LIST_SCROLL_FRAME_BEGIN:
            return NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN;
        case ON_LIST_SCROLL_START:
            return NODE_SCROLL_EVENT_ON_SCROLL_START;
        case ON_LIST_SCROLL_STOP:
            return NODE_SCROLL_EVENT_ON_SCROLL_STOP;
        case ON_WILL_SCROLL:
            return NODE_ON_WILL_SCROLL;
        default:
            return -1;
    }
}

bool IsStringEvent(ArkUI_Int32 type)
{
    switch (type) {
        case NODE_TEXT_INPUT_ON_CHANGE:
        case NODE_TEXT_INPUT_ON_CUT:
        case NODE_TEXT_INPUT_ON_PASTE:
        case NODE_TEXT_AREA_ON_CHANGE:
        case NODE_TEXT_AREA_ON_PASTE:
            return true;
        default:
            return false;
    }
}

bool IsTouchEvent(ArkUI_Int32 type)
{
    switch (type) {
        case NODE_TOUCH_EVENT:
            return true;
        default:
            return false;
    }
}

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_NodeEvent* event)
{
    ArkUIEventCategory eventCategory = static_cast<ArkUIEventCategory>(origin->kind);
    switch (eventCategory) {
        case COMPONENT_ASYNC_EVENT: {
            ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(origin->componentAsyncEvent.subKind);
            event->kind = ConvertToNodeEventType(subKind);
            if (memcpy_sp(event->componentEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue),
                    origin->componentAsyncEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue)) != 0) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event data");
                return false;
            }
            return true;
        }
        case TEXT_INPUT: {
            ArkUIEventSubKind subKind = static_cast<ArkUIEventSubKind>(origin->textInputEvent.subKind);
            event->kind = ConvertToNodeEventType(subKind);
            event->stringEvent.pStr = reinterpret_cast<ArkUI_CharPtr>(origin->textInputEvent.nativeStringPtr);
            return true;
        }
        case TOUCH_EVENT:
            event->kind = ConvertToNodeEventType(ON_TOUCH);
            if (memcpy_sp(&(event->touchEvent), sizeof(ArkUI_NodeTouchEvent), &(origin->touchEvent),
                    sizeof(ArkUITouchEvent)) != 0) {
                TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert origin event data");
                return false;
            }
            switch (origin->touchEvent.action) {
                case ACTION_DOWN:
                    event->touchEvent.action = NODE_ACTION_DOWN;
                    break;
                case ACTION_UP:
                    event->touchEvent.action = NODE_ACTION_UP;
                    break;
                case ACTION_MOVE:
                    event->touchEvent.action = NODE_ACTION_MOVE;
                    break;
                case ACTION_CANCEL:
                    event->touchEvent.action = NODE_ACTION_CANCEL;
                    break;
                default:
                    event->touchEvent.action = NODE_ACTION_CANCEL;
            }
            return true;
        default:
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "failed to convert origin event data");
            return false;
    }

    return true;
}

bool ConvertEventResult(ArkUI_NodeEvent* event, ArkUINodeEvent* origin)
{
    if (IsTouchEvent(event->kind)) {
        origin->touchEvent.preventDefault = event->touchEvent.preventDefault;
        origin->touchEvent.stopPropagation = event->touchEvent.stopPropagation;
        return true;
    }
    if (!IsStringEvent(event->kind)) {
        if (memcpy_sp(origin->componentAsyncEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue),
                event->componentEvent.data, MAX_COMPONENT_EVENT_ARG_NUM * sizeof(ArkUI_NumberValue)) != 0) {
            TAG_LOGE(AceLogTag::ACE_NATIVE_NODE, "fail to convert event result data");
            return false;
        }
    }
    return true;
}

void HandleInnerEvent(ArkUINodeEvent* innerEvent)
{
    switch (innerEvent->kind) {
        case ArkUIEventCategory::GESTURE_ASYNC_EVENT: {
            // handle gesture event.
            OHOS::Ace::GestureModel::HandleGestureEvent(innerEvent);
            break;
        }
        default: {
            OHOS::Ace::NodeModel::HandleInnerNodeEvent(innerEvent);
        }
    }
}

}; // namespace OHOS::Ace::NodeModel
