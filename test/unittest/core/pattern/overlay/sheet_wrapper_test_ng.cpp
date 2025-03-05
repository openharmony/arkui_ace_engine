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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
} // namespace
class SheetWrapperTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SheetWrapperTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetWrapperTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DecreaseArrowHeightWhenArrowIsShown001
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(VERSION_EIGHTEEN)) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, DecreaseArrowHeightWhenArrowIsShown001, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 400.0f;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 1000.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 400.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: DecreaseArrowHeightWhenArrowIsShown002
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!prePopupInfo.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, DecreaseArrowHeightWhenArrowIsShown002, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 400.0f;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 1000.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 400.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: DecreaseArrowHeightWhenArrowIsShown003
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!prePopupInfo.showArrow) = false
 *           Branch: case Placement::BOTTOM_LEFT = true
 *           Branch: case Placement::BOTTOM_RIGHT = true
 *           Branch: case Placement::BOTTOM = true
 *           Branch: case Placement::TOP_LEFT = true
 *           Branch: case Placement::TOP_RIGHT = true
 *           Branch: case Placement::TOP = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, DecreaseArrowHeightWhenArrowIsShown003, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 1000.0f;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 992.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 984.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 976.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 968.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 960.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 952.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: DecreaseArrowHeightWhenArrowIsShown004
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!prePopupInfo.showArrow) = false
 *           Branch: case Placement::RIGHT_TOP = true
 *           Branch: case Placement::RIGHT_BOTTOM = true
 *           Branch: case Placement::RIGHT = true
 *           Branch: case Placement::LEFT_TOP = true
 *           Branch: case Placement::LEFT_BOTTOM = true
 *           Branch: case Placement::LEFT = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, DecreaseArrowHeightWhenArrowIsShown004, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 400.0f;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 392.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 384.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 376.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 368.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 360.0f);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 352.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: DecreaseArrowHeightWhenArrowIsShown005
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!prePopupInfo.showArrow) = false
 *           Branch: default = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, DecreaseArrowHeightWhenArrowIsShown005, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 400.0f;

    sheetWrapperLayoutAlgorithm->DecreaseArrowHeightWhenArrowIsShown(sheetNode);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetHeight_, 1000.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetWidth_, 400.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetLeftSpaceWithPlacement001
 * @tc.desc: Branch: case Placement::BOTTOM_LEFT = true
 *           Branch: case Placement::BOTTOM_RIGHT = true
 *           Branch: case Placement::BOTTOM = true
 *           Branch: if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusTopLeft->ConvertToPx() +
 *              sheetRadius_.radiusTopRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 *           Branch: if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusTopLeft->ConvertToPx() +
 *              sheetRadius_.radiusTopRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetLeftSpaceWithPlacement001, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.width_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.height_ = 800.0f;
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 0.0f;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 900.0_vp;

    SizeF sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::BOTTOM_LEFT, SizeF(), OffsetF());
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 1000.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 786.0f);

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::BOTTOM_RIGHT, SizeF(), OffsetF());
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 1000.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 786.0f);

    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 700.0_vp;

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::BOTTOM, SizeF(), OffsetF());
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 1000.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 778.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetLeftSpaceWithPlacement002
 * @tc.desc: Branch: case Placement::TOP_LEFT = true
 *           Branch: case Placement::TOP_RIGHT = true
 *           Branch: case Placement::TOP = true
 *           Branch: if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
                sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 *           Branch: if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
                sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetLeftSpaceWithPlacement002, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.width_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.height_ = 800.0f;
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 0.0f;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 900.0_vp;

    SizeF sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::TOP_LEFT, SizeF(), OffsetF(0.0f, 1000.0f));
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 1000.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 986.0f);

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::TOP_RIGHT, SizeF(), OffsetF(0.0f, 1000.0f));
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 1000.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 986.0f);

    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 700.0_vp;

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::TOP, SizeF(), OffsetF(0.0f, 1000.0f));
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 1000.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 978.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetLeftSpaceWithPlacement003
 * @tc.desc: Branch: case Placement::RIGHT_TOP = true
 *           Branch: case Placement::RIGHT_BOTTOM = true
 *           Branch: case Placement::RIGHT = true
 *           Branch: if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopLeft->ConvertToPx() +
                sheetRadius_.radiusBottomLeft->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 *           Branch: if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopLeft->ConvertToPx() +
                sheetRadius_.radiusBottomLeft->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetLeftSpaceWithPlacement003, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.width_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.height_ = 800.0f;
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 0.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 700.0_vp;

    SizeF sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::RIGHT_TOP, SizeF(), OffsetF());
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 986.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 788.0f);

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::RIGHT_BOTTOM, SizeF(), OffsetF());
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 986.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 788.0f);

    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 500.0_vp;

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::RIGHT, SizeF(), OffsetF());
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 978.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 788.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetLeftSpaceWithPlacement004
 * @tc.desc: Branch: case Placement::LEFT_TOP = true
 *           Branch: case Placement::LEFT_BOTTOM = true
 *           Branch: case Placement::LEFT = true
 *           Branch: if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
                sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 *           Branch: if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
                sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetLeftSpaceWithPlacement004, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.width_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.height_ = 800.0f;
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 0.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 700.0_vp;

    SizeF sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::LEFT_TOP, SizeF(), OffsetF(1000.0f, 0.0f));
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 986.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 788.0f);

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::LEFT_BOTTOM, SizeF(), OffsetF(1000.0f, 0.0f));
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 986.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 788.0f);

    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 500.0_vp;

    sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::LEFT, SizeF(), OffsetF(1000.0f, 0.0f));
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 978.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 788.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetLeftSpaceWithPlacement005
 * @tc.desc: Branch: default = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetLeftSpaceWithPlacement005, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };

    SizeF sheetWrapperLeftSpace = sheetWrapperLayoutAlgorithm->GetLeftSpaceWithPlacement(
        Placement::NONE, SizeF(), OffsetF());
    EXPECT_EQ(sheetWrapperLeftSpace.Width(), 0.0f);
    EXPECT_EQ(sheetWrapperLeftSpace.Height(), 0.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: RecheckBestPlacementWithInsufficientSpace001
 * @tc.desc: Branch: if (curLeftSpace.Width() >= sheetWidth_ && curLeftSpace.Height() < sheetHeight_) = false
 *           Condition: curLeftSpace.Width() >= sheetWidth_ = false
 *           Branch: if (curLeftSpace.Width() >= sheetWidth_ && curLeftSpace.Height() < sheetHeight_) = false
 *           Condition: curLeftSpace.Width() >= sheetWidth_ = true, curLeftSpace.Height() < sheetHeight_ = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, RecheckBestPlacementWithInsufficientSpace001, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.width_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.height_ = 800.0f;
    sheetWrapperLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 200.0f;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;

    SizeF bestSize = SizeF(800.0f, 600.0f);
    auto expectedPlacement = sheetWrapperLayoutAlgorithm->RecheckBestPlacementWithInsufficientSpace(
        SizeF(), OffsetF(0.0f, 100.0f), bestSize);
    EXPECT_EQ(expectedPlacement, Placement::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: RecheckBestPlacementWithInsufficientSpace002
 * @tc.desc: Branch: if (curLeftSpace.Width() >= sheetWidth_ && curLeftSpace.Height() < sheetHeight_) = false
 *           Condition: curLeftSpace.Width() >= sheetWidth_ = true, curLeftSpace.Height() < sheetHeight_ = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, RecheckBestPlacementWithInsufficientSpace002, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.width_ = 1000.0f;
    sheetWrapperLayoutAlgorithm->windowGlobalRect_.height_ = 800.0f;
    sheetWrapperLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 0.0f;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;

    SizeF bestSize = SizeF();
    auto expectedPlacement = sheetWrapperLayoutAlgorithm->RecheckBestPlacementWithInsufficientSpace(
        SizeF(800.0f, 600.0f), OffsetF(100.0f, 100.0f), bestSize);
    EXPECT_EQ(expectedPlacement, Placement::BOTTOM_LEFT);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTop001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTop001, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTop002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTop002, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTop003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTop003, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTopLeft001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTopLeft001, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTopLeft(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTopLeft002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTopLeft002, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTopLeft(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTopLeft003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTopLeft003, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTopLeft(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTopRight001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTopRight001, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTopRight(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTopRight002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTopRight002, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTopRight(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithTopRight003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, GetOffsetWithTopRight003, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithTopRight(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: CheckIsArrowOverlapSheetRadius001
 * @tc.desc: Branch: case Placement::BOTTOM_LEFT = true
 *           Branch: case Placement::BOTTOM_RIGHT
 *           Branch: case Placement::BOTTOM
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusTopLeft->ConvertToPx())) = true
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusTopLeft->ConvertToPx())) = false
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *              sheetWidth_ - sheetRadius_.radiusTopRight->ConvertToPx())) = true
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *              sheetWidth_ - sheetRadius_.radiusTopRight->ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, CheckIsArrowOverlapSheetRadius001, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetX = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 150.0_vp;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetX = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 80.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_RIGHT);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetX = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 200.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: CheckIsArrowOverlapSheetRadius002
 * @tc.desc: Branch: case Placement::TOP_LEFT = true
 *           Branch: case Placement::TOP_RIGHT = true
 *           Branch: case Placement::TOP = true
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusBottomLeft->ConvertToPx())) = true
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusBottomLeft->ConvertToPx())) = false
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetWidth_ - sheetRadius_.radiusBottomRight->ConvertToPx())) = true
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetWidth_ - sheetRadius_.radiusBottomRight->ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, CheckIsArrowOverlapSheetRadius002, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetX = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 150.0_vp;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::TOP_LEFT);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetX = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 80.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::TOP_RIGHT);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::TOP;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetX = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 200.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: CheckIsArrowOverlapSheetRadius003
 * @tc.desc: Branch: case Placement::RIGHT_TOP = true
 *           Branch: case Placement::RIGHT_BOTTOM = true
 *           Branch: case Placement::RIGHT = true
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetY - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusTopLeft->ConvertToPx())) = true
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetY - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusTopLeft->ConvertToPx())) = false
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetY + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *               sheetHeight_ - sheetRadius_.radiusBottomLeft->ConvertToPx())) = true
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetY + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *               sheetHeight_ - sheetRadius_.radiusBottomLeft->ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, CheckIsArrowOverlapSheetRadius003, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetY = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 150.0_vp;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::RIGHT_TOP);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetY = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 80.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::RIGHT_BOTTOM);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetY = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 200.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: CheckIsArrowOverlapSheetRadius004
 * @tc.desc: Branch: case Placement::LEFT_TOP = true
 *           Branch: case Placement::LEFT_BOTTOM = true
 *           Branch: case Placement::LEFT = true
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetY - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusTopRight->ConvertToPx())) = true
 *           Branch: if (LessNotEqual(sheetPopupInfo_.arrowOffsetY - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
 *               sheetRadius_.radiusTopRight->ConvertToPx())) = false
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetY + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetHeight_ - sheetRadius_.radiusBottomRight->ConvertToPx())) = true
 *           Branch: if (GreatNotEqual(sheetPopupInfo_.arrowOffsetY + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
 *               sheetHeight_ - sheetRadius_.radiusBottomRight->ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, CheckIsArrowOverlapSheetRadius004, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetY = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 150.0_vp;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::LEFT_TOP);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetY = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 80.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::LEFT_BOTTOM);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetY = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 50.0_vp;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 200.0f;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}

/**
 * @tc.name: CheckIsArrowOverlapSheetRadius005
 * @tc.desc: Branch: default
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperTestNg, CheckIsArrowOverlapSheetRadius005, TestSize.Level1)
{
    SheetWrapperTestNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::NONE;

    sheetWrapperLayoutAlgorithm->CheckIsArrowOverlapSheetRadius();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG