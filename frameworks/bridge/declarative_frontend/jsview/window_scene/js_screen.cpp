/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/window_scene/js_screen.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/core/components_ng/pattern/window_scene/screen/screen_model.h"

namespace OHOS::Ace::Framework {

void JSScreen::JSBind(BindingTarget globalObj)
{
    JSClass<JSScreen>::Declare("Screen");
    JSClass<JSScreen>::StaticMethod("create", &JSScreen::Create, MethodOptions::NONE);
    JSClass<JSScreen>::StaticMethod("brightness", &JSScreen::SetBrightness, MethodOptions::NONE);
    JSClass<JSScreen>::StaticMethod("rotation", &JSScreen::SetRotation, MethodOptions::NONE);
    JSClass<JSScreen>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSScreen>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSScreen>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSScreen>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSScreen>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSScreen>::Inherit<JSViewAbstract>();
    JSClass<JSScreen>::Bind(globalObj);
}

void JSScreen::Create(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGE("Window scene is only supported on new pipeline!");
        return;
    }

    // if (info.Length() < 1) {
    //     LOGE("The arg is wrong, it is supposed to have 1 argument");
    //     return;
    // }

    // auto screenSession = CreateScreenSessionFromNapiValue(info[0]);
    NG::ScreenModel::Create(nullptr);
}

void JSScreen::SetBrightness(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have 1 argument");
        return;
    }

    double brightness;
    if (!ParseJsDouble(info[0], brightness)) {
        LOGE("Failed to parse brightness");
        return;
    }

    // brightness is between 0 and 1
    brightness = std::clamp<double>(brightness, 0.f, 1.f);

    NG::ScreenModel::SetBrightness(brightness);
}

void JSScreen::SetRotation(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have 1 argument");
        return;
    }

    double degree;
    if (!ParseJsDouble(info[0], degree)) {
        LOGE("Failed to parse degree");
        return;
    }

    NG::ScreenModel::SetRotation(degree);
}

} // namespace OHOS::Ace::Framework
