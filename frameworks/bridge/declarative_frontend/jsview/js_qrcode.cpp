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

#include "frameworks/bridge/declarative_frontend/jsview/js_qrcode.h"

#include "base/log/ace_trace.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSQRCode::Create(const std::string& value)
{
    RefPtr<QrcodeComponent> qrcodeComponent = AceType::MakeRefPtr<OHOS::Ace::QrcodeComponent>();
    qrcodeComponent->SetValue(value);
    qrcodeComponent->SetQrcodeColor(Color::BLACK);
    qrcodeComponent->SetBackgroundColor(Color::WHITE);
    ViewStackProcessor::GetInstance()->Push(qrcodeComponent);
}

void JSQRCode::SetQRCodeColor(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto qrcode = AceType::DynamicCast<OHOS::Ace::QrcodeComponent>(component);
    qrcode->SetQrcodeColor(Color::FromString(value));
}

void JSQRCode::SetBackgroundColor(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto qrcode = AceType::DynamicCast<OHOS::Ace::QrcodeComponent>(component);
    qrcode->SetBackgroundColor(Color::FromString(value));
}

void JSQRCode::JSBind(BindingTarget globalObj)
{
    JSClass<JSQRCode>::Declare("QRCode");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSQRCode>::StaticMethod("create", &JSQRCode::Create, opt);
    JSClass<JSQRCode>::StaticMethod("color", &JSQRCode::SetQRCodeColor, opt);
    JSClass<JSQRCode>::StaticMethod("backgroundColor", &JSQRCode::SetBackgroundColor, opt);
    JSClass<JSQRCode>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSQRCode>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSQRCode>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSQRCode>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSQRCode>::Inherit<JSContainerBase>();
    JSClass<JSQRCode>::Inherit<JSViewAbstract>();
    JSClass<JSQRCode>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
