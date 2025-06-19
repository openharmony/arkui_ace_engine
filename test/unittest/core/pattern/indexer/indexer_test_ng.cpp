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
#include "test/mock/base/mock_system_properties.h"

namespace OHOS::Ace::NG {
void IndexerTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
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
    RemoveFromStageNode();
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
    eventHub_ = frameNode_->GetOrCreateEventHub<IndexerEventHub>();
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
    pattern_->UpdateBubbleSize();
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

/**
 * @tc.name: RemoveResourceObjTest001
 * @tc.desc: Verify IndexerModelNG::RemoveColor
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, RemoveResourceObjTest001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(std::vector<std::string>());
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::COLOR, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::SELECTED_COLOR, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::POPUP_COLOR, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::SELECTED_BACKGROUND_COLOR, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::POPUP_BACKGROUND, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::POPUP_UNSELECTED_COLOR, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::POPUP_SELECTED_COLOR, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::POPUP_ITEM_BACKGROUND_COLOR, resObj);
    IndexerModelNG::CreateWithResourceObj(frameNode, IndexerJsResourceType::POPUP_TITLE_BACKGROUND, resObj);
    model.RemoveColor(frameNode);
    model.RemovePopupColor(frameNode);
    model.RemoveSelectedColor(frameNode);
    model.RemoveSelectedBackgroundColor(frameNode);
    model.RemovePopupUnselectedColor(frameNode);
    model.RemovePopupBackground(frameNode);
    model.RemovePopupSelectedColor(frameNode);
    model.RemovePopupItemBackground(frameNode);
    model.RemovePopupTitleBackground(frameNode);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.Color"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.PopupColor"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.SelectedColor"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.SelectedBackgroundColor"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.PopupUnselectedColor"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.PopupBackground"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.PopupSelectedColor"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.PopupItemBackground"), "");
    EXPECT_EQ(pattern_->GetResCacheMapByKey("indexer.PopupTitleBackground"), "");
}

/**
 * @tc.name: IndexerSetColorByUser001
 * @tc.desc: Test property SetColorByUser UpdateThemeColor
 * @tc.type: FUNC
 */
HWTEST_F(IndexerTestNg, IndexerSetColorByUser001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 2);
    model.SetColor(std::optional<Color>(Color::RED));
    model.SetSelectedColor(std::optional<Color>(Color::RED));
    model.SetPopupColor(std::optional<Color>(Color::RED));
    model.SetSelectedBackgroundColor(std::optional<Color>(Color::RED));
    model.SetPopupUnselectedColor(std::optional<Color>(Color::RED));
    model.SetPopupSelectedColor(std::optional<Color>(Color::RED));
    model.SetPopupItemBackground(std::optional<Color>(Color::RED));
    model.SetPopupBackground(std::optional<Color>(Color::RED));
    model.SetPopupTitleBackground(std::optional<Color>(Color::RED));
    model.SetColorByUser(true);
    model.SetSelectedColorByUser(true);
    model.SetPopupColorByUser(true);
    model.SetSelectedBGColorByUser(true);
    model.SetPopupUnselectedColorByUser(true);
    model.SetPopupTitleBackgroundByUser(true);
    model.SetPopupSelectedColorByUser(true);
    model.SetPopupItemBackgroundColorByUser(true);
    model.SetPopupBackgroundColorByUser(true);
    pattern_->OnModifyDone();
    auto indexerLayoutProperty = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    ASSERT_NE(indexerLayoutProperty, nullptr);
    EXPECT_TRUE(indexerLayoutProperty->GetSetColorByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetSelectedColorByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetPopupColorByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetSelectedBGColorByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetPopupUnselectedColorByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetPopupTitleBackgroundByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetPopupSelectedColorByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetPopupItemBackgroundColorByUser().value_or(false));
    EXPECT_TRUE(indexerLayoutProperty->GetSetPopupBackgroundColorByUser().value_or(false));
    indexerLayoutProperty->UpdateSelected(1);
    pattern_->selected_ = 0;
    pattern_->UpdateThemeColor();
    auto paintProperty = pattern_->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    EXPECT_EQ(indexerLayoutProperty->GetColor(), Color::RED);
    EXPECT_EQ(indexerLayoutProperty->GetSelectedColor(), Color::RED);
    EXPECT_EQ(indexerLayoutProperty->GetPopupColor(), Color::RED);
    EXPECT_EQ(paintProperty->GetSelectedBackgroundColor(), Color::RED);
    EXPECT_EQ(paintProperty->GetPopupUnselectedColor(), Color::RED);
    EXPECT_EQ(paintProperty->GetPopupSelectedColor(), Color::RED);
    EXPECT_EQ(paintProperty->GetPopupItemBackground(), Color::RED);
    EXPECT_EQ(paintProperty->GetPopupBackground(), Color::RED);
    EXPECT_EQ(paintProperty->GetPopupTitleBackground(), Color::RED);

    model.SetColorByUser(false);
    model.SetSelectedColorByUser(false);
    model.SetPopupColorByUser(false);
    model.SetSelectedBGColorByUser(false);
    model.SetPopupUnselectedColorByUser(false);
    model.SetPopupTitleBackgroundByUser(false);
    model.SetPopupSelectedColorByUser(false);
    model.SetPopupItemBackgroundColorByUser(false);
    model.SetPopupBackgroundColorByUser(false);
    pattern_->OnModifyDone();
    indexerLayoutProperty->UpdateSelected(1);
    pattern_->selected_ = 1;
    pattern_->UpdateThemeColor();
    EXPECT_FALSE(indexerLayoutProperty->GetColor().has_value());
    EXPECT_FALSE(indexerLayoutProperty->GetSelectedColor().has_value());
    EXPECT_FALSE(indexerLayoutProperty->GetPopupColor().has_value());
    EXPECT_FALSE(paintProperty->GetSelectedBackgroundColor().has_value());
    EXPECT_FALSE(paintProperty->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty->GetPopupItemBackground().has_value());
    EXPECT_FALSE(paintProperty->GetPopupBackground().has_value());
    EXPECT_FALSE(paintProperty->GetPopupTitleBackground().has_value());
    g_isConfigChangePerform = false;
    CreateDone();
}
} // namespace OHOS::Ace::NG
