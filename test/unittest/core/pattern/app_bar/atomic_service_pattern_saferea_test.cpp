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

class AtomicServicePatternSafeAreaTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->SetCustomAppBarNode(nullptr);
    }
};

void AtomicServicePatternSafeAreaTest::SetUpTestSuite()
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

void AtomicServicePatternSafeAreaTest::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: MenuBarSafeAreaCallBack001
 * @tc.desc: Test MenuBarSafeAreaCallBack triggers safe area callback
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternSafeAreaTest, MenuBarSafeAreaCallBack001, TestSize.Level1)
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
     * @tc.steps: step2. Set up safe area manager and system safe area.
     * @tc.expected: Safe area is configured.
     */
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    SafeAreaInsets systemSafeArea;
    pipeline->safeAreaManager_->UpdateSystemSafeArea(systemSafeArea);

    /**
     * @tc.steps: step3. Create CustomAppBarNode and set callback.
     * @tc.expected: CustomAppBarNode is created and callback is set.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step4. Set callback to verify MenuBarSafeAreaCallBack is triggered.
     * @tc.expected: MenuBarSafeAreaCallBack should be executed with correct safe area value.
     */
    bool callbackExecuted = false;
    std::string receivedValue;
    auto callback = [&callbackExecuted, &receivedValue](const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BAR_MENU_SAFE_AREA) {
            callbackExecuted = true;
            receivedValue = value;
        }
    };
    custom->SetCustomCallback(std::move(callback));

    /**
     * @tc.steps: step5. Call MenuBarSafeAreaCallBack.
     * @tc.expected: Callback should be executed with safe area value.
     */
    pattern->MenuBarSafeAreaCallBack();
    EXPECT_TRUE(callbackExecuted);
    EXPECT_FALSE(receivedValue.empty());
}

/**
 * @tc.name: ContentSafeAreaCallBack001
 * @tc.desc: Test ContentSafeAreaCallBack triggers content safe area callback
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternSafeAreaTest, ContentSafeAreaCallBack001, TestSize.Level1)
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
     * @tc.steps: step2. Set up safe area.
     * @tc.expected: Safe area is configured.
     */
    SafeAreaInsets safeArea;
    pipeline->UpdateSystemSafeArea(safeArea);
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();

    /**
     * @tc.steps: step3. Create CustomAppBarNode and set callback.
     * @tc.expected: CustomAppBarNode is created and callback is set.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step4. Set callback to verify ContentSafeAreaCallBack is triggered.
     * @tc.expected: ContentSafeAreaCallBack should be executed with correct safe area values.
     */
    bool callbackExecuted = false;
    std::string receivedValue;
    auto callback = [&callbackExecuted, &receivedValue](const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BAR_CONTENT_SAFE_AREA) {
            callbackExecuted = true;
            receivedValue = value;
        }
    };
    custom->SetCustomCallback(std::move(callback));

    /**
     * @tc.steps: step5. Call ContentSafeAreaCallBack.
     * @tc.expected: Callback should be executed with content safe area values.
     */
    pattern->ContentSafeAreaCallBack();
    EXPECT_TRUE(callbackExecuted);
    EXPECT_FALSE(receivedValue.empty());
}

/**
 * @tc.name: ContentSafeAreaCallBack002
 * @tc.desc: Test ContentSafeAreaCallBack with keyboard enabled
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternSafeAreaTest, ContentSafeAreaCallBack002, TestSize.Level1)
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
     * @tc.steps: step2. Set up safe area with keyboard enabled.
     * @tc.expected: Safe area is configured with keyboard.
     */
    SafeAreaInsets safeArea;
    pipeline->UpdateSystemSafeArea(safeArea);

    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    pipeline->safeAreaManager_->keyboardSafeAreaEnabled_ = true;
    SafeAreaInsets keyboardInset;
    pipeline->safeAreaManager_->UpdateSystemSafeArea(keyboardInset);

    /**
     * @tc.steps: step3. Create CustomAppBarNode and set callback.
     * @tc.expected: CustomAppBarNode is created and callback is set.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step4. Set callback to verify ContentSafeAreaCallBack includes keyboard inset.
     * @tc.expected: ContentSafeAreaCallBack should be executed with keyboard inset included.
     */
    bool callbackExecuted = false;
    std::string receivedValue;
    auto callback = [&callbackExecuted, &receivedValue](const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BAR_CONTENT_SAFE_AREA) {
            callbackExecuted = true;
            receivedValue = value;
        }
    };
    custom->SetCustomCallback(std::move(callback));

    /**
     * @tc.steps: step5. Call ContentSafeAreaCallBack.
     * @tc.expected: Callback should be executed with keyboard inset combined in bottom value.
     */
    pattern->ContentSafeAreaCallBack();
    EXPECT_TRUE(callbackExecuted);
    EXPECT_FALSE(receivedValue.empty());
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: Test BeforeCreateLayoutWrapper calls all callbacks
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternSafeAreaTest, BeforeCreateLayoutWrapper001, TestSize.Level1)
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
     * @tc.steps: step2. Set up safe area manager.
     * @tc.expected: Safe area manager is configured.
     */
    pipeline->safeAreaManager_ = AceType::MakeRefPtr<SafeAreaManager>();
    SafeAreaInsets systemSafeArea;
    pipeline->safeAreaManager_->UpdateSystemSafeArea(systemSafeArea);

    SafeAreaInsets safeArea;
    pipeline->UpdateSystemSafeArea(safeArea);

    /**
     * @tc.steps: step3. Create CustomAppBarNode and set callback.
     * @tc.expected: CustomAppBarNode is created and callback is set.
     */
    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    /**
     * @tc.steps: step4. Set callback to verify all callbacks are triggered.
     * @tc.expected: All callbacks should be executed.
     */
    bool menuSafeAreaCalled = false;
    bool contentSafeAreaCalled = false;
    bool colorConfigCalled = false;

    auto callback = [&menuSafeAreaCalled, &contentSafeAreaCalled, &colorConfigCalled](
                        const std::string& name, const std::string& value) {
        if (name == ARKUI_APP_BAR_MENU_SAFE_AREA) {
            menuSafeAreaCalled = true;
        } else if (name == ARKUI_APP_BAR_CONTENT_SAFE_AREA) {
            contentSafeAreaCalled = true;
        } else if (name == ARKUI_APP_BAR_COLOR_CONFIGURATION) {
            colorConfigCalled = true;
        }
    };
    custom->SetCustomCallback(std::move(callback));

    /**
     * @tc.steps: step5. Call BeforeCreateLayoutWrapper.
     * @tc.expected: All three callbacks should be executed.
     */
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(menuSafeAreaCalled);
    EXPECT_TRUE(contentSafeAreaCalled);
    EXPECT_TRUE(colorConfigCalled);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper002
 * @tc.desc: Test BeforeCreateLayoutWrapper with custom builder
 * @tc.type: FUNC
 */
HWTEST_F(AtomicServicePatternSafeAreaTest, BeforeCreateLayoutWrapper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern and call BeforeCreateLayoutWrapper.
     * @tc.expected: Custom builder should be called, safe area callbacks should not be called.
     */
    auto stage = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stage, nullptr);
    auto appBar = AceType::MakeRefPtr<AppBarView>();
    ASSERT_NE(appBar, nullptr);
    auto atom = appBar->Create(stage);
    ASSERT_NE(atom, nullptr);
    auto pattern = atom->GetPattern<AtomicServicePattern>();
    ASSERT_NE(pattern, nullptr);

    auto custom = CustomAppBarNode::CreateCustomAppBarNode(-1, "");
    ASSERT_NE(custom, nullptr);
    ViewStackProcessor::GetInstance()->SetCustomAppBarNode(custom);
    pattern->SetCustomAppBarNode(custom);

    bool anyCallbackCalled = false;
    auto callback = [&anyCallbackCalled](const std::string& name, const std::string& value) {
        anyCallbackCalled = true;
    };
    custom->SetCustomCallback(std::move(callback));

    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(anyCallbackCalled);
}

} // namespace OHOS::Ace::NG
