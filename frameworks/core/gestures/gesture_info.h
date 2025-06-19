/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_INFO_H

#include <functional>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "base/geometry/matrix4.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/event_callback.h"
#include "base/utils/macros.h"
#include "base/utils/type_definition.h"
#include "core/event/ace_events.h"
#include "core/gestures/velocity.h"

namespace OHOS::Ace {

constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
constexpr Dimension DRAG_PAN_DISTANCE_MOUSE = 1.0_vp;
constexpr Dimension DEFAULT_SLIDE_DISTANCE = DEFAULT_PAN_DISTANCE;
constexpr Dimension DEFAULT_PEN_PAN_DISTANCE = 8.0_vp;
constexpr int32_t DEFAULT_SLIDE_FINGER = DEFAULT_PAN_FINGER;
constexpr double DEFAULT_SLIDE_SPEED = 300.0;
constexpr int32_t DEFAULT_LONG_PRESS_DURATION = 100;

class GestureRecognizer;
class PipelineBase;

struct TransformConfig {
    double scaleX = 1.0;
    double scaleY = 1.0;
    double centerX = 0.0;
    double centerY = 0.0;
    double offsetX = 0.0;
    double offsetY = 0.0;
    double translateX = 0.0;
    double translateY = 0.0;
    double degree = 0.0;
    int id = -1;
    Matrix4 localMat;
    bool operator==(TransformConfig tc)
    {
        return scaleX = tc.scaleX && scaleY == tc.scaleY && centerX == tc.centerX && centerY == tc.centerY &&
                        offsetX == tc.offsetX && offsetY == tc.offsetY && translateX == tc.translateX &&
                        translateY == tc.translateY && degree == tc.degree;
    }
};

struct AncestorNodeInfo {
    int parentId = 0;
};

enum class GesturePriority {
    Begin = -1,
    Low = 0,
    High,
    Parallel,
    End,
};

enum class GestureMask {
    Begin = -1,
    Normal = 0,
    IgnoreInternal,
    End,
};

enum class GestureMode {
    Begin = -1,
    Sequence = 0,
    Parallel,
    Exclusive,
    End,
};

enum class Direction {
    BEGIN = -1,
    ALL = 0,
    HORIZONTAL,
    VERTICAL,
    END,
};

enum class DragEventAction {
    DRAG_EVENT_START = 0,
    DRAG_EVENT_MOVE,
    DRAG_EVENT_END,
    DRAG_EVENT_OUT,
    DRAG_EVENT_START_FOR_CONTROLLER,
    DRAG_EVENT_PULL_CANCEL,
    DRAG_EVENT_PULL_THROW,
};

enum class InputEventType {
    TOUCH_SCREEN = 0,
    TOUCH_PAD,
    MOUSE_BUTTON,
    AXIS,
    KEYBOARD,
};

struct PanDirection final {
    static constexpr uint32_t NONE = 0;
    static constexpr uint32_t LEFT = 1;
    static constexpr uint32_t RIGHT = 2;
    static constexpr uint32_t HORIZONTAL = 3;
    static constexpr uint32_t UP = 4;
    static constexpr uint32_t DOWN = 8;
    static constexpr uint32_t VERTICAL = 12;
    static constexpr uint32_t ALL = 15;

    uint32_t type = ALL;
};

using OnPanFingersFunc = EventCallback<void(int32_t fingers)>;
using PanFingersFuncType = OnPanFingersFunc::FunctionType;
using OnPanDirectionFunc = EventCallback<void(const PanDirection& direction)>;
using PanDirectionFuncType = OnPanDirectionFunc::FunctionType;
using OnPanDistanceFunc = EventCallback<void(double distance)>;
using PanDistanceFuncType = OnPanDistanceFunc::FunctionType;
using PanDistanceMap = std::unordered_map<SourceTool, double>;
using PanDistanceMapDimension = std::unordered_map<SourceTool, Dimension>;

class PanGestureOption : public AceType {
    DECLARE_ACE_TYPE(PanGestureOption, AceType);

public:
    PanGestureOption() = default;
    ~PanGestureOption() override = default;

    void SetDirection(PanDirection direction)
    {
        direction_ = direction;
        for (const auto& callback : onPanDirectionIds_) {
            (callback.second.GetCallback())(direction);
        }
    }

    const PanDirection& GetDirection() const
    {
        return direction_;
    }

    void SetDistance(double distance)
    {
        distance_ = distance;
        distanceMap_[SourceTool::UNKNOWN] = Dimension(distance_, DimensionUnit::PX);
        for (const auto& callback : onPanDistanceIds_) {
            (callback.second.GetCallback())(distance);
        }
    }

    void SetDistanceMap(const PanDistanceMapDimension& distanceMap)
    {
        distanceMap_ = distanceMap;
    }

    const PanDistanceMapDimension& GetPanDistanceMap() const
    {
        return distanceMap_;
    }

    double GetDistance() const
    {
        return distance_;
    }

    void SetFingers(int32_t fingers)
    {
        fingers_ = fingers;
        for (const auto& callback : onPanFingersIds_) {
            (callback.second.GetCallback())(fingers);
        }
    }

    int32_t GetFingers() const
    {
        return fingers_;
    }

    void SetIsLimitFingerCount(bool isLimitFingerCount)
    {
        isLimitFingerCount_ = isLimitFingerCount;
    }

    bool GetIsLimitFingerCount() const
    {
        return isLimitFingerCount_;
    }

    std::unordered_map<typename OnPanFingersFunc::IdType, OnPanFingersFunc>& GetOnPanFingersIds()
    {
        return onPanFingersIds_;
    }

    void SetOnPanFingersId(const OnPanFingersFunc& onPanFingersId)
    {
        onPanFingersIds_.emplace(onPanFingersId.GetId(), onPanFingersId);
    }

    std::unordered_map<typename OnPanDirectionFunc::IdType, OnPanDirectionFunc>& GetOnPanDirectionIds()
    {
        return onPanDirectionIds_;
    }

    void SetOnPanDirectionId(const OnPanDirectionFunc& onPanDirectionId)
    {
        onPanDirectionIds_.emplace(onPanDirectionId.GetId(), onPanDirectionId);
    }

    std::unordered_map<typename OnPanDistanceFunc::IdType, OnPanDistanceFunc>& GetOnPanDistanceIds()
    {
        return onPanDistanceIds_;
    }

    void SetOnPanDistanceId(const OnPanDistanceFunc& onPanDistanceId)
    {
        onPanDistanceIds_.emplace(onPanDistanceId.GetId(), onPanDistanceId);
    }
    
private:
    PanDirection direction_;
    double distance_ = DEFAULT_PAN_DISTANCE.ConvertToPx();
    PanDistanceMapDimension distanceMap_;
    int32_t fingers_ = 1;
    bool isLimitFingerCount_ = false;
    std::unordered_map<typename OnPanFingersFunc::IdType, OnPanFingersFunc> onPanFingersIds_;
    std::unordered_map<typename OnPanDirectionFunc::IdType, OnPanDirectionFunc> onPanDirectionIds_;
    std::unordered_map<typename OnPanDistanceFunc::IdType, OnPanDistanceFunc> onPanDistanceIds_;
};

struct SwipeDirection final {
    static constexpr uint32_t NONE = 0;
    static constexpr uint32_t HORIZONTAL = 1;
    static constexpr uint32_t VERTICAL = 2;
    static constexpr uint32_t ALL = 3;

    uint32_t type = ALL;
};
using OnSwipeFingersFunc = EventCallback<void(int32_t fingers)>;
using SwipeFingersFuncType = OnSwipeFingersFunc::FunctionType;
using OnSwipeDirectionFunc = EventCallback<void(const SwipeDirection& direction)>;
using SwipeDirectionFuncType = OnSwipeDirectionFunc::FunctionType;
using OnSwipeSpeedFunc = EventCallback<void(double speed)>;
using SwipeSpeedFuncType = OnSwipeSpeedFunc::FunctionType;

struct FingerInfo {
    int32_t fingerId_ = -1;
    int32_t operatingHand_ = 0;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;

    //screen position at which the touch point contacts the screen.
    Offset screenLocation_;
    // The location where the touch point touches the screen when there are multiple screens.
    Offset globalDisplayLocation_;
    SourceType sourceType_ = SourceType::NONE;
    SourceTool sourceTool_ = SourceTool::UNKNOWN;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_INFO_H
