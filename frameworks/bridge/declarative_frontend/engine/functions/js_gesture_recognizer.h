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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_GESTURE_RECOGNIZER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_GESTURE_RECOGNIZER_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_gesture.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "frameworks/core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "frameworks/core/components_ng/gestures/recognizers/swipe_recognizer.h"

namespace OHOS::Ace::Framework {
enum class GestureRecognizerState {
    UNKNOWN = -1,
    READY = 0,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCEED = 4,
    FAIL = 5,
};

class JSEventTargetInfo : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);

    void SetInspectorId(const std::string& inspectorId)
    {
        inspectorId_ = inspectorId;
    }

    void GetInspectorId(const JSCallbackInfo& args)
    {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(inspectorId_)));
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsEventTarget = Referenced::MakeRefPtr<JSEventTargetInfo>();
        jsEventTarget->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsEventTarget));
    }

    static void Destructor(JSEventTargetInfo* jsEventTarget)
    {
        if (jsEventTarget != nullptr) {
            jsEventTarget->DecRefCount();
        }
    }

    std::string inspectorId_;
};

class JSScrollableTargetInfo : public JSEventTargetInfo {
public:
    static void JSBind(BindingTarget globalObj);

    void SetPattern(const WeakPtr<NG::Pattern>& pattern)
    {
        pattern_ = pattern;
    }
    
    // use for ArkTs1.2 interop
    int64_t GetPatternPointer()
    {
        auto pattern = pattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, 0);
        return reinterpret_cast<int64_t>(AceType::RawPtr(pattern));
    }

    void IsBegin(const JSCallbackInfo& args);
    
    void IsEnd(const JSCallbackInfo& args);

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsScrollableTargetInfo = Referenced::MakeRefPtr<JSScrollableTargetInfo>();
        jsScrollableTargetInfo->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsScrollableTargetInfo));
    }

    static void Destructor(JSScrollableTargetInfo* jsScrollableTargetInfo)
    {
        if (jsScrollableTargetInfo != nullptr) {
            jsScrollableTargetInfo->DecRefCount();
        }
    }

    WeakPtr<NG::Pattern> pattern_;
};

class JSGestureRecognizer : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);
    
    void Update(const RefPtr<NG::NGGestureRecognizer>& recognizer)
    {
        recognizer_ = recognizer;
    }

    WeakPtr<NG::NGGestureRecognizer> GetRecognizer()
    {
        return recognizer_;
    }

    void GetTag(const JSCallbackInfo& args);

    void GetType(const JSCallbackInfo& args);
    
    void GetFingers(const JSCallbackInfo& args);

    void IsFingerCountLimit(const JSCallbackInfo& args);

    void IsBuiltInRecognizer(const JSCallbackInfo& args);

    void SetEnabled(const JSCallbackInfo& args);

    void PreventBegin(const JSCallbackInfo& args);

    void IsEnabled(const JSCallbackInfo& args);

    void GetEventTargetInfo(const JSCallbackInfo& args);

    void GetRefereeState(const JSCallbackInfo& args);

    void IsValid(const JSCallbackInfo& args);

    static GestureRecognizerState ConvertRefereeState(NG::RefereeState state)
    {
        switch (state) {
            case NG::RefereeState::READY:
                return GestureRecognizerState::READY;
            case NG::RefereeState::DETECTING:
                return GestureRecognizerState::DETECTING;
            case NG::RefereeState::PENDING:
                return GestureRecognizerState::PENDING;
            case NG::RefereeState::PENDING_BLOCKED:
            case NG::RefereeState::SUCCEED_BLOCKED:
                return GestureRecognizerState::BLOCKED;
            case NG::RefereeState::SUCCEED:
                return GestureRecognizerState::SUCCEED;
            case NG::RefereeState::FAIL:
                return GestureRecognizerState::FAIL;
            default:
                return GestureRecognizerState::UNKNOWN;
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsGestureRecognizer = Referenced::MakeRefPtr<JSGestureRecognizer>();
        jsGestureRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsGestureRecognizer));
    }

    static void Destructor(JSGestureRecognizer* jsGestureRecognizer)
    {
        if (jsGestureRecognizer != nullptr) {
            jsGestureRecognizer->DecRefCount();
        }
    }

    WeakPtr<NG::NGGestureRecognizer> recognizer_;

protected:
    bool isLimitFingerCount_ = false;
    int fingers_ = 1;
};

class JSMultiFingerRecognizer : public JSGestureRecognizer {
public:
    void Update(const RefPtr<NG::MultiFingersRecognizer>& recognizer)
    {
        JSGestureRecognizer::Update(recognizer);
        isLimitFingerCount_ = recognizer->GetLimitFingerCount();
        fingers_ = recognizer->GetFingers();
    }
};

class JSPanRecognizer : public JSMultiFingerRecognizer {
public:
    static void JSBind(BindingTarget globalObj);

    void Update(const RefPtr<NG::PanRecognizer>& recognizer)
    {
        JSMultiFingerRecognizer::Update(recognizer);
        SetPanGestureOptions(
            recognizer->GetFingers(), recognizer->GetDistance(), recognizer->GetDirection());
        direction_ = recognizer->GetDirection();
        distance_ = recognizer->GetDistance();
    }

    void GetPanGestureOptions(const JSCallbackInfo& args)
    {
        JSRef<JSObject> panGestureOptionObj = JSClass<JSPanGestureOption>::NewInstance();
        auto panGestureOption = Referenced::Claim(panGestureOptionObj->Unwrap<JSPanGestureOption>());
        panGestureOption->SetPanGestureOption(panGestureOption_);
        args.SetReturnValue(panGestureOptionObj);
    }

    void GetDirection(const JSCallbackInfo& args);

    void GetPanDistance(const JSCallbackInfo& args);

    void GetPanDistanceMap(const JSCallbackInfo& args);
private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsPanRecognizer = Referenced::MakeRefPtr<JSPanRecognizer>();
        jsPanRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsPanRecognizer));
    }

    static void Destructor(JSPanRecognizer* jsPanRecognizer)
    {
        if (jsPanRecognizer != nullptr) {
            jsPanRecognizer->DecRefCount();
        }
    }

    void SetPanGestureOptions(int32_t fingers, double distance, PanDirection direction)
    {
        panGestureOption_ = AceType::MakeRefPtr<PanGestureOption>();
        panGestureOption_->SetFingers(fingers);
        panGestureOption_->SetDistance(distance);
        panGestureOption_->SetDirection(direction);
    }
    RefPtr<PanGestureOption> panGestureOption_;
    PanDirection direction_;
    double distance_;
};

class JSPinchRecognizer : public JSMultiFingerRecognizer {
public:
    static void JSBind(BindingTarget globalObj);

    void Update(const RefPtr<NG::PinchRecognizer>& recognizer)
    {
        JSMultiFingerRecognizer::Update(recognizer);
        distance_ = recognizer->GetDistance();
    }

    void GetDistance(const JSCallbackInfo& args);

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsPinchRecognizer = Referenced::MakeRefPtr<JSPinchRecognizer>();
        jsPinchRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsPinchRecognizer));
    }

    static void Destructor(JSPinchRecognizer* jsPinchRecognizer)
    {
        if (jsPinchRecognizer != nullptr) {
            jsPinchRecognizer->DecRefCount();
        }
    }

    double distance_ = 5;
};

class JSTapRecognizer : public JSMultiFingerRecognizer {
public:
    static void JSBind(BindingTarget globalObj);

    void Update(const RefPtr<NG::ClickRecognizer>& recognizer)
    {
        JSMultiFingerRecognizer::Update(recognizer);
        count_ = recognizer->GetCount();
    }

    void GetCount(const JSCallbackInfo& args);

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsTapRecognizer = Referenced::MakeRefPtr<JSTapRecognizer>();
        jsTapRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsTapRecognizer));
    }

    static void Destructor(JSTapRecognizer* jsTapRecognizer)
    {
        if (jsTapRecognizer != nullptr) {
            jsTapRecognizer->DecRefCount();
        }
    }

    int32_t count_ = 1;
};

class JSLongPressRecognizer : public JSMultiFingerRecognizer {
public:
    static void JSBind(BindingTarget globalObj);

    void Update(const RefPtr<NG::LongPressRecognizer>& recognizer)
    {
        JSMultiFingerRecognizer::Update(recognizer);
        duration_ = recognizer->GetDuration();
        repeat_ = recognizer->GetIsRepeat();
    }

    void GetDuration(const JSCallbackInfo& args);
    void GetRepeat(const JSCallbackInfo& args);
    void SetRepeat(bool repeat);

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsLongPressRecognizer = Referenced::MakeRefPtr<JSLongPressRecognizer>();
        jsLongPressRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsLongPressRecognizer));
    }

    static void Destructor(JSLongPressRecognizer* jsLongPressRecognizer)
    {
        if (jsLongPressRecognizer != nullptr) {
            jsLongPressRecognizer->DecRefCount();
        }
    }

    int32_t duration_ = 500;
    bool repeat_ = false;
};

class JSRotationRecognizer : public JSMultiFingerRecognizer {
public:
    static void JSBind(BindingTarget globalObj);

    void Update(const RefPtr<NG::RotationRecognizer>& recognizer)
    {
        JSMultiFingerRecognizer::Update(recognizer);
        angle_ = recognizer->GetAngle();
    }

    void GetAngle(const JSCallbackInfo& args);

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsRotationRecognizer = Referenced::MakeRefPtr<JSRotationRecognizer>();
        jsRotationRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsRotationRecognizer));
    }

    static void Destructor(JSRotationRecognizer* jsRotationRecognizer)
    {
        if (jsRotationRecognizer != nullptr) {
            jsRotationRecognizer->DecRefCount();
        }
    }

    double angle_ = 1.0;
};

class JSSwipeRecognizer : public JSMultiFingerRecognizer {
public:
    static void JSBind(BindingTarget globalObj);

    void Update(const RefPtr<NG::SwipeRecognizer>& recognizer)
    {
        JSMultiFingerRecognizer::Update(recognizer);
        direction_ = recognizer->GetDirection();
        speed_ = recognizer->GetSpeed();
    }

    void GetDirection(const JSCallbackInfo& args);
    void GetSpeed(const JSCallbackInfo& args);

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsSwipeRecognizer = Referenced::MakeRefPtr<JSSwipeRecognizer>();
        jsSwipeRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsSwipeRecognizer));
    }

    static void Destructor(JSSwipeRecognizer* jsSwipeRecognizer)
    {
        if (jsSwipeRecognizer != nullptr) {
            jsSwipeRecognizer->DecRefCount();
        }
    }

    SwipeDirection direction_;
    double speed_ = 100.0;
};

class JSTouchRecognizer : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);
    
    void GetEventTargetInfo(const JSCallbackInfo& args);
    void CancelTouch(const JSCallbackInfo& args);
    void SetTouchData(const WeakPtr<TouchEventTarget>& target, const std::unordered_set<int32_t>& fingerIds)
    {
        target_ = std::move(target);
        fingerIds_ = std::move(fingerIds);
    }
    
private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsTouchRecognizer = Referenced::MakeRefPtr<JSTouchRecognizer>();
        jsTouchRecognizer->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsTouchRecognizer));
    }
    
    static void Destructor(JSTouchRecognizer* jsTouchRecognizer)
    {
        if (jsTouchRecognizer != nullptr) {
            jsTouchRecognizer->DecRefCount();
        }
    }
    
    WeakPtr<TouchEventTarget> target_;
    std::unordered_set<int32_t> fingerIds_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_GESTURE_RECOGNIZER_H