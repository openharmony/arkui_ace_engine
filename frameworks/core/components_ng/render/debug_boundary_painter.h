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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DEBUG_BOUNDARY_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DEBUG_BOUNDARY_PAINTER_H

#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class DebugBoundaryPainter {
public:
    DebugBoundaryPainter() = default;
    DebugBoundaryPainter(const SizeF& content, const SizeF& frame) : contentSize_(content), frameMarginSize_(frame) {}
    ~DebugBoundaryPainter() = default;

    void DrawDebugBoundaries(RSCanvas& canvas, const OffsetF& offset) const
    {
        PaintDebugBoundary(canvas, offset);
        PaintDebugCorner(canvas, offset);
        PaintDebugMargin(canvas, offset);
    }

    void SetFrameOffset(const OffsetF& offset)
    {
        contentOffset_ = offset;
    }

private:
    void PaintDebugBoundary(RSCanvas& canvas, const OffsetF& offset) const;
    void PaintDebugMargin(RSCanvas& canvas, const OffsetF& offset) const;
    void PaintDebugCorner(RSCanvas& canvas, const OffsetF& offset) const;

    SizeF contentSize_;
    SizeF frameMarginSize_;
    OffsetF contentOffset_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DEBUG_BOUNDARY_PAINTER_H