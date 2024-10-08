/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
void IndexerTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_INDEXER);
    auto indexerTheme = IndexerTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(indexerTheme));

    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    MockPipelineContext::GetCurrent()->fontManager_ = fontManager;
}

void IndexerTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void IndexerTestNg::SetUp()
{
    indexerTheme_ = MockPipelineContext::GetCurrent()->GetTheme<IndexerTheme>();
}

void IndexerTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    ClearOldNodes(); // Each testCase will create new list at begin
}

IndexerModelNG IndexerTestNg::CreateIndexer(std::vector<std::string> arrayValue, int32_t selected)
{
    ResetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    IndexerModelNG model;
    model.Create(arrayValue, selected);
    model.SetAutoCollapse(false);
    ViewAbstract::SetHeight(CalcLength(INDEXER_HEIGHT));
    GetIndexer();
    return model;
}

void IndexerTestNg::GetIndexer()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<IndexerPattern>();
    eventHub_ = frameNode_->GetEventHub<IndexerEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<IndexerLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<IndexerPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
}

void IndexerTestNg::OnPopupTouchDown(TouchType touchType)
{
    auto gesture = pattern_->popupNode_->GetOrCreateGestureEventHub();
    auto onPopupTouchDown = gesture->touchEventActuator_->touchEvents_.front()->GetTouchEventCallback();
    TouchEventInfo touchEventInfo = CreateTouchEventInfo(touchType, Offset());
    onPopupTouchDown(touchEventInfo);
}

RefPtr<FrameNode> IndexerTestNg::GetListItemNode(int32_t listItemIndex)
{
    auto listUINode = pattern_->popupNode_->GetLastChild()->GetFirstChild();
    auto listNode = AceType::DynamicCast<FrameNode>(listUINode);
    auto listItemNode = GetChildFrameNode(listNode, listItemIndex);
    return listItemNode;
}

void IndexerTestNg::ListItemClick(int32_t clickIndex, TouchType touchType)
{
    auto listItemNode = GetListItemNode(clickIndex);
    auto gesture = listItemNode->GetOrCreateGestureEventHub();
    auto touchEvent = gesture->touchEventActuator_->touchEvents_.front()->GetTouchEventCallback();
    TouchEventInfo touchEventInfo = CreateTouchEventInfo(touchType, Offset());
    touchEvent(touchEventInfo);
}

/**
 * @tc.name: IndexerPatternCoverage001
 * @tc.desc: For Coverage Rate, branches that are not normally covered.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerPatternCoverage001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    CreateDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step1. Supplement MoveIndexByOffset branch,
     * the itemCount_ would not be 0 when itemHeight_ was not 0.
     */
    pattern_->itemCount_ = 0;
    pattern_->MoveIndexByOffset(Offset(0, 0));
    pattern_->itemCount_ = GetLongArrayValue().size();

    /**
     * @tc.steps: step2. Supplement MoveIndexByStep branch,
     * has no condition that step is 0 when call panEvent_.
     */
    EXPECT_FALSE(pattern_->MoveIndexByStep(0));

    /**
     * @tc.steps: step3. Supplement GetFocusChildIndex branch,
     * has no condition that searchStr is ABC when MoveIndexBySearch.
     */
    pattern_->selected_ = 5;
    EXPECT_EQ(pattern_->GetFocusChildIndex("ABC"), -1);

    /**
     * @tc.steps: step4. Supplement OnSelect branch.
     * has no condition that selected_ more than itemCount_-1 when OnTouchUp.
     */
    pattern_->selected_ = GetLongArrayValue().size();
    pattern_->OnSelect();

    /**
     * @tc.steps: step5. Supplement OnSelect branch.
     * has no condition that selected_ less than 0 when OnTouchUp.
     */
    pattern_->selected_ = -1;
    pattern_->OnSelect();

    /**
     * @tc.steps: step6. Supplement UpdateBubbleSize branch,
     * has no condition that has no popListData when showPopup.
     */
    pattern_->MoveIndexBySearch("C");
    std::vector<std::string> bubbleData = std::vector<std::string>();
    pattern_->UpdateBubbleSize(bubbleData);
}

/**
 * @tc.name: IndexerEnableHapticFeedback001
 * @tc.desc: Test property enableHapticFeedback by default
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerEnableHapticFeedback001, TestSize.Level1)
{
    CreateIndexer(std::vector<std::string>());
    CreateDone();
    EXPECT_TRUE(pattern_->enableHapticFeedback_);
}

/**
 * @tc.name: IndexerEnableHapticFeedback002
 * @tc.desc: Test property enableHapticFeedback by Setter/Getter API
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerEnableHapticFeedback002, TestSize.Level1)
{
    std::vector<bool> testValues = { false, true, true, false, false };
    for (auto testValue : testValues) {
        IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 2);
        model.SetEnableHapticFeedback(testValue);
        CreateDone();
        EXPECT_EQ(pattern_->enableHapticFeedback_, testValue);
        auto indexerLayoutProperty = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
        auto value = indexerLayoutProperty->GetEnableHapticFeedback().value_or(!testValue);
        EXPECT_EQ(value, testValue);
    }
}
} // namespace OHOS::Ace::NG
