/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_MASK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_MASK_H

#include "core/components_ng/render/drawing.h"

#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
#include "frameworks/core/components_ng/svg/parse/svg_quote.h"

namespace OHOS::Ace::NG {

class SvgMask : public SvgQuote {
    DECLARE_ACE_TYPE(SvgMask, SvgQuote);

public:
    SvgMask();
    ~SvgMask() override = default;
    static RefPtr<SvgNode> Create();

protected:
    void OnInitStyle() override;
    void OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) override;
    void OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) override;

    double ParseUnitsAttr(const Dimension& attr, double value);
    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;

private:
    Dimension x_ = Dimension(-0.1, DimensionUnit::PERCENT); // x-axis default value
    Dimension y_ = Dimension(-0.1, DimensionUnit::PERCENT); // y-axis default value
    Dimension height_ = Dimension(1.2, DimensionUnit::PERCENT); // masking area width default value
    Dimension width_ = Dimension(1.2, DimensionUnit::PERCENT); // masking area height default  value
    bool isDefaultMaskUnits_ = true;
    bool isDefaultMaskContentUnits_ = true;

    SvgMaskAttribute maskAttr_;

    RSRect maskBounds_;
    int canvasLayerCount_ = -1;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_MASK_H