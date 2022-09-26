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

#include "frameworks/core/components_ng/svg/parse/svg_node.h"

#include "include/core/SkPaint.h"

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
        path_ = AsPath(layout); // asPath override by graphic tag
        if (UpdateFillStyle()) {
            OnGraphicFill();
        }
        if (UpdateStrokeStyle()) {
            OnGraphicStroke();
        }
    }

protected:
    bool UpdateStrokeStyle()
    {
        return false;
    }

    bool UpdateFillStyle()
    {
        return false;
    }

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
        childStyleTraversed_ = false;
        styleTraversed_ = true;
        drawTraversed_ = true;
    }

    SkPath path_;
    SkPaint fillPaint_;
    SkPaint strokePaint_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_GRAPHIC_H