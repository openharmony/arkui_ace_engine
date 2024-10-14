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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SHOULD_BUILT_IN_RECOGNIZER_PARALLEL_WITH_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SHOULD_BUILT_IN_RECOGNIZER_PARALLEL_WITH_FUNCTION_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_gesture.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

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

    void IsBegin(const JSCallbackInfo& args)
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

    void IsEnd(const JSCallbackInfo& args)
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

    void SetRecognizer(const RefPtr<NG::NGGestureRecognizer>& recognizer)
    {
        recognizer_ = recognizer;
    }

    WeakPtr<NG::NGGestureRecognizer> GetRecognizer()
    {
        return recognizer_;
    }

    void GetTag(const JSCallbackInfo& args)
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

    void GetType(const JSCallbackInfo& args)
    {
        GestureTypeName type = GestureTypeName::UNKNOWN;
        auto recognizer = recognizer_.Upgrade();
        if (recognizer) {
            auto gestureInfo = recognizer->GetGestureInfo();
            type = gestureInfo->GetRecognizerType();
        }
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(type))));
    }

    void IsBuiltInRecognizer(const JSCallbackInfo& args)
    {
        bool isBuiltIn = false;
        auto recognizer = recognizer_.Upgrade();
        if (recognizer) {
            auto gestureInfo = recognizer->GetGestureInfo();
            isBuiltIn = gestureInfo->IsSystemGesture();
        }
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isBuiltIn)));
    }

    void SetEnabled(const JSCallbackInfo& args)
    {
        auto recognizer = recognizer_.Upgrade();
        CHECK_NULL_VOID(recognizer);
        bool enabled = true;
        if (args[0]->IsBoolean()) {
            enabled = args[0]->ToBoolean();
        }
        recognizer->SetEnabled(enabled);
    }

    void IsEnabled(const JSCallbackInfo& args)
    {
        bool isEnabled = false;
        auto recognizer = recognizer_.Upgrade();
        if (recognizer) {
            isEnabled = recognizer->IsEnabled();
        }
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isEnabled)));
    }

    void GetEventTargetInfo(const JSCallbackInfo& args)
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

    void GetRefereeState(const JSCallbackInfo& args)
    {
        GestureRecognizerState state = GestureRecognizerState::FAIL;
        auto recognizer = recognizer_.Upgrade();
        if (recognizer) {
            state = ConvertRefereeState(recognizer->GetRefereeState());
        }
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(static_cast<int32_t>(state))));
    }

    void IsValid(const JSCallbackInfo& args)
    {
        bool isValid = false;
        auto recognizer = recognizer_.Upgrade();
        if (recognizer && recognizer->IsInResponseLinkRecognizers()) {
            isValid = true;
        }
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isValid)));
    }

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
};

class JSPanRecognizer : public JSGestureRecognizer {
public:
    static void JSBind(BindingTarget globalObj);

    void SetPanGestureOptions(int32_t fingers, double distance, PanDirection direction)
    {
        panGestureOption_ = AceType::MakeRefPtr<PanGestureOption>();
        panGestureOption_->SetFingers(fingers);
        panGestureOption_->SetDistance(distance);
        panGestureOption_->SetDirection(direction);
    }

    void GetPanGestureOptions(const JSCallbackInfo& args)
    {
        JSRef<JSObject> panGestureOptionObj = JSClass<JSPanGestureOption>::NewInstance();
        auto panGestureOption = Referenced::Claim(panGestureOptionObj->Unwrap<JSPanGestureOption>());
        panGestureOption->SetPanGestureOption(panGestureOption_);
        args.SetReturnValue(panGestureOptionObj);
    }

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

    RefPtr<PanGestureOption> panGestureOption_;
};

class JsShouldBuiltInRecognizerParallelWithFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsShouldBuiltInRecognizerParallelWithFunction, JsFunction)

public:
    explicit JsShouldBuiltInRecognizerParallelWithFunction(const JSRef<JSFunc>& jsFunction)
        : JsFunction(JSRef<JSObject>(), jsFunction)
    {}

    ~JsShouldBuiltInRecognizerParallelWithFunction() override = default;

    void Execute() override
    {
        ExecuteJS();
    }

    RefPtr<NG::NGGestureRecognizer> Execute(
        const RefPtr<NG::NGGestureRecognizer>& current, const std::vector<RefPtr<NG::NGGestureRecognizer>>& others);
    static JSRef<JSObject> CreateRecognizerObject(const RefPtr<NG::NGGestureRecognizer>& target);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SHOULD_BUILT_IN_RECOGNIZER_PARALLEL_WITH_FUNCTION_H
