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
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_toolbar.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/toolbaritem/toolbar_row_pattern.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class ContainerModelToolBarTestNg : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTitleMgr();
    void GetInstance();
    RefPtr<FrameNode> CreateContent();
    void SetMockWindow(WindowMode windowMode);
    void CreateContainerModal();

    RefPtr<FrameNode> frameNode_;
    RefPtr<ContainerModalPattern> pattern_;
    RefPtr<LayoutProperty> layoutProperty_;
    RefPtr<ContainerModalAccessibilityProperty> accessibilityProperty_;
    RefPtr<ContainerModalToolBar> titleMgr_;
};

void ContainerModelToolBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_CONTAINER_MODAL);
    auto containerModalTheme = ContainerModalTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(containerModalTheme));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void ContainerModelToolBarTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerModelToolBarTestNg::SetUp()
{
    SetMockWindow(WindowMode::WINDOW_MODE_FULLSCREEN);
}

void ContainerModelToolBarTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    titleMgr_ = nullptr;
}

void ContainerModelToolBarTestNg::CreateTitleMgr()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("frameNode", 0, AceType::MakeRefPtr<Pattern>());
    pattern_->SetToolbarBuilder(frameNode, nullptr);
    titleMgr_ = pattern_->titleMgr_;
}

void ContainerModelToolBarTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ContainerModalPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ContainerModalAccessibilityProperty>();
}

RefPtr<FrameNode> ContainerModelToolBarTestNg::CreateContent()
{
    return AceType::MakeRefPtr<FrameNode>("content", 0, AceType::MakeRefPtr<Pattern>());
}

void ContainerModelToolBarTestNg::SetMockWindow(WindowMode windowMode)
{
    const auto windowManager = AceType::MakeRefPtr<WindowManager>();
    auto windowModeCallback = [windowMode]() { return windowMode; };
    windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->windowManager_ = windowManager;
}

void ContainerModelToolBarTestNg::CreateContainerModal()
{
    ContainerModalView view;
    RefPtr<FrameNode> content = CreateContent();
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ;
    content->AddChild(pageNode);
    auto frameNode = view.Create(content);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    GetInstance();
    CreateTitleMgr();
    FlushUITasks(frameNode_);
}

/**
 * @tc.name: FocusEventTest001
 * @tc.desc: Test PagePattern GetScopeFocusAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest001, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    auto pageNode = pattern_->GetPageNode();
    ASSERT_NE(pageNode, nullptr);
    EXPECT_EQ(pageNode->GetTag(), V2::PAGE_ETS_TAG);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePattern, nullptr);

    pattern_->SetIsHaveToolBar(false);
    EXPECT_EQ(pattern_->GetIsHaveToolBar(), false);
    auto focusAlgorithmFalse = pagePattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(focusAlgorithmFalse.getNextFocusNode, nullptr);
}

/**
 * @tc.name: FocusEventTest002
 * @tc.desc: Test ToolBarRowPattern GetScopeFocusAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModelToolBarTestNg, FocusEventTest002, TestSize.Level1)
{
    CreateContainerModal();
    ASSERT_NE(pattern_, nullptr);
    auto toolBarRow = pattern_->GetCustomTitleRow();
    ASSERT_NE(toolBarRow, nullptr);
    EXPECT_EQ(toolBarRow->GetTag(), V2::ROW_ETS_TAG);
    auto toolBarRowPattern = toolBarRow->GetPattern<ToolBarRowPattern>();
    ASSERT_NE(toolBarRowPattern, nullptr);

    auto focusAlgorithm = toolBarRowPattern->GetScopeFocusAlgorithm();
    ASSERT_NE(focusAlgorithm.getNextFocusNode, nullptr);
}
}