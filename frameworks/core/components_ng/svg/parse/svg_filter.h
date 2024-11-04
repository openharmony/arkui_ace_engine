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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FILTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FILTER_H

#include "include/core/SkPaint.h"

#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
#include "frameworks/core/components_ng/svg/parse/svg_quote.h"

namespace OHOS::Ace::NG {

class SvgFilter : public SvgQuote {
    DECLARE_ACE_TYPE(SvgFilter, SvgQuote);

public:
    SvgFilter();
    ~SvgFilter() override = default;
    static RefPtr<SvgNode> Create();
    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;

protected:
    void OnInitStyle() override;
    void OnDrawTraversed(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) override;
    void OnDrawTraversedBefore(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) override;
    void OnDrawTraversedAfter(RSCanvas& canvas, const Size& viewPort, const std::optional<Color>& color) override;

    void OnAsPaint();

private:
    RSBrush filterBrush_;
    SvgFilterAttribute filterAttr_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_FILTER_H