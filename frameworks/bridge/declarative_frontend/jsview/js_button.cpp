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

#include "frameworks/bridge/declarative_frontend/jsview/js_button.h"

#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_function.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"
#endif
#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_click_function.h"
#endif

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "core/components/button/button_component.h"
#include "core/components/button/button_theme.h"
#include "core/components/padding/padding_component.h"
#include "core/components/text/text_component.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

RefPtr<OHOS::Ace::Component> JSButton::CreateSpecializedComponent()
{
    ACE_DEBUG_SCOPED_TRACE("JSButton::CreateSpecializedComponent");
    LOGD("Create component: Button for %s", (child_ == nullptr) ? "text" : "image");
    // TODO: get default properties from theme
    RefPtr<OHOS::Ace::ButtonComponent> buttonComponent;
    std::list<RefPtr<Component>> buttonChildren;
    if (child_ == nullptr) {
        auto textComponent = AceType::MakeRefPtr<TextComponent>(text_);
        textComponent->SetTextStyle(textStyle_);
        auto padding = AceType::MakeRefPtr<PaddingComponent>();
        padding->SetChild(textComponent);
        buttonChildren.emplace_back(padding);
        buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    } else {
        buttonChildren.emplace_back(child_->CreateComponent());
        buttonComponent = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    }

    buttonComponent->SetType(ButtonType::CAPSULE);
    buttonComponent->SetWidth(100.0_px);
    buttonComponent->SetHeight(50.0_px);
    buttonComponent->SetBackgroundColor(Color::GRAY);

    // Apply styles if any.
    if (GreatNotEqual(ViewWidth().Value(), 0.0)) {
        buttonComponent->SetWidth(ViewWidth());
    }
    if (GreatNotEqual(ViewHeight().Value(), 0.0)) {
        buttonComponent->SetHeight(ViewHeight());
    }
    if (GetUserDefColor()) {
        buttonComponent->SetBackgroundColor(BackGroundColor());
    }
    if (GreatNotEqual(ViewRadius().Value(), 0.0)) {
        buttonComponent->SetRectRadius(ViewRadius());
    }
    if (buttonType_ == static_cast<int32_t>(ButtonType::CAPSULE) ||
        buttonType_ == static_cast<int32_t>(ButtonType::CIRCLE)) {
        buttonComponent->SetType(static_cast<ButtonType>(buttonType_));
    }

    if (onClickFunc_) {
        EventMarker clickEventId([func = std::move(onClickFunc_)](const BaseEventInfo* info) {
#ifdef USE_QUICKJS_ENGINE
            func->execute();
#elif USE_V8_ENGINE
            auto clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
            func->execute(*clickInfo);
#endif
        });
        buttonComponent->SetClickedEventId(clickEventId);
    }

    return buttonComponent;
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSButton::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

#ifdef USE_QUICKJS_ENGINE
void JSButton::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSButton => MarkGC: Mark value for GC start");
    JSInteractableView::MarkGC(rt, markFunc);
    LOGD("JSButton => MarkGC: Mark value for GC end");
}

void JSButton::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSButton => release start");
    JSInteractableView::ReleaseRT(rt);
    LOGD("JSButton => release end");
}
#endif

void JSButton::SetFontSize(double value)
{
    textStyle_.SetFontSize(Dimension(value));
}

void JSButton::SetFontWeight(std::string value)
{
    textStyle_.SetFontWeight(ConvertStrToFontWeight(value));
}

void JSButton::SetTextColor(std::string value)
{
    textStyle_.SetTextColor(Color::FromString(value));
}

void JSButton::SetType(int value)
{
    if ((ButtonType)value == ButtonType::CAPSULE || (ButtonType)value == ButtonType::CIRCLE) {
        buttonType_ = value;
    } else {
        LOGE("Setting button to non valid ButtonType %d", value);
    }
}

// STATIC qjs_class_bindings
#ifdef USE_QUICKJS_ENGINE
JSValue JSButton::JsOnClick(JSContext* ctx, JSValueConst jsBtn, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("onCick expects a function as parameter. Throwing exception.");
        return JS_EXCEPTION;
    }

    QJSContext::Scope scope(ctx);
    JSButton* btn = Unwrap<JSButton>(jsBtn);

    if (btn == nullptr) {
        LOGE("onClick must be called on a JSButton. Throwing exception.");
        return JS_EXCEPTION;
    }

    // Dup and Free shoulj happen inside the QJSClickFunction
    onClickFunc_ = AceType::MakeRefPtr<QJSClickFunction>(ctx, JS_DupValue(ctx, argv[0]));

    return JS_DupValue(ctx, jsBtn); // for call chaining
}

JSValue JSButton::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSButton::ConstructorCallback");
    if (argc > 0 || JS_IsObject(argv[0])) {
        JSViewAbstract* img = static_cast<JSViewAbstract*>(UnwrapAny(argv[0]));
        if (img != nullptr) {
            JS_DupValue(ctx, argv[0]);
            JSButton* view = new JSButton(img);
            return Wrap<JSButton>(new_target, view);
        }
    }

    if (argc > 0 && JS_IsString(argv[0])) {
        QJSContext::Scope scope(ctx);
        ScopedString text(argv[0]);
        JSButton* view = new JSButton(text);
        return Wrap<JSButton>(new_target, view);
    }

    LOGE("Invalid call for Button constructor. Must provide one string argument or an Image component.");
    return JS_NULL;
}

void JSButton::QjsDestructor(JSRuntime* rt, JSButton* view)
{
    LOGD("JSButton(QjsDestructor) start");

    if (!view)
        return;

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSButton(QjsDestructor) end");
}

void JSButton::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSButton(QjsGcMark) start");

    JSButton* btn = Unwrap<JSButton>(val);
    if (!btn)
        return;

    btn->MarkGC(rt, markFunc);
    LOGD("JSButton(QjsGcMark) end");
}
#endif // USE_QUICKJS_ENGINE

void JSButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSButton>::Declare("Button");
    JSClass<JSButton>::Inherit<JSViewAbstract>();
    MethodOptions opt = MethodOptions::RETURN_SELF;
    // "radius" bound by JSViewAbstract
    JSClass<JSButton>::Method("color", &JSButton::SetTextColor, opt);
    JSClass<JSButton>::Method("fontSize", &JSButton::SetFontSize, opt);
    JSClass<JSButton>::Method("fontWeight", &JSButton::SetFontWeight, opt);
    JSClass<JSButton>::Method("type", &JSButton::SetType, opt);
    JSClass<JSButton>::CustomMethod("onClick", &JSButton::JsOnClick);
    JSClass<JSButton>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSButton>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSButton::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();
    if (context.IsEmpty()) {
        LOGE("context is empty!");
        return;
    }

    int argc = args.Length();
    if (argc > 0 && args[0]->IsObject()) {
        v8::Local<v8::Object> obj = args[0]->ToObject(context).ToLocalChecked();
        JSViewAbstract* value = static_cast<JSViewAbstract*>(obj->GetAlignedPointerFromInternalField(0));
        auto instance = V8Object<JSButton>::New(args.This(), value);
        args.GetReturnValue().Set(instance->Get());
    } else if (argc > 0 && args[0]->IsString()) {
        v8::Local<v8::Object> obj = args[0]->ToObject(context).ToLocalChecked();
        V8Utils::ScopedString text(obj);
        auto instance = V8Object<JSButton>::New(args.This(), text);
        args.GetReturnValue().Set(instance->Get());
    } else {
        LOGE("JSButton creation with unsupported child/parameter. Expected Image or text string.");
        V8Utils ::ThrowException("JSButton creation with unsupported child / parameter.");
    }
}

void JSButton::JsOnClick(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    LOGD("JSButton JsOnClick");
    if (args[0]->IsFunction()) {
        v8::Local<v8::Function> clickFunction = v8::Local<v8::Function>::Cast(args[0]);
        onClickFunc_ = AceType::MakeRefPtr<V8ClickFunction>(clickFunction);
    }
    args.GetReturnValue().Set(args.This());
}
#endif

} // namespace OHOS::Ace::Framework
