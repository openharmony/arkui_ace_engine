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

#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"

#include "base/log/ace_trace.h"
#include "core/components/foreach/foreach_component.h"

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSStack::JSStack(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("Stack(children: [%lu])", children_.size());
}
#else
JSStack::JSStack(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("Stack(children: [%lu])", children_.size());
}
#endif

JSStack::~JSStack()
{
    LOGD("Destroy: JSStack");
};

RefPtr<OHOS::Ace::Component> JSStack::CreateSpecializedComponent()
{
    LOGD("Create with align: %s", alignment_.ToString().c_str());

    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    for (auto jsViewChild : children_) {
        auto component = jsViewChild->CreateComponent();
        if (AceType::TypeName<ForEachComponent>() == AceType::TypeName(component)) {
            auto children = AceType::DynamicCast<ForEachComponent>(component)->GetChildren();
            for (auto childComponent : children) {
                componentChildren.emplace_back(childComponent);
            }
        } else {
            componentChildren.emplace_back(component);
        }
    }

    LOGD("Create component: Stack");
    RefPtr<OHOS::Ace::StackComponent> component =
        AceType::MakeRefPtr<StackComponent>(alignment_, stackFit_, overflow_, componentChildren);

    // Refresh component
    component->SetAlignment(alignment_);
    component->SetStackFit(stackFit_);
    component->SetOverflow(overflow_);

    return component;
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSStack::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

void JSStack::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSStack::Destroy start");
    JSContainerBase::Destroy(parentCustomView);
    LOGD("JSStack::Destroy end");
}

#ifdef USE_QUICKJS_ENGINE
void JSStack::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSStack => MarkGC: start");
    JSContainerBase::MarkGC(rt, markFunc);
    LOGD("JSStack => MarkGC: end");
}

void JSStack::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSStack => release children: start");
    JSContainerBase::ReleaseRT(rt);
    LOGD("JSStack => release children: end");
}

// STATIC qjs_class_bindings
JSValue JSStack::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSStack::ConstructorCallback");

    QJSContext::Scope scope(ctx);

    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);

    JSStack* stack = new JSStack(children, jsChildren);

    return Wrap(new_target, stack);
}

void JSStack::QjsDestructor(JSRuntime* rt, JSStack* view)
{
    LOGD("JSStack(QjsDestructor) start");
    if (!view) {
        return;
    }

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSStack(QjsDestructor) end");
}

void JSStack::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSStack(QjsGcMark) start");
    JSStack* view = Unwrap<JSStack>(val);
    if (!view) {
        return;
    }

    view->MarkGC(rt, markFunc);
    LOGD("JSStack(QjsGcMark) end");
}
#endif

void JSStack::SetStackFit(int value)
{
    if (value >= (int)StackFit::KEEP && value <= (int)StackFit::FIRST_CHILD) {
        stackFit_ = (StackFit)value;
    } else {
        LOGE("Invaild value for stackfit");
    }
}

void JSStack::SetOverflow(int value)
{
    if (value >= (int)Overflow::CLIP && value <= (int)Overflow::OBSERVABLE) {
        overflow_ = (Overflow)value;
    } else {
        LOGE("Invaild value for overflow");
    }
}

void JSStack::SetAlignment(int value)
{
    Alignment alignment = Alignment::TOP_LEFT;

    switch (value) {
        case 0:
            alignment = Alignment::TOP_LEFT;
            break;
        case 1:
            alignment = Alignment::TOP_CENTER;
            break;
        case 2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case 3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case 4:
            alignment = Alignment::CENTER;
            break;
        case 5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case 6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case 7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case 8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            LOGE("Invaild value for alignment");
            return;
    }

    alignment_ = alignment;
}

void JSStack::JSBind(BindingTarget globalObj)
{
    JSClass<JSStack>::Declare("Stack");
    JSClass<JSStack>::Inherit<JSViewAbstract>();

    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSStack>::Method("stackFit", &JSStack::SetStackFit, opt);
    JSClass<JSStack>::Method("overflow", &JSStack::SetOverflow, opt);
    JSClass<JSStack>::Method("alignment", &JSStack::SetAlignment, opt);
    JSClass<JSStack>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSStack>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSStack>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSStack::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSStack>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}

#endif

} // namespace OHOS::Ace::Framework
