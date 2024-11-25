/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
    const SafeAreaInsets::Inset KEYBOARD_INSET = { .start = 500.f, .end = 1000.f };
} // namespace

class SheetPresentationTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
    static void TearDownTestCase();

private:
    void SetOnBindSheet();
    void CreateSheetBuilder();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
};

void SheetPresentationTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
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

void SheetPresentationTestTwoNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
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

void SheetPresentationTestTwoNg::CreateSheetBuilder()
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}

void SheetPresentationTestTwoNg::SetOnBindSheet()
{
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    SheetStyle style;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), style,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
}

void SheetPresentationTestTwoNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
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
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
}

void SheetPresentationTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SetSheetType001
 * @tc.desc: Increase the coverage of SheetPresentationTestTwoNg::SetSheetType function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SetSheetType001, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM);

    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_FREE_WINDOW);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_FREE_WINDOW);

    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM_OFFSET);

    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOMLANDSPACE);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOMLANDSPACE);

    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_CENTER);

    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsPhoneInLandScape001
 * @tc.desc: Increase the coverage of SheetPresentationPattern::IsPhoneInLandScape function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsPhoneInLandScape001, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "popup";
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);

    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_NE(pipelineContext->GetTheme<SheetTheme>(), nullptr);
    auto sheetType = pipelineContext->GetTheme<SheetTheme>()->GetSheetType();
    EXPECT_NE(sheetType, "auto");
    bool ret = sheetPattern->IsPhoneInLandScape();
    EXPECT_FALSE(ret);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsPhoneInLandScape002
 * @tc.desc: Increase the coverage of SheetPresentationPattern::IsPhoneInLandScape function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsPhoneInLandScape002, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "auto";
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return true; });

    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_NE(pipelineContext->GetTheme<SheetTheme>(), nullptr);
    auto sheetType = pipelineContext->GetTheme<SheetTheme>()->GetSheetType();
    EXPECT_EQ(sheetType, "auto");
    auto foldWindow = FoldableWindow::CreateFoldableWindow(containerId);
    ASSERT_NE(foldWindow, false);
    EXPECT_TRUE(foldWindow->IsFoldExpand());
    bool ret = sheetPattern->IsPhoneInLandScape();
    EXPECT_FALSE(ret);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsPhoneInLandScape003
 * @tc.desc: Increase the coverage of SheetPresentationPattern::IsPhoneInLandScape function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsPhoneInLandScape003, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "auto";
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return false; });
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;

    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_NE(pipelineContext->GetTheme<SheetTheme>(), nullptr);
    auto sheetType = pipelineContext->GetTheme<SheetTheme>()->GetSheetType();
    EXPECT_EQ(sheetType, "auto");
    auto foldWindow = FoldableWindow::CreateFoldableWindow(containerId);
    ASSERT_NE(foldWindow, false);
    EXPECT_FALSE(foldWindow->IsFoldExpand());
    EXPECT_NE(SystemProperties::GetDeviceOrientation(), DeviceOrientation::LANDSCAPE);
    bool ret = sheetPattern->IsPhoneInLandScape();
    EXPECT_FALSE(ret);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsPhoneInLandScape004
 * @tc.desc: Increase the coverage of SheetPresentationPattern::IsPhoneInLandScape function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsPhoneInLandScape004, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "auto";
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return false; });
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;

    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_NE(pipelineContext->GetTheme<SheetTheme>(), nullptr);
    auto sheetType = pipelineContext->GetTheme<SheetTheme>()->GetSheetType();
    EXPECT_EQ(sheetType, "auto");
    auto foldWindow = FoldableWindow::CreateFoldableWindow(containerId);
    ASSERT_NE(foldWindow, false);
    EXPECT_FALSE(foldWindow->IsFoldExpand());
    EXPECT_EQ(SystemProperties::GetDeviceOrientation(), DeviceOrientation::LANDSCAPE);
    bool ret = sheetPattern->IsPhoneInLandScape();
    EXPECT_TRUE(ret);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdate001
 * @tc.desc: Increase the coverage of SheetPresentationPattern::HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, HandleDragUpdate001, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);

    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    GestureEvent info;
    sheetPattern->HandleDragUpdate(info);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdate002
 * @tc.desc: Increase the coverage of SheetPresentationPattern::HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, HandleDragUpdate002, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    EXPECT_TRUE(sheetPattern->sheetDetentHeight_.size() <= 0);
    GestureEvent info;
    sheetPattern->HandleDragUpdate(info);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdate003
 * @tc.desc: Increase the coverage of SheetPresentationPattern::HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, HandleDragUpdate003, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make detentSize greater than 0
    sheetPattern->sheetDetentHeight_.emplace_back(1800.0f);
    // Make height - currentOffset_ less than maxDetentSize
    sheetPattern->height_ = 1000;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    // Make currentOffset_ equal to tempOffset
    GestureEvent info;
    info.mainDelta_ = 0.0f;
    sheetPattern->currentOffset_ = 0;

    // Ensure sheetType is not SHEET_POPUP
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);
    auto height = sheetPattern->height_ + sheetPattern->sheetHeightUp_ - sheetPattern->bottomOffsetY_;
    auto maxDetentSize = sheetPattern->sheetDetentHeight_[sheetPattern->sheetDetentHeight_.size() - 1];
    EXPECT_FALSE(GreatNotEqual((height - sheetPattern->currentOffset_), maxDetentSize));
    sheetPattern->HandleDragUpdate(info);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdate004
 * @tc.desc: Increase the coverage of SheetPresentationPattern::HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, HandleDragUpdate004, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make detentSize greater than 0
    sheetPattern->sheetDetentHeight_.emplace_back(800.0f);
    // Make height - currentOffset_ greater than maxDetentSize
    sheetPattern->height_ = 1000;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    // Make mainDelta greater than 0
    // Make currentOffset_ greater than tempOffset
    GestureEvent info;
    info.mainDelta_ = 10.0f;
    sheetPattern->currentOffset_ = 0;
    // Make offset greater than pageHeight - sheetMaxHeight_
    sheetPattern->pageHeight_ = 1200.0f;
    sheetPattern->sheetMaxHeight_ = 1800.0f;
    // Make isNeedChangeScrollHeight false
    sheetPattern->scrollSizeMode_ = ScrollSizeMode::FOLLOW_DETENT;

    // Ensure sheetType is not SHEET_POPUP
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);
    auto height = sheetPattern->height_ + sheetPattern->sheetHeightUp_ - sheetPattern->bottomOffsetY_;
    auto maxDetentSize = sheetPattern->sheetDetentHeight_[sheetPattern->sheetDetentHeight_.size() - 1];
    EXPECT_TRUE(GreatNotEqual((height - sheetPattern->currentOffset_), maxDetentSize));
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    EXPECT_FALSE(LessNotEqual(mainDelta, 0));
    // Ensure IsSheetBottomStyle returns true
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());
    sheetPattern->HandleDragUpdate(info);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdate005
 * @tc.desc: Increase the coverage of SheetPresentationPattern::HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, HandleDragUpdate005, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make detentSize greater than 0
    sheetPattern->sheetDetentHeight_.emplace_back(800.0f);
    // Make height - currentOffset_ greater than maxDetentSize
    sheetPattern->height_ = 1000;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    // Make mainDelta less than 0
    // Make currentOffset_ less than tempOffset
    GestureEvent info;
    info.mainDelta_ = -10.0f;
    sheetPattern->currentOffset_ = 0;
    // Make sheetMaxHeight_ equal to 0.0f
    // Make offset less than pageHeight - sheetMaxHeight_
    sheetPattern->sheetMaxHeight_ = 0.0f;

    // Ensure sheetType is not SHEET_POPUP
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);
    auto height = sheetPattern->height_ + sheetPattern->sheetHeightUp_ - sheetPattern->bottomOffsetY_;
    auto maxDetentSize = sheetPattern->sheetDetentHeight_[sheetPattern->sheetDetentHeight_.size() - 1];
    EXPECT_TRUE(GreatNotEqual((height - sheetPattern->currentOffset_), maxDetentSize));
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    EXPECT_TRUE(LessNotEqual(mainDelta, 0));
    sheetPattern->HandleDragUpdate(info);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdate006
 * @tc.desc: Increase the coverage of SheetPresentationPattern::HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, HandleDragUpdate006, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make detentSize greater than 0
    sheetPattern->sheetDetentHeight_.emplace_back(800.0f);
    // Make height - currentOffset_ greater than maxDetentSize
    sheetPattern->height_ = 1000;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    // Make mainDelta less than 0
    // Make currentOffset_ less than tempOffset
    GestureEvent info;
    info.mainDelta_ = -10.0f;
    sheetPattern->currentOffset_ = 0;
    // Make sheetMaxHeight_ greater than 0.0f
    // Make offset greater than pageHeight - sheetMaxHeight_
    sheetPattern->sheetMaxHeight_ = 1800.0f;

    // Ensure sheetType is not SHEET_POPUP
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);
    auto height = sheetPattern->height_ + sheetPattern->sheetHeightUp_ - sheetPattern->bottomOffsetY_;
    auto maxDetentSize = sheetPattern->sheetDetentHeight_[sheetPattern->sheetDetentHeight_.size() - 1];
    EXPECT_TRUE(GreatNotEqual((height - sheetPattern->currentOffset_), maxDetentSize));
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    EXPECT_TRUE(LessNotEqual(mainDelta, 0));
    sheetPattern->HandleDragUpdate(info);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragUpdate007
 * @tc.desc: Increase the coverage of SheetPresentationPattern::HandleDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, HandleDragUpdate007, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    // Make detentSize greater than 0
    sheetPattern->sheetDetentHeight_.emplace_back(1800.0f);
    // Make height - currentOffset_ less than maxDetentSize
    sheetPattern->height_ = 1000;
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    // Make mainDelta less than 0
    // Make currentOffset_ less than tempOffset
    GestureEvent info;
    info.mainDelta_ = -10.0f;
    sheetPattern->currentOffset_ = 0;
    // Make offset greater than pageHeight - sheetMaxHeight_
    sheetPattern->sheetMaxHeight_ = 1800.0f;
    // Make isNeedChangeScrollHeight true
    sheetPattern->scrollSizeMode_ = ScrollSizeMode::CONTINUOUS;
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;

    // Ensure sheetType is not SHEET_POPUP
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);
    auto height = sheetPattern->height_ + sheetPattern->sheetHeightUp_ - sheetPattern->bottomOffsetY_;
    auto maxDetentSize = sheetPattern->sheetDetentHeight_[sheetPattern->sheetDetentHeight_.size() - 1];
    EXPECT_FALSE(GreatNotEqual((height - sheetPattern->currentOffset_), maxDetentSize));
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    EXPECT_TRUE(LessNotEqual(mainDelta, 0));
    // Ensure IsSheetBottomStyle returns true
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());
    sheetPattern->HandleDragUpdate(info);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBeforeTranslate001
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBeforeTranslate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBeforeTranslate001, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::RESIZE_ONLY;

    EXPECT_EQ(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::RESIZE_ONLY);
    sheetPattern->AvoidKeyboardBeforeTranslate();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBeforeTranslate002
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBeforeTranslate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBeforeTranslate002, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::NONE;

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::RESIZE_ONLY);
    sheetPattern->AvoidKeyboardBeforeTranslate();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardAfterTranslate001
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardAfterTranslate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardAfterTranslate001, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::NONE;

    EXPECT_EQ(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    sheetPattern->AvoidKeyboardAfterTranslate(1000.0f);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardAfterTranslate002
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardAfterTranslate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardAfterTranslate002, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::RESIZE_ONLY;

    EXPECT_EQ(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::RESIZE_ONLY);
    sheetPattern->AvoidKeyboardAfterTranslate(1000.0f);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardAfterTranslate003
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardAfterTranslate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardAfterTranslate003, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE;

    EXPECT_EQ(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE);
    sheetPattern->AvoidKeyboardAfterTranslate(1000.0f);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardAfterTranslate004
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardAfterTranslate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardAfterTranslate004, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;

    EXPECT_EQ(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL);
    sheetPattern->AvoidKeyboardAfterTranslate(1000.0f);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardAfterTranslate005
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardAfterTranslate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardAfterTranslate005, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode(100);

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::RESIZE_ONLY);
    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::TRANSLATE_AND_RESIZE);
    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL);
    sheetPattern->AvoidKeyboardAfterTranslate(1000.0f);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBySheetMode001
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode001, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::NONE;

    EXPECT_EQ(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    sheetPattern->AvoidKeyboardBySheetMode();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBySheetMode002
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode002, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make keyboardAvoidMode_ not equal to SheetKeyboardAvoidMode::NONE
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    // Make keyboardHeight_ equal to manager->GetKeyboardInset().Length()
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    sheetPattern->keyboardHeight_ = safeAreaManager->GetKeyboardInset().Length();

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_EQ(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    sheetPattern->AvoidKeyboardBySheetMode();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBySheetMode003
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode003, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make keyboardAvoidMode_ not equal to SheetKeyboardAvoidMode::NONE
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    // Make keyboardHeight_ not equal to manager->GetKeyboardInset().Length()
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    sheetPattern->keyboardHeight_ = safeAreaManager->GetKeyboardInset().Length() + 10.0f;
    // Make isDismissProcess_ true
    sheetPattern->isDismissProcess_ = true;

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_NE(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    EXPECT_TRUE(sheetPattern->isDismissProcess_);
    sheetPattern->AvoidKeyboardBySheetMode();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBySheetMode004
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode004, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make keyboardAvoidMode_ not equal to SheetKeyboardAvoidMode::NONE
    // Make AvoidKeyboardBeforeTranslate return true
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::RESIZE_ONLY;
    // Make keyboardHeight_ not equal to manager->GetKeyboardInset().Length()
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    sheetPattern->keyboardHeight_ = safeAreaManager->GetKeyboardInset().Length() + 10.0f;
    // Make isDismissProcess_ false
    sheetPattern->isDismissProcess_ = false;

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_NE(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    EXPECT_FALSE(sheetPattern->isDismissProcess_);
    EXPECT_TRUE(sheetPattern->AvoidKeyboardBeforeTranslate());
    sheetPattern->AvoidKeyboardBySheetMode();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBySheetMode005
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode005, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make keyboardAvoidMode_ not equal to SheetKeyboardAvoidMode::NONE
    // Make AvoidKeyboardBeforeTranslate return false
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    // Make keyboardHeight_ not equal to manager->GetKeyboardInset().Length()
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    sheetPattern->keyboardHeight_ = safeAreaManager->GetKeyboardInset().Length() + 10.0f;
    // Make isDismissProcess_ false
    sheetPattern->isDismissProcess_ = false;
    // Make isScrolling_ false
    sheetPattern->isScrolling_ = false;
    // Make IsSheetBottomStyle return false
    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_NE(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    EXPECT_FALSE(sheetPattern->isDismissProcess_);
    EXPECT_FALSE(sheetPattern->AvoidKeyboardBeforeTranslate());
    EXPECT_FALSE(sheetPattern->isScrolling_);
    EXPECT_FALSE(sheetPattern->IsSheetBottomStyle());
    sheetPattern->AvoidKeyboardBySheetMode();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBySheetMode006
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode006, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make keyboardAvoidMode_ not equal to SheetKeyboardAvoidMode::NONE
    // Make AvoidKeyboardBeforeTranslate return false
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    // Make keyboardHeight_ not equal to manager->GetKeyboardInset().Length()
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    sheetPattern->keyboardHeight_ = safeAreaManager->GetKeyboardInset().Length() + 10.0f;
    // Make isDismissProcess_ false
    sheetPattern->isDismissProcess_ = false;
    // Make isScrolling_ true
    sheetPattern->isScrolling_ = true;
    // Make heightUp equal to 0
    auto focusHub = host->GetFocusHub();
    focusHub->currentFocus_ = false;
    // Make IsSheetBottomStyle return false
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_NE(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    EXPECT_FALSE(sheetPattern->isDismissProcess_);
    EXPECT_FALSE(sheetPattern->AvoidKeyboardBeforeTranslate());
    EXPECT_TRUE(sheetPattern->isScrolling_);
    EXPECT_FALSE(focusHub->IsCurrentFocus());
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());
    sheetPattern->AvoidKeyboardBySheetMode();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidKeyboardBySheetMode007
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode007, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    // Make keyboardAvoidMode_ not equal to SheetKeyboardAvoidMode::NONE
    // Make AvoidKeyboardBeforeTranslate return false
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    // Make keyboardHeight_ not equal to manager->GetKeyboardInset().Length()
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    sheetPattern->keyboardHeight_ = safeAreaManager->GetKeyboardInset().Length() + 10.0f;
    // Make isDismissProcess_ false
    sheetPattern->isDismissProcess_ = false;
    // Make isScrolling_ true
    sheetPattern->isScrolling_ = true;
    // Make heightUp not equal to 0
    // Make GetSheetHeightChange return not 0
    auto focusHub = host->GetFocusHub();
    focusHub->currentFocus_ = true;
    safeAreaManager->keyboardInset_.end = 1000.0f;
    pipelineContext->rootHeight_ = 1800.0f;
    // Make IsSheetBottomStyle return false
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_NE(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    EXPECT_FALSE(sheetPattern->isDismissProcess_);
    EXPECT_FALSE(sheetPattern->AvoidKeyboardBeforeTranslate());
    EXPECT_TRUE(sheetPattern->isScrolling_);
    EXPECT_NE(sheetPattern->GetSheetHeightChange(), 0.0f);
    EXPECT_TRUE(focusHub->IsCurrentFocus());
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());
    sheetPattern->AvoidKeyboardBySheetMode();
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsCustomHeightOrDetentsChanged001
 * @tc.desc: Test update detents of sheetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsCustomHeightOrDetentsChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    SheetHeight detent;
    detent.sheetMode = SheetMode::AUTO;
    style.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    style.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::LARGE;
    style.detents.emplace_back(detent);
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step2. get sheetNode layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    auto customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step4. change detents of SheetStyle.
     * @tc.expected: padding.right is 0vp
     */
    detent.sheetMode = SheetMode::LARGE;
    style.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    style.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::LARGE;
    style.detents.emplace_back(detent);

    /**
     * @tc.steps: step5. excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: true
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetMode = SheetMode::LARGE;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, true);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsCustomHeightOrDetentsChanged002
 * @tc.desc: Test update sheetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsCustomHeightOrDetentsChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.height = Dimension(100.0f, DimensionUnit::AUTO);
    style.sheetMode = SheetMode::MEDIUM;
    style.showDragBar = false;
    style.showCloseIcon = false;
    style.isTitleBuilder = false;
    style.sheetType = SheetType::SHEET_BOTTOM;
    style.backgroundColor = Color::GREEN;
    style.maskColor = Color::GREEN;
    style.bottomOffset = OffsetF(100.0, 100.0);
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step2. get sheetNode layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: true
     */
    layoutProperty->UpdateSheetStyle(style);
    style.height = Dimension(200.0f, DimensionUnit::AUTO);
    auto customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, true);

    /**
     * @tc.steps: step4. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: true
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetMode = SheetMode::LARGE;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, true);

    /**
     * @tc.steps: step5. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.showDragBar = true;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step6. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.showCloseIcon = true;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step7. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.isTitleBuilder = true;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step8. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.backgroundColor = Color::BLACK;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step9. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.maskColor = Color::BLACK;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step10. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.bottomOffset = OffsetF(200.0, 200.0);
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsCustomHeightOrDetentsChanged003
 * @tc.desc: Test update sheetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsCustomHeightOrDetentsChanged003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::THIN;
    style.backgroundBlurStyle = styleOption;
    style.sheetTitle = "title1";
    style.sheetSubtitle = "subtile1";
    style.interactive = false;
    style.scrollSizeMode = ScrollSizeMode::FOLLOW_DETENT;
    BorderWidthProperty BorderWidth;
    BorderWidth.SetBorderWidth(Dimension(10.0));
    style.borderWidth = BorderWidth;
    style.borderColor = { Color::BLUE, Color::BLUE, Color::BLUE, Color::BLUE };
    style.borderStyle = { BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID, BorderStyle::SOLID };
    Shadow shadow = ShadowConfig::DefaultShadowL;
    style.shadow = shadow;
    style.width = Dimension(100.0f, DimensionUnit::AUTO);
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step2. get sheetNode layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    styleOption.blurStyle = BlurStyle::THICK;
    style.backgroundBlurStyle = styleOption;
    auto customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step4. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetTitle = "title2";
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step5. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetSubtitle = "subtile2";
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step6. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.scrollSizeMode = ScrollSizeMode::CONTINUOUS;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step7. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    BorderWidth.SetBorderWidth(Dimension(20.0));
    style.borderWidth = BorderWidth;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step8. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.borderColor = { Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK };
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step9. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.borderStyle = { BorderStyle::DASHED, BorderStyle::DASHED, BorderStyle::DASHED, BorderStyle::DASHED };
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step10. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    shadow = ShadowConfig::NoneShadow;
    style.shadow = shadow;
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);

    /**
     * @tc.steps: step11. change style and excute the IsCustomHeightOrDetentsChanged function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.width = Dimension(200.0f, DimensionUnit::AUTO);
    customHeightOrDetentsChanged = sheetPattern->IsCustomHeightOrDetentsChanged(style);
    EXPECT_EQ(customHeightOrDetentsChanged, false);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: FireOnHeightDidChange001
 * @tc.desc: Test FireOnHeightDidChange function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, FireOnHeightDidChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create builder.
     */
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };

    auto buildTitleNodeFunc = []() -> RefPtr<UINode> { return nullptr; };

    /**
     * @tc.steps: step3. create sheet node.
     * @tc.expected: Make sure the modalStack holds the sheetNode.
     */
    SheetStyle sheetStyle;
    sheetStyle.height = Dimension(100.0f, DimensionUnit::AUTO);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_EQ(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    /**
     * @tc.steps: step4. same height to excute FireOnHeightDidChange.
     * @tc.expected: preDidHeight_ is 100.
     */

    sheetPattern->FireOnHeightDidChange(100);
    EXPECT_EQ(sheetPattern->preDidHeight_, 100);

    /**
     * @tc.steps: step5. new height to excute FireOnHeightDidChange.
     * @tc.expected: preDidHeight_ is 200.
     */
    sheetPattern->FireOnHeightDidChange(200);
    EXPECT_EQ(sheetPattern->preDidHeight_, 200);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: SheetOffset001
 * @tc.desc: Test SetBottomOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme
     */
    SetOnBindSheet();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step2. set up empty sheet style
     * @tc.expected: bottom offsets are zero
     */
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    sheetPattern->SetBottomOffset(sheetStyle);
    EXPECT_EQ(sheetPattern->bottomOffsetX_, 0.0f);
    EXPECT_EQ(sheetPattern->bottomOffsetY_, 0.0f);
}

/**
 * @tc.name: SheetOffset002
 * @tc.desc: Test SetBottomOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme.
     */
    SetOnBindSheet();
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    /**
     * @tc.steps: step2. sheet is center style.
     * @tc.expected: bottom offsets are zero when style is center.
     */
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    sheetStyle.bottomOffset = { 10.0, -10.0 };
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    sheetPattern->SetBottomOffset(sheetStyle);
    EXPECT_EQ(sheetPattern->bottomOffsetX_, 0.0f);
    EXPECT_EQ(sheetPattern->bottomOffsetY_, 0.0f);

    /**
     * @tc.steps: step3. sheet is bottom style.
     * @tc.expected: bottom offsets are valid when style is center.
     */
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetPattern->SetBottomOffset(sheetStyle);
    EXPECT_NE(sheetPattern->bottomOffsetX_, 0.0f);
    EXPECT_NE(sheetPattern->bottomOffsetY_, 0.0f);
}

/**
 * @tc.name: SheetOffset003
 * @tc.desc: Test Layout, OnDirtyLayoutWrapperSwap and PlaySheetTransition function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme
     */
    SetOnBindSheet();
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. set up sheet algo pre-condition.
     */
    auto dirty = sheetNode->CreateLayoutWrapper();
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM_OFFSET;
    sheetLayoutAlgorithm->sheetMaxHeight_ = 2000;
    sheetLayoutAlgorithm->sheetHeight_ = 1000;
    sheetLayoutAlgorithm->sheetStyle_.bottomOffset = { 10.0, -20.0 };
    sheetLayoutAlgorithm->Layout(AceType::RawPtr(sheetNode));

    /**
     * @tc.steps: step3. test sheet offset.
     */
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    MockPipelineContext::GetCurrent()->SetRootSize(800, 2000);
    SheetStyle sheetStyle;
    layoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step4. test OnDirtyLayoutWrapperSwap and PlaySheetTransition.
     * @tc.expected: sheet offset can be correctly computed.
     */
    sheetPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    overlayManager->PlaySheetTransition(sheetNode, true, true);
    EXPECT_EQ(sheetPattern->GetSheetOffset(), 980);
}

/**
 * @tc.name: SheetOffset004
 * @tc.desc: Test SetSheetOuterBorderWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. set up sheet style
     * @tc.expected: sheet type is bottom style.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.bottomOffset = { 10, 20 };
    layoutProperty->propSheetStyle_ = sheetStyle;
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();

    /**
     * @tc.steps: step3. set up device type
     * @tc.expected: SHEET_BOTTOM_OFFSET only valid in TWO_IN_ONE.
     */
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    auto sheetType = sheetPattern->GetSheetType();
    EXPECT_NE(sheetType, SheetType::SHEET_BOTTOM_OFFSET);
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    auto sheetType1 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType1, SheetType::SHEET_BOTTOM_OFFSET);

    /**
     * @tc.steps: step4. set up sheet theme.
     * @tc.expected: SHEET_BOTTOM_OFFSET can obtain render properties.
     */
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    sheetTheme->sheetOuterBorderWidth_ = Dimension(20.0);
    sheetTheme->sheetInnerBorderWidth_ = Dimension(10.0);
    sheetTheme->sheetRadius_ = Dimension(10.0);
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    sheetPattern->SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
    auto renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), true);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), true);
    EXPECT_EQ(renderContext->GetBorderRadius().has_value(), true);
}

/**
 * @tc.name: SheetOffset005
 * @tc.desc: Test GetSheetHeightBeforeDragUpdate and GetSheetHeightBeforeDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetOffset005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    /**
     * @tc.expected: SHEET_BOTTOM_OFFSET's height can be correctly computed.
     */
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_OFFSET;
    sheetPattern->pageHeight_ = 20;
    sheetPattern->sheetOffsetY_ = 10;
    EXPECT_EQ(sheetPattern->GetSheetHeightBeforeDragUpdate(), 10);
    EXPECT_EQ(sheetPattern->GetMaxSheetHeightBeforeDragUpdate(), 10);
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    EXPECT_EQ(sheetPattern->GetSheetHeightBeforeDragUpdate(), 0);
    EXPECT_EQ(sheetPattern->GetMaxSheetHeightBeforeDragUpdate(), 0);
}

/**
 * @tc.name: SheetOffset006
 * @tc.desc: Test avoid safe area function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetOffset006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. run OnDirtyLayoutWrapperSwap.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    sheetStyle.bottomOffset = { 10, 20 };
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto dirty = sheetNode->CreateLayoutWrapper();
    DirtySwapConfig config;
    config.skipMeasure = false;
    sheetPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    auto sheetType = sheetPattern->GetSheetType();

    /**
     * @tc.expected: SHEET_BOTTOM_OFFSET did not avoid keyboard.
     */
    EXPECT_EQ(sheetType, SheetType::SHEET_BOTTOM_OFFSET);
    EXPECT_EQ(sheetPattern->sheetHeightUp_, 0.0f);
}

/**
 * @tc.name: SheetHoverStatus001
 * @tc.desc: Test InitFoldCreaseRegion function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetHoverStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme.
     */
    SetOnBindSheet();
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step1. set enableHoverMode is true
     * @tc.expected: fold crease region is not empty
     */
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(0, 1064, 2294, 171);
    rects.insert(rects.end(), rect);
    sheetPattern->currentFoldCreaseRegion_ = rects;
    SheetStyle sheetStyle;
    sheetStyle.enableHoverMode = true;
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->InitFoldCreaseRegion();
    EXPECT_TRUE(!sheetPattern->currentFoldCreaseRegion_.empty());
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: SheetHoverStatus002
 * @tc.desc: Test InitParameter function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetHoverStatus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create bind sheet node.
     */
    SheetStyle sheetStyle;
    sheetStyle.enableHoverMode = true;
    sheetStyle.hoverModeArea = HoverModeAreaType::TOP_SCREEN;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test hover mode status flag.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    manager->keyboardInset_ = KEYBOARD_INSET;
    pipeline->isHalfFoldHoverStatus_ = true;
    auto dirty = sheetNode->CreateLayoutWrapper();
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetLayoutAlgorithm->sheetStyle_ = sheetStyle;

    /**
     * @tc.expected: isKeyBoardShow_ and isHoverMode_ are true.
     */
    sheetLayoutAlgorithm->InitParameter();
    EXPECT_TRUE(sheetLayoutAlgorithm->isKeyBoardShow_);
    EXPECT_TRUE(sheetLayoutAlgorithm->isHoverMode_);
    EXPECT_EQ(sheetLayoutAlgorithm->hoverModeArea_, HoverModeAreaType::TOP_SCREEN);
}

/**
 * @tc.name: SheetHoverStatus003
 * @tc.desc: Test InitParameter function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetHoverStatus003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create bind sheet node.
     */
    SheetStyle sheetStyle;
    sheetStyle.enableHoverMode = true;
    sheetStyle.hoverModeArea = HoverModeAreaType::TOP_SCREEN;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    SheetPresentationTestTwoNg::SetUpTestCase();

    /**
     * @tc.steps: step3. test hover mode status flag.
     */
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto dirty = sheetNode->CreateLayoutWrapper();
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    auto sheetTheme1 = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme1->isOuterBorderEnable_ = false;
    SheetStyle sheetStyle1;
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme1);
    sheetLayoutAlgorithm->sheetStyle_ = sheetStyle1;

    /**
     * @tc.expected: isHoverMode_ is false and hoverModeArea_ is BOTTOM_SCREEN.
     */
    sheetLayoutAlgorithm->InitParameter();
    EXPECT_FALSE(sheetLayoutAlgorithm->isHoverMode_);
    EXPECT_EQ(sheetLayoutAlgorithm->hoverModeArea_, HoverModeAreaType::BOTTOM_SCREEN);
}
} // namespace OHOS::Ace::NG