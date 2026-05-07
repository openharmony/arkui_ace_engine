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

#include "grid_test_ng.h"

#include "test/mock/frameworks/core/animation/mock_animation_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
#include "core/components_ng/pattern/grid/grid_item_theme.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/scrollable/selectable_container_pattern.h"
#include "core/components_ng/pattern/scrollable/selectable_item_pattern.h"
#include "core/components_ng/pattern/scrollable/selectable_theme.h"

namespace OHOS::Ace::NG {

class GridItemEditModeTestNg : public GridTestNg {
public:
    void SetUp() override
    {
        GridTestNg::SetUp();
    }
    void TearDown() override
    {
        GridTestNg::TearDown();
    }

    RefPtr<GridItemPattern> GetItemPattern(int32_t index)
    {
        auto child = GetChildFrameNode(frameNode_, index);
        CHECK_NULL_RETURN(child, nullptr);
        return child->GetPattern<GridItemPattern>();
    }

    bool HasCheckBoxNode(int32_t index)
    {
        auto pattern = GetItemPattern(index);
        return pattern ? (pattern->editModeCheckBoxNode_ != nullptr) : false;
    }

    int32_t CountCheckBoxNodes()
    {
        int32_t count = 0;
        auto host = frameNode_;
        CHECK_NULL_RETURN(host, 0);
        for (const auto& child : host->GetChildren()) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (!frameNode) {
                continue;
            }
            auto itemPattern = frameNode->GetPattern<SelectableItemPattern>();
            if (itemPattern && itemPattern->editModeCheckBoxNode_) {
                count++;
            }
        }
        return count;
    }
};

// ============================================================
// Step 7: Theme checkbox shape (T7.1-T7.2)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, GridItemThemeDefaultShape001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<SelectableTheme>();
    EXPECT_EQ(theme->GetEditModeCheckBoxShape(), 0);
}

HWTEST_F(GridItemEditModeTestNg, GridItemThemeGetShape001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<SelectableTheme>();
    theme->editModeCheckBoxShape_ = 1;
    EXPECT_EQ(theme->GetEditModeCheckBoxShape(), 1);
}

// ============================================================
// Step 8.1: Create/Remove CheckBox (T8.1-T8.8)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, CreateEditModeCheckBox001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->SetEditModeEnabled(true);
    EXPECT_NE(itemPattern->editModeCheckBoxNode_, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, CreateEditModeCheckBoxAsChild001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto itemPattern = gridItemNode->GetPattern<GridItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    size_t childCountBefore = gridItemNode->GetChildren().size();
    itemPattern->SetEditModeEnabled(true);

    EXPECT_GT(gridItemNode->GetChildren().size(), childCountBefore);
}

HWTEST_F(GridItemEditModeTestNg, CreateEditModeCheckBoxInitialSyncSelected001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetSelected(true);
    ASSERT_TRUE(itemPattern->IsSelected());

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    auto renderContext = itemPattern->editModeCheckBoxNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, CreateEditModeCheckBoxInitialSyncUnselected001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    ASSERT_FALSE(itemPattern->IsSelected());

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    auto renderContext = itemPattern->editModeCheckBoxNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, RemoveEditModeCheckBox001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->SetEditModeEnabled(false);
    EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, RemoveEditModeCheckBoxRemovesChild001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto itemPattern = gridItemNode->GetPattern<GridItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    size_t childCountWith = gridItemNode->GetChildren().size();
    EXPECT_GT(childCountWith, 0u);

    itemPattern->SetEditModeEnabled(false);
    size_t childCountAfter = gridItemNode->GetChildren().size();
    EXPECT_LT(childCountAfter, childCountWith);
}

HWTEST_F(GridItemEditModeTestNg, RemoveEditModeCheckBoxNoOp001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->SetEditModeEnabled(false));
    EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);
}

// ============================================================
// Step 8.2: SetEditModeEnabled toggle (T8.9-T8.11)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, SetEditModeEnabledTrue001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    EXPECT_NE(itemPattern->editModeCheckBoxNode_, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, SetEditModeEnabledFalse001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->SetEditModeEnabled(false);
    EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, SetEditModeEnabledCycle001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    for (int32_t i = 0; i < 3; ++i) {
        itemPattern->SetEditModeEnabled(true);
        EXPECT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

        itemPattern->SetEditModeEnabled(false);
        EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);
    }
}

// ============================================================
// Step 8.3: Position (T8.12-T8.14)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, CheckBoxPositionBottomRight001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    auto renderContext = itemPattern->editModeCheckBoxNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->UpdateEditModeCheckBoxPosition());
}

HWTEST_F(GridItemEditModeTestNg, CheckBoxPositionNoOp001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->UpdateEditModeCheckBoxPosition());
}

// ============================================================
// Step 8.4: ApplyEditModeToVisibleItems (T8.15-T8.17)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, ApplyEditModeToVisibleItems001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->ApplyEditModeToVisibleItems();

    for (int32_t i = 0; i < 6; ++i) {
        EXPECT_TRUE(HasCheckBoxNode(i)) << "item " << i << " should have CheckBox";
    }
}

HWTEST_F(GridItemEditModeTestNg, RemoveEditModeFromItems001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->ApplyEditModeToVisibleItems();
    EXPECT_EQ(CountCheckBoxNodes(), 6);

    pattern_->RemoveEditModeFromItems();
    EXPECT_EQ(CountCheckBoxNodes(), 0);
}

HWTEST_F(GridItemEditModeTestNg, RemoveEditModeFromItemsNoCrash001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    EXPECT_NO_FATAL_FAILURE(pattern_->RemoveEditModeFromItems());
    EXPECT_EQ(CountCheckBoxNodes(), 0);
}

// ============================================================
// Step 9.1: Item → CheckBox sync (T9.1-T9.5)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, SyncCheckBoxFromItemSelected001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->MarkIsSelected(true);
    ASSERT_TRUE(itemPattern->IsSelected());

    auto renderContext = itemPattern->editModeCheckBoxNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, SyncCheckBoxFromItemDeselected001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->MarkIsSelected(true);
    ASSERT_TRUE(itemPattern->IsSelected());

    itemPattern->MarkIsSelected(false);
    ASSERT_FALSE(itemPattern->IsSelected());
}

HWTEST_F(GridItemEditModeTestNg, SyncCheckBoxFromItemNoCrash001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    ASSERT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->SyncCheckBoxFromItem());
}

HWTEST_F(GridItemEditModeTestNg, MarkIsSelectedSyncsCheckBox001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->MarkIsSelected(true);
    EXPECT_TRUE(itemPattern->IsSelected());
}

HWTEST_F(GridItemEditModeTestNg, MarkIsSelectedSyncsCheckBox002, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->SetSelected(true);
    itemPattern->MarkIsSelected(false);
    EXPECT_FALSE(itemPattern->IsSelected());
}

// ============================================================
// Step 9.2: CheckBox → Item click (T9.6-T9.7)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, CheckBoxClickTogglesSelected001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    ASSERT_FALSE(itemPattern->IsSelected());

    itemPattern->MarkIsSelected(true);
    EXPECT_TRUE(itemPattern->IsSelected());

    itemPattern->MarkIsSelected(false);
    EXPECT_FALSE(itemPattern->IsSelected());
}

// ============================================================
// Step 9.3: Loop prevention (T9.8-T9.9)
// ============================================================

HWTEST_F(GridItemEditModeTestNg, NoLoopOnValueUnchanged001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->SetSelected(true);
    ASSERT_TRUE(itemPattern->IsSelected());

    EXPECT_NO_FATAL_FAILURE(itemPattern->MarkIsSelected(true));
    EXPECT_TRUE(itemPattern->IsSelected());
}

HWTEST_F(GridItemEditModeTestNg, MarkIsSelectedFiresEvent001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    bool eventFired = false;
    bool eventValue = false;
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto eventHub = gridItemNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSelect([&eventFired, &eventValue](bool isSelected) {
        eventFired = true;
        eventValue = isSelected;
    });

    itemPattern->MarkIsSelected(true);
    EXPECT_TRUE(eventFired);
    EXPECT_TRUE(eventValue);
}

HWTEST_F(GridItemEditModeTestNg, MarkIsSelectedNoEventOnSameValue001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    ASSERT_FALSE(itemPattern->IsSelected());

    int32_t eventCount = 0;
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto eventHub = gridItemNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSelect([&eventCount](bool isSelected) {
        eventCount++;
    });

    itemPattern->MarkIsSelected(false);
    EXPECT_EQ(eventCount, 0);
}

// ============================================================
// Refactoring: BeforeCreateLayoutWrapper auto-sync
// ============================================================

HWTEST_F(GridItemEditModeTestNg, BeforeCreateLayoutWrapperAutoCreate001, TestSize.Level0)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    pattern_->SetEnableEditMode(true);
    pattern_->OnModifyDone();
    FlushUITasks();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    EXPECT_NE(itemPattern->editModeCheckBoxNode_, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, BeforeCreateLayoutWrapperAutoRemove001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    pattern_->SetEnableEditMode(false);
    pattern_->OnModifyDone();
    FlushUITasks();

    itemPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);
}

HWTEST_F(GridItemEditModeTestNg, BeforeCreateLayoutWrapperNoParentContainer001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->BeforeCreateLayoutWrapper());
    EXPECT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);
}

// ============================================================
// Refactoring: MarkIsSelectedWithoutCheckbox fires event
// ============================================================

HWTEST_F(GridItemEditModeTestNg, OnEditModeCheckBoxClickFiresEvent001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    bool eventFired = false;
    bool eventValue = false;
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto eventHub = gridItemNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSelect([&eventFired, &eventValue](bool isSelected) {
        eventFired = true;
        eventValue = isSelected;
    });

    itemPattern->MarkIsSelectedWithoutCheckbox(true);
    EXPECT_TRUE(eventFired);
    EXPECT_TRUE(eventValue);
}

HWTEST_F(GridItemEditModeTestNg, OnEditModeCheckBoxClickDeselectFiresEvent001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    itemPattern->SetSelected(true);

    bool eventFired = false;
    bool eventValue = true;
    auto gridItemNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(gridItemNode, nullptr);
    auto eventHub = gridItemNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSelect([&eventFired, &eventValue](bool isSelected) {
        eventFired = true;
        eventValue = isSelected;
    });

    itemPattern->MarkIsSelectedWithoutCheckbox(false);
    EXPECT_TRUE(eventFired);
    EXPECT_FALSE(eventValue);
}

// ============================================================
// Checkbox margin padding (commit: add padding to checkbox)
// ============================================================

/**
 * @tc.name: CheckBoxHasMarginPadding001
 * @tc.desc: Test edit mode checkbox has margin padding applied
 * @tc.type: FUNC
 */
HWTEST_F(GridItemEditModeTestNg, CheckBoxHasMarginPadding001, TestSize.Level1)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);

    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    auto checkboxLayoutProperty = itemPattern->editModeCheckBoxNode_->GetLayoutProperty<LayoutProperty>();
    ASSERT_NE(checkboxLayoutProperty, nullptr);
    const auto& margin = checkboxLayoutProperty->GetMarginProperty();
    ASSERT_NE(margin, nullptr);
    EXPECT_TRUE(margin->left.has_value() || margin->right.has_value()
        || margin->top.has_value() || margin->bottom.has_value());
}

/**
 * @tc.name: CreateEditModeCheckBoxNullHandleNoCrash001
 * @tc.desc: Verify no crash when createCheckboxFrameNode returns null handle.
 *           Tests the null-safety of the full CreateEditModeCheckBox flow.
 * @tc.type: FUNC
 */
HWTEST_F(GridItemEditModeTestNg, CreateEditModeCheckBoxNullHandleNoCrash001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    ASSERT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->CreateEditModeCheckBox());
}

/**
 * @tc.name: UpdateEditModeCheckBoxPositionNoGeometryNoCrash001
 * @tc.desc: Verify no crash when editModeCheckBoxNode_ has null geometry node,
 *           which can happen if checkbox creation partially failed.
 * @tc.type: FUNC
 */
HWTEST_F(GridItemEditModeTestNg, UpdateEditModeCheckBoxPositionNoGeometryNoCrash001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->SetEditModeEnabled(true);
    ASSERT_NE(itemPattern->editModeCheckBoxNode_, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->UpdateEditModeCheckBoxPosition());
}

/**
 * @tc.name: SyncCheckBoxFromItemNoCrashWithoutCheckBox001
 * @tc.desc: Verify SyncCheckBoxFromItem does not crash when editModeCheckBoxNode_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(GridItemEditModeTestNg, SyncCheckBoxFromItemNoCrashWithoutCheckBox001, TestSize.Level2)
{
    auto model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(6);
    CreateDone();

    auto itemPattern = GetItemPattern(0);
    ASSERT_NE(itemPattern, nullptr);
    ASSERT_EQ(itemPattern->editModeCheckBoxNode_, nullptr);

    EXPECT_NO_FATAL_FAILURE(itemPattern->SyncCheckBoxFromItem());
}

} // namespace OHOS::Ace::NG
