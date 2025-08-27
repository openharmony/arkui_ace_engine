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

#include "gtest/gtest.h"
#include "list_test_ng.h"

#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ListItemGroupModelTestNg : public ListTestNg {};

/**
 * @tc.name: SetHeader_TwoParameters
 * @tc.desc: Test ListItemGroupModelNG SetHeader
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, SetHeader_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetHeaderComponentContentExist(false);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto headerNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(headerNode, nullptr);

    /**
     * @tc.steps: step2. Calling the SetHeader function
     * @tc.expected: The isHeaderComponentContentExist_ be true
     */
    model.SetHeader(listNode, AceType::RawPtr(headerNode));
    EXPECT_TRUE(pattern->isHeaderComponentContentExist_);
    CreateDone();
}

/**
 * @tc.name: SetFooter_TwoParameters
 * @tc.desc: Test ListItemGroupModelNG SetFooter
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, SetFooter_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetFooterComponentContentExist(false);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto footerNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(footerNode, nullptr);

    /**
     * @tc.steps: step2. Calling the SetFooter function
     * @tc.expected: The isFooterComponentContentExist_ be true
     */
    model.SetFooter(listNode, AceType::RawPtr(footerNode));
    EXPECT_TRUE(pattern->isFooterComponentContentExist_);
    CreateDone();
}

/**
 * @tc.name: SetListChildrenMainSize
 * @tc.desc: Test ListItemGroupModelNG SetListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, SetListChildrenMainSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetPixelRoundMode(PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE);
    listNode->context_ = AceType::RawPtr(context);
    pattern->frameNode_ = listNode;
    std::vector<float> mainSize = { 2.0f, 4.0f };
    pattern->childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);
    pattern->childrenSize_->isRoundingMode_ = false;

    /**
     * @tc.steps: step2. Calling the SetListChildrenMainSize function
     * @tc.expected: The isRoundingMode_ be true
     */
    model.SetListChildrenMainSize(listNode, 2.0f, mainSize);
    listNode->context_ = nullptr;
    EXPECT_TRUE(pattern->childrenSize_->isRoundingMode_);
    CreateDone();
}

/**
 * @tc.name: ResetListChildrenMainSize
 * @tc.desc: Test ListItemGroupModelNG ResetListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, ResetListChildrenMainSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->SetPixelRoundMode(PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE);
    listNode->context_ = AceType::RawPtr(context);
    pattern->frameNode_ = listNode;
    std::vector<float> mainSize = { 2.0f, 4.0f };
    model.SetListChildrenMainSize(listNode, 2.0f, mainSize);
    EXPECT_NE(pattern->childrenSize_, nullptr);

    /**
     * @tc.steps: step2. Calling the SetListChildrenMainSize function
     * @tc.expected: The childrenSize_ is reset to empty
     */
    model.ResetListChildrenMainSize(listNode);
    listNode->context_ = nullptr;
    EXPECT_EQ(pattern->childrenSize_, nullptr);
    CreateDone();
}

/**
 * @tc.name: GetDivider
 * @tc.desc: Test ListItemGroupModelNG GetDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, GetDivider, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListItemGroupLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListItemGroupLayoutProperty>();
    listNode->SetLayoutProperty(layoutProperty);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->frameNode_ = listNode;

    /**
     * @tc.steps: step2. Set the divider
     */
    V2::ItemDivider divider = { 6.0_vp, 2.0_vp, 8.0_vp, Color::RED };
    model.SetDivider(divider);

    /**
     * @tc.steps: step3. Calling the GetDivider function
     * @tc.expected: The diver is set successfully, and the obtained diver is the same as the setting
     */
    auto result = model.GetDivider(listNode);
    EXPECT_EQ(result, divider);
    CreateDone();
}

/**
 * @tc.name: SetSpace_TwoParameters
 * @tc.desc: Test ListItemGroupModelNG SetSpace
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, SetSpace_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    RefPtr<ListItemGroupLayoutProperty> layoutProperty = AceType::MakeRefPtr<ListItemGroupLayoutProperty>();
    listNode->SetLayoutProperty(layoutProperty);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->frameNode_ = listNode;

    /**
     * @tc.steps: step2. Set the space size
     */
    Dimension space = 20.0_vp;

    /**
     * @tc.steps: step3. Calling the SetSpace function
     * @tc.expected: The space is set successfully
     */
    model.SetSpace(listNode, space);
    auto value = listNode->GetLayoutProperty<ListItemGroupLayoutProperty>()->GetSpaceValue();
    EXPECT_EQ(value, 20.0_vp);
    CreateDone();
}

/**
 * @tc.name: RemoveHeader_NoParameter
 * @tc.desc: Test ListItemGroupModelNG RemoveHeader
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, RemoveHeader_NoParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetHeaderComponentContentExist(false);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto headerNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(headerNode, nullptr);

    /**
     * @tc.steps: step2. Calling the SetHeader function
     * @tc.expected: Set the isHeaderComponentContentExist_ to true
     */
    model.SetHeader(listNode, AceType::RawPtr(headerNode));
    EXPECT_TRUE(pattern->isHeaderComponentContentExist_);

    /**
     * @tc.steps: step3. Calling the RemoveHeader function
     * @tc.expected: The isHeaderComponentContentExist_ be false
     */
    model.RemoveHeader();
    EXPECT_FALSE(pattern->isHeaderComponentContentExist_);
    CreateDone();
}

/**
 * @tc.name: RemoveFooter_NoParameter
 * @tc.desc: Test ListItemGroupModelNG RemoveFooter
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, RemoveFooter_NoParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetFooterComponentContentExist(false);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto footerNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(footerNode, nullptr);

    /**
     * @tc.steps: step2. Calling the SetFooter function
     * @tc.expected: Set the isFooterComponentContentExist_ to true
     */
    model.SetFooter(listNode, AceType::RawPtr(footerNode));
    EXPECT_TRUE(pattern->isFooterComponentContentExist_);

    /**
     * @tc.steps: step3. Calling the RemoveFooter function
     * @tc.expected: The isFooterComponentContentExist_ be false
     */
    model.RemoveFooter();
    EXPECT_FALSE(pattern->isFooterComponentContentExist_);
    CreateDone();
}

/**
 * @tc.name: HasHeader
 * @tc.desc: Test ListItemGroupModelNG HasHeader
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, HasHeader, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetHeaderComponentContentExist(false);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto headerNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(headerNode, nullptr);

    /**
     * @tc.steps: step2. Set the headerNode
     */
    model.SetHeader(listNode, AceType::RawPtr(headerNode));

    /**
     * @tc.steps: step3. Calling the HasHeader function
     * @tc.expected: The result of the invocation of the function is true
     */
    auto result = model.HasHeader(listNode);
    EXPECT_TRUE(result);
    CreateDone();
}

/**
 * @tc.name: HasFooter
 * @tc.desc: Test ListItemGroupModelNG HasFooter
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupModelTestNg, HasFooter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListItemGroupModelNG model;
    model.Create(V2::ListItemGroupStyle::CARD);
    auto listNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(listNode, nullptr);
    auto pattern = listNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetFooterComponentContentExist(false);
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    auto footerNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, listPattern);
    ASSERT_NE(footerNode, nullptr);

    /**
     * @tc.steps: step2. Set the footerNode
     */
    model.SetFooter(listNode, AceType::RawPtr(footerNode));

    /**
     * @tc.steps: step3. Calling the HasFooter function
     * @tc.expected: The result of the invocation of the function is true
     */
    auto result = model.HasFooter(listNode);
    EXPECT_TRUE(result);
    CreateDone();
}
} // namespace OHOS::Ace::NG