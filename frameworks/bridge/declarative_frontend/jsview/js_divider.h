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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DIVIDER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DIVIDER_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/divider/divider_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSDivider : public JSViewAbstract, public JSInteractableView {
    DECLARE_ACE_TYPE(JSDivider, JSViewAbstract);

public:
    JSDivider() = default;
    ~JSDivider() override = default;
    void SetDividerColor(const std::string& color);
    void SetVertical(bool isVertical);
    void SetLineCap(int lineCap);
    void SetStrokeWidth(const std::string& width);

public:
    RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    static void QjsDestructor(JSRuntime* rt, JSDivider* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif

    static void JSBind(BindingTarget globalObj);

private:
    LineCap lineCap_ = LineCap::BUTT;
    Dimension strokeWidth_ = Dimension(1.0);
    bool isVertical_ = false;
    Color dividerColor_ = Color(0x51000000);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DIVIDER_H
