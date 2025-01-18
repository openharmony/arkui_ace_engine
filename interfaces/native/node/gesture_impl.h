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

ArkUI_GestureRecognizer* CreateTapGesture(int32_t count, int32_t fingers);

ArkUI_GestureRecognizer* CreateTapGestureWithDistanceThreshold(
    int32_t count, int32_t fingers, double distanceThreshold);

ArkUI_GestureRecognizer* CreateLongPressGesture(int32_t fingers, bool repeatResult, int32_t duration);

ArkUI_GestureRecognizer* CreatePanGesture(int32_t fingersNum, ArkUI_GestureDirectionMask mask, double distanceNum);

ArkUI_GestureRecognizer* CreatePinchGesture(int32_t fingersNum, double distanceNum);

ArkUI_GestureRecognizer* CreateRotationGesture(int32_t fingersNum, double angleNum);

ArkUI_GestureRecognizer* CreateSwipeGesture(
    int32_t fingersNum, ArkUI_GestureDirectionMask directions, double speedNum);

void DisposeGesture(ArkUI_GestureRecognizer* recognizer);

int32_t SetGestureEventTarget(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventActionTypeMask mask,
    void* extraParam, void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParam));

int32_t AddGestureToNode(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer, ArkUI_GesturePriority priorityNum,
    ArkUI_GestureMask mask);

int32_t RemoveGestureFromNode(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer);

ArkUI_GestureRecognizerType GetGestureType(ArkUI_GestureRecognizer* recognizer);

ArkUI_GestureRecognizer* CreateGroupGesture(ArkUI_GroupGestureMode gestureMode);

int32_t AddChildGesture(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

int32_t RemoveChildGesture(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

void HandleGestureEvent(ArkUINodeEvent* event);

int32_t SetGestureInterrupterToNode(
    ArkUI_NodeHandle node,  ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info));

int32_t SetInnerGestureParallelTo(ArkUI_NodeHandle node, void* userData,
    ArkUI_GestureRecognizer* (*parallelInnerGesture)(ArkUI_ParallelInnerGestureEvent* event));

}; // namespace OHOS::Ace::GestureModel
#endif