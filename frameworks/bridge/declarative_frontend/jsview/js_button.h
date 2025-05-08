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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BUTTON_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BUTTON_H

#include <variant>

#include "core/components/button/button_component.h"
#include "core/components/text/text_component.h"
#include "core/components/touch_listener/touch_listener_component.h"
#include "core/components_ng/pattern/button/button_model.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "core/event/ace_event_handler.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {
class JSButton : public JSContainerBase {
public:
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(const std::string& value);
    static void SetFontStyle(int32_t value);
    static void SetFontFamily(const JSCallbackInfo& info);
    static void SetTextColor(const JSCallbackInfo& info);
    static void SetType(const JSCallbackInfo& info);
    static void SetStateEffect(const JSCallbackInfo& info);
    static void SetLableStyle(const JSCallbackInfo& info);
    static void SetButtonStyle(const JSCallbackInfo& info);
    static void SetControlSize(const JSCallbackInfo& info);
    static void JsBackgroundColor(const JSCallbackInfo& info);
    static void JsRadius(const JSCallbackInfo& info);
    static void JsRadius(const JSRef<JSVal>& jsValue);
    static void JsBorder(const JSCallbackInfo& info);
    static void JsWidth(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void JsAspectRatio(const JSCallbackInfo& info);
    static void JsOnClick(const JSCallbackInfo& info);
    static void JsSize(const JSCallbackInfo& info);
    static void JsRemoteMessage(const JSCallbackInfo& info);
    static void JsPadding(const JSCallbackInfo& info);
    static void SetRole(const JSCallbackInfo& info);
    static void SetMinFontScale(const JSCallbackInfo& info);
    static void SetMaxFontScale(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void CreateWithChild(const JSCallbackInfo& info);
    static void CreateWithLabel(const JSCallbackInfo& info);
    static constexpr char TYPE[] = "type";
    static constexpr char STATE_EFFECT[] = "stateEffect";
    static constexpr char BUTTON_STYLE[] = "buttonStyle";
    static constexpr char CONTROL_SIZE[] = "controlSize";
    static constexpr char ROLE[] = "role";

private:
    static void GetFontContent(JSRef<JSVal>& font, ButtonParameters& buttonParameters);
    static void CompleteParameters(ButtonParameters& buttonParameters);
    static CalcDimension GetSizeValue(const JSCallbackInfo& info);
    static NG::PaddingProperty GetNewPadding(const JSCallbackInfo& info);
    static Edge GetOldPadding(const JSCallbackInfo& info);
    static NG::PaddingProperty SetPaddings(const std::optional<CalcDimension>& top,
        const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
        const std::optional<CalcDimension>& right);
    static CreateWithPara ParseCreatePara(const JSCallbackInfo& info, bool hasLabel);
    static void ParseButtonRole(const JSRef<JSObject>& optionObj, CreateWithPara& param);
    static bool isLabelButton_;
    static void SetMinMaxFontSize(ButtonParameters& buttonParameters, const JSRef<JSVal>& fontSizeValue,
        const ButtonDimensionType type);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_BUTTON_H
