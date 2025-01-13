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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_FORM_GESTURE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_FORM_GESTURE_MANAGER_H

#include <unordered_map>

#include "base/memory/ace_type.h"
#include "core/event/touch_event.h"
#include "interfaces/inner_api/ace/serialized_gesture.h"
#include "core/common/event_manager.h"

namespace OHOS::Ace {
namespace NG {

class PipelineContext;

class FormGestureManager : public virtual AceType {
    DECLARE_ACE_TYPE(FormGestureManager, AceType);
public:
    FormGestureManager() = default;

    ~FormGestureManager() override = default;

    void LinkGesture(const AxisEvent& event, PipelineContext* pipeline, const RefPtr<FrameNode>& node,
        std::unordered_map<size_t, TouchTestResult>& axisTouchTestResults, SerializedGesture& etsSerializedGesture,
        RefPtr<EventManager>& eventManager);
};

} // namespace OHOS::Ace
} // namespace OHOS::Ace::NG
#endif //FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_FORM_GESTURE_MANAGER_H

