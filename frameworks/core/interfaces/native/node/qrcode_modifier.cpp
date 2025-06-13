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

void SetQRColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRCodeColor(frameNode, Color(color));

    if (SystemProperties::ConfigChangePerform()) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::COLOR, colorResObj);
    }
}

void ResetQRColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(qrcodeTheme);
    Color qrcodeColor = qrcodeTheme->GetQrcodeColor();
    QRCodeModelNG::SetQRCodeColor(frameNode, qrcodeColor);
    if (SystemProperties::ConfigChangePerform()) {
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::COLOR, nullptr);
    }
}

void SetQRBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(color));
}

void SetQRBackgroundColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(color));

    if (SystemProperties::ConfigChangePerform()) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::BACKGROUND_COLOR, colorResObj);
    }
}

void ResetQRBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(DEFAULT_BG_COLOR));
    if (SystemProperties::ConfigChangePerform()) {
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::BACKGROUND_COLOR, nullptr);
    }
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

void SetContentOpacityPtr(ArkUINodeHandle node, ArkUI_Float32 opacity, void* opacityRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // The minimum value of opacity is 0 and the maximum value is 1.
    if (LessNotEqual(opacity, 0.0) || GreatNotEqual(opacity, 1.0)) {
        QRCodeModelNG::SetContentOpacity(frameNode, DEFAULT_OPACITY);
    } else {
        QRCodeModelNG::SetContentOpacity(frameNode, opacity);
    }

    if (SystemProperties::ConfigChangePerform()) {
        auto* opacity = reinterpret_cast<ResourceObject*>(opacityRawPtr);
        auto opacityResObj = AceType::Claim(opacity);
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::CONTENT_OPACITY, opacityResObj);
    }
}

void ResetContentOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetContentOpacity(frameNode, DEFAULT_OPACITY);
    if (SystemProperties::ConfigChangePerform()) {
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::CONTENT_OPACITY, nullptr);
    }
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
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIQRCodeModifier modifier = {
        .setQRColor = SetQRColor,
        .setQRColorPtr = SetQRColorPtr,
        .resetQRColor = ResetQRColor,
        .setQRBackgroundColor = SetQRBackgroundColor,
        .setQRBackgroundColorPtr = SetQRBackgroundColorPtr,
        .resetQRBackgroundColor = ResetQRBackgroundColor,
        .setContentOpacity = SetContentOpacity,
        .setContentOpacityPtr = SetContentOpacityPtr,
        .resetContentOpacity = ResetContentOpacity,
        .setQRValue = SetQRValue,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIQRCodeModifier* GetCJUIQRCodeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIQRCodeModifier modifier = {
        .setQRColor = SetQRColor,
        .setQRColorPtr = SetQRColorPtr,
        .resetQRColor = ResetQRColor,
        .setQRBackgroundColor = SetQRBackgroundColor,
        .setQRBackgroundColorPtr = SetQRBackgroundColorPtr,
        .resetQRBackgroundColor = ResetQRBackgroundColor,
        .setContentOpacity = SetContentOpacity,
        .setContentOpacityPtr = SetContentOpacityPtr,
        .resetContentOpacity = ResetContentOpacity,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
}
