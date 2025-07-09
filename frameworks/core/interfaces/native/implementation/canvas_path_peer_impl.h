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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H

#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/paint_state.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class CanvasPathPeerImpl : public OHOS::Ace::Referenced {
public:
    struct ArcParam {
        double x;
        double y;
        double radius;
        double startAngle;
        double endAngle;
        std::optional<bool> anticlockwise;
    };
    struct ArcToParam {
        double x1;
        double y1;
        double x2;
        double y2;
        double radius;
    };
    struct BezierCurveToParam {
        double cp1x;
        double cp1y;
        double cp2x;
        double cp2y;
        double x;
        double y;
    };
    struct EllipseParam {
        double x;
        double y;
        double radiusX;
        double radiusY;
        double rotation;
        double startAngle;
        double endAngle;
        std::optional<bool> anticlockwise;
    };

    CanvasPathPeerImpl();
    ~CanvasPathPeerImpl() override = default;

    virtual void Path2DArc(const ArcParam& params);
    virtual void Path2DArcTo(const ArcToParam& params);
    virtual void Path2DBezierCurveTo(const BezierCurveToParam& params);
    virtual void Path2DClosePath();
    virtual void Path2DEllipse(const EllipseParam& params);
    virtual void Path2DLineTo(double x, double y);
    virtual void Path2DMoveTo(double x, double y);
    virtual void Path2DQuadraticCurveTo(double cpx, double cpy, double x, double y);
    virtual void Path2DRect(double x, double y, double width, double height);

    RefPtr<CanvasPath2D> GetCanvasPath2d() const
    {
        return path2d_;
    }
    void SetCanvasPath2d(const RefPtr<CanvasPath2D>& path2d)
    {
        path2d_ = path2d;
    }
    void SetUnit(OHOS::Ace::CanvasUnit unit)
    {
        unit_ = unit;
    }
    OHOS::Ace::CanvasUnit GetUnit()
    {
        return unit_;
    }
    double GetDensity()
    {
        return 0;
    }

protected:
    bool IfJudgeSpecialValue(double value);
    bool GetDoubleArg(double& dst, double src);
    bool GetDoubleArgArray(std::vector<double>& dst, const std::vector<double>& src);
    void SetPathSize();

    OHOS::Ace::RefPtr<OHOS::Ace::CanvasPath2D> path2d_;
    OHOS::Ace::CanvasUnit unit_ = OHOS::Ace::CanvasUnit::DEFAULT;
    bool isJudgeSpecialValue_ = false;
    size_t lastPathSize_ = 0;
};

} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H