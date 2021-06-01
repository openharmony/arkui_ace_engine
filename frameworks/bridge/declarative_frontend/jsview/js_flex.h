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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_FLEX_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_FLEX_H

#include <list>

#include "base/log/ace_trace.h"
#include "core/components/common/layout/constants.h"
#include "core/components/flex/flex_component.h"
#include "core/components/foreach/foreach_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

template<typename T>
class JSFlex : public JSContainerBase {
protected:
    // These need to be exposed in style setters
    FlexAlign mainAxisAlign_ { FlexAlign::FLEX_START };
    FlexAlign crossAxisAlign_ { FlexAlign::FLEX_START };
    MainAxisSize mainAxisSize_ { MainAxisSize::MAX };
    WrapAlignment alignContent_ = { WrapAlignment::START };
    bool wrap_ = false;

    // Template method for creating component
    virtual RefPtr<OHOS::Ace::FlexComponent> ComponentForType(
        FlexAlign mainAxisAlign, FlexAlign crossAxisAlign, const std::list<RefPtr<Component>>& children);

    virtual bool IsHorizontal() const = 0;

public:
    JSFlex() = delete;
#ifdef USE_V8_ENGINE
    JSFlex(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif

#ifdef USE_QUICKJS_ENGINE
    JSFlex(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#endif

    ~JSFlex();

    RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;

    void SetFillParent();
    void SetWrapContent();

    /**
     * JS JustifyContent function definition:
     * Main axis alignment format of the current row of the flex container. The options are as follows:
     * flexstart: The project is at the beginning of the container.
     * flexend: The project is at the end of the container.
     * center: The project is located in the center of the container.
     * spacebetween: The project is located in a container with a blank space between lines.
     * spacearound: The item is located in a container with blank space before, between, and after each line.
     */
    void SetJustifyContent(int value);

    /**
     * JS AlignItems function definition:
     * Alignment format of the cross axis of the current row of the flex container. The options are as follows:
     *	stretch: The elastic element is stretched to the same height or width as the container in the cross axis
     *  direction.
     * flexstart: The element is aligned to the start point of the cross axis.
     * flexend: The element is aligned to the end of the cross axis.
     * center: The element is centered on the cross axis.
     */
    void SetAlignItems(int value);

    void SetAlignContent(int value);

    void SetWrap(bool value);

#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    void ReleaseRT(JSRuntime* rt) override;
    template<typename U>
    static JSValue JsFlexConstructorInternal(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv,
        std::function<U*(std::list<JSViewAbstract*>, std::list<JSValue>)> flex);
#elif USE_V8_ENGINE
    static void V8FlexConstructorInternal(const v8::FunctionCallbackInfo<v8::Value>& args,
        std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren);
#endif

private:
#ifdef USE_QUICKJS_ENGINE
    static void JsFlexChildFromObject(
        JSContext* ctx, JSValueConst& argObj, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren);
    static void JsFlexChildrenFromArray(
        JSContext* ctx, JSValueConst& argArray, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren);
    static void JsFlexChildrenFromFunction(
        JSContext* ctx, JSValueConst& argArray, std::list<JSViewAbstract*>& children, std::list<JSValue>& jsChildren);
#endif

#ifdef USE_V8_ENGINE
    static void V8FlexChildrenFromObject(
        v8::Local<v8::Context> context, v8::Local<v8::Value> v8Val, std::list<JSViewAbstract*>& children);
    static void V8FlexChildrenFromArray(
        v8::Local<v8::Context> context, v8::Local<v8::Array> v8Array, std::list<JSViewAbstract*>& children);
#endif

}; // JSFlex class

} // namespace OHOS::Ace::Framework

#include "frameworks/bridge/declarative_frontend/jsview/js_flex.inl"

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_FLEX_H
