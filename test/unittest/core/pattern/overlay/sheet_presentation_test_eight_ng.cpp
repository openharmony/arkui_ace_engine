/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/base/window/mock_foldable_window.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"

#include "base/geometry/rect.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/root/root_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SheetPresentationTestEightNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void TearDownTestCase();
    static void SetApiVersion(int32_t apiTargetVersion);

private:
    static RefPtr<FrameNode> CreateSheetNode(SheetType sheetType);
    static RefPtr<SheetPresentationLayoutAlgorithm> CreateLayoutAlgorithm(SheetType sheetType);
};

void SheetPresentationTestEightNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
            sheetTheme->closeIconButtonWidth_ = SHEET_CLOSE_ICON_WIDTH;
            sheetTheme->centerDefaultWidth_ = SHEET_LANDSCAPE_WIDTH;
            sheetTheme->sheetCloseIconTitleSpaceNew_ = SHEET_CLOSE_ICON_TITLE_SPACE_NEW;
            sheetTheme->sheetHeightPercentMax_ = 0.95f;
            sheetTheme->bigWindowMinHeight_ = Dimension(320.0_vp);
            return sheetTheme;
        } else {
            return nullptr;
        }
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly([](ThemeType type, int32_t) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
            sheetTheme->closeIconButtonWidth_ = SHEET_CLOSE_ICON_WIDTH;
            sheetTheme->centerDefaultWidth_ = SHEET_LANDSCAPE_WIDTH;
            sheetTheme->sheetCloseIconTitleSpaceNew_ = SHEET_CLOSE_ICON_TITLE_SPACE_NEW;
            sheetTheme->sheetHeightPercentMax_ = 0.95f;
            sheetTheme->bigWindowMinHeight_ = Dimension(320.0_vp);
            return sheetTheme;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPresentationTestEightNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type)
                             -> RefPtr<Theme> {
            if (type == SheetTheme::TypeId()) {
                return sheetTheme.Upgrade();
            } else {
                return nullptr;
            }
        });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPresentationTestEightNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetPresentationTestEightNg::SetApiVersion(int32_t apiTargetVersion)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(apiTargetVersion);
}

RefPtr<FrameNode> SheetPresentationTestEightNg::CreateSheetNode(SheetType sheetType)
{
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
            "SheetPresentation", std::move(callback)));
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    sheetStyle.sheetType = sheetType;
    layoutProperty->propSheetStyle_ = sheetStyle;
    pattern->sheetThemeType_ = "popup";
    return sheetNode;
}

RefPtr<SheetPresentationLayoutAlgorithm> SheetPresentationTestEightNg::CreateLayoutAlgorithm(SheetType sheetType)
{
    SheetPopupInfo popupInfo;
    auto layoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>(sheetType, popupInfo);
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    layoutAlgorithm->sheetMaxWidth_ = 1000.0f;
    return layoutAlgorithm;
}

/**
 * @tc.name: CalcMaxHeightMinusDoubleStatusBarHeight001
 * @tc.desc: Test CalcMaxHeightMinusDoubleStatusBarHeight with API version >= 26, SHEET_CENTER type
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalcMaxHeightMinusDoubleStatusBarHeight001, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    double maxHeight = 800.0f;
    float sheetMaxHeight = 1000.0f;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetTopSafeArea_ = 50.0f;

    layoutAlgorithm->CalcMaxHeightMinusDoubleStatusBarHeight(
        Referenced::RawPtr(layoutWrapper), maxHeight, sheetMaxHeight);

    double expectedMaxHeight = std::min(800.0f, 1000.0f - 50.0f * 2);
    EXPECT_EQ(maxHeight, expectedMaxHeight);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalcMaxHeightMinusDoubleStatusBarHeight002
 * @tc.desc: Test CalcMaxHeightMinusDoubleStatusBarHeight with API version < 26, SHEET_CENTER type
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalcMaxHeightMinusDoubleStatusBarHeight002, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    double maxHeight = 800.0f;
    float sheetMaxHeight = 1000.0f;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetTopSafeArea_ = 50.0f;

    layoutAlgorithm->CalcMaxHeightMinusDoubleStatusBarHeight(
        Referenced::RawPtr(layoutWrapper), maxHeight, sheetMaxHeight);

    EXPECT_EQ(maxHeight, 800.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalcMaxHeightMinusDoubleStatusBarHeight003
 * @tc.desc: Test CalcMaxHeightMinusDoubleStatusBarHeight with SHEET_BOTTOM type (should not modify)
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalcMaxHeightMinusDoubleStatusBarHeight003, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_BOTTOM);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;

    double maxHeight = 800.0f;
    float sheetMaxHeight = 1000.0f;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetTopSafeArea_ = 50.0f;

    layoutAlgorithm->CalcMaxHeightMinusDoubleStatusBarHeight(
        Referenced::RawPtr(layoutWrapper), maxHeight, sheetMaxHeight);

    // SHEET_BOTTOM should not modify maxHeight
    EXPECT_EQ(maxHeight, 800.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalcMaxHeightMinusDoubleStatusBarHeight004
 * @tc.desc: Test CalcMaxHeightMinusDoubleStatusBarHeight with zero safe area (boundary value)
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalcMaxHeightMinusDoubleStatusBarHeight004, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    double maxHeight = 800.0f;
    float sheetMaxHeight = 1000.0f;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetTopSafeArea_ = 0.0f;

    layoutAlgorithm->CalcMaxHeightMinusDoubleStatusBarHeight(
        Referenced::RawPtr(layoutWrapper), maxHeight, sheetMaxHeight);

    EXPECT_EQ(maxHeight, 800.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes001
 * @tc.desc: Test CalculateSheetHeightInOtherScenes with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalculateSheetHeightInOtherScenes001, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    layoutAlgorithm->isHoverMode_ = true;
    layoutAlgorithm->hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;

    float heightBefore = 800.0f;
    float result = layoutAlgorithm->CalculateSheetHeightInOtherScenes(nullptr, heightBefore);

    EXPECT_EQ(result, heightBefore);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes002
 * @tc.desc: Test CalculateSheetHeightInOtherScenes with SHEET_CENTER type and hover mode enabled
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalculateSheetHeightInOtherScenes002, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    layoutAlgorithm->isHoverMode_ = true;
    layoutAlgorithm->hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    Rect foldCreaseRect(100.0, 500.0, 900.0, 600.0);
    sheetPattern->currentFoldCreaseRegion_ = {foldCreaseRect};

    float heightBefore = 800.0f;
    float result = layoutAlgorithm->CalculateSheetHeightInOtherScenes(
        Referenced::RawPtr(layoutWrapper), heightBefore);

    float maxUpSheetHeight = foldCreaseRect.Top() - SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx();
    float expected = std::min(heightBefore, maxUpSheetHeight);
    EXPECT_EQ(result, expected);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes003
 * @tc.desc: Test CalculateSheetHeightInOtherScenes with SHEET_CENTER type, hover mode, BOTTOM_SCREEN area
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalculateSheetHeightInOtherScenes003, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    layoutAlgorithm->isHoverMode_ = true;
    layoutAlgorithm->hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    Rect foldCreaseRect(100.0, 500.0, 900.0, 600.0);
    sheetPattern->currentFoldCreaseRegion_ = {foldCreaseRect};

    float heightBefore = 800.0f;
    float result = layoutAlgorithm->CalculateSheetHeightInOtherScenes(
        Referenced::RawPtr(layoutWrapper), heightBefore);

    float maxDownSheetHeight =
        layoutAlgorithm->sheetMaxHeight_ - SHEET_HOVERMODE_DOWN_HEIGHT.ConvertToPx() - foldCreaseRect.Bottom();
    float expected = std::min(heightBefore, maxDownSheetHeight);
    EXPECT_EQ(result, expected);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes004
 * @tc.desc: Test CalculateSheetHeightInOtherScenes with hover mode disabled
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalculateSheetHeightInOtherScenes004, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    layoutAlgorithm->isHoverMode_ = false;

    float heightBefore = 800.0f;
    float result = layoutAlgorithm->CalculateSheetHeightInOtherScenes(
        Referenced::RawPtr(layoutWrapper), heightBefore);

    EXPECT_EQ(result, heightBefore);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes005
 * @tc.desc: Test CalculateSheetHeightInOtherScenes with SHEET_BOTTOM type
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalculateSheetHeightInOtherScenes005, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_BOTTOM);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    layoutAlgorithm->isHoverMode_ = true;

    float heightBefore = 800.0f;
    float result = layoutAlgorithm->CalculateSheetHeightInOtherScenes(
        Referenced::RawPtr(layoutWrapper), heightBefore);

    EXPECT_EQ(result, heightBefore);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetHeightInOtherScenes006
 * @tc.desc: Test CalculateSheetHeightInOtherScenes with keyboard showing
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, CalculateSheetHeightInOtherScenes006, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    layoutAlgorithm->isHoverMode_ = true;
    layoutAlgorithm->isKeyBoardShow_ = true;
    layoutAlgorithm->hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    Rect foldCreaseRect(100.0, 500.0, 900.0, 600.0);
    sheetPattern->currentFoldCreaseRegion_ = {foldCreaseRect};

    float heightBefore = 800.0f;
    float result = layoutAlgorithm->CalculateSheetHeightInOtherScenes(
        Referenced::RawPtr(layoutWrapper), heightBefore);

    float maxUpSheetHeight = foldCreaseRect.Top() - SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx();
    float expected = std::min(heightBefore, maxUpSheetHeight);
    EXPECT_EQ(result, expected);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightByScreenSizeType001
 * @tc.desc: Test GetHeightByScreenSizeType with SHEET_BOTTOM type
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightByScreenSizeType001, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_BOTTOM);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightByScreenSizeType(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_EQ(result, parentConstraintHeight);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightByScreenSizeType002
 * @tc.desc: Test GetHeightByScreenSizeType with SHEET_CENTER type
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightByScreenSizeType002, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightByScreenSizeType(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightByScreenSizeType003
 * @tc.desc: Test GetHeightByScreenSizeType with SHEET_POPUP type, API < 18
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightByScreenSizeType003, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_POPUP);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_POPUP);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightByScreenSizeType(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightByScreenSizeType004
 * @tc.desc: Test GetHeightByScreenSizeType with SHEET_POPUP type, API >= 18
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightByScreenSizeType004, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_POPUP);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_POPUP);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightByScreenSizeType(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightByScreenSizeType005
 * @tc.desc: Test GetHeightByScreenSizeType with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightByScreenSizeType005, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    layoutAlgorithm->sheetMaxHeight_ = 1000.0f;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightByScreenSizeType(parentConstraintHeight, parentConstraintWidth, nullptr);

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightBySheetStyle001
 * @tc.desc: Test GetHeightBySheetStyle with SheetMode::MEDIUM
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightBySheetStyle001, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.sheetHeight.height = Dimension(500.0_vp);
    layoutProperty->propSheetStyle_ = sheetStyle;
    layoutAlgorithm->sheetStyle_ = sheetStyle;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightBySheetStyle(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightBySheetStyle002
 * @tc.desc: Test GetHeightBySheetStyle with SheetMode::LARGE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightBySheetStyle002, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::LARGE;
    layoutProperty->propSheetStyle_ = sheetStyle;
    layoutAlgorithm->sheetStyle_ = sheetStyle;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightBySheetStyle(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightBySheetStyle003
 * @tc.desc: Test GetHeightBySheetStyle with SheetMode::AUTO
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightBySheetStyle003, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::AUTO;
    layoutProperty->propSheetStyle_ = sheetStyle;
    layoutAlgorithm->sheetStyle_ = sheetStyle;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightBySheetStyle(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightBySheetStyle004
 * @tc.desc: Test GetHeightBySheetStyle with percent height dimension
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightBySheetStyle004, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.sheetHeight.height = Dimension(50.0, DimensionUnit::PERCENT);
    layoutProperty->propSheetStyle_ = sheetStyle;
    layoutAlgorithm->sheetStyle_ = sheetStyle;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightBySheetStyle(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightBySheetStyle005
 * @tc.desc: Test GetHeightBySheetStyle with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, GetHeightBySheetStyle005, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    sheetStyle.sheetHeight.height = Dimension(500.0_vp);
    layoutAlgorithm->sheetStyle_ = sheetStyle;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->GetHeightBySheetStyle(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeMaxHeight001
 * @tc.desc: Test ComputeMaxHeight in normal mode
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ComputeMaxHeight001, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->ComputeMaxHeight(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeMaxHeight003
 * @tc.desc: Test ComputeMaxHeight with API version >= 26
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ComputeMaxHeight003, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetTopSafeArea_ = 50.0f;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->ComputeMaxHeight(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeMaxHeight004
 * @tc.desc: Test ComputeMaxHeight with API version < 26
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ComputeMaxHeight004, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    auto layoutAlgorithm = CreateLayoutAlgorithm(SheetType::SHEET_CENTER);
    layoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetTopSafeArea_ = 50.0f;

    float parentConstraintHeight = 1000.0f;
    float parentConstraintWidth = 800.0f;
    float result = layoutAlgorithm->ComputeMaxHeight(
        parentConstraintHeight, parentConstraintWidth, Referenced::RawPtr(layoutWrapper));

    EXPECT_GT(result, 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetBackgroundColor001
 * @tc.desc: Test SetSheetBackgroundColor with API >= 12, no systemMaterial, backgroundColor has value
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, SetSheetBackgroundColor001, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    sheetStyle.backgroundColor = Color::BLUE;
    layoutProperty->propSheetStyle_ = sheetStyle;

    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBackgoundColor_ = Color::WHITE;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(sheetNode);
    overlayManager->SetSheetBackgroundColor(sheetNode, sheetTheme, sheetStyle, true);

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto backgroundColor = renderContext->GetBackgroundColorValue();
    EXPECT_EQ(backgroundColor, Color::BLUE);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetBackgroundColor002
 * @tc.desc: Test SetSheetBackgroundColor with API >= 12, no systemMaterial, no backgroundColor, isPartialUpdate=false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, SetSheetBackgroundColor002, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;

    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBackgoundColor_ = Color::WHITE;

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(sheetNode);
    overlayManager->SetSheetBackgroundColor(sheetNode, sheetTheme, sheetStyle, false);

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto backgroundColor = renderContext->GetBackgroundColorValue();
    EXPECT_EQ(backgroundColor, Color::WHITE);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetBackgroundColor003
 * @tc.desc: Test SetSheetBackgroundColor with API >= 12, systemMaterial, UiMaterialLevel::SMOOTH
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, SetSheetBackgroundColor003, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();
    SheetPresentationTestEightNg::SetApiVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    SheetStyle sheetStyle;
    sheetStyle.backgroundColor = Color::BLUE;
    auto material = AceType::MakeRefPtr<UiMaterial>();
    sheetStyle.systemMaterial = material;
    layoutProperty->propSheetStyle_ = sheetStyle;

    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBackgoundColor_ = Color::WHITE;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(sheetNode);
    overlayManager->SetSheetBackgroundColor(sheetNode, sheetTheme, sheetStyle, true);

    auto backgroundColor = renderContext->GetBackgroundColorValue();
    EXPECT_EQ(backgroundColor, Color::WHITE);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateSheetBackgroundColor002
 * @tc.desc: Test UpdateSheetBackgroundColor with systemMaterial and UiMaterialLevel != SMOOTH, returns early
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, UpdateSheetBackgroundColor002, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("sheetNode", 001,
        AceType::MakeRefPtr<SheetPresentationPattern>(002, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    auto material = AceType::MakeRefPtr<UiMaterial>();
    sheetStyle.systemMaterial = material;
    layoutProperty->propSheetStyle_ = sheetStyle;

    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    sheetPattern->UpdateSheetBackgroundColor();

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_FALSE(renderContext->HasBackgroundColor());

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate001
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate when isOnDisappearing_ is false, no translation should be set
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate001, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->isOnDisappearing_ = false;
    sheetPattern->pageHeight_ = 800.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate002
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_BOTTOM type and isOnDisappearing_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate002, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1000.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate003
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_BOTTOMLANDSPACE type and isOnDisappearing_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate003, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOMLANDSPACE);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1200.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1200.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate004
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CENTER type and isOnDisappearing_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate004, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1500.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1500.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate005
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER type, modalTransition DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate005, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 600.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 600.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate006
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER type, modalTransition NONE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate006, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::NONE;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 600.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate007
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER type, modalTransition ALPHA
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate007, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::ALPHA;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 600.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate008
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_POPUP type and isOnDisappearing_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate008, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_POPUP);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate009
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_SIDE type and isOnDisappearing_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate009, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_SIDE);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_SIDE;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_SIDE;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate010
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_BOTTOM_OFFSET type and isOnDisappearing_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate010, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM_OFFSET);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM_OFFSET;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_OFFSET;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate011
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER type, no modalTransition set (default)
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate011, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 500.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 500.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate012
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_MINIMIZE type and isOnDisappearing_ is true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate012, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_MINIMIZE);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_MINIMIZE;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_MINIMIZE;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate013
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_BOTTOM type, pageHeight_ is zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate013, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 0.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate014
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CENTER type, pageHeight_ is large value
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate014, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 2000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 2000.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate015
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER, geometryNode height is zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate015, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 0.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate016
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER, geometryNode height is large
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate016, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 1800.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1800.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate017
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_BOTTOMLANDSPACE, pageHeight_ is negative (edge case)
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate017, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOMLANDSPACE);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = -100.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), -100.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate018
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate transition from false to true state
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate018, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->pageHeight_ = 800.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->isOnDisappearing_ = false;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 800.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate019
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_BOTTOM_FREE_WINDOW type
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate019, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM_FREE_WINDOW);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate020
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate multiple calls with different sheetType
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate020, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 900.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 900.0f);

    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 900.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate021
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with x and z translation values should be zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate021, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1000.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate022
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER, x and z should be zero
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate022, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(1000.0f, 750.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 750.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate023
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with sheetStyle having other properties set
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate023, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetStyle.backgroundColor = Color::BLUE;
    sheetStyle.maskColor = Color::BLACK;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1100.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1100.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate024
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER and sheetStyle with backgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate024, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    sheetStyle.backgroundColor = Color::RED;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(600.0f, 400.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 400.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate025
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate after changing pageHeight_ multiple times
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate025, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->isOnDisappearing_ = true;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->pageHeight_ = 500.0f;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 500.0f);

    sheetPattern->pageHeight_ = 1500.0f;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1500.0f);

    sheetPattern->pageHeight_ = 800.0f;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 800.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate026
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with geometryNode having different width
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate026, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200.0f, 300.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 300.0f);
    EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate027
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with isOnDisappearing_ toggling
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate027, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1000.0f);

    sheetPattern->isOnDisappearing_ = false;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1000.0f);

    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1200.0f;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1200.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate028
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with all bottom-style sheet types in sequence
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate028, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    std::vector<SheetType> bottomTypes = {
        SheetType::SHEET_BOTTOM,
        SheetType::SHEET_BOTTOMLANDSPACE,
        SheetType::SHEET_CENTER
    };

    for (const auto& sheetType : bottomTypes) {
        auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        SheetStyle sheetStyle;
        sheetStyle.sheetType = sheetType;
        layoutProperty->propSheetStyle_ = sheetStyle;
        sheetPattern->sheetType_ = sheetType;

        sheetPattern->ReachToBottomWhenCloseAndRotate();
        ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
        EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1000.0f);
        EXPECT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
        EXPECT_EQ(renderContext->GetTransformTranslate()->z.ConvertToPx(), 0.0f);
    }

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate029
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER multiple modalTransition values
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate029, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 600.0f));

    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    SheetStyle sheetStyleDefault;
    sheetStyleDefault.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyleDefault.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyleDefault;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 600.0f);

    SheetStyle sheetStyleNone;
    sheetStyleNone.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyleNone.modalTransition = ModalTransition::NONE;
    layoutProperty->propSheetStyle_ = sheetStyleNone;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 600.0f);

    SheetStyle sheetStyleAlpha;
    sheetStyleAlpha.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyleAlpha.modalTransition = ModalTransition::ALPHA;
    layoutProperty->propSheetStyle_ = sheetStyleAlpha;
    sheetPattern->ReachToBottomWhenCloseAndRotate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 600.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate030
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_BOTTOMLANDSPACE special pageHeight values
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate030, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOMLANDSPACE);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetPattern->isOnDisappearing_ = true;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    std::vector<float> pageHeights = { 0.0f, 100.0f, 500.0f, 1000.0f, 2000.0f, -50.0f };

    for (const auto& pageHeight : pageHeights) {
        sheetPattern->pageHeight_ = pageHeight;
        sheetPattern->ReachToBottomWhenCloseAndRotate();
        ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
        EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), pageHeight);
    }

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate031
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate boundary condition - very small pageHeight
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate031, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_BOTTOM);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate032
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate boundary condition - very large pageHeight
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate032, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CENTER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 10000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 10000.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate033
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER boundary - very small height
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate033, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 1.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 1.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate034
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with SHEET_CONTENT_COVER boundary - very large height
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate034, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_CONTENT_COVER);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CONTENT_COVER;
    sheetStyle.modalTransition = ModalTransition::DEFAULT;
    layoutProperty->propSheetStyle_ = sheetStyle;

    sheetPattern->sheetType_ = SheetType::SHEET_CONTENT_COVER;
    sheetPattern->isOnDisappearing_ = true;

    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800.0f, 10000.0f));

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    sheetPattern->ReachToBottomWhenCloseAndRotate();

    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 10000.0f);

    SheetPresentationTestEightNg::TearDownTestCase();
}

/**
 * @tc.name: ReachToBottomWhenCloseAndRotate035
 * @tc.desc: Test ReachToBottomWhenCloseAndRotate with all non-bottom types that should not translate
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestEightNg, ReachToBottomWhenCloseAndRotate035, TestSize.Level1)
{
    SheetPresentationTestEightNg::SetUpTestCase();

    auto sheetNode = CreateSheetNode(SheetType::SHEET_POPUP);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->pageHeight_ = 1000.0f;

    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    std::vector<SheetType> nonTranslateTypes = {
        SheetType::SHEET_POPUP,
        SheetType::SHEET_SIDE,
        SheetType::SHEET_BOTTOM_OFFSET,
        SheetType::SHEET_MINIMIZE,
        SheetType::SHEET_BOTTOM_FREE_WINDOW
    };

    for (const auto& sheetType : nonTranslateTypes) {
        auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
        ASSERT_NE(layoutProperty, nullptr);
        SheetStyle sheetStyle;
        sheetStyle.sheetType = sheetType;
        layoutProperty->propSheetStyle_ = sheetStyle;
        sheetPattern->sheetType_ = sheetType;

        sheetPattern->ReachToBottomWhenCloseAndRotate();
        EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);
    }

    SheetPresentationTestEightNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG
