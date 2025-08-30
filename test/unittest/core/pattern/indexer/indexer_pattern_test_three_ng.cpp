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

#include "indexer_test_ng.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_layout_algorithm.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class IndexerPatternTestThreeNg : public IndexerTestNg {

};

/**
 * @tc.name: IndexerPatternTestThreeNg001
 * @tc.desc: Test indexer pattern CollapseArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with empty array.
     * @tc.expected: lastCollapsingMode_ NONE.
     */
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    model.SetAutoCollapse(true);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);

    /**
     * @tc.steps: step2. Test with enough height.
     * @tc.expected: lastCollapsingMode_ NONE.
     */
    pattern_->fullArrayValue_ = GetMidArrayValue();
    pattern_->maxContentHeight_ = LONG_INDEXER_HEIGHT;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);

    /**
     * @tc.steps: step3. Test with ShortArray and height not enough.
     * @tc.expected: lastCollapsingMode_ NONE.
     */
    pattern_->fullArrayValue_ = GetShortArrayValue();
    pattern_->maxContentHeight_ = (pattern_->fullArrayValue_.size() - 1) * INDEXER_ITEM_SIZE;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);

    /**
     * @tc.steps: step4. Test with MidArray.
     * @tc.expected: lastCollapsingMode_ FIVE.
     */
    pattern_->fullArrayValue_ = GetMidArrayValue();
    pattern_->maxContentHeight_ = SHORT_INDEXER_HEIGHT;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);

    /**
     * @tc.steps: step5. Test with LongArray and enough height.
     * @tc.expected: lastCollapsingMode_ SEVEN.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->maxContentHeight_ = LONG_INDEXER_HEIGHT;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);

    /**
     * @tc.steps: step6. Test with LongArray and height not enough.
     * @tc.expected: lastCollapsingMode_ FIVE.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->maxContentHeight_ = SHORT_INDEXER_HEIGHT;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);

    /**
     * @tc.steps: step7. Test with AutoCollapseArray.
     * @tc.expected: lastCollapsingMode_ FIVE.
     */
    pattern_->fullArrayValue_ = GetAutoCollapseArrayValue();
    pattern_->maxContentHeight_ = SHORT_INDEXER_HEIGHT;
    pattern_->sharpItemCount_ = 1;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);

    /**
     * @tc.steps: step8. Test with MidCollapseArrayValue and height not enough.
     * @tc.expected: lastCollapsingMode_ FIVE.
     */
    pattern_->fullArrayValue_ = GetMidCollapseArrayValue();
    pattern_->maxContentHeight_ = LONG_INDEXER_HEIGHT;
    pattern_->sharpItemCount_ = 1;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);

    /**
     * @tc.steps: step9. Test with MidCollapseArrayValue and enough height.
     * @tc.expected: lastCollapsingMode_ SEVEN.
     */
    pattern_->fullArrayValue_ = GetMidCollapseArrayValue();
    pattern_->maxContentHeight_ = LONG_INDEXER_HEIGHT + INDEXER_ITEM_SIZE;
    pattern_->sharpItemCount_ = 1;
    pattern_->CollapseArrayValue();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);
}

/**
 * @tc.name: IndexerPatternTestThreeNg002
 * @tc.desc: Test indexer pattern InitArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    bool autoCollapseModeChanged = false;
    bool itemCountChanged = false;

    /**
     * @tc.steps: step1. Test with CollapseMode on.
     * @tc.expected: autoCollapseModeChanged is true.
     */
    pattern_->isNewHeightCalculated_ = false;
    model.SetAutoCollapse(AceType::RawPtr(frameNode_), true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    pattern_->lastAutoCollapse_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_TRUE(autoCollapseModeChanged);
    EXPECT_FALSE(itemCountChanged);
    EXPECT_FALSE(pattern_->selectChanged_);

    /**
     * @tc.steps: step2. Test with itemCount change to shortArray .
     * @tc.expected: itemCountChanged is true.
     */
    autoCollapseModeChanged = false;
    itemCountChanged = false;
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetShortArrayValue());
    pattern_->maxContentHeight_ = SHORT_INDEXER_HEIGHT;
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_FALSE(autoCollapseModeChanged);
    EXPECT_TRUE(itemCountChanged);
    EXPECT_EQ(pattern_->fullArrayValue_, GetShortArrayValue());
    EXPECT_EQ(pattern_->itemCount_, GetShortArrayValue().size());
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_FALSE(pattern_->selectChanged_);
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);

    /**
     * @tc.steps: step3. Test with itemCount change to midArray.
     * @tc.expected: itemCountChanged is false.
     */
    autoCollapseModeChanged = false;
    itemCountChanged = false;
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetMidArrayValue());
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_FALSE(autoCollapseModeChanged);
    EXPECT_FALSE(itemCountChanged);
    EXPECT_EQ(pattern_->fullArrayValue_, GetMidArrayValue());
    EXPECT_EQ(pattern_->itemCount_, 9);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    
    /**
     * @tc.steps: step4. Test with SharpArrayValue.
     * @tc.expected: itemCountChanged is true.
     */
    autoCollapseModeChanged = false;
    itemCountChanged = false;
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetMidCollapseArrayValue());
    pattern_->isNewHeightCalculated_ = false;
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_FALSE(autoCollapseModeChanged);
    EXPECT_TRUE(itemCountChanged);
    EXPECT_EQ(pattern_->fullArrayValue_, GetMidCollapseArrayValue());
    EXPECT_EQ(pattern_->itemCount_, 10);
    EXPECT_EQ(pattern_->sharpItemCount_, 1);
    EXPECT_FALSE(pattern_->selectChanged_);
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    
    /**
     * @tc.steps: step5. Test with itemCount change to longArray.
     * @tc.expected: itemCountChanged is true.
     */
    autoCollapseModeChanged = false;
    itemCountChanged = false;
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetLongArrayValue());
    pattern_->isNewHeightCalculated_ = false;
    pattern_->maxContentHeight_ = LONG_INDEXER_HEIGHT;
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_FALSE(autoCollapseModeChanged);
    EXPECT_TRUE(itemCountChanged);
    EXPECT_EQ(pattern_->fullArrayValue_, GetLongArrayValue());
    EXPECT_EQ(pattern_->itemCount_, 13);
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);

    /**
     * @tc.steps: step6. Test with select changed.
     * @tc.expected: selectChanged_ is true.
     */
    autoCollapseModeChanged = false;
    itemCountChanged = false;
    model.SetSelected(AceType::RawPtr(frameNode_), 10);
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_FALSE(autoCollapseModeChanged);
    EXPECT_FALSE(itemCountChanged);
    EXPECT_TRUE(pattern_->selectChanged_);
    EXPECT_EQ(pattern_->GetSelected(), 5);

    /**
     * @tc.steps: step7. Test with CollapseMode off.
     * @tc.expected: autoCollapseModeChanged is true.
     */
    autoCollapseModeChanged = false;
    itemCountChanged = false;
    model.SetAutoCollapse(AceType::RawPtr(frameNode_), false);
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_TRUE(autoCollapseModeChanged);
    EXPECT_TRUE(itemCountChanged);
    EXPECT_TRUE(pattern_->selectChanged_);
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);

    /**
     * @tc.steps: step8. Test with voidArray.
     * @tc.expected: itemCountChanged is true.
     */
    autoCollapseModeChanged = false;
    itemCountChanged = false;
    model.SetSelected(AceType::RawPtr(frameNode_), 0);
    model.SetArrayValue(AceType::RawPtr(frameNode_), std::vector<std::string>());
    pattern_->InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    EXPECT_FALSE(autoCollapseModeChanged);
    EXPECT_TRUE(itemCountChanged);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), 0);
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_TRUE(pattern_->selectChanged_);
    EXPECT_EQ(pattern_->sharpItemCount_, 0);
    EXPECT_EQ(pattern_->itemCount_, 0);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_EQ(pattern_->collapsedItemNums_.size(), 0);
}

/**
 * @tc.name: IndexerPatternTestThreeNg003
 * @tc.desc: Test indexer pattern BuildFullArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg003, TestSize.Level1)
{
    CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    std::vector<std::string> arrayvalue;

    /**
     * @tc.steps: step1. Test with ShortArray.
     * @tc.expected: arrValue change to ShortArray.
     */
    pattern_->fullArrayValue_ = GetShortArrayValue();
    pattern_->BuildFullArrayValue();
    
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, GetShortArrayValue());
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_FALSE(pattern_->autoCollapse_);

    /**
     * @tc.steps: step2. Test with MidArray.
     * @tc.expected: arrValue change to MidArray.
     */
    pattern_->fullArrayValue_ = GetMidArrayValue();
    pattern_->BuildFullArrayValue();
    arrayvalue.clear();
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, GetMidArrayValue());
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_FALSE(pattern_->autoCollapse_);

    /**
     * @tc.steps: step3. Test with LongArray.
     * @tc.expected: arrValue change to LongArray.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->BuildFullArrayValue();
    arrayvalue.clear();
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, GetLongArrayValue());
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_FALSE(pattern_->autoCollapse_);
}

/**
 * @tc.name: IndexerPatternTestThreeNg004
 * @tc.desc: Test indexer pattern ApplyFivePlusOneMode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg004, TestSize.Level1)
{
    CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    std::vector<std::string> arrayvalue;
    
    /**
     * @tc.steps: step1. Test with MidArray.
     * @tc.expected: arrayValue_ changed.
     */
    pattern_->fullArrayValue_ = GetMidArrayValue();
    pattern_->ApplyFivePlusOneMode(pattern_->fullArrayValue_.size());
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    std::vector<std::string> expectValue = { "A", "B", "D", "E", "G", "H", "J", "K", "M" };
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_TRUE(pattern_->autoCollapse_);

    /**
     * @tc.steps: step2. Test with LongArray.
     * @tc.expected: arrayValue_ changed.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->ApplyFivePlusOneMode(pattern_->fullArrayValue_.size());
    arrayvalue.clear();
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    expectValue = { "A", "B", "G", "H", "M", "N", "S", "T", "Z" };
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_TRUE(pattern_->autoCollapse_);

    /**
     * @tc.steps: step3. Test with sharpItemArray.
     * @tc.expected: arrayValue_ changed.
     */
    pattern_->fullArrayValue_ = GetAutoCollapseArrayValue();
    pattern_->sharpItemCount_ = 1;
    pattern_->ApplyFivePlusOneMode(pattern_->fullArrayValue_.size());
    arrayvalue.clear();
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    expectValue = { "#", "A", "B", "C", "D", "F", "G", "I", "J", "L" };
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_TRUE(pattern_->autoCollapse_);

    /**
     * @tc.steps: step4. Test with sharpItemMidArray.
     * @tc.expected: arrayValue_ changed.
     */
    pattern_->fullArrayValue_ = GetMidCollapseArrayValue();
    pattern_->ApplyFivePlusOneMode(pattern_->fullArrayValue_.size());
    arrayvalue.clear();
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    expectValue = { "#", "A", "B", "D", "E", "H", "I", "L", "M", "P" };
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_TRUE(pattern_->autoCollapse_);
}

/**
 * @tc.name: IndexerPatternTestThreeNg005
 * @tc.desc: Test indexer pattern ApplySevenPlusOneMode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg005, TestSize.Level1)
{
    CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    std::vector<std::string> arrayvalue;
    
    /**
     * @tc.steps: step1. Test with LongArray.
     * @tc.expected: arrayValue_ changed.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->ApplyFivePlusOneMode(pattern_->fullArrayValue_.size());
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    std::vector<std::string> expectValue = { "A", "B", "G", "H", "M", "N", "S", "T", "Z" };
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_TRUE(pattern_->autoCollapse_);

    /**
     * @tc.steps: step2. Test with sharpItemLongArray.
     * @tc.expected: arrayValue_ changed.
     */
    std::vector<std::string> arrayValue = GetLongArrayValue();
    arrayValue.insert(arrayValue.begin(), "#");
    pattern_->fullArrayValue_ = arrayValue;
    pattern_->sharpItemCount_ = 1;
    pattern_->ApplySevenPlusOneMode(pattern_->fullArrayValue_.size());
    arrayvalue.clear();
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    expectValue = { "#", "A", "B", "E", "F", "I", "J", "M", "N", "Q", "R", "U", "V", "Z" };
    EXPECT_EQ(arrayvalue, expectValue);
    EXPECT_TRUE(pattern_->autoCollapse_);
}

/**
 * @tc.name: IndexerPatternTestThreeNg006
 * @tc.desc: Test indexer pattern GetAutoCollapseIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg006, TestSize.Level1)
{
    CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    
    /**
     * @tc.steps: step1. Test with MidArray and MODE_FIVE.
     * @tc.expected: GetAutoCollapseIndex return 7.
     */
    pattern_->fullArrayValue_ = GetMidArrayValue();
    pattern_->sharpItemCount_ = 0;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::FIVE;
    EXPECT_EQ(pattern_->GetAutoCollapseIndex(10), 7);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);

    /**
     * @tc.steps: step2. Test with SharpMidArray and MODE_FIVE.
     * @tc.expected: GetAutoCollapseIndex return 8.
     */
    pattern_->fullArrayValue_ = GetAutoCollapseArrayValue();
    pattern_->sharpItemCount_ = 1;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::FIVE;
    EXPECT_EQ(pattern_->GetAutoCollapseIndex(10), 8);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    
    /**
     * @tc.steps: step3. Test with LongArray and MODE_FIVE.
     * @tc.expected: GetAutoCollapseIndex return 3.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->sharpItemCount_ = 0;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::FIVE;
    EXPECT_EQ(pattern_->GetAutoCollapseIndex(10), 3);
    EXPECT_EQ(pattern_->collapsedIndex_, 3);

    /**
     * @tc.steps: step4. Test with MidCollapseArrayValue and MODE_FIVE.
     * @tc.expected: GetAutoCollapseIndex return 6.
     */
    pattern_->fullArrayValue_ = GetMidCollapseArrayValue();
    pattern_->sharpItemCount_ = 1;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::FIVE;
    EXPECT_EQ(pattern_->GetAutoCollapseIndex(10), 6);
    EXPECT_EQ(pattern_->collapsedIndex_, 1);

    /**
     * @tc.steps: step5. Test with LongArray and MODE_SEVEN.
     * @tc.expected: GetAutoCollapseIndex return 5.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->sharpItemCount_ = 0;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::SEVEN;
    EXPECT_EQ(pattern_->GetAutoCollapseIndex(10), 5);
    EXPECT_EQ(pattern_->collapsedIndex_, 1);

    /**
     * @tc.steps: step6. Test with MidCollapseArrayValue and MODE_SEVEN.
     * @tc.expected: GetAutoCollapseIndex return 10.
     */
    pattern_->fullArrayValue_ = GetMidCollapseArrayValue();
    pattern_->sharpItemCount_ = 1;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::SEVEN;
    EXPECT_EQ(pattern_->GetAutoCollapseIndex(10), 9);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
}

/**
 * @tc.name: IndexerPatternTestThreeNg007
 * @tc.desc: Test indexer pattern GetActualIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg007, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    model.SetAutoCollapse(true);
    CreateDone();
    
    /**
     * @tc.steps: step1. Test with MidArray and MODE_FIVE.
     * @tc.expected: GetActualIndex return correct.
     */
    pattern_->fullArrayValue_ = GetMidArrayValue();
    pattern_->sharpItemCount_ = 0;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::FIVE;
    pattern_->ApplyFivePlusOneMode(pattern_->fullArrayValue_.size());
    pattern_->itemCount_ = pattern_->arrayValue_.size();
    pattern_->collapsedIndex_ = 0;
    int32_t index = pattern_->GetAutoCollapseIndex(10);
    EXPECT_EQ(index, 7);
    EXPECT_EQ(pattern_->GetActualIndex(index), 10);

    /**
     * @tc.steps: step2. Test with LongArray and MODE_SEVEN.
     * @tc.expected: GetActualIndex return correct.
     */
    pattern_->fullArrayValue_ = GetLongArrayValue();
    pattern_->sharpItemCount_ = 0;
    pattern_->lastCollapsingMode_ = IndexerCollapsingMode::SEVEN;
    pattern_->ApplySevenPlusOneMode(pattern_->fullArrayValue_.size());
    pattern_->itemCount_ = pattern_->arrayValue_.size();
    pattern_->collapsedIndex_ = 0;
    index = pattern_->GetAutoCollapseIndex(10);
    EXPECT_EQ(index, 5);
    EXPECT_EQ(pattern_->GetActualIndex(index), 10);

    /**
     * @tc.steps: step3. Test with index out of range.
     * @tc.expected: GetActualIndex return correct.
     */
    EXPECT_EQ(pattern_->GetActualIndex(-1), 0);
    EXPECT_EQ(pattern_->GetActualIndex(pattern_->fullArrayValue_.size() + 1), pattern_->fullArrayValue_.size() - 1);
}

/**
 * @tc.name: IndexerPatternTestThreeNg008
 * @tc.desc: Test indexer pattern OnHover function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with voidArray.
     * @tc.expected: isHover_ false.
     */
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    pattern_->OnHover(true);
    EXPECT_FALSE(pattern_->isHover_);

    /**
     * @tc.steps: step2. Test with MidArray.
     * @tc.expected: isHover_ true.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetMidArrayValue());
    frameNode_->MarkModifyDone();
    FlushUITasks();
    pattern_->OnHover(true);
    EXPECT_TRUE(pattern_->isHover_);
    EXPECT_FALSE(pattern_->isTouch_);
    pattern_->OnHover(true);
    EXPECT_TRUE(pattern_->isHover_);
    pattern_->OnHover(false);
    EXPECT_FALSE(pattern_->isHover_);
    EXPECT_FALSE(pattern_->isTouch_);
}

/**
 * @tc.name: IndexerPatternTestThreeNg009
 * @tc.desc: Test indexer pattern OnChildHover function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with OnChildHover 2.
     * @tc.expected: childHoverIndex_ correct.
     */
    CreateIndexer(GetMidArrayValue(), 0);
    pattern_->OnChildHover(2, false);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    pattern_->OnChildHover(2, true);
    EXPECT_EQ(pattern_->childHoverIndex_, 2);
}

/**
 * @tc.name: IndexerPatternTestThreeNg010
 * @tc.desc: Test indexer pattern OnPopupHover function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with OnPopupHover true and false.
     * @tc.expected: isPopupHover_ correct.
     */
    CreateIndexer(GetMidArrayValue(), 0);
    pattern_->OnPopupHover(true);
    EXPECT_TRUE(pattern_->isPopupHover_);
    pattern_->OnPopupHover(false);
    EXPECT_FALSE(pattern_->isPopupHover_);
}

/**
 * @tc.name: IndexerPatternTestThreeNg011
 * @tc.desc: Test indexer pattern GetSelectChildIndex1 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg011, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetMidArrayValue(), 0);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();
    int32_t count = 0;
    int32_t index;
    float offsetY;

    /**
     * @tc.steps: step1. Test with MidArray and Offset(0.f, offsetY - 1.f).
     * @tc.expected: GetSelectChildIndex return -1.
     */
    for (auto child : frameNode_->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        auto geometryNode = childNode->GetGeometryNode();
        geometryNode->SetFrameOffset(OffsetF(0, INDEXER_ITEM_SIZE * count + INDEXER_PADDING_TOP));
        count++;
    }
    offsetY = GetChildY(frameNode_, 0);
    pattern_->itemHeight_ = INDEXER_ITEM_SIZE;
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY - 1.f), true);
    EXPECT_EQ(index, -1);

    /**
     * @tc.steps: step2. Test with MidArray and Offset(0.f, offsetY + 50.f).
     * @tc.expected: GetSelectChildIndex return 3.
     */
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + 50.f), true);
    EXPECT_EQ(index, 3);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + 50.f), false);
    EXPECT_EQ(index, 3);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);

    /**
     * @tc.steps: step3. Test with MidArray and Offset(0.f, offsetY + LONG_INDEXER_HEIGHT).
     * @tc.expected: GetSelectChildIndex return -1.
     */
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + LONG_INDEXER_HEIGHT), false);
    EXPECT_EQ(index, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
}

/**
 * @tc.name: IndexerPatternTestThreeNg012
 * @tc.desc: Test indexer pattern GetSelectChildIndex2 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg012, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(LONG_INDEXER_HEIGHT));
    CreateDone();
    int32_t count = 0;
    int32_t index;
    float offsetY;

    /**
     * @tc.steps: step1. Test with LongArray and Offset(0.f, offsetY - 1.f).
     * @tc.expected: GetSelectChildIndex return -1.
     */
    pattern_->itemHeight_ = INDEXER_ITEM_SIZE;
    for (auto child : frameNode_->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        auto geometryNode = childNode->GetGeometryNode();
        geometryNode->SetFrameOffset(OffsetF(0, INDEXER_ITEM_SIZE * count + INDEXER_PADDING_TOP));
        count++;
    }
    offsetY = GetChildY(frameNode_, 0);
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY - 1.f), true);
    EXPECT_EQ(index, -1);

    /**
     * @tc.steps: step2. Test with LongArray and Offset(0.f, offsetY + 80.f).
     * @tc.expected: GetSelectChildIndex return 3.
     */
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + 80.f), true);
    EXPECT_EQ(index, 5);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + 80.f), false);
    EXPECT_EQ(index, 5);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);

    /**
     * @tc.steps: step3. Test with LongArray and Offset(0.f, offsetY + INDEXER_HEIGHT).
     * @tc.expected: GetSelectChildIndex return -1.
     */
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + INDEXER_HEIGHT), false);
    EXPECT_EQ(index, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
}

/**
 * @tc.name: IndexerPatternTestThreeNg013
 * @tc.desc: Test indexer pattern GetSelectChildIndex3 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg013, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetAutoCollapseArrayValue(), 0);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();
    int32_t count = 0;
    int32_t index;
    float offsetY;

    /**
     * @tc.steps: step1. Test with AutoCollapseArrayValue and Offset(0.f, offsetY - 1.f).
     * @tc.expected: GetSelectChildIndex return -1.
     */
    pattern_->itemHeight_ = INDEXER_ITEM_SIZE;
    for (auto child : frameNode_->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        auto geometryNode = childNode->GetGeometryNode();
        geometryNode->SetFrameOffset(OffsetF(0, INDEXER_ITEM_SIZE * count + INDEXER_PADDING_TOP));
        count++;
    }
    offsetY = GetChildY(frameNode_, 0);
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY - 1.f), true);
    EXPECT_EQ(index, -1);

    /**
     * @tc.steps: step2. Test with AutoCollapseArrayValue and Offset(0.f, offsetY + 50.f).
     * @tc.expected: GetSelectChildIndex return 3.
     */
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + 50.f), true);
    EXPECT_EQ(index, 3);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + 50.f), false);
    EXPECT_EQ(index, 3);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);

    /**
     * @tc.steps: step3. Test with AutoCollapseArrayValue and Offset(0.f, offsetY + SHORT_INDEXER_HEIGHT).
     * @tc.expected: GetSelectChildIndex return -1.
     */
    index = pattern_->GetSelectChildIndex(Offset(0.f, offsetY + LONG_INDEXER_HEIGHT), false);
    EXPECT_EQ(index, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
}

/**
 * @tc.name: IndexerPatternTestThreeNg014
 * @tc.desc: Test indexer pattern MoveIndexByOffset1 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg014, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    model.SetAutoCollapse(true);
    CreateDone();
    int32_t count = 0;

    /**
     * @tc.steps: step1. Test with VoidArray.
     * @tc.expected: selected_ 0.
     */
    pattern_->itemHeight_ = INDEXER_ITEM_SIZE;
    pattern_->itemCount_ = 0;
    for (auto child : frameNode_->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        auto geometryNode = childNode->GetGeometryNode();
        geometryNode->SetFrameOffset(OffsetF(0, INDEXER_ITEM_SIZE * count + INDEXER_PADDING_TOP));
        count++;
    }
    pattern_->MoveIndexByOffset(Offset(0.f, 50.f), true);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_FALSE(pattern_->selectedChangedForHaptic_);
}

/**
 * @tc.name: IndexerPatternTestThreeNg015
 * @tc.desc: Test indexer pattern MoveIndexByOffset2 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg015, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetMidArrayValue(), 3);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();
    int32_t count = 0;
    float offsetY;

    /**
     * @tc.steps: step1. Test with MidArray and Offset(0.f, offsetY + 255.f).
     * @tc.expected: selected_ not change.
     */
    pattern_->itemHeight_ = INDEXER_ITEM_SIZE;
    for (auto child : frameNode_->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        auto geometryNode = childNode->GetGeometryNode();
        geometryNode->SetFrameOffset(OffsetF(0, INDEXER_ITEM_SIZE * count + INDEXER_PADDING_TOP));
        count++;
    }
    int32_t childPressIndex = pattern_->childPressIndex_;
    int32_t selected = pattern_->selected_;
    int32_t lastSelected = pattern_->lastSelected_;
    offsetY = GetChildY(frameNode_, 0);
    pattern_->MoveIndexByOffset(Offset(0.f, offsetY + 255.f), true);
    EXPECT_EQ(pattern_->childPressIndex_, childPressIndex);
    EXPECT_EQ(pattern_->selected_, selected);
    EXPECT_EQ(pattern_->lastSelected_, lastSelected);

    /**
     * @tc.steps: step2. Test with MidArray and Offset(0.f, offsetY + 80.f).
     * @tc.expected: selected_ changed.
     */
    pattern_->MoveIndexByOffset(Offset(0.f, offsetY + 80.f), true);
    EXPECT_EQ(pattern_->childPressIndex_, 5);
    EXPECT_EQ(pattern_->selected_, 5);
    EXPECT_EQ(pattern_->lastSelected_, 5);
    EXPECT_TRUE(pattern_->selectedChangedForHaptic_);
    EXPECT_EQ(pattern_->childFocusIndex_, -1);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
}

/**
 * @tc.name: IndexerPatternTestThreeNg016
 * @tc.desc: Test indexer pattern MoveIndexByOffset3 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg016, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetAutoCollapseArrayValue(), 0);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();
    int32_t count = 0;
    float offsetY;

    /**
     * @tc.steps: step1. Test with AutoCollapseArrayValue and Offset(0.f, offsetY + 50).
     * @tc.expected: selected_ changed.
     */
    pattern_->itemHeight_ = INDEXER_ITEM_SIZE;
    for (auto child : frameNode_->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        auto geometryNode = childNode->GetGeometryNode();
        geometryNode->SetFrameOffset(OffsetF(0, INDEXER_ITEM_SIZE * count + INDEXER_PADDING_TOP));
        count++;
    }
    offsetY = GetChildY(frameNode_, 0);
    pattern_->isHover_ = true;
    pattern_->MoveIndexByOffset(Offset(0.f, offsetY + 50.f), true);
    EXPECT_EQ(pattern_->childPressIndex_, 3);
    EXPECT_EQ(pattern_->selected_, 3);
    EXPECT_EQ(pattern_->lastSelected_, 3);
    EXPECT_TRUE(pattern_->selectedChangedForHaptic_);
    EXPECT_EQ(pattern_->childFocusIndex_, -1);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
}

/**
 * @tc.name: IndexerPatternTestThreeNg017
 * @tc.desc: Test indexer pattern MoveIndexByStep function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg017, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetMidArrayValue(), 1);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();

    /**
     * @tc.steps: step1. Test with MidArray and step out of range.
     * @tc.expected: MoveIndexByStep return false.
     */
    int32_t index = pattern_->GetSkipChildIndex(pattern_->itemCount_);
    EXPECT_EQ(index, -1);
    EXPECT_FALSE(pattern_->MoveIndexByStep(pattern_->itemCount_));
    index = pattern_->GetSkipChildIndex(-2);
    EXPECT_EQ(index, -1);
    EXPECT_FALSE(pattern_->MoveIndexByStep(-2));

    /**
     * @tc.steps: step2. Test with MidArray and valid step.
     * @tc.expected: MoveIndexByStep return correct.
     */
    index = pattern_->GetSkipChildIndex(0);
    EXPECT_EQ(index, 1);
    EXPECT_FALSE(pattern_->MoveIndexByStep(0));
    index = pattern_->GetSkipChildIndex(3);
    EXPECT_EQ(index, 4);
    EXPECT_TRUE(pattern_->MoveIndexByStep(3));
    EXPECT_EQ(pattern_->selected_, 4);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_FALSE(pattern_->MoveIndexByStep(pattern_->itemCount_));

    /**
     * @tc.steps: step3. Test with MidCollapseArrayValue and step out of range.
     * @tc.expected: MoveIndexByStep return false.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetMidCollapseArrayValue());
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(LONG_INDEXER_HEIGHT));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    pattern_->selected_ = 3;
    index = pattern_->GetSkipChildIndex(pattern_->itemCount_);
    EXPECT_EQ(index, -1);
    EXPECT_FALSE(pattern_->MoveIndexByStep(pattern_->itemCount_));

    /**
     * @tc.steps: step4. Test with MidCollapseArrayValue and valid step.
     * @tc.expected: MoveIndexByStep return correct.
     */
    index = pattern_->GetSkipChildIndex(-2);
    EXPECT_EQ(index, 1);
    EXPECT_TRUE(pattern_->MoveIndexByStep(-2));
    index = pattern_->GetSkipChildIndex(0);
    EXPECT_EQ(index, 1);
    EXPECT_FALSE(pattern_->MoveIndexByStep(0));
    index = pattern_->GetSkipChildIndex(2);
    EXPECT_EQ(index, 3);
    EXPECT_TRUE(pattern_->MoveIndexByStep(2));
    EXPECT_EQ(pattern_->selected_, 3);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    EXPECT_FALSE(pattern_->MoveIndexByStep(pattern_->itemCount_));
}

/**
 * @tc.name: IndexerPatternTestThreeNg018
 * @tc.desc: Test indexer pattern GetFocusChildIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg018, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetMidArrayValue(), 3);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();

    /**
     * @tc.steps: step1. Test with MidArray.
     * @tc.expected: GetFocusChildIndex return correct.
     */
    std::string searchStr = "ABC";
    int32_t index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, -1);
    searchStr = "B";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 1);
    searchStr = "E";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 4);
    searchStr = "Z";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, -1);

    /**
     * @tc.steps: step2. Test with AutoCollapseArrayValue.
     * @tc.expected: GetFocusChildIndex return correct.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetAutoCollapseArrayValue());
    model.SetSelected(AceType::RawPtr(frameNode_), 5);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    searchStr = "EF";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, -1);
    searchStr = "#";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 0);
    searchStr = "C";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 3);
    searchStr = "L";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 9);
}

/**
 * @tc.name: IndexerPatternTestThreeNg019
 * @tc.desc: Test indexer pattern GetFocusChildIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg019, TestSize.Level1)
{
    std::vector<std::string> arrayValye = { "ABC", "BCD", "CDE", "DEF", "EFG", "FGH", "GH", "HIJ", "IJ", "JK", "kL",
        "LM", "MN" };
    IndexerModelNG model = CreateIndexer(arrayValye, 6);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();

    /**
     * @tc.steps: step1. Test with LongStrArray.
     * @tc.expected: GetFocusChildIndex return correct.
     */
    std::string searchStr = "ABCDE";
    int32_t index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, -1);
    searchStr = "BC";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 1);
    searchStr = "K";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 10);
    searchStr = "Z";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, -1);
    searchStr = "EFG";
    index = pattern_->GetFocusChildIndex(searchStr);
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: IndexerPatternTestThreeNg020
 * @tc.desc: Test indexer pattern MoveIndexBySearch1 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg020, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetMidArrayValue(), 3);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();

    /**
     * @tc.steps: step1. Test with MidArray.
     * @tc.expected: selected_ correct.
     */
    std::string searchStr = "ABC";
    EXPECT_FALSE(pattern_->MoveIndexBySearch(searchStr));
    searchStr = "Z";
    EXPECT_FALSE(pattern_->MoveIndexBySearch(searchStr));
    searchStr = "B";
    EXPECT_TRUE(pattern_->MoveIndexBySearch(searchStr));
    EXPECT_EQ(pattern_->selected_, 1);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, 1);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    searchStr = "j";
    EXPECT_TRUE(pattern_->MoveIndexBySearch(searchStr));
    EXPECT_EQ(pattern_->selected_, 9);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, 9);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);

    /**
     * @tc.steps: step2. Test with AutoCollapseArrayValue.
     * @tc.expected: selected_ correct.
     */
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetAutoCollapseArrayValue());
    model.SetSelected(AceType::RawPtr(frameNode_), 5);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    searchStr = "BC";
    EXPECT_FALSE(pattern_->MoveIndexBySearch(searchStr));
    searchStr = "Z";
    EXPECT_FALSE(pattern_->MoveIndexBySearch(searchStr));
    searchStr = "#";
    EXPECT_TRUE(pattern_->MoveIndexBySearch(searchStr));
    EXPECT_EQ(pattern_->selected_, 0);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, 0);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    searchStr = "j";
    EXPECT_TRUE(pattern_->MoveIndexBySearch(searchStr));
    EXPECT_EQ(pattern_->selected_, 8);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, 8);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
}

/**
 * @tc.name: IndexerPatternTestThreeNg021
 * @tc.desc: Test indexer pattern MoveIndexBySearch2 function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg021, TestSize.Level1)
{
    std::vector<std::string> arrayValue = { "ABC", "BCD", "CDE", "DEF", "EFG", "FGH", "GH", "HIJ", "IJ", "JK", "kL",
        "LM", "MN" };
    IndexerModelNG model = CreateIndexer(arrayValue, 6);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();

    /**
     * @tc.steps: step1. Test with searchStr longer than arrayValue_.
     * @tc.expected: selected_ correct.
     */
    std::string searchStr = "ABCDE";
    EXPECT_FALSE(pattern_->MoveIndexBySearch(searchStr));

    /**
     * @tc.steps: step2. Test with searchStr shorter than arrayValue_.
     * @tc.expected: selected_ correct.
     */
    searchStr = "Z";
    EXPECT_FALSE(pattern_->MoveIndexBySearch(searchStr));
    searchStr = "K";
    EXPECT_TRUE(pattern_->MoveIndexBySearch(searchStr));
    EXPECT_EQ(pattern_->selected_, 10);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, 10);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
    searchStr = "HI";
    EXPECT_TRUE(pattern_->MoveIndexBySearch(searchStr));
    EXPECT_EQ(pattern_->selected_, 7);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, 7);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);

    /**
     * @tc.steps: step3. Test with searchStr equal arrayValue_.
     * @tc.expected: selected_ correct.
     */
    searchStr = "EFG";
    EXPECT_TRUE(pattern_->MoveIndexBySearch(searchStr));
    EXPECT_EQ(pattern_->selected_, 4);
    EXPECT_EQ(pattern_->childPressIndex_, -1);
    EXPECT_EQ(pattern_->childFocusIndex_, 4);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    EXPECT_EQ(pattern_->collapsedIndex_, 0);
}

/**
 * @tc.name: IndexerPatternTestThreeNg022
 * @tc.desc: Test indexer pattern ItemSelectedChangedAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg022, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetMidArrayValue(), 0);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();

    /**
     * @tc.steps: step1. Test with selected_ changed.
     * @tc.expected: selectedChangedForHaptic_ true.
     */
    pattern_->ItemSelectedChangedAnimation();
    EXPECT_TRUE(pattern_->selectedChangedForHaptic_);
    EXPECT_EQ(pattern_->lastSelected_, 0);
    EXPECT_EQ(pattern_->animateSelected_, 0);
    pattern_->selected_ = 3;
    pattern_->ItemSelectedChangedAnimation();
    EXPECT_TRUE(pattern_->selectedChangedForHaptic_);
    EXPECT_EQ(pattern_->lastSelected_, 3);
    EXPECT_EQ(pattern_->animateSelected_, 3);

    /**
     * @tc.steps: step2. Test with selected_ not changed.
     * @tc.expected: selectedChangedForHaptic_ false.
     */
    pattern_->selected_ = 3;
    pattern_->ItemSelectedChangedAnimation();
    EXPECT_FALSE(pattern_->selectedChangedForHaptic_);
    EXPECT_EQ(pattern_->lastSelected_, 3);
    EXPECT_EQ(pattern_->animateSelected_, 3);
}

/**
 * @tc.name: IndexerPatternTestThreeNg023
 * @tc.desc: Test indexer pattern CalcBubbleListSize function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg023, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetMidArrayValue(), 0);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();

    /**
     * @tc.steps: step1. Test with popupSize less than maxItemsSize.
     * @tc.expected: size correct.
     */
    auto expectSzie = CalcSize();
    auto bubbleSize = Dimension(56, DimensionUnit::VP).ConvertToPx();
    auto bubbleHeight = Dimension(48, DimensionUnit::VP).ConvertToPx();
    auto bubbleDivider = Dimension(4, DimensionUnit::VP).ConvertToPx();
    std::optional<CalcLength> width = CalcLength(bubbleSize);
    auto bubbleLength = bubbleHeight + bubbleDivider;
    std::optional<CalcLength> height = CalcLength(bubbleLength * static_cast<int32_t>(5) - bubbleDivider);
    auto size = pattern_->CalcBubbleListSize(5, 8);
    EXPECT_EQ(size.width_, width);
    EXPECT_EQ(size.height_, height);
    size = pattern_->CalcBubbleListSize(5, 5);
    EXPECT_EQ(size.width_, width);
    EXPECT_EQ(size.height_, height);

    /**
     * @tc.steps: step2. Test with popupSize more than maxItemsSize.
     * @tc.expected: size correct.
     */
    pattern_->autoCollapse_ = true;
    width = CalcLength(bubbleSize);
    height = CalcLength(Dimension(178.0f, DimensionUnit::VP).ConvertToPx());
    size = pattern_->CalcBubbleListSize(8, 5);
    EXPECT_EQ(size.width_, width);
    EXPECT_EQ(size.height_, height);
    pattern_->autoCollapse_ = false;
    width = CalcLength(bubbleSize);
    height = CalcLength(Dimension(282.0f, DimensionUnit::VP).ConvertToPx());
    size = pattern_->CalcBubbleListSize(8, 5);
    EXPECT_EQ(size.width_, width);
    EXPECT_EQ(size.height_, height);
}

/**
 * @tc.name: IndexerPatternTestThreeNg024
 * @tc.desc: Test indexer pattern OnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg024, TestSize.Level1)
{
    CreateIndexer(GetMidArrayValue(), 0);
    CreateDone();

    /**
     * @tc.steps: step1. Test with KEY_DPAD_UP.
     * @tc.expected: selected_ correct.
     */
    KeyEvent keyEvent = KeyEvent();
    keyEvent.action = KeyAction::UP;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    keyEvent.action = KeyAction::DOWN;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 0);
    pattern_->selected_ = 3;
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 2);

    /**
     * @tc.steps: step2. Test with KEY_DPAD_DOWN.
     * @tc.expected: selected_ correct.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 3);
    pattern_->selected_ = pattern_->itemCount_;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, pattern_->itemCount_);

    /**
     * @tc.steps: step3. Test with CombinationKey.
     * @tc.expected: selected_ not changed.
     */
    pattern_->selected_ = 3;
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = { KeyCode::KEY_B, KeyCode::KEY_C };
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 3);
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_DPAD_DOWN, KeyCode::KEY_B };
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 4);
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.pressedCodes = { KeyCode::KEY_DPAD_UP, KeyCode::KEY_B };
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 3);
}

/**
 * @tc.name: IndexerPatternTestThreeNg025
 * @tc.desc: Test indexer pattern OnKeyEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg025, TestSize.Level1)
{
    CreateIndexer(GetMidArrayValue(), 2);
    CreateDone();

    /**
     * @tc.steps: step1. Test with IsLetterKey.
     * @tc.expected: selected_ correct.
     */
    KeyEvent keyEvent = KeyEvent();
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_A;
    keyEvent.pressedCodes = {};
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 0);
    keyEvent.code = KeyCode::KEY_D;
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 3);
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 3);
    keyEvent.code = KeyCode::KEY_H;
    EXPECT_TRUE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 7);
    keyEvent.code = KeyCode::KEY_Z;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 7);

    /**
     * @tc.steps: step2. Test with IsNumberKey.
     * @tc.expected: selected_ not changed.
     */
    keyEvent.code = KeyCode::KEY_3;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 7);
    keyEvent.code = KeyCode::KEY_0;
    EXPECT_FALSE(pattern_->OnKeyEvent(keyEvent));
    EXPECT_EQ(pattern_->selected_, 7);
}

/**
 * @tc.name: IndexerPatternTestThreeNg026
 * @tc.desc: Test indexer pattern IndexerHoverOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with IndexerHoverOutAnimation.
     * @tc.expected: color TRANSPARENT.
     */
    CreateIndexer(GetMidArrayValue(), 0);
    CreateDone();
    pattern_->IndexerHoverOutAnimation();
    auto host = pattern_->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
}

/**
 * @tc.name: IndexerPatternTestThreeNg027
 * @tc.desc: Test indexer pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg027, TestSize.Level1)
{
    CreateIndexer(GetMidArrayValue(), 0);
    CreateDone();
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = true;
    dirtySwapConfig.skipMeasure = true;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    auto algorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;

    /**
     * @tc.steps: step1. Test with skipLayout true and skipMeasure true.
     * @tc.expected: initialized_ true.
     */
    bool ret = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_FALSE(ret);
    EXPECT_TRUE(pattern_->initialized_);

    /**
     * @tc.steps: step2. Test with skipLayout true and skipMeasure false.
     * @tc.expected: maxContentHeight_ correct.
     */
    pattern_->lastAutoCollapse_ = true;
    dirtySwapConfig.skipLayout = true;
    dirtySwapConfig.skipMeasure = false;
    algorithm->maxContentHeight_ = INDEXER_ITEM_SIZE;
    pattern_->maxContentHeight_ = INDEXER_ITEM_SIZE + 1;
    ret = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(pattern_->maxContentHeight_, INDEXER_ITEM_SIZE);
    EXPECT_TRUE(pattern_->isNewHeightCalculated_);
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step3. Test with skipLayout false and skipMeasure true.
     * @tc.expected: maxContentHeight_ correct.
     */
    dirtySwapConfig.skipLayout = false;
    dirtySwapConfig.skipMeasure = true;
    pattern_->maxContentHeight_ = INDEXER_ITEM_SIZE + 1;
    ret = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_EQ(pattern_->maxContentHeight_, INDEXER_ITEM_SIZE);
    EXPECT_TRUE(pattern_->isNewHeightCalculated_);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: IndexerPatternTestThreeNg028
 * @tc.desc: Test indexer pattern CollapseArrayValue function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg028, TestSize.Level1)
{
    std::vector<std::string> arrayvalue;
    CreateIndexer(GetShortArrayValue(), 0);
    CreateDone();

    /**
     * @tc.steps: step1. Test with itemSize 0.
     * @tc.expected: arrayValue_ correct.
     */
    pattern_->maxContentHeight_ = SHORT_INDEXER_HEIGHT;
    pattern_->fullArrayValue_ = GetShortArrayValue();
    layoutProperty_->UpdateItemSize(Dimension(0, DimensionUnit::VP));
    pattern_->CollapseArrayValue();
    for (auto item : pattern_->arrayValue_) {
        arrayvalue.push_back(item.first);
    }
    EXPECT_EQ(arrayvalue, GetShortArrayValue());
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(pattern_->arrayValue_.size(), GetShortArrayValue().size());
    EXPECT_EQ(arrayvalue, GetShortArrayValue());
}

/**
 * @tc.name: IndexerPatternTestThreeNg029
 * @tc.desc: Test indexer pattern FireOnSelect function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestThreeNg, IndexerPatternTestThreeNg029, TestSize.Level1)
{
    int32_t selected = -1;
    int32_t changeSelected = -1;
    int32_t creatChangeSelected = -1;
    OnSelectedEvent onSelected = [&selected](int32_t selectedIndex) { selected = selectedIndex; };
    OnSelectedEvent changeEvent = [&changeSelected](int32_t selectedIndex) { changeSelected = selectedIndex; };
    OnSelectedEvent creatChangeEvent = [&creatChangeSelected](
                                           int32_t selectedIndex) { creatChangeSelected = selectedIndex; };
    IndexerModelNG model = CreateIndexer(GetShortArrayValue(), 0);
    eventHub_->SetOnSelected(std::move(onSelected));
    eventHub_->SetChangeEvent(std::move(changeEvent));
    eventHub_->SetCreatChangeEvent(std::move(creatChangeEvent));

    /**
     * @tc.steps: step1. Test with selected_ > itemCount_.
     * @tc.expected: lastFireSelectIndex_ correct.
     */
    EXPECT_NE(eventHub_->GetChangeEvent(), nullptr);
    pattern_->lastFireSelectIndex_ = 0;
    pattern_->lastIndexFromPress_ = false;
    pattern_->selected_ = pattern_->itemCount_ + 1;
    pattern_->FireOnSelect(pattern_->itemCount_ + 1, false);
    EXPECT_EQ(pattern_->lastFireSelectIndex_, 1);
    EXPECT_FALSE(pattern_->lastIndexFromPress_);

    /**
     * @tc.steps: step2. Test with selected_ < 0.
     * @tc.expected: lastFireSelectIndex_ correct.
     */
    pattern_->lastFireSelectIndex_ = 0;
    pattern_->lastIndexFromPress_ = true;
    pattern_->selected_ = -1;
    pattern_->FireOnSelect(-1, false);
    EXPECT_EQ(pattern_->lastFireSelectIndex_, -1);
    EXPECT_FALSE(pattern_->lastIndexFromPress_);

    /**
     * @tc.steps: step3. Test with lastFireSelectIndex_ != selectIndex.
     * @tc.expected: lastFireSelectIndex_ correct.
     */
    pattern_->lastFireSelectIndex_ = 0;
    pattern_->lastIndexFromPress_ = true;
    pattern_->FireOnSelect(1, false);
    EXPECT_EQ(pattern_->lastFireSelectIndex_, 1);
    EXPECT_FALSE(pattern_->lastIndexFromPress_);
}
} // namespace OHOS::Ace::NG
