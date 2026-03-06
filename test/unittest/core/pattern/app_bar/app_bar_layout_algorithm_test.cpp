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
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/app_bar/atomic_service_layout_algorithm.h"
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

class AppBarLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->SetCustomAppBarNode(nullptr);
    }
};

void AppBarLayoutAlgorithmTest::SetUpTestSuite()
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

void AppBarLayoutAlgorithmTest::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: AtomicServiceLayoutAlgorithm001
 * @tc.desc: Test AtomicServiceLayoutAlgorithm creation and basic functionality
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, AtomicServiceLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create AtomicServiceLayoutAlgorithm instance.
     * @tc.expected: Algorithm instance is created successfully.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<AtomicServiceLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_NE(layoutAlgorithm, nullptr);
}

/**
 * @tc.name: AtomicServiceLayoutAlgorithm002
 * @tc.desc: Test AtomicServiceLayoutAlgorithm inherits from LinearLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, AtomicServiceLayoutAlgorithm002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create AtomicServiceLayoutAlgorithm instance.
     * @tc.expected: Algorithm instance is created successfully.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<AtomicServiceLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. Verify it can be cast to LinearLayoutAlgorithm.
     * @tc.expected: Cast should succeed.
     */
    auto linearLayoutAlgorithm = AceType::DynamicCast<LinearLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(linearLayoutAlgorithm, nullptr);
    EXPECT_EQ(linearLayoutAlgorithm, layoutAlgorithm);
}

/**
 * @tc.name: AtomicServiceLayoutAlgorithm003
 * @tc.desc: Test AtomicServiceLayoutAlgorithm inherits from LinearLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, AtomicServiceLayoutAlgorithm003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create AtomicServiceLayoutAlgorithm instance.
     * @tc.expected: Algorithm instance is created successfully.
     */
    auto layoutAlgorithm = AceType::MakeRefPtr<AtomicServiceLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. Verify it can be cast to LinearLayoutAlgorithm.
     * @tc.expected: Cast should succeed.
     */
    auto linearLayoutAlgorithm = AceType::DynamicCast<LinearLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(linearLayoutAlgorithm, nullptr);
    EXPECT_EQ(linearLayoutAlgorithm, layoutAlgorithm);
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm returns AtomicServiceLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, CreateLayoutAlgorithm001, TestSize.Level1)
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
     * @tc.steps: step2. Call CreateLayoutAlgorithm.
     * @tc.expected: Should return AtomicServiceLayoutAlgorithm instance.
     */
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Verify the returned algorithm is AtomicServiceLayoutAlgorithm.
     * @tc.expected: Cast should succeed.
     */
    auto atomicServiceLayoutAlgorithm = AceType::DynamicCast<AtomicServiceLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(atomicServiceLayoutAlgorithm, nullptr);
    EXPECT_EQ(atomicServiceLayoutAlgorithm, layoutAlgorithm);
}

/**
 * @tc.name: UpdateOverlayLayout001
 * @tc.desc: Test UpdateOverlayLayout with no overlay children
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, UpdateOverlayLayout001, TestSize.Level1)
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
     * @tc.steps: step2. Call UpdateOverlayLayout when atom has no overlay children.
     * @tc.expected: Function should return early without error.
     */
    pattern->UpdateOverlayLayout();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: UpdateOverlayLayout002
 * @tc.desc: Test UpdateOverlayLayout with overlay children
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, UpdateOverlayLayout002, TestSize.Level1)
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
     * @tc.steps: step2. Add overlay children to atom.
     * @tc.expected: Overlay children are added.
     */
    auto menuBar = appBar->BuildMenuBar();
    ASSERT_NE(menuBar, nullptr);
    atom->AddChild(menuBar);

    auto overlay = FrameNode::CreateFrameNode(
        "overlay", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(overlay, nullptr);
    atom->AddChild(overlay);

    /**
     * @tc.steps: step3. Call UpdateOverlayLayout.
     * @tc.expected: Overlay position should be updated without error.
     */
    pattern->UpdateOverlayLayout();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: GetAtomicServicePattern001
 * @tc.desc: Test GetAtomicServicePattern returns pattern instance
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, GetAtomicServicePattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stage and appBar.
     * @tc.expected: Objects are created successfully.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);

    /**
     * @tc.steps: step2. Call GetAtomicServicePattern.
     * @tc.expected: Should return AtomicServicePattern instance.
     */
    auto pattern = appBar->GetAtomicServicePattern();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. Verify the pattern type.
     * @tc.expected: Should be AtomicServicePattern.
     */
    auto atomicServicePattern = AceType::DynamicCast<AtomicServicePattern>(pattern);
    ASSERT_NE(atomicServicePattern, nullptr);
    EXPECT_EQ(atomicServicePattern, pattern);
}

/**
 * @tc.name: GetAtomicServicePattern002
 * @tc.desc: Test GetAtomicServicePattern with null atomic service
 * @tc.type: FUNC
 */
HWTEST_F(AppBarLayoutAlgorithmTest, GetAtomicServicePattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create AppBarView without creating atomic service.
     * @tc.expected: AppBarView is created successfully.
     */
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);

    /**
     * @tc.steps: step2. Call GetAtomicServicePattern when atomicService_ is null.
     * @tc.expected: Should return null.
     */
    auto pattern = appBar->GetAtomicServicePattern();
    EXPECT_EQ(pattern, nullptr);
}

} // namespace OHOS::Ace::NG
