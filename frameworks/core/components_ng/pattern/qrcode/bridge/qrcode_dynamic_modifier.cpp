/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/common/dynamic_module_helper.h"
#include "core/components/theme/app_theme.h"
 #include "core/interfaces/native/node/qrcode_modifier.h"

#include "core/components/qrcode/qrcode_theme.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
QRCodeModel* GetQRCodeModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("qrcode");
    static QRCodeModel* instance = loader ? reinterpret_cast<QRCodeModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_BG_COLOR = 0xffffffff;
constexpr double DEFAULT_OPACITY = 1.0;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void CreateModel(ArkUI_CharPtr value)
{
    QRCodeModelNG::CreateQRCodeModelNG(value);
}

void SetQRColor(ArkUINodeHandle node, uint32_t color)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRCodeColor(frameNode, Color(color));
}

void SetQRColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(color));
}

void SetQRBackgroundColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(color));

    if (SystemProperties::ConfigChangePerform()) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::BACKGROUND_COLOR, colorResObj);
    }
}

void ResetQRBackgroundColor(ArkUINodeHandle node, ArkUI_Bool isJsView)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (isJsView) {
        RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
        CHECK_NULL_VOID(qrcodeTheme);
        Color qrcodeBackgroundColor = qrcodeTheme->GetBackgroundColor();
        QRCodeModelNG::SetQRBackgroundColor(frameNode, qrcodeBackgroundColor);
    } else {
        QRCodeModelNG::SetQRBackgroundColor(frameNode, Color(DEFAULT_BG_COLOR));
    }

    if (SystemProperties::ConfigChangePerform()) {
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::BACKGROUND_COLOR, nullptr);
    }
}

void SetContentOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    QRCodeModelNG::SetContentOpacity(frameNode, DEFAULT_OPACITY);
    if (SystemProperties::ConfigChangePerform()) {
        QRCodeModelNG::CreateWithResourceObj(frameNode, QRCodeResourceType::CONTENT_OPACITY, nullptr);
    }
}

void SetQRValue(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    QRCodeModelNG::SetQRCodeValue(frameNode, std::string(value));
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    auto frameNode = QRCodeModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

#ifndef CROSS_PLATFORM
void CreateModelImpl(ArkUI_CharPtr value)
{
    GetQRCodeModelImpl()->Create(value);
}

void SetQRColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetQRCodeModelImpl()->SetQRCodeColor(Color(color));
}

void SetQRColorPtrImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    GetQRCodeModelImpl()->SetQRCodeColor(Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        GetQRCodeModelImpl()->CreateWithResourceObj(QRCodeResourceType::COLOR, colorResObj);
    }
}

void ResetQRColorImpl(ArkUINodeHandle node)
{
    RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(qrcodeTheme);
    Color qrcodeColor = qrcodeTheme->GetQrcodeColor();
    GetQRCodeModelImpl()->SetQRCodeColor(qrcodeColor);
    if (SystemProperties::ConfigChangePerform()) {
        GetQRCodeModelImpl()->CreateWithResourceObj(QRCodeResourceType::COLOR, nullptr);
    }
}

void SetQRBackgroundColorImpl(ArkUINodeHandle node, uint32_t color)
{
    GetQRCodeModelImpl()->SetQRBackgroundColor(Color(color));
}

void SetQRBackgroundColorPtrImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    GetQRCodeModelImpl()->SetQRBackgroundColor(Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        GetQRCodeModelImpl()->CreateWithResourceObj(QRCodeResourceType::BACKGROUND_COLOR, colorResObj);
    }
}

void ResetQRBackgroundColorImpl(ArkUINodeHandle node, ArkUI_Bool isJsView)
{
    if (isJsView) {
        RefPtr<QrcodeTheme> qrcodeTheme = GetTheme<QrcodeTheme>();
        CHECK_NULL_VOID(qrcodeTheme);
        Color qrcodeBackgroundColor = qrcodeTheme->GetBackgroundColor();
        GetQRCodeModelImpl()->SetQRBackgroundColor(qrcodeBackgroundColor);
    } else {
        GetQRCodeModelImpl()->SetQRBackgroundColor(Color(DEFAULT_BG_COLOR));
    }

    if (SystemProperties::ConfigChangePerform()) {
        GetQRCodeModelImpl()->CreateWithResourceObj(QRCodeResourceType::BACKGROUND_COLOR, nullptr);
    }
}
#endif

const ArkUIQRCodeModifier* GetQRCodeDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIQRCodeModifier modifier = {
            .createModel = CreateModelImpl,
            .setQRColor = SetQRColorImpl,
            .setQRColorPtr = SetQRColorPtrImpl,
            .resetQRColor = ResetQRColorImpl,
            .setQRBackgroundColor = SetQRBackgroundColorImpl,
            .setQRBackgroundColorPtr = SetQRBackgroundColorPtrImpl,
            .resetQRBackgroundColor = ResetQRBackgroundColorImpl,
            .setContentOpacity = nullptr,
            .setContentOpacityPtr = nullptr,
            .resetContentOpacity = nullptr,
            .setQRValue = nullptr,
            .createFrameNode = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIQRCodeModifier modifier = {
        .createModel = CreateModel,
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
        .createFrameNode = CreateFrameNode,
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
