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
#ifndef ARKUI_NATIVE_GESTTURE_IMPL_H
#define ARKUI_NATIVE_GESTTURE_IMPL_H

#include <cstdint>

#include "native_gesture.h"
#include "native_node.h"
#include "native_type.h"

namespace OHOS::Ace::GestureModel {

ArkUI_GestureRecognizer* CreatePanGesture(int32_t fingersNum, ArkUI_GestureDirectionMask mask, double distanceNum);

void DisposeGesture(ArkUI_GestureRecognizer* recognizer);

int32_t SetGestureEventTarget(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventActionTypeMask mask,
    void* extraParam, void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParam));

void AddGestureToNode(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer, ArkUI_GesturePriority priorityNum,
    ArkUI_GestureMask mask);

void HandleGestureEvent(ArkUINodeEvent* event);

}; // namespace OHOS::Ace::GestureModel
#endif