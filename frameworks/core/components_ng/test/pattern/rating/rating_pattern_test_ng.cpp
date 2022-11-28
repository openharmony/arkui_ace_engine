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

#include "base/memory/ace_type.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/image/image_source_info.h"

#define private public
#define protected public
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
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const bool RATING_INDICATOR = true;
const bool DEFAULT_RATING_INDICATOR = false;
const int32_t DEFAULT_STAR_NUM_0 = 0;
const int32_t DEFAULT_STAR_NUM = 5;
const int32_t RATING_STAR_NUM = 10;
constexpr double RATING_SCORE = 3.0;
constexpr double RATING_LAST_SCORE = 5.0;
const std::string RATING_SCORE_STRING = "3";
constexpr double RATING_SCORE_2 = -2;
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
const std::string RESOURCE_URL = "resource:///ohos_test_image.svg";
const std::string IMAGE_SOURCE_INFO_STRING = "empty source";
const int32_t RATING_FOREGROUND_FLAG = 0b001;
const int32_t RATING_SECONDARY_FLAG = 0b010;
const int32_t RATING_BACKGROUND_FLAG = 0b100;
const int32_t INVALID_IMAGE_FLAG = 0b100;
const std::string RATING_IMAGE_LOAD_FAILED = "ImageDataFailed";
constexpr int32_t RATING_IMAGE_SUCCESS_CODE = 0b111;
const InternalResource::ResourceId FOREGROUND_IMAGE_RESOURCE_ID = InternalResource::ResourceId::RATE_STAR_BIG_ON_SVG;
const InternalResource::ResourceId SECONDARY_IMAGE_RESOURCE_ID = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
const InternalResource::ResourceId BACKGROUND_IMAGE_RESOURCE_ID = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
const std::string RATING_FOREGROUND_IMAGE_KEY = "foregroundImageSourceInfo";
const std::string RATING_SECONDARY_IMAGE_KEY = "secondaryImageSourceInfo";
const std::string RATING_BACKGROUND_IMAGE_KEY = "backgroundImageSourceInfo";
} // namespace

class RatingPropertyTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void RatingPropertyTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void RatingPropertyTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

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
    /**
     * @tc.steps: step1. Create Rating without parameters.
     */
    RatingModelNG rating;
    rating.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_NE(ratingLayoutProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    EXPECT_NE(ratingPattern, nullptr);

    /**
     * @tc.steps: step2. Get indicator and starNum values.
     * @tc.expected: indicator and starNum used the values defined in theme.
     */
    EXPECT_EQ(ratingLayoutProperty->GetIndicator().value_or(false), DEFAULT_RATING_INDICATOR);
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(5), DEFAULT_STAR_NUM);

    /**
     * @tc.steps: step3. Invoke UpdateInternalResource.
     * @tc.expected: GetIconPath and update value of foreground, background and secondary images.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IconTheme>()));
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    EXPECT_NE(ratingTheme, nullptr);
    ImageSourceInfo imageSourceInfo = ImageSourceInfo("");

    imageSourceInfo.SetResourceId(ratingTheme->GetForegroundResourceId());
    ratingPattern->UpdateInternalResource(imageSourceInfo, RATING_FOREGROUND_FLAG);
    EXPECT_EQ(
        ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(), RESOURCE_URL);

    imageSourceInfo.SetResourceId(ratingTheme->GetSecondaryResourceId());
    ratingPattern->UpdateInternalResource(imageSourceInfo, RATING_SECONDARY_FLAG);
    EXPECT_EQ(ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(), RESOURCE_URL);

    imageSourceInfo.SetResourceId(ratingTheme->GetBackgroundResourceId());
    ratingPattern->UpdateInternalResource(imageSourceInfo, RATING_BACKGROUND_FLAG);
    EXPECT_EQ(
        ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(), RESOURCE_URL);
    ratingPattern->UpdateInternalResource(imageSourceInfo, INVALID_IMAGE_FLAG);
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
    EXPECT_NE(ratingLayoutProperty, nullptr);

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
    EXPECT_NE(ratingRenderProperty, nullptr);

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
    EXPECT_NE(ratingRenderProperty, nullptr);

    // Test ratingScore and stepSize value.
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(0.0), RATING_STEP_SIZE);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(0.0),
        Round(RATING_SCORE / RATING_STEP_SIZE) * RATING_STEP_SIZE);
}

/**
 * @tc.name: RatingConstrainsPropertyTest006
 * @tc.desc: Test setting out-of-bounds ratingScore and starNum values.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingConstrainsPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating with its the ratingScore and starNums are both negative.
     * @tc.expected: Constrain them with the values defined in theme.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RatingTheme>()));
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE_2);
    rating.SetStars(RATING_STAR_NUM_1);
    rating.SetStepSize(DEFAULT_STEP_SIZE);

    /**
     * @tc.steps: step2. Set Rating OnChange Event.
     * @tc.expected: Fire onChange Event when ratingScore has been changed.
     */
    std::string unknownRatingScore;
    auto onChange = [&unknownRatingScore](const std::string& ratingScore) { unknownRatingScore = ratingScore; };
    rating.SetOnChange(onChange);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    EXPECT_NE(ratingRenderProperty, nullptr);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_NE(ratingLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Update ratingScore and invoke ConstrainsRatingScore function.
     * @tc.expected: onChange Event will be fired, and unknownRatingScore will be assigned the correct value when it is
     * initialized for the first time.
     */
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(DEFAULT_STAR_NUM), DEFAULT_STAR_NUM_0);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(DEFAULT_RATING_SCORE), DEFAULT_RATING_SCORE);
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ratingRenderProperty->UpdateRatingScore(RATING_SCORE);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    EXPECT_NE(ratingPattern, nullptr);

    /**
     * @tc.steps: step4. Invoke ConstrainsRatingScore when the score has not changed compared with the last time.
     * @tc.expected: onChange Event will not be fired.
     */
    ratingPattern->lastRatingScore_ = RATING_SCORE;
    ratingPattern->ConstrainsRatingScore();
    EXPECT_TRUE(unknownRatingScore.empty());

    /**
     * @tc.steps: step5. Invoke ConstrainsRatingScore when the score has changed compared with the last time and it is
     * not the first time initialized.
     * @tc.expected: onChange Event will be fired.
     */
    ratingPattern->lastRatingScore_ = RATING_LAST_SCORE;
    ratingPattern->ConstrainsRatingScore();
    EXPECT_EQ(unknownRatingScore, RATING_SCORE_STRING);
}

/**
 * @tc.name: RatingPatternGetImageSourceFromThemeTest007
 * @tc.desc: Invoke GetImageSourceInfoFromTheme and ready, success and fail callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingPatternGetImageSourceFromThemeTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    EXPECT_NE(ratingPattern, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RatingTheme>()));

    const ImageSourceInfo foregroundImage = ratingPattern->GetImageSourceInfoFromTheme(RATING_FOREGROUND_FLAG);
    const ImageSourceInfo secondaryImage = ratingPattern->GetImageSourceInfoFromTheme(RATING_SECONDARY_FLAG);
    const ImageSourceInfo backgroundImage = ratingPattern->GetImageSourceInfoFromTheme(RATING_BACKGROUND_FLAG);

    EXPECT_EQ(foregroundImage.GetResourceId(), FOREGROUND_IMAGE_RESOURCE_ID);
    EXPECT_EQ(secondaryImage.GetResourceId(), SECONDARY_IMAGE_RESOURCE_ID);
    EXPECT_EQ(backgroundImage.GetResourceId(), BACKGROUND_IMAGE_RESOURCE_ID);
    /**
     * @tc.steps: step2. Invoke CheckImageInfoHasChangedOrNot.
     */
    ratingPattern->CheckImageInfoHasChangedOrNot(
        RATING_FOREGROUND_FLAG, ImageSourceInfo(RATING_FOREGROUND_URL), RATING_IMAGE_LOAD_FAILED);
    ratingPattern->CheckImageInfoHasChangedOrNot(
        RATING_SECONDARY_FLAG, ImageSourceInfo(RATING_SECONDARY_URL), RATING_IMAGE_LOAD_FAILED);
    ratingPattern->CheckImageInfoHasChangedOrNot(
        RATING_BACKGROUND_FLAG, ImageSourceInfo(RATING_BACKGROUND_URL), RATING_IMAGE_LOAD_FAILED);

    /**
     * @tc.steps: step3. Invoke OnImageLoadSuccess when the foreground, secondary and background image has been loaded
     * successfully.
     * @tc.expected: imageSuccessStateCode_ will be set as the success code only when 3 images have been loaded.
     */
    ratingPattern->OnImageDataReady(RATING_FOREGROUND_FLAG);
    ratingPattern->OnImageDataReady(RATING_SECONDARY_FLAG);
    ratingPattern->OnImageDataReady(RATING_BACKGROUND_FLAG);
    EXPECT_EQ(ratingPattern->imageReadyStateCode_, RATING_IMAGE_SUCCESS_CODE);

    /**
     * @tc.steps: step4. Invoke OnImageLoadSuccess when the foreground, secondary and background image has been loaded
     * successfully.
     * @tc.expected: imageSuccessStateCode_ will be set as the success code only when 3 images have been loaded.
     */
    ratingPattern->OnImageLoadSuccess(RATING_FOREGROUND_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_SECONDARY_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_BACKGROUND_FLAG);
    EXPECT_EQ(ratingPattern->imageSuccessStateCode_, RATING_IMAGE_SUCCESS_CODE);
}

/**
 * @tc.name: RatingPatternToJsonValueTest008
 * @tc.desc: Invoke ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingPatternToJsonValueTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetBackgroundSrc(RATING_BACKGROUND_URL);
    rating.SetForegroundSrc(RATING_FOREGROUND_URL);
    rating.SetSecondarySrc(RATING_SECONDARY_URL);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    EXPECT_NE(ratingPattern, nullptr);

    /**
     * @tc.steps: step2. Invoke ToJsonValue when the foreground, secondary and background image are used in theme.
     * @tc.expected: ImageSourceInfo src is null.
     */
    ratingPattern->isForegroundImageInfoFromTheme_ = true;
    ratingPattern->isSecondaryImageInfoFromTheme_ = true;
    ratingPattern->isBackgroundImageInfoFromTheme_ = true;
    auto json = JsonUtil::Create(true);
    ratingPattern->ToJsonValue(json);

    EXPECT_EQ(json->GetValue(RATING_FOREGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json->GetValue(RATING_SECONDARY_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json->GetValue(RATING_BACKGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);

    /**
     * @tc.steps: step3. Invoke ToJsonValue when the foreground, secondary and background image are not used in theme.
     * @tc.expected: ImageSourceInfo src is users defined when create component.
     */
    ratingPattern->isForegroundImageInfoFromTheme_ = false;
    ratingPattern->isSecondaryImageInfoFromTheme_ = false;
    ratingPattern->isBackgroundImageInfoFromTheme_ = false;
    ratingPattern->ToJsonValue(json);

    EXPECT_EQ(json->GetValue(RATING_FOREGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json->GetValue(RATING_SECONDARY_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json->GetValue(RATING_BACKGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
}

/**
 * @tc.name: RatingMeasureTest009
 * @tc.desc: Test rating measure and layout function
 * @tc.type: FUNC
 */
HWTEST_F(RatingPropertyTestNg, RatingMeasureTest009, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(RATING_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);

    // Create LayoutWrapper and set ratingLayoutAlgorithm.
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    EXPECT_NE(ratingPattern, nullptr);
    auto ratingLayoutAlgorithm = ratingPattern->CreateLayoutAlgorithm();
    EXPECT_NE(ratingLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(ratingLayoutAlgorithm));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RatingTheme>()));
    // Rating without setting height and width.
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    // Calculate the size and offset.
    ratingLayoutAlgorithm->Measure(&layoutWrapper);
    ratingLayoutAlgorithm->Layout(&layoutWrapper);
    // Test the default size set in theme and the offset.
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    EXPECT_NE(ratingTheme, nullptr);
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