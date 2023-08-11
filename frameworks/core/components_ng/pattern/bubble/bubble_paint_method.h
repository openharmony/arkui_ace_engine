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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_PAINT_METHOD_H

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BubblePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(BubblePaintMethod, NodePaintMethod)
public:
    BubblePaintMethod() = default;
    ~BubblePaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
            auto bubble = weak.Upgrade();
            if (bubble) {
                bubble->PaintMask(canvas, paintWrapper);
                bubble->PaintBubble(canvas, paintWrapper);
                bubble->PaintBorder(canvas, paintWrapper);
            }
        };
    }

    void SetShowArrow(bool flag)
    {
        showArrow_ = flag;
    }

    void SetChildOffset(const OffsetF& offset)
    {
        childOffset_ = offset;
    }

    void SetChildSize(const SizeF& size)
    {
        childSize_ = size;
    }

    void SetArrowPosition(const OffsetF& offset)
    {
        arrowPosition_ = offset;
    }

    void PaintBubble(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintMask(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);

private:
    void PaintBubbleWithArrow(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintNonCustomPopup(RSCanvas& canvas, PaintWrapper* wrapper);

    void PaintTopBubble(RSCanvas& canvas);
    void PaintBottomBubble(RSCanvas& canvas);
    void PaintDefaultBubble(RSCanvas& canvas);

    void UpdateArrowOffset(const std::optional<Dimension>& offset, const Placement& placement);

    RSRoundRect MakeRRect();
    float GetArrowOffset(const Placement& placement);
    void InitEdgeSize(Edge& edge);

    void BuildCompletePath(RSPath& path);
    void BuildCornerPath(RSPath& path, const Placement& placement, float radius);
    void BuildTopLinePath(RSPath& path, float arrowOffset, float radius);
    void BuildRightLinePath(RSPath& path, float arrowOffset, float radius);
    void BuildBottomLinePath(RSPath& path, float arrowOffset, float radius);
    void BuildLeftLinePath(RSPath& path, float arrowOffset, float radius);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas);

    // Get from RenderProp
    bool useCustom_ = false;
    Placement arrowPlacement_ = Placement::BOTTOM;
    bool enableArrow_ = false;
    Dimension arrowOffset_;
    Color maskColor_;
    Color backgroundColor_;

    // Get from pattern
    OffsetF childOffset_;
    OffsetF arrowPosition_;
    SizeF childSize_;
    bool showArrow_ = false;

    // Get from theme
    Border border_;
    Edge padding_;

#ifndef USE_ROSEN_DRAWING
    RSPath path_;
#else
    RSRecordingPath path_;
#endif

    ACE_DISALLOW_COPY_AND_MOVE(BubblePaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_PAINT_METHOD_H