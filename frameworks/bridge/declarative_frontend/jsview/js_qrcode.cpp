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

#include "frameworks/bridge/declarative_frontend/jsview/js_qrcode.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/qrcode_model_impl.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_qrcode_theme.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/qrcode/qrcode_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/qrcode/qrcode_model.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<QRCodeModel> QRCodeModel::instance_ = nullptr;
std::mutex QRCodeModel::mutex_;

QRCodeModel* QRCodeModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::QRCodeModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::QRCodeModelNG());
            } else {
                instance_.reset(new Framework::QRCodeModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSQRCode::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::string value;
    if (info[0]->IsNumber()) {
        auto num = info[0]->ToNumber<int32_t>();
        value = std::to_string(num);
    } else if (info[0]->IsNull()) {
        value = "null";
    } else if (info[0]->IsUndefined()) {
        value = "undefined";
    } else {
        ParseJsString(info[0], value);
    }
    QRCodeModel::GetInstance()->Create(value);
    JSQRCodeTheme::ApplyTheme();
}

void JSQRCode::SetQRCodeColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color qrcodeColor;
    if (!ParseJsColor(info[0], qrcodeColor) && !JSQRCodeTheme::ObtainQRCodeColor(qrcodeColor)) {
        RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
        CHECK_NULL_VOID(qrcodeTheme);
        qrcodeColor = qrcodeTheme->GetQrcodeColor();
    }
    QRCodeModel::GetInstance()->SetQRCodeColor(qrcodeColor);
}

void JSQRCode::SetBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor) && !JSQRCodeTheme::ObtainBackgroundColor(backgroundColor)) {
        RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
        CHECK_NULL_VOID(qrcodeTheme);
        backgroundColor = qrcodeTheme->GetBackgroundColor();
    }

    QRCodeModel::GetInstance()->SetQRBackgroundColor(backgroundColor);
}

void JSQRCode::SetContentOpacity(const JSCallbackInfo& info)
{
    double opacity = 1.0;
    if (!ParseJsDouble(info[0], opacity)) {
        opacity = 1.0;
    }
    if (LessNotEqual(opacity, 0.0) || GreatNotEqual(opacity, 1.0)) {
        opacity = 1.0;
    }
    QRCodeModel::GetInstance()->SetContentOpacity(opacity);
}

void JSQRCode::JSBind(BindingTarget globalObj)
{
    JSClass<JSQRCode>::Declare("QRCode");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSQRCode>::StaticMethod("create", &JSQRCode::Create, opt);
    JSClass<JSQRCode>::StaticMethod("color", &JSQRCode::SetQRCodeColor, opt);
    JSClass<JSQRCode>::StaticMethod("backgroundColor", &JSQRCode::SetBackgroundColor, opt);
    JSClass<JSQRCode>::StaticMethod("contentOpacity", &JSQRCode::SetContentOpacity, opt);
    JSClass<JSQRCode>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSQRCode>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSQRCode>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSQRCode>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSQRCode>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSQRCode>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSQRCode>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSQRCode>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSQRCode>::Inherit<JSInteractableView>();
    JSClass<JSQRCode>::InheritAndBind<JSViewAbstract>(globalObj);
}

} // namespace OHOS::Ace::Framework
