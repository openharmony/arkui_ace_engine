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
#include <stdint.h>
#include <string>

#include "gtest/gtest.h"
#include "third_party/libpng/png.h"

#include "core/components/rating/rating_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_layout_property.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const bool RATING_INDICATOR = true;
const bool DEFAULT_RATING_INDICATOR = false;
const int32_t DEFAULT_STAR_NUM = 5;
const int32_t RATING_STAR_NUM = 10;
constexpr double RATING_SCORE = 3.0;
const std::string RATING_SCORE_CHANGE = "3.0";
constexpr double RATING_SCORE_1 = 6.0;
constexpr int32_t RATING_STAR_NUM_1 = -1;
const std::string RATING_BACKGROUND_URL = "common/img1.png";
const std::string RATING_FOREGROUND_URL = "common/img2.png";
const std::string RATING_SECONDARY_URL = "common/img3.png";
constexpr double DEFAULT_RATING_SCORE = 0.0;
constexpr double DEFAULT_STEP_SIZE = 0.5;
constexpr double RATING_STEP_SIZE = 0.7;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
} // namespace

class RatingPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: RatingLayoutPropertyTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingLayoutPropertyTest001, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
}

/**
 * @tc.name: RatingLayoutPropertyTest002
 * @tc.desc: Test rating indicator, starStyle and starNum default value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingLayoutPropertyTest002, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_FALSE(ratingLayoutProperty == nullptr);

    // Test indicator default value.
    EXPECT_EQ(ratingLayoutProperty->GetIndicator().value_or(false), DEFAULT_RATING_INDICATOR);
    // Test starNum default value.
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(5), DEFAULT_STAR_NUM);
    // Test starStyle default value set in theme.
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    CHECK_NULL_VOID(iconTheme);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    EXPECT_EQ(ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        iconTheme->GetIconPath(ratingTheme->GetForegroundResourceId()));
    EXPECT_EQ(ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        iconTheme->GetIconPath(ratingTheme->GetSecondaryResourceId()));
    EXPECT_EQ(ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        iconTheme->GetIconPath(ratingTheme->GetBackgroundResourceId()));
}

/**
 * @tc.name: RatingLayoutPropertyTest003
 * @tc.desc: Test setting indicator, starStyle and starNum.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingLayoutPropertyTest003, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR);
    rating.SetStars(RATING_STAR_NUM);
    rating.SetBackgroundSrc(RATING_BACKGROUND_URL);
    rating.SetForegroundSrc(RATING_FOREGROUND_URL);
    rating.SetSecondarySrc(RATING_SECONDARY_URL);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_FALSE(ratingLayoutProperty == nullptr);

    // Test indicator value.
    EXPECT_EQ(ratingLayoutProperty->GetIndicator().value_or(false), RATING_INDICATOR);
    // Test starNum value.
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(5), RATING_STAR_NUM);
    // Test starStyle value.
    EXPECT_EQ(ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_FOREGROUND_URL);
    EXPECT_EQ(ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_SECONDARY_URL);
    EXPECT_EQ(ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_BACKGROUND_URL);
}

/**
 * @tc.name: RatingRenderPropertyTest004
 * @tc.desc: Test rating ratingScore and stepSize default value.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingRenderPropertyTest004, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    EXPECT_FALSE(ratingRenderProperty == nullptr);

    // Test ratingScore and stepSize default value.
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(0.0), DEFAULT_RATING_SCORE);
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(0.5), DEFAULT_STEP_SIZE);
}

/**
 * @tc.name: RatingRenderPropertyTest005
 * @tc.desc: Test setting rating ratingScore(drawScore) and stepSize.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingRenderPropertyTest005, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(RATING_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    EXPECT_FALSE(ratingRenderProperty == nullptr);

    // Test ratingScore and stepSize value.
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(0.0), RATING_STEP_SIZE);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(0.0),
        Round(RATING_SCORE / RATING_STEP_SIZE) * RATING_STEP_SIZE);
}

/**
 * @tc.name: RatingLConstrainsPropertyTest006
 * @tc.desc: Test setting out-of-bounds ratingScore and starNum values.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingLConstrainsPropertyTest006, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE_1);
    rating.SetStars(RATING_STAR_NUM_1);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    EXPECT_FALSE(ratingRenderProperty == nullptr);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_FALSE(ratingLayoutProperty == nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);

    // Test StarNums and ratingScore constrained value when they are out-of-bounds.
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(ratingTheme->GetStarNum()), ratingTheme->GetStarNum());
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(ratingTheme->GetRatingScore()),
        ratingLayoutProperty->GetStars().value_or(ratingTheme->GetStarNum()));
}

/**
 * @tc.name: RatingEventTest007
 * @tc.desc: Test Rating onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingEventTest007, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE);
    rating.SetStars(RATING_STAR_NUM_1);
   
    std::string unknownRatingScore;
    auto onChange = [&unknownRatingScore](const std::string& raingScore) { unknownRatingScore = raingScore; };
    rating.SetOnChange(onChange);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);

    auto ratingEventHub = frameNode->GetEventHub<RatingEventHub>();
    ratingEventHub->FireChangeEvent(RATING_SCORE_CHANGE);
    EXPECT_EQ(unknownRatingScore, RATING_SCORE_CHANGE);
}

/**
 * @tc.name: RatingMeasureTest008
 * @tc.desc: Test rating measure and layout function
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingMeasureTest008, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(RATING_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);

    // Create LayoutWrapper and set ratingLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    EXPECT_FALSE(ratingPattern == nullptr);
    auto ratingLayoutAlgorithm = ratingPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(ratingLayoutAlgorithm == nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(ratingLayoutAlgorithm));

    // Rating without setting height and width.
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    // Calculate the size and offset.
    ratingLayoutAlgorithm->Measure(&layoutWrapper);
    ratingLayoutAlgorithm->Layout(&layoutWrapper);
    // Test the default size set in theme and the offset.
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(),
        SizeF(ratingTheme->GetRatingHeight().ConvertToPx(), ratingTheme->GetRatingWidth().ConvertToPx()));
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF(0.0, 0.0));

    /**
    //     corresponding ets code:
    //         Rating().width(300).height(300)
    */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    ratingLayoutAlgorithm->Measure(&layoutWrapper);
    // Test the size set by codes.
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_SIZE));
}

} // namespace OHOS::Ace::NG