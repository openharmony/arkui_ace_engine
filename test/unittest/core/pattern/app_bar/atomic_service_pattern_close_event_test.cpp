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

#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/ace_type.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class AtomicServicePatternCloseEventTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->SetCustomAppBarNode(nullptr);
    }
};

void AtomicServicePatternCloseEventTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp(PipelineBase::GetCurrentContext());

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppBarTheme>()));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void AtomicServicePatternCloseEventTest::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GetJSAppBarContainer002
 * @tc.desc: Verify GetJSAppBarContainer returns nullptr by default.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, GetJSAppBarContainer002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetJSAppBarContainer(), nullptr);
}

/**
 * @tc.name: SetCustomAppBarNode003
 * @tc.desc: Verify SetCustomAppBarNode supports repeated overwrite.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, SetCustomAppBarNode003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    auto firstNode = CustomAppBarNode::CreateCustomAppBarNode(-101, "first");
    auto secondNode = CustomAppBarNode::CreateCustomAppBarNode(-102, "second");
    ASSERT_NE(firstNode, nullptr);
    ASSERT_NE(secondNode, nullptr);

    pattern->SetCustomAppBarNode(firstNode);
    EXPECT_EQ(pattern->GetJSAppBarContainer(), firstNode);

    pattern->SetCustomAppBarNode(secondNode);
    EXPECT_EQ(pattern->GetJSAppBarContainer(), secondNode);
}

/**
 * @tc.name: SetCustomAppBarNode004
 * @tc.desc: Verify SetCustomAppBarNode accepts nullptr and clears state.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, SetCustomAppBarNode004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    auto customNode = CustomAppBarNode::CreateCustomAppBarNode(-103, "clear");
    ASSERT_NE(customNode, nullptr);
    pattern->SetCustomAppBarNode(customNode);
    ASSERT_NE(pattern->GetJSAppBarContainer(), nullptr);

    pattern->SetCustomAppBarNode(nullptr);
    EXPECT_EQ(pattern->GetJSAppBarContainer(), nullptr);
}

/**
 * @tc.name: FireArkuiAbilityCloseEvent001
 * @tc.desc: Verify FireAbilityCloseEvent dispatches expected event and payload.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, FireArkuiAbilityCloseEvent001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    auto customNode = CustomAppBarNode::CreateCustomAppBarNode(-104, "close_event");
    ASSERT_NE(customNode, nullptr);
    pattern->SetCustomAppBarNode(customNode);

    int32_t callbackCount = 0;
    std::string eventName;
    std::string eventParam;
    customNode->SetCustomCallback(
        [&callbackCount, &eventName, &eventParam](const std::string& name, const std::string& param) {
            ++callbackCount;
            eventName = name;
            eventParam = param;
        });

    pattern->FireAbilityCloseEvent();

    EXPECT_EQ(callbackCount, 1);
    EXPECT_EQ(eventName, ARKUI_ABILITY_CLOSE_EVENT);
    EXPECT_EQ(eventParam, "true");
}

/**
 * @tc.name: FireArkuiAbilityCloseEvent002
 * @tc.desc: Verify FireAbilityCloseEvent handles nullptr node safely.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, FireArkuiAbilityCloseEvent002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetCustomAppBarNode(nullptr);
    pattern->FireAbilityCloseEvent();
    SUCCEED();
}

/**
 * @tc.name: AppBarViewFireArkuiAbilityCloseEvent001
 * @tc.desc: Verify AppBarView::FireAbilityCloseEvent returns safely when atomic service is empty.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, AppBarViewFireArkuiAbilityCloseEvent001, TestSize.Level1)
{
    auto mockPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(mockPipeline, nullptr);
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
    ASSERT_NE(taskExecutor, nullptr);
    mockPipeline->SetTaskExecutor(taskExecutor);

    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    appBar->FireAbilityCloseEvent();
    SUCCEED();
}

/**
 * @tc.name: AppBarViewFireArkuiAbilityCloseEvent002
 * @tc.desc: Verify callback is not fired when UI task is posted but not executed.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, AppBarViewFireArkuiAbilityCloseEvent002, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    auto customNode = CustomAppBarNode::CreateCustomAppBarNode(-105, "close_event_not_run");
    ASSERT_NE(customNode, nullptr);
    pattern->SetCustomAppBarNode(customNode);

    int32_t callbackCount = 0;
    customNode->SetCustomCallback([&callbackCount](const std::string&, const std::string&) { ++callbackCount; });

    auto mockPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(mockPipeline, nullptr);
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
    ASSERT_NE(taskExecutor, nullptr);
    mockPipeline->SetTaskExecutor(taskExecutor);

    appBar->FireAbilityCloseEvent();
    EXPECT_EQ(callbackCount, 0);
}

/**
 * @tc.name: AppBarViewFireArkuiAbilityCloseEvent003
 * @tc.desc: Verify callback is fired when UI task executes normally.
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternCloseEventTest, AppBarViewFireArkuiAbilityCloseEvent003, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    auto customNode = CustomAppBarNode::CreateCustomAppBarNode(-106, "close_event_run");
    ASSERT_NE(customNode, nullptr);
    pattern->SetCustomAppBarNode(customNode);

    int32_t callbackCount = 0;
    std::string eventName;
    std::string eventParam;
    customNode->SetCustomCallback(
        [&callbackCount, &eventName, &eventParam](const std::string& name, const std::string& param) {
            ++callbackCount;
            eventName = name;
            eventParam = param;
        });

    auto mockPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(mockPipeline, nullptr);
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(false);
    ASSERT_NE(taskExecutor, nullptr);
    mockPipeline->SetTaskExecutor(taskExecutor);

    appBar->FireAbilityCloseEvent();
    EXPECT_EQ(callbackCount, 1);
    EXPECT_EQ(eventName, ARKUI_ABILITY_CLOSE_EVENT);
    EXPECT_EQ(eventParam, "true");
}
} // namespace OHOS::Ace::NG
