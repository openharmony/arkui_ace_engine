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

#include "core/components_ng/pattern/qrcode/qrcode_paint_method.h"

#include "core/components_ng/pattern/qrcode/qrcode_paint_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t QRCODE_START_INDEX = 0;
constexpr uint32_t QRCODE_VALUE_MAX_LENGTH = 512;
} // namespace

void QRCodePaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = AceType::DynamicCast<QRCodePaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->GetValue().has_value()) {
        return;
    }
    auto value = paintProperty->GetValueValue();
    auto renderContext = paintWrapper->GetRenderContext();
    if (renderContext->HasForegroundColor()) {
        if (renderContext->GetForegroundColorValue().GetValue() != paintProperty->GetColorValue().GetValue()) {
            paintProperty->UpdateColor(Color::FOREGROUND);
        }
    } else if (renderContext->HasForegroundColorStrategy()) {
        paintProperty->UpdateColor(Color::FOREGROUND);
    }
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(qrCodeTheme);
    auto color = paintProperty->GetColorValue(qrCodeTheme->GetQrcodeColor());
    auto backgroundColor = paintProperty->GetBackgroundColorValue(qrCodeTheme->GetBackgroundColor());
    auto opacity = paintProperty->GetOpacityValue(1.0f);

    // For the long string, just show the length as 256.
    if (value.size() > QRCODE_VALUE_MAX_LENGTH) {
        value = value.substr(QRCODE_START_INDEX, QRCODE_VALUE_MAX_LENGTH);
    }
    auto paintOffset = paintWrapper->GetContentOffset();
    qrCodeModifier_->SetQRCodeOpacity(opacity);
    auto contentSize = paintWrapper->GetContentSize();
    auto qrCodeSize = std::min(contentSize.Width(), contentSize.Height());
    qrCodeModifier_->SetQRCodeSize(qrCodeSize);
    qrCodeModifier_->SetQRCodeValue(value);
    qrCodeModifier_->SetPaintOffset(paintOffset);
    qrCodeModifier_->SetQRCodeColor(color);
    qrCodeModifier_->SetQRCodeBackgroundColor(backgroundColor);
}
} // namespace OHOS::Ace::NG
