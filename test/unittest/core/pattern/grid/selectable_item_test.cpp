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

#include "test/unittest/core/pattern/grid/grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"
#include "core/components_ng/pattern/scrollable/selectable_utils.h"

namespace OHOS::Ace::NG {
class SelectableItemUtilsTestNG : public GridTestNg {};

/**
 * @tc.name: IsSelectedItemNode
 * @tc.desc: Test IsSelectedItemNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectableItemUtilsTestNG, IsSelectedItemNode, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(10);
    CreateDone();

    // Grid item is not selected.
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_FALSE(SelectableUtils::IsSelectedItemNode(gridItemNode));

    // Grid item is selected.
    auto selectableItemPattern = gridItemNode->GetPattern<SelectableItemPattern>();
    selectableItemPattern->SetSelected(true);
    EXPECT_TRUE(SelectableUtils::IsSelectedItemNode(gridItemNode));

    // Non-grid item node.
    EXPECT_FALSE(SelectableUtils::IsSelectedItemNode(frameNode_));

    // Null node.
    EXPECT_FALSE(SelectableUtils::IsSelectedItemNode(nullptr));
}

/**
 * @tc.name: GetVisibleSelectedItems
 * @tc.desc: Test GetVisibleSelectedItems function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectableItemUtilsTestNG, GetVisibleSelectedItems, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(10);
    CreateDone();

    // Grid item is not selected.
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    auto children = SelectableUtils::GetVisibleSelectedItems(gridItemNode);
    EXPECT_TRUE(children.empty());

    // Grid item is selected.
    auto selectableItemPattern = gridItemNode->GetPattern<SelectableItemPattern>();
    selectableItemPattern->SetSelected(true);
    children = SelectableUtils::GetVisibleSelectedItems(gridItemNode);
    EXPECT_EQ(children.size(), 1);
    EXPECT_EQ(children[0], gridItemNode);

    // Non-grid item node.
    children = SelectableUtils::GetVisibleSelectedItems(frameNode_);
    EXPECT_TRUE(children.empty());

    // Null node.
    children = SelectableUtils::GetVisibleSelectedItems(nullptr);
    EXPECT_TRUE(children.empty());
}

/**
 * @tc.name: IsGatherSelectedItemsAnimationEnabled
 * @tc.desc: Test IsGatherSelectedItemsAnimationEnabled function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectableItemUtilsTestNG, IsGatherSelectedItemsAnimationEnabled, TestSize.Level1)
{
    CreateGrid();
    CreateFixedItems(10);
    CreateDone();

    // Grid item is not selected.
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_FALSE(SelectableUtils::IsGatherSelectedItemsAnimationEnabled(gridItemNode));

    // Grid item is selected but animation is disabled.
    auto selectableItemPattern = gridItemNode->GetPattern<SelectableItemPattern>();
    selectableItemPattern->SetSelected(true);
    EXPECT_FALSE(SelectableUtils::IsGatherSelectedItemsAnimationEnabled(gridItemNode));

    // Grid item is selected and animation is enabled.
    EditModeOptions options;
    options.enableGatherSelectedItemsAnimation = true;
    GridModelNG::SetEditModeOptions(AceType::RawPtr(frameNode_), options);
    EXPECT_TRUE(SelectableUtils::IsGatherSelectedItemsAnimationEnabled(gridItemNode));
    EXPECT_TRUE(GridModelNG::GetEditModeOptions(AceType::RawPtr(frameNode_)).enableGatherSelectedItemsAnimation);
}
} // namespace OHOS::Ace::NG