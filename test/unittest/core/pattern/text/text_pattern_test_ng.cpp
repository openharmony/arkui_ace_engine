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
} // namespace OHOS::Ace::NG