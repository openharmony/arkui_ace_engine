/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/canvas/js_canvas_gradient.h"

#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

JSCanvasGradient::JSCanvasGradient() {}

void JSCanvasGradient::Constructor(const JSCallbackInfo& args)
{
    auto jsCanvasGradient = Referenced::MakeRefPtr<JSCanvasGradient>();
    jsCanvasGradient->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsCanvasGradient));
}

void JSCanvasGradient::Destructor(JSCanvasGradient* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSCanvasGradient::JSBind(BindingTarget globalObj)
{
    JSClass<JSCanvasGradient>::Declare("CanvasGradient");
    JSClass<JSCanvasGradient>::CustomMethod("addColorStop", &JSCanvasGradient::AddColorStop);
    JSClass<JSCanvasGradient>::Bind(globalObj, JSCanvasGradient::Constructor, JSCanvasGradient::Destructor);
}

// if the params is invalid, fill the shape with transparent
void JSCanvasGradient::AddColorTransparent()
{
    CHECK_NULL_VOID(gradient_);
    isColorStopValid_ = false;
    gradient_->ClearColors();
    GradientColor color;
    color.SetColor(Color::TRANSPARENT);
    color.SetDimension(0.0);
    gradient_->AddColor(color);
    gradient_->AddColor(color);
}

void JSCanvasGradient::AddColorStop(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(gradient_);
    if (!isColorStopValid_ && gradient_->GetColors().empty()) {
        isColorStopValid_ = true;
    }
    if (!isColorStopValid_ || !info[0]->IsNumber() || (!info[1]->IsString() && !info[1]->IsObject())) {
        return;
    }
    double offset = 0.0;
    JSViewAbstract::ParseJsDouble(info[0], offset);
    if (offset < 0 || offset > 1) {
        AddColorTransparent();
        return;
    }
    GradientColor gradientColor;
    Color color = Color::WHITE;
    ColorSpace colorSpace = ColorSpace::SRGB;
    if (info[1]->IsString()) {
        std::string colorStr;
        JSViewAbstract::ParseJsString(info[1], colorStr);
        if (!Color::ParseColorString(colorStr, color)) {
            AddColorTransparent();
            return;
        }
    } else {
        if (!JSViewAbstract::ParseColorMetricsToColor(info[1], color)) {
            AddColorTransparent();
            return;
        }
        colorSpace = color.GetColorSpace();
    }
    if (!gradient_->GetColors().empty() && colorSpace != colorSpace_) {
        JSException::Throw(
            ERROR_CODE_CANVAS_PARAM_INVALID, "%s", "The color's ColorSpace is not the same as the last color's.");
        return;
    }
    gradientColor.SetColor(color);
    gradientColor.SetDimension(offset);
    if (gradient_->GetColors().empty()) {
        colorSpace_ = colorSpace;
        // prevent setting only one colorStop
        gradient_->AddColor(gradientColor);
    }
    gradient_->AddColor(gradientColor);
}

} // namespace OHOS::Ace::Framework
