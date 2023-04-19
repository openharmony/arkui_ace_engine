/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components/rating/rating_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const int32_t RATING_STAR_NUM = 10;
constexpr double RATING_SCORE = 3.0;
} // namespace

class RatingAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingAccessibilityPropertyTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RatingAccessibilityPropertyTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: RatingAccessibilityPropertyTestNg001
 * @tc.desc: Test the HasRange and RangeInfo properties of Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingAccessibilityPropertyTestNg, RatingAccessibilityPropertyTestNg001, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE);
    rating.SetStars(RATING_STAR_NUM);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto ratingAccessibilityProperty = frameNode->GetAccessibilityProperty<RatingAccessibilityProperty>();
    EXPECT_NE(ratingAccessibilityProperty, nullptr);
    EXPECT_TRUE(ratingAccessibilityProperty->HasRange());
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().current, RATING_SCORE);
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().max, RATING_STAR_NUM);
    EXPECT_EQ(ratingAccessibilityProperty->GetAccessibilityValue().min, 0);
}

/**
 * @tc.name: RatingAccessibilityPropertyTestNg002
 * @tc.desc: Test the Text property of Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RatingAccessibilityPropertyTestNg, RatingAccessibilityPropertyTestNg002, TestSize.Level1)
{
    RatingModelNG rating;
    rating.Create();
    rating.SetRatingScore(RATING_SCORE);
    rating.SetStars(RATING_STAR_NUM);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    auto ratingAccessibilityProperty = frameNode->GetAccessibilityProperty<RatingAccessibilityProperty>();
    EXPECT_NE(ratingAccessibilityProperty, nullptr);
    EXPECT_EQ(ratingAccessibilityProperty->GetText(), std::to_string(RATING_SCORE));
}
} // namespace OHOS::Ace::NG
