/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_stepper.h"

#include "bridge/declarative_frontend/jsview/models/stepper_model_impl.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace {

std::unique_ptr<StepperModel> StepperModel::instance_ = nullptr;
std::mutex StepperModel::mutex_;

StepperModel* StepperModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::StepperModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::StepperModelNG());
            } else {
                instance_.reset(new Framework::StepperModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void ParseStepperIndexObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    StepperModel::GetInstance()->SetOnChangeEvent(
        JsEventCallback<void(int32_t)>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(changeEventVal)));
}

void JSStepper::Create(const JSCallbackInfo& info)
{
    uint32_t index = 0;
    JSRef<JSVal> changeEventVal;
    if (info.Length() < 1 || !info[0]->IsObject()) {
        index = 0;
    } else {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> stepperValue = obj->GetProperty("index");
        if (stepperValue->IsNumber()) {
            auto indexValue = stepperValue->ToNumber<int32_t>();
            index = indexValue <= 0 ? 0 : static_cast<uint32_t>(indexValue);
        } else if (stepperValue->IsObject()) {
            JSRef<JSObject> stepperObj = JSRef<JSObject>::Cast(stepperValue);
            auto stepperValueProperty = stepperObj->GetProperty("value");
            if (stepperValueProperty->IsNumber()) {
                auto indexValue = stepperValueProperty->ToNumber<int32_t>();
                index = indexValue <= 0 ? 0 : static_cast<uint32_t>(indexValue);
            }
            changeEventVal = stepperObj->GetProperty("changeEvent");
        }
    }
    StepperModel::GetInstance()->Create(index);
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseStepperIndexObject(info, changeEventVal);
    }
}

void JSStepper::JSBind(BindingTarget globalObj)
{
    JSClass<JSStepper>::Declare("Stepper");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSStepper>::StaticMethod("create", &JSStepper::Create, opt);
    JSClass<JSStepper>::StaticMethod("onFinish", &JSStepper::OnFinish);
    JSClass<JSStepper>::StaticMethod("onSkip", &JSStepper::OnSkip);
    JSClass<JSStepper>::StaticMethod("onChange", &JSStepper::OnChange);
    JSClass<JSStepper>::StaticMethod("onNext", &JSStepper::OnNext);
    JSClass<JSStepper>::StaticMethod("onPrevious", &JSStepper::OnPrevious);
    JSClass<JSStepper>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSStepper>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSStepper>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSStepper>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSStepper>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSStepper>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSStepper::OnFinish(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    StepperModel::GetInstance()->SetOnFinish(
        JsEventCallback<void()>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0])));
    info.ReturnSelf();
}

void JSStepper::OnSkip(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    StepperModel::GetInstance()->SetOnSkip(
        JsEventCallback<void()>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0])));
    info.ReturnSelf();
}

void JSStepper::OnChange(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    StepperModel::GetInstance()->SetOnChange(
        JsEventCallback<void(int32_t, int32_t)>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0])));
    info.ReturnSelf();
}

void JSStepper::OnNext(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    StepperModel::GetInstance()->SetOnNext(
        JsEventCallback<void(int32_t, int32_t)>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0])));
    info.ReturnSelf();
}

void JSStepper::OnPrevious(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    StepperModel::GetInstance()->SetOnPrevious(
        JsEventCallback<void(int32_t, int32_t)>(info.GetExecutionContext(), JSRef<JSFunc>::Cast(info[0])));
    info.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
