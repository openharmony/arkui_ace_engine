/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/qrcode/qrcode_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/qrcode/qrcode_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void QRCodeModelStatic::SetQRCodeColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, Color, *color, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, *color, frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        auto castQRCodePaintProperty = frameNode->GetPaintPropertyPtr<QRCodePaintProperty>();
        CHECK_NULL_VOID(castQRCodePaintProperty);
        const auto& castRenderContext = frameNode->GetRenderContext();
        CHECK_NULL_VOID(castRenderContext);
        castQRCodePaintProperty->ResetColor();
        castRenderContext->ResetForegroundColor();
        castQRCodePaintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void QRCodeModelStatic::SetQRBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, BackgroundColor, *color, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundColor, *color, frameNode);
    } else {
        auto context = frameNode->GetContext();
        CHECK_NULL_VOID(context);
        auto themeManager = context->GetThemeManager();
        CHECK_NULL_VOID(themeManager);
        auto qrcodeTheme = themeManager->GetTheme<QrcodeTheme>();
        CHECK_NULL_VOID(qrcodeTheme);
        auto defaultQrcodeBackgroundColor = qrcodeTheme->GetBackgroundColor();
        ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, BackgroundColor, defaultQrcodeBackgroundColor, frameNode);
        ACE_UPDATE_NODE_RENDER_CONTEXT(BackgroundColor, defaultQrcodeBackgroundColor, frameNode);
    }
}

void QRCodeModelStatic::SetContentOpacity(FrameNode* frameNode, const std::optional<double>& opacity)
{
    if (opacity) {
        double opca = *opacity;
        if (LessNotEqual(opca, 0.0) || GreatNotEqual(opca, 1.0)) {
            opca = 1.0;
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, Opacity, opca, frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        auto castQRCodePaintProperty = frameNode->GetPaintPropertyPtr<QRCodePaintProperty>();
        CHECK_NULL_VOID(castQRCodePaintProperty);
        castQRCodePaintProperty->ResetOpacity();
        castQRCodePaintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
}
} // namespace OHOS::Ace::NG
