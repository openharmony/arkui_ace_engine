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

#include "frameworks/bridge/declarative_frontend/jsview/js_sliding_panel.h"

#include <algorithm>
#include <iterator>

#include "core/components/foreach/foreach_component.h"
#include "core/components/panel/sliding_panel_component.h"

namespace OHOS::Ace::Framework {
namespace {

#ifdef USE_QUICKJS_ENGINE
JSValue SlidingPanelSizeChangeEventToJSValue(const SlidingPanelSizeChangeEvent& eventInfo, JSContext* ctx)
{
    JSValue eventObj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, eventObj, "width", JS_NewFloat64(ctx, eventInfo.GetWidth()));
    JS_SetPropertyStr(ctx, eventObj, "height", JS_NewFloat64(ctx, eventInfo.GetHeight()));

    const PanelMode& mode = eventInfo.GetMode();
    if (mode == PanelMode::FULL) {
        JS_SetPropertyStr(ctx, eventObj, "mode", JS_NewString(ctx, "full"));
    } else if (mode == PanelMode::MINI) {
        JS_SetPropertyStr(ctx, eventObj, "mode", JS_NewString(ctx, "mini"));
    } else {
        JS_SetPropertyStr(ctx, eventObj, "mode", JS_NewString(ctx, "half"));
    }
    return eventObj;
}
#elif USE_V8_ENGINE
v8::Local<v8::Value> SlidingPanelSizeChangeEventToJSValue(
    const SlidingPanelSizeChangeEvent& eventInfo, v8::Isolate* isolate)
{
    ACE_DCHECK(isolate);
    auto context = isolate->GetCurrentContext();
    v8::Local<v8::Object> obj = v8::Object::New(isolate);
    std::string modeStr = "half";
    const PanelMode& mode = eventInfo.GetMode();
    if (mode == PanelMode::FULL) {
        modeStr = "full";
    } else if (mode == PanelMode::MINI) {
        modeStr = "mini";
    }
    obj->Set(context, v8::String::NewFromUtf8(isolate, "mode").ToLocalChecked(),
           v8::String::NewFromUtf8(isolate, modeStr.c_str()).ToLocalChecked())
        .ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "width").ToLocalChecked(),
           v8::Number::New(isolate, eventInfo.GetWidth()))
        .ToChecked();
    obj->Set(context, v8::String::NewFromUtf8(isolate, "height").ToLocalChecked(),
           v8::Number::New(isolate, eventInfo.GetHeight()))
        .ToChecked();
    return v8::Local<v8::Value>(obj);
}
#endif

} // namespace

#ifdef USE_QUICKJS_ENGINE
JSSlidingPanel::JSSlidingPanel(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("JSSlidingPanel(children: [%lu])", children_.size());
}
#elif USE_V8_ENGINE
JSSlidingPanel::JSSlidingPanel(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("JSSlidingPanel(children: [%lu])", children_.size());
}
#endif

JSSlidingPanel::~JSSlidingPanel()
{
    LOGD("Destroy: JSSlidingPanel");
};

void JSSlidingPanel::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSSlidingPanel::Destroy start");
    JSContainerBase::Destroy(parentCustomView);
    LOGD("JSSlidingPanel::Destroy end");
}

RefPtr<OHOS::Ace::Component> JSSlidingPanel::CreateSpecializedComponent()
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
    // support only one child
    RefPtr<OHOS::Ace::Component> child;
    if (!componentChildren.empty()) {
        child = componentChildren.front();
    }
    RefPtr<OHOS::Ace::PanelComponent> panelComponent =
        AceType::MakeRefPtr<OHOS::Ace::PanelComponent>("PanelComponent", "Wrapper", child);
    PreparePanelComponent(panelComponent);

    return SlidingPanelComponent::Create(panelComponent);
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSSlidingPanel::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

void JSSlidingPanel::JSBind(BindingTarget globalObj)
{
    JSClass<JSSlidingPanel>::Declare("Panel");
    JSClass<JSSlidingPanel>::Inherit<JSViewAbstract>();
    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSSlidingPanel>::Method("dragBar", &JSSlidingPanel::SetHasDragBar, opt);
    JSClass<JSSlidingPanel>::Method("show", &JSSlidingPanel::SetShow, opt);
    JSClass<JSSlidingPanel>::Method("mode", &JSSlidingPanel::SetPanelMode, opt);
    JSClass<JSSlidingPanel>::Method("type", &JSSlidingPanel::SetPanelType, opt);
    JSClass<JSSlidingPanel>::Method("fullHeight", &JSSlidingPanel::SetFullHeight, opt);
    JSClass<JSSlidingPanel>::Method("halfHeight", &JSSlidingPanel::SetHalfHeight, opt);
    JSClass<JSSlidingPanel>::Method("miniHeight", &JSSlidingPanel::SetMiniHeight, opt);
    JSClass<JSSlidingPanel>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSlidingPanel>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSSlidingPanel>::CustomMethod("onChange", &JSSlidingPanel::SetOnSizeChange);
    JSClass<JSSlidingPanel>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSSlidingPanel::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSSlidingPanel>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}

void JSSlidingPanel::SetOnSizeChange(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    auto isolate = args.GetIsolate();
    v8::HandleScope scp(isolate);
    if (args[0]->IsFunction()) {
        onSizeChangeFunc_ = AceType::MakeRefPtr<V8EventFunction<SlidingPanelSizeChangeEvent, 1>>(
            v8::Local<v8::Function>::Cast(args[0]), SlidingPanelSizeChangeEventToJSValue);
    }
    args.GetReturnValue().Set(args.This());
}
#elif USE_QUICKJS_ENGINE
void JSSlidingPanel::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSSlidingPanel => MarkGC: start");
    JSContainerBase::MarkGC(rt, markFunc);

    LOGD("JSSlidingPanel => MarkGC: end");
}

void JSSlidingPanel::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSSlidingPanel => release children: start");
    JSContainerBase::ReleaseRT(rt);

    LOGD("JSSlidingPanel => release children: end");
}

// STATIC qjs_class_bindings
JSValue JSSlidingPanel::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSSlidingPanel::ConstructorCallback");

    QJSContext::Scope scope(ctx);

    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);

    JSSlidingPanel* panel = new JSSlidingPanel(children, jsChildren);

    return Wrap(new_target, panel);
}

void JSSlidingPanel::QjsDestructor(JSRuntime* rt, JSSlidingPanel* view)
{
    LOGD("JSSlidingPanel(QjsDestructor) start");
    if (!view) {
        return;
    }

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSSlidingPanel(QjsDestructor) end");
}

void JSSlidingPanel::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSSlidingPanel(QjsGcMark) start");
    JSSlidingPanel* view = Unwrap<JSSlidingPanel>(val);
    if (!view) {
        return;
    }

    view->MarkGC(rt, markFunc);
    LOGD("JSSlidingPanel(QjsGcMark) end");
}

JSValue JSSlidingPanel::SetOnSizeChange(JSContext* ctx, JSValue this_value, int32_t argc, JSValue* argv)
{
    if ((argc != 1) || !JS_IsFunction(ctx, argv[0])) {
        LOGE("sizeChange expects a function as parameter. Throwing exception.");
        return JS_ThrowSyntaxError(ctx, "sizeChange() expect a function parameter. Throwing exception");
    }

    QJSContext::Scope scope(ctx);
    // Dup and Free shoulj happen inside the QJSClickFunction

    onSizeChangeFunc_ = AceType::MakeRefPtr<QJSEventFunction<SlidingPanelSizeChangeEvent, 1>>(
        ctx, JS_DupValue(ctx, argv[0]), SlidingPanelSizeChangeEventToJSValue);

    return JS_DupValue(ctx, this_value); // for call chaining
}

#endif

void JSSlidingPanel::PreparePanelComponent(RefPtr<OHOS::Ace::PanelComponent>& panelComponent)
{
    // adjust panel mode
    if (type_ == PanelType::TEMP_DISPLAY && mode_ == PanelMode::MINI) {
        mode_ = PanelMode::HALF;
    } else if (type_ == PanelType::MINI_BAR && mode_ == PanelMode::HALF) {
        mode_ = PanelMode::MINI;
    }
    panelComponent->SetPanelMode(mode_);
    panelComponent->SetPanelType(type_);
    panelComponent->SetHasDragBar(hasDragBar_);
    panelComponent->SetMiniHeight(miniHeight_);
    panelComponent->SetHalfHeight(halfHeight_);
    panelComponent->SetFullHeight(fullHeight_);

    if (!displayComponent_) {
        displayComponent_ = AceType::MakeRefPtr<DisplayComponent>();
    }
    displayComponent_->SetVisible(isShow_ ? VisibleType::VISIBLE : VisibleType::GONE);

    if (onSizeChangeFunc_) {
        auto onSizeChange = EventMarker([func = std::move(onSizeChangeFunc_)](const BaseEventInfo* param) {
            auto sizeChange = TypeInfoHelper::DynamicCast<SlidingPanelSizeChangeEvent>(param);
            if (!sizeChange) {
                LOGE("HandleSizeChangeEvent, sizeChange == nullptr");
                return;
            }
            func->execute(*sizeChange);
        });
        panelComponent->SetOnSizeChanged(onSizeChange);
    }

    if (boxComponent_) {
        panelComponent->SetHasBoxStyle(true);
        panelComponent->SetHasDecorationStyle(true);
        panelComponent->SetHasBackgroundColor(true);
        panelComponent->SetHasBorderStyle(true);
        panelComponent->SetBoxStyle(boxComponent_);
        boxComponent_ = nullptr;
    } else {
        panelComponent->SetBoxStyle(AceType::MakeRefPtr<BoxComponent>());
    }
}

void JSSlidingPanel::SetHasDragBar(bool hasDragBar)
{
    hasDragBar_ = hasDragBar;
}

void JSSlidingPanel::SetShow(bool isShow)
{
    isShow_ = isShow;
}

void JSSlidingPanel::SetPanelMode(int32_t mode)
{
    if (static_cast<int>(PanelMode::HALF) == mode) {
        mode_ = PanelMode::HALF;
    } else if (static_cast<int>(PanelMode::MINI) == mode) {
        mode_ = PanelMode::MINI;
    } else {
        mode_ = PanelMode::FULL;
    }
}

void JSSlidingPanel::SetPanelType(int32_t type)
{
    if (static_cast<int>(PanelType::MINI_BAR) == type) {
        type_ = PanelType::MINI_BAR;
    } else if (static_cast<int>(PanelType::TEMP_DISPLAY) == type) {
        type_ = PanelType::TEMP_DISPLAY;
    } else {
        type_ = PanelType::FOLDABLE_BAR;
    }
}

void JSSlidingPanel::SetMiniHeight(const std::string& height)
{
    miniHeight_.first = StringUtils::StringToDimension(height, true);
    miniHeight_.second = true;
}

void JSSlidingPanel::SetHalfHeight(const std::string& height)
{
    halfHeight_.first = StringUtils::StringToDimension(height, true);
    halfHeight_.second = true;
}

void JSSlidingPanel::SetFullHeight(const std::string& height)
{
    fullHeight_.first = StringUtils::StringToDimension(height, true);
    fullHeight_.second = true;
}

} // namespace OHOS::Ace::Framework
