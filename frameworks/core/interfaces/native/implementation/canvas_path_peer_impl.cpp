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

#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "canvas_path_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr size_t GCTHRESHOLD = 50;

CanvasPathPeerImpl::CanvasPathPeerImpl()
{
    if (OHOS::Ace::Container::GreatOrEqualAPITargetVersion(OHOS::Ace::PlatformVersion::VERSION_FOURTEEN)) {
        isJudgeSpecialValue_ = true;
    }
}
void CanvasPathPeerImpl::Path2DArc(const ArcParam& params)
{
    CHECK_NULL_VOID(path2d_);
    double x = 0.0;
    double y = 0.0;
    double radius = 0.0;
    double startAngle = 0.0;
    double endAngle = 0.0;
    if (GetDoubleArg(x, params.x) && GetDoubleArg(y, params.y) && GetDoubleArg(radius, params.radius) &&
        GetDoubleArg(startAngle, params.startAngle) && GetDoubleArg(endAngle, params.endAngle)) {
        bool anticlockwise = params.anticlockwise.value_or(false);
        double density = GetDensity();
        path2d_->Arc(x * density, y * density, radius * density, startAngle, endAngle, anticlockwise);
        SetPathSize();
    }
}
void CanvasPathPeerImpl::Path2DArcTo(const ArcToParam& params)
{
    CHECK_NULL_VOID(path2d_);
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
    double radius = 0.0;
    if (GetDoubleArg(x1, params.x1) && GetDoubleArg(y1, params.y1) && GetDoubleArg(x2, params.x2) &&
        GetDoubleArg(y2, params.y2) && GetDoubleArg(radius, params.radius)) {
        double density = GetDensity();
        path2d_->ArcTo(x1 * density, y1 * density, x2 * density, y2 * density, radius * density);
        SetPathSize();
    }
}
void CanvasPathPeerImpl::Path2DBezierCurveTo(const BezierCurveToParam& params)
{
    CHECK_NULL_VOID(path2d_);
    double cp1x = 0.0;
    double cp1y = 0.0;
    double cp2x = 0.0;
    double cp2y = 0.0;
    double x = 0.0;
    double y = 0.0;
    if (GetDoubleArg(cp1x, params.cp1x) && GetDoubleArg(cp1y, params.cp1y) && GetDoubleArg(cp2x, params.cp2x) &&
        GetDoubleArg(cp2y, params.cp2y) && GetDoubleArg(x, params.x) && GetDoubleArg(y, params.y)) {
        double density = GetDensity();
        path2d_->BezierCurveTo(
            cp1x * density, cp1y * density, cp2x * density, cp2y * density, x * density, y * density);
        SetPathSize();
    }
}
void CanvasPathPeerImpl::Path2DClosePath()
{
    CHECK_NULL_VOID(path2d_);
    path2d_->ClosePath();
    SetPathSize();
}
void CanvasPathPeerImpl::Path2DEllipse(const EllipseParam& params)
{
    CHECK_NULL_VOID(path2d_);
    double x = 0.0;
    double y =  0.0;
    double radiusX =  0.0;
    double radiusY =  0.0;
    double rotation =  0.0;
    double startAngle =  0.0;
    double endAngle =  0.0;
    if (GetDoubleArg(x, params.x) && GetDoubleArg(y, params.y) && GetDoubleArg(radiusX, params.radiusX) &&
        GetDoubleArg(radiusY, params.radiusY) && GetDoubleArg(rotation, params.rotation) &&
        GetDoubleArg(startAngle, params.startAngle) && GetDoubleArg(endAngle, params.endAngle)) {
        bool anticlockwise = params.anticlockwise.value_or(false);
        double density = GetDensity();
        path2d_->Ellipse(x * density, y * density, radiusX * density, radiusY * density, rotation, startAngle, endAngle,
            anticlockwise);
        SetPathSize();
    }
}
void CanvasPathPeerImpl::Path2DLineTo(double x, double y)
{
    CHECK_NULL_VOID(path2d_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y)) {
        double density = GetDensity();
        path2d_->LineTo(x * density, y * density);
        SetPathSize();
    }
}
void CanvasPathPeerImpl::Path2DMoveTo(double x, double y)
{
    CHECK_NULL_VOID(path2d_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y)) {
        double density = GetDensity();
        path2d_->MoveTo(x * density, y * density);
        SetPathSize();
    }
}
void CanvasPathPeerImpl::Path2DQuadraticCurveTo(double cpx, double cpy, double x, double y)
{
    CHECK_NULL_VOID(path2d_);
    if (IfJudgeSpecialValue(cpx) && IfJudgeSpecialValue(cpy) && IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y)) {
        double density = GetDensity();
        path2d_->QuadraticCurveTo(cpx * density, cpy * density, x * density, y * density);
        SetPathSize();
    }
}
void CanvasPathPeerImpl::Path2DRect(double x, double y, double width, double height)
{
    CHECK_NULL_VOID(path2d_);
    if (IfJudgeSpecialValue(x) && IfJudgeSpecialValue(y) && IfJudgeSpecialValue(width) && IfJudgeSpecialValue(height)) {
        double density = GetDensity();
        path2d_->Rect(x * density, y * density, width * density, height * density);
        SetPathSize();
    }
}
// protected
bool CanvasPathPeerImpl::IfJudgeSpecialValue(double value)
{
    if (isJudgeSpecialValue_) {
        return !(std::isnan(value) || std::isinf(value));
    }
    return true;
}
bool CanvasPathPeerImpl::GetDoubleArg(double& dst, double src)
{
    if (IfJudgeSpecialValue(src)) {
        dst = src;
        return true;
    }
    return false;
}
bool CanvasPathPeerImpl::GetDoubleArgArray(std::vector<double>& dst, const std::vector<double>& src)
{
    if (src.empty()) {
        return false;
    }
    uint32_t length = src.size();
    dst.reserve(length);
    for (size_t i = 0; i < length; i++) {
        auto value = src[i];
        if (IfJudgeSpecialValue(value)) {
            dst.emplace_back(value);
        }
    }
    return true;
}
void CanvasPathPeerImpl::SetPathSize()
{
    CHECK_NULL_VOID(path2d_);
    const std::vector<std::pair<PathCmd, PathArgs>> caches = path2d_->GetCaches();
    size_t pathSize = caches.size();
    if (pathSize - lastPathSize_ > GCTHRESHOLD) {
        lastPathSize_ = pathSize;
    }
}
} // namespace OHOS::Ace::NG::GeneratedModifier
