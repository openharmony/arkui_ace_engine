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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_gesture_judge_function.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_should_built_in_recognizer_parallel_with_function.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::Framework {
constexpr int32_t PARAM_COUNT_THREE = 3;
constexpr int32_t PARAM_COUNT_FOUR = 4;

GestureJudgeResult JsGestureJudgeFunction::Execute(
    const RefPtr<NG::GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info)
{
    JSRef<JSObject> gestureInfoObj = JSRef<JSObject>::New();
    CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
    CHECK_NULL_RETURN(info, GestureJudgeResult::CONTINUE);
    if (gestureInfo->GetTag().has_value()) {
        gestureInfoObj->SetProperty<std::string>("tag", gestureInfo->GetTag().value());
    }
    gestureInfoObj->SetProperty<int32_t>("type", static_cast<int32_t>(gestureInfo->GetType()));
    gestureInfoObj->SetProperty<bool>("isSystemGesture", gestureInfo->IsSystemGesture());
    gestureInfoObj->SetProperty<int32_t>("targetDisplayId", info->GetTargetDisplayId());
    auto obj = CreateGestureEventObject(info, gestureInfo->GetType());
    int32_t paramCount = 2;
    JSRef<JSVal> params[paramCount];
    params[0] = gestureInfoObj;
    params[1] = obj;
    auto jsValue = JsFunction::ExecuteJS(paramCount, params);
    auto returnValue = GestureJudgeResult::CONTINUE;
    if (jsValue->IsNumber()) {
        returnValue = static_cast<GestureJudgeResult>(jsValue->ToNumber<int32_t>());
    }
    return returnValue;
}

GestureJudgeResult JsGestureJudgeFunction::Execute(const std::shared_ptr<BaseGestureEvent>& info,
    const RefPtr<NG::NGGestureRecognizer>& current, const std::list<RefPtr<NG::NGGestureRecognizer>>& others)
{
    CHECK_NULL_RETURN(info, GestureJudgeResult::CONTINUE);
    auto gestureInfo = current->GetGestureInfo();
    CHECK_NULL_RETURN(gestureInfo, GestureJudgeResult::CONTINUE);
    auto obj = CreateGestureEventObject(info, gestureInfo->GetRecognizerType());
    JSRef<JSVal> params[PARAM_COUNT_FOUR];
    params[0] = obj;
    auto currentObj = JsShouldBuiltInRecognizerParallelWithFunction::CreateRecognizerObject(current);
    params[1] = currentObj;
    JSRef<JSArray> othersArr = JSRef<JSArray>::New();
    uint32_t othersIdx = 0;
    for (const auto& item : others) {
        auto othersObj = JsShouldBuiltInRecognizerParallelWithFunction::CreateRecognizerObject(item);
        othersArr->SetValueAt(othersIdx++, othersObj);
    }

    auto touchRecognizerMap = CreateTouchRecognizerMap(info, current);
    JSRef<JSArray> touchRecognizers = JSRef<JSArray>::New();
    uint32_t touchRecognizersIdx = 0;
    for (auto& [item, fingerIds] : touchRecognizerMap) {
        JSRef<JSObject> recognizerObj = JSClass<JSTouchRecognizer>::NewInstance();
        auto jsRecognizer = Referenced::Claim(recognizerObj->Unwrap<JSTouchRecognizer>());
        if (jsRecognizer) {
            jsRecognizer->SetTouchData(item, fingerIds);
        }
        touchRecognizers->SetValueAt(touchRecognizersIdx++, recognizerObj);
    }
    params[2] = othersArr;
    params[PARAM_COUNT_THREE] = touchRecognizers;
    auto jsValue = JsFunction::ExecuteJS(PARAM_COUNT_FOUR, params);
    auto returnValue = GestureJudgeResult::CONTINUE;
    if (jsValue->IsNumber()) {
        returnValue = static_cast<GestureJudgeResult>(jsValue->ToNumber<int32_t>());
    }
    return returnValue;
}

TouchRecognizerMap JsGestureJudgeFunction::CreateTouchRecognizerMap(
    const std::shared_ptr<BaseGestureEvent>& info, const RefPtr<NG::NGGestureRecognizer>& current)
{
    TouchRecognizerMap touchRecognizerMap;
    auto frameNode = current->GetAttachedNode().Upgrade();
    CHECK_NULL_RETURN(frameNode, touchRecognizerMap);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, touchRecognizerMap);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_RETURN(eventManager, touchRecognizerMap);
    auto& touchTestResult = eventManager->touchTestResults_;
    const auto& fingerList = info->GetFingerList();
    for (const auto& finger : fingerList) {
        auto& touchTargetList = touchTestResult[finger.fingerId_];
        CollectTouchEventTarget(touchRecognizerMap, touchTargetList, AceType::RawPtr(frameNode), finger.fingerId_);
    }
    return touchRecognizerMap;
}

void JsGestureJudgeFunction::CollectTouchEventTarget(
    TouchRecognizerMap& dict, std::list<RefPtr<TouchEventTarget>>& targets, NG::FrameNode* frameNode, int32_t fingerId)
{
    for (auto& target : targets) {
        if (AceType::DynamicCast<NG::NGGestureRecognizer>(target)) {
            continue;
        }
        auto weakTarget = WeakPtr<TouchEventTarget>(target);
        if (dict.find(weakTarget) != dict.end() && dict[weakTarget].count(fingerId) > 0) {
            continue;
        }
        auto targetNode = target->GetAttachedNode().Upgrade();
        if (targetNode && targetNode == frameNode) {
            dict[weakTarget].insert(fingerId);
            return;
        }
        while (targetNode) {
            if (targetNode == frameNode) {
                dict[weakTarget].insert(fingerId);
                break;
            }
            targetNode = targetNode->GetParentFrameNode();
        }
    }
}

JSRef<JSObject> JsGestureJudgeFunction::CreateFingerInfo(const FingerInfo& fingerInfo)
{
    JSRef<JSObject> fingerInfoObj = JSRef<JSObject>::New();
    const OHOS::Ace::Offset& globalLocation = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& localLocation = fingerInfo.localLocation_;
    const OHOS::Ace::Offset& screenLocation = fingerInfo.screenLocation_;
    const OHOS::Ace::Offset& globalDisplayLocation = fingerInfo.globalDisplayLocation_;
    fingerInfoObj->SetProperty<int32_t>("id", fingerInfo.fingerId_);
    fingerInfoObj->SetProperty<double>("globalX", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX()));
    fingerInfoObj->SetProperty<double>("globalY", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY()));
    fingerInfoObj->SetProperty<double>("localX", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX()));
    fingerInfoObj->SetProperty<double>("localY", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY()));
    fingerInfoObj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX()));
    fingerInfoObj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY()));
    fingerInfoObj->SetProperty<double>(
        "globalDisplayX", PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetX()));
    fingerInfoObj->SetProperty<double>(
        "globalDisplayY", PipelineBase::Px2VpWithCurrentDensity(globalDisplayLocation.GetY()));
    return fingerInfoObj;
}

JSRef<JSObject> JsGestureJudgeFunction::CreateEventTargetObject(const std::shared_ptr<BaseGestureEvent>& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> target = objectTemplate->NewInstance();
    JSRef<JSObject> area = objectTemplate->NewInstance();
    JSRef<JSObject> offset = objectTemplate->NewInstance();
    JSRef<JSObject> globalOffset = objectTemplate->NewInstance();
    const auto& localOffset = info->GetTarget().area.GetOffset();
    const auto& origin = info->GetTarget().origin;
    offset->SetProperty<double>("x", localOffset.GetX().ConvertToVp());
    offset->SetProperty<double>("y", localOffset.GetY().ConvertToVp());
    globalOffset->SetProperty<double>("x", (origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp()));
    globalOffset->SetProperty<double>("y", (origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp()));
    area->SetPropertyObject("position", offset);
    area->SetPropertyObject("globalPosition", globalOffset);
    area->SetProperty<double>("width", info->GetTarget().area.GetWidth().ConvertToVp());
    area->SetProperty<double>("height", info->GetTarget().area.GetHeight().ConvertToVp());
    target->SetPropertyObject("area", area);
    if (!info->GetTarget().id.empty()) {
        target->SetProperty<const char*>("id", info->GetTarget().id.c_str());
    } else {
        target->SetPropertyObject("id", JsiValue::Undefined());
    }
    return target;
}

void JsGestureJudgeFunction::ParsePanGestureEvent(JSRef<JSObject>& obj, const std::shared_ptr<BaseGestureEvent>& info)
{
    auto panGestureEvent = TypeInfoHelper::DynamicCast<PanGestureEvent>(info.get());
    if (panGestureEvent) {
        obj->SetProperty<double>(
            "offsetX", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetOffsetX()));
        obj->SetProperty<double>(
            "offsetY", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetOffsetY()));
        obj->SetProperty<double>(
            "velocityX", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityX()));
        obj->SetProperty<double>(
            "velocityY", PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityY()));
        obj->SetProperty<double>("velocity",
            PipelineBase::Px2VpWithCurrentDensity(panGestureEvent->GetVelocity().GetVelocityValue()));
    }
}

void JsGestureJudgeFunction::SetUniqueAttributes(
    JSRef<JSObject>& obj, GestureTypeName typeName, const std::shared_ptr<BaseGestureEvent>& info)
{
    switch (typeName) {
        case OHOS::Ace::GestureTypeName::LONG_PRESS_GESTURE: {
            auto longPressGestureEvent = TypeInfoHelper::DynamicCast<LongPressGestureEvent>(info.get());
            if (longPressGestureEvent) {
                obj->SetProperty<bool>("repeat", longPressGestureEvent->GetRepeat());
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::PAN_GESTURE: {
            ParsePanGestureEvent(obj, info);
            break;
        }
        case OHOS::Ace::GestureTypeName::PINCH_GESTURE: {
            auto pinchGestureEvent = TypeInfoHelper::DynamicCast<PinchGestureEvent>(info.get());
            if (pinchGestureEvent) {
                obj->SetProperty<double>("scale", pinchGestureEvent->GetScale());
                obj->SetProperty<double>(
                    "pinchCenterX", PipelineBase::Px2VpWithCurrentDensity(pinchGestureEvent->GetPinchCenter().GetX()));
                obj->SetProperty<double>(
                    "pinchCenterY", PipelineBase::Px2VpWithCurrentDensity(pinchGestureEvent->GetPinchCenter().GetY()));
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::ROTATION_GESTURE: {
            auto rotationGestureEvent = TypeInfoHelper::DynamicCast<RotationGestureEvent>(info.get());
            if (rotationGestureEvent) {
                obj->SetProperty<double>("angle", rotationGestureEvent->GetAngle());
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::SWIPE_GESTURE: {
            auto swipeGestureEvent = TypeInfoHelper::DynamicCast<SwipeGestureEvent>(info.get());
            if (swipeGestureEvent) {
                obj->SetProperty<double>("angle", swipeGestureEvent->GetAngle());
                obj->SetProperty<double>("speed", swipeGestureEvent->GetSpeed());
            }
            break;
        }
        case OHOS::Ace::GestureTypeName::TAP_GESTURE: {
            auto tapGestureEvent = TypeInfoHelper::DynamicCast<TapGestureEvent>(info.get());
            if (tapGestureEvent && !tapGestureEvent->GetFingerList().empty()) {
                obj->SetPropertyObject("tapLocation", GetTapLocation(tapGestureEvent->GetFingerList().back()));
            }
            break;
        }
        default:
            break;
    }
}

JSRef<JSObject> JsGestureJudgeFunction::CreateGestureEventObject(
    const std::shared_ptr<BaseGestureEvent>& info, GestureTypeName typeName)
{
    JSRef<JSObjTemplate> objTemp = JSRef<JSObjTemplate>::New();
    objTemp->SetInternalFieldCount(1);
    JSRef<JSObject> obj = objTemp->NewInstance();
    SetUniqueAttributes(obj, typeName, info);
    obj->SetProperty<double>("timestamp", info->GetTimeStamp().time_since_epoch().count());
    obj->SetProperty<double>("source", static_cast<int32_t>(info->GetSourceDevice()));
    obj->SetProperty<double>("pressure", info->GetForce());
    obj->SetProperty<double>("tiltX", info->GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info->GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("rollAngle", info->GetRollAngle().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info->GetSourceTool()));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info->GetDeviceId()));
    obj->SetProperty<int32_t>("targetDisplayId", info->GetTargetDisplayId());
    obj->SetProperty<float>("axisVertical", info->GetVerticalAxis());
    obj->SetProperty<float>("axisHorizontal", info->GetHorizontalAxis());
    obj->SetPropertyObject(
        "getModifierKeyState", JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));

    JSRef<JSArray> fingerArr = JSRef<JSArray>::New();
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    int32_t maxFingerId = -1;
    for (const FingerInfo& fingerInfo : fingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            fingerArr->SetValueAt(fingerInfo.fingerId_, element);
            if (fingerInfo.fingerId_ > maxFingerId) {
                maxFingerId = fingerInfo.fingerId_;
            }
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    auto idx = maxFingerId + 1;
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        fingerArr->SetValueAt(idx++, element);
    }
    obj->SetPropertyObject("fingerList", fingerArr);
    auto target = CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    CreateFingerInfosObject(info, obj);
    obj->Wrap<BaseGestureEvent>(info.get());
    return obj;
}

JSRef<JSObject> JsGestureJudgeFunction::CreateFingerInfosObject(
    const std::shared_ptr<BaseGestureEvent>& info, JSRef<JSObject>& obj)
{
    JSRef<JSArray> fingerArr = JSRef<JSArray>::New();
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    std::vector<JSRef<JSObject>> validFingers;
    for (const FingerInfo& fingerInfo : fingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            validFingers.emplace_back(element);
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    for (size_t i = 0; i < validFingers.size(); ++i) {
        fingerArr->SetValueAt(i, validFingers[i]);
    }
    auto idx = validFingers.size();
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        fingerArr->SetValueAt(idx++, element);
    }
    obj->SetPropertyObject("fingerInfos", fingerArr);
    return obj;
}
} // namespace OHOS::Ace::Framework
