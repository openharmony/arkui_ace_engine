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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SLIDER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SLIDER_H

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

enum class SliderStyle {
    OUTSET = 0,
    INSET,
    NONE,
    CAPSULE,
};

enum class SliderChangeMode {
    BEGIN = 0,
    MOVING,
    END,
};

class JSSlider : public JSViewAbstract {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void SetBlockColor(const JSCallbackInfo& info);
    static void SetTrackColor(const JSCallbackInfo& info);
    static void SetThickness(const JSCallbackInfo& info);
    static void SetSelectedColor(const JSCallbackInfo& info);
    static void SetMinLabel(const JSCallbackInfo& info);
    static void SetMaxLabel(const JSCallbackInfo& info);
    static void SetMinResponsiveDistance(const JSCallbackInfo& info);
    static void SetShowSteps(const JSCallbackInfo& info);
    static void SetShowTips(const JSCallbackInfo& info);
    static void SetSliderInteractionMode(const JSCallbackInfo& info);
    static void SetBlockBorderColor(const JSCallbackInfo& info);
    static void SetBlockBorderWidth(const JSCallbackInfo& info);
    static void SetStepColor(const JSCallbackInfo& info);
    static void SetTrackBorderRadius(const JSCallbackInfo& info);
    static void SetSelectedBorderRadius(const JSCallbackInfo& info);
    static void SetBlockSize(const JSCallbackInfo& info);
    static void SetBlockStyle(const JSCallbackInfo& info);
    static void SetStepSize(const JSCallbackInfo& info);
    static void SetDigitalCrownSensitivity(const JSCallbackInfo& info);
    static void OnChange(const JSCallbackInfo& info);
    static void SetValidSlideRange(const JSCallbackInfo& info);
    static void SetEnableHapticFeedback(const JSCallbackInfo& info);

private:
    static void ResetBlockStyle();
    static bool ConvertGradientColor(const JsiRef<JsiValue>& param, NG::Gradient& gradient);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SLIDER_H
