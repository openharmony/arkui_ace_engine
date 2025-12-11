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
const int32_t DEFAULT_STAR_NUM = 5;
const int32_t RATING_STAR_NUM = 10;
const int32_t RATING_STAR_NUM_ZERO = 0;
constexpr double RATING_SCORE = 3.0;
const std::string RATING_SCORE_STRING = "";
const std::string RATING_BACKGROUND_URL = "common/img1.png";
const std::string RATING_FOREGROUND_URL = "common/img2.png";
const std::string RATING_SECONDARY_URL = "common/img3.png";
const std::string RATING_SVG_URL = "common/img4.svg";
constexpr double DEFAULT_RATING_SCORE = 0.0;
constexpr double DEFAULT_STEP_SIZE = 0.5;
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
const SizeF TEST_SIZE_0 = SizeF(0.0f, 0.0f);
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
const SizeF TEST_SIZE_100 = SizeF(100.0f, 100.0f);
const SizeF TEST_SIZE_10 = SizeF(10.0f, 10.0f);
constexpr float TEST_WIDTH_50 = 50.0f;
constexpr float TEST_HEIGHT_60 = 60.0f;
} // namespace

class RatingThreeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingThreeTestNg::SetUpTestCase()
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

void RatingThreeTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: MeasureTest006
 * @tc.desc: Test Rating MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(RatingThreeTestNg, MeasureTest006, TestSize.Level1)
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
HWTEST_F(RatingThreeTestNg, MeasureTest007, TestSize.Level1)
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
HWTEST_F(RatingThreeTestNg, LayoutPolicyIsMatchParentTest001, TestSize.Level1)
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
HWTEST_F(RatingThreeTestNg, CreateWithMediaResourceObj, TestSize.Level1)
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
HWTEST_F(RatingThreeTestNg, UpdateStarStyleImage, TestSize.Level1)
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
HWTEST_F(RatingThreeTestNg, StringTypeToStr, TestSize.Level1)
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
HWTEST_F(RatingThreeTestNg, OnColorModeChange, TestSize.Level1)
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
