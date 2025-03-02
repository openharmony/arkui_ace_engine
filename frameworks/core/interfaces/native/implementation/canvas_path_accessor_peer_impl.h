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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H

#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"
#include "core/components/common/properties/decoration.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class CanvasPathPeerImpl : public Referenced {
public:
    CanvasPathPeerImpl() = default;
    ~CanvasPathPeerImpl() override = default;
    virtual void TriggerArcImpl(double x,
                                double y,
                                double radius,
                                double startAngle,
                                double endAngle,
                                bool counterclockwise)
    {
        CHECK_NULL_VOID(path);
        path->Arc(x, y, radius, startAngle, endAngle, counterclockwise);
    }
    virtual void TriggerArcToImpl(double x1, double y1, double x2, double y2, double radius)
    {
        CHECK_NULL_VOID(path);
        path->ArcTo(x1, y1, x2, y2, radius);
    }
    virtual void TriggerBezierCurveToImpl(double cp1x,
                                          double cp1y,
                                          double cp2x,
                                          double cp2y,
                                          double x,
                                          double y)
    {
        CHECK_NULL_VOID(path);
        path->BezierCurveTo(cp1x, cp1y, cp2x, cp2y, x, y);
    }
    virtual void TriggerClosePathImpl()
    {
        CHECK_NULL_VOID(path);
        path->ClosePath();
    }
    virtual void TriggerEllipseImpl(double x,
                                    double y,
                                    double radiusX,
                                    double radiusY,
                                    double rotation,
                                    double startAngle,
                                    double endAngle,
                                    bool counterclockwise)
    {
        CHECK_NULL_VOID(path);
        path->Ellipse(x, y, radiusX, radiusY, rotation, startAngle, endAngle, counterclockwise);
    }
    virtual void TriggerLineToImpl(double x, double y)
    {
        CHECK_NULL_VOID(path);
        path->LineTo(x, y);
    }
    virtual void TriggerMoveToImpl(double x, double y)
    {
        CHECK_NULL_VOID(path);
        path->MoveTo(x, y);
    }
    virtual void TriggerQuadraticCurveToImpl(double cpx, double cpy, double x, double y)
    {
        CHECK_NULL_VOID(path);
        path->QuadraticCurveTo(cpx, cpy, x, y);
    }
    virtual void TriggerRectImpl(double x, double y, double w, double h)
    {
        CHECK_NULL_VOID(path);
        path->Rect(x, y, w, h);
    }

public:
    RefPtr<CanvasPath2D> path;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CANVAS_PATH_ACCESSOR_PEER_IMPL_H