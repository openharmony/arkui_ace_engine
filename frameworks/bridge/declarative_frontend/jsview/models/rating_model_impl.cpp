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

#include "bridge/declarative_frontend/jsview/models/rating_model_impl.h"

#include "core/components/rating/rating_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void RatingModelImpl::Create(double rating, bool indicator)
{
    auto component = AceType::MakeRefPtr<RatingComponent>();
    component->SetMouseAnimationType(HoverAnimationType::NONE);
    component->SetRatingScore(rating);
    component->SetIndicator(indicator);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(theme);

    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (component->GetIndicator()) {
        if (boxComponent->GetHeightDimension().Value() < 0.0) {
            boxComponent->SetHeight(theme->GetRatingMiniHeight());
        }
        if (boxComponent->GetWidthDimension().Value() < 0.0) {
            boxComponent->SetWidth(theme->GetRatingMiniWidth());
        }
        component->SetPaddingVertical(Dimension());
        component->SetMiniResIdFromTheme(theme);
    } else {
        if (boxComponent->GetHeightDimension().Value() < 0.0) {
            boxComponent->SetHeight(theme->GetRatingHeight());
        }
        if (boxComponent->GetWidthDimension().Value() < 0.0) {
            boxComponent->SetWidth(theme->GetRatingWidth());
        }
        component->SetPaddingVertical(theme->GetPaddingVertical());
        component->SetResIdFromTheme(theme);
    }
    component->SetThemeStyle(theme);
}

void RatingModelImpl::SetRatingScore(double value)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetRatingScore(value);
}

void RatingModelImpl::SetIndicator(bool value)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetIndicator(value);
}

void RatingModelImpl::SetStars(int32_t value)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetStarNum(value);
}

void RatingModelImpl::SetStepSize(double value)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetStepSize(value);
}

void RatingModelImpl::SetForegroundSrc(const std::string& value, bool flag)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetForegroundSrc(value);
}

void RatingModelImpl::SetSecondarySrc(const std::string& value, bool flag)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetSecondarySrc(value);
}

void RatingModelImpl::SetBackgroundSrc(const std::string& value, bool flag)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetBackgroundSrc(value);
}

void RatingModelImpl::SetOnChange(RatingChangeEvent&& onChange)
{
    auto ratingComponent = AceType::DynamicCast<RatingComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(ratingComponent);
    ratingComponent->SetOnChange(onChange);
}

} // namespace OHOS::Ace::Framework