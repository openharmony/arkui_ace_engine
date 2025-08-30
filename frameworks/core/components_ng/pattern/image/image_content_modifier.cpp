/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/image/image_content_modifier.h"

#include "core/common/ace_application_info.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/render/adapter/svg_canvas_image.h"
#include "core/components_ng/render/image_painter.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#include "2d_graphics/include/recording/draw_cmd_list.h"
#endif

namespace OHOS::Ace::NG {
ImageContentModifier::ImageContentModifier(const WeakPtr<ImagePattern>& pattern)
{
    pattern_ = pattern;
    sensitive_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(sensitive_);
    size_ = AceType::MakeRefPtr<PropertySizeF>(SizeF());
    AttachProperty(size_);
    canvasImageWrapper_ = AceType::MakeRefPtr<PropertyCanvasImageModifierWrapper>(CanvasImageModifierWrapper());
    AttachProperty(canvasImageWrapper_);
}

void ImageContentModifier::onDraw(DrawingContext& drawingContext)
{
    DrawDrawable(drawingContext);
    CHECK_NULL_VOID(canvasImageWrapper_);
    auto canvasImage = canvasImageWrapper_->Get().GetCanvasImage();
    CHECK_NULL_VOID(canvasImage);
    UpdateSvgColorFilter(canvasImage);
    ImagePainter imagePainter(canvasImage);
    if (!sensitive_->Get()) {
#ifdef ENABLE_ROSEN_BACKEND
        const auto& config = canvasImage->GetPaintConfig();
        if (config.isSvg_) {
            RSRecordingCanvas* recordingCanvas = static_cast<RSRecordingCanvas*>(&drawingContext.canvas);
            if (recordingCanvas != nullptr && recordingCanvas->GetDrawCmdList() != nullptr &&
                Rosen::RSUIDirector::GetHybridRenderSwitch(Rosen::ComponentEnableSwitch::SVG)) {
                recordingCanvas->GetDrawCmdList()->SetHybridRenderType(RSHybridRenderType::SVG);
            }
        }
#endif
        imagePainter.DrawImage(drawingContext.canvas, {}, size_->Get());
    }
}

void ImageContentModifier::DrawDrawable(DrawingContext& drawingContext)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->DrawDrawable(drawingContext.canvas);
}

void ImageContentModifier::UpdateSvgColorFilter(const RefPtr<CanvasImage>& canvasImage)
{
    auto&& paintConfig = canvasImage->GetPaintConfig();
    auto svgCanvas = AceType::DynamicCast<SvgCanvasImage>(canvasImage);
    if (svgCanvas) {
        svgCanvas->SetFillColor(paintConfig.svgFillColor_);
        svgCanvas->SetSmoothEdge(paintConfig.smoothEdge_);
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            std::optional<ImageColorFilter> imageColorFilter = std::nullopt;
            if (paintConfig.colorFilter_.colorFilterMatrix_ || paintConfig.colorFilter_.colorFilterDrawing_) {
                imageColorFilter = paintConfig.colorFilter_;
            }
            svgCanvas->SetColorFilter(imageColorFilter);
        }
    }
}
} // namespace OHOS::Ace::NG
