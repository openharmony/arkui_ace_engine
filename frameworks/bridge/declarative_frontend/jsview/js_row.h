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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_ROW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_ROW_H

#include "frameworks/bridge/declarative_frontend/jsview/js_flex.h"

namespace OHOS::Ace::Framework {

class JSRow : public JSFlex<RowComponent> {
    DECLARE_ACE_TYPE(JSRow, JSContainerBase);

public:
    JSRow() = delete;
#ifdef USE_V8_ENGINE
    JSRow(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
#else
    JSRow(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
#endif
        : JSFlex<RowComponent>(children, jsChildren) {};

    ~JSRow()
    {
        LOGD("Destroy: JSRow");
    };

    virtual void Destroy(JSViewAbstract* parentCustomView) override;

protected:
    bool IsHorizontal() const override;

public:
    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSRow* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#elif USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_ROW_H
