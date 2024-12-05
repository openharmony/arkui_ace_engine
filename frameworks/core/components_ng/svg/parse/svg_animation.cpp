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

#include "frameworks/core/components_ng/svg/parse/svg_animation.h"

#include "frameworks/core/components_ng/svg/parse/svg_constants.h"

namespace OHOS::Ace::NG {
namespace {
const char ANIMATION_FILL_MODE_FREEZE[] = "freeze";
const char ANIMATION_CALC_MODE_DISCRETE[] = "discrete";
const char ANIMATION_CALC_MODE_PACED[] = "paced";
const char ANIMATION_CALC_MODE_SPLINE[] = "spline";

double ConvertTimeStr(const std::string& str)
{
    std::string time(str);
    StringUtils::TrimStr(time);
    double result = 0.0;
    if (StringUtils::EndWith(time, "ms")) {
        result = StringUtils::StringToDouble(std::string(time.begin(), time.end() - 2.0));
    } else if (StringUtils::EndWith(time, "s")) {
        result = StringUtils::StringToDouble(std::string(time.begin(), time.end() - 1.0)) * 1000.0;
    } else if (StringUtils::EndWith(time, "m")) {
        result = StringUtils::StringToDouble(std::string(time.begin(), time.end() - 1.0)) * 60.0 * 1000.0;
    } else {
        result = StringUtils::StringToDouble(str);
    }
    return result;
}

const std::unordered_map<std::string, CalcMode> CALC_MODE_MAP = { { ANIMATION_CALC_MODE_DISCRETE, CalcMode::DISCRETE },
    { ANIMATION_CALC_MODE_PACED, CalcMode::PACED }, { ANIMATION_CALC_MODE_SPLINE, CalcMode::SPLINE } };
} // namespace

using SvgAnimateMap = std::unordered_map<std::string, void (*)(const std::string&, SvgAnimateAttribute&)>;

SvgAnimation::SvgAnimation(SvgAnimateType svgAnimateType)
{
    svgAnimateType_ = svgAnimateType;
    InitNoneFlag();
}

void SvgAnimation::OnInitStyle() {}

RefPtr<SvgNode> SvgAnimation::Create()
{
    return MakeRefPtr<SvgAnimation>(SvgAnimateType::ANIMATE);
}

RefPtr<SvgNode> SvgAnimation::CreateAnimateMotion()
{
    return MakeRefPtr<SvgAnimation>(SvgAnimateType::MOTION);
}

RefPtr<SvgNode> SvgAnimation::CreateAnimateTransform()
{
    return MakeRefPtr<SvgAnimation>(SvgAnimateType::TRANSFORM);
}

void SvgAnimation::SetAttr(const std::string& name, const std::string& value)
{
    static const SvgAnimateMap svgMap = {
        { SVG_ANIMATION_BEGIN,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.begin = ConvertTimeStr(val);
            } },
        { SVG_ANIMATION_DUR,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                if (val == "indefinite") {
                    attr.dur = 0;
                } else {
                    attr.dur = ConvertTimeStr(val);
                }
            } },
        { SVG_ANIMATION_END,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.end = ConvertTimeStr(val);
            } },
        { SVG_ANIMATION_REPEAT_COUNT,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                if (val == "indefinite") {
                    attr.repeatCount = -1;
                } else {
                    attr.repeatCount = StringUtils::StringToInt(val);
                }
            } },
        { SVG_ANIMATION_FILL,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.fillMode = val;
            } },
        { SVG_ANIMATION_CALC_MODE,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.calcMode = val;
            } },
        { SVG_ANIMATION_VALUES,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                StringUtils::SplitStr(val, ";", attr.values);
            } },
        { SVG_ANIMATION_KEY_TIMES,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                if (val.empty()) {
                    return;
                }
                StringUtils::StringSplitter(val, ';', attr.keyTimes);
            } },
        { SVG_ANIMATION_KEY_SPLINES,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                if (val.empty()) {
                    return;
                }
                StringUtils::SplitStr(val, ";", attr.keySplines);
            } },
        { SVG_ANIMATION_FROM,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.from = val;
            } },
        { SVG_ANIMATION_TO,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.to = val;
            } },
        { SVG_ANIMATION_ATTRIBUTE_NAME,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.attributeName = val;
            } },
        { SVG_ANIMATION_KEY_POINTS,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                if (val.empty()) {
                    return;
                }
                StringUtils::StringSplitter(val, ';', attr.keyPoints);
            } },
        { SVG_ANIMATION_PATH,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.path = val;
            } },
        { SVG_ANIMATION_ROTATE,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.rotate = val;
            } },
        { SVG_ANIMATION_TYPE,
            [](const std::string& val, SvgAnimateAttribute& attr) {
                attr.transformType = val;
            } },
    };
    std::string key = name;
    // convert key to lower case to match dom_type strings
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    auto attrIter = svgMap.find(key);
    if (attrIter != svgMap.end()) {
        attrIter->second(value, animateAttr_);
    }
}

// sync attributes to SvgAnimate
void SvgAnimation::UpdateAttr()
{
    SetBegin(animateAttr_.begin);
    SetDur(animateAttr_.dur);
    SetEnd(animateAttr_.end);
    SetRepeatCount(animateAttr_.repeatCount);
    Fill fillMode = (animateAttr_.fillMode == ANIMATION_FILL_MODE_FREEZE ? Fill::FREEZE : Fill::REMOVE);
    SetFillMode(fillMode);
    SetCalcMode(ConvertCalcMode(animateAttr_.calcMode));
    SetValues(animateAttr_.values);
    SetKeyTimes(animateAttr_.keyTimes);
    SetKeySplines(animateAttr_.keySplines);
    SetFrom(animateAttr_.from);
    SetTo(animateAttr_.to);
    SetAttributeName(animateAttr_.attributeName);

    if (GetSvgAnimateType() == SvgAnimateType::MOTION) {
        SetKeyPoints(animateAttr_.keyPoints);
        SetPath(animateAttr_.path);
        SetRotate(animateAttr_.rotate);
    }
    if (GetSvgAnimateType() == SvgAnimateType::TRANSFORM) {
        SetTransformType(animateAttr_.transformType);
    }
}

CalcMode SvgAnimation::ConvertCalcMode(const std::string& val)
{
    auto it = CALC_MODE_MAP.find(val);
    if (it != CALC_MODE_MAP.end()) {
        return it->second;
    }
    // CalcMode linear by default
    return CalcMode::LINEAR;
}

template<typename T>
void SvgAnimation::CreatePropertyAnimation(const T& originalValue, std::function<void(T)>&& callback)
{
    if (animator_) {
        // reset animator
        if (!animator_->IsStopped()) {
            animator_->Stop();
        }
        animator_->ClearInterpolators();
    } else {
        animator_ = CREATE_ANIMATOR(PipelineContext::GetCurrentContext());
        animator_->AddStopListener([weak = svgContext_]() {
            auto context = AceType::DynamicCast<SvgContext>(weak.Upgrade());
            CHECK_NULL_VOID(context);
            context->OnAnimationFinished();
        });
        auto context = svgContext_.Upgrade();
        CHECK_NULL_VOID(context);
        context->AddAnimator(animator_->GetId(), animator_);
    }

    if (!CreatePropertyAnimate(std::move(callback), originalValue, animator_)) {
        animator_ = nullptr;
        LOGW("CreatePropertyAnimate failed");
    }
}

// explicit instantiation to compile
template void SvgAnimation::CreatePropertyAnimation(const Color& originalValue, std::function<void(Color)>&& callback);
template void SvgAnimation::CreatePropertyAnimation(
    const Dimension& originalValue, std::function<void(Dimension)>&& callback);
template void SvgAnimation::CreatePropertyAnimation(
    const double& originalValue, std::function<void(double)>&& callback);
} // namespace OHOS::Ace::NG
