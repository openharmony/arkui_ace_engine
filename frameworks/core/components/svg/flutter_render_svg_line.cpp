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

#include "frameworks/core/components/svg/flutter_render_svg_line.h"

#include "include/utils/SkParsePath.h"

#include "frameworks/core/components/common/painter/flutter_svg_painter.h"
#include "frameworks/core/components/transform/flutter_render_transform.h"
#include "frameworks/core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> RenderSvgLine::Create()
{
    return AceType::MakeRefPtr<FlutterRenderSvgLine>();
}

RenderLayer FlutterRenderSvgLine::GetRenderLayer()
{
    if (!transformLayer_) {
        transformLayer_ = AceType::MakeRefPtr<Flutter::TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(transformLayer_);
}

void FlutterRenderSvgLine::Paint(RenderContext& context, const Offset& offset)
{
    const auto renderContext = static_cast<FlutterRenderContext*>(&context);
    flutter::Canvas* canvas = renderContext->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    SkCanvas* skCanvas = canvas->canvas();
    if (!skCanvas) {
        LOGE("Paint skCanvas is null");
        return;
    }

    SkPath path;
    double width = GetLayoutSize().Width();
    double height = GetLayoutSize().Height();
    path.moveTo(ConvertDimensionToPx(x1_, width), ConvertDimensionToPx(y1_, height));
    path.lineTo(ConvertDimensionToPx(x2_, width), ConvertDimensionToPx(y2_, height));

    FlutterSvgPainter::SetFillStyle(skCanvas, path, fillState_, opacity_);
    FlutterSvgPainter::SetStrokeStyle(skCanvas, path, strokeState_, opacity_);

    RenderNode::Paint(context, offset);
}

void FlutterRenderSvgLine::UpdateMotion(const std::string& path, const std::string& rotate,
    double percent, const Point& point)
{
    if (!transformLayer_) {
        LOGE("transformLayer is null");
        return;
    }
    bool isSuccess = true;
    auto motionMatrix = FlutterSvgPainter::CreateMotionMatrix(path, rotate, point, percent, isSuccess);
    if (isSuccess) {
        auto transform = FlutterRenderTransform::GetTransformByOffset(motionMatrix, GetGlobalOffset());
        transformLayer_->Update(transform);
    }
}

bool FlutterRenderSvgLine::GetStartPoint(Point& point)
{
    double width = GetLayoutSize().Width();
    double height = GetLayoutSize().Height();
    point = Point(ConvertDimensionToPx(x1_, width), ConvertDimensionToPx(y1_, height));
    return true;
}

} // namespace OHOS::Ace
