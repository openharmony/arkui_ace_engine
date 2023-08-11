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
#include <cstdint>
#include <string>
#include <cmath>

#include "gtest/gtest.h"
#include "third_party/libpng/png.h"
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
#include "core/components_ng/test/mock/render/mock_canvas_image.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const bool RATING_INDICATOR = true;
const bool DEFAULT_RATING_INDICATOR = false;
const int32_t DEFAULT_STAR_NUM = 5;
const int32_t RATING_STAR_NUM = 10;
constexpr double RATING_SCORE = 3.0;
constexpr double RATING_LAST_SCORE = 5.0;
const std::string RATING_SCORE_STRING = "3";
constexpr double RATING_SCORE_2 = -2;
constexpr double RATING_SCORE_3 = 3.5;
constexpr double RATING_SCORE_4 = 3.0;
constexpr int32_t RATING_STAR_NUM_1 = -1;
const std::string RATING_BACKGROUND_URL = "common/img1.png";
const std::string RATING_FOREGROUND_URL = "common/img2.png";
const std::string RATING_SECONDARY_URL = "common/img3.png";
const std::string RATING_SVG_URL = "common/img4.svg";
constexpr double DEFAULT_RATING_SCORE = 0.0;
constexpr double DEFAULT_STEP_SIZE = 0.5;
constexpr double RATING_STEP_SIZE = 0.7;
constexpr double RATING_STEP_SIZE_2 = DEFAULT_STAR_NUM + DEFAULT_STAR_NUM;
constexpr int32_t RATING_TOUCH_STAR = 3;
constexpr int32_t RATING_DRAW_BACKGROUND_TIMES = 1;
constexpr int32_t RATING_SAVE_TIMES = 3;
constexpr int32_t RATING_CLIP_ROUND_RECT_TIMES = 1;
constexpr int32_t RATING_CLIP_CLIP_RECT_TIMES = 2;
constexpr int32_t RATING_RESTORE_TIMES = 3;
constexpr int32_t RATING_INVALID_TOUCH_STAR = -1;
constexpr int32_t RATING_INVALID_TOUCH_STAR_2 = 11;
constexpr int32_t RATING_RESTORE_TIMES_1 = 1;
constexpr int32_t RATING_SAVE_TIMES_1 = 1;
constexpr int32_t RATING_CLIP_CLIP_RECT_TIMES_1 = 1;
const float FRAME_WIDTH = 400.0f;
const float FRAME_HEIGHT = 400.0f;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const float INVALID_CONTAINER_WIDTH = -300.0f;
const float INVALID_CONTAINER_HEIGHT = -300.0f;
const SizeF INVALID_CONTAINER_SIZE(INVALID_CONTAINER_WIDTH, INVALID_CONTAINER_HEIGHT);
const std::string RESOURCE_URL = "resource:///ohos_test_image.svg";
const std::string IMAGE_SOURCE_INFO_STRING = "empty source";
const int32_t RATING_FOREGROUND_FLAG = 0b001;
const int32_t RATING_SECONDARY_FLAG = 0b010;
const int32_t RATING_BACKGROUND_FLAG = 0b100;
const int32_t INVALID_IMAGE_FLAG = 0b111;
const std::string RATING_IMAGE_LOAD_FAILED = "ImageDataFailed";
const std::string RATING_IMAGE_LOAD_SUCCESS = "ImageDataSuccess";
constexpr int32_t RATING_IMAGE_SUCCESS_CODE = 0b111;
const InternalResource::ResourceId FOREGROUND_IMAGE_RESOURCE_ID = InternalResource::ResourceId::RATE_STAR_BIG_ON_SVG;
const InternalResource::ResourceId SECONDARY_IMAGE_RESOURCE_ID = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
const InternalResource::ResourceId BACKGROUND_IMAGE_RESOURCE_ID = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
const std::string RATING_FOREGROUND_IMAGE_KEY = "foregroundImageSourceInfo";
const std::string RATING_SECONDARY_IMAGE_KEY = "secondaryImageSourceInfo";
const std::string RATING_BACKGROUND_IMAGE_KEY = "backgroundImageSourceInfo";
} // namespace

class RatingPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RatingPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingCreateTest001, TestSize.Level1)
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
HWTEST_F(RatingPatternTestNg, RatingLayoutPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating without parameters.
     */
    RatingModelNG rating;
    rating.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);

    /**
     * @tc.steps: step2. Get indicator and starNum values.
     * @tc.expected: indicator and starNum used the values defined in theme.
     */
    EXPECT_EQ(ratingLayoutProperty->GetIndicator().value_or(false), DEFAULT_RATING_INDICATOR);
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(DEFAULT_STAR_NUM), DEFAULT_STAR_NUM);

    /**
     * @tc.steps: step3. Invoke UpdateInternalResource.
     * @tc.expected: GetIconPath and update value of foreground, background and secondary images.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IconTheme>()));
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
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
HWTEST_F(RatingPatternTestNg, RatingLayoutPropertyTest003, TestSize.Level1)
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
    ASSERT_NE(ratingLayoutProperty, nullptr);
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
HWTEST_F(RatingPatternTestNg, RatingRenderPropertyTest004, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);

    // Test ratingScore and stepSize default value.
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(0.0), DEFAULT_RATING_SCORE);
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(0.5), DEFAULT_STEP_SIZE);
}

/**
 * @tc.name: RatingRenderPropertyTest005
 * @tc.desc: Test setting rating ratingScore(drawScore) and stepSize.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingRenderPropertyTest005, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(RATING_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);

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
HWTEST_F(RatingPatternTestNg, RatingConstrainsPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating with its the ratingScore and starNums are both negative.
     * @tc.expected: Constrain them with the values defined in theme.
     */
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ratingTheme->starNum_ = DEFAULT_STAR_NUM;
    ratingTheme->ratingScore_ = DEFAULT_RATING_SCORE;
    ratingTheme->stepSize_ = DEFAULT_STEP_SIZE;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(ratingTheme));
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE_2);
    rating.SetStars(RATING_STAR_NUM_1);
    rating.SetStepSize(RATING_STEP_SIZE_2);

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
    ASSERT_NE(ratingRenderProperty, nullptr);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Update ratingScore and invoke ConstrainsRatingScore function.
     * @tc.expected: onChange Event will be fired, and unknownRatingScore will be assigned the correct value when it is
     * initialized for the first time.
     */
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(DEFAULT_STAR_NUM), DEFAULT_STAR_NUM);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(DEFAULT_RATING_SCORE), DEFAULT_RATING_SCORE);
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(DEFAULT_STEP_SIZE), DEFAULT_STEP_SIZE);
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ratingRenderProperty->UpdateRatingScore(RATING_SCORE);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);

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
HWTEST_F(RatingPatternTestNg, RatingPatternGetImageSourceFromThemeTest007, TestSize.Level1)
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
    ASSERT_NE(ratingPattern, nullptr);

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
    std::string lifeCycleTags[] = { RATING_IMAGE_LOAD_FAILED, RATING_IMAGE_LOAD_SUCCESS };
    for (std::string tag : lifeCycleTags) {
        ratingPattern->CheckImageInfoHasChangedOrNot(
            RATING_FOREGROUND_FLAG, ImageSourceInfo(RATING_FOREGROUND_URL), tag);
        ratingPattern->CheckImageInfoHasChangedOrNot(RATING_SECONDARY_FLAG, ImageSourceInfo(RATING_SECONDARY_URL), tag);
        ratingPattern->CheckImageInfoHasChangedOrNot(
            RATING_BACKGROUND_FLAG, ImageSourceInfo(RATING_BACKGROUND_URL), tag);
    }

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
HWTEST_F(RatingPatternTestNg, RatingPatternToJsonValueTest008, TestSize.Level1)
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
    ASSERT_NE(ratingPattern, nullptr);

    /**
     * @tc.steps: step3. Invoke ToJsonValue when the foreground, secondary and background image are not used in theme.
     * @tc.expected: ImageSourceInfo src is users defined when create component.
     */
    EXPECT_FALSE(ratingPattern->isForegroundImageInfoFromTheme_);
    EXPECT_FALSE(ratingPattern->isSecondaryImageInfoFromTheme_);
    EXPECT_FALSE(ratingPattern->isSecondaryImageInfoFromTheme_);
    auto json = JsonUtil::Create(true);
    ratingPattern->ToJsonValue(json);

    EXPECT_EQ(json->GetValue(RATING_FOREGROUND_IMAGE_KEY)->GetString(), RATING_FOREGROUND_URL);
    EXPECT_EQ(json->GetValue(RATING_SECONDARY_IMAGE_KEY)->GetString(), RATING_SECONDARY_URL);
    EXPECT_EQ(json->GetValue(RATING_BACKGROUND_IMAGE_KEY)->GetString(), RATING_BACKGROUND_URL);

    /**
     * @tc.steps: step2. Invoke ToJsonValue when the foreground, secondary and background image are used in theme.
     * @tc.expected: ImageSourceInfo src is null.
     */
    ratingPattern->isForegroundImageInfoFromTheme_ = true;
    ratingPattern->isSecondaryImageInfoFromTheme_ = true;
    ratingPattern->isBackgroundImageInfoFromTheme_ = true;
    auto json2 = JsonUtil::Create(true);
    ratingPattern->ToJsonValue(json2);

    EXPECT_EQ(json2->GetValue(RATING_FOREGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json2->GetValue(RATING_SECONDARY_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json2->GetValue(RATING_BACKGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
}

/**
 * @tc.name: RatingMeasureTest009
 * @tc.desc: Test rating measure and layout function and invoke OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingMeasureTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(RATING_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set ratingLayoutAlgorithm.
     */
    const RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    auto ratingLayoutAlgorithm = ratingPattern->CreateLayoutAlgorithm();
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(ratingLayoutAlgorithm));
    frameNode->SetGeometryNode(geometryNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RatingTheme>()));

    /**
     * @tc.steps: step3. Invoke MeasureContent when the size has not been defined.
     * @tc.expected: Use the size defined in ratingTheme.
     */
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper),
        SizeF(ratingTheme->GetRatingHeight().ConvertToPx(), ratingTheme->GetRatingWidth().ConvertToPx()));

    /**
     * @tc.steps: step4. Invoke MeasureContent when the size has been defined.
     * @tc.expected: Use the size defined before.
     */
    LayoutConstraintF layoutConstraintSize;
    /**
    //     corresponding ets code:
    //         Rating().width(300).height(300)
    */
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper), CONTAINER_SIZE);

    /**
     * @tc.steps: step5. Invoke MeasureContent when the size is negative.
     * @tc.expected: Use the size defined in theme.
     */
    layoutConstraintSize.selfIdealSize.SetSize(INVALID_CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper),
        SizeF(ratingTheme->GetRatingHeight().ConvertToPx(), ratingTheme->GetRatingWidth().ConvertToPx()));

    /**
     * @tc.steps: step6. Invoke Layout when contentSize is valid.
     */
    geometryNode->SetContentSize(CONTAINER_SIZE);
    ratingLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameOffset(), OffsetF(0.0, 0.0));

    /**
     * @tc.steps: step7. Invoke OnDirtyLayoutWrapperSwap when the skipMeasure and skipMeasureContent values are
     * different.
     * @tc.expected: OnDirtyLayoutWrapperSwap return the false.
     */
    DirtySwapConfig config;
    auto layoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    layoutWrapper2->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(ratingLayoutAlgorithm));
    bool skipMeasureChanges[2] = { true, false };
    bool skipMeasureContentChanges[2] = { true, false };
    for (bool skipMeasure : skipMeasureChanges) {
        for (bool skipMeasureContent : skipMeasureContentChanges) {
            config.skipMeasure = skipMeasure;
            layoutWrapper2->skipMeasureContent_ = skipMeasureContent;
            EXPECT_FALSE(ratingPattern->OnDirtyLayoutWrapperSwap(layoutWrapper2, config));
        }
    }

    /**
     * @tc.steps: step8. Invoke OnDirtyLayoutWrapperSwap when the canvas images are nullptr or not.
     * @tc.expected: OnDirtyLayoutWrapperSwap return the true only when the canvas images all have been initialized.
     */
    auto canvasImage = AceType::MakeRefPtr<MockCanvasImage>();
    const RefPtr<CanvasImage> canvasImages[2] = { nullptr, canvasImage };
    for (const auto& foregroundCanvasImage : canvasImages) {
        for (const auto& secondaryCanvasImage : canvasImages) {
            for (const auto& backgroundCanvasImage : canvasImages) {
                ratingPattern->foregroundImageCanvas_ = foregroundCanvasImage;
                ratingPattern->secondaryImageCanvas_ = secondaryCanvasImage;
                ratingPattern->backgroundImageCanvas_ = backgroundCanvasImage;
                if (ratingPattern->foregroundImageCanvas_ && ratingPattern->secondaryImageCanvas_ &&
                    ratingPattern->backgroundImageCanvas_) {
                    EXPECT_TRUE(ratingPattern->OnDirtyLayoutWrapperSwap(layoutWrapper2, config));
                } else {
                    EXPECT_FALSE(ratingPattern->OnDirtyLayoutWrapperSwap(layoutWrapper2, config));
                }
            }
        }
    }
}

/**
 * @tc.name: RatingLayoutPropertyTest010
 * @tc.desc: Test when starStyle is undefined, flag is set by true, and star sourceInfo is from Theme.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingLayoutPropertyTest010, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetBackgroundSrc("", true);
    rating.SetForegroundSrc("", true);
    rating.SetSecondarySrc("", true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutProperty, nullptr);
    EXPECT_EQ(ratingLayoutProperty->propertyChangeFlag_ & PROPERTY_UPDATE_MEASURE, PROPERTY_UPDATE_MEASURE);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    EXPECT_TRUE(ratingPattern->foregroundConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->secondaryConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->backgroundConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->isBackgroundImageInfoFromTheme_);
    EXPECT_TRUE(ratingPattern->isSecondaryImageInfoFromTheme_);
    EXPECT_TRUE(ratingPattern->isForegroundImageInfoFromTheme_);
}

/**
 * @tc.name: RatingPatternTest011
 * @tc.desc: Test when starStyle is 3 different image formats, modifier will also update CanvasImage.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingPatternTest011, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<IconTheme>()));
    /**
     * @tc.steps: step1. create rating FrameNode and pattern loads ImageLoadingContext.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetBackgroundSrc(RATING_BACKGROUND_URL, false);
    rating.SetForegroundSrc("", true);
    rating.SetSecondarySrc(RATING_SVG_URL, false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutProperty, nullptr);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    ImageSourceInfo foreInfo;
    foreInfo.SetResourceId(FOREGROUND_IMAGE_RESOURCE_ID);
    ratingLayoutProperty->UpdateForegroundImageSourceInfo(foreInfo);
    /**
     * @tc.steps: step2. 3 ImageLoadContexts carry out successfully.
     */
    ratingPattern->OnModifyDone();
    ASSERT_NE(ratingPattern->foregroundImageLoadingCtx_, nullptr);
    ASSERT_NE(ratingPattern->secondaryImageLoadingCtx_, nullptr);
    ASSERT_NE(ratingPattern->backgroundImageLoadingCtx_, nullptr);
    EXPECT_TRUE(ratingPattern->secondaryConfig_.isSvg_);
    EXPECT_FALSE(ratingPattern->backgroundConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->foregroundConfig_.isSvg_);
    ratingPattern->foregroundImageLoadingCtx_->SuccessCallback(nullptr);
    ratingPattern->secondaryImageLoadingCtx_->SuccessCallback(nullptr);
    ratingPattern->backgroundImageLoadingCtx_->SuccessCallback(nullptr);
    /**
     * @tc.steps: step3. 3 ImageLoadContexts callback successfuly, and imageSuccessStateCode_ ==
     * RATING_IMAGE_SUCCESS_CODE.
     * @tc.expected: ratingModifier will update CanvasImage the first time.
     */
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->foregroundImageCanvas_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->secondaryImageCanvas_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->backgroundImageCanvas_, nullptr);
    EXPECT_EQ(ratingPattern->ratingModifier_->foregroundUri_, RESOURCE_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->secondaryUri_, RATING_SVG_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->backgroundUri_, RATING_BACKGROUND_URL);
    /**
     * @tc.steps: case1. When update starStyle Image Uri again, ratingModifier JudgeImageUri is different, but
     * imageSuccessStateCode_ is 0.
     * @tc.expected: ratingModifier will not update CanvasImage or Image Uri.
     */
    rating.SetBackgroundSrc("", true);
    rating.SetForegroundSrc(RATING_SVG_URL, false);
    rating.SetSecondarySrc(RATING_SECONDARY_URL, false);
    ImageSourceInfo backInfo;
    backInfo.SetResourceId(BACKGROUND_IMAGE_RESOURCE_ID);
    ratingLayoutProperty->UpdateBackgroundImageSourceInfo(backInfo);
    ratingPattern->OnModifyDone();
    EXPECT_FALSE(ratingPattern->secondaryConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->backgroundConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->foregroundConfig_.isSvg_);
    EXPECT_EQ(ratingPattern->imageSuccessStateCode_, 0);
    auto paintMethod2 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod2, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->foregroundImageCanvas_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->secondaryImageCanvas_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->backgroundImageCanvas_, nullptr);
    EXPECT_EQ(ratingPattern->ratingModifier_->foregroundUri_, RESOURCE_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->secondaryUri_, RATING_SVG_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->backgroundUri_, RATING_BACKGROUND_URL);
    /**
     * @tc.steps: case2. when new 3 image load successfully and imageSuccessStateCode_ is 0b111 in the above situation
     * @tc.expected: ratingModifier will update new CanvasImage and Image Uri.
     */
    ratingPattern->foregroundImageLoadingCtx_->SuccessCallback(nullptr);
    ratingPattern->secondaryImageLoadingCtx_->SuccessCallback(nullptr);
    ratingPattern->backgroundImageLoadingCtx_->SuccessCallback(nullptr);
    EXPECT_EQ(ratingPattern->imageSuccessStateCode_, 0b111);
    auto paintMethod3 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod3, nullptr);
    EXPECT_EQ(ratingPattern->ratingModifier_->foregroundUri_, RATING_SVG_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->secondaryUri_, RATING_SECONDARY_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->backgroundUri_, RESOURCE_URL);
}

/**
 * @tc.name: RatingPatternTest012
 * @tc.desc: Test rating three images render scale.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rating FrameNode and Pattern, and initialize rating modifier.
     */
    RatingModelNG rating;
    rating.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);
    ratingPattern->foregroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->secondaryImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    /**
     * @tc.steps: step2. update PaintConfig.
     */
    frameNode->geometryNode_->SetFrameSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    frameNode->geometryNode_->SetContentSize(CONTAINER_SIZE);
    ratingPattern->imageSuccessStateCode_ = RATING_IMAGE_SUCCESS_CODE;
    auto paintMethod2 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod2, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    auto scaleX = CONTAINER_SIZE.Height() / FRAME_WIDTH / DEFAULT_STAR_NUM;
    auto scaleY = CONTAINER_SIZE.Height() / FRAME_HEIGHT;
    EXPECT_EQ(ratingPattern->foregroundConfig_.scaleX_, scaleX);
    EXPECT_EQ(ratingPattern->foregroundConfig_.scaleY_, scaleY);
    EXPECT_EQ(ratingPattern->secondaryConfig_.scaleX_, scaleX);
    EXPECT_EQ(ratingPattern->secondaryConfig_.scaleY_, scaleY);
    EXPECT_EQ(ratingPattern->backgroundConfig_.scaleX_, scaleX);
    EXPECT_EQ(ratingPattern->backgroundConfig_.scaleY_, scaleY);
    ASSERT_NE(ratingPattern->ratingModifier_->foregroundImageCanvas_->paintConfig_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->secondaryImageCanvas_->paintConfig_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->backgroundImageCanvas_->paintConfig_, nullptr);
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
}

/**
 * @tc.name: RatingMeasureTest013
 * @tc.desc: Test rating MeasureContent when rating component's width or height is not fully valid.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingMeasureTest013, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RatingTheme>()));
    /**
     * @tc.steps: step1. Create LayoutWrapperNode and RatingLayoutAlgorithm.
     */
    auto ratingLayoutProperty = AceType::MakeRefPtr<RatingLayoutProperty>();
    ratingLayoutProperty->UpdateIndicator(true);
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ASSERT_NE(ratingLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(nullptr, nullptr, ratingLayoutProperty);
    auto ratingLayoutAlgorithm = AceType::MakeRefPtr<RatingLayoutAlgorithm>(nullptr, nullptr, nullptr);
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    /**
    //     corresponding ets code:
    //         Rating().width(300)
    */
    layoutConstraint.selfIdealSize.SetWidth(CONTAINER_WIDTH);
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper),
        SizeF(CONTAINER_WIDTH, CONTAINER_WIDTH / DEFAULT_STAR_NUM));
    /**
    //     corresponding ets code:
    //         Rating().height(300)
    */
    layoutConstraint.selfIdealSize.Reset();
    layoutConstraint.selfIdealSize.SetHeight(CONTAINER_HEIGHT);
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper),
        SizeF(CONTAINER_HEIGHT * DEFAULT_STAR_NUM, CONTAINER_HEIGHT));
}

/**
 * @tc.name: RatingOnChangeEventTest001
 * @tc.desc: Test setting out-of-bounds ratingScore and starNum values.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingOnChangeEventTest001, TestSize.Level1)
{
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ratingTheme->starNum_ = DEFAULT_STAR_NUM;
    ratingTheme->ratingScore_ = DEFAULT_RATING_SCORE;
    ratingTheme->stepSize_ = DEFAULT_STEP_SIZE;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(ratingTheme));

    RatingModelNG rating;
    rating.Create();
    rating.SetBackgroundSrc(RATING_BACKGROUND_URL, false);
    rating.SetForegroundSrc("", true);
    rating.SetSecondarySrc(RATING_SVG_URL, false);
    auto onChange = [](const std::string& ratingScore) { EXPECT_EQ(ratingScore, "1"); };
    rating.SetOnChangeEvent(onChange);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingEventHub = frameNode->GetEventHub<NG::RatingEventHub>();
    ASSERT_NE(ratingEventHub, nullptr);
    ratingEventHub->SetOnChangeEvent(onChange);
    ratingEventHub->FireChangeEvent("1");
}

/**
 * @tc.name: RatingPatternTestNg001
 * @tc.desc: Test the HasRange and RangeInfo properties of Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingPatternTestNg001, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE);
    rating.SetStars(RATING_STAR_NUM);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto ratingAccessibilityProperty = frameNode->GetAccessibilityProperty<RatingAccessibilityProperty>();
    ASSERT_NE(ratingAccessibilityProperty, nullptr);
    EXPECT_TRUE(ratingAccessibilityProperty->HasRange());
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().current, RATING_SCORE);
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().max, RATING_STAR_NUM);
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().min, 0);
}

/**
 * @tc.name: RatingPatternTestNg002
 * @tc.desc: Test the Text property of Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingPatternTestNg002, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE);
    rating.SetStars(RATING_STAR_NUM);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto ratingAccessibilityProperty = frameNode->GetAccessibilityProperty<RatingAccessibilityProperty>();
    ASSERT_NE(ratingAccessibilityProperty, nullptr);
    EXPECT_EQ(ratingAccessibilityProperty->GetText(), std::to_string(RATING_SCORE));
}


/**
 * @tc.name: RatingPaintMethodTest001
 * @tc.desc: Test Rating PaintMethod ShouldHighLight
 * @tc.type: FUNC
 */
HWTEST_F(RatingPatternTestNg, RatingPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating without parameters.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE_3);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    EXPECT_NE(ratingPattern, nullptr);
    /**
     * @tc.steps: step2. Invoke OnImageLoadSuccess to initialize image canvas.
     * @tc.expected: image canvas is not nullptr.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RatingTheme>()));
    ratingPattern->OnImageLoadSuccess(RATING_FOREGROUND_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_SECONDARY_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_BACKGROUND_FLAG);
    EXPECT_NE(ratingPattern->foregroundImageCanvas_, nullptr);
    EXPECT_NE(ratingPattern->secondaryImageCanvas_, nullptr);
    EXPECT_NE(ratingPattern->backgroundImageCanvas_, nullptr);
    const RefPtr<RatingPaintMethod> ratingPaintMethod =
        AceType::DynamicCast<RatingPaintMethod>(ratingPattern->CreateNodePaintMethod());
    EXPECT_NE(ratingPaintMethod, nullptr);

    /**
     * @tc.steps: step3. Invoke GetContentDrawFunction to get draw function and execute it.
     * @tc.expected: The methods are expected call a preset number of times.
     */
    auto ratingPaintProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ratingPaintProperty->UpdateTouchStar(RATING_TOUCH_STAR);
    const RefPtr<RenderContext> renderContext;
    const RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto* paintWrapper1 = new PaintWrapper(renderContext, geometryNode, ratingPaintProperty);
    EXPECT_NE(paintWrapper1, nullptr);

    ratingPaintMethod->UpdateContentModifier(paintWrapper1);
    EXPECT_EQ(ratingPaintMethod->ratingModifier_->touchStar_->Get(), RATING_TOUCH_STAR);
    auto mockCanvas = OHOS::Ace::Testing::MockCanvas();
    DrawingContext context = { mockCanvas, 10.0f, 10.0f };
    EXPECT_CALL(mockCanvas, DrawBackground(_)).Times(RATING_DRAW_BACKGROUND_TIMES);
    EXPECT_CALL(mockCanvas, Save()).Times(RATING_SAVE_TIMES);
    EXPECT_CALL(mockCanvas, ClipRoundRectImpl(_, _, _)).Times(RATING_CLIP_ROUND_RECT_TIMES);
    EXPECT_CALL(mockCanvas, Restore()).Times(RATING_RESTORE_TIMES);
    EXPECT_CALL(mockCanvas, ClipRect(_, _)).Times(RATING_CLIP_CLIP_RECT_TIMES);
    ratingPaintMethod->ratingModifier_->onDraw(context);

    /**
     * @tc.steps: step4. Invoke GetContentDrawFunction to get draw function and execute it when touch star is invalid
     * and ratingScore is integer, which means the secondary image does not draw.
     * @tc.expected: The methods are expected call a preset number of times.
     */
    ratingPaintProperty->UpdateTouchStar(RATING_INVALID_TOUCH_STAR);
    ratingPaintProperty->UpdateRatingScore(RATING_SCORE_4);
    auto* paintWrapper2 = new PaintWrapper(renderContext, geometryNode, ratingPaintProperty);
    ratingPaintMethod->UpdateContentModifier(paintWrapper2);
    EXPECT_EQ(ratingPaintMethod->ratingModifier_->touchStar_->Get(), RATING_INVALID_TOUCH_STAR);
    EXPECT_EQ(ratingPaintMethod->ratingModifier_->drawScore_->Get(), RATING_SCORE_4);
    auto mockCanvas2 = OHOS::Ace::Testing::MockCanvas();
    DrawingContext context2 = { mockCanvas2, 10.0f, 10.0f };

    EXPECT_CALL(mockCanvas2, Save()).Times(RATING_SAVE_TIMES_1);
    EXPECT_CALL(mockCanvas2, Restore()).Times(RATING_RESTORE_TIMES_1);
    EXPECT_CALL(mockCanvas2, ClipRect(_, _)).Times(RATING_CLIP_CLIP_RECT_TIMES_1);
    ratingPaintMethod->ratingModifier_->onDraw(context2);

    /**
     * @tc.steps: step5. Invoke GetContentDrawFunction to get draw function and execute it when touch star is invalid
     * and ratingScore is integer, which means the secondary image does not draw.
     * @tc.expected: The methods are expected call a preset number of times.
     */
    ratingPaintProperty->UpdateTouchStar(RATING_INVALID_TOUCH_STAR_2);
    auto* paintWrapper3 = new PaintWrapper(renderContext, geometryNode, ratingPaintProperty);
    ratingPaintMethod->UpdateContentModifier(paintWrapper3);
    EXPECT_EQ(ratingPaintMethod->ratingModifier_->touchStar_->Get(), RATING_INVALID_TOUCH_STAR_2);
    auto mockCanvas3 = OHOS::Ace::Testing::MockCanvas();
    DrawingContext context3 = { mockCanvas3, 10.0f, 10.0f };
    EXPECT_CALL(mockCanvas3, Save()).Times(RATING_SAVE_TIMES_1);
    EXPECT_CALL(mockCanvas3, Restore()).Times(RATING_RESTORE_TIMES_1);
    EXPECT_CALL(mockCanvas3, ClipRect(_, _)).Times(RATING_CLIP_CLIP_RECT_TIMES_1);
    ratingPaintMethod->ratingModifier_->onDraw(context3);
}
} // namespace OHOS::Ace::NG
