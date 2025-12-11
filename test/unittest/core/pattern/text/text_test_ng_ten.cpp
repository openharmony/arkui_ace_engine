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

class TextTestNgTen : public TextBases {};

/**
 * @tc.name: InitKeyEvent_HandleKey
 * @tc.desc: Test TextPattern InitKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTen, InitKeyEvent_HandleKey, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, InitUrlTouchEvent_TouchTask, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, InitTouchEvent_TouchTask, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, HandleKeyEvent_Marquee, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, HandleKeyEvent_False, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, OnDragStartNoChild_GetIsTextDraggable_False, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, GetTextBoxes_IsAiSelected, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, BetweenSelectedPosition_HasRenderTransform, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, BeforeCreateLayoutWrapper_HasSpanOnHoverEvent, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, ResetTextEffectBeforeLayout_001, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, ResetTextEffectBeforeLayout_002, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, ResetTextEffectBeforeLayout_003, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, ResetTextEffectBeforeLayout_004, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, ResetTextEffectBeforeLayout_005, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, ResetTextEffectBeforeLayout_006, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, GetOrCreateTextEffect_001, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, GetOrCreateTextEffect_002, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, GetOrCreateTextEffect_003, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, RegularMatchNumbers_for, TestSize.Level1)
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
HWTEST_F(TextTestNgTen, SetSpanEventFlagValue_OnClickAndPressCallback, TestSize.Level1)
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


/**
 * @tc.name: UpdateMarqueeOptions001
 * @tc.desc: test MarqueeOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgTen, UpdateMarqueeOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
 
    /**
     * @tc.steps: step2. test property.
     * @tc.expect：expect property as expect.
     */
    TextMarqueeOptions options;
    options.UpdateTextMarqueeStart(true);
    options.UpdateTextMarqueeStep(3);
    options.UpdateTextMarqueeLoop(3);
    options.UpdateTextMarqueeDirection(MarqueeDirection::RIGHT);
    options.UpdateTextMarqueeDelay(3);
    options.UpdateTextMarqueeFadeout(false);
    options.UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::ON_FOCUS);
    options.UpdateTextMarqueeUpdatePolicy(MarqueeUpdatePolicy::PRESERVE_POSITION);
    options.UpdateTextMarqueeSpacing(CalcDimension(4.0f, DimensionUnit::VP));
    textModelNG.SetMarqueeOptions(options);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStart().value(), true);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStep().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeLoop().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDirection().value(), MarqueeDirection::RIGHT);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDelay().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeFadeout().value(), false);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStartPolicy().value(), MarqueeStartPolicy::ON_FOCUS);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeUpdatePolicy().value(), MarqueeUpdatePolicy::PRESERVE_POSITION);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeSpacing().value(), CalcDimension(4.0f, DimensionUnit::VP));
}
}