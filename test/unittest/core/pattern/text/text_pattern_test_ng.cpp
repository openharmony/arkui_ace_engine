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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"

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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    textPattern->dataDetectorAdapter_->aiDetectInitialized_ = true;
    textPattern->RecoverCopyOption();
    GestureEvent info;
    textPattern->HandleSingleClickEvent(info);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    TextModelNG textModelNG;
    textModelNG.Create(u"Hello World");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(host, nullptr);
    auto textPattern = host->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate).WillOnce(Return(1));
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    MouseInfo info;
    Offset textOffset;
    info.action_ = MouseAction::RELEASE;
    textPattern->HandleMouseLeftButton(info, textOffset);
    EXPECT_EQ(textPattern->mouseStatus_, MouseStatus::RELEASED);
    textPattern->pManager_.Reset();
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
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

/**
 * @tc.name: RegisterVisibleAreaChangeCallback019
 * @tc.desc: Test RegisterVisibleAreaChangeCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, RegisterVisibleAreaChangeCallback019, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    textPattern->frameNode_.Upgrade() = frameNode;
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    textPattern->RegisterVisibleAreaChangeCallback();
}

/**
 * @tc.name: ExecSubComponent001
 * @tc.desc: Test ExecSubComponent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ExecSubComponent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t spanId = -1;
    std::vector<SubComponentInfo> subComponentInfos;
    SubComponentInfo subComponentInfo;
    subComponentInfos.emplace_back(subComponentInfo);
    auto result = textPattern->ExecSubComponent(spanId);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ExecSubComponent002
 * @tc.desc: Test ExecSubComponent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ExecSubComponent002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t spanId = 1;
    std::vector<SubComponentInfo> subComponentInfos;
    SubComponentInfo subComponentInfo;
    subComponentInfos.emplace_back(subComponentInfo);
    auto result = textPattern->ExecSubComponent(spanId);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ActSetSelection001
 * @tc.desc: Test ActSetSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ActSetSelection001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    textPattern->textForDisplay_ = u"asdfghjkl";
    OffsetF offset = {0, 0};
    textPattern->ActSetSelection(start, end);
    EXPECT_EQ(textPattern->parentGlobalOffset_, offset);
}

/**
 * @tc.name: ActSetSelection002
 * @tc.desc: Test ActSetSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ActSetSelection002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    int32_t start = 1;
    int32_t end = 10;
    textPattern->textForDisplay_ = u"asdfghjkl";
    OffsetF offset = {0, 0};
    textPattern->ActSetSelection(start, end);
    EXPECT_EQ(textPattern->parentGlobalOffset_, offset);
}

/**
 * @tc.name: ActSetSelection003
 * @tc.desc: Test ActSetSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ActSetSelection003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(textPattern->pManager_, nullptr);
    int32_t start = 1;
    int32_t end = 10;
    textPattern->textForDisplay_ = u"asdfghjkl";
    textPattern->textSelector_.firstHandle = { 1, 2, 1, 2 };
    textPattern->textSelector_.secondHandle = { 1, 2, 1, 2 };
    textPattern->ActSetSelection(start, end);
    EXPECT_EQ(textPattern->selectOverlay_, 1);
}

/**
 * @tc.name: ActSetSelection004
 * @tc.desc: Test ActSetSelection
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ActSetSelection004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(textPattern->pManager_, nullptr);
    int32_t start = 1;
    int32_t end = 10;
    textPattern->textForDisplay_ = u"asdfghjkl";
    textPattern->textSelector_.firstHandle = { 1, 2, 1, 2 };
    textPattern->textSelector_.secondHandle = {};
    textPattern->ActSetSelection(start, end);
    EXPECT_EQ(textPattern->selectOverlay_, 1);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<LayoutWrapperNode> dirty = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(dirty, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    dirty->skipMeasureContent_ = true;
    auto result = textPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<LayoutWrapperNode> dirty = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(dirty, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = false;
    dirty->skipMeasureContent_ = true;
    auto result = textPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<LayoutWrapperNode> dirty = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(dirty, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    dirty->skipMeasureContent_ = false;
    auto result = textPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap004
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnDirtyLayoutWrapperSwap004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<LayoutWrapperNode> dirty = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(dirty, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = false;
    dirty->skipMeasureContent_ = false;
    auto result = textPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PreCreateLayoutWrapper001
 * @tc.desc: Test PreCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, PreCreateLayoutWrapper001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->childNodes_.emplace_back(frameNode);
    textPattern->placeholderCount_ = 1;
    textPattern->PreCreateLayoutWrapper();
    EXPECT_EQ(textPattern->placeholderCount_, 0);
}

/**
 * @tc.name: PreCreateLayoutWrapper002
 * @tc.desc: Test PreCreateLayoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, PreCreateLayoutWrapper002, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->childNodes_.emplace_back();
    textPattern->childNodes_.clear();
    textPattern->placeholderCount_ = 1;
    textPattern->PreCreateLayoutWrapper();
    EXPECT_NE(textPattern->placeholderCount_, 0);
}

/**
 * @tc.name: InitSpanItem001
 * @tc.desc: Test InitSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, InitSpanItem001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->childNodes_.emplace_back(frameNode);
    auto host = textPattern->GetHost();
    ASSERT_NE(host, nullptr);
    textPattern->textForDisplay_ = u"asdfghjkl";
    const auto& children = host->GetChildren();
    std::stack<SpanNodeInfo> nodes;
    nodes.push({ .node = *children.rbegin() });
    textPattern->InitSpanItem(nodes);
    EXPECT_EQ(textPattern->textForDisplay_, u"");
}

/**
 * @tc.name: InitSpanItem002
 * @tc.desc: Test InitSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, InitSpanItem002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->childNodes_.emplace_back(frameNode);
    textPattern->textForDisplay_ = u"asdfghjkl";
    std::stack<SpanNodeInfo> nodes;
    textPattern->InitSpanItem(nodes);
    EXPECT_NE(textPattern->textForDisplay_, u"");
}

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: Test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnVisibleChange001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    bool isVisible = false;
    textPattern->textSelector_.baseOffset = 1;
    textPattern->textSelector_.destinationOffset = 1;
    textPattern->OnVisibleChange(isVisible);
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->aiDetectDelayTask_.Cancel(), true);
}

/**
 * @tc.name: OnVisibleChange002
 * @tc.desc: Test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnVisibleChange002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    bool isVisible = false;
    textPattern->textDetectEnable_ = true;
    textPattern->OnVisibleChange(isVisible);
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->aiDetectDelayTask_.Cancel(), true);
}

/**
 * @tc.name: OnVisibleChange003
 * @tc.desc: Test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnVisibleChange003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    bool isVisible = false;
    textPattern->textDetectEnable_ = false;
    textPattern->OnVisibleChange(isVisible);
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->aiDetectDelayTask_.Cancel(), true);
}

/**
 * @tc.name: OnVisibleChange004
 * @tc.desc: Test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnVisibleChange004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    bool isVisible = true;
    textPattern->textDetectEnable_ = false;
    textPattern->enabled_ = false;
    textPattern->OnVisibleChange(isVisible);
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->aiDetectDelayTask_.Cancel(), true);
}

/**
 * @tc.name: OnVisibleChange005
 * @tc.desc: Test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnVisibleChange005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    bool isVisible = true;
    textPattern->textDetectEnable_ = true;
    textPattern->enabled_ = true;
    textPattern->OnVisibleChange(isVisible);
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(textPattern->dataDetectorAdapter_->aiDetectDelayTask_.Cancel(), true);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: Test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSurfaceChanged001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    int32_t newWidth = 1;
    int32_t newHeight = 1;
    int32_t prevWidth = 1;
    int32_t prevHeight = 1;
    WindowSizeChangeReason type = WindowSizeChangeReason::HIDE;
    textPattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, type);
    EXPECT_NE(textLayoutProperty->propNeedReCreateParagraph_, true);
}

/**
 * @tc.name: HandleSurfaceChanged002
 * @tc.desc: Test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSurfaceChanged002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    int32_t newWidth = 1;
    int32_t newHeight = 2;
    int32_t prevWidth = 1;
    int32_t prevHeight = 1;
    WindowSizeChangeReason type = WindowSizeChangeReason::HIDE;
    textPattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, type);
    EXPECT_NE(textLayoutProperty->propNeedReCreateParagraph_, true);
}

/**
 * @tc.name: HandleSurfaceChanged003
 * @tc.desc: Test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSurfaceChanged003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    int32_t newWidth = 1;
    int32_t newHeight = 1;
    int32_t prevWidth = 1;
    int32_t prevHeight = 2;
    WindowSizeChangeReason type = WindowSizeChangeReason::HIDE;
    textPattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, type);
    EXPECT_NE(textLayoutProperty->propNeedReCreateParagraph_, true);
}

/**
 * @tc.name: HandleSurfaceChanged004
 * @tc.desc: Test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSurfaceChanged004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    int32_t newWidth = 1;
    int32_t newHeight = 2;
    int32_t prevWidth = 1;
    int32_t prevHeight = 2;
    WindowSizeChangeReason type = WindowSizeChangeReason::HIDE;
    textPattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, type);
    EXPECT_NE(textLayoutProperty->propNeedReCreateParagraph_, true);
}

/**
 * @tc.name: HandleSurfaceChanged005
 * @tc.desc: Test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSurfaceChanged005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    int32_t newWidth = 1;
    int32_t newHeight = 2;
    int32_t prevWidth = 1;
    int32_t prevHeight = 2;
    WindowSizeChangeReason type = WindowSizeChangeReason::DRAG;
    textPattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, type);
    EXPECT_NE(textLayoutProperty->propNeedReCreateParagraph_, true);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->magnifierController_ =
        AceType::MakeRefPtr<MagnifierController>(AccessibilityManagerNG::WeakClaim(AceType::RawPtr(textPattern)));
    textPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(textPattern->magnifierController_->colorModeChange_, true);
}

/**
 * @tc.name: OnColorConfigurationUpdate002
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, OnColorConfigurationUpdate002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->magnifierController_ = nullptr;
    textPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(textPattern->magnifierController_->colorModeChange_, true);
}

/**
 * @tc.name: GetOriginCaretPosition001
 * @tc.desc: Test GetOriginCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOriginCaretPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    OffsetF offset = { 1.0f, 1.0f };
    textPattern->originCaretPosition_ = offset;
    auto result = textPattern->GetOriginCaretPosition(offset);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: GetOriginCaretPosition002
 * @tc.desc: Test GetOriginCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOriginCaretPosition002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    OffsetF offset = { -1.0f, -1.0f };
    textPattern->originCaretPosition_ = offset;
    auto result = textPattern->GetOriginCaretPosition(offset);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ParseOriText001
 * @tc.desc: Test ParseOriText
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, ParseOriText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    std::u16string currentText = u"bundleName";
    textPattern->textForDisplay_ = u"asdfghjkl";
    textPattern->childNodes_.emplace_back(frameNode);
    textPattern->ParseOriText(currentText);
    EXPECT_NE(textPattern->textForDisplay_, u"");
}

/**
 * @tc.name: UpdateSpanItemDragStatus001
 * @tc.desc: Test UpdateSpanItemDragStatus
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, UpdateSpanItemDragStatus001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->isSpanStringMode_ = true;
    std::list<ResultObject> resultObjects;
    bool isDragging = true;
    textPattern->UpdateSpanItemDragStatus(resultObjects, isDragging);
    EXPECT_EQ(textPattern->dragSpanItems_.empty(), true);
}


/**
 * @tc.name: GetOrCreatePreviewMenuController001
 * @tc.desc: Test GetOrCreatePreviewMenuController
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOrCreatePreviewMenuController001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    TextStyle textStyle;
    WeakPtr<TextPattern> weakPattern = textPattern;
    RefPtr<PreviewMenuController> controller = AceType::MakeRefPtr<PreviewMenuController>(weakPattern);
    textPattern->previewController_ = controller;
    textPattern->GetOrCreatePreviewMenuController();
    EXPECT_NE(textPattern->blockPress_, true);
}

/**
 * @tc.name: GetOrCreatePreviewMenuController002
 * @tc.desc: Test GetOrCreatePreviewMenuController
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, GetOrCreatePreviewMenuController002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    TextStyle textStyle;
    textPattern->previewController_ = nullptr;
    textPattern->GetOrCreatePreviewMenuController();
    EXPECT_NE(textPattern->blockPress_, true);
}

/**
 * @tc.name: IsPreviewMenuShow001
 * @tc.desc: Test TextPattern IsPreviewMenuShow function
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, IsPreviewMenuShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create the TextPattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test when previewController_ is null
     * @tc.expected: Returns false
     */
    pattern->previewController_ = nullptr;
    EXPECT_FALSE(pattern->IsPreviewMenuShow());

    /**
     * @tc.steps: step3. Create PreviewMenuController and test when menu is not showing
     * @tc.expected: Returns false
     */
    RefPtr<TextPattern> textPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<PreviewMenuController> controller = AceType::MakeRefPtr<PreviewMenuController>(textPattern);
    pattern->previewController_ = controller;
    EXPECT_FALSE(pattern->IsPreviewMenuShow());

    pattern->previewController_->isShow_ = true;

    /**
     * @tc.steps: step4. Test when menu is showing
     * @tc.expected: Returns true
     */
    // Note: This part would need implementation of ShowPreviewMenu in PreviewMenuController
    EXPECT_TRUE(pattern->IsPreviewMenuShow());
}

/**
 * @tc.name: AddPixelMapToUdmfData001
 * @tc.desc: Test AddPixelMapToUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, AddPixelMapToUdmfData001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    textPattern->AddPixelMapToUdmfData(pixelMap, unifiedData);
    EXPECT_NE(textPattern->pManager_, nullptr);
}

/**
 * @tc.name: AddPixelMapToUdmfData002
 * @tc.desc: Test AddPixelMapToUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, AddPixelMapToUdmfData002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<PixelMap> pixelMap = nullptr;
    auto unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    textPattern->AddPixelMapToUdmfData(pixelMap, unifiedData);
    EXPECT_NE(textPattern->pManager_, nullptr);
}

/**
 * @tc.name: AddPixelMapToUdmfData003
 * @tc.desc: Test AddPixelMapToUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, AddPixelMapToUdmfData003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    auto unifiedData = nullptr;
    textPattern->AddPixelMapToUdmfData(pixelMap, unifiedData);
    EXPECT_NE(textPattern->pManager_, nullptr);
}

/**
 * @tc.name: AddPixelMapToUdmfData004
 * @tc.desc: Test AddPixelMapToUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, AddPixelMapToUdmfData004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<PixelMap> pixelMap = nullptr;
    auto unifiedData = nullptr;
    textPattern->AddPixelMapToUdmfData(pixelMap, unifiedData);
    EXPECT_NE(textPattern->pManager_, nullptr);
}

/**
 * @tc.name: AddUdmfData001
 * @tc.desc: Test AddUdmfData
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, AddUdmfData001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    ASSERT_NE(textPattern->styledString_, nullptr);
    RefPtr<Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    textPattern->isSpanStringMode_ = true;
    textPattern->AddUdmfData(event);
    EXPECT_EQ(textPattern->dragResultObjects_.empty(), true);
}

/**
 * @tc.name: HandleSelectionUp001
 * @tc.desc: Test HandleSelectionUp
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSelectionUp001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->textSelector_.firstHandle = { 1, 2, 1, 2 };
    textPattern->textSelector_.secondHandle = { 1, 2, 1, 2 };
    textPattern->HandleSelectionUp();
    EXPECT_NE(textPattern->textSelector_.GetEnd(), 0);
}

/**
 * @tc.name: InitUrlTouchEvent001
 * @tc.desc: Test InitUrlTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, InitUrlTouchEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->urlTouchEventInitialized_ = false;
    textPattern->InitUrlTouchEvent();
    EXPECT_EQ(textPattern->urlTouchEventInitialized_, true);
}

/**
 * @tc.name: HandleMouseRightButton001
 * @tc.desc: Test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseRightButton001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::PRESS);
    Offset textOffset;
    textPattern->HandleMouseRightButton(info, textOffset);
    EXPECT_EQ(textPattern->selectOverlay_, 1);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction020
 * @tc.desc: Test HandleMouseLeftReleaseAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftReleaseAction020, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::NONE);
    Offset textOffset;
    textPattern->isDoubleClick_ = true;
    textPattern->mouseStatus_ = MouseStatus::PRESSED;
    textPattern->status_ = Status::DRAGGING;
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    textPattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    textPattern->HandleMouseLeftReleaseAction(info, textOffset);
    EXPECT_EQ(textPattern->isMousePressed_, false);
}

/**
 * @tc.name: HandleMouseLeftPressAction001
 * @tc.desc: Test HandleMouseLeftPressAction
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleMouseLeftPressAction001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    MouseInfo info;
    info.SetAction(MouseAction::MOVE);
    Offset textOffset;
    textPattern->HandleMouseLeftPressAction(info, textOffset);
    EXPECT_NE(textPattern->blockPress_, true);
}

/**
 * @tc.name: HandleSetStyledString01
 * @tc.desc: Test UpdateStyledStringByColorMode
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternTestNg, HandleSetStyledString01, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->UpdateStyledStringByColorMode();
    auto spanString = AceType::MakeRefPtr<SpanString>(u"1234455");
    textPattern->SetStyledString(spanString);
}
} // namespace OHOS::Ace::NG