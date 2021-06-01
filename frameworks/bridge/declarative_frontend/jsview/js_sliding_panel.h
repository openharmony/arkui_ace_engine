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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SLIDING_PANEL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SLIDING_PANEL_H

#include <utility>

#include "core/components/panel/panel_component.h"
#include "core/components/panel/render_sliding_panel.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

class JSSlidingPanel : public JSContainerBase {
    DECLARE_ACE_TYPE(JSSlidingPanel, JSContainerBase);

public:
    JSSlidingPanel() = delete;
#ifdef USE_QUICKJS_ENGINE
    JSSlidingPanel(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren);
#elif USE_V8_ENGINE
    JSSlidingPanel(const std::list<JSViewAbstract*>& children,
        std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren);
#endif
    virtual ~JSSlidingPanel();
    virtual void Destroy(JSViewAbstract* parentCustomView) override;

    static void JSBind(BindingTarget globalObj);

#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    void ReleaseRT(JSRuntime* rt) override;
    static JSValue ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv);
    static void QjsDestructor(JSRuntime* rt, JSSlidingPanel* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#elif USE_V8_ENGINE
    static void ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args);
#endif

protected:
    RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;
    void SetHasDragBar(bool hasDragBar);
    void SetShow(bool isShow);
    void SetPanelMode(int32_t mode);
    void SetPanelType(int32_t type);
    void SetMiniHeight(const std::string& height);
    void SetHalfHeight(const std::string& height);
    void SetFullHeight(const std::string& height);
#ifdef USE_V8_ENGINE
    void SetOnSizeChange(const v8::FunctionCallbackInfo<v8::Value>& args);
#elif USE_QUICKJS_ENGINE
    JSValue SetOnSizeChange(JSContext* ctx, JSValueConst this_value, int32_t argc, JSValueConst* argv);
#endif

private:
    void PreparePanelComponent(RefPtr<OHOS::Ace::PanelComponent>& panelComponent);

    bool hasDragBar_ = true;
    bool isShow_ = true;
    PanelMode mode_ = PanelMode::FULL;
    PanelType type_ = PanelType::FOLDABLE_BAR;
    std::pair<Dimension, bool> miniHeight_ = { 0.0_px, false };
    std::pair<Dimension, bool> halfHeight_ = { 0.0_px, false };
    std::pair<Dimension, bool> fullHeight_ = { 0.0_px, false };
#ifdef USE_V8_ENGINE
    RefPtr<V8EventFunction<SlidingPanelSizeChangeEvent, 1>> onSizeChangeFunc_;
#elif USE_QUICKJS_ENGINE
    RefPtr<QJSEventFunction<SlidingPanelSizeChangeEvent, 1>> onSizeChangeFunc_;
#endif
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SLIDING_PANEL_H
