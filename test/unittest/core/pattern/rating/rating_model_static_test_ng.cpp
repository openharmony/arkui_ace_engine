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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components/rating/rating_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_layout_property.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_model_static.h"
#include "core/components_ng/pattern/rating/rating_paint_method.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t DEFAULT_STAR_NUM = 5;
const int32_t RATING_STAR_NUM = 10;
constexpr double DEFAULT_RATING_SCORE = 0.0;
constexpr double RATING_SCORE_3 = 3.5;
constexpr double DEFAULT_RATING_STEP_SIZE = 0.0;
constexpr double RATING_STEP_SIZE = 0.7;
const bool RATING_INDICATOR = true;
} // namespace

class RatingStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingStaticTestNg::SetUpTestCase()
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

void RatingStaticTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RatingStaticTestNg001
 * @tc.desc: test rating SetStars.
 * @tc.type: FUNC
 */
HWTEST_F(RatingStaticTestNg, RatingStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rating frameNode.
     */
    auto node = RatingModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RATING_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create rating paintProperty.
     */
    auto ratingLayoutrProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutrProperty, nullptr);

    /**
     * @tc.steps: step3. test SetStars.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<int32_t> ratingStars = std::nullopt;
    RatingModelStatic::SetStars(frameNode, ratingStars);
    EXPECT_EQ(ratingLayoutrProperty->GetStars().value_or(5), DEFAULT_STAR_NUM);
    ratingStars = RATING_STAR_NUM;
    RatingModelStatic::SetStars(frameNode, ratingStars);
    EXPECT_EQ(ratingLayoutrProperty->GetStars(), RATING_STAR_NUM);
}

/**
 * @tc.name: RatingStaticTestNg002
 * @tc.desc: test rating SetStepSize.
 * @tc.type: FUNC
 */
HWTEST_F(RatingStaticTestNg, RatingStaticTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rating frameNode.
     */
    auto node = RatingModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RATING_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create rating paintProperty.
     */
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);

    /**
     * @tc.steps: step3. test SetStepSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<double> ratingStepSize = std::nullopt;
    RatingModelStatic::SetStepSize(frameNode, ratingStepSize);
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(0.0), DEFAULT_RATING_STEP_SIZE);
    ratingStepSize = RATING_STEP_SIZE;
    RatingModelStatic::SetStepSize(frameNode, ratingStepSize);
    EXPECT_EQ(ratingRenderProperty->GetStepSize().value_or(0.0), RATING_STEP_SIZE);
}

/**
 * @tc.name: RatingStaticTestNg003
 * @tc.desc: test rating SetStepSize.
 * @tc.type: FUNC
 */
HWTEST_F(RatingStaticTestNg, RatingStaticTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rating frameNode.
     */
    auto node = RatingModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RATING_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create rating paintProperty.
     */
    auto ratingLayoutrProperty = frameNode->GetLayoutProperty<RatingLayoutProperty>();
    ASSERT_NE(ratingLayoutrProperty, nullptr);
    auto ratingRenderProperty = frameNode->GetPaintProperty<RatingRenderProperty>();
    ASSERT_NE(ratingRenderProperty, nullptr);
    /**
     * @tc.steps: step3. test SetRatingOptions.
     * @tc.expected: step3. the property value meet expectations.
     */
    double ratingValue = 0.0;
    std::optional<bool> ratingIndicator = std::nullopt;
    RatingModelStatic::SetRatingOptions(frameNode, ratingValue, ratingIndicator);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(0.0), DEFAULT_RATING_SCORE);
    EXPECT_EQ(ratingLayoutrProperty->GetIndicator().value_or(false), false);
    ratingValue = RATING_SCORE_3;
    ratingIndicator = RATING_INDICATOR;
    RatingModelStatic::SetRatingOptions(frameNode, ratingValue, ratingIndicator);
    EXPECT_EQ(ratingRenderProperty->GetRatingScore().value_or(0.0), RATING_SCORE_3);
    EXPECT_EQ(ratingLayoutrProperty->GetIndicator().value_or(false), RATING_INDICATOR);
}
} // namespace OHOS::Ace::NG