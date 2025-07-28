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

#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const int32_t fingerId = 1;
} // namespace

class SheetPresentationTestFourNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SheetPresentationTestFourNg::SetUpTestCase()
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
            return sheetTheme;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPresentationTestFourNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateAccessibilityDetents001
 * @tc.desc: UpdateAccessibilityDetents true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateAccessibilityDetents001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    auto count = sheetPattern->sheetDetentHeight_.size();
    EXPECT_EQ(count, 5);
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    auto res = sheetPattern->UpdateAccessibilityDetents(10.0f);
    EXPECT_TRUE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: OnCoordScrollUpdate001
 * @tc.desc: OnCoordScrollUpdate false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto count = sheetPattern->sheetDetentHeight_.size();
    EXPECT_EQ(count, 0);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->scrollableDistance_ = 10.0f;
    auto res = sheetPattern->OnCoordScrollUpdate(10.0f);
    EXPECT_FALSE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: OnCoordScrollUpdate002
 * @tc.desc: OnCoordScrollUpdate false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(0.0f);
    auto count = sheetPattern->sheetDetentHeight_.size();
    EXPECT_EQ(count, 5);
    sheetPattern->currentOffset_ = 0.0f;
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->scrollableDistance_ = 10.0f;
    auto res = sheetPattern->OnCoordScrollUpdate(0.0f);
    EXPECT_FALSE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: OnCoordScrollUpdate003
 * @tc.desc: OnCoordScrollUpdate false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnCoordScrollUpdate003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    EXPECT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    EXPECT_NE(sheetPattern, nullptr);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    auto count = sheetPattern->sheetDetentHeight_.size();
    EXPECT_EQ(count, 5);
    sheetPattern->pageHeight_ = 10.0f;
    sheetPattern->height_ = 10.0f;
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->scrollableDistance_ = 10.0f;
    auto res = sheetPattern->OnCoordScrollUpdate(10.0f);
    EXPECT_TRUE(sheetPattern->GetShowState());
    EXPECT_TRUE(sheetPattern->IsScrollable());
    EXPECT_TRUE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndAccessibilityEvent001
 * @tc.desc: HandleDragEndAccessibilityEvent event.beforeText
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndAccessibilityEvent001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    auto count = sheetPattern->sheetDetentHeight_.size();
    EXPECT_EQ(count, 5);
    sheetPattern->height_ = 10.0f;
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    auto res = sheetPattern->UpdateAccessibilityDetents(sheetPattern->GetSheetHeightBeforeDragUpdate());
    EXPECT_TRUE(res);
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    sheetPattern->HandleDragEndAccessibilityEvent();
    AccessibilityEvent event;
    EXPECT_EQ(event.beforeText, "");
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetWindowButtonRect001
 * @tc.desc: GetWindowButtonRect EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetWindowButtonRect001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = 1019;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
    ASSERT_NE(avoidInfoMgr, nullptr);
    avoidInfoMgr->instanceId_ = 1001;
    avoidInfoMgr->avoidInfo_.needAvoid = true;
    NG::RectF floatButtons;
    floatButtons.SetHeight(10.0f);
    floatButtons.SetWidth(10.0f);
    auto res = sheetPattern->GetWindowButtonRect(floatButtons);
    EXPECT_TRUE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: InitialSingleGearHeight001
 * @tc.desc: InitialSingleGearHeight sheetHeight
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, InitialSingleGearHeight001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    NG::SheetStyle sheetStyle;
    sheetStyle.sheetHeight.sheetMode = SheetMode::MEDIUM;
    Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_EIGHTEEN);
    sheetPattern->pageHeight_ = 10.0f;
    auto sheetHeight = sheetPattern->InitialSingleGearHeight(sheetStyle);
    EXPECT_EQ(sheetHeight, 5.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateSheetTransitionOffset001
 * @tc.desc: UpdateSheetTransitionOffset sheetHeightUp_
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateSheetTransitionOffset001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->isSpringBack_ = true;
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    sheetPattern->sheetDetentHeight_.push_back(10.0f);
    auto count = sheetPattern->sheetDetentHeight_.size();
    EXPECT_EQ(count, 5);
    sheetPattern->UpdateSheetTransitionOffset();
    EXPECT_EQ(sheetPattern->sheetHeightUp_, 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SheetHeightNeedChanged001
 * @tc.desc: SheetHeightNeedChanged EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SheetHeightNeedChanged001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeometryNode);

    auto size = sheetGeometryNode->GetFrameSize();
    size.SetHeight(100.0f);
    sheetGeometryNode->SetFrameSize(size);

    CHECK_NULL_VOID(sheetPattern->sheetObject_);
    sheetPattern->sheetObject_->SetSheetHeight(50.0f);

    auto res = sheetPattern->SheetHeightNeedChanged();
    EXPECT_TRUE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckSheetHeightChange001
 * @tc.desc: isRenderDirtyMarked_ EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckSheetHeightChange001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->typeChanged_ = true;
    sheetPattern->isFirstInit_ = false;
    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    sheetNode->isRenderDirtyMarked_ = false;
    sheetNode->isLayoutDirtyMarked_ = false;
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    sheetGeometryNode->SetFrameSize(SizeF(100.0f, 200.0f));
    CHECK_NULL_VOID(sheetPattern->sheetObject_);
    sheetPattern->CheckSheetHeightChange();
    EXPECT_TRUE(sheetNode->isRenderDirtyMarked_);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckSheetHeightChange002
 * @tc.desc: CheckSheetHeightChange PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckSheetHeightChange002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->typeChanged_ = true;
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto sheetGeometryNode = sheetNode->GetGeometryNode();
    sheetGeometryNode->SetFrameSize(SizeF(100.0f, 200.0f));
    CHECK_NULL_VOID(sheetPattern->sheetObject_);
    sheetPattern->CheckSheetHeightChange();
    EXPECT_EQ(layoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: IsCustomDetentsChanged001
 * @tc.desc: IsCustomDetentsChanged
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, IsCustomDetentsChanged001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->detentsFinalIndex_ = 1;
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    SheetStyle sheetStyle;

    SheetHeight preDetents;
    preDetents.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    sheetPattern->preDetents_.emplace_back(preDetents);
    unsigned int preDetentsSize = sheetPattern->preDetents_.size();
    unsigned int userSetDetentsSize = sheetStyle.detents.size();
    EXPECT_EQ(preDetentsSize, 1);
    EXPECT_EQ(userSetDetentsSize, 1);
    sheetPattern->IsCustomDetentsChanged(sheetStyle);
    EXPECT_EQ(sheetPattern->detentsFinalIndex_, 0);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: IsCustomDetentsChanged002
 * @tc.desc: IsCustomDetentsChanged
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, IsCustomDetentsChanged002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->detentsFinalIndex_ = 1;
    ASSERT_NE(sheetPattern, nullptr);
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    SheetStyle sheetStyle;

    SheetHeight preDetents;
    preDetents.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    sheetPattern->preDetents_.emplace_back(preDetents);
    unsigned int preDetentsSize = sheetPattern->preDetents_.size();
    unsigned int userSetDetentsSize = sheetStyle.detents.size();
    EXPECT_EQ(preDetentsSize, 1);
    EXPECT_EQ(userSetDetentsSize, 1);
    sheetPattern->IsCustomDetentsChanged(sheetStyle);
    EXPECT_EQ(sheetPattern->detentsFinalIndex_, 1);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetSubWindowId001
 * @tc.desc: GetSubWindowId INVALID_SUBWINDOW_ID
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetSubWindowId001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    EXPECT_EQ(sheetWrapperPattern->GetSubWindowId(), INVALID_SUBWINDOW_ID);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: OnWindowSizeChangedTest001
 * @tc.desc: OnWindowSizeChanged EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, OnWindowSizeChangedTest001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->windowSize_ = SizeT<int32_t>(1600, 800);
    sheetPattern->OnWindowSizeChanged(100, 100, WindowSizeChangeReason::UNDEFINED);
    EXPECT_TRUE(sheetPattern->windowChanged_);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: AdditionalScrollTo001
 * @tc.desc: AdditionalScrollTo EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, AdditionalScrollTo001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 501, AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);

    auto scrollGeometryNode = scrollNode->GetGeometryNode();
    ASSERT_NE(scrollGeometryNode, nullptr);
    auto size = scrollGeometryNode->GetFrameSize();
    size.SetHeight(100.0f);
    scrollGeometryNode->SetFrameSize(size);

    auto buildContent = sheetPattern->GetFirstFrameNodeOfBuilder();
    CHECK_NULL_VOID(buildContent);
    auto buildContentGeometryNode = buildContent->GetGeometryNode();
    ASSERT_NE(buildContentGeometryNode, nullptr);
    auto size1 = buildContentGeometryNode->GetFrameSize();
    size1.SetHeight(50.0f);
    buildContentGeometryNode->SetFrameSize(size1);
    auto res = sheetPattern->AdditionalScrollTo(scrollNode, 10.0f);
    EXPECT_TRUE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayManagertest001
 * @tc.desc: GetOverlayManager OverlayManager
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetOverlayManagertest001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetStyle currentStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    currentStyle.showInSubWindow = false;
    auto OverlayManager = sheetPattern->GetOverlayManager();
    ASSERT_NE(OverlayManager, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetCurrentScrollHeight001
 * @tc.desc: GetCurrentScrollHeight scrollHeight_
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetCurrentScrollHeight001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    scrollPattern->currentOffset_ = -100.0f;
    sheetPattern->scrollHeight_ = 200.0f;

    sheetPattern->GetCurrentScrollHeight();
    EXPECT_EQ(sheetPattern->scrollHeight_, 100.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateSheetWhenSheetTypeChanged001
 * @tc.desc: UpdateSheetWhenSheetTypeChanged
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateSheetWhenSheetTypeChanged001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    sheetNode->isRenderDirtyMarked_ = false;
    sheetNode->isLayoutDirtyMarked_ = false;

    CHECK_NULL_VOID(sheetPattern->sheetObject_);
    sheetPattern->UpdateSheetWhenSheetTypeChanged();
    EXPECT_TRUE(sheetNode->isRenderDirtyMarked_);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragStart001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetObject = sheetPattern->GetSheetObject();
    CHECK_NULL_VOID(sheetObject);

    sheetPattern->isAnimationProcess_ = false;
    sheetObject->HandleDragStart();
    EXPECT_TRUE(sheetPattern->IsDragging());
    EXPECT_FLOAT_EQ(sheetPattern->currentOffset_, 0.0f);
    EXPECT_TRUE(sheetPattern->GetIsDirectionUp());
    EXPECT_FALSE(sheetPattern->GetAnimationBreak());
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragStart002
 * @tc.desc: HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragStart002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetNode, nullptr);
    auto sheetObject = sheetPattern->GetSheetObject();
    CHECK_NULL_VOID(sheetObject);

    AnimationOption option;
    auto propertyCallback = []() {};
    sheetPattern->animation_ = AnimationUtils::StartAnimation(option, propertyCallback);
    sheetPattern->isAnimationProcess_ = true;
    sheetObject->HandleDragStart();
    EXPECT_TRUE(sheetPattern->IsDragging());
    EXPECT_FLOAT_EQ(sheetPattern->currentOffset_, 0.0f);
    EXPECT_TRUE(sheetPattern->GetIsDirectionUp());
    EXPECT_TRUE(sheetPattern->GetAnimationBreak());
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionBottom001
 * @tc.desc: CheckDirectionBottom EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionBottom001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 1200);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionBottom(targetSize, targetOffset);
    EXPECT_TRUE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionBottom002
 * @tc.desc: CheckDirectionBottom EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionBottom002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 800);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionBottom(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionBottom003
 * @tc.desc: CheckDirectionBottom EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionBottom003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 800);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 500.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionBottom(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionTop001
 * @tc.desc: CheckDirectionTop EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionTop001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 1200);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 50.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionTop(targetSize, targetOffset);
    EXPECT_TRUE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionTop002
 * @tc.desc: CheckDirectionTop EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionTop002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 800);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 500.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionTop(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionTop003
 * @tc.desc: CheckDirectionTop EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionTop003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 1200);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionTop(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionRight001
 * @tc.desc: CheckDirectionRight EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionRight001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 800);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionRight(targetSize, targetOffset);
    EXPECT_TRUE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionRight002
 * @tc.desc: CheckDirectionRight EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionRight002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 800);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 500.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 300.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionRight(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionRight003
 * @tc.desc: CheckDirectionRight EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionRight003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 500.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionRight(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionRight001
 * @tc.desc: CheckDirectionLeft EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionLeft001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(150.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 800);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 500.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionLeft(targetSize, targetOffset);
    EXPECT_TRUE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionRight001
 * @tc.desc: CheckDirectionLeft EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionLeft002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 500.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionLeft(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckDirectionRight001
 * @tc.desc: CheckDirectionLeft EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckDirectionLeft003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(150.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 500.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckDirectionLeft(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckPlacementBottom001
 * @tc.desc: CheckPlacementBottom EXPECT TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckPlacementBottom001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(150.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 450.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckPlacementBottom(targetSize, targetOffset);
    EXPECT_TRUE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckPlacementBottom002
 * @tc.desc: CheckPlacementBottom EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckPlacementBottom002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(300.0f, 400.0f);
    OffsetF targetOffset(150.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 300, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 450.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckPlacementBottom(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckPlacementBottom003
 * @tc.desc: CheckPlacementBottom EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckPlacementBottom003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(10.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 450.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckPlacementBottom(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckPlacementBottomRight001
 * @tc.desc: CheckPlacementBottomRight EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckPlacementBottomRight001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(60.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 450.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckPlacementBottomRight(targetSize, targetOffset);
    EXPECT_TRUE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckPlacementBottomRight001
 * @tc.desc: CheckPlacementBottomRight EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckPlacementBottomRight002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(40.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 500, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 450.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckPlacementBottomRight(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: CheckPlacementBottomRight001
 * @tc.desc: CheckPlacementBottomRight EXPECT FLASE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, CheckPlacementBottomRight003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(60.0f, 400.0f);
    OffsetF targetOffset(50.0f, 100.0f);

    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->windowGlobalRect_ = Rect(0, 0, 100, 500);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 100.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 450.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = Dimension(10.0f);
    sheetWrapperLayoutAlgorithm->windowEdgeWidth_ = 5.0f;

    bool result = sheetWrapperLayoutAlgorithm->CheckPlacementBottomRight(targetSize, targetOffset);
    EXPECT_FALSE(result);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SetArrowOffsetInBottomOrTop001
 * @tc.desc: SetArrowOffsetInBottomOrTop
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetArrowOffsetInBottomOrTop001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(200.0f, 100.0f);
    OffsetF targetOffset(400.0f, 0.0f);
    float sheetOffset = 150.0f;
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 300.0f;

    sheetWrapperLayoutAlgorithm->SetArrowOffsetInBottomOrTop(targetSize, targetOffset, sheetOffset);
    EXPECT_FLOAT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetX, 292.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SetArrowOffsetInRightOrLeft001
 * @tc.desc: SetArrowOffsetInRightOrLeft
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetArrowOffsetInRightOrLeft001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SizeF targetSize(200.0f, 100.0f);
    OffsetF targetOffset(400.0f, 0.0f);
    float sheetOffset = 150.0f;
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 300.0f;

    sheetWrapperLayoutAlgorithm->SetArrowOffsetInRightOrLeft(targetSize, targetOffset, sheetOffset);
    EXPECT_FLOAT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowOffsetY, 8.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: IsSingleDetents001
 * @tc.desc: IsSingleDetents FALSE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, IsSingleDetents001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    NG::SheetStyle sheetStyle;
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    auto res = SheetView::IsSingleDetents(sheetStyle);
    EXPECT_FALSE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: IsSingleDetents002
 * @tc.desc: IsSingleDetents TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, IsSingleDetents002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    NG::SheetStyle sheetStyle;
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    auto res = SheetView::IsSingleDetents(sheetStyle);
    EXPECT_TRUE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: IsSingleDetents003
 * @tc.desc: IsSingleDetents FALSE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, IsSingleDetents003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    NG::SheetStyle sheetStyle;
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    auto res = SheetView::IsSingleDetents(sheetStyle);
    EXPECT_FALSE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: IsSingleDetents004
 * @tc.desc: IsSingleDetents TRUE
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, IsSingleDetents004, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    NG::SheetStyle sheetStyle;
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    auto res = SheetView::IsSingleDetents(sheetStyle);
    EXPECT_TRUE(res);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: MinusSubwindowDistance001
 * @tc.desc: MinusSubwindowDistance
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, MinusSubwindowDistance001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto sheetPageLayoutAlgorithm = AceType::MakeRefPtr<SheetPresentationLayoutAlgorithm>();
    ASSERT_NE(sheetPageLayoutAlgorithm, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    auto subContainer = AceEngine::Get().GetContainer(sheetWrapperPattern->GetSubWindowId());
    CHECK_NULL_VOID(subContainer);
    auto subWindowContext = AceType::DynamicCast<NG::PipelineContext>(subContainer->GetPipelineContext());
    CHECK_NULL_VOID(subWindowContext);
    subWindowContext->displayWindowRectInfo_ = Rect(0, 0, 100.0f, 100.0f);

    sheetPageLayoutAlgorithm->sheetOffsetX_ = 100.0f;
    sheetPageLayoutAlgorithm->sheetOffsetY_ = 100.0f;
    sheetPageLayoutAlgorithm->MinusSubwindowDistance(sheetWrapperNode);
    EXPECT_FLOAT_EQ(sheetPageLayoutAlgorithm->sheetOffsetX_, 100.0f);
    EXPECT_FLOAT_EQ(sheetPageLayoutAlgorithm->sheetOffsetY_, 100.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleTouchDown001
 * @tc.desc: HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleTouchDown001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    TouchLocationInfo info(fingerId);
    info.globalLocation_ = Offset(100.0f, 100.0f);
    auto dragBarNode =
        FrameNode::CreateFrameNode("SheetDragBarNode", 04, AceType::MakeRefPtr<SheetDragBarPattern>());
    ASSERT_NE(dragBarNode, nullptr);
        auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    dragBarPattern->HandleTouchDown(info);
    EXPECT_FLOAT_EQ(dragBarPattern->downPoint_.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(dragBarPattern->downPoint_.GetY(), 100.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetContentDrawFunction001
 * @tc.desc: GetContentDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetContentDrawFunction001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    SheetDragBarPaintMethod sheetdragbarpaintmethod;
    auto paintFunc = sheetdragbarpaintmethod.GetContentDrawFunction(nullptr);
    EXPECT_EQ(paintFunc, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetContentDrawFunction001
 * @tc.desc: GetContentDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetContentDrawFunction002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(
            ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG, std::move(callback)));
    columnNode->AddChild(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetPaintWrapper = new PaintWrapper(
        columnNode->GetRenderContext(), sheetNode->GetGeometryNode(), sheetNode->GetPaintProperty<PaintProperty>());
        SheetDragBarPaintMethod sheetdragbarpaintmethod;
        auto paintFunc = sheetdragbarpaintmethod.GetContentDrawFunction(sheetPaintWrapper);
        EXPECT_NE(paintFunc, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetAvoidKeyboardModeByDefault001
 * @tc.desc: GetAvoidKeyboardModeByDefault
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetAvoidKeyboardModeByDefault001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->animation_ = nullptr;
    EXPECT_EQ(sheetPattern->animation_, nullptr);
    sheetPattern->InitSheetObject();
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);

    sheetObject->sheetType_ = SheetType::SHEET_POPUP;
    auto sheetKeyboardAvoidMode = sheetObject->GetAvoidKeyboardModeByDefault();
    EXPECT_EQ(sheetKeyboardAvoidMode, SheetKeyboardAvoidMode::NONE);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetAvoidKeyboardModeByDefault001
 * @tc.desc: GetAvoidKeyboardModeByDefault
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetAvoidKeyboardModeByDefault002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->animation_ = nullptr;
    EXPECT_EQ(sheetPattern->animation_, nullptr);
    sheetPattern->InitSheetObject();
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);

    sheetObject->sheetType_ = SheetType::SHEET_CENTER;
    auto sheetKeyboardAvoidMode = sheetObject->GetAvoidKeyboardModeByDefault();
    EXPECT_EQ(sheetKeyboardAvoidMode, SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: DirtyLayoutProcess001
 * @tc.desc: DirtyLayoutProcess
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, DirtyLayoutProcess001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
        auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto dirty = sheetNode->CreateLayoutWrapper();
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    auto algorithm = AceType::MakeRefPtr<SheetPresentationSideLayoutAlgorithm>();
    algorithm->sheetMaxWidth_ = 1.0f;
    algorithm->sheetHeight_ = 100.0f;
    object->DirtyLayoutProcess(layoutAlgorithmWrapper);
    EXPECT_EQ(sheetPattern->centerHeight_, 100.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: DirtyLayoutProcess002
 * @tc.desc: DirtyLayoutProcess
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, DirtyLayoutProcess002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
        auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto dirty = sheetNode->CreateLayoutWrapper();
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    auto algorithm = AceType::MakeRefPtr<SheetPresentationSideLayoutAlgorithm>();
    algorithm->sheetMaxWidth_ = 0.0f;
    algorithm->sheetHeight_ = 50.0f;
    sheetPattern->centerHeight_ = 100.0f;
    object->DirtyLayoutProcess(layoutAlgorithmWrapper);
    EXPECT_EQ(sheetPattern->centerHeight_, 100.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateSidePosition001
 * @tc.desc: UpdateSidePosition
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateSidePosition001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    sheetPattern->isOnAppearing_ = false;
    sheetPattern->isOnDisappearing_ = false;
    sheetPattern->isDrag_ = false;

    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    object->sheetMaxWidth_ = 100.0f;
    object->sheetWidth_ = 50.0f;
    object->UpdateSidePosition();
    const auto& transform = context->GetTransform();
    auto translation = transform->GetTransformTranslate();
    EXPECT_EQ(translation->x.Value(), 50.0f);
    EXPECT_EQ(translation->y.Value(), 0.0f);
    EXPECT_EQ(translation->z.Value(), 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: UpdateSidePosition002
 * @tc.desc: UpdateSidePosition
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, UpdateSidePosition002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    sheetPattern->isOnAppearing_ = false;
    sheetPattern->isOnDisappearing_ = false;
    sheetPattern->isDrag_ = false;

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    object->sheetMaxWidth_ = 100.0f;
    object->sheetWidth_ = 50.0f;
    object->UpdateSidePosition();
    const auto& transform = context->GetTransform();
    auto translation = transform->GetTransformTranslate();
    EXPECT_EQ(translation->x.Value(), 0.0f);
    EXPECT_EQ(translation->y.Value(), 0.0f);
    EXPECT_EQ(translation->z.Value(), 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTransitionCurve001
 * @tc.desc: GetSheetTransitionCurve
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetSheetTransitionCurve001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    float dragVelocity = 100.0f;
    auto curve = object->GetSheetTransitionCurve(dragVelocity);

    EXPECT_FLOAT_EQ(curve->GetMass(), CURVE_MASS);
    EXPECT_FLOAT_EQ(curve->GetStiffness(), CURVE_STIFFNESS);
    EXPECT_FLOAT_EQ(curve->GetDamping(), CURVE_DAMPING);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTransitionFinishEvent001
 * @tc.desc: GetSheetTransitionFinishEvent
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetSheetTransitionFinishEvent001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    bool isTransitionIn = false;
    auto event = object->GetSheetTransitionFinishEvent(isTransitionIn);
    EXPECT_NE(event, nullptr);
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTransitionFinishEvent002
 * @tc.desc: GetSheetTransitionFinishEvent
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetSheetTransitionFinishEvent002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    bool isTransitionIn = true;
    sheetPattern->isAnimationBreak_ = false;
    auto event = object->GetSheetTransitionFinishEvent(isTransitionIn);
    EXPECT_NE(event, nullptr);
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    EXPECT_EQ(sheetPattern->GetSheetObject()->currentOffset_, 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTransitionFinishEvent003
 * @tc.desc: GetSheetTransitionFinishEvent
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetSheetTransitionFinishEvent003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    bool isTransitionIn = true;
    sheetPattern->isAnimationBreak_ = true;
    auto event = object->GetSheetTransitionFinishEvent(isTransitionIn);
    EXPECT_NE(event, nullptr);
    EXPECT_FALSE(sheetPattern->isAnimationBreak_);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetAnimationEvent001
 * @tc.desc: GetSheetAnimationEvent
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetSheetAnimationEvent001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    bool isTransitionIn = true;
    float offset = 100.0f;
    object->sheetMaxWidth_ = 100.0f;
    object->sheetWidth_ = 50.0f;
    const auto& transform = context->GetTransform();
    auto translation = transform->GetTransformTranslate();
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    auto event = object->GetSheetAnimationEvent(isTransitionIn, offset);
    EXPECT_NE(event, nullptr);
    EXPECT_EQ(translation->x.Value(), 50.0f);
    EXPECT_EQ(translation->y.Value(), 0.0f);
    EXPECT_EQ(translation->z.Value(), 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetAnimationEvent002
 * @tc.desc: GetSheetAnimationEvent
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetSheetAnimationEvent002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    bool isTransitionIn = false;
    float offset = 100.0f;
    object->sheetMaxWidth_ = 100.0f;
    const auto& transform = context->GetTransform();
    auto translation = transform->GetTransformTranslate();
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    auto event = object->GetSheetAnimationEvent(isTransitionIn, offset);
    EXPECT_NE(event, nullptr);
    EXPECT_EQ(translation->x.Value(), 100.0f);
    EXPECT_EQ(translation->y.Value(), 0.0f);
    EXPECT_EQ(translation->z.Value(), 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: SetFinishEventForAnimationOption001
 * @tc.desc: SetFinishEventForAnimationOption
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, SetFinishEventForAnimationOption001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    AnimationOption option;
    bool isTransitionIn = true;
    bool isFirstTransition = true;
    object->SetFinishEventForAnimationOption(option, isTransitionIn, isFirstTransition);
    EXPECT_NE(option.onFinishEvent_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdateForLTR001
 * @tc.desc: HandleDragUpdateForLTR
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragUpdateForLTR001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    GestureEvent event;
    event.mainDelta_ = 10.0;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = -20.0f;
    sheetObject->sheetWidth_ = 10.0f;
    object->HandleDragUpdateForLTR(event);

    EXPECT_EQ(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdateForLTR002
 * @tc.desc: HandleDragUpdateForLTR
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragUpdateForLTR002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    GestureEvent event;
    event.mainDelta_ = 10.0;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 10.0f;
    sheetObject->sheetWidth_ = 10.0f;
    object->HandleDragUpdateForLTR(event);

    EXPECT_NE(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdateForRTL001
 * @tc.desc: HandleDragUpdateForRTL
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragUpdateForRTL001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    GestureEvent event;
    event.mainDelta_ = 10.0;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 10.0f;
    sheetObject->sheetWidth_ = 10.0f;
    object->HandleDragUpdateForRTL(event);

    EXPECT_EQ(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdateForRTL002
 * @tc.desc: HandleDragUpdateForRTL
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragUpdateForRTL002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    GestureEvent event;
    event.mainDelta_ = 10.0;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = -20.0f;
    sheetObject->sheetWidth_ = 10.0f;
    object->HandleDragUpdateForRTL(event);

    EXPECT_NE(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForLTR001
 * @tc.desc: HandleDragEndForLTR
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForLTR001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = 500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 10.0f;
    sheetObject->sheetWidth_ = 10.0f;
    object->HandleDragEndForLTR(dragVelocity);
    EXPECT_TRUE(sheetPattern->isDirectionUp_);
    EXPECT_NE(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForLTR002
 * @tc.desc: HandleDragEndForLTR
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForLTR002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = 500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 1.0f;
    sheetObject->sheetWidth_ = 10.0f;
    AnimationOption option;
    object->HandleDragEndForLTR(dragVelocity);
    EXPECT_EQ(option.fillMode_, FillMode::FORWARDS);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForLTR003
 * @tc.desc: HandleDragEndForLTR
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForLTR003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = -1500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 1.0f;
    sheetObject->sheetWidth_ = 10.0f;
    AnimationOption option;
    object->HandleDragEndForLTR(dragVelocity);
    EXPECT_EQ(option.fillMode_, FillMode::FORWARDS);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForLTR004
 * @tc.desc: HandleDragEndForLTR
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForLTR004, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = 1500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 10.0f;
    sheetObject->sheetWidth_ = 10.0f;
    AnimationOption option;
    object->HandleDragEndForLTR(dragVelocity);
    EXPECT_TRUE(sheetPattern->isDirectionUp_);
    EXPECT_NE(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForRTL001
 * @tc.desc: HandleDragEndForRTL
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForRTL001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = 500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 10.0f;
    sheetObject->sheetWidth_ = 10.0f;
    AnimationOption option;
    object->HandleDragEndForRTL(dragVelocity);
    EXPECT_TRUE(sheetPattern->isDirectionUp_);
    EXPECT_NE(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForRTL002
 * @tc.desc: HandleDragEndForRTL
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForRTL002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = 500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 1.0f;
    sheetObject->sheetWidth_ = 10.0f;
    AnimationOption option;
    object->HandleDragEndForRTL(dragVelocity);
    EXPECT_EQ(option.fillMode_, FillMode::FORWARDS);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForRTL003
 * @tc.desc: HandleDragEndForRTL
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForRTL003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = -1500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 10.0f;
    sheetObject->sheetWidth_ = 10.0f;
    AnimationOption option;
    object->HandleDragEndForRTL(dragVelocity);
    EXPECT_TRUE(sheetPattern->isDirectionUp_);
    EXPECT_NE(sheetPattern->onWidthDidChange_, nullptr);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragEndForRTL004
 * @tc.desc: HandleDragEndForRTL
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, HandleDragEndForRTL004, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);

    float dragVelocity = 1500.0f;
    auto sheetObject = sheetPattern->GetSheetObject();
    ASSERT_NE(sheetObject, nullptr);
    sheetObject->currentOffset_ = 10.0f;
    sheetObject->sheetWidth_ = 10.0f;
    AnimationOption option;
    object->HandleDragEndForRTL(dragVelocity);
    EXPECT_EQ(option.fillMode_, FillMode::FORWARDS);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetUpOffsetCaretNeed001
 * @tc.desc: GetUpOffsetCaretNeed
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetUpOffsetCaretNeed001, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSafeAreaManager();
    ASSERT_NE(manager, nullptr);
    manager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    manager->keyboardInset_.start = 0;
    manager->keyboardInset_.end = 0;
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    auto height = object->GetUpOffsetCaretNeed();
    EXPECT_EQ(height, 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetUpOffsetCaretNeed002
 * @tc.desc: GetUpOffsetCaretNeed
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetUpOffsetCaretNeed002, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSafeAreaManager();
    ASSERT_NE(manager, nullptr);
    manager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET_WITH_CARET;
    manager->keyboardInset_.start = 0;
    manager->keyboardInset_.end = 10;
    manager->systemSafeArea_.bottom_.start = 0;
    manager->systemSafeArea_.bottom_.end = 10;
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    auto height = object->GetUpOffsetCaretNeed();
    EXPECT_EQ(height, 20);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetUpOffsetCaretNeed003
 * @tc.desc: GetUpOffsetCaretNeed
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetUpOffsetCaretNeed003, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSafeAreaManager();
    ASSERT_NE(manager, nullptr);
    manager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    manager->keyboardInset_.start = 0;
    manager->keyboardInset_.end = 10;
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    auto height = object->GetUpOffsetCaretNeed();
    EXPECT_EQ(height, 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetUpOffsetCaretNeed003
 * @tc.desc: GetUpOffsetCaretNeed
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetUpOffsetCaretNeed004, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSafeAreaManager();
    ASSERT_NE(manager, nullptr);
    manager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET_WITH_CARET;
    manager->keyboardInset_.start = 0;
    manager->keyboardInset_.end = 10;
    manager->systemSafeArea_.bottom_.start = 0;
    manager->systemSafeArea_.bottom_.end = 10;
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    textFieldManager->optionalPosition_ = Offset { 10.0f, 20.0f };
    auto height = object->GetUpOffsetCaretNeed();
    EXPECT_EQ(height, 20);
    SheetPresentationTestFourNg::TearDownTestCase();
}

/**
 * @tc.name: GetUpOffsetCaretNeed003
 * @tc.desc: GetUpOffsetCaretNeed
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestFourNg, GetUpOffsetCaretNeed005, TestSize.Level1)
{
    SheetPresentationTestFourNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSafeAreaManager();
    ASSERT_NE(manager, nullptr);
    manager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET_WITH_CARET;
    manager->keyboardInset_.start = 0;
    manager->keyboardInset_.end = 10;
    manager->systemSafeArea_.bottom_.start = 0;
    manager->systemSafeArea_.bottom_.end = 10;
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    CHECK_NULL_VOID(object);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    textFieldManager->optionalPosition_ = Offset { 10.0f, 20.0f };
    pipeline->rootHeight_ = 100;
    textFieldManager->height_ = 10;
    auto height = object->GetUpOffsetCaretNeed();
    EXPECT_EQ(height, 0.0f);
    SheetPresentationTestFourNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG