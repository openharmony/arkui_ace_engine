/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.. All rights reserved.
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

#ifndef CORE_CANVAS_H
#define CORE_CANVAS_H

#include <memory>

#include "blend_mode.h"
#include "brush.h"
#include "clip.h"
#include "paint.h"
#include "path.h"
#include "shadow.h"

#include "image/bitmap.h"
#include "image/image.h"
#include "image/image_info.h"

#include "utils/matrix.h"
#include "utils/point3.h"
#include "utils/rect.h"
#include "utils/round_rect.h"
#include "utils/vertices.h"

#include "text/text_blob.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class SrcRectConstraint {
    STRICT_SRC_RECT_CONSTRAINT = 0,
    FAST_SRC_RECT_CONSTRAINT,
};

struct Lattice {
    enum RectType : uint8_t {
        DEFAULT = 0,
        TRANSPARENT,
        FIXEDCOLOR,
    };
    std::vector<int> fXDivs;
    std::vector<int> fYDivs;
    std::vector<RectType> fRectTypes;
    int fXCount;
    int fYCount;
    std::vector<RectI> fBounds;
    std::vector<Color> fColors;
};

class SaveLayerOps {
public:
    // How to allocate layer
    enum Flags {
        INIT_WITH_PREVIOUS = 1 << 1,    // create with previous contents
    };

    SaveLayerOps() : bounds_(nullptr), brush_(nullptr), saveLayerFlags_(0) {}
    SaveLayerOps(const Rect* bounds, const Brush* brush, uint32_t saveLayerFlags = 0)
        : bounds_(bounds), brush_(brush), saveLayerFlags_(saveLayerFlags) {}
    ~SaveLayerOps() {}
    const Rect* GetBounds() const
    {
        return bounds_;
    }
    const Brush* GetBrush() const
    {
        return brush_;
    }
    uint32_t GetSaveLayerFlags() const
    {
        return saveLayerFlags_;
    }

private:
    const Rect* bounds_;
    const Brush* brush_;
    uint32_t saveLayerFlags_;
};

class SkSVGDOM {
    SkSVGDOM() = default;
};

class CoreCanvas {
public:
    CoreCanvas();
    virtual ~CoreCanvas() {}
    CoreCanvas(int32_t width, int32_t height) {};
    void Bind(const Bitmap& bitmap);
    virtual Matrix GetTotalMatrix() const;
    virtual Rect GetLocalClipBounds() const;
    virtual RectI GetDeviceClipBounds() const;
    virtual RectI GetRoundInDeviceClipBounds() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    ImageInfo GetImageInfo();
    bool ReadPixels(const ImageInfo& dstInfo, void* dstPixels, size_t dstRowBytes,
        int srcX, int srcY);
    bool ReadPixels(const Bitmap& dstBitmap, int srcX, int srcY);
    virtual void DrawPoint(const Point& point);
    virtual void DrawLine(const Point& startPt, const Point& endPt);
    virtual void DrawRect(const Rect& rect);
    virtual void DrawRoundRect(const RoundRect& roundRect);
    virtual void DrawNestedRoundRect(const RoundRect& outer, const RoundRect& inner);
    virtual void DrawArc(const Rect& oval, scalar startAngle, scalar sweepAngle);
    virtual void DrawPie(const Rect& oval, scalar startAngle, scalar sweepAngle);
    virtual void DrawOval(const Rect& oval);
    virtual void DrawCircle(const Point& centerPt, scalar radius);
    virtual void DrawPath(const Path& path);
    virtual void DrawPathWithStencil(const Path& path, uint32_t stencilVal);
    virtual void DrawBackground(const Brush& brush);
    virtual void DrawShadow(const Path& path, const Point3& planeParams, const Point3& devLightPos, scalar lightRadius,
        Color ambientColor, Color spotColor, ShadowFlags flag);
    virtual void DrawShadowStyle(const Path& path, const Point3& planeParams, const Point3& devLightPos,
        scalar lightRadius, Color ambientColor, Color spotColor, ShadowFlags flag, bool isLimitElevation);
    virtual void DrawVertices(const Vertices& vertices, BlendMode mode);
    virtual void DrawImageNine(const Image* image, const RectI& center, const Rect& dst,
        FilterMode filter, const Brush* brush = nullptr);
    virtual void DrawImageLattice(const Image* image, const Lattice& lattice, const Rect& dst,
        FilterMode filter);
    virtual void DrawBitmap(const Bitmap& bitmap, const scalar px, const scalar py);
    virtual void DrawImage(const Image& image, const scalar px, const scalar py, const SamplingOptions& sampling);
    virtual void DrawImageRect(const Image& image, const Rect& src, const Rect& dst, const SamplingOptions& sampling,
        SrcRectConstraint constraint = SrcRectConstraint::STRICT_SRC_RECT_CONSTRAINT);
    virtual void DrawImageRect(const Image& image, const Rect& dst, const SamplingOptions& sampling);
    template<typename T>
    using  sk_sp = std::shared_ptr<T>;
    virtual void DrawSVGDOM(const sk_sp<SkSVGDOM>& svgDom);
    virtual void DrawTextBlob(const TextBlob* blob, const scalar x, const scalar y);
    virtual void ClearStencil(const RectI& rect, uint32_t stencilVal);
    virtual void ClipRect(const Rect& rect, ClipOp op = ClipOp::INTERSECT, bool doAntiAlias = false);
    virtual void ClipIRect(const RectI& rect, ClipOp op = ClipOp::INTERSECT);
    virtual void ClipRoundRect(const RoundRect& roundRect, ClipOp op = ClipOp::INTERSECT, bool doAntiAlias = false);
    virtual void ClipRoundRect(const Rect& rect, std::vector<Point>& pts, bool doAntiAlias = false);
    virtual void ClipPath(const Path& path, ClipOp op = ClipOp::INTERSECT, bool doAntiAlias = false);
    virtual bool IsClipEmpty();
    virtual bool IsClipRect();

    virtual void ResetClip();

    virtual bool QuickReject(const Path& path);

    virtual bool QuickReject(const Rect& rect);

    virtual void SetMatrix(const Matrix& matrix);

    virtual void ResetMatrix();

    virtual void ConcatMatrix(const Matrix& matrix);

    virtual void Translate(scalar dx, scalar dy);

    virtual void Scale(scalar sx, scalar sy);

    void Rotate(scalar deg)
    {
        Rotate(deg, 0, 0);
    }

    virtual void Rotate(scalar deg, scalar sx, scalar sy);

    virtual void Shear(scalar sx, scalar sy);

    virtual void Flush();

    virtual void Clear(ColorQuad color);

    virtual uint32_t Save();

    virtual void SaveLayer(const SaveLayerOps& saveLayerOps);

    virtual void Restore();

    virtual uint32_t GetSaveCount() const;

    virtual CoreCanvas& AttachPen(const Pen& pen);

    virtual CoreCanvas& AttachBrush(const Brush& brush);

    virtual CoreCanvas& AttachPaint(const Paint& paint);

    virtual CoreCanvas& DetachPen();

    virtual CoreCanvas& DetachBrush();

    virtual float GetAlpha() const;
    virtual int GetAlphaSaveCount() const;

    Paint& GetMutableBrush()
    {
        return paintBrush_;
    }

protected:
    Paint paintBrush_;
    Paint defaultPaint_;
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
