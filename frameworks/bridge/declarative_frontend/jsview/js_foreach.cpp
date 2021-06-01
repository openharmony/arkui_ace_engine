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

#include "frameworks/bridge/declarative_frontend/jsview/js_foreach.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_customview_base.h"
#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"
#endif

#include "base/log/ace_trace.h"
#include "core/components/foreach/foreach_component.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSForEach::JSForEach(QJSForEachFunction* jsForEachFunction)
#else
JSForEach::JSForEach(V8ForEachFunction* jsForEachFunction)
#endif
    : jsForEachFunction_(jsForEachFunction)
{
    LOGD("ForEach constructor");
};

JSForEach::~JSForEach()
{
    if (jsForEachFunction_) {
        delete jsForEachFunction_;
    }
    LOGD("Destroy: JSForEach");
};

RefPtr<OHOS::Ace::Component> JSForEach::CreateSpecializedComponent()
{
    LOGD("Create component: JSForEach");

    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    std::vector<std::tuple<std::string, JSViewAbstract*>> items;
    std::vector<std::string> keys = jsForEachFunction_->executeIdentityMapper();

    for (size_t i = 0; i < keys.size(); i++) {
        keys[i].insert(0, "_");
        keys[i].insert(0, transpilerGeneratedViewId_);
        parentCustomView_->StartHandlingForEach(keys[i]);
        std::vector<JSViewAbstract*> views = jsForEachFunction_->executeBuilderForIndex(i);
        parentCustomView_->EndHandlingForEachKeys();
        for (auto view : views) {
            items.emplace_back(std::make_tuple(keys[i], view));
        }
    }

    itemsCount_ = items.size();
    if (items.size() > 0) {
        firstItemKey_ = HasUniqueKey() ? GetUniqueKey().append(std::get<0>(items[0])) : std::get<0>(items[0]);
    }

    bool shouldSetElementFunction = true;
    for (auto const& item : items) {
        std::string key = HasUniqueKey() ? GetUniqueKey().append(std::get<0>(item)) : std::get<0>(item);
        JSViewAbstract* view = std::get<1>(item);

        auto composedComponent =
            AceType::MakeRefPtr<OHOS::Ace::ComposedComponent>(key, "ForEachItemView", view->CreateComponent());

        if (shouldSetElementFunction) {
            // Get hold of the first item's element. It is used in the markNeedUpdate
            // to get the the parentElement_ (jsflex element).
            // We can't get parent here because the item is not yet inflated.
            auto elementFunction = [&](OHOS::Ace::ComposedElement* element) {
                if (!element_) {
                    element_ = element;
                }
            };
            composedComponent->SetElementFunction(std::move(elementFunction));
            shouldSetElementFunction = false;
        }

        componentChildren.emplace_back(composedComponent);
    }

    // create component, return new something, need to set proper ID
    auto forEachComponent = AceType::MakeRefPtr<OHOS::Ace::ForEachComponent>(componentChildren);
    return std::move(forEachComponent);
}

/**
 * marks the JSForEach's child's needing update / rerender
 */
void JSForEach::MarkNeedUpdate()
{
    if (needsUpdate_)
        return;

    needsUpdate_ = true;
    // This function will be called whenever the ForEach's array is a observableobject
    // and the array is mutated(for ex new item added/removed or items order changed).
    // This function will update the foreach item's elements in the parent element tree
    // i.e insert or remove or reorder the foreach items element in the parent.
    // Please remember that ForEach items element are always ComposedElement.

    // JSForEach doesnt know abt ctx, so moving the PostTask implementation
    // to for_each_function
    jsForEachFunction_->PostTask([&] {
        needsUpdate_ = false;

        if (!parentElement_) {
            if (!element_)
                return;
            auto parent = element_->GetElementParent().Upgrade();
            parentElement_ = AceType::RawPtr(parent);
        }

        // take hold of the items count and first item key before current update.
        int32_t olditemsCount = itemsCount_;
        std::string oldFirstItemkey = firstItemKey_;

        // execute the identifier function on the updated array to get the updated
        // new items identifier vector(the identifiers are uniquekeys). We will
        // use this to compare with last items elments in the parent
        std::vector<std::string> newItems = jsForEachFunction_->executeIdentityMapper();
        std::for_each(newItems.begin(), newItems.end(), [&](std::string& item) {
            if (HasUniqueKey())
                item = GetUniqueKey().append(item);
        });

        // updated items count and first item key
        firstItemKey_ = newItems[0];
        itemsCount_ = newItems.size();

        // on the parent element call UpdateComposedChildrenForEach
        // This will internally compare and update the foreach's new item elements
        // and reorder the existing foreach item elements.
        auto groupElement = AceType::DynamicCast<ComponentGroupElement>(parentElement_);
        groupElement->UpdateComposedChildrenForEach(
            oldFirstItemkey, olditemsCount, newItems, [&](int32_t index) -> RefPtr<Component> {
                auto view = jsForEachFunction_->executeBuilderForIndex(index);

                auto composedComponent = AceType::MakeRefPtr<OHOS::Ace::ComposedComponent>(
                    newItems[index], "ForEachItemView", view[0]->CreateComponent());

                return composedComponent;
            });
    });
}

void JSForEach::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSForEach::Destroy start");
    if (jsForEachFunction_) {
        jsForEachFunction_->Destroy(parentCustomView);
        delete jsForEachFunction_;
        jsForEachFunction_ = nullptr;
    }
    JSViewAbstract::Destroy(parentCustomView);
    LOGD("JSForEach::Destroy end");
}

#ifdef USE_QUICKJS_ENGINE
void JSForEach::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSForEach => MarkGC: start");
    if (jsForEachFunction_) {
        jsForEachFunction_->MarkGC(rt, markFunc);
    }
    LOGD("JSForEach => MarkGC: end");
}

void JSForEach::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSForEach => release: start");
    if (jsForEachFunction_) {
        jsForEachFunction_->ReleaseRT(rt);
    }
    LOGD("JSForEach => release: end");
}

JSValue JSForEach::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    QJSContext::Scope scope(ctx);

    if (argc < 4 || !JS_IsArray(ctx, argv[2]) || !JS_IsFunction(ctx, argv[3]) ||
        (!JS_IsString(argv[0]) && !JS_IsNumber(argv[0])) || JS_IsUndefined(argv[1]) || !JS_IsObject(argv[1])) {
        LOGE("qjs_forEach_constructor Invalid arguments for ForEach");
        return JS_NULL;
    }

    JSValue jsIdentityMapperFunc = JS_NULL;
    if (argc > 4 && JS_IsFunction(ctx, argv[4])) {
        jsIdentityMapperFunc = argv[4];
    }

    QJSForEachFunction* jsForEachFunction = new QJSForEachFunction(ctx, argv[2], jsIdentityMapperFunc, argv[3]);

    JSForEach* view = new JSForEach(jsForEachFunction);

    ScopedString viewId(argv[0]);
    JSCustomViewBase* parentView = static_cast<JSCustomViewBase*>(UnwrapAny(argv[1]));
    view->SetParentCustomView(parentView);
    view->SetTranspilerGeneratedViewId(viewId);

    return Wrap(new_target, view);
}

void JSForEach::QjsDestructor(JSRuntime* rt, JSForEach* view)
{
    LOGD("JSForEach(QjsDestructor) start");
    if (!view)
        return;

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSForEach(QjsDestructor) end");
}

void JSForEach::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSForEach(QjsGcMark) start");

    JSForEach* view = Unwrap<JSForEach>(val);
    if (!view)
        return;

    view->MarkGC(rt, markFunc);
    LOGD("JSForEach(QjsGcMark) end");
}
#endif

#ifdef USE_V8_ENGINE
void JSForEach::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    auto isolate = info.GetIsolate();
    v8::HandleScope scp(isolate);
    auto context = isolate->GetCurrentContext();

    if (!info[2]->IsObject() || !info[3]->IsFunction() || (!info[0]->IsNumber() && !info[0]->IsString()) ||
        info[1]->IsUndefined() || !info[1]->IsObject()) {
        LOGE("v8_foreach_constructor invalid arguments for ForEach");
        info.GetReturnValue().Set(info.This());
        return;
    }

    V8Utils::ScopedString viewId(info[0]);
    v8::Local<v8::Object> jsArray = v8::Local<v8::Object>::Cast(info[2]);
    v8::Local<v8::Function> jsIdentityMapperFunc;
    if (info.Length() > 4 && info[4]->IsFunction()) {
        jsIdentityMapperFunc = v8::Local<v8::Function>::Cast(info[4]);
    }
    v8::Local<v8::Function> jsViewMapperFunc = v8::Local<v8::Function>::Cast(info[3]);
    V8ForEachFunction* jsForEachFunction = new V8ForEachFunction(jsArray, jsIdentityMapperFunc, jsViewMapperFunc);

    auto instance = V8Object<JSForEach>::New(info.This(), jsForEachFunction);
    info.GetReturnValue().Set(instance->Get());

    v8::Local<v8::Object> parentObj = info[1]->ToObject(context).ToLocalChecked();
    JSCustomViewBase* parentView = static_cast<JSCustomViewBase*>(parentObj->GetAlignedPointerFromInternalField(0));
    JSForEach* view = instance->GetInstance();
    if (view) {
        view->SetParentCustomView(parentView);
        view->SetTranspilerGeneratedViewId(viewId);
    }
}
#endif

void JSForEach::JSBind(BindingTarget globalObj)
{
    JSClass<JSForEach>::Declare("ForEach");
    JSClass<JSForEach>::Inherit<JSViewAbstract>();
    JSClass<JSForEach>::Bind(globalObj, ConstructorCallback);
}
} // namespace OHOS::Ace::Framework
