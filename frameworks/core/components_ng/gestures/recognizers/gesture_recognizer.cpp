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
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/event/response_ctrl.h"
#include "core/components_ng/gestures/gesture_referee.h"
#include "core/event/axis_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<EventManager> GetCurrentEventManager()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);

    return context->GetEventManager();
}

RefPtr<GestureReferee> GetCurrentGestureReferee(const RefPtr<NGGestureRecognizer>& recognizer)
{
    auto eventManager = GetCurrentEventManager();
    CHECK_NULL_RETURN(eventManager, nullptr);
    return eventManager->GetGestureRefereeNG(recognizer);
}

} // namespace

struct TransformInstance {
    std::unordered_map<int, TransformConfig> transFormConfig;
    std::unordered_map<int, AncestorNodeInfo> transFormIds;
};

TransformInstance g_emptyInstance;
std::unordered_map<int, TransformInstance> globalTransFormInstance;

std::unordered_map<int, TransformConfig>& NGGestureRecognizer::GetGlobalTransCfg()
{
    auto id = Container::CurrentId();
    auto iter = globalTransFormInstance.find(id);
    if (iter == globalTransFormInstance.end()) {
        return g_emptyInstance.transFormConfig;
    }
    return iter->second.transFormConfig;
}

std::unordered_map<int, AncestorNodeInfo>& NGGestureRecognizer::GetGlobalTransIds()
{
    auto id = Container::CurrentId();
    auto iter = globalTransFormInstance.find(id);
    if (iter == globalTransFormInstance.end()) {
        return g_emptyInstance.transFormIds;
    }
    return iter->second.transFormIds;
}

void NGGestureRecognizer::ResetGlobalTransCfg()
{
    auto id = Container::CurrentId();
    globalTransFormInstance[id].transFormConfig.clear();
    globalTransFormInstance[id].transFormIds.clear();
}

bool NGGestureRecognizer::ShouldResponse()
{
    if (AceType::InstanceOf<RecognizerGroup>(this)) {
        return true;
    }
    auto eventManager = GetCurrentEventManager();
    CHECK_NULL_RETURN(eventManager, true);
    auto frameNode = GetAttachedNode();
    auto ctrl = eventManager->GetResponseCtrl();
    CHECK_NULL_RETURN(ctrl, true);
    if (!ctrl->ShouldResponse(frameNode)) {
        if (refereeState_ != RefereeState::FAIL) {
            Adjudicate(AceType::Claim(this), GestureDisposal::REJECT);
        }
        return false;
    }
    return true;
}

bool NGGestureRecognizer::HandleEvent(const TouchEvent& point)
{
    auto attachedNode = GetAttachedNode();
    if (attachedNode.Invalid()) {
        return true;
    }
    if (!ShouldResponse()) {
        return true;
    }
    switch (point.type) {
        case TouchType::MOVE:
            HandleTouchMoveEvent(point);
            break;
        case TouchType::DOWN: {
            deviceId_ = point.deviceId;
            deviceType_ = point.sourceType;
            auto result = AboutToAddCurrentFingers(point.id);
            if (result) {
                HandleTouchDownEvent(point);
            }
            break;
        }
        case TouchType::UP:
            HandleTouchUpEvent(point);
            currentFingers_--;
            break;
        case TouchType::CANCEL:
            HandleTouchCancelEvent(point);
            currentFingers_--;
            break;
        default:
            break;
    }
    return true;
}

bool NGGestureRecognizer::HandleEvent(const AxisEvent& event)
{
    if (!ShouldResponse()) {
        return true;
    }
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

    auto referee = GetCurrentGestureReferee(recognizer);
    if (!referee) {
        recognizer->OnRejected();
        return;
    }
    referee->Adjudicate(recognizer, disposal);
}

void NGGestureRecognizer::Transform(PointF& localPointF, const WeakPtr<FrameNode>& node, bool isRealTime)
{
    if (node.Invalid()) {
        return;
    }

    std::vector<Matrix4> vTrans {};
    auto host = node.Upgrade();
    CHECK_NULL_VOID(host);

    std::function<Matrix4()> getLocalMatrix;
    if (isRealTime) {
        getLocalMatrix = [&host]()->Matrix4 {
            auto context = host->GetRenderContext();
            CHECK_NULL_RETURN(context, Matrix4::CreateIdentity());
            return context->GetLocalTransformMatrix();
        };
    } else {
        getLocalMatrix = [&host]()->Matrix4 {
            return host->GetLocalMatrix();
        };
    }

    while (host) {
        auto localMat = getLocalMatrix();
        vTrans.emplace_back(localMat);
        //when the InjectPointerEvent is invoked, need to enter the lowest windowscene.
        if (host->GetTag() == V2::WINDOW_SCENE_ETS_TAG) {
            TAG_LOGD(AceLogTag::ACE_GESTURE, "need to break when inject WindowsScene, id:%{public}d", host->GetId());
            break;
        }
        host = host->GetAncestorNodeOfFrame();
    }

    Point temp(localPointF.GetX(), localPointF.GetY());
    for (auto iter = vTrans.rbegin(); iter != vTrans.rend(); iter++) {
        temp = *iter * temp;
    }
    localPointF.SetX(temp.GetX());
    localPointF.SetY(temp.GetY());
}

void NGGestureRecognizer::SetTransInfo(int transId)
{
    transId_ = transId;
}

void NGGestureRecognizer::AboutToAccept()
{
    if (AceType::InstanceOf<RecognizerGroup>(this)) {
        OnAccepted();
        return;
    }

    auto eventManager = GetCurrentEventManager();
    CHECK_NULL_VOID(eventManager);
    if (fromCardOrUIExtension_) {
        eventManager->SetInnerFlag(true);
    }
    auto frameNode = GetAttachedNode();
    auto ctrl = eventManager->GetResponseCtrl();
    CHECK_NULL_VOID(ctrl);
    if (!ctrl->ShouldResponse(frameNode)) {
        return;
    }
    ctrl->TrySetFirstResponse(frameNode);
    OnAccepted();
}

RefPtr<GestureSnapshot> NGGestureRecognizer::Dump() const
{
    RefPtr<GestureSnapshot> info = TouchEventTarget::Dump();
    auto group = gestureGroup_.Upgrade();
    if (group) {
        info->parentId = reinterpret_cast<uintptr_t>(AceType::RawPtr(group));
    }
    return info;
}

void NGGestureRecognizer::AddGestureProcedure(const std::string& procedure) const
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto eventMgr = context->GetEventManager();
    CHECK_NULL_VOID(eventMgr);
    eventMgr->GetEventTreeRecord().AddGestureProcedure(
        reinterpret_cast<uintptr_t>(this),
        procedure,
        TransRefereeState(this->GetRefereeState()),
        TransGestureDisposal(this->GetGestureDisposal()));
}

void NGGestureRecognizer::AddGestureProcedure(const TouchEvent& point,
    const RefPtr<NGGestureRecognizer>& recognizer) const
{
    if (!recognizer) {
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto eventMgr = context->GetEventManager();
    CHECK_NULL_VOID(eventMgr);
    eventMgr->GetEventTreeRecord().AddGestureProcedure(
        reinterpret_cast<uintptr_t>(AceType::RawPtr(recognizer)),
        point,
        TransRefereeState(recognizer->GetRefereeState()),
        TransGestureDisposal(recognizer->GetGestureDisposal()));
}

bool NGGestureRecognizer::SetGestureGroup(const WeakPtr<NGGestureRecognizer>& gestureGroup)
{
    if (!gestureGroup_.Invalid() && !gestureGroup.Invalid()) {
        return false;
    }

    gestureGroup_ = gestureGroup;
    return true;
}

} // namespace OHOS::Ace::NG
