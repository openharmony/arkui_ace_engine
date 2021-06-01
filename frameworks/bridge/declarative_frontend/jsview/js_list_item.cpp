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

#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"

#include "core/components/box/box_base_component.h"
#include "core/components/flex/flex_component.h"

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSListItem::JSListItem(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren)
#else
JSListItem::JSListItem(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
#endif
{
    LOGD("JSListItem, children size is %{public}lu", children_.size());
}

JSListItem::~JSListItem()
{
    LOGI("Destroy: JSListItem");
};

RefPtr<OHOS::Ace::Component> JSListItem::CreateSpecializedComponent()
{
    LOGD("Create component: ListItem");
    auto child = children_.front();
    if (!child) {
        LOGE("ListItem children is null");
        return nullptr;
    }
    auto component = child->CreateComponent();
    RefPtr<ListItemComponent> listItemComponent =
        AceType::MakeRefPtr<ListItemComponent>("default", RefPtr<Component>());
    RefPtr<FlexComponent> flexComponent = AceType::MakeRefPtr<FlexComponent>(
        FlexDirection::COLUMN, FlexAlign::FLEX_START, FlexAlign::FLEX_START, std::list<RefPtr<Component>>());
    flexComponent->AppendChild(component);
    listItemComponent->SetChild(flexComponent);
    listItemComponent->SetSupportClick(false);
    return AceType::MakeRefPtr<ComposedComponent>(GetUniqueKey(), "wrapper", std::move(listItemComponent));
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSListItem::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

#ifdef USE_QUICKJS_ENGINE

void JSListItem::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSListItem => MarkGC: Mark value for GC start");
    JSContainerBase::MarkGC(rt, markFunc);
    LOGD("JSListItem => MarkGC: Mark value for GC end");
}

void JSListItem::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSListItem => release start");
    for (JSValue const& jsChild : jsChildren_) {
        JS_FreeValueRT(rt, jsChild);
    }
    jsChildren_.clear();
    LOGD("JSListItem => release end");
}

// STATIC qjs_class_bindings
JSValue JSListItem::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSList::ConstructorCallback");
    QJSContext::Scope scope(ctx);
    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);
    JSListItem* item = new JSListItem(children, jsChildren);
    return Wrap<JSListItem>(new_target, item);
}

void JSListItem::QjsDestructor(JSRuntime* rt, JSListItem* view)
{
    LOGD("JSListItem(QjsDestructor) start");
    if (!view) {
        return;
    }
    view->ReleaseRT(rt);
    delete view;
    view = nullptr;
    LOGD("JSListItem(QjsDestructor) end");
}

void JSListItem::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSListItem(QjsGcMark) start");
    JSListItem* item = Unwrap<JSListItem>(val);
    if (!item) {
        return;
    }
    item->MarkGC(rt, markFunc);
    LOGD("JSListItem(QjsGcMark) end");
}

#endif // USE_QUICKJS_ENGINE

void JSListItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSListItem>::Declare("ListItem");
    JSClass<JSListItem>::Inherit<JSViewAbstract>();
    JSClass<JSListItem>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSListItem>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSListItem>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSListItem::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSListItem>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}

#endif

} // namespace OHOS::Ace::Framework
