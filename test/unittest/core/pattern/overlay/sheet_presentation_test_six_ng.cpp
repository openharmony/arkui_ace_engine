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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

class SheetPresentationTestSixNg : public testing::Test {
public:
    static RefPtr<SheetTheme> sheetTheme_;
    static void SetUpTestCase();
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
};

RefPtr<SheetTheme> SheetPresentationTestSixNg::sheetTheme_ = nullptr;

void SheetPresentationTestSixNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    sheetTheme_ = AceType::MakeRefPtr<SheetTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPresentationTestSixNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetPresentationTestSixNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
{
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = sheetType;
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->sheetThemeType_ = "popup";
    Rect windowRect = { 0.0f, 0.0f, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx(), 0.0f };
    MockPipelineContext::SetCurrentWindowRect(windowRect);
    sheetPattern->sheetKey_.hasValidTargetNode = true;
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "popup";
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    SheetPresentationTestSixNg::SetSheetTheme(sheetTheme);
}

void SheetPresentationTestSixNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme.Upgrade();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow011
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                       sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *                     if (LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()))
 *                     if (sheetStyle.sheetType.has_value())
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager = nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = fasle
 *                      LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = false
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = true
 *                      !sheetKey_.hasValidTargetNode = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, ComputeSheetTypeInSubWindow011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 128,
        AceType::MakeRefPtr<SheetPresentationPattern>(228, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    
    /**
     * @tc.steps: step2. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);

    /**
     * @tc.steps: step3. create container.
     */
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);

    /**
     * @tc.steps: step4. init mainWindowContext and displayWindowRectInfo.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->windowManager_ = nullptr;
    ASSERT_EQ(pipelineContext->windowManager_, nullptr);
    Rect displayWindowRectInfo (0.0f, 0.0f, 1800.0f, 1020.0f);
    pipelineContext->SetDisplayWindowRectInfo(displayWindowRectInfo);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. set isUIExtensionWindow.
     */
    mockContainer->SetIsUIExtensionWindow(false);

    /**
     * @tc.steps: step6. set sheetStyle.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step7. set sheetKey_.
     */
    sheetPattern->sheetKey_.hasValidTargetNode = false;

    /**
     * @tc.steps: step8. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_CENTER);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow012
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                       sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *                     if (LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()))
 *                     if (sheetStyle.sheetType.has_value())
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager = nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = fasle
 *                      LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = false
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = false
 *                      !sheetKey_.hasValidTargetNode = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, ComputeSheetTypeInSubWindow012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 129,
        AceType::MakeRefPtr<SheetPresentationPattern>(229, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    
    /**
     * @tc.steps: step2. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);

    /**
     * @tc.steps: step3. create container.
     */
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);

    /**
     * @tc.steps: step4. init mainWindowContext and displayWindowRectInfo.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->windowManager_ = nullptr;
    ASSERT_EQ(pipelineContext->windowManager_, nullptr);
    Rect displayWindowRectInfo (0.0f, 0.0f, 1800.0f, 1020.0f);
    pipelineContext->SetDisplayWindowRectInfo(displayWindowRectInfo);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. set isUIExtensionWindow.
     */
    mockContainer->SetIsUIExtensionWindow(false);

    /**
     * @tc.steps: step6. set sheetStyle.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step7. set sheetKey_.
     */
    sheetPattern->sheetKey_.hasValidTargetNode = false;

    /**
     * @tc.steps: step8. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_BOTTOM_FREE_WINDOW);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow013
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                       sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *                     if (LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()))
 *                     if (sheetStyle.sheetType.has_value())
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager = nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = fasle
 *                      LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = false
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = true
 *                      !sheetKey_.hasValidTargetNode = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, ComputeSheetTypeInSubWindow013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 130,
        AceType::MakeRefPtr<SheetPresentationPattern>(230, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    
    /**
     * @tc.steps: step2. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);

    /**
     * @tc.steps: step3. create container.
     */
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);

    /**
     * @tc.steps: step4. init mainWindowContext and displayWindowRectInfo.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->windowManager_ = nullptr;
    ASSERT_EQ(pipelineContext->windowManager_, nullptr);
    Rect displayWindowRectInfo (0.0f, 0.0f, 1800.0f, 1020.0f);
    pipelineContext->SetDisplayWindowRectInfo(displayWindowRectInfo);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. set isUIExtensionWindow.
     */
    mockContainer->SetIsUIExtensionWindow(false);

    /**
     * @tc.steps: step6. set sheetStyle.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step7. set sheetKey_.
     */
    sheetPattern->sheetKey_.hasValidTargetNode = true;

    /**
     * @tc.steps: step8. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_POPUP);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow014
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                       sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *                     if (LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()))
 *                     if (sheetStyle.sheetType.has_value())
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager = nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = fasle
 *                      LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = false
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = false
 *                      !sheetKey_.hasValidTargetNode = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, ComputeSheetTypeInSubWindow014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 130,
        AceType::MakeRefPtr<SheetPresentationPattern>(230, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    
    /**
     * @tc.steps: step2. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);

    /**
     * @tc.steps: step3. create container.
     */
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);

    /**
     * @tc.steps: step4. init mainWindowContext and displayWindowRectInfo.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->windowManager_ = nullptr;
    ASSERT_EQ(pipelineContext->windowManager_, nullptr);
    Rect displayWindowRectInfo (0.0f, 0.0f, 1800.0f, 1020.0f);
    pipelineContext->SetDisplayWindowRectInfo(displayWindowRectInfo);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. set isUIExtensionWindow.
     */
    mockContainer->SetIsUIExtensionWindow(false);

    /**
     * @tc.steps: step6. set sheetStyle.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM_OFFSET;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step7. set sheetKey_.
     */
    sheetPattern->sheetKey_.hasValidTargetNode = true;

    /**
     * @tc.steps: step8. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_BOTTOM_OFFSET);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: InitSheetTransitionAction001
 * @tc.desc: Branch:    if (IsShowInSubWindowTwoInOne())
 *           Condition: IsShowInSubWindowTwoInOne() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, InitSheetTransitionAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 131,
        AceType::MakeRefPtr<SheetPresentationPattern>(231, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetStyle.
     */
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = true;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step3. set sheetTheme.
     */
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    SheetPresentationTestSixNg::SetSheetTheme(sheetTheme);

    /**
     * @tc.steps: step4. test InitSheetTransitionAction.
     */
    float offset = 100.0;
    sheetPattern->InitSheetTransitionAction(offset);
    auto sheetContext = sheetNode->GetRenderContext();
    ASSERT_NE(sheetContext, nullptr);
    EXPECT_EQ(sheetContext->GetOpacity(), 0.0f);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: PostTask001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, PostTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 132,
        AceType::MakeRefPtr<SheetPresentationPattern>(232, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test PostTask.
     */
    const TaskExecutor::Task task;
    const std::string name;
    auto ret = sheetPattern->PostTask(task, name);
    EXPECT_EQ(ret, false);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: GetRootOffsetYToWindow001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, GetRootOffsetYToWindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 133,
        AceType::MakeRefPtr<SheetPresentationPattern>(233, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set sheetStyle.
     */
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step3. test GetRootOffsetYToWindow.
     */
    auto ret = sheetPattern->GetRootOffsetYToWindow();
    EXPECT_EQ(ret, 0.0f);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, DumpAdvanceInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 134,
        AceType::MakeRefPtr<SheetPresentationPattern>(234, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test DumpAdvanceInfo.
     */
    sheetPattern->DumpAdvanceInfo();
    EXPECT_NE(DumpLog::GetInstance().description_.size(), 0);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, DumpAdvanceInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 135,
        AceType::MakeRefPtr<SheetPresentationPattern>(235, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetPattern value.
     */
    sheetPattern->targetId_ = 100;
    sheetPattern->targetTag_ = "targetTag";

    /**
     * @tc.steps: step3.set sheetType.
     */
    SheetPresentationTestSixNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);

    /**
     * @tc.steps: step4. test DumpAdvanceInfo.
     */
    auto json = JsonUtil::Create(true);
    sheetPattern->DumpAdvanceInfo(json);
    EXPECT_EQ(sheetPattern->sheetType_, SheetType::SHEET_BOTTOM);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetMainPipeline001
 * @tc.desc: Branch:    if (sheetStyle.instanceId.has_value())
 *           Condition: sheetStyle.instanceId.has_value() = false
 *                      sheetStyle.instanceId.has_value() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, GetSheetMainPipeline001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 136,
        AceType::MakeRefPtr<SheetPresentationPattern>(236, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test GetSheetMainPipeline instanceId.has_value() = false.
     */
    auto ret1  = sheetPattern->GetSheetMainPipeline();
    EXPECT_NE(ret1, nullptr);

    /**
     * @tc.steps: stepa3. set sheetStyle.
     */
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.instanceId = 100;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step4. create parentPipelineBase.
     */
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. test GetSheetMainPipeline instanceId.has_value() = true.
     */
    auto ret2  = sheetPattern->GetSheetMainPipeline();
    EXPECT_NE(ret2, nullptr);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: SetBottomStyleHotAreaInSubwindow001
 * @tc.desc: Branch:  if (IsShowInSubWindow() && IsSheetBottom())
 *           Condition: (IsShowInSubWindow() && IsSheetBottom()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, SetBottomStyleHotAreaInSubwindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step2. set IsShowInSubWindow true, set IsSheetBottom false.
     */
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = true;
    sheetNode->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    SheetPresentationTestSixNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test SetBottomStyleHotAreaInSubwindow.
     */
    sheetPattern->SetBottomStyleHotAreaInSubwindow();
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_CENTER);
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), true);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: SetBottomStyleHotAreaInSubwindow002
 * @tc.desc: Branch:  if (IsShowInSubWindow() && IsSheetBottom())
 *           Condition: (IsShowInSubWindow() && IsSheetBottom()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, SetBottomStyleHotAreaInSubwindow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step2. set IsShowInSubWindow true, set IsSheetBottom true.
     */
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = true;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test SetBottomStyleHotAreaInSubwindow.
     */
    sheetPattern->SetBottomStyleHotAreaInSubwindow();
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM);
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), true);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: SetBottomStyleHotAreaInSubwindow003
 * @tc.desc: Branch:  if (IsShowInSubWindow() && IsSheetBottom())
 *           Condition: (IsShowInSubWindow() && IsSheetBottom()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, SetBottomStyleHotAreaInSubwindow003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step2. set IsShowInSubWindow false, set IsSheetBottom false.
     */
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = false;
    sheetNode->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    SheetPresentationTestSixNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test SetBottomStyleHotAreaInSubwindow.
     */
    sheetPattern->SetBottomStyleHotAreaInSubwindow();
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_CENTER);
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), false);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: SetBottomStyleHotAreaInSubwindow004
 * @tc.desc: Branch:  if (IsShowInSubWindow() && IsSheetBottom())
 *           Condition: (IsShowInSubWindow() && IsSheetBottom()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, SetBottomStyleHotAreaInSubwindow004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step2. set IsShowInSubWindow false, set IsSheetBottom true.
     */
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = false;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step3. test SetBottomStyleHotAreaInSubwindow.
     */
    sheetPattern->SetBottomStyleHotAreaInSubwindow();
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM);
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), false);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Branch:  if (IsShowInSubWindow())
 *           Condition: (IsShowInSubWindow() && IsSheetBottom()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, OnAttachToFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);
    /**
     * @tc.steps: step2. set IsShowInSubWindow true
     */
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = true;
    layoutProperty->propSheetStyle_ = sheetStyle;
    /**
     * @tc.steps: step3. test OnAttachToFrameNode
     */
    sheetPattern->OnAttachToFrameNode();
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), true);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetBorderWidth001
 * @tc.desc: Branch:  if (sheetStyle.borderWidth.has_value())
 *           Condition: (sheetStyle.borderWidth.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, SetSheetBorderWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. test SetSheetBorderWidth.
     */
    SheetStyle sheetStyle;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->SetSheetBorderWidth();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);
    SheetPresentationTestSixNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetBorderWidth002
 * @tc.desc: Branch:  if (sheetStyle.borderWidth.has_value())
 *           Condition: (sheetStyle.borderWidth.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSixNg, SetSheetBorderWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSixNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);

    /**
     * @tc.steps: step2. create sheet object.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);

    /**
     * @tc.steps: step3. set borderWidth.
     */
    SheetStyle sheetStyle;
    sheetStyle.borderWidth = { 1.0_vp, 1.0_vp, 1.0_vp, 0.0_vp };
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test SetSheetBorderWidth.
     */
    sheetPattern->SetSheetBorderWidth();
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), true);
    SheetPresentationTestSixNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG