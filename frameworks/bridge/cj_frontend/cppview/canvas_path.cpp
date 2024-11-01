/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/cppview/canvas_path.h"

namespace OHOS::Ace::Framework {

NativeCanvasPath::NativeCanvasPath() : FFIData()
{
    path2d_ = AceType::MakeRefPtr<CanvasPath2D>();
}

NativeCanvasPath::NativeCanvasPath(const std::string& capStr) : FFIData()
{
    path2d_ = AceType::MakeRefPtr<CanvasPath2D>(capStr);
}

NativeCanvasPath::~NativeCanvasPath()
{
    LOGI("Native CanvasPath Destroyed: %{public}" PRId64, GetID());
}

void NativeCanvasPath::AddPath(const sptr<NativeCanvasPath>& path)
{
    auto toBeAdd = path->GetCanvasPath2d();
    path2d_->AddPath(toBeAdd);
}

void NativeCanvasPath::AddPathWithMatrix(const sptr<NativeCanvasPath>& path, const sptr<NativeMatrix2d>& matrix2d)
{
    auto toBeAdd = path->GetCanvasPath2d();
    path2d_->AddPath(toBeAdd);

    path2d_->SetTransform(matrix2d->GetScaleX(), matrix2d->GetRotateX(), matrix2d->GetRotateY(), matrix2d->GetScaleY(),
        matrix2d->GetTranslateX(), matrix2d->GetTranslateY());
}

void NativeCanvasPath::SetTransform(
    double scaleX, double skewX, double skewY, double scaleY, double translateX, double translateY)
{
    double density = GetDensity();
    path2d_->SetTransform(scaleX, skewX, skewY, scaleY, translateX * density, translateY * density);
}

void NativeCanvasPath::MoveTo(double x, double y)
{
    double density = GetDensity();
    path2d_->MoveTo(x * density, y * density);
}

void NativeCanvasPath::LineTo(double x, double y)
{
    double density = GetDensity();
    path2d_->LineTo(x * density, y * density);
}

void NativeCanvasPath::Arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise)
{
    double density = GetDensity();
    path2d_->Arc(x * density, y * density, radius * density, startAngle, endAngle, anticlockwise);
}

void NativeCanvasPath::ArcTo(double x1, double y1, double x2, double y2, double radius)
{
    double density = GetDensity();
    path2d_->ArcTo(x1 * density, y1 * density, x2 * density, y2 * density, radius * density);
}

void NativeCanvasPath::QuadraticCurveTo(double cpx, double cpy, double x, double y)
{
    double density = GetDensity();
    path2d_->QuadraticCurveTo(cpx * density, cpy * density, x * density, y * density);
}

void NativeCanvasPath::BezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y)
{
    double density = GetDensity();
    path2d_->BezierCurveTo(cp1x * density, cp1y * density, cp2x * density, cp2y * density, x * density, y * density);
}

void NativeCanvasPath::Ellipse(double x, double y, double radiusX, double radiusY, double rotation, double startAngle,
    double endAngle, bool anticlockwise)
{
    double density = GetDensity();
    path2d_->Ellipse(
        x * density, y * density, radiusX * density, radiusY * density, rotation, startAngle, endAngle, anticlockwise);
}

void NativeCanvasPath::Rect(double x, double y, double width, double height)
{
    double density = GetDensity();
    path2d_->Rect(x * density, y * density, width * density, height * density);
}

void NativeCanvasPath::ClosePath()
{
    path2d_->ClosePath();
}
} // namespace OHOS::Ace::Framework