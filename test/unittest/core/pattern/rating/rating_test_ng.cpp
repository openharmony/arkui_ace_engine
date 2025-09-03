/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
const int32_t RATING_STAR_NUM_ZERO = 0;
constexpr double RATING_SCORE = 3.0;
constexpr double RATING_LAST_SCORE = 5.0;
const std::string RATING_SCORE_STRING = "";
constexpr double RATING_SCORE_2 = -2;
constexpr double RATING_SCORE_3 = 3.5;
constexpr double RATING_SCORE_4 = 3.0;
constexpr double RATING_SCORE_5 = 1.0;
constexpr int32_t RATING_STAR_NUM_1 = -1;
const std::string RATING_BACKGROUND_URL = "common/img1.png";
const std::string RATING_FOREGROUND_URL = "common/img2.png";
const std::string RATING_SECONDARY_URL = "common/img3.png";
const std::string RATING_SVG_URL = "common/img4.svg";
constexpr double DEFAULT_RATING_SCORE = 0.0;
constexpr double DEFAULT_STEP_SIZE = 0.5;
constexpr double RATING_STEP_SIZE = 0.7;
constexpr double RATING_STEP_SIZE_1 = 1;
constexpr double RATING_STEP_SIZE_2 = DEFAULT_STAR_NUM + DEFAULT_STAR_NUM;
constexpr int32_t RATING_TOUCH_STAR = 3;
constexpr int32_t RATING_SAVE_TIMES = 3;
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
const SizeF ZERO_CONTAINER_SIZE(DEFAULT_RATING_SCORE, DEFAULT_RATING_SCORE);
const std::string RESOURCE_URL = "resource:///ohos_test_image.svg";
const std::string IMAGE_SOURCE_INFO_STRING = "empty source";
const int32_t RATING_FOREGROUND_FLAG = 0b001;
const int32_t RATING_SECONDARY_FLAG = 0b010;
const int32_t RATING_BACKGROUND_FLAG = 0b100;
const int32_t RATING_BACKGROUNDFOCUS_FLAG = 0b1000;
const int32_t INVALID_IMAGE_FLAG = 0b111;
const std::string RATING_IMAGE_LOAD_FAILED = "ImageDataFailed";
const std::string RATING_IMAGE_LOAD_SUCCESS = "ImageDataSuccess";
constexpr int32_t RATING_IMAGE_SUCCESS_CODE = 0b111;
constexpr int32_t RATING_IMAGE_SUCCESS_FOCUS_CODE = 0b1111;
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
constexpr float TEST_HEIGHT_60 = 60.0f;
} // namespace

class RatingTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingTestNg::SetUpTestCase()
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

void RatingTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingCreateTest001, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
}

/**
 * @tc.name: RatingLayoutPropertyTest003
 * @tc.desc: Test setting indicator, starStyle and starNum.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingLayoutPropertyTest003, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingRenderPropertyTest004, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);

    // Test ratingScore and stepSize default value.
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(DEFAULT_RATING_SCORE), DEFAULT_RATING_SCORE);
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(DEFAULT_STEP_SIZE), DEFAULT_STEP_SIZE);
}

/**
 * @tc.name: RatingRenderPropertyTest005
 * @tc.desc: Test setting rating ratingScore(drawScore) and stepSize.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingRenderPropertyTest005, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(RATING_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);

    // Test ratingScore and stepSize value.
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(0.0), RATING_STEP_SIZE);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(DEFAULT_RATING_SCORE), RATING_SCORE);
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: RatingConstrainsPropertyTest006
 * @tc.desc: Test setting out-of-bounds ratingScore and starNum values.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingConstrainsPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating with its the ratingScore and starNums are both negative.
     * @tc.expected: Constrain them with the values defined in theme.
     */
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ratingTheme->starNum_ = DEFAULT_STAR_NUM;
    ratingTheme->ratingScore_ = DEFAULT_RATING_SCORE;
    ratingTheme->stepSize_ = DEFAULT_STEP_SIZE;
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

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    EXPECT_EQ(ratingLayoutProperty->GetStars().value_or(DEFAULT_STAR_NUM), RATING_STAR_NUM_1);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(DEFAULT_RATING_SCORE), RATING_SCORE_2);
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(DEFAULT_STEP_SIZE), RATING_STEP_SIZE_2);
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ratingRenderProperty->UpdateRatingScore(RATING_SCORE);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);

    /**
     * @tc.steps: step4. Invoke ConstrainsRatingScore when the score has not changed compared with the last time.
     * @tc.expected: onChange Event will not be fired.
     */
    ratingPattern->lastRatingScore_ = RATING_SCORE;
    ratingPattern->ConstrainsRatingScore(ratingLayoutProperty);
    EXPECT_TRUE(unknownRatingScore.empty());

    /**
     * @tc.steps: step5. Invoke ConstrainsRatingScore when the score has changed compared with the last time and it is
     * not the first time initialized.
     * @tc.expected: onChange Event will be fired.
     */
    ratingPattern->lastRatingScore_ = RATING_LAST_SCORE;
    ratingPattern->ConstrainsRatingScore(ratingLayoutProperty);
    EXPECT_EQ(unknownRatingScore, RATING_SCORE_STRING);
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: RatingPatternGetImageSourceFromThemeTest007
 * @tc.desc: success and fail callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternGetImageSourceFromThemeTest007, TestSize.Level1)
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
     * @tc.steps: step2. Invoke CheckImageInfoHasChangedOrNot.
     */
    std::string lifeCycleTags[] = { RATING_IMAGE_LOAD_FAILED, RATING_IMAGE_LOAD_SUCCESS };
    for (std::string tag : lifeCycleTags) {
        ratingPattern->CheckImageInfoHasChangedOrNot(
            RATING_FOREGROUND_FLAG, ImageSourceInfo(RATING_FOREGROUND_URL), tag);
        ratingPattern->CheckImageInfoHasChangedOrNot(RATING_SECONDARY_FLAG, ImageSourceInfo(RATING_SECONDARY_URL), tag);
        ratingPattern->CheckImageInfoHasChangedOrNot(
            RATING_BACKGROUND_FLAG, ImageSourceInfo(RATING_BACKGROUND_URL), tag);
        /**
         * @tc.cases: case. cover branch switch imageFlag default branch.
         */
        ratingPattern->CheckImageInfoHasChangedOrNot(INVALID_IMAGE_FLAG, ImageSourceInfo(RATING_BACKGROUND_URL), tag);
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
 * @tc.name: RatingPatternGetImageSourceFromThemeTest008
 * @tc.desc: success and fail callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternGetImageSourceFromThemeTest008, TestSize.Level1)
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
    ratingPattern->isNeedFocusStyle_ = true;
    ratingPattern->OnModifyDone();
    ratingPattern->InitEvent();
    ASSERT_NE(ratingPattern, nullptr);

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
        /**
         * @tc.cases: case. cover branch switch imageFlag default branch.
         */
        ratingPattern->CheckImageInfoHasChangedOrNot(INVALID_IMAGE_FLAG, ImageSourceInfo(RATING_BACKGROUND_URL), tag);
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
     * @tc.steps: step4. Invoke OnImageLoadSuccess when the foreground, secondary background and focusbackground image
     * has been loaded successfully.
     * @tc.expected: imageSuccessStateCode_ will be set as the success code only when 4 images have been loaded.
     */
    ratingPattern->OnImageLoadSuccess(RATING_FOREGROUND_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_SECONDARY_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_BACKGROUND_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_BACKGROUNDFOCUS_FLAG);
    EXPECT_EQ(ratingPattern->imageSuccessStateCode_, RATING_IMAGE_SUCCESS_FOCUS_CODE);
}

/**
 * @tc.name: RatingPatternToJsonValueTest008
 * @tc.desc: Invoke ToJsonValue function.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternToJsonValueTest008, TestSize.Level1)
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
    ratingPattern->ToJsonValue(json, filter);

    EXPECT_EQ(json->GetValue(RATING_FOREGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json->GetValue(RATING_SECONDARY_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json->GetValue(RATING_BACKGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);

    /**
     * @tc.steps: step2. Invoke ToJsonValue when the foreground, secondary and background image are used in theme.
     * @tc.expected: ImageSourceInfo src is null.
     */
    ratingPattern->isForegroundImageInfoFromTheme_ = true;
    ratingPattern->isSecondaryImageInfoFromTheme_ = true;
    ratingPattern->isBackgroundImageInfoFromTheme_ = true;
    auto json2 = JsonUtil::Create(true);
    ratingPattern->ToJsonValue(json2, filter);

    EXPECT_EQ(json2->GetValue(RATING_FOREGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json2->GetValue(RATING_SECONDARY_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
    EXPECT_EQ(json2->GetValue(RATING_BACKGROUND_IMAGE_KEY)->GetString(), IMAGE_SOURCE_INFO_STRING);
}

/**
 * @tc.name: RatingMeasureTest009
 * @tc.desc: Test rating measure and layout function and invoke OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingMeasureTest009, TestSize.Level1)
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

    /**
     * @tc.steps: step3. Invoke MeasureContent when the size has not been defined.
     * @tc.expected: Use the size defined in ratingTheme.
     */
    const LayoutConstraintF layoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper), std::nullopt);

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

    layoutConstraintSize.selfIdealSize.SetSize(SizeF(CONTAINER_WIDTH, -500));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper), std::nullopt);
    /**
     * @tc.steps: step5. Invoke MeasureContent when the size is negative.
     * @tc.expected: Use the size defined in theme.
     */
    layoutConstraintSize.selfIdealSize.SetSize(INVALID_CONTAINER_SIZE);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper), std::nullopt);

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
    auto contentNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ratingPattern->contentModifierNode_ = contentNode;
    ratingLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_FALSE(ratingPattern->OnDirtyLayoutWrapperSwap(layoutWrapper2, config));
}

/**
 * @tc.name: RatingLayoutPropertyTest010
 * @tc.desc: Test when starStyle is undefined, flag is set by true, and star sourceInfo is from Theme.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingLayoutPropertyTest010, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest011, TestSize.Level1)
{
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

    /**
     * @tc.steps: step2. create nodePaintMethod before carry out ImageLoadContexts, should return a default method
     * instead of nullptr.
     */
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto ratingTheme = pipeline->GetTheme<RatingTheme>();
    CHECK_NULL_VOID(ratingTheme);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    /**
     * @tc.steps: step3. 3 ImageLoadContexts carry out successfully.
     */
    ratingPattern->LoadForeground(ratingLayoutProperty, ratingTheme, iconTheme);
    ratingPattern->LoadSecondary(ratingLayoutProperty, ratingTheme, iconTheme);
    ratingPattern->LoadBackground(ratingLayoutProperty, ratingTheme, iconTheme);
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
     * @tc.steps: step4. 3 ImageLoadContexts callback successfuly, and imageSuccessStateCode_ ==
     * RATING_IMAGE_SUCCESS_CODE.
     * @tc.expected: ratingModifier will update CanvasImage the first time.
     */
    auto paintMethod2 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod2, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->foregroundImageCanvas_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->secondaryImageCanvas_, nullptr);
    ASSERT_NE(ratingPattern->ratingModifier_->backgroundImageCanvas_, nullptr);
    EXPECT_EQ(ratingPattern->ratingModifier_->foreground_.GetSrc(), RESOURCE_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->secondary_.GetSrc(), RATING_SVG_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->background_.GetSrc(), RATING_BACKGROUND_URL);
    /**
     * @tc.steps: case. when new 3 image load successfully and imageSuccessStateCode_ is 0b111 in the above situation
     * @tc.expected: ratingModifier will update new CanvasImage and Image Uri.
     */
    rating.SetBackgroundSrc("", true);
    rating.SetForegroundSrc(RATING_SVG_URL, false);
    rating.SetSecondarySrc(RATING_SECONDARY_URL, false);
    ratingPattern->LoadBackground(ratingLayoutProperty, ratingTheme, iconTheme);
    ratingPattern->LoadForeground(ratingLayoutProperty, ratingTheme, iconTheme);
    ratingPattern->LoadSecondary(ratingLayoutProperty, ratingTheme, iconTheme);
    EXPECT_FALSE(ratingPattern->secondaryConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->backgroundConfig_.isSvg_);
    EXPECT_TRUE(ratingPattern->foregroundConfig_.isSvg_);
    EXPECT_EQ(ratingPattern->imageSuccessStateCode_, 7);
    ratingPattern->foregroundImageLoadingCtx_->SuccessCallback(nullptr);
    ratingPattern->secondaryImageLoadingCtx_->SuccessCallback(nullptr);
    ratingPattern->backgroundImageLoadingCtx_->SuccessCallback(nullptr);
    EXPECT_EQ(ratingPattern->imageSuccessStateCode_, RATING_IMAGE_SUCCESS_CODE);
    auto paintMethod3 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod3, nullptr);
    EXPECT_EQ(ratingPattern->ratingModifier_->foreground_.GetSrc(), RATING_SVG_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->secondary_.GetSrc(), RATING_SECONDARY_URL);
    EXPECT_EQ(ratingPattern->ratingModifier_->background_.GetSrc(), RESOURCE_URL);
}

/**
 * @tc.name: RatingPatternTest012
 * @tc.desc: Test rating three images render scale.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest012, TestSize.Level1)
{
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
    ratingPattern->OnModifyDone();
    ratingPattern->InitEvent();
    ratingPattern->foregroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->secondaryImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
    ratingPattern->backgroundImageFocusCanvas_ = AceType::MakeRefPtr<MockCanvasImage>();
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
 * @tc.name: RatingPatternTest015
 * @tc.desc: Test for CreateNodePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest015, TestSize.Level1)
{
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

    /**
     * @tc.steps: step2. create nodePaintMethod, should return a default method instead of nullptr.
     */
    auto paintMethod1 = ratingPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod1, nullptr);
}

/**
 * @tc.name: RatingMeasureTest013
 * @tc.desc: Test rating MeasureContent when rating component's width or height is not fully valid.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingMeasureTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create LayoutWrapperNode and RatingLayoutAlgorithm.
     * add contentModifierNode for fitting new builder
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
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(config.starNum_, RATING_STAR_NUM);
        EXPECT_EQ(config.isIndicator_, RATING_INDICATOR);
        EXPECT_EQ(config.rating_, RATING_SCORE);
        EXPECT_EQ(config.stepSize_, DEFAULT_STEP_SIZE);
        return nullptr;
    };
    ratingPattern->SetBuilderFunc(node);
    ratingPattern->BuildContentModifierNode();
    auto ratingLayoutProperty = AceType::MakeRefPtr<RatingLayoutProperty>();
    ratingLayoutProperty->UpdateIndicator(true);
    ratingLayoutProperty->UpdateStars(DEFAULT_STAR_NUM);
    ASSERT_NE(ratingLayoutProperty, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, nullptr, ratingLayoutProperty);
    auto ratingLayoutAlgorithm = AceType::MakeRefPtr<RatingLayoutAlgorithm>(nullptr, nullptr, nullptr, nullptr);
    ASSERT_NE(ratingLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    auto contentNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ratingPattern->contentModifierNode_ = contentNode;
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper), std::nullopt);
    ratingPattern->contentModifierNode_ = nullptr;
    EXPECT_EQ(ratingLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper), ZERO_CONTAINER_SIZE);
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
HWTEST_F(RatingTestNg, RatingOnChangeEventTest001, TestSize.Level1)
{
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ratingTheme->starNum_ = DEFAULT_STAR_NUM;
    ratingTheme->ratingScore_ = DEFAULT_RATING_SCORE;
    ratingTheme->stepSize_ = DEFAULT_STEP_SIZE;

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
 * @tc.name: RatingTestNg001
 * @tc.desc: Test the HasRange and RangeInfo properties of Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingTestNg001, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE);
    rating.SetStars(RATING_STAR_NUM);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto ratingAccessibilityProperty = frameNode->GetAccessibilityProperty<RatingAccessibilityProperty>();
    ASSERT_NE(ratingAccessibilityProperty, nullptr);
    EXPECT_TRUE(ratingAccessibilityProperty->HasRange());
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().current, RATING_SCORE);
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().max, RATING_STAR_NUM);
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().min, 0);
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: RatingTestNg002
 * @tc.desc: Test the Text property of Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingTestNg002, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE);
    rating.SetStars(RATING_STAR_NUM);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto ratingAccessibilityProperty = frameNode->GetAccessibilityProperty<RatingAccessibilityProperty>();
    ASSERT_NE(ratingAccessibilityProperty, nullptr);
    EXPECT_EQ(ratingAccessibilityProperty->GetText(), std::to_string(RATING_SCORE));
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: RatingPaintMethodTest001
 * @tc.desc: Test RatingModifier::onDraw
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPaintPropertyTest001, TestSize.Level1)
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
    ratingPattern->OnImageLoadSuccess(RATING_FOREGROUND_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_SECONDARY_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_BACKGROUND_FLAG);
    ratingPattern->OnImageLoadSuccess(RATING_BACKGROUNDFOCUS_FLAG);
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
    EXPECT_CALL(mockCanvas, Save()).Times(AtLeast(RATING_SAVE_TIMES));
    EXPECT_CALL(mockCanvas, Restore()).Times(AtLeast(RATING_RESTORE_TIMES));
    EXPECT_CALL(mockCanvas, ClipRect(_, _, _)).Times(RATING_CLIP_CLIP_RECT_TIMES);
    EXPECT_CALL(mockCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(mockCanvas));
    EXPECT_CALL(mockCanvas, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(mockCanvas, DetachBrush()).WillRepeatedly(ReturnRef(mockCanvas));
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

    EXPECT_CALL(mockCanvas2, Save()).Times(AtLeast(RATING_SAVE_TIMES_1));
    EXPECT_CALL(mockCanvas2, Restore()).Times(AtLeast(RATING_RESTORE_TIMES_1));
    EXPECT_CALL(mockCanvas2, ClipRect(_, _, _)).Times(RATING_CLIP_CLIP_RECT_TIMES_1);
    EXPECT_CALL(mockCanvas2, AttachBrush(_)).WillRepeatedly(ReturnRef(mockCanvas2));
    EXPECT_CALL(mockCanvas2, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(mockCanvas2, DetachBrush()).WillRepeatedly(ReturnRef(mockCanvas2));
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
    EXPECT_CALL(mockCanvas3, Save()).Times(AtLeast(RATING_SAVE_TIMES_1));
    EXPECT_CALL(mockCanvas3, Restore()).Times(AtLeast(RATING_RESTORE_TIMES_1));
    EXPECT_CALL(mockCanvas3, ClipRect(_, _, _)).Times(RATING_CLIP_CLIP_RECT_TIMES_1);
    EXPECT_CALL(mockCanvas3, AttachBrush(_)).WillRepeatedly(ReturnRef(mockCanvas3));
    EXPECT_CALL(mockCanvas3, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(mockCanvas3, DetachBrush()).WillRepeatedly(ReturnRef(mockCanvas3));
    ratingPaintMethod->ratingModifier_->onDraw(context3);
}

/**
 * @tc.name: RatingPaintMethodTest002
 * @tc.desc: Test RatingModifier::onDraw
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPaintPropertyTest002, TestSize.Level1)
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
    ratingPaintMethod->ratingModifier_->SetUseContentModifier(true);
    EXPECT_CALL(mockCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(mockCanvas));
    EXPECT_CALL(mockCanvas, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(mockCanvas, DetachBrush()).WillRepeatedly(ReturnRef(mockCanvas));
    ratingPaintMethod->ratingModifier_->onDraw(context);

    ratingPaintMethod->ratingModifier_->SetUseContentModifier(false);
    ratingPaintMethod->ratingModifier_->SetReverse(true);
    ratingPaintMethod->ratingModifier_->onDraw(context);
    ratingPaintProperty->UpdateRatingScore(RATING_SCORE_4);
    ratingPaintMethod->ratingModifier_->onDraw(context);
    auto testResult = ratingPaintMethod->ratingModifier_->drawScore_->Get();
    const int32_t testExpect = ceil(testResult);
    EXPECT_NE(testExpect, testResult);
    ratingPaintProperty->UpdateRatingScore(RATING_SCORE_3);
    ratingPaintMethod->ratingModifier_->onDraw(context);
    EXPECT_NE(testExpect, testResult);
}

/**
 * @tc.name: RatingPatternOnKeyEvent001
 * @tc.desc: Test Rating Pattern OnKeyEven()
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternOnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating pattern.
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
     * @tc.steps: step2. Construct KeyEvent and call OnKeyEvent().
     * @tc.expected: result is expected.
     */
    KeyEvent event;

    /**
     * @tc.cases: case. cover KeyAction is not DOWN.
     */
    event.action = KeyAction::UP;
    event.code = KeyCode::KEY_TAB;
    bool result = ratingPattern->OnKeyEvent(event);
    EXPECT_FALSE(result);

    /**
     * @tc.cases: case. cover branch event action is DOWN and KeyCode is KEY_DPAD_LEFT.
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;
    result = ratingPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);

    /**
     * @tc.cases: case. cover branch event action is DOWN and KeyCode is KEY_DPAD_RIGHT.
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    result = ratingPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);

    /**
     * @tc.cases: case. cover branch event action is DOWN and KeyCode is KEY_MOVE_HOME.
     */
    event.code = KeyCode::KEY_MOVE_HOME;
    result = ratingPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);

    /**
     * @tc.cases: case. cover branch event action is DOWN and KeyCode is KEY_MOVE_END.
     */
    event.code = KeyCode::KEY_MOVE_END;
    result = ratingPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);

    /**
     * @tc.cases: case. cover branch event action is DOWN and KeyCode is KEY_ENTER.
     */
    event.code = KeyCode::KEY_ENTER;
    result = ratingPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);

    /**
     * @tc.cases: case. cover branch event action is DOWN and KeyCode is KEY_SPACE.
     */
    event.code = KeyCode::KEY_SPACE;
    result = ratingPattern->OnKeyEvent(event);
    EXPECT_TRUE(result);

    /**
     * @tc.cases: case. cover branch invalid event code.
     */
    event.code = KeyCode::KEY_MENU;
    result = ratingPattern->OnKeyEvent(event);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RatingTestBuilderFunc001
 * @tc.desc: SetBuilderFunc and get value, and test the result when the func changed, the func is not nullptr.
 * This test will change 3 times:
 * 1.Func set 1 star,expect the result is 1 star.
 * 2.Func change to set 2 stars, and expect 2 stars.
 * 3.Func change to set 3 stars, and expect 3 stars.
 * This test whether the function can be excuted successfully by changing the function callback.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingTestBuilderFunc001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     * @tc.expected: step1. node is not null.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(1); // Default step size as 1.
    rating.SetStars(5); // Default stars as 5.
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();

    std::string result;
    /**
     * @tc.steps: step2. Create RatingBuilderFunc and test a node with rating star 1.
     */
    auto firstNodeFunc = [&result](RatingConfiguration config) -> RefPtr<FrameNode> {
        result = TEST_RESULT_FIRST;
        RatingModelNG rating;
        rating.Create();
        rating.SetStars(1); // First time, set stars as 1.
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        return frameNode;
    };

    /**
     * @tc.steps: step3. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(firstNodeFunc);
    auto firstNode = ratingPattern->BuildContentModifierNode();

    EXPECT_EQ(result, TEST_RESULT_FIRST);
    EXPECT_EQ("Rating", firstNode->GetTag());
    auto layoutProperty = firstNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetStars().value(), 1); // First time， set 1 star, and expect the result is 1.

    /**
     * @tc.steps: step4. Create RatingBuilderFunc and test a node with rating star 2.
     */
    auto secondNodeFunc = [&result](RatingConfiguration config) -> RefPtr<FrameNode> {
        result = TEST_RESULT_SECOND;
        RatingModelNG rating;
        rating.Create();
        rating.SetStars(2); // Second time, set stars as 2.
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        return frameNode;
    };
    ratingPattern->SetBuilderFunc(secondNodeFunc);
    auto secondNode = ratingPattern->BuildContentModifierNode();
    EXPECT_EQ(result, TEST_RESULT_SECOND);
    auto secondLayoutProperty = secondNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_EQ(secondLayoutProperty->GetStars().value(), 2); // Second time， set 2 star, and expect the result is 2.

    /**
     * @tc.steps: step5. Create RatingBuilderFunc and test a node with rating star 3,expect star is 3.
     */
    auto thirdNodeFunc = [&result](RatingConfiguration config) -> RefPtr<FrameNode> {
        result = TEST_RESULT_THIRD;
        RatingModelNG rating;
        rating.Create();
        rating.SetStars(3); // Third time, set stars as 3.
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        return frameNode;
    };
    ratingPattern->SetBuilderFunc(thirdNodeFunc);
    auto thirdNode = ratingPattern->BuildContentModifierNode();
    EXPECT_EQ(result, TEST_RESULT_THIRD);
    auto thirdLayoutProperty = thirdNode->GetLayoutProperty<RatingLayoutProperty>();
    EXPECT_EQ(thirdLayoutProperty->GetStars().value(), 3); // Third time， set 3 star, and expect the result is 3.
}

/**
 * @tc.name: RatingTestBuilderFunc002
 * @tc.desc: SetBuilderFunc and get value, and test the result when the func is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingTestBuilderFunc002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create RatingModelNG.
     * @tc.expected: step1. node is not null.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetIndicator(RATING_INDICATOR_FALSE);
    rating.SetStepSize(1); // Default step size as 1.
    rating.SetStars(5); // Default stars as 5.
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto ratingPattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(ratingPattern, nullptr);

    std::string result;
    /**
     * @tc.steps: step2. Create RatingBuilderFunc and test a nullptr node.
     * @tc.expected: step2. Func is excuted successfully.
     */
    auto forthNodeFunc = [&result](RatingConfiguration config) -> RefPtr<FrameNode> {
        result = TEST_RESULT_FORTH;
        return nullptr;
    };

    /**
     * @tc.steps: step3. Set paramaters to pattern Builderfunc.
     */
    ratingPattern->SetBuilderFunc(forthNodeFunc);
    auto forthNode = ratingPattern->BuildContentModifierNode();
    EXPECT_EQ(result, TEST_RESULT_FORTH);
    EXPECT_EQ(forthNode, nullptr);
}

/**
 * @tc.name: RatingPatternTest059
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest059, TestSize.Level1)
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
    ratingPattern->SetRatingScore(RATING_SCORE_3);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
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
 * @tc.name: RatingPatternTest060
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest060, TestSize.Level1)
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
    ratingPattern->SetRatingScore(RATING_SCORE_4);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
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
 * @tc.name: RatingPatternTest061
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest061, TestSize.Level1)
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
    ratingPattern->SetRatingScore(RATING_SCORE_5);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
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
 * @tc.name: RatingPatternTest062
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest062, TestSize.Level1)
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
    ratingPattern->SetRatingScore(DEFAULT_RATING_SCORE);

    /**
     * @tc.steps: step3. Make builderFunc.
     */
    auto node = [](RatingConfiguration config) -> RefPtr<FrameNode> {
            EXPECT_EQ(config.starNum_, DEFAULT_STAR_NUM);
            EXPECT_EQ(config.isIndicator_, RATING_INDICATOR_FALSE);
            EXPECT_EQ(config.rating_, DEFAULT_RATING_SCORE);
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
 * @tc.name: RatingPatternTest063
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest063, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest064, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest065, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest066, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest067, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest068, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest069, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest070, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest071, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest072, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest073, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest074, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest075, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingNGTest076, TestSize.Level1)
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
    EXPECT_EQ(paintProperty->GetRatingScoreValue(), 10.0f);
}

/**
 * @tc.name: RatingPatternTest016
 * @tc.desc: Test rating three images and focus image render scale.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, RatingPatternTest016, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest017, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest018, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingPatternTest019, TestSize.Level1)
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
HWTEST_F(RatingTestNg, RatingOnChangeEventTest002, TestSize.Level1)
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
HWTEST_F(RatingTestNg, StyleTest001, TestSize.Level1)
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
HWTEST_F(RatingTestNg, MeasureTest001, TestSize.Level1)
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
HWTEST_F(RatingTestNg, MeasureTest002, TestSize.Level1)
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
HWTEST_F(RatingTestNg, MeasureTest003, TestSize.Level1)
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
HWTEST_F(RatingTestNg, MeasureTest004, TestSize.Level1)
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
HWTEST_F(RatingTestNg, MeasureTest005, TestSize.Level1)
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

/**
 * @tc.name: MeasureTest006
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, MeasureTest006, TestSize.Level1)
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
    LayoutPolicyProperty layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ratingTheme->ratingMiniHeight_ = Dimension(TEST_WIDTH_50);
    ratingTheme->ratingHeight_ = Dimension(TEST_WIDTH_50);
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    auto ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_10);
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. call MeasureContent function.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.selfIdealSize.SetSize(TEST_SIZE_200);
    ret = ratingLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, TEST_SIZE_200);
}

/**
 * @tc.name: MeasureTest007
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, MeasureTest007, TestSize.Level1)
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
     * @tc.expected: ret is not equal to TEST_SIZE_0.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ratingTheme = AceType::MakeRefPtr<RatingTheme>();
    ASSERT_NE(ratingTheme, nullptr);
    auto ret = ratingLayoutAlgorithm->LayoutPolicyIsWrapContent(
        contentConstraint, layoutPolicyProperty, DEFAULT_STAR_NUM, TEST_SIZE_200.Width(), TEST_SIZE_200.Height());
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step2. call MeasureContent function.
     * @tc.expected: ret is not equal to TEST_SIZE_0.
     */
    ret = ratingLayoutAlgorithm->LayoutPolicyIsWrapContent(
        contentConstraint, layoutPolicyProperty, RATING_STAR_NUM_ZERO, TEST_SIZE_200.Width(), TEST_SIZE_200.Height());
    EXPECT_EQ(ret, TEST_SIZE_0);
}

/**
 * @tc.name: LayoutPolicyIsMatchParentTest001
 * @tc.desc: Test Rating LayoutPolicyIsMatchParent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, LayoutPolicyIsMatchParentTest001, TestSize.Level1)
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
     * @tc.steps: step2. call LayoutPolicyIsMatchParent function.
     * @tc.expected: ret is equal to TEST_SIZE_0.
     */
    LayoutConstraintF contentConstraint;
    int32_t stars = 1;
    auto layoutPolicy = ratingLayoutProperty->GetLayoutPolicyProperty();
    auto ret = ratingLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, stars);
    EXPECT_EQ(ret, TEST_SIZE_0);

    /**
     * @tc.steps: step3. set layoutPolicy->widthLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = ratingLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, stars);
    EXPECT_EQ(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step4. set selfIdealSize.height_ to TEST_HEIGHT_60.
     * @tc.expected: result equals.
     */
    contentConstraint.selfIdealSize.SetHeight(TEST_HEIGHT_60);
    ret = ratingLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, stars);
    EXPECT_EQ(ret, SizeF({ TEST_SIZE_200.Width(), TEST_HEIGHT_60 }));

    /**
     * @tc.steps: step5. set layoutPolicy->heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: ret is equal to TEST_SIZE_200.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    ret = ratingLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, stars);
    EXPECT_EQ(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step6. set selfIdealSize.width_ to TEST_WIDTH_50.
     * @tc.expected: result equals.
     */
    contentConstraint.selfIdealSize.SetWidth(TEST_WIDTH_50);
    ret = ratingLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy, stars);
    EXPECT_EQ(ret, SizeF({ TEST_WIDTH_50, TEST_SIZE_200.Height() }));
}


/**
 * @tc.name: CreateWithMediaResourceObj
 * @tc.desc: Test CreateWithMediaResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, CreateWithMediaResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a RatingModelNG instance and get the main frame node.
     */
    RatingModelNG rating;
    rating.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::RATING_ETS_TAG);
    auto pattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string key = "rating" + rating.StringTypeToStr(RatingUriType::BACKGROUND_URI);

    /**
     * @tc.steps: step2. Test CreateWithMediaResourceObj with a valid ResourceObject.
     * @tc.expected: count is equal to 1.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    rating.CreateWithMediaResourceObj(resObj, RatingUriType::BACKGROUND_URI);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);

    /**
     * @tc.steps: step3. Test CreateWithMediaResourceObj with a null ResourceObject.
     * @tc.expected: The resource manager should be null.
     */
    rating.CreateWithMediaResourceObj(nullptr, RatingUriType::BACKGROUND_URI);
    resMgr = pattern->resourceMgr_;
    EXPECT_EQ(resMgr, nullptr);

    /**
     * @tc.steps: step4. Test CreateWithMediaResourceObj with a ResourceObject containing parameters.
     * @tc.expected: count is equal to 1.
     */
    ResourceObjectParams params { .value = "", .type = ResourceObjectParamType::NONE };
    RefPtr<ResourceObject> resObjWithParams =
        AceType::MakeRefPtr<ResourceObject>(1, 10003, std::vector<ResourceObjectParams> { params }, "", "", 100000);
    rating.CreateWithMediaResourceObj(resObjWithParams, RatingUriType::BACKGROUND_URI);
    resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
    pattern->OnColorModeChange(1);
}

/**
 * @tc.name: UpdateStarStyleImage
 * @tc.desc: Test UpdateStarStyleImage
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, UpdateStarStyleImage, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up the theme manager and pipeline context.
     */
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

    /**
     * @tc.steps: step2. Create a RatingModelNG instance and get the main frame node.
     */
    RatingModelNG rating;
    rating.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. Test UpdateStarStyleImage for background URI.
     * @tc.expected: result is equal to RATING_BACKGROUND_URL.
     */
    rating.UpdateStarStyleImage(frameNode, RatingUriType::BACKGROUND_URI, RATING_BACKGROUND_URL);
    EXPECT_EQ(ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_BACKGROUND_URL);

    /**
     * @tc.steps: step4. Test UpdateStarStyleImage for foreground URI.
     * @tc.expected: result is equal to RATING_FOREGROUND_URL.
     */
    rating.UpdateStarStyleImage(frameNode, RatingUriType::FOREGROUND_URI, RATING_FOREGROUND_URL);
    EXPECT_EQ(ratingLayoutProperty->GetForegroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_FOREGROUND_URL);

    /**
     * @tc.steps: step5. Test UpdateStarStyleImage for secondary URI.
     * @tc.expected: result is equal to RATING_SECONDARY_URL.
     */
    rating.UpdateStarStyleImage(frameNode, RatingUriType::SECONDARY_URI, RATING_SECONDARY_URL);
    EXPECT_EQ(ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_SECONDARY_URL);

    /**
     * @tc.steps: step6. Test UpdateStarStyleImage with an empty secondary URI.
     * @tc.expected: result is equal to "".
     */
    rating.UpdateStarStyleImage(frameNode, RatingUriType::SECONDARY_URI, "");
    EXPECT_EQ(ratingLayoutProperty->GetSecondaryImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(), "");

    /**
     * @tc.steps: step7. Test UpdateStarStyleImage with an invalid URI type.
     */
    int32_t defaultValue = 999;
    rating.UpdateStarStyleImage(frameNode, static_cast<RatingUriType>(defaultValue), "");
    EXPECT_EQ(ratingLayoutProperty->GetBackgroundImageSourceInfo().value_or(ImageSourceInfo("")).GetSrc(),
        RATING_BACKGROUND_URL);
}

/**
 * @tc.name: StringTypeToStr
 * @tc.desc: test StringTypeToStr.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, StringTypeToStr, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Define a list of RatingUriType and their expected string values.
     * @tc.expected: The StringTypeToStr function should return the correct string values.
     */
    std::vector<std::pair<RatingUriType, std::string>> types = {
        { RatingUriType::BACKGROUND_URI, "BackgroundUri" },
        { RatingUriType::FOREGROUND_URI, "ForegroundUri" },
        { RatingUriType::SECONDARY_URI, "SecondaryUri" } };
    for (const auto& [type, val] : types) {
        auto ret = RatingModelNG::StringTypeToStr(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: OnColorModeChange
 * @tc.desc: Test OnColorModeChange.
 * @tc.type: FUNC
 */
HWTEST_F(RatingTestNg, OnColorModeChange, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RatingPattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    int32_t colorMode = static_cast<int32_t>(ColorMode::DARK);
    pattern->isNeedFocusStyle_ = true;
    pattern->OnColorModeChange(colorMode);

    EXPECT_TRUE(pattern->isForegroundImageInfoFromTheme_);
    EXPECT_TRUE(pattern->isSecondaryImageInfoFromTheme_);
    EXPECT_TRUE(pattern->isBackgroundImageInfoFromTheme_);

    g_isConfigChangePerform = false;
}
} // namespace OHOS::Ace::NG
