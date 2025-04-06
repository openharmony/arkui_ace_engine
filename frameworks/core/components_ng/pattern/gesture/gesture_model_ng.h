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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GESTURE_GESTURE_VIEW_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GESTURE_GESTURE_VIEW_MODEL_NG_H

#include "core/components_ng/pattern/gesture/gesture_model.h"
#include "frameworks/base/utils/macros.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GestureModelNG : public OHOS::Ace::GestureModel {
public:
    void Create(int32_t priorityNum, int32_t gestureMaskNum) override;
    void Finish() override;
    void Pop() override;
    void SetOnGestureEvent(const GestureEventFunc& gestureEventFunc) override;
    void SetOnActionFunc(const GestureEventFunc& gestureEventFunc, const Ace::GestureEventAction& action) override;
    void SetTag(const std::string& tag) override;
    void SetAllowedTypes(const std::set<SourceTool>& allowedTypes) override;
};

class ACE_EXPORT TapGestureModelNG : public OHOS::Ace::TapGestureModel {
public:
    void Create(int32_t countNum, int32_t fingersNum,
        double distanceThreshold = std::numeric_limits<double>::infinity(), bool isLimitFingerCount = false) override;
};

class ACE_EXPORT LongPressGestureModelNG : public OHOS::Ace::LongPressGestureModel {
public:
    void Create(int32_t fingersNum, bool repeatResult, int32_t durationNum, bool isLimitFingerCount = false) override;
};

class ACE_EXPORT PanGestureModelNG : public OHOS::Ace::PanGestureModel {
public:
    void Create(int32_t fingersNum, const PanDirection& panDirection, double distanceNum,
        bool isLimitFingerCount = false) override;
    void Create(int32_t fingersNum, const PanDirection& panDirection, const PanDistanceMap& distanceMap,
        bool isLimitFingerCount) override;
    void SetPanGestureOption(const RefPtr<PanGestureOption>& panGestureOption) override;
};

class ACE_EXPORT SwipeGestureModelNG : public OHOS::Ace::SwipeGestureModel {
public:
    void Create(int32_t fingersNum, const SwipeDirection& slideDirection, double speedNum,
        bool isLimitFingerCount = false) override;
};

class ACE_EXPORT PinchGestureModelNG : public OHOS::Ace::PinchGestureModel {
public:
    void Create(int32_t fingersNum, double distanceNum, bool isLimitFingerCount = false) override;
};

class ACE_EXPORT RotationGestureModelNG : public OHOS::Ace::RotationGestureModel {
public:
    void Create(int32_t fingersNum, double angleNum, bool isLimitFingerCount = false) override;
};

class ACE_EXPORT GestureGroupModelNG : public OHOS::Ace::GestureGroupModel {
public:
    void Create(int32_t gestureMode) override;
};

class ACE_EXPORT TimeoutGestureModelNG : public OHOS::Ace::TimeoutGestureModel {
public:
    RefPtr<GestureProcessor> GetGestureProcessor() override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GESTURE_GESTURE_VIEW_MODEL_NG_H
