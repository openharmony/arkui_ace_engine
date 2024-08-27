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

#include "frameworks/core/components/svg/rosen_render_svg_path.h"

#ifndef USE_ROSEN_DRAWING
#include "include/utils/SkParsePath.h"
#endif

#include "frameworks/core/components/common/painter/rosen_svg_painter.h"
#include "frameworks/core/components/transform/rosen_render_transform.h"

namespace OHOS::Ace {

void RosenRenderSvgPath::Paint(RenderContext& context, const Offset& offset)
{
    if (d_.empty()) {
        return;
    }
    const auto renderContext = static_cast<RosenRenderContext*>(&context);
    auto rsNode = renderContext->GetRSNode();
    auto canvas = renderContext->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

    if (rsNode && NeedTransform()) {
        auto [transform, pivotX, pivotY] = GetRawTransformInfo();
        rsNode->SetPivot(pivotX, pivotY);
        RosenRenderTransform::SyncTransformToRsNode(rsNode, transform);
    }
#ifndef USE_ROSEN_DRAWING
    SkAutoCanvasRestore save(canvas, false);
    PaintMaskLayer(context, offset, offset);

    SkPath out;
#else
    RSAutoCanvasRestore save(*canvas, false);
    PaintMaskLayer(context, offset, offset);

    RSRecordingPath out;
#endif
    GetPath(out);
    UpdateGradient(fillState_);

    RenderInfo renderInfo = { AceType::Claim(this), offset, opacity_, true };
    RosenSvgPainter::SetFillStyle(canvas, out, fillState_, renderInfo);
    RosenSvgPainter::SetStrokeStyle(canvas, out, strokeState_, renderInfo);
    RenderNode::Paint(context, offset);
}

void RosenRenderSvgPath::PaintDirectly(RenderContext& context, const Offset& offset)
{
    if (d_.empty()) {
        return;
    }
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkAutoCanvasRestore save(canvas, true);
    if (NeedTransform()) {
        canvas->concat(RosenSvgPainter::ToSkMatrix(GetTransformMatrix4Raw()));
    }
    PaintMaskLayer(context, offset, offset);

    SkPath out;
#else
    RSAutoCanvasRestore save(*canvas, true);
    if (NeedTransform()) {
        canvas->ConcatMatrix(RosenSvgPainter::ToDrawingMatrix(GetTransformMatrix4Raw()));
    }
    PaintMaskLayer(context, offset, offset);

    RSRecordingPath out;
#endif
    GetPath(out);
    UpdateGradient(fillState_);
    RosenSvgPainter::SetFillStyle(canvas, out, fillState_, opacity_);
    RosenSvgPainter::SetStrokeStyle(canvas, out, strokeState_, opacity_);
}

void RosenRenderSvgPath::UpdateMotion(const std::string& path, const std::string& rotate, double percent)
{
    auto rsNode = GetRSNode();
    if (!rsNode) {
        LOGE("transformLayer is null");
        return;
    }
    RosenSvgPainter::UpdateMotionMatrix(rsNode, path, rotate, percent);
}

Rect RosenRenderSvgPath::GetPaintBounds(const Offset& offset)
{
#ifndef USE_ROSEN_DRAWING
    SkPath path;
    GetPath(path);
    auto& bounds = path.getBounds();
    return Rect(bounds.left(), bounds.top(), bounds.width(), bounds.height());
#else
    RSRecordingPath recordingPath;
    GetPath(recordingPath);
    auto bounds = recordingPath.GetBounds();
    return Rect(bounds.GetLeft(), bounds.GetTop(), bounds.GetWidth(), bounds.GetHeight());
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderSvgPath::GetPath(SkPath& out)
{
    if (paths_.empty()) {
        SkParsePath::FromSVGString(d_.c_str(), &out);
    } else {
        SkPath path;
        SkPath ending;
        int32_t firstPart = (int)weight_;
        int32_t pathsSize = static_cast<int32_t>(paths_.size());
        bool ret = false;
        if (firstPart < 0 || firstPart > (pathsSize - 1)) {
            ret = false;
        } else if (firstPart == (pathsSize - 1)) {
            SkParsePath::FromSVGString(paths_[firstPart].c_str(), &path);
            SkParsePath::FromSVGString(paths_[firstPart - 1].c_str(), &ending);
            ret = ending.interpolate(path, 1.0f, &out);
        } else {
            float newWeight = weight_ - firstPart;
            SkParsePath::FromSVGString(paths_[firstPart + 1].c_str(), &path);
            SkParsePath::FromSVGString(paths_[firstPart].c_str(), &ending);
            ret = ending.interpolate(path, newWeight, &out);
        }
        if (!ret) {
            SkParsePath::FromSVGString(d_.c_str(), &out);
        }
    }
    if (fillState_.IsEvenodd()) {
        out.setFillType(SkPathFillType::kEvenOdd);
    }
}
#else
void RosenRenderSvgPath::GetPath(RSRecordingPath& out)
{
    if (paths_.empty()) {
        out.BuildFromSVGString(d_);
    } else {
        RSRecordingPath path;
        RSRecordingPath ending;
        int32_t firstPart = (int)weight_;
        int32_t pathsSize = static_cast<int32_t>(paths_.size());
        bool ret = false;
        if (firstPart < 0 || firstPart > (pathsSize - 1)) {
            ret = false;
        } else if (firstPart == (pathsSize - 1)) {
            path.BuildFromSVGString(paths_[firstPart]);
            ending.BuildFromSVGString(paths_[firstPart - 1]);
            ret = out.BuildFromInterpolate(ending, path, 1.0f);
        } else {
            float newWeight = weight_ - firstPart;
            path.BuildFromSVGString(paths_[firstPart + 1]);
            ending.BuildFromSVGString(paths_[firstPart]);
            ret = out.BuildFromInterpolate(ending, path, newWeight);
        }
        if (!ret) {
            out.BuildFromSVGString(d_);
        }
    }
    if (fillState_.IsEvenodd()) {
        out.SetFillStyle(RSPathFillType::EVENTODD);
    }
}
#endif

} // namespace OHOS::Ace
