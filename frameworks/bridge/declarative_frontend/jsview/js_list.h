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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_H

#include "base/json/json_util.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/core/components/list/list_component.h"
#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_function.h"
#endif

#ifdef USE_V8_ENGINE
#include "frameworks/bridge/declarative_frontend/engine/v8/functions/v8_function.h"
#endif

namespace OHOS::Ace::Framework {

enum class Direction {
    COLUMN = 0,
    ROW,
};

class JSList : public JSContainerBase {
    DECLARE_ACE_TYPE(JSList, JSContainerBase);

public:
    JSList() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSList(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#else
    JSList(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif
    ~JSList();

public:
    static void JSBind(BindingTarget globalObj);
    RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;

#ifdef USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#elif USE_QUICKJS_ENGINE
    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSList* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;
#endif

#ifdef USE_V8_ENGINE
    // Functions called from JS to register List callback function for event with v8 engine.
    void ScrollCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
    void ReachStartCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
    void ReachEndCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
    void ScrollStopCallback(const v8::FunctionCallbackInfo<v8::Value>& args);

    // Functions called from JS to register List callback function for divider attributes with v8 engine.
    void SetDivider(const v8::FunctionCallbackInfo<v8::Value>& info);
#elif USE_QUICKJS_ENGINE
    // Functions called from JS to register List callback function for event with qjs engine.
    JSValue ScrollCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv);
    JSValue ReachStartCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv);
    JSValue ReachEndCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv);
    JSValue ScrollStopCallback(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv);

    // Functions called from JS to register List callback function for divider attributes with qjs engine.
    JSValue SetDivider(JSContext* ctx, JSValueConst jsList, int argc, JSValueConst* argv);
#endif

protected:
    void SetFlexDirection(int32_t flexDirection);
    void SetScrollBarState(int32_t state);
    void SetScrollEffect(int32_t scrollEffect);
    void SetInitialIndex(int32_t initialIndex);
    void HandleScrollEvent(const BaseEventInfo& param);

private:
    void InitScrollBarTheme();
    void InitDivider(const RefPtr<Component>& child);

    FlexDirection flexDirection_ { FlexDirection::COLUMN };

    // List scrollBar, on or off or auto
    RefPtr<ScrollBar> scrollBar_;
    DisplayMode displayMode_ = DisplayMode::OFF;

    // List edgeEffect, spring or fade or none
    EdgeEffect edgeEffect_ = EdgeEffect::SPRING;

    // List initialIndex
    int32_t initialIndex_ = 0;

    // List divider
    bool needDivider_ = false;
    Dimension dividerHeight_ = DIVIDER_DEFAULT_HEIGHT;
    Dimension dividerLength_;
    Dimension dividerOffset_;
    Color dividerColor_ = Color::BLACK;

#ifdef USE_V8_ENGINE
    RefPtr<V8EventFunction<ScrollEventInfo, 1>> onScrollFunc_;
    RefPtr<V8EventFunction<ScrollEventInfo, 1>> onReachStartFunc_;
    RefPtr<V8EventFunction<ScrollEventInfo, 1>> onReachEndFunc_;
    RefPtr<V8EventFunction<ScrollEventInfo, 1>> onScrollStopFunc_;
#elif USE_QUICKJS_ENGINE
    RefPtr<QJSEventFunction<ScrollEventInfo, 1>> onScrollFunc_;
    RefPtr<QJSEventFunction<ScrollEventInfo, 1>> onReachStartFunc_;
    RefPtr<QJSEventFunction<ScrollEventInfo, 1>> onReachEndFunc_;
    RefPtr<QJSEventFunction<ScrollEventInfo, 1>> onScrollStopFunc_;
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_H
