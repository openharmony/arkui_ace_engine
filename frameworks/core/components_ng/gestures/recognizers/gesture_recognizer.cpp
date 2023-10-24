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
    CHECK_NULL_RETURN(eventManager, nullptr);
    return eventManager->GetGestureRefereeNG();
}

} // namespace

std::unordered_map<int, TransformConfig> globalTransFormConfig;
std::unordered_map<int, AncestorNodeInfo> globalTransFormIds;

std::unordered_map<int, TransformConfig>& NGGestureRecognizer::GetGlobalTransCfg()
{
    return globalTransFormConfig;
}

std::unordered_map<int, AncestorNodeInfo>& NGGestureRecognizer::GetGlobalTransIds()
{
    return globalTransFormIds;
}

void NGGestureRecognizer::ResetGlobalTransCfg()
{
    globalTransFormConfig.clear();
    globalTransFormIds.clear();
}

bool NGGestureRecognizer::HandleEvent(const TouchEvent& point)
{
    switch (point.type) {
        case TouchType::MOVE:
            HandleTouchMoveEvent(point);
            break;
        case TouchType::DOWN:
            deviceId_ = point.deviceId;
            deviceType_ = point.sourceType;
            currentFingers_++;
            HandleTouchDownEvent(point);
            break;
        case TouchType::UP:
            HandleTouchUpEvent(point);
            currentFingers_--;
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

bool NGGestureRecognizer::HandleEvent(const AxisEvent& event)
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
            // When scroll one step. Axis events are 'BEGIN' and 'END'. So it's need to do 'UPDATE' before 'END'.
            HandleTouchMoveEvent(event);
            HandleTouchUpEvent(event);
            break;
        default:
            HandleTouchCancelEvent(event);
            LOGW("unknown touch type");
            break;
    }
    return true;
}

void NGGestureRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
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

void NGGestureRecognizer::Transform(PointF& localPointF, int id)
{
    auto& translateCfg = NGGestureRecognizer::GetGlobalTransCfg();
    auto& translateIds = NGGestureRecognizer::GetGlobalTransIds();

    auto translateIter = translateIds.find(id);
    if (translateIter == translateIds.end()) {
        return;
    }
    std::vector<int32_t> vTrans {};
    vTrans.emplace_back(id);
    while (translateIter != translateIds.end()) {
        int32_t translateId = translateIter->second.parentId;
        if (translateCfg.find(translateId) != translateCfg.end()) {
            vTrans.emplace_back(translateId);
        }
        translateIter = translateIds.find(translateId);
    }

    Point temp(localPointF.GetX(), localPointF.GetY());
    for (auto iter = vTrans.rbegin(); iter != vTrans.rend(); iter++) {
        auto& trans = translateCfg[*iter];
        temp = trans.localMat * temp;
    }
    localPointF.SetX(temp.GetX());
    localPointF.SetY(temp.GetY());
}

void NGGestureRecognizer::SetTransInfo(int transId)
{
    transId_ = transId;
}
} // namespace OHOS::Ace::NG
