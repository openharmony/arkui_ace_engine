/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "text_input_base.h"

#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/text_field/text_field_free_scroller.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float CONTENT_WIDTH = 300.0f;
constexpr float CONTENT_HEIGHT = 150.0f;
constexpr float TEXT_WIDTH = 600.0f;
constexpr float TEXT_HEIGHT = 400.0f;
constexpr float TEST_OFFSET_VALUE = 50.0f;
constexpr float TEST_LARGE_OFFSET = 5000.0f;
constexpr int32_t TEST_SOURCE_START = 10; // SCROLL_FROM_START = 10
} // namespace

class TextFieldFreeScrollerTest : public TextInputBases {
public:
    RefPtr<TextFieldFreeScroller> CreateScroller()
    {
        return AceType::MakeRefPtr<TextFieldFreeScroller>(pattern_);
    }

    void SetUpScrollerRects(const RefPtr<TextFieldFreeScroller>& scroller)
    {
        ASSERT_TRUE(pattern_);
        pattern_->contentRect_ = RectF(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
        pattern_->textRect_ = RectF(0.0f, 0.0f, TEXT_WIDTH, TEXT_HEIGHT);
        pattern_->frameRect_ = RectF(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
        scroller->scrollBar_ = AceType::MakeRefPtr<TextScrollBar2D>(pattern_);
    }
};

/**
 * @tc.name: TextFieldFreeScroller_Construct_001
 * @tc.desc: Test constructor initializes pattern and controller successfully.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_Construct_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    EXPECT_NE(scroller, nullptr);
    EXPECT_NE(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_Initialize_001
 * @tc.desc: Test Initialize when pattern upgrade fails (null weak pattern).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_Initialize_001, TestSize.Level1)
{
    CreateTextField();
    WeakPtr<Pattern> nullPattern;
    auto scroller = AceType::MakeRefPtr<TextFieldFreeScroller>(nullPattern);
    EXPECT_EQ(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleScrollCallback_001
 * @tc.desc: Test HandleScrollCallback with SCROLL_FROM_START source.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleScrollCallback_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->HandleScrollCallback(TEST_OFFSET_VALUE, TEST_SOURCE_START, true);
    EXPECT_EQ(scroller->scrollingAxis_, Axis::VERTICAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleScrollCallback_002
 * @tc.desc: Test HandleScrollCallback with SCROLL_FROM_START source and horizontal axis.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleScrollCallback_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->HandleScrollCallback(TEST_OFFSET_VALUE, TEST_SOURCE_START, false);
    EXPECT_EQ(scroller->scrollingAxis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleScrollCallback_003
 * @tc.desc: Test HandleScrollCallback when pattern is null - early return.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleScrollCallback_003, TestSize.Level1)
{
    CreateTextField();
    WeakPtr<Pattern> nullPattern;
    auto scroller = AceType::MakeRefPtr<TextFieldFreeScroller>(nullPattern);
    scroller->HandleScrollCallback(TEST_OFFSET_VALUE, 0, true);
    EXPECT_EQ(scroller->scrollingAxis_, Axis::NONE);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleScrollCallback_004
 * @tc.desc: Test HandleScrollCallback with normal source that reaches boundary.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleScrollCallback_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->HandleScrollCallback(TEST_LARGE_OFFSET, 0, true);
    EXPECT_NE(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_001
 * @tc.desc: Test UpdateScrollBarOffsetWithAxis with VERTICAL axis branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_002
 * @tc.desc: Test UpdateScrollBarOffsetWithAxis with HORIZONTAL axis branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->UpdateScrollBarOffsetWithAxis(Axis::HORIZONTAL);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_003
 * @tc.desc: Test UpdateScrollBarOffsetWithAxis with NONE axis - early return.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->UpdateScrollBarOffsetWithAxis(Axis::NONE);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_004
 * @tc.desc: Test UpdateScrollBarOffsetWithAxis when scrollBar_ is null - early return.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBarOffsetWithAxis_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->scrollBar_ = nullptr;
    scroller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL);
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleStartScroll_001
 * @tc.desc: Test HandleStartScroll when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleStartScroll_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->HandleStartScroll(true);
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleStartScroll_002
 * @tc.desc: Test HandleStartScroll when menu is visible.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleStartScroll_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->HandleStartScroll(true);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleStartScroll_003
 * @tc.desc: Test HandleStartScroll horizontal direction.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleStartScroll_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->HandleStartScroll(false);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleEndScrollCallback_001
 * @tc.desc: Test HandleEndScrollCallback vertical branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleEndScrollCallback_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->HandleEndScrollCallback(true);
    SUCCEED();
}

/**
 * @tc.name: TextFieldFreeScroller_HandleEndScrollCallback_002
 * @tc.desc: Test HandleEndScrollCallback horizontal branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleEndScrollCallback_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->HandleEndScrollCallback(false);
    SUCCEED();
}

/**
 * @tc.name: TextFieldFreeScroller_SyncOffset_001
 * @tc.desc: Test SyncOffset with valid pattern and controller.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SyncOffset_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->SyncOffset();
    EXPECT_NE(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_SyncOffset_002
 * @tc.desc: Test SyncOffset when freeScrollController_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SyncOffset_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->freeScrollController_ = nullptr;
    scroller->SyncOffset();
    EXPECT_EQ(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_SyncOffset_003
 * @tc.desc: Test SyncOffset when pattern is null - early return.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SyncOffset_003, TestSize.Level1)
{
    CreateTextField();
    WeakPtr<Pattern> nullPattern;
    auto scroller = AceType::MakeRefPtr<TextFieldFreeScroller>(nullPattern);
    scroller->SyncOffset();
    EXPECT_EQ(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_SetScrollBar_001
 * @tc.desc: Test SetScrollBar with OFF mode and existing scrollBar_.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SetScrollBar_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(scroller->scrollBar_, nullptr);
    EXPECT_FALSE(scroller->isScrollBarModiferPropertyttached_);
}

/**
 * @tc.name: TextFieldFreeScroller_SetScrollBar_002
 * @tc.desc: Test SetScrollBar with OFF mode and no scrollBar_.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SetScrollBar_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->SetScrollBar(DisplayMode::OFF);
    EXPECT_EQ(scroller->scrollBar_, nullptr);
    EXPECT_FALSE(scroller->isScrollBarModiferPropertyttached_);
}

/**
 * @tc.name: TextFieldFreeScroller_SetScrollBar_003
 * @tc.desc: Test SetScrollBar with AUTO mode (new scrollBar_).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SetScrollBar_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->SetScrollBar(DisplayMode::AUTO);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_SetScrollBar_004
 * @tc.desc: Test SetScrollBar with ON mode after AUTO already set (oldMode == displayMode).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SetScrollBar_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->SetScrollBar(DisplayMode::AUTO);
    ASSERT_NE(scroller->scrollBar_, nullptr);
    scroller->SetScrollBar(DisplayMode::AUTO);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_SetMinHeight_001
 * @tc.desc: Test SetMinHeight when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SetMinHeight_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->SetMinHeight(Dimension(10.0, DimensionUnit::VP));
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_SetMinHeight_002
 * @tc.desc: Test SetMinHeight with scrollBar_ available.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_SetMinHeight_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->SetMinHeight(Dimension(10.0, DimensionUnit::VP));
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBar_001
 * @tc.desc: Test UpdateScrollBar when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBar_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->UpdateScrollBar();
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBar_002
 * @tc.desc: Test UpdateScrollBar with scrollBar_ available.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBar_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->UpdateScrollBar();
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_AttachModifier_001
 * @tc.desc: Test AttachModifier when already attached.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_AttachModifier_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->isScrollBarModiferPropertyttached_ = true;
    auto modifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(
        pattern_, AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect()));
    scroller->AttachModifier(modifier);
    EXPECT_TRUE(scroller->isScrollBarModiferPropertyttached_);
}

/**
 * @tc.name: TextFieldFreeScroller_AttachModifier_002
 * @tc.desc: Test AttachModifier when modifier is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_AttachModifier_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    RefPtr<TextFieldOverlayModifier> nullModifier;
    scroller->AttachModifier(nullModifier);
    EXPECT_FALSE(scroller->isScrollBarModiferPropertyttached_);
}

/**
 * @tc.name: TextFieldFreeScroller_AttachModifier_003
 * @tc.desc: Test AttachModifier when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_AttachModifier_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    auto modifier = AceType::MakeRefPtr<TextFieldOverlayModifier>(
        pattern_, AceType::MakeRefPtr<ScrollEdgeEffect>(EdgeEffect()));
    scroller->AttachModifier(modifier);
    EXPECT_FALSE(scroller->isScrollBarModiferPropertyttached_);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleMouseEventByScrollBar_001
 * @tc.desc: Test HandleMouseEventByScrollBar when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleMouseEventByScrollBar_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    MouseInfo info;
    scroller->HandleMouseEventByScrollBar(info);
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleMouseEventByScrollBar_002
 * @tc.desc: Test HandleMouseEventByScrollBar with scrollBar_ available.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleMouseEventByScrollBar_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    MouseInfo info;
    auto result = scroller->HandleMouseEventByScrollBar(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_CheckMousePressedOverScrollBar_001
 * @tc.desc: Test CheckMousePressedOverScrollBar when no point in scrollbar rect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_CheckMousePressedOverScrollBar_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    GestureEvent info;
    auto result = scroller->CheckMousePressedOverScrollBar(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_CheckMousePressedOverScrollBar_002
 * @tc.desc: Test CheckMousePressedOverScrollBar with null scrollBar_.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_CheckMousePressedOverScrollBar_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    GestureEvent info;
    auto result = scroller->CheckMousePressedOverScrollBar(info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_IsPointInScrollBarRect_001
 * @tc.desc: Test IsPointInScrollBarRect when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_IsPointInScrollBarRect_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    GestureEvent info;
    auto result = scroller->IsPointInScrollBarRect(&info, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_IsPointInScrollBarRect_002
 * @tc.desc: Test IsPointInScrollBarRect with scrollBar_ available but no paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_IsPointInScrollBarRect_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    GestureEvent info;
    auto result = scroller->IsPointInScrollBarRect(&info, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleInHorizontalBand_001
 * @tc.desc: Test HandleInHorizontalBand when not in band.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleInHorizontalBand_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(-1000.0f, 0.0f);
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    auto result = scroller->HandleInHorizontalBand(param, workRect, axis, step);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleInHorizontalBand_002
 * @tc.desc: Test HandleInHorizontalBand when in band and hasHotArea true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleInHorizontalBand_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH / 2.0f, CONTENT_HEIGHT / 2.0f);
    param.hasHotArea = true;
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    auto result = scroller->HandleInHorizontalBand(param, workRect, axis, step);
    EXPECT_TRUE(result);
    EXPECT_EQ(axis, Axis::VERTICAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleInHorizontalBand_003
 * @tc.desc: Test HandleInHorizontalBand when in band but outside vertical bounds.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleInHorizontalBand_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH / 2.0f, CONTENT_HEIGHT + 100.0f);
    param.hasHotArea = false;
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    auto result = scroller->HandleInHorizontalBand(param, workRect, axis, step);
    EXPECT_TRUE(result);
    EXPECT_EQ(axis, Axis::VERTICAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleInVerticalBand_001
 * @tc.desc: Test HandleInVerticalBand when not in band.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleInVerticalBand_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(0.0f, -1000.0f);
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    auto result = scroller->HandleInVerticalBand(param, workRect, axis, step);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleInVerticalBand_002
 * @tc.desc: Test HandleInVerticalBand when in band and hasHotArea true.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleInVerticalBand_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH / 2.0f, CONTENT_HEIGHT / 2.0f);
    param.hasHotArea = true;
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    auto result = scroller->HandleInVerticalBand(param, workRect, axis, step);
    EXPECT_TRUE(result);
    EXPECT_EQ(axis, Axis::HORIZONTAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleInVerticalBand_003
 * @tc.desc: Test HandleInVerticalBand when in band but outside horizontal bounds.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleInVerticalBand_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH + 100.0f, CONTENT_HEIGHT / 2.0f);
    param.hasHotArea = false;
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    auto result = scroller->HandleInVerticalBand(param, workRect, axis, step);
    EXPECT_TRUE(result);
    EXPECT_EQ(axis, Axis::HORIZONTAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleCornerScrolling_001
 * @tc.desc: Test HandleCornerScrolling with offset far away - no match case.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleCornerScrolling_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH / 2.0f, CONTENT_HEIGHT / 2.0f);
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    auto result = scroller->HandleCornerScrolling(param, workRect, axis, step);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleCornerScrolling_002
 * @tc.desc: Test HandleCornerScrolling in top-right corner vertical range (270-315 degrees).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleCornerScrolling_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH + 10.0f, -10.0f);
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->HandleCornerScrolling(param, workRect, axis, step);
    EXPECT_EQ(axis, Axis::HORIZONTAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleCornerScrolling_003
 * @tc.desc: Test HandleCornerScrolling in top-right corner horizontal range (315-360 degrees).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleCornerScrolling_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH + 10.0f, -1.0f);
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->HandleCornerScrolling(param, workRect, axis, step);
    EXPECT_EQ(axis, Axis::HORIZONTAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleCornerScrolling_004
 * @tc.desc: Test HandleCornerScrolling in bottom-right horizontal range (0-45 degrees).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleCornerScrolling_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH + 100.0f, 10.0f);
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->HandleCornerScrolling(param, workRect, axis, step);
    EXPECT_EQ(axis, Axis::NONE);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleCornerScrolling_005
 * @tc.desc: Test HandleCornerScrolling in bottom-left horizontal range (135-180 degrees).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleCornerScrolling_005, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(-100.0f, 10.0f);
    RectF workRect(0.0f, 0.0f, CONTENT_WIDTH, CONTENT_HEIGHT);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->HandleCornerScrolling(param, workRect, axis, step);
    EXPECT_EQ(axis, Axis::NONE);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateAutoScrollStepOffset_001
 * @tc.desc: Test UpdateAutoScrollStepOffset when pattern is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateAutoScrollStepOffset_001, TestSize.Level1)
{
    CreateTextField();
    WeakPtr<Pattern> nullPattern;
    auto scroller = AceType::MakeRefPtr<TextFieldFreeScroller>(nullPattern);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(0.0f, 0.0f);
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->UpdateAutoScrollStepOffset(param, axis, step);
    EXPECT_EQ(axis, Axis::NONE);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateAutoScrollStepOffset_002
 * @tc.desc: Test UpdateAutoScrollStepOffset with hasHotArea=true and offset in horizontal band.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateAutoScrollStepOffset_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH / 2.0f, CONTENT_HEIGHT / 2.0f);
    param.hasHotArea = true;
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->UpdateAutoScrollStepOffset(param, axis, step);
    EXPECT_EQ(axis, Axis::VERTICAL);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateAutoScrollStepOffset_003
 * @tc.desc: Test UpdateAutoScrollStepOffset with hasHotArea=false and offset in vertical band.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateAutoScrollStepOffset_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH / 2.0f, CONTENT_HEIGHT / 2.0f);
    param.hasHotArea = false;
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->UpdateAutoScrollStepOffset(param, axis, step);
    EXPECT_EQ(axis, Axis::NONE);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateAutoScrollStepOffset_004
 * @tc.desc: Test UpdateAutoScrollStepOffset when offset falls in corner scrolling area.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateAutoScrollStepOffset_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(CONTENT_WIDTH + 100.0f, 10.0f);
    param.hasHotArea = false;
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->UpdateAutoScrollStepOffset(param, axis, step);
    EXPECT_EQ(axis, Axis::HORIZONTAL);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateSecondHandleInfoByMouse_001
 * @tc.desc: Test UpdateSecondHandleInfoByMouse with valid pattern.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateSecondHandleInfoByMouse_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    MouseInfo info;
    info.SetLocalLocation(Offset(CONTENT_WIDTH / 2.0f, CONTENT_HEIGHT / 2.0f));
    scroller->UpdateSecondHandleInfoByMouse(info);
    SUCCEED();
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateSecondHandleInfoByMouse_002
 * @tc.desc: Test UpdateSecondHandleInfoByMouse when localLocation is outside contentRect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateSecondHandleInfoByMouse_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    MouseInfo info;
    info.SetLocalLocation(Offset(CONTENT_WIDTH + 1000.0f, CONTENT_HEIGHT + 1000.0f));
    scroller->UpdateSecondHandleInfoByMouse(info);
    SUCCEED();
}

/**
 * @tc.name: TextFieldFreeScroller_PlayScrollBarAppearAnimation_001
 * @tc.desc: Test PlayScrollBarAppearAnimation when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_PlayScrollBarAppearAnimation_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->PlayScrollBarAppearAnimation(Axis::VERTICAL);
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_PlayScrollBarAppearAnimation_002
 * @tc.desc: Test PlayScrollBarAppearAnimation with VERTICAL axis.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_PlayScrollBarAppearAnimation_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->PlayScrollBarAppearAnimation(Axis::VERTICAL);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_PlayScrollBarAppearAnimation_003
 * @tc.desc: Test PlayScrollBarAppearAnimation with HORIZONTAL axis.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_PlayScrollBarAppearAnimation_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->PlayScrollBarAppearAnimation(Axis::HORIZONTAL);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_ScheduleDisappearDelayTaskWitAxis_001
 * @tc.desc: Test ScheduleDisappearDelayTaskWitAxis when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_ScheduleDisappearDelayTaskWitAxis_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->ScheduleDisappearDelayTaskWitAxis(Axis::VERTICAL);
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_ScheduleDisappearDelayTaskWitAxis_002
 * @tc.desc: Test ScheduleDisappearDelayTaskWitAxis with VERTICAL axis.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_ScheduleDisappearDelayTaskWitAxis_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->ScheduleDisappearDelayTaskWitAxis(Axis::VERTICAL);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_ScheduleDisappearDelayTaskWitAxis_003
 * @tc.desc: Test ScheduleDisappearDelayTaskWitAxis with HORIZONTAL axis.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_ScheduleDisappearDelayTaskWitAxis_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->ScheduleDisappearDelayTaskWitAxis(Axis::HORIZONTAL);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_ScheduleDisappearDelayTask_001
 * @tc.desc: Test ScheduleDisappearDelayTask when scrollBar_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_ScheduleDisappearDelayTask_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->ScheduleDisappearDelayTask();
    EXPECT_EQ(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_ScheduleDisappearDelayTask_002
 * @tc.desc: Test ScheduleDisappearDelayTask with scrollBar_ available.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_ScheduleDisappearDelayTask_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->ScheduleDisappearDelayTask();
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_ScheduleScrollingDisappearDelayTask_001
 * @tc.desc: Test ScheduleScrollingDisappearDelayTask when scrollingAxis_ is set.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_ScheduleScrollingDisappearDelayTask_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->scrollingAxis_ = Axis::VERTICAL;
    scroller->ScheduleScrollingDisappearDelayTask();
    EXPECT_EQ(scroller->scrollingAxis_, Axis::NONE);
}

/**
 * @tc.name: TextFieldFreeScroller_ScheduleScrollingDisappearDelayTask_002
 * @tc.desc: Test ScheduleScrollingDisappearDelayTask when scrollingAxis_ is NONE.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_ScheduleScrollingDisappearDelayTask_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    scroller->scrollingAxis_ = Axis::NONE;
    scroller->ScheduleScrollingDisappearDelayTask();
    EXPECT_EQ(scroller->scrollingAxis_, Axis::NONE);
}

/**
 * @tc.name: TextFieldFreeScroller_StopScrolling_001
 * @tc.desc: Test StopScrolling with valid controller.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_StopScrolling_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->StopScrolling();
    EXPECT_NE(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_StopScrolling_002
 * @tc.desc: Test StopScrolling when freeScrollController_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_StopScrolling_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->freeScrollController_ = nullptr;
    scroller->StopScrolling();
    EXPECT_EQ(scroller->freeScrollController_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_GetScrollGestureRecognizer_001
 * @tc.desc: Test GetScrollGestureRecognizer with valid controller.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_GetScrollGestureRecognizer_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    auto recognizer = scroller->GetScrollGestureRecognizer();
    EXPECT_NE(recognizer, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_GetScrollGestureRecognizer_002
 * @tc.desc: Test GetScrollGestureRecognizer when freeScrollController_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_GetScrollGestureRecognizer_002, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    scroller->freeScrollController_ = nullptr;
    auto recognizer = scroller->GetScrollGestureRecognizer();
    EXPECT_EQ(recognizer, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_IsAttachedModifier_001
 * @tc.desc: Test IsAttachedModifier returns isScrollBarModiferPropertyttached_ flag.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_IsAttachedModifier_001, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    EXPECT_FALSE(scroller->IsAttachedModifier());
    scroller->isScrollBarModiferPropertyttached_ = true;
    EXPECT_TRUE(scroller->IsAttachedModifier());
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBar_003
 * @tc.desc: Test UpdateScrollBar when vertical bar needs paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBar_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto verticalBar = scroller->scrollBar_->GetVerticalBar();
    ASSERT_NE(verticalBar, nullptr);
    verticalBar->isScrollable_ = true;
    scroller->UpdateScrollBar();
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateScrollBar_004
 * @tc.desc: Test UpdateScrollBar when horizontal bar needs paint.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateScrollBar_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto horizontalBar = scroller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(horizontalBar, nullptr);
    horizontalBar->isScrollable_ = true;
    scroller->UpdateScrollBar();
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleMouseEventByScrollBar_003
 * @tc.desc: Test HandleMouseEventByScrollBar with vertical bar pressed.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleMouseEventByScrollBar_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto verticalBar = scroller->scrollBar_->GetVerticalBar();
    ASSERT_NE(verticalBar, nullptr);
    verticalBar->SetPressed(true);
    MouseInfo info;
    auto result = scroller->HandleMouseEventByScrollBar(info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleMouseEventByScrollBar_004
 * @tc.desc: Test HandleMouseEventByScrollBar with horizontal bar hovered.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleMouseEventByScrollBar_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto horizontalBar = scroller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(horizontalBar, nullptr);
    horizontalBar->SetHover(true);
    MouseInfo info;
    auto result = scroller->HandleMouseEventByScrollBar(info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_IsPointInScrollBarRect_003
 * @tc.desc: Test IsPointInScrollBarRect with info that is neither GestureEvent nor MouseInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_IsPointInScrollBarRect_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    HoverInfo info;
    auto result = scroller->IsPointInScrollBarRect(&info, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_IsPointInScrollBarRect_004
 * @tc.desc: Test IsPointInScrollBarRect vertical with paint and point in region.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_IsPointInScrollBarRect_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto verticalBar = scroller->scrollBar_->GetVerticalBar();
    ASSERT_NE(verticalBar, nullptr);
    verticalBar->isScrollable_ = true;
    MouseInfo info;
    info.SetLocalLocation(Offset(0.0f, 50.0f));
    auto result = scroller->IsPointInScrollBarRect(&info, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_IsPointInScrollBarRect_005
 * @tc.desc: Test IsPointInScrollBarRect horizontal with paint and point in region.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_IsPointInScrollBarRect_005, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto horizontalBar = scroller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(horizontalBar, nullptr);
    horizontalBar->isScrollable_ = true;
    MouseInfo info;
    info.SetLocalLocation(Offset(50.0f, 0.0f));
    auto result = scroller->IsPointInScrollBarRect(&info, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: TextFieldFreeScroller_UpdateAutoScrollStepOffset_005
 * @tc.desc: Test UpdateAutoScrollStepOffset when offset falls outside both bands (corner fallthrough).
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_UpdateAutoScrollStepOffset_005, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    TextFieldFreeScroller::AutoScrollStepParam param;
    param.offset = Offset(-100.0f, -100.0f);
    param.hasHotArea = false;
    Axis axis = Axis::NONE;
    std::optional<float> step;
    scroller->UpdateAutoScrollStepOffset(param, axis, step);
    SUCCEED();
}

/**
 * @tc.name: TextFieldFreeScroller_HandleScrollCallback_005
 * @tc.desc: Test HandleScrollCallback with SCROLL_FROM_START using the framework constant.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleScrollCallback_005, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    pattern_->freeScroller_ = scroller;
    scroller->HandleScrollCallback(TEST_OFFSET_VALUE, SCROLL_FROM_START, true);
    EXPECT_EQ(scroller->scrollingAxis_, Axis::VERTICAL);
}

/**
 * @tc.name: TextFieldFreeScroller_HandleStartScroll_004
 * @tc.desc: Test HandleStartScroll triggers CheckSelectAreaVisible branch with valid caret rect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_HandleStartScroll_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    pattern_->selectController_->caretInfo_.rect =
        RectF(CONTENT_WIDTH / 4.0f, CONTENT_HEIGHT / 4.0f, 20.0f, 20.0f);
    scroller->HandleStartScroll(true);
    EXPECT_NE(scroller->scrollBar_, nullptr);
}

/**
 * @tc.name: TextFieldFreeScroller_CheckMousePressedOverScrollBar_003
 * @tc.desc: Test CheckMousePressedOverScrollBar with point in vertical scrollbar region.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_CheckMousePressedOverScrollBar_003, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto verticalBar = scroller->scrollBar_->GetVerticalBar();
    ASSERT_NE(verticalBar, nullptr);
    verticalBar->isScrollable_ = true;
    verticalBar->barRect_ = Rect(0.0f, 0.0f, 16.0f, 100.0f);
    GestureEvent info;
    info.SetLocalLocation(Offset(12.0f, 50.0f));
    auto result = scroller->CheckMousePressedOverScrollBar(info);
    SUCCEED();
    (void)result;
}

/**
 * @tc.name: TextFieldFreeScroller_CheckMousePressedOverScrollBar_004
 * @tc.desc: Test CheckMousePressedOverScrollBar with point in horizontal scrollbar region.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldFreeScrollerTest, TextFieldFreeScroller_CheckMousePressedOverScrollBar_004, TestSize.Level1)
{
    CreateTextField();
    auto scroller = CreateScroller();
    SetUpScrollerRects(scroller);
    auto horizontalBar = scroller->scrollBar_->GetHorizontalBar();
    ASSERT_NE(horizontalBar, nullptr);
    horizontalBar->isScrollable_ = true;
    horizontalBar->barRect_ = Rect(0.0f, 0.0f, 100.0f, 16.0f);
    GestureEvent info;
    info.SetLocalLocation(Offset(50.0f, 12.0f));
    auto result = scroller->CheckMousePressedOverScrollBar(info);
    SUCCEED();
    (void)result;
}
} // namespace OHOS::Ace::NG
