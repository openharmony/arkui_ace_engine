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
} // namespace OHOS::Ace::NG
