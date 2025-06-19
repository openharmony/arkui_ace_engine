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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RADIO_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RADIO_H

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSRadio : public JSViewAbstract {
public:
    static void Checked(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void ParseIndicator(const JSCallbackInfo& info, std::optional<int32_t>& indicator,
        std::function<void()>& customBuilderFunc, JSRef<JSVal>& builderObject);
    static void JsPadding(const JSCallbackInfo& info);
    static void JsRadioStyle(const JSCallbackInfo& info);
    static void JsResponseRegion(const JSCallbackInfo& info);
    static void JsSize(const JSCallbackInfo& args);
    static void JsOnClick(const JSCallbackInfo& args);
    static void OnChange(const JSCallbackInfo& info);
    static void JsHoverEffect(const JSCallbackInfo& info);
    static NG::PaddingPropertyF GetOldPadding(const JSCallbackInfo& info);
    static NG::PaddingProperty GetNewPadding(const JSCallbackInfo& info);
    static NG::PaddingProperty GetPadding(const std::optional<CalcDimension>& top,
        const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
        const std::optional<CalcDimension>& right);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_RADIO_H
