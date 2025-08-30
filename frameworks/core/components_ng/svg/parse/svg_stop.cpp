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

#include "frameworks/core/components_ng/svg/parse/svg_stop.h"

#include "core/common/container.h"
#include "frameworks/core/components_ng/svg/parse/svg_constants.h"
#include "frameworks/core/components_ng/svg/svg_utils.h"

namespace OHOS::Ace::NG {

namespace {
const char DOM_SVG_SRC_STOP_COLOR[] = "stop-color";
const char DOM_SVG_SRC_STOP_OPACITY[] = "stop-opacity";
const char VALUE_NONE[] = "none";
}

SvgStop::SvgStop() : SvgNode() {}

RefPtr<SvgNode> SvgStop::Create()
{
    auto svgNode = AceType::MakeRefPtr<SvgStop>();
    svgNode->stopAttr_.gradientColor.SetDimension(0.0);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
        svgNode->stopAttr_.gradientColor.SetColor(Color::BLACK);
    }
    return svgNode;
}

const Ace::GradientColor& SvgStop::GetGradientColor() const
{
    return stopAttr_.gradientColor;
}

bool SvgStop::ParseAndSetSpecializedAttr(const std::string& name, const std::string& value)
{
    static const LinearMapNode<void (*)(const std::string&, SvgStopAttribute&)> attrs[] = {
        { SVG_OFFSET,
            [](const std::string& val, SvgStopAttribute& attribute) {
                attribute.gradientColor.SetDimension(SvgAttributesParser::ParseDimension(val));
            } },
        { DOM_SVG_SRC_STOP_COLOR,
            [](const std::string& val, SvgStopAttribute& attribute) {
                Color color = (val == VALUE_NONE ? Color::TRANSPARENT : SvgAttributesParser::GetColor(val));
                if (!SvgUtils::IsFeatureEnable(SVG_FEATURE_SUPPORT_TWO, attribute.usrConfigVersion)) {
                    attribute.gradientColor.SetColor(color);
                    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
                        SvgAttributesParser::CheckColorAlpha(val, color);
                        attribute.gradientColor.SetColor(color);
                    }
                    return;
                }
                SvgAttributesParser::ParseRGBAMagicColor(val, color);
                SvgAttributesParser::CheckColorAlpha(val, color);
                attribute.gradientColor.SetColor(color);
            } },
        { DOM_SVG_SRC_STOP_OPACITY,
            [](const std::string& val, SvgStopAttribute& attribute) {
                attribute.gradientColor.SetOpacity(SvgAttributesParser::ParseDouble(val));
            } },
        { SVG_STOP_COLOR,
            [](const std::string& val, SvgStopAttribute& attribute) {
                Color color = (val == VALUE_NONE ? Color::TRANSPARENT : SvgAttributesParser::GetColor(val));
                if (!SvgUtils::IsFeatureEnable(SVG_FEATURE_SUPPORT_TWO, attribute.usrConfigVersion)) {
                    attribute.gradientColor.SetColor(color);
                    return;
                }
                SvgAttributesParser::ParseRGBAMagicColor(val, color);
                attribute.gradientColor.SetColor(color);
            } },
        { SVG_STOP_OPACITY,
            [](const std::string& val, SvgStopAttribute& attribute) {
                attribute.gradientColor.SetOpacity(SvgAttributesParser::ParseDouble(val));
            } },
    };
    auto attrIter = BinarySearchFindIndex(attrs, ArraySize(attrs), name.c_str());
    if (attrIter != -1) {
        stopAttr_.usrConfigVersion = GetUsrConfigVersion();
        attrs[attrIter].value(value, stopAttr_);
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
