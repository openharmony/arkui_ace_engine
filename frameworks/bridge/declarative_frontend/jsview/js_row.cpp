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

#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"

#include "base/log/ace_trace.h"

namespace OHOS::Ace::Framework {

template<>
RefPtr<OHOS::Ace::FlexComponent> JSFlex<RowComponent>::ComponentForType(
    FlexAlign mainAxisAlign, FlexAlign crossAxisAlign, const std::list<RefPtr<Component>>& children)
{
    auto rowComponent = AceType::MakeRefPtr<RowComponent>(mainAxisAlign, crossAxisAlign, children);
    if (rowComponent && GetIsDefHeight()) {
        rowComponent->SetCrossAxisSize(CrossAxisSize::MAX);
    }
    return rowComponent;
}

bool JSRow::IsHorizontal() const
{
    return true;
}

void JSRow::Destroy(JSViewAbstract* parentCustomView)
{
    LOGD("JSRow::Destroy start");
    JSContainerBase::Destroy(parentCustomView);
    LOGD("JSRow::Destroy end");
}

#ifdef USE_QUICKJS_ENGINE
// STATIC qjs_class_bindings
JSValue JSRow::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSRow::ConstructorCallback");
    auto flex = [](std::list<JSViewAbstract*> children, std::list<JSValue> jsChildren) {
        return new JSRow(children, jsChildren);
    };
    return JSFlex<RowComponent>::JsFlexConstructorInternal<JSRow>(ctx, new_target, argc, argv, flex);
}

void JSRow::QjsDestructor(JSRuntime* rt, JSRow* view)
{
    LOGD("JSRow(QjsDestructor) start");
    if (!view)
        return;
    view->ReleaseRT(rt);
    delete view;
    LOGD("JSRow(QjsDestructor) end");
}

void JSRow::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSRow(QjsGcMark) start");
    JSRow* view = Unwrap<JSRow>(val);
    if (!view)
        return;

    view->MarkGC(rt, markFunc);
    LOGD("JSRow(QjsGcMark) end");
}
#endif // USE_QUICKJS_ENGINE

void JSRow::JSBind(BindingTarget globalObj)
{
    JSClass<JSRow>::Declare("Row");
    JSClass<JSRow>::Inherit<JSViewAbstract>();

    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSRow>::Method("fillParent", &JSFlex::SetFillParent, opt);
    JSClass<JSRow>::Method("wrapContent", &JSFlex::SetWrapContent, opt);
    JSClass<JSRow>::Method("justifyContent", &JSFlex::SetJustifyContent, opt);
    JSClass<JSRow>::Method("alignItems", &JSFlex::SetAlignItems, opt);
    JSClass<JSRow>::Method("wrap", &JSFlex::SetWrap, opt);
    JSClass<JSRow>::Method("alignContent", &JSFlex::SetAlignContent, opt);
    JSClass<JSRow>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRow>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRow>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSRow::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8FlexConstructorInternal(args, children, jsChildren);
    auto instance = V8Object<JSRow>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}

#endif

} // namespace OHOS::Ace::Framework
