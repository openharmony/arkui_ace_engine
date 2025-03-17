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
class SheetWrapperPaintTestNg : public testing::Test {
public:
    static RefPtr<SheetTheme> sheetTheme_;
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
};

RefPtr<SheetTheme> SheetWrapperPaintTestNg::sheetTheme_ = nullptr;

void SheetWrapperPaintTestNg::SetUpTestCase()
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

void SheetWrapperPaintTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetWrapperPaintTestNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
{
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto pipelineContext = PipelineContext::GetCurrentContext();
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
    sheetTheme_->sheetType_ = "popup";
}

/**
 * @tc.name: IsDrawBorder001
 * @tc.desc: Branch: if (sheetTheme->IsOuterBorderEnable() && sheetType == SheetType::SHEET_POPUP &&
 *               !sheetStyle.borderWidth.has_value()) = false
 *           Condition: sheetTheme->IsOuterBorderEnable() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, IsDrawBorder001, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    columnNode->AddChild(sheetNode);
    auto sheetPaintWrapper = new PaintWrapper(columnNode->GetRenderContext(),
        sheetNode->GetGeometryNode(), sheetNode->GetPaintProperty<PaintProperty>());
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetLayoutProperty->propSheetStyle_ = sheetStyle;
    sheetTheme_->isOuterBorderEnable_ = false;

    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    bool ret = sheetWrapperPaintMethod->IsDrawBorder(sheetPaintWrapper);
    EXPECT_FALSE(ret);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: IsDrawBorder002
 * @tc.desc: Branch: if (sheetTheme->IsOuterBorderEnable() && sheetType == SheetType::SHEET_POPUP &&
 *               !sheetStyle.borderWidth.has_value()) = false
 *           Condition: sheetTheme->IsOuterBorderEnable() = true, sheetType == SheetType::SHEET_POPUP = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, IsDrawBorder002, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    columnNode->AddChild(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    SheetWrapperPaintTestNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    auto sheetPaintWrapper = new PaintWrapper(columnNode->GetRenderContext(),
        sheetNode->GetGeometryNode(), sheetNode->GetPaintProperty<PaintProperty>());
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetTheme_->isOuterBorderEnable_ = true;

    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    bool ret = sheetWrapperPaintMethod->IsDrawBorder(sheetPaintWrapper);
    EXPECT_FALSE(ret);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: IsDrawBorder003
 * @tc.desc: Branch: if (sheetTheme->IsOuterBorderEnable() && sheetType == SheetType::SHEET_POPUP &&
 *               !sheetStyle.borderWidth.has_value()) = false
 *           Condition: sheetTheme->IsOuterBorderEnable() = true, sheetType == SheetType::SHEET_POPUP = true,
 *               !sheetStyle.borderWidth.has_value() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, IsDrawBorder003, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    columnNode->AddChild(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    SheetWrapperPaintTestNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    auto sheetPaintWrapper = new PaintWrapper(columnNode->GetRenderContext(),
        sheetNode->GetGeometryNode(), sheetNode->GetPaintProperty<PaintProperty>());
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->propSheetStyle_->borderWidth = { 5.0_vp, 5.0_vp, 5.0_vp, 5.0_vp };
    sheetTheme_->isOuterBorderEnable_ = true;

    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    bool ret = sheetWrapperPaintMethod->IsDrawBorder(sheetPaintWrapper);
    EXPECT_FALSE(ret);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: IsDrawBorder004
 * @tc.desc: Branch: if (sheetTheme->IsOuterBorderEnable() && sheetType == SheetType::SHEET_POPUP &&
 *               !sheetStyle.borderWidth.has_value()) = true
 *           Condition: sheetTheme->IsOuterBorderEnable() = true, sheetType == SheetType::SHEET_POPUP = true,
 *               !sheetStyle.borderWidth.has_value() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, IsDrawBorder004, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    columnNode->AddChild(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    SheetWrapperPaintTestNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    auto sheetPaintWrapper = new PaintWrapper(columnNode->GetRenderContext(),
        sheetNode->GetGeometryNode(), sheetNode->GetPaintProperty<PaintProperty>());
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->propSheetStyle_->borderWidth = std::nullopt;
    sheetTheme_->isOuterBorderEnable_ = true;

    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    bool ret = sheetWrapperPaintMethod->IsDrawBorder(sheetPaintWrapper);
    EXPECT_TRUE(ret);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetBorderDrawPathNew001
 * @tc.desc: Branch: if (!sheetPopupInfo.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, GetBorderDrawPathNew001, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = false;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_FALSE(sheetPattern->sheetPopupInfo_.showArrow);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetBorderDrawPathNew002
 * @tc.desc: Branch: if (!sheetPopupInfo.showArrow) = false
 *           Branch: case Placement::BOTTOM_LEFT = true
 *           Branch: case Placement::BOTTOM_RIGHT = true
 *           Branch: case Placement::BOTTOM = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, GetBorderDrawPathNew002, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_TRUE(sheetPattern->sheetPopupInfo_.showArrow);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::BOTTOM_LEFT);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_RIGHT;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::BOTTOM_RIGHT);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::BOTTOM;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::BOTTOM);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetBorderDrawPathNew003
 * @tc.desc: Branch: if (!sheetPopupInfo.showArrow) = false
 *           Branch: case Placement::TOP_LEFT = true
 *           Branch: case Placement::TOP_RIGHT = true
 *           Branch: case Placement::TOP = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, GetBorderDrawPathNew003, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP_LEFT;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_TRUE(sheetPattern->sheetPopupInfo_.showArrow);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::TOP_LEFT);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP_RIGHT;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::TOP_RIGHT);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::TOP;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::TOP);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetBorderDrawPathNew004
 * @tc.desc: Branch: if (!sheetPopupInfo.showArrow) = false
 *           Branch: case Placement::RIGHT_TOP = true
 *           Branch: case Placement::RIGHT_BOTTOM = true
 *           Branch: case Placement::RIGHT = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, GetBorderDrawPathNew004, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT_TOP;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_TRUE(sheetPattern->sheetPopupInfo_.showArrow);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::RIGHT_TOP);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT_BOTTOM;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::RIGHT_BOTTOM);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::RIGHT;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::RIGHT);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetBorderDrawPathNew005
 * @tc.desc: Branch: if (!sheetPopupInfo.showArrow) = false
 *           Branch: case Placement::LEFT_TOP = true
 *           Branch: case Placement::LEFT_BOTTOM = true
 *           Branch: case Placement::LEFT = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, GetBorderDrawPathNew005, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT_TOP;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_TRUE(sheetPattern->sheetPopupInfo_.showArrow);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::LEFT_TOP);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT_BOTTOM;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::LEFT_BOTTOM);

    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::LEFT;

    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::LEFT);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetBorderDrawPathNew006
 * @tc.desc: Branch: if (!sheetPopupInfo.showArrow) = false
 *           Branch: default = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, GetBorderDrawPathNew006, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.finalPlacement = Placement::NONE;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->GetBorderDrawPathNew(path, sheetNode, 0.0f, sheetRadius);
    EXPECT_TRUE(sheetPattern->sheetPopupInfo_.showArrow);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.finalPlacement, Placement::NONE);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathBottom001
 * @tc.desc: Branch: if (arrowPosition == SheetArrowPosition::BOTTOM_LEFT) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::BOTTOM_LEFT) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::BOTTOM_RIGHT) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::BOTTOM_RIGHT) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::BOTTOM_LEFT) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::BOTTOM_RIGHT) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, DrawClipPathBottom001, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_LEFT;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->DrawClipPathBottom(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::NONE;

    sheetWrapperPaintMethod->DrawClipPathBottom(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;

    sheetWrapperPaintMethod->DrawClipPathBottom(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_RIGHT);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathTop001
 * @tc.desc: Branch: if (arrowPosition == SheetArrowPosition::TOP_RIGHT) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::TOP_RIGHT) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::TOP_LEFT) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::TOP_LEFT) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, DrawClipPathTop001, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::TOP_RIGHT;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->DrawClipPathTop(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::TOP_RIGHT);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::NONE;

    sheetWrapperPaintMethod->DrawClipPathTop(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::TOP_LEFT;

    sheetWrapperPaintMethod->DrawClipPathTop(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::TOP_LEFT);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathLeft001
 * @tc.desc: Branch: if (arrowPosition == SheetArrowPosition::LEFT_TOP) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::LEFT_TOP) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::LEFT_BOTTOM) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::LEFT_BOTTOM) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, DrawClipPathLeft001, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::LEFT_TOP;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->DrawClipPathLeft(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::LEFT_TOP);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::NONE;

    sheetWrapperPaintMethod->DrawClipPathLeft(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::LEFT_BOTTOM;

    sheetWrapperPaintMethod->DrawClipPathLeft(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::LEFT_BOTTOM);
    SheetWrapperPaintTestNg::TearDownTestCase();
}

/**
 * @tc.name: DrawClipPathRight001
 * @tc.desc: Branch: if (arrowPosition == SheetArrowPosition::RIGHT_TOP) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::RIGHT_TOP) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::RIGHT_BOTTOM) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::RIGHT_BOTTOM) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = false
 *           Branch: if (arrowPosition == SheetArrowPosition::NONE) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::RIGHT_TOP) = true
 *           Branch: if (arrowPosition == SheetArrowPosition::RIGHT_TOP) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperPaintTestNg, DrawClipPathRight001, TestSize.Level1)
{
    SheetWrapperPaintTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(ElementRegister::GetInstance()->MakeUniqueId(),
        V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetPopupInfo_.showArrow = true;
    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::RIGHT_TOP;

    RSPath path;
    BorderRadiusProperty sheetRadius;
    auto sheetWrapperPaintMethod = AceType::MakeRefPtr<SheetWrapperPaintMethod>();
    sheetWrapperPaintMethod->DrawClipPathRight(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::RIGHT_TOP);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::RIGHT_BOTTOM;

    sheetWrapperPaintMethod->DrawClipPathRight(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::RIGHT_BOTTOM);

    sheetPattern->sheetPopupInfo_.arrowPosition = SheetArrowPosition::NONE;

    sheetWrapperPaintMethod->DrawClipPathRight(path, sheetNode, sheetRadius, 0.0f, sheetPattern->sheetPopupInfo_);
    EXPECT_EQ(sheetPattern->sheetPopupInfo_.arrowPosition, SheetArrowPosition::NONE);
    SheetWrapperPaintTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG