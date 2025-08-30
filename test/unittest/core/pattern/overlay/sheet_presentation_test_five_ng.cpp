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
#include "test/mock/core/common/mock_window.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::BorderWidthProperty BORDER_WIDTH_TEST = { 1.0_vp, 1.0_vp, 1.0_vp, 0.0_vp };
const std::string MESSAGE = "hello world";
} // namespace

class SheetPresentationTestFiveNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
    static void TearDownTestCase();
    static void SetApiVersion(int32_t apiTargetVersion);
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
protected:
    void CreateSheetBuilder(float builderHeight = 800.f, float titleHeight = 800.f);
};

void SheetPresentationTestFiveNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            auto  sheetTheme = AceType::MakeRefPtr<SheetTheme>();
            sheetTheme->closeIconButtonWidth_ = SHEET_CLOSE_ICON_WIDTH;
            sheetTheme->centerDefaultWidth_ = SHEET_LANDSCAPE_WIDTH;
            sheetTheme->sheetCloseIconTitleSpaceNew_ = SHEET_CLOSE_ICON_TITLE_SPACE_NEW;
            return sheetTheme;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPresentationTestFiveNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
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

void SheetPresentationTestFiveNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
{
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
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "popup";
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
}

void SheetPresentationTestFiveNg::SetApiVersion(int32_t apiTargetVersion)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(apiTargetVersion);
}

void SheetPresentationTestFiveNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetPresentationTestFiveNg::CreateSheetBuilder(float builderHeight, float titleHeight)
{
    auto builderFunc = [builderHeight]() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = [titleHeight]() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}

/**
 * @tc.name: SetSheetOuterBorderWidth001
 * @tc.desc: Test SetSheetOuterBorderWidth outerBorder updated.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, SetSheetOuterBorderWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    SheetPresentationTestFiveNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));

    auto renderContext = sheetNode->GetRenderContext();

    /**
     * @tc.steps: step2. Change the SheetTheme border.
     * @tc.expected: the border is updated successfully
     */
    SheetStyle sheetStyle;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    sheetTheme->sheetOuterBorderWidth_ = Dimension(20.0);
    sheetTheme->sheetInnerBorderWidth_ = Dimension(10.0);
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), true);
    BorderWidthProperty BorderWidth;
    BorderWidth.SetBorderWidth(Dimension(20.0));
    EXPECT_EQ(renderContext->GetOuterBorderWidth().value(), BorderWidth);
    BorderWidth.SetBorderWidth(Dimension(10.0));
    EXPECT_EQ(renderContext->GetBorderWidth().value(), BorderWidth);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetOuterBorderWidth002
 * @tc.desc: Test SetSheetOuterBorderWidth outerBorder.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, SetSheetOuterBorderWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    SheetPresentationTestFiveNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));

    auto renderContext = sheetNode->GetRenderContext();

    /**
     * @tc.steps: step2. Change the SheetTheme border.
     * @tc.expected: the border is not updated
     */
    SheetStyle sheetStyle;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = false;
    sheetTheme->sheetOuterBorderWidth_ = Dimension(20.0);
    sheetTheme->sheetInnerBorderWidth_ = Dimension(10.0);
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), false);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetOuterBorderWidth003
 * @tc.desc: Test SetSheetOuterBorderWidth outerBorder.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, SetSheetOuterBorderWidth003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    SheetPresentationTestFiveNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));

    auto renderContext = sheetNode->GetRenderContext();

    /**
     * @tc.steps: step2. Change the SheetTheme border.
     * @tc.expected: the border is not updated
     */
    SheetStyle sheetStyle;

    sheetStyle.borderWidth = BORDER_WIDTH_TEST;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    sheetTheme->sheetOuterBorderWidth_ = Dimension(20.0);
    sheetTheme->sheetInnerBorderWidth_ = Dimension(10.0);
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), false);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), false);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetOuterBorderWidth004
 * @tc.desc: Test SetSheetOuterBorderWidth outerBorder updated.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, SetSheetOuterBorderWidth004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    SheetPresentationTestFiveNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));

    auto renderContext = sheetNode->GetRenderContext();

    /**
     * @tc.steps: step2. Change the SheetTheme border.
     * @tc.expected: the border is updated successfully
     */
    SheetStyle sheetStyle;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    sheetTheme->sheetOuterBorderWidth_ = Dimension(20.0);
    sheetTheme->sheetInnerBorderWidth_ = Dimension(10.0);
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), true);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), true);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: SetSheetOuterBorderWidth005
 * @tc.desc: Test SetSheetOuterBorderWidth outerBorder updated.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, SetSheetOuterBorderWidth005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    SheetPresentationTestFiveNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));

    auto renderContext = sheetNode->GetRenderContext();

    /**
     * @tc.steps: step2. Change the SheetTheme border.
     * @tc.expected: the border is not updated successfully
     */
    SheetStyle sheetStyle;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    sheetTheme->sheetOuterBorderWidth_ = Dimension(20.0);
    sheetTheme->sheetInnerBorderWidth_ = Dimension(10.0);
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), true);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), true);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTitlePadding001
 * @tc.desc: Increase the coverage of SheetPresentationPattern::UpdateTitlePadding function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateTitlePadding001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetTitle = MESSAGE;
    style.showCloseIcon = false;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step2. set API11.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    /**
     * @tc.steps: step3. Excute the UpdateTitlePadding function.
     * @tc.expected: padding.right is 72vp
     */
    sheetPattern->UpdateTitlePadding();
    auto titleNode  = sheetPattern->GetTitleNode();
    auto titleLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(titleNode->GetLayoutProperty());
    const auto& paddingProperty = titleLayoutProperty->GetPaddingProperty();
    ASSERT_NE(paddingProperty, nullptr);
    EXPECT_EQ(paddingProperty->right->GetDimension(), SHEET_CLOSE_ICON_TITLE_SPACE + SHEET_CLOSE_ICON_WIDTH);
    SheetPresentationTestFiveNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: UpdateTitlePadding002
 * @tc.desc: Increase the coverage of SheetPresentationPattern::UpdateTitlePadding function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateTitlePadding002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetTitle = MESSAGE;
    style.showCloseIcon = false;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step2. set API12.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    /**
     * @tc.steps: step3. Excute the UpdateTitlePadding function.
     * @tc.expected: padding.right is 48vp
     */
    sheetPattern->UpdateTitlePadding();
    auto titleNode  = sheetPattern->GetTitleNode();
    auto titleLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(titleNode->GetLayoutProperty());
    const auto& paddingProperty = titleLayoutProperty->GetPaddingProperty();
    ASSERT_NE(paddingProperty, nullptr);
    EXPECT_EQ(paddingProperty->right->GetDimension(), SHEET_CLOSE_ICON_TITLE_SPACE_NEW + SHEET_CLOSE_ICON_WIDTH);
    SheetPresentationTestFiveNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: UpdateTitlePadding003
 * @tc.desc: Increase the coverage of SheetPresentationPattern::UpdateTitlePadding function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateTitlePadding003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetTitle = MESSAGE;
    style.showCloseIcon = false;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step2. set API14.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    /**
     * @tc.steps: step3. Excute the UpdateTitlePadding function.
     * @tc.expected: padding.right is 0vp
     */
    sheetPattern->UpdateTitlePadding();
    auto titleNode  = sheetPattern->GetTitleNode();
    auto titleLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(titleNode->GetLayoutProperty());
    const auto& paddingProperty = titleLayoutProperty->GetPaddingProperty();
    ASSERT_NE(paddingProperty, nullptr);
    EXPECT_EQ(paddingProperty->right->GetDimension(), 0.0_vp);
    SheetPresentationTestFiveNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: IsScrollable
 * @tc.desc: Whether the bindsheet's scroll is scrollable.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, IsScrollable, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 11, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 12,
        AceType::MakeRefPtr<SheetPresentationPattern>(13, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 14, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 15, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 16,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and scrollPattern.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollLayoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(scrollLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test "IsScrollable", when scrollableDistance_ < 0.
     */
    scrollPattern->scrollableDistance_ = -1.0f;
    EXPECT_EQ(sheetPattern->IsScrollable(), false);

    /**
     * @tc.steps: step4. test "IsScrollable", when scrollableDistance_ = 0.
     */
    scrollPattern->scrollableDistance_ = 0.0f;
    EXPECT_EQ(sheetPattern->IsScrollable(), false);

    /**
     * @tc.steps: step5. test "IsScrollable", when scrollableDistance_ > 0.
     */
    scrollPattern->scrollableDistance_ = 5.2f;
    EXPECT_EQ(sheetPattern->IsScrollable(), true);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ChangeScrollHeight
 * @tc.desc: Test ChangeScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ChangeScrollHeight, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 02,
        AceType::MakeRefPtr<SheetPresentationPattern>(03, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 04, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 05, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 06, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 07,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    
    /**
     * @tc.steps: step2. Get sheetPattern and set scroll node.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    sheetPattern->SetTitleBuilderNode(WeakPtr<FrameNode>(operationColumn));

    /**
     * @tc.steps: step3. init sheetStyle.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    layoutProperty->propSheetStyle_ = sheetStyle;
    
    /**
     * @tc.steps: step4. test "ChangeScrollHeight".
     */
    sheetPattern->ChangeScrollHeight(700);
    sheetPattern->resizeDecreasedHeight_ = 0.0f;
    auto scrollLayoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(scrollLayoutProperty, nullptr);
    EXPECT_EQ(scrollLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize,
        CalcSize(std::nullopt, CalcLength(700)));
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: IsScrollOutOfBoundary
 * @tc.desc: Whether the bindsheet's scroll is out of boundary.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, IsScrollOutOfBoundary, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 001, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 002,
        AceType::MakeRefPtr<SheetPresentationPattern>(003, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 201, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 004, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(operationColumn);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 005, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 006,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and scrollPattern.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto scrollLayoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(scrollLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. init sheetStyle.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetHeight.height = Dimension(0.0f, DimensionUnit::AUTO);
    sheetStyle.width = Dimension(0.0f, DimensionUnit::AUTO);
    sheetStyle.sheetHeight.sheetMode = SheetMode::AUTO;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.sheetTitle = "Title";
    sheetStyle.sheetSubtitle = "SubTitle";
    sheetStyle.scrollSizeMode = ScrollSizeMode::CONTINUOUS;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "IsScrollOutOfBoundary" when "IsOutOfBoundary" is true.
     */
    EXPECT_TRUE(layoutProperty->GetSheetStyle()->isTitleBuilder);
    scrollPattern->IsOutOfBoundary(true);
    EXPECT_EQ(sheetPattern->IsScrollOutOfBoundary(), false);

    /**
     * @tc.steps: step5. test "IsScrollOutOfBoundary" when "IsOutOfBoundary" is false.
     */
    scrollPattern->IsOutOfBoundary(false);
    EXPECT_EQ(sheetPattern->IsScrollOutOfBoundary(), false);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: GetTitleBuilderHeight001
 * @tc.desc: Test ChangeScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, GetTitleBuilderHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 101, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 102,
        AceType::MakeRefPtr<SheetPresentationPattern>(103, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 201, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 104, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(operationColumn);
    auto scrollNode =
        FrameNode::CreateFrameNode("Scroll", 105, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 106,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    
    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    sheetPattern->SetTitleBuilderNode(WeakPtr<FrameNode>(operationColumn));

    /**
     * @tc.steps: step3. init SheetStyle and set sheetHeight.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = "Title";
    sheetStyle.sheetSubtitle = "SubTitle";
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    layoutProperty->propSheetStyle_ = sheetStyle;
    
    /**
     * @tc.steps: step4. test "GetTitleBuilderHeight", when isTitleBuilder is true.
     */
    EXPECT_TRUE(layoutProperty->GetSheetStyle()->isTitleBuilder);
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    auto firstChildGeometryNode = operationColumn->GetGeometryNode();
    ASSERT_NE(firstChildGeometryNode, nullptr);
    firstChildGeometryNode->SetFrameSize(SizeF(56, 56));
    sheetPattern->UpdateSheetTitle();
    EXPECT_EQ(sheetPattern->GetTitleBuilderHeight(), SHEET_OPERATION_AREA_HEIGHT.ConvertToPx());
}

/**
 * @tc.name: GetTitleBuilderHeight002
 * @tc.desc: Test ChangeScrollHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, GetTitleBuilderHeight002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 111, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 222,
        AceType::MakeRefPtr<SheetPresentationPattern>(333, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 444, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 555, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(operationColumn);
    auto scrollNode =
        FrameNode::CreateFrameNode("Scroll", 666, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 777,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    
    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetHeight.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = "Title";
    sheetStyle.sheetSubtitle = "SubTitle";
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. test "GetTitleBuilderHeight", when isTitleBuilder is false.
     */
    sheetStyle.isTitleBuilder = false;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    EXPECT_TRUE(layoutProperty->GetSheetStyle()->isTitleBuilder);
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    auto firstChildGeometryNode = operationColumn->GetGeometryNode();
    ASSERT_NE(firstChildGeometryNode, nullptr);
    firstChildGeometryNode->SetFrameSize(SizeF(0, 0));
    sheetPattern->UpdateSheetTitle();
    EXPECT_EQ(sheetPattern->GetTitleBuilderHeight(), 0.0f);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ModifyFireSheetTransition001
 * @tc.desc: Test SheetPresentationPattern::ModifyFireSheetTransition().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ModifyFireSheetTransition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 2,
        AceType::MakeRefPtr<SheetPresentationPattern>(3, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 4, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 5, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 6,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetHeight, test ModifyFireSheetTransition.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    SheetHeight detent;
    detent.sheetMode = SheetMode::AUTO;
    sheetStyle.detents.emplace_back(detent);
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. set params of isNeedProcessHeight_, test ModifyFireSheetTransition.
     */
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    sheetPattern->isNeedProcessHeight_ = true;
    sheetPattern->SetStartProp(1.0);
    sheetPattern->ModifyFireSheetTransition();
    EXPECT_FALSE(sheetPattern->isNeedProcessHeight_);

    /**
     * @tc.steps: step5. set params of isNeedProcessHeight_, test ModifyFireSheetTransition.
     */
    sheetPattern->isSpringBack_ = true;
    sheetPattern->SetStartProp(1.0);
    sheetPattern->ModifyFireSheetTransition();
    EXPECT_FALSE(sheetPattern->isSpringBack_);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ModifyFireSheetTransition002
 * @tc.desc: Test SheetPresentationPattern::ModifyFireSheetTransition().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ModifyFireSheetTransition002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 101, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 102,
        AceType::MakeRefPtr<SheetPresentationPattern>(103, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 104, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 105, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 106,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetHeight.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    SheetHeight detent;
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. set params of isNeedProcessHeight_, test ModifyFireSheetTransition.
     */
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    sheetPattern->isAnimationProcess_ = true;
    sheetPattern->SetStartProp(1.0);
    sheetPattern->ModifyFireSheetTransition();
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ModifyFireSheetTransition003
 * @tc.desc: Test SheetPresentationPattern::ModifyFireSheetTransition().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ModifyFireSheetTransition003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 101, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 102, AceType::MakeRefPtr<SheetPresentationPattern>(103, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 104, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 105, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        "SheetContent", 106, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetHeight.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    SheetHeight detent;
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. set params of isNeedProcessHeight_, test ModifyFireSheetTransition.
     */
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    sheetPattern->isAnimationProcess_ = true;
    sheetPattern->SetStartProp(0.0);
    sheetPattern->ModifyFireSheetTransition();
    EXPECT_TRUE(sheetPattern->isAnimationProcess_);
    sheetPattern->SetStartProp(1.0);
    sheetPattern->ModifyFireSheetTransition();
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: IsSheetBottomStyle001
 * @tc.desc: Test SheetPresentationPattern::IsSheetBottomStyle().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, IsSheetBottomStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet",
        02, AceType::MakeRefPtr<SheetPresentationPattern>(03, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar",
        04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent",
        06, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetMode and sheetType.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.sheetHeight.sheetMode = SheetMode::LARGE;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. set API11.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN);

    /**
     * @tc.steps: step5. set bottom style sheetType_, test "IsSheetBottomStyle".
     */
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_OFFSET;
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());

    /**
     * @tc.steps: step6. set non-bottom style sheetType_, test "IsSheetBottomStyle".
     */
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());

    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());

    SheetPresentationTestFiveNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: IsSheetBottomStyle002
 * @tc.desc: Test SheetPresentationPattern::IsSheetBottomStyle().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, IsSheetBottomStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 01, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet",
        02, AceType::MakeRefPtr<SheetPresentationPattern>(03, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar",
        04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 05, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent",
        06, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetMode and sheetType.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    sheetStyle.sheetHeight.sheetMode = SheetMode::AUTO;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. set API12.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);

    /**
     * @tc.steps: step5. set non-bottom style sheetType_, test "IsSheetBottomStyle".
     */
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());

    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());

    /**
     * @tc.steps: step6. set bottom style sheetType_, test "IsSheetBottomStyle".
     */
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_OFFSET;
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());

    SheetPresentationTestFiveNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: UpdateMaskBackgroundColor001
 * @tc.desc: Test SheetPresentationPattern::UpdateMaskBackgroundColor().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateMaskBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 010, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet",
        020, AceType::MakeRefPtr<SheetPresentationPattern>(030, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar",
        040, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 050, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent",
        060, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetMode and sheetType.
     */
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. set API11.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN);

    /**
     * @tc.steps: step5. set maskColor, test "UpdateMaskBackgroundColor".
     */
    sheetPattern->UpdateMaskBackgroundColor();
    EXPECT_EQ(sheetPattern->sheetMaskColor_, Color(0xff000000));

    sheetStyle.maskColor = Color::GREEN;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->UpdateMaskBackgroundColor();
    EXPECT_EQ(sheetPattern->sheetMaskColor_, Color(0xff00ff00));

    SheetPresentationTestFiveNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: UpdateMaskBackgroundColor002
 * @tc.desc: Test SheetPresentationPattern::UpdateMaskBackgroundColor().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateMaskBackgroundColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 011, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet",
        012, AceType::MakeRefPtr<SheetPresentationPattern>(013, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    sheetNode->MountToParent(rootNode);
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar",
        014, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 015, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent",
        016, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);

    /**
     * @tc.steps: step2. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. init SheetStyle and set sheetMode and sheetType.
     */
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;

    /**
     * @tc.steps: step4. set API12.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);

    /**
     * @tc.steps: step5. set maskColor, test "UpdateMaskBackgroundColor".
     */
    sheetPattern->UpdateMaskBackgroundColor();
    EXPECT_EQ(sheetPattern->sheetMaskColor_, Color(0xff000000));
    
    sheetStyle.maskColor = Color::BLUE;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->UpdateMaskBackgroundColor();
    EXPECT_EQ(sheetPattern->sheetMaskColor_, Color(0xff0000ff));

    sheetStyle.interactive = true;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->UpdateMaskBackgroundColor();
    EXPECT_EQ(sheetPattern->sheetMaskColor_, Color(0x00000000));

    SheetPresentationTestFiveNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: CalculateSheetRadius001
 * @tc.desc: Test bindSheet supports configuring corner radius.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, CalculateSheetRadius001, TestSize.Level1)
{
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 32.0_vp;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(1000, 1500));
    BorderRadiusProperty radius(Dimension(100.0));

    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.radius = radius;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->ClipSheetNode();
    auto renderContext = sheetNode->GetRenderContext();
    radius.radiusBottomLeft = 1.0_px;
    radius.radiusBottomRight = 1.0_px;
    EXPECT_EQ(renderContext->GetBorderRadius(), radius);

    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetRadius002
 * @tc.desc: Test bindSheet supports configuring corner radius.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, CalculateSheetRadius002, TestSize.Level1)
{
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 32.0_vp;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    BorderRadiusProperty sheetRadius(sheetTheme->GetSheetRadius());
    SheetStyle sheetStyle;
    sheetStyle.radius = BorderRadiusProperty(Dimension(100.0));
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);

    geometryNode->SetFrameSize(SizeF(0, 0));
    sheetPattern->CalculateSheetRadius(sheetRadius);
    BorderRadiusProperty radius(sheetTheme->GetSheetRadius());
    EXPECT_EQ(sheetRadius, radius);

    sheetRadius.SetRadius(sheetTheme->GetSheetRadius());
    geometryNode->SetFrameSize(SizeF(1000, 1500));
    sheetPattern->CalculateSheetRadius(sheetRadius);
    radius.SetRadius(Dimension(100.0));
    EXPECT_EQ(sheetRadius, radius);

    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetRadius003
 * @tc.desc: Test bindSheet supports configuring corner radius.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, CalculateSheetRadius003, TestSize.Level1)
{
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 32.0_vp;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    std::optional<Dimension> sheetStyleRadius;

    geometryNode->SetFrameSize(SizeF(1000, 1500));
    std::optional<Dimension> sheetRadius = sheetTheme->GetSheetRadius();
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    std::optional<Dimension> radius = sheetTheme->GetSheetRadius();
    EXPECT_EQ(sheetRadius, radius);

    geometryNode->SetFrameSize(SizeF(20, 30));
    sheetRadius = sheetTheme->GetSheetRadius();
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    radius = Dimension(10.0);
    EXPECT_EQ(sheetRadius, radius);

    sheetStyleRadius = Dimension(-100.0);
    geometryNode->SetFrameSize(SizeF(1000, 1500));
    sheetRadius = sheetTheme->GetSheetRadius();
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    radius = sheetTheme->GetSheetRadius();
    EXPECT_EQ(sheetRadius, radius);

    geometryNode->SetFrameSize(SizeF(20, 30));
    sheetRadius = sheetTheme->GetSheetRadius();
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    radius = Dimension(10.0);
    EXPECT_EQ(sheetRadius, radius);

    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetRadius004
 * @tc.desc: Test bindSheet supports configuring corner radius.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, CalculateSheetRadius004, TestSize.Level1)
{
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetRadius_ = 32.0_vp;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    std::optional<Dimension> sheetStyleRadius;

    geometryNode->SetFrameSize(SizeF(1000, 1500));
    std::optional<Dimension> sheetRadius = sheetTheme->GetSheetRadius();
    sheetStyleRadius = Dimension(100.0);
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    std::optional<Dimension> radius = Dimension(100.0);
    EXPECT_EQ(sheetRadius, radius);

    sheetStyleRadius = Dimension(0.2, DimensionUnit::PERCENT);
    sheetRadius = sheetTheme->GetSheetRadius();
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    radius = Dimension(200.0);
    EXPECT_EQ(sheetRadius, radius);

    geometryNode->SetFrameSize(SizeF(100, 150));
    sheetRadius = sheetTheme->GetSheetRadius();
    sheetStyleRadius = Dimension(100.0);
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    radius = Dimension(50.0);
    EXPECT_EQ(sheetRadius, radius);

    sheetStyleRadius = Dimension(1, DimensionUnit::PERCENT);
    sheetRadius = sheetTheme->GetSheetRadius();
    sheetPattern->CalculateAloneSheetRadius(sheetRadius, sheetStyleRadius);
    radius = Dimension(50.0);
    EXPECT_EQ(sheetRadius, radius);

    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTitleTextColor001
 * @tc.desc: Test bindSheet mainText color.
 *           Condition: sheetStyle.sheetTitle.has_value() == true.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateTitleTextColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetType = SheetType::SHEET_CENTER;
    style.sheetTitle = MESSAGE;
    style.showCloseIcon = false;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();

    /**
     * @tc.steps: step4. execute UpdateTitleTextColor.
     */
    sheetPattern->UpdateTitleTextColor();

    /**
     * @tc.steps: step4. get main text property.
     */
    auto firstChild = sheetPattern->GetTitleBuilderNode();
    ASSERT_NE(firstChild, nullptr);
    auto sheetTitleColumn = firstChild->GetChildAtIndex(0);
    ASSERT_NE(sheetTitleColumn, nullptr);
    auto mainRow = sheetTitleColumn->GetChildAtIndex(0);
    ASSERT_NE(mainRow, nullptr);
    auto mainTitleText = AceType::DynamicCast<FrameNode>(mainRow->GetChildAtIndex(0));
    ASSERT_NE(mainTitleText, nullptr);
    auto mainProp = mainTitleText->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.expected: mainProp->GetTextColor() == sheetTheme->GetTitleTextFontColor()
     */
    EXPECT_EQ(mainProp->GetTextColor(), sheetTheme->GetTitleTextFontColor());

    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateTitleTextColor002
 * @tc.desc: Branch: if (sheetStyle.sheetSubtitle.has_value()).
 *           Condition: 1.sheetEffectEdge_ = SheetEffectEdge::START,
 *                      2.scrollSizeMode_ = ScrollSizeMode::CONTINUOUS, IsScrollable().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateTitleTextColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetType = SheetType::SHEET_CENTER;
    style.sheetTitle = MESSAGE;
    style.sheetSubtitle = MESSAGE;
    style.showCloseIcon = false;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();

    /**
     * @tc.steps: step4. execute UpdateTitleTextColor.
     */
    sheetPattern->UpdateTitleTextColor();

    /**
     * @tc.steps: step4. get main text property.
     */
    auto firstChild = sheetPattern->GetTitleBuilderNode();
    ASSERT_NE(firstChild, nullptr);
    auto sheetTitleColumn = firstChild->GetChildAtIndex(0);
    ASSERT_NE(sheetTitleColumn, nullptr);
    auto subRow = sheetTitleColumn->GetChildAtIndex(1);
    ASSERT_NE(subRow, nullptr);
    auto subTitleText = AceType::DynamicCast<FrameNode>(subRow->GetChildAtIndex(0));
    ASSERT_NE(subTitleText, nullptr);
    auto subProp = subTitleText->GetLayoutProperty<TextLayoutProperty>();

    /**
     * @tc.expected: subProp->GetTextColor() == sheetTheme->GetSubtitleTextFontColor()
     */
    EXPECT_EQ(subProp->GetTextColor(), sheetTheme->GetSubtitleTextFontColor());

    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateSheetObject001
 * @tc.desc: Test UpdateSheetObject Function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateSheetObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet node and pattern.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    /**
     * @tc.steps: step2. set sheetType_ is SheetType::SHEET_BOTTOM, create sheetObject.
     */
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    sheetPattern->InitSheetObject();
    auto sheetObject = sheetPattern->GetSheetObject();
    /**
     * @tc.steps: step3. set newType is SheetType::SHEET_CENTER, UpdateSheetObject.
     * @tc.expected: sheetType_ = SheetType::SHEET_CENTER.
     */
    sheetPattern->UpdateSheetObject(SheetType::SHEET_CENTER);
    EXPECT_EQ(sheetObject->sheetType_, SheetType::SHEET_CENTER);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: SheetTransitionForOverlay001
 * @tc.desc: Branch: if (GetDismissProcess()).
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, SheetTransitionForOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto targetNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetPattern.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto context = sheetNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    context->UpdateTransformTranslate({ 0.0f, 100.0f, 0.0f });
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->pageHeight_ = 800.0f;
    sheetPattern->isDismissProcess_ = true;

    /**
     * @tc.steps: step. set sheetHeight_ is 800.0f, SheetTransitionForOverlay.
     * @tc.expected: GetTransformTranslate()->y.ConvertToPx() is 100.0f.
     */
    overlayManager->sheetHeight_ = 800.0f;
    sheetPattern->SheetTransitionForOverlay(true, true);
    EXPECT_EQ(context->GetTransformTranslate()->y.ConvertToPx(), 100.0f);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateMaskBackgroundColorRender001
 * @tc.desc: Branch: if (GetDismissProcess()).
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateMaskBackgroundColorRender001, TestSize.Level1)
{
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    SheetStyle sheetStyle;
    sheetStyle.maskColor = Color(0x00000000);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    sheetPattern->sheetMaskColor_ = Color(0xff0000ff);
    sheetPattern->SetDismissProcess(true);
    sheetPattern->UpdateMaskBackgroundColorRender();
    EXPECT_EQ(sheetPattern->sheetMaskColor_, Color(0xff0000ff));

    SheetPresentationTestFiveNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG