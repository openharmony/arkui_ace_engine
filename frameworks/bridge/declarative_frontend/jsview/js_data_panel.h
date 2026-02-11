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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DATA_PANEL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DATA_PANEL_H

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
namespace OHOS::Ace::Framework {

class JSDataPanel : public JSViewAbstract {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void CloseEffect(const JSCallbackInfo& info);
    static void ValueColors(const JSCallbackInfo& info);
    static void TrackBackground(const JSCallbackInfo& info);
    static void StrokeWidth(const JSCallbackInfo& info);
    static void ShadowOption(const JSCallbackInfo& info);
    static void BorderRadius(const JSCallbackInfo& info);
    static void ParseShadowColors(
        const JSRef<JSArray>& colorsArray, std::vector<OHOS::Ace::NG::Gradient>& shadowColors);
    static void HandleShadowRadius(const JSRef<JSVal>& jsRadius, double& radius, RefPtr<ResourceObject>& resR,
        OHOS::Ace::NG::DataPanelShadow& shadow);
    static void HandleShadowOffsetX(const JSRef<JSVal>& jsOffsetX, double& offsetX, RefPtr<ResourceObject>& resX,
        OHOS::Ace::NG::DataPanelShadow& shadow);
    static void HandleShadowOffsetY(const JSRef<JSVal>& jsOffsetY, double& offsetY, RefPtr<ResourceObject>& resY,
        OHOS::Ace::NG::DataPanelShadow& shadow);

private:
    static bool ConvertGradientColor(const JsiRef<JsiValue>& itemParam, OHOS::Ace::NG::Gradient& gradient);
    static bool ConvertResourceColor(const JsiRef<JsiValue>& itemParam, OHOS::Ace::NG::Gradient& gradient);
    static void ConvertThemeColor(std::vector<OHOS::Ace::NG::Gradient>& colors);
    static uint32_t dataPanelType_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DATA_PANEL_H