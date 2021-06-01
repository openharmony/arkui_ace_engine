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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_H

#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/core/components/list/list_item_component.h"

namespace OHOS::Ace::Framework {

class JSListItem : public JSContainerBase {
    DECLARE_ACE_TYPE(JSListItem, JSContainerBase);

public:
    JSListItem() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSListItem(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#else
    JSListItem(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif
    ~JSListItem();

    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;

    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsBind();
    static void QjsDestructor(JSRuntime* rt, JSListItem* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif

#ifdef USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_ITEM_H
