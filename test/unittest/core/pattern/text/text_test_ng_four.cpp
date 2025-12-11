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

#include "text_base.h"

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {

class TextTestNgFour : public TextBases {
public:
};

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2.call OnVisibleChange function
     * @tc.expected: selectOverlay is closed
     */
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);
    pattern->OnVisibleChange(false);

    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);

    /**
     * @tc.steps: step3. create MouseEvent and call HandleMouseEvent function when copyOption is none
     * @tc.expected: selectOverlay is closed
     */
    MouseInfo info;
    info.localLocation_ = Offset(1, 1);
    pattern->copyOption_ = copyOption;
    pattern->HandleMouseEvent(info);

    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is not none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleMouseEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: selectOverlay is not closed
     */
    MouseInfo info;
    info.localLocation_ = Offset(2, 2);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::PRESS;
    pattern->HandleMouseEvent(info);

    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent003
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is not none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleMouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 0 });

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: selectOverlay is not closed
     */
    MouseInfo info;
    // none none
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::NONE_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);

    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // left none
    pattern->textSelector_.Update(0, 3);
    info.localLocation_ = Offset(2, 2);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);

    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // right none
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);

    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // left press
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    // left move
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::MOVE;
    pattern->blockPress_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    pattern->textSelector_.Update(0, 3);
    pattern->blockPress_ = false;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    // left RELEASE
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->blockPress_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);

    pattern->textSelector_.Update(0, 3);
    pattern->blockPress_ = false;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent004
 * @tc.desc: test test_pattern.h HandleMouseEvent function when isDoubleClick_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleMouseEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: isDoubleClick_ is false
     */
    MouseInfo info;
    // left RELEASE
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->blockPress_ = true;
    pattern->isDoubleClick_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_FALSE(pattern->isDoubleClick_);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent005
 * @tc.desc: test test_pattern.h HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleMouseEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, InitMouseEvent.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    auto host = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();
    auto inputHub = host->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    inputHub->mouseEventActuator_->inputEvents_.clear();
    pattern->mouseEventInitialized_ = false;
    pattern->InitMouseEvent();
    auto mouseEvent = inputHub->mouseEventActuator_->inputEvents_.back();

    AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_START;
    aiSpan1.end = AI_SPAN_END;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    AISpan aiSpan2;
    aiSpan2.start = AI_SPAN_START_II;
    aiSpan2.end = AI_SPAN_END_II;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->aiSpanMap_[AI_SPAN_START] = aiSpan1;
    pattern->dataDetectorAdapter_->aiSpanMap_[AI_SPAN_START_II] = aiSpan2;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 40, 40) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: MouseInfo localLocation is in GetRectsForRange region, expect MouseRightButton release event
     *     captured by AISpan.
     */
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    (*mouseEvent)(info);
    info.SetLocalLocation(Offset(5.f, 5.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    (*mouseEvent)(info);
    EXPECT_TRUE(pattern->dataDetectorAdapter_->hasClickedAISpan_);

    /**
     * @tc.steps: step3. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: MouseInfo localLocation is not in GetRectsForRange region.
     */
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    info.SetLocalLocation(Offset(60.f, 60.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    (*mouseEvent)(info);
    EXPECT_TRUE(!pattern->dataDetectorAdapter_->hasClickedAISpan_);
    EXPECT_EQ(pattern->textResponseType_, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(pattern->selectedType_, TextSpanType::TEXT);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleMouseEvent006
 * @tc.desc: test test_pattern.h HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleMouseEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, add child imageSpanNode.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    auto host = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = host->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 40, 40) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    ImageSpanNodeProperty firstProperty { .imageSrc = std::make_optional("image") };
    auto imageSpanNode = CreateImageSpanNode(firstProperty);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    ImageSpanNodeProperty secondProperty { .pixelMap = std::make_optional(PixelMap::CreatePixelMap(nullptr)),
        .imageFit = std::make_optional(ImageFit::FILL) };
    imageSpanNode = CreateImageSpanNode(secondProperty);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    pattern->CreateHandles();

    /**
     * @tc.steps: step2. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: expect selectedType_ IMAGE when mouse release offset not in textContentRect region.
     */
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 30 });
    auto inputHub = host->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    inputHub->mouseEventActuator_->inputEvents_.clear();
    pattern->mouseEventInitialized_ = false;
    pattern->InitMouseEvent();
    auto mouseEvent = inputHub->mouseEventActuator_->inputEvents_.back();
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    (*mouseEvent)(info);
    info.SetLocalLocation(Offset(40.f, 40.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->contentRect_ = { 30, 30, 20, 20 };
    (*mouseEvent)(info);
    EXPECT_EQ(pattern->textResponseType_, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(pattern->selectedType_, TextSpanType::IMAGE);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test test_pattern.h HandleOnCopy function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleOnCopy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. call HandleOnCopy function when textSelector is valid and textStart is equal to textEnd
     * @tc.steps: step3. call HandleOnCopy function when textSelector is not valid and textStart < 0.
     * @tc.expected: selectOverlay is closed.
     */
    std::vector<std::vector<int32_t>> params = { { 2, 2 }, { 1, 20 }, { -1, -1 } };
    for (int turn = 0; turn < params.size(); turn++) {
        pattern->textSelector_.Update(params[turn][0], params[turn][1]);
        pattern->HandleOnCopy();
        if (turn == 0) {
            EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
            EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
        } else if (turn == 1) {
            EXPECT_EQ(pattern->textSelector_.GetTextStart(), 1);
            EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
        } else {
            EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
            EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
        }
    }
}

/**
 * @tc.name: HandleOnCopy002
 * @tc.desc: test test_pattern.h HandleOnCopy function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleOnCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. call HandleOnCopy function with valid textSelector and copyOption
     * @tc.expected: selectOverlay is closed
     */
    pattern->textSelector_.Update(0, 6);
    pattern->textForDisplay_ = u"TestHandleOnCopy";
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->HandleOnCopy();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 6);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test text_pattern.h HandleLongPress function when IsDraggable is false
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleLongPress001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    frameNode->draggable_ = false;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 3);
    pattern->textForDisplay_ = TEXT_U16CONTENT;
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    EXPECT_FALSE(pattern->IsDraggable(info.GetLocalLocation()));

    /**
     * @tc.steps: step2. call HandleLongPress function
     * @tc.expected: The function exits normally
     */
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 1);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: test text_pattern.h HandleLongPress function when IsDraggable is true
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleLongPress002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream).WillRepeatedly(Return(true));
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream).WillRepeatedly(Return(true));
    EXPECT_CALL(*paragraph, GetWordBoundary).WillRepeatedly(Return(false));
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).Times(1).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    frameNode->draggable_ = true;
    frameNode->GetEventHub<EventHub>()->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 3);
    pattern->textForDisplay_ = TEXT_U16CONTENT;
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    /**
     * @tc.steps: step2. call HandleLongPress function
     * @tc.expected: The function exits normally
     */
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleOnSelectAll001
 * @tc.desc: Test TextPattern HandleOnSelectAll when selectOverlayProxy is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleOnSelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"TestHandleOnSelectAll";
    pattern->selectOverlayProxy_ = nullptr;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    /**
     * @tc.steps: step3. call HandleOnSelectAll
     * @tc.expected:The function exits normally
     */
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), pattern->textForDisplay_.length());
    pattern->pManager_->Reset();
}

/**
 * @tc.name: HandleOnSelectAll002
 * @tc.desc: Test TextPattern HandleOnSelectAll when selectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, HandleOnSelectAll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    /**
     * @tc.steps: step2. construct a SelectOverlayManager and rootNode
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step3. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    pattern->textForDisplay_ = u"TestHandleOnSelectAll";

    /**
     * @tc.steps: step4. call HandleOnSelectAll
     * @tc.expected:textSelector updates successfully
     */
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 21);

    /**
     * @tc.steps: step5. call CloseSelectOverlay
     * @tc.expected: Related function is called
     */
    pattern->CloseSelectOverlay();
    EXPECT_TRUE(pattern->selectOverlayProxy_->IsClosed());
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Text Accessibility PerformAction test Select ClearSelection and Copy.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text, get text frameNode and pattern, set callback function.
     * @tc.expected: FrameNode and pattern is not null, related function is called.
     */
    MockPipelineContext::GetCurrent()->rootNode_ =
        FrameNode::CreateFrameNodeWithTree(V2::ROOT_ETS_TAG, 0, AceType::MakeRefPtr<RootPattern>());
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::None);
    textPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get text accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. When text CopyOptions is None, call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(1, TEXT_SIZE_INT));
    EXPECT_TRUE(textAccessibilityProperty->ActActionClearSelection());
    EXPECT_TRUE(textAccessibilityProperty->ActActionCopy());

    /**
     * @tc.steps: step4. When text CopyOptions is InApp, call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(-1, -1));
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(1, TEXT_SIZE_INT));
    EXPECT_TRUE(textAccessibilityProperty->ActActionClearSelection());
    EXPECT_TRUE(textAccessibilityProperty->ActActionCopy());
}

/**
 * @tc.name: TextSelectorTest001
 * @tc.desc: test Update function in TextSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextSelectorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text.
     */
    TextModelNG textModel;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: textSelector_ update successfully.
     */
    textPattern->textSelector_.Update(0);
    EXPECT_EQ(textPattern->textSelector_.baseOffset, 0);

    textPattern->textSelector_.Update(0, TEXT_SIZE_INT);
    EXPECT_EQ(textPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(textPattern->textSelector_.destinationOffset, TEXT_SIZE_INT);
}

/**
 * @tc.name: TextPaintMethodTest003
 * @tc.desc: test text_paint_method.cpp UpdateContentModifier function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextPaintMethodTest003, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create textFrameNode and geometryNode.
     */
    auto [host, pattern] = Init();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. set textForDisplay_ to EMPTY_TEXT.
     */
    pattern->textForDisplay_ = u"";

    /**
     * @tc.steps: step3. push UNKNOWN_REASON and PLACEHOLDER to reasons.
     *                   set obscured of renderContext to reasons.
     */
    std::vector<ObscuredReasons> reasons;
    reasons.push_back((ObscuredReasons)UNKNOWN_REASON);
    reasons.push_back(ObscuredReasons::PLACEHOLDER);
    renderContext->UpdateObscured(reasons);

    /**
     * @tc.steps: step4. create textPaintMethod and call UpdateContentModifier function.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is empty.
     */
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(textContentModifier->drawObscuredRects_, std::vector<RectF>());

    /**
     * @tc.steps: step5. set textForDisplay_ to CREATE_VALUE.
     */
    pattern->textForDisplay_ = CREATE_VALUE_W;

    /**
     * @tc.steps: step6. call UpdateContentModifier function.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is not empty.
     */
    renderContext = host->GetRenderContext();
    paintProperty = pattern->CreatePaintProperty();
    paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    TextPaintMethod textPaintMethod1(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textPaintMethod1.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_NE(textContentModifier->drawObscuredRects_, std::vector<RectF>());

    /**
     * @tc.steps: step7. call OnModifyDone function.
     * @tc.expected: The obscured of renderContext is reasons.
     */
    pattern->OnModifyDone();
    EXPECT_EQ(renderContext->GetObscured(), reasons);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier004
 * @tc.desc: test text_content_modifier.cpp DrawObscuration function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. set context and paragraph.
     *                   set defaultFontSize defaultTextColor and contentSize of textContentModifier.
     *                   push one rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    TextStyle textStyle;
    textStyle.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textContentModifier->SetDefaultAnimatablePropertyValue(textStyle, textFrameNode);
    SizeF contentSize(TEXT_CONTENT_SIZE, TEXT_CONTENT_SIZE);
    textContentModifier->SetContentSize(contentSize);
    std::vector<RectF> drawObscuredRects;
    RectF textRect;
    textRect.SetHeight(TEXT_RECT_WIDTH);
    textRect.SetWidth(TEXT_RECT_WIDTH);
    textRect.SetTop(TEXT_RECT_TOP_ONE);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step3. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step4. push two rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    drawObscuredRects.push_back(textRect);
    textRect.SetTop(TEXT_RECT_TOP_TWO);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step5. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step6. push three rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    textRect.SetHeight(TEXT_RECT_SIZE_ZEOR);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step7. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step8. push four rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    textRect.SetWidth(TEXT_RECT_SIZE_ZEOR);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step9. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier005
 * @tc.desc: test text_content_modifier.cpp SetImageSpanNodeList function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
    textPattern->SetImageSpanNodeList(imageNodeList);
    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 1.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));

    ASSERT_NE(textPaintMethod->textContentModifier_, nullptr);
    EXPECT_EQ(textPaintMethod->textContentModifier_->imageNodeList_.size(), 1);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextOverlayModifierTest002
 * @tc.desc: test IsSelectedRectsChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextOverlayModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier
     */
    TextOverlayModifier textOverlayModifier;
    std::vector<RectF> rectList;
    rectList.push_back(RectF(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    rectList.push_back(RectF(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    textOverlayModifier.SetSelectedRects(rectList);
    /**
     * @tc.steps: step2. test IsSelectedRectsChanged
     */
    RectF secondRect(RECT_SECOND_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);
    textOverlayModifier.selectedRects_[0] = secondRect;
    bool rectsChanged = textOverlayModifier.IsSelectedRectsChanged(rectList);
    EXPECT_EQ(rectsChanged, true);
}

/**
 * @tc.name: TextOverlayModifierTest003
 * @tc.desc: test TextOverlayModifier function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextOverlayModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier
     */
    TextOverlayModifier textOverlayModifier;
    OffsetF paintOffset;
    textOverlayModifier.SetPrintOffset(paintOffset);
    textOverlayModifier.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step2. change version and save initial version
     */
    int32_t settingHighApiVersion = 12;
    int32_t settingLowApiVersion = 10;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingHighApiVersion);

    /**
     * @tc.steps: step3. test TextOverlayModifier
     */
    TextOverlayModifier();
    EXPECT_EQ(textOverlayModifier.isClip_->Get(), true);

    /**
     * @tc.steps: step4. test TextOverlayModifier again and reuse initial ApiTargetVersion
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(settingLowApiVersion);
    TextOverlayModifier();
    EXPECT_EQ(textOverlayModifier.isClip_->Get(), true);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: TextOverlayModifierTest004
 * @tc.desc: test onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextOverlayModifierTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier
     */
    TextOverlayModifier textOverlayModifier;
    OffsetF paintOffset;
    textOverlayModifier.SetPrintOffset(paintOffset);
    textOverlayModifier.SetSelectedColor(SELECTED_COLOR);

    /**
     * @tc.steps: step1. create selectedRects_
     */
    std::vector<RectF> rectList;
    rectList.push_back(RectF(RECT_SECOND_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    textOverlayModifier.SetSelectedRects(rectList);

    /**
     * @tc.steps: step3. create canvas
     */

    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());

    /**
     * @tc.steps: step4. change ApiVersion and set isClip_ is true
     */

    int32_t changeApiVersion = 12;
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(changeApiVersion);
    TextOverlayModifier();
    EXPECT_EQ(textOverlayModifier.isClip_->Get(), true);

    /**
     * @tc.steps: step5. create context and textContentRect
     */
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    RectF textContentRect = CONTENT_RECT;
    textOverlayModifier.SetContentRect(textContentRect);

    /**
     * @tc.steps: step6. test onDraw
     */
    textOverlayModifier.SetShowSelect(true);
    textOverlayModifier.onDraw(context);
    RectF finalSelectRect = textOverlayModifier.selectedRects_[0];
    EXPECT_EQ(textOverlayModifier.paintOffset_->Get(), paintOffset);
    EXPECT_EQ(finalSelectRect.Width(), 5);
    EXPECT_EQ(textOverlayModifier.contentRect_, textContentRect);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: TextPaintMethodTest004
 * @tc.desc: test text_paint_method.cpp UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextPaintMethodTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textLayoutProperty.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. create textPaintMethod and update textLayoutProperty.
     */
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(ADAPT_BASE_LINE_OFFSET_VALUE);

    /**
     * @tc.steps: step3. update ClipEdge and create textTheme.
     */
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    renderContext->UpdateClipEdge(true);
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));
    ASSERT_NE(textTheme, nullptr);

    /**
     * @tc.steps: step4. call UpdateContentModifier and GetOverlayModifier.
     */
    textPaintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    auto OverlayModifier = textPaintMethod.GetOverlayModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(OverlayModifier, nullptr);
    EXPECT_EQ(textOverlayModifier->isClip_->Get(), true);
}

/**
 * @tc.name: TextContentModifierB001
 * @tc.desc: test text_content_modifier.cpp ChangeDragStatus
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call ChangeDragStatus and expect no error.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    textContentModifier->dragStatus_ = AceType::MakeRefPtr<PropertyBool>(false);
    textContentModifier->ChangeDragStatus();
    EXPECT_EQ(textContentModifier->dragStatus_, true);
}

/**
 * @tc.name: TextContentModifierB002
 * @tc.desc: test text_content_modifier.cpp ModifyLineHeightInTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call ModifyLineHeightInTextStyle and expect no error.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    float lineHeight = 2.0f;
    textContentModifier->lineHeightFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(lineHeight);
    textContentModifier->lineHeight_ = Dimension(1.0f);
    TextStyle textStyle;
    textContentModifier->ModifyLineHeightInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetLineHeight(), Dimension(2.0f, DimensionUnit::PX));
}

/**
 * @tc.name: TextContentModifierB003
 * @tc.desc: test text_content_modifier.cpp TextColorModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call TextColorModifier and expect no error.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    Color color = Color::BLACK;
    textContentModifier->TextColorModifier(color);
    EXPECT_EQ(textContentModifier->onlyTextColorAnimation_, true);
}

/**
 * @tc.name: TextContentModifierB004
 * @tc.desc: test text_content_modifier.cpp ResumeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call ResumeAnimation and expect no error.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    AnimationOption option = AnimationOption();
    textContentModifier->raceAnimation_ = AnimationUtils::StartAnimation(option, [&]() {}, []() {});
    textContentModifier->ResumeAnimation();
    EXPECT_EQ(textContentModifier->marqueeState_, MarqueeState::IDLE);
    textContentModifier->PauseAnimation();
    EXPECT_EQ(textContentModifier->marqueeState_, MarqueeState::IDLE);
}


/**
 * @tc.name: TextContentModifierB005
 * @tc.desc: test text_content_modifier.cpp GetTextRaceDirectionByContent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call GetTextRaceDirectionByContent and expect no error.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    auto direction = textContentModifier->GetTextRaceDirectionByContent();
    EXPECT_EQ(direction, TextDirection::LTR);
}


/**
 * @tc.name: TextContentModifierB006
 * @tc.desc: test text_content_modifier.cpp ResettextRacePercent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call ResettextRacePercent and expect no error.
     */
    auto layoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    textContentModifier->ResetTextRacePercent();
    EXPECT_NE(textContentModifier->racePercentFloat_, nullptr);
}

/**
 * @tc.name: TextContentModifierB007
 * @tc.desc: test text_content_modifier.cpp SetIsFocused
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call SetIsFocused and expect no error.
     */
    textContentModifier->SetIsFocused(false);
    EXPECT_EQ(textContentModifier->marqueeFocused_, false);
}
 
/**
 * @tc.name: TextContentModifierB008
 * @tc.desc: test text_content_modifier.cpp AllowTextRace
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPaintMethod and textContentModifier
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. call AllowTextRace and expect no error.
     */
    textContentModifier->marqueeOption_.start = false;
    textContentModifier->ResumeTextRace(false);
    auto isAllowTextRace = textContentModifier->AllowTextRace();
    EXPECT_EQ(isAllowTextRace, false);
    textContentModifier->marqueeSet_ = true;
    textContentModifier->marqueeOption_.start = true;
    textContentModifier->marqueeOption_.loop = 1;
    textContentModifier->marqueeCount_ = 2;
    isAllowTextRace = textContentModifier->AllowTextRace();
    EXPECT_EQ(isAllowTextRace, false);
    textContentModifier->marqueeCount_ = 0;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::ON_FOCUS;
    textContentModifier->marqueeFocused_ = false;
    textContentModifier->marqueeHovered_ = false;
    EXPECT_EQ(isAllowTextRace, false);
}

/**
 * @tc.name: TextContentModifierB009
 * @tc.desc: test text_content_modifier.cpp DetermineTextRace
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgFour, TextContentModifierB009, TestSize.Level1)
{
    /**
        * @tc.steps: step1. create textPaintMethod and textContentModifier
        */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
        * @tc.steps: step2. call DetermineTextRace and expect no error.
        */
    textContentModifier->marqueeSet_ = false;
    textContentModifier->DetermineTextRace();
    textContentModifier->marqueeOption_.start = true;
    textContentModifier->marqueeOption_.startPolicy = MarqueeStartPolicy::ON_FOCUS;
    textContentModifier->marqueeState_ = MarqueeState::RUNNING;
    textContentModifier->marqueeFocused_ = false;
    textContentModifier->marqueeHovered_ = false;
    textContentModifier->DetermineTextRace();
    textContentModifier->marqueeHovered_ = true;
    textContentModifier->marqueeState_ = MarqueeState::IDLE;
    textContentModifier->DetermineTextRace();
    EXPECT_EQ(textContentModifier->marqueeFocused_, false);
}

} // namespace OHOS::Ace::NG