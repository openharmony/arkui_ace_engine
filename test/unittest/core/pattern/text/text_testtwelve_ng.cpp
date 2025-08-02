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

#include "foundation/arkui/ace_engine/test/mock/core/render/mock_paragraph.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "text_base.h"

#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {

const OffsetF DEFAULT_NEGATIVE_CARET_OFFSET { -1.0f, -1.0f };

class TextTwelveTestNg : public TextBases {};

/**
 * @tc.name: GetOrCreatePreviewMenuController_ControllerNotExist
 * @tc.desc: Test TextPattern GetOrCreatePreviewMenuController
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetOrCreatePreviewMenuController_ControllerNotExist, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Calling the GetOrCreatePreviewMenuController function
     * @tc.expected: The previewController_ should be created and returned.
     */
    auto result = pattern->GetOrCreatePreviewMenuController();
    EXPECT_EQ(result, pattern->previewController_);
}

/**
 * @tc.name: GetOrCreatePreviewMenuController_ControllerExist
 * @tc.desc: Test TextPattern GetOrCreatePreviewMenuController
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetOrCreatePreviewMenuController_ControllerExist, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the previewController_ of pattern
     */
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<PreviewMenuController> controller = AceType::MakeRefPtr<PreviewMenuController>(textPattern);
    pattern->previewController_ = controller;

    /**
     * @tc.steps: step3. Calling the GetOrCreatePreviewMenuController function
     * @tc.expected: The previewController_ should be created and returned.
     */
    auto result = pattern->GetOrCreatePreviewMenuController();
    EXPECT_EQ(result, pattern->previewController_);
}

/**
 * @tc.name: CanAIEntityDrag_IsPreviewMenuShow
 * @tc.desc: Test TextPattern CanAIEntityDrag
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, CanAIEntityDrag_IsPreviewMenuShow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the previewController_ of pattern
     * and set the IsPreviewMenuShow to return true
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->enablePreviewMenu_ = true;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(-2, -4);
    pattern->textSelector_ = textSelector;
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<PreviewMenuController> controller = AceType::MakeRefPtr<PreviewMenuController>(textPattern);
    controller->isShow_ = true;
    pattern->previewController_ = controller;

    /**
     * @tc.steps: step3. Calling the CanAIEntityDrag function
     * @tc.expected: The result return false
     */
    auto result = pattern->CanAIEntityDrag();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CanAIEntityDrag_IsNotPreviewMenuShow
 * @tc.desc: Test TextPattern CanAIEntityDrag
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, CanAIEntityDrag_IsNotPreviewMenuShow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the previewController_ of pattern
     * and set the IsPreviewMenuShow to return false
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->enablePreviewMenu_ = true;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(-2, -4);
    pattern->textSelector_ = textSelector;
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<PreviewMenuController> controller = AceType::MakeRefPtr<PreviewMenuController>(textPattern);
    controller->ClosePreviewMenu();
    pattern->previewController_ = controller;

    /**
     * @tc.steps: step3. Calling the CanAIEntityDrag function
     * @tc.expected: The result return false
     */
    auto result = pattern->CanAIEntityDrag();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CanAIEntityDrag_NeedShowAIDetect_False
 * @tc.desc: Test TextPattern CanAIEntityDrag
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, CanAIEntityDrag_NeedShowAIDetect_False, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the textDetectEnable_ and enabled_ of pattern to true
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->enablePreviewMenu_ = true;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(-2, -4);
    pattern->textSelector_ = textSelector;
    pattern->textDetectEnable_ = true;
    pattern->enabled_ = true;

    /**
     * @tc.steps: step3. Calling the CanAIEntityDrag function
     * @tc.expected: The result return false
     */
    auto result = pattern->CanAIEntityDrag();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CanAIEntityDrag_NeedShowAIDetect_True
 * @tc.desc: Test TextPattern CanAIEntityDrag
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, CanAIEntityDrag_NeedShowAIDetect_True, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the textDetectEnable_ and enabled_ of pattern to true
     * and set the aiSpanMap_ of dataDetectorAdapter
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->enablePreviewMenu_ = true;
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 6;
    aiSpan.params["key"] = "value";
    dataDetectorAdapter->aiSpanMap_[0] = aiSpan;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(-2, -4);
    pattern->textSelector_ = textSelector;
    pattern->textDetectEnable_ = true;
    pattern->enabled_ = true;

    /**
     * @tc.steps: step3. Calling the CanAIEntityDrag function
     * @tc.expected: The result return true
     */
    auto result = pattern->CanAIEntityDrag();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetSelectedAIData_Default
 * @tc.desc: Test TextPattern GetSelectedAIData
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetSelectedAIData_Default, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the value of aiStart equal to aiSpanMap_.end()
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->enablePreviewMenu_ = true;
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 6;
    aiSpan.params["key"] = "value";
    dataDetectorAdapter->aiSpanMap_[0] = aiSpan;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 1;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;

    /**
     * @tc.steps: step3. Calling the GetSelectedAIData function
     * @tc.expected: The result return AISpan()
     */
    auto result = pattern->GetSelectedAIData();
    EXPECT_EQ(result, AISpan());
}

/**
 * @tc.name: GetSelectedAIData_NotDefault
 * @tc.desc: Test TextPattern GetSelectedAIData
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetSelectedAIData_NotDefault, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the value of aiStart not equal to aiSpanMap_.end()
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 6;
    aiSpan.params["key"] = "value";
    dataDetectorAdapter->aiSpanMap_[0] = aiSpan;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 0;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;

    /**
     * @tc.steps: step3. Calling the GetSelectedAIData function
     * @tc.expected: The result return aiSpan
     */
    auto result = pattern->GetSelectedAIData();
    EXPECT_EQ(result, aiSpan);
}

/**
 * @tc.name: CreateAIEntityMenu_Nullptr
 * @tc.desc: Test TextPattern GetSelectedAIData
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, CreateAIEntityMenu_Nullptr, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the value of aiStart equal to aiSpanMap_.end()
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->enablePreviewMenu_ = true;
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 6;
    aiSpan.params["key"] = "value";
    dataDetectorAdapter->aiSpanMap_[0] = aiSpan;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 1;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;

    /**
     * @tc.steps: step3. Calling the CreateAIEntityMenu function
     * @tc.expected: The result return nullptr
     */
    auto result = pattern->CreateAIEntityMenu();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: CreateAIEntityMenu_Success
 * @tc.desc: Test TextPattern GetSelectedAIData
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, CreateAIEntityMenu_Success, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the value of aiStart not equal to aiSpanMap_.end()
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->enablePreviewMenu_ = true;
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 6;
    aiSpan.params["key"] = "value";
    dataDetectorAdapter->aiSpanMap_[0] = aiSpan;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 0;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;

    /**
     * @tc.steps: step3. Calling the CreateAIEntityMenu function
     * @tc.expected: The result return nullptr
     */
    auto result = pattern->CreateAIEntityMenu();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetRenderContext
 * @tc.desc: Test TextPattern GetRenderContext
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetRenderContext, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the renderContext_ of frameNode
     */
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    frameNode->renderContext_ = renderContext;

    /**
     * @tc.steps: step3. Calling the GetRenderContext function
     * @tc.expected: The result return not nullptr
     */
    auto result = pattern->GetRenderContext();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: UpdateAIMenuOptions_PrepareAIMenuOptions
 * @tc.desc: Test TextPattern UpdateAIMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, UpdateAIMenuOptions_PrepareAIMenuOptions, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set the NeedShowAIDetect to true
     * and set the copyOption_ to CopyOptions::Local
     */
    pattern->copyOption_ = CopyOptions::Local;
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    AISpan aiSpan;
    aiSpan.start = 0;
    aiSpan.end = 4;
    aiSpan.params["key"] = "value";
    dataDetectorAdapter->aiSpanMap_[3] = aiSpan;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    pattern->textDetectEnable_ = true;
    pattern->enabled_ = true;
    pattern->SetIsShowAIMenuOption(false);
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 3;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;

    /**
     * @tc.steps: step3. Calling the UpdateAIMenuOptions function
     * @tc.expected: The IsShowAIMenuOption return true
     */
    pattern->UpdateAIMenuOptions();
    EXPECT_TRUE(pattern->IsShowAIMenuOption());
}

/**
 * @tc.name: ClickAISpan_001
 * @tc.desc: Test TextPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ClickAISpan_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set rage.start less than aiSpan.start and rage.end equal to aiSpan.end
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetEllipsisTextRange()).WillOnce(testing::Return(std::make_pair(3, 5)));
    paragraphInfo.paragraph = paragraph;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the ClickAISpan function
     * @tc.expected: The result return false
     */
    AISpan aiSpan;
    aiSpan.start = 4;
    aiSpan.end = 5;
    aiSpan.params["key"] = "value";
    PointF textOffset(2.0f, 4.0f);
    auto result = pattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClickAISpan_002
 * @tc.desc: Test TextPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ClickAISpan_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set rage.start less than aiSpan.start and rage.end equal to aiSpan.start
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetEllipsisTextRange()).WillOnce(testing::Return(std::make_pair(3, 4)));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the ClickAISpan function
     * @tc.expected: The result return false
     */
    AISpan aiSpan;
    aiSpan.start = 4;
    aiSpan.end = 5;
    aiSpan.params["key"] = "value";
    PointF textOffset(2.0f, 4.0f);
    auto result = pattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClickAISpan_003
 * @tc.desc: Test TextPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ClickAISpan_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set rage.start less than aiSpan.start and rage.end less than aiSpan.start
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetEllipsisTextRange()).WillOnce(testing::Return(std::make_pair(2, 3)));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the ClickAISpan function
     * @tc.expected: The result return false
     */
    AISpan aiSpan;
    aiSpan.start = 4;
    aiSpan.end = 5;
    aiSpan.params["key"] = "value";
    PointF textOffset(2.0f, 4.0f);
    auto result = pattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClickAISpan_004
 * @tc.desc: Test TextPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ClickAISpan_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set rage.start less than aiSpan.end and rage.end greater than aiSpan.end
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetEllipsisTextRange()).WillOnce(testing::Return(std::make_pair(5, 6)));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the ClickAISpan function
     * @tc.expected: The result return false
     */
    AISpan aiSpan;
    aiSpan.start = 4;
    aiSpan.end = 5;
    aiSpan.params["key"] = "value";
    PointF textOffset(2.0f, 4.0f);
    auto result = pattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClickAISpan_005
 * @tc.desc: Test TextPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ClickAISpan_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set rage.start less than aiSpan.end and rage.end less than aiSpan.end
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetEllipsisTextRange()).WillOnce(testing::Return(std::make_pair(4, 5)));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the ClickAISpan function
     * @tc.expected: The result return false
     */
    AISpan aiSpan;
    aiSpan.start = 3;
    aiSpan.end = 6;
    aiSpan.params["key"] = "value";
    PointF textOffset(2.0f, 4.0f);
    auto result = pattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ClickAISpan_006
 * @tc.desc: Test TextPattern ClickAISpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ClickAISpan_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set rage.start greater than aiSpan.start and aiSpan.end
     */
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetEllipsisTextRange()).WillOnce(testing::Return(std::make_pair(4, 5)));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the ClickAISpan function
     * @tc.expected: The result return false
     */
    AISpan aiSpan;
    aiSpan.start = 1;
    aiSpan.end = 2;
    aiSpan.params["key"] = "value";
    PointF textOffset(2.0f, 4.0f);
    auto result = pattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ConvertHoverInfoFromMouseInfo_001
 * @tc.desc: Test TextPattern ConvertHoverInfoFromMouseInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ConvertHoverInfoFromMouseInfo_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set tiltX of MouseInfo to 2.0f
     */
    MouseInfo info;
    info.SetTiltX(2.0f);

    /**
     * @tc.steps: step3. Calling the ConvertHoverInfoFromMouseInfo function
     * @tc.expected: The tiltX of result return 2.0f
     */
    auto result = pattern->ConvertHoverInfoFromMouseInfo(info);
    EXPECT_EQ(result.GetTiltX().value(), 2.0f);
}

/**
 * @tc.name: ConvertHoverInfoFromMouseInfo_002
 * @tc.desc: Test TextPattern ConvertHoverInfoFromMouseInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ConvertHoverInfoFromMouseInfo_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set tiltY of MouseInfo to 2.0f
     */
    MouseInfo info;
    info.SetTiltY(2.0f);

    /**
     * @tc.steps: step3. Calling the ConvertHoverInfoFromMouseInfo function
     * @tc.expected: The tiltY of result return 2.0f
     */
    auto result = pattern->ConvertHoverInfoFromMouseInfo(info);
    EXPECT_EQ(result.GetTiltY().value(), 2.0f);
}

/**
 * @tc.name: ConvertHoverInfoFromMouseInfo_003
 * @tc.desc: Test TextPattern ConvertHoverInfoFromMouseInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ConvertHoverInfoFromMouseInfo_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set rollAngle of MouseInfo to 2.0f
     */
    MouseInfo info;
    info.SetRollAngle(2.0f);

    /**
     * @tc.steps: step3. Calling the ConvertHoverInfoFromMouseInfo function
     * @tc.expected: The rollAngle of result return 2.0f
     */
    auto result = pattern->ConvertHoverInfoFromMouseInfo(info);
    EXPECT_EQ(result.GetRollAngle().value(), 2.0f);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction_Pressed
 * @tc.desc: Test TextPattern HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, HandleMouseLeftReleaseAction_Pressed, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set isDoubleClick_ to false and hasClickedAISpan_ to true
     * and set the isMousePressed_ and leftMousePressed_ to true
     */
    AISpan aiSpan;
    aiSpan.start = 4;
    aiSpan.end = 5;
    aiSpan.params["key"] = "value";
    RefPtr<DataDetectorAdapter> dataDetectorAdapter = AceType::MakeRefPtr<DataDetectorAdapter>();
    dataDetectorAdapter->hasClickedAISpan_ = true;
    dataDetectorAdapter->aiSpanMap_[3] = aiSpan;
    pattern->dataDetectorAdapter_ = dataDetectorAdapter;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetEllipsisTextRange()).WillOnce(testing::Return(std::make_pair(2, 3)));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(testing::Return(0.0f));
    EXPECT_CALL(*paragraph, GetRectsForRange(testing::_, testing::_, testing::_))
        .WillRepeatedly(testing::Invoke([](int32_t start, int32_t end, std::vector<RectF>& rects) {
            rects.emplace_back(0.0f, 0.0f, 100.0f, 50.0f);
        }));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 0;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;
    pattern->mouseStatus_ = MouseStatus::PRESSED;
    pattern->status_ = Status::ON_DROP;
    pattern->isTryEntityDragging_ = false;
    pattern->isDoubleClick_ = false;
    pattern->isMousePressed_ = true;
    pattern->leftMousePressed_ = true;
    pattern->textDetectEnable_ = true;
    pattern->enabled_ = true;
    MouseInfo info;
    info.SetTiltX(2.0f);
    info.SetTiltY(4.0f);
    Offset textOffset(2.0, 4.0);

    /**
     * @tc.steps: step3. Calling the HandleMouseLeftReleaseAction function
     * @tc.expected: The isMousePressed_ and leftMousePressed_ be false
     */
    pattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_FALSE(pattern->isMousePressed_);
    EXPECT_FALSE(pattern->leftMousePressed_);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction_IsSelectedBindSelectionMenu
 * @tc.desc: Test TextPattern HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, HandleMouseLeftReleaseAction_IsSelectedBindSelectionMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateMaxLines(0);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set mouseStatus_ to MOVE
     * and set the IsSelectedBindSelectionMenu to return true
     */
    pattern->mouseStatus_ = MouseStatus::MOVE;
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 1;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    pattern->pManager_ = pManager;
    pattern->SetTextResponseType(TextResponseType::LONG_PRESS);
    pattern->selectedType_ = TextSpanType::TEXT;
    pattern->ClearSelectionMenu();
    std::pair<TextSpanType, TextResponseType> key =
        std::make_pair(TextSpanType::TEXT, TextResponseType::SELECTED_BY_MOUSE);
    auto buildFunc = []() {};
    auto onAppear = [](int32_t, int32_t) {};
    auto onDisappear = []() {};
    pattern->selectionMenuMap_[key] = std::make_shared<SelectionMenuParams>(
        TextSpanType::TEXT, buildFunc, onAppear, onDisappear, TextResponseType::SELECTED_BY_MOUSE);
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    WeakPtr<ScrollablePattern> scrollableParent = std::move(scrollablePattern);
    pattern->scrollableParent_ = scrollableParent;
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    WeakPtr<TextPattern> textBase = pattern->WeakClaim(AceType::RawPtr(textPattern));
    RefPtr<TextSelectOverlay> selectOverlay = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_ = selectOverlay;
    EXPECT_EQ(pattern->selectOverlay_->mouseMenuOffset_.GetX(), 0.0f);
    EXPECT_EQ(pattern->selectOverlay_->mouseMenuOffset_.GetX(), 0.0f);
    MouseInfo info;
    info.SetTiltX(2.0f);
    info.SetTiltY(4.0f);
    Offset offset(4.0, 8.0);
    info.SetGlobalLocation(offset);
    Offset textOffset(2.0, 4.0);

    /**
     * @tc.steps: step3. Calling the HandleMouseLeftReleaseAction function
     * @tc.expected: The textResponseType_ from LONG_PRESS to SELECTED_BY_MOUSE
     * and the selectOverlay_ of mouseMenuOffset_ from (0.0f, 0.0f) to (4.0f, 8.0f)
     */
    pattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(pattern->selectOverlay_->mouseMenuOffset_.GetX(), 4.0f);
    EXPECT_EQ(pattern->selectOverlay_->mouseMenuOffset_.GetY(), 8.0f);
    EXPECT_EQ(pattern->textResponseType_.value(), TextResponseType::SELECTED_BY_MOUSE);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction_SelectOverlayIsOn
 * @tc.desc: Test TextPattern HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, HandleMouseLeftReleaseAction_SelectOverlayIsOn, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set SelectOverlayIsOn function to return false
     */
    pattern->mouseStatus_ = MouseStatus::MOVE;
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 1;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    pattern->pManager_ = pManager;
    pattern->isAutoScrollByMouse_ = true;
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    WeakPtr<ScrollablePattern> scrollableParent = std::move(scrollablePattern);
    pattern->scrollableParent_ = scrollableParent;
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    WeakPtr<TextPattern> textBase = pattern->WeakClaim(AceType::RawPtr(textPattern));
    RefPtr<TextSelectOverlay> selectOverlay = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_ = selectOverlay;
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(node, nullptr);
    WeakPtr<FrameNode> weakNode = std::move(node);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->changeInfoListeners_.clear();
    context->changeInfoListeners_.emplace_back(weakNode);
    frameNode->context_ = AceType::RawPtr(context);
    MouseInfo info;
    info.SetTiltX(2.0f);
    info.SetTiltY(4.0f);
    Offset offset(4.0, 8.0);
    info.SetGlobalLocation(offset);
    Offset textOffset(2.0, 4.0);

    /**
     * @tc.steps: step3. Calling the HandleMouseLeftReleaseAction function
     * @tc.expected: The isAutoScrollByMouse_ of pattern from true to false
     */
    pattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_FALSE(pattern->isAutoScrollByMouse_);
    EXPECT_EQ(frameNode->context_->changeInfoListeners_.size(), 1);
    frameNode->context_ = nullptr;
}

/**
 * @tc.name: HandleMouseLeftMoveAction_IsMousePressed_True
 * @tc.desc: Test TextPattern HandleMouseLeftMoveAction
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, HandleMouseLeftMoveAction_IsMousePressed_True, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_FOCUSABLE);
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set isMousePressed_ to true
     * and set the moveOverClickThreshold_ to false
     */
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 1;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    pattern->pManager_ = pManager;
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    WeakPtr<ScrollablePattern> scrollableParent = std::move(scrollablePattern);
    pattern->scrollableParent_ = scrollableParent;
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    WeakPtr<TextPattern> textBase = pattern->WeakClaim(AceType::RawPtr(textPattern));
    RefPtr<TextSelectOverlay> selectOverlay = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_ = selectOverlay;
    pattern->copyOption_ = CopyOptions::Local;
    pattern->textEffect_ = nullptr;
    pattern->moveOverClickThreshold_ = false;
    pattern->isMousePressed_ = true;
    pattern->mouseStatus_ = MouseStatus::PRESSED;
    Offset offset(2.0, 4.0);
    pattern->leftMousePressedOffset_ = offset;
    MouseInfo info;
    info.SetTiltX(2.0f);
    info.SetTiltY(4.0f);
    info.SetGlobalLocation(offset);
    Offset textOffset(5.0, 8.0);

    /**
     * @tc.steps: step3. Calling the HandleMouseLeftMoveAction function
     * @tc.expected: The moveOverClickThreshold_ of pattern from false to true
     */
    pattern->HandleMouseLeftMoveAction(info, textOffset);
    EXPECT_TRUE(pattern->moveOverClickThreshold_);
}

/**
 * @tc.name: InitSpanStringTouchEvent
 * @tc.desc: Test TextPattern InitSpanStringTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, InitSpanStringTouchEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set spanStringTouchInitialized_ to false
     */
    pattern->spanStringTouchInitialized_ = false;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(testing::Return(0.0f));
    EXPECT_CALL(*paragraph, GetRectsForRange(testing::_, testing::_, testing::_))
        .WillRepeatedly(testing::Invoke([](int32_t start, int32_t end, std::vector<RectF>& rects) {
            rects.emplace_back(0.0f, 0.0f, 100.0f, 50.0f);
        }));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 3;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;
    pattern->SetSpanStringMode(true);
    RectF contentRect(2.0f, 4.0f, 100.0f, 50.0f);
    pattern->contentRect_ = contentRect;
    pattern->spans_.clear();
    RefPtr<SpanItem> span = AceType::MakeRefPtr<SpanItem>();
    span->position = -1;
    span->interval = std::make_pair(0, 4);
    span->onTouch = [](TouchEventInfo& info) { info.isTouchEventsEnd_ = true; };
    pattern->spans_.emplace_back(span);

    TouchEventInfo info("touch");
    info.isTouchEventsEnd_ = false;
    info.touches_.clear();
    TouchLocationInfo locationInfo("touchLocation", 2);
    Offset localLocation(4.0, 8.0);
    locationInfo.SetLocalLocation(localLocation);
    info.touches_.emplace_back(locationInfo);

    /**
     * @tc.steps: step3. Calling the InitSpanStringTouchEvent function
     * @tc.expected: The spanStringTouchInitialized_ of pattern from false to true
     * and the isTouchEventsEnd_ of TouchEventInfo from false to true
     */
    pattern->InitSpanStringTouchEvent();
    auto onTouch = gesture->touchEventActuator_->touchEvents_.back()->GetTouchEventCallback();
    ASSERT_NE(onTouch, nullptr);
    onTouch(info);
    EXPECT_TRUE(pattern->spanStringTouchInitialized_);
    EXPECT_TRUE(info.isTouchEventsEnd_);
}

/**
 * @tc.name: InitKeyEvent_HandleKey
 * @tc.desc: Test TextPattern InitKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, InitKeyEvent_HandleKey, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    frameNode->SetLayoutProperty(layoutProperty);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set spanStringTouchInitialized_ to false
     * and Set the pressedCodes of KeyEvent to { KEY_CTRL_LEFT, KEY_C }
     */
    pattern->keyEventInitialized_ = false;
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_C };

    /**
     * @tc.steps: step3. Calling the InitKeyEvent and onKey function
     * @tc.expected: The spanStringTouchInitialized_ of pattern from false to true
     * and the result return true
     */
    pattern->InitKeyEvent();
    auto onKey = focusHub->onKeyEventsInternal_[OnKeyEventType::DEFAULT];
    ASSERT_NE(onKey, nullptr);
    auto result = onKey(keyEvent);
    EXPECT_TRUE(pattern->keyEventInitialized_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: InitUrlTouchEvent_TouchTask
 * @tc.desc: Test TextPattern InitUrlTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, InitUrlTouchEvent_TouchTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set urlTouchEventInitialized_ to false
     */
    pattern->urlTouchEventInitialized_ = false;
    RefPtr<TextOverlayModifier> overlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    overlayModifier->selectedUrlRects_.clear();
    overlayModifier->selectedUrlRects_.emplace_back(RectF(0.0f, 0.0f, 100.0f, 50.0f));
    overlayModifier->selectedUrlRects_.emplace_back(RectF(0.0f, 0.0f, 100.0f, 50.0f));
    pattern->overlayMod_ = overlayModifier;
    EXPECT_EQ(pattern->overlayMod_->selectedUrlRects_.size(), 2);
    pattern->status_ = Status::FLOATING;
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    WeakPtr<TextPattern> textBase = pattern->WeakClaim(AceType::RawPtr(textPattern));
    RefPtr<TextSelectOverlay> selectOverlay = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_ = selectOverlay;

    TouchEventInfo info("touch");
    info.touches_.clear();
    TouchLocationInfo locationInfo("touchLocation", 1);
    locationInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_back(locationInfo);
    auto touchType = info.GetTouches().front().GetTouchType();
    EXPECT_EQ(touchType, TouchType::UP);

    /**
     * @tc.steps: step3. Calling the InitUrlTouchEvent function
     * @tc.expected: The urlTouchEventInitialized_ of pattern from false to true
     * and the selectedUrlRects_.size() of overlayMod_ from 2 to 0
     */
    pattern->InitUrlTouchEvent();
    auto onUrlTouch = gesture->touchEventActuator_->touchEvents_.back()->GetTouchEventCallback();
    ASSERT_NE(onUrlTouch, nullptr);
    onUrlTouch(info);
    EXPECT_TRUE(pattern->urlTouchEventInitialized_);
    EXPECT_EQ(pattern->overlayMod_->selectedUrlRects_.size(), 0);
}

/**
 * @tc.name: InitTouchEvent_TouchTask
 * @tc.desc: Test TextPattern InitTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, InitTouchEvent_TouchTask, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set touchEventInitialized_ to false
     */
    pattern->touchEventInitialized_ = false;
    pattern->isSelecting_ = false;
    pattern->isStarted_ = true;
    pattern->selectingFingerId_ = 0;
    OffsetF position(2.0f, 4.0f);
    pattern->originCaretPosition_ = position;
    pattern->minMoveDistance_ = 3.0_vp;
    Offset startOffset(0.0, 0.0);
    pattern->StartGestureSelection(1, 2, startOffset);

    TouchEventInfo info("touch");
    info.SetSourceDevice(SourceType::TOUCH);
    info.changedTouches_.clear();
    TouchLocationInfo locationInfo("touchLocation", 1);
    Offset localLocation(3.0, 4.0);
    locationInfo.SetLocalLocation(localLocation);
    locationInfo.SetTouchType(TouchType::MOVE);
    info.changedTouches_.emplace_back(locationInfo);
    auto touchType = info.GetChangedTouches().front().GetTouchType();
    EXPECT_EQ(touchType, TouchType::MOVE);

    /**
     * @tc.steps: step3. Calling the InitTouchEvent function
     * @tc.expected: The touchEventInitialized_ and isSelecting_ be true
     * and the originCaretPosition_ be DEFAULT_NEGATIVE_CARET_OFFSET and selectingFingerId_ be 1
     */
    pattern->InitTouchEvent();
    auto onTouch = gesture->touchEventActuator_->touchEvents_.back()->GetTouchEventCallback();
    ASSERT_NE(onTouch, nullptr);
    onTouch(info);
    EXPECT_TRUE(pattern->touchEventInitialized_);
    EXPECT_EQ(pattern->originCaretPosition_, DEFAULT_NEGATIVE_CARET_OFFSET);
    EXPECT_TRUE(pattern->isSelecting_);
    EXPECT_EQ(pattern->selectingFingerId_, 1);
}

/**
 * @tc.name: HandleKeyEvent_Marquee
 * @tc.desc: Test TextPattern HandleKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, HandleKeyEvent_Marquee, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(textLayoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextOverflow to MARQUEE
     * and Set the pressedCodes of KeyEvent to { KeyCode::KEY_A };
     */
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    pattern->textEffect_ = nullptr;
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_A };

    /**
     * @tc.steps: step3. Calling the HandleKeyEvent function
     * @tc.expected: The result return false
     */
    auto result = pattern->HandleKeyEvent(keyEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleKeyEvent_False
 * @tc.desc: Test TextPattern HandleKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, HandleKeyEvent_False, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textNode->SetLayoutProperty(textLayoutProperty);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set TextOverflow to ELLIPSIS
     * and Set the pressedCodes of KeyEvent to { KeyCode::KEY_A, KeyCode::KEY_B, KeyCode::KEY_C };
     */
    SystemProperties::textTraceEnable_ = true;
    auto layoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    pattern->textEffect_ = nullptr;
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B, KeyCode::KEY_C };

    /**
     * @tc.steps: step3. Calling the HandleKeyEvent function
     * @tc.expected: The result return false
     */
    auto result = pattern->HandleKeyEvent(keyEvent);
    SystemProperties::textTraceEnable_ = false;
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDragStartNoChild_GetIsTextDraggable_False
 * @tc.desc: Test TextPattern GetIsTextDraggable
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, OnDragStartNoChild_GetIsTextDraggable_False, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    frameNode->eventHub_ = eventHub;
    auto hub = frameNode->GetEventHub<EventHub>();
    auto gesture = hub->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set event and extraParams
     */

    RefPtr<Ace::DragEvent> event;
    std::string extraParams = "extraParams";

    /**
     * @tc.steps: step3. Calling the OnDragStartNoChild function
     * @tc.expected: The onlyForLifting and delayCreating of result return false
     */
    auto result = pattern->OnDragStartNoChild(event, extraParams);
    EXPECT_FALSE(result.onlyForLifting);
    EXPECT_FALSE(result.delayCreating);
}

/**
 * @tc.name: GetTextBoxes_IsAiSelected
 * @tc.desc: Test TextPattern GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetTextBoxes_IsAiSelected, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set textSelector and pManager
     */
    TextSelector textSelector(2, 4);
    textSelector.aiStart = 0;
    textSelector.aiEnd = 4;
    pattern->textSelector_ = textSelector;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(testing::Return(0.0f));
    EXPECT_CALL(*paragraph, GetRectsForRange(testing::_, testing::_, testing::_))
        .WillRepeatedly(testing::Invoke([](int32_t start, int32_t end, std::vector<RectF>& rects) {
            rects.emplace_back(0.0f, 0.0f, 100.0f, 50.0f);
        }));
    paragraphInfo.paragraph = paragraph;
    paragraphInfo.start = 3;
    paragraphInfo.end = 5;
    std::vector<ParagraphManager::ParagraphInfo> paragraphs = { paragraphInfo };
    pManager->SetParagraphs(paragraphs);
    pattern->pManager_ = pManager;

    /**
     * @tc.steps: step3. Calling the GetTextBoxes function
     * @tc.expected: The front() of result return {0.0f, 0.0f, 100.0f, 50.0f};
     */
    RectF res(0.0f, 0.0f, 100.0f, 50.0f);
    auto result = pattern->GetTextBoxes();
    EXPECT_EQ(result.front(), res);
}

/**
 * @tc.name: BetweenSelectedPosition_HasRenderTransform
 * @tc.desc: Test TextPattern BetweenSelectedPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, BetweenSelectedPosition_HasRenderTransform, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set hasTransform_ of selectOverlay_ to true
     */
    frameNode->renderContext_ = RenderContext::Create();
    string path = "M 0,0 L 100,0 L 100,50 L 0,50 Z";
    MotionPathOption motionPathOption(path, 1.0f, 4.0f, false);
    frameNode->renderContext_->UpdateMotionPath(motionPathOption);
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    WeakPtr<TextPattern> textBase = pattern->WeakClaim(AceType::RawPtr(textPattern));
    RefPtr<TextSelectOverlay> selectOverlay = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_ = selectOverlay;
    pattern->selectOverlay_->hasTransform_ = true;
    /**
     * @tc.steps: step3. Calling the BetweenSelectedPosition function
     * @tc.expected: The result return false
     */
    Offset globalOffset(2.0, 4.0);
    auto result = pattern->BetweenSelectedPosition(globalOffset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper_HasSpanOnHoverEvent
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, BeforeCreateLayoutWrapper_HasSpanOnHoverEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    frameNode->eventHub_ = eventHub;
    auto hub = frameNode->GetEventHub<EventHub>();
    hub->GetOrCreateInputEventHub();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set spanMouseEventInitialized_ to false
     */
    pattern->isSpanStringMode_ = true;
    pattern->spanMouseEventInitialized_ = false;
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    WeakPtr<TextPattern> textBase = pattern->WeakClaim(AceType::RawPtr(textPattern));
    RefPtr<TextSelectOverlay> selectOverlay = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_ = selectOverlay;
    pattern->spans_.clear();
    RefPtr<SpanItem> span = AceType::MakeRefPtr<SpanItem>();
    auto onHoverFunc = [](bool isHover, HoverInfo& info) {
        if (isHover) {
            info.SetLocalLocation(Offset(2.0, 4.0));
        } else {
            info.SetGlobalLocation(Offset(0.0, 0.0));
        }
    };
    span->onHover = onHoverFunc;
    pattern->spans_.emplace_back(span);

    /**
     * @tc.steps: step3. Calling the BeforeCreateLayoutWrapper function
     * @tc.expected: The spanMouseEventInitialized_ be true
     */
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(pattern->spanMouseEventInitialized_);
}

/**
 * @tc.name: ResetTextEffectBeforeLayout_001
 * @tc.desc: Test TextPattern ResetTextEffectBeforeLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ResetTextEffectBeforeLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set TextEffectStrategy to NONE
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::NONE);
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();
    RefPtr<SpanItem> span = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.emplace_back(span);

    /**
     * @tc.steps: step3. Calling the ResetTextEffectBeforeLayout function
     * @tc.expected: The result return true and textEffect_ be nullptr
     */
    auto result = pattern->ResetTextEffectBeforeLayout(false);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetTextEffectBeforeLayout_002
 * @tc.desc: Test TextPattern ResetTextEffectBeforeLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ResetTextEffectBeforeLayout_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set TextOverflow to MARQUEE
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();
    RefPtr<SpanItem> span = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.emplace_back(span);

    /**
     * @tc.steps: step3. Calling the ResetTextEffectBeforeLayout function
     * @tc.expected: The result return true and textEffect_ be nullptr
     */
    auto result = pattern->ResetTextEffectBeforeLayout(false);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetTextEffectBeforeLayout_003
 * @tc.desc: Test TextPattern ResetTextEffectBeforeLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ResetTextEffectBeforeLayout_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set spans_ is not empty
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();
    RefPtr<SpanItem> span = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.emplace_back(span);

    /**
     * @tc.steps: step3. Calling the ResetTextEffectBeforeLayout function
     * @tc.expected: The result return true and textEffect_ be nullptr
     */
    auto result = pattern->ResetTextEffectBeforeLayout(false);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetTextEffectBeforeLayout_004
 * @tc.desc: Test TextPattern ResetTextEffectBeforeLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ResetTextEffectBeforeLayout_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set isSpanStringMode_ to true
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    pattern->isSpanStringMode_ = true;
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();

    /**
     * @tc.steps: step3. Calling the ResetTextEffectBeforeLayout function
     * @tc.expected: The result return true and textEffect_ be nullptr
     */
    auto result = pattern->ResetTextEffectBeforeLayout(false);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetTextEffectBeforeLayout_005
 * @tc.desc: Test TextPattern ResetTextEffectBeforeLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ResetTextEffectBeforeLayout_005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set externalParagraph_ to paraPtr
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    pattern->isSpanStringMode_ = false;
    struct ExternalParagraph {
        int32_t data;
    };
    ExternalParagraph externalPara;
    void* paraPtr = &externalPara;
    pattern->SetExternalParagraph(paraPtr);
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();

    /**
     * @tc.steps: step3. Calling the ResetTextEffectBeforeLayout function
     * @tc.expected: The result return true and textEffect_ be nullptr
     */
    auto result = pattern->ResetTextEffectBeforeLayout(false);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetTextEffectBeforeLayout_006
 * @tc.desc: Test TextPattern ResetTextEffectBeforeLayout
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, ResetTextEffectBeforeLayout_006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->SetPrivacySensitive(true);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set isSensitive_ to true
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    pattern->isSpanStringMode_ = false;
    pattern->externalParagraph_ = std::nullopt;
    pattern->isSensitive_ = true;
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();

    /**
     * @tc.steps: step3. Calling the ResetTextEffectBeforeLayout function
     * @tc.expected: The result return true and textEffect_ be nullptr
     */
    auto result = pattern->ResetTextEffectBeforeLayout(false);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetOrCreateTextEffect_001
 * @tc.desc: Test TextPattern GetOrCreateTextEffect
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetOrCreateTextEffect_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->SetPrivacySensitive(false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set ResetTextEffectBeforeLayout function to return true
     * and Set spans_ to not empty
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    pattern->isSpanStringMode_ = false;
    pattern->externalParagraph_ = std::nullopt;
    pattern->isSensitive_ = true;
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();
    RefPtr<SpanItem> span = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.emplace_back(span);
    std::u16string content = u"Test content";
    bool needUpdateTypography = true;

    /**
     * @tc.steps: step3. Calling the GetOrCreateTextEffect function
     * @tc.expected: The result return nullptr and textEffect_ be nullptr
     */
    auto result = pattern->GetOrCreateTextEffect(content, needUpdateTypography);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetOrCreateTextEffect_002
 * @tc.desc: Test TextPattern GetOrCreateTextEffect
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetOrCreateTextEffect_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->SetPrivacySensitive(false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set content to empty string
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    pattern->isSpanStringMode_ = false;
    pattern->externalParagraph_ = std::nullopt;
    pattern->isSensitive_ = true;
    pattern->textEffect_ = TextEffect::CreateTextEffect();
    pattern->spans_.clear();
    std::u16string content = u"";
    bool needUpdateTypography = true;

    /**
     * @tc.steps: step3. Calling the GetOrCreateTextEffect function
     * @tc.expected: The result return nullptr and textEffect_ be nullptr
     */
    auto result = pattern->GetOrCreateTextEffect(content, needUpdateTypography);
    EXPECT_EQ(pattern->textEffect_, nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetOrCreateTextEffect_003
 * @tc.desc: Test TextPattern GetOrCreateTextEffect
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, GetOrCreateTextEffect_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextLayoutProperty> layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    frameNode->SetLayoutProperty(layoutProperty);
    frameNode->SetPrivacySensitive(false);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.steps: step2. Set textEffect_ to nullptr and content to "123"
     */
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::DEFAULT);
    pattern->isSpanStringMode_ = false;
    pattern->externalParagraph_ = std::nullopt;
    pattern->isSensitive_ = true;
    pattern->textEffect_ = nullptr;
    pattern->spans_.clear();
    RefPtr<SelectOverlayProxy> overlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(2);
    pattern->selectOverlayProxy_ = overlayProxy;
    TextSelector textSelector(2, 4);
    pattern->textSelector_ = textSelector;
    std::u16string content = u"123";
    bool needUpdateTypography = true;

    /**
     * @tc.steps: step3. Calling the GetOrCreateTextEffect function
     * @tc.expected: The result return not nullptr and textEffect_ be not nullptr
     */
    auto result = pattern->GetOrCreateTextEffect(content, needUpdateTypography);
    EXPECT_NE(pattern->textEffect_, nullptr);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: RegularMatchNumbers_for
 * @tc.desc: Test TextPattern RegularMatchNumbers
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, RegularMatchNumbers_for, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Set content to "12a3"
     */
    std::u16string content = u"12a3";

    /**
     * @tc.steps: step3. Calling the RegularMatchNumbers function
     * @tc.expected: The result return not nullptr and textEffect_ be not nullptr
     */
    auto result = pattern->RegularMatchNumbers(content);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetSpanEventFlagValue_OnClickAndPressCallback
 * @tc.desc: Test TextPattern SetSpanEventFlagValue
 * @tc.type: FUNC
 */
HWTEST_F(TextTwelveTestNg, SetSpanEventFlagValue_OnClickAndPressCallback, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto pattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto hub = textNode->GetOrCreateFocusHub();

    /**
     * @tc.steps: step2. Set isSpanHasClick and isSpanHasLongPress to false
     */
    auto onClickEventCallback = [](GestureEvent& func) {};
    auto onSpanLongPressEventCallback = [](GestureEvent& func) {};
    hub->SetOnClickCallback(std::move(onClickEventCallback));
    hub->SetOnLongPressCallback(std::move(onSpanLongPressEventCallback));
    bool isSpanHasClick = false;
    bool isSpanHasLongPress = false;

    /**
     * @tc.steps: step3. Calling the SetSpanEventFlagValue function
     * @tc.expected: The isSpanHasClick and isSpanHasLongPress return true
     */
    pattern->SetSpanEventFlagValue(textNode, isSpanHasClick, isSpanHasLongPress);
    EXPECT_TRUE(isSpanHasClick);
    EXPECT_TRUE(isSpanHasLongPress);
}
} // namespace OHOS::Ace::NG