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

#include "custom_layout_options.h"
#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_custom/grid_custom_layout_algorithm.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t FEW_ITEMS_COUNT = 2;
constexpr int32_t MANY_ITEMS_COUNT = 20;
constexpr int32_t CUSTOM_CROSS_COUNT = 2;
constexpr float SMALL_ITEM_SIZE = 50.0f;
}

class GridCustomOverScrollTestNg : public GridTestNg {};

/**
 * @tc.name: GetEndOffset_CustomLayout_AlwaysEnabled_ContentSmallerThanViewport
 * @tc.desc: Test GetEndOffset when userDefined_ is true with alwaysEnabled and content
 *           smaller than viewport, verifying it uses GetHeightInRange path
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetEndOffset_CustomLayout_AlwaysEnabled_ContentSmallerThanViewport,
    TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, ITEM_MAIN_SIZE));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(FEW_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());

    float endOffset = pattern_->GetEndOffset();
    EXPECT_EQ(endOffset, 0.0f);
}

/**
 * @tc.name: GetEndOffset_CustomLayout_ScrollableContent
 * @tc.desc: Test GetEndOffset when userDefined_ is true with scrollable content (content > viewport)
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetEndOffset_CustomLayout_ScrollableContent, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, ITEM_MAIN_SIZE));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(MANY_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    float endOffset = pattern_->GetEndOffset();
    EXPECT_EQ(endOffset, 0.0f);
}

/**
 * @tc.name: GetOverScrollOffset_CustomLayout_AtStart
 * @tc.desc: Test GetOverScrollOffset with custom layout at start position, verifying
 *           it uses GetEndOverScrollIrregular path for end overscroll calculation
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetOverScrollOffset_CustomLayout_AtStart, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, ITEM_MAIN_SIZE));
    CreateFixedItems(MANY_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.end, 0.0f);

    offset = pattern_->GetOverScrollOffset(0.0);
    EXPECT_EQ(offset.start, 0.0f);
    EXPECT_EQ(offset.end, 0.0f);
}

/**
 * @tc.name: GetOverScrollOffset_CustomLayout_AtEnd
 * @tc.desc: Test GetOverScrollOffset with custom layout scrolled to end, verifying
 *           it uses GetEndOverScrollIrregular path
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetOverScrollOffset_CustomLayout_AtEnd, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, ITEM_MAIN_SIZE));
    CreateFixedItems(MANY_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    OverScrollOffset offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, 0.0f);
    EXPECT_EQ(offset.end, -ITEM_MAIN_SIZE);
}

/**
 * @tc.name: GetEndOffset_CustomLayout_WithContentOffsets
 * @tc.desc: Test GetEndOffset with custom layout, alwaysEnabled and contentStartOffset/contentEndOffset
 *           when content is smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetEndOffset_CustomLayout_WithContentOffsets, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, SMALL_ITEM_SIZE));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateFixedItems(FEW_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());

    float endOffset = pattern_->GetEndOffset();
    EXPECT_EQ(endOffset, CONTENT_START_OFFSET);
}

/**
 * @tc.name: GetOverScrollOffset_CustomLayout_AlwaysEnabled_FewItems
 * @tc.desc: Test GetOverScrollOffset when userDefined_ is true with alwaysEnabled and few items,
 *           verifying the end overscroll uses GetEndOverScrollIrregular
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetOverScrollOffset_CustomLayout_AlwaysEnabled_FewItems, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, SMALL_ITEM_SIZE));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(FEW_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());

    OverScrollOffset offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, 0.0f);
    EXPECT_EQ(offset.end, -ITEM_MAIN_SIZE);

    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.end, 0.0f);
}

/**
 * @tc.name: GetEndOffset_CustomLayout_ScrollableWithSpring
 * @tc.desc: Test GetEndOffset with custom layout when using spring effect
 *           and content fills the viewport
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetEndOffset_CustomLayout_ScrollableWithSpring, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, ITEM_MAIN_SIZE));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(MANY_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    float endOffset = pattern_->GetEndOffset();
    EXPECT_EQ(endOffset, 0.0f);
}

/**
 * @tc.name: GetOverScrollOffset_CustomLayout_ContentSmallerThanViewport
 * @tc.desc: Test GetOverScrollOffset with custom layout when content is smaller than viewport,
 *           verifying start overscroll works correctly with userDefined_ path
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetOverScrollOffset_CustomLayout_ContentSmallerThanViewport,
    TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, SMALL_ITEM_SIZE));
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(FEW_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.end, 0.0f);

    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, 0.0f);
    EXPECT_EQ(offset.end, -ITEM_MAIN_SIZE);
}

/**
 * @tc.name: GetOverScrollOffset_CustomLayout_ScrolledToMiddle
 * @tc.desc: Test GetOverScrollOffset with custom layout when scrolled to middle,
 *           verifying no overscroll at start or end
 * @tc.type: FUNC
 */
HWTEST_F(GridCustomOverScrollTestNg, GetOverScrollOffset_CustomLayout_ScrolledToMiddle, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetLayoutOptions(GetRegularDemoOptions(CUSTOM_CROSS_COUNT, ITEM_MAIN_SIZE));
    CreateFixedItems(MANY_ITEMS_COUNT);
    CreateDone();

    EXPECT_TRUE(pattern_->userDefined_);

    ScrollBy(0, ITEM_MAIN_SIZE * 2);
    OverScrollOffset offset = pattern_->GetOverScrollOffset(0.0);
    EXPECT_EQ(offset.start, 0.0f);
    EXPECT_EQ(offset.end, 0.0f);

    offset = pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, 0.0f);
    EXPECT_EQ(offset.end, 0.0f);

    offset = pattern_->GetOverScrollOffset(-ITEM_MAIN_SIZE);
    EXPECT_EQ(offset.start, 0.0f);
    EXPECT_EQ(offset.end, 0.0f);
}
} // namespace OHOS::Ace::NG