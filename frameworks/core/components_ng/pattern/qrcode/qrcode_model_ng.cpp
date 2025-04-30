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

#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/qrcode/qrcode_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DEFAULT_OPACITY = 1.0f;
} // namespace

void QRCodeModelNG::Create(const std::string& value)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::QRCODE_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::QRCODE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<QRCodePattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_VOID(qrCodeTheme);
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Value, value);
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Color, qrCodeTheme->GetQrcodeColor());
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, BackgroundColor, qrCodeTheme->GetBackgroundColor());
    ACE_UPDATE_RENDER_CONTEXT(BackgroundColor, qrCodeTheme->GetBackgroundColor());
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Opacity, DEFAULT_OPACITY);
}

void QRCodeModelNG::SetQRCodeColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Color, color);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, color);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void QRCodeModelNG::SetQRBackgroundColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, BackgroundColor, color);
    ACE_UPDATE_RENDER_CONTEXT(BackgroundColor, color);
}

void QRCodeModelNG::SetContentOpacity(const double opacity)
{
    ACE_UPDATE_PAINT_PROPERTY(QRCodePaintProperty, Opacity, opacity);
}

RefPtr<FrameNode> QRCodeModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::QRCODE_ETS_TAG, nodeId, AceType::MakeRefPtr<QRCodePattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, nullptr);
    RefPtr<QrcodeTheme> qrCodeTheme = pipeline->GetTheme<QrcodeTheme>();
    CHECK_NULL_RETURN(qrCodeTheme, nullptr);
    auto paintPropertyPtr = frameNode->GetPaintPropertyPtr<QRCodePaintProperty>();
    if (paintPropertyPtr) {
        paintPropertyPtr->UpdateColor(qrCodeTheme->GetQrcodeColor());
        paintPropertyPtr->UpdateBackgroundColor(qrCodeTheme->GetBackgroundColor());
    }
    const auto& context = frameNode->GetRenderContext();
    if (context) {
        context->UpdateBackgroundColor(qrCodeTheme->GetBackgroundColor());
    }
    if (paintPropertyPtr) {
        paintPropertyPtr->UpdateOpacity(DEFAULT_OPACITY);
    }
    return frameNode;
}

void QRCodeModelNG::SetQRCodeValue(FrameNode* frameNode, const std::string& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, Value, value, frameNode);
}

void QRCodeModelNG::SetQRCodeColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, Color, color, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void QRCodeModelNG::SetQRBackgroundColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, BackgroundColor, color, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundColor, color, frameNode);
}

void QRCodeModelNG::SetContentOpacity(FrameNode* frameNode, const double opacity)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, Opacity, opacity, frameNode);
}
} // namespace OHOS::Ace::NG
