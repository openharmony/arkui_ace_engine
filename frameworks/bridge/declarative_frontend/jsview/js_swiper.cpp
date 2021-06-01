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

#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"

#include <algorithm>
#include <iterator>

#include "core/components/foreach/foreach_component.h"

namespace OHOS::Ace::Framework {
namespace {

#ifdef USE_QUICKJS_ENGINE
JSValue SwiperChangeEventToJSValue(const SwiperChangeEvent& eventInfo, JSContext* ctx)
{
    JSValue eventObj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, eventObj, "index", JS_NewInt32(ctx, eventInfo.GetIndex()));
    return eventObj;
}
#elif USE_V8_ENGINE
v8::Local<v8::Value> SwiperChangeEventToJSValue(const SwiperChangeEvent& eventInfo, v8::Isolate* isolate)
{
    ACE_DCHECK(isolate);
    auto context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    obj->Set(context, v8::String::NewFromUtf8(isolate, "index").ToLocalChecked(),
           v8::Number::New(isolate, eventInfo.GetIndex()))
        .ToChecked();
    return v8::Local<v8::Value>(obj);
}
#endif
} // namespace

#ifdef USE_QUICKJS_ENGINE
JSSwiper::JSSwiper(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("Swiper(children: [%lu])", children.size());
}
#else
JSSwiper::JSSwiper(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("Swiper(children: [%lu])", children_.size());
}
#endif

JSSwiper::~JSSwiper()
{
    LOGD("Destroy: JSSwiper");
}

RefPtr<OHOS::Ace::Component> JSSwiper::CreateSpecializedComponent()
{
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    for (const auto& jsViewChild : children_) {
        if (!jsViewChild) {
            continue;
        }
        auto component = jsViewChild->CreateComponent();
        if (AceType::TypeName<ForEachComponent>() == AceType::TypeName(component)) {
            auto children = AceType::DynamicCast<ForEachComponent>(component)->GetChildren();
            std::copy(children.begin(), children.end(), std::back_insert_iterator(componentChildren));
        } else {
            componentChildren.emplace_back(component);
        }
    }
    RefPtr<OHOS::Ace::SwiperComponent> component = AceType::MakeRefPtr<OHOS::Ace::SwiperComponent>(componentChildren);
    component->SetAutoPlay(autoPlay_);
    component->SetDigitalIndicator(digitalIndicator_);
    component->SetDuration(duration_);
    component->SetIndex(index_);
    component->SetAutoPlayInterval(autoPlayInterval_);
    component->SetLoop(loop_);
    component->SetAxis(axis_);
    if (onChangeFunc_) {
        auto onChange = EventMarker([func = std::move(onChangeFunc_)](const BaseEventInfo* info) {
            auto swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
            if (!swiperInfo) {
                LOGE("HandleChangeEvent swiperInfo == nullptr");
                return;
            }
            func->execute(*swiperInfo);
        });
        component->SetChangeEventId(onChange);
    }
    if (!indicator_) {
        InitIndicatorStyle();
    }
    component->SetIndicator(showIndicator_ ? indicator_ : nullptr);

    return component;
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSSwiper::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

void JSSwiper::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSSwiper::Destroy start");
    JSContainerBase::Destroy(parentCustomView);
    LOGD("JSSwiper::Destroy end");
}

void JSSwiper::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwiper>::Declare("Swiper");
    JSClass<JSSwiper>::Inherit<JSViewAbstract>();
    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSSwiper>::Method("autoPlay", &JSSwiper::SetAutoplay, opt);
    JSClass<JSSwiper>::Method("digital", &JSSwiper::SetDigital, opt);
    JSClass<JSSwiper>::Method("duration", &JSSwiper::SetDuration, opt);
    JSClass<JSSwiper>::Method("index", &JSSwiper::SetIndex, opt);
    JSClass<JSSwiper>::Method("interval", &JSSwiper::SetInterval, opt);
    JSClass<JSSwiper>::Method("loop", &JSSwiper::SetLoop, opt);
    JSClass<JSSwiper>::Method("vertical", &JSSwiper::SetVertical, opt);
    JSClass<JSSwiper>::Method("indicator", &JSSwiper::SetIndicator, opt);
    JSClass<JSSwiper>::CustomMethod("onChange", &JSSwiper::SetOnChange);
    JSClass<JSSwiper>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSwiper>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSwiper>::CustomMethod("indicatorStyle", &JSSwiper::SetIndicatorStyle);
    JSClass<JSSwiper>::Bind(globalObj, ConstructorCallback);
}

void JSSwiper::SetAutoplay(bool autoPlay)
{
    autoPlay_ = autoPlay;
}

void JSSwiper::SetDigital(bool digitalIndicator)
{
    digitalIndicator_ = digitalIndicator;
}

void JSSwiper::SetDuration(double duration)
{
    duration_ = duration;
}

void JSSwiper::SetIndex(uint32_t index)
{
    index_ = index;
}

void JSSwiper::SetInterval(double interval)
{
    autoPlayInterval_ = interval;
}

void JSSwiper::SetLoop(bool loop)
{
    loop_ = loop;
}

void JSSwiper::SetVertical(bool isVertical)
{
    axis_ = isVertical ? Axis::VERTICAL : Axis::HORIZONTAL;
}

void JSSwiper::SetIndicator(bool showIndicator)
{
    showIndicator_ = showIndicator;
}

#ifdef USE_QUICKJS_ENGINE
void JSSwiper::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSSwiper => MarkGC: start");
    JSContainerBase::MarkGC(rt, markFunc);
    LOGD("JSSwiper => MarkGC: end");
}

void JSSwiper::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSSwiper => release children: start");
    JSContainerBase::ReleaseRT(rt);
    LOGD("JSSwiper => release children: end");
}

JSValue JSSwiper::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSSwiper::QjsConstructor");

    QJSContext::Scope scope(ctx);

    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);

    JSSwiper* stack = new JSSwiper(children, jsChildren);

    return Wrap<JSSwiper>(stack);
}

JSValue JSSwiper::SetIndicatorStyle(JSContext* ctx, JSValue jsSwiper, int argc, JSValue* argv)
{
    if ((argc != 1) || !JS_IsObject(argv[0]) || JS_IsArray(ctx, argv[0]) || JS_IsFunction(ctx, argv[0])) {
        LOGE("indicatorStyle expects a object as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "indicatorStyle expects a object as parameter");
    }
    JSSwiper* swiper = Unwrap<JSSwiper>(jsSwiper);

    if (swiper == nullptr) {
        LOGE("indicatorStyle must be called on a JSSwiper. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "indicatorStyle must be called on a JSSwiper");
    }

    if (swiper->indicator_ == nullptr) {
        swiper->InitIndicatorStyle();
    }

    JSValue leftValue = JS_GetPropertyStr(ctx, argv[0], "left");
    JSValue rightValue = JS_GetPropertyStr(ctx, argv[0], "right");
    JSValue topValue = JS_GetPropertyStr(ctx, argv[0], "top");
    JSValue bottomValue = JS_GetPropertyStr(ctx, argv[0], "bottom");
    JSValue sizeValue = JS_GetPropertyStr(ctx, argv[0], "size");
    JSValue maskValue = JS_GetPropertyStr(ctx, argv[0], "mask");
    JSValue colorValue = JS_GetPropertyStr(ctx, argv[0], "color");
    JSValue selectedColorValue = JS_GetPropertyStr(ctx, argv[0], "selectedColor");

    if (JS_IsNumber(leftValue)) {
        double left = 0.0;
        JS_ToFloat64(ctx, &left, leftValue);
        swiper->indicator_->SetLeft(Dimension(left));
    }

    if (JS_IsNumber(rightValue)) {
        double right = 0.0;
        JS_ToFloat64(ctx, &right, rightValue);
        swiper->indicator_->SetRight(Dimension(right));
    }

    if (JS_IsNumber(topValue)) {
        double top = 0.0;
        JS_ToFloat64(ctx, &top, topValue);
        swiper->indicator_->SetTop(Dimension(top));
    }

    if (JS_IsNumber(bottomValue)) {
        double bottom = 0.0;
        JS_ToFloat64(ctx, &bottom, bottomValue);
        swiper->indicator_->SetBottom(Dimension(bottom));
    }

    if (JS_IsNumber(sizeValue)) {
        double size = 0.0;
        JS_ToFloat64(ctx, &size, sizeValue);
        swiper->indicator_->SetSize(Dimension(size));
    }

    if (JS_IsBool(maskValue)) {
        bool mask = JS_ToBool(ctx, maskValue) == 1 ? true : false;
        swiper->indicator_->SetIndicatorMask(mask);
    }

    if (JS_IsString(colorValue)) {
        const char* colorStr = JS_ToCString(ctx, JS_ToString(ctx, colorValue));
        if (colorStr != nullptr) {
            std::string color(colorStr);
            swiper->indicator_->SetColor(Color::FromString(color));
        }
    }

    if (JS_IsString(selectedColorValue)) {
        const char* colorStr = JS_ToCString(ctx, JS_ToString(ctx, selectedColorValue));
        if (colorStr != nullptr) {
            std::string color(colorStr);
            swiper->indicator_->SetSelectedColor(Color::FromString(color));
        }
    }

    JS_FreeValue(ctx, leftValue);
    JS_FreeValue(ctx, rightValue);
    JS_FreeValue(ctx, bottomValue);
    JS_FreeValue(ctx, topValue);
    JS_FreeValue(ctx, sizeValue);
    JS_FreeValue(ctx, maskValue);
    JS_FreeValue(ctx, colorValue);
    JS_FreeValue(ctx, selectedColorValue);
    return JS_DupValue(ctx, jsSwiper);
}

void JSSwiper::QjsDestructor(JSRuntime* rt, JSSwiper* ptr)
{
    LOGD("JSSwiper(QjsDestructor) start");
    if (!ptr) {
        return;
    }

    ptr->ReleaseRT(rt);
    delete ptr;
    LOGD("JSSwiper(QjsDestructor) end");
}

void JSSwiper::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSStack(QjsGcMark) start");
    JSSwiper* view = Unwrap<JSSwiper>(val);
    if (!view) {
        return;
    }

    view->MarkGC(rt, markFunc);
    LOGD("JSStack(QjsGcMark) end");
}

JSValue JSSwiper::SetOnChange(JSContext* ctx, JSValue this_value, int32_t argc, JSValue* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("change expects a function as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "change() expect a function parameter. Throwing exception");
    }

    QJSContext::Scope scope(ctx);
    // Dup and Free shoulj happen inside the QJSClickFunction

    auto changeHandler = AceType::MakeRefPtr<QJSEventFunction<SwiperChangeEvent, 1>>(
        ctx, JS_DupValue(ctx, argv[0]), SwiperChangeEventToJSValue);

    onChangeFunc_ = changeHandler;

    return JS_DupValue(ctx, this_value); // for call chaining
}
#elif USE_V8_ENGINE
void JSSwiper::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSSwiper>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}

void JSSwiper::SetIndicatorStyle(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    ACE_DCHECK(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    if (context.IsEmpty()) {
        LOGE("Context Is Empty");
        return;
    }

    if (!indicator_) {
        InitIndicatorStyle();
    }
    if (info[0]->IsObject()) {
        v8::Local<v8::Object> obj = info[0]->ToObject(context).ToLocalChecked();
        v8::MaybeLocal<v8::Value> leftValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "left").ToLocalChecked());
        v8::MaybeLocal<v8::Value> topValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "top").ToLocalChecked());
        v8::MaybeLocal<v8::Value> rightValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "right").ToLocalChecked());
        v8::MaybeLocal<v8::Value> bottomValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "bottom").ToLocalChecked());
        v8::MaybeLocal<v8::Value> sizeValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "size").ToLocalChecked());
        v8::MaybeLocal<v8::Value> maskValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "mask").ToLocalChecked());
        v8::MaybeLocal<v8::Value> colorValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "color").ToLocalChecked());
        v8::MaybeLocal<v8::Value> selectedColorValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "selectedColor").ToLocalChecked());

        if (leftValue.ToLocalChecked()->IsNumber()) {
            auto left = V8ValueConvertor::fromV8Value<float>(leftValue.ToLocalChecked());
            indicator_->SetLeft(Dimension(left));
        }
        if (topValue.ToLocalChecked()->IsNumber()) {
            auto top = V8ValueConvertor::fromV8Value<float>(topValue.ToLocalChecked());
            indicator_->SetTop(Dimension(top));
        }
        if (rightValue.ToLocalChecked()->IsNumber()) {
            auto right = V8ValueConvertor::fromV8Value<float>(rightValue.ToLocalChecked());
            indicator_->SetRight(Dimension(right));
        }
        if (bottomValue.ToLocalChecked()->IsNumber()) {
            auto bottom = V8ValueConvertor::fromV8Value<float>(bottomValue.ToLocalChecked());
            indicator_->SetBottom(Dimension(bottom));
        }
        if (sizeValue.ToLocalChecked()->IsNumber()) {
            auto size = V8ValueConvertor::fromV8Value<float>(sizeValue.ToLocalChecked());
            indicator_->SetSize(Dimension(size));
        }
        if (maskValue.ToLocalChecked()->IsBoolean()) {
            auto mask = V8ValueConvertor::fromV8Value<bool>(maskValue.ToLocalChecked());
            indicator_->SetIndicatorMask(mask);
        }
        if (colorValue.ToLocalChecked()->IsString()) {
            auto colorString = V8ValueConvertor::fromV8Value<std::string>(colorValue.ToLocalChecked());
            indicator_->SetColor(Color::FromString(colorString));
        }
        if (selectedColorValue.ToLocalChecked()->IsString()) {
            auto selectedColorString = V8ValueConvertor::fromV8Value<std::string>(selectedColorValue.ToLocalChecked());
            indicator_->SetSelectedColor(Color::FromString(selectedColorString));
        }
    }
    info.GetReturnValue().Set(info.This());
}

void JSSwiper::SetOnChange(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args[0]->IsFunction()) {
        onChangeFunc_ = AceType::MakeRefPtr<V8EventFunction<SwiperChangeEvent, 1>>(
            v8::Local<v8::Function>::Cast(args[0]), SwiperChangeEventToJSValue);
    }
    args.GetReturnValue().Set(args.This());
}
#endif

void JSSwiper::InitIndicatorStyle()
{
    if (!indicator_) {
        indicator_ = AceType::MakeRefPtr<OHOS::Ace::SwiperIndicator>();
        auto indicatorTheme = GetTheme<SwiperIndicatorTheme>();
        if (indicatorTheme) {
            indicator_->InitStyle(indicatorTheme);
        }
    }
}

} // namespace OHOS::Ace::Framework
