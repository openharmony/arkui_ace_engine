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

#include "frameworks/core/components/svg/flutter_render_svg_polygon.h"

#include "include/utils/SkParsePath.h"

#include "frameworks/core/components/common/painter/flutter_svg_painter.h"
#include "frameworks/core/components/transform/flutter_render_transform.h"
#include "frameworks/core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> RenderSvgPolygon::Create()
{
    return AceType::MakeRefPtr<FlutterRenderSvgPolygon>();
}

RenderLayer FlutterRenderSvgPolygon::GetRenderLayer()
{
    if (!transformLayer_) {
        transformLayer_ = AceType::MakeRefPtr<Flutter::TransformLayer>(Matrix4::CreateIdentity(), 0.0, 0.0);
    }
    return AceType::RawPtr(transformLayer_);
}

void FlutterRenderSvgPolygon::Paint(RenderContext& context, const Offset& offset)
{
    if (points_.empty()) {
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
    if (pointsVector_.empty()) {
        std::vector<SkPoint> skPoints;
        if (!CreateSkPath(points_, skPoints)) {
            return;
        }
        SkPath out;
        out.addPoly(&skPoints[0], skPoints.size(), true);
        FlutterSvgPainter::SetFillStyle(skCanvas, out, fillState_, opacity_);
        FlutterSvgPainter::SetStrokeStyle(skCanvas, out, strokeState_, opacity_);
        RenderNode::Paint(context, offset);
        return;
    }
    int32_t firstPart = (int)weight_;
    int32_t pathsSize = pointsVector_.size();
    float weight = 1.0f;
    int32_t currValue = 0;
    int32_t nextValue = 0;
    if (firstPart < 0 || firstPart > (pathsSize - 1)) {
        return;
    } else if (firstPart == (pathsSize - 1)) {
        currValue = firstPart;
        nextValue = firstPart - 1;
    } else {
        weight = weight_ - firstPart;
        currValue = firstPart + 1;
        nextValue = firstPart;
    }
    SkPath out;
    if (!CreateSkPaths(pointsVector_[currValue].c_str(), pointsVector_[nextValue].c_str(), weight, &out)) {
        return;
    }
    FlutterSvgPainter::SetFillStyle(skCanvas, out, fillState_, opacity_);
    FlutterSvgPainter::SetStrokeStyle(skCanvas, out, strokeState_, opacity_);
    RenderNode::Paint(context, offset);
}

bool FlutterRenderSvgPolygon::CreateSkPath(const std::string& pointsStr, std::vector<SkPoint>& skPoints)
{
    if (pointsStr.empty()) {
        return false;
    }
    FlutterSvgPainter::StringToPoints(pointsStr.c_str(), skPoints);
    return !skPoints.empty();
}

bool FlutterRenderSvgPolygon::CreateSkPaths(const std::string& points1,
    const std::string& points2, double weight, SkPath* out)
{
    SkPath begin;
    SkPath end;
    if (points1.empty() || points2.empty() || out == nullptr) {
        return false;
    }
    std::vector<SkPoint> skPoints1;
    std::vector<SkPoint> skPoints2;
    if (!CreateSkPath(points1.c_str(), skPoints1) || !CreateSkPath(points2.c_str(), skPoints2)) {
        return false;
    }
    if (skPoints1.size() != skPoints2.size()) {
        return false;
    }
    if (isBy_) {
        auto skPointIter1 = skPoints1.begin();
        auto skPointIter2 = skPoints2.begin();
        while (skPointIter1 != skPoints1.end()) {
            *skPointIter1 = *skPointIter1 + *skPointIter2;
            ++skPointIter1;
            ++skPointIter2;
        }
    }
    begin.addPoly(&skPoints1[0], skPoints1.size(), true);
    end.addPoly(&skPoints2[0], skPoints2.size(), true);
    begin.interpolate(end, weight, out);
    return true;
}

void FlutterRenderSvgPolygon::UpdateMotion(const std::string& path, const std::string& rotate,
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

bool FlutterRenderSvgPolygon::GetStartPoint(Point& point)
{
    if (points_.empty()) {
        return false;
    }
    std::vector<SkPoint> skPoints;
    FlutterSvgPainter::StringToPoints(points_.c_str(), skPoints);
    if (skPoints.empty()) {
        return false;
    }
    point = Point(skPoints[0].x(), skPoints[0].y());
    return true;
}

} // namespace OHOS::Ace
