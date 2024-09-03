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

#include "bridge/declarative_frontend/jsview/models/qrcode_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/qrcode/qrcode_component.h"

namespace OHOS::Ace::Framework {
void QRCodeModelImpl::Create(const std::string& value)
{
    RefPtr<QrcodeComponent> qrcode = AceType::MakeRefPtr<OHOS::Ace::QrcodeComponent>();
    qrcode->SetValue(value);
    qrcode->SetQrcodeColor(Color::BLACK);
    qrcode->SetBackgroundColor(Color::WHITE);
    ViewStackProcessor::GetInstance()->ClaimElementId(qrcode);
    ViewStackProcessor::GetInstance()->Push(qrcode);
}

void QRCodeModelImpl::SetQRCodeColor(const Color& color)
{
    auto qrcode = AceType::DynamicCast<QrcodeComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (qrcode) {
        qrcode->SetQrcodeColor(color);
    }
}

void QRCodeModelImpl::SetQRBackgroundColor(const Color& color)
{
    auto qrcode = AceType::DynamicCast<QrcodeComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (qrcode) {
        qrcode->SetBackgroundColor(color);
    }
}
} // namespace OHOS::Ace::Framework