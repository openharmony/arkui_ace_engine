/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include <cmath>
#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components/rating/rating_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_layout_property.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_paint_method.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const bool RATING_INDICATOR = true;
const bool RATING_INDICATOR_FALSE = false;
const int32_t DEFAULT_STAR_NUM = 5;
const int32_t RATING_STAR_NUM = 10;
constexpr double RATING_SCORE = 3.0;
constexpr double RATING_LAST_SCORE = 5.0;
constexpr double RATING_SCORE_3 = 3.5;
constexpr double RATING_SCORE_4 = 3.0;
constexpr double RATING_SCORE_5 = 1.0;
constexpr double DEFAULT_RATING_SCORE = 0.0;
constexpr double DEFAULT_STEP_SIZE = 0.5;
constexpr double RATING_STEP_SIZE_1 = 1;
} // namespace

class RatingContentModifierTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingContentModifierTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == RatingTheme::TypeId()) {
            return AceType::MakeRefPtr<RatingTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void RatingContentModifierTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RatingPatternTest013
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE);
}

/**
 * @tc.name: RatingPatternTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest015
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_LAST_SCORE);
}

/**
 * @tc.name: RatingPatternTest016
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_4);
}

/**
 * @tc.name: RatingPatternTest017
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_5);
}

/**
 * @tc.name: RatingPatternTest018
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_3);
}

/**
 * @tc.name: RatingPatternTest019
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE);
}

/**
 * @tc.name: RatingPatternTest020
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_LAST_SCORE);
}

/**
 * @tc.name: RatingPatternTest021
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_4);
}

/**
 * @tc.name: RatingPatternTest022
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_5);
}

/**
 * @tc.name: RatingPatternTest023
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_3);
}

/**
 * @tc.name: RatingPatternTest024
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE);
}

/**
 * @tc.name: RatingPatternTest025
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_LAST_SCORE);
}

/**
 * @tc.name: RatingPatternTest026
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_4);
}

/**
 * @tc.name: RatingPatternTest027
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_5);
}

/**
 * @tc.name: RatingPatternTest028
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_3);
}

/**
 * @tc.name: RatingPatternTest029
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE);
}

/**
 * @tc.name: RatingPatternTest030
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_LAST_SCORE);
}

/**
 * @tc.name: RatingPatternTest031
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_4);
}

/**
 * @tc.name: RatingPatternTest032
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_5);
}

/**
 * @tc.name: RatingPatternTest033
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest034
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE);
            EXPECT_EQ(config.stepSize_, RATING_STEP_SIZE_1);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest035
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest036
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_LAST_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest037
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_4);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest038
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_5);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest039
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_3);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest040
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_LAST_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest041
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_SCORE_4);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest042
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_SCORE_5);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest043
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_SCORE_3);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest044
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_LAST_SCORE);
            EXPECT_EQ(config.stepSize_, RATING_STEP_SIZE_1);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest045
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_4);
            EXPECT_EQ(config.stepSize_, RATING_STEP_SIZE_1);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest046
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_5);
            EXPECT_EQ(config.stepSize_, RATING_STEP_SIZE_1);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest047
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_LAST_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest048
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_4);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest049
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_5);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest050
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
            EXPECT_EQ(config.rating_, RATING_SCORE_3);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest051
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_LAST_SCORE);
            EXPECT_EQ(config.stepSize_, RATING_STEP_SIZE_1);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest052
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE);
}

/**
 * @tc.name: RatingPatternTest053
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_LAST_SCORE);
}

/**
 * @tc.name: RatingPatternTest054
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_3);
}

/**
 * @tc.name: RatingPatternTest055
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_4);
}

/**
 * @tc.name: RatingPatternTest056
 * @tc.desc: SetChangeValue and get value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Get render property.
     * @tc.expected: Check the Rating property value.
     */
    double ratingScore = DEFAULT_RATING_SCORE;
    if (ratingRenderProperty->HasRatingScore()) {
        ratingScore = ratingRenderProperty->GetRatingScore().value();
    } else {
        ratingScore = DEFAULT_RATING_SCORE;
    }
    EXPECT_EQ(ratingScore, RATING_SCORE_5);
}

/**
 * @tc.name: RatingPatternTest057
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}

/**
 * @tc.name: RatingPatternTest058
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingContentModifierTestNg, RatingPatternTest058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(RATING_LAST_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, RATING_LAST_SCORE);
            EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
            return nullptr;
        };

    /**
     * @tc.steps: step4. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG