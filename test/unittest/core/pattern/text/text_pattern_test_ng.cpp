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
#include "text_base.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {

void TextPatternTestNg::SetUp() {}

void TextPatternTestNg::TearDown() {}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 10;
    textPattern->OnAttachToFrameNode();
    EXPECT_EQ(frameNode->GetRenderContext(), 1);
}

/**
 * @tc.name: OnAttachToFrameNode002
 * @tc.desc: Test OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnAttachToFrameNode002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIX);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 10;
    textPattern->OnAttachToFrameNode();
    EXPECT_EQ(frameNode->GetRenderContext(), 1);
}

/**
 * @tc.name: OnAttachToFrameNode003
 * @tc.desc: Test OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnAttachToFrameNode003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 6;
    textPattern->OnAttachToFrameNode();
    EXPECT_EQ(frameNode->GetRenderContext(), 1);
}

/**
 * @tc.name: OnAttachToFrameNode004
 * @tc.desc: Test OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnAttachToFrameNode004, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIX);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->minPlatformVersion_ = 6;
    textPattern->OnAttachToFrameNode();
    EXPECT_EQ(frameNode->GetRenderContext(), 1);
}

/**
 * @tc.name: GetSpansInfo001
 * @tc.desc: Test GetSpansInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetSpansInfo001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t start = -1;
    int32_t end = 0;
    std::int32_t realStart = 0;
    GetSpansMethod method = GetSpansMethod::GETSPANS;
    textPattern->GetSpansInfo(start, end, method);
    EXPECT_EQ(realStart, 0);
}

/**
 * @tc.name: GetSpansInfo002
 * @tc.desc: Test GetSpansInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetSpansInfo002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t start = -1;
    int32_t end = 0;
    std::int32_t realStart = 0;
    GetSpansMethod method = GetSpansMethod::ONSELECT;
    textPattern->GetSpansInfo(start, end, method);
    EXPECT_EQ(realStart, 0);
}

/**
 * @tc.name: GetSpansInfo003
 * @tc.desc: Test GetSpansInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetSpansInfo003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t start = 5;
    int32_t end = 1;
    std::int32_t realEnd = 0;
    GetSpansMethod method = GetSpansMethod::GETSPANS;
    textPattern->GetSpansInfo(start, end, method);
    EXPECT_EQ(realEnd, 0);
}

/**
 * @tc.name: GetTextContentLength001
 * @tc.desc: Test GetTextContentLength
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextContentLength001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto result = textPattern->GetTextContentLength();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: GetTextContentLength002
 * @tc.desc: Test GetTextContentLength
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetTextContentLength002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    textPattern->spans_.emplace_back(spanItem);
    textPattern->placeholderCount_ = 10;
    auto result = textPattern->GetTextContentLength();
    EXPECT_EQ(result, 10);
}

/**
 * @tc.name: GetSelectedText001
 * @tc.desc: Test GetSelectedText
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetSelectedText001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t start = 10;
    int32_t end = 8;
    bool includeStartHalf = true;
    bool includeEndHalf = true;
    bool getSubstrDirectly = true;
    textPattern->textForDisplay_ = { 'l' };
    auto expected = textPattern->textForDisplay_;
    textPattern->textForDisplay_ = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
    auto result = textPattern->GetSelectedText(start, end, includeStartHalf, includeEndHalf, getSubstrDirectly);
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: GetSelectedText002
 * @tc.desc: Test GetSelectedText
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetSelectedText002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t start = 10;
    int32_t end = 10;
    bool includeStartHalf = true;
    bool includeEndHalf = true;
    bool getSubstrDirectly = true;
    textPattern->textForDisplay_ = { 'l' };
    auto expected = textPattern->textForDisplay_;
    textPattern->textForDisplay_ = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
    auto result = textPattern->GetSelectedText(start, end, includeStartHalf, includeEndHalf, getSubstrDirectly);
    EXPECT_NE(result, expected);
}

/**
 * @tc.name: IsShowSearch001
 * @tc.desc: Test IsShowSearch
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsShowSearch001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto result = textPattern->IsShowSearch();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: Test HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleClickEvent001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    GestureEvent info;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->HandleClickEvent(info);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleClickEvent002
 * @tc.desc: Test HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleClickEvent002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    GestureEvent info;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->HandleClickEvent(info);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleClickEvent003
 * @tc.desc: Test HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleClickEvent003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->multipleClickRecognizer_ = AceType::MakeRefPtr<MultipleClickRecognizer>();
    ASSERT_NE(textPattern->multipleClickRecognizer_, nullptr);
    GestureEvent info;
    textPattern->multipleClickRecognizer_->clickTimes_ = 3;
    textPattern->HandleClickEvent(info);
    EXPECT_NE(textPattern->isDoubleClick_, true);
}

/**
 * @tc.name: HandleUrlClick001
 * @tc.desc: Test HandleUrlClick
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleUrlClick001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->clickedSpanPosition_ = -1;
    auto result = textPattern->HandleUrlClick();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleUrlClick002
 * @tc.desc: Test HandleUrlClick
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleUrlClick002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->clickedSpanPosition_ = 1;
    auto result = textPattern->HandleUrlClick();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleSingleClickEvent001
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    GestureEvent info;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->selectOverlay_->originalMenuIsShow_, true);
}

/**
 * @tc.name: HandleSingleClickEvent002
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    GestureEvent info;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->selectOverlay_->originalMenuIsShow_, true);
}

/**
 * @tc.name: CheckClickedOnSpanOrText001
 * @tc.desc: Test CheckClickedOnSpanOrText
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CheckClickedOnSpanOrText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(frameNode->renderContext_, nullptr);
    frameNode->renderContext_ = RenderContext::Create();
    ASSERT_NE(frameNode->renderContext_, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    RectF textContentRect;
    int buff = 0;
    Offset localLocation;
    std::function<void(GestureEvent&)> func = [buff](GestureEvent& info) mutable { buff++; };
    textPattern->onClick_ = func;
    auto result = textPattern->CheckClickedOnSpanOrText(textContentRect, localLocation);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CheckClickedOnSpanOrText002
 * @tc.desc: Test CheckClickedOnSpanOrText
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CheckClickedOnSpanOrText002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(frameNode->renderContext_, nullptr);
    frameNode->renderContext_ = RenderContext::Create();
    ASSERT_NE(frameNode->renderContext_, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    RectF textContentRect;
    Offset localLocation;
    textPattern->onClick_ = nullptr;
    auto result = textPattern->CheckClickedOnSpanOrText(textContentRect, localLocation);
    EXPECT_NE(result, true);
}

/**
 * @tc.name: CheckAndClick001
 * @tc.desc: Test CheckAndClick
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CCheckAndClick001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    int buff = 0;
    std::function<void(GestureEvent&)> func = [buff](GestureEvent& info) mutable { buff++; };
    spanItem->onClick = func;
    int refCount = 0;
    std::function<void()> urlOnRelease_ = [&refCount]() { refCount++; };
    spanItem->urlOnRelease = urlOnRelease_;
    auto result = textPattern->CheckAndClick(spanItem);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CheckAndClick002
 * @tc.desc: Test CheckAndClick
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CCheckAndClick002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->onClick = nullptr;
    spanItem->urlOnRelease = nullptr;
    auto result = textPattern->CheckAndClick(spanItem);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: CheckAndClick003
 * @tc.desc: Test CheckAndClick
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CCheckAndClick003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    int buff = 0;
    std::function<void(GestureEvent&)> func = [buff](GestureEvent& info) mutable { buff++; };
    spanItem->onClick = func;
    spanItem->urlOnRelease = nullptr;
    auto result = textPattern->CheckAndClick(spanItem);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CheckAndClick004
 * @tc.desc: Test CheckAndClick
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, CCheckAndClick004, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->onClick = nullptr;
    int refCount = 0;
    std::function<void()> urlOnRelease_ = [&refCount]() { refCount++; };
    spanItem->urlOnRelease = urlOnRelease_;
    auto result = textPattern->CheckAndClick(spanItem);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: OnHover001
 * @tc.desc: Test OnHover
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnHover001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    bool isHover = true;
    textPattern->OnHover(isHover);
    EXPECT_EQ(textPattern->currentMouseStyle_, MouseFormat::DEFAULT);
}

/**
 * @tc.name: OnHover002
 * @tc.desc: Test OnHover
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnHover002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    bool isHover = false;
    textPattern->OnHover(isHover);
    EXPECT_EQ(textPattern->currentMouseStyle_, MouseFormat::DEFAULT);
}

/**
 * @tc.name: RecoverCopyOption001
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = true;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = true;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: RecoverCopyOption002
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = false;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = true;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: RecoverCopyOption003
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = true;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = false;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: RecoverCopyOption004
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = true;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = true;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: RecoverCopyOption005
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = false;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = false;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: RecoverCopyOption006
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption006, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = true;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = false;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: RecoverCopyOption007
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption007, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = false;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = true;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: RecoverCopyOption008
 * @tc.desc: Test RecoverCopyOption
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RecoverCopyOption008, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = false;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = false;
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    textPattern->RecoverCopyOption();
    EXPECT_EQ(textPattern->dataDetectorAdapter_->textForAI_, textPattern->textForDisplay_);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: Test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseEvent001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    textPattern->HandleMouseEvent(info);
    EXPECT_EQ(textPattern->lastLeftMouseMoveLocation_, info.GetGlobalLocation());
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: Test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseEvent002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    info.button_ = MouseButton::RIGHT_BUTTON;
    textPattern->HandleMouseEvent(info);
    EXPECT_EQ(textPattern->sourceType_, info.GetSourceDevice());
}

/**
 * @tc.name: HandleMouseEvent003
 * @tc.desc: Test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseEvent003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    info.button_ = MouseButton::NONE_BUTTON;
    textPattern->HandleMouseEvent(info);
    EXPECT_EQ(textPattern->sourceType_, info.GetSourceDevice());
}

/**
 * @tc.name: HandleMouseLeftButton001
 * @tc.desc: Test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftButton001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    info.action_ = MouseAction::PRESS;
    textPattern->HandleMouseLeftButton(info, textOffset);
    EXPECT_EQ(textPattern->isMousePressed_, true);
}

/**
 * @tc.name: HandleMouseLeftButton002
 * @tc.desc: Test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftButton002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    info.action_ = MouseAction::MOVE;
    textPattern->isMousePressed_ = true;
    textPattern->HandleMouseLeftButton(info, textOffset);
    EXPECT_EQ(textPattern->leftMousePressed_, false);
}

/**
 * @tc.name: HandleMouseLeftButton003
 * @tc.desc: Test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftButton003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    info.action_ = MouseAction::RELEASE;
    textPattern->HandleMouseLeftButton(info, textOffset);
    EXPECT_EQ(textPattern->mouseStatus_, MouseStatus::RELEASED);
}

/**
 * @tc.name: HandleMouseLeftButton004
 * @tc.desc: Test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftButton004, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    info.action_ = MouseAction::WINDOW_ENTER;
    textPattern->HandleMouseLeftButton(info, textOffset);
    EXPECT_EQ(textPattern->isMousePressed_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction001
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->blockPress_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->blockPress_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction002
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->blockPress_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->blockPress_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction003
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->isDoubleClick_ = true;
    textPattern->isMousePressed_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->isMousePressed_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction004
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction004, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->isDoubleClick_ = false;
    textPattern->isMousePressed_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->isMousePressed_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction005
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction005, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->mouseStatus_ = MouseStatus::PRESSED;
    textPattern->status_ = Status::FLOATING;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->isDoubleClick_ = false;
    textPattern->isTryEntityDragging_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction006
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction006, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->mouseStatus_ = MouseStatus::MOVE;
    textPattern->status_ = Status::FLOATING;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->isDoubleClick_ = false;
    textPattern->isTryEntityDragging_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_NE(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction007
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction007, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->mouseStatus_ = MouseStatus::NONE;
    textPattern->status_ = Status::FLOATING;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->isDoubleClick_ = false;
    textPattern->isTryEntityDragging_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_NE(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction008
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction008, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->mouseStatus_ = MouseStatus::PRESSED;
    textPattern->status_ = Status::DRAGGING;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->isDoubleClick_ = false;
    textPattern->isTryEntityDragging_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_NE(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction009
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction009, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->mouseStatus_ = MouseStatus::MOVE;
    textPattern->status_ = Status::DRAGGING;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->isDoubleClick_ = false;
    textPattern->isTryEntityDragging_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_NE(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction010
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction010, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->mouseStatus_ = MouseStatus::NONE;
    textPattern->status_ = Status::DRAGGING;
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->isDoubleClick_ = false;
    textPattern->isTryEntityDragging_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_NE(textPattern->dataDetectorAdapter_->hasClickedAISpan_, false);
}

/**
 * @tc.name: HandleMouseLeftMoveAction001
 * @tc.desc: Test HandleMouseLeftMoveAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftMoveAction001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->isMousePressed_ = false;
    textPattern->mouseStatus_ = MouseStatus::PRESSED;
    textPattern->HandleMouseLeftMoveAction(info, textOffset);
    EXPECT_NE(textPattern->mouseStatus_, MouseStatus::MOVE);
}

/**
 * @tc.name: HandleKeyEvent001
 * @tc.desc: Test HandleKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleKeyEvent001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    auto result = textPattern->HandleKeyEvent(keyEvent);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction011
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction011, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = true;
    textPattern->mouseStatus_ = MouseStatus::MOVE;
    textPattern->shiftFlag_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction012
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction012, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = true;
    textPattern->mouseStatus_ = MouseStatus::MOVE;
    textPattern->shiftFlag_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction013
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction013, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = false;
    textPattern->mouseStatus_ = MouseStatus::PRESSED;
    textPattern->shiftFlag_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction014
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction014, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = false;
    textPattern->mouseStatus_ = MouseStatus::MOVE;
    textPattern->shiftFlag_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction015
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction015, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = false;
    textPattern->mouseStatus_ = MouseStatus::PRESSED;
    textPattern->shiftFlag_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction016
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction016, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = true;
    textPattern->mouseStatus_ = MouseStatus::MOVE;
    textPattern->shiftFlag_ = false;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction017
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction017, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = false;
    textPattern->mouseStatus_ = MouseStatus::MOVE;
    textPattern->shiftFlag_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction018
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction018, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 2;
    textPattern->isMousePressed_ = true;
    textPattern->mouseStatus_ = MouseStatus::PRESSED;
    textPattern->shiftFlag_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction019
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction019, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    Offset textOffset;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 1;
    EXPECT_EQ(textPattern->textSelector_.GetStart(), 1);
}

/**
 * @tc.name: SetTextSelectableMode001
 * @tc.desc: Test SetTextSelectableMode
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, SetTextSelectableMode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    TextSelectableMode value = TextSelectableMode::SELECTABLE_FOCUSABLE;
    textPattern->SetTextSelectableMode(value);
    EXPECT_EQ(focusHub->focusCallbackEvents_->isFocusOnTouch_, true);
}

/**
 * @tc.name: SetTextSelectableMode002
 * @tc.desc: Test SetTextSelectableMode
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, SetTextSelectableMode002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    TextSelectableMode value = TextSelectableMode::UNSELECTABLE;
    textPattern->SetTextSelectableMode(value);
    EXPECT_EQ(focusHub->focusCallbackEvents_->isFocusOnTouch_, false);
}

/**
 * @tc.name: OnDragEnde001
 * @tc.desc: Test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDragEnde001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(frameNode->renderContext_, nullptr);
    RefPtr<Ace::DragEvent> event = AceType::MakeRefPtr<Ace::DragEvent>();
    textPattern->status_ = Status::DRAGGING;
    textPattern->OnDragEnd(event);
    EXPECT_EQ(textPattern->status_, Status::NONE);
}

/**
 * @tc.name: OnDragEnde002
 * @tc.desc: Test OnDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDragEnde002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(frameNode->renderContext_, nullptr);
    RefPtr<Ace::DragEvent> event = AceType::MakeRefPtr<Ace::DragEvent>();
    textPattern->status_ = Status::FLOATING;
    textPattern->OnDragEnd(event);
    EXPECT_NE(textPattern->status_, Status::NONE);
}

/**
 * @tc.name: OnDragStart001
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDragStart001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<Ace::DragEvent> event = AceType::MakeRefPtr<Ace::DragEvent>();
    std::string extraParams;
    textPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    RectF boundsRect = { 1.0f, 1.0f, 1.0f, 1.0f };
    textPattern->overlayMod_->SetBoundsRect(boundsRect);
    textPattern->OnDragStart(event, extraParams);
    EXPECT_EQ(textPattern->overlayMod_->selectedUrlRects_.empty(), true);
}

/**
 * @tc.name: OnDragEndNoChild001
 * @tc.desc: Test OnDragEndNoChild
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDragEndNoChild001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<Ace::DragEvent> event = AceType::MakeRefPtr<Ace::DragEvent>();
    textPattern->status_ = Status::DRAGGING;
    TextStyle textStyle;
    textPattern->contentMod_ =
        AceType::MakeRefPtr<TextContentModifier>(textStyle, AceType::WeakClaim(AceType::RawPtr(textPattern)));
    textPattern->OnDragEndNoChild(event);
    EXPECT_EQ(textPattern->status_, Status::NONE);
}

/**
 * @tc.name: OnDragEndNoChild002
 * @tc.desc: Test OnDragEndNoChild
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDragEndNoChild002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<Ace::DragEvent> event = AceType::MakeRefPtr<Ace::DragEvent>();
    textPattern->status_ = Status::FLOATING;
    TextStyle textStyle;
    textPattern->contentMod_ =
        AceType::MakeRefPtr<TextContentModifier>(textStyle, AceType::WeakClaim(AceType::RawPtr(textPattern)));
    textPattern->OnDragEndNoChild(event);
    EXPECT_NE(textPattern->status_, Status::NONE);
}


/**
 * @tc.name: HandleSingleClickEvent003
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent003, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent004
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent004, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent005
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent005, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent006
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent006, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent007
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent007, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}

/**
 * @tc.name: HandleSingleClickEvent008
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent008, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent009
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent009, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent010
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent010, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}


/**
 * @tc.name: HandleSingleClickEvent011
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent011, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent012
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent012, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}

/**
 * @tc.name: HandleSingleClickEvent013
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent013, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}

/**
 * @tc.name: HandleSingleClickEvent014
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent014, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}

/**
 * @tc.name: HandleSingleClickEvent015
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent015, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = true;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}

/**
 * @tc.name: HandleSingleClickEvent016
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent016, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = true;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}

/**
 * @tc.name: HandleSingleClickEvent017
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent017, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = true;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(textPattern->moveOverClickThreshold_);
}

/**
 * @tc.name: HandleSingleClickEvent018
 * @tc.desc: Test HandleSingleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSingleClickEvent018, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    GestureEvent info;
    textPattern->sourceType_ = SourceType::NONE;
    textPattern->isMousePressed_ = false;
    textPattern->leftMousePressed_ = false;
    textPattern->moveOverClickThreshold_ = false;
    textPattern->HandleSingleClickEvent(info);
    EXPECT_EQ(textPattern->moveOverClickThreshold_, false);
}
} // namespace OHOS::Ace::NG