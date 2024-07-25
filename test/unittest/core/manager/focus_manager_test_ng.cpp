/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"
#define private public
#include "base/log/dump_log.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SIZE_1 = 1;
} // namespace

class FocusManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FocusManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void FocusManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: FocusManagerTest001
 * @tc.desc: Create FocusManager
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_TRUE(focusManager->focusViewStack_.empty());

    /**
     * @tc.steps: step2. lastFocusView_ is nullptr. GetWeakFocusViewList() is empty.
     */
    EXPECT_FALSE(focusManager->lastFocusView_.Upgrade());
    EXPECT_TRUE(focusManager->GetWeakFocusViewList().empty());
}

/**
 * @tc.name: FocusManagerTest002
 * @tc.desc: FocusViewShow / FocusViewHide / FocusViewClose
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager and a FocusView
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Do FocusViewShow. lastFocusView is focusView. GetWeakFocusViewList().size == 1
     */
    focusManager->FocusViewShow(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), pagePattern);
    EXPECT_EQ(focusManager->GetWeakFocusViewList().size(), SIZE_1);

    /**
     * @tc.steps: step3. Do FocusViewHide. lastFocusView is nullptr. GetWeakFocusViewList().size == 1
     */
    focusManager->FocusViewHide(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), nullptr);
    EXPECT_EQ(focusManager->GetWeakFocusViewList().size(), SIZE_1);

    /**
     * @tc.steps: step4. Do FocusViewClose. lastFocusView is nullptr. GetWeakFocusViewList().size == 0
     */
    focusManager->FocusViewShow(pagePattern);
    focusManager->FocusViewClose(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), nullptr);
    EXPECT_TRUE(focusManager->GetWeakFocusViewList().empty());
}

/**
 * @tc.name: FocusManagerTest003
 * @tc.desc: SetRequestFocusCallback / TriggerRequestFocusCallback
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    /**
     * @tc.steps: step2. call SetRequestFocusCallback and TriggerRequestFocusCallback.
     */
    bool flag = false;
    RequestFocusCallback requestFocusCallback = [&flag](NG::RequestFocusResult result) { flag = !flag; };
    focusManager->SetRequestFocusCallback(requestFocusCallback);
    focusManager->TriggerRequestFocusCallback(NG::RequestFocusResult::DEFAULT);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step3. TriggerRequestFocusCallback again.
     */
    focusManager->TriggerRequestFocusCallback(NG::RequestFocusResult::DEFAULT);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: FocusManagerTest004
 * @tc.desc: FlushFocusView
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = false;

    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageFouceView = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern));
    auto pageFouceView2 = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern2));

    focusManager->lastFocusView_ = pageFouceView;
    focusManager->focusViewStack_.push_back(pageFouceView);
    focusManager->focusViewStack_.push_back(pageFouceView2);

    focusManager->FlushFocusView();
    ASSERT_TRUE(focusManager->lastFocusView_.Invalid());

    pageFocusHub->currentFocus_ = true;
    focusManager->FlushFocusView();
    ASSERT_FALSE(focusManager->lastFocusView_.Invalid());
}

/**
 * @tc.name: FocusManagerTest005
 * @tc.desc: GetFocusViewMap
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = false;

    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageFouceView = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern));
    auto pageFouceView2 = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern2));

    focusManager->lastFocusView_ = pageFouceView;
    focusManager->focusViewStack_.push_back(pageFouceView);
    focusManager->focusViewStack_.push_back(pageFouceView2);
    focusManager->focusViewStack_.push_back(nullptr);

    std::unordered_map<int32_t, std::pair<WeakPtr<FocusView>, std::list<WeakPtr<FocusView>>>> focusViewMap;
    focusViewMap[1] = std::make_pair(pageFouceView, focusManager->focusViewStack_);

    focusManager->GetFocusViewMap(focusViewMap);
    ASSERT_FALSE(focusViewMap[1].second.empty());
}


/**
 * @tc.name: setFocusManagerViewStack
 * @tc.desc: setFocusManagerViewStack
 * @tc.type: FUNC
 */
void setFocusManagerViewStack(RefPtr<FocusManager> focusManager)
{
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = false;

    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageFouceView = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern));
    auto pageFouceView2 = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern2));

    focusManager->lastFocusView_ = pageFouceView;
    focusManager->focusViewStack_.push_back(pageFouceView);
    focusManager->focusViewStack_.push_back(pageFouceView2);
    focusManager->focusViewStack_.push_back(nullptr);
}

/**
 * @tc.name: FocusManagerTest006
 * @tc.desc: DumpFocusManager
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    focusManager->DumpFocusManager();
    
    auto ss = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    focusManager->DumpFocusManager();
    ASSERT_TRUE(DumpLog::GetInstance().GetDumpFile());

    setFocusManagerViewStack(focusManager);
    focusManager->DumpFocusManager();
    ASSERT_TRUE(DumpLog::GetInstance().GetDumpFile());
}

/**
 * @tc.name: FocusManagerTest007
 * @tc.desc: RemoveFocusScope
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    focusManager->RemoveFocusScope("scop1");
    ASSERT_TRUE(focusManager->focusHubScopeMap_.empty());

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = false;

    std::unordered_map<std::string, std::pair<WeakPtr<FocusHub>, std::list<WeakPtr<FocusHub>>>> focusHubScopeMap;
    std::list<WeakPtr<FocusHub>> focusHubScopeList;
    focusHubScopeList.push_back(pageFocusHub);
    focusHubScopeMap["scop1"] = std::make_pair(pageFocusHub, focusHubScopeList);
    std::list<WeakPtr<FocusHub>> focusHubScopeEmptyList;
    focusHubScopeMap["scop2"] = std::make_pair(pageFocusHub, focusHubScopeEmptyList);
    focusManager->focusHubScopeMap_ = focusHubScopeMap;

    focusManager->RemoveFocusScope("scop1");
    focusManager->RemoveFocusScope("scop2");
    ASSERT_TRUE(focusManager->focusHubScopeMap_.find("scop2") == focusManager->focusHubScopeMap_.end());
}

/**
 * @tc.name: FocusManagerTest008
 * @tc.desc: GetFocusScopePriorityList
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    ASSERT_EQ(focusManager->GetFocusScopePriorityList("scop1"), std::nullopt);
    
    std::list<WeakPtr<FocusHub>> focusHubScopeEmptyList;
    focusManager->focusHubScopeMap_["scop2"] = std::make_pair(nullptr, focusHubScopeEmptyList);
    ASSERT_EQ(focusManager->GetFocusScopePriorityList("scop2"), std::nullopt);

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    auto pageFocusHubWeakPtr = AceType::WeakClaim<FocusHub>(AceType::RawPtr<FocusHub>(pageFocusHub));
    focusHubScopeEmptyList.push_back(pageFocusHubWeakPtr);
    focusManager->focusHubScopeMap_["scop2"] = std::make_pair(pageFocusHub, focusHubScopeEmptyList);
    ASSERT_TRUE(focusManager->GetFocusScopePriorityList("scop2").has_value());
}

/**
 * @tc.name: FocusManagerTest009
 * @tc.desc: WindowFocusMoveEnd
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingWindow_ = true;

    focusManager->isSwitchingFocus_ = std::nullopt;
    focusManager->WindowFocusMoveEnd();
    ASSERT_FALSE(focusManager->isSwitchingWindow_);
}

/**
 * @tc.name: FocusManagerTest010
 * @tc.desc: FocusSwitchingEnd
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingWindow_ = true;

    focusManager->isSwitchingFocus_ = false;
    focusManager->FocusSwitchingEnd();
    ASSERT_TRUE(focusManager->isSwitchingFocus_);
}

/**
 * @tc.name: FocusManagerTest011
 * @tc.desc: GetFocusViewMap
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    setFocusManagerViewStack(focusManager);

    std::unordered_map<int32_t, std::pair<WeakPtr<FocusView>, std::list<WeakPtr<FocusView>>>> focusViewMap;
    focusViewMap[1] = std::make_pair(focusManager->lastFocusView_, focusManager->focusViewStack_);

    focusManager->GetFocusViewMap(focusViewMap);
    ASSERT_FALSE(focusViewMap[1].second.empty());
}

/**
 * @tc.name: setFocusManagerHubScopeMap
 * @tc.desc: setFocusManagerHubScopeMap
 * @tc.type: FUNC
 */
void setFocusManagerHubScopeMap(RefPtr<FocusManager> focusManager)
{
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();

    std::unordered_map<std::string, std::pair<WeakPtr<FocusHub>, std::list<WeakPtr<FocusHub>>>> focusHubScopeMap;
    std::list<WeakPtr<FocusHub>> focusHubScopeList;
    focusHubScopeList.push_back(pageFocusHub);
    focusHubScopeMap["scop1"] = std::make_pair(pageFocusHub, focusHubScopeList);
    std::list<WeakPtr<FocusHub>> focusHubScopeEmptyList;
    focusHubScopeMap["scop2"] = std::make_pair(nullptr, focusHubScopeEmptyList);
    focusManager->focusHubScopeMap_ = focusHubScopeMap;
}

/**
 * @tc.name: FocusManagerTest012
 * @tc.desc: AddFocusScope
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);

    setFocusManagerHubScopeMap(focusManager);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();

    ASSERT_TRUE(focusManager->AddFocusScope("scop1", pageFocusHub));
    ASSERT_TRUE(focusManager->AddFocusScope("scop2", pageFocusHub));
    focusManager->AddFocusScope("scop3", pageFocusHub);
    ASSERT_TRUE(focusManager->focusHubScopeMap_["scop3"].second.empty());
}

/**
 * @tc.name: FocusManagerTest013
 * @tc.desc: AddScopePriorityNode
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    setFocusManagerHubScopeMap(focusManager);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();

    focusManager->AddScopePriorityNode("scop1", pageFocusHub, true);
    ASSERT_FALSE(focusManager->focusHubScopeMap_["scop1"].second.empty());

    focusManager->AddScopePriorityNode("scop3", pageFocusHub, true);
    ASSERT_FALSE(focusManager->focusHubScopeMap_["scop3"].second.empty());
}

/**
 * @tc.name: FocusManagerTest014
 * @tc.desc: RemoveScopePriorityNode
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    setFocusManagerHubScopeMap(focusManager);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();

    focusManager->RemoveScopePriorityNode("scop1", pageFocusHub);
    focusManager->RemoveScopePriorityNode("scop2", pageFocusHub);
    ASSERT_TRUE(focusManager->focusHubScopeMap_["scop2"].second.empty());

    focusManager->RemoveScopePriorityNode("scop3", pageFocusHub);
    ASSERT_TRUE(focusManager->focusHubScopeMap_.find("scop3") == focusManager->focusHubScopeMap_.end());
    
    std::list<WeakPtr<FocusHub>> focusHubScopeEmptyList;
    focusManager->focusHubScopeMap_["scop4"] = std::make_pair(pageFocusHub, focusHubScopeEmptyList);
    focusManager->RemoveScopePriorityNode("scop4", pageFocusHub);

    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode2 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    auto pageFocusHub2 = pageNode2->GetOrCreateFocusHub();
    focusHubScopeEmptyList.push_back(pageFocusHub2);
    focusManager->focusHubScopeMap_["scop5"] = std::make_pair(nullptr, focusHubScopeEmptyList);
    focusManager->RemoveScopePriorityNode("scop5", pageFocusHub);
}

/**
 * @tc.name: FocusManagerTest015
 * @tc.desc: FlushFocusView
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest015, TestSize.Level1)
{
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootFocusHub->currentFocus_ = true;
    pageFocusHub->currentFocus_ = true;
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode2 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    auto pageFocusHub2 = pageNode2->GetOrCreateFocusHub();
    pageFocusHub2->currentFocus_ = true;
    rootNode->AddChild(pageNode2);
    pageNode2->AddChild(pageNode);

    auto pagePattern3 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode3 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern3);
    auto pageFocusHub3 = pageNode3->GetOrCreateFocusHub();
    pageFocusHub3->currentFocus_ = false;
    pageNode2->AddChild(pageNode3);

    auto pageFouceView = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern));
    auto pageFouceView2 = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern2));
    auto pageFouceView3 = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern3));

    focusManager->lastFocusView_ = pageFouceView3;
    focusManager->focusViewStack_.push_back(pageFouceView);
    focusManager->focusViewStack_.push_back(pageFouceView2);
    focusManager->focusViewStack_.push_back(pageFouceView3);

    focusManager->FlushFocusView();
    EXPECT_FALSE(focusManager->lastFocusView_.Invalid());
}

/**
 * @tc.name: FocusManagerTest016
 * @tc.desc: GetFocusViewMap
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest016, TestSize.Level1)
{
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = false;

    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageFouceView = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern));
    auto pageFouceView2 = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern2));

    focusManager->lastFocusView_ = pageFouceView;
    focusManager->focusViewStack_.push_back(pageFouceView);
    focusManager->focusViewStack_.push_back(pageFouceView2);

    std::unordered_map<int32_t, std::pair<WeakPtr<FocusView>, std::list<WeakPtr<FocusView>>>> focusViewMap;
    focusViewMap[1] = std::make_pair(pageFouceView, focusManager->focusViewStack_);

    focusManager->GetFocusViewMap(focusViewMap);
    EXPECT_FALSE(focusViewMap[1].second.empty());
}

/**
 * @tc.name: FocusManagerTest017
 * @tc.desc: DumpFocusManager
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest017, TestSize.Level1)
{
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto ss = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = false;

    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageFouceView = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern));
    auto pageFouceView2 = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern2));

    focusManager->lastFocusView_ = pageFouceView;
    focusManager->focusViewStack_.push_back(pageFouceView);
    std::unordered_map<int32_t, std::pair<WeakPtr<FocusView>, std::list<WeakPtr<FocusView>>>> focusViewMap;
    focusViewMap[1] = std::make_pair(pageFouceView, focusManager->focusViewStack_);
    focusManager->DumpFocusManager();
    setFocusManagerViewStack(focusManager);
    focusManager->DumpFocusManager();
    EXPECT_TRUE(DumpLog::GetInstance().GetDumpFile());
}

/**
 * @tc.name: FocusManagerTest018
 * @tc.desc: AddFocusScope
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest018, TestSize.Level1)
{
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();

    std::unordered_map<std::string, std::pair<WeakPtr<FocusHub>, std::list<WeakPtr<FocusHub>>>> focusHubScopeMap;
    std::list<WeakPtr<FocusHub>> focusHubScopeList;
    focusHubScopeList.push_back(pageFocusHub);
    focusHubScopeMap["scop1"] = std::make_pair(pageFocusHub, focusHubScopeList);
    std::list<WeakPtr<FocusHub>> focusHubScopeEmptyList;
    focusHubScopeMap["scop2"] = std::make_pair(nullptr, focusHubScopeEmptyList);
    focusManager->focusHubScopeMap_ = focusHubScopeMap;

    focusManager->AddFocusScope("scop1", pageFocusHub);
    focusManager->AddFocusScope("scop3", pageFocusHub);
    EXPECT_TRUE(focusManager->focusHubScopeMap_["scop3"].second.empty());
}
} // namespace OHOS::Ace::NG
