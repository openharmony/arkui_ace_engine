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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_GRAPHIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_GRAPHIC_H

#include "include/core/SkPaint.h"

#include "frameworks/core/components_ng/svg/parse/svg_node.h"

namespace OHOS::Ace::NG {

class SvgGraphic : public SvgNode {
    DECLARE_ACE_TYPE(SvgGraphic, SvgNode);

public:
    SvgGraphic() : SvgNode()
    {
        InitGraphicFlag();
    }
    ~SvgGraphic() override = default;

    void OnDraw(RSCanvas& canvas, const Size& layout, const std::optional<Color>& color) override
    {
        fillPaint_.reset();
        strokePaint_.reset();
        path_ = AsPath(layout); // asPath override by graphic tag
        UpdateGradient(layout);
        if (UpdateFillStyle(color)) {
            OnGraphicFill();
        }
        if (UpdateStrokeStyle()) {
            OnGraphicStroke();
        }
    }

protected:
    void OnGraphicFill()
    {
        if (skCanvas_) {
            skCanvas_->drawPath(path_, fillPaint_);
        }
    }

    void OnGraphicStroke()
    {
        if (skCanvas_) {
            skCanvas_->drawPath(path_, strokePaint_);
        }
    }

    // rect line polygon path circle ellipse
    void InitGraphicFlag()
    {
        hrefFill_ = true;
        hrefRender_ = true;
        passStyle_ = false;
        inheritStyle_ = true;
        drawTraversed_ = true;
    }

    // Update fillStates & strokeStates
    void UpdateGradient(const Size& viewPort);
    bool UpdateFillStyle(const std::optional<Color>& color, bool antiAlias = true);
    bool UpdateStrokeStyle(bool antiAlias = true);
    void SetGradientStyle(double opacity);
    void UpdateLineDash();

    SkPath path_;
    SkPaint fillPaint_;
    SkPaint strokePaint_;
    FillState fillState_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_GRAPHIC_H