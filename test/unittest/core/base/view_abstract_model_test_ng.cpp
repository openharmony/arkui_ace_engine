/*
 * Copyright (c) 2024 iSoftStone Information Technology (Group) Co.,Ltd.
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
#define protected public
#define private public

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#undef private
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    ViewAbstractModelNG viewAbstractModelNG;
    RefPtr<MockTaskExecutor> MOCK_TASK_EXECUTOR;
    int32_t flag = 0;
}; // namespace

class ViewAbstractModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestCase();
};

void ViewAbstractModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}
void ViewAbstractModelTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ViewAbstractModelTestNg001
 * @tc.desc: Test the GetSheetContext of View_Abstract_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build sheetStyle instanceId is empty.
     */
    SheetStyle style;
    auto testContext1 = viewAbstractModelNG.GetSheetContext(style);
    EXPECT_NE(testContext1, nullptr);

    /**
     * @tc.steps: step2. Build sheetStyle instanceId is 100001.
     */
    style.instanceId = 100001;
    /**
     * @tc.steps: step3. Build an AceEngine.
     */
    AceEngine& aceEngine = AceEngine::Get();

    /**
     * @tc.steps: step4. Add Container.
     * @tc.expected: Add Container success.
     */
    aceEngine.AddContainer(style.instanceId.value(), MockContainer::container_);
    EXPECT_NE(aceEngine.GetContainer(style.instanceId.value()), nullptr);
    /**
     * @tc.expected: context is not nullptr.
     */
    auto testContext2 = viewAbstractModelNG.GetSheetContext(style);
    EXPECT_NE(testContext2, nullptr);
}

/**
 * @tc.name: BindSheetShowInPageTest1
 * @tc.desc: Test the composition of sheet parent nodes when page will show in page
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, BindSheetShowInPageTest1, TestSize.Level1)
{
    // pagelevel Node is Page Node
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    targetNode->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    NG::SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    viewAbstractModelNG.BindSheet(false, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto pagePatern = pageNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePatern, nullptr);
    auto overlay1 = pagePatern->GetOverlayManager();
    EXPECT_EQ(overlay1, nullptr);
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto overlay2 = pagePatern->GetOverlayManager();
    EXPECT_NE(overlay2, nullptr);
    EXPECT_FALSE(!targetNode->RootNodeIsPage());
    EXPECT_EQ(targetNode->GetRootNodeId(), pageNode->GetId());
}

/**
 * @tc.name: BindSheetShowInPageTest2
 * @tc.desc: Test the composition of sheet parent nodes when page will show in navDestination page
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, BindSheetShowInPageTest2, TestSize.Level1)
{
    // pagelevel Node is navDestination Node
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto navDestinaion = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavDestinationPattern>());
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    targetNode->MountToParent(navDestinaion);
    navDestinaion->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    NG::SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto navPatern = navDestinaion->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navPatern, nullptr);
    auto overlay = navPatern->GetOverlayManager();
    EXPECT_NE(overlay, nullptr);
    EXPECT_TRUE(!targetNode->RootNodeIsPage());
    EXPECT_EQ(targetNode->GetRootNodeId(), navDestinaion->GetId());
    EXPECT_TRUE(!pageNode->RootNodeIsPage());
    EXPECT_EQ(pageNode->GetRootNodeId(), targetNode->GetRootNodeId());
}

/**
 * @tc.name: GetOverlayFromPageTest
 * @tc.desc: set sheetStyle.showInPage.value_or(false) to endter FindPageNodeOverlay
 *           and targetNode->GetRootNodeId() > 0 to enter GetOverlayFromPage
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, GetOverlayFromPageTest, TestSize.Level1)
{
    // pagelevel Node is navDestination Node
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto navDestinaion = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavDestinationPattern>());
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    targetNode->MountToParent(navDestinaion);
    targetNode->SetRootNodeId(1);
    navDestinaion->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    NG::SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    sheetStyle.showInPage = false;
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    sheetStyle.showInPage = false;
    viewAbstractModelNG.BindSheet(false, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

    auto navPatern = navDestinaion->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navPatern, nullptr);
    auto overlay = navPatern->GetOverlayManager();
    EXPECT_EQ(overlay, nullptr);
    EXPECT_FALSE(!targetNode->RootNodeIsPage());
    EXPECT_EQ(targetNode->GetRootNodeId(), 1);
    EXPECT_FALSE(!pageNode->RootNodeIsPage());
    EXPECT_NE(pageNode->GetRootNodeId(), targetNode->GetRootNodeId());
}

/**
 * @tc.name: BindContextMenuTest
 * @tc.desc: Test the BindContextMenu method with various parameters and conditions
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, BindContextMenuTest, TestSize.Level1)
{
    std::function<void()> buildFunc = nullptr;
    std::function<void()> previewBuildFunc = nullptr;
    MenuParam menuParam;

    /**
     * @tc.steps: subwindow is null and does not enter BindContextMenuSingle.
     */
    SubwindowManager::GetInstance()->RemoveSubwindow(Container::CurrentId());
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    ASSERT_EQ(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: entering BindContextMenuSingle with subwindow null, menuParam.isShow true, and buildFunc not null.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = true;
    buildFunc = []() {};
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    ASSERT_EQ(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: entering BindContextMenuSingle with subwindow null, menuParam.isShow true, and buildFunc null.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = true;
    buildFunc = nullptr;
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    ASSERT_EQ(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: BindContextMenuSingle with subwindow null, menuParam.isShow false, and buildFunc not null.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = false;
    buildFunc = []() {};
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    ASSERT_EQ(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: entering BindContextMenuSingle with subwindow null, menuParam.isShow false, and buildFunc null.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = false;
    buildFunc = nullptr;
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    ASSERT_EQ(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: subwindow is null and does not enter BindContextMenuSingle, with type == ResponseType::RIGHT_CLICK.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::NORMAL_TYPE;
    viewAbstractModelNG.BindContextMenu(ResponseType::RIGHT_CLICK, buildFunc, menuParam, previewBuildFunc);
    ASSERT_EQ(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: subwindow is null and does not enter BindContextMenuSingle, with type == ResponseType::LONG_PRESS.
     */
    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam, previewBuildFunc);
    ASSERT_EQ(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);

    /**
     * @tc.steps: subwindow is not null.
     */
    auto subwindow = Subwindow::CreateSubwindow(Container::CurrentId());
    SubwindowManager::GetInstance()->AddSubwindow(Container::CurrentId(), subwindow);
    viewAbstractModelNG.BindContextMenu(ResponseType::LONG_PRESS, buildFunc, menuParam, previewBuildFunc);
    ASSERT_NE(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg003
 * @tc.desc: Test the BindDragWithContextMenuParams of View_Abstract_model_ng
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg003, TestSize.Level1)
{
    MenuParam menuParam;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(pageNode, nullptr);
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(column, nullptr);
    auto navDestinaion = FrameNode::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinaion, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(targetNode, nullptr);
    targetNode->MountToParent(navDestinaion);
    targetNode->SetRootNodeId(1);
    navDestinaion->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    viewAbstractModelNG.BindDragWithContextMenuParams(menuParam);
    EXPECT_NE(pageNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg004
 * @tc.desc: Test the BindMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg004, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);

    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    menuParam.isShow = true;
    menuParam.isShowInSubWindow = true;
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    menuParam.isShowInSubWindow = false;
    buildFunc = []() { flag++; };
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    params.push_back(OptionParam());
    menuParam.setShow = true;
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg005
 * @tc.desc: Test the BindMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg005, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto menuNode = overlayManager->GetMenuNode(1);
    if (menuNode) {
        auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
        if (wrapperPattern) {
            wrapperPattern->SetMenuStatus(MenuStatus::SHOW);
        }
    }
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    menuParam.isShow = true;
    menuParam.isShowInSubWindow = true;
    menuParam.hasTransitionEffect = false;
    menuParam.setShow = true;
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    menuParam.isShowInSubWindow = false;
    menuParam.hasTransitionEffect = true;
    menuParam.isShow = false;
    buildFunc = []() { flag++; };
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    params.push_back(OptionParam());
    menuParam.setShow = false;
    menuParam.isShow = false;
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    if (menuNode) {
        auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
        if (wrapperPattern) {
            wrapperPattern->SetMenuStatus(MenuStatus::INIT);
        }
    }
    viewAbstractModelNG.BindMenu(std::move(params), std::move(buildFunc), menuParam);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg006
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg006, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    buildFunc = []() { flag++; };
    params.push_back(OptionParam());
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg007
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg007, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    menuParam.isShowInSubWindow = false;
    buildFunc = []() { flag++; };
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg008
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg008, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 9, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    menuParam.isShowInSubWindow = false;
    menuParam.hasTransitionEffect = true;
    menuParam.isShow = false;
    buildFunc = []() { flag++; };
    params.push_back(OptionParam());
    menuParam.setShow = false;
    menuParam.isShow = false;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg009
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg009, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 6, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::LONG_PRESS;
    menuParam.isShowInSubWindow = false;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    buildFunc = []() { flag++; };
    menuParam.isShowHoverImage = false;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    menuParam.previewMode = MenuPreviewMode::NONE;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg010
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg010, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 6, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::LONG_PRESS;
    menuParam.isShowInSubWindow = false;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    menuParam.previewMode = MenuPreviewMode::NONE;
    buildFunc = []() { flag++; };
    menuParam.isShowHoverImage = true;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg011
 * @tc.desc: Test the BindContextMenuSingle and CreateCustomMenuWithPreview
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg011, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 6, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::LONG_PRESS;
    menuParam.isShowInSubWindow = false;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    buildFunc = []() { flag++; };
    menuParam.isShowHoverImage = false;
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = true;

    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    menuParam.isShow = false;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    menuParam.isShow = true;
    buildFunc = nullptr;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg012
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg012, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 9, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    menuParam.isShowInSubWindow = false;
    menuParam.hasTransitionEffect = true;
    menuParam.isShow = false;
    buildFunc = []() { flag++; };
    params.push_back(OptionParam());
    menuParam.setShow = false;
    menuParam.isShow = false;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    auto targetNode1 = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    for (const auto& destroyCallback : targetNode1->destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg013
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg013, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 9, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    menuParam.isShowInSubWindow = false;
    menuParam.hasTransitionEffect = true;
    menuParam.isShow = false;
    buildFunc = []() { flag++; };
    params.push_back(OptionParam());
    menuParam.setShow = false;
    menuParam.isShow = false;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    auto targetNode1 = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    for (const auto& destroyCallback : targetNode1->destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg014
 * @tc.desc: Test the composition of sheet parent nodes when page will show in page
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg014, TestSize.Level1)
{
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(pageNode, nullptr);
    auto column = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(column, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(targetNode, nullptr);
    targetNode->MountToParent(column);
    column->MountToParent(pageNode);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    NG::SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    viewAbstractModelNG.BindSheet(false, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto pagePatern = pageNode->GetPattern<PagePattern>();
    ASSERT_NE(pagePatern, nullptr);
    auto overlay1 = pagePatern->GetOverlayManager();
    EXPECT_EQ(overlay1, nullptr);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    sheetStyle.showInPage = false;
    viewAbstractModelNG.BindSheet(true, nullptr, nullptr, nullptr, sheetStyle, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    auto targetNode1 = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    for (const auto& destroyCallback : targetNode1->destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    auto overlay2 = pagePatern->GetOverlayManager();
    EXPECT_NE(overlay2, nullptr);
    EXPECT_FALSE(!targetNode->RootNodeIsPage());
    EXPECT_EQ(targetNode->GetRootNodeId(), pageNode->GetId());
}

/**
 * @tc.name: ViewAbstractModelTestNg015
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg015, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> flagFunc = []() { flag++; };
    std::vector<NG::OptionParam> params = {};
    std::function<void()> buildFunc;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    buildFunc = []() { flag++; };
    params.push_back(OptionParam());
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto targetId = targetNode->GetId();
    auto menu =
        FrameNode::CreateFrameNode("targetNode", targetId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId), false);
    overlayManager->menuMap_[targetId] = menu;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg016
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg016, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> buildFunc = []() { flag++; };
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::RIGHT_CLICK;
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto targetId = targetNode->GetId();
    auto menu =
        FrameNode::CreateFrameNode("targetNode", targetId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId), false);
    overlayManager->menuMap_[targetId] = menu;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    auto inputHub = targetNode->GetOrCreateInputEventHub();
    auto mouseEventActuator_ = inputHub->mouseEventActuator_;
    auto Events = mouseEventActuator_->inputEvents_;
    MouseInfo mouseInfo;
    for (const auto& callback : Events) {
        (*callback)(mouseInfo);
    }
    mouseInfo.button_ = MouseButton::RIGHT_BUTTON;
    for (const auto& callback : Events) {
        (*callback)(mouseInfo);
    }
    mouseInfo.action_ = MouseAction::RELEASE;
    for (const auto& callback : Events) {
        (*callback)(mouseInfo);
    }
    mouseInfo.button_ = MouseButton::LEFT_BUTTON;
    for (const auto& callback : Events) {
        (*callback)(mouseInfo);
    }
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg017
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg017, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> buildFunc = []() { flag++; };
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::LONG_PRESS;
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto targetId = targetNode->GetId();
    auto menu =
        FrameNode::CreateFrameNode("targetNode", targetId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId), false);
    overlayManager->menuMap_[targetId] = menu;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    auto hub = targetNode->GetOrCreateGestureEventHub();
    auto longPressEventActuator = hub->longPressEventActuator_;
    auto Events = longPressEventActuator->longPressEvent_;
    GestureEvent info;
    const auto& callback = Events;
    (*callback)(info);
    auto pipelineContext1 = NG::PipelineContext::GetCurrentContext();
    auto dragDropManager = pipelineContext1->GetDragDropManager();
    dragDropManager->dragDropState_ = DragDropMgrState::DRAGGING;
    (*callback)(info);
    dragDropManager->dragDropState_ = DragDropMgrState::ABOUT_TO_PREVIEW;
    (*callback)(info);
    dragDropManager->dragDropState_ = DragDropMgrState::IDLE;
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg018
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg018, TestSize.Level1)
{
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto container = Container::Current();
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    std::function<void()> buildFunc = []() { flag++; };
    MenuParam menuParam;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    menuParam.isShowHoverImage = true;
    std::function<void()> previewBuildFunc = nullptr;
    auto type = ResponseType::LONG_PRESS;
    auto targetNode = AceType::Claim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto targetId = targetNode->GetId();
    auto menu =
        FrameNode::CreateFrameNode("targetNode", targetId, AceType::MakeRefPtr<MenuWrapperPattern>(targetId), false);
    overlayManager->menuMap_[targetId] = menu;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    auto hub = targetNode->GetOrCreateGestureEventHub();
    auto longPressEventActuator = hub->longPressEventActuator_;
    auto Events = longPressEventActuator->longPressEvent_;
    GestureEvent info;
    const auto& callback = Events;
    (*callback)(info);
    auto focusHub = targetNode->GetOrCreateFocusHub();
    KeyEvent event;
    focusHub->ProcessOnKeyEventInternal(event);
    event.action = KeyAction::DOWN;
    focusHub->ProcessOnKeyEventInternal(event);
    event.keyIntention = KeyIntention::INTENTION_MENU;
    focusHub->ProcessOnKeyEventInternal(event);
    event.code = KeyCode::KEY_MENU;
    menuParam.placement = Placement::BOTTOM_LEFT;
    viewAbstractModelNG.BindContextMenu(type, buildFunc, menuParam, previewBuildFunc);
    focusHub->ProcessOnKeyEventInternal(event);
    EXPECT_NE(mainNode, nullptr);
}

/**
 * @tc.name: ViewAbstractModelTestNg019
 * @tc.desc: Test the BindBackground
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create main frame node and push into view abstract.
     */
    const RefPtr<FrameNode> mainNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(mainNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(mainNode);

    /**
     * @tc.steps: step2. init theme, pipeline and container.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto containerId = pipelineContext->GetInstanceId();
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);

    /**
     * @tc.steps: step3. init background build func and alignment.
     * @tc.expected: background function and alignment is successfully set.
     */
    auto mainFrameNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    Alignment alignment = Alignment::CENTER;
    auto buildFunc = [mainFrameNode] () {
        flag++;
    };
    viewAbstractModelNG.BindBackground(std::move(buildFunc), alignment);
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(targetNode, nullptr);
    auto renderContext = targetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto backgroundAlign = renderContext->GetBackgroundAlign().value_or(Alignment::BOTTOM_CENTER);
    ASSERT_EQ(backgroundAlign, alignment);

    /**
     * @tc.steps: step4. update background build func and alignment.
     * @tc.expected: background function and alignment is successfully set.
     */
    alignment = Alignment::TOP_CENTER;
    viewAbstractModelNG.BindBackground(std::move(buildFunc), alignment);
    backgroundAlign = renderContext->GetBackgroundAlign().value_or(Alignment::BOTTOM_CENTER);
    ASSERT_EQ(backgroundAlign, alignment);
}

/**
 * @tc.name: ViewAbstractModelTestNg020
 * @tc.desc: Test the DismissSheet
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. setup environment.
     */
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageMainNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stageMainNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageMainNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step2. create target node.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step3. create sheetNode, get sheetPattern.
     */
    bool isShow = true;
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_RETURN(frameNode, nullptr);
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        CHECK_NULL_RETURN(childFrameNode, nullptr);
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_RETURN(frameNode, nullptr);
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(childFrameNode, nullptr);
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    SheetStyle sheetStyle;
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());


    /**
     * @tc.steps: step4. set dismiss sheet id.
     */
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto nodeId = topSheetNode->GetId();
    SheetManager::GetInstance().SetDismissSheet(nodeId);
    viewAbstractModelNG.DismissSheet();
}

/**
 * @tc.name: ViewAbstractModelTestNg021
 * @tc.desc: Test the SheetSpringBack
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. setup environment.
     */
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageMainNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stageMainNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageMainNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step2. create target node.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step3. create sheetNode, get sheetPattern.
     */
    bool isShow = true;
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_RETURN(frameNode, nullptr);
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        CHECK_NULL_RETURN(childFrameNode, nullptr);
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_RETURN(frameNode, nullptr);
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(childFrameNode, nullptr);
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    SheetStyle sheetStyle;
    if (!sheetStyle.sheetHeight.sheetMode.has_value()) {
        sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    }
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());


    /**
     * @tc.steps: step4. set dismiss sheet id.
     */
    auto topSheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topSheetNode, nullptr);
    auto nodeId = topSheetNode->GetId();
    SheetManager::GetInstance().SetDismissSheet(nodeId);
    viewAbstractModelNG.SheetSpringBack();
}

/**
 * @tc.name: ViewAbstractModelTestNg022
 * @tc.desc: Test the DismissContentCover
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. setup environment.
     */
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageMainNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stageMainNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageMainNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step3. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_RETURN(frameNode, nullptr);
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        CHECK_NULL_RETURN(childFrameNode, nullptr);
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step4. create modal node and call DismissContentCover.
     * @tc.expected: destroy modal page successfully
     */
    ModalStyle modalStyle;
    bool isShow = true;
    // auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    auto targetId = topModalPattern->GetTargetId();
    overlayManager->SetDismissTarget(DismissTarget(targetId));
    viewAbstractModelNG.DismissContentCover();
    EXPECT_TRUE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: ViewAbstractModelTestNg023
 * @tc.desc: Test the BindContentCover
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelTestNg, ViewAbstractModelTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    ASSERT_NE(stageNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. setup environment.
     */
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageMainNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stageMainNode, nullptr);
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageMainNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    
    /**
     * @tc.steps: step3. create modal page node.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_COMPONENT_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_RETURN(frameNode, nullptr);
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        CHECK_NULL_RETURN(childFrameNode, nullptr);
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    /**
     * @tc.steps: step4. create modal node and get modal node, get pattern.
     * @tc.expected: related flag is false.
     */
    ModalStyle modalStyle;
    bool isShow = true;
    std::function<void(int32_t info)> onWillDismiss = [](int32_t info) {};
    RefPtr<NG::ChainedTransitionEffect> effect = AceType::MakeRefPtr<NG::ChainedOpacityEffect>(1.0);
    // auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto container = MockContainer::Current();
    ASSERT_NE(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr, nullptr,
        nullptr, ContentCoverParam(), targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto topModalNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(topModalNode, nullptr);
    auto topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    ASSERT_NE(topModalPattern, nullptr);
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), false);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), false);

    /**
     * @tc.steps: step5. create modal node and call BindContentCover.
     * @tc.expected: related flag is true.
     */
    ContentCoverParam contentCoverParam;
    contentCoverParam.onWillDismiss = onWillDismiss;
    contentCoverParam.transitionEffect = std::move(effect);
    viewAbstractModelNG.BindContentCover(isShow, nullptr, std::move(builderFunc), modalStyle, nullptr, nullptr,
        nullptr, nullptr, contentCoverParam);
    topModalNode = overlayManager->modalStack_.top().Upgrade();
    topModalPattern = topModalNode->GetPattern<ModalPresentationPattern>();
    EXPECT_EQ(topModalPattern->HasOnWillDismiss(), true);
    EXPECT_EQ(topModalPattern->HasTransitionEffect(), true);
}
} // namespace OHOS::Ace::NG