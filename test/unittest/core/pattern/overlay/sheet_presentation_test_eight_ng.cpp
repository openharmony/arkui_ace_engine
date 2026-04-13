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

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/rect.h"
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

    EXPECT_EQ(maxHeight, 800.0f);

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

    double expectedMaxHeight = std::min(800.0f, 1000.0f - 50.0f * 2);
    EXPECT_EQ(maxHeight, expectedMaxHeight);

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

} // namespace OHOS::Ace::NG
