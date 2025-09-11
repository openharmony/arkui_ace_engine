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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GESTURE_GESTURE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GESTURE_GESTURE_MODEL_H

#include <mutex>
#include <string>

#include "core/gestures/gesture_info.h"
#include "core/gestures/gesture_processor.h"
#include "frameworks/base/memory/referenced.h"

namespace OHOS::Ace {
enum class GestureEventAction { ACTION, START, UPDATE, END, CANCEL };
class GestureModel {
public:
    static GestureModel* GetInstance();
    virtual ~GestureModel() = default;

    virtual void Create(int32_t priorityNum, int32_t gestureMaskNum) = 0;
    virtual void Finish() = 0;
    virtual void Pop() = 0;
    virtual void SetOnGestureEvent(const GestureEventFunc& gestureEventFunc) = 0;
    virtual void SetOnActionFunc(const GestureEventFunc& gestureEventFunc, const Ace::GestureEventAction& action) = 0;
    virtual void SetTag(const std::string& tag) = 0;
    virtual void SetAllowedTypes(const std::set<SourceTool>& allowedTypes) = 0;

private:
    static std::unique_ptr<GestureModel> instance_;
    static std::mutex mutex_;
};

class TapGestureModel {
public:
    static TapGestureModel* GetInstance();
    virtual ~TapGestureModel() = default;

    virtual void Create(int32_t countNum, int32_t fingersNum, double distanceThreshold, bool isLimitFingerCount) = 0;

private:
    static std::unique_ptr<TapGestureModel> instance_;
    static std::mutex mutex_;
};

class LongPressGestureModel {
public:
    static LongPressGestureModel* GetInstance();
    virtual ~LongPressGestureModel() = default;

    virtual void Create(int32_t fingersNum, bool repeatResult, int32_t durationNum, bool isLimitFingerCount) = 0;

private:
    static std::unique_ptr<LongPressGestureModel> instance_;
    static std::mutex mutex_;
};

class PanGestureModel {
public:
    static PanGestureModel* GetInstance();
    virtual ~PanGestureModel() = default;

    virtual void Create(
        int32_t fingersNum, const PanDirection& panDirection, double distanceNum, bool isLimitFingerCount) = 0;
    virtual void Create(int32_t fingersNum, const PanDirection& panDirection,
        const PanDistanceMapDimension& distanceMap, bool isLimitFingerCount) = 0;
    virtual void SetPanGestureOption(const RefPtr<PanGestureOption>& panGestureOption) = 0;

private:
    static std::unique_ptr<PanGestureModel> instance_;
    static std::mutex mutex_;
};

class SwipeGestureModel {
public:
    static SwipeGestureModel* GetInstance();
    virtual ~SwipeGestureModel() = default;

    virtual void Create(int32_t fingersNum, const SwipeDirection& slideDirection,
        const Dimension& speedNum, bool isLimitFingerCount) = 0;

private:
    static std::unique_ptr<SwipeGestureModel> instance_;
    static std::mutex mutex_;
};

class PinchGestureModel {
public:
    static PinchGestureModel* GetInstance();
    virtual ~PinchGestureModel() = default;

    virtual void Create(int32_t fingersNum, double distanceNum, bool isLimitFingerCount) = 0;

private:
    static std::unique_ptr<PinchGestureModel> instance_;
    static std::mutex mutex_;
};

class RotationGestureModel {
public:
    static RotationGestureModel* GetInstance();
    virtual ~RotationGestureModel() = default;

    virtual void Create(int32_t fingersNum, double angleNum, bool isLimitFingerCount) = 0;

private:
    static std::unique_ptr<RotationGestureModel> instance_;
    static std::mutex mutex_;
};

class GestureGroupModel {
public:
    static GestureGroupModel* GetInstance();
    virtual ~GestureGroupModel() = default;

    virtual void Create(int32_t gestureMode) = 0;

private:
    static std::unique_ptr<GestureGroupModel> instance_;
    static std::mutex mutex_;
};

class TimeoutGestureModel {
public:
    static TimeoutGestureModel* GetInstance();
    virtual ~TimeoutGestureModel() = default;

    virtual RefPtr<GestureProcessor> GetGestureProcessor() = 0;

private:
    static std::unique_ptr<TimeoutGestureModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GESTURE_GESTURE_MODEL_H
