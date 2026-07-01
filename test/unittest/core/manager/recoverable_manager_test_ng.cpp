/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <functional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/manager/recoverable/recoverable_manager.h"
#include "core/components_ng/manager/recoverable/recoverable_view.h"
#include "core/components_ng/manager/recoverable/recoverable_declaration.h"

#include "base/json/json_util.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PAGE_ID_1 = 100;
constexpr int32_t PAGE_ID_2 = 200;
const std::string COMPONENT_ID_TABS = "Tabs-0";
const std::string COMPONENT_ID_NAV = "Navigation-1";
const std::string NAVIGATION_ID = "nav_main";
const std::string HOME_INFO = "{\"homeIndex\":3}";
} // namespace

class RecoverableManagerTestNg : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
        manager_ = AceType::MakeRefPtr<RecoverableManager>();
    }
    void TearDown() override
    {
        manager_ = nullptr;
        MockPipelineContext::TearDown();
    }
    RefPtr<RecoverableManager> manager_;
};

/**
 * @tc.name: AddRestoreComponentRouterTypeTest
 * @tc.desc: Add restore component with router type (isNavigationType=false)
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, AddRestoreComponentRouterTypeTest, TestSize.Level1)
{
    auto saveCallback = []() -> std::string {
        auto info = JsonUtil::Create();
        info->Put("index", 0);
        return info->ToString();
    };

    int32_t callbackId = manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback));

    EXPECT_NE(callbackId, -1);
    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) != manager_->routerRestoreInfos_.end());
    EXPECT_TRUE(manager_->navigationRestoreInfos_.find(PAGE_ID_1) == manager_->navigationRestoreInfos_.end());
}

/**
 * @tc.name: AddRestoreComponentNavigationTypeTest
 * @tc.desc: Add restore component with navigation type (isNavigationType=true)
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, AddRestoreComponentNavigationTypeTest, TestSize.Level1)
{
    auto saveCallback = []() -> std::string {
        auto info = JsonUtil::Create();
        info->Put("index", 2);
        return info->ToString();
    };

    int32_t callbackId = manager_->AddRestoreComponent(true, PAGE_ID_1, COMPONENT_ID_NAV, std::move(saveCallback));

    EXPECT_NE(callbackId, -1);
    EXPECT_TRUE(manager_->navigationRestoreInfos_.find(PAGE_ID_1) != manager_->navigationRestoreInfos_.end());
    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) == manager_->routerRestoreInfos_.end());
}

/**
 * @tc.name: AddRestoreComponentIncrementalIdTest
 * @tc.desc: Each AddRestoreComponent should return incremental callbackId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, AddRestoreComponentIncrementalIdTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return ""; };
    auto saveCallback2 = []() -> std::string { return ""; };
    auto saveCallback3 = []() -> std::string { return ""; };

    int32_t id1 = manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback1));
    int32_t id2 = manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_NAV, std::move(saveCallback2));
    int32_t id3 = manager_->AddRestoreComponent(true, PAGE_ID_2, COMPONENT_ID_NAV, std::move(saveCallback3));

    EXPECT_NE(id1, id2);
    EXPECT_NE(id2, id3);
    EXPECT_EQ(id2, id1 + 1);
    EXPECT_EQ(id3, id2 + 1);
}

/**
 * @tc.name: AddRestoreComponentMultiplePerPageTest
 * @tc.desc: Multiple components can be registered under the same pageId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, AddRestoreComponentMultiplePerPageTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return "{\"index\":0}"; };
    auto saveCallback2 = []() -> std::string { return "{\"index\":1}"; };

    int32_t id1 = manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-0", std::move(saveCallback1));
    int32_t id2 = manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-1", std::move(saveCallback2));

    EXPECT_NE(id1, -1);
    EXPECT_NE(id2, -1);

    auto& pageInfos = manager_->routerRestoreInfos_[PAGE_ID_1];
    EXPECT_EQ(static_cast<int32_t>(pageInfos.size()), 2);
}

/**
 * @tc.name: RemoveRestoreComponentExistingTest
 * @tc.desc: RemoveRestoreComponent should remove existing entry by callbackId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, RemoveRestoreComponentExistingTest, TestSize.Level1)
{
    auto saveCallback = []() -> std::string { return ""; };
    int32_t callbackId = manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback));

    manager_->RemoveRestoreComponent(false, PAGE_ID_1, callbackId);

    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) == manager_->routerRestoreInfos_.end());
}

/**
 * @tc.name: RemoveRestoreComponentPartialTest
 * @tc.desc: RemoveRestoreComponent should only remove the specified callback, keep others in same page
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, RemoveRestoreComponentPartialTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return ""; };
    auto saveCallback2 = []() -> std::string { return ""; };

    int32_t id1 = manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-0", std::move(saveCallback1));
    int32_t id2 = manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-1", std::move(saveCallback2));

    manager_->RemoveRestoreComponent(false, PAGE_ID_1, id1);

    auto& pageInfos = manager_->routerRestoreInfos_[PAGE_ID_1];
    EXPECT_EQ(static_cast<int32_t>(pageInfos.size()), 1);
    EXPECT_TRUE(pageInfos.find(id2) != pageInfos.end());
}

/**
 * @tc.name: RemoveRestoreComponentNonExistingPageTest
 * @tc.desc: RemoveRestoreComponent should do nothing when pageId not found
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, RemoveRestoreComponentNonExistingPageTest, TestSize.Level1)
{
    manager_->RemoveRestoreComponent(false, PAGE_ID_1, 0);

    EXPECT_TRUE(manager_->routerRestoreInfos_.empty());
}

/**
 * @tc.name: RemoveRestoreComponentNonExistingCallbackTest
 * @tc.desc: RemoveRestoreComponent should do nothing when callbackId not found in page
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, RemoveRestoreComponentNonExistingCallbackTest, TestSize.Level1)
{
    auto saveCallback = []() -> std::string { return ""; };
    int32_t callbackId = manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback));

    manager_->RemoveRestoreComponent(false, PAGE_ID_1, callbackId + 100);

    auto& pageInfos = manager_->routerRestoreInfos_[PAGE_ID_1];
    EXPECT_EQ(static_cast<int32_t>(pageInfos.size()), 1);
}

/**
 * @tc.name: GetRestoreByPageValidTest
 * @tc.desc: GetRestoreByPage should return JSON array with component restore info
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, GetRestoreByPageValidTest, TestSize.Level1)
{
    auto saveCallback = []() -> std::string {
        auto info = JsonUtil::Create();
        info->Put("index", 2);
        return info->ToString();
    };
    manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback));

    std::string result;
    bool ret = manager_->GetRestoreByPage(false, PAGE_ID_1, result);

    EXPECT_TRUE(ret);
    EXPECT_FALSE(result.empty());
}

/**
 * @tc.name: GetRestoreByPageEmptyPageTest
 * @tc.desc: GetRestoreByPage should return false when pageId not found
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, GetRestoreByPageEmptyPageTest, TestSize.Level1)
{
    std::string result;
    bool ret = manager_->GetRestoreByPage(false, PAGE_ID_1, result);

    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetRestoreByPageMultipleComponentsTest
 * @tc.desc: GetRestoreByPage should include all components under the same page
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, GetRestoreByPageMultipleComponentsTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return "{\"index\":0}"; };
    auto saveCallback2 = []() -> std::string { return "{\"index\":2}"; };

    manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-0", std::move(saveCallback1));
    manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-1", std::move(saveCallback2));

    std::string result;
    bool ret = manager_->GetRestoreByPage(false, PAGE_ID_1, result);

    EXPECT_TRUE(ret);
    EXPECT_FALSE(result.empty());

    auto arr = JsonUtil::ParseJsonString(result);
    EXPECT_NE(arr, nullptr);
    EXPECT_EQ(arr->GetArraySize(), 2);
}

/**
 * @tc.name: RemoveRestoreByPageExistingTest
 * @tc.desc: RemoveRestoreByPage should remove all components for a pageId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, RemoveRestoreByPageExistingTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return ""; };
    auto saveCallback2 = []() -> std::string { return ""; };

    manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-0", std::move(saveCallback1));
    manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-1", std::move(saveCallback2));

    manager_->RemoveRestoreByPage(false, PAGE_ID_1);

    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) == manager_->routerRestoreInfos_.end());

    std::string result;
    EXPECT_FALSE(manager_->GetRestoreByPage(false, PAGE_ID_1, result));
}

/**
 * @tc.name: RemoveRestoreByPageNonExistingTest
 * @tc.desc: RemoveRestoreByPage should do nothing when pageId not found
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, RemoveRestoreByPageNonExistingTest, TestSize.Level1)
{
    manager_->RemoveRestoreByPage(false, PAGE_ID_1);

    EXPECT_TRUE(manager_->routerRestoreInfos_.empty());
}

/**
 * @tc.name: GetRestoreInfoTypeRoutingTest
 * @tc.desc: isNavigationType=false should store in routerRestoreInfos
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, GetRestoreInfoTypeRoutingTest, TestSize.Level1)
{
    auto saveCallback = []() -> std::string { return ""; };
    manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback));

    auto& routerInfos = manager_->routerRestoreInfos_;
    auto& navInfos = manager_->navigationRestoreInfos_;

    EXPECT_TRUE(routerInfos.find(PAGE_ID_1) != routerInfos.end());
    EXPECT_TRUE(navInfos.empty());
}

/**
 * @tc.name: GetRestoreInfoTypeNavigationTest
 * @tc.desc: isNavigationType=true should store in navigationRestoreInfos
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, GetRestoreInfoTypeNavigationTest, TestSize.Level1)
{
    auto saveCallback = []() -> std::string { return ""; };
    manager_->AddRestoreComponent(true, PAGE_ID_1, COMPONENT_ID_NAV, std::move(saveCallback));

    auto& routerInfos = manager_->routerRestoreInfos_;
    auto& navInfos = manager_->navigationRestoreInfos_;

    EXPECT_TRUE(navInfos.find(PAGE_ID_1) != navInfos.end());
    EXPECT_TRUE(routerInfos.empty());
}

/**
 * @tc.name: SetNavigationHomeInfoTest
 * @tc.desc: SetNavigationHomeInfo should store home info by navigationId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, SetNavigationHomeInfoTest, TestSize.Level1)
{
    manager_->SetNavigationHomeInfo(NAVIGATION_ID, HOME_INFO);

    EXPECT_EQ(manager_->homeNavigationInfo_[NAVIGATION_ID], HOME_INFO);
}

/**
 * @tc.name: GetNavigationHomeInfoExistingTest
 * @tc.desc: GetNavigationHomeInfo should return stored info for existing navigationId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, GetNavigationHomeInfoExistingTest, TestSize.Level1)
{
    manager_->SetNavigationHomeInfo(NAVIGATION_ID, HOME_INFO);

    std::string result = manager_->GetNavigationHomeInfo(NAVIGATION_ID);
    EXPECT_EQ(result, HOME_INFO);
}

/**
 * @tc.name: GetNavigationHomeInfoNonExistingTest
 * @tc.desc: GetNavigationHomeInfo should return empty string for non-existing navigationId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, GetNavigationHomeInfoNonExistingTest, TestSize.Level1)
{
    std::string result = manager_->GetNavigationHomeInfo("nonexistent");
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: SetNavigationHomeInfoOverwriteTest
 * @tc.desc: SetNavigationHomeInfo should overwrite existing entry
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, SetNavigationHomeInfoOverwriteTest, TestSize.Level1)
{
    manager_->SetNavigationHomeInfo(NAVIGATION_ID, HOME_INFO);
    std::string newHomeInfo = "{\"homeIndex\":5}";
    manager_->SetNavigationHomeInfo(NAVIGATION_ID, newHomeInfo);

    std::string result = manager_->GetNavigationHomeInfo(NAVIGATION_ID);
    EXPECT_EQ(result, newHomeInfo);
}

/**
 * @tc.name: MultiplePagesIndependentTest
 * @tc.desc: Components in different pages should be stored independently
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, MultiplePagesIndependentTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return "{\"index\":0}"; };
    auto saveCallback2 = []() -> std::string { return "{\"index\":2}"; };

    manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-0", std::move(saveCallback1));
    manager_->AddRestoreComponent(false, PAGE_ID_2, "Tabs-1", std::move(saveCallback2));

    EXPECT_EQ(static_cast<int32_t>(manager_->routerRestoreInfos_.size()), 2);

    manager_->RemoveRestoreByPage(false, PAGE_ID_1);

    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) == manager_->routerRestoreInfos_.end());
    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_2) != manager_->routerRestoreInfos_.end());

    std::string result;
    EXPECT_FALSE(manager_->GetRestoreByPage(false, PAGE_ID_1, result));
    EXPECT_TRUE(manager_->GetRestoreByPage(false, PAGE_ID_2, result));
}

/**
 * @tc.name: MixedNavigationAndRouterTypesTest
 * @tc.desc: Both navigation and router type entries should be stored independently
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, MixedNavigationAndRouterTypesTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return "{\"index\":0}"; };
    auto saveCallback2 = []() -> std::string { return "{\"index\":2}"; };

    manager_->AddRestoreComponent(false, PAGE_ID_1, "Tabs-0", std::move(saveCallback1));
    manager_->AddRestoreComponent(true, PAGE_ID_1, "Nav-0", std::move(saveCallback2));

    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) != manager_->routerRestoreInfos_.end());
    EXPECT_TRUE(manager_->navigationRestoreInfos_.find(PAGE_ID_1) != manager_->navigationRestoreInfos_.end());

    manager_->RemoveRestoreByPage(false, PAGE_ID_1);

    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) == manager_->routerRestoreInfos_.end());
    EXPECT_TRUE(manager_->navigationRestoreInfos_.find(PAGE_ID_1) != manager_->navigationRestoreInfos_.end());
}

class RecoverableViewTestNg : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
    }
    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: RecoverableViewOnSaveDataDefaultTest
 * @tc.desc: Default RecoverableView::OnSaveData should return false
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableViewTestNg, RecoverableViewOnSaveDataDefaultTest, TestSize.Level1)
{
    auto view = AceType::MakeRefPtr<RecoverableView>();
    ASSERT_NE(view, nullptr);

    std::string data;
    bool result = view->OnSaveData(data);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: RecoverableViewGetRestoreInfoNotRegisteredTest
 * @tc.desc: GetRestoreInfo should return false when pageId and callbackId are -1
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableViewTestNg, RecoverableViewGetRestoreInfoNotRegisteredTest, TestSize.Level1)
{
    auto view = AceType::MakeRefPtr<RecoverableView>();
    ASSERT_NE(view, nullptr);

    std::string result;
    EXPECT_FALSE(view->GetRestoreInfo(result));
}

/**
 * @tc.name: RecoverableViewUnregisterRecoverableNotRegisteredTest
 * @tc.desc: UnregisterRecoverable should do nothing when pageId or callbackId is -1
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableViewTestNg, RecoverableViewUnregisterRecoverableNotRegisteredTest, TestSize.Level1)
{
    auto view = AceType::MakeRefPtr<RecoverableView>();
    ASSERT_NE(view, nullptr);

    view->pageId_ = -1;
    view->callbackId_ = -1;

    view->UnregisterRecoverable();
}

/**
 * @tc.name: RecoverableViewSetHostNodeTest
 * @tc.desc: SetRecoverableViewHostNode should store weak reference to host
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableViewTestNg, RecoverableViewSetHostNodeTest, TestSize.Level1)
{
    auto view = AceType::MakeRefPtr<RecoverableView>();
    ASSERT_NE(view, nullptr);

    auto host = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(host, nullptr);

    view->SetRecoverableViewHostNode(host);

    auto upgraded = view->hostNode_.Upgrade();
    EXPECT_NE(upgraded, nullptr);
    EXPECT_EQ(upgraded->GetId(), host->GetId());
}

/**
 * @tc.name: RecoverableViewGenerateGlobalComponentIdNoCustomIdTest
 * @tc.desc: GenerateGlobalComponentId without customId should use only tag
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableViewTestNg, RecoverableViewGenerateGlobalComponentIdNoCustomIdTest, TestSize.Level1)
{
    auto view = AceType::MakeRefPtr<RecoverableView>();
    ASSERT_NE(view, nullptr);

    auto host = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(host, nullptr);

    view->SetRecoverableViewHostNode(host);
    view->GenerateGlobalComponentId();

    EXPECT_FALSE(view->globalComponentId_.empty());
    EXPECT_TRUE(view->globalComponentId_.find(V2::TEXT_ETS_TAG) != std::string::npos);
}

/**
 * @tc.name: RecoverableViewGenerateGlobalComponentIdWithCustomIdTest
 * @tc.desc: GenerateGlobalComponentId with customId should append customId to tag
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableViewTestNg, RecoverableViewGenerateGlobalComponentIdWithCustomIdTest, TestSize.Level1)
{
    auto view = AceType::MakeRefPtr<RecoverableView>();
    ASSERT_NE(view, nullptr);

    auto host = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(host, nullptr);

    view->SetRecoverableViewHostNode(host);
    view->GenerateGlobalComponentId("custom123");

    EXPECT_FALSE(view->globalComponentId_.empty());
    EXPECT_TRUE(view->globalComponentId_.find("custom123") != std::string::npos);
    EXPECT_TRUE(view->globalComponentId_.find(V2::TEXT_ETS_TAG) != std::string::npos);
}

/**
 * @tc.name: RecoverableViewGenerateGlobalComponentIdNullHostTest
 * @tc.desc: GenerateGlobalComponentId should do nothing when hostNode is null
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableViewTestNg, RecoverableViewGenerateGlobalComponentIdNullHostTest, TestSize.Level1)
{
    auto view = AceType::MakeRefPtr<RecoverableView>();
    ASSERT_NE(view, nullptr);

    view->GenerateGlobalComponentId("custom");

    EXPECT_TRUE(view->globalComponentId_.empty());
}

/**
 * @tc.name: RestoreInfoStructTest
 * @tc.desc: RestoreInfo struct should store componentId, saveCallback, and callbackId
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, RestoreInfoStructTest, TestSize.Level1)
{
    RestoreInfo info;
    info.componentId = "Tabs-0";
    info.callbackId = 42;
    info.saveCallback = []() -> std::string { return "{\"index\":0}"; };

    EXPECT_EQ(info.componentId, "Tabs-0");
    EXPECT_EQ(info.callbackId, 42);
    EXPECT_TRUE(info.saveCallback);
    EXPECT_EQ(info.saveCallback(), "{\"index\":0}");
}

/**
 * @tc.name: AddThenRemoveThenAddSamePageTest
 * @tc.desc: After removing all entries for a page, adding again should work correctly
 * @tc.type: FUNC
 */
HWTEST_F(RecoverableManagerTestNg, AddThenRemoveThenAddSamePageTest, TestSize.Level1)
{
    auto saveCallback1 = []() -> std::string { return "{\"index\":0}"; };
    int32_t id1 = manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback1));
    EXPECT_NE(id1, -1);

    manager_->RemoveRestoreByPage(false, PAGE_ID_1);
    EXPECT_TRUE(manager_->routerRestoreInfos_.find(PAGE_ID_1) == manager_->routerRestoreInfos_.end());

    auto saveCallback2 = []() -> std::string { return "{\"index\":2}"; };
    int32_t id2 = manager_->AddRestoreComponent(false, PAGE_ID_1, COMPONENT_ID_TABS, std::move(saveCallback2));
    EXPECT_NE(id2, -1);

    std::string result;
    EXPECT_TRUE(manager_->GetRestoreByPage(false, PAGE_ID_1, result));
}
} // namespace OHOS::Ace::NG
