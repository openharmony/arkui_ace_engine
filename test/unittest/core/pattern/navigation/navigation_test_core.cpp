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

#include "navigation_test_min.h"
#include "mock_navigation_route.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/interfaces/inner_api/ui_session/mock_ui_session_manager.h"

#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;


namespace OHOS::Ace::NG {

// Test classes for TDD development (quick compile mode)
// These classes use different names from full test suite to avoid conflicts
// When ace_enable_full_test_suite=true, full test files will be compiled instead

class NavigationModelNgTestCore : public NavigationTestBase {};
class NavigationPatternTestCore : public NavigationTestBase {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
    }
};

// Placeholder test to ensure compilation
HWTEST_F(NavigationModelNgTestCore, NavigationTestPlaceholder, TestSize.Level1)
{
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ContentChangeNavigationStartTest001
 * @tc.desc: Test Navigation reports PAGE START and normal END with the same top destination identity.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestCore, ContentChangeNavigationStartTest001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto navigationNode =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 411, navigationPattern, true);
    auto topDestination = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 412, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(navigationNode, nullptr);
    ASSERT_NE(topDestination, nullptr);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    EXPECT_CALL(*mockUiSessionManager,
        ReportContentChangeEvent(ChangeType::PAGE_START, HasSubstr("\"$ID\":412"))).Times(1);
    navigationPattern->ContentChangeOnTransitionStart(topDestination);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE, _)).Times(1);
    navigationPattern->ContentChangeReport(topDestination);
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    manager->StopContentChangeReport();
}

} // namespace OHOS::Ace::NG
