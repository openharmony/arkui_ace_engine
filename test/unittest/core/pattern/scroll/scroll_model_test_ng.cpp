/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"
#include "ui/base/ace_type.h"

#include "base/memory/ace_type.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"

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

/**
 * @tc.name: ScrollModelNGTestNg009
 * @tc.desc: Test CreateWithResourceObjFriction.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg009, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    ASSERT_NE(pattern, nullptr);

    ScrollModelNG model;
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    model.CreateWithResourceObjFriction(nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.CreateWithResourceObjFriction(resObj);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetFriction(), FRICTION);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "30.0");
    model.CreateWithResourceObjFriction(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetFriction(), 30.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "-30.0");
    model.CreateWithResourceObjFriction(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetFriction(), FRICTION);

    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ScrollModelNGTestNg010
 * @tc.desc: Test static CreateWithResourceObjFriction.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg010, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    ASSERT_NE(pattern, nullptr);

    ResetMockResourceData();
    g_isConfigChangePerform = true;
    ScrollModelNG::CreateWithResourceObjFriction(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ScrollModelNG::CreateWithResourceObjFriction(frameNode, resObj);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetFriction(), FRICTION);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "30.0");
    ScrollModelNG::CreateWithResourceObjFriction(frameNode, resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetFriction(), 30.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "-30.0");
    ScrollModelNG::CreateWithResourceObjFriction(frameNode, resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetFriction(), FRICTION);

    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ScrollModelNGTestNg011
 * @tc.desc: Test CreateWithResourceObjIntervalSize.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg011, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);

    ScrollModelNG model;
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    model.CreateWithResourceObjIntervalSize(nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    model.CreateWithResourceObjIntervalSize(resObj);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 0.0f);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    model.CreateWithResourceObjIntervalSize(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 100.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "invaild");
    model.CreateWithResourceObjIntervalSize(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 0.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::NONE);
    model.CreateWithResourceObjIntervalSize(resObjWithString);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 0.0f);

    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ScrollModelNGTestNg012
 * @tc.desc: Test CreateWithResourceObjIntervalSize.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg012, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);

    ResetMockResourceData();
    g_isConfigChangePerform = true;
    std::vector<RefPtr<ResourceObject>> resObjs;
    ScrollModelNG::CreateWithResourceObjIntervalSize(frameNode, resObjs);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    resObjs.push_back(resObj);
    ScrollModelNG::CreateWithResourceObjIntervalSize(frameNode, resObjs);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 0.0f);

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    resObjs.resize(1);
    resObjs[0] = resObjWithString;
    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    ScrollModelNG::CreateWithResourceObjIntervalSize(frameNode, resObjs);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 100.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "invaild");
    ScrollModelNG::CreateWithResourceObjIntervalSize(frameNode, resObjs);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 0.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::NONE);
    ScrollModelNG::CreateWithResourceObjIntervalSize(frameNode, resObjs);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 0.0f);

    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    resObjs.resize(10);
    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    ScrollModelNG::CreateWithResourceObjIntervalSize(frameNode, resObjs);
    pattern->resourceMgr_->ReloadResources();
    EXPECT_EQ(pattern->GetIntervalSize().Value(), 0.0f);

    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ScrollModelNGTestNg013
 * @tc.desc: Test CreateWithResourceObjSnapPaginations.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg013, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);

    ScrollModelNG model;
    ResetMockResourceData();
    g_isConfigChangePerform = true;
    Dimension dimension;
    std::vector<Dimension> snapPaginations = { Dimension(50.0, DimensionUnit::VP), dimension,
        Dimension(200.0, DimensionUnit::VP) };
    std::vector<RefPtr<ResourceObject>> resObjs(3, nullptr);
    model.CreateWithResourceObjSnapPaginations(snapPaginations, resObjs);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    resObjs[1] = resObj;
    model.CreateWithResourceObjSnapPaginations(snapPaginations, resObjs);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    pattern->resourceMgr_->ReloadResources();
    auto patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    resObjs[1] = resObjWithString;
    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    model.CreateWithResourceObjSnapPaginations(snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_FALSE(patternSnapPaginations.empty());
    EXPECT_EQ(patternSnapPaginations.size(), 3);
    EXPECT_EQ(patternSnapPaginations[0].Value(), 50.0f);
    EXPECT_EQ(patternSnapPaginations[1].Value(), 100.0f);
    EXPECT_EQ(patternSnapPaginations[2].Value(), 200.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "invaild");
    model.CreateWithResourceObjSnapPaginations(snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    ResetMockResourceData();
    AddMockResourceData(0, "-100.0");
    model.CreateWithResourceObjSnapPaginations(snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    ResetMockResourceData();
    AddMockResourceData(0, "500.0");
    model.CreateWithResourceObjSnapPaginations(snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    resObjs.resize(10);
    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    model.CreateWithResourceObjSnapPaginations(snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ScrollModelNGTestNg014
 * @tc.desc: Test static CreateWithResourceObjSnapPaginations.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ScrollModelNGTestNg014, TestSize.Level1)
{
    auto viewStackProcessor = ViewStackProcessor::GetInstance();
    auto buff = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    buff->layoutSeperately_ = true;
    viewStackProcessor->Push(buff);
    auto frameNode = viewStackProcessor->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);

    ResetMockResourceData();
    g_isConfigChangePerform = true;
    Dimension dimension;
    std::vector<Dimension> snapPaginations = { Dimension(50.0, DimensionUnit::VP), dimension,
        Dimension(200.0, DimensionUnit::VP) };
    std::vector<RefPtr<ResourceObject>> resObjs(3, nullptr);
    ScrollModelNG::CreateWithResourceObjSnapPaginations(frameNode, snapPaginations, resObjs);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    resObjs[1] = resObj;
    ScrollModelNG::CreateWithResourceObjSnapPaginations(frameNode, snapPaginations, resObjs);
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    pattern->resourceMgr_->ReloadResources();
    auto patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    std::vector<ResourceObjectParams> params;
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        0, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    resObjs[1] = resObjWithString;
    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    ScrollModelNG::CreateWithResourceObjSnapPaginations(frameNode, snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_FALSE(patternSnapPaginations.empty());
    EXPECT_EQ(patternSnapPaginations.size(), 3);
    EXPECT_EQ(patternSnapPaginations[0].Value(), 50.0f);
    EXPECT_EQ(patternSnapPaginations[1].Value(), 100.0f);
    EXPECT_EQ(patternSnapPaginations[2].Value(), 200.0f);

    ResetMockResourceData();
    AddMockResourceData(0, "invaild");
    ScrollModelNG::CreateWithResourceObjSnapPaginations(frameNode, snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    ResetMockResourceData();
    AddMockResourceData(0, "-100.0");
    ScrollModelNG::CreateWithResourceObjSnapPaginations(frameNode, snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    ResetMockResourceData();
    AddMockResourceData(0, "500.0");
    ScrollModelNG::CreateWithResourceObjSnapPaginations(frameNode, snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    resObjs.resize(10);
    ResetMockResourceData();
    AddMockResourceData(0, "100.0");
    ScrollModelNG::CreateWithResourceObjSnapPaginations(frameNode, snapPaginations, resObjs);
    pattern->resourceMgr_->ReloadResources();
    patternSnapPaginations = pattern->GetSnapPaginations();
    EXPECT_TRUE(patternSnapPaginations.empty());

    ResetMockResourceData();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: GetOnScrollEdge001
 * @tc.desc: Test ScrollModelNG GetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, GetOnScrollEdge001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;

    /**
     * @tc.steps: step2. Set axis to VERTICAL
     * and Change the value of the list member variable to make the IsAtTop of ListPattern function return true
     */
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->SetAxis(Axis::VERTICAL);
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, scrollablePattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->startMainPos_ = 18.0f;
    scrollablePattern->endMainPos_ = 20.0f;
    scrollablePattern->currentDelta_ = 2.0f;
    scrollablePattern->contentStartOffset_ = 4.0f;
    scrollablePattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    scrollablePattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };

    /**
     * @tc.steps: step3. Calling the GetOnScrollEdge function
     * @tc.expected: The result of calling the function returns SCROLL_TOP
     */
    auto result = scrollModelNG.GetOnScrollEdge(AceType::RawPtr(scrollNode));
    EXPECT_EQ(result, ScrollEdgeType::SCROLL_TOP);
}

/**
 * @tc.name: GetOnScrollEdge002
 * @tc.desc: Test ScrollModelNG GetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, GetOnScrollEdge002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;

    /**
     * @tc.steps: step2. Set axis to VERTICAL
     * and Change the value of the list member variable to make the IsAtBottom of ListPattern function return true
     */
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->SetAxis(Axis::VERTICAL);
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, scrollablePattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 2;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->maxListItemIndex_ = 4;
    scrollablePattern->startMainPos_ = 18.0f;
    scrollablePattern->endMainPos_ = 20.0f;
    scrollablePattern->currentDelta_ = 25.0f;
    scrollablePattern->contentStartOffset_ = 4.0f;
    scrollablePattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { false, true };
    scrollablePattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };

    /**
     * @tc.steps: step3. Calling the GetOnScrollEdge function
     * @tc.expected: The result of calling the function returns SCROLL_BOTTOM
     */
    auto result = scrollModelNG.GetOnScrollEdge(AceType::RawPtr(scrollNode));
    EXPECT_EQ(result, ScrollEdgeType::SCROLL_BOTTOM);
}

/**
 * @tc.name: GetOnScrollEdge003
 * @tc.desc: Test ScrollModelNG GetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, GetOnScrollEdge003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;

    /**
     * @tc.steps: step2. Set axis to HORIZONTAL
     * and Change the value of the list member variable to make the IsAtTop of ListPattern function return true
     */
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->SetAxis(Axis::HORIZONTAL);
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 0;
    scrollablePattern->startMainPos_ = 18.0f;
    scrollablePattern->endMainPos_ = 20.0f;
    scrollablePattern->currentDelta_ = 2.0f;
    scrollablePattern->contentStartOffset_ = 4.0f;
    scrollablePattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    scrollablePattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };

    /**
     * @tc.steps: step3. Calling the GetOnScrollEdge function
     * @tc.expected: The result of calling the function returns SCROLL_LEFT
     */
    auto result = scrollModelNG.GetOnScrollEdge(AceType::RawPtr(scrollNode));
    EXPECT_EQ(result, ScrollEdgeType::SCROLL_LEFT);
}

/**
 * @tc.name: GetOnScrollEdge004
 * @tc.desc: Test ScrollModelNG GetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, GetOnScrollEdge004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;

    /**
     * @tc.steps: step2. Set axis to HORIZONTAL
     * and Change the value of the list member variable to make the IsAtBottom of ListPattern function return true
     */
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->SetAxis(Axis::HORIZONTAL);
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, scrollablePattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 2;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->maxListItemIndex_ = 4;
    scrollablePattern->startMainPos_ = 18.0f;
    scrollablePattern->endMainPos_ = 20.0f;
    scrollablePattern->currentDelta_ = 25.0f;
    scrollablePattern->contentStartOffset_ = 4.0f;
    scrollablePattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { false, true };
    scrollablePattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };

    /**
     * @tc.steps: step3. Calling the GetOnScrollEdge function
     * @tc.expected: The result of calling the function returns SCROLL_RIGHT
     */
    auto result = scrollModelNG.GetOnScrollEdge(AceType::RawPtr(scrollNode));
    EXPECT_EQ(result, ScrollEdgeType::SCROLL_RIGHT);
}

/**
 * @tc.name: GetOnScrollEdge005
 * @tc.desc: Test ScrollModelNG GetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, GetOnScrollEdge005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;

    /**
     * @tc.steps: step2. Set axis to FREE
     * and Change the value of the list member variable to make the IsAtBottom of ListPattern function return true
     */
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->SetAxis(Axis::FREE);
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, scrollablePattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 2;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->maxListItemIndex_ = 4;
    scrollablePattern->startMainPos_ = 18.0f;
    scrollablePattern->endMainPos_ = 20.0f;
    scrollablePattern->currentDelta_ = 25.0f;
    scrollablePattern->contentStartOffset_ = 4.0f;
    scrollablePattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { false, true };
    scrollablePattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };

    /**
     * @tc.steps: step3. Calling the GetOnScrollEdge function
     * @tc.expected: The result of calling the function returns SCROLL_NONE
     */
    auto result = scrollModelNG.GetOnScrollEdge(AceType::RawPtr(scrollNode));
    EXPECT_EQ(result, ScrollEdgeType::SCROLL_NONE);
}

/**
 * @tc.name: GetOnScrollEdge006
 * @tc.desc: Test ScrollModelNG GetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, GetOnScrollEdge006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;

    /**
     * @tc.steps: step2. Set axis to VERTICAL
     * and Change the value of the list member variable to make the IsAtBottom of ListPattern function return false
     */
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->SetAxis(Axis::VERTICAL);
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, scrollablePattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 2;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->maxListItemIndex_ = 4;
    scrollablePattern->startMainPos_ = 18.0f;
    scrollablePattern->endMainPos_ = 20.0f;
    scrollablePattern->currentDelta_ = 25.0f;
    scrollablePattern->contentStartOffset_ = 4.0f;
    scrollablePattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { false, false };
    scrollablePattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };

    /**
     * @tc.steps: step3. Calling the GetOnScrollEdge function
     * @tc.expected: The result of calling the function returns SCROLL_NONE
     */
    auto result = scrollModelNG.GetOnScrollEdge(AceType::RawPtr(scrollNode));
    EXPECT_EQ(result, ScrollEdgeType::SCROLL_NONE);
}

/**
 * @tc.name: GetOnScrollEdge007
 * @tc.desc: Test ScrollModelNG GetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, GetOnScrollEdge007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;

    /**
     * @tc.steps: step2. Set axis to HORIZONTAL
     * and Change the value of the list member variable to make the IsAtBottom of ListPattern function return false
     */
    RefPtr<ListPattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();
    scrollablePattern->SetAxis(Axis::HORIZONTAL);
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 1, scrollablePattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollablePattern->isStackFromEnd_ = false;
    scrollablePattern->startIndex_ = 2;
    scrollablePattern->endIndex_ = 4;
    scrollablePattern->maxListItemIndex_ = 4;
    scrollablePattern->startMainPos_ = 18.0f;
    scrollablePattern->endMainPos_ = 20.0f;
    scrollablePattern->currentDelta_ = 25.0f;
    scrollablePattern->contentStartOffset_ = 4.0f;
    scrollablePattern->canStayOverScroll_ = false;
    ListItemGroupLayoutInfo itemGroupInfo = { false, false };
    scrollablePattern->itemPosition_[0] = { 2, 2.0f, 4.0f, true, false, 1.0f, 0.0f, itemGroupInfo };

    /**
     * @tc.steps: step3. Calling the GetOnScrollEdge function
     * @tc.expected: The result of calling the function returns SCROLL_NONE
     */
    auto result = scrollModelNG.GetOnScrollEdge(AceType::RawPtr(scrollNode));
    EXPECT_EQ(result, ScrollEdgeType::SCROLL_NONE);
}

/**
 * @tc.name: SetScrollController
 * @tc.desc: Test ScrollModelNG SetScrollController
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollController, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollableController> scroller = AceType::MakeRefPtr<ScrollableController>();
    RefPtr<ScrollBarProxy> proxy = AceType::MakeRefPtr<ScrollBarProxy>();

    /**
     * @tc.steps: step2. Calling the SetScrollController function
     * @tc.expected: The GetScrollBarProxy() of scrollPattern returns proxy
     */
    scrollModelNG.SetScrollController(AceType::RawPtr(scrollNode), scroller, proxy);
    EXPECT_EQ(scrollPattern->GetScrollBarProxy(), proxy);
}

/**
 * @tc.name: SetOnScrollFrameBegin_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnScrollFrameBegin
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnScrollFrameBegin_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    auto scrollHandler = [](Dimension delta, ScrollState state) -> ScrollFrameResult {
        Dimension newOffset;

        switch (state) {
            case ScrollState::IDLE:
                newOffset.SetValue(0.0);
                break;

            case ScrollState::SCROLL:
                newOffset.SetValue(delta.Value());
                break;

            case ScrollState::FLING:
                newOffset.SetValue(delta.Value() * 0.8);
                break;
        }

        return { newOffset };
    };

    /**
     * @tc.steps: step2. Calling the SetOnScrollFrameBegin function
     * @tc.expected: Calling the onScrollFrameBeginEvent returns 8.0
     */
    scrollModelNG.SetOnScrollFrameBegin(AceType::RawPtr(scrollNode), scrollHandler);
    auto onScrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    auto onScrollFrameBegin = onScrollFrameBeginEvent(Dimension(10.0), ScrollState::FLING);
    EXPECT_EQ(onScrollFrameBegin.offset.Value(), 8.0);
}

/**
 * @tc.name: SetOnScrollBegin_OneParameter
 * @tc.desc: Test ScrollModelNG SetOnScrollBegin
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnScrollBegin_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    stack->Push(scrollNode);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    auto scrollBeginHandler = [](Dimension initialDeltaX, Dimension initialDeltaY) -> ScrollInfo {
        return { initialDeltaX, initialDeltaY };
    };

    /**
     * @tc.steps: step2. Calling the SetOnScrollBegin function
     * @tc.expected: Calling the onScrollBeginEvent returns {10.0, 5.0}
     */
    scrollModelNG.SetOnScrollBegin(scrollBeginHandler);
    auto onScrollBeginEvent = eventHub->GetScrollBeginEvent();
    auto onScrollBegin = onScrollBeginEvent(Dimension(10.0), Dimension(5.0));
    EXPECT_EQ(onScrollBegin.dx.Value(), 10.0);
    EXPECT_EQ(onScrollBegin.dy.Value(), 5.0);
}

/**
 * @tc.name: SetOnScrollFrameBegin_OneParameter
 * @tc.desc: Test ScrollModelNG SetOnScrollFrameBegin
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnScrollFrameBegin_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    stack->Push(scrollNode);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    auto scrollHandler = [](Dimension delta, ScrollState state) -> ScrollFrameResult {
        Dimension newOffset;

        switch (state) {
            case ScrollState::IDLE:
                newOffset.SetValue(0.0);
                break;

            case ScrollState::SCROLL:
                newOffset.SetValue(delta.Value());
                break;

            case ScrollState::FLING:
                newOffset.SetValue(delta.Value() * 0.8);
                break;
        }

        return { newOffset };
    };

    /**
     * @tc.steps: step2. Calling the SetOnScrollFrameBegin function
     * @tc.expected: Calling the onScrollFrameBeginEvent returns 10.0
     */
    scrollModelNG.SetOnScrollFrameBegin(scrollHandler);
    auto onScrollFrameBeginEvent = eventHub->GetOnScrollFrameBegin();
    EXPECT_EQ(onScrollFrameBeginEvent(Dimension(10.0), ScrollState::SCROLL).offset.Value(), 10.0);
}

/**
 * @tc.name: SetOnWillScroll_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnWillScroll_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    auto scrollHandler = [](Dimension deltaX, Dimension deltaY, ScrollState state,
                             ScrollSource source) -> TwoDimensionScrollResult {
        TwoDimensionScrollResult result;

        bool isHorizontalAllowed = true;
        bool isVerticalAllowed = true;

        if (source == ScrollSource::SCROLL_BAR) {
            if (std::abs(deltaX.Value()) > std::abs(deltaY.Value())) {
                isVerticalAllowed = false;
            } else {
                isHorizontalAllowed = false;
            }
        }

        double stateMultiplier = 1.0;
        switch (state) {
            case ScrollState::IDLE:
                stateMultiplier = 0.0;
                break;
            case ScrollState::SCROLL:
                stateMultiplier = 1.0;
                break;
            case ScrollState::FLING:
                stateMultiplier = 1.2;
                break;
        }

        result.xOffset.value_ = isHorizontalAllowed ? deltaX.Value() * stateMultiplier : 0.0;
        result.yOffset.value_ = isVerticalAllowed ? deltaY.Value() * stateMultiplier : 0.0;

        return result;
    };

    /**
     * @tc.steps: step2. Calling the SetOnWillScroll function
     * @tc.expected: Calling the onWillScrollEvent returns {12.0, 0.0}
     */
    scrollModelNG.SetOnWillScroll(AceType::RawPtr(scrollNode), scrollHandler);
    auto onWillScrollEvent = eventHub->GetOnWillScrollEvent();
    auto scrollEventWithReturn =
        onWillScrollEvent(Dimension(10.0), Dimension(5.0), ScrollState::FLING, ScrollSource::SCROLL_BAR);
    EXPECT_EQ(scrollEventWithReturn.xOffset.Value(), 12.0);
    EXPECT_EQ(scrollEventWithReturn.yOffset.Value(), 0.0);
}

/**
 * @tc.name: SetOnDidScroll_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnDidScroll_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    bool scrollCallback = false;
    auto scrollHandler = [&scrollCallback](Dimension deltaX, Dimension deltaY, ScrollState state) {
        switch (state) {
            case ScrollState::IDLE: {
                scrollCallback = false;
                break;
            }
            case ScrollState::SCROLL: {
                scrollCallback = true;
                break;
            }
            default: {
                break;
            }
        }
    };

    /**
     * @tc.steps: step2. Calling the SetOnDidScroll function
     * @tc.expected: The scrollCallback from false to true
     */
    scrollModelNG.SetOnDidScroll(AceType::RawPtr(scrollNode), scrollHandler);
    auto onDidScrollEvent = eventHub->GetOnDidScrollEvent();
    onDidScrollEvent(Dimension(10.0), Dimension(5.0), ScrollState::SCROLL);
    EXPECT_TRUE(scrollCallback);
}

/**
 * @tc.name: SetOnReachStart_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnReachStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnReachStart_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    bool onStart = false;
    auto onReachStart = [&onStart]() { onStart = true; };

    /**
     * @tc.steps: step2. Calling the SetOnReachStart function
     * @tc.expected: The onStart from false to true
     */
    scrollModelNG.SetOnReachStart(AceType::RawPtr(scrollNode), onReachStart);
    auto onReachStartEvent = eventHub->GetOnReachStart();
    onReachStartEvent();
    EXPECT_TRUE(onStart);
}

/**
 * @tc.name: SetOnReachEnd_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnReachEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnReachEnd_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    bool onEnd = false;
    auto onReachEnd = [&onEnd]() { onEnd = true; };

    /**
     * @tc.steps: step2. Calling the SetOnReachEnd function
     * @tc.expected: The onEnd from false to true
     */
    scrollModelNG.SetOnReachEnd(AceType::RawPtr(scrollNode), onReachEnd);
    auto onReachEndEvent = eventHub->GetOnReachEnd();
    onReachEndEvent();
    EXPECT_TRUE(onEnd);
}

/**
 * @tc.name: SetScrollSnap_FiveParameters001
 * @tc.desc: Test ScrollModelNG SetScrollSnap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollSnap_FiveParameters001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetScrollSnapUpdate(false);
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollLayoutProperty> layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::CENTER);
    scrollNode->SetLayoutProperty(layoutProperty);
    scrollPattern->frameNode_ = scrollNode;
    Dimension intervalSize(10.0);
    std::vector<Dimension> snapPaginations = { Dimension(2.0), Dimension(4.0) };
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, false);
    scrollPattern->scrollSnapUpdate_ = false;

    /**
     * @tc.steps: step2. Set the scrollSnapAlign to NONE
     * @tc.expected: The scrollSnapUpdate_ return true
     */
    scrollModelNG.SetScrollSnap(
        AceType::RawPtr(scrollNode), ScrollSnapAlign::NONE, intervalSize, snapPaginations, enableSnapToSide);
    auto endElement = scrollPattern->GetSnapPaginations().back();
    EXPECT_EQ(endElement.Value(), 4.0);
    EXPECT_TRUE(scrollPattern->GetEnableSnapToSide().first);
    EXPECT_TRUE(scrollPattern->GetScrollSnapUpdate());
}

/**
 * @tc.name: SetScrollSnap_FiveParameters002
 * @tc.desc: Test ScrollModelNG SetScrollSnap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollSnap_FiveParameters002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetIntervalSize(Dimension(6.0));
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollLayoutProperty> layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::CENTER);
    scrollNode->SetLayoutProperty(layoutProperty);
    scrollPattern->frameNode_ = scrollNode;
    Dimension intervalSize(10.0);
    std::vector<Dimension> snapPaginations = { Dimension(2.0), Dimension(4.0) };
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, false);

    /**
     * @tc.steps: step2. Set the scrollSnapAlign to CENTER
     * @tc.expected: The value of intervalSize_ return 10.0
     */
    scrollModelNG.SetScrollSnap(
        AceType::RawPtr(scrollNode), ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    auto headElement = scrollPattern->GetSnapPaginations().front();
    EXPECT_EQ(headElement.Value(), 2.0);
    EXPECT_EQ(scrollPattern->GetIntervalSize().Value(), 10.0);
}

/**
 * @tc.name: SetScrollBarColor_OneParameter
 * @tc.desc: Test ScrollModelNG SetScrollBarColor
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollBarColor_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollablePaintProperty> paintProperty = AceType::MakeRefPtr<ScrollablePaintProperty>();
    scrollNode->paintProperty_ = paintProperty;
    stack->Push(scrollNode);
    Color color = Color::TRANSPARENT;

    /**
     * @tc.steps: step2. Calling the SetScrollBarColor function
     * @tc.expected: The GetScrollBarColor returns TRANSPARENT
     */
    scrollModelNG.SetScrollBarColor(color);
    EXPECT_EQ(scrollModelNG.GetScrollBarColor(AceType::RawPtr(scrollNode)), color.GetValue());
}

/**
 * @tc.name: SetScrollEnabled_OneParameter
 * @tc.desc: Test ScrollModelNG SetScrollEnabled
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollEnabled_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollLayoutProperty> layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    scrollNode->SetLayoutProperty(layoutProperty);
    stack->Push(scrollNode);

    /**
     * @tc.steps: step2. Calling the SetScrollEnabled function
     * @tc.expected: The GetScrollEnabled returns TRUE
     */
    scrollModelNG.SetScrollEnabled(true);
    EXPECT_TRUE(scrollModelNG.GetScrollEnabled(AceType::RawPtr(scrollNode)));
}

/**
 * @tc.name: SetOnScrollEdge_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnScrollEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnScrollEdge_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    bool edgeEvent = false;
    auto edgeHandler = [&edgeEvent](ScrollEdge edge) {
        if (edge == ScrollEdge::TOP || edge == ScrollEdge::BOTTOM) {
            edgeEvent = true;
        } else {
            edgeEvent = false;
        }
    };

    /**
     * @tc.steps: step2. Calling the SetOnScrollEdge function
     * @tc.expected: The edgeEvent from false to true
     */
    scrollModelNG.SetOnScrollEdge(AceType::RawPtr(scrollNode), edgeHandler);
    auto onEdgeEvent = eventHub->GetScrollEdgeEvent();
    onEdgeEvent(ScrollEdge::BOTTOM);
    EXPECT_TRUE(edgeEvent);
}

/**
 * @tc.name: SetInitialOffset_TwoParameters
 * @tc.desc: Test ScrollModelNG SetInitialOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetInitialOffset_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    OffsetT<CalcDimension> offset(CalcDimension(2.0), CalcDimension(4.0));

    /**
     * @tc.steps: step2. Calling the SetOnScrollEdge function
     * @tc.expected: The value of initialOffset_ return {2.0, 4.0}
     */
    scrollModelNG.SetInitialOffset(AceType::RawPtr(scrollNode), offset);
    EXPECT_EQ(scrollPattern->GetInitialOffset().GetX().Value(), 2.0);
    EXPECT_EQ(scrollPattern->GetInitialOffset().GetY().Value(), 4.0);
}

/**
 * @tc.name: SetScrollBarProxy_TwoParameters
 * @tc.desc: Test ScrollModelNG SetScrollBarProxy
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollBarProxy_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollBarProxy> proxy = AceType::MakeRefPtr<ScrollBarProxy>();

    /**
     * @tc.steps: step2. Calling the SetScrollBarProxy function
     * @tc.expected: The GetScrollBarProxy() of scrollPattern returns proxy
     */
    scrollModelNG.SetScrollBarProxy(AceType::RawPtr(scrollNode), proxy);
    EXPECT_EQ(scrollPattern->GetScrollBarProxy(), proxy);
}

/**
 * @tc.name: SetScrollSnap_FourParameters001
 * @tc.desc: Test ScrollModelNG SetScrollSnap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollSnap_FourParameters001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetScrollSnapUpdate(false);
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollLayoutProperty> layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::CENTER);
    scrollNode->SetLayoutProperty(layoutProperty);
    scrollPattern->frameNode_ = scrollNode;
    stack->Push(scrollNode);

    Dimension intervalSize(10.0);
    std::vector<Dimension> snapPaginations = { Dimension(2.0), Dimension(4.0) };
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, false);
    scrollPattern->scrollSnapUpdate_ = false;

    /**
     * @tc.steps: step2. Set the scrollSnapAlign to NONE
     * @tc.expected: The scrollSnapUpdate_ return true
     */
    scrollModelNG.SetScrollSnap(ScrollSnapAlign::NONE, intervalSize, snapPaginations, enableSnapToSide);
    auto endElement = scrollPattern->GetSnapPaginations().back();
    EXPECT_EQ(endElement.Value(), 4.0);
    EXPECT_TRUE(scrollPattern->GetEnableSnapToSide().first);
    EXPECT_TRUE(scrollPattern->GetScrollSnapUpdate());
}

/**
 * @tc.name: SetScrollSnap_FourParameters002
 * @tc.desc: Test ScrollModelNG SetScrollSnap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetScrollSnap_FourParameters002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetIntervalSize(Dimension(6.0));
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollLayoutProperty> layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::CENTER);
    scrollNode->SetLayoutProperty(layoutProperty);
    scrollNode->layoutSeperately_ = true;
    scrollPattern->frameNode_ = scrollNode;
    stack->Push(scrollNode);

    Dimension intervalSize(10.0);
    std::vector<Dimension> snapPaginations = { Dimension(2.0), Dimension(4.0) };
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, false);

    /**
     * @tc.steps: step2. Set the scrollSnapAlign to CENTER
     * @tc.expected: The value of intervalSize_ return 10.0
     */
    scrollModelNG.SetScrollSnap(ScrollSnapAlign::CENTER, intervalSize, snapPaginations, enableSnapToSide);
    auto headElement = scrollPattern->GetSnapPaginations().front();
    EXPECT_EQ(headElement.Value(), 2.0);
    EXPECT_EQ(scrollPattern->GetIntervalSize().Value(), 10.0);
}

/**
 * @tc.name: ResetZoomScale_NoParameter
 * @tc.desc: Test ScrollModelNG ResetZoomScale
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, ResetZoomScale_NoParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetZoomScale(2.0f);
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollLayoutProperty> layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    scrollNode->SetLayoutProperty(layoutProperty);
    scrollNode->layoutSeperately_ = true;
    scrollPattern->frameNode_ = scrollNode;
    stack->Push(scrollNode);

    /**
     * @tc.steps: step2. Calling the ResetZoomScale function
     * @tc.expected: The value of zoomScale_ from 2.0f to 1.0f
     */
    scrollModelNG.ResetZoomScale();
    EXPECT_EQ(scrollPattern->GetZoomScale(), 1.0f);
}

/**
 * @tc.name: SetEnableBouncesZoom_OneParameter
 * @tc.desc: Test ScrollModelNG SetEnableBouncesZoom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetEnableBouncesZoom_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetEnableBouncesZoom(false);
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollLayoutProperty> layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    scrollNode->SetLayoutProperty(layoutProperty);
    scrollNode->layoutSeperately_ = true;
    scrollPattern->frameNode_ = scrollNode;
    stack->Push(scrollNode);

    /**
     * @tc.steps: step2. Calling the SetEnableBouncesZoom function
     * @tc.expected: The value of enableBouncesZoom from false to true
     */
    scrollModelNG.SetEnableBouncesZoom(true);
    EXPECT_TRUE(scrollPattern->GetEnableBouncesZoom());
}

/**
 * @tc.name: SetEnableBouncesZoom_TwoParameters
 * @tc.desc: Test ScrollModelNG SetEnableBouncesZoom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetEnableBouncesZoom_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetEnableBouncesZoom(false);
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);

    /**
     * @tc.steps: step2. Calling the SetEnableBouncesZoom function
     * @tc.expected: The value of enableBouncesZoom from false to true
     */
    scrollModelNG.SetEnableBouncesZoom(AceType::RawPtr(scrollNode), true);
    EXPECT_TRUE(scrollPattern->GetEnableBouncesZoom());
}

/**
 * @tc.name: SetOnDidZoom_OneParameter
 * @tc.desc: Test ScrollModelNG SetOnDidZoom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnDidZoom_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    scrollPattern->frameNode_ = scrollNode;
    stack->Push(scrollNode);

    float offset = 2.0f;
    std::function<void(float)> zoomCallback = [&offset](float zoom) { offset += zoom; };

    /**
     * @tc.steps: step2. Calling the SetOnDidZoom function
     * @tc.expected: The value of offset return from 2.0 to 6.0
     */
    scrollModelNG.SetOnDidZoom(std::move(zoomCallback));
    eventHub->FireOnDidZoom(4.0f);
    EXPECT_EQ(offset, 6.0f);
}

/**
 * @tc.name: SetOnDidZoom_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnDidZoom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnDidZoom_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    scrollPattern->frameNode_ = scrollNode;

    float offset = 2.0f;
    std::function<void(float)> zoomCallback = [&offset](float zoom) { offset += zoom; };

    /**
     * @tc.steps: step2. Calling the SetOnDidZoom function
     * @tc.expected: The value of offset return from 2.0 to 6.0
     */
    scrollModelNG.SetOnDidZoom(AceType::RawPtr(scrollNode), std::move(zoomCallback));
    eventHub->FireOnDidZoom(4.0f);
    EXPECT_EQ(offset, 6.0f);
}

/**
 * @tc.name: SetOnZoomStart_OneParameter
 * @tc.desc: Test ScrollModelNG SetOnZoomStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnZoomStart_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    scrollPattern->frameNode_ = scrollNode;
    stack->Push(scrollNode);

    float offset = 2.0f;
    std::function<void()> zoomCallback = [&offset]() {
        float zoom = 0.0f;
        offset *= zoom;
    };

    /**
     * @tc.steps: step2. Calling the SetOnZoomStart function
     * @tc.expected: The value of offset return from 2.0 to 0.0
     */
    scrollModelNG.SetOnZoomStart(std::move(zoomCallback));
    eventHub->FireOnZoomStart();
    EXPECT_EQ(offset, 0.0f);
}

/**
 * @tc.name: SetOnZoomStart_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnZoomStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnZoomStart_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    scrollPattern->frameNode_ = scrollNode;

    float offset = 2.0f;
    std::function<void()> zoomCallback = [&offset]() {
        float zoom = 0.0f;
        offset *= zoom;
    };

    /**
     * @tc.steps: step2. Calling the SetOnZoomStart function
     * @tc.expected: The value of offset return from 2.0 to 0.0
     */
    scrollModelNG.SetOnZoomStart(AceType::RawPtr(scrollNode), std::move(zoomCallback));
    eventHub->FireOnZoomStart();
    EXPECT_EQ(offset, 0.0f);
}

/**
 * @tc.name: SetOnZoomStop_OneParameter
 * @tc.desc: Test ScrollModelNG SetOnZoomStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnZoomStop_OneParameter, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->layoutSeperately_ = true;
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    scrollPattern->frameNode_ = scrollNode;
    stack->Push(scrollNode);

    float offset = 2.0f;
    std::function<void()> zoomCallback = [&offset]() {
        float zoom = -1.0f;
        offset *= zoom;
    };

    /**
     * @tc.steps: step2. Calling the SetOnZoomStop function
     * @tc.expected: The value of offset return from 2.0 to -2.0
     */
    scrollModelNG.SetOnZoomStop(std::move(zoomCallback));
    eventHub->FireOnZoomStop();
    EXPECT_EQ(offset, -2.0f);
}

/**
 * @tc.name: SetOnZoomStop_TwoParameters
 * @tc.desc: Test ScrollModelNG SetOnZoomStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetOnZoomStop_TwoParameters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ScrollModelNG scrollModelNG;
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    RefPtr<ScrollEventHub> scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    scrollNode->eventHub_ = scrollEventHub;
    auto eventHub = scrollNode->GetEventHub<ScrollEventHub>();
    scrollPattern->frameNode_ = scrollNode;

    float offset = 1.0f;
    std::function<void()> zoomCallback = [&offset]() {
        float zoom = -1.0f;
        offset *= zoom;
    };

    /**
     * @tc.steps: step2. Calling the SetOnZoomStop function
     * @tc.expected: The value of offset return from 1.0 to -1.0f
     */
    scrollModelNG.SetOnZoomStop(AceType::RawPtr(scrollNode), std::move(zoomCallback));
    eventHub->FireOnZoomStop();
    EXPECT_EQ(offset, -1.0f);
}
} // namespace OHOS::Ace::NG