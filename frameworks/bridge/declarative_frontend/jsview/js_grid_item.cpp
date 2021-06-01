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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid_item.h"

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSGridItem::JSGridItem(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren)
#else
JSGridItem::JSGridItem(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
#endif
{
    LOGD("JSGridItem");
}

JSGridItem::~JSGridItem()
{
    LOGD("Destroy: JSGridItem");
};

RefPtr<OHOS::Ace::Component> JSGridItem::CreateSpecializedComponent()
{
    LOGD("Create component: GridItem");
    if (children_.empty()) {
        return nullptr;
    }

    auto child = children_.front();
    if (!child) {
        LOGE("grid item has no child");
        return nullptr;
    }
    auto component = child->CreateComponent();
    auto itemComponent = AceType::MakeRefPtr<GridLayoutItemComponent>(component);
    itemComponent->SetRowIndex(rowStart_);
    itemComponent->SetColumnIndex(columnStart_);
    itemComponent->SetRowSpan(rowEnd_ - rowStart_ + 1);
    itemComponent->SetColumnSpan(columnEnd_ - columnStart_ + 1);

    return itemComponent;
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSGridItem::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

void JSGridItem::SetColumnStart(int32_t columnStart)
{
    columnStart_ = columnStart;
}

void JSGridItem::SetColumnEnd(int32_t columnEnd)
{
    columnEnd_ = columnEnd;
}

void JSGridItem::SetRowStart(int32_t rowStart)
{
    rowStart_ = rowStart;
}

void JSGridItem::SetRowEnd(int32_t rowEnd)
{
    rowEnd_ = rowEnd;
}

#ifdef USE_QUICKJS_ENGINE
void JSGridItem::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSGridItem => MarkGC: Mark value for GC start");
    JSContainerBase::MarkGC(rt, markFunc);
    LOGD("JSGridItem => MarkGC: Mark value for GC end");
}

void JSGridItem::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSGridItem => release start");
    JSContainerBase::ReleaseRT(rt);
    LOGD("JSGridItem => release end");
}

// STATIC qjs_class_bindings
JSValue JSGridItem::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSGrid::ConstructorCallback");
    QJSContext::Scope scope(ctx);
    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);
    JSGridItem* item = new JSGridItem(children, jsChildren);
    return Wrap<JSGridItem>(new_target, item);
}

void JSGridItem::QjsDestructor(JSRuntime* rt, JSGridItem* view)
{
    LOGD("JSGridItem(QjsDestructor) start");

    if (!view) {
        return;
    }

    view->ReleaseRT(rt);
    delete view;
    view = nullptr;
    LOGD("JSGridItem(QjsDestructor) end");
}

void JSGridItem::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSGridItem(QjsGcMark) start");

    JSGridItem* item = Unwrap<JSGridItem>(val);
    if (!item) {
        return;
    }

    item->MarkGC(rt, markFunc);
    LOGD("JSGridItem(QjsGcMark) end");
}
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE
void JSGridItem::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("GridItem:ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSGridItem>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}
#endif // USE_V8_ENGINE

void JSGridItem::JSBind(BindingTarget globalObj)
{
    LOGD("GridItem:JSBind");
    JSClass<JSGridItem>::Declare("GridItem");
    JSClass<JSGridItem>::Inherit<JSViewAbstract>();
    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSGridItem>::Method("columnStart", &JSGridItem::SetColumnStart, opt);
    JSClass<JSGridItem>::Method("columnEnd", &JSGridItem::SetColumnEnd, opt);
    JSClass<JSGridItem>::Method("rowStart", &JSGridItem::SetRowStart, opt);
    JSClass<JSGridItem>::Method("rowEnd", &JSGridItem::SetRowEnd, opt);
    JSClass<JSGridItem>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSGridItem>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGridItem>::Bind(globalObj, ConstructorCallback);
}

} // namespace OHOS::Ace::Framework
