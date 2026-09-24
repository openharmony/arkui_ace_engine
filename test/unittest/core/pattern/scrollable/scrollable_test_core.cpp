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

#include "scrollable_test_min.h"

#define private public
#define protected public

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/interfaces/inner_api/ui_session/mock_ui_session_manager.h"

#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;


namespace OHOS::Ace::NG {

// Test classes for TDD development (quick compile mode)
// These classes use different names from full test suite to avoid conflicts
// When ace_enable_full_test_suite=true, full test files will be compiled instead

class ScrollableTestCore : public ScrollableTestBase {
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
HWTEST_F(ScrollableTestCore, ScrollableTestPlaceholder, TestSize.Level1)
{
    EXPECT_TRUE(true);
}

/**
 * @tc.name: ContentChangeScrollStartTest001
 * @tc.desc: Test scroll START and abort normal END are connected to ContentChangeManager.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestCore, ContentChangeScrollStartTest001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetContentChangeManager();
    ASSERT_NE(manager, nullptr);
    ContentChangeConfig config;
    config.reportStartEvent = true;
    manager->StartContentChangeReport(config);

    auto pattern = AceType::MakeRefPtr<ListPattern>();
    auto scrollNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 421, pattern, true);
    ASSERT_NE(scrollNode, nullptr);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    ASSERT_NE(mockUiSessionManager, nullptr);

    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SCROLL_START, _)).Times(1);
    pattern->ContentChangeOnScrollStart(scrollNode);
    Mock::VerifyAndClearExpectations(mockUiSessionManager);

    pattern->scrollStop_ = true;
    pattern->SetScrollAbort(true);
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SCROLL, Truly([](const auto& json) {
        auto value = JsonUtil::ParseJsonString(json);
        return value && value->GetString("endReason").empty();
    }))).Times(1);
    pattern->OnScrollStop({}, {});
    EXPECT_TRUE(manager->activeContentChanges_.empty());
    EXPECT_TRUE(manager->scrollingNodes_.empty());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    manager->StopContentChangeReport();
}

/**
 * @tc.name: ContentChangeScrollAbortContinuationTest001
 * @tc.desc: Replacing an animation keeps the content change cycle active until the new animation stops.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestCore, ContentChangeScrollAbortContinuationTest001, TestSize.Level1)
{
    auto manager = MockPipelineContext::GetCurrent()->GetContentChangeManager();
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    for (bool reportStartEvent : { false, true }) {
        ContentChangeConfig config;
        config.reportStartEvent = reportStartEvent;
        manager->StartContentChangeReport(config);
        auto pattern = AceType::MakeRefPtr<ListPattern>();
        auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 422, pattern, true);
        ASSERT_NE(node, nullptr);
        EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SCROLL_START, _))
            .Times(reportStartEvent ? 1 : 0);
        pattern->ContentChangeOnScrollStart(node);
        Mock::VerifyAndClearExpectations(mockUiSessionManager);

        // AnimateTo stops the old animation, starts a new one, and suppresses the duplicate OnScrollStart.
        pattern->isAnimationStop_ = false;
        pattern->scrollStop_ = true;
        pattern->SetScrollAbort(true);
        EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _)).Times(0);
        pattern->FireOnScrollStart(false);
        pattern->OnScrollStop({}, {});
        EXPECT_TRUE(manager->IsScrolling());
        EXPECT_EQ(manager->activeContentChanges_.empty(), !reportStartEvent);
        Mock::VerifyAndClearExpectations(mockUiSessionManager);

        pattern->isAnimationStop_ = true;
        pattern->scrollStop_ = true;
        EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(ChangeType::SCROLL, _)).Times(1);
        pattern->OnScrollStop({}, {});
        EXPECT_FALSE(manager->IsScrolling());
        EXPECT_TRUE(manager->activeContentChanges_.empty());
        Mock::VerifyAndClearExpectations(mockUiSessionManager);
        manager->StopContentChangeReport();
    }
}

/**
 * @tc.name: ContentChangeScrollAbortLegacyTest001
 * @tc.desc: With START reporting disabled, an abort preserves the existing scroll tracking behavior.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableTestCore, ContentChangeScrollAbortLegacyTest001, TestSize.Level1)
{
    auto manager = MockPipelineContext::GetCurrent()->GetContentChangeManager();
    manager->StartContentChangeReport(ContentChangeConfig());
    auto pattern = AceType::MakeRefPtr<ListPattern>();
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 423, pattern, true);
    ASSERT_NE(node, nullptr);
    pattern->ContentChangeOnScrollStart(node);
    pattern->scrollStop_ = true;
    pattern->SetScrollAbort(true);
    auto mockUiSessionManager = reinterpret_cast<MockUiSessionManager*>(UiSessionManager::GetInstance());
    EXPECT_CALL(*mockUiSessionManager, ReportContentChangeEvent(_, _)).Times(0);
    pattern->OnScrollStop({}, {});
    EXPECT_TRUE(manager->IsScrolling());
    Mock::VerifyAndClearExpectations(mockUiSessionManager);
    manager->StopContentChangeReport();
}

} // namespace OHOS::Ace::NG
