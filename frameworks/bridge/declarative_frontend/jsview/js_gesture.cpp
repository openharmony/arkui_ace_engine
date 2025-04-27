/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_gesture.h"

#include "base/log/log_wrapper.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/jsview/models/gesture_model_impl.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/gesture/gesture_model_ng.h"
#include "frameworks/base/log/ace_scoring_log.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_gesture_function.h"
#include "frameworks/core/gestures/timeout_gesture.h"

namespace OHOS::Ace {
std::unique_ptr<GestureModel> GestureModel::instance_ = nullptr;
std::mutex GestureModel::mutex_;
GestureModel* GestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::GestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::GestureModelNG());
            } else {
                instance_.reset(new Framework::GestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<TapGestureModel> TapGestureModel::instance_ = nullptr;
std::mutex TapGestureModel::mutex_;
TapGestureModel* TapGestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::TapGestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::TapGestureModelNG());
            } else {
                instance_.reset(new Framework::TapGestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<LongPressGestureModel> LongPressGestureModel::instance_ = nullptr;
std::mutex LongPressGestureModel::mutex_;
LongPressGestureModel* LongPressGestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::LongPressGestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::LongPressGestureModelNG());
            } else {
                instance_.reset(new Framework::LongPressGestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<PanGestureModel> PanGestureModel::instance_ = nullptr;
std::mutex PanGestureModel::mutex_;
PanGestureModel* PanGestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::PanGestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::PanGestureModelNG());
            } else {
                instance_.reset(new Framework::PanGestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<SwipeGestureModel> SwipeGestureModel::instance_ = nullptr;
std::mutex SwipeGestureModel::mutex_;
SwipeGestureModel* SwipeGestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::SwipeGestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::SwipeGestureModelNG());
            } else {
                instance_.reset(new Framework::SwipeGestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<PinchGestureModel> PinchGestureModel::instance_ = nullptr;
std::mutex PinchGestureModel::mutex_;
PinchGestureModel* PinchGestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::PinchGestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::PinchGestureModelNG());
            } else {
                instance_.reset(new Framework::PinchGestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<RotationGestureModel> RotationGestureModel::instance_ = nullptr;
std::mutex RotationGestureModel::mutex_;
RotationGestureModel* RotationGestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RotationGestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RotationGestureModelNG());
            } else {
                instance_.reset(new Framework::RotationGestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<GestureGroupModel> GestureGroupModel::instance_ = nullptr;
std::mutex GestureGroupModel::mutex_;
GestureGroupModel* GestureGroupModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::GestureGroupModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::GestureGroupModelNG());
            } else {
                instance_.reset(new Framework::GestureGroupModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<TimeoutGestureModel> TimeoutGestureModel::instance_ = nullptr;
std::mutex TimeoutGestureModel::mutex_;
TimeoutGestureModel* TimeoutGestureModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::TimeoutGestureModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::TimeoutGestureModelNG());
            } else {
                instance_.reset(new Framework::TimeoutGestureModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t DEFAULT_TAP_FINGER = 1;
constexpr int32_t DEFAULT_TAP_COUNT = 1;
constexpr double DEFAULT_TAP_DISTANCE = std::numeric_limits<double>::infinity();
constexpr int32_t DEFAULT_LONG_PRESS_FINGER = 1;
constexpr int32_t DEFAULT_LONG_PRESS_DURATION = 500;
constexpr int32_t DEFAULT_PINCH_FINGER = 2;
constexpr int32_t DEFAULT_MAX_PINCH_FINGER = 5;
constexpr double DEFAULT_PINCH_DISTANCE = 5.0;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr int32_t DEFAULT_MAX_PAN_FINGERS = 10;
constexpr Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
constexpr int32_t DEFAULT_SLIDE_FINGER = DEFAULT_PAN_FINGER;
constexpr double DEFAULT_SLIDE_SPEED = 100.0;
constexpr int32_t DEFAULT_ROTATION_FINGER = 2;
constexpr double DEFAULT_ROTATION_ANGLE = 1.0;

constexpr char GESTURE_FINGERS[] = "fingers";
constexpr char GESTURE_DISTANCE[] = "distance";
constexpr char TAP_GESTURE_DISTANCE[] = "distanceThreshold";
constexpr char GESTURE_SPEED[] = "speed";
constexpr char TAP_COUNT[] = "count";
constexpr char LONG_PRESS_REPEAT[] = "repeat";
constexpr char LONG_PRESS_DURATION[] = "duration";
constexpr char PAN_DIRECTION[] = "direction";
constexpr char SWIPE_DIRECTION[] = "direction";
constexpr char ROTATION_ANGLE[] = "angle";
constexpr char LIMIT_FINGER_COUNT[] = "isFingerCountLimited";
constexpr char GESTURE_DISTANCE_MAP[] = "distanceMap";
} // namespace

void JSGesture::Create(const JSCallbackInfo& info)
{
    int32_t priorityNum = 0;
    if (info.Length() > 0) {
        auto jsPriorityNum = info[0];
        if (jsPriorityNum->IsNumber()) {
            priorityNum = jsPriorityNum->ToNumber<int32_t>();
        }
    }

    int32_t gestureMaskNum = 0;
    if (info.Length() > 1) {
        auto jsGestureMaskNum = info[1];
        if (jsGestureMaskNum->IsNumber()) {
            gestureMaskNum = jsGestureMaskNum->ToNumber<int32_t>();
        }
    }

    GestureModel::GetInstance()->Create(priorityNum, gestureMaskNum);
}

void JSGesture::Finish()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSGesture][pop]", &JSGesture::Finish);
    }
    GestureModel::GetInstance()->Finish();
}

void JSGesture::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSGesture][pop]", &JSGesture::Pop);
    }
    GestureModel::GetInstance()->Pop();
}

void JSTapGesture::Create(const JSCallbackInfo& args)
{
    int32_t countNum = DEFAULT_TAP_COUNT;
    int32_t fingersNum = DEFAULT_TAP_FINGER;
    double distanceThresholdNum = DEFAULT_TAP_DISTANCE;
    bool isLimitFingerCount = false;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> count = obj->GetProperty(TAP_COUNT);
        JSRef<JSVal> fingers = obj->GetProperty(GESTURE_FINGERS);
        JSRef<JSVal> distanceThreshold = obj->GetProperty(TAP_GESTURE_DISTANCE);
        JSRef<JSVal> limitFingerCount = obj->GetProperty(LIMIT_FINGER_COUNT);

        if (count->IsNumber()) {
            int32_t countNumber = count->ToNumber<int32_t>();
            countNum = countNumber <= DEFAULT_TAP_COUNT ? DEFAULT_TAP_COUNT : countNumber;
        }
        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_TAP_FINGER ? DEFAULT_TAP_FINGER : fingersNumber;
        }
        if (distanceThreshold->IsNumber()) {
            double distanceThresholdNumber = distanceThreshold->ToNumber<double>();
            distanceThresholdNum = distanceThresholdNumber < 0? DEFAULT_TAP_DISTANCE : distanceThresholdNumber;
            distanceThresholdNum = Dimension(distanceThresholdNum, DimensionUnit::VP).ConvertToPx();
        }
        if (limitFingerCount->IsBoolean()) {
            isLimitFingerCount = limitFingerCount->ToBoolean();
        }
    }

    TapGestureModel::GetInstance()->Create(countNum, fingersNum, distanceThresholdNum, isLimitFingerCount);
}

void JSLongPressGesture::Create(const JSCallbackInfo& args)
{
    int32_t fingersNum = DEFAULT_LONG_PRESS_FINGER;
    bool repeatResult = false;
    int32_t durationNum = DEFAULT_LONG_PRESS_DURATION;
    bool isLimitFingerCount = false;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty(GESTURE_FINGERS);
        JSRef<JSVal> repeat = obj->GetProperty(LONG_PRESS_REPEAT);
        JSRef<JSVal> duration = obj->GetProperty(LONG_PRESS_DURATION);
        JSRef<JSVal> limitFingerCount = obj->GetProperty(LIMIT_FINGER_COUNT);

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_LONG_PRESS_FINGER ? DEFAULT_LONG_PRESS_FINGER : fingersNumber;
        }
        if (repeat->IsBoolean()) {
            repeatResult = repeat->ToBoolean();
        }
        if (duration->IsNumber()) {
            int32_t durationNumber = duration->ToNumber<int32_t>();
            durationNum = durationNumber <= 0 ? DEFAULT_LONG_PRESS_DURATION : durationNumber;
        }
        if (limitFingerCount->IsBoolean()) {
            isLimitFingerCount = limitFingerCount->ToBoolean();
        }
    }
    LongPressGestureModel::GetInstance()->Create(fingersNum, repeatResult, durationNum, isLimitFingerCount);
}

napi_value GetIteratorNext(const napi_env env, napi_value iterator, napi_value func, bool *done)
{
    napi_value next = nullptr;
    NAPI_CALL(env, napi_call_function(env, iterator, func, 0, nullptr, &next));
    napi_value doneValue = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, next, "done", &doneValue));
    NAPI_CALL(env, napi_get_value_bool(env, doneValue, done));
    return next;
}

napi_value JSPanGesture::ParsePanDistanceMap(JSRef<JSVal> jsDistanceMap, PanDistanceMap& distanceMap)
{
    napi_value emptyValue = nullptr;
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, emptyValue);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, emptyValue);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    auto jsVal = JSRef<JSVal>::Cast(jsDistanceMap);
    panda::Local<JsiValue> value = jsVal.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);

    // parse map object
    napi_value entriesFunc = nullptr;
    napi_value iterator = nullptr;
    napi_value nextFunc = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, nativeValue, "entries", &entriesFunc));
    NAPI_CALL(env, napi_call_function(env, nativeValue, entriesFunc, 0, nullptr, &iterator));
    NAPI_CALL(env, napi_get_named_property(env, iterator, "next", &nextFunc));

    bool done = false;
    napi_value next = nullptr;
    while ((next = GetIteratorNext(env, iterator, nextFunc, &done)) != nullptr && !done) {
        napi_value entry = nullptr;
        napi_value key = nullptr;
        napi_value value = nullptr;
        NAPI_CALL(env, napi_get_named_property(env, next, "value", &entry));
        NAPI_CALL(env, napi_get_element(env, entry, 0, &key));
        NAPI_CALL(env, napi_get_element(env, entry, 1, &value));
        int32_t sourceTool = 0;
        NAPI_CALL(env, napi_get_value_int32(env, key, &sourceTool));
        double distance = 0.0;
        NAPI_CALL(env, napi_get_value_double(env, value, &distance));
        SourceTool st = static_cast<SourceTool>(sourceTool);
        if (st >= SourceTool::UNKNOWN && st <= SourceTool::JOYSTICK && GreatOrEqual(distance, 0.0)) {
            Dimension dimension = Dimension(distance, DimensionUnit::VP);
            distanceMap[st] = dimension.ConvertToPx();
        }
    }
    return next;
}

void JSPanGesture::ParsePanDistance(const JSRef<JSObject>& obj, PanDistanceMap& distanceMap)
{
    JSRef<JSVal> distance = obj->GetProperty(GESTURE_DISTANCE);
    JSRef<JSVal> jsDistanceMap = obj->GetProperty(GESTURE_DISTANCE_MAP);
    if (distance->IsNumber()) {
        double distanceNumber = distance->ToNumber<double>();
        if (!LessNotEqual(distanceNumber, 0.0)) {
            Dimension dimension = Dimension(distanceNumber, DimensionUnit::VP);
            distanceMap[SourceTool::UNKNOWN] = dimension.ConvertToPx();
        } else {
            distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
        }
    } else {
        distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
    }
    if (jsDistanceMap->IsObject()) {
        ParsePanDistanceMap(jsDistanceMap, distanceMap);
    }
}

void JSPanGesture::Create(const JSCallbackInfo& args)
{
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    bool isLimitFingerCount = false;
    PanDirection panDirection;
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() } };
    if (args.Length() <= 0 || !args[0]->IsObject()) {
        distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
        PanGestureModel::GetInstance()->Create(fingersNum, panDirection, distanceMap, isLimitFingerCount);
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    JSPanGestureOption* panGestureOption = obj->Unwrap<JSPanGestureOption>();

    if (panGestureOption != nullptr) {
        RefPtr<PanGestureOption> refPanGestureOption = panGestureOption->GetPanGestureOption();
        PanGestureModel::GetInstance()->SetPanGestureOption(refPanGestureOption);
        return;
    }

    JSRef<JSVal> fingers = obj->GetProperty(GESTURE_FINGERS);
    JSRef<JSVal> directionNum = obj->GetProperty(PAN_DIRECTION);
    JSRef<JSVal> limitFingerCount = obj->GetProperty(LIMIT_FINGER_COUNT);

    if (fingers->IsNumber()) {
        int32_t fingersNumber = fingers->ToNumber<int32_t>();
        fingersNum = fingersNumber <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingersNumber;
    }
    if (directionNum->IsNumber()) {
        uint32_t directNum = directionNum->ToNumber<uint32_t>();
        if (directNum >= static_cast<uint32_t>(PanDirection::NONE) &&
            directNum <= static_cast<uint32_t>(PanDirection::ALL)) {
            panDirection.type = directNum;
        }
    }
    if (limitFingerCount->IsBoolean()) {
        isLimitFingerCount = limitFingerCount->ToBoolean();
    }
    ParsePanDistance(obj, distanceMap);
    PanGestureModel::GetInstance()->Create(fingersNum, panDirection, distanceMap, isLimitFingerCount);
}

void JSSwipeGesture::Create(const JSCallbackInfo& args)
{
    int32_t fingersNum = DEFAULT_SLIDE_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    bool isLimitFingerCount = false;

    if (args.Length() <= 0 || !args[0]->IsObject()) {
        SwipeGestureModel::GetInstance()->Create(fingersNum, slideDirection, speedNum, isLimitFingerCount);
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    JSRef<JSVal> fingers = obj->GetProperty(GESTURE_FINGERS);
    JSRef<JSVal> speed = obj->GetProperty(GESTURE_SPEED);
    JSRef<JSVal> directionNum = obj->GetProperty(SWIPE_DIRECTION);
    JSRef<JSVal> limitFingerCount = obj->GetProperty(LIMIT_FINGER_COUNT);

    if (fingers->IsNumber()) {
        int32_t fingersNumber = fingers->ToNumber<int32_t>();
        fingersNum = fingersNumber <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingersNumber;
    }
    if (speed->IsNumber()) {
        double speedNumber = speed->ToNumber<double>();
        speedNum = LessOrEqual(speedNumber, 0.0) ? DEFAULT_SLIDE_SPEED : speedNumber;
    }
    if (directionNum->IsNumber()) {
        uint32_t directNum = directionNum->ToNumber<uint32_t>();
        if (directNum >= static_cast<uint32_t>(SwipeDirection::NONE) &&
            directNum <= static_cast<uint32_t>(SwipeDirection::ALL)) {
            slideDirection.type = directNum;
        }
    }
    if (limitFingerCount->IsBoolean()) {
            isLimitFingerCount = limitFingerCount->ToBoolean();
    }

    SwipeGestureModel::GetInstance()->Create(fingersNum, slideDirection, speedNum, isLimitFingerCount);
}

void JSPinchGesture::Create(const JSCallbackInfo& args)
{
    int32_t fingersNum = DEFAULT_PINCH_FINGER;
    double distanceNum = DEFAULT_PINCH_DISTANCE;
    bool isLimitFingerCount = false;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty(GESTURE_FINGERS);
        JSRef<JSVal> distance = obj->GetProperty(GESTURE_DISTANCE);
        JSRef<JSVal> limitFingerCount = obj->GetProperty(LIMIT_FINGER_COUNT);

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_PINCH_FINGER ? DEFAULT_PINCH_FINGER : fingersNumber;
            fingersNum = fingersNum > DEFAULT_MAX_PINCH_FINGER ? DEFAULT_PINCH_FINGER : fingersNum;
        }
        if (distance->IsNumber()) {
            double distanceNumber = distance->ToNumber<double>();
            distanceNum = LessNotEqual(distanceNumber, 0.0) ? DEFAULT_PINCH_DISTANCE : distanceNumber;
        }
        if (limitFingerCount->IsBoolean()) {
            isLimitFingerCount = limitFingerCount->ToBoolean();
        }
    }

    PinchGestureModel::GetInstance()->Create(fingersNum, distanceNum, isLimitFingerCount);
}

void JSRotationGesture::Create(const JSCallbackInfo& args)
{
    double angleNum = DEFAULT_ROTATION_ANGLE;
    int32_t fingersNum = DEFAULT_ROTATION_FINGER;
    bool isLimitFingerCount = false;
    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty(GESTURE_FINGERS);
        JSRef<JSVal> angle = obj->GetProperty(ROTATION_ANGLE);
        JSRef<JSVal> limitFingerCount = obj->GetProperty(LIMIT_FINGER_COUNT);

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_ROTATION_FINGER ? DEFAULT_ROTATION_FINGER : fingersNumber;
        }
        if (angle->IsNumber()) {
            double angleNumber = angle->ToNumber<double>();
            angleNum = LessNotEqual(angleNumber, 0.0) ? DEFAULT_ROTATION_ANGLE : angleNumber;
        }
        if (limitFingerCount->IsBoolean()) {
            isLimitFingerCount = limitFingerCount->ToBoolean();
        }
    }

    RotationGestureModel::GetInstance()->Create(fingersNum, angleNum, isLimitFingerCount);
}

void JSGestureGroup::Create(const JSCallbackInfo& args)
{
    int32_t gestureMode = 0;
    if (args.Length() > 0) {
        auto jsGestureMode = args[0];
        if (jsGestureMode->IsNumber()) {
            gestureMode = jsGestureMode->ToNumber<int32_t>();
        }
    }

    GestureGroupModel::GetInstance()->Create(gestureMode);
}

void JSGesture::JsHandlerOnGestureEvent(Ace::GestureEventAction action, const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    RefPtr<JsGestureFunction> handlerFunc = AceType::MakeRefPtr<JsGestureFunction>(JSRef<JSFunc>::Cast(args[0]));

    if (action == Ace::GestureEventAction::CANCEL) {
        auto onActionCancelFunc = [execCtx = args.GetExecutionContext(), func = std::move(handlerFunc)](
                                      GestureEvent& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Gesture.onCancel");
            func->Execute(info);
        };
        GestureModel::GetInstance()->SetOnGestureEvent(onActionCancelFunc);
        return;
    }

    auto onActionFunc = [execCtx = args.GetExecutionContext(), func = std::move(handlerFunc)](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Gesture.onActionCancel");
        func->Execute(info);
    };

    GestureModel::GetInstance()->SetOnActionFunc(onActionFunc, action);
}

void JSGesture::SetTag(const JSCallbackInfo& args)
{
    std::string tag;
    if (args.Length() > 0) {
        auto jsTag = args[0];
        if (jsTag->IsString()) {
            tag = jsTag->ToString();
        }
    }
    GestureModel::GetInstance()->SetTag(tag);
}

void JSGesture::SetAllowedTypes(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }

    JSRef<JSVal> jsTypes = args[0];
    if (!jsTypes->IsArray()) {
        return;
    }
    JSRef<JSArray> jsTypesArr = JSRef<JSArray>::Cast(jsTypes);
    std::set<SourceTool> allowedTypes{};
    auto typesArrLength = jsTypesArr->Length();
    for (size_t i = 0; i < typesArrLength; ++i) {
        auto type = jsTypesArr->GetValueAt(i);
        if (type->IsNumber()) {
            allowedTypes.insert(static_cast<SourceTool>(type->ToNumber<int32_t>()));
        }
    }
    if (allowedTypes.empty()) {
        return;
    }
    GestureModel::GetInstance()->SetAllowedTypes(allowedTypes);
}

void JSGesture::JsHandlerOnAction(const JSCallbackInfo& args)
{
    JSGesture::JsHandlerOnGestureEvent(Ace::GestureEventAction::ACTION, args);
}
void JSGesture::JsHandlerOnActionStart(const JSCallbackInfo& args)
{
    JSGesture::JsHandlerOnGestureEvent(Ace::GestureEventAction::START, args);
}
void JSGesture::JsHandlerOnActionUpdate(const JSCallbackInfo& args)
{
    JSGesture::JsHandlerOnGestureEvent(Ace::GestureEventAction::UPDATE, args);
}

void JSGesture::JsHandlerOnActionEnd(const JSCallbackInfo& args)
{
    JSGesture::JsHandlerOnGestureEvent(Ace::GestureEventAction::END, args);
}
void JSGesture::JsHandlerOnActionCancel(const JSCallbackInfo& args)
{
    JSGesture::JsHandlerOnGestureEvent(Ace::GestureEventAction::CANCEL, args);
}

void JSPanGestureOption::JSBind(BindingTarget globalObj)
{
    JSClass<JSPanGestureOption>::Declare("PanGestureOption");
    JSClass<JSPanGestureOption>::CustomMethod("setDirection", &JSPanGestureOption::SetDirection);
    JSClass<JSPanGestureOption>::CustomMethod("setDistance", &JSPanGestureOption::SetDistance);
    JSClass<JSPanGestureOption>::CustomMethod("setFingers", &JSPanGestureOption::SetFingers);
    JSClass<JSPanGestureOption>::Bind(globalObj, &JSPanGestureOption::Constructor, &JSPanGestureOption::Destructor);

    JSClass<JSPanGestureOption>::Declare("PanGestureOptions");
    JSClass<JSPanGestureOption>::CustomMethod("setDirection", &JSPanGestureOption::SetDirection);
    JSClass<JSPanGestureOption>::CustomMethod("setDistance", &JSPanGestureOption::SetDistance);
    JSClass<JSPanGestureOption>::CustomMethod("setFingers", &JSPanGestureOption::SetFingers);
    JSClass<JSPanGestureOption>::CustomMethod("getDirection", &JSPanGestureOption::GetDirection);
    JSClass<JSPanGestureOption>::CustomMethod("getDistance", &JSPanGestureOption::GetDistance);
    JSClass<JSPanGestureOption>::Bind(globalObj, &JSPanGestureOption::Constructor, &JSPanGestureOption::Destructor);
}

void JSPanGestureOption::SetDirection(const JSCallbackInfo& args)
{
    if (args.Length() > 0 && args[0]->IsNumber()) {
        PanDirection direction = { args[0]->ToNumber<int32_t>() };
        panGestureOption_->SetDirection(direction);
    } else {
        PanDirection directionAll = { PanDirection::ALL };
        panGestureOption_->SetDirection(directionAll);
    }
}

void JSPanGestureOption::SetDistance(const JSCallbackInfo& args)
{
    if (args.Length() > 0 && args[0]->IsNumber()) {
        auto distance = args[0]->ToNumber<double>();
        Dimension dimension =
            LessNotEqual(distance, 0.0) ? DEFAULT_PAN_DISTANCE : Dimension(distance, DimensionUnit::VP);
        panGestureOption_->SetDistance(dimension.ConvertToPx());
    } else {
        panGestureOption_->SetDistance(DEFAULT_PAN_DISTANCE.ConvertToPx());
    }
}

void JSPanGestureOption::SetFingers(const JSCallbackInfo& args)
{
    if (args.Length() > 0 && args[0]->IsNumber()) {
        auto fingers = args[0]->ToNumber<int32_t>();
        fingers = fingers <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingers;
        fingers = fingers > DEFAULT_MAX_PAN_FINGERS ? DEFAULT_PAN_FINGER : fingers;
        panGestureOption_->SetFingers(fingers);
    } else {
        panGestureOption_->SetFingers(DEFAULT_PAN_FINGER);
    }
}

void JSPanGestureOption::GetDirection(const JSCallbackInfo& args)
{
    PanDirection direction = { PanDirection::NONE };
    if (panGestureOption_) {
        direction = panGestureOption_->GetDirection();
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(direction.type))));
}

void JSPanGestureOption::GetDistance(const JSCallbackInfo& args)
{
    double distance = 5;
    double distance_new = distance;
    if (panGestureOption_) {
        distance = panGestureOption_->GetDistance();
        auto context = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        distance_new = context->ConvertPxToVp(Dimension(distance, DimensionUnit::PX));
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(RoundToMaxPrecision(distance_new))));
}

void JSPanGestureOption::Constructor(const JSCallbackInfo& args)
{
    auto panGestureOption = Referenced::MakeRefPtr<JSPanGestureOption>();
    panGestureOption->IncRefCount();
    RefPtr<PanGestureOption> option = AceType::MakeRefPtr<PanGestureOption>();

    int32_t fingersNum = DEFAULT_PAN_FINGER;
    bool isLimitFingerCount = false;
    PanDirection panDirection;
    PanDistanceMap distanceMap;
    distanceMap[SourceTool::UNKNOWN] = DEFAULT_PAN_DISTANCE.ConvertToPx();

    if (args.Length() > 0 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> fingers = obj->GetProperty(GESTURE_FINGERS);
        JSRef<JSVal> distance = obj->GetProperty(GESTURE_DISTANCE);
        JSRef<JSVal> directionNum = obj->GetProperty(PAN_DIRECTION);
        JSRef<JSVal> limitFingerCount = obj->GetProperty(LIMIT_FINGER_COUNT);

        if (fingers->IsNumber()) {
            int32_t fingersNumber = fingers->ToNumber<int32_t>();
            fingersNum = fingersNumber <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingersNumber;
        }
        if (distance->IsNumber()) {
            double distanceNumber = distance->ToNumber<double>();
            if (!LessNotEqual(distanceNumber, 0.0)) {
                Dimension dimension = Dimension(distanceNumber, DimensionUnit::VP);
                distanceMap[SourceTool::UNKNOWN] = dimension.ConvertToPx();
            } else {
                distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
            }
        } else {
            distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
        }
        if (directionNum->IsNumber()) {
            uint32_t directNum = directionNum->ToNumber<uint32_t>();
            if (directNum >= static_cast<uint32_t>(PanDirection::NONE) &&
                directNum <= static_cast<uint32_t>(PanDirection::ALL)) {
                panDirection.type = directNum;
            }
        }
        if (limitFingerCount->IsBoolean()) {
            isLimitFingerCount = limitFingerCount->ToBoolean();
        }
    }
    option->SetDirection(panDirection);
    option->SetDistanceMap(distanceMap);
    option->SetDistance(distanceMap[SourceTool::UNKNOWN]);
    option->SetFingers(fingersNum);
    option->SetIsLimitFingerCount(isLimitFingerCount);

    panGestureOption->SetPanGestureOption(option);
    args.SetReturnValue(Referenced::RawPtr(panGestureOption));
}

void JSPanGestureOption::Destructor(JSPanGestureOption* panGestureOption)
{
    if (panGestureOption != nullptr) {
        panGestureOption->DecRefCount();
    }
}

void JSGesture::JSBind(BindingTarget globalObj)
{
    JSClass<JSGesture>::Declare("Gesture");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSGesture>::StaticMethod("create", &JSGesture::Create, opt);
    JSClass<JSGesture>::StaticMethod("pop", &JSGesture::Finish);
    JSClass<JSGesture>::Bind<>(globalObj);

    JSClass<JSTapGesture>::Declare("TapGesture");
    JSClass<JSTapGesture>::StaticMethod("create", &JSTapGesture::Create, opt);
    JSClass<JSTapGesture>::StaticMethod("tag", &JSGesture::SetTag, opt);
    JSClass<JSTapGesture>::StaticMethod("allowedTypes", &JSGesture::SetAllowedTypes);
    JSClass<JSTapGesture>::StaticMethod("pop", &JSGesture::Pop);
    JSClass<JSTapGesture>::StaticMethod("onAction", &JSGesture::JsHandlerOnAction);
    JSClass<JSTapGesture>::StaticMethod("onActionUpdate", &JSGesture::JsHandlerOnActionUpdate);
    JSClass<JSTapGesture>::Bind<>(globalObj);

    JSClass<JSLongPressGesture>::Declare("LongPressGesture");
    JSClass<JSLongPressGesture>::StaticMethod("create", &JSLongPressGesture::Create, opt);
    JSClass<JSLongPressGesture>::StaticMethod("tag", &JSGesture::SetTag, opt);
    JSClass<JSLongPressGesture>::StaticMethod("allowedTypes", &JSGesture::SetAllowedTypes);
    JSClass<JSLongPressGesture>::StaticMethod("pop", &JSGesture::Pop);
    JSClass<JSLongPressGesture>::StaticMethod("onAction", &JSGesture::JsHandlerOnAction);
    JSClass<JSLongPressGesture>::StaticMethod("onActionEnd", &JSGesture::JsHandlerOnActionEnd);
    JSClass<JSLongPressGesture>::StaticMethod("onActionCancel", &JSGesture::JsHandlerOnActionCancel);
    JSClass<JSLongPressGesture>::StaticMethod("onActionUpdate", &JSGesture::JsHandlerOnActionUpdate);
    JSClass<JSLongPressGesture>::Bind(globalObj);

    JSClass<JSPanGesture>::Declare("PanGesture");
    JSClass<JSPanGesture>::StaticMethod("create", &JSPanGesture::Create, opt);
    JSClass<JSPanGesture>::StaticMethod("tag", &JSGesture::SetTag, opt);
    JSClass<JSPanGesture>::StaticMethod("allowedTypes", &JSGesture::SetAllowedTypes);
    JSClass<JSPanGesture>::StaticMethod("pop", &JSGesture::Pop);
    JSClass<JSPanGesture>::StaticMethod("onActionStart", &JSGesture::JsHandlerOnActionStart);
    JSClass<JSPanGesture>::StaticMethod("onActionUpdate", &JSGesture::JsHandlerOnActionUpdate);
    JSClass<JSPanGesture>::StaticMethod("onActionEnd", &JSGesture::JsHandlerOnActionEnd);
    JSClass<JSPanGesture>::StaticMethod("onActionCancel", &JSGesture::JsHandlerOnActionCancel);
    JSClass<JSPanGesture>::Bind(globalObj);

    JSClass<JSSwipeGesture>::Declare("SwipeGesture");
    JSClass<JSSwipeGesture>::StaticMethod("create", &JSSwipeGesture::Create, opt);
    JSClass<JSSwipeGesture>::StaticMethod("tag", &JSGesture::SetTag, opt);
    JSClass<JSSwipeGesture>::StaticMethod("allowedTypes", &JSGesture::SetAllowedTypes);
    JSClass<JSSwipeGesture>::StaticMethod("pop", &JSGesture::Pop);
    JSClass<JSSwipeGesture>::StaticMethod("onAction", &JSGesture::JsHandlerOnAction);
    JSClass<JSSwipeGesture>::Bind(globalObj);

    JSClass<JSPinchGesture>::Declare("PinchGesture");
    JSClass<JSPinchGesture>::StaticMethod("create", &JSPinchGesture::Create, opt);
    JSClass<JSPinchGesture>::StaticMethod("tag", &JSGesture::SetTag, opt);
    JSClass<JSPinchGesture>::StaticMethod("allowedTypes", &JSGesture::SetAllowedTypes);
    JSClass<JSPinchGesture>::StaticMethod("pop", &JSGesture::Pop);
    JSClass<JSPinchGesture>::StaticMethod("onActionStart", &JSGesture::JsHandlerOnActionStart);
    JSClass<JSPinchGesture>::StaticMethod("onActionUpdate", &JSGesture::JsHandlerOnActionUpdate);
    JSClass<JSPinchGesture>::StaticMethod("onActionEnd", &JSGesture::JsHandlerOnActionEnd);
    JSClass<JSPinchGesture>::StaticMethod("onActionCancel", &JSGesture::JsHandlerOnActionCancel);
    JSClass<JSPinchGesture>::Bind(globalObj);

    JSClass<JSRotationGesture>::Declare("RotationGesture");
    JSClass<JSRotationGesture>::StaticMethod("create", &JSRotationGesture::Create, opt);
    JSClass<JSRotationGesture>::StaticMethod("tag", &JSGesture::SetTag, opt);
    JSClass<JSRotationGesture>::StaticMethod("allowedTypes", &JSGesture::SetAllowedTypes);
    JSClass<JSRotationGesture>::StaticMethod("pop", &JSGesture::Pop);
    JSClass<JSRotationGesture>::StaticMethod("onActionStart", &JSGesture::JsHandlerOnActionStart);
    JSClass<JSRotationGesture>::StaticMethod("onActionUpdate", &JSGesture::JsHandlerOnActionUpdate);
    JSClass<JSRotationGesture>::StaticMethod("onActionEnd", &JSGesture::JsHandlerOnActionEnd);
    JSClass<JSRotationGesture>::StaticMethod("onActionCancel", &JSGesture::JsHandlerOnActionCancel);
    JSClass<JSRotationGesture>::Bind(globalObj);

    JSClass<JSGestureGroup>::Declare("GestureGroup");
    JSClass<JSGestureGroup>::StaticMethod("create", &JSGestureGroup::Create, opt);
    JSClass<JSGestureGroup>::StaticMethod("pop", &JSGesture::Pop);
    JSClass<JSGestureGroup>::StaticMethod("onCancel", &JSGesture::JsHandlerOnActionCancel);
    JSClass<JSGestureGroup>::Bind<>(globalObj);

    JSClass<JSTimeoutGesture>::Declare("TimeoutGesture");
    JSClass<JSTimeoutGesture>::StaticMethod("create", &JSTimeoutGesture::Create, opt);
    JSClass<JSTimeoutGesture>::StaticMethod("pop", &JSGesture::Pop);

    JSClass<JSTimeoutGesture>::Bind<>(globalObj);
}

void JSTimeoutGesture::Create(const JSCallbackInfo& args)
{
    auto jsGesture = args[0];
    if (!jsGesture->IsNumber()) {
        return;
    }

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = TimeoutGestureModel::GetInstance()->GetGestureProcessor();
    auto gesture = AceType::MakeRefPtr<TimeoutGesture>(std::chrono::duration<float>(jsGesture->ToNumber<float>()));
    gestureProcessor->PushGesture(gesture);
}

void JSTimeoutGesture::JSBind(BindingTarget globalObj)
{
    JSClass<JSTimeoutGesture>::Declare("TimeoutGesture");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTimeoutGesture>::StaticMethod("create", &JSTimeoutGesture::Create, opt);
    JSClass<JSTimeoutGesture>::StaticMethod("pop", &JSGesture::Pop);

    JSClass<JSTimeoutGesture>::Bind<>(globalObj);
}
}; // namespace OHOS::Ace::Framework
