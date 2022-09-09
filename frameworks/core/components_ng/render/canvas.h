/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_CANVAS_H

#include "base/geometry/matrix3.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rrect.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/clip_path.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/paint.h"

namespace OHOS::Ace::NG {

enum class ClipQuality {
    NONE = 0,
    HARD_EDGE,
    ANTI_ALIAS,
};

// Canvas is interface for drawing content.
class Canvas : public virtual AceType {
    DECLARE_ACE_TYPE(NG::Canvas, AceType)

public:
    static RefPtr<Canvas> Create(void* rawCanvas);

    // save and restore interfaces
    virtual void Save() = 0;
    virtual void Restore() = 0;

    // transform interfaces
    virtual void Translate(float dx, float dy) = 0;
    virtual void Scale(float sx, float sy) = 0;
    virtual void Rotate(float rad) = 0;
    virtual void Skew(float sx, float sy) = 0;
    virtual void SetMatrix(const Matrix3& matrix) = 0;
    virtual void ConcatMatrix(const Matrix3& matrix) = 0;

    // clip interfaces
    virtual void ClipRect(const RectF& rect, ClipQuality quality) = 0;
    virtual void ClipRRect(const RRect& rRect, ClipQuality quality) = 0;
    virtual void ClipWithPath(const ClipPath& path, ClipQuality quality) = 0;

    // drawing interfaces
    virtual void ClearColor(const Color& color) = 0;
    virtual void DrawColor(const Color& color) = 0;
    virtual void DrawLine(const PointF& start, const PointF& end, const RefPtr<Paint>& paint) = 0;
    virtual void DrawRect(const RectF& rect, const RefPtr<Paint>& paint) = 0;
    virtual void DrawRRect(const RRect& rect, const RefPtr<Paint>& paint) = 0;
    virtual void DrawCircle(float centerX, float centerY, float radius, const RefPtr<Paint>& paint) = 0;

    // drawing image.
    virtual void DrawImage(
        const RefPtr<CanvasImage>& image, const RectF& srcRect, const RectF& dstRect, const RefPtr<Paint>& paint) = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_CANVAS_H
