/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/qrcode_modifier.h"

#include "core/components/qrcode/qrcode_theme.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_BG_COLOR = 0xffffffff;
constexpr double DEFAULT_OPACITY = 1.0;

void SetQRColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRCodeColor(frameNode, Color(color));
}

void ResetQRColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(qrcodeTheme);
    Color qrcodeColor = qrcodeTheme->GetQrcodeColor();
    QRCodeModelNG::SetQRCodeColor(frameNode, qrcodeColor);
}

void SetQRBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(color));
}

void ResetQRBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(DEFAULT_BG_COLOR));
}

void SetContentOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // The minimum value of opacity is 0 and the maximum value is 1.
    if (LessNotEqual(opacity, 0.0) || GreatNotEqual(opacity, 1.0)) {
        QRCodeModelNG::SetContentOpacity(frameNode, DEFAULT_OPACITY);
    } else {
        QRCodeModelNG::SetContentOpacity(frameNode, opacity);
    }
}

void ResetContentOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetContentOpacity(frameNode, DEFAULT_OPACITY);
}

void SetQRValue(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    QRCodeModelNG::SetQRCodeValue(frameNode, std::string(value));
}

namespace NodeModifier {
const ArkUIQRCodeModifier* GetQRCodeModifier()
{
    static const ArkUIQRCodeModifier modifier = { SetQRColor, ResetQRColor, SetQRBackgroundColor,
        ResetQRBackgroundColor, SetContentOpacity, ResetContentOpacity, SetQRValue };

    return &modifier;
}

const CJUIQRCodeModifier* GetCJUIQRCodeModifier()
{
    static const CJUIQRCodeModifier modifier = { SetQRColor, ResetQRColor, SetQRBackgroundColor,
        ResetQRBackgroundColor, SetContentOpacity, ResetContentOpacity };

    return &modifier;
}
}
}