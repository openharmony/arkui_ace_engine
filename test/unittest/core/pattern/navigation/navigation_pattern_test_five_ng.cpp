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
#include <iostream>
#include <optional>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/mousestyle/mouse_style.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAVIGATION_ID1 = "Navigation1";
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";
const InspectorFilter filter;
const std::string TEST_TAG = "test";
constexpr Dimension STACK_WIDTH = 510.0_vp;
constexpr float HEIGHT = 1000.0f;
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;

RefPtr<NavigationBarTheme> CreateAndBindNavigationBarTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    return navigationTheme;
}
} // namespace

class NavigationPatternTestFiveNg : public testing::Test {
public:
    static RefPtr<DialogTheme> dialogTheme_;
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateDialogNode();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    void MockPipelineContextGetTheme();
};

void NavigationPatternTestFiveNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
{
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { width, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

void NavigationPatternTestFiveNg::MockPipelineContextGetTheme()
{
    CreateAndBindNavigationBarTheme();
}

namespace {
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == DialogTheme::TypeId()) {
        return NavigationPatternTestFiveNg::dialogTheme_;
    } else if (type == NavigationBarTheme::TypeId()) {
        return NavigationPatternTestFiveNg::navigationBarTheme_;
    } else {
        return nullptr;
    }
}
} // namespace

RefPtr<DialogTheme> NavigationPatternTestFiveNg::dialogTheme_ = nullptr;
RefPtr<NavigationBarTheme> NavigationPatternTestFiveNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestFiveNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestFiveNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> NavigationPatternTestFiveNg::CreateDialogNode()
{
    auto contentNode = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    DialogProperties dialogProperties {
        .title = "Title",
        .content = "Content",
        .width = 300,
        .height = 200,
    };
    return DialogView::CreateDialogNode(dialogProperties, contentNode);
}

/**
 * @tc.name: NavigationToolBarManager_001
 * @tc.desc: Test ToolbarManager SetToolBarChangeCallback and SetModifyDoneCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NavigationToolBarManager_001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolBarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolBarManager, nullptr);

    int32_t modifyDoneCallbackCount = 0;
    int32_t toolBarChangeCallback = 0;
    toolBarManager->SetModifyDoneCallback([&modifyDoneCallbackCount]() {
        modifyDoneCallbackCount++;
    });
    toolBarManager->SetToolBarChangeCallback([&toolBarChangeCallback]() {
        toolBarChangeCallback++;
    });

    // init SetUsrNavigationMode:SPLIT, expect run callback after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitToolBarManager();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    ASSERT_EQ(modifyDoneCallbackCount, 1);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    NavigationPatternTestFiveNg::RunMeasureAndLayout(layoutWrapper);

    ASSERT_EQ(modifyDoneCallbackCount, 1);
    ASSERT_EQ(toolBarChangeCallback, 4);
}

/**
 * @tc.name: NavigationToolBarManager_002
 * @tc.desc: Test ToolbarManager SetToolBarChangeCallback and SetModifyDoneCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NavigationToolBarManager_002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolBarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolBarManager, nullptr);

    // init SetUsrNavigationMode:SPLIT, expect run callback after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitToolBarManager();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    NavigationPatternTestFiveNg::RunMeasureAndLayout(layoutWrapper);

    // NavBar | Divider | NavDest
    // 240    | 1       | 239    = 480
    auto navBarInfo = toolBarManager->GetNavBarInfo();
    ASSERT_TRUE(navBarInfo.isShow);
    ASSERT_EQ(navBarInfo.width, 240);
    auto navDestInfo = toolBarManager->GetNavDestInfo();
    ASSERT_TRUE(navDestInfo.isShow);
    ASSERT_EQ(navDestInfo.width, 239);
    ASSERT_TRUE(toolBarManager->HasNavBar());
    ASSERT_TRUE(toolBarManager->HasNavDest());
}

/**
 * @tc.name: NavigationToolBarManager_003
 * @tc.desc: Test ToolbarManager SetToolBarChangeCallback and SetModifyDoneCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NavigationToolBarManager_003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolBarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolBarManager, nullptr);

    int32_t toolBarChangeCallback = 0;
    toolBarManager->SetToolBarChangeCallback([&toolBarChangeCallback]() {
        toolBarChangeCallback++;
    });

    // init SetUsrNavigationMode:SPLIT, expect run callback after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitToolBarManager();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    NavigationPatternTestFiveNg::RunMeasureAndLayout(layoutWrapper);

    pattern->HandleDragUpdate(16);
    ASSERT_EQ(toolBarChangeCallback, 4);
    auto navDividerInfo = toolBarManager->GetNavBarDividerInfo();
    ASSERT_EQ(navDividerInfo.width, 1);
}
} // namespace OHOS::Ace::NG