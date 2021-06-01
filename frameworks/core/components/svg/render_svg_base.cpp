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

#include "frameworks/core/components/svg/render_svg_base.h"

#include "frameworks/core/animation/curve_animation.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t START_VALUE = 0;
constexpr int32_t END_VALUE = 1;

const std::unordered_map<std::string, std::function<Color(RenderSvgBase&)>> COLOR_PROPER_GETTERS = {
    { ATTR_NAME_FILL, [](RenderSvgBase& base) -> Color {
        return base.GetFillState().GetColor();
    } },
    { ATTR_NAME_STROKE, [](RenderSvgBase& base) -> Color {
        return base.GetStrokeState().GetColor();
    } },
};

const std::unordered_map<std::string, std::function<Dimension(RenderSvgBase&)>> DIMENSION_PROPER_GETTERS = {
    { ATTR_NAME_STROKE_WIDTH, [](RenderSvgBase& base) -> Dimension {
        return base.GetStrokeState().GetLineWidth();
    } },
    { ATTR_NAME_FONT_SIZE, [](RenderSvgBase& base) -> Dimension {
        return base.GetTextStyle().GetFontSize();
    } },
};

const std::unordered_map<std::string, std::function<double(RenderSvgBase&)>> DOUBLE_PROPER_GETTERS = {
    { ATTR_NAME_FILL_OPACITY, [](RenderSvgBase& base) -> double {
        return base.GetFillState().GetOpacity();
    } },
    { ATTR_NAME_STROKE_OPACITY, [](RenderSvgBase& base) -> double {
        return base.GetStrokeState().GetOpacity();
    } },
    { ATTR_NAME_LETTER_SPACING, [](RenderSvgBase& base) -> double {
        return base.GetTextStyle().GetLetterSpacing();
    } },
    { ATTR_NAME_MITER_LIMIT, [](RenderSvgBase& base) -> double {
        return base.GetStrokeState().GetMiterLimit();
    } },
    { ATTR_NAME_STROKE_DASHOFFSET, [](RenderSvgBase& base) -> double {
        return base.GetStrokeState().GetLineDash().dashOffset;
    } },
    { ATTR_NAME_OPACITY, [](RenderSvgBase& base) -> double {
        return base.GetOpacity() * (1.0 / UINT8_MAX);
    } },
};

} // namespace

RenderSvgBase::~RenderSvgBase()
{
    std::unordered_map<std::string, RefPtr<Animator>>::iterator it;
    for (it = animators_.begin(); it != animators_.end(); it++) {
        if (!it->second) {
            LOGE("animator is null");
            continue;
        }
        if (!it->second->IsStopped()) {
            it->second->Stop();
        }
        it->second->ClearInterpolators();
    }
    animators_.clear();
}

double RenderSvgBase::ConvertDimensionToPx(const Dimension& value, double baseValue)
{
    if (value.Unit() == DimensionUnit::PERCENT) {
        return value.Value() * baseValue;
    } else if (value.Unit() == DimensionUnit::PX) {
        return value.Value();
    } else {
        return NormalizeToPx(value);
    }
}

void RenderSvgBase::SetPresentationAttrs(const RefPtr<SvgSharp>& svgSharp)
{
    opacity_ = static_cast<uint8_t>(round(svgSharp->GetOpacity() * UINT8_MAX));
    fillState_ = svgSharp->GetFillState();
    strokeState_ = svgSharp->GetStrokeState();
    textStyle_ = svgSharp->GetTextStyle();
}

template<typename T>
void RenderSvgBase::PreparePresentationAnimation(const RefPtr<SvgAnimate>& svgAnimate, const T& originalValue,
    const RefPtr<Evaluator<T>>& evaluator)
{
    std::function<void(T)> callback;
    callback = [weakRect = AceType::WeakClaim(this), attrName = svgAnimate->GetAttributeName()](T value) {
        auto svgBase = weakRect.Upgrade();
        if (!svgBase) {
            LOGE("svgBase is null");
            return;
        }
        if (!svgBase->SetPresentationProperty(attrName, value)) {
            LOGE("no the property: %{public}s", attrName.c_str());
            return;
        }

        // notify render node to paint.
        // if tspan has changed, should notify parent node of text or textpath.
        svgBase->OnNotifyRender();

        if (svgBase->IsSvgNode()) {
            svgBase->ChangeChildInheritValue(svgBase, attrName, value);
        }
    };
    CreatePropertyAnimation(svgAnimate, originalValue, std::move(callback), evaluator);
}

template<typename T>
void RenderSvgBase::ChangeChildInheritValue(const RefPtr<RenderNode>& svgBase, const std::string& attrName, T value)
{
    if (!svgBase) {
        LOGE("ChangeChildInheritValue failed, svgBase is null");
        return;
    }
    auto renderChildren = svgBase->GetChildren();
    for (const auto& item : renderChildren) {
        if (!item->GetVisible()) {
            continue;
        }
        auto child = AceType::DynamicCast<RenderSvgBase>(item);
        if (child && !child->IsSelfValue(attrName) && !child->HasAnimator(attrName)) {
            if (child->SetPresentationProperty(attrName, value, false)) {
                child->MarkNeedRender(true);
            }
        }
        ChangeChildInheritValue(item, attrName, value);
    }
}

bool RenderSvgBase::PrepareBaseAnimation(const RefPtr<SvgAnimate>& svgAnimate)
{
    auto attrName = svgAnimate->GetAttributeName();
    if (COLOR_PROPER_GETTERS.find(attrName) != COLOR_PROPER_GETTERS.end()) {
        Color originalValue = COLOR_PROPER_GETTERS.find(attrName)->second(*this);
        RefPtr<Evaluator<Color>> evaluator = AceType::MakeRefPtr<ColorEvaluator>();
        PreparePresentationAnimation(svgAnimate, originalValue, evaluator);
    } else if (DIMENSION_PROPER_GETTERS.find(attrName) != DIMENSION_PROPER_GETTERS.end()) {
        Dimension originalValue = DIMENSION_PROPER_GETTERS.find(attrName)->second(*this);
        RefPtr<Evaluator<Dimension>> evaluator = AceType::MakeRefPtr<LinearEvaluator<Dimension>>();
        PreparePresentationAnimation(svgAnimate, originalValue, evaluator);
    } else if (DOUBLE_PROPER_GETTERS.find(attrName) != DOUBLE_PROPER_GETTERS.end()) {
        double originalValue = DOUBLE_PROPER_GETTERS.find(attrName)->second(*this);
        RefPtr<Evaluator<double>> evaluator = AceType::MakeRefPtr<LinearEvaluator<double>>();
        PreparePresentationAnimation(svgAnimate, originalValue, evaluator);
    } else {
        return false;
    }
    return true;
}

template<typename T>
bool RenderSvgBase::CreatePropertyAnimation(const RefPtr<SvgAnimate>& svgAnimate, const T& originalValue,
    std::function<void(T)>&& callback, const RefPtr<Evaluator<T>>& evaluator)
{
    if (!svgAnimate) {
        LOGE("create property animation failed, svgAnimate is null");
        return false;
    }
    auto animatorIter = animators_.find(svgAnimate->GetAttributeName());
    if (animatorIter != animators_.end()) {
        if (!animatorIter->second->IsStopped()) {
            animatorIter->second->Stop();
        }
        animatorIter->second->ClearInterpolators();
        auto animator = animatorIter->second;
        if (!svgAnimate->CreatePropertyAnimate(std::move(callback), originalValue, evaluator, animator)) {
            animators_.erase(animatorIter);
        }
    } else {
        auto animator = AceType::MakeRefPtr<Animator>(context_);
        if (svgAnimate->CreatePropertyAnimate(std::move(callback), originalValue, evaluator, animator)) {
            animators_.emplace(svgAnimate->GetAttributeName(), animator);
        }
    }
    return true;
}

bool RenderSvgBase::PrepareAnimateMotion(const RefPtr<SvgAnimate>& svgAnimate)
{
    if (!svgAnimate || svgAnimate->GetSvgAnimateType() != SvgAnimateType::MOTION) {
        LOGE("create motion animation failed, svgAnimate is null");
        return false;
    }
    std::function<void(double)> callback;
    callback = [weak = AceType::WeakClaim(this), path = svgAnimate->GetPath(),
        rotate = svgAnimate->GetRotate()](double value) {
        auto sharp = weak.Upgrade();
        if (!sharp) {
            LOGE("sharp is null");
            return;
        }
        Point point;
        if (!sharp->GetStartPoint(point)) {
            return;
        }
        sharp->UpdateMotion(path, rotate, value, point);
        sharp->MarkNeedLayout(true);
    };

    auto animatorIter = animators_.find(ANIMATOR_TYPE_MOTION);
    if (animatorIter != animators_.end()) {
        if (!animatorIter->second->IsStopped()) {
            animatorIter->second->Stop();
        }
        animatorIter->second->ClearInterpolators();
        auto animator = animatorIter->second;
        if (!svgAnimate->CreateMotionAnimate(std::move(callback), animator)) {
            animators_.erase(animatorIter);
        }
    } else {
        auto animator = AceType::MakeRefPtr<Animator>(context_);
        if (svgAnimate->CreateMotionAnimate(std::move(callback), animator)) {
            animators_.emplace(ANIMATOR_TYPE_MOTION, animator);
        }
    }
    return true;
}

void RenderSvgBase::PrepareWeightAnimate(const RefPtr<SvgAnimate>& svgAnimate, std::vector<std::string>& valueVector,
    const std::string& originalValue, bool& isBy)
{
    if (!svgAnimate->GetValues().empty()) {
        valueVector = svgAnimate->GetValues();
        valueVector.insert(valueVector.begin(), originalValue);
        std::vector<std::string> newValues;
        int32_t size =  svgAnimate->GetValues().size();
        for (int32_t i = 0; i < size; i++) {
            newValues.emplace_back(std::to_string(i));
        }
        svgAnimate->SetValues(newValues);
    } else {
        std::string from = svgAnimate->GetFrom().empty() ? originalValue : svgAnimate->GetFrom();
        if (!svgAnimate->GetTo().empty()) {
            valueVector.emplace_back(from);
            valueVector.emplace_back(svgAnimate->GetTo());
            svgAnimate->SetFrom(std::to_string(START_VALUE));
            svgAnimate->SetTo(std::to_string(END_VALUE));
        } else if (!svgAnimate->GetBy().empty()) {
            valueVector.emplace_back(from);
            valueVector.emplace_back(svgAnimate->GetBy());
            svgAnimate->SetFrom(std::to_string(START_VALUE));
            svgAnimate->SetTo(std::to_string(END_VALUE));
            isBy = true;
        } else {
            if (from == originalValue) {
                return;
            }
            valueVector.emplace_back(originalValue);
            valueVector.emplace_back(from);
            svgAnimate->SetFrom(std::to_string(START_VALUE));
            svgAnimate->SetTo(std::to_string(END_VALUE));
        }
    }
}

template<typename T>
bool RenderSvgBase::SetPresentationProperty(const std::string& attrName, const T& val, bool isSelf)
{
    return false;
}

template<>
bool RenderSvgBase::SetPresentationProperty(const std::string& attrName, const Color& val, bool isSelf)
{
    if (attrName == ATTR_NAME_FILL) {
        fillState_.SetColor(val, isSelf);
    } else if (attrName == ATTR_NAME_STROKE) {
        strokeState_.SetColor(val, isSelf);
    } else {
        return false;
    }
    return true;
}

template<>
bool RenderSvgBase::SetPresentationProperty(const std::string& attrName, const Dimension& val, bool isSelf)
{
    if (attrName == ATTR_NAME_STROKE_WIDTH) {
        strokeState_.SetLineWidth(val, isSelf);
    } else if (attrName == ATTR_NAME_FONT_SIZE) {
        textStyle_.SetFontSize(val, isSelf);
    } else {
        return false;
    }
    return true;
}

template<>
bool RenderSvgBase::SetPresentationProperty(const std::string& attrName, const double& val, bool isSelf)
{
    if (attrName == ATTR_NAME_FILL_OPACITY) {
        fillState_.SetOpacity(val, isSelf);
    } else if (attrName == ATTR_NAME_STROKE_OPACITY) {
        strokeState_.SetOpacity(val, isSelf);
    } else if (attrName == ATTR_NAME_LETTER_SPACING) {
        textStyle_.SetLetterSpacing(val, isSelf);
    } else if (attrName == ATTR_NAME_MITER_LIMIT) {
        strokeState_.SetMiterLimit(val, isSelf);
    } else if (attrName == ATTR_NAME_STROKE_DASHOFFSET) {
        strokeState_.SetLineDashOffset(val, isSelf);
    } else if (attrName == ATTR_NAME_OPACITY) {
        opacity_ = static_cast<uint8_t>(round(val * UINT8_MAX));
    } else {
        return false;
    }
    return true;
}

bool RenderSvgBase::IsSelfValue(const std::string& attrName)
{
    if (attrName == ATTR_NAME_FILL_OPACITY) {
        return fillState_.HasOpacity();
    } else if (attrName == ATTR_NAME_STROKE_OPACITY) {
        return strokeState_.HasOpacity();
    } else if (attrName == ATTR_NAME_LETTER_SPACING) {
        return textStyle_.HasLetterSpacing();
    } else if (attrName == ATTR_NAME_MITER_LIMIT) {
        return strokeState_.HasMiterLimit();
    } else if (attrName == ATTR_NAME_STROKE_DASHOFFSET) {
        return strokeState_.HasDashOffset();
    } else if (attrName == ATTR_NAME_STROKE_WIDTH) {
        return strokeState_.HasLineWidth();
    } else if (attrName == ATTR_NAME_FONT_SIZE) {
        return textStyle_.HasFontSize();
    } else if (attrName == ATTR_NAME_FILL) {
        return fillState_.HasColor();
    } else if (attrName == ATTR_NAME_STROKE) {
        return strokeState_.HasColor();
    } else {
        return true;
    }
}

bool RenderSvgBase::HasAnimator(const std::string& attrName)
{
    return !animators_.empty() && animators_.find(attrName) != animators_.end();
}

void RenderSvgBase::PrepareAnimation(const std::list<RefPtr<Component>>& componentChildren)
{
    for (const auto& childComponent : componentChildren) {
        auto svgAnimate = AceType::DynamicCast<SvgAnimate>(childComponent);
        if (!svgAnimate) {
            LOGE("animateComponent is null");
            continue;
        }
        if (!PrepareAnimateMotion(svgAnimate)) {
            PreparePropertyAnimation(svgAnimate);
        }
    }
}

bool RenderSvgBase::PreparePropertyAnimation(const RefPtr<SvgAnimate>& svgAnimate)
{
    if (svgAnimate->GetSvgAnimateType() != SvgAnimateType::ANIMATE) {
        return false;
    }
    if (!PrepareSelfAnimation(svgAnimate)) {
        PrepareBaseAnimation(svgAnimate);
    }
    return true;
}

template bool RenderSvgBase::CreatePropertyAnimation(const RefPtr<SvgAnimate>& svgAnimate, const Color& originalValue,
    std::function<void(Color)>&& callback, const RefPtr<Evaluator<Color>>& evaluator);
template bool RenderSvgBase::CreatePropertyAnimation(const RefPtr<SvgAnimate>& svgAnimate,
    const Dimension& originalValue, std::function<void(Dimension)>&& callback,
    const RefPtr<Evaluator<Dimension>>& evaluator);
template bool RenderSvgBase::CreatePropertyAnimation(const RefPtr<SvgAnimate>& svgAnimate,
    const double& originalValue, std::function<void(double)>&& callback, const RefPtr<Evaluator<double>>& evaluator);
template void RenderSvgBase::PreparePresentationAnimation(const RefPtr<SvgAnimate>& svgAnimate, const Dimension& value,
    const RefPtr<Evaluator<Dimension>>& evaluator);
template void RenderSvgBase::PreparePresentationAnimation(const RefPtr<SvgAnimate>& svgAnimate, const Color& value,
    const RefPtr<Evaluator<Color>>& evaluator);
template void RenderSvgBase::PreparePresentationAnimation(const RefPtr<SvgAnimate>& svgAnimate, const double& value,
    const RefPtr<Evaluator<double>>& evaluator);

} // namespace OHOS::Ace
