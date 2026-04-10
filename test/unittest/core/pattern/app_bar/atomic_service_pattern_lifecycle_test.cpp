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
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

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

class AtomicServicePatternLifecycleTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->SetCustomAppBarNode(nullptr);
    }
};

void AtomicServicePatternLifecycleTest::SetUpTestSuite()
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

void AtomicServicePatternLifecycleTest::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode initializes measure type and calls AppBgColorCallBack
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternLifecycleTest, OnAttachToFrameNode001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Create CustomAppBarNode and set callback.
     * @tc.expected: CustomAppBarNode is created and callback is set.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step3. Call OnAttachToFrameNode and verify measure type is set.
     * @tc.expected: Measure type should be MATCH_PARENT.
     */
    pattern->OnAttachToFrameNode();
    auto layoutProperty = atom->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetMeasureType(), MeasureType::MATCH_PARENT);

    /**
     * @tc.steps: step4. Verify AppBgColorCallBack is triggered.
     * @tc.expected: Callback should be executed.
     */
    bool callbackExecuted = false;
    auto callback = [&callbackExecuted](const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BG_COLOR) {
            callbackExecuted = true;
        }
    };
    custom->SetCustomCallback(std::move(callback));
    pattern->OnAttachToFrameNode();
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: OnLanguageConfigurationUpdate001
 * @tc.desc: Test OnLanguageConfigurationUpdate triggers AppInfoCallBack and reload
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternLifecycleTest, OnLanguageConfigurationUpdate001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Create CustomAppBarNode and set callback.
     * @tc.expected: CustomAppBarNode is created and callback is set.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step3. Set callback to verify AppInfoCallBack is triggered.
     * @tc.expected: AppInfoCallBack should be executed.
     */
    bool appInfoCallbackExecuted = false;
    auto callback = [&appInfoCallbackExecuted](const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BAR_BAR_INFO) {
            appInfoCallbackExecuted = true;
        }
    };
    custom->SetCustomCallback(std::move(callback));

    /**
     * @tc.steps: step4. Call OnLanguageConfigurationUpdate.
     * @tc.expected: AppInfoCallBack should be triggered.
     */
    pattern->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(appInfoCallbackExecuted);
}

/**
 * @tc.name: OnLanguageConfigurationUpdate002
 * @tc.desc: Test OnLanguageConfigurationUpdate triggers reload function
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternLifecycleTest, OnLanguageConfigurationUpdate002, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Create CustomAppBarNode and verify callbacks are triggered.
     * @tc.expected: AppInfoCallBack should be executed.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    pattern->SetCustomAppBarNode(custom);

    bool appInfoCallbackExecuted = false;
    auto callback = [&appInfoCallbackExecuted](const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BAR_BAR_INFO) {
            appInfoCallbackExecuted = true;
        }
    };
    custom->SetCustomCallback(std::move(callback));

    pattern->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(appInfoCallbackExecuted);
}

/**
 * @tc.name: RegisterBeforeCreateLayoutBuilder001
 * @tc.desc: Test RegisterBeforeCreateLayoutBuilder sets custom builder
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternLifecycleTest, RegisterBeforeCreateLayoutBuilder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern and trigger BeforeCreateLayoutWrapper.
     * @tc.expected: Custom builder should be called.
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
     * @tc.steps: step2. Create CustomAppBarNode and verify callbacks are triggered.
     * @tc.expected: AppInfoCallBack should be executed.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    pattern->SetCustomAppBarNode(custom);

    bool builderCalled = false;
    auto callback = [&builderCalled](const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BAR_BAR_INFO) {
            builderCalled = true;
        }
    };
    custom->SetCustomCallback(std::move(callback));

    pattern->settedColorMode = true;
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(builderCalled);
}

/**
 * @tc.name: SetOnBackPressedConsumed001
 * @tc.desc: Test SetOnBackPressedConsumed sets the flag when already has value
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternLifecycleTest, SetOnBackPressedConsumed001, TestSize.Level1)
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
     * @tc.steps: step2. Initialize onBackPressedConsumed_ to false.
     * @tc.expected: Flag is set to false.
     */
    pattern->onBackPressedConsumed_ = false;

    /**
     * @tc.steps: step3. Call SetOnBackPressedConsumed.
     * @tc.expected: Flag should be set to true.
     */
    pattern->SetOnBackPressedConsumed();
    EXPECT_TRUE(pattern->onBackPressedConsumed_.has_value());
    EXPECT_EQ(pattern->onBackPressedConsumed_.value(), true);

    /**
     * @tc.steps: step4. Call SetOnBackPressedConsumed when flag is already true.
     * @tc.expected: Flag should remain true.
     */
    pattern->SetOnBackPressedConsumed();
    EXPECT_EQ(pattern->onBackPressedConsumed_.value(), true);
}

/**
 * @tc.name: SetOnBackPressedConsumed002
 * @tc.desc: Test SetOnBackPressedConsumed does nothing when no value exists
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternLifecycleTest, SetOnBackPressedConsumed002, TestSize.Level1)
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
     * @tc.steps: step2. Ensure onBackPressedConsumed_ has no value.
     * @tc.expected: Flag is empty.
     */
    pattern->onBackPressedConsumed_.reset();
    EXPECT_FALSE(pattern->onBackPressedConsumed_.has_value());

    /**
     * @tc.steps: step3. Call SetOnBackPressedConsumed when flag is empty.
     * @tc.expected: Flag should remain empty.
     */
    pattern->SetOnBackPressedConsumed();
    EXPECT_FALSE(pattern->onBackPressedConsumed_.has_value());
}

} // namespace OHOS::Ace::NG
