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
#include "scroll_test_ng.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

void ScrollModelNGTestNg::SetUp() {}

void ScrollModelNGTestNg::TearDown() {}

/**
 * @tc.name: ScrollModelNGTestNg001
 * @tc.desc: Test SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg001, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG scrollModelNG;
    scrollModelNG.SetEnablePaging(false);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::INVALID);
}

/**
 * @tc.name: ScrollModelNGTestNg002
 * @tc.desc: Test SetEnablePaging When enablePaging is True
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg002, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG scrollModelNG;
    scrollModelNG.SetEnablePaging(true);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::VALID);
}

/**
 * @tc.name: ScrollModelNGTestNg003
 * @tc.desc: Test Static SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg003, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG::SetEnablePaging(frameNode, true);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::VALID);
}

/**
 * @tc.name: ScrollModelNGTestNg004
 * @tc.desc: Test Static SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg004, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG::SetEnablePaging(frameNode, false);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::INVALID);
}

/**
 * @tc.name: ScrollModelNGTestNg005
 * @tc.desc: Test SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg005, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG scrollModelNG;
    scrollModelNG.SetEnablePaging(false);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::INVALID);
}

/**
 * @tc.name: ScrollModelNGTestNg006
 * @tc.desc: Test SetEnablePaging When enablePaging is True
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg006, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG scrollModelNG;
    scrollModelNG.SetEnablePaging(true);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::VALID);
}

/**
 * @tc.name: ScrollModelNGTestNg007
 * @tc.desc: Test Static SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg007, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG::SetEnablePaging(frameNode, true);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::VALID);
}

/**
 * @tc.name: ScrollModelNGTestNg008
 * @tc.desc: Test Static SetEnablePaging When enablePaging is false
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg008, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    ScrollModelNG::SetEnablePaging(frameNode, false);
    EXPECT_EQ(pattern->GetEnablePaging(), ScrollPagingStatus::INVALID);
}
} // namespace OHOS::Ace::NG