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

#ifndef OHOS_ACE_FRAMEWORK_CJ_GESTURE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_GESTURE_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
struct CJGestureInfo {
    const char* tag;
    int32_t type;
    bool isSystemGesture;
};

struct CJBaseGestureEvent {
    CJBaseEvent* baseEvent;
    CJFingerInfo* fingerList;
    int32_t fingerListSize;
    bool repeat;
    double offsetX;
    double offsetY;
    double velocityX;
    double velocityY;
    double velocity;
    double scale;
    double pinchCenterX;
    double pinchCenterY;
    double angle;
    double speed;
};

CJ_EXPORT void FfiOHOSAceFrameworkGestureCreate(int32_t priority, int32_t mask);
CJ_EXPORT void FfiOHOSAceFrameworkGestureSetTag(const char* tag);
CJ_EXPORT void FfiOHOSAceFrameworkGestureOnAction(void (*callback)(CJGestureEvent info));
CJ_EXPORT void FfiOHOSAceFrameworkGestureOnActionStart(void (*callback)(CJGestureEvent info));
CJ_EXPORT void FfiOHOSAceFrameworkGestureOnActionUpdate(void (*callback)(CJGestureEvent info));
CJ_EXPORT void FfiOHOSAceFrameworkGestureOnActionEnd(void (*callback)(CJGestureEvent info));
CJ_EXPORT void FfiOHOSAceFrameworkGestureOnActionCancel(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkGestureFinish();
CJ_EXPORT void FfiOHOSAceFrameworkGesturePop();
CJ_EXPORT void FfiOHOSAceFrameworkTapGestureCreate(int32_t count, int32_t fingers);
CJ_EXPORT void FfiOHOSAceFrameworkLongPressGestureCreate(int32_t fingers, bool repeat, int32_t duration);
CJ_EXPORT void FfiOHOSAceFrameworkPinchGestureCreate(int32_t fingers, double distance);
CJ_EXPORT void FfiOHOSAceFrameworkSwipeGestureCreate(int32_t fingers, uint32_t direction, double speed);
CJ_EXPORT void FfiOHOSAceFrameworkRotationGestureCreate(int32_t fingers, double angle);
CJ_EXPORT void FfiOHOSAceFrameworkPanGestureCreate(int32_t fingers, uint32_t direction, double distance);
CJ_EXPORT void FfiOHOSAceFrameworkPanGestureCreateWithOptions(int64_t OptionID);
CJ_EXPORT void FfiOHOSAceFrameworkGestureGroupCreate(int32_t mode);
CJ_EXPORT void FfiOHOSAceFrameworkGestureGroupCreate(int32_t mode);
CJ_EXPORT int64_t FfiOHOSAceFrameworkPanGestureOptionsCtor(int32_t fingers, uint32_t direction, double distance);
CJ_EXPORT void FfiOHOSAceFrameworkPanGestureOptionsSetFingers(int64_t selfID, int32_t fingers);
CJ_EXPORT void FfiOHOSAceFrameworkPanGestureOptionsSetDirection(int64_t selfID, uint32_t direction);
CJ_EXPORT void FfiOHOSAceFrameworkPanGestureOptionsSetDistance(int64_t selfID, double distance);

CJ_EXPORT int64_t FfiOHOSAceFrameworkTapGestureHandlerCtor(int32_t count, int32_t fingers);
CJ_EXPORT int64_t FfiOHOSAceFrameworkLongPressGestureHandlerCtor(int32_t fingers, bool repeat, int32_t duration);
CJ_EXPORT int64_t FfiOHOSAceFrameworkPinchGestureHandlerCtor(int32_t fingers, double distance);
CJ_EXPORT int64_t FfiOHOSAceFrameworkSwipeGestureHandlerCtor(int32_t fingers, uint32_t direction, double speed);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRotationGestureHandlerCtor(int32_t fingers, double angle);
CJ_EXPORT int64_t FfiOHOSAceFrameworkPanGestureHandlerCtor(int32_t fingers, uint32_t direction, double distance);
CJ_EXPORT int64_t FfiOHOSAceFrameworkGestureGroupHandlerCtor(int32_t mode, VectorInt64Handle vectorHandle);
CJ_EXPORT void FfiOHOSAceFrameworkGestureGroupHandlerSetOnCancel(int64_t id, void (*onCancel)());
CJ_EXPORT void FfiOHOSAceFrameworkGestureHandlerSetTag(int64_t id, const char* tag);
CJ_EXPORT void FfiOHOSAceFrameworkGestureHandlerSetOnAction(int64_t id, void (*onActionCallback)(CJGestureEvent));
CJ_EXPORT void FfiOHOSAceFrameworkGestureHandlerSetOnActionStart(int64_t id, void (*onActionCallback)(CJGestureEvent));
CJ_EXPORT void FfiOHOSAceFrameworkGestureHandlerSetOnActionUpdate(int64_t id, void (*onActionCallback)(CJGestureEvent));
CJ_EXPORT void FfiOHOSAceFrameworkGestureHandlerSetOnActionEnd(int64_t id, void (*onActionCallback)(CJGestureEvent));
CJ_EXPORT void FfiOHOSAceFrameworkGestureHandlerSetOnActionCancel(int64_t id, void (*onCancel)());
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetGestureHandler(
    int64_t elemId, int64_t gestureId, int32_t priority, int32_t mask);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetGestureGroupHandler(
    int64_t elemId, int64_t gestureId, int32_t priority, int32_t mask);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractClearGestureHandlers(int64_t elemId);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractRemoveGestureHandlerByTag(int64_t elemId, const char* tag);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetOnGestureJudgeBegin(
    int32_t (*callback)(CJGestureInfo, CJBaseGestureEvent));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_GESTURE_FFI_H
