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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_PATH_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_PATH_H

#include "ffi_remote_data.h"

#include "base/memory/referenced.h"
#include "core/components/common/properties/decoration.h"
#include "bridge/cj_frontend/cppview/matrix2d.h"
#include "frameworks/core/components/common/properties/paint_state.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT NativeCanvasPath : public OHOS::FFI::FFIData {
public:
    NativeCanvasPath();
    explicit NativeCanvasPath(const std::string& capStr);
    ~NativeCanvasPath() override;

    void AddPath(const sptr<NativeCanvasPath>& path);
    void AddPathWithMatrix(const sptr<NativeCanvasPath>& path, const sptr<NativeMatrix2d>& matrix2d);
    void SetTransform(double scaleX, double skewX, double skewY, double scaleY, double translateX, double translateY);
    void MoveTo(double x, double y);
    void LineTo(double x, double y);
    void Arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise);
    void ArcTo(double x1, double y1, double x2, double y2, double radius);
    void QuadraticCurveTo(double cpx, double cpy, double x, double y);
    void BezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
    void Ellipse(double x, double y, double radiusX, double radiusY, double rotation, double startAngle,
        double endAngle, bool anticlockwise);
    void Rect(double x, double y, double width, double height);
    void ClosePath();
    RefPtr<CanvasPath2D> GetCanvasPath2d() const
    {
        return path2d_;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    double GetDensity();

protected:
    RefPtr<CanvasPath2D> path2d_;

private:
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
};

} //  namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_CAVANS_PATH_H
