/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_svg_animate.h"

#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

const char ANIMATION_RESTART_ALWAYS[] = "always";
const char ANIMATION_RESTART_WHENNOTACTIVE[] = "whenNotActive";
const char ANIMATION_RESTART_NEVER[] = "never";
const char ANIMATION_VALUE_INDEFINITE[] = "indefinite";
const char ANIMATION_FILL_MODE_FREEZE[] = "freeze";
const char ANIMATION_CALC_MODE_DISCRETE[] = "discrete";
const char ANIMATION_CALC_MODE_LINEAR[] = "linear";
const char ANIMATION_CALC_MODE_PACED[] = "paced";
const char ANIMATION_CALC_MODE_SPLINE[] = "spline";
const char ANIMATION_ADDITIVE_REPLACE[] = "replace";
const char ANIMATION_ADDITIVE_SUM[] = "sum";
const char ANIMATION_ACCUMULATE_NONE[] = "none";
const char ANIMATION_ACCUMULATE_SUM[] = "sum";

} // namespace

DOMSvgAnimate::DOMSvgAnimate(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName) {}

void DOMSvgAnimate::OnMounted(const RefPtr<DOMNode>& parentNode) {}

void DOMSvgAnimate::PrepareSpecializedComponent()
{
    if (!animateComponent_) {
        animateComponent_ = AceType::MakeRefPtr<SvgAnimateComponent>(std::to_string(GetNodeId()), GetTag());
    }
    PrepareSpecializedComponent(animateComponent_);
}

void DOMSvgAnimate::PrepareSpecializedComponent(const RefPtr<SvgAnimateComponent>& animateComponent)
{
    animateComponent->SetSvgId(svgId_);
    animateComponent->SetBegin(begin_);
    animateComponent->SetDur(dur_);
    animateComponent->SetEnd(end_);
    animateComponent->SetMin(min_);
    animateComponent->SetMax(max_);
    animateComponent->SetRestart(restart_);
    animateComponent->SetRepeatCount(repeatCount_);
    animateComponent->SetRepeatDur(repeatDur_);
    animateComponent->SetFillMode(fillMode_);
    animateComponent->SetCalcMode(calcMode_);
    animateComponent->SetValues(values_);
    animateComponent->SetKeyTimes(keyTimes_);
    animateComponent->SetKeySplines(keySplines_);
    animateComponent->SetFrom(from_);
    animateComponent->SetTo(to_);
    animateComponent->SetBy(by_);
    animateComponent->SetAttributeName(attributeName_);
    animateComponent->SetAdditive(additive_);
    animateComponent->SetAccumulate(accumulate_);
}

bool DOMSvgAnimate::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    if (attr.first == DOM_SVG_ID) {
        svgId_ = attr.second;
        return true;
    }

    if (attr.first == DOM_SVG_ANIMATION_BEGIN) {
        begin_ = ConvertTimeStr(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_DUR) {
        if (attr.second == ANIMATION_VALUE_INDEFINITE) {
            dur_ = 0;
        } else {
            dur_ = ConvertTimeStr(attr.second);
        }
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_END) {
        end_ = ConvertTimeStr(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_MIN) {
        min_ = ConvertTimeStr(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_MAX) {
        max_ = ConvertTimeStr(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_RESTART) {
        if (attr.second == ANIMATION_RESTART_ALWAYS) {
            restart_ = Restart::ALWAYS;
        } else if (attr.second == ANIMATION_RESTART_WHENNOTACTIVE) {
            restart_ = Restart::WHEN_NOT_ACTIVE;
        } else if (attr.second == ANIMATION_RESTART_NEVER) {
            restart_ = Restart::NEVER;
        }
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_REPEAT_COUNT) {
        if (attr.second == ANIMATION_VALUE_INDEFINITE) {
            repeatCount_ = -1;
        } else {
            repeatCount_ = StringToInt(attr.second);
        }
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_REPEAT_DUR) {
        repeatDur_ = ConvertTimeStr(attr.second);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_FILL) {
        if (attr.second == ANIMATION_FILL_MODE_FREEZE) {
            fillMode_ = Fill::FREEZE;
        } else {
            fillMode_ = Fill::REMOVE;
        }
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_CALC_MODE) {
        if (attr.second == ANIMATION_CALC_MODE_DISCRETE) {
            calcMode_ = CalcMode::DISCRETE;
        } else if (attr.second == ANIMATION_CALC_MODE_LINEAR) {
            calcMode_ = CalcMode::LINEAR;
        } else if (attr.second == ANIMATION_CALC_MODE_PACED) {
            calcMode_ = CalcMode::PACED;
        } else if (attr.second == ANIMATION_CALC_MODE_SPLINE) {
            calcMode_ = CalcMode::SPLINE;
        }
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_VALUES) {
        StringUtils::SplitStr(attr.second, ";", values_);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_KEY_TIMES) {
        StringUtils::StringSpliter(attr.second, ';', keyTimes_);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_KEY_SPLINES) {
        StringUtils::SplitStr(attr.second, ";", keySplines_);
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_FROM) {
        from_ = attr.second;
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_TO) {
        to_ = attr.second;
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_BY) {
        by_ = attr.second;
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_ATTRIBUTE_NAME) {
        attributeName_ = attr.second;
        return true;
    }

    if (attr.first == DOM_SVG_ANIMATION_ADDITIVE) {
        if (attr.second == ANIMATION_ADDITIVE_REPLACE) {
            additive_ = Additive::REPLACE;
        } else if (attr.second == ANIMATION_ADDITIVE_SUM) {
            additive_ = Additive::SUM_ADD;
        }
        return true;
    }
    if (attr.first == DOM_SVG_ANIMATION_ACCUMULATE) {
        if (attr.second == ANIMATION_ACCUMULATE_NONE) {
            accumulate_ = Accumulate::NONE;
        } else if (attr.second == ANIMATION_ACCUMULATE_SUM) {
            accumulate_ = Accumulate::SUM_ACC;
        }
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::Framework
