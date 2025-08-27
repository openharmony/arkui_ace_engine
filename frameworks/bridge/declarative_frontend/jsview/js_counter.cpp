/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_counter.h"

#include "bridge/declarative_frontend/jsview/models/counter_model_impl.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/core/components/counter/counter_theme.h"

namespace OHOS::Ace {

std::unique_ptr<CounterModel> CounterModel::instance_ = nullptr;
std::mutex CounterModel::mutex_;

CounterModel* CounterModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::CounterModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::CounterModelNG());
            } else {
                instance_.reset(new Framework::CounterModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSCounter::JSBind(BindingTarget globalObj)
{
    JSClass<JSCounter>::Declare("Counter");
    JSClass<JSCounter>::StaticMethod("create", &JSCounter::Create, MethodOptions::NONE);
    JSClass<JSCounter>::StaticMethod("enableDec", &JSCounter::JsEnableDec);
    JSClass<JSCounter>::StaticMethod("enableInc", &JSCounter::JsEnableInc);
    JSClass<JSCounter>::StaticMethod("onInc", &JSCounter::JsOnInc);
    JSClass<JSCounter>::StaticMethod("onDec", &JSCounter::JsOnDec);
    JSClass<JSCounter>::StaticMethod("height", &JSCounter::JSHeight);
    JSClass<JSCounter>::StaticMethod("width", &JSCounter::JSWidth);
    JSClass<JSCounter>::StaticMethod("size", &JSCounter::SetSize);
    JSClass<JSCounter>::StaticMethod("controlWidth", &JSCounter::JSControlWidth);
    JSClass<JSCounter>::StaticMethod("state", &JSCounter::JSStateChange);
    JSClass<JSCounter>::StaticMethod("backgroundColor", &JSCounter::JsBackgroundColor);
    JSClass<JSCounter>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSCounter>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCounter>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSCounter>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCounter>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCounter>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSCounter::JsEnableDec(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    if (!args[0]->IsBoolean()) {
        CounterModel::GetInstance()->SetEnableDec(true);
    } else {
        CounterModel::GetInstance()->SetEnableDec(args[0]->ToBoolean());
    }
}

void JSCounter::JsEnableInc(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    if (!args[0]->IsBoolean()) {
        CounterModel::GetInstance()->SetEnableInc(true);
    } else {
        CounterModel::GetInstance()->SetEnableInc(args[0]->ToBoolean());
    }
}

void JSCounter::JsOnInc(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    CounterModel::GetInstance()->SetOnInc(
        JsEventCallback<void()>(args.GetExecutionContext(), JSRef<JSFunc>::Cast(args[0])));
    args.ReturnSelf();
}

void JSCounter::JsOnDec(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    CounterModel::GetInstance()->SetOnDec(
        JsEventCallback<void()>(args.GetExecutionContext(), JSRef<JSFunc>::Cast(args[0])));
    args.ReturnSelf();
}

static void UpdateLayoutPolicy(const JSCallbackInfo& args, bool isWidth)
{
    auto jsValue = args[0];
    LayoutCalPolicy policy = LayoutCalPolicy::NO_MATCH;
    if (jsValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::Cast(jsValue);
        CHECK_NULL_VOID(!object->IsEmpty());
        JSRef<JSVal> layoutPolicy = object->GetProperty("id_");
        CHECK_NULL_VOID(!layoutPolicy->IsEmpty());
        if (layoutPolicy->IsString()) {
            policy = JSContainerBase::ParseLayoutPolicy(layoutPolicy->ToString());
        }
    }
    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, false);
}

void JSCounter::JSHeight(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }

    Dimension value;
    RefPtr<ResourceObject> heightResObj;
    if (SystemProperties::ConfigChangePerform()) {
        bool state = ConvertFromJSValue(args[0], value, heightResObj);
        CounterModel::GetInstance()->CreateWithResourceObj(JsCounterResourceType::Height, heightResObj);
        if (!state) {
            UpdateLayoutPolicy(args, false);
            return;
        }
        if (LessNotEqual(value.Value(), 0.0)) {
            return;
        }
        CounterModel::GetInstance()->SetHeight(value);
        args.ReturnSelf();
    } else {
        if (!ConvertFromJSValue(args[0], value)) {
            UpdateLayoutPolicy(args, false);
            return;
        }
        if (LessNotEqual(value.Value(), 0.0)) {
            return;
        }
        CounterModel::GetInstance()->SetHeight(value);
        args.ReturnSelf();
    }
}

void JSCounter::JSWidth(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }

    Dimension value;
    RefPtr<ResourceObject> widthResObj;
    if (SystemProperties::ConfigChangePerform()) {
        bool state = ConvertFromJSValue(args[0], value, widthResObj);
        CounterModel::GetInstance()->CreateWithResourceObj(JsCounterResourceType::Width, widthResObj);
        if (!state) {
            UpdateLayoutPolicy(args, true);
            return;
        }
        if (LessNotEqual(value.Value(), 0.0)) {
            return;
        }
        CounterModel::GetInstance()->SetWidth(value);
        args.ReturnSelf();
    } else {
        if (!ConvertFromJSValue(args[0], value)) {
            UpdateLayoutPolicy(args, true);
            return;
        }
        if (LessNotEqual(value.Value(), 0.0)) {
            return;
        }
        CounterModel::GetInstance()->SetWidth(value);
        args.ReturnSelf();
    }
}

void JSCounter::SetSize(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        args.ReturnSelf();
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

    Dimension height;
    RefPtr<ResourceObject> heightResObj;
    Dimension width;
    RefPtr<ResourceObject> widthResObj;
    if (SystemProperties::ConfigChangePerform()) {
        bool heightState = ConvertFromJSValue(obj->GetProperty("height"), height, heightResObj);
        CounterModel::GetInstance()->CreateWithResourceObj(JsCounterResourceType::Height, heightResObj);
        if (heightState) {
            if (height.IsValid() && GreatOrEqual(height.Value(), 0.0)) {
                CounterModel::GetInstance()->SetHeight(height);
            }
        }
        bool widthState = ConvertFromJSValue(obj->GetProperty("width"), width, widthResObj);
        CounterModel::GetInstance()->CreateWithResourceObj(JsCounterResourceType::Width, widthResObj);
        if (widthState) {
            if (width.IsValid() && GreatOrEqual(width.Value(), 0.0)) {
                CounterModel::GetInstance()->SetWidth(width);
            }
        }
    } else {
        if (ConvertFromJSValue(obj->GetProperty("height"), height) && height.IsValid()) {
            if (height.IsValid() && GreatOrEqual(height.Value(), 0.0)) {
                CounterModel::GetInstance()->SetHeight(height);
            }
        }
        if (ConvertFromJSValue(obj->GetProperty("width"), width) && width.IsValid()) {
            if (width.IsValid() && GreatOrEqual(width.Value(), 0.0)) {
                CounterModel::GetInstance()->SetWidth(width);
            }
        }
    }
    args.ReturnSelf();
}

void JSCounter::JSControlWidth(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }

    Dimension value;
    if (!ConvertFromJSValue(args[0], value)) {
        return;
    }
    CounterModel::GetInstance()->SetControlWidth(value);
    args.ReturnSelf();
}

void JSCounter::JSStateChange(bool state)
{
    CounterModel::GetInstance()->SetStateChange(state);
}

void JSCounter::JsBackgroundColor(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }

    Color color;
    RefPtr<ResourceObject> resObj;
    if (ParseJsColor(args[0], color, resObj)) {
        if (SystemProperties::ConfigChangePerform()) {
            CounterModel::GetInstance()->CreateWithResourceObj(JsCounterResourceType::BackgroundColor, resObj);
        }
        CounterModel::GetInstance()->SetBackgroundColor(color);
        args.ReturnSelf();
    } else if (SystemProperties::ConfigChangePerform()) {
        CounterModel::GetInstance()->CreateWithResourceObj(JsCounterResourceType::BackgroundColor, nullptr);
    }
}

void JSCounter::Create()
{
    CounterModel::GetInstance()->Create();
}

} // namespace OHOS::Ace::Framework
