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
} // namespace OHOS::Ace::NG
