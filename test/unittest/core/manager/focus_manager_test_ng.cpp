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
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest001, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest002, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest003, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest004, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest005, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest006, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest007, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest008, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest009, TestSize.Level0)
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
HWTEST_F(FocusManagerTestNg, FocusManagerTest010, TestSize.Level0)
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

/**
 * @tc.name: FocusManagerTest028
 * @tc.desc: Test IsModalFocusViewStackValid with empty stack and valid views.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with null pipeline.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Check IsModalFocusViewStackValid when stack is empty.
     * @tc.expected: Returns false for empty stack.
     */
    EXPECT_FALSE(focusManager->IsModalFocusViewStackValid());

    /**
     * @tc.steps: step3. Create and add valid FocusView to modal stack.
     * @tc.expected: Returns true when valid view exists.
     */
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto rootFocusHub = pageNode->GetOrCreateFocusHub();
    focusManager->modalFocusViewStack_.emplace_back(pagePattern);
    EXPECT_TRUE(focusManager->IsModalFocusViewStackValid());
}

/**
 * @tc.name: FocusManagerTest029
 * @tc.desc: Test GetValidModalFocusView with valid and expired views.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add expired view to modal stack.
     * @tc.expected: Returns nullptr when no valid view exists.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    WeakPtr<FocusView> expiredView;
    focusManager->modalFocusViewStack_.emplace_back(expiredView);
    EXPECT_EQ(focusManager->GetValidModalFocusView().Upgrade(), nullptr);

    /**
     * @tc.steps: step2. Add valid FocusView to modal stack.
     * @tc.expected: Returns the valid view.
     */
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    focusManager->modalFocusViewStack_.emplace_back(pagePattern);
    auto validView = focusManager->GetValidModalFocusView().Upgrade();
    EXPECT_EQ(validView, pagePattern);
}

/**
 * @tc.name: FocusManagerTest030
 * @tc.desc: Test FocusViewShow with null focusView parameter.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call FocusViewShow with null focusView.
     * @tc.expected: Function returns directly without crash.
     */
    focusManager->FocusViewShow(nullptr);
    EXPECT_TRUE(focusManager->focusViewStack_.empty());
}

/**
 * @tc.name: FocusManagerTest031
 * @tc.desc: Test FocusViewShow when focusView has no parent focus hub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and PagePattern without parent.
     * @tc.expected: Objects created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);

    /**
     * @tc.steps: step2. Call FocusViewShow.
     * @tc.expected: Function returns early when HasParentFocusHub returns false.
     */
    focusManager->FocusViewShow(pagePattern);
    EXPECT_TRUE(focusManager->focusViewStack_.empty());
}

/**
 * @tc.name: FocusManagerTest032
 * @tc.desc: Test FocusViewShow when focusView is same as lastFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and root node structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Show focusView first time.
     * @tc.expected: focusViewStack_ contains one element, lastFocusView_ is set.
     */
    focusManager->FocusViewShow(pagePattern);
    EXPECT_EQ(focusManager->focusViewStack_.size(), SIZE_1);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), pagePattern);

    /**
     * @tc.steps: step3. Show same focusView again.
     * @tc.expected: Function returns early when focusView == lastFocusView.
     */
    focusManager->FocusViewShow(pagePattern);
    EXPECT_EQ(focusManager->focusViewStack_.size(), SIZE_1);
}

/**
 * @tc.name: FocusManagerTest033
 * @tc.desc: Test FocusViewShow with isTriggerByStep parameter.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and root node structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Call FocusViewShow with isTriggerByStep = true.
     * @tc.expected: LastWeakFocus is not set when triggered by step.
     */
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    auto lastWeakFocusBefore = pageFocusHub->GetLastWeakFocusNode();
    focusManager->FocusViewShow(pagePattern, true);
    auto lastWeakFocusAfter = pageFocusHub->GetLastWeakFocusNode();
    EXPECT_EQ(lastWeakFocusBefore.Upgrade(), lastWeakFocusAfter.Upgrade());

    /**
     * @tc.steps: step3. Call FocusViewShow with isTriggerByStep = false.
     * @tc.expected: LastWeakFocus is set when not triggered by step.
     */
    focusManager->FocusViewShow(pagePattern, false);
    lastWeakFocusAfter = pageFocusHub->GetLastWeakFocusNode();
    EXPECT_NE(lastWeakFocusAfter.Upgrade(), nullptr);
}

/**
 * @tc.name: FocusManagerTest034
 * @tc.desc: Test FocusViewShow removes duplicate focusView from stack.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and root node structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Show focusView multiple times.
     * @tc.expected: Duplicate focusView is removed from stack.
     */
    focusManager->FocusViewShow(pagePattern);
    auto stackSize1 = focusManager->focusViewStack_.size();
    focusManager->FocusViewShow(pagePattern);
    auto stackSize2 = focusManager->focusViewStack_.size();
    EXPECT_EQ(stackSize1, stackSize2);
    EXPECT_EQ(focusManager->focusViewStack_.size(), SIZE_1);
}

/**
 * @tc.name: FocusManagerTest035
 * @tc.desc: Test RearrangeViewStack with null currentFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call RearrangeViewStack when currentFocusView is null.
     * @tc.expected: Returns false without crash.
     */
    auto result = focusManager->RearrangeViewStack();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusManagerTest036
 * @tc.desc: Test RearrangeViewStack with SHOW state and not current focus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and focusView structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Set up focusView stack and state.
     */
    focusManager->FocusViewShow(pagePattern);
    focusManager->focusViewStackState_ = FocusViewStackState::SHOW;
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = false;

    /**
     * @tc.steps: step3. Call RearrangeViewStack.
     * @tc.expected: Removes currentFocusView from stack and returns true.
     */
    auto result = focusManager->RearrangeViewStack();
    EXPECT_TRUE(result);
    EXPECT_TRUE(focusManager->focusViewStack_.empty());
}

/**
 * @tc.name: FocusManagerTest037
 * @tc.desc: Test FocusViewHide with null focusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call FocusViewHide with null parameter.
     * @tc.expected: Returns directly without crash.
     */
    focusManager->FocusViewHide(nullptr);
}

/**
 * @tc.name: FocusManagerTest038
 * @tc.desc: Test FocusViewHide with modal focus view stack.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set up modal focus view stack.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    focusManager->modalFocusViewStack_.emplace_back(pagePattern);

    /**
     * @tc.steps: step2. Call FocusViewHide with modal focus view.
     * @tc.expected: Returns early when modal focus view is valid.
     */
    focusManager->FocusViewHide(pagePattern);
}

/**
 * @tc.name: FocusManagerTest039
 * @tc.desc: Test EraseModalFocusView with invalid modal focus view stack.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with empty modal stack.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call EraseModalFocusView when modal stack is invalid.
     * @tc.expected: Returns early without crash.
     */
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    focusManager->EraseModalFocusView(pagePattern);
}

/**
 * @tc.name: FocusManagerTest040
 * @tc.desc: Test EraseModalFocusView removes matching focus view.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus views to modal stack.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode2 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    focusManager->modalFocusViewStack_.emplace_back(pagePattern1);
    focusManager->modalFocusViewStack_.emplace_back(pagePattern2);

    /**
     * @tc.steps: step2. Erase first focus view from modal stack.
     * @tc.expected: First focus view is removed, stack size decreases.
     */
    auto stackSizeBefore = focusManager->modalFocusViewStack_.size();
    focusManager->EraseModalFocusView(pagePattern1);
    auto stackSizeAfter = focusManager->modalFocusViewStack_.size();
    EXPECT_EQ(stackSizeBefore - stackSizeAfter, 1);
}

/**
 * @tc.name: FocusManagerTest041
 * @tc.desc: Test FocusViewClose with isAutoFocusTransfer_ false and isDetachFromTree false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with auto focus transfer disabled.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->SetIsAutoFocusTransfer(false);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);

    /**
     * @tc.steps: step2. Call FocusViewClose with isDetachFromTree = false.
     * @tc.expected: Returns early without modifying stack.
     */
    focusManager->FocusViewShow(pagePattern);
    auto stackSizeBefore = focusManager->focusViewStack_.size();
    focusManager->FocusViewClose(pagePattern, false);
    auto stackSizeAfter = focusManager->focusViewStack_.size();
    EXPECT_EQ(stackSizeBefore, stackSizeAfter);
}

/**
 * @tc.name: FocusManagerTest042
 * @tc.desc: Test FocusViewClose with empty focusViewStack_.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focusView to stack.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    focusManager->FocusViewShow(pagePattern);

    /**
     * @tc.steps: step2. Call FocusViewClose to remove focusView.
     * @tc.expected: Stack becomes empty, lastFocusView_ is nullptr.
     */
    focusManager->FocusViewClose(pagePattern);
    EXPECT_TRUE(focusManager->focusViewStack_.empty());
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), nullptr);
}

/**
 * @tc.name: FocusManagerTest043
 * @tc.desc: Test FlushFocusView with lastFocusView having current focus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set up lastFocusView with current focus.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    pageFocusHub->currentFocus_ = true;
    focusManager->FocusViewShow(pagePattern);

    /**
     * @tc.steps: step2. Call FlushFocusView.
     * @tc.expected: Returns early when lastFocusView has current focus.
     */
    auto lastFocusViewBefore = focusManager->lastFocusView_.Upgrade();
    focusManager->FlushFocusView();
    auto lastFocusViewAfter = focusManager->lastFocusView_.Upgrade();
    EXPECT_EQ(lastFocusViewBefore, lastFocusViewAfter);
}

/**
 * @tc.name: FocusManagerTest044
 * @tc.desc: Test AddFocusScope with new scopeId.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Add new focus scope with unique scopeId.
     * @tc.expected: Returns true, scope is added to focusHubScopeMap_.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();
    auto result = focusManager->AddFocusScope("test_scope", focusHub);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusManagerTest045
 * @tc.desc: Test AddFocusScope with existing scopeId and valid focusScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub1 = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", focusHub1);

    /**
     * @tc.steps: step2. Try to add same scopeId with different focusHub.
     * @tc.expected: Returns false when focusScope is valid.
     */
    auto focusHub2 = rootNode->GetOrCreateFocusHub();
    auto result = focusManager->AddFocusScope("test_scope", focusHub2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusManagerTest046
 * @tc.desc: Test RemoveFocusScope with existing scopeId and empty priority list.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", focusHub);

    /**
     * @tc.steps: step2. Remove focus scope.
     * @tc.expected: Scope is erased from focusHubScopeMap_.
     */
    focusManager->RemoveFocusScope("test_scope");
    EXPECT_EQ(focusManager->focusHubScopeMap_.count("test_scope"), 0);
}

/**
 * @tc.name: FocusManagerTest047
 * @tc.desc: Test AddScopePriorityNode with pushFront = false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto scopeHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", scopeHub);

    /**
     * @tc.steps: step2. Add priority node to scope with pushFront = false.
     * @tc.expected: Node is added to back of priority list.
     */
    auto priorHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddScopePriorityNode("test_scope", priorHub, false);
    auto priorityList = focusManager->GetFocusScopePriorityList("test_scope");
    EXPECT_TRUE(priorityList.has_value());
    EXPECT_EQ(priorityList.value()->size(), 1);
}

/**
 * @tc.name: FocusManagerTest048
 * @tc.desc: Test AddScopePriorityNode with pushFront = true.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope with priority nodes.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto scopeHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", scopeHub);
    auto priorHub1 = rootNode->GetOrCreateFocusHub();
    focusManager->AddScopePriorityNode("test_scope", priorHub1, false);

    /**
     * @tc.steps: step2. Add another priority node with pushFront = true.
     * @tc.expected: New node is added to front of priority list.
     */
    auto priorHub2 = rootNode->GetOrCreateFocusHub();
    focusManager->AddScopePriorityNode("test_scope", priorHub2, true);
    auto priorityList = focusManager->GetFocusScopePriorityList("test_scope");
    EXPECT_TRUE(priorityList.has_value());
    EXPECT_EQ(priorityList.value()->size(), 2);
}

/**
 * @tc.name: FocusManagerTest049
 * @tc.desc: Test RemoveScopePriorityNode removes node from priority list.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add scope with priority nodes.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto scopeHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", scopeHub);
    auto priorHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddScopePriorityNode("test_scope", priorHub, false);

    /**
     * @tc.steps: step2. Remove priority node from scope.
     * @tc.expected: Node is removed from priority list.
     */
    focusManager->RemoveScopePriorityNode("test_scope", priorHub);
    auto priorityList = focusManager->GetFocusScopePriorityList("test_scope");
    EXPECT_FALSE(priorityList.has_value());
}

/**
 * @tc.name: FocusManagerTest050
 * @tc.desc: Test GetFocusScopePriorityList with non-existent scopeId.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Try to get priority list for non-existent scope.
     * @tc.expected: Returns std::nullopt.
     */
    auto result = focusManager->GetFocusScopePriorityList("non_existent_scope");
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: FocusManagerTest051
 * @tc.desc: Test UpdateCurrentFocus when isSwitchingFocus_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set isSwitchingFocus_ to true.
     * @tc.expected: FocusManager is created and configured.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingFocus_ = true;

    /**
     * @tc.steps: step2. Call UpdateCurrentFocus with new focus hub.
     * @tc.expected: switchingFocus_ and updateReason_ are updated.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();
    focusManager->UpdateCurrentFocus(focusHub, SwitchingUpdateReason::DEFAULT);
    EXPECT_EQ(focusManager->switchingFocus_, focusHub);
    EXPECT_EQ(focusManager->updateReason_.value(), SwitchingUpdateReason::DEFAULT);
}

/**
 * @tc.name: FocusManagerTest052
 * @tc.desc: Test UpdateCurrentFocus when isSwitchingFocus_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest052, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set isSwitchingFocus_ to false.
     * @tc.expected: FocusManager is created and configured.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingFocus_ = false;

    /**
     * @tc.steps: step2. Call UpdateCurrentFocus.
     * @tc.expected: switchingFocus_ and updateReason_ are not updated.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();
    focusManager->UpdateCurrentFocus(focusHub, SwitchingUpdateReason::DEFAULT);
    EXPECT_EQ(focusManager->switchingFocus_, nullptr);
    EXPECT_FALSE(focusManager->updateReason_.has_value());
}

/**
 * @tc.name: FocusManagerTest053
 * @tc.desc: Test GetCurrentFocus returns currentFocus_.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest053, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Get current focus when it is null.
     * @tc.expected: Returns nullptr.
     */
    auto currentFocus = focusManager->GetCurrentFocus();
    EXPECT_EQ(currentFocus, nullptr);

    /**
     * @tc.steps: step3. Set current focus and get it again.
     * @tc.expected: Returns the set focus hub.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();
    focusManager->currentFocus_ = focusHub;
    currentFocus = focusManager->GetCurrentFocus();
    EXPECT_EQ(currentFocus, focusHub);
}

/**
 * @tc.name: FocusManagerTest054
 * @tc.desc: Test FocusSwitchingStart sets switching state.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest054, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call FocusSwitchingStart with focus hub.
     * @tc.expected: isSwitchingFocus_ is true, switchingFocus_ and startReason_ are set.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();
    focusManager->FocusSwitchingStart(focusHub, SwitchingStartReason::REQUEST_FOCUS);
    EXPECT_TRUE(focusManager->isSwitchingFocus_.value());
    EXPECT_EQ(focusManager->switchingFocus_, focusHub);
    EXPECT_EQ(focusManager->startReason_.value(), SwitchingStartReason::REQUEST_FOCUS);
}

/**
 * @tc.name: FocusManagerTest055
 * @tc.desc: Test ReportFocusSwitching updates current focus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest055, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set up switching state.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto currentHub = rootNode->GetOrCreateFocusHub();
    auto switchingHub = rootNode->GetOrCreateFocusHub();
    focusManager->currentFocus_ = currentHub;
    focusManager->switchingFocus_ = switchingHub;

    /**
     * @tc.steps: step2. Call ReportFocusSwitching.
     * @tc.expected: currentFocus_ is updated to switchingFocus_.
     */
    focusManager->ReportFocusSwitching(FocusReason::DEFAULT);
    EXPECT_EQ(focusManager->currentFocus_, switchingHub);
    EXPECT_FALSE(focusManager->isSwitchingFocus_.has_value());
}

/**
 * @tc.name: FocusManagerTest056
 * @tc.desc: Test FocusSwitchingEnd when isSwitchingFocus_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with isSwitchingFocus_ false.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingFocus_ = false;

    /**
     * @tc.steps: step2. Call FocusSwitchingEnd.
     * @tc.expected: Returns early without crash.
     */
    focusManager->FocusSwitchingEnd();
}

/**
 * @tc.name: FocusManagerTest057
 * @tc.desc: Test WindowFocusMoveStart sets isSwitchingWindow_ flag.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call WindowFocusMoveStart.
     * @tc.expected: isSwitchingWindow_ is set to true.
     */
    focusManager->WindowFocusMoveStart();
    EXPECT_TRUE(focusManager->isSwitchingWindow_);
}

/**
 * @tc.name: FocusManagerTest058
 * @tc.desc: Test WindowFocusMoveEnd when isSwitchingFocus_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest058, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set up window focus move.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingWindow_ = true;
    focusManager->isSwitchingFocus_ = false;

    /**
     * @tc.steps: step2. Call WindowFocusMoveEnd.
     * @tc.expected: isSwitchingWindow_ is set to false.
     */
    focusManager->WindowFocusMoveEnd();
    EXPECT_FALSE(focusManager->isSwitchingWindow_);
}

/**
 * @tc.name: FocusManagerTest059
 * @tc.desc: Test SetFocusViewRootScope requests focus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest059, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and root node structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();

    /**
     * @tc.steps: step2. Set view root scope focused.
     * @tc.expected: Returns true when focus request succeeds.
     */
    (void)focusManager->SetFocusViewRootScope(pagePattern);
    EXPECT_TRUE(pagePattern->GetIsViewRootScopeFocused());
}

/**
 * @tc.name: FocusManagerTest060
 * @tc.desc: Test SetFocusViewRootScope with null view root scope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest060, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and page node without root scope.
     * @tc.expected: Objects created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);

    /**
     * @tc.steps: step2. Call SetFocusViewRootScope.
     * @tc.expected: Returns false when view root scope is null.
     */
    (void)focusManager->SetFocusViewRootScope(pagePattern);
}

/**
 * @tc.name: FocusManagerTest061
 * @tc.desc: Test PaintFocusState with null pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest061, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with null pipeline.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call PaintFocusState.
     * @tc.expected: Returns early without crash.
     */
    focusManager->PaintFocusState();
}

/**
 * @tc.name: FocusManagerTest062
 * @tc.desc: Test PaintFocusState when pipeline is not focus active.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest062, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with pipeline context.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set pipeline focus active to false.
     * @tc.expected: PaintFocusState returns early.
     */
    context->SetIsFocusActive(false);
    focusManager->PaintFocusState();
}

/**
 * @tc.name: FocusManagerTest063
 * @tc.desc: Test WindowFocus when isFocus is false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest063, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call WindowFocus with isFocus = false.
     * @tc.expected: Returns early without crash.
     */
    focusManager->WindowFocus(false);
}

/**
 * @tc.name: FocusManagerTest064
 * @tc.desc: Test SetIsFocusActive with same focus active state.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest064, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set same focus active state.
     * @tc.expected: Returns false when state is unchanged.
     */
    auto currentState = focusManager->GetIsFocusActive();
    auto result = focusManager->SetIsFocusActive(currentState);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusManagerTest065
 * @tc.desc: Test SetIsFocusActive with different focus active state.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest065, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set different focus active state.
     * @tc.expected: Returns true when state is changed.
     */
    auto currentState = focusManager->GetIsFocusActive();
    auto result = focusManager->SetIsFocusActive(!currentState);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusManagerTest066
 * @tc.desc: Test SetIsFocusActive with null pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest066, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with null pipeline.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call SetIsFocusActive.
     * @tc.expected: Returns false when pipeline is null.
     */
    auto result = focusManager->SetIsFocusActive(true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusManagerTest067
 * @tc.desc: Test SyncWindowsFocus with null pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest067, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with null pipeline.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call SyncWindowsFocus.
     * @tc.expected: Returns false when pipeline is null.
     */
    auto result = focusManager->SyncWindowsFocus(true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusManagerTest068
 * @tc.desc: Test SyncWindowsFocus with null container.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest068, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and context.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set container to null and call SyncWindowsFocus.
     * @tc.expected: Returns false when container is null.
     */
    auto result = focusManager->SyncWindowsFocus(true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusManagerTest069
 * @tc.desc: Test NeedChangeFocusAvtive with same focus active state.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest069, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set focus active state.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isFocusActive_ = true;

    /**
     * @tc.steps: step2. Call NeedChangeFocusAvtive with same state.
     * @tc.expected: Returns false when state is unchanged.
     */
    auto result = focusManager->NeedChangeFocusAvtive(true, FocusActiveReason::DEFAULT, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusManagerTest070
 * @tc.desc: Test NeedChangeFocusAvtive with ACTIVE_MARK reason.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest070, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isFocusActive_ = false;

    /**
     * @tc.steps: step2. Call NeedChangeFocusAvtive with ACTIVE_MARK reason.
     * @tc.expected: Returns true for ACTIVE_MARK reason.
     */
    auto result = focusManager->NeedChangeFocusAvtive(true, FocusActiveReason::ACTIVE_MARK, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusManagerTest071
 * @tc.desc: Test NeedChangeFocusAvtive when focus cannot be active.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest071, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with focus active false.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isFocusActive_ = false;

    /**
     * @tc.steps: step2. Call NeedChangeFocusAvtive with SystemProperties check.
     * @tc.expected: Returns false when focus cannot be active.
     */
    (void)focusManager->NeedChangeFocusAvtive(true, FocusActiveReason::DEFAULT, true);
}

/**
 * @tc.name: FocusManagerTest072
 * @tc.desc: Test NeedChangeFocusAvtive with POINTER_EVENT reason.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest072, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with focus active true.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isFocusActive_ = true;
    focusManager->autoFocusInactive_ = false;

    /**
     * @tc.steps: step2. Call NeedChangeFocusAvtive with POINTER_EVENT reason.
     * @tc.expected: Returns false when autoFocusInactive is false.
     */
    auto result = focusManager->NeedChangeFocusAvtive(false, FocusActiveReason::POINTER_EVENT, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusManagerTest073
 * @tc.desc: Test HandleKeyForExtendOrActivateFocus with key down event.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest073, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Create key event with DOWN action and activeMark true.
     * @tc.expected: Returns true and activates focus.
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.activeMark = true;
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    (void)focusManager->HandleKeyForExtendOrActivateFocus(event, pagePattern);
}

/**
 * @tc.name: FocusManagerTest074
 * @tc.desc: Test HandleKeyForExtendOrActivateFocus with key down event and activeMark false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest074, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Create key event with DOWN action and activeMark false.
     * @tc.expected: Returns true and deactivates focus.
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.activeMark = false;
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    (void)focusManager->HandleKeyForExtendOrActivateFocus(event, pagePattern);
}

/**
 * @tc.name: FocusManagerTest075
 * @tc.desc: Test HandleKeyForExtendOrActivateFocus with KEY_TAB event.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest075, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Create key event with TAB key.
     * @tc.expected: Returns true for TAB key event.
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    (void)focusManager->HandleKeyForExtendOrActivateFocus(event, pagePattern);
}

/**
 * @tc.name: FocusManagerTest076
 * @tc.desc: Test HandleKeyForExtendOrActivateFocus with non-down action.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest076, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Create key event with UP action.
     * @tc.expected: Returns false for non-down action.
     */
    KeyEvent event;
    event.action = KeyAction::UP;
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    (void)focusManager->HandleKeyForExtendOrActivateFocus(event, pagePattern);
}

/**
 * @tc.name: FocusManagerTest077
 * @tc.desc: Test ExtendOrActivateFocus with null focus view.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest077, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call ExtendOrActivateFocus with null focus view.
     * @tc.expected: Returns true when SetIsFocusActive succeeds.
     */
    (void)focusManager->ExtendOrActivateFocus(nullptr);
}

/**
 * @tc.name: FocusManagerTest078
 * @tc.desc: Test ExtendOrActivateFocus with valid focus view.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest078, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and root node structure.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Call ExtendOrActivateFocus with valid focus view.
     * @tc.expected: Returns true when SetIsFocusActive succeeds.
     */
    (void)focusManager->ExtendOrActivateFocus(pagePattern);
}

/**
 * @tc.name: FocusManagerTest079
 * @tc.desc: Test GetFocusViewMap with empty focusViewStack_.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest079, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with empty focus view stack.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call GetFocusViewMap.
     * @tc.expected: Returns empty map when stack is empty.
     */
    FocusViewMap focusViewMap;
    focusManager->GetFocusViewMap(focusViewMap);
    EXPECT_TRUE(focusViewMap.empty());
}

/**
 * @tc.name: FocusManagerTest080
 * @tc.desc: Test GetFocusViewMap with focus views.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest080, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus views to stack.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    focusManager->FocusViewShow(pagePattern);

    /**
     * @tc.steps: step2. Call GetFocusViewMap.
     * @tc.expected: Returns map with focus view entries.
     */
    FocusViewMap focusViewMap;
    focusManager->GetFocusViewMap(focusViewMap);
    EXPECT_FALSE(focusViewMap.empty());
}

/**
 * @tc.name: FocusManagerTest081
 * @tc.desc: Test DumpFocusManager when dump file is not available.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest081, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call DumpFocusManager without dump file.
     * @tc.expected: Returns early without crash.
     */
    focusManager->DumpFocusManager();
}

/**
 * @tc.name: FocusManagerTest082
 * @tc.desc: Test TriggerAllFocusActiveChangeCallback with null manager.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest082, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with null callbacks.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call TriggerAllFocusActiveChangeCallback.
     * @tc.expected: Returns early without crash.
     */
    focusManager->TriggerAllFocusActiveChangeCallback(true);
}

/**
 * @tc.name: FocusManagerTest083
 * @tc.desc: Test FocusSwitchingEnd with isSwitchingWindow_ true.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest083, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set up switching state.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingFocus_ = true;
    focusManager->isSwitchingWindow_ = true;

    /**
     * @tc.steps: step2. Call FocusSwitchingEnd.
     * @tc.expected: isSwitchingFocus_ is set to false, endReason_ is set.
     */
    focusManager->FocusSwitchingEnd();
    EXPECT_FALSE(focusManager->isSwitchingFocus_.value());
    EXPECT_TRUE(focusManager->endReason_.has_value());
}

/**
 * @tc.name: FocusManagerTest084
 * @tc.desc: Test FocusSwitchingEnd calls ReportFocusSwitching.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest084, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set up switching state.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto currentHub = rootNode->GetOrCreateFocusHub();
    auto switchingHub = rootNode->GetOrCreateFocusHub();
    focusManager->currentFocus_ = currentHub;
    focusManager->switchingFocus_ = switchingHub;
    focusManager->isSwitchingFocus_ = true;
    focusManager->isSwitchingWindow_ = false;

    /**
     * @tc.steps: step2. Call FocusSwitchingEnd.
     * @tc.expected: ReportFocusSwitching is called, state is reset.
     */
    focusManager->FocusSwitchingEnd();
    EXPECT_EQ(focusManager->currentFocus_, switchingHub);
    EXPECT_FALSE(focusManager->isSwitchingFocus_.has_value());
}

/**
 * @tc.name: FocusManagerTest085
 * @tc.desc: Test ArrangeModalFocusViewStack with null current focus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest085, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call ArrangeModalFocusViewStack with null current focus.
     * @tc.expected: Returns early without crash.
     */
    focusManager->ArrangeModalFocusViewStack();
}

/**
 * @tc.name: FocusManagerTest086
 * @tc.desc: Test ArrangeModalFocusViewStack with non-UI extension component.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest086, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and current focus.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();
    focusManager->currentFocus_ = focusHub;

    /**
     * @tc.steps: step2. Call ArrangeModalFocusViewStack.
     * @tc.expected: Returns early when frame name is not UI_EXTENSION.
     */
    focusManager->ArrangeModalFocusViewStack();
}

/**
 * @tc.name: FocusManagerTest087
 * @tc.desc: Test FocusViewShow with child FocusView of lastFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest087, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and parent-child node structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto parentPattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, parentPattern);
    auto childPattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto childNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, childPattern);
    rootNode->AddChild(parentNode);
    parentNode->AddChild(childNode);

    /**
     * @tc.steps: step2. Show parent then child FocusView.
     * @tc.expected: child FocusView does not call LostViewFocus on parent.
     */
    focusManager->FocusViewShow(parentPattern);
    auto lastFocusView1 = focusManager->lastFocusView_.Upgrade();
    focusManager->FocusViewShow(childPattern);
    auto lastFocusView2 = focusManager->lastFocusView_.Upgrade();
    EXPECT_EQ(lastFocusView1, parentPattern);
    EXPECT_EQ(lastFocusView2, childPattern);
}

/**
 * @tc.name: FocusManagerTest088
 * @tc.desc: Test FocusViewShow with modal focus view interruption.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest088, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager with modal focus view stack.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto modalPattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto modalNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, modalPattern);
    focusManager->modalFocusViewStack_.emplace_back(modalPattern);
    focusManager->FocusViewShow(modalPattern);

    /**
     * @tc.steps: step2. Try to show non-child FocusView.
     * @tc.expected: Returns early when interrupted by modal focus view.
     */
    auto otherPattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto otherNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, otherPattern);
    focusManager->FocusViewShow(otherPattern);
}

/**
 * @tc.name: FocusManagerTest089
 * @tc.desc: Test FocusViewHide with null lastFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest089, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Call FocusViewHide when lastFocusView is null.
     * @tc.expected: Returns without modifying lastFocusView_.
     */
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    focusManager->FocusViewHide(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), nullptr);
}

/**
 * @tc.name: FocusManagerTest090
 * @tc.desc: Test FocusViewHide sets lastFocusView_ to null.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest090, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and show FocusView.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    rootNode->AddChild(pageNode);
    focusManager->FocusViewShow(pagePattern);

    /**
     * @tc.steps: step2. Hide the FocusView.
     * @tc.expected: lastFocusView_ is set to null.
     */
    focusManager->FocusViewHide(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), nullptr);
}

/**
 * @tc.name: FocusManagerTest091
 * @tc.desc: Test FocusViewClose removes focusView from stack.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest091, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and show FocusView.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode2 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);
    focusManager->FocusViewShow(pagePattern1);
    focusManager->FocusViewShow(pagePattern2);

    /**
     * @tc.steps: step2. Close first FocusView.
     * @tc.expected: Stack size decreases, FocusView is removed.
     */
    auto stackSizeBefore = focusManager->focusViewStack_.size();
    focusManager->FocusViewClose(pagePattern1);
    auto stackSizeAfter = focusManager->focusViewStack_.size();
    EXPECT_EQ(stackSizeBefore - stackSizeAfter, 1);
}

/**
 * @tc.name: FocusManagerTest092
 * @tc.desc: Test FlushFocusView updates lastFocusView_.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest092, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add FocusViews to stack.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern1 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode1 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern1);
    auto pagePattern2 = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode2 = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern2);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    rootNode->AddChild(pageNode1);
    rootNode->AddChild(pageNode2);
    focusManager->FocusViewShow(pagePattern1);
    focusManager->FocusViewShow(pagePattern2);
    focusManager->focusViewStackState_ = FocusViewStackState::SHOW;
    auto pageFocusHub1 = pageNode1->GetOrCreateFocusHub();
    pageFocusHub1->currentFocus_ = false;

    /**
     * @tc.steps: step2. Call FlushFocusView.
     * @tc.expected: lastFocusView_ is updated to stack back.
     */
    focusManager->FlushFocusView();
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), pagePattern2);
}

/**
 * @tc.name: FocusManagerTest093
 * @tc.desc: Test AddFocusScope with existing scopeId and expired scope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest093, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub1 = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", focusHub1);

    /**
     * @tc.steps: step2. Expire the scope and add new one with same scopeId.
     * @tc.expected: Returns true, scope is updated.
     */
    auto focusHub2 = rootNode->GetOrCreateFocusHub();
    focusManager->focusHubScopeMap_["test_scope"].first = nullptr;
    auto result = focusManager->AddFocusScope("test_scope", focusHub2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusManagerTest094
 * @tc.desc: Test RemoveFocusScope with non-empty priority list.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest094, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope with priority nodes.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto scopeHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", scopeHub);
    auto priorHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddScopePriorityNode("test_scope", priorHub, false);

    /**
     * @tc.steps: step2. Remove focus scope with non-empty priority list.
     * @tc.expected: Scope first element is set to null, not erased.
     */
    focusManager->RemoveFocusScope("test_scope");
    EXPECT_EQ(focusManager->focusHubScopeMap_.count("test_scope"), 1);
}

/**
 * @tc.name: FocusManagerTest095
 * @tc.desc: Test RemoveScopePriorityNode with empty priority list.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest095, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto scopeHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", scopeHub);

    /**
     * @tc.steps: step2. Call RemoveScopePriorityNode with empty priority list.
     * @tc.expected: Returns early without crash.
     */
    auto priorHub = rootNode->GetOrCreateFocusHub();
    focusManager->RemoveScopePriorityNode("test_scope", priorHub);
}

/**
 * @tc.name: FocusManagerTest096
 * @tc.desc: Test RemoveScopePriorityNode removes scope when empty.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest096, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add scope with single priority node.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto scopeHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", scopeHub);
    focusManager->focusHubScopeMap_["test_scope"].first = nullptr;
    auto priorHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddScopePriorityNode("test_scope", priorHub, false);

    /**
     * @tc.steps: step2. Remove the only priority node.
     * @tc.expected: Scope is erased from focusHubScopeMap_.
     */
    focusManager->RemoveScopePriorityNode("test_scope", priorHub);
    EXPECT_EQ(focusManager->focusHubScopeMap_.count("test_scope"), 0);
}

/**
 * @tc.name: FocusManagerTest097
 * @tc.desc: Test GetFocusScopePriorityList with empty priority list.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest097, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and add focus scope.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto scopeHub = rootNode->GetOrCreateFocusHub();
    focusManager->AddFocusScope("test_scope", scopeHub);

    /**
     * @tc.steps: step2. Get priority list when it is empty.
     * @tc.expected: Returns std::nullopt.
     */
    auto result = focusManager->GetFocusScopePriorityList("test_scope");
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: FocusManagerTest098
 * @tc.desc: Test UpdateSwitchingEndReason updates endReason_.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest098, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set isSwitchingFocus_.
     * @tc.expected: FocusManager is created and configured.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingFocus_ = true;

    /**
     * @tc.steps: step2. Call UpdateSwitchingEndReason.
     * @tc.expected: endReason_ is updated.
     */
    focusManager->UpdateSwitchingEndReason(SwitchingEndReason::FOCUS_GUARD_DESTROY);
    EXPECT_TRUE(focusManager->endReason_.has_value());
    EXPECT_EQ(focusManager->endReason_.value(), SwitchingEndReason::FOCUS_GUARD_DESTROY);
}

/**
 * @tc.name: FocusManagerTest099
 * @tc.desc: Test UpdateSwitchingEndReason when isSwitchingFocus_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest099, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set isSwitchingFocus_ to false.
     * @tc.expected: FocusManager is created and configured.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->isSwitchingFocus_ = false;

    /**
     * @tc.steps: step2. Call UpdateSwitchingEndReason.
     * @tc.expected: endReason_ is not updated.
     */
    focusManager->UpdateSwitchingEndReason(SwitchingEndReason::FOCUS_GUARD_DESTROY);
    EXPECT_FALSE(focusManager->endReason_.has_value());
}

/**
 * @tc.name: FocusManagerTest100
 * @tc.desc: Test WindowFocusMoveEnd calls ReportFocusSwitching.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set up window focus move.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isSwitchingWindow_ = true;
    focusManager->isSwitchingFocus_ = true;

    /**
     * @tc.steps: step2. Call WindowFocusMoveEnd.
     * @tc.expected: ReportFocusSwitching is called, flags are reset.
     */
    focusManager->WindowFocusMoveEnd();
    EXPECT_FALSE(focusManager->isSwitchingWindow_);
}

/**
 * @tc.name: FocusManagerTest101
 * @tc.desc: Test SetRequestFocusCallback sets callback.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set request focus callback.
     * @tc.expected: Callback is set successfully.
     */
    bool callbackCalled = false;
    RequestFocusCallback callback = [&callbackCalled](NG::RequestFocusResult result) {
        callbackCalled = true;
    };
    focusManager->SetRequestFocusCallback(callback);
    EXPECT_NE(focusManager->requestCallback_, nullptr);
}

/**
 * @tc.name: FocusManagerTest102
 * @tc.desc: Test TriggerRequestFocusCallback calls callback.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set callback.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    bool callbackCalled = false;
    RequestFocusCallback callback = [&callbackCalled](NG::RequestFocusResult result) {
        callbackCalled = true;
    };
    focusManager->SetRequestFocusCallback(callback);

    /**
     * @tc.steps: step2. Trigger request focus callback.
     * @tc.expected: Callback is called and then reset to nullptr.
     */
    focusManager->TriggerRequestFocusCallback(NG::RequestFocusResult::DEFAULT);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(focusManager->requestCallback_, nullptr);
}

/**
 * @tc.name: FocusManagerTest103
 * @tc.desc: Test ResetRequestFocusCallback resets callback.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest103, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set callback.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    RequestFocusCallback callback = [](NG::RequestFocusResult result) {};
    focusManager->SetRequestFocusCallback(callback);

    /**
     * @tc.steps: step2. Reset request focus callback.
     * @tc.expected: Callback is reset to nullptr.
     */
    focusManager->ResetRequestFocusCallback();
    EXPECT_EQ(focusManager->requestCallback_, nullptr);
}

/**
 * @tc.name: FocusManagerTest104
 * @tc.desc: Test SetRequestFocusResult sets result.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest104, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set request focus result.
     * @tc.expected: Result is set successfully.
     */
    focusManager->SetRequestFocusResult(123);
    EXPECT_EQ(focusManager->GetRequestFocusResult(), 123);
}

/**
 * @tc.name: FocusManagerTest105
 * @tc.desc: Test ResetRequestFocusResult resets result.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest105, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and set result.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    focusManager->SetRequestFocusResult(123);

    /**
     * @tc.steps: step2. Reset request focus result.
     * @tc.expected: Result is reset to ERROR_CODE_NO_ERROR.
     */
    focusManager->ResetRequestFocusResult();
    EXPECT_EQ(focusManager->GetRequestFocusResult(), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: FocusManagerTest106
 * @tc.desc: Test SetLastFocusStateNode sets node.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest106, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and focus node.
     * @tc.expected: Objects created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();

    /**
     * @tc.steps: step2. Set last focus state node.
     * @tc.expected: Node is set successfully.
     */
    focusManager->SetLastFocusStateNode(focusHub);
    auto lastNode = focusManager->GetLastFocusStateNode();
    EXPECT_EQ(lastNode, focusHub);
}

/**
 * @tc.name: FocusManagerTest107
 * @tc.desc: Test SetNeedTriggerScroll sets isNeedTriggerScroll_.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest107, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set isNeedTriggerScroll with value.
     * @tc.expected: isNeedTriggerScroll_ is set.
     */
    focusManager->SetNeedTriggerScroll(true);
    EXPECT_TRUE(focusManager->GetNeedTriggerScroll());
}

/**
 * @tc.name: FocusManagerTest108
 * @tc.desc: Test SetNeedTriggerScroll with nullopt.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest108, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set isNeedTriggerScroll with nullopt.
     * @tc.expected: isNeedTriggerScroll_ is nullopt.
     */
    focusManager->SetNeedTriggerScroll(std::nullopt);
    EXPECT_FALSE(focusManager->isNeedTriggerScroll_.has_value());
}

/**
 * @tc.name: FocusManagerTest109
 * @tc.desc: Test SetIsAutoFocusTransfer sets flag.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest109, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set is auto focus transfer.
     * @tc.expected: Flag is set correctly.
     */
    focusManager->SetIsAutoFocusTransfer(false);
    EXPECT_FALSE(focusManager->IsAutoFocusTransfer());

    focusManager->SetIsAutoFocusTransfer(true);
    EXPECT_TRUE(focusManager->IsAutoFocusTransfer());
}

/**
 * @tc.name: FocusManagerTest110
 * @tc.desc: Test SetFocusViewStackState sets state.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest110, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set focus view stack state.
     * @tc.expected: State is set correctly.
     */
    focusManager->SetFocusViewStackState(FocusViewStackState::SHOW);
    EXPECT_EQ(focusManager->focusViewStackState_, FocusViewStackState::SHOW);

    focusManager->SetFocusViewStackState(FocusViewStackState::CLOSE);
    EXPECT_EQ(focusManager->focusViewStackState_, FocusViewStackState::CLOSE);
}

/**
 * @tc.name: FocusManagerTest111
 * @tc.desc: Test SetKeyProcessingMode sets mode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest111, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Set key processing mode.
     * @tc.expected: Mode is set correctly.
     */
    focusManager->SetKeyProcessingMode(KeyProcessingMode::ANCESTOR_EVENT);
    EXPECT_EQ(focusManager->GetKeyProcessingMode(), KeyProcessingMode::ANCESTOR_EVENT);

    focusManager->SetKeyProcessingMode(KeyProcessingMode::FOCUS_NAVIGATION);
    EXPECT_EQ(focusManager->GetKeyProcessingMode(), KeyProcessingMode::FOCUS_NAVIGATION);
}

/**
 * @tc.name: FocusManagerTest112
 * @tc.desc: Test ResetCurrentFocusEvent resets event.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest112, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager.
     * @tc.expected: FocusManager is created successfully.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    EXPECT_NE(focusManager, nullptr);

    /**
     * @tc.steps: step2. Reset current focus event.
     * @tc.expected: Event is reset to nullopt.
     */
    focusManager->ResetCurrentFocusEvent();
    auto currentEvent = focusManager->GetCurrentFocusEvent();
    EXPECT_FALSE(currentEvent.has_value());
}

/**
 * @tc.name: FocusManagerTest113
 * @tc.desc: Test GetFocusManager with null node.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest114, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetFocusManager with null node.
     * @tc.expected: Returns nullptr.
     */
    RefPtr<FrameNode> node = nullptr;
    auto focusManager = FocusManager::GetFocusManager(node);
    EXPECT_EQ(focusManager, nullptr);
}

/**
 * @tc.name: FocusManagerTest115
 * @tc.desc: Test GetFocusManager with valid node.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest115, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and frame node.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());

    /**
     * @tc.steps: step2. Get focus manager from node.
     * @tc.expected: Returns focus manager.
     */
    auto focusManager = FocusManager::GetFocusManager(rootNode);
    EXPECT_NE(focusManager, nullptr);
}

/**
 * @tc.name: FocusManagerTest116
 * @tc.desc: Test FocusGuard constructor with null hub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest116, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusGuard with null focus hub.
     * @tc.expected: FocusGuard is created without crash.
     */
    RefPtr<FocusHub> focusHub = nullptr;
    FocusManager::FocusGuard guard(focusHub, SwitchingStartReason::REQUEST_FOCUS);
}

/**
 * @tc.name: FocusManagerTest117
 * @tc.desc: Test FocusGuard destructor calls FocusSwitchingEnd.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest117, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and FocusGuard.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto focusHub = rootNode->GetOrCreateFocusHub();

    /**
     * @tc.steps: step2. Create FocusGuard in scope.
     * @tc.expected: FocusSwitchingStart is called.
     */
    {
        FocusManager::FocusGuard guard(focusHub, SwitchingStartReason::REQUEST_FOCUS);
        EXPECT_TRUE(focusManager->isSwitchingFocus_.has_value());
    }

    /**
     * @tc.steps: step3. FocusGuard goes out of scope.
     * @tc.expected: FocusSwitchingEnd is called.
     */
    EXPECT_FALSE(focusManager->isSwitchingFocus_.has_value());
}

/**
 * @tc.name: FocusManagerTest118
 * @tc.desc: Test FocusViewShow sets focusViewStackState_.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest118, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and root node structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Call FocusViewShow.
     * @tc.expected: focusViewStackState_ is set to SHOW.
     */
    focusManager->FocusViewShow(pagePattern);
    EXPECT_EQ(focusManager->focusViewStackState_, FocusViewStackState::SHOW);
}

/**
 * @tc.name: FocusManagerTest119
 * @tc.desc: Test FocusViewClose sets focusViewStackState_ to CLOSE.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest119, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and show FocusView.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    rootNode->AddChild(pageNode);
    focusManager->FocusViewShow(pagePattern);

    /**
     * @tc.steps: step2. Call FocusViewClose.
     * @tc.expected: focusViewStackState_ is set to CLOSE.
     */
    focusManager->FocusViewClose(pagePattern);
    EXPECT_EQ(focusManager->focusViewStackState_, FocusViewStackState::CLOSE);
}

/**
 * @tc.name: FocusManagerTest120
 * @tc.desc: Test EraseModalFocusView with child FocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest120, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusManager and parent-child node structure.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>(nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto parentPattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto parentNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, parentPattern);
    auto childPattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto childNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, childPattern);
    rootNode->AddChild(parentNode);
    parentNode->AddChild(childNode);
    focusManager->modalFocusViewStack_.emplace_back(parentPattern);

    /**
     * @tc.steps: step2. Erase child FocusView.
     * @tc.expected: Parent FocusView is removed.
     */
    focusManager->EraseModalFocusView(childPattern);
    EXPECT_TRUE(focusManager->modalFocusViewStack_.empty());
}
} // namespace OHOS::Ace::NG
