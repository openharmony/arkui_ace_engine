/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class IndexerAccessibilityTestNg : public IndexerTestNg {
public:
};

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test GetEndIndex/GetText with empty arrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, AccessibilityProperty001, TestSize.Level1)
{
    CreateIndexer(std::vector<std::string>());
    CreateDone();
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), -1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "");
}

/**
 * @tc.name: PerformAction001
 * @tc.desc: Indexer AccessibilityProperty PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, PerformAction001, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), GetLongArrayValue().size() - 1);

    /**
     * @tc.steps: step1. Clear select when no selected
     */
    auto thirdTextAccessibilityProperty = GetChildAccessibilityProperty<AccessibilityProperty>(frameNode_, 2);
    auto fifthTextAccessibilityProperty = GetChildAccessibilityProperty<AccessibilityProperty>(frameNode_, 4);
    thirdTextAccessibilityProperty->ActActionClearSelection();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), GetLongArrayValue().at(0));

    /**
     * @tc.steps: step2. Select a text node
     */
    thirdTextAccessibilityProperty->ActActionSelect();
    EXPECT_EQ(pattern_->GetSelected(), 2);
    EXPECT_EQ(accessibilityProperty_->GetText(), GetLongArrayValue().at(2));

    /**
     * @tc.steps: step3. Clear select
     */
    thirdTextAccessibilityProperty->ActActionClearSelection();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), GetLongArrayValue().at(0));

    /**
     * @tc.steps: step4. Change select
     */
    fifthTextAccessibilityProperty->ActActionSelect();
    EXPECT_EQ(pattern_->GetSelected(), 4);
    EXPECT_EQ(accessibilityProperty_->GetText(), GetLongArrayValue().at(4));
}

/**
 * @tc.name: PerformAction002
 * @tc.desc: Indexer AccessibilityProperty PerformAction test Select and ClearSelection with autoCollapse
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, PerformAction002, TestSize.Level1)
{
    // "A•G•M•S•Z"
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAutoCollapse(true);
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 8);

    /**
     * @tc.steps: step1. Default select "A"
     */
    auto thirdTextAccessibilityProperty = GetChildAccessibilityProperty<AccessibilityProperty>(frameNode_, 2);
    auto fourthTextAccessibilityProperty = GetChildAccessibilityProperty<AccessibilityProperty>(frameNode_, 3);
    auto fifthTextAccessibilityProperty = GetChildAccessibilityProperty<AccessibilityProperty>(frameNode_, 4);
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), GetLongArrayValue().at(0));
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    /**
     * @tc.steps: step2. Select a text node
     */
    thirdTextAccessibilityProperty->ActActionSelect();
    EXPECT_EQ(pattern_->GetSelected(), 2);
    EXPECT_EQ(accessibilityProperty_->GetText(), "G");

    /**
     * @tc.steps: step3. Clear select
     */
    thirdTextAccessibilityProperty->ActActionClearSelection();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    /**
     * @tc.steps: step4. Change select "•"
     */
    fourthTextAccessibilityProperty->ActActionSelect();
    EXPECT_EQ(pattern_->GetSelected(), 3);
    EXPECT_EQ(accessibilityProperty_->GetText(), "H");

    /**
     * @tc.steps: step5. Change select
     */
    fifthTextAccessibilityProperty->ActActionSelect();
    EXPECT_EQ(pattern_->GetSelected(), 4);
    EXPECT_EQ(accessibilityProperty_->GetText(), "M");
}

/**
 * @tc.name: GetCollectionItemCounts001
 * @tc.desc: Indexer AccessibilityProperty GetCollectionItemCounts
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, GetCollectionItemCounts001, TestSize.Level1)
{
    RefPtr<IndexerAccessibilityProperty> indexerAccessibilityProperty =
        AceType::MakeRefPtr<IndexerAccessibilityProperty>();
    RefPtr<IndexerPattern> indexerPattern = AceType::MakeRefPtr<IndexerPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, indexerPattern);
    RefPtr<IndexerLayoutProperty> layoutProperty = AceType::MakeRefPtr<IndexerLayoutProperty>();
    layoutProperty->propActualArrayValue_ = std::nullopt;
    frameNode->layoutProperty_ = layoutProperty;
    indexerAccessibilityProperty->host_ = frameNode;
    auto result = indexerAccessibilityProperty->GetCollectionItemCounts();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: OnInjectionEvent001
 * @tc.desc: Test OnInjectionEvent
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, OnInjectionEvent001, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();

    pattern_->isHover_ = 1;
    auto ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","params": {"value": 1}})");
    EXPECT_EQ(ret, RET_SUCCESS);

    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","params": {"value": 1}})");
    EXPECT_EQ(ret, RET_SUCCESS);

    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","params": {"value": -1}})");
    EXPECT_EQ(ret, RET_FAILED);

    pattern_->itemCount_ = 3;
    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","params": {"value": 4444}})");
    EXPECT_EQ(ret, RET_FAILED);

    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexe","params": {"value": 1}})");
    EXPECT_EQ(ret, RET_FAILED);

    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","params": {"valu": 1}})");
    EXPECT_EQ(ret, RET_FAILED);

    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","params": {"value": "1"}})");
    EXPECT_EQ(ret, RET_FAILED);

    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","param": {"value": 2}})");
    EXPECT_EQ(ret, RET_FAILED);

    ret = pattern_->OnInjectionEvent(R"({"cmd":"setAlphabetIndexer","params": 3})");
    EXPECT_EQ(ret, RET_FAILED);
}

/**
 * @tc.name: ParseCommand001
 * @tc.desc: Test ParseCommand
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, ParseCommand001, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();

    int select = 0;
    auto ret = pattern_->ParseCommand(R"({"cmd":"setAlphabetIndexer","params": {"value": 1}})", select);
    EXPECT_EQ(ret, true);

    ret = pattern_->ParseCommand(R"({"cmd":"setAlphabetIndexer","params": {"valu": 1}})", select);
    EXPECT_EQ(ret, false);

    ret = pattern_->ParseCommand(R"({"cmd":"setAlphabetIndexer","params": {"value": "1"}})", select);
    EXPECT_EQ(ret, false);
}

namespace {
    const int32_t TEST_INDEX_START = 0;
    const int32_t TEST_INDEX_MIDDLE = 5;
    const int32_t TEST_INDEX_END = 9;
    const int32_t TEST_ARRAY_SIZE = 10;

    std::vector<std::string> CreateTestArray(int32_t size)
    {
        std::vector<std::string> testArray;
        for (int32_t i = 0; i < size; i++) {
            testArray.push_back(std::string(1, 'A' + i));
        }
        return testArray;
    }
}

/**
 * @tc.name: SetSpecificSupportAction001
 * @tc.desc: Test SetSpecificSupportAction when currentIndex is at start
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, SetSpecificSupportAction001, TestSize.Level1)
{
    auto testArray = CreateTestArray(TEST_ARRAY_SIZE);
    CreateIndexer(testArray, TEST_INDEX_START);
    CreateDone();
    accessibilityProperty_->SetSpecificSupportAction();
    auto supportActions = accessibilityProperty_->GetSupportAction();
    EXPECT_FALSE(supportActions.count(AceAction::ACTION_SCROLL_BACKWARD) > 0);
    EXPECT_TRUE(supportActions.count(AceAction::ACTION_SCROLL_FORWARD) > 0);
    accessibilityProperty_->ResetSupportAction();
}

/**
 * @tc.name: SetSpecificSupportAction002
 * @tc.desc: Test SetSpecificSupportAction when currentIndex is in middle
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, SetSpecificSupportAction002, TestSize.Level1)
{
    auto testArray = CreateTestArray(TEST_ARRAY_SIZE);
    CreateIndexer(testArray, TEST_INDEX_MIDDLE);
    CreateDone();
    accessibilityProperty_->SetSpecificSupportAction();
    auto supportActions = accessibilityProperty_->GetSupportAction();
    EXPECT_TRUE(supportActions.count(AceAction::ACTION_SCROLL_BACKWARD) > 0);
    EXPECT_TRUE(supportActions.count(AceAction::ACTION_SCROLL_FORWARD) > 0);
    accessibilityProperty_->ResetSupportAction();
}

/**
 * @tc.name: SetSpecificSupportAction003
 * @tc.desc: Test SetSpecificSupportAction when currentIndex is at end
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, SetSpecificSupportAction003, TestSize.Level1)
{
    auto testArray = CreateTestArray(TEST_ARRAY_SIZE);
    CreateIndexer(testArray, TEST_INDEX_END);
    CreateDone();
    accessibilityProperty_->SetSpecificSupportAction();
    auto supportActions = accessibilityProperty_->GetSupportAction();
    EXPECT_TRUE(supportActions.count(AceAction::ACTION_SCROLL_BACKWARD) > 0);
    EXPECT_FALSE(supportActions.count(AceAction::ACTION_SCROLL_FORWARD) > 0);
    accessibilityProperty_->ResetSupportAction();
}

/**
 * @tc.name: SetSpecificSupportAction004
 * @tc.desc: Test SetSpecificSupportAction with single element array
 * @tc.type: FUNC
 */
HWTEST_F(IndexerAccessibilityTestNg, SetSpecificSupportAction004, TestSize.Level1)
{
    CreateIndexer({ "A" }, TEST_INDEX_START);
    CreateDone();
    accessibilityProperty_->SetSpecificSupportAction();
    auto supportActions = accessibilityProperty_->GetSupportAction();
    EXPECT_FALSE(supportActions.count(AceAction::ACTION_SCROLL_BACKWARD) > 0);
    EXPECT_FALSE(supportActions.count(AceAction::ACTION_SCROLL_FORWARD) > 0);
    accessibilityProperty_->ResetSupportAction();
}
} // namespace OHOS::Ace::NG
