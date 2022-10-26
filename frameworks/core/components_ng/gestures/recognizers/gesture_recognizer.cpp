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

#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/event/axis_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

RefPtr<GestureReferee> GetCurrentGestureReferee()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);

    auto eventManager = context->GetEventManager();
    if (!eventManager) {
        return nullptr;
    }
    return eventManager->GetGestureRefereeNG();
}

} // namespace

bool GestureRecognizer::HandleEvent(const TouchEvent& point)
{
    switch (point.type) {
        case TouchType::MOVE:
            HandleTouchMoveEvent(point);
            break;
        case TouchType::DOWN:
            deviceId_ = point.deviceId;
            deviceType_ = point.sourceType;
            HandleTouchDownEvent(point);
            break;
        case TouchType::UP:
            HandleTouchUpEvent(point);
            break;
        case TouchType::CANCEL:
            HandleTouchCancelEvent(point);
            break;
        default:
            LOGW("unknown touch type");
            break;
    }
    return true;
}

bool GestureRecognizer::HandleEvent(const AxisEvent& event)
{
    switch (event.action) {
        case AxisAction::BEGIN:
            deviceId_ = event.deviceId;
            deviceType_ = event.sourceType;
            HandleTouchDownEvent(event);
            break;
        case AxisAction::UPDATE:
            HandleTouchMoveEvent(event);
            break;
        case AxisAction::END:
            HandleTouchUpEvent(event);
            break;
        default:
            HandleTouchCancelEvent(event);
            LOGW("unknown touch type");
            break;
    }
    return true;
}

void GestureRecognizer::BatchAdjudicate(const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal)
{
    auto gestureGroup = gestureGroup_.Upgrade();
    if (gestureGroup) {
        gestureGroup->Adjudicate(recognizer, disposal);
        return;
    }

    auto referee = GetCurrentGestureReferee();
    if (!referee) {
        LOGW("the referee is nullptr");
        recognizer->OnRejected();
        return;
    }
    referee->Adjudicate(recognizer, disposal);
}
} // namespace OHOS::Ace::NG
