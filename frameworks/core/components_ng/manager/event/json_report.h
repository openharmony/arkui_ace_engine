/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_EVENT_JSON_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_EVENT_JSON_REPORT_H

#include <functional>
#include <limits>

#include "interfaces/inner_api/ace_kit/include/ui/base/geometry/point.h"
#include "interfaces/inner_api/ui_session/ui_session_json_util.h"

#include "core/components/common/layout/constants.h"
#include "frameworks/core/components_ng/event/event_constants.h"
#include "frameworks/core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {

class JsonReport {
public:
    virtual std::shared_ptr<InspectorJsonValue> GetJsonData() const
    {
        return nullptr;
    };
    void SetGestureType(GestureTypeName gestureType)
    {
        gestureType_ = gestureType;
    }

    GestureTypeName GetGestureType() const
    {
        return gestureType_;
    }

    void SetCallbackType(GestureCallbackType callBackType)
    {
        callBackType_ = callBackType;
    }

    GestureCallbackType GetCallBackType() const
    {
        return callBackType_;
    }

    void SetId(int32_t id)
    {
        id_ = id;
    }

    int32_t GetId() const
    {
        return id_;
    }

    void SetPoint(Point point)
    {
        point_ = point;
    }

    Point GetPoint() const
    {
        return point_;
    }

    void SetFingerList(std::list<FingerInfo> fingerList)
    {
        fingerList_ = fingerList;
    }

    const std::list<FingerInfo>& GetFingerList() const
    {
        return fingerList_;
    }

private:
    GestureTypeName gestureType_ = GestureTypeName::UNKNOWN;
    GestureCallbackType callBackType_ = GestureCallbackType::ACTION;
    int32_t id_ = -1;
    Point point_;
    std::list<FingerInfo> fingerList_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_EVENT_JSON_REPORT_H