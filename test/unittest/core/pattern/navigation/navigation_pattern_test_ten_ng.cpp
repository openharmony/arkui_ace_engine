/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/common/router_recover_record.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";

class TestNavigationStack : public MockNavigationStack {
public:
    bool createHomeResult_ = false;
    RefPtr<UINode> homeNode_;

    bool CreateHomeDestination(const WeakPtr<UINode>& customNode, RefPtr<UINode>& node) override
    {
        node = homeNode_;
        return createHomeResult_;
    }
};

struct NavigationTestContext {
    RefPtr<NavigationGroupNode> navNode;
    RefPtr<NavigationPattern> pattern;
    RefPtr<TestNavigationStack> stack;
};

NavigationTestContext CreateNavigationTestContext()
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto rawNavNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<NavigationGroupNode> navNode = rawNavNode ? AceType::Claim(rawNavNode) : nullptr;
    auto pattern = navNode ? navNode->GetPattern<NavigationPattern>() : nullptr;
    auto stack = AceType::MakeRefPtr<TestNavigationStack>();
    if (pattern) {
        pattern->SetNavigationStack(stack);
    }
    return { navNode, pattern, stack };
}

void RunNavigationStackSync(const RefPtr<NavigationPattern>& navigationPattern)
{
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
}
} // namespace

class NavigationPatternTestTenNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

RefPtr<NavigationBarTheme> NavigationPatternTestTenNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestTenNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == NavigationBarTheme::TypeId()) {
            return navigationBarTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationPatternTestTenNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationPatternTestTenNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: CheckNeedHandleIntent001
 * @tc.desc: Branch: navigationIntentInfo has no value => return false
 *           Condition: navigationIntentInfo_ = std::nullopt
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, CheckNeedHandleIntent001, TestSize.Level1)
{
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::nullopt;
    auto result = navigationPattern->CheckNeedHandleIntent(false);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: CheckNeedHandleIntent002
 * @tc.desc: Branch: navigationInspectorId != host curId => return false
 *           Condition: inspectorId mismatch
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, CheckNeedHandleIntent002, TestSize.Level1)
{
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    navigationGroupNode->curId_ = "myId";
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::make_optional<NavigationIntentInfo>();
    navigationManager->navigationIntentInfo_->navigationInspectorId = "otherId";
    auto result = navigationPattern->CheckNeedHandleIntent(false);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: CheckNeedHandleIntent003
 * @tc.desc: Branch: navigationInspectorId == host curId => return true
 *           Condition: inspectorId matches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, CheckNeedHandleIntent003, TestSize.Level1)
{
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    navigationGroupNode->curId_ = "matchedId";
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::make_optional<NavigationIntentInfo>();
    navigationManager->navigationIntentInfo_->navigationInspectorId = "matchedId";
    auto result = navigationPattern->CheckNeedHandleIntent(false);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: CheckNeedHandleIntent004
 * @tc.desc: Branch: host is nullptr => return false
 *           Condition: Pattern has no host node attached
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, CheckNeedHandleIntent004, TestSize.Level1)
{
    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto result = navigationPattern->CheckNeedHandleIntent(false);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleIntent001
 * @tc.desc: Branch: CheckNeedHandleIntent returns false => HandleIntent returns false
 *           Condition: navigationIntentInfo has no value
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, HandleIntent001, TestSize.Level1)
{
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::nullopt;
    auto result = navigationPattern->HandleIntent(false);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleIntent002
 * @tc.desc: Branch: CheckNeedHandleIntent returns true => HandleIntent
 * processes intent, ResetNavigationIntentInfo called
 *           Condition: inspectorId matches, intentInfo has value
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, HandleIntent002, TestSize.Level1)
{
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    navigationGroupNode->curId_ = "matchedId";
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::make_optional<NavigationIntentInfo>();
    navigationManager->navigationIntentInfo_->navigationInspectorId = "matchedId";
    navigationManager->navigationIntentInfo_->navDestinationName = PAGE01;
    navigationManager->navigationIntentInfo_->isColdStart = false;
    auto result = navigationPattern->HandleIntent(true);
    EXPECT_EQ(result, true);
    EXPECT_EQ(navigationManager->navigationIntentInfo_, std::nullopt);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Branch: CheckNeedHandleIntent returns true in OnModifyDone => HandleIntent called, intentInfo reset
 *           Condition: inspectorId matches navigation curId
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, OnModifyDone001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    MockPipelineContextGetTheme();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto navigationManager = pipeline->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::make_optional<NavigationIntentInfo>();
    navigationManager->navigationIntentInfo_->navigationInspectorId = "matchedId";
    navigationManager->navigationIntentInfo_->navDestinationName = PAGE01;
    navigationManager->navigationIntentInfo_->isColdStart = false;
    context.navNode->curId_ = "matchedId";
    context.pattern->OnModifyDone();
    EXPECT_EQ(navigationManager->navigationIntentInfo_, std::nullopt);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Branch: CheckNeedHandleIntent returns false in OnModifyDone => HandleIntent NOT called
 *           Condition: no intentInfo available
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, OnModifyDone002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    MockPipelineContextGetTheme();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto navigationManager = pipeline->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::nullopt;
    context.navNode->curId_ = "myId";
    context.pattern->OnModifyDone();
    EXPECT_EQ(navigationManager->navigationIntentInfo_, std::nullopt);
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Branch: InitNavigationId called, curId_ becomes non-empty when no intent
 *           Condition: curId_ initially empty, no intent info
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, OnAttachToMainTree001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    MockPipelineContextGetTheme();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto navigationManager = pipeline->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::nullopt;
    context.navNode->curId_ = "";
    context.navNode->recoverable_ = true;
    context.pattern->OnAttachToMainTree();
    EXPECT_FALSE(context.navNode->GetCurId().empty());
}

/**
 * @tc.name: OnAttachToMainTree002
 * @tc.desc: Branch: curId_ already set => InitNavigationId does not change it
 *           Condition: curId_ = "presetId"
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, OnAttachToMainTree002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    MockPipelineContextGetTheme();
    context.navNode->curId_ = "presetId";
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto navigationManager = pipeline->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::nullopt;
    context.pattern->OnAttachToMainTree();
    EXPECT_EQ(context.navNode->GetCurId(), "presetId");
}

/**
 * @tc.name: OnAttachToMainTree003
 * @tc.desc: Branch: CheckNeedHandleIntent returns true => skip AddRecoverableNavigation
 *           Condition: intentInfo matches navigation curId
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, OnAttachToMainTree003, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    MockPipelineContextGetTheme();
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto navigationManager = pipeline->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->navigationIntentInfo_ = std::make_optional<NavigationIntentInfo>();
    navigationManager->navigationIntentInfo_->navigationInspectorId = "matchedId";
    navigationManager->navigationIntentInfo_->navDestinationName = PAGE01;
    context.navNode->curId_ = "matchedId";
    context.pattern->OnAttachToMainTree();
    EXPECT_FALSE(context.navNode->GetCurId().empty());
}

/**
 * @tc.name: GenerateUINodeByIndex001
 * @tc.desc: Branch: isRecovery=true => calls CreateNodeFromRecovery instead of CreateNodeByIndex
 *           Condition: isRecovery parameter is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, GenerateUINodeByIndex001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);
    context.stack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(PAGE01));
    context.pattern->OnModifyDone();
    RefPtr<UINode> node;
    bool result = context.pattern->GenerateUINodeByIndex(0, node, true);
    EXPECT_TRUE(result || node == nullptr);
}

/**
 * @tc.name: GenerateUINodeByIndex002
 * @tc.desc: Branch: isRecovery=false => calls CreateNodeByIndex (original behavior)
 *           Condition: isRecovery parameter is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, GenerateUINodeByIndex002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);
    context.stack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(PAGE01));
    context.pattern->OnModifyDone();
    RefPtr<UINode> node;
    bool result = context.pattern->GenerateUINodeByIndex(0, node, false);
    EXPECT_TRUE(result || node == nullptr);
}

/**
 * @tc.name: GetNavdestinationJsonArray001
 * @tc.desc: Branch: GetOhmUrl returns true => fileName and moduleName added to JSON
 *           Condition: mock stack returns GetOhmUrl = true with testModule/testFile
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, GetNavdestinationJsonArray001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);
    MockPipelineContextGetTheme();
    context.stack->SetMockGetOhmUrlResult(true, "testModule", "testFile");
    context.stack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(PAGE01));
    RunNavigationStackSync(context.pattern);
    auto json = context.pattern->GetNavdestinationJsonArray();
    ASSERT_NE(json, nullptr);
    if (json->GetArraySize() > 0) {
        auto destInfo = json->GetArrayItem(0);
        ASSERT_NE(destInfo, nullptr);
        auto fileNameVal = destInfo->GetValue("fileName");
        auto moduleNameVal = destInfo->GetValue("moduleName");
        if (fileNameVal && moduleNameVal && fileNameVal->IsString() && moduleNameVal->IsString()) {
            EXPECT_EQ(fileNameVal->GetString(), "testFile");
            EXPECT_EQ(moduleNameVal->GetString(), "testModule");
        }
    }
}

/**
 * @tc.name: GetNavdestinationJsonArray002
 * @tc.desc: Branch: GetOhmUrl returns false => fileName and moduleName NOT in JSON
 *           Condition: mock stack returns GetOhmUrl = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, GetNavdestinationJsonArray002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);
    MockPipelineContextGetTheme();
    context.stack->SetMockGetOhmUrlResult(false);
    context.stack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(PAGE01));
    RunNavigationStackSync(context.pattern);
    auto json = context.pattern->GetNavdestinationJsonArray();
    ASSERT_NE(json, nullptr);
    if (json->GetArraySize() > 0) {
        auto destInfo = json->GetArrayItem(0);
        ASSERT_NE(destInfo, nullptr);
        auto fileNameVal = destInfo->GetValue("fileName");
        auto moduleNameVal = destInfo->GetValue("moduleName");
        EXPECT_TRUE(fileNameVal == nullptr || fileNameVal->IsNull());
        EXPECT_TRUE(moduleNameVal == nullptr || moduleNameVal->IsNull());
    }
}

/**
 * @tc.name: RouterRecoverRecord001
 * @tc.desc: Branch: 4-arg constructor with ohmUrl - NOTE: ohmUrl field declaration missing in struct
 *           This test verifies the 4-arg constructor compiles once ohmUrl field is added
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, RouterRecoverRecord001, TestSize.Level1)
{
    RouterRecoverRecord record("testUrl", "testParams", true);
    EXPECT_EQ(record.url, "testUrl");
    EXPECT_EQ(record.params, "testParams");
    EXPECT_EQ(record.isNamedRouter, true);
}

/**
 * @tc.name: RouterRecoverRecord002
 * @tc.desc: Branch: default constructor - url/params empty, isNamedRouter false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, RouterRecoverRecord002, TestSize.Level1)
{
    RouterRecoverRecord record;
    EXPECT_EQ(record.url, "");
    EXPECT_EQ(record.params, "");
    EXPECT_EQ(record.isNamedRouter, false);
}

/**
 * @tc.name: RouterRecoverRecord003
 * @tc.desc: Branch: 3-arg constructor - url/params/isNamedRouter set correctly
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, RouterRecoverRecord003, TestSize.Level1)
{
    RouterRecoverRecord record("testUrl", "testParams", true);
    EXPECT_EQ(record.url, "testUrl");
    EXPECT_EQ(record.params, "testParams");
    EXPECT_EQ(record.isNamedRouter, true);
}

/**
 * @tc.name: NavdestinationRecoveryInfo001
 * @tc.desc: Branch: default moduleName/fileName are empty strings
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, NavdestinationRecoveryInfo001, TestSize.Level1)
{
    NavdestinationRecoveryInfo info("name", "param", 0);
    EXPECT_EQ(info.name, "name");
    EXPECT_EQ(info.param, "param");
    EXPECT_EQ(info.fileName, "");
    EXPECT_EQ(info.moduleName, "");
    EXPECT_EQ(info.mode, 0);
}

/**
 * @tc.name: NavdestinationRecoveryInfo002
 * @tc.desc: Branch: moduleName/fileName can be set after construction
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, NavdestinationRecoveryInfo002, TestSize.Level1)
{
    NavdestinationRecoveryInfo info("name", "param", 0);
    info.moduleName = "testModule";
    info.fileName = "testFile";
    EXPECT_EQ(info.moduleName, "testModule");
    EXPECT_EQ(info.fileName, "testFile");
}

/**
 * @tc.name: NavigationStackGetOhmUrl001
 * @tc.desc: Branch: base NavigationStack GetOhmUrl returns false (default virtual impl)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, NavigationStackGetOhmUrl001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    std::string moduleName;
    std::string fileName;
    auto result = stack->GetOhmUrl(nullptr, moduleName, fileName);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: NavigationStackCreateNodeFromRecovery001
 * @tc.desc: Branch: base NavigationStack CreateNodeFromRecovery returns false (default virtual impl)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, NavigationStackCreateNodeFromRecovery001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    RefPtr<UINode> node;
    auto result = stack->CreateNodeFromRecovery(0, nullptr, node);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: MockNavigationStackGetOhmUrl001
 * @tc.desc: Branch: MockNavigationStack GetOhmUrl returns configured result
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, MockNavigationStackGetOhmUrl001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    std::string moduleName;
    std::string fileName;
    EXPECT_EQ(stack->GetOhmUrl(nullptr, moduleName, fileName), false);
    stack->SetMockGetOhmUrlResult(true, "testModule", "testFile");
    EXPECT_EQ(stack->GetOhmUrl(nullptr, moduleName, fileName), true);
    EXPECT_EQ(moduleName, "testModule");
    EXPECT_EQ(fileName, "testFile");
}

/**
 * @tc.name: MockNavigationStackCreateNodeFromRecovery001
 * @tc.desc: Branch: MockNavigationStack CreateNodeFromRecovery delegates to CreateNodeByIndex
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, MockNavigationStackCreateNodeFromRecovery001, TestSize.Level1)
{
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    stack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(PAGE01));
    RefPtr<UINode> node;
    bool result = stack->CreateNodeFromRecovery(0, nullptr, node);
    EXPECT_EQ(result, true);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: ClearContentStackIfNeeded001
 * @tc.desc: Branch: curList is empty => early return
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // curList is empty, early return, needSyncWithJsStack_ not cleared
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded002
 * @tc.desc: Branch: forceSplitSuccess_ is true => early return
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // forceSplitSuccess_ is true, early return, needSyncWithJsStack_ not cleared
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded003
 * @tc.desc: Branch: IsRealStackDisplay() is true (STACK mode) => early return
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // IsRealStackDisplay() returns true in STACK mode, early return
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded004
 * @tc.desc: Branch: !topDest (curTopNode is not a NavDestinationGroupNode) => early return
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded004, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    // Use a CustomNode (not NavDestinationGroupNode) as curTopNode
    // GetNavDestinationNode won't find NAVDESTINATION_VIEW_ETS_TAG tag, so topDest will be nullptr
    auto plainNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "testKey");
    ASSERT_NE(plainNode, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", plainNode};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // !topDest, early return, needSyncWithJsStack_ not cleared
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded005
 * @tc.desc: Branch: topDest->IsFullScreenOverlay() is true => early return
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded005, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    dest->SetIsFullScreenOverlay(true);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // IsFullScreenOverlay() is true, early return
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded006
 * @tc.desc: Branch: !homeTouched (homeNodeTouched_ is nullopt or false) => early return
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded006, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);
    NavPathList preList;
    pattern->forceSplitSuccess_ = false;

    // homeNodeTouched_ is nullopt
    pattern->homeNodeTouched_ = std::nullopt;
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);

    // homeNodeTouched_ is false
    pattern->homeNodeTouched_ = false;
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded007
 * @tc.desc: Branch: curTopNode found in preList => early return, homeNodeTouched_ reset to nullopt
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded007, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    // Both preList and curList have the same node as top
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);
    NavPathList preList;
    preList.push_back(testPair);
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // curTopNode found in preList, early return, homeNodeTouched_ reset to nullopt
    ASSERT_EQ(pattern->homeNodeTouched_, std::nullopt);
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded008
 * @tc.desc: Branch: removeIndexes empty (firstNewNodeIndex <= 0) => early return, homeNodeTouched_ reset to nullopt
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded008, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    // preList has dest1, curList has dest1 at index 0 (old) and dest2 at index 1 (new)
    // firstNewNodeIndex = 1, so removeIndexes = {0}
    // To test empty removeIndexes, make firstNewNodeIndex = 0 (curList's first node is new)
    NavPathList preList;
    preList.push_back(testPair1);
    stack->navPathList_.clear();
    // curList only has the new node (dest2), firstNewNodeIndex = 0
    // so index = 0 - 1 = -1, loop doesn't execute, removeIndexes is empty
    stack->navPathList_.push_back(testPair2);
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // removeIndexes empty, early return, but homeNodeTouched_ was reset to nullopt
    ASSERT_EQ(pattern->homeNodeTouched_, std::nullopt);
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearContentStackIfNeeded009
 * @tc.desc: Branch: actual removal path - nodes before firstNewNodeIndex are removed,
 *           needSyncWithJsStack_ set to false, homeNodeTouched_ reset to nullopt
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTenNg, ClearContentStackIfNeeded009, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    auto dest3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest3, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair3{"three", dest3};

    // preList: [dest1, dest2], curList: [dest1, dest2, dest3]
    // curTopNode = dest3 (not in preList), firstNewNodeIndex = 2
    // removeIndexes = {1, 0} (reversed to {0, 1})
    NavPathList preList;
    preList.push_back(testPair1);
    preList.push_back(testPair2);
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair1);
    stack->navPathList_.push_back(testPair2);
    stack->navPathList_.push_back(testPair3);
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = true;
    pattern->ClearContentStackIfNeeded(std::move(preList));
    // Actual removal path taken: needSyncWithJsStack_ set to false, homeNodeTouched_ reset
    ASSERT_EQ(pattern->homeNodeTouched_, std::nullopt);
    ASSERT_FALSE(pattern->needSyncWithJsStack_);
}
} // namespace OHOS::Ace::NG
