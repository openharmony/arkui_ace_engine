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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATOR_H

#include "core/components/navigator/navigator_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

class JSNavigator : public JSContainerBase {
    DECLARE_ACE_TYPE(JSNavigator, JSContainerBase);

public:
    JSNavigator() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSNavigator(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#else
    JSNavigator(const std::list<JSViewAbstract*>& children,
               std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif
    ~JSNavigator() {};

    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;

    static void JSBind(BindingTarget globalObj);

    void SetUri(const std::string& uri)
    {
        uri_ = uri;
        if (type_ == NavigatorType::DEFAULT) {
            // default type is page push
            type_ = NavigatorType::PUSH;
        }
    }

    void SetType(uint8_t type)
    {
        type_ = NavigatorType(type);
    }

    void SetActive(bool active)
    {
        active_ = active;
    }

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    static void QjsDestructor(JSRuntime* rt, JSNavigator* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);

    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
#endif

#ifdef USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

private:
    std::string uri_ = "";
    NavigatorType type_ = NavigatorType::DEFAULT;
    bool active_ = false;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_NAVIGATOR_H
