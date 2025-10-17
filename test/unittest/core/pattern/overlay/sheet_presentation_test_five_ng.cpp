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

class SheetPresentationTestFiveNg : public testing::Test {
public:
    static RefPtr<SheetTheme> sheetTheme_;
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
protected:
    void CreateSheetBuilder();
};

RefPtr<SheetTheme> SheetPresentationTestFiveNg::sheetTheme_ = nullptr;

void SheetPresentationTestFiveNg::SetUpTestCase()
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

void SheetPresentationTestFiveNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetPresentationTestFiveNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
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
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "popup";
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
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

void SheetPresentationTestFiveNg::CreateSheetBuilder()
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
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
 * @tc.name: ChangeScrollHeight001
 * @tc.desc: Branch: if (sheetType == SheetType::SHEET_POPUP || sheetType == SheetType::SHEET_CENTER ||
 *       sheetType == SheetType::SHEET_BOTTOM_OFFSET)
 *           Condition:  sheetType == SheetType::SHEET_CENTER =true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ChangeScrollHeight001, TestSize.Level1)
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
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 14, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBar", 15, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 16, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 17,
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
    SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    layoutProperty->propSheetStyle_ = sheetStyle;
    
    /**
     * @tc.steps: step4. test "ChangeScrollHeight".
     */
    sheetPattern->ChangeScrollHeight(300);
    sheetPattern->resizeDecreasedHeight_ = 0.0f;
    auto scrollLayoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    ASSERT_NE(scrollLayoutProperty, nullptr);
    EXPECT_EQ(scrollLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize,
        CalcSize(std::nullopt, CalcLength(0)));
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: SheetPresentationPattern001
 * @tc.desc: Test SheetPresentationPattern::InitSheetDetents().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, SheetPresentationPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. test InitSheetDetents
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto displayWindowRectInfo = Rect(0, 0, 400, 400);
    pipelineContext->SetDisplayWindowRectInfo(displayWindowRectInfo);
    SheetStyle sheetStyle;
    sheetStyle.bottomOffset = OffsetF(100.0, 100.0);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    auto isPcOrPadFreeMultiWindow = []() {
        return true;
    };
    windowManager->SetIsPcOrPadFreeMultiWindowModeCallback(std::move(isPcOrPadFreeMultiWindow));
    sheetPattern->InitSheetDetents();
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.front(), -8);
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.back(), -8);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: GetSubWindowId001
 * @tc.desc: Test SheetPresentationPattern::GetSubWindowId().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, GetSubWindowId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
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
     * @tc.steps: step2. test GetSubWindowId
     */
    auto ret = sheetPattern->GetSubWindowId();
    EXPECT_EQ(ret, 1);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateDragBarStatus001
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))
 *           Condition: Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateDragBarStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 105,
        AceType::MakeRefPtr<SheetPresentationPattern>(205, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    sheetPattern->SetDragBarNode(WeakPtr<NG::FrameNode>(dragBarNode));

    /**
     * @tc.steps: step2. test UpdateDragBarStatus.
     */
    sheetPattern->UpdateDragBarStatus();
    EXPECT_NE(sheetPattern->GetDragBarNode(), nullptr);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateDragBarStatus002
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))
 *                   if (IsSheetBottomStyle() && (sheetDetentHeight_.size() > 1))
 *           Condition: Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN = true
 *                      IsSheetBottomStyle() = true
 *                      sheetDetentHeight_.size() > 1 = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateDragBarStatus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 106,
        AceType::MakeRefPtr<SheetPresentationPattern>(206, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    sheetPattern->SetDragBarNode(WeakPtr<NG::FrameNode>(dragBarNode));
    
    /**
     * @tc.steps: step3. set version.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step4. test UpdateDragBarStatus.
     */
    sheetPattern->UpdateDragBarStatus();
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    ASSERT_NE(dragBarLayoutProperty, nullptr);
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::GONE);
    EXPECT_NE(sheetPattern->GetDragBarNode(), nullptr);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateDragBarStatus003
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))
 *                   if (IsSheetBottomStyle() && (sheetDetentHeight_.size() > 1))
 *                   if (sheetStyle.isTitleBuilder.has_value())
 *           Condition: Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN = true
 *                      IsSheetBottomStyle() = true
 *                      sheetDetentHeight_.size() > 1 = true
 *                      sheetStyle.isTitleBuilder.has_value() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateDragBarStatus003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 107,
        AceType::MakeRefPtr<SheetPresentationPattern>(207, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    sheetPattern->SetDragBarNode(WeakPtr<NG::FrameNode>(dragBarNode));
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    sheetPattern->sheetDetentHeight_.emplace_back(30);
    
    /**
     * @tc.steps: step3. set version.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step4. test UpdateDragBarStatus.
     */
    sheetPattern->UpdateDragBarStatus();
    EXPECT_NE(sheetPattern->GetDragBarNode(), nullptr);
    EXPECT_EQ(sheetPattern->GetSheetDetentHeight().front(), 20);
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    ASSERT_NE(dragBarLayoutProperty, nullptr);
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::VISIBLE);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateDragBarStatus004
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))
 *                   if (IsSheetBottomStyle() && (sheetDetentHeight_.size() > 1))
 *                   if (sheetStyle.isTitleBuilder.has_value())
 *           Condition: Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN = true
 *                      IsSheetBottomStyle() = true
 *                      sheetDetentHeight_.size() > 1 = true
 *                      sheetStyle.isTitleBuilder.has_value() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateDragBarStatus004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 107,
        AceType::MakeRefPtr<SheetPresentationPattern>(207, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    sheetPattern->SetDragBarNode(WeakPtr<NG::FrameNode>(dragBarNode));
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    sheetPattern->sheetDetentHeight_.emplace_back(30);
    
    /**
     * @tc.steps: step3. set version.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    
    /**
     * @tc.steps: step4. set isTitleBuilder.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step5. test UpdateDragBarStatus.
     */
    sheetPattern->UpdateDragBarStatus();
    EXPECT_NE(sheetPattern->GetDragBarNode(), nullptr);
    EXPECT_EQ(sheetPattern->GetSheetDetentHeight().back(), 30);
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    ASSERT_NE(dragBarLayoutProperty, nullptr);
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::VISIBLE);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateDragBarStatus005
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))
 *                   if (IsSheetBottomStyle() && (sheetDetentHeight_.size() > 1))
 *                   if (sheetStyle.isTitleBuilder.has_value())
 *           Condition: Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN = true
 *                      IsSheetBottomStyle() = true
 *                      sheetDetentHeight_.size() > 1 = false
 *                      sheetStyle.isTitleBuilder.has_value() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateDragBarStatus005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 108,
        AceType::MakeRefPtr<SheetPresentationPattern>(208, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    sheetPattern->SetDragBarNode(WeakPtr<NG::FrameNode>(dragBarNode));
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    
    /**
     * @tc.steps: step3. set version.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    
    /**
     * @tc.steps: step4. set isTitleBuilder.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    ASSERT_NE(dragBarLayoutProperty, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step5. test UpdateDragBarStatus.
     */
    sheetPattern->UpdateDragBarStatus();
    EXPECT_NE(sheetPattern->GetDragBarNode(), nullptr);
    EXPECT_EQ(sheetPattern->GetSheetDetentHeight().back(), 20);
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::INVISIBLE);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateDragBarStatus006
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))
 *                   if (IsSheetBottomStyle() && (sheetDetentHeight_.size() > 1))
 *                   if (sheetStyle.isTitleBuilder.has_value())
 *           Condition: Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN = true
 *                      IsSheetBottomStyle() = false
 *                      sheetDetentHeight_.size() > 1 = false
 *                      sheetStyle.isTitleBuilder.has_value() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateDragBarStatus006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 109,
        AceType::MakeRefPtr<SheetPresentationPattern>(209, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    sheetPattern->SetDragBarNode(WeakPtr<NG::FrameNode>(dragBarNode));
    sheetPattern->sheetDetentHeight_.emplace_back(20);
    
    /**
     * @tc.steps: step3. set version.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    
    /**
     * @tc.steps: step4. set isTitleBuilder.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    ASSERT_NE(dragBarLayoutProperty, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step5. set isTitleBuilder.
     */
    SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;

    /**
     * @tc.steps: step6. test UpdateDragBarStatus.
     */
    sheetPattern->UpdateDragBarStatus();
    EXPECT_NE(sheetPattern->GetDragBarNode(), nullptr);
    EXPECT_EQ(sheetPattern->GetSheetDetentHeight().back(), 20);
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::GONE);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateDragBarStatus007
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))
 *                   if (IsSheetBottomStyle() && (sheetDetentHeight_.size() > 1))
 *                   if (sheetStyle.isTitleBuilder.has_value())
 *           Condition: Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN = true
 *                      IsSheetBottomStyle() = false
 *                      sheetDetentHeight_.size() > 1 = true
 *                      sheetStyle.isTitleBuilder.has_value() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateDragBarStatus007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 110,
        AceType::MakeRefPtr<SheetPresentationPattern>(210, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    auto dragBarNode = FrameNode::CreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    sheetPattern->SetDragBarNode(WeakPtr<NG::FrameNode>(dragBarNode));
    sheetPattern->sheetDetentHeight_.emplace_back(100);
    sheetPattern->sheetDetentHeight_.emplace_back(200);
    
    /**
     * @tc.steps: step3. set version.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    
    /**
     * @tc.steps: step4. set isTitleBuilder.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = false;
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    ASSERT_NE(dragBarLayoutProperty, nullptr);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step5. set isTitleBuilder.
     */
    // SheetPresentationTestFiveNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    /**
     * @tc.steps: step6. test UpdateDragBarStatus.
     */
    sheetPattern->UpdateDragBarStatus();
    EXPECT_NE(sheetPattern->GetDragBarNode(), nullptr);
    EXPECT_EQ(sheetPattern->GetSheetDetentHeight().back(), 200);
    EXPECT_EQ(dragBarLayoutProperty->propVisibility_, VisibleType::INVISIBLE);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: GetCloseIconPosX001
 * @tc.desc: Branch:  if (AceApplicationInfo::GetInstance().IsRightToLeft() &&
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE))
 *           Condition: AceApplicationInfo::GetInstance().IsRightToLeft() = true
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) = true
 *                      AceApplicationInfo::GetInstance().IsRightToLeft() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, GetCloseIconPosX001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 111,
        AceType::MakeRefPtr<SheetPresentationPattern>(211, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create sheet page.
     */
    Dimension closeIconButtonWidth = 100.0_vp;
    Dimension titleTextMargin = 200.0_vp;
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->closeIconButtonWidth_ = closeIconButtonWidth;
    sheetTheme->titleTextMargin_ = titleTextMargin;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(13);
    /**
     * @tc.steps: step3. set direction.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    /**
     * @tc.steps: step4. test GetCloseIconPosX.
     */
    SizeF sheetSize(400.0, 400.0);
    auto ret = sheetPattern->GetCloseIconPosX(sheetSize, sheetTheme_);
    EXPECT_EQ(ret, 0);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: GetCloseIconPosX002
 * @tc.desc: Branch:  if (AceApplicationInfo::GetInstance().IsRightToLeft() &&
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE))
 *           Condition: AceApplicationInfo::GetInstance().IsRightToLeft() = true
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) = false
 *                      AceApplicationInfo::GetInstance().IsRightToLeft() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, GetCloseIconPosX002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 111,
        AceType::MakeRefPtr<SheetPresentationPattern>(211, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create sheet page.
     */
    Dimension closeIconButtonWidth = 100.0_vp;
    Dimension titleTextMargin = 200.0_vp;
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->closeIconButtonWidth_ = closeIconButtonWidth;
    sheetTheme->titleTextMargin_ = titleTextMargin;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(13);

    /**
     * @tc.steps: step4. test GetCloseIconPosX.
     */
    SizeF sheetSize(500.0, 500.0);
    auto ret = sheetPattern->GetCloseIconPosX(sheetSize, sheetTheme_);
    EXPECT_EQ(ret, 500);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: GetCloseIconPosX003
 * @tc.desc: Branch:  if (AceApplicationInfo::GetInstance().IsRightToLeft() &&
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE))
 *           Condition: AceApplicationInfo::GetInstance().IsRightToLeft() = true
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) = true
 *                      AceApplicationInfo::GetInstance().IsRightToLeft() = fasle
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, GetCloseIconPosX003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 111,
        AceType::MakeRefPtr<SheetPresentationPattern>(211, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create sheet page.
     */
    Dimension closeIconButtonWidth = 100.0_vp;
    Dimension titleTextMargin = 200.0_vp;
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->closeIconButtonWidth_ = closeIconButtonWidth;
    sheetTheme->titleTextMargin_ = titleTextMargin;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(11);
    /**
     * @tc.steps: step3. set direction.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    /**
     * @tc.steps: step4. test GetCloseIconPosX.
     */
    SizeF sheetSize(600.0, 600.0);
    auto ret = sheetPattern->GetCloseIconPosX(sheetSize, sheetTheme_);
    EXPECT_EQ(ret, 600.0);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: GetCloseIconPosX004
 * @tc.desc: Branch:  if (AceApplicationInfo::GetInstance().IsRightToLeft() &&
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE))
 *           Condition: AceApplicationInfo::GetInstance().IsRightToLeft() = true
 *   AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) = false
 *                      AceApplicationInfo::GetInstance().IsRightToLeft() = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, GetCloseIconPosX004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 111,
        AceType::MakeRefPtr<SheetPresentationPattern>(211, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create sheet page.
     */
    Dimension closeIconButtonWidth = 100.0_vp;
    Dimension titleTextMargin = 200.0_vp;
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->closeIconButtonWidth_ = closeIconButtonWidth;
    sheetTheme->titleTextMargin_ = titleTextMargin;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(11);

    /**
     * @tc.steps: step3. set direction.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    /**
     * @tc.steps: step4. test GetCloseIconPosX.
     */
    SizeF sheetSize(500.0, 500.0);
    auto ret = sheetPattern->GetCloseIconPosX(sheetSize, sheetTheme_);
    EXPECT_EQ(ret, 500);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateFontScaleStatus001
 * @tc.desc: Branch:  if (isSheetHasNoTitle || isFontScaledInSystemTitle)
 *           Condition: isSheetHasNoTitle = true
 *                      isFontScaledInSystemTitle = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateFontScaleStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 112,
        AceType::MakeRefPtr<SheetPresentationPattern>(212, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetTitle = "sheetTitle";
    style.sheetSubtitle = "sheetSubtitle";
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 12, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    auto titleColumnNode =
        FrameNode::CreateFrameNode("Column", 13, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(titleColumnNode, nullptr);
    titleColumnNode->MountToParent(operationColumn);
    sheetPattern->SetTitleBuilderNode(WeakPtr<FrameNode>(operationColumn));

    /**
     * @tc.steps: step4. test GetDragBarHeight.
     */
    sheetPattern->scale_ = 1.75f;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 1.1f;
    sheetPattern->UpdateFontScaleStatus();
    EXPECT_EQ(sheetPattern->scale_, pipeline->GetFontScale());
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateFontScaleStatus002
 * @tc.desc: Branch:  if (isSheetHasNoTitle || isFontScaledInSystemTitle)
 *           Condition: isSheetHasNoTitle = false
 *                      isFontScaledInSystemTitle = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateFontScaleStatus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 113,
        AceType::MakeRefPtr<SheetPresentationPattern>(213, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    SheetStyle sheetStyle;
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 14, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    auto titleColumnNode =
        FrameNode::CreateFrameNode("Column", 15, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(titleColumnNode, nullptr);
    titleColumnNode->MountToParent(operationColumn);
    sheetPattern->SetTitleBuilderNode(WeakPtr<FrameNode>(operationColumn));
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetNormalScale_ = 0.9;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);

    /**
     * @tc.steps: step4. test GetDragBarHeight.
     */
    sheetPattern->scale_ = 1.75f;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 1.1f;
    sheetPattern->UpdateFontScaleStatus();
    EXPECT_EQ(sheetPattern->scale_, pipeline->GetFontScale());
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateFontScaleStatus003
 * @tc.desc: Branch:  if (isSheetHasNoTitle || isFontScaledInSystemTitle)
 *           Condition: isSheetHasNoTitle = false
 *                      isFontScaledInSystemTitle = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, UpdateFontScaleStatus003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 114,
        AceType::MakeRefPtr<SheetPresentationPattern>(214, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. create dragBarNode.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    sheetStyle.isTitleBuilder = false;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto operationColumn =
        FrameNode::CreateFrameNode("Column", 16, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(operationColumn, nullptr);
    auto titleColumnNode =
        FrameNode::CreateFrameNode("Column", 17, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(titleColumnNode, nullptr);
    titleColumnNode->MountToParent(operationColumn);
    sheetPattern->SetTitleBuilderNode(WeakPtr<FrameNode>(operationColumn));
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetNormalScale_ = 1.0;
    SheetPresentationTestFiveNg::SetSheetTheme(sheetTheme);

    /**
     * @tc.steps: step3. test GetDragBarHeight.
     */
    sheetPattern->scale_ = 0.8f;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->fontScale_ = 1.9f;
    sheetPattern->UpdateFontScaleStatus();
    EXPECT_EQ(sheetPattern->scale_, pipeline->GetFontScale());
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: PopupSheetChanged001
 * @tc.desc: Branch:  if (SheetHeightNeedChanged() || SheetWidthNeedChanged() || typeChanged_ || sheetOffsetYChanged_)
 *           Condition: SheetHeightNeedChanged() = true
 *                      SheetWidthNeedChanged() = false
 *                      typeChanged_ = false
 *                      sheetOffsetYChanged_ = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, PopupSheetChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(115, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetWidth_ = 500;
    sheetPattern->wrapperWidth_ = 400;
    sheetPattern->wrapperHeight_ = 400;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. init sheetGeometryNode.
     */
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(500, 500));

    /**
     * @tc.steps: step3. init SheetObject.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->GetSheetObject()->SetSheetHeight(300);

    /**
     * @tc.steps: step4. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetNode->MountToParent(sheetWrapperNode);
    auto sheetWrapperGeometryNode = sheetWrapperNode->GetGeometryNode();
    ASSERT_NE(sheetWrapperGeometryNode, nullptr);
    sheetWrapperGeometryNode->SetFrameSize(SizeF(400, 400));

    /**
     * @tc.steps: step5. set typeChanged.
     */
    sheetPattern->typeChanged_ = false;
    sheetPattern->sheetOffsetYChanged_ = false;

    /**
     * @tc.steps: step6. test PopupSheetChanged.
     */
    sheetPattern->PopupSheetChanged();
    EXPECT_EQ(sheetPattern->typeChanged_, false);
    EXPECT_EQ(sheetPattern->sheetOffsetYChanged_, false);
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Width(), sheetPattern->sheetWidth_), true);
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Height(), sheetPattern->sheetObject_->GetSheetHeight()), false);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: PopupSheetChanged002
 * @tc.desc: Branch:  if (SheetHeightNeedChanged() || SheetWidthNeedChanged() || typeChanged_ || sheetOffsetYChanged_)
 *           Condition: SheetHeightNeedChanged() = false
 *                      SheetWidthNeedChanged() = true
 *                      typeChanged_ = false
 *                      sheetOffsetYChanged_ = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, PopupSheetChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(116, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetWidth_ = 600;
    sheetPattern->wrapperWidth_ = 400;
    sheetPattern->wrapperHeight_ = 400;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. init sheetGeometryNode.
     */
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(500, 500));

    /**
     * @tc.steps: step3. init SheetObject.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->GetSheetObject()->SetSheetHeight(500);

    /**
     * @tc.steps: step4. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetNode->MountToParent(sheetWrapperNode);
    auto sheetWrapperGeometryNode = sheetWrapperNode->GetGeometryNode();
    ASSERT_NE(sheetWrapperGeometryNode, nullptr);
    sheetWrapperGeometryNode->SetFrameSize(SizeF(400, 400));

    /**
     * @tc.steps: step5. set typeChanged.
     */
    sheetPattern->typeChanged_ = false;
    sheetPattern->sheetOffsetYChanged_ = false;

    /**
     * @tc.steps: step6. test PopupSheetChanged.
     */
    sheetPattern->PopupSheetChanged();
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Width(), sheetPattern->sheetWidth_), false);
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Height(), sheetPattern->sheetObject_->GetSheetHeight()), true);
    EXPECT_EQ(sheetPattern->typeChanged_, false);
    EXPECT_EQ(sheetPattern->sheetOffsetYChanged_, false);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: PopupSheetChanged003
 * @tc.desc: Branch:  if (SheetHeightNeedChanged() || SheetWidthNeedChanged() || typeChanged_ || sheetOffsetYChanged_)
 *           Condition: SheetHeightNeedChanged() = false
 *                      SheetWidthNeedChanged() = false
 *                      typeChanged_ = true
 *                      sheetOffsetYChanged_ = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, PopupSheetChanged003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(117, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetWidth_ = 100;
    sheetPattern->wrapperWidth_ = 700;
    sheetPattern->wrapperHeight_ = 700;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. init sheetGeometryNode.
     */
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100, 100));

    /**
     * @tc.steps: step3. init SheetObject.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->GetSheetObject()->SetSheetHeight(100);

    /**
     * @tc.steps: step4. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetNode->MountToParent(sheetWrapperNode);
    auto sheetWrapperGeometryNode = sheetWrapperNode->GetGeometryNode();
    ASSERT_NE(sheetWrapperGeometryNode, nullptr);
    sheetWrapperGeometryNode->SetFrameSize(SizeF(700, 700));

    /**
     * @tc.steps: step5. set typeChanged.
     */
    sheetPattern->typeChanged_ = true;
    sheetPattern->sheetOffsetYChanged_ = false;

    /**
     * @tc.steps: step6. test PopupSheetChanged.
     */
    sheetPattern->PopupSheetChanged();
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Width(), sheetPattern->sheetWidth_), true);
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Height(), sheetPattern->sheetObject_->GetSheetHeight()), true);
    EXPECT_EQ(sheetPattern->typeChanged_, false);
    EXPECT_EQ(sheetPattern->sheetOffsetYChanged_, false);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: PopupSheetChanged004
 * @tc.desc: Branch:  if (SheetHeightNeedChanged() || SheetWidthNeedChanged() || typeChanged_ || sheetOffsetYChanged_)
 *           Condition: SheetHeightNeedChanged() = false
 *                      SheetWidthNeedChanged() = false
 *                      typeChanged_ = false
 *                      sheetOffsetYChanged_ = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, PopupSheetChanged004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(118, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetWidth_ = 200;
    sheetPattern->wrapperWidth_ = 800;
    sheetPattern->wrapperHeight_ = 800;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. init sheetGeometryNode.
     */
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(200, 200));

    /**
     * @tc.steps: step3. init SheetObject.
     */
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    sheetPattern->GetSheetObject()->SetSheetHeight(200);

    /**
     * @tc.steps: step4. create sheetWrapperNode.
     */
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetNode->MountToParent(sheetWrapperNode);
    auto sheetWrapperGeometryNode = sheetWrapperNode->GetGeometryNode();
    ASSERT_NE(sheetWrapperGeometryNode, nullptr);
    sheetWrapperGeometryNode->SetFrameSize(SizeF(800, 800));

    /**
     * @tc.steps: step5. set typeChanged.
     */
    sheetPattern->typeChanged_ = false;
    sheetPattern->sheetOffsetYChanged_ = true;

    /**
     * @tc.steps: step6. test PopupSheetChanged.
     */
    sheetPattern->PopupSheetChanged();
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Width(), sheetPattern->sheetWidth_), true);
    EXPECT_EQ(NearEqual(geometryNode->GetFrameSize().Height(), sheetPattern->sheetObject_->GetSheetHeight()), true);
    EXPECT_EQ(sheetPattern->typeChanged_, false);
    EXPECT_EQ(sheetPattern->sheetOffsetYChanged_, false);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow001
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *           Condition: container->IsUIExtensionWindow() = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 119,
        AceType::MakeRefPtr<SheetPresentationPattern>(219, "SheetPresentation", std::move(callback)));
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
     * @tc.steps: step4. create mainWindowContext.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. set isUIExtensionWindow.
     */
    mockContainer->SetIsUIExtensionWindow(true);

    /**
     * @tc.steps: step6. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_CENTER);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow002
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager != nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = true
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = true
 *                      sheetKey_.hasValidTargetNode = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 120,
        AceType::MakeRefPtr<SheetPresentationPattern>(220, "SheetPresentation", std::move(callback)));
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
     * @tc.steps: step4. init mainWindowContext.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mainWindowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(mainWindowManager, nullptr);
    auto isPcOrPadFreeMultiWindowMode = []() {
        return true;
    };
    mainWindowManager->SetIsPcOrPadFreeMultiWindowModeCallback(isPcOrPadFreeMultiWindowMode);
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
     * @tc.steps: step7. set sheetKey.
     */
    sheetPattern->sheetKey_.hasValidTargetNode = true;

    /**
     * @tc.steps: step8. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_POPUP);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow003
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager != nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = true
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = false
 *                      sheetKey_.hasValidTargetNode = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 121,
        AceType::MakeRefPtr<SheetPresentationPattern>(221, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mainWindowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(mainWindowManager, nullptr);
    auto isPcOrPadFreeMultiWindowMode = []() {
        return true;
    };
    mainWindowManager->SetIsPcOrPadFreeMultiWindowModeCallback(isPcOrPadFreeMultiWindowMode);
    mockContainer->pipelineContext_ = pipelineContext;
    mockContainer->SetIsUIExtensionWindow(false);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_SIDE;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetKey_.hasValidTargetNode = true;

    /**
     * @tc.steps: step2. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_CENTER);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow004
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager != nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = true
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = true
 *                      sheetKey_.hasValidTargetNode = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 122,
        AceType::MakeRefPtr<SheetPresentationPattern>(222, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mainWindowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(mainWindowManager, nullptr);
    auto isPcOrPadFreeMultiWindowMode = []() {
        return true;
    };
    mainWindowManager->SetIsPcOrPadFreeMultiWindowModeCallback(isPcOrPadFreeMultiWindowMode);
    mockContainer->pipelineContext_ = pipelineContext;
    mockContainer->SetIsUIExtensionWindow(false);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetKey_.hasValidTargetNode = false;

    /**
     * @tc.steps: step2. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_CENTER);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow005
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager != nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = true
 *                      sheetStyle.sheetType.has_value() = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_POPUP = false
 *                      sheetKey_.hasValidTargetNode = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 123,
        AceType::MakeRefPtr<SheetPresentationPattern>(223, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mainWindowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(mainWindowManager, nullptr);
    auto isPcOrPadFreeMultiWindowMode = []() {
        return true;
    };
    mainWindowManager->SetIsPcOrPadFreeMultiWindowModeCallback(isPcOrPadFreeMultiWindowMode);
    mockContainer->pipelineContext_ = pipelineContext;
    mockContainer->SetIsUIExtensionWindow(false);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetKey_.hasValidTargetNode = false;

    /**
     * @tc.steps: step2. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_CENTER);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow006
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                       sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *                     if (LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())) {
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager != nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = fasle
 *                      LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 124,
        AceType::MakeRefPtr<SheetPresentationPattern>(224, "SheetPresentation", std::move(callback)));
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
     * @tc.steps: step4. init mainWindowContext.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    auto mainWindowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(mainWindowManager, nullptr);
    auto isPcOrPadFreeMultiWindowMode = []() {
        return false;
    };
    mainWindowManager->SetIsPcOrPadFreeMultiWindowModeCallback(isPcOrPadFreeMultiWindowMode);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. set isUIExtensionWindow.
     */
    mockContainer->SetIsUIExtensionWindow(false);

    /**
     * @tc.steps: step6. set sheetStyle.
     */
    SheetStyle sheetStyle;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step8. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_BOTTOM);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow007
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                       sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *                     if (LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx())) {
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager = nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = fasle
 *                      LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 125,
        AceType::MakeRefPtr<SheetPresentationPattern>(225, "SheetPresentation", std::move(callback)));
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
     * @tc.steps: step4. init mainWindowContext.
     */
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->windowManager_ = nullptr;
    ASSERT_EQ(pipelineContext->windowManager_, nullptr);
    mockContainer->pipelineContext_ = pipelineContext;

    /**
     * @tc.steps: step5. set isUIExtensionWindow.
     */
    mockContainer->SetIsUIExtensionWindow(false);

    /**
     * @tc.steps: step6. set sheetStyle.
     */
    SheetStyle sheetStyle;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step7. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_BOTTOM);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow008
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
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 125,
        AceType::MakeRefPtr<SheetPresentationPattern>(225, "SheetPresentation", std::move(callback)));
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
    sheetStyle.sheetType = SheetType::SHEET_BOTTOMLANDSPACE;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step7. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_BOTTOMLANDSPACE);
    SheetPresentationTestFiveNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetTypeInSubWindow010
 * @tc.desc: Branch:   if (container->IsUIExtensionWindow())
 *                     if (manager && manager->IsPcOrPadFreeMultiWindowMode())
 *                     if (sheetStyle.sheetType.has_value() &&
 *                       sheetStyle.sheetType.value() == SheetType::SHEET_POPUP && sheetKey_.hasValidTargetNode)
 *                     if (LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()))
 *                     if (LessOrEqual(windowWidth, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) &&
 *                         GreatOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) &&
 *                         LessOrEqual(windowWidth, BOTTOM_STYLE_RATIO * windowHeight))
 *                    if (sheetStyle.sheetType.has_value() && sheetStyle.sheetType.value() == SheetType::SHEET_BOTTOM)
 *           Condition: container->IsUIExtensionWindow() = false
 *                      manager = nullptr
 *                      manager->IsPcOrPadFreeMultiWindowMode() = fasle
 *                      LessOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = false
 *                      LessOrEqual(windowWidth, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = true
 *                      GreatOrEqual(windowWidth, SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()) = true
 *                      LessOrEqual(windowWidth, BOTTOM_STYLE_RATIO * windowHeight)  = true
 *                      sheetStyle.sheetType.value() == SheetType::SHEET_BOTTOM  = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFiveNg, ComputeSheetTypeInSubWindow010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestFiveNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 127,
        AceType::MakeRefPtr<SheetPresentationPattern>(227, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->subWindowId_ = 1;
    sheetNode->MountToParent(sheetWrapperNode);
    SubwindowManager::GetInstance()->parentContainerMap_.try_emplace(1, 1);
    AceEngine::Get().containerMap_.clear();
    auto mockContainer = MockContainer::Current();
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->windowManager_ = nullptr;
    ASSERT_EQ(pipelineContext->windowManager_, nullptr);
    Rect displayWindowRectInfo (0.0f, 0.0f, 700.0f, 1020.0f);
    pipelineContext->SetDisplayWindowRectInfo(displayWindowRectInfo);
    mockContainer->pipelineContext_ = pipelineContext;
    mockContainer->SetIsUIExtensionWindow(false);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step2. test ComputeSheetTypeInSubWindow.
     */
    auto ret = sheetPattern->ComputeSheetTypeInSubWindow();
    EXPECT_EQ(ret, SheetType::SHEET_BOTTOM);
    SheetPresentationTestFiveNg::TearDownTestCase();
}
}