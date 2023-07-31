/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
struct BorderRadius {
    CalcDimension radiusTopLeft;
    CalcDimension radiusTopRight;
    CalcDimension radiusBottomLeft;
    CalcDimension radiusBottomRight;
};

class JSSlidingPanel : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void Pop();
    static void SetHasDragBar(const JSCallbackInfo& info);
    static void SetShowCloseIcon(const JSCallbackInfo& info);
    static void SetShow(const JSCallbackInfo& info);
    static void SetPanelMode(const JSCallbackInfo& info);
    static void SetPanelType(const JSCallbackInfo& info);
    static void SetCustomHeight(const JSCallbackInfo& info);
    static void SetMiniHeight(const JSCallbackInfo& info);
    static void SetHalfHeight(const JSCallbackInfo& info);
    static void SetFullHeight(const JSCallbackInfo& info);
    static void SetOnSizeChange(const JSCallbackInfo& info);
    static void JsBackgroundColor(const JSCallbackInfo& info);
    static void JsPanelBorder(const JSCallbackInfo& info);
    static void JsPanelBorderColor(const JSCallbackInfo& info);
    static void JsPanelBorderStyle(int32_t style);
    static void JsPanelBorderWidth(const JSCallbackInfo& info);
    static void ParsePanelRadius(const JSRef<JSVal>& args, BorderRadius& borderRadius);
    static void SetBackgroundMask(const JSCallbackInfo& info);
    static void SetOnHeightChange(const JSCallbackInfo& args);
    static void JsPanelBorderRadius(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SLIDING_PANEL_H
