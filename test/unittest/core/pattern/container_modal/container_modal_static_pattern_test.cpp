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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "foundation/arkui/ace_engine/frameworks/base/memory/referenced.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/container_modal/container_modal_element.h"
#include "core/components/theme/advanced_pattern_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/container_modal/static/container_modal_static_pattern.h"
#include "core/components_ng/pattern/container_modal/static/container_modal_static_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/event/mouse_event.h"
#include "core/pipeline/container_window_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class ContainerModalStaticPatternTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ContainerModalStaticPatternTest::SetUpTestCase()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<ContainerModalTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
}

void ContainerModalStaticPatternTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ContainerModalStaticViewTestSetCustomTitle
 * @tc.desc: Test SetCustomTitle
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticViewTestSetCustomTitle, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecuteAppTitleCallback = false;
    auto appTitleCallback = [&isExecuteAppTitleCallback](
                                const std::string& content) { isExecuteAppTitleCallback = true; };
    xbarComponent->setAppTitleFunc = std::move(appTitleCallback);

    patternStatic->SetCustomTitle(xbarComponent);

    auto node = patternStatic->GetCustomTitle();
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: ContainerModalStaticPatternTestSetCustomFloatingTitle
 * @tc.desc: Test SetCustomFloatingTitle
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestSetCustomFloatingTitle, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecuteAppTitleCallback = false;
    auto appTitleCallback = [&isExecuteAppTitleCallback](
                                const std::string& content) { isExecuteAppTitleCallback = true; };
    xbarComponent->setAppTitleFunc = std::move(appTitleCallback);

    patternStatic->SetCustomFloatingTitle(xbarComponent);

    auto node = patternStatic->GetCustomFloatingTitle();
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: ContainerModalStaticPatternTestSetCustomButton
 * @tc.desc: Test SetCustomButton
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestSetCustomButton, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecuteAppTitleCallback = false;
    auto appTitleCallback = [&isExecuteAppTitleCallback](
                                const std::string& content) { isExecuteAppTitleCallback = true; };
    xbarComponent->setAppTitleFunc = std::move(appTitleCallback);

    patternStatic->SetCustomButton(xbarComponent);

    auto node = patternStatic->GetCustomButton();
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: ContainerModalStaticPatternTestSetAppTitle
 * @tc.desc: Test SetAppTitle
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticViewTestSetAppTitle, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto appTitleCallback = [&isExecute](const std::string& content) { isExecute = true; };
    xbarComponent->setAppTitleFunc = std::move(appTitleCallback);

    patternStatic->SetCustomTitle(xbarComponent);
    patternStatic->SetAppTitle("title");
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestChangeCustomTitle001
 * @tc.desc: Test ChangeCustomTitle
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestChangeCustomTitle001, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto callback = [&isExecute]() { isExecute = true; };
    xbarComponent->onWindowFocusedFunc = std::move(callback);

    patternStatic->SetCustomTitle(xbarComponent);
    patternStatic->ChangeCustomTitle(true);
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestChangeCustomTitle002
 * @tc.desc: Test ChangeCustomTitle
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestChangeCustomTitle002, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto callback = [&isExecute]() { isExecute = true; };
    xbarComponent->onWindowUnfocusedFunc = std::move(callback);

    patternStatic->SetCustomTitle(xbarComponent);
    patternStatic->ChangeCustomTitle(false);
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestChangeControlButtons001
 * @tc.desc: Test ChangeControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestChangeControlButtons001, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto callback = [&isExecute]() { isExecute = true; };
    xbarComponent->onWindowFocusedFunc = std::move(callback);

    patternStatic->SetCustomButton(xbarComponent);
    patternStatic->ChangeControlButtons(true);
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestChangeControlButtons002
 * @tc.desc: Test ChangeControlButtons
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestChangeControlButtons002, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto callback = [&isExecute]() { isExecute = true; };
    xbarComponent->onWindowUnfocusedFunc = std::move(callback);

    patternStatic->SetCustomButton(xbarComponent);
    patternStatic->ChangeControlButtons(false);
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestSetContainerButtonHide
 * @tc.desc: Test SetContainerButtonHide
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestSetContainerButtonHide, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto callback = [&isExecute](const std::string& eventName, const std::string& param) { isExecute = true; };
    xbarComponent->setCustomCallbackFunc = std::move(callback);

    patternStatic->SetCustomButton(xbarComponent);
    patternStatic->SetContainerButtonHide(true, false, true, false);
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestSetColorConfigurationUpdate
 * @tc.desc: Test SetColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestSetColorConfigurationUpdate, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    auto frameNode = FrameNode::CreateFrameNode("ContainerModal", 1, patternStatic);
    patternStatic->AttachToFrameNode(frameNode);

    bool isExecute = false;
    auto callback = [&isExecute](const std::string& eventName, const std::string& param) { isExecute = true; };
    xbarComponent->setCustomCallbackFunc = std::move(callback);

    patternStatic->SetCustomButton(xbarComponent);
    patternStatic->SetColorConfigurationUpdate();
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestSetCloseButtonStatus
 * @tc.desc: Test SetCloseButtonStatus
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestSetCloseButtonStatus, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto callback = [&isExecute](const std::string& eventName, const std::string& param) { isExecute = true; };
    xbarComponent->setCustomCallbackFunc = std::move(callback);

    patternStatic->SetCustomButton(xbarComponent);
    patternStatic->SetCloseButtonStatus(true);
    EXPECT_EQ(isExecute, true);
}

/**
 * @tc.name: ContainerModalStaticPatternTestOnContainerModalEvent
 * @tc.desc: Test OnContainerModalEvent
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalStaticPatternTest, ContainerModalStaticPatternTestOnContainerModalEvent, TestSize.Level1)
{
    auto patternStatic = AceType::MakeRefPtr<ContainerModalStaticPattern>();
    auto xbarComponent = AceType::MakeRefPtr<XbarComponent>(1);

    bool isExecute = false;
    auto callback = [&isExecute](const std::string& eventName, const std::string& param) { isExecute = true; };
    xbarComponent->setCustomCallbackFunc = std::move(callback);

    patternStatic->SetCustomButton(xbarComponent);
    patternStatic->OnContainerModalEvent("name", "value");
    EXPECT_EQ(isExecute, true);
}
} // namespace OHOS::Ace::NG
