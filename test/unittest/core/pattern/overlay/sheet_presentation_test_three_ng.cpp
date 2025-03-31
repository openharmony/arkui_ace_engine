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

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

class SheetPresentationTestThreeNg : public testing::Test {
public:
    static RefPtr<SheetTheme> sheetTheme_;
    static void SetUpTestCase();
    static void TearDownTestCase();
};

RefPtr<SheetTheme> SheetPresentationTestThreeNg::sheetTheme_ = nullptr;

void SheetPresentationTestThreeNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    sheetTheme_ = AceType::MakeRefPtr<SheetTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPresentationTestThreeNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ComputeCenterStyleOffset001
 * @tc.desc: Branch: if (!showInSubWindow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, ComputeCenterStyleOffset001, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetStyle_.showInSubWindow = false;
    sheetLayoutAlgorithm->sheetMaxWidth_ = 1800.0f;
    sheetLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetLayoutAlgorithm->sheetOffsetX_ = 0.0f;
    sheetLayoutAlgorithm->sheetOffsetY_ = 0.0f;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->ComputeCenterStyleOffset(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 500.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeCenterStyleOffset002
 * @tc.desc: Branch: if (!showInSubWindow) = false
 *           Branch: if (mainWindowContext && GetContainerModalButtonsRect()) = false
 *           Condition: mainWindowContext = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, ComputeCenterStyleOffset002, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetStyle_.showInSubWindow = true;
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    AceEngine::Get().containerMap_.emplace(1, MockContainer::Current());
    sheetNode->MountToParent(sheetWrapperNode);
    sheetWrapperPattern->mainWindowRect_ = RectF(0.0f, 0.0f, 1800.0f, 1020.0f);
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(sheetGeometryNode, nullptr);
    sheetGeometryNode->frame_.rect_ = RectF(0.0f, 0.0f, 800.0f, 600.0f);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetGeometryNode, sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->ComputeCenterStyleOffset(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 500.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, 210.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeCenterStyleOffset003
 * @tc.desc: Branch: if (!showInSubWindow) = false
 *           Branch: if (mainWindowContext && GetContainerModalButtonsRect()) = false
 *           Condition: mainWindowContext = true, GetContainerModalButtonsRect() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, ComputeCenterStyleOffset003, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetStyle_.showInSubWindow = true;
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    auto container = MockContainer::Current();
    AceEngine::Get().containerMap_.clear();
    AceEngine::Get().containerMap_.emplace(1, container);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    container->pipelineContext_ = pipelineContext;
    pipelineContext->SetContainerModalButtonsRect(false);
    sheetNode->MountToParent(sheetWrapperNode);
    sheetWrapperPattern->mainWindowRect_ = RectF(0.0f, 0.0f, 1800.0f, 1020.0f);
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(sheetGeometryNode, nullptr);
    sheetGeometryNode->frame_.rect_ = RectF(0.0f, 0.0f, 800.0f, 600.0f);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetGeometryNode, sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->ComputeCenterStyleOffset(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 500.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, 210.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeCenterStyleOffset004
 * @tc.desc: Branch: if (!showInSubWindow) = false
 *           Branch: if (mainWindowContext && GetContainerModalButtonsRect()) = true
 *           Condition: mainWindowContext = true, GetContainerModalButtonsRect() = true
 *           Branch: if (LessOrEqual(sheetOffsetY_, mainWindowRect.GetY() + buttonsRect.Height())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, ComputeCenterStyleOffset004, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetStyle_.showInSubWindow = true;
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    auto container = MockContainer::Current();
    AceEngine::Get().containerMap_.clear();
    AceEngine::Get().containerMap_.emplace(1, container);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    container->pipelineContext_ = pipelineContext;
    sheetNode->MountToParent(sheetWrapperNode);
    sheetWrapperPattern->mainWindowRect_ = RectF(0.0f, 0.0f, 1800.0f, 1020.0f);
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(sheetGeometryNode, nullptr);
    sheetGeometryNode->frame_.rect_ = RectF(0.0f, 0.0f, 800.0f, 600.0f);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetGeometryNode, sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->ComputeCenterStyleOffset(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 500.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, 210.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeCenterStyleOffset005
 * @tc.desc: Branch: if (!showInSubWindow) = false
 *           Branch: if (mainWindowContext && GetContainerModalButtonsRect()) = true
 *           Condition: mainWindowContext = true, GetContainerModalButtonsRect() = true
 *           Branch: if (LessOrEqual(sheetOffsetY_, mainWindowRect.GetY() + buttonsRect.Height())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, ComputeCenterStyleOffset005, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetStyle_.showInSubWindow = true;
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    auto container = MockContainer::Current();
    AceEngine::Get().containerMap_.clear();
    AceEngine::Get().containerMap_.emplace(1, container);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    container->pipelineContext_ = pipelineContext;
    sheetNode->MountToParent(sheetWrapperNode);
    sheetWrapperPattern->mainWindowRect_ = RectF(0.0f, 0.0f, 1800.0f, 1020.0f);
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(sheetGeometryNode, nullptr);
    sheetGeometryNode->frame_.rect_ = RectF(0.0f, 0.0f, 1800.0f, 2400.0f);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetGeometryNode, sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->ComputeCenterStyleOffset(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 0.0f);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTranslateOffsetWithPlacement001
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateTranslateOffsetWithPlacement001, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    OffsetF translate;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 8.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTranslateOffsetWithPlacement002
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = true
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateTranslateOffsetWithPlacement002, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    OffsetF translate;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTranslateOffsetWithPlacement003
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = true
 *           Condition: sheetPopupInfo_.placementRechecked = false, !sheetPopupInfo_.showArrow = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateTranslateOffsetWithPlacement003, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    OffsetF translate;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTranslateOffsetWithPlacement004
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = true
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = false,
 *               !sheetPopupInfo_.showArrow = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateTranslateOffsetWithPlacement004, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    OffsetF translate;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTranslateOffsetWithPlacement005
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = false
 *           Condition: sheetPopupInfo_.placementRechecked = false, !sheetPopupInfo_.showArrow = false
 *           Branch: case Placement::BOTTOM_LEFT = true
 *           Branch: case Placement::BOTTOM_RIGHT = true
 *           Branch: case Placement::BOTTOM = true
 *           Branch: case Placement::RIGHT_TOP = true
 *           Branch: case Placement::RIGHT_BOTTOM = true
 *           Branch: case Placement::RIGHT = true
 *           Branch: default = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateTranslateOffsetWithPlacement005, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;

    OffsetF translate;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 8.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 16.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 8.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 16.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 24.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::NONE;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate);
    EXPECT_EQ(translate.GetX(), 24.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetWidthByScreenSizeType001
 * @tc.desc: Branch: case SheetType::SHEET_BOTTOM = true
 *           Branch: if (sheetPattern->IsPhoneInLandScape()) = true
 *           Branch: if (!sheetStyle_.width.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetWidthByScreenSizeType001, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    // Make IsPhoneInLandScape return true
    sheetTheme_->sheetType_ = "auto";
    auto foldWindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(0));
    EXPECT_CALL(*foldWindow, IsFoldExpand()).WillRepeatedly(Return(false));
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    float sheetWidth = sheetLayoutAlgorithm->GetWidthByScreenSizeType(800.0f, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetWidth, 480.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetWidthByScreenSizeType002
 * @tc.desc: Branch: case SheetType::SHEET_BOTTOM = true
 *           Branch: if (sheetPattern->IsPhoneInLandScape()) = false
 *           Branch: if (!sheetStyle_.width.has_value()) = false
 *           Branch: if (sheetStyle_.width->Unit() == DimensionUnit::PERCENT) = false
 *           Branch: if (LessNotEqual(width, 0.0f) || width > parentConstraintWidth) = true
 *           Condition: LessNotEqual(width, 0.0f) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetWidthByScreenSizeType002, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetLayoutAlgorithm->sheetStyle_.width = -800.0_vp;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    float sheetWidth = sheetLayoutAlgorithm->GetWidthByScreenSizeType(800.0f, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetWidth, 800.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetWidthByScreenSizeType003
 * @tc.desc: Branch: case SheetType::SHEET_BOTTOM_FREE_WINDOW = true
 *           Branch: if (!sheetStyle_.width.has_value()) = false
 *           Branch: if (sheetStyle_.width->Unit() == DimensionUnit::PERCENT) = true
 *           Branch: if (LessNotEqual(width, 0.0f) || width > parentConstraintWidth) = true
 *           Condition: LessNotEqual(width, 0.0f) = false, width > parentConstraintWidth = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetWidthByScreenSizeType003, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    sheetLayoutAlgorithm->sheetStyle_.width = 2.0_pct;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    float sheetWidth = sheetLayoutAlgorithm->GetWidthByScreenSizeType(800.0f, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetWidth, 800.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetWidthByScreenSizeType004
 * @tc.desc: Branch: case SheetType::SHEET_BOTTOMLANDSPACE = true
 *           Branch: if (!sheetStyle_.width.has_value()) = false
 *           Branch: if (sheetStyle_.width->Unit() == DimensionUnit::PERCENT) = true
 *           Branch: if (LessNotEqual(width, 0.0f) || width > parentConstraintWidth) = false
 *           Condition: LessNotEqual(width, 0.0f) = false, width > parentConstraintWidth = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetWidthByScreenSizeType004, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetLayoutAlgorithm->sheetStyle_.width = 0.5_pct;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    float sheetWidth = sheetLayoutAlgorithm->GetWidthByScreenSizeType(800.0f, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetWidth, 400.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetWidthByScreenSizeType005
 * @tc.desc: Branch: case SheetType::SHEET_CENTER = true
 *           Branch: case SheetType::SHEET_POPUP = true
 *           Branch: default = true
 *           Branch: if (!sheetStyle_.width.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetWidthByScreenSizeType005, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    float sheetWidth = sheetLayoutAlgorithm->GetWidthByScreenSizeType(800.0f, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetWidth, 0.0f);

    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;

    sheetWidth = sheetLayoutAlgorithm->GetWidthByScreenSizeType(800.0f, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetWidth, 360.0f);

    sheetLayoutAlgorithm->sheetType_ = SheetType(-1);

    sheetWidth = sheetLayoutAlgorithm->GetWidthByScreenSizeType(800.0f, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetWidth, 800.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateMaxSizeWithPlacement001
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateMaxSizeWithPlacement001, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1992.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateMaxSizeWithPlacement002
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = true
 *           Branch: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateMaxSizeWithPlacement002, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 2000.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateMaxSizeWithPlacement003
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = true
 *           Branch: sheetPopupInfo_.placementRechecked = false, !sheetPopupInfo_.showArrow = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateMaxSizeWithPlacement003, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 2000.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateMaxSizeWithPlacement004
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = true
 *           Branch: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = false,
 *               !sheetPopupInfo_.showArrow = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateMaxSizeWithPlacement004, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 2000.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateMaxSizeWithPlacement005
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = false
 *           Branch: sheetPopupInfo_.placementRechecked = false, !sheetPopupInfo_.showArrow = false
 *           Branch: case Placement::BOTTOM_LEFT = true
 *           Branch: case Placement::BOTTOM_RIGHT = true
 *           Branch: case Placement::BOTTOM = true
 *           Branch: case Placement::TOP_LEFT = true
 *           Branch: case Placement::TOP_RIGHT = true
 *           Branch: case Placement::TOP = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateMaxSizeWithPlacement005, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1992.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1984.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1976.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1968.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1960.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1952.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateMaxSizeWithPlacement006
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
 *               !sheetPopupInfo_.showArrow) = false
 *           Branch: sheetPopupInfo_.placementRechecked = false, !sheetPopupInfo_.showArrow = false
 *           Branch: case Placement::RIGHT_TOP = true
 *           Branch: case Placement::RIGHT_BOTTOM = true
 *           Branch: case Placement::RIGHT = true
 *           Branch: case Placement::LEFT_TOP = true
 *           Branch: case Placement::LEFT_BOTTOM = true
 *           Branch: case Placement::LEFT = true
 *           Branch: default = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, UpdateMaxSizeWithPlacement006, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 2992.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 2984.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 2976.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 2968.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 2960.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 2952.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::NONE;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 2952.0f);
    EXPECT_EQ(maxHeight, 2000.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG