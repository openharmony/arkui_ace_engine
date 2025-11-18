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
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
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

class SheetPresentationTestSevenNg : public testing::Test {
public:
    static RefPtr<SheetTheme> sheetTheme_;
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
};

RefPtr<SheetTheme> SheetPresentationTestSevenNg::sheetTheme_ = nullptr;

void SheetPresentationTestSevenNg::SetUpTestCase()
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

void SheetPresentationTestSevenNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetPresentationTestSevenNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
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

void SheetPresentationTestSevenNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
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
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
}

/**
 * @tc.name: UpdateSheetWhenSheetTypeChanged001
 * @tc.desc: Branch:   if (sheetType_ != sheetType)
 *                     if (sheetType_ == SheetType::SHEET_POPUP)
 *           Condition: sheetType_ != sheetType = true
 *                      step2：sheetType_ == SheetType::SHEET_POPUP  = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, UpdateSheetWhenSheetTypeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 2,
        AceType::MakeRefPtr<SheetPresentationPattern>(102, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. sheetType_ != sheetType, test UpdateSheetWhenSheetTypeChanged.
     */
    SheetStyle sheetStyle;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->typeChanged_ = false;
    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    sheetPattern->UpdateSheetWhenSheetTypeChanged();
    EXPECT_EQ(sheetPattern->typeChanged_, true);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: IsWaterfallWindowMode001
 * @tc.desc: Branch:   if (!SystemProperties::IsSuperFoldDisplayDevice())
 *           Condition: !SystemProperties::IsSuperFoldDisplayDevice() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, IsWaterfallWindowMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 3,
        AceType::MakeRefPtr<SheetPresentationPattern>(103, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    
    /**
     * @tc.steps: step2. test IsWaterfallWindowMode.
     */
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;

    auto ret = sheetPattern->IsWaterfallWindowMode();
    EXPECT_EQ(ret, false);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: IsWaterfallWindowMode002
 * @tc.desc: Branch:   if (!SystemProperties::IsSuperFoldDisplayDevice())
 *                     if (!container)
 *           Condition: !SystemProperties::IsSuperFoldDisplayDevice() = false
 *                      container = nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, IsWaterfallWindowMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 4,
        AceType::MakeRefPtr<SheetPresentationPattern>(104, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    
    /**
     * @tc.steps: step2. test IsWaterfallWindowMode.
     */
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    MockContainer::TearDown();
    auto ret = sheetPattern->IsWaterfallWindowMode();
    EXPECT_EQ(ret, false);
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: IsWaterfallWindowMode003
 * @tc.desc: Branch:   if (!SystemProperties::IsSuperFoldDisplayDevice())
 *                     if (!container)
 *                     if (container->IsSubContainer())
 *           Condition: !SystemProperties::IsSuperFoldDisplayDevice() = false
 *                      container = nullptr
 *                      container->IsSubContainer() = false
 *                      container->IsSubContainer() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, IsWaterfallWindowMode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 5,
        AceType::MakeRefPtr<SheetPresentationPattern>(105, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    
    /**
     * @tc.steps: step2. set SubContainer.
     */
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto mockContainer = MockContainer::Current();
    mockContainer->isSubContainer_ = true;

    /**
     * @tc.steps: step3. GetContainer(instanceId) = nullptr, test IsWaterfallWindowMode.
     */
    AceEngine::Get().containerMap_.clear();
    AceEngine::Get().containerMap_.emplace(12345, mockContainer);
    auto ret1 = sheetPattern->IsWaterfallWindowMode();
    EXPECT_EQ(ret1, false);

    /**
     * @tc.steps: step4. GetContainer(instanceId) != nullptr, test IsWaterfallWindowMode.
     */
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.instanceId = 1;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5 test IsWaterfallWindowMode.
     */
    auto ret2 = sheetPattern->IsWaterfallWindowMode();
    EXPECT_EQ(ret2, false);

    MockSystemProperties::g_isSuperFoldDisplayDevice = false;
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetArrowOffsetByPlacement001
 * @tc.desc: Branch:   if (!IsCurSheetNeedHalfFoldHover())
 *           Condition: !IsCurSheetNeedHalfFoldHover() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetArrowOffsetByPlacement001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 7,
        AceType::MakeRefPtr<SheetPresentationPattern>(107, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. IsCurSheetNeedHalfFoldHover = false, test FireHoverModeChangeCallback.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    sheetPattern->FireHoverModeChangeCallback();
    EXPECT_EQ(pipelineContext->IsHalfFoldHoverStatus(), false);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetArrowOffsetByPlacement002
 * @tc.desc: Branch:   if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN))
 *                     if (!showArrow_ || finalPlacement_ == Placement::NONE)
 *           Condition: !Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) = false
 *                      (!showArrow_ || finalPlacement_ == Placement::NONE) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetArrowOffsetByPlacement002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 9,
        AceType::MakeRefPtr<SheetPresentationPattern>(109, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetPopupInfo_
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));

    /**
     * @tc.steps: step3. set sheetPopupInfo_ and showArrow_
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::NONE;
    sheetPattern->showArrow_ = false;

    /**
     * @tc.steps: step4. test GetArrowOffsetByPlacement
     */
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetArrowOffsetByPlacement003
 * @tc.desc: Branch:   if (!showArrow_ || finalPlacement_ == Placement::NONE)
 *                     switch (finalPlacement_)
 *           Condition: (!showArrow_ || finalPlacement_ == Placement::NONE) = false
 *                      finalPlacement_ = Placement::BOTTOM_LEFT
 *                      finalPlacement_ = Placement::BOTTOM_RIGHT
 *                      finalPlacement_ = Placement::BOTTOM
 *                      finalPlacement_ = Placement::TOP_LEFT
 *                      finalPlacement_ = Placement::TOP_RIGHT
 *                      finalPlacement_ = Placement::TOP
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetArrowOffsetByPlacement003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 10,
        AceType::MakeRefPtr<SheetPresentationPattern>(110, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetPopupInfo_
     */
    sheetNode->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY);

    /**
     * @tc.steps: step3. set sheetPopupInfo_ and showArrow_
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetPattern->showArrow_ = true;

    /**
     * @tc.steps: step4.finalPlacement_ = Placement::BOTTOM_LEFT, test GetArrowOffsetByPlacement
     */
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetPattern->sheetPopupInfo_.arrowOffsetX = 100;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetX(), 100);

    /**
     * @tc.steps: step5.finalPlacement_ = Placement::BOTTOM_RIGHT, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;
    sheetPattern->sheetPopupInfo_.arrowOffsetX = 200;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetX(), 200);

    /**
     * @tc.steps: step6.finalPlacement_ = Placement::BOTTOM, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;
    sheetPattern->sheetPopupInfo_.arrowOffsetX = 300;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetX(), 300);

    /**
     * @tc.steps: step7.finalPlacement_ = Placement::TOP_LEFT, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT;
    sheetPattern->sheetPopupInfo_.arrowOffsetX = 400;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetX(), 400);

    /**
     * @tc.steps: step8.finalPlacement_ = Placement::TOP_RIGHT, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT;
    sheetPattern->sheetPopupInfo_.arrowOffsetX = 500;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetX(), 500);

    /**
     * @tc.steps: step9.finalPlacement_ = Placement::TOP, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP;
    sheetPattern->sheetPopupInfo_.arrowOffsetX = 600;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetX(), 600);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetArrowOffsetByPlacement004
 * @tc.desc: Branch:   if (!showArrow_ || finalPlacement_ == Placement::NONE)
 *                     switch (finalPlacement_)
 *           Condition: (!showArrow_ || finalPlacement_ == Placement::NONE) = false
 *                      finalPlacement_ = Placement::RIGHT_TOP
 *                      finalPlacement_ = Placement::RIGHT_BOTTOM
 *                      finalPlacement_ = Placement::RIGHT
 *                      finalPlacement_ = Placement::LEFT_TOP
 *                      finalPlacement_ = Placement::LEFT_BOTTOM
 *                      finalPlacement_ = Placement::LEFT
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetArrowOffsetByPlacement004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 17,
        AceType::MakeRefPtr<SheetPresentationPattern>(117, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetPopupInfo_
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    sheetNode->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWENTY);

    /**
     * @tc.steps: step3. set sheetPopupInfo_ and showArrow_
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;
    sheetPattern->showArrow_ = true;

    /**
     * @tc.steps: step4.finalPlacement_ = Placement::RIGHT_TOP, test GetArrowOffsetByPlacement
     */
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetPattern->sheetPopupInfo_.arrowOffsetY = 101;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetY(), 101);

    /**
     * @tc.steps: step5.finalPlacement_ = Placement::RIGHT_BOTTOM, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;
    sheetPattern->sheetPopupInfo_.arrowOffsetY = 201;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetY(), 201);

    /**
     * @tc.steps: step6.finalPlacement_ = Placement::RIGHT, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT;
    sheetPattern->sheetPopupInfo_.arrowOffsetY = 301;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetY(), 301);

    /**
     * @tc.steps: step7.finalPlacement_ = Placement::LEFT_TOP, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP;
    sheetPattern->sheetPopupInfo_.arrowOffsetY = 401;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetY(), 401);

    /**
     * @tc.steps: step8.finalPlacement_ = Placement::LEFT_BOTTOM, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM;
    sheetPattern->sheetPopupInfo_.arrowOffsetY = 501;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetY(), 501);

    /**
     * @tc.steps: step9.finalPlacement_ = Placement::LEFT, test GetArrowOffsetByPlacement
     */
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT;
    sheetPattern->sheetPopupInfo_.arrowOffsetY = 601;
    sheetPattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    EXPECT_EQ(sheetPattern->GetSheetArrowOffset().GetY(), 601);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetPopupStyleSheetClipPathNew001
 * @tc.desc: Branch:   switch (finalPlacement_)
 *           Condition: finalPlacement_ = Placement::BOTTOM_LEFT
 *                      finalPlacement_ = Placement::BOTTOM_RIGHT
 *                      finalPlacement_ = Placement::BOTTOM
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetPopupStyleSheetClipPathNew001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 22,
        AceType::MakeRefPtr<SheetPresentationPattern>(122, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. finalPlacement_ = lacement::BOTTOM_LEFT, test GetArrowOffsetByPlacement
     */
    auto sheetSize = SizeF(1000, 720);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.0_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());
    sheetPattern->finalPlacement_ = Placement::BOTTOM_LEFT;
    auto ret1 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret1, " ");

    /**
     * @tc.steps: step3. finalPlacement_ = lacement::BOTTOM_RIGHT, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::BOTTOM_RIGHT;
    auto ret2 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret2, " ");

    /**
     * @tc.steps: step4. finalPlacement_ = lacement::BOTTOM, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::BOTTOM;
    auto ret3 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret3, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetPopupStyleSheetClipPathNew002
 * @tc.desc: Branch:   switch (finalPlacement_)
 *           Condition: finalPlacement_ = Placement::TOP_LEFT
 *                      finalPlacement_ = Placement::TOP_RIGHT
 *                      finalPlacement_ = Placement::TOP
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetPopupStyleSheetClipPathNew002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 25,
        AceType::MakeRefPtr<SheetPresentationPattern>(125, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. finalPlacement_ = lacement::TOP_LEFT, test GetArrowOffsetByPlacement
     */
    auto sheetSize = SizeF(1001, 721);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.1_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());
    sheetPattern->finalPlacement_ = Placement::TOP_LEFT;
    auto ret4 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret4, " ");

    /**
     * @tc.steps: step3. finalPlacement_ = lacement::TOP_RIGHT, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::TOP_RIGHT;
    auto ret5 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret5, " ");

    /**
     * @tc.steps: step4. finalPlacement_ = lacement::TOP, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::TOP;
    auto ret6 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret6, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetPopupStyleSheetClipPathNew003
 * @tc.desc: Branch:   switch (finalPlacement_)
 *           Condition: finalPlacement_ = Placement::RIGHT_TOP
 *                      finalPlacement_ = Placement::RIGHT_BOTTOM
 *                      finalPlacement_ = Placement::RIGHT
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetPopupStyleSheetClipPathNew003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 28,
        AceType::MakeRefPtr<SheetPresentationPattern>(128, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. finalPlacement_ = lacement::RIGHT_TOP, test GetArrowOffsetByPlacement
     */
    auto sheetSize = SizeF(1002, 722);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.2_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());
    sheetPattern->finalPlacement_ = Placement::RIGHT_TOP;
    auto ret7 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret7, " ");

    /**
     * @tc.steps: step3. finalPlacement_ = lacement::RIGHT_BOTTOM, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::RIGHT_BOTTOM;
    auto ret8 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret8, " ");

    /**
     * @tc.steps: step4. finalPlacement_ = lacement::RIGHT, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::RIGHT;
    auto ret9 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret9, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: GetPopupStyleSheetClipPathNew004
 * @tc.desc: Branch:   switch (finalPlacement_)
 *           Condition: finalPlacement_ = Placement::LEFT_TOP
 *                      finalPlacement_ = Placement::LEFT_BOTTOM
 *                      finalPlacement_ = Placement::LEFT
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, GetPopupStyleSheetClipPathNew004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 32,
        AceType::MakeRefPtr<SheetPresentationPattern>(132, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. finalPlacement_ = lacement::LEFT_TOP, test GetArrowOffsetByPlacement
     */
    auto sheetSize = SizeF(1003, 723);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.3_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());
    sheetPattern->finalPlacement_ = Placement::LEFT_TOP;
    auto ret10 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret10, " ");

    /**
     * @tc.steps: step3. finalPlacement_ = lacement::LEFT_BOTTOM, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::LEFT_BOTTOM;
    auto ret11 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret11, " ");

    /**
     * @tc.steps: step4. finalPlacement_ = lacement::LEFT, test GetArrowOffsetByPlacement
     */
    sheetPattern->finalPlacement_ = Placement::LEFT;
    auto ret12 = sheetPattern->GetPopupStyleSheetClipPathNew(sheetSize, sheetRadius);
    EXPECT_NE(ret12, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathBottom001
 * @tc.desc: Branch:   if (arrowPosition_ == SheetArrowPosition::BOTTOM_LEFT)
 *                     if (arrowPosition_ == SheetArrowPosition::BOTTOM_RIGHT)
 *           Condition: arrowPosition_ == SheetArrowPosition::BOTTOM_LEFT = true
 *                      arrowPosition_ == SheetArrowPosition::BOTTOM_RIGHT = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, DrawClipPathBottom001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 35,
        AceType::MakeRefPtr<SheetPresentationPattern>(135, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetSize and sheetRadius.
     */
    auto sheetSize = SizeF(1003, 723);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.3_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());

    /**
     * @tc.steps: step3. arrowPosition_ = SheetArrowPosition::BOTTOM_LEFT, test DrawClipPathBottom.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::BOTTOM_LEFT;
    auto ret1 = sheetPattern->DrawClipPathBottom(sheetSize, sheetRadius);
    EXPECT_NE(ret1, " ");

    /**
     * @tc.steps: step4. arrowPosition_ = SheetArrowPosition::BOTTOM_RIGHT, test DrawClipPathBottom.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::BOTTOM_RIGHT;
    auto ret2 = sheetPattern->DrawClipPathBottom(sheetSize, sheetRadius);
    EXPECT_NE(ret2, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathTop001
 * @tc.desc: Branch:   if (arrowPosition_ == SheetArrowPosition::TOP_RIGHT)
 *                     if (arrowPosition_ == SheetArrowPosition::TOP_LEFT)
 *           Condition: arrowPosition_ == SheetArrowPosition::TOP_RIGHT = true
 *                      arrowPosition_ == SheetArrowPosition::TOP_LEFT = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, DrawClipPathTop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 37,
        AceType::MakeRefPtr<SheetPresentationPattern>(137, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetSize and sheetRadius.
     */
    auto sheetSize = SizeF(1004, 724);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.4_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());

    /**
     * @tc.steps: step3. arrowPosition_ = SheetArrowPosition::TOP_RIGHT, test DrawClipPathTop.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::TOP_RIGHT;
    auto ret1 = sheetPattern->DrawClipPathTop(sheetSize, sheetRadius);
    EXPECT_NE(ret1, " ");

    /**
     * @tc.steps: step4. arrowPosition_ = SheetArrowPosition::TOP_LEFT, test DrawClipPathTop.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::TOP_LEFT;
    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    auto ret2 = sheetPattern->DrawClipPathTop(sheetSize, sheetRadius);
    EXPECT_NE(ret2, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathLeft001
 * @tc.desc: Branch:   if (arrowPosition_ == SheetArrowPosition::LEFT_TOP)
 *                     if (arrowPosition_ == SheetArrowPosition::TOP_LEFT)
 *           Condition: arrowPosition_ == SheetArrowPosition::LEFT_TOP = true
 *                      arrowPosition_ == SheetArrowPosition::TOP_LEFT = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, DrawClipPathLeft001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 40,
        AceType::MakeRefPtr<SheetPresentationPattern>(140, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetSize and sheetRadius.
     */
    auto sheetSize = SizeF(1005, 725);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.5_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());

    /**
     * @tc.steps: step3. arrowPosition_ = SheetArrowPosition::LEFT_TOP, test DrawClipPathLeft.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::LEFT_TOP;
    auto ret1 = sheetPattern->DrawClipPathLeft(sheetSize, sheetRadius);
    EXPECT_NE(ret1, " ");

    /**
     * @tc.steps: step4. arrowPosition_ = SheetArrowPosition::NONE, test DrawClipPathLeft.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::NONE;
    auto ret2 = sheetPattern->DrawClipPathLeft(sheetSize, sheetRadius);
    EXPECT_NE(ret2, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();

    /**
     * @tc.steps: step4. arrowPosition_ = SheetArrowPosition::LEFT_BOTTOM, test DrawClipPathLeft.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::LEFT_BOTTOM;
    auto ret3 = sheetPattern->DrawClipPathLeft(sheetSize, sheetRadius);
    EXPECT_NE(ret3, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathRight001
 * @tc.desc: Branch:   if (arrowPosition_ == SheetArrowPosition::RIGHT_TOP)
 *                     if (arrowPosition_ == SheetArrowPosition::RIGHT_BOTTOM)
 *           Condition: arrowPosition_ == SheetArrowPosition::RIGHT_TOP = true
 *                      arrowPosition_ == SheetArrowPosition::RIGHT_BOTTOM = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, DrawClipPathRight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 45,
        AceType::MakeRefPtr<SheetPresentationPattern>(145, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. init sheetSize and sheetRadius.
     */
    auto sheetSize = SizeF(1006, 726);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 40.6_vp;
    SheetPresentationTestSevenNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());

    /**
     * @tc.steps: step3. arrowPosition_ = SheetArrowPosition::RIGHT_TOP, test DrawClipPathRight.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::RIGHT_TOP;
    auto ret1 = sheetPattern->DrawClipPathRight(sheetSize, sheetRadius);
    EXPECT_NE(ret1, " ");

    /**
     * @tc.steps: step4. arrowPosition_ = SheetArrowPosition::RIGHT_BOTTOM, test DrawClipPathRight.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::NONE;
    auto ret2 = sheetPattern->DrawClipPathRight(sheetSize, sheetRadius);
    EXPECT_NE(ret2, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();

    /**
     * @tc.steps: step4. arrowPosition_ = SheetArrowPosition::LEFT_BOTTOM, test DrawClipPathRight.
     */
    sheetPattern->arrowPosition_ = SheetArrowPosition::NONE;
    auto ret3 = sheetPattern->DrawClipPathRight(sheetSize, sheetRadius);
    EXPECT_NE(ret3, " ");
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: RecoverAvoidKeyboardStatus001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, RecoverAvoidKeyboardStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 50,
        AceType::MakeRefPtr<SheetPresentationPattern>(150, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test RecoverAvoidKeyboardStatus.
     */
    sheetPattern->SetSheetHeightUp(10.0f);
    sheetPattern->RecoverAvoidKeyboardStatus();
    EXPECT_EQ(sheetPattern->GetSheetHeightUp(), 0.0f);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, OnFontScaleConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 51,
        AceType::MakeRefPtr<SheetPresentationPattern>(151, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test OnFontScaleConfigurationUpdate.
     */
    sheetPattern->OnFontScaleConfigurationUpdate();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_EQ(pipelineContext->afterReloadAnimationTasks_.empty(), false);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: OnAvoidInfoChange001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, OnAvoidInfoChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 52,
        AceType::MakeRefPtr<SheetPresentationPattern>(152, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test OnAvoidInfoChange.
     */
    ContainerModalAvoidInfo info;
    sheetPattern->OnAvoidInfoChange(info);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: SendMessagesBeforeFirstTransitionIn001
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, SendMessagesBeforeFirstTransitionIn001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 53,
        AceType::MakeRefPtr<SheetPresentationPattern>(153, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test SendMessagesBeforeFirstTransitionIn.
     */
    bool isFirstTransition = true;
    sheetPattern->SendMessagesBeforeFirstTransitionIn(isFirstTransition);
    EXPECT_TRUE(isFirstTransition);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: SendMessagesBeforeFirstTransitionIn002
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, SendMessagesBeforeFirstTransitionIn002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 54,
        AceType::MakeRefPtr<SheetPresentationPattern>(154, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. test SendMessagesBeforeFirstTransitionIn.
     */
    bool isFirstTransition = false;
    sheetPattern->SendMessagesBeforeFirstTransitionIn(isFirstTransition);
    EXPECT_FALSE(isFirstTransition);
    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes001
 * @tc.desc: Branch: if (isWaterfallWindowMode_)
 *           Condition: isWaterfallWindowMode_ = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, CalculateSheetHeightInOtherScenes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. set sheetLayoutAlgorithm.
     */
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetTheme_->isOuterBorderEnable_ = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isHalfFoldHoverStatus_ = false;

    /**
     * @tc.steps: step3. set isWaterfallWindowMode_ = true .
     */
    sheetLayoutAlgorithm->isWaterfallWindowMode_ = true;

    /**
     * @tc.steps: step4. creat and mount layoutWrapper.
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>());
    sheetNode->MountToParent(sheetWrapperNode);
    auto heightBefore =
        sheetLayoutAlgorithm->CalculateSheetHeightInOtherScenes(Referenced::RawPtr(layoutWrapper), 200.0f);
    EXPECT_EQ(heightBefore, 200.0f);
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetLayoutAlgorithm->isHoverMode_ = true;
    sheetLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    std::vector<Rect> currentFoldCreaseRegion;
    Rect rect;
    rect.SetRect(0, 2000.0f, 1000.0f, 200.0f);
    currentFoldCreaseRegion.insert(currentFoldCreaseRegion.end(), rect);
    sheetPattern->currentFoldCreaseRegion_ = currentFoldCreaseRegion;

    /**
     * @tc.steps: step5. test CalculateSheetHeightInOtherScenes.
     */
    auto ret =
        sheetLayoutAlgorithm->CalculateSheetHeightInOtherScenes(Referenced::RawPtr(layoutWrapper), 3000.0f);
    EXPECT_EQ(ret, 1984);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize001
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) ||
 *      sheetType_ != SheetType::SHEET_POPUP)
 *      if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *      !sheetPopupInfo_.showArrow)
 *           Condition: Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) = false
 *                      sheetType_ != SheetType::SHEET_POPUP = false
 *                      sheetPopupInfo_.placementRechecked = false
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;

    /**
     * @tc.steps: step3.finalPlacement = Placement::BOTTOM_LEFT, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 8.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize002
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetHeight_ = 8.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::BOTTOM_RIGHT, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 16.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize003
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::BOTTOM
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetHeight_ = 16.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::BOTTOM, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 24.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize004
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetHeight_ = 24.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::TOP_LEFT, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 32.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize005
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetHeight_ = 32.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::TOP_RIGHT, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 40.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize006
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::TOP
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetHeight_ = 40.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::TOP, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 48.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize007
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetWidth_ = 0.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::RIGHT_TOP, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 8.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize008
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetWidth_ = 8.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::RIGHT_BOTTOM, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 16.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize009
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::RIGHT
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetWidth_ = 16.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::RIGHT, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 24.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize010
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetWidth_ = 24.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::LEFT_TOP, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 32.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize011
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetWidth_ = 32.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::LEFT_BOTTOM, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 40.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: AddArrowHeightToSheetSize012
 * @tc.desc: Branch: switch (sheetPopupInfo_.finalPlacement)
 *           Condition: sheetPopupInfo_.finalPlacement = Placement::LEFT
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, AddArrowHeightToSheetSize012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetLayoutAlgorithm.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();

    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. SetApiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetWidth_ = 40.0f;

    /**
     * @tc.steps: step3.finalPlacement = Placement::LEFT, test SendMessagesBeforeFirstTransitionIn.
     */
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT;
    sheetLayoutAlgorithm->AddArrowHeightToSheetSize();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 48.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: UpdatePopupInfoAndRemeasure001
 * @tc.desc: Branch:  if (sheetType_ != SheetType::SHEET_POPUP)
 *           Condition:   sheetType_ != SheetType::SHEET_POPUP = true
 *                      
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, UpdatePopupInfoAndRemeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetNode.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 70,
        AceType::MakeRefPtr<SheetPresentationPattern>(170, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create sheetLayoutAlgorithm.
     */
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    
    /**
     * @tc.steps: step3. creat layoutWrapper.
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step4. init sheetPopupInfo.
     */
    SheetPopupInfo sheetPopupInfo;
    sheetPopupInfo.sheetOffsetX = 1.0f;
    sheetPopupInfo.sheetOffsetY = 2.0f;
    float sheetWidth = 3.0f;
    float sheetHeight = 4.0f;

    /**
     * @tc.steps: step4. test UpdatePopupInfoAndRemeasure.
     */
    sheetLayoutAlgorithm->UpdatePopupInfoAndRemeasure(
        Referenced::RawPtr(layoutWrapper), sheetPopupInfo, sheetWidth, sheetHeight);
    EXPECT_EQ(sheetLayoutAlgorithm->GetSheetOffsetX(), 0.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->GetSheetOffsetY(), 0.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 0.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 0.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}

/**
 * @tc.name: UpdatePopupInfoAndRemeasure002
 * @tc.desc: Branch:  if (sheetType_ != SheetType::SHEET_POPUP)
 *                    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN))
 *           Condition:   sheetType_ != SheetType::SHEET_POPUP = false
 *                        Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestSevenNg, UpdatePopupInfoAndRemeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheetNode.
     */
    SheetPresentationTestSevenNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 71,
        AceType::MakeRefPtr<SheetPresentationPattern>(171, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create sheetLayoutAlgorithm.
     */
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    
    /**
     * @tc.steps: step3. creat layoutWrapper.
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step4. init sheetPopupInfo.
     */
    SheetPopupInfo sheetPopupInfo;
    sheetPopupInfo.sheetOffsetX = 7.0f;
    sheetPopupInfo.sheetOffsetY = 8.0f;
    float sheetWidth = 9.0f;
    float sheetHeight = 10.0f;

    /**
     * @tc.steps: step5. set apiTargetVersion.
     */
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step6. test UpdatePopupInfoAndRemeasure.
     */
    sheetLayoutAlgorithm->UpdatePopupInfoAndRemeasure(
        Referenced::RawPtr(layoutWrapper), sheetPopupInfo, sheetWidth, sheetHeight);
    EXPECT_EQ(sheetLayoutAlgorithm->GetSheetOffsetX(), 7.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->GetSheetOffsetY(), 8.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetWidth_, 0.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 0.0f);

    SheetPresentationTestSevenNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG
