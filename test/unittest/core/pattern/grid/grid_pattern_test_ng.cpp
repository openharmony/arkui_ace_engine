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
#include "grid_test_ng.h"

#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/scrollable/scrollable_utils_test_ng.h"

#include "core/components_ng/base/simplified_inspector.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_utils.h"

namespace OHOS::Ace::NG {
class GridPatternTestNg : public GridTestNg {};

/**
 * @tc.name: ParseArgsTest001
 * @tc.desc: Test Empty String
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, ParseArgsTest001, TestSize.Level1)
{
    // Arrange
    std::string args = "";

    // Act
    std::string result = GridUtils::ParseArgs(args);

    // Assert
    EXPECT_EQ(args, result);
}

/**
 * @tc.name: ParseArgsTest002
 * @tc.desc: Test No Auto Keyword
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, ParseArgsTest002, TestSize.Level1)
{
    // Arrange
    std::string args = "1 2 3";

    // Act
    std::string result = GridUtils::ParseArgs(args);

    // Assert
    EXPECT_EQ(args, result);
}

/**
 * @tc.name: ParseArgsTest003
 * @tc.desc: Test Single Auto Keyword
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, ParseArgsTest003, TestSize.Level1)
{
    // Arrange
    std::string args = "auto";

    // Act
    std::string result = GridUtils::ParseArgs(args);

    // Assert
    EXPECT_EQ(" 1fr", result);
}

/**
 * @tc.name: ParseArgsTest004
 * @tc.desc: Test Multiple Auto Keywords
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, ParseArgsTest004, TestSize.Level1)
{
    // Arrange
    std::string args = "auto 2 auto";

    // Act
    std::string result = GridUtils::ParseArgs(args);

    // Assert
    EXPECT_EQ(" 1fr 2 1fr", result);
}

/**
 * @tc.name: ParseArgsTest005
 * @tc.desc: Test Mixed Args
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, ParseArgsTest005, TestSize.Level1)
{
    // Arrange
    std::string args = "1fr 2 3 auto";

    // Act
    std::string result = GridUtils::ParseArgs(args);

    // Assert
    EXPECT_EQ(" 1fr 2 3 1fr", result);
}

/**
 * @tc.name: ScrollToTagetTest001
 * @tc.desc: Test ScrollToTaget with id in viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, ScrollToTagetTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetCachedCount(2, false);
    CreateItemsInLazyForEach(50, [](uint32_t idx) { return ITEM_MAIN_SIZE; });
    CreateDone();
    auto mockContext = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    mockContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, WIDTH, HEIGHT));
    float targetOffset = 50.0f;
    ScrollAlign align = ScrollAlign::CENTER;
    // No target node
    RefPtr<FrameNode> target;
    EXPECT_EQ(ScrollablePattern::ScrollToTarget(frameNode_, target, targetOffset, align), RET_FAILED);
    // Move index 3 to middle of Grid with targetOffset
    auto child = frameNode_->GetChildByIndex(3);
    ASSERT_NE(child, nullptr);
    auto childNode = child->GetHostNode();
    ASSERT_NE(childNode, nullptr);
    auto mockChildContext = AceType::DynamicCast<MockRenderContext>(childNode->GetRenderContext());
    mockChildContext->SetPaintRectWithTransform(RectF(0.0f, 3 * ITEM_MAIN_SIZE, WIDTH, ITEM_MAIN_SIZE));
    EXPECT_EQ(ScrollablePattern::ScrollToTarget(frameNode_, childNode, targetOffset, align), RET_SUCCESS);
    EXPECT_TRUE(TickPosition(-150.0f));

    // Move index 0 to start of Grid
    align = ScrollAlign::START;
    child = frameNode_->GetChildByIndex(0);
    ASSERT_NE(child, nullptr);
    childNode = child->GetHostNode();
    ASSERT_NE(childNode, nullptr);
    mockChildContext = AceType::DynamicCast<MockRenderContext>(childNode->GetRenderContext());
    mockChildContext->SetPaintRectWithTransform(RectF(0.0f, -150.0f, WIDTH, ITEM_MAIN_SIZE));
    EXPECT_EQ(ScrollablePattern::ScrollToTarget(frameNode_, childNode, 0.0f, align), RET_SUCCESS);
    EXPECT_TRUE(TickPosition(0.0f));
}

/**
 * @tc.name: ScrollToTagetTest002
 * @tc.desc: Test ScrollToTaget from dump
 * @tc.type: FUNC
 */
HWTEST_F(GridPatternTestNg, ScrollToTagetTest002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetCachedCount(2, true);
    CreateItemsInLazyForEach(50, [](uint32_t idx) { return ITEM_MAIN_SIZE; });
    CreateDone();
    auto mockContext = AceType::DynamicCast<MockRenderContext>(frameNode_->GetRenderContext());
    mockContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, WIDTH, HEIGHT));
    float targetOffset = 50.0f;
    ScrollAlign align = ScrollAlign::CENTER;
    // Move index 5 to middle of Grid with targetOffset
    auto child = frameNode_->GetChildByIndex(5);
    ASSERT_NE(child, nullptr);
    auto childNode = child->GetHostNode();
    ASSERT_NE(childNode, nullptr);
    auto mockChildContext = AceType::DynamicCast<MockRenderContext>(childNode->GetRenderContext());
    mockChildContext->SetPaintRectWithTransform(RectF(0.0f, 5 * ITEM_MAIN_SIZE, WIDTH, ITEM_MAIN_SIZE));
    std::vector<std::string> params = { "-element", "-lastpage", std::to_string(childNode->GetId()),
        std::to_string(targetOffset), std::to_string(static_cast<int32_t>(align)) };
    SimplifiedInspector::TestScrollToTarget(params, frameNode_);
    EXPECT_TRUE(TickPosition(-350.0f));
}
} // namespace OHOS::Ace::NG
