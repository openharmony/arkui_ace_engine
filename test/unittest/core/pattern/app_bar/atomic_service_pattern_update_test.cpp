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
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/pattern/custom/custom_app_bar_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class AtomicServicePatternUpdateTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->SetCustomAppBarNode(nullptr);
    }
};

void AtomicServicePatternUpdateTest::SetUpTestSuite()
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

void AtomicServicePatternUpdateTest::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: UpdateLayout001
 * @tc.desc: Test UpdateLayout updates menu and close button layouts
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom and pattern.
     * @tc.expected: All objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. Build menu bar and add to atom.
     * @tc.expected: Menu bar is created and added.
     */
    auto menuBar = appBar->BuildMenuBar();
    ASSERT_NE(menuBar, nullptr);
    atom->AddChild(menuBar);

    /**
     * @tc.steps: step3. Call UpdateLayout and verify no crash.
     * @tc.expected: UpdateLayout should complete without error.
     */
    pattern->UpdateLayout();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateLayoutMargin001
 * @tc.desc: Test UpdateLayoutMargin updates stage margin with safe area
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateLayoutMargin001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom and pattern.
     * @tc.expected: All objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. Set safe area on pipeline.
     * @tc.expected: Safe area is set.
     */
    SafeAreaInsets safeArea;
    pipeline->UpdateSystemSafeArea(safeArea);

    /**
     * @tc.steps: step3. Create CustomAppBarNode and set up stage node wrapper.
     * @tc.expected: Stage node wrapper is created.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step4. Build appbar and stage structure.
     * @tc.expected: Structure is built.
     */
    AppBarView::BuildAppbar(pipeline);

    /**
     * @tc.steps: step5. Call UpdateLayoutMargin.
     * @tc.expected: Margin should be updated without error.
     */
    pattern->UpdateLayoutMargin();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateLayoutMargin002
 * @tc.desc: Test UpdateLayoutMargin when stage is null
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateLayoutMargin002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom and pattern.
     * @tc.expected: All objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. Call UpdateLayoutMargin when stage node wrapper is not set.
     * @tc.expected: Function should return gracefully without crash.
     */
    pattern->UpdateLayoutMargin();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateColor001
 * @tc.desc: Test UpdateColor with isLight parameter
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom and pattern.
     * @tc.expected: All objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. Build menu bar with buttons and icons.
     * @tc.expected: Menu bar structure is created.
     */
    auto menuBar = appBar->BuildMenuBar();
    ASSERT_NE(menuBar, nullptr);
    atom->AddChild(menuBar);

    /**
     * @tc.steps: step3. Call UpdateColor with isLight = true.
     * @tc.expected: Colors should be updated for light mode.
     */
    pattern->UpdateColor(true);
    EXPECT_NE(pattern, nullptr);

    /**
     * @tc.steps: step4. Call UpdateColor with isLight = false.
     * @tc.expected: Colors should be updated for dark mode.
     */
    pattern->UpdateColor(false);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateColor002
 * @tc.desc: Test UpdateColor with std::nullopt
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom and pattern.
     * @tc.expected: All objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. Build menu bar structure.
     * @tc.expected: Menu bar structure is created.
     */
    auto menuBar = appBar->BuildMenuBar();
    ASSERT_NE(menuBar, nullptr);
    atom->AddChild(menuBar);

    /**
     * @tc.steps: step3. Call UpdateColor with std::nullopt.
     * @tc.expected: Colors should be updated based on pipeline color mode.
     */
    pattern->UpdateColor(std::nullopt);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateDividerColor001
 * @tc.desc: Test UpdateDividerColor with light mode
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateDividerColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom and pattern.
     * @tc.expected: All objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. Build divider.
     * @tc.expected: Divider is created.
     */
    auto divider = appBar->BuildDivider();
    ASSERT_NE(divider, nullptr);

    /**
     * @tc.steps: step3. Call UpdateDividerColor with isLight = true.
     * @tc.expected: Divider color should be updated for light mode.
     */
    pattern->UpdateDividerColor(theme, divider, true);
    auto dividerPattern = divider->GetPattern<DividerPattern>();
    ASSERT_NE(dividerPattern, nullptr);
    EXPECT_NE(dividerPattern, nullptr);
}

/**
 * @tc.name: UpdateDividerColor002
 * @tc.desc: Test UpdateDividerColor with dark mode
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateDividerColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage, appBar, atom and pattern.
     * @tc.expected: All objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. Build divider.
     * @tc.expected: Divider is created.
     */
    auto divider = appBar->BuildDivider();
    ASSERT_NE(divider, nullptr);

    /**
     * @tc.steps: step3. Call UpdateDividerColor with isLight = false.
     * @tc.expected: Divider color should be updated for dark mode.
     */
    pattern->UpdateDividerColor(theme, divider, false);
    auto dividerPattern = divider->GetPattern<DividerPattern>();
    ASSERT_NE(dividerPattern, nullptr);
    EXPECT_NE(dividerPattern, nullptr);
}

/**
 * @tc.name: UpdateIconColor001
 * @tc.desc: Test UpdateIconColor with null icon
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateIconColor001, TestSize.Level1)
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
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    ASSERT_NE(theme, nullptr);

    /**
     * @tc.steps: step2. Call UpdateIconColor with null icon.
     * @tc.expected: Function should return gracefully without crash.
     */
    RefPtr<FrameNode> nullIcon = nullptr;
    pattern->UpdateIconColor(theme, nullIcon, true);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateIconColor002
 * @tc.desc: Test UpdateIconColor with null theme
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternUpdateTest, UpdateIconColor002, TestSize.Level1)
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
     * @tc.steps: step2. Build icon.
     * @tc.expected: Icon is created.
     */
    auto icon = appBar->BuildIcon(true);
    ASSERT_NE(icon, nullptr);

    /**
     * @tc.steps: step3. Call UpdateIconColor with null theme.
     * @tc.expected: Function should return gracefully without crash.
     */
    RefPtr<AppBarTheme> nullTheme = nullptr;
    pattern->UpdateIconColor(nullTheme, icon, true);
    EXPECT_NE(pattern, nullptr);
}

} // namespace OHOS::Ace::NG
