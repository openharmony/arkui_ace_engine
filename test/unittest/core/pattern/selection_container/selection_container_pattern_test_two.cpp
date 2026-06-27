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

#define private public
#define protected public

#include "selection_container_test_common.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

/* ==================== RebuildSelectionSpanTypeByFullScan ==================== */

/**
 * @tc.name: RebuildSelectionSpanTypeByFullScan001
 * @tc.desc: Test RebuildSelectionSpanTypeByFullScan with one TEXT child producing TEXT type.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RebuildSelectionSpanTypeByFullScan001, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetSelectionSpanType(TextSpanType::TEXT);
    pattern_->RegisterChild(child1_);
    pattern_->RebuildSelectionSpanTypeByFullScan();
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
    EXPECT_EQ(pattern_->selectedImageCount_, 0);
    EXPECT_EQ(pattern_->selectedBuilderCount_, 0);
    EXPECT_EQ(pattern_->selectedMixedCount_, 0);
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::TEXT);
}

/**
 * @tc.name: RebuildSelectionSpanTypeByFullScan002
 * @tc.desc: Test RebuildSelectionSpanTypeByFullScan with TEXT and IMAGE children producing MIXED.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RebuildSelectionSpanTypeByFullScan002, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetSelectionSpanType(TextSpanType::TEXT);
    child2_->SetSelectionText(SCT_TEST_SELECTION_TEXT2);
    child2_->SetSelectionSpanType(TextSpanType::IMAGE);
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    pattern_->RebuildSelectionSpanTypeByFullScan();
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
    EXPECT_EQ(pattern_->selectedImageCount_, 1);
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::MIXED);
}

/**
 * @tc.name: RebuildSelectionSpanTypeByFullScan003
 * @tc.desc: Test RebuildSelectionSpanTypeByFullScan with empty selection text child.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RebuildSelectionSpanTypeByFullScan003, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_EMPTY_TEXT);
    child1_->SetSelectionSpanType(TextSpanType::TEXT);
    pattern_->RegisterChild(child1_);
    pattern_->RebuildSelectionSpanTypeByFullScan();
    EXPECT_EQ(pattern_->selectedTextCount_, 0);
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::NONE);
}

/**
 * @tc.name: RebuildSelectionSpanTypeByFullScan004
 * @tc.desc: Test RebuildSelectionSpanTypeByFullScan with BUILDER type child.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RebuildSelectionSpanTypeByFullScan004, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetSelectionSpanType(TextSpanType::BUILDER);
    pattern_->RegisterChild(child1_);
    pattern_->RebuildSelectionSpanTypeByFullScan();
    EXPECT_EQ(pattern_->selectedBuilderCount_, 1);
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::BUILDER);
}

/**
 * @tc.name: RebuildSelectionSpanTypeByFullScan005
 * @tc.desc: Test RebuildSelectionSpanTypeByFullScan with MIXED type child.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RebuildSelectionSpanTypeByFullScan005, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetSelectionSpanType(TextSpanType::MIXED);
    pattern_->RegisterChild(child1_);
    pattern_->RebuildSelectionSpanTypeByFullScan();
    EXPECT_EQ(pattern_->selectedMixedCount_, 1);
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::MIXED);
}

/* ==================== OnChildSelectionSpanTypeChanged ==================== */

/**
 * @tc.name: OnChildSelectionSpanTypeChanged001
 * @tc.desc: Test OnChildSelectionSpanTypeChanged transitions from non-contributing to TEXT contributing.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnChildSelectionSpanTypeChanged001, TestSize.Level1)
{
    ChildSelectionSummary oldSummary = { false, TextSpanType::NONE };
    ChildSelectionSummary newSummary = { true, TextSpanType::TEXT };
    pattern_->OnChildSelectionSpanTypeChanged(SCT_TEST_NODE_ID_CHILD1, oldSummary, newSummary);
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::TEXT);
}

/**
 * @tc.name: OnChildSelectionSpanTypeChanged002
 * @tc.desc: Test OnChildSelectionSpanTypeChanged transitions from TEXT contributing to non-contributing.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnChildSelectionSpanTypeChanged002, TestSize.Level1)
{
    ChildSelectionSummary oldSummary = { true, TextSpanType::TEXT };
    ChildSelectionSummary newSummary = { false, TextSpanType::NONE };
    pattern_->selectedTextCount_ = 1;
    pattern_->OnChildSelectionSpanTypeChanged(SCT_TEST_NODE_ID_CHILD1, oldSummary, newSummary);
    EXPECT_EQ(pattern_->selectedTextCount_, 0);
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::NONE);
}

/**
 * @tc.name: OnChildSelectionSpanTypeChanged003
 * @tc.desc: Test OnChildSelectionSpanTypeChanged erases from map when child stops contributing.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnChildSelectionSpanTypeChanged003, TestSize.Level1)
{
    ChildSelectionSummary oldSummary = { true, TextSpanType::IMAGE };
    ChildSelectionSummary newSummary = { false, TextSpanType::NONE };
    pattern_->childSelectionSummaryMap_[SCT_TEST_NODE_ID_CHILD1] = oldSummary;
    pattern_->OnChildSelectionSpanTypeChanged(SCT_TEST_NODE_ID_CHILD1, oldSummary, newSummary);
    EXPECT_EQ(pattern_->childSelectionSummaryMap_.count(SCT_TEST_NODE_ID_CHILD1), 0);
}

/**
 * @tc.name: OnChildSelectionSpanTypeChanged004
 * @tc.desc: Test OnChildSelectionSpanTypeChanged inserts in map when child starts contributing.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnChildSelectionSpanTypeChanged004, TestSize.Level1)
{
    ChildSelectionSummary oldSummary = { false, TextSpanType::NONE };
    ChildSelectionSummary newSummary = { true, TextSpanType::BUILDER };
    pattern_->OnChildSelectionSpanTypeChanged(SCT_TEST_NODE_ID_CHILD1, oldSummary, newSummary);
    EXPECT_EQ(pattern_->childSelectionSummaryMap_.count(SCT_TEST_NODE_ID_CHILD1), 1);
    EXPECT_EQ(pattern_->selectedBuilderCount_, 1);
}

/* ==================== ApplySelectionSummaryDelta ==================== */

/**
 * @tc.name: ApplySelectionSummaryDelta001
 * @tc.desc: Test ApplySelectionSummaryDelta with non-contributing summary is a no-op.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta001, TestSize.Level1)
{
    ChildSelectionSummary summary = { false, TextSpanType::TEXT };
    pattern_->ApplySelectionSummaryDelta(summary, 1);
    EXPECT_EQ(pattern_->selectedTextCount_, 0);
}

/**
 * @tc.name: ApplySelectionSummaryDelta002
 * @tc.desc: Test ApplySelectionSummaryDelta increments TEXT count.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta002, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::TEXT };
    pattern_->ApplySelectionSummaryDelta(summary, 1);
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
}

/**
 * @tc.name: ApplySelectionSummaryDelta003
 * @tc.desc: Test ApplySelectionSummaryDelta increments IMAGE count.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta003, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::IMAGE };
    pattern_->ApplySelectionSummaryDelta(summary, 1);
    EXPECT_EQ(pattern_->selectedImageCount_, 1);
}

/**
 * @tc.name: ApplySelectionSummaryDelta004
 * @tc.desc: Test ApplySelectionSummaryDelta increments BUILDER count.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta004, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::BUILDER };
    pattern_->ApplySelectionSummaryDelta(summary, 1);
    EXPECT_EQ(pattern_->selectedBuilderCount_, 1);
}

/**
 * @tc.name: ApplySelectionSummaryDelta005
 * @tc.desc: Test ApplySelectionSummaryDelta increments MIXED count.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta005, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::MIXED };
    pattern_->ApplySelectionSummaryDelta(summary, 1);
    EXPECT_EQ(pattern_->selectedMixedCount_, 1);
}

/**
 * @tc.name: ApplySelectionSummaryDelta006
 * @tc.desc: Test ApplySelectionSummaryDelta decrements TEXT count and clamps to 0.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta006, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::TEXT };
    pattern_->selectedTextCount_ = 1;
    pattern_->ApplySelectionSummaryDelta(summary, -1);
    EXPECT_EQ(pattern_->selectedTextCount_, 0);
}

/**
 * @tc.name: ApplySelectionSummaryDelta007
 * @tc.desc: Test ApplySelectionSummaryDelta with NONE type increments TEXT count.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta007, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::NONE };
    pattern_->ApplySelectionSummaryDelta(summary, 1);
    EXPECT_EQ(pattern_->selectedTextCount_, 1);
}

/**
 * @tc.name: ApplySelectionSummaryDelta008
 * @tc.desc: Test ApplySelectionSummaryDelta clamps IMAGE count to 0 when delta goes negative.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta008, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::IMAGE };
    pattern_->ApplySelectionSummaryDelta(summary, -1);
    EXPECT_EQ(pattern_->selectedImageCount_, 0);
}

/**
 * @tc.name: ApplySelectionSummaryDelta009
 * @tc.desc: Test ApplySelectionSummaryDelta clamps BUILDER count to 0 when delta goes negative.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta009, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::BUILDER };
    pattern_->ApplySelectionSummaryDelta(summary, -1);
    EXPECT_EQ(pattern_->selectedBuilderCount_, 0);
}

/**
 * @tc.name: ApplySelectionSummaryDelta010
 * @tc.desc: Test ApplySelectionSummaryDelta clamps MIXED count to 0 when delta goes negative.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ApplySelectionSummaryDelta010, TestSize.Level1)
{
    ChildSelectionSummary summary = { true, TextSpanType::MIXED };
    pattern_->ApplySelectionSummaryDelta(summary, -1);
    EXPECT_EQ(pattern_->selectedMixedCount_, 0);
}

/* ==================== RecomputeSelectedTypeFromSummary ==================== */

/**
 * @tc.name: RecomputeSelectedTypeFromSummary001
 * @tc.desc: Test RecomputeSelectedTypeFromSummary when only text count > 0 sets TEXT.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RecomputeSelectedTypeFromSummary001, TestSize.Level1)
{
    pattern_->selectedTextCount_ = 1;
    pattern_->selectedImageCount_ = 0;
    pattern_->selectedBuilderCount_ = 0;
    pattern_->selectedMixedCount_ = 0;
    pattern_->RecomputeSelectedTypeFromSummary();
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::TEXT);
}

/**
 * @tc.name: RecomputeSelectedTypeFromSummary002
 * @tc.desc: Test RecomputeSelectedTypeFromSummary when only image count > 0 sets IMAGE.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RecomputeSelectedTypeFromSummary002, TestSize.Level1)
{
    pattern_->selectedTextCount_ = 0;
    pattern_->selectedImageCount_ = 1;
    pattern_->selectedBuilderCount_ = 0;
    pattern_->selectedMixedCount_ = 0;
    pattern_->RecomputeSelectedTypeFromSummary();
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::IMAGE);
}

/**
 * @tc.name: RecomputeSelectedTypeFromSummary003
 * @tc.desc: Test RecomputeSelectedTypeFromSummary when only builder count > 0 sets BUILDER.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RecomputeSelectedTypeFromSummary003, TestSize.Level1)
{
    pattern_->selectedTextCount_ = 0;
    pattern_->selectedImageCount_ = 0;
    pattern_->selectedBuilderCount_ = 1;
    pattern_->selectedMixedCount_ = 0;
    pattern_->RecomputeSelectedTypeFromSummary();
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::BUILDER);
}

/**
 * @tc.name: RecomputeSelectedTypeFromSummary004
 * @tc.desc: Test RecomputeSelectedTypeFromSummary when text+image > 0 sets MIXED.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RecomputeSelectedTypeFromSummary004, TestSize.Level1)
{
    pattern_->selectedTextCount_ = 1;
    pattern_->selectedImageCount_ = 1;
    pattern_->selectedBuilderCount_ = 0;
    pattern_->selectedMixedCount_ = 0;
    pattern_->RecomputeSelectedTypeFromSummary();
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::MIXED);
}

/**
 * @tc.name: RecomputeSelectedTypeFromSummary005
 * @tc.desc: Test RecomputeSelectedTypeFromSummary when all counts are 0 sets NONE.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RecomputeSelectedTypeFromSummary005, TestSize.Level1)
{
    pattern_->selectedTextCount_ = 0;
    pattern_->selectedImageCount_ = 0;
    pattern_->selectedBuilderCount_ = 0;
    pattern_->selectedMixedCount_ = 0;
    pattern_->RecomputeSelectedTypeFromSummary();
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::NONE);
}

/**
 * @tc.name: RecomputeSelectedTypeFromSummary006
 * @tc.desc: Test RecomputeSelectedTypeFromSummary when selectedMixedCount_ > 0 takes priority.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RecomputeSelectedTypeFromSummary006, TestSize.Level1)
{
    pattern_->selectedTextCount_ = 1;
    pattern_->selectedImageCount_ = 0;
    pattern_->selectedBuilderCount_ = 0;
    pattern_->selectedMixedCount_ = 1;
    pattern_->RecomputeSelectedTypeFromSummary();
    EXPECT_EQ(pattern_->selectedType_.value(), TextSpanType::MIXED);
}

/* ==================== IsSelectedTypeChange ==================== */

/**
 * @tc.name: IsSelectedTypeChange001
 * @tc.desc: Test IsSelectedTypeChange returns true when types differ.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsSelectedTypeChange001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::IMAGE;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    EXPECT_TRUE(pattern_->IsSelectedTypeChange());
}

/**
 * @tc.name: IsSelectedTypeChange002
 * @tc.desc: Test IsSelectedTypeChange returns false when types are the same.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsSelectedTypeChange002, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::TEXT;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    EXPECT_FALSE(pattern_->IsSelectedTypeChange());
}

/**
 * @tc.name: IsSelectedTypeChange003
 * @tc.desc: Test IsSelectedTypeChange returns false when selectedType_ has no value.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsSelectedTypeChange003, TestSize.Level1)
{
    pattern_->selectedType_ = std::nullopt;
    EXPECT_FALSE(pattern_->IsSelectedTypeChange());
}

/* ==================== CheckSelectedTypeChange ==================== */

/**
 * @tc.name: CheckSelectedTypeChange001
 * @tc.desc: Test CheckSelectedTypeChange returns true and updates oldSelectedType_ when changed.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CheckSelectedTypeChange001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::IMAGE;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    auto result = pattern_->CheckSelectedTypeChange();
    EXPECT_TRUE(result);
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: CheckSelectedTypeChange002
 * @tc.desc: Test CheckSelectedTypeChange returns false and does not update when not changed.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CheckSelectedTypeChange002, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::TEXT;
    pattern_->oldSelectedType_ = TextSpanType::TEXT;
    auto result = pattern_->CheckSelectedTypeChange();
    EXPECT_FALSE(result);
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::TEXT);
}

/* ==================== SaveOldSelectedType ==================== */

/**
 * @tc.name: SaveOldSelectedType001
 * @tc.desc: Test SaveOldSelectedType stores current selected type value.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, SaveOldSelectedType001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::IMAGE;
    pattern_->SaveOldSelectedType();
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: SaveOldSelectedType002
 * @tc.desc: Test SaveOldSelectedType stores NONE when selectedType_ has no value.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, SaveOldSelectedType002, TestSize.Level1)
{
    pattern_->selectedType_ = std::nullopt;
    pattern_->SaveOldSelectedType();
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::NONE);
}

/* ==================== GetCopyOption ==================== */

/**
 * @tc.name: GetCopyOption001
 * @tc.desc: Test GetCopyOption returns default InApp when no property is set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetCopyOption001, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetCopyOption(), CopyOptions::InApp);
}

/**
 * @tc.name: GetCopyOption002
 * @tc.desc: Test GetCopyOption returns value from layout property.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetCopyOption002, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOption(CopyOptions::Distributed);
    EXPECT_EQ(pattern_->GetCopyOption(), CopyOptions::Distributed);
}

/* ==================== GetSelectedBackgroundColor ==================== */

/**
 * @tc.name: GetSelectedBackgroundColor001
 * @tc.desc: Test GetSelectedBackgroundColor returns nullopt when no property is set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetSelectedBackgroundColor001, TestSize.Level1)
{
    auto result = pattern_->GetSelectedBackgroundColor();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: GetSelectedBackgroundColor002
 * @tc.desc: Test GetSelectedBackgroundColor returns the color from the layout property.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetSelectedBackgroundColor002, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSelectedBackgroundColor(SCT_TEST_SELECTED_BG_COLOR);
    auto result = pattern_->GetSelectedBackgroundColor();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), SCT_TEST_SELECTED_BG_COLOR);
}

/* ==================== OnModifyDone ==================== */

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone initializes key event when copy option is not None.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOption(CopyOptions::InApp);
    pattern_->hasModifyDone_ = false;
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->hasModifyDone_);
    EXPECT_TRUE(pattern_->keyEventInitialized_);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone initializes key event when HasSelectableText is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->hasModifyDone_ = false;
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->hasModifyDone_);
    EXPECT_TRUE(pattern_->keyEventInitialized_);
}

/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Test OnModifyDone notifies pending property updates after first modify done.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnModifyDone003, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->hasModifyDone_ = true;
    uint32_t flags = static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR);
    pattern_->pendingContainerPropertyUpdateFlags_ = flags;
    child1_->ResetPropertyUpdated();
    pattern_->OnModifyDone();
    EXPECT_TRUE(child1_->GetPropertyUpdated());
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, 0);
}

/**
 * @tc.name: OnModifyDone004
 * @tc.desc: Test OnModifyDone with CopyOptions::None and no selectable text does not init key event.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnModifyDone004, TestSize.Level1)
{
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOption(CopyOptions::None);
    pattern_->hasModifyDone_ = false;
    pattern_->keyEventInitialized_ = false;
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->hasModifyDone_);
    EXPECT_FALSE(pattern_->keyEventInitialized_);
}

/* ==================== InitKeyEvent ==================== */

/**
 * @tc.name: InitKeyEvent001
 * @tc.desc: Test InitKeyEvent is skipped when already initialized.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, InitKeyEvent001, TestSize.Level1)
{
    pattern_->keyEventInitialized_ = true;
    pattern_->InitKeyEvent();
    EXPECT_TRUE(pattern_->keyEventInitialized_);
}

/**
 * @tc.name: InitKeyEvent002
 * @tc.desc: Test InitKeyEvent sets focus hub key event callback and marks initialized.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, InitKeyEvent002, TestSize.Level1)
{
    pattern_->keyEventInitialized_ = false;
    pattern_->InitKeyEvent();
    EXPECT_TRUE(pattern_->keyEventInitialized_);
}

/* ==================== HandleKeyEvent ==================== */

/**
 * @tc.name: HandleKeyEvent001
 * @tc.desc: Test HandleKeyEvent returns false for non-DOWN action.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleKeyEvent001, TestSize.Level1)
{
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    auto result = pattern_->HandleKeyEvent(keyEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleKeyEvent002
 * @tc.desc: Test HandleKeyEvent returns false for an unrelated key down event.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleKeyEvent002, TestSize.Level1)
{
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_B;
    auto result = pattern_->HandleKeyEvent(keyEvent);
    EXPECT_FALSE(result);
}

/* ==================== MarkContainerPropertyUpdate ==================== */

/**
 * @tc.name: MarkContainerPropertyUpdate001
 * @tc.desc: Test MarkContainerPropertyUpdate sets the pending flags.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, MarkContainerPropertyUpdate001, TestSize.Level1)
{
    uint32_t flags = static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION);
    pattern_->MarkContainerPropertyUpdate(flags);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, flags);
}

/**
 * @tc.name: MarkContainerPropertyUpdate002
 * @tc.desc: Test MarkContainerPropertyUpdate accumulates flags with OR.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, MarkContainerPropertyUpdate002, TestSize.Level1)
{
    uint32_t flags1 = static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION);
    uint32_t flags2 = static_cast<uint32_t>(SelectionContainerPropertyChange::ENABLE_HAPTIC_FEEDBACK);
    pattern_->MarkContainerPropertyUpdate(flags1);
    pattern_->MarkContainerPropertyUpdate(flags2);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, flags1 | flags2);
}

/* ==================== UpdatePropertyImpl ==================== */

/**
 * @tc.name: UpdatePropertyImpl001
 * @tc.desc: Test UpdatePropertyImpl updates caret color property.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdatePropertyImpl001, TestSize.Level1)
{
    auto propertyValue = AceType::MakeRefPtr<PropertyValueBase>();
    propertyValue->SetValue(SCT_TEST_CARET_COLOR);
    pattern_->UpdatePropertyImpl("SelectionContainerCaretColor", propertyValue);
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto caretColor = layoutProperty->GetCaretColorValue(Color::TRANSPARENT);
    EXPECT_EQ(caretColor, SCT_TEST_CARET_COLOR);
}

/**
 * @tc.name: UpdatePropertyImpl002
 * @tc.desc: Test UpdatePropertyImpl updates selected background color and marks property update.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdatePropertyImpl002, TestSize.Level1)
{
    auto propertyValue = AceType::MakeRefPtr<PropertyValueBase>();
    propertyValue->SetValue(SCT_TEST_SELECTED_BG_COLOR);
    pattern_->UpdatePropertyImpl("SelectionContainerSelectedBackgroundColor", propertyValue);
    auto layoutProperty = containerNode_->GetLayoutProperty<SelectionContainerLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto bgColor = layoutProperty->GetSelectedBackgroundColor();
    EXPECT_TRUE(bgColor.has_value());
    EXPECT_EQ(bgColor.value(), SCT_TEST_SELECTED_BG_COLOR);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_,
        static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR));
}

/**
 * @tc.name: UpdatePropertyImpl003
 * @tc.desc: Test UpdatePropertyImpl with unknown key does not change properties.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdatePropertyImpl003, TestSize.Level1)
{
    auto propertyValue = AceType::MakeRefPtr<PropertyValueBase>();
    propertyValue->SetValue(SCT_TEST_CARET_COLOR);
    pattern_->UpdatePropertyImpl("UnknownKey", propertyValue);
    EXPECT_EQ(pattern_->pendingContainerPropertyUpdateFlags_, 0);
}

/* ==================== HandleOnSelectAll ==================== */

/**
 * @tc.name: HandleOnSelectAll001
 * @tc.desc: Test HandleOnSelectAll selects all children with selectable text.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnSelectAll001, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->HandleOnSelectAll();
    EXPECT_TRUE(child1_->IsSelectAll());
    EXPECT_TRUE(child1_->GetHandleInfoUpdated());
    EXPECT_EQ(pattern_->GetSelectionStartChild(), child1_);
    EXPECT_EQ(pattern_->GetSelectionEndChild(), child1_);
}

/**
 * @tc.name: HandleOnSelectAll002
 * @tc.desc: Test HandleOnSelectAll with multiple children sets first and last selection children.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnSelectAll002, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    child2_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    pattern_->HandleOnSelectAll();
    EXPECT_TRUE(child1_->IsSelectAll());
    EXPECT_TRUE(child2_->IsSelectAll());
    EXPECT_EQ(pattern_->GetSelectionStartChild(), child1_);
    EXPECT_EQ(pattern_->GetSelectionEndChild(), child2_);
}

/**
 * @tc.name: HandleOnSelectAll003
 * @tc.desc: Test HandleOnSelectAll with child that has no selectable text calls SelectTextByIndex(-1,-1).
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnSelectAll003, TestSize.Level1)
{
    child1_->SetHasSelectableText(false);
    pattern_->RegisterChild(child1_);
    pattern_->HandleOnSelectAll();
    auto indexes = child1_->GetSelectionIndexes();
    EXPECT_EQ(indexes.startIndex, -1);
    EXPECT_EQ(indexes.endIndex, -1);
}

/**
 * @tc.name: HandleOnSelectAll004
 * @tc.desc: Test HandleOnSelectAll resets origin caret position on all children.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnSelectAll004, TestSize.Level1)
{
    child1_->SetHasSelectableText(true);
    child2_->SetHasSelectableText(true);
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    pattern_->HandleOnSelectAll();
    EXPECT_TRUE(child1_->GetCaretPositionReset());
    EXPECT_TRUE(child2_->GetCaretPositionReset());
}

/* ==================== BindSelectionMenu ==================== */

/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: Test BindSelectionMenu adds menu params and can be retrieved.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, BindSelectionMenu001, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = true;
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    ASSERT_NE(menuParams, nullptr);
    EXPECT_TRUE(menuParams->isValid);
}

/**
 * @tc.name: BindSelectionMenu002
 * @tc.desc: Test BindSelectionMenu removes menu when builder is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, BindSelectionMenu002, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    std::function<void()> nullBuilder = nullptr;
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, nullBuilder, menuParam);
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_EQ(menuParams, nullptr);
}

/**
 * @tc.name: BindSelectionMenu003
 * @tc.desc: Test BindSelectionMenu updates existing entry with new builder.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, BindSelectionMenu003, TestSize.Level1)
{
    bool builder1Called = false;
    std::function<void()> menuBuilder1 = [&builder1Called]() { builder1Called = true; };
    SelectMenuParam menuParam;
    menuParam.isValid = true;
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder1, menuParam);
    bool builder2Called = false;
    std::function<void()> menuBuilder2 = [&builder2Called]() { builder2Called = true; };
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder2, menuParam);
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    ASSERT_NE(menuParams, nullptr);
    ASSERT_NE(menuParams->buildFunc, nullptr);
    menuParams->buildFunc();
    EXPECT_TRUE(builder2Called);
    EXPECT_FALSE(builder1Called);
}

/* ==================== GetMenuParams ==================== */

/**
 * @tc.name: GetMenuParams001
 * @tc.desc: Test GetMenuParams returns nullptr when not found.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetMenuParams001, TestSize.Level1)
{
    auto menuParams = pattern_->GetMenuParams(TextSpanType::IMAGE, TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_EQ(menuParams, nullptr);
}

/**
 * @tc.name: GetMenuParams002
 * @tc.desc: Test GetMenuParams falls back to NONE response type.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetMenuParams002, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::NONE, menuBuilder, menuParam);
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    ASSERT_NE(menuParams, nullptr);
}

/**
 * @tc.name: GetMenuParams003
 * @tc.desc: Test GetMenuParams falls back to NONE span type when spanType != NONE.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetMenuParams003, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    pattern_->BindSelectionMenu(TextSpanType::NONE, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    ASSERT_NE(menuParams, nullptr);
}

/**
 * @tc.name: GetMenuParams004
 * @tc.desc: Test GetMenuParams falls back to {NONE, NONE} when spanType != NONE.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetMenuParams004, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    pattern_->BindSelectionMenu(TextSpanType::NONE, TextResponseType::NONE, menuBuilder, menuParam);
    auto menuParams = pattern_->GetMenuParams(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    ASSERT_NE(menuParams, nullptr);
}

/* ==================== IsSelectedBindSelectionMenu ==================== */

/**
 * @tc.name: IsSelectedBindSelectionMenu001
 * @tc.desc: Test IsSelectedBindSelectionMenu returns false when no menu is bound.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsSelectedBindSelectionMenu001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::TEXT;
    EXPECT_FALSE(pattern_->IsSelectedBindSelectionMenu());
}

/**
 * @tc.name: IsSelectedBindSelectionMenu002
 * @tc.desc: Test IsSelectedBindSelectionMenu returns true when a menu is bound for the type.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsSelectedBindSelectionMenu002, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = true;
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE, menuBuilder, menuParam);
    pattern_->selectedType_ = TextSpanType::TEXT;
    EXPECT_TRUE(pattern_->IsSelectedBindSelectionMenu());
}

/* ==================== OnHandleSelectionMenuCallback ==================== */

/**
 * @tc.name: OnHandleSelectionMenuCallback001
 * @tc.desc: Test OnHandleSelectionMenuCallback MENU_SHOW with onMenuShowWithText invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnHandleSelectionMenuCallback001, TestSize.Level1)
{
    auto menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, std::function<void()>(), nullptr, nullptr, TextResponseType::NONE);
    bool callbackCalled = false;
    menuParams->onMenuShowWithText = [&callbackCalled](const std::u16string& text) { callbackCalled = true; };
    pattern_->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_SHOW, menuParams);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: OnHandleSelectionMenuCallback002
 * @tc.desc: Test OnHandleSelectionMenuCallback MENU_HIDE with onMenuHideWithText invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnHandleSelectionMenuCallback002, TestSize.Level1)
{
    auto menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, std::function<void()>(), nullptr, nullptr, TextResponseType::NONE);
    bool callbackCalled = false;
    menuParams->onMenuHideWithText = [&callbackCalled](const std::u16string& text) { callbackCalled = true; };
    pattern_->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_HIDE, menuParams);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: OnHandleSelectionMenuCallback003
 * @tc.desc: Test OnHandleSelectionMenuCallback MENU_APPEAR with onAppearWithText invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnHandleSelectionMenuCallback003, TestSize.Level1)
{
    auto menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, std::function<void()>(), nullptr, nullptr, TextResponseType::NONE);
    bool callbackCalled = false;
    menuParams->onAppearWithText = [&callbackCalled](const std::u16string& text) { callbackCalled = true; };
    pattern_->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_APPEAR, menuParams);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: OnHandleSelectionMenuCallback004
 * @tc.desc: Test OnHandleSelectionMenuCallback MENU_SHOW with onMenuShow (no WithText) invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnHandleSelectionMenuCallback004, TestSize.Level1)
{
    auto menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, std::function<void()>(), nullptr, nullptr, TextResponseType::NONE);
    bool callbackCalled = false;
    menuParams->onMenuShow = [&callbackCalled](int32_t start, int32_t end) { callbackCalled = true; };
    pattern_->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_SHOW, menuParams);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: OnHandleSelectionMenuCallback005
 * @tc.desc: Test OnHandleSelectionMenuCallback MENU_HIDE with onMenuHide (no WithText) invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnHandleSelectionMenuCallback005, TestSize.Level1)
{
    auto menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, std::function<void()>(), nullptr, nullptr, TextResponseType::NONE);
    bool callbackCalled = false;
    menuParams->onMenuHide = [&callbackCalled](int32_t start, int32_t end) { callbackCalled = true; };
    pattern_->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_HIDE, menuParams);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: OnHandleSelectionMenuCallback006
 * @tc.desc: Test OnHandleSelectionMenuCallback MENU_APPEAR with onAppear (no WithText) invokes callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnHandleSelectionMenuCallback006, TestSize.Level1)
{
    auto menuParams = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, std::function<void()>(), nullptr, nullptr, TextResponseType::NONE);
    bool callbackCalled = false;
    menuParams->onAppear = [&callbackCalled](int32_t start, int32_t end) { callbackCalled = true; };
    pattern_->OnHandleSelectionMenuCallback(SelectionMenuCalblackId::MENU_APPEAR, menuParams);
    EXPECT_TRUE(callbackCalled);
}

/* ==================== SetSelectionMenuItemClickWithTextCallback ==================== */

/**
 * @tc.name: SetSelectionMenuItemClickWithText001
 * @tc.desc: Test SetSelectionMenuItemClickWithTextCallback stores the callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, SetSelectionMenuItemClickWithText001, TestSize.Level1)
{
    std::function<bool(const MenuItemParam&, const std::u16string&)> callback =
        [](const MenuItemParam& param, const std::u16string& text) { return true; };
    pattern_->SetSelectionMenuItemClickWithTextCallback(std::move(callback));
    EXPECT_TRUE(pattern_->onMenuItemClickWithText_ != nullptr);
}

/* ==================== CopySelectionMenuParams ==================== */

/**
 * @tc.name: CopySelectionMenuParams001
 * @tc.desc: Test CopySelectionMenuParams returns early when menuParams is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CopySelectionMenuParams001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    pattern_->CopySelectionMenuParams(selectInfo);
    EXPECT_FALSE(selectInfo.menuInfo.menuBuilder);
}

/**
 * @tc.name: CopySelectionMenuParams002
 * @tc.desc: Test CopySelectionMenuParams returns early when isValid is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CopySelectionMenuParams002, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = false;
    pattern_->BindSelectionMenu(TextSpanType::TEXT, TextResponseType::NONE, menuBuilder, menuParam);
    pattern_->selectedType_ = TextSpanType::TEXT;
    SelectOverlayInfo selectInfo;
    pattern_->CopySelectionMenuParams(selectInfo);
    EXPECT_FALSE(selectInfo.menuInfo.menuBuilder);
}

/**
 * @tc.name: CopySelectionMenuParams003
 * @tc.desc: Test CopySelectionMenuParams sets menuBuilder and callbacks when menu is valid.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CopySelectionMenuParams003, TestSize.Level1)
{
    std::function<void()> menuBuilder = []() {};
    SelectMenuParam menuParam;
    menuParam.isValid = true;
    pattern_->BindSelectionMenu(TextSpanType::NONE, TextResponseType::NONE, menuBuilder, menuParam);
    pattern_->selectedType_ = TextSpanType::NONE;
    SelectOverlayInfo selectInfo;
    pattern_->CopySelectionMenuParams(selectInfo);
    EXPECT_TRUE(selectInfo.menuInfo.menuBuilder);
    EXPECT_TRUE(selectInfo.menuCallback.onAppear);
    EXPECT_TRUE(selectInfo.menuCallback.onMenuShow);
    EXPECT_TRUE(selectInfo.menuCallback.onMenuHide);
}

/* ==================== CollectDescendantChangeFlags ==================== */

/**
 * @tc.name: CollectDescendantChangeFlags001
 * @tc.desc: Test CollectDescendantChangeFlags returns NONE when no children registered.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CollectDescendantChangeFlags001, TestSize.Level1)
{
    auto flags = pattern_->CollectDescendantChangeFlags();
    EXPECT_EQ(flags, FRAME_NODE_CHANGE_INFO_NONE);
}

/**
 * @tc.name: CollectDescendantChangeFlags002
 * @tc.desc: Test CollectDescendantChangeFlags returns NONE when children have no change flags.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CollectDescendantChangeFlags002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    childNode1_->changeInfoFlag_ = FRAME_NODE_CHANGE_INFO_NONE;
    auto flags = pattern_->CollectDescendantChangeFlags();
    EXPECT_EQ(flags, FRAME_NODE_CHANGE_INFO_NONE);
}

/* ==================== CollectFlagsFromChildToHost ==================== */

/**
 * @tc.name: CollectFlagsFromChildToHost001
 * @tc.desc: Test CollectFlagsFromChildToHost returns child flag when child is direct ancestor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CollectFlagsFromChildToHost001, TestSize.Level1)
{
    childNode1_->changeInfoFlag_ = FRAME_NODE_CHANGE_INFO_NONE;
    auto flags = pattern_->CollectFlagsFromChildToHost(childNode1_, SCT_TEST_NODE_ID);
    EXPECT_EQ(flags, FRAME_NODE_CHANGE_INFO_NONE);
}

/* ==================== OnSelectionMenuOptionsUpdate ==================== */

/**
 * @tc.name: OnSelectionMenuOptionsUpdate001
 * @tc.desc: Test OnSelectionMenuOptionsUpdate without onMenuItemClickWithText_ delegates to overlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnSelectionMenuOptionsUpdate001, TestSize.Level1)
{
    OnCreateMenuCallback onCreateMenuCallback = [](const std::vector<MenuItemParam>& params) {
        return std::vector<MenuOptionsParam>();
    };
    OnMenuItemClickCallback onMenuItemClick = [](const MenuItemParam& param) { return false; };
    OnPrepareMenuCallback onPrepareMenuCallback = [](const std::vector<MenuItemParam>& params) {
        return std::vector<MenuOptionsParam>();
    };
    pattern_->OnSelectionMenuOptionsUpdate(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/**
 * @tc.name: OnSelectionMenuOptionsUpdate002
 * @tc.desc: Test OnSelectionMenuOptionsUpdate with onMenuItemClickWithText_ wraps the click callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnSelectionMenuOptionsUpdate002, TestSize.Level1)
{
    pattern_->SetSelectionMenuItemClickWithTextCallback(
        [](const MenuItemParam& param, const std::u16string& text) { return true; });
    OnCreateMenuCallback onCreateMenuCallback = [](const std::vector<MenuItemParam>& params) {
        return std::vector<MenuOptionsParam>();
    };
    OnMenuItemClickCallback onMenuItemClick = [](const MenuItemParam& param) { return false; };
    OnPrepareMenuCallback onPrepareMenuCallback = [](const std::vector<MenuItemParam>& params) {
        return std::vector<MenuOptionsParam>();
    };
    pattern_->OnSelectionMenuOptionsUpdate(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

} // namespace OHOS::Ace::NG
