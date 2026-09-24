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

#include "stage_test_min.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/interfaces/inner_api/ui_session/mock_ui_session_manager.h"

#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;


namespace OHOS::Ace::NG {

// Test classes for TDD development (quick compile mode)
// These classes use different names from full test suite to avoid conflicts
// When ace_enable_full_test_suite=true, full test files will be compiled instead

class StagePatternTestCore : public StageTestBase {
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

class ContentChangePagePattern : public PagePattern {
    DECLARE_ACE_TYPE(ContentChangePagePattern, PagePattern);

public:
    ContentChangePagePattern() : PagePattern(AceType::MakeRefPtr<PageInfo>()) {}

    void TriggerDefaultTransition(
        const std::function<void()>& onFinish, PageTransitionType /* type */) override
    {
        transitionFinish_ = onFinish;
    }

    std::function<void()> transitionFinish_;
};

// Placeholder test to ensure compilation
HWTEST_F(StagePatternTestCore, StageTestPlaceholder, TestSize.Level1)
{
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ContentChangePageStartTest001
 * @tc.desc: Test only entering page transitions report START.
 * @tc.type: FUNC
 */
HWTEST_F(StagePatternTestCore, ContentChangePageStartTest001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto pattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 401, pattern, true);
    ASSERT_NE(pageNode, nullptr);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE_START, _)).Times(0);
    pattern->FirePageTransitionStart(PageTransitionType::EXIT_PUSH);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE_START, _)).Times(1);
    pattern->FirePageTransitionStart(PageTransitionType::ENTER_PUSH);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangePageStartTest002
 * @tc.desc: Test an interrupted page transition keeps the existing animation completion END.
 * @tc.type: FUNC
 */
HWTEST_F(StagePatternTestCore, ContentChangePageStartTest002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto pattern = AceType::MakeRefPtr<ContentChangePagePattern>();
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 402, pattern, true);
    ASSERT_NE(pageNode, nullptr);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE_START, _)).Times(1);
    pattern->TriggerPageTransition({}, PageTransitionType::ENTER_PUSH);
    ASSERT_TRUE(pattern->transitionFinish_);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE, _)).Times(0);
    pattern->StopPageTransition();
    EXPECT_FALSE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE, Truly([](const auto& json) {
        auto value = JsonUtil::ParseJsonString(json);
        return value && value->GetString("endReason").empty();
    }))).Times(1);
    pattern->transitionFinish_();
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangePageStartTest003
 * @tc.desc: Test stale transition completion keeps the legacy normal END behavior when START reporting is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(StagePatternTestCore, ContentChangePageStartTest003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    manager->StartContentChangeReport({});

    auto pattern = AceType::MakeRefPtr<ContentChangePagePattern>();
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 403, pattern, true);
    ASSERT_NE(pageNode, nullptr);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE_START, _)).Times(0);
    pattern->TriggerPageTransition({}, PageTransitionType::ENTER_PUSH);
    ASSERT_TRUE(pattern->transitionFinish_);
    pattern->StopPageTransition();
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::PAGE, _)).Times(1);
    pattern->transitionFinish_();
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    manager->StopContentChangeReport();
}

} // namespace OHOS::Ace::NG
