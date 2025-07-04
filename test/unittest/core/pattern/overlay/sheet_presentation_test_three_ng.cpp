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
    static void SetApiVersion(int32_t apiTargetVersion);
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

void SheetPresentationTestThreeNg::SetApiVersion(int32_t apiTargetVersion)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(apiTargetVersion);
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
    sheetWrapperPattern->isShowInUEC_ = true;
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
    sheetWrapperPattern->isShowInUEC_ = true;
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
    sheetWrapperPattern->isShowInUEC_ = true;
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
    sheetWrapperPattern->isShowInUEC_ = true;
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
 * @tc.name: ComputeCenterStyleOffset006
 * @tc.desc: Branch: if (!showInSubWindow) = false
 *           Branch: ShowInUEC = false
 *           Branch: if (mainWindowContext && GetContainerModalButtonsRect()) = true
 *           Condition: mainWindowContext = true, GetContainerModalButtonsRect() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, ComputeCenterStyleOffset006, TestSize.Level1)
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
    auto rootGeometryNode = pipelineContext->rootNode_->GetGeometryNode();
    rootGeometryNode->SetFrameSize(SizeF(1800.0f, 1020.0f));
    container->pipelineContext_ = pipelineContext;
    sheetNode->MountToParent(sheetWrapperNode);
    sheetWrapperPattern->mainWindowRect_ = RectF(0.0f, 0.0f, 1800.0f, 1020.0f);
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(sheetGeometryNode, nullptr);
    sheetGeometryNode->frame_.rect_ = RectF(0.0f, 0.0f, 500.0f, 500.0f);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetGeometryNode, sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->ComputeCenterStyleOffset(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, (1800.0f - 500.0f) / 2);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, (1020.0f - 500.0f) / 2);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    OffsetF translate;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    OffsetF translate;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    OffsetF translate;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    OffsetF translate;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;

    OffsetF translate;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 8.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 16.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
    EXPECT_EQ(translate.GetX(), 0.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
    EXPECT_EQ(translate.GetX(), 8.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
    EXPECT_EQ(translate.GetX(), 16.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
    EXPECT_EQ(translate.GetX(), 24.0f);
    EXPECT_EQ(translate.GetY(), 24.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::NONE;
    sheetLayoutAlgorithm->UpdateTranslateOffsetWithPlacement(translate, layoutWrapper);
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
 * @tc.name: SetCurrentHeight001
 * @tc.desc: Branch: if (height_ != currentHeight).
 *           Condition: 1.height_ = 500,
 *                      2.currentHeight = 700.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, SetCurrentHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "SetCurrentHeight".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto rootNode =
        FrameNode::CreateFrameNode("RootNode", 001, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("SheetNode", 002,
        AceType::MakeRefPtr<SheetPresentationPattern>(003, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);

    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBarNode", 004, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);

    auto scrollNode =
        FrameNode::CreateFrameNode("ScrollNode", 005, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContentNode", 006,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    
    /**
     * @tc.steps: step2. get sheetPattern、layoutProperty、scrollPattern, before test "SetCurrentHeight".
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));

    /**
     * @tc.steps: step3. init SheetStyle, before test "SetCurrentHeight".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.sheetHeight.sheetMode = SheetMode::LARGE;
    sheetStyle.sheetTitle = "Title";
    sheetStyle.sheetSubtitle = "SubTitle";
    sheetStyle.scrollSizeMode = ScrollSizeMode::CONTINUOUS;
    sheetStyle.borderWidth = { 1.0_vp, 1.0_vp, 1.0_vp, 0.0_vp };
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "SetCurrentHeight",
     * when sheetPattern->height_ = 500,
     * currentHeight = 700.
     * @tc.expected: height_ = currentHeight = 700.
     */
    sheetPattern->height_ = 500;
    sheetPattern->SetCurrentHeight(700);
    EXPECT_EQ(sheetPattern->height_, 700);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: SetBottomOffset001
 * @tc.desc: Branch: if (deviceType != DeviceType::TWO_IN_ONE).
 *           Condition: 1.deviceType = DeviceType::PHONE,
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, SetBottomOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "SetBottomOffset".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("RootNode", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("SheetNode", 02,
        AceType::MakeRefPtr<SheetPresentationPattern>(03, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);

    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBarNode", 04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);

    auto scrollNode =
        FrameNode::CreateFrameNode("ScrollNode", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    
    auto content = FrameNode::GetOrCreateFrameNode("SheetContentNode", 06,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(content, nullptr);
    content->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    
    /**
     * @tc.steps: step2. get sheetPresentationPattern、scrollPattern、layoutProperty, before test "SetBottomOffset".
     */
    auto sheetPresentationPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPresentationPattern, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPresentationPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    auto layoutProperty = sheetPresentationPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle, before test "SetBottomOffset".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.sheetTitle = "SheetTitle";
    sheetStyle.sheetSubtitle = "SheetSubTitle";
    sheetStyle.scrollSizeMode = ScrollSizeMode::FOLLOW_DETENT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "SetBottomOffset" when deviceType = DeviceType::PHONE.
     */
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    sheetPresentationPattern->SetBottomOffset(sheetStyle);
    EXPECT_EQ(sheetPresentationPattern->bottomOffsetX_, 0.0f);
    EXPECT_EQ(sheetPresentationPattern->bottomOffsetY_, 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: SetBottomOffset002
 * @tc.desc: Branch: if (sheetStyle.bottomOffset.has_value()
 *                      && sheetStyle.sheetType.value_or(SheetType::SHEET_BOTTOM)
 *                      == SheetType::SHEET_BOTTOM)
 *           Condition: 1.deviceType = DeviceType::TWO_IN_ONE,
 *                      2.sheetStyle.sheetType.value_or(SheetType::SHEET_BOTTOM)
 *                        != SheetType::SHEET_BOTTOM.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, SetBottomOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "SetBottomOffset".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto root = FrameNode::CreateFrameNode("RootNode", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(root, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheet = FrameNode::CreateFrameNode("SheetNode", 02,
        AceType::MakeRefPtr<SheetPresentationPattern>(03, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheet, nullptr);
    sheet->MountToParent(root);

    auto dragBar =
        FrameNode::CreateFrameNode("SheetDragBarNode", 04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBar, nullptr);
    dragBar->MountToParent(sheet);

    auto scroll =
        FrameNode::CreateFrameNode("ScrollNode", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    
    auto content = FrameNode::GetOrCreateFrameNode("SheetContentNode", 06,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(content, nullptr);
    content->MountToParent(scroll);
    scroll->MountToParent(sheet);
    
    /**
     * @tc.steps: step2. get sheetPattern、layoutProperty、scrollPattern, before test "SetBottomOffset".
     */
    auto sheetPresentationPattern = sheet->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPresentationPattern, nullptr);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPresentationPattern->SetScrollNode(WeakPtr<FrameNode>(scroll));
    auto layoutProperty = sheetPresentationPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle, before test "SetBottomOffset".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.sheetTitle = "SheetTitle";
    sheetStyle.sheetSubtitle = "SheetSubTitle";
    sheetStyle.scrollSizeMode = ScrollSizeMode::FOLLOW_DETENT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "SetBottomOffset" when deviceType = DeviceType::TWO_IN_ONE.
     */
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    sheetPresentationPattern->SetBottomOffset(sheetStyle);
    EXPECT_EQ(sheetPresentationPattern->bottomOffsetX_, 0.0f);
    EXPECT_EQ(sheetPresentationPattern->bottomOffsetY_, 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: IsResizeWhenAvoidKeyboard001
 * @tc.desc: Branch: return keyboardAvoidMode_ == SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE ||
 *                      keyboardAvoidMode_ == SheetKeyboardAvoidMode::RESIZE_ONLY
 *           Condition: 1.keyboardAvoidMode_ == SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, IsResizeWhenAvoidKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "SetBottomOffset".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto root = FrameNode::CreateFrameNode("RootNode", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(root, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheet = FrameNode::CreateFrameNode("SheetNode", 02,
        AceType::MakeRefPtr<SheetPresentationPattern>(03, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheet, nullptr);
    sheet->MountToParent(root);

    auto dragBar =
        FrameNode::CreateFrameNode("SheetDragBarNode", 04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBar, nullptr);
    dragBar->MountToParent(sheet);

    auto scroll =
        FrameNode::CreateFrameNode("ScrollNode", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    
    auto content = FrameNode::GetOrCreateFrameNode("SheetContentNode", 06,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(content, nullptr);
    content->MountToParent(scroll);
    scroll->MountToParent(sheet);
    
    /**
     * @tc.steps: step2. get sheetPattern、layoutProperty、scrollPattern, before test "SetBottomOffset".
     */
    auto sheetPresentationPattern = sheet->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPresentationPattern, nullptr);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPresentationPattern->SetScrollNode(WeakPtr<FrameNode>(scroll));
    auto layoutProperty = sheetPresentationPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle, before test "SetBottomOffset".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.sheetTitle = "SheetTitle";
    sheetStyle.sheetSubtitle = "SheetSubTitle";
    sheetStyle.scrollSizeMode = ScrollSizeMode::FOLLOW_DETENT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "SetBottomOffset" when deviceType = DeviceType::TWO_IN_ONE.
     */
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    sheetPresentationPattern->SetBottomOffset(sheetStyle);
    EXPECT_EQ(sheetPresentationPattern->bottomOffsetX_, 0.0f);
    EXPECT_EQ(sheetPresentationPattern->bottomOffsetY_, 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetCurrentScrollHeight001
 * @tc.desc: Branch: if (!isScrolling_)
 *           Condition: 1.isScrolling_ = false.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetCurrentScrollHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "GetCurrentScrollHeight".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto root = FrameNode::CreateFrameNode("Root", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(root, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheet = FrameNode::CreateFrameNode("Sheet", 02,
        AceType::MakeRefPtr<SheetPresentationPattern>(03, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheet, nullptr);
    sheet->MountToParent(root);

    auto dragBar =
        FrameNode::CreateFrameNode("SheetDragBar", 04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBar, nullptr);
    dragBar->MountToParent(sheet);

    auto scroll =
        FrameNode::CreateFrameNode("Scroll", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scroll, nullptr);
    
    auto content = FrameNode::GetOrCreateFrameNode("SheetContent", 06,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(content, nullptr);
    content->MountToParent(scroll);
    scroll->MountToParent(sheet);
    
    /**
     * @tc.steps: step2. get sheetPattern、sheetLayoutProperty、scrollPattern,
     *                      before test "GetCurrentScrollHeight".
     */
    auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutProperty =
        sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    auto scrollPattern = scroll->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scroll));

    /**
     * @tc.steps: step3. init SheetStyle, before test "GetCurrentScrollHeight".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.scrollSizeMode = ScrollSizeMode::CONTINUOUS;
    sheetLayoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "GetCurrentScrollHeight" when isScrolling_ = false.
     */
    sheetPattern->isScrolling_ = false;
    EXPECT_EQ(sheetPattern->scrollHeight_, 0.0f);
    sheetPattern->GetCurrentScrollHeight();
    EXPECT_EQ(sheetPattern->scrollHeight_, 0.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetCurrentScrollHeight002
 * @tc.desc: Branch: if (NearEqual(scrollHeight_, curOffset))
 *           Condition: 1.isScrolling_ = true.
 *                      2.scrollHeight_ = curOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetCurrentScrollHeight002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "GetCurrentScrollHeight".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto root = FrameNode::CreateFrameNode("ROOT", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(root, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheet = FrameNode::CreateFrameNode("SHEET", 02,
        AceType::MakeRefPtr<SheetPresentationPattern>(03, "SHEETPRESENTATION", std::move(callback)));
    ASSERT_NE(sheet, nullptr);
    sheet->MountToParent(root);

    auto dragBar =
        FrameNode::CreateFrameNode("DRAGBAR", 04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBar, nullptr);
    dragBar->MountToParent(sheet);

    auto scrollNode =
        FrameNode::CreateFrameNode("SCROLL", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    
    auto content = FrameNode::GetOrCreateFrameNode("CONTENT", 06,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(content, nullptr);
    content->MountToParent(scrollNode);
    scrollNode->MountToParent(sheet);
    
    /**
     * @tc.steps: step2. get sheetPattern、sheetLayoutProperty、scrollPattern,
     *                      before test "GetCurrentScrollHeight".
     */
    auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));

    /**
     * @tc.steps: step3. init SheetStyle, before test "GetCurrentScrollHeight".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.sheetHeight.height = Dimension(400.0f, DimensionUnit::AUTO);
    sheetStyle.scrollSizeMode = ScrollSizeMode::FOLLOW_DETENT;
    sheetLayoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "GetCurrentScrollHeight" when isScrolling_ = true.
     */
    sheetPattern->isScrolling_ = true;
    EXPECT_EQ(sheetPattern->scrollHeight_, 0.0f);
    scrollPattern->UpdateCurrentOffset(100, SCROLL_FROM_JUMP);
    sheetPattern->scrollHeight_ = 100;
    sheetPattern->GetCurrentScrollHeight();
    EXPECT_EQ(sheetPattern->scrollHeight_, -100);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: GetCurrentScrollHeight003
 * @tc.desc: Branch: if (NearEqual(scrollHeight_, curOffset))
 *           Condition: 1.isScrolling_ = true.
 *                      2.scrollHeight_ != curOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, GetCurrentScrollHeight003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "GetCurrentScrollHeight".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("ROOT", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheet = FrameNode::CreateFrameNode("SHEET", 02,
        AceType::MakeRefPtr<SheetPresentationPattern>(03, "SHEETPRESENTATION", std::move(callback)));
    ASSERT_NE(sheet, nullptr);
    sheet->MountToParent(rootNode);

    auto dragBar =
        FrameNode::CreateFrameNode("SHEETDRAGBAR", 04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBar, nullptr);
    dragBar->MountToParent(sheet);

    auto scrollNode =
        FrameNode::CreateFrameNode("SCROLLNODE", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    
    auto content = FrameNode::GetOrCreateFrameNode("SHEETCONTENT", 06,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(content, nullptr);
    content->MountToParent(scrollNode);
    scrollNode->MountToParent(sheet);
    
    /**
     * @tc.steps: step2. get sheetPattern、sheetLayoutProperty、scrollPattern,
     * before test "GetCurrentScrollHeight".
     */
    auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));

    /**
     * @tc.steps: step3. init SheetStyle, before test "GetCurrentScrollHeight".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.sheetHeight.height = Dimension(500.0f, DimensionUnit::AUTO);
    sheetStyle.scrollSizeMode = ScrollSizeMode::CONTINUOUS;
    sheetLayoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "GetCurrentScrollHeight".
     */
    sheetPattern->isScrolling_ = true;
    EXPECT_EQ(sheetPattern->scrollHeight_, 0.0f);
    scrollPattern->UpdateCurrentOffset(200, SCROLL_FROM_JUMP);
    sheetPattern->scrollHeight_ = 100;
    sheetPattern->GetCurrentScrollHeight();
    EXPECT_EQ(sheetPattern->scrollHeight_, -200);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: IsShowInSubWindowTest001
 * @tc.desc: Branch: return sheetStyle.showInSubWindow.value_or(false);
 *           Condition: 1.sheetStyle.showInSubWindow = true.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, IsShowInSubWindowTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, before test "IsShowInSubWindow".
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto rootNode =
        FrameNode::CreateFrameNode("ROOT", 001, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    
    auto callback = [](const std::string&) {};
    auto sheet = FrameNode::CreateFrameNode("SHEET", 002,
        AceType::MakeRefPtr<SheetPresentationPattern>(003, "SHEETPRESENTATION", std::move(callback)));
    ASSERT_NE(sheet, nullptr);
    sheet->MountToParent(rootNode);

    auto dragBar =
        FrameNode::CreateFrameNode("SHEETDRAGBAR", 004, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBar, nullptr);
    dragBar->MountToParent(sheet);

    auto scrollNode =
        FrameNode::CreateFrameNode("SCROLLNODE", 005, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    
    auto contentNode = FrameNode::GetOrCreateFrameNode("SHEETCONTENT", 006,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheet);
    
    /**
     * @tc.steps: step2. get sheetPattern、scrollPattern、sheetLayoutProperty
     *                      before test "IsShowInSubWindow".
     */
    auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto sheetLayoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));

    /**
     * @tc.steps: step3. init SheetStyle, before test "IsShowInSubWindow".
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.sheetHeight.height = Dimension(800.0f, DimensionUnit::AUTO);
    sheetStyle.scrollSizeMode = ScrollSizeMode::CONTINUOUS;
    sheetLayoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "IsShowInSubWindow".
     */
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), false);
    sheetStyle.showInSubWindow = true;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), true);
    sheetStyle.showInSubWindow = false;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    EXPECT_EQ(sheetPattern->IsShowInSubWindow(), false);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = false;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1992.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1984.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1976.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1968.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 3000.0f);
    EXPECT_EQ(maxHeight, 1960.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
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
    SheetPresentationTestThreeNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    sheetLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;

    float maxWidth = 3000.0f;
    float maxHeight = 2000.0f;
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 2992.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 2984.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 2976.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 2968.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 2960.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 2952.0f);
    EXPECT_EQ(maxHeight, 2000.0f);

    sheetLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::NONE;
    sheetLayoutAlgorithm->UpdateMaxSizeWithPlacement(maxWidth, maxHeight, layoutWrapper);
    EXPECT_EQ(maxWidth, 2952.0f);
    EXPECT_EQ(maxHeight, 2000.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: InitParameter001
 * @tc.desc: Branch: if (sheetTheme->IsOuterBorderEnable())
 *           Condition: sheetTheme->IsOuterBorderEnable() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, InitParameter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. set some parameters of sheetLayoutAlgorithm.
     */
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetTheme_->isOuterBorderEnable_ = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->isHalfFoldHoverStatus_ = false;

    /**
     * @tc.steps: step3. excute InitParameter function.
     * @tc.expected: isHoverMode_ is false
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->InitParameter(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->isHoverMode_, false);

    /**
     * @tc.steps: step4. excute InitParameter function.
     * @tc.expected: isHoverMode_ is false
     */
    sheetTheme_->isOuterBorderEnable_ = true;
    sheetLayoutAlgorithm->sheetStyle_.enableHoverMode = true;
    sheetLayoutAlgorithm->InitParameter(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->isHoverMode_, false);

    /**
     * @tc.steps: step5. excute InitParameter function.
     * @tc.expected: isHoverMode_ is true
     */
    pipeline->isHalfFoldHoverStatus_ = true;
    sheetTheme_->isOuterBorderEnable_ = false;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    sheetLayoutAlgorithm->sheetStyle_.enableHoverMode = true;
    sheetLayoutAlgorithm->InitParameter(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->isHoverMode_, true);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes001
 * @tc.desc: Branch: if (sheetType_ != SheetType::SHEET_CENTER || !isHoverMode_)
 *           Condition: sheetLayoutAlgorithm->isWaterfallWindowMode_ = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, CalculateSheetHeightInOtherScenes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. set some parameters of sheetLayoutAlgorithm.
     */
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetTheme_->isOuterBorderEnable_ = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->isHalfFoldHoverStatus_ = false;
    sheetLayoutAlgorithm->isWaterfallWindowMode_ = false;

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());

    /**
     * @tc.steps: step3. excute CalculateSheetHeightInOtherScenes function.
     * @tc.expected: 100.0f
     */
    auto heightBefore =
        sheetLayoutAlgorithm->CalculateSheetHeightInOtherScenes(Referenced::RawPtr(layoutWrapper), 100.0f);
    EXPECT_EQ(heightBefore, 100.0f);

    /**
     * @tc.steps: step4. set currentFoldCreaseRegion and compute height.
     */
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetLayoutAlgorithm->isHoverMode_ = true;
    sheetLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    std::vector<Rect> currentFoldCreaseRegion;
    Rect rect;
    rect.SetRect(0, 2000.0f, 1000.0f, 200.0f);
    currentFoldCreaseRegion.insert(currentFoldCreaseRegion.end(), rect);
    sheetPattern->currentFoldCreaseRegion_ = currentFoldCreaseRegion;

    auto upScreenHeight =
        sheetLayoutAlgorithm->CalculateSheetHeightInOtherScenes(Referenced::RawPtr(layoutWrapper), 3000.0f);
    EXPECT_EQ(upScreenHeight, 2000.0f - SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx());

    sheetLayoutAlgorithm->sheetMaxHeight_ = 3000.0f;
    sheetLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    auto downScreenHeight =
        sheetLayoutAlgorithm->CalculateSheetHeightInOtherScenes(Referenced::RawPtr(layoutWrapper), 3000.0f);
    EXPECT_EQ(downScreenHeight, 3000.0f - SHEET_HOVERMODE_DOWN_HEIGHT.ConvertToPx() - 2200.0f);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetOffsetInOtherScenes001
 * @tc.desc: Branch: if (sheetType_ != SheetType::SHEET_CENTER || !isHoverMode_)
 *           Condition: sheetLayoutAlgorithm->isWaterfallWindowMode_ = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, CalculateSheetOffsetInOtherScenes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();

    /**
     * @tc.steps: step2. set some parameters of sheetLayoutAlgorithm.
     */
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetTheme_->isOuterBorderEnable_ = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->isHalfFoldHoverStatus_ = false;
    sheetLayoutAlgorithm->isWaterfallWindowMode_ = false;

    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(sheetGeometryNode, nullptr);
    sheetGeometryNode->SetFrameSize(SizeF(100.0f, 300.0f));

    /**
     * @tc.steps: step3. set currentFoldCreaseRegion and compute sheetOffsetY.
     */
    sheetLayoutAlgorithm->isHoverMode_ = true;
    sheetLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    std::vector<Rect> currentFoldCreaseRegion;
    Rect rect;
    rect.SetRect(0, 2000.0f, 1000.0f, 200.0f);
    currentFoldCreaseRegion.insert(currentFoldCreaseRegion.end(), rect);
    sheetPattern->currentFoldCreaseRegion_ = currentFoldCreaseRegion;

    sheetLayoutAlgorithm->CalculateSheetOffsetInOtherScenes(Referenced::RawPtr(layoutWrapper));
    auto sheetOffsetY =
        SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx() + (2000.0f - SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx() - 300.0f) / 2;
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, sheetOffsetY);

    sheetLayoutAlgorithm->sheetMaxHeight_ = 2800.0f;
    sheetLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    sheetLayoutAlgorithm->CalculateSheetOffsetInOtherScenes(Referenced::RawPtr(layoutWrapper));
    sheetOffsetY = 2200.0f + (2800.0f - SHEET_HOVERMODE_DOWN_HEIGHT.ConvertToPx() - 2200.0f - 300.0f) / 2;
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, sheetOffsetY);
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: StartSheetTransitionAnimation001
 * @tc.desc: Increase the coverage of SheetPresentationPattern::StartSheetTransitionAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, StartSheetTransitionAnimation001, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->sheetObject_, nullptr);
    AnimationOption option;
    float offset = 0.0f;
    sheetPattern->StartSheetTransitionAnimation(option, false, offset);
    auto overlayManager = sheetPattern->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    EXPECT_TRUE(overlayManager->modalStack_.empty());
}

/**
 * @tc.name: SetWindowUseImplicitAnimation001
 * @tc.desc: Branch: if (sheetStyle.showInSubWindow.value_or(false))
 *           Condition: sheetStyle.showInSubWindow = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, SetWindowUseImplicitAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 301, AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. set sheetStyle.showInSubWindow true.
     */
    SheetStyle sheetStyle;
    sheetStyle.showInSubWindow = true;
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowManager = pipelineContext->windowManager_;
    pipelineContext->windowManager_ = nullptr;

    /**
     * @tc.steps: step2. set useImplicitAnimationCallback_.
     * @tc.expected: isUseImplicit will be changed.
     */
    pipelineContext->windowManager_ = windowManager;
    bool isUseImplicit = false;
    pipelineContext->windowManager_->useImplicitAnimationCallback_ = [&isUseImplicit](bool m) { isUseImplicit = m; };

    /**
     * @tc.expected: isUseImplicit is false.
     */
    sheetPattern->SetWindowUseImplicitAnimation(AceType::RawPtr(sheetNode), true);
    EXPECT_EQ(isUseImplicit, false);

    /**
     * @tc.steps: step3. set sheetStyle.showInSubWindow false.
     * @tc.expected: isUseImplicit is true.
     */
    sheetStyle.showInSubWindow = false;
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->SetWindowUseImplicitAnimation(AceType::RawPtr(sheetNode), true);
    EXPECT_EQ(isUseImplicit, true);
    pipelineContext->windowManager_->useImplicitAnimationCallback_ = nullptr;
    pipelineContext->windowManager_ = nullptr;
    SheetPresentationTestThreeNg::TearDownTestCase();
}

/**
 * @tc.name: IsNeedChangeScrollHeight001
 * @tc.desc: Test IsNeedChangeScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, IsNeedChangeScrollHeight001, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    // Make the lowest detentSize is not in the end of the vector
    sheetPattern->sheetDetentHeight_.emplace_back(50.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(60.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(70.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(40.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(80.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(90.0f);
    // Make height great than lowest value of detentSize
    sheetPattern->height_ = 45;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    sheetPattern->scrollSizeMode_ = ScrollSizeMode::CONTINUOUS;
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);

    bool isNeedChangeScrollHeight = sheetPattern->IsNeedChangeScrollHeight(sheetPattern->height_);
    ASSERT_TRUE(isNeedChangeScrollHeight);
}

/**
 * @tc.name: IsNeedChangeScrollHeight002
 * @tc.desc: Test IsNeedChangeScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, IsNeedChangeScrollHeight002, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    // Make the lowest detentSize is in the end of the vector
    sheetPattern->sheetDetentHeight_.emplace_back(50.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(60.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(70.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(80.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(90.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(40.0f);
    // Make height great than lowest value of detentSize
    sheetPattern->height_ = 120;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    sheetPattern->scrollSizeMode_ = ScrollSizeMode::CONTINUOUS;
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);

    bool isNeedChangeScrollHeight = sheetPattern->IsNeedChangeScrollHeight(sheetPattern->height_);
    ASSERT_TRUE(isNeedChangeScrollHeight);
}

/**
 * @tc.name: IsNeedChangeScrollHeight003
 * @tc.desc: Test IsNeedChangeScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestThreeNg, IsNeedChangeScrollHeight003, TestSize.Level1)
{
    SheetPresentationTestThreeNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    // Make the lowest detentSize is not in the end of the vector
    sheetPattern->sheetDetentHeight_.emplace_back(50.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(60.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(70.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(40.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(80.0f);
    sheetPattern->sheetDetentHeight_.emplace_back(90.0f);
    // Make height great than lowest value of detentSize
    sheetPattern->height_ = 45;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    // Make scroll size mode is not continuous
    sheetPattern->scrollSizeMode_ = ScrollSizeMode::FOLLOW_DETENT;
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);

    bool isNeedChangeScrollHeight = sheetPattern->IsNeedChangeScrollHeight(sheetPattern->height_);
    ASSERT_FALSE(isNeedChangeScrollHeight);
}
} // namespace OHOS::Ace::NG