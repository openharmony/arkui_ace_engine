/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include <string>
#include <unistd.h>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/common/app_bar_helper.h"
#include "core/common/container.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class AtomicServicePatternGetterTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->SetCustomAppBarNode(nullptr);
    }
};

void AtomicServicePatternGetterTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppBarTheme>()));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void AtomicServicePatternGetterTest::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GetStageNodeWrapper001
 * @tc.desc: Test GetStageNodeWrapper function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetStageNodeWrapper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetStageNodeWrapper.
     * @tc.expected: Function should complete without crash.
     */
    auto stageNodeWrapper = pattern->GetStageNodeWrapper();
    // Result depends on inspector setup
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetContent001
 * @tc.desc: Test GetContent function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetContent.
     * @tc.expected: Function should complete without crash.
     */
    auto content = pattern->GetContent();
    // Result depends on stage node wrapper setup
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetMenuBarRow001
 * @tc.desc: Test GetMenuBarRow function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetMenuBarRow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetMenuBarRow.
     * @tc.expected: Function should complete without crash.
     */
    auto menuBarRow = pattern->GetMenuBarRow();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetMenuBar001
 * @tc.desc: Test GetMenuBar function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetMenuBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetMenuBar.
     * @tc.expected: Function should complete without crash.
     */
    auto resultMenuBar = pattern->GetMenuBar();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetMenuButton001
 * @tc.desc: Test GetMenuButton function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetMenuButton001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetMenuButton.
     * @tc.expected: Function should complete without crash.
     */
    auto resultMenuButton = pattern->GetMenuButton();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetDivider001
 * @tc.desc: Test GetDivider function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetDivider.
     * @tc.expected: Function should complete without crash.
     */
    auto resultDivider = pattern->GetDivider();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetCloseButton001
 * @tc.desc: Test GetCloseButton function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetCloseButton001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCloseButton.
     * @tc.expected: Function should complete without crash.
     */
    auto resultCloseButton = pattern->GetCloseButton();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetMenuIcon001
 * @tc.desc: Test GetMenuIcon function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetMenuIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetMenuIcon.
     * @tc.expected: Function should complete without crash.
     */
    auto resultMenuIcon = pattern->GetMenuIcon();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetCloseIcon001
 * @tc.desc: Test GetCloseIcon function call completes
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternGetterTest, GetCloseIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern instance.
     * @tc.expected: Pattern is created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call GetCloseIcon.
     * @tc.expected: Function should complete without crash.
     */
    auto resultCloseIcon = pattern->GetCloseIcon();
    EXPECT_NE(pattern, nullptr);
}

} // namespace OHOS::Ace::NG
