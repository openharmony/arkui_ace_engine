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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GESTURE_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GESTURE_MODEL_IMPL_H

#include "core/components_ng/pattern/gesture/gesture_model.h"
#include "core/components_ng/gestures/gesture_info.h"

namespace OHOS::Ace::Framework {
class GestureModelImpl : public OHOS::Ace::GestureModel {
public:
    void Create(int32_t priorityNum, int32_t gestureMaskNum) override;
    void Finish() override;
    void Pop() override;
    void SetOnGestureEvent(const GestureEventFunc& gestureEventFunc) override;
    void SetOnActionFunc(const GestureEventFunc& gestureEventFunc, const Ace::GestureEventAction& action) override;
    void SetTag(const std::string& tag) override {}
    void SetAllowedTypes(const std::set<SourceTool>& allowedTypes) override {}
};

class TapGestureModelImpl : public OHOS::Ace::TapGestureModel {
public:
    void Create(int32_t countNum, int32_t fingersNum, double distanceThreshold, bool isLimitFingerCount) override;
};

class LongPressGestureModelImpl : public OHOS::Ace::LongPressGestureModel {
public:
    void Create(int32_t fingersNum, bool repeatResult, int32_t durationNum, bool isLimitFingerCount) override;
};

class PanGestureModelImpl : public OHOS::Ace::PanGestureModel {
public:
    void Create(
        int32_t fingersNum, const PanDirection& panDirection, double distanceNum, bool isLimitFingerCount) override;
    void Create(int32_t fingersNum, const PanDirection& panDirection, const PanDistanceMapDimension& distanceMap,
        bool isLimitFingerCount) override;
    void SetPanGestureOption(const RefPtr<PanGestureOption>& panGestureOption) override;
};

class SwipeGestureModelImpl : public OHOS::Ace::SwipeGestureModel {
public:
    void Create(int32_t fingersNum, const SwipeDirection& slideDirection,
        const Dimension& speedNum, bool isLimitFingerCount) override;
};

class PinchGestureModelImpl : public OHOS::Ace::PinchGestureModel {
public:
    void Create(int32_t fingersNum, double distanceNum, bool isLimitFingerCount) override;
};

class RotationGestureModelImpl : public OHOS::Ace::RotationGestureModel {
public:
    void Create(int32_t fingersNum, double angleNum, bool isLimitFingerCount) override;
};

class GestureGroupModelImpl : public OHOS::Ace::GestureGroupModel {
public:
    void Create(int32_t gestureMode) override;
};

class ACE_EXPORT TimeoutGestureModelImpl : public OHOS::Ace::TimeoutGestureModel {
public:
    RefPtr<GestureProcessor> GetGestureProcessor() override;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GESTURE_MODEL_IMPL_H
