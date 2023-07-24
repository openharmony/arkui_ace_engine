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

#include "frameworks/core/components_ng/svg/parse/svg_animation.h"

#include <unordered_map>

#include "frameworks/core/components/declaration/svg/svg_animate_declaration.h"

namespace OHOS::Ace::NG {
namespace {
const char ANIMATION_FILL_MODE_FREEZE[] = "freeze";
const char ANIMATION_CALC_MODE_DISCRETE[] = "discrete";
const char ANIMATION_CALC_MODE_PACED[] = "paced";
const char ANIMATION_CALC_MODE_SPLINE[] = "spline";

const std::unordered_map<std::string, CalcMode> CALC_MODE_MAP = { { ANIMATION_CALC_MODE_DISCRETE, CalcMode::DISCRETE },
    { ANIMATION_CALC_MODE_PACED, CalcMode::PACED }, { ANIMATION_CALC_MODE_SPLINE, CalcMode::SPLINE } };
} // namespace

SvgAnimation::SvgAnimation(SvgAnimateType svgAnimateType)
{
    svgAnimateType_ = svgAnimateType;
    animDeclaration_ = AceType::MakeRefPtr<SvgAnimateDeclaration>();
    animDeclaration_->Init();
    animDeclaration_->InitializeStyle();

    InitNoneFlag();
}

void SvgAnimation::OnInitStyle() {}

RefPtr<SvgNode> SvgAnimation::Create()
{
    LOGD("svgAnimate create");
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
    animDeclaration_->SetSpecializedAttr({ name, value });
}

// sync attributes from declaration to SvgAnimate
void SvgAnimation::UpdateAttr()
{
    CHECK_NULL_VOID(animDeclaration_);
    SetBegin(animDeclaration_->GetBegin());
    SetDur(animDeclaration_->GetDur());
    SetEnd(animDeclaration_->GetEnd());
    SetRepeatCount(animDeclaration_->GetRepeatCount());
    Fill fillMode = (animDeclaration_->GetFillMode() == ANIMATION_FILL_MODE_FREEZE ? Fill::FREEZE : Fill::REMOVE);
    SetFillMode(fillMode);
    SetCalcMode(ConvertCalcMode(animDeclaration_->GetCalcMode()));
    SetValues(animDeclaration_->GetValues());
    SetKeyTimes(animDeclaration_->GetKeyTimes());
    SetKeySplines(animDeclaration_->GetKeySplines());
    SetFrom(animDeclaration_->GetFrom());
    SetTo(animDeclaration_->GetTo());
    SetAttributeName(animDeclaration_->GetAttributeName());

    if (GetSvgAnimateType() == SvgAnimateType::MOTION) {
        SetKeyPoints(animDeclaration_->GetKeyPoints());
        SetPath(animDeclaration_->GetPath());
        SetRotate(animDeclaration_->GetRotate());
    }
    if (GetSvgAnimateType() == SvgAnimateType::TRANSFORM) {
        SetTransformType(animDeclaration_->GetTransformType());
    }
}

CalcMode SvgAnimation::ConvertCalcMode(const std::string& val)
{
    if (CALC_MODE_MAP.find(val) != CALC_MODE_MAP.end()) {
        return CALC_MODE_MAP.find(val)->second;
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
