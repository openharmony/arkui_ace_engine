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

#ifndef ARKUI_NATIVE_NODE_EVENT_CONVERTER_H
#define ARKUI_NATIVE_NODE_EVENT_CONVERTER_H

#include "native_compatible.h"
#include "native_node.h"
#include "native_type.h"

#include "core/interfaces/arkoala/arkoala_api.h"

struct ArkUI_NodeEvent {
    int32_t category;
    int32_t kind;
    int32_t targetId;
    ArkUI_NodeHandle node;
    void* userData;
    void* origin;
    int32_t eventId;
};

enum NodeEventCategory {
    NODE_EVENT_CATEGORY_UNKOWN = -1,
    NODE_EVENT_CATEGORY_INPUT_EVENT,
    NODE_EVENT_CATEGORY_COMPONENT_EVENT,
    NODE_EVENT_CATEGORY_STRING_ASYNC_EVENT,
    NODE_EVENT_CATEGORY_MIXED_EVENT,
};

namespace OHOS::Ace::NodeModel {
// for error info, use int instead of ArkUINodeEventType
ArkUI_Int32 ConvertOriginEventType(ArkUI_NodeEventType type, int32_t nodeType);
ArkUI_Int32 ConvertToNodeEventType(ArkUIEventSubKind type);
bool IsStringEvent(ArkUI_Int32 type);
bool IsTouchEvent(ArkUI_Int32 type);

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_NodeEvent* event);

void HandleInnerEvent(ArkUINodeEvent* innerEvent);
int32_t ConvertToCTouchActionType(int32_t originActionType);
int32_t ConvertToCInputEventToolType(int32_t originSourceType);

bool ConvertEvent(ArkUINodeEvent* origin, ArkUI_CompatibleNodeEvent* event);
bool ConvertEventResult(ArkUI_CompatibleNodeEvent* event, ArkUINodeEvent* origin);

int32_t ConvertToCMouseActionType(int32_t originActionType);
int32_t ConvertToCMouseEventButtonType(int32_t originButtonType);
int32_t ConvertToCAxisActionType(int32_t originActionType);

}; // namespace OHOS::Ace::NodeModel
#endif // ARKUI_NATIVE_NODE_EVENT_CONVERTER_H
