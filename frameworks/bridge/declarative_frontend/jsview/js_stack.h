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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_STACK_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_STACK_H

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/core/components/stack/stack_component.h"

namespace OHOS::Ace::Framework {

class JSStack : public JSContainerBase {
    DECLARE_ACE_TYPE(JSStack, JSContainerBase);

public:
    JSStack() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSStack(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#else
    JSStack(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif
    ~JSStack();

    RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;
    virtual void Destroy(JSViewAbstract* parentCustomView) override;

    static void JSBind(BindingTarget globalObj);
#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    void ReleaseRT(JSRuntime* rt) override;
#endif

public:
#ifdef USE_QUICKJS_ENGINE
    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSStack* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#elif USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

protected:
    void SetStackFit(int value);
    void SetOverflow(int value);
    void SetAlignment(int value);

    StackFit stackFit_ = StackFit::INHERIT;
    Overflow overflow_ = Overflow::OBSERVABLE;
    Alignment alignment_ = Alignment::CENTER;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_STACK_H
