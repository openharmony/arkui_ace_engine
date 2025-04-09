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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_gesture_recognizer.h"

#include "ui/base/utils/utils.h"

#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/tap_gesture.h"

namespace OHOS::Ace::Framework {

void JSScrollableTargetInfo::IsBegin(const JSCallbackInfo& args)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto scrollablePattern = AceType::DynamicCast<NG::ScrollablePattern>(pattern);
    if (scrollablePattern) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(scrollablePattern->IsAtTop())));
        return;
    }
    auto swiperPattern = AceType::DynamicCast<NG::SwiperPattern>(pattern);
    if (swiperPattern) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(swiperPattern->IsAtStart())));
    }
}

void JSScrollableTargetInfo::IsEnd(const JSCallbackInfo& args)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto scrollablePattern = AceType::DynamicCast<NG::ScrollablePattern>(pattern);
    if (scrollablePattern) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(scrollablePattern->IsAtBottom())));
        return;
    }
    auto swiperPattern = AceType::DynamicCast<NG::SwiperPattern>(pattern);
    if (swiperPattern) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(swiperPattern->IsAtEnd())));
    }
}

void JSGestureRecognizer::GetTag(const JSCallbackInfo& args)
{
    std::string tag;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        if (gestureInfo->GetTag().has_value()) {
            tag = gestureInfo->GetTag().value();
        }
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(tag)));
}

void JSGestureRecognizer::GetType(const JSCallbackInfo& args)
{
    GestureTypeName type = GestureTypeName::UNKNOWN;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        type = gestureInfo->GetRecognizerType();
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(type))));
}

void JSGestureRecognizer::GetFingers(const JSCallbackInfo& args)
{
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(fingers_)));
}

void JSGestureRecognizer::IsFingerCountLimit(const JSCallbackInfo& args)
{
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isLimitFingerCount_)));
}

void JSGestureRecognizer::IsBuiltInRecognizer(const JSCallbackInfo& args)
{
    bool isBuiltIn = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        auto gestureInfo = recognizer->GetGestureInfo();
        isBuiltIn = gestureInfo->IsSystemGesture();
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isBuiltIn)));
}

void JSGestureRecognizer::SetEnabled(const JSCallbackInfo& args)
{
    auto recognizer = recognizer_.Upgrade();
    CHECK_NULL_VOID(recognizer);
    bool enabled = true;
    if (args[0]->IsBoolean()) {
        enabled = args[0]->ToBoolean();
    }
    recognizer->SetEnabled(enabled);
}

void JSGestureRecognizer::IsEnabled(const JSCallbackInfo& args)
{
    bool isEnabled = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        isEnabled = recognizer->IsEnabled();
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isEnabled)));
}

void JSGestureRecognizer::GetEventTargetInfo(const JSCallbackInfo& args)
{
    auto recognizer = recognizer_.Upgrade();
    if (!recognizer) {
        args.SetReturnValue(JSClass<JSEventTargetInfo>::NewInstance());
        return;
    }
    auto attachNode = recognizer->GetAttachedNode().Upgrade();
    if (!attachNode) {
        args.SetReturnValue(JSClass<JSEventTargetInfo>::NewInstance());
        return;
    }
    RefPtr<NG::Pattern> pattern;
    auto scrollablePattern = attachNode->GetPattern<NG::ScrollablePattern>();
    if (scrollablePattern) {
        pattern = scrollablePattern;
    }
    auto swiperPattern = attachNode->GetPattern<NG::SwiperPattern>();
    if (swiperPattern) {
        pattern = swiperPattern;
    }
    if (pattern) {
        JSRef<JSObject> scrollableTargetObj = JSClass<JSScrollableTargetInfo>::NewInstance();
        auto scrollableTarget = Referenced::Claim(scrollableTargetObj->Unwrap<JSScrollableTargetInfo>());
        scrollableTarget->SetPattern(pattern);
        scrollableTarget->SetInspectorId(attachNode->GetInspectorIdValue(""));
        args.SetReturnValue(scrollableTargetObj);
        return;
    }
    JSRef<JSObject> eventTargetObj = JSClass<JSEventTargetInfo>::NewInstance();
    auto eventTarget = Referenced::Claim(eventTargetObj->Unwrap<JSEventTargetInfo>());
    eventTarget->SetInspectorId(attachNode->GetInspectorIdValue(""));
    args.SetReturnValue(eventTargetObj);
}

void JSGestureRecognizer::GetRefereeState(const JSCallbackInfo& args)
{
    GestureRecognizerState state = GestureRecognizerState::FAIL;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer) {
        state = ConvertRefereeState(recognizer->GetRefereeState());
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(state))));
}

void JSGestureRecognizer::IsValid(const JSCallbackInfo& args)
{
    bool isValid = false;
    auto recognizer = recognizer_.Upgrade();
    if (recognizer && recognizer->IsInResponseLinkRecognizers()) {
        isValid = true;
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isValid)));
}

void JSPanRecognizer::GetDirection(const JSCallbackInfo& args)
{
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(direction_.type)));
}

void JSPanRecognizer::GetPanDistance(const JSCallbackInfo& args)
{
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(distance_)));
}

void JSPanRecognizer::GetPanDistanceMap(const JSCallbackInfo& args)
{
    auto vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    auto distanceMap = panda::MapRef::New(vm);
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (!recognizer) {
        args.SetReturnValue(JsiRef<JsiObject>(JsiObject(distanceMap)));
        return;
    }
    auto panRecognizer = AceType::DynamicCast<NG::PanRecognizer>(recognizer);
    if (!panRecognizer) {
        args.SetReturnValue(JsiRef<JsiObject>(JsiObject(distanceMap)));
        return;
    }
    auto panDistanceMap = panRecognizer->GetDistanceMap();
    for (const auto& item : panDistanceMap) {
        distanceMap->Set(vm, panda::NumberRef::New(vm, static_cast<int32_t>(item.first)),
            panda::NumberRef::New(vm, item.second));
    }
    args.SetReturnValue(JsiRef<JsiObject>(JsiObject(distanceMap)));
}

void JSPinchRecognizer::GetDistance(const JSCallbackInfo& args)
{
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (recognizer) {
        auto context = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        double distance = context->ConvertPxToVp(Dimension(distance_, DimensionUnit::PX));
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(RoundToMaxPrecision(distance))));
    }
}

void JSTapRecognizer::GetCount(const JSCallbackInfo& args)
{
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (recognizer) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(count_)));
    }
}

void JSLongPressRecognizer::GetDuration(const JSCallbackInfo& args)
{
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (recognizer) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(duration_)));
    }
}

void JSLongPressRecognizer::SetRepeat(bool repeat)
{
    repeat_ = repeat;
}

void JSLongPressRecognizer::GetRepeat(const JSCallbackInfo& args)
{
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (recognizer) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(repeat_)));
    }
}

void JSRotationRecognizer::GetAngle(const JSCallbackInfo& args)
{
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (recognizer) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(angle_)));
    }
}

void JSSwipeRecognizer::GetDirection(const JSCallbackInfo& args)
{
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (recognizer) {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(direction_.type)));
    }
}

void JSSwipeRecognizer::GetSpeed(const JSCallbackInfo& args)
{
    auto recognizer = JSGestureRecognizer::GetRecognizer().Upgrade();
    if (recognizer) {
        auto context = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        double speed = context->ConvertPxToVp(Dimension(speed_, DimensionUnit::PX));
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(RoundToMaxPrecision(speed))));
    }
}

void JSEventTargetInfo::JSBind(BindingTarget globalObj)
{
    JSClass<JSEventTargetInfo>::Declare("EventTargetInfo");
    JSClass<JSEventTargetInfo>::CustomMethod("getId", &JSEventTargetInfo::GetInspectorId);
    JSClass<JSEventTargetInfo>::Bind(globalObj, &JSEventTargetInfo::Constructor, &JSEventTargetInfo::Destructor);
}

void JSScrollableTargetInfo::JSBind(BindingTarget globalObj)
{
    JSClass<JSScrollableTargetInfo>::Declare("ScrollableTargetInfo");
    JSClass<JSScrollableTargetInfo>::CustomMethod("isBegin", &JSScrollableTargetInfo::IsBegin);
    JSClass<JSScrollableTargetInfo>::CustomMethod("isEnd", &JSScrollableTargetInfo::IsEnd);
    JSClass<JSScrollableTargetInfo>::CustomMethod("getId", &JSEventTargetInfo::GetInspectorId);
    JSClass<JSScrollableTargetInfo>::Inherit<JSEventTargetInfo>();
    JSClass<JSScrollableTargetInfo>::Bind(
        globalObj, &JSScrollableTargetInfo::Constructor, &JSScrollableTargetInfo::Destructor);
}

void JSGestureRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSGestureRecognizer>::Declare("GestureRecognizer");
    JSClass<JSGestureRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSGestureRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSGestureRecognizer>::CustomMethod("getFingerCount", &JSGestureRecognizer::GetFingers);
    JSClass<JSGestureRecognizer>::CustomMethod("isFingerCountLimit", &JSGestureRecognizer::IsFingerCountLimit);
    JSClass<JSGestureRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSGestureRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSGestureRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSGestureRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSGestureRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSGestureRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSGestureRecognizer>::Bind(globalObj, &JSGestureRecognizer::Constructor, &JSGestureRecognizer::Destructor);
}

void JSPanRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSPanRecognizer>::Declare("PanRecognizer");
    JSClass<JSPanRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSPanRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSPanRecognizer>::CustomMethod("getFingerCount", &JSGestureRecognizer::GetFingers);
    JSClass<JSPanRecognizer>::CustomMethod("isFingerCountLimit", &JSGestureRecognizer::IsFingerCountLimit);
    JSClass<JSPanRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSPanRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSPanRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSPanRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSPanRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSPanRecognizer>::CustomMethod("getPanGestureOptions", &JSPanRecognizer::GetPanGestureOptions);
    JSClass<JSPanRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSPanRecognizer>::CustomMethod("getDirection", &JSPanRecognizer::GetDirection);
    JSClass<JSPanRecognizer>::CustomMethod("getDistance", &JSPanRecognizer::GetPanDistance);
    JSClass<JSPanRecognizer>::CustomMethod("getDistanceMap", &JSPanRecognizer::GetPanDistanceMap);
    JSClass<JSPanRecognizer>::Inherit<JSGestureRecognizer>();
    JSClass<JSPanRecognizer>::Bind(globalObj, &JSPanRecognizer::Constructor, &JSPanRecognizer::Destructor);
}

void JSPinchRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSPinchRecognizer>::Declare("PinchRecognizer");
    JSClass<JSPinchRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSPinchRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSPinchRecognizer>::CustomMethod("getFingerCount", &JSGestureRecognizer::GetFingers);
    JSClass<JSPinchRecognizer>::CustomMethod("isFingerCountLimit", &JSGestureRecognizer::IsFingerCountLimit);
    JSClass<JSPinchRecognizer>::CustomMethod("getDistance", &JSPinchRecognizer::GetDistance);
    JSClass<JSPinchRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSPinchRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSPinchRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSPinchRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSPinchRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSPinchRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSPinchRecognizer>::Inherit<JSGestureRecognizer>();
    JSClass<JSPinchRecognizer>::Bind(globalObj, &JSPinchRecognizer::Constructor, &JSPinchRecognizer::Destructor);
}

void JSTapRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSTapRecognizer>::Declare("TapRecognizer");
    JSClass<JSTapRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSTapRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSTapRecognizer>::CustomMethod("getFingerCount", &JSGestureRecognizer::GetFingers);
    JSClass<JSTapRecognizer>::CustomMethod("isFingerCountLimit", &JSGestureRecognizer::IsFingerCountLimit);
    JSClass<JSTapRecognizer>::CustomMethod("getTapCount", &JSTapRecognizer::GetCount);
    JSClass<JSTapRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSTapRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSTapRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSTapRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSTapRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSTapRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSTapRecognizer>::Inherit<JSGestureRecognizer>();
    JSClass<JSTapRecognizer>::Bind(globalObj, &JSTapRecognizer::Constructor, &JSTapRecognizer::Destructor);
}

void JSLongPressRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSLongPressRecognizer>::Declare("LongPressRecognizer");
    JSClass<JSLongPressRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSLongPressRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSLongPressRecognizer>::CustomMethod("getFingerCount", &JSGestureRecognizer::GetFingers);
    JSClass<JSLongPressRecognizer>::CustomMethod("isFingerCountLimit", &JSGestureRecognizer::IsFingerCountLimit);
    JSClass<JSLongPressRecognizer>::CustomMethod("isRepeat", &JSLongPressRecognizer::GetRepeat);
    JSClass<JSLongPressRecognizer>::CustomMethod("getDuration", &JSLongPressRecognizer::GetDuration);
    JSClass<JSLongPressRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSLongPressRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSLongPressRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSLongPressRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSLongPressRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSLongPressRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSLongPressRecognizer>::Inherit<JSGestureRecognizer>();
    JSClass<JSLongPressRecognizer>::Bind(
        globalObj, &JSLongPressRecognizer::Constructor, &JSLongPressRecognizer::Destructor);
}

void JSRotationRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSRotationRecognizer>::Declare("RotationRecognizer");
    JSClass<JSRotationRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSRotationRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSRotationRecognizer>::CustomMethod("getFingerCount", &JSGestureRecognizer::GetFingers);
    JSClass<JSRotationRecognizer>::CustomMethod("isFingerCountLimit", &JSGestureRecognizer::IsFingerCountLimit);
    JSClass<JSRotationRecognizer>::CustomMethod("getAngle", &JSRotationRecognizer::GetAngle);
    JSClass<JSRotationRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSRotationRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSRotationRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSRotationRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSRotationRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSRotationRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSRotationRecognizer>::Inherit<JSGestureRecognizer>();
    JSClass<JSRotationRecognizer>::Bind(
        globalObj, &JSRotationRecognizer::Constructor, &JSRotationRecognizer::Destructor);
}

void JSSwipeRecognizer::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwipeRecognizer>::Declare("SwipeRecognizer");
    JSClass<JSSwipeRecognizer>::CustomMethod("getTag", &JSGestureRecognizer::GetTag);
    JSClass<JSSwipeRecognizer>::CustomMethod("getType", &JSGestureRecognizer::GetType);
    JSClass<JSSwipeRecognizer>::CustomMethod("getFingerCount", &JSGestureRecognizer::GetFingers);
    JSClass<JSSwipeRecognizer>::CustomMethod("isFingerCountLimit", &JSGestureRecognizer::IsFingerCountLimit);
    JSClass<JSSwipeRecognizer>::CustomMethod("getVelocityThreshold", &JSSwipeRecognizer::GetSpeed);
    JSClass<JSSwipeRecognizer>::CustomMethod("getDirection", &JSSwipeRecognizer::GetDirection);
    JSClass<JSSwipeRecognizer>::CustomMethod("isBuiltIn", &JSGestureRecognizer::IsBuiltInRecognizer);
    JSClass<JSSwipeRecognizer>::CustomMethod("setEnabled", &JSGestureRecognizer::SetEnabled);
    JSClass<JSSwipeRecognizer>::CustomMethod("isEnabled", &JSGestureRecognizer::IsEnabled);
    JSClass<JSSwipeRecognizer>::CustomMethod("getEventTargetInfo", &JSGestureRecognizer::GetEventTargetInfo);
    JSClass<JSSwipeRecognizer>::CustomMethod("getState", &JSGestureRecognizer::GetRefereeState);
    JSClass<JSSwipeRecognizer>::CustomMethod("isValid", &JSGestureRecognizer::IsValid);
    JSClass<JSSwipeRecognizer>::Inherit<JSGestureRecognizer>();
    JSClass<JSSwipeRecognizer>::Bind(globalObj, &JSSwipeRecognizer::Constructor, &JSSwipeRecognizer::Destructor);
}
} // namespace OHOS::Ace::Framework