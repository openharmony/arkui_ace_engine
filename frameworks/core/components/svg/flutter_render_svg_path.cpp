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

#include "frameworks/core/components/svg/flutter_render_svg_path.h"

#include "include/utils/SkParsePath.h"

#include "frameworks/core/components/common/painter/flutter_svg_painter.h"
#include "frameworks/core/components/transform/flutter_render_transform.h"
#include "frameworks/core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> RenderSvgPath::Create()
{
    return AceType::MakeRefPtr<FlutterRenderSvgPath>();
}

RenderLayer FlutterRenderSvgPath::GetRenderLayer()
{
    if (!transformLayer_) {
        transformLayer_ = AceType::MakeRefPtr<Flutter::TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(transformLayer_);
}

void FlutterRenderSvgPath::Paint(RenderContext& context, const Offset& offset)
{
    if (d_.empty()) {
        return;
    }
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
    SkPath out;
    if (paths_.empty()) {
        SkParsePath::FromSVGString(d_.c_str(), &out);
    } else {
        SkPath path;
        SkPath ending;
        int32_t firstPart = (int)weight_;
        int32_t pathsSize = paths_.size();
        if (firstPart < 0 || firstPart > (pathsSize - 1)) {
            return;
        } else if (firstPart == (pathsSize - 1)) {
            SkParsePath::FromSVGString(paths_[firstPart].c_str(), &path);
            SkParsePath::FromSVGString(paths_[firstPart - 1].c_str(), &ending);
            ending.interpolate(path, 1.0f, &out);
        } else {
            float newWeight = weight_ - firstPart;
            SkParsePath::FromSVGString(paths_[firstPart + 1].c_str(), &path);
            SkParsePath::FromSVGString(paths_[firstPart].c_str(), &ending);
            ending.interpolate(path, newWeight, &out);
        }
    }

    FlutterSvgPainter::SetFillStyle(skCanvas, out, fillState_, opacity_);
    FlutterSvgPainter::SetStrokeStyle(skCanvas, out, strokeState_, opacity_);
    RenderNode::Paint(context, offset);
}

void FlutterRenderSvgPath::UpdateMotion(const std::string& path, const std::string& rotate,
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

bool FlutterRenderSvgPath::GetStartPoint(Point& point)
{
    if (paths_.empty()) {
        return false;
    }
    SkPath out;
    if (!SkParsePath::FromSVGString(d_.c_str(), &out)) {
        return false;
    }
    SkPoint skPoint = out.getPoint(0);
    point = Point(skPoint.x(), skPoint.y());
    return true;
}

} // namespace OHOS::Ace
