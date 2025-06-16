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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components/theme/app_theme.h"

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

struct HandleFocusCanBeActiveTestCase {
    bool initialActive = false;
    bool focusCanBeActive = false;
    bool setActiveByUser = false;
    bool parameterSwitch = false;
    bool exceptResult = false;
};

const std::vector<HandleFocusCanBeActiveTestCase> FOCUS_ACTIVE_SUPPORT_HIERARCHY_PARAMETER_TEST_CASE = {
    { false, false, true, false, false },
    { false, false, true, true, false },
    { false, true, true, false, true },
    { false, true, true, true, false },
    { true, false, false, false, false },
    { true, false, true, false, true },
    { true, true, false, false, false },
    { true, true, true, false, true },
    { true, true, true, true, false },
};

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

/**
 * @tc.name: FocusManagerTest019
 * @tc.desc: HandleKeyForExtendOrActivateFocus
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page
     *   - Column
     *     - Button
     *     - Button
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    EXPECT_NE(focusManager, nullptr);
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();

    auto buttonPattern1 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode1 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern1);
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();

    auto buttonPattern2 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode2 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern2);
    auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();

    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode1);
    columnNode->AddChild(buttonNode2);

    EXPECT_EQ(pagePattern->GetViewRootScope(), columnFocusHub);
    pagePattern->FocusViewShow();
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_EQ(pagePattern->GetIsViewRootScopeFocused(), true);
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());

    /**
     * @tc.steps: step2. sendKeyEvent down and tab.
     * expected: active and button1 focus
     */
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_TAB };
    event.action = KeyAction::DOWN;
    auto curFocusView = focusManager ? focusManager->GetLastFocusView().Upgrade() : nullptr;
    focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    EXPECT_EQ(focusManager->GetIsFocusActive(), true);
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), true);

    /**
     * @tc.steps: step3. sendKeyEvent up and tab.
     * expected: unactive and button1 blur
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    FocusHub::LostFocusToViewRoot();
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);
    event.pressedCodes = { KeyCode::KEY_TAB };
    event.action = KeyAction::UP;
    focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);

    /**
     * @tc.steps: step4. sendKeyEvent dwon and direction.
     * expected: active and button1 focus
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    FocusHub::LostFocusToViewRoot();
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);
    event.pressedCodes = { KeyCode::KEY_DPAD_UP };
    event.code = KeyCode::KEY_DPAD_UP;
    event.action = KeyAction::DOWN;
    pageFocusHub->enableDirectionalKeyFocus_ = true;
    focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    EXPECT_EQ(focusManager->GetIsFocusActive(), true);
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), true);

    /**
     * @tc.steps: step5. sendKeyEvent up and direction.
     * expected: unactive and button1 blur
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    FocusHub::LostFocusToViewRoot();
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);
    event.pressedCodes = { KeyCode::KEY_DPAD_UP };
    event.code = KeyCode::KEY_DPAD_UP;
    event.action = KeyAction::UP;
    pageFocusHub->enableDirectionalKeyFocus_ = true;
    focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);

    /**
     * @tc.steps: step6. sendKeyEvent dwon and joystick direction.
     * expected: active and button1 focus
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    FocusHub::LostFocusToViewRoot();
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);
    event.pressedCodes = { KeyCode::KEY_DPAD_UP };
    event.code = KeyCode::KEY_DPAD_UP;
    event.sourceType = SourceType::JOYSTICK;
    event.action = KeyAction::DOWN;
    focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    EXPECT_EQ(focusManager->GetIsFocusActive(), true);
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), true);

    /**
     * @tc.steps: step7. sendKeyEvent up and joystick direction.
     * expected: unactive and button1 blur
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    FocusHub::LostFocusToViewRoot();
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);
    event.pressedCodes = { KeyCode::KEY_DPAD_UP };
    event.code = KeyCode::KEY_DPAD_UP;
    event.sourceType = SourceType::JOYSTICK;
    event.action = KeyAction::UP;
    focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);

    /**
     * @tc.steps: step8. sendKeyEvent dwon and joystick space.
     * expected: unactive and button1 blur
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    FocusHub::LostFocusToViewRoot();
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);
    event.pressedCodes = { KeyCode::KEY_SPACE };
    event.code = KeyCode::KEY_SPACE;
    event.sourceType = SourceType::JOYSTICK;
    event.action = KeyAction::DOWN;
    focusManager->HandleKeyForExtendOrActivateFocus(event, curFocusView);
    EXPECT_EQ(focusManager->GetIsFocusActive(), false);
    EXPECT_EQ(buttonFocusHub1->IsCurrentFocus(), false);
}

/**
 * @tc.name: FocusManagerTest020
 * @tc.desc: SetIsFocusActive
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct components.
     * - Page
     *   - Column
     *     - Button
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    EXPECT_NE(focusManager, nullptr);
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, -1, columnPattern);
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();

    auto buttonPattern1 = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode1 = FrameNodeOnTree::CreateFrameNode(V2::BUTTON_ETS_TAG, -1, buttonPattern1);
    auto buttonFocusHub1 = buttonNode1->GetOrCreateFocusHub();

    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode1);

    EXPECT_EQ(pagePattern->GetViewRootScope(), columnFocusHub);
    pagePattern->FocusViewShow();
    PipelineContext::GetCurrentContext()->FlushFocusView();
    EXPECT_EQ(pagePattern->GetIsViewRootScopeFocused(), true);
    EXPECT_TRUE(columnFocusHub->IsCurrentFocus());
    
    /**
     * @tc.steps: step2. SetFocusActive autoFocusInactive.
     * expected: equal set
     */
    focusManager->SetIsFocusActive(true, FocusActiveReason::USE_API, false);
    EXPECT_FALSE(focusManager->autoFocusInactive_);
    focusManager->SetIsFocusActive(true, FocusActiveReason::USE_API, true);
    EXPECT_TRUE(focusManager->autoFocusInactive_);

    /**
     * @tc.steps: step3. SetFocusActive autoFocusInactive false and set by pointer event.
     * expected: unactive
     */
    focusManager->autoFocusInactive_ = true;
    focusManager->isFocusActive_ = false;
    focusManager->SetIsFocusActive(false, FocusActiveReason::POINTER_EVENT);
    EXPECT_FALSE(focusManager->isFocusActive_);

    /**
     * @tc.steps: step4. SetFocusActive with check focusCanBeActive.
     * expected: focusCanBeActive dicedes isFocusActive.
     */
    focusManager->isFocusActive_ = false;
    SystemProperties::focusCanBeActive_.store(false);
    focusManager->SetIsFocusActive(true);
    EXPECT_FALSE(focusManager->isFocusActive_);
    SystemProperties::focusCanBeActive_.store(true);
    focusManager->SetIsFocusActive(true);
    EXPECT_TRUE(focusManager->isFocusActive_);

    /**
     * @tc.steps: step5. SetFocusActive with check focusActiveByTab.
     * expected: focusActiveByTab dicedes isFocusActive.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto appTheme = context->GetTheme<AppTheme>();
    focusManager->isFocusActive_ = false;
    appTheme->focusActiveByTab_ = false;
    focusManager->SetIsFocusActive(true, FocusActiveReason::KEY_TAB);
    EXPECT_FALSE(focusManager->isFocusActive_);
    appTheme->focusActiveByTab_ = true;
    focusManager->SetIsFocusActive(true, FocusActiveReason::KEY_TAB);
    EXPECT_TRUE(focusManager->isFocusActive_);
}

/**
 * @tc.name: FocusManagerTest021
 * @tc.desc: test focusActive
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest021, TestSize.Level1)
{
    for (const auto& testCase : FOCUS_ACTIVE_SUPPORT_HIERARCHY_PARAMETER_TEST_CASE) {
        auto context = PipelineContext::GetCurrentContext();
        ASSERT_NE(context, nullptr);
        auto focusManager = context->GetOrCreateFocusManager();
        ASSERT_NE(focusManager, nullptr);
        focusManager->isFocusActive_ = testCase.initialActive;
        SystemProperties::focusCanBeActive_.store(testCase.focusCanBeActive);
        focusManager->SetIsFocusActive(testCase.setActiveByUser, FocusActiveReason::USE_API);
        if (testCase.parameterSwitch && testCase.focusCanBeActive) {
            focusManager->SetIsFocusActive(false, FocusActiveReason::USE_API);
        }
        EXPECT_EQ(focusManager->isFocusActive_, testCase.exceptResult);
    }
}

/**
 * @tc.name: FocusManagerTest022
 * @tc.desc: test focusActive
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest022, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->SetKeyProcessingMode(KeyProcessingMode::ANCESTOR_EVENT);
    auto keyProcessingMode = focusManager->GetKeyProcessingMode();
    EXPECT_EQ(keyProcessingMode, KeyProcessingMode::ANCESTOR_EVENT);
}

/**
 * @tc.name: FocusManagerTest023
 * @tc.desc: test focusActive
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest023, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->SetKeyProcessingMode(KeyProcessingMode::FOCUS_NAVIGATION);
    auto keyProcessingMode = focusManager->GetKeyProcessingMode();
    EXPECT_EQ(keyProcessingMode, KeyProcessingMode::FOCUS_NAVIGATION);
}

/**
 * @tc.name: FocusManagerTest021
 * @tc.desc: SyncWindowsFocus
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest024, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, properties.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps2: Call the function SyncWindowsFocus.
     * @tc.expected: Test the stability of this function.
     */
    focusManager->isFocusActive_= true;
    focusManager->SyncWindowsFocus(false, FocusActiveReason::KEY_TAB);
    EXPECT_FALSE(focusManager->isFocusActive_);
}

/**
 * @tc.name: FocusManagerTest025
 * @tc.desc: Test that focus scroll is triggered after screen rotation to ensure focused node is visible.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest025, TestSize.Level1)
{
    /**
     * @tc.steps1: Get current pipeline context and create FocusManager.
     * @tc.expected: FocusManager is created successfully and isNeedTriggerScroll_ is nullopt initially.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = AceType::MakeRefPtr<FocusManager>(pipeline);
    ASSERT_NE(focusManager, nullptr);
    focusManager->isNeedTriggerScroll_ = std::nullopt;
    EXPECT_EQ(focusManager->isNeedTriggerScroll_, std::nullopt);

    /**
     * @tc.steps2: Simulate a screen rotation via surfaceChangedCallbackMap_.
     * @tc.expected: isNeedTriggerScroll_ is set to true, indicating a scroll should be triggered.
     */
    for (const auto& [id, callback] : pipeline->surfaceChangedCallbackMap_) {
        if (callback) {
            callback(1080, 1920, 1080, 720, WindowSizeChangeReason::ROTATION);
        }
    }
    EXPECT_EQ(focusManager->isNeedTriggerScroll_, true);
}

/**
 * @tc.name: FocusManagerTest026
 * @tc.desc: Test that activating main window pipeline also activates all child pipelines.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest026, TestSize.Level1)
{
    /**
     * @tc.steps1: Get current MockPipelineContext and retrieve FocusManager.
     * @tc.expected: FocusManager is created and initially inactive.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    focusManager->isFocusActive_ = false;

    /**
     * @tc.steps2: Call SetIsFocusActive(true) to activate main window pipeline.
     * @tc.expected: isFocusActive_ becomes true, indicating activation is successful.
     */
    focusManager->SetIsFocusActive(true, FocusActiveReason::USE_API, false);
    EXPECT_TRUE(focusManager->isFocusActive_);
}

/**
 * @tc.name: FocusManagerTest027
 * @tc.desc: Test that focusGuard is executed when window gains focus and is destroyed at the end of its lifecycle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest027, TestSize.Level1)
{
    /**
     * @tc.steps1: Get the current pipeline context and its FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps2: Create root node and page node with corresponding FocusHub.
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();

    /**
     * @tc.steps3: Add pageNode to rootNode and trigger page focus show.
     */
    rootNode->AddChild(pageNode);
    pagePattern->FocusViewShow();
    context->FlushFocusView();

    /**
     * @tc.steps4: Simulate window focus and check internal focusGuard-related flags.
     * @tc.expected: isSwitchingFocus_ is set temporarily, and then reset; endReason_ is set.
     */
    focusManager->WindowFocus(true);

    EXPECT_TRUE(focusManager->isSwitchingFocus_.has_value());
    EXPECT_FALSE(focusManager->isSwitchingFocus_.value());
    EXPECT_TRUE(focusManager->endReason_.has_value());
}
} // namespace OHOS::Ace::NG
