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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_ITEM_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_ITEM_H

#include "core/components/touch_listener/touch_listener_component.h"
#include "core/event/ace_event_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/grid_layout/grid_layout_item_component.h"

namespace OHOS::Ace::Framework {

class JSGridItem : public JSContainerBase {
    DECLARE_ACE_TYPE(JSGridItem, JSContainerBase);

public:
    JSGridItem() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSGridItem(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#else
    JSGridItem(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif
    ~JSGridItem();

    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    virtual std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;

    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSGridItem* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif

#ifdef USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

protected:
    void SetColumnStart(int32_t columnStart);
    void SetColumnEnd(int32_t columnEnd);
    void SetRowStart(int32_t rowStart);
    void SetRowEnd(int32_t rowEnd);

private:
    int32_t columnStart_ = -1;
    int32_t columnEnd_ = -1;
    int32_t rowStart_ = -1;
    int32_t rowEnd_ = -1;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_ITEM_H
