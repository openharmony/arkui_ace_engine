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

#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"

#include "base/log/ace_trace.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/core/components/foreach/foreach_component.h"
#include "frameworks/core/components/scroll/scroll_bar_theme.h"
#include "frameworks/core/components/scroll/scroll_fade_effect.h"
#include "frameworks/core/components/scroll/scroll_spring_effect.h"

namespace OHOS::Ace::Framework {

#ifdef USE_V8_ENGINE
v8::Local<v8::Value> ScrollEventInfoToJSValue(const ScrollEventInfo& eventInfo, v8::Isolate* isolate)
{
    ACE_DCHECK(isolate);
    auto context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = v8::Object::New(isolate);

    double scrollOffset = NearZero(eventInfo.GetScrollX()) ? eventInfo.GetScrollY() : eventInfo.GetScrollX();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "scrollOffset").ToLocalChecked(),
           v8::Number::New(isolate, scrollOffset))
        .ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "scrollState").ToLocalChecked(),
           v8::Number::New(isolate, eventInfo.GetScrollState()))
        .ToChecked();
    return v8::Local<v8::Value>(obj);
}
#elif USE_QUICKJS_ENGINE
JSValue ScrollEventInfoToJSValue(const ScrollEventInfo& eventInfo, JSContext* ctx)
{
    JSValue sizeObj = JS_NewObject(ctx);
    double scrollOffset = NearZero(eventInfo.GetScrollX()) ? eventInfo.GetScrollY() : eventInfo.GetScrollX();
    JS_SetPropertyStr(ctx, sizeObj, "scrollOffset", JS_NewFloat64(ctx, scrollOffset));
    JS_SetPropertyStr(ctx, sizeObj, "scrollState", JS_NewInt32(ctx, eventInfo.GetScrollState()));
    return sizeObj;
}
#endif

#ifdef USE_QUICKJS_ENGINE
JSList::JSList(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren), onScrollFunc_(nullptr), onReachStartFunc_(nullptr),
      onReachEndFunc_(nullptr), onScrollStopFunc_(nullptr)
#elif USE_V8_ENGINE
JSList::JSList(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
#endif
{
    LOGD("List, children size is : %{public}lu)", children_.size());
}

JSList::~JSList()
{
    LOGD("Destroy: JSList");
};

RefPtr<OHOS::Ace::Component> JSList::CreateSpecializedComponent()
{
    LOGD("Create component: List, childSize %lu", children_.size());
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    RefPtr<ListComponent> listComponent = AceType::MakeRefPtr<ListComponent>(componentChildren);
    for (const auto& jsViewChild : children_) {
        if (!jsViewChild) {
            continue;
        }
        auto component = jsViewChild->CreateComponent();
        if (AceType::TypeName<ForEachComponent>() == AceType::TypeName(component)) {
            auto children = AceType::DynamicCast<ForEachComponent>(component)->GetChildren();
            for (const auto& childComponent : children) {
                listComponent->AppendChild(childComponent);
                InitDivider(childComponent);
            }
        } else {
            InitDivider(component);
            listComponent->AppendChild(component);
        }
    }

    listComponent->SetDirection(flexDirection_);

    if (onScrollFunc_) {
        auto onScroll = EventMarker(
            [func = std::move(onScrollFunc_)](const BaseEventInfo* info) {
                auto eventInfo = TypeInfoHelper::DynamicCast<ScrollEventInfo>(info);
                if (!eventInfo) {
                    LOGE("HandleScrollEvent, param is not  ScrollEventInfo");
                    return;
                }
                LOGD("onScrollFunc_ execute");
                func->execute(*eventInfo);
            },
            "scroll", 0);
        listComponent->SetOnScroll(onScroll);
    }
    if (onScrollStopFunc_) {
        auto onScrollStop = EventMarker([func = std::move(onScrollStopFunc_)] { func->execute(); }, "scrollStop", 0);
        listComponent->SetOnScrollEnd(onScrollStop);
    }
    if (onReachStartFunc_) {
        auto onReachStart = EventMarker([func = std::move(onReachStartFunc_)] { func->execute(); }, "reachStart", 0);
        listComponent->SetOnScrollTop(onReachStart);
    }
    if (onReachEndFunc_) {
        auto onReachEnd = EventMarker([func = std::move(onReachEndFunc_)] { func->execute(); }, "reachEnd", 0);
        listComponent->SetOnScrollBottom(onReachEnd);
    }

    if (edgeEffect_ == EdgeEffect::SPRING) {
        listComponent->SetScrollEffect(AceType::MakeRefPtr<ScrollSpringEffect>());
    } else if (edgeEffect_ == EdgeEffect::FADE) {
        listComponent->SetScrollEffect(AceType::MakeRefPtr<ScrollFadeEffect>());
    } else {
        listComponent->SetScrollEffect(AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect::NONE));
    }

    if (!listComponent->GetPositionController()) {
        listComponent->SetPositionController(AceType::MakeRefPtr<ScrollPositionController>());
    }
    listComponent->GetPositionController()->SetInitialIndex(initialIndex_);

    if (displayMode_ == DisplayMode::ON || displayMode_ == DisplayMode::AUTO) {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>(displayMode_, ShapeMode::RECT);
        InitScrollBarTheme();
    } else {
        scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF, ShapeMode::DEFAULT);
    }
    listComponent->SetScrollBar(scrollBar_);

    return listComponent;
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSList::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

void JSList::SetFlexDirection(int32_t flexDirection)
{
    LOGD("JSList SetFlexDirection is %{public}d", flexDirection);
    if (static_cast<int32_t>(Direction::COLUMN) == flexDirection) {
        flexDirection_ = FlexDirection::COLUMN;
    } else if (static_cast<int32_t>(Direction::ROW) == flexDirection) {
        flexDirection_ = FlexDirection::ROW;
    } else {
        flexDirection_ = FlexDirection::COLUMN;
    }
}

void JSList::SetScrollBarState(int32_t state)
{
    if (static_cast<int32_t>(DisplayMode::OFF) == state) {
        displayMode_ = DisplayMode::OFF;
    } else if (static_cast<int32_t>(DisplayMode::AUTO) == state) {
        displayMode_ = DisplayMode::AUTO;
    } else if (static_cast<int32_t>(DisplayMode::ON) == state) {
        displayMode_ = DisplayMode::ON;
    } else {
        displayMode_ = DisplayMode::OFF;
    }
}

void JSList::SetScrollEffect(int32_t scrollEffect)
{
    LOGD("JSList SetScrollEffect is %{public}d", scrollEffect);
    if (static_cast<int32_t>(EdgeEffect::SPRING) == scrollEffect) {
        edgeEffect_ = EdgeEffect::SPRING;
    } else if (static_cast<int32_t>(EdgeEffect::FADE) == scrollEffect) {
        edgeEffect_ = EdgeEffect::FADE;
    } else if (static_cast<int32_t>(EdgeEffect::NONE) == scrollEffect) {
        edgeEffect_ = EdgeEffect::NONE;
    } else {
        edgeEffect_ = EdgeEffect::SPRING;
    }
}

void JSList::SetInitialIndex(int32_t initialIndex)
{
    initialIndex_ = initialIndex;
}

void JSList::InitDivider(const RefPtr<Component>& child)
{
    auto item = ListItemComponent::GetListItem(child);
    if (!item) {
        LOGW("InitDivider: no list item in child");
        return;
    }
    if (needDivider_) {
        item->MarkNeedDivider(needDivider_);
        item->SetDividerColor(dividerColor_);
        item->SetDividerHeight(dividerHeight_);
        item->SetDividerLength(dividerLength_);
        item->SetDividerOrigin(dividerOffset_);
        LOGD("divider: height(%{public}lf), length(%{public}lf), Origin(%{public}lf), color(%{public}x)",
            dividerHeight_.Value(), dividerLength_.Value(), dividerOffset_.Value(), dividerColor_.GetValue());
    }
}

void JSList::InitScrollBarTheme()
{
    if (!scrollBar_ || displayMode_ == DisplayMode::OFF) {
        LOGD("ScrollBar is Off, no need set this");
        return;
    }

    // Set scrollBar theme
    RefPtr<ScrollBarTheme> scrollBarTheme = GetTheme<ScrollBarTheme>();
    if (scrollBarTheme) {
        if (scrollBar_->GetShapeMode() == ShapeMode::DEFAULT) {
            scrollBar_->SetShapeMode(scrollBarTheme->GetShapeMode());
        }
        scrollBar_->SetInactiveWidth(scrollBarTheme->GetNormalWidth());
        scrollBar_->SetNormalWidth(scrollBarTheme->GetNormalWidth());
        scrollBar_->SetActiveWidth(scrollBarTheme->GetActiveWidth());
        scrollBar_->SetMinHeight(scrollBarTheme->GetMinHeight());
        scrollBar_->SetMinDynamicHeight(scrollBarTheme->GetMinDynamicHeight());
        scrollBar_->SetReservedHeight(scrollBarTheme->GetReservedHeight());
        scrollBar_->SetTouchWidth(scrollBarTheme->GetTouchWidth());
        scrollBar_->SetBackgroundColor(scrollBarTheme->GetBackgroundColor());
        scrollBar_->SetForegroundColor(scrollBarTheme->GetForegroundColor());
        scrollBar_->SetPadding(scrollBarTheme->GetPadding());
    }
}

void JSList::JSBind(BindingTarget globalObj)
{
    JSClass<JSList>::Declare("List");
    JSClass<JSList>::Inherit<JSViewAbstract>();

    MethodOptions opt = MethodOptions::RETURN_SELF;
    // Bind the method here
    LOGD("JSList V8Bind start.");
    JSClass<JSList>::Method("listDirection", &JSList::SetFlexDirection, opt);
    JSClass<JSList>::Method("scrollBar", &JSList::SetScrollBarState, opt);
    JSClass<JSList>::Method("scrollEffect", &JSList::SetScrollEffect, opt);
    JSClass<JSList>::Method("initialIndex", &JSList::SetInitialIndex, opt);
    JSClass<JSList>::CustomMethod("divider", &JSList::SetDivider);
    JSClass<JSList>::CustomMethod("onScroll", &JSList::ScrollCallback);
    JSClass<JSList>::CustomMethod("onReachStart", &JSList::ReachStartCallback);
    JSClass<JSList>::CustomMethod("onReachEnd", &JSList::ReachEndCallback);
    JSClass<JSList>::CustomMethod("onScrollStop", &JSList::ScrollStopCallback);
    JSClass<JSList>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSList>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSList>::Bind(globalObj, ConstructorCallback);
    LOGD("JSList V8Bind end.");
}

#ifdef USE_QUICKJS_ENGINE
void JSList::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSList => MarkGC: start");
    JSContainerBase::MarkGC(rt, markFunc);
    LOGD("JSList => MarkGC: end");
}

void JSList::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSList => release children: start");
    JSContainerBase::ReleaseRT(rt);
    LOGD("JSList => release children: end");
}

// STATIC qjs_class_bindings
JSValue JSList::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSList::ConstructorCallback");
    QJSContext::Scope scope(ctx);
    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);
    JSList* list = new JSList(children, jsChildren);
    return Wrap<JSList>(new_target, list);
}

void JSList::QjsDestructor(JSRuntime* rt, JSList* view)
{
    LOGD("JSList(QjsDestructor) start");
    if (!view) {
        return;
    }

    view->ReleaseRT(rt);
    delete view;
    view = nullptr;
    LOGD("JSList(QjsDestructor) end");
}

void JSList::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSList(QjsGcMark) start");
    JSList* view = Unwrap<JSList>(val);
    if (!view) {
        return;
    }

    view->MarkGC(rt, markFunc);
    LOGD("JSList(QjsGcMark) end");
}

JSValue JSList::SetDivider(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsObject(argv[0]) || JS_IsArray(ctx, argv[0]) || JS_IsFunction(ctx, argv[0])) {
        LOGE("divider expects a object as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "divider expects a object as parameter");
    }
    JSList* list = Unwrap<JSList>(jsList);

    if (list == nullptr) {
        LOGE("divider must be called on a JSList. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "divider must be called on a JSList");
    }

    JSValue jsHeight = JS_GetPropertyStr(ctx, argv[0], "height");
    JSValue jsLength = JS_GetPropertyStr(ctx, argv[0], "length");
    JSValue jsOffset = JS_GetPropertyStr(ctx, argv[0], "offset");
    JSValue jsColor = JS_GetPropertyStr(ctx, argv[0], "color");
    if (JS_IsNumber(jsHeight)) {
        double height = 0.0;
        JS_ToFloat64(ctx, &height, jsHeight);
        list->dividerHeight_ = Dimension(height);
        list->needDivider_ = true;
    }
    if (JS_IsNumber(jsLength)) {
        double length = 0.0;
        JS_ToFloat64(ctx, &length, jsLength);
        list->dividerLength_ = Dimension(length);
        list->needDivider_ = true;
    }
    if (JS_IsNumber(jsOffset)) {
        double offset = 0.0;
        JS_ToFloat64(ctx, &offset, jsOffset);
        list->dividerOffset_ = Dimension(offset);
        list->needDivider_ = true;
    }

    if (JS_IsString(jsColor)) {
        const char* jsColorStr = JS_ToCString(ctx, JS_ToString(ctx, jsColor));
        if (jsColorStr) {
            std::string color(jsColorStr);
            list->dividerColor_ = Color::FromString(color);
            list->needDivider_ = true;
        }
        auto listTheme = list->GetTheme<ListTheme>();
        if (list->dividerColor_ == Color::TRANSPARENT && listTheme) {
            LOGD("Use the color of the theme");
            list->dividerColor_ = listTheme->GetDividerColor();
        }
    }
    JS_FreeValue(ctx, jsHeight);
    JS_FreeValue(ctx, jsLength);
    JS_FreeValue(ctx, jsOffset);
    JS_FreeValue(ctx, jsColor);
    return JS_DupValue(ctx, jsList);
}

JSValue JSList::ScrollCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("scrollCallback expects a function as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "scrollCallback expects a function as parameter");
    }
    QJSContext::Scope scope(ctx);
    JSList* list = Unwrap<JSList>(jsList);

    if (list == nullptr) {
        LOGE("scrollCallback must be called on a JSList. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "scrollCallback must be called on a JSList");
    }

    list->onScrollFunc_ = AceType::MakeRefPtr<QJSEventFunction<ScrollEventInfo, 1>>(
        ctx, JS_DupValue(ctx, argv[0]), ScrollEventInfoToJSValue);
    return JS_DupValue(ctx, jsList);
}

JSValue JSList::ReachStartCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("reachStart expects a function as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "reachStart expects a function as parameter");
    }
    QJSContext::Scope scope(ctx);
    JSList* list = Unwrap<JSList>(jsList);

    if (list == nullptr) {
        LOGE("reachStart must be called on a JSList. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "reachStart must be called on a JSList");
    }

    list->onReachStartFunc_ = AceType::MakeRefPtr<QJSEventFunction<ScrollEventInfo, 1>>(
        ctx, JS_DupValue(ctx, argv[0]), ScrollEventInfoToJSValue);
    return JS_DupValue(ctx, jsList);
}

JSValue JSList::ReachEndCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("reachEnd expects a function as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "reachEnd expects a function as parameter");
    }
    QJSContext::Scope scope(ctx);
    JSList* list = Unwrap<JSList>(jsList);

    if (list == nullptr) {
        LOGE("reachEnd must be called on a JSList. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "reachEnd must be called on a JSList");
    }

    list->onReachEndFunc_ = AceType::MakeRefPtr<QJSEventFunction<ScrollEventInfo, 1>>(
        ctx, JS_DupValue(ctx, argv[0]), ScrollEventInfoToJSValue);
    return JS_DupValue(ctx, jsList);
}

JSValue JSList::ScrollStopCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("scrollStop expects a function as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "scrollStop expects a function as parameter");
    }
    QJSContext::Scope scope(ctx);
    JSList* list = Unwrap<JSList>(jsList);

    if (list == nullptr) {
        LOGE("scrollStop must be called on a JSList. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "scrollStop must be called on a JSList");
    }

    list->onScrollStopFunc_ = AceType::MakeRefPtr<QJSEventFunction<ScrollEventInfo, 1>>(
        ctx, JS_DupValue(ctx, argv[0]), ScrollEventInfoToJSValue);
    return JS_DupValue(ctx, jsList);
}
#elif USE_V8_ENGINE
void JSList::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSList>::New(args.This(), children, jsChildren);
    LOGD("ConstructorCallback children size %{public}lu", children.size());
    args.GetReturnValue().Set(instance->Get());
}

void JSList::SetDivider(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    LOGD("V8 set divider");
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    ACE_DCHECK(isolate);
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    if (context.IsEmpty()) {
        LOGE("Context Is Empty");
        return;
    }
    if (info[0]->IsObject()) {
        LOGD("V8 need divider");
        needDivider_ = true;
        v8::Local<v8::Object> obj = info[0]->ToObject(context).ToLocalChecked();
        v8::MaybeLocal<v8::Value> lengthValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "length").ToLocalChecked());
        v8::MaybeLocal<v8::Value> heightValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked());
        v8::MaybeLocal<v8::Value> offsetValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "offset").ToLocalChecked());
        v8::MaybeLocal<v8::Value> colorValue =
            obj->Get(context, v8::String::NewFromUtf8(isolate, "color").ToLocalChecked());

        if (heightValue.ToLocalChecked()->IsNumber()) {
            double height = V8ValueConvertor::fromV8Value<double>(heightValue.ToLocalChecked());
            dividerHeight_ = Dimension(height);
        }
        if (lengthValue.ToLocalChecked()->IsNumber()) {
            double length = V8ValueConvertor::fromV8Value<double>(lengthValue.ToLocalChecked());
            dividerLength_ = Dimension(length);
        }
        if (offsetValue.ToLocalChecked()->IsNumber()) {
            double offset = V8ValueConvertor::fromV8Value<double>(offsetValue.ToLocalChecked());
            dividerOffset_ = Dimension(offset);
        }
        if (!colorValue.ToLocalChecked()->IsNumber()) {
            std::string color = V8ValueConvertor::fromV8Value<std::string>(colorValue.ToLocalChecked());
            dividerColor_ = Color::FromString(color);
        }
        RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
        if (dividerColor_ == Color::TRANSPARENT && listTheme) {
            LOGD("Use the color of the theme");
            dividerColor_ = listTheme->GetDividerColor();
        }
    }
    info.GetReturnValue().Set(info.This());
}

void JSList::ScrollCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args[0]->IsFunction()) {
        onScrollFunc_ = AceType::MakeRefPtr<V8EventFunction<ScrollEventInfo, 1>>(
            v8::Local<v8::Function>::Cast(args[0]), ScrollEventInfoToJSValue);
    }
    args.GetReturnValue().Set(args.This());
}

void JSList::ReachStartCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args[0]->IsFunction()) {
        onReachStartFunc_ = AceType::MakeRefPtr<V8EventFunction<ScrollEventInfo, 1>>(
            v8::Local<v8::Function>::Cast(args[0]), ScrollEventInfoToJSValue);
    }
    args.GetReturnValue().Set(args.This());
}

void JSList::ReachEndCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args[0]->IsFunction()) {
        onReachEndFunc_ = AceType::MakeRefPtr<V8EventFunction<ScrollEventInfo, 1>>(
            v8::Local<v8::Function>::Cast(args[0]), ScrollEventInfoToJSValue);
    }
    args.GetReturnValue().Set(args.This());
}

void JSList::ScrollStopCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args[0]->IsFunction()) {
        onScrollStopFunc_ = AceType::MakeRefPtr<V8EventFunction<ScrollEventInfo, 1>>(
            v8::Local<v8::Function>::Cast(args[0]), ScrollEventInfoToJSValue);
    }
    args.GetReturnValue().Set(args.This());
}
#endif

} // namespace OHOS::Ace::Framework
