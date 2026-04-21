/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef PATH_H
#define PATH_H

#include <memory>
#include <vector>

#include "utils/matrix.h"
#include "utils/point.h"
#include "utils/rect.h"
#include "utils/round_rect.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class DrawingType {
    COMMON,
    RECORDING,
    OVER_DRAW,
    NO_DRAW,
    PAINT_FILTER,
    STATE_RECORD
};

enum class PathDirection {
    CW_DIRECTION,
    CCW_DIRECTION,
};

enum class PathFillType {
    WINDING,
    EVENTODD,
    INVERSE_WINDING,
    INVERSE_EVENTODD,
};

enum class PathOp {
    DIFFERENCE,
    INTERSECT,
    UNION,
    XOR,
    REVERSE_DIFFERENCE,
};

enum class PathAddMode {
    APPEND_PATH_ADD_MODE,
    EXTEND_PATH_ADD_MODE,
};

enum class PathMeasureMatrixFlags {
    GET_POSITION_MATRIX,
    GET_TANGENT_MATRIX,
    GET_POS_AND_TAN_MATRIX,
};

class Path {
public:
    Path() noexcept;
    Path(const Path& p) noexcept;
    Path &operator=(const Path& p) noexcept;
    virtual ~Path();

    virtual DrawingType GetDrawingType() const
    {
        return DrawingType::COMMON;
    }
    virtual bool BuildFromSVGString(const std::string& str);
    std::string ConvertToSVGString() const;
    virtual void MoveTo(scalar x, scalar y);
    virtual void LineTo(scalar x, scalar y);
    virtual void ArcTo(scalar pt1X, scalar pt1Y, scalar pt2X, scalar pt2Y, scalar startAngle, scalar sweepAngle);
    virtual void ArcTo(const Point& pt1, const Point& pt2, scalar startAngle, scalar sweepAngle);
    virtual void ArcTo(scalar rx, scalar ry, scalar angle, PathDirection direction, scalar endX, scalar endY);
    virtual void ArcTo(scalar x1, scalar y1, scalar x2, scalar y2, scalar radius);
    virtual void CubicTo(
        scalar ctrlPt1X, scalar ctrlPt1Y, scalar ctrlPt2X, scalar ctrlPt2Y, scalar endPtX, scalar endPtY);
    virtual void CubicTo(const Point& ctrlPt1, const Point& ctrlPt2, const Point& endPt);
    virtual void QuadTo(scalar ctrlPtX, scalar ctrlPtY, scalar endPtX, scalar endPtY);
    virtual void QuadTo(const Point& ctrlPt, const Point endPt);
    virtual void ConicTo(scalar ctrlX, scalar ctrlY, scalar endX, scalar endY, scalar weight);
    virtual void RMoveTo(scalar dx, scalar dy);
    virtual void RLineTo(scalar dx, scalar dy);
    virtual void RArcTo(scalar rx, scalar ry, scalar angle, PathDirection direction, scalar dx, scalar dy);
    virtual void RCubicTo(scalar dx1, scalar dy1, scalar dx2, scalar dy2, scalar dx3, scalar dy3);
    virtual void RQuadTo(scalar dx1, scalar dy1, scalar dx2, scalar dy2);
    virtual void RConicTo(scalar ctrlPtX, scalar ctrlPtY, scalar endPtX, scalar endPtY, scalar weight);
    virtual void AddRect(const Rect& rect, PathDirection dir = PathDirection::CW_DIRECTION);
    virtual void AddRect(const Rect& rect, unsigned start, PathDirection dir = PathDirection::CW_DIRECTION);
    virtual void AddRect(
        scalar left, scalar top, scalar right, scalar bottom, PathDirection dir = PathDirection::CW_DIRECTION);
    virtual void AddOval(const Rect& oval, PathDirection dir = PathDirection::CW_DIRECTION);
    virtual void AddOval(const Rect& oval, unsigned start, PathDirection dir = PathDirection::CCW_DIRECTION);
    virtual void AddArc(const Rect& oval, scalar startAngle, scalar sweepAngle);
    virtual void AddPoly(const std::vector<Point>& points, int count, bool close);
    virtual void AddCircle(scalar x, scalar y, scalar radius, PathDirection dir = PathDirection::CW_DIRECTION);
    virtual void AddRoundRect(
        const Rect& rect, scalar xRadius, scalar yRadius, PathDirection dir = PathDirection::CW_DIRECTION);
    virtual void AddRoundRect(const RoundRect& roundRect, PathDirection dir = PathDirection::CW_DIRECTION);
    virtual void AddPath(const Path& src, scalar dx, scalar dy, PathAddMode mode = PathAddMode::APPEND_PATH_ADD_MODE);
    virtual void AddPath(const Path& src, PathAddMode mode = PathAddMode::APPEND_PATH_ADD_MODE);
    virtual void AddPath(const Path& src, const Matrix& matrix, PathAddMode mode = PathAddMode::APPEND_PATH_ADD_MODE);
    virtual bool Contains(scalar x, scalar y) const;
    virtual void ReverseAddPath(const Path& src);
    Rect GetBounds() const;
    virtual void SetFillStyle(PathFillType fillstyle);
    PathFillType GetFillStyle() const;
    bool Interpolate(const Path& ending, scalar weight, Path& out);
    int CountVerbs() const;
    Point GetPoint(int index) const;
    bool IsInterpolate(const Path& other);
    void Approximate(scalar acceptableError, std::vector<scalar>& points);
    virtual bool BuildFromInterpolate(const Path& src, const Path& ending, scalar weight);
    virtual void Transform(const Matrix& matrix);
    virtual void TransformWithPerspectiveClip(const Matrix& matrix, Path* dst, bool applyPerspectiveClip);
    virtual void Offset(scalar dx, scalar dy);
    virtual void Offset(Path* dst, scalar dx, scalar dy);
    virtual bool Op(const Path& path1, Path& path2, PathOp op);
    bool IsValid() const;
    virtual void Reset();
    void SetLastPoint(scalar x, scalar y);
    void ReWind();
    virtual void Close();
    scalar GetLength(bool forceClosed) const;
    bool GetPositionAndTangent(scalar distance, Point& position, Point& tangent, bool forceClosed) const;
    bool GetSegment(scalar start, scalar stop, Path* dst, bool startWithMoveTo, bool forceClosed) const;
    bool IsClosed(bool forceClosed) const;
    bool IsEmpty() const;
    void SetPath(const Path& path);
    bool IsRect(Rect* rect, bool* isClosed = nullptr, PathDirection* direction = nullptr) const;
    bool GetMatrix(bool forceClosed, float distance, Matrix* matrix,
        PathMeasureMatrixFlags flags = PathMeasureMatrixFlags::GET_POS_AND_TAN_MATRIX);
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
