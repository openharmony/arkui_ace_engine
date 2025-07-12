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
} // namespace OHOS::Ace::NG