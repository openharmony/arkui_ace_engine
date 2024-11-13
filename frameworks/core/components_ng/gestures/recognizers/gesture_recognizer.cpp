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

#include "core/components_ng/base/observer_handler.h"

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

bool NGGestureRecognizer::IsAllowedType(SourceTool type)
{
    // allow all types by default
    if (!gestureInfo_) {
        return true;
    }

    auto allowedTypes = gestureInfo_->GetAllowedTypes();
    return allowedTypes.empty() || allowedTypes.find(type) != allowedTypes.end();
}

void NGGestureRecognizer::OnRejectBridgeObj()
{
    if (bridgeObjList_.empty()) {
        return;
    }
    for (const auto& item : bridgeObjList_) {
        auto bridgeObj = item.Upgrade();
        if (bridgeObj) {
            bridgeObj->OnRejected();
            bridgeObj->OnRejectBridgeObj();
        }
    }
}

bool NGGestureRecognizer::HandleEvent(const TouchEvent& point)
{
    if (!IsAllowedType(point.sourceTool) && point.type != TouchType::CANCEL) {
        if (point.type == TouchType::DOWN) {
            RemoveUnsupportEvent(point.id);
        }
        return true;
    }
    if (!ShouldResponse() || bridgeMode_) {
        return true;
    }
    switch (point.type) {
        case TouchType::MOVE:
            HandleTouchMoveEvent(point);
            HandleEventToBridgeObjList(point, bridgeObjList_);
            break;
        case TouchType::DOWN: {
            deviceId_ = point.deviceId;
            deviceType_ = point.sourceType;
            inputEventType_ = deviceType_ == SourceType::MOUSE ? InputEventType::MOUSE_BUTTON :
                InputEventType::TOUCH_SCREEN;
            auto result = AboutToAddCurrentFingers(point);
            if (result) {
                HandleTouchDownEvent(point);
                HandleEventToBridgeObjList(point, bridgeObjList_);
            }
            break;
        }
        case TouchType::UP: {
            auto result = AboutToMinusCurrentFingers(point.id);
            if (result) {
                HandleTouchUpEvent(point);
                HandleEventToBridgeObjList(point, bridgeObjList_);
                currentFingers_--;
            }
            break;
        }
        case TouchType::CANCEL: {
            auto result = AboutToMinusCurrentFingers(point.id);
            if (result) {
                HandleTouchCancelEvent(point);
                HandleEventToBridgeObjList(point, bridgeObjList_);
                currentFingers_--;
            }
            break;
        }
        default:
            break;
    }
    return true;
}

bool NGGestureRecognizer::HandleEvent(const AxisEvent& event)
{
    if (!IsAllowedType(event.sourceTool) && event.action != AxisAction::CANCEL) {
        if (event.action == AxisAction::BEGIN) {
            RemoveUnsupportEvent(event.id);
        }
        return true;
    }
    if (!ShouldResponse() || bridgeMode_) {
        return true;
    }
    switch (event.action) {
        case AxisAction::BEGIN:
            deviceId_ = event.deviceId;
            deviceType_ = event.sourceType;
            inputEventType_ = InputEventType::AXIS;
            HandleTouchDownEvent(event);
            break;
        case AxisAction::UPDATE:
            HandleTouchMoveEvent(event);
            break;
        case AxisAction::END:
            HandleTouchUpEvent(event);
            break;
        case AxisAction::CANCEL:
            HandleTouchCancelEvent(event);
            break;
        default:
            HandleTouchCancelEvent(event);
            break;
    }
    for (const auto& item : bridgeObjList_) {
        auto bridgeObj = item.Upgrade();
        if (bridgeObj) {
            bridgeObj->HandleBridgeModeEvent(event);
        }
    }
    return true;
}

void NGGestureRecognizer::HandleBridgeModeEvent(const TouchEvent& point)
{
    switch (point.type) {
        case TouchType::MOVE:
            HandleTouchMoveEvent(point);
            HandleEventToBridgeObjList(point, bridgeObjList_);
            break;
        case TouchType::DOWN: {
            deviceId_ = point.deviceId;
            deviceType_ = point.sourceType;
            if (deviceType_ == SourceType::MOUSE) {
                inputEventType_ = InputEventType::MOUSE_BUTTON;
            } else {
                inputEventType_ = InputEventType::TOUCH_SCREEN;
            }
            auto result = AboutToAddCurrentFingers(point);
            if (result) {
                HandleTouchDownEvent(point);
                HandleEventToBridgeObjList(point, bridgeObjList_);
            }
            break;
        }
        case TouchType::UP: {
            auto result = AboutToMinusCurrentFingers(point.id);
            if (result) {
                HandleTouchUpEvent(point);
                currentFingers_--;
                HandleEventToBridgeObjList(point, bridgeObjList_);
            }
            break;
        }
        case TouchType::CANCEL: {
            auto result = AboutToMinusCurrentFingers(point.id);
            if (result) {
                HandleTouchCancelEvent(point);
                currentFingers_--;
                HandleEventToBridgeObjList(point, bridgeObjList_);
            }
            break;
        }
        default:
            break;
    }
}

void NGGestureRecognizer::HandleEventToBridgeObjList(
    const TouchEvent& point, const std::list<WeakPtr<NGGestureRecognizer>>& bridgeObjList)
{
    for (const auto& item : bridgeObjList) {
        auto bridgeObj = item.Upgrade();
        if (bridgeObj) {
            bridgeObj->HandleBridgeModeEvent(point);
        }
    }
}

void NGGestureRecognizer::HandleBridgeModeEvent(const AxisEvent& event)
{
    switch (event.action) {
        case AxisAction::BEGIN:
            deviceId_ = event.deviceId;
            deviceType_ = event.sourceType;
            inputEventType_ = InputEventType::AXIS;
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
    for (const auto& item : bridgeObjList_) {
        auto bridgeObj = item.Upgrade();
        if (bridgeObj) {
            bridgeObj->HandleBridgeModeEvent(event);
        }
    }
}

void NGGestureRecognizer::BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal)
{
    RefPtr<NGGestureRecognizer> gestureGroup;
    if (!eventImportGestureGroup_.Invalid()) {
        gestureGroup = eventImportGestureGroup_.Upgrade();
    } else {
        gestureGroup = gestureGroup_.Upgrade();
    }
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

void NGGestureRecognizer::Transform(PointF& localPointF, const WeakPtr<FrameNode>& node, bool isRealTime,
    bool isPostEventResult, int32_t postEventNodeId)
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
        if ((postEventNodeId == host->GetId()) && isPostEventResult) {
            TAG_LOGD(AceLogTag::ACE_GESTURE, "need to break when used in NodeContainer, id:%{public}d", host->GetId());
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
        HandleWillAccept();
        OnAccepted();
        HandleDidAccept();
        return;
    }

    auto eventManager = GetCurrentEventManager();
    CHECK_NULL_VOID(eventManager);
    auto frameNode = GetAttachedNode();
    auto ctrl = eventManager->GetResponseCtrl();
    CHECK_NULL_VOID(ctrl);
    if (!ctrl->ShouldResponse(frameNode)) {
        return;
    }
    if (fromCardOrUIExtension_) {
        eventManager->SetInnerFlag(true);
    } else {
        eventManager->SetInnerFlag(false);
    }
    ctrl->TrySetFirstResponse(frameNode);
    HandleWillAccept();
    OnAccepted();
    HandleDidAccept();
}

void NGGestureRecognizer::HandleWillAccept()
{
    auto node = GetAttachedNode().Upgrade();
    if (AceType::InstanceOf<ClickRecognizer>(this)) {
        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(this);
        CHECK_NULL_VOID(clickRecognizer);
        GestureEvent gestureEventInfo = clickRecognizer->GetGestureEventInfo();
        ClickInfo clickInfo = clickRecognizer->GetClickInfo();
        UIObserverHandler::GetInstance().NotifyWillClick(gestureEventInfo, clickInfo, node);
    }
}

void NGGestureRecognizer::HandleDidAccept()
{
    auto node = GetAttachedNode().Upgrade();
    if (AceType::InstanceOf<ClickRecognizer>(this)) {
        auto clickRecognizer = AceType::DynamicCast<ClickRecognizer>(this);
        CHECK_NULL_VOID(clickRecognizer);
        GestureEvent gestureEventInfo = clickRecognizer->GetGestureEventInfo();
        ClickInfo clickInfo = clickRecognizer->GetClickInfo();
        UIObserverHandler::GetInstance().NotifyDidClick(gestureEventInfo, clickInfo, node);
    }
}

void NGGestureRecognizer::ReconcileGestureInfoFrom(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);
    auto currGestureInfo = recognizer->GetGestureInfo();
    if (gestureInfo_ && currGestureInfo) {
        gestureInfo_->SetAllowedTypes(currGestureInfo->GetAllowedTypes());
    }
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
    eventMgr->GetEventTreeRecord(isPostEventResult_ ? EventTreeType::POST_EVENT : EventTreeType::TOUCH)
        .AddGestureProcedure(reinterpret_cast<uintptr_t>(this), procedure, TransRefereeState(this->GetRefereeState()),
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
    eventMgr->GetEventTreeRecord(isPostEventResult_ ? EventTreeType::POST_EVENT : EventTreeType::TOUCH)
        .AddGestureProcedure(reinterpret_cast<uintptr_t>(AceType::RawPtr(recognizer)), point,
            TransRefereeState(recognizer->GetRefereeState()), TransGestureDisposal(recognizer->GetGestureDisposal()));
}

bool NGGestureRecognizer::SetGestureGroup(const WeakPtr<NGGestureRecognizer>& gestureGroup)
{
    if (!gestureGroup_.Invalid() && !gestureGroup.Invalid()) {
        return false;
    }

    gestureGroup_ = gestureGroup;
    return true;
}

void NGGestureRecognizer::SetEventImportGestureGroup(const WeakPtr<NGGestureRecognizer>& gestureGroup)
{
    if (gestureGroup.Invalid()) {
        return;
    }

    eventImportGestureGroup_ = gestureGroup;
}

bool NGGestureRecognizer::IsInAttachedNode(const TouchEvent& event, bool isRealTime)
{
    bool isChildTouchTestResult = false;
    auto frameNode = GetAttachedNode();
    if (frameNode.Invalid()) {
        return true;
    }
    auto host = frameNode.Upgrade();
    CHECK_NULL_RETURN(host, true);
    auto id = host->GetInspectorIdValue("");
    isChildTouchTestResult = std::any_of(event.childTouchTestList.begin(), event.childTouchTestList.end(),
        [id](const std::string& inspectorId) {
            return inspectorId == id;
        });
    if (isChildTouchTestResult) {
        return true;
    }

    PointF localPoint(event.x, event.y);
    if (isRealTime) {
        NGGestureRecognizer::Transform(localPoint, frameNode, !isPostEventResult_,
            isPostEventResult_, event.postEventNodeId);
    } else {
        NGGestureRecognizer::Transform(localPoint, frameNode, false,
            isPostEventResult_, event.postEventNodeId);
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto paintRect = renderContext->GetPaintRectWithoutTransform();
    localPoint = localPoint + paintRect.GetOffset();
    auto responseRegion = host->GetResponseRegionListForRecognizer(static_cast<int32_t>(event.sourceType));
    auto result = host->InResponseRegionList(localPoint, responseRegion);
    if (!result) {
        std::string responseInfo = std::string("responseRegionList = ");
        for (const auto& item : responseRegion) {
            responseInfo.append(item.ToString()).append("; ");
        }
        TAG_LOGW(AceLogTag::ACE_GESTURE,
            "%{public}s IsInAttachedNode result is negative, node tag = %{public}s, id = %{public}s, point = "
            "%{public}s, frameRect = %{public}s, %{public}s",
            AceType::TypeName(this), host->GetTag().c_str(), std::to_string(host->GetId()).c_str(),
            localPoint.ToString().c_str(), host->GetFrameRectWithoutSafeArea().ToString().c_str(),
            responseInfo.c_str());
    }
    return result;
}

void NGGestureRecognizer::SetResponseLinkRecognizers(const ResponseLinkResult& responseLinkResult)
{
    responseLinkRecognizer_ = responseLinkResult;
}

bool NGGestureRecognizer::IsInResponseLinkRecognizers()
{
    return std::any_of(responseLinkRecognizer_.begin(), responseLinkRecognizer_.end(),
        [recognizer = Claim(this)](const RefPtr<NGGestureRecognizer>& item) { return item == recognizer; });
}

bool NGGestureRecognizer::AboutToAddCurrentFingers(const TouchEvent& event)
{
    bool isInAttachedNode = IsInAttachedNode(event, !AceType::InstanceOf<ClickRecognizer>(this));
    if (!isInAttachedNode) {
        return false;
    }
    if (fingersId_.find(event.id) != fingersId_.end()) {
        auto node = GetAttachedNode().Upgrade();
        TAG_LOGI(AceLogTag::ACE_GESTURE,
            "Recognizer has already receive touchId: %{public}d event, node tag = %{public}s, id = %{public}s",
            event.id, node ? node->GetTag().c_str() : "null",
            node ? std::to_string(node->GetId()).c_str() : "invalid");
        return false;
    }
    currentFingers_++;
    return true;
}

bool NGGestureRecognizer::AboutToMinusCurrentFingers(int32_t touchId)
{
    if (fingersId_.find(touchId) != fingersId_.end()) {
        return true;
    }
    auto node = GetAttachedNode().Upgrade();
    TAG_LOGI(AceLogTag::ACE_GESTURE,
        "Recognizer has already receive touchId: %{public}d up event, node tag = %{public}s, id = %{public}s",
        touchId, node ? node->GetTag().c_str() : "null",
        node ? std::to_string(node->GetId()).c_str() : "invalid");
    return false;
}
} // namespace OHOS::Ace::NG
