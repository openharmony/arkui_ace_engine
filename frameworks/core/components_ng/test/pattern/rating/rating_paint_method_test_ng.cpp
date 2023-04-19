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

#include <cmath>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#define protected public
#include "base/geometry/offset.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "core/components_ng/pattern/rating/rating_paint_method.h"
#include "core/components_ng/pattern/rating/rating_pattern.h"
#include "core/components_ng/pattern/rating/rating_render_property.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t RATING_STAR_NUM = 10;
constexpr double RATING_SCORE = 3.5;
constexpr double DEFAULT_STEP_SIZE = 0.5;
constexpr int32_t RATING_TOUCH_STAR = 3;
constexpr int32_t RATING_FOREGROUND_FLAG = 0b001;
constexpr int32_t RATING_SECONDARY_FLAG = 0b010;
constexpr int32_t RATING_BACKGROUND_FLAG = 0b100;
constexpr int32_t RATING_DRAW_BACKGROUND_TIMES = 1;
constexpr int32_t RATING_SAVE_TIMES = 3;
constexpr int32_t RATING_CLIP_ROUND_RECT_TIMES = 1;
constexpr int32_t RATING_CLIP_CLIP_RECT_TIMES = 2;
constexpr int32_t RATING_RESTORE_TIMES = 3;
constexpr int32_t RATING_INVALID_TOUCH_STAR = -1;
constexpr int32_t RATING_INVALID_TOUCH_STAR_2 = 11;
constexpr double RATING_SCORE_2 = 3.0;
constexpr int32_t RATING_RESTORE_TIMES_1 = 1;
constexpr int32_t RATING_SAVE_TIMES_1 = 1;
constexpr int32_t RATING_CLIP_CLIP_RECT_TIMES_1 = 1;
} // namespace

class RatingPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RatingPaintMethodTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void RatingPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: RatingPaintMethodTest001
 * @tc.desc: Test Rating PaintMethod ShouldHighLight
 * @tc.type: FUNC
 */
HWTEST_F(RatingPaintMethodTestNg, RatingPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Rating without parameters.
     */
    RatingModelNG rating;
    rating.Create();
    rating.SetStepSize(DEFAULT_STEP_SIZE);
    rating.SetRatingScore(RATING_SCORE);
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
    EXPECT_CALL(mockCanvas, ClipRoundRect(_, _)).Times(RATING_CLIP_ROUND_RECT_TIMES);
    EXPECT_CALL(mockCanvas, Restore()).Times(RATING_RESTORE_TIMES);
    EXPECT_CALL(mockCanvas, ClipRect(_, _)).Times(RATING_CLIP_CLIP_RECT_TIMES);
    ratingPaintMethod->ratingModifier_->onDraw(context);

    /**
     * @tc.steps: step4. Invoke GetContentDrawFunction to get draw function and execute it when touch star is invalid
     * and ratingScore is integer, which means the secondary image does not draw.
     * @tc.expected: The methods are expected call a preset number of times.
     */
    ratingPaintProperty->UpdateTouchStar(RATING_INVALID_TOUCH_STAR);
    ratingPaintProperty->UpdateRatingScore(RATING_SCORE_2);
    auto* paintWrapper2 = new PaintWrapper(renderContext, geometryNode, ratingPaintProperty);
    ratingPaintMethod->UpdateContentModifier(paintWrapper2);
    EXPECT_EQ(ratingPaintMethod->ratingModifier_->touchStar_->Get(), RATING_INVALID_TOUCH_STAR);
    EXPECT_EQ(ratingPaintMethod->ratingModifier_->drawScore_->Get(), RATING_SCORE_2);
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
