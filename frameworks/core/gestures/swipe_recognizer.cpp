/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/gestures/swipe_recognizer.h"

#include "base/json/json_util.h"
#include "base/log/log.h"

namespace OHOS::Ace {
namespace {

SwipeEventInfo::SwipeDirection GetSwipeDirection(const TouchPoint& firstPoint, const TouchPoint& lastPoint)
{
    static const double duration = 15.0;
    auto xOffset = lastPoint.x - firstPoint.x;
    auto yOffset = lastPoint.y - firstPoint.y;
    if (std::abs(xOffset) > std::abs(yOffset)) {
        if (std::abs(xOffset) < duration) {
            return SwipeEventInfo::SwipeDirection::NONE;
        }
        return xOffset > 0.0 ? SwipeEventInfo::SwipeDirection::RIGHT : SwipeEventInfo::SwipeDirection::LEFT;
    } else {
        if (std::abs(yOffset) < duration) {
            return SwipeEventInfo::SwipeDirection::NONE;
        }
        return yOffset > 0.0 ? SwipeEventInfo::SwipeDirection::DOWN : SwipeEventInfo::SwipeDirection::UP;
    }
}

} // namespace

std::string SwipeEventInfo::ToJsonParamInfo() const
{
    static std::unordered_map<SwipeEventInfo::SwipeDirection, std::string> conventMap {
        { SwipeEventInfo::SwipeDirection::RIGHT, "right" },
        { SwipeEventInfo::SwipeDirection::LEFT, "left" },
        { SwipeEventInfo::SwipeDirection::UP, "up" },
        { SwipeEventInfo::SwipeDirection::DOWN, "down" },
    };
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("type", GetType().c_str());
    jsonValue->Put("timestamp", static_cast<double>(GetTimeStamp().time_since_epoch().count()));
    jsonValue->Put("direction", conventMap[swipeDirection_].c_str());
    return jsonValue->ToString();
}

bool SwipeRecognizer::HandleEvent(const TouchPoint& point)
{
    switch (point.type) {
        case TouchType::DOWN: {
            // reset the recognizer status.
            auto& status = statusMap_[point.id];
            status.first = point;
            status.second = false;
            break;
        }
        case TouchType::UP: {
            auto& status = statusMap_[point.id];
            if (status.second && swipeCallback_) {
                auto direction = GetSwipeDirection(status.first, point);
                if (direction == SwipeEventInfo::SwipeDirection::NONE) {
                    return true;
                }
                swipeCallback_(SwipeEventInfo(direction));
            }
            break;
        }
        case TouchType::MOVE: {
            auto& status = statusMap_[point.id];
            status.second = true;
            break;
        }
        case TouchType::CANCEL: {
            auto& status = statusMap_[point.id];
            status.second = false;
            break;
        }
        default:
            LOGW("unknown type point type.");
    }
    return true;
}

bool SwipeRecognizer::DispatchEvent(const TouchPoint& point)
{
    return true;
}

} // namespace OHOS::Ace