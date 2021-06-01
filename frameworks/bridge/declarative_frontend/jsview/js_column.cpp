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

#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"

#include "base/log/ace_trace.h"

namespace OHOS::Ace::Framework {

template<>
RefPtr<OHOS::Ace::FlexComponent> JSFlex<ColumnComponent>::ComponentForType(
    FlexAlign mainAxisAlign, FlexAlign crossAxisAlign, const std::list<RefPtr<Component>>& children)
{
    auto columnComponent = AceType::MakeRefPtr<ColumnComponent>(mainAxisAlign, crossAxisAlign, children);
    if (columnComponent && GetIsDefWidth()) {
        columnComponent->SetCrossAxisSize(CrossAxisSize::MAX);
    }
    return columnComponent;
}

bool JSColumn::IsHorizontal() const
{
    return false;
}

void JSColumn::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSColumn::Destroy start");
    JSContainerBase::Destroy(parentCustomView);
    LOGD("JSColumn::Destroy end");
}

#ifdef USE_QUICKJS_ENGINE
// STATIC qjs_class_bindings
JSValue JSColumn::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSColumn::ConstructorCallback");
    auto flex = [](std::list<JSViewAbstract*> children, std::list<JSValue> jsChildren) {
        return new JSColumn(children, jsChildren);
    };
    return JSFlex<ColumnComponent>::JsFlexConstructorInternal<JSColumn>(ctx, new_target, argc, argv, flex);
}

void JSColumn::QjsDestructor(JSRuntime* rt, JSColumn* view)
{
    LOGD("JSColumn(QjsDestructor) start");
    if (!view)
        return;
    view->ReleaseRT(rt);
    delete view;
    LOGD("JSColumn(QjsDestructor) end");
}

void JSColumn::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSColumn(QjsGcMark) start");
    JSColumn* view = Unwrap<JSColumn>(val);
    if (!view)
        return;

    view->MarkGC(rt, markFunc);
    LOGD("JSColumn(QjsGcMark) end");
}
#endif // USE_QUICKJS_ENGINE

void JSColumn::JSBind(BindingTarget globalObj)
{
    JSClass<JSColumn>::Declare("Column");
    JSClass<JSColumn>::Inherit<JSViewAbstract>();

    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSColumn>::Method("fillParent", &JSFlex::SetFillParent, opt);
    JSClass<JSColumn>::Method("wrapContent", &JSFlex::SetWrapContent, opt);
    JSClass<JSColumn>::Method("justifyContent", &JSFlex::SetJustifyContent, opt);
    JSClass<JSColumn>::Method("alignItems", &JSFlex::SetAlignItems, opt);
    JSClass<JSColumn>::Method("wrap", &JSFlex::SetWrap, opt);
    JSClass<JSColumn>::Method("alignContent", &JSFlex::SetAlignContent, opt);
    JSClass<JSColumn>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSColumn>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
#ifdef USE_V8_ENGINE
    JSClass<JSColumn>::CustomMethod("onPan", &JSInteractableView::JsOnPan);
#endif
    JSClass<JSColumn>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSColumn::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8FlexConstructorInternal(args, children, jsChildren);
    auto instance = V8Object<JSColumn>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}

#endif

} // namespace OHOS::Ace::Framework
