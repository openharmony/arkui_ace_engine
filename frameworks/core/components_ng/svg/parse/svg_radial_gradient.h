/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_RADIAL_GRADIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_RADIAL_GRADIENT_H
#include "core/components_ng/svg/parse/svg_attributes_parser.h"
#include "core/components_ng/svg/parse/svg_gradient.h"
namespace OHOS::Ace::NG {
class SvgRadialGradient : public SvgGradient {
    DECLARE_ACE_TYPE(SvgRadialGradient, SvgGradient);
public:
    SvgRadialGradient()
    {
        InitNoneFlag();
    }
    ~SvgRadialGradient() = default;
    static RefPtr<SvgNode> Create();
    void SetAttr(const std::string& name, const std::string& value) override;
    SvgRadialGradientInfo GetRadialGradientInfo(const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    SvgLengthScaleUnit GradientUnits();
private:
    SvgRadialGradientAttribute radialGradientAttr_;
};
}
#endif