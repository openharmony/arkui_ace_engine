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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_SVG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_SVG_H

#include "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"
#include "frameworks/core/components_ng/svg/parse/svg_group.h"

namespace OHOS::Ace::NG {

class SvgSvg : public SvgGroup {
    DECLARE_ACE_TYPE(SvgSvg, SvgGroup);

public:
    SvgSvg();
    ~SvgSvg() override = default;
    static RefPtr<SvgNode> Create();

    RSRecordingPath AsPath(const Size& viewPort) const override;
    RSRecordingPath AsPath(const SvgLengthScaleRule& lengthRule) override;

    Size GetSize() const;

    Rect GetViewBox() const;
    bool ParseAndSetSpecializedAttr(const std::string& name, const std::string& value) override;
    void AdjustContentAreaByViewBox(RSCanvas& canvas, const Size& viewPort) override;
    void AdjustContentAreaSvgSizeValid(RSCanvas& canvas, const Size& viewPort, const Size& svgSize,
        const Rect& viewBox);
    void AdjustContentAreaSvgSizeInvalid(RSCanvas& canvas, const Size& viewPort, const Size& svgSize,
        const Rect& viewBox);
    SvgPreserveAspectRatio GetPreserveAspectRatio() const;

private:
    SvgAttributes svgAttr_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_SVG_H