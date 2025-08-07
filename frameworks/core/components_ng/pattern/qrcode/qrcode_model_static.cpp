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
        ACE_RESET_NODE_PAINT_PROPERTY(QRCodePaintProperty, Color, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColor, frameNode);
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
        ACE_RESET_NODE_PAINT_PROPERTY(QRCodePaintProperty, BackgroundColor, frameNode);
        ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, BackgroundColor, frameNode);
    }
}

void QRCodeModelStatic::SetContentOpacity(FrameNode* frameNode, const std::optional<double>& opacity)
{
    if (opacity) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(QRCodePaintProperty, Opacity, *opacity, frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(QRCodePaintProperty, Opacity, frameNode);
    }
}
} // namespace OHOS::Ace::NG
