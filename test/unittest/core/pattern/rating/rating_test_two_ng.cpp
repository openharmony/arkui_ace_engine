/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/rating/rating_layout_property.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_paint_method.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/root/root_pattern.h"

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
const std::string RATING_SCORE_STRING = "";
constexpr double RATING_SCORE_4 = 3.0;
constexpr double RATING_SCORE_5 = 1.0;
constexpr double RATING_SCORE_10 = 10.0f;
const std::string RATING_BACKGROUND_URL = "common/img1.png";
const std::string RATING_FOREGROUND_URL = "common/img2.png";
const std::string RATING_SECONDARY_URL = "common/img3.png";
const std::string RATING_SVG_URL = "common/img4.svg";
constexpr double DEFAULT_RATING_SCORE = 0.0;
constexpr double DEFAULT_STEP_SIZE = 0.5;
constexpr double RATING_STEP_SIZE_1 = 1;
const float FRAME_WIDTH = 400.0f;
const float FRAME_HEIGHT = 400.0f;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const float INVALID_CONTAINER_WIDTH = -300.0f;
const float INVALID_CONTAINER_HEIGHT = -300.0f;
const SizeF INVALID_CONTAINER_SIZE(INVALID_CONTAINER_WIDTH, INVALID_CONTAINER_HEIGHT);
const SizeF ZERO_CONTAINER_SIZE(DEFAULT_RATING_SCORE, DEFAULT_RATING_SCORE);
const std::string RESOURCE_URL = "resource:///ohos_test_image.svg";
const std::string IMAGE_SOURCE_INFO_STRING = "empty source";
const std::string RATING_IMAGE_LOAD_FAILED = "ImageDataFailed";
const std::string RATING_IMAGE_LOAD_SUCCESS = "ImageDataSuccess";
const std::string RATING_FOREGROUND_IMAGE_KEY = "foregroundImageSourceInfo";
const std::string RATING_SECONDARY_IMAGE_KEY = "secondaryImageSourceInfo";
const std::string RATING_BACKGROUND_IMAGE_KEY = "backgroundImageSourceInfo";
const std::string TEST_RESULT_FIRST = "test_ok_1";
const std::string TEST_RESULT_SECOND = "test_ok_2";
const std::string TEST_RESULT_THIRD = "test_ok_3";
const std::string TEST_RESULT_FORTH = "test_ok_4";
constexpr int32_t OFFSET_FIRST = 10;
constexpr int32_t OFFSET_SECOND = 20;
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_10 = SizeF(10.0f, 10.0f);
constexpr float TEST_WIDTH_50 = 50.0f;
} // namespace

class RatingTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingTwoTestNg::SetUpTestCase()
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

void RatingTwoTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RatingPatternTest063
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest063, TestSize.Level1)
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
 * @tc.name: RatingPatternTest064
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest064, TestSize.Level1)
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
 * @tc.name: RatingPatternTest065
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest065, TestSize.Level1)
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
 * @tc.name: RatingPatternTest066
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest066, TestSize.Level1)
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
 * @tc.name: RatingPatternTest067
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest067, TestSize.Level1)
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
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Set parameters to pattern ratingScore.
     */
    ratingPattern->SetRatingScore(DEFAULT_RATING_SCORE);

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
    EXPECT_EQ(ratingScore, DEFAULT_RATING_SCORE);
}

/**
 * @tc.name: RatingPatternTest068
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
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
 * @tc.name: RatingPatternTest069
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
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
 * @tc.name: RatingPatternTest070
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
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
 * @tc.name: RatingPatternTest071
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
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
 * @tc.name: RatingPatternTest072
 * @tc.desc: test RatingPattern::HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest072, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(pattern, nullptr);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    pattern->LoadForeground(ratingLayoutProperty, ratingTheme, iconTheme);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    /**
     * @tc.steps: step2. Mock TouchEvent info and set preventDefault to false
     * @tc.expected: Check the param value
     */
    GestureEvent clickInfo;
    clickInfo.SetPreventDefault(false);
    clickInfo.SetSourceDevice(SourceType::TOUCH);
    pattern->HandleClick(clickInfo);
    clickInfo.SetLocalLocation(Offset(OFFSET_FIRST, OFFSET_SECOND));
    pattern->HandleClick(clickInfo);
    EXPECT_FALSE(Negative(clickInfo.GetLocalLocation().GetX()));
}
/**
 * @tc.name: RatingPatternTest073
 * @tc.desc: test RatingModelNG::SetForegroundSrc SetSecondarySrc SetBackgroundSrc
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    /**
     * @tc.steps: step2. call function and flag is false.
     * @tc.expected: these properties are updated.
     */
    rating.SetForegroundSrc(frameNode, RATING_FOREGROUND_URL, false);
    rating.SetSecondarySrc(frameNode, RATING_SECONDARY_URL, false);
    rating.SetBackgroundSrc(frameNode, RATING_BACKGROUND_URL, false);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    EXPECT_FALSE(ratingPattern->foregroundConfig_.isSvg_);
    EXPECT_FALSE(ratingPattern->secondaryConfig_.isSvg_);
    EXPECT_FALSE(ratingPattern->backgroundConfig_.isSvg_);
    /**
     * @tc.steps: step2+. call function and flag is true.
     * @tc.expected: these properties are updated.
     */
    rating.SetForegroundSrc(frameNode, RATING_FOREGROUND_URL, true);
    rating.SetSecondarySrc(frameNode, RATING_SECONDARY_URL, true);
    rating.SetBackgroundSrc(frameNode, RATING_BACKGROUND_URL, true);
    EXPECT_FALSE(ratingPattern->foregroundConfig_.isSvg_);
    EXPECT_FALSE(ratingPattern->secondaryConfig_.isSvg_);
    EXPECT_FALSE(ratingPattern->backgroundConfig_.isSvg_);
}
/**
 * @tc.name: RatingPatternTest074
 * @tc.desc: test RatingPattern::HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest074, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto ratingpattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingpattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    /**
     * @tc.steps: step2. call HandleHoverEvent and flag is false or true.
     * @tc.expected: test state_ is update or not.
     */
    ratingpattern->HandleHoverEvent(true);
    EXPECT_EQ(ratingpattern->state_, RatingModifier::RatingAnimationType::HOVER);
    ratingpattern->HandleHoverEvent(false);
    EXPECT_EQ(ratingpattern->state_, RatingModifier::RatingAnimationType::NONE);
}

/**
 * @tc.name: RatingPatternTest075
 * @tc.desc: test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest075, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStepSize(RATING_STEP_SIZE_1);
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Mock GestureEvent info
     */
    GestureEvent dragInfo;
    pattern->InitPanEvent(gestureHub);
    EXPECT_FALSE(LessNotEqual(dragInfo.GetLocalLocation().GetX(), 0.0));
}

/**
 * @tc.name: RatingNGTest076
 * @tc.desc: test SetRatingOptions
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingNGTest076, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating node.
     */
    auto frameNode = RatingModelNG::CreateFrameNode(0);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. SetRatingOptions.
     */
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    RatingModelNG::SetRatingOptions(node, 10, true);

    /**
     * @tc.steps: step3. Get layoutProperty and assert the value.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetIndicatorValue(false), true);
    auto paintProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_EQ(paintProperty->GetRatingScoreValue(), RATING_SCORE_10);
}

/**
 * @tc.name: RatingPatternTest016
 * @tc.desc: Test rating three images and focus image render scale.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create rating FrameNode and Pattern, and initialize rating modifier.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    ratingPattern->isNeedFocusStyle_ = true;
    ratingPattern->OnModifyDone();
    ratingPattern->InitEvent();
    /**
     * @tc.steps: step2. Create image canvas.
     */
    ratingPattern->foregroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->secondaryImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageFocusCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    /**
     * @tc.steps: step3. Update PaintConfig and invoke CreateNodePaintMethod.
     */
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    frameNode->geometryNode_->SetFrameSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    frameNode->geometryNode_->SetContentSize(CONTAINER_SIZE);
    ratingPattern->imageSuccessStateCode_ = 0b1111;
    auto paintMethod2 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod2, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    /**
     * @tc.steps: step4. calculate scale size.
     * @tc.expected: get ImagePaintConfig and check scaleX && scaleY.
     */
    auto scaleX = CONTAINER_SIZE.Height() / FRAME_WIDTH / DEFAULT_STAR_NUM;
    auto scaleY = CONTAINER_SIZE.Height() / FRAME_HEIGHT;
    EXPECT_EQ(ratingPattern->backgroundFocusConfig_.scaleX_, scaleX);
    EXPECT_EQ(ratingPattern->backgroundFocusConfig_.scaleY_, scaleY);
    ASSERT_NE(ratingPattern->ratingModifier_->foregroundImageCanvas_->paintConfig_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->secondaryImageCanvas_->paintConfig_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->backgroundImageCanvas_->paintConfig_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->backgroundImageFocusCanvas_->paintConfig_, nullptr);
    EXPECT_EQ(ratingPattern->foregroundConfig_.scaleX_,
        ratingPattern->ratingModifier_->foregroundImageCanvas_->GetPaintConfig().scaleX_);
    EXPECT_EQ(ratingPattern->foregroundConfig_.scaleY_,
        ratingPattern->ratingModifier_->foregroundImageCanvas_->GetPaintConfig().scaleY_);
    EXPECT_EQ(ratingPattern->secondaryConfig_.scaleX_,
        ratingPattern->ratingModifier_->secondaryImageCanvas_->GetPaintConfig().scaleX_);
    EXPECT_EQ(ratingPattern->secondaryConfig_.scaleY_,
        ratingPattern->ratingModifier_->secondaryImageCanvas_->GetPaintConfig().scaleY_);
    EXPECT_EQ(ratingPattern->backgroundConfig_.scaleX_,
        ratingPattern->ratingModifier_->backgroundImageCanvas_->GetPaintConfig().scaleX_);
    EXPECT_EQ(ratingPattern->backgroundConfig_.scaleY_,
        ratingPattern->ratingModifier_->backgroundImageCanvas_->GetPaintConfig().scaleY_);
    EXPECT_EQ(ratingPattern->backgroundFocusConfig_.scaleX_,
        ratingPattern->ratingModifier_->backgroundImageFocusCanvas_->GetPaintConfig().scaleX_);
    EXPECT_EQ(ratingPattern->backgroundFocusConfig_.scaleY_,
        ratingPattern->ratingModifier_->backgroundImageFocusCanvas_->GetPaintConfig().scaleY_);
}

/**
 * @tc.name: RatingPatternTest017
 * @tc.desc: Test OnFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ratingTheme->cancelAnimation_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(ratingTheme));
    /**
     * @tc.steps: step1. create rating FrameNode and Pattern, and initialize rating modifier.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    ratingPattern->isNeedFocusStyle_ = true;
    ratingPattern->OnModifyDone();
    ratingPattern->InitEvent();
    /**
     * @tc.steps: step2. Create image canvas.
     */
    ratingPattern->foregroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->secondaryImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageFocusCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    /**
     * @tc.steps: step3. Create RatingPaintMethod, check ratingPattern->ratingModifier_.
     */
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    /**
     * @tc.steps: step4. Test OnFocusEvent && SetModifierFocus.
     * @tc.expected: Check the param value when focus.
     */
    ratingPattern->OnAttachToFrameNode();
    ratingPattern->OnFocusEvent();
    ratingPattern->AddIsFocusActiveUpdateEvent();
    ratingPattern->SetModifierFocus(true);
    ASSERT_NE(ratingPattern->pipelineContext_, nullptr);
    EXPECT_TRUE(ratingPattern->isfocus_);
    EXPECT_EQ(ratingPattern->state_, RatingModifier::RatingAnimationType::FOCUS);
    EXPECT_EQ(ratingPattern->ratingModifier_->boardColor_->Get().ToColor(), ratingTheme->GetFocusColor());
    EXPECT_TRUE(ratingPattern->ratingModifier_->isFocus_);
    EXPECT_TRUE(ratingPattern->ratingModifier_->needDraw_);
}

/**
 * @tc.name: RatingPatternTest018
 * @tc.desc: Test OnFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ratingTheme->cancelAnimation_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(ratingTheme));
    /**
     * @tc.steps: step1. create rating FrameNode and Pattern, and initialize rating modifier.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    ratingPattern->isNeedFocusStyle_ = true;
    ratingPattern->OnModifyDone();
    ratingPattern->InitEvent();
    /**
     * @tc.steps: step2. Create image canvas.
     */
    ratingPattern->foregroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->secondaryImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageFocusCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    /**
     * @tc.steps: step3. Create RatingPaintMethod, check ratingPattern->ratingModifier.
     */
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    /**
     * @tc.steps: step4. Test OnBlurEvent && SetModifierFocus.
     * @tc.expected: Check the param value when blur.
     */
    ratingPattern->OnAttachToFrameNode();
    ratingPattern->OnBlurEvent();
    ratingPattern->RemoveIsFocusActiveUpdateEvent();
    ratingPattern->SetModifierFocus(false);
    ASSERT_NE(ratingPattern->pipelineContext_, nullptr);
    EXPECT_FALSE(ratingPattern->isfocus_);
    EXPECT_EQ(ratingPattern->state_, RatingModifier::RatingAnimationType::NONE);
    EXPECT_EQ(ratingPattern->ratingModifier_->boardColor_->Get().ToColor(), Color::TRANSPARENT);
    EXPECT_FALSE(ratingPattern->ratingModifier_->isFocus_);
    EXPECT_TRUE(ratingPattern->ratingModifier_->needDraw_);
}

/**
 * @tc.name: RatingPatternTest019
 * @tc.desc: test RatingPattern::HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ratingTheme->cancelAnimation_ = 1;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(ratingTheme));
    /**
     * @tc.steps: step1. create rating FrameNode and Pattern, and initialize rating modifier.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetStars(DEFAULT_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    ratingPattern->isNeedFocusStyle_ = true;
    ratingPattern->OnModifyDone();
    ratingPattern->InitEvent();
    /**
     * @tc.steps: step2. Create image canvas.
     */
    ratingPattern->foregroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->secondaryImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageFocusCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    /**
     * @tc.steps: step3. Create RatingPaintMethod, check ratingPattern->ratingModifier.
     */
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    /**
     * @tc.steps: step4. Test HandleHoverEvent.
     * @tc.expected: Check the param value when focus && hover.
     */
    ratingPattern->isfocus_ = true;
    ratingPattern->HandleHoverEvent(true);
    EXPECT_EQ(ratingPattern->state_, RatingModifier::RatingAnimationType::FOCUS);
    ratingPattern->HandleHoverEvent(false);
    EXPECT_EQ(ratingPattern->state_, RatingModifier::RatingAnimationType::FOCUS);
    /**
     * @tc.steps: step5. Test HandleHoverEvent.
     * @tc.expected: Check the param value when blur && hover.
     */
    ratingPattern->isfocus_ = false;
    ratingPattern->HandleHoverEvent(true);
    EXPECT_EQ(ratingPattern->state_, RatingModifier::RatingAnimationType::HOVER);
    ratingPattern->HandleHoverEvent(false);
    EXPECT_EQ(ratingPattern->state_, RatingModifier::RatingAnimationType::NONE);
}

/**
 * @tc.name: RatingOnChangeEventTest002
 * @tc.desc: Test Rating onChange event
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, RatingOnChangeEventTest002, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<RatingEventHub>();
    ASSERT_NE(eventHub, nullptr);
    std::string unknownRatingScore;
    auto onChange = [&unknownRatingScore](const std::string& ratingScore) { unknownRatingScore = ratingScore; };
    rating.SetOnChange(frameNode, onChange);
    EXPECT_NE(eventHub->changeEvent_, nullptr);
}

/**
 * @tc.name: StyleTest001
 * @tc.desc: Test style
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, StyleTest001, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetBackgroundSrc(RATING_BACKGROUND_URL);
    rating.SetForegroundSrc(RATING_FOREGROUND_URL);
    rating.SetSecondarySrc(RATING_SECONDARY_URL);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutProperty, nullptr);
    // Test starStyle value.
    EXPECT_EQ(ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_BACKGROUND_URL);
    EXPECT_EQ(ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_FOREGROUND_URL);
    EXPECT_EQ(ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_SECONDARY_URL);
}

/**
 * @tc.name: MeasureTest001
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, MeasureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayoutWrapperNode and RatingLayoutAlgorithm.
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
    ratingPattern->SetRatingScore(RATING_SCORE);
    auto ratingLayoutProperty = AceType::MakeRefPtr<RatingLayoutProperty>();
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ASSERT_NE(ratingLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, ratingLayoutProperty);
    auto ratingLayoutAlgorithm = AceType::MakeRefPtr<RatingLayoutAlgorithm>(nullptr, nullptr, nullptr, nullptr);
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. call MeasureContent function.
     * @tc.expected: ret is not equal to TEST_SIZE_200.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    auto ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret->Width(), TEST_SIZE_200.Width());
    EXPECT_NE(ret->Height(), TEST_SIZE_200.Height());

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret->Width(), TEST_SIZE_200.Width());
    EXPECT_EQ(ret->Height(), TEST_SIZE_200.Height());
}

/**
 * @tc.name: MeasureTest002
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, MeasureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayoutWrapperNode and RatingLayoutAlgorithm.
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
    ratingPattern->SetRatingScore(RATING_SCORE);
    auto ratingLayoutProperty = AceType::MakeRefPtr<RatingLayoutProperty>();
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ASSERT_NE(ratingLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, ratingLayoutProperty);
    auto ratingLayoutAlgorithm = AceType::MakeRefPtr<RatingLayoutAlgorithm>(nullptr, nullptr, nullptr, nullptr);
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. call MeasureContent function.
     * @tc.expected: ret is not equal to TEST_SIZE_200.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    auto ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_200);
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);
}

/**
 * @tc.name: MeasureTest003
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, MeasureTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayoutWrapperNode and RatingLayoutAlgorithm.
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
    ratingPattern->SetRatingScore(RATING_SCORE);
    auto ratingLayoutProperty = AceType::MakeRefPtr<RatingLayoutProperty>();
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ASSERT_NE(ratingLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, ratingLayoutProperty);
    auto ratingLayoutAlgorithm = AceType::MakeRefPtr<RatingLayoutAlgorithm>(nullptr, nullptr, nullptr, nullptr);
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. call MeasureContent function.
     * @tc.expected: ret is not equal to TEST_SIZE_200.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_200);
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_200);
    ret = ratingLayoutAlgorithm->LayoutPolicyIsFixAtIdelSize(contentConstraint, layoutPolicyProperty, DEFAULT_STAR_NUM,
        TEST_SIZE_200.Width(), TEST_SIZE_200.Height());
    EXPECT_EQ(ret, TEST_SIZE_200);
}

/**
 * @tc.name: MeasureTest004
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, MeasureTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayoutWrapperNode and RatingLayoutAlgorithm.
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
    ratingPattern->SetRatingScore(RATING_SCORE);
    auto ratingLayoutProperty = AceType::MakeRefPtr<RatingLayoutProperty>();
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ASSERT_NE(ratingLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, ratingLayoutProperty);
    auto ratingLayoutAlgorithm = AceType::MakeRefPtr<RatingLayoutAlgorithm>(nullptr, nullptr, nullptr, nullptr);
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. call MeasureContent function.
     * @tc.expected: ret is not equal to TEST_SIZE_200.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    ratingTheme->ratingMiniHeight_ = Dimension(TEST_WIDTH_50);
    ratingTheme->ratingHeight_ = Dimension(TEST_WIDTH_50);
    auto ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_10);
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_0);
}

/**
 * @tc.name: MeasureTest005
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTwoTestNg, MeasureTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayoutWrapperNode and RatingLayoutAlgorithm.
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
    ratingPattern->SetRatingScore(RATING_SCORE);
    auto ratingLayoutProperty = AceType::MakeRefPtr<RatingLayoutProperty>();
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ASSERT_NE(ratingLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, ratingLayoutProperty);
    auto ratingLayoutAlgorithm = AceType::MakeRefPtr<RatingLayoutAlgorithm>(nullptr, nullptr, nullptr, nullptr);
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. call MeasureContent function.
     * @tc.expected: ret is not equal to TEST_SIZE_200.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    ratingTheme->ratingMiniHeight_ = Dimension(TEST_WIDTH_50);
    ratingTheme->ratingHeight_ = Dimension(TEST_WIDTH_50);
    LayoutPolicyProperty layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    auto ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_10);
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_200);
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);
}
} // namespace OHOS::Ace::NG