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
    const SafeAreaInsets::Inset KEYBOARD_INSET = { .start = 500.f, .end = 1000.f };
} // namespace

class SheetPresentationTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
    static void TearDownTestCase();
    static void SetApiVersion(int32_t apiTargetVersion);

private:
    void SetOnBindSheet();
    void CreateSheetBuilder();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
};

void SheetPresentationTestTwoNg::SetUpTestCase()
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

void SheetPresentationTestTwoNg::SetApiVersion(int32_t apiTargetVersion)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(apiTargetVersion);
}

void SheetPresentationTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: SetSheetType001
 * @tc.desc: Increase the coverage of SheetPresentationTestTwoNg::SetSheetType function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SetSheetType001, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
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
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    // Make detentSize greater than 0
    sheetPattern->sheetDetentHeight_.emplace_back(1800.0f);
    // Make height - currentOffset_ less than maxDetentSize
    sheetPattern->sheetHeightUp_ = 0;
    sheetPattern->bottomOffsetY_ = 0;
    // Make mainDelta less than 0
    // Make currentOffset_ less than tempOffset
    GestureEvent info;
    info.mainDelta_ = -10.0f;
    sheetPattern->currentOffset_ = 0;
    // Make offset greater than pageHeight - sheetMaxHeight_
    sheetPattern->sheetMaxHeight_ = 1800.0f;
    sheetPattern->height_ = 2000.0f;
    // Make isNeedChangeScrollHeight true
    sheetPattern->scrollSizeMode_ = ScrollSizeMode::CONTINUOUS;
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;

    // Ensure sheetType is not SHEET_POPUP
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    ASSERT_TRUE(sheetPattern->sheetDetentHeight_.size() > 0);
    auto height = sheetPattern->height_ + sheetPattern->sheetHeightUp_ - sheetPattern->bottomOffsetY_;
    auto maxDetentSize = sheetPattern->sheetDetentHeight_[sheetPattern->sheetDetentHeight_.size() - 1];
    EXPECT_TRUE(GreatNotEqual((height - sheetPattern->currentOffset_), maxDetentSize));
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
    safeAreaManager->keyboardInset_ = SafeAreaInsets::Inset();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::POPUP_SHEET;
    host->GetFocusHub()->currentFocus_ = true;
    sheetPattern->AvoidKeyboardBySheetMode();
    EXPECT_EQ(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::RESIZE_ONLY;
    sheetPattern->AvoidKeyboardBySheetMode();
    EXPECT_EQ(sheetPattern->keyboardHeight_, 0);
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
    auto focusHub = host->GetFocusHub();
    focusHub->currentFocus_ = true;
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
 * @tc.name: AvoidKeyboardBySheetMode008
 * @tc.desc: Increase the coverage of SheetPresentationPattern::AvoidKeyboardBySheetMode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, AvoidKeyboardBySheetMode008, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_ETS_TAG, 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, V2::TEXT_ETS_TAG, std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto safeAreaManager = pipelineContext->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    sheetPattern->keyboardHeight_ = safeAreaManager->GetKeyboardInset().Length() + 10.0f;
    sheetPattern->isDismissProcess_ = false;
    sheetPattern->isScrolling_ = true;
    sheetPattern->isAnimationProcess_ = true;
    sheetPattern->AvoidKeyboardBySheetMode();
    AnimationOption option;
    auto propertyCallback = []() {};
    sheetPattern->animation_ = AnimationUtils::StartAnimation(option, propertyCallback);
    auto focusHub = host->GetFocusHub();
    focusHub->currentFocus_ = true;
    safeAreaManager->keyboardInset_.end = 1000.0f;
    pipelineContext->rootHeight_ = 1800.0f;
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;

    EXPECT_NE(sheetPattern->keyboardAvoidMode_, SheetKeyboardAvoidMode::NONE);
    EXPECT_NE(sheetPattern->keyboardHeight_, safeAreaManager->GetKeyboardInset().Length());
    EXPECT_FALSE(sheetPattern->isDismissProcess_);
    EXPECT_FALSE(sheetPattern->AvoidKeyboardBeforeTranslate());
    EXPECT_TRUE(sheetPattern->isScrolling_);
    EXPECT_NE(sheetPattern->GetSheetHeightChange(), 0.0f);
    EXPECT_TRUE(focusHub->IsCurrentFocus());
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());
    EXPECT_TRUE(sheetPattern->IsSheetBottomStyle());
    sheetPattern->AvoidKeyboardBySheetMode();
    EXPECT_TRUE(sheetPattern->isAnimationProcess_);
    EXPECT_FALSE(sheetPattern->isAnimationBreak_);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsNeedPlayTransition001
 * @tc.desc: Test update detents of sheetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition001, TestSize.Level1)
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
     * @tc.steps: step3. excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

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
     * @tc.steps: step5. excute the IsNeedPlayTransition function.
     * @tc.expected: true
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetHeight.sheetMode = SheetMode::LARGE;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_TRUE(sheetPattern->GetIsPlayTransition());
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsNeedPlayTransition002
 * @tc.desc: Test update sheetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.sheetHeight.height = Dimension(100.0f, DimensionUnit::AUTO);
    style.sheetHeight.sheetMode = SheetMode::MEDIUM;
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
     * @tc.steps: step3. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: true
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetHeight.height = Dimension(200.0f, DimensionUnit::AUTO);
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_TRUE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step4. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: true
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetHeight.sheetMode = SheetMode::LARGE;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_TRUE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step5. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.showDragBar = true;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step6. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.showCloseIcon = true;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step7. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.isTitleBuilder = true;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step8. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.backgroundColor = Color::BLACK;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step9. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.maskColor = Color::BLACK;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step10. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.bottomOffset = OffsetF(200.0, 200.0);
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsNeedPlayTransition003
 * @tc.desc: Test update sheetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition003, TestSize.Level1)
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
     * @tc.steps: step3. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    styleOption.blurStyle = BlurStyle::THICK;
    style.backgroundBlurStyle = styleOption;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step4. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetTitle = "title2";
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step5. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.sheetSubtitle = "subtile2";
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step6. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.scrollSizeMode = ScrollSizeMode::CONTINUOUS;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step7. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    BorderWidth.SetBorderWidth(Dimension(20.0));
    style.borderWidth = BorderWidth;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step8. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.borderColor = { Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK };
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step9. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.borderStyle = { BorderStyle::DASHED, BorderStyle::DASHED, BorderStyle::DASHED, BorderStyle::DASHED };
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step10. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    shadow = ShadowConfig::NoneShadow;
    style.shadow = shadow;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());

    /**
     * @tc.steps: step11. change style and excute the IsNeedPlayTransition function.
     * @tc.expected: false
     */
    layoutProperty->UpdateSheetStyle(style);
    style.width = Dimension(200.0f, DimensionUnit::AUTO);
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsNeedPlayTransition004
 * @tc.desc: Branch: if (!inputStyle.detentSelection.has_value() || inputStyle.detents.size() == 0).
 *           Condition: !inputStyle.detentSelection.has_value().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition004, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    style.detents.emplace_back(detent);
    SheetHeight detent1;
    detent1.height->unit_ = DimensionUnit::VP;
    detent1.height->value_ = 100;
    style.detents.emplace_back(detent1);
    layoutProperty->UpdateSheetStyle(style);
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());
    EXPECT_EQ(sheetPattern->GetDetentsFinalIndex(), 0);
}

/**
 * @tc.name: IsNeedPlayTransition005
 * @tc.desc: Branch: if (!inputStyle.detentSelection.has_value() || inputStyle.detents.size() == 0).
 *           Condition: inputStyle.detents.size() == 0.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition005, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateSheetStyle(style);
    SheetHeight sheetHeight;
    sheetHeight.sheetMode = SheetMode::MEDIUM;
    style.detentSelection = sheetHeight;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());
    EXPECT_EQ(sheetPattern->GetDetentsFinalIndex(), 0);
}

/**
 * @tc.name: IsNeedPlayTransition006
 * @tc.desc: Branch: if ((selection.sheetMode.has_value() && selection.sheetMode.value() == NG::SheetMode::AUTO)).
 *           Condition: (selection.sheetMode.has_value() && selection.sheetMode.value() == NG::SheetMode::AUTO).
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition006, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetHeight sheetHeight;
    sheetHeight.sheetMode = SheetMode::AUTO;
    style.detents.emplace_back(sheetHeight);
    layoutProperty->UpdateSheetStyle(style);
    style.detentSelection = sheetHeight;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());
    EXPECT_EQ(sheetPattern->GetDetentsFinalIndex(), 0);
}

/**
 * @tc.name: IsNeedPlayTransition007
 * @tc.desc: Branch: if (inputStyle.detents[index] == inputStyle.detentSelection.value()).
 *           Condition 1: inputStyle.detents[index] == inputStyle.detentSelection.value().
 *                     2: inputStyle.detents[index] != inputStyle.detentSelection.value().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition007, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    style.detents.emplace_back(detent);
    SheetHeight detent1;
    detent1.height->unit_ = DimensionUnit::VP;
    detent1.height->value_ = 100;
    style.detents.emplace_back(detent1);
    layoutProperty->UpdateSheetStyle(style);
    style.detentSelection = detent1;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_TRUE(sheetPattern->GetIsPlayTransition());
    EXPECT_EQ(sheetPattern->GetDetentsFinalIndex(), 1);

    layoutProperty->UpdateSheetStyle(style);
    SheetHeight selection1;
    selection1.sheetMode = SheetMode::LARGE;
    style.detentSelection = selection1;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());
    EXPECT_EQ(sheetPattern->GetDetentsFinalIndex(), 1);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: IsNeedPlayTransition008
 * @tc.desc: Branch: if (!isFirstTransition && preStyle.detentSelection == inputStyle.detentSelection).
 *           Condition: preStyle.detentSelection == inputStyle.detentSelection.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, IsNeedPlayTransition008, TestSize.Level1)
{
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SheetHeight height1;
    height1.sheetMode = SheetMode::AUTO;
    SheetHeight height2;
    height2.height->unit_ = DimensionUnit::VP;
    height2.height->value_ = 100;
    style.detents.emplace_back(height1);
    style.detents.emplace_back(height2);
    layoutProperty->UpdateSheetStyle(style);
    style.detentSelection = height2;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_TRUE(sheetPattern->GetIsPlayTransition());
    EXPECT_EQ(sheetPattern->GetDetentsFinalIndex(), 1);

    layoutProperty->UpdateSheetStyle(style);
    style.detentSelection = height2;
    style.showDragBar = true;
    sheetPattern->IsNeedPlayTransition(style);
    EXPECT_FALSE(sheetPattern->GetIsPlayTransition());
    EXPECT_EQ(sheetPattern->GetDetentsFinalIndex(), 1);
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
    sheetStyle.sheetHeight.height = Dimension(100.0f, DimensionUnit::AUTO);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->overlayManager_ = overlayManager;
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    EXPECT_EQ(sheetNode->GetTag(), V2::SHEET_PAGE_TAG);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();

    /**
     * @tc.steps: step4. same height to excute FireOnHeightDidChange.
     * @tc.expected: preDidHeight_ is -8.
     */

    sheetPattern->FireOnHeightDidChange();
    EXPECT_EQ(sheetPattern->preDidHeight_, -8);

    /**
     * @tc.steps: step5. new height to excute FireOnHeightDidChange.
     * @tc.expected: preDidHeight_ is -8.
     */
    sheetPattern->FireOnHeightDidChange();
    EXPECT_EQ(sheetPattern->preDidHeight_, -8);
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
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
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
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    /**
     * @tc.steps: step4. set up sheet theme.
     * @tc.expected: SHEET_BOTTOM_OFFSET can obtain render properties.
     */
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = true;
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    sheetTheme->sheetOuterBorderWidth_ = Dimension(20.0);
    sheetTheme->sheetInnerBorderWidth_ = Dimension(10.0);
    sheetTheme->sheetRadius_ = Dimension(10.0);
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    sheetPattern->SetSheetOuterBorderWidth(sheetTheme, sheetStyle);
    auto renderContext = sheetNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetOuterBorderWidth().has_value(), true);
    EXPECT_EQ(renderContext->GetBorderWidth().has_value(), true);
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
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
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
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());

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
    SystemProperties::SetDeviceType(DeviceType::PHONE);

    /**
     * @tc.expected: isKeyBoardShow_ and isHoverMode_ are true.
     */
    sheetLayoutAlgorithm->InitParameter(Referenced::RawPtr(layoutWrapper));
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
    SystemProperties::SetDeviceType(DeviceType::PHONE);

    /**
     * @tc.expected: isHoverMode_ is false and hoverModeArea_ is BOTTOM_SCREEN.
     */
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->InitParameter(Referenced::RawPtr(layoutWrapper));
    EXPECT_FALSE(sheetLayoutAlgorithm->isHoverMode_);
    EXPECT_EQ(sheetLayoutAlgorithm->hoverModeArea_, HoverModeAreaType::BOTTOM_SCREEN);
}

/**
 * @tc.name: UpdateBackBlurStyle001
 * @tc.desc: Test SheetPresentationPattern::OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, UpdateBackBlurStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and set API12.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheet renderContext.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step3. set sheetBackgroundBlurStyle_ of sheetTheme to THIN.
     * @tc.expected: the sheet renderContext backgroundColor is TRANSPARENT
     * @tc.expected: the sheet renderContext blurStyle is THIN
     */
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBackgroundBlurStyle_ = 1;
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    auto backgroundColor = renderContext->GetBackgroundColorValue();
    auto styleOption = renderContext->GetBackBlurStyle();
    EXPECT_EQ(backgroundColor, Color::TRANSPARENT);
    EXPECT_EQ(styleOption->blurStyle, BlurStyle::THIN);

    /**
     * @tc.steps: step4. set sheetBackgroundBlurStyle_ of sheetTheme to THIN.
     * @tc.expected: the sheet renderContext backgroundColor is TRANSPARENT
     * @tc.expected: the sheet renderContext blurStyle is REGULAR
     */
    sheetTheme->sheetBackgroundBlurStyle_ = 2;
    sheetStyle.backgroundColor = Color::BLUE;
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    backgroundColor = renderContext->GetBackgroundColorValue();
    styleOption = renderContext->GetBackBlurStyle();
    EXPECT_EQ(backgroundColor, Color::TRANSPARENT);
    EXPECT_EQ(styleOption->blurStyle, BlurStyle::REGULAR);

    /**
     * @tc.steps: step5. set sheetBackgroundBlurStyle_ of sheetTheme to THIN.
     * @tc.expected: the sheet renderContext backgroundColor is BLUE
     * @tc.expected: the sheet renderContext blurStyle is NO_MATERIAL
     */
    sheetTheme->sheetBackgroundBlurStyle_ = 0;
    BlurStyleOption styleOption_;
    styleOption_.blurStyle = BlurStyle::NO_MATERIAL;
    sheetStyle.backgroundBlurStyle = styleOption_;
    sheetStyle.backgroundColor = Color::BLUE;
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    sheetNode = overlayManager->modalStack_.top().Upgrade();
    renderContext = sheetNode->GetRenderContext();
    backgroundColor = renderContext->GetBackgroundColorValue();
    styleOption = renderContext->GetBackBlurStyle();
    EXPECT_EQ(backgroundColor, Color::BLUE);
    EXPECT_EQ(styleOption->blurStyle, BlurStyle::NO_MATERIAL);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test SheetPresentationLayoutAlgorithm::Layout.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, Layout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetTitle = "Title";
    style.sheetSubtitle = "Subtitle";
    style.sheetType = SheetType::SHEET_CENTER;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step2. create sheetNode, get sheet LayoutAlgorithm.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetNode->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sheetLayoutAlgorithm);

    /**
     * @tc.steps: step3. set sheetType_ and width.
     * @tc.expected: the sheet sheetOffsetX_ is 250
     */
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    sheetLayoutAlgorithm->sheetMaxWidth_ = 1000.0f;
    sheetLayoutAlgorithm->sheetWidth_ = 500.0f;
    sheetNode->Layout();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 250);

    /**
     * @tc.steps: step4. set sheetType_ and width.
     * @tc.expected: the sheet sheetOffsetX_ is 150
     */
    sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetNode->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sheetLayoutAlgorithm);
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetLayoutAlgorithm->sheetMaxWidth_ = 800.0f;
    sheetLayoutAlgorithm->sheetWidth_ = 500.0f;
    sheetNode->Layout();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 150);

    /**
     * @tc.steps: step5. set sheetType_ and width.
     * @tc.expected: the sheet sheetOffsetX_ is 0
     */
    sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetNode->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sheetLayoutAlgorithm);
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_POPUP;
    sheetNode->Layout();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 0);

    /**
     * @tc.steps: step6. set sheetType_ and width and height.
     * @tc.expected: the sheet sheetOffsetX_ is 300
     * @tc.expected: the sheet sheetOffsetY_ is 500
     */
    sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetNode->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sheetLayoutAlgorithm);
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_BOTTOM_OFFSET;
    sheetLayoutAlgorithm->sheetMaxWidth_ = 800.0f;
    sheetLayoutAlgorithm->sheetWidth_ = 400.0f;
    sheetLayoutAlgorithm->sheetMaxHeight_ = 1000.0f;
    sheetLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetLayoutAlgorithm->sheetStyle_.bottomOffset->SetX(100.0f);
    sheetLayoutAlgorithm->sheetStyle_.bottomOffset->SetY(100.0f);
    sheetNode->Layout();
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 300);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, 500);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: CalculateSheetOffsetInOtherScenes001
 * @tc.desc: Test CalculateSheetOffsetInOtherScenes function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, CalculateSheetOffsetInOtherScenes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.isTitleBuilder = true;
    style.sheetTitle = "MESSAGE";
    style.sheetSubtitle = "MESSAGE";
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: step2. set some parameters of sheetLayoutAlgorithm.
     */
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0, 500.0));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetLayoutAlgorithm->isHoverMode_ = true;
    std::vector<Rect> currentFoldCreaseRegion;
    Rect rect;
    rect.SetRect(0, 1000, 2000, 3000);
    currentFoldCreaseRegion.insert(currentFoldCreaseRegion.end(), rect);
    sheetPattern->currentFoldCreaseRegion_ = currentFoldCreaseRegion;
    sheetLayoutAlgorithm->isKeyBoardShow_ = true;
    sheetLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;

    /**
     * @tc.steps: step3. excute CalculateSheetOffsetInOtherScenes function.
     * @tc.expected: The first result of the trinocular operator
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->CalculateSheetOffsetInOtherScenes(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_,
        SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx() + (1000 - SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx() - 500) / 2);

    /**
     * @tc.steps: step4. set some parameters of sheetLayoutAlgorithm.
     */
    sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    auto geometryNode_new = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode_new, nullptr);
    geometryNode_new->SetFrameSize(SizeF(100.0, 600.0));
    sheetLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetLayoutAlgorithm->isHoverMode_ = true;
    currentFoldCreaseRegion.clear();
    rect.SetRect(0, 1500, 2000, 3000);
    currentFoldCreaseRegion.insert(currentFoldCreaseRegion.end(), rect);
    sheetPattern->currentFoldCreaseRegion_ = currentFoldCreaseRegion;
    sheetLayoutAlgorithm->isKeyBoardShow_ = false;
    sheetLayoutAlgorithm->hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    sheetLayoutAlgorithm->sheetMaxHeight_ = 2000.0f;

    /**
     * @tc.steps: step5. excute CalculateSheetOffsetInOtherScenes function.
     * @tc.expected: The second result of the trinocular operator
     */
    layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->CalculateSheetOffsetInOtherScenes(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_,
        4500 + (2000 - SHEET_HOVERMODE_DOWN_HEIGHT.ConvertToPx() - 4500 - 600) / 2);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetOffset001
 * @tc.desc: Test OverlayManager::ComputeSheetOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, ComputeSheetOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetNode.
     * @tc.expected: sheetNode is not nullptr.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step3. get sheetPattern.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step8. set SheetType to SHEET_BOTTOMLANDSPACE.
     * @tc.expected: SheetType is SHEET_BOTTOMLANDSPACE and pageHeight_ is 1000 and frameSize height is 500.
     */
    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_CENTER);
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->pageHeight_ = 1000.0f;
    auto sheetSize = SizeF({ 500, 500 });
    sheetNode->GetGeometryNode()->SetFrameSize(sheetSize);

    /**
     * @tc.steps: step9. excute ComputeSheetOffset function.
     * @tc.expected: sheetHeight_ is ((pageHeight_ + sheetSize.height) / 2).
     */
    overlayManager->ComputeSheetOffset(sheetStyle, sheetNode);
    EXPECT_EQ(overlayManager->sheetHeight_, 750);

    /**
     * @tc.steps: step10. set SheetType to SHEET_BOTTOMLANDSPACE.
     * @tc.expected: SheetType is SHEET_BOTTOMLANDSPACE.
     */
    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    sheetPattern->sheetType_ = SheetType::SHEET_POPUP;
    sheetPattern->pageHeight_ = 1200.0f;
    /**
     * @tc.steps: step11. excute ComputeSheetOffset function.
     * @tc.expected: sheetHeight_ is pageHeight_.
     */
    overlayManager->ComputeSheetOffset(sheetStyle, sheetNode);
    EXPECT_EQ(overlayManager->sheetHeight_, 1200);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeSheetOffset002
 * @tc.desc: Test OverlayManager::ComputeSheetOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, ComputeSheetOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, get sheetNode.
     * @tc.expected: sheetNode is not nullptr.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    CreateSheetBuilder();
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step3. get sheetPattern.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);

    /**
     * @tc.steps: step5. set SheetType to SHEET_BOTTOMLANDSPACE.
     * @tc.expected: SheetType is SHEET_BOTTOMLANDSPACE and pageHeight_ is 800.
     */
    SheetPresentationTestTwoNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOMLANDSPACE);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOMLANDSPACE);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: ComputeDetentsSheetOffset001
 * @tc.desc: Test OverlayManager::ComputeDetentsSheetOffset.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, ComputeDetentsSheetOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();

    /**
     * @tc.steps: step2. create sheetNode, set builder height is 500, get sheetNode.
     * @tc.expected: sheetNode is not nullptr.
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    auto builderFunc = []() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
        frameNode->AddChild(childFrameNode);
        auto size = SizeF({ 500, 500 });
        frameNode->GetGeometryNode()->SetFrameSize(size);
        return frameNode;
    };
    auto buildTitleNodeFunc = []() -> RefPtr<UINode> { return nullptr; };
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc), std::move(buildTitleNodeFunc), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    auto sheetNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetNode, nullptr);

    /**
     * @tc.steps: step3. get sheetPattern and layoutProperty.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step4. set API10.
     */
    int originApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);

    /**
     * @tc.steps: step5. set detent.sheetMode is MEDIUM and pageHeight_ is 800.
     */
    SheetHeight detent;
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    sheetPattern->pageHeight_ = 800.0f;

    /**
     * @tc.steps: step6. excute ComputeDetentsSheetOffset function.
     * @tc.expected: sheetHeight_ is (pageHeight_ * MEDIUM_SIZE_PRE)
     */
    layoutProperty->UpdateSheetStyle(sheetStyle);
    overlayManager->ComputeDetentsSheetOffset(sheetStyle, sheetNode);
    EXPECT_EQ(overlayManager->sheetHeight_, 800 * MEDIUM_SIZE_PRE);

    /**
     * @tc.steps: step7. set API12.
     */
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);

    /**
     * @tc.steps: step8. set detent.sheetMode is AUTO and pageHeight_ is 1000.
     * @tc.expected: sheetHeight_ is builder height because fit_content
     */
    detent.sheetMode = SheetMode::AUTO;
    sheetStyle.detents.clear();
    sheetStyle.detents.emplace_back(detent);
    sheetPattern->pageHeight_ = 1000.0f;
    overlayManager->sheetHeight_ = 0.0f;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    overlayManager->ComputeDetentsSheetOffset(sheetStyle, sheetNode);
    EXPECT_EQ(overlayManager->sheetHeight_, 500);

    /**
     * @tc.steps: step9. set detent.sheetMode is AUTO and pageHeight_ is 500.
     * @tc.expected: sheetHeight_ is (pageHeight_ - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() -
     * sheetPattern->GetSheetTopSafeArea())
     */
    detent.sheetMode = SheetMode::AUTO;
    sheetStyle.detents.clear();
    sheetStyle.detents.emplace_back(detent);
    sheetPattern->pageHeight_ = 500.0f;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    overlayManager->ComputeDetentsSheetOffset(sheetStyle, sheetNode);
    EXPECT_EQ(overlayManager->sheetHeight_,
        500 - SHEET_BLANK_MINI_HEIGHT.ConvertToPx() - sheetPattern->GetSheetTopSafeArea());
    SheetPresentationTestTwoNg::TearDownTestCase();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(originApiVersion);
}

/**
 * @tc.name: SheetHoverStatus004
 * @tc.desc: Test Measure function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetHoverStatus004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    style.enableHoverMode = true;
    style.hoverModeArea = HoverModeAreaType::TOP_SCREEN;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    ASSERT_NE(sheetWrapperNode, nullptr);
    sheetNode->MountToParent(sheetWrapperNode);
    /**
     * @tc.steps: step2. create sheet property and style.
     * @tc.expected: layoutProperty and LayoutAlgorithm are not nullptr.
     */
    auto dirty = sheetNode->CreateLayoutWrapper();
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetLayoutAlgorithm->isKeyBoardShow_ = true;
    sheetLayoutAlgorithm->sheetMaxHeight_ = 2420;
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propSheetStyle_ = style;

    /**
     * @tc.steps: step3. set layout constraint.
     */
    sheetNode->Measure(sheetNode->GetLayoutConstraint());
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSafeAreaManager();
    manager->keyboardInset_ = KEYBOARD_INSET;
    pipeline->isHalfFoldHoverStatus_ = true;
    sheetLayoutAlgorithm->sheetStyle_ = style;

    /**
     * @tc.steps: step4. set sheetType and run measure task.
     * @tc.expected: sheetHeight_ has been measured and is not zero.
     */
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetNode, sheetNode->GetGeometryNode(), sheetNode->GetLayoutProperty());
    sheetLayoutAlgorithm->InitParameter(Referenced::RawPtr(layoutWrapper));
    EXPECT_TRUE(sheetLayoutAlgorithm->isHoverMode_);
    std::vector<Rect> rects;
    Rect rect(0, 1064, 2294, 171);
    rects.insert(rects.end(), rect);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->currentFoldCreaseRegion_ = rects;
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800, 1800));
    sheetLayoutAlgorithm->sheetType_ = SHEET_CENTER;
    sheetLayoutAlgorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetHeight_, 560);
}

/**
 * @tc.name: SheetHoverStatus005
 * @tc.desc: Test Layout function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetHoverStatus005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set up bind sheet and theme
     */
    SetOnBindSheet();
    SheetPresentationTestTwoNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto dirty = sheetNode->CreateLayoutWrapper();
    ASSERT_NE(dirty, nullptr);
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);

    /**
     * @tc.steps: step2. set up layoutAlgorithm states
     */
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetLayoutAlgorithm->sheetType_ = SHEET_CENTER;
    sheetLayoutAlgorithm->isHoverMode_ = true;
    sheetLayoutAlgorithm->isKeyBoardShow_ = true;
    sheetLayoutAlgorithm->sheetMaxHeight_ = 2420;
    sheetLayoutAlgorithm->sheetMaxWidth_ = 2420;
    sheetLayoutAlgorithm->sheetWidth_ = 1420;
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateSheetStyle(sheetLayoutAlgorithm->sheetStyle_);

    /**
     * @tc.steps: step3. run layout task.
     * @tc.expected: sheetOffsetY_ has been layout and offset is not zero.
     */
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(0, 1064, 2294, 171);
    rects.insert(rects.end(), rect);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->currentFoldCreaseRegion_ = rects;
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(800, 1800));
    sheetLayoutAlgorithm->Layout(AceType::RawPtr(sheetNode));
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetY_, -348);
    EXPECT_EQ(sheetLayoutAlgorithm->sheetOffsetX_, 500);
}

/**
 * @tc.name: SheetHoverStatus006
 * @tc.desc: Test OnDirtyLayoutWrapperSwap and AvoidSafeArea function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetHoverStatus006, TestSize.Level1)
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
     * @tc.steps: step2. create sheet builder and set sheet theme.
     */
    SheetStyle sheetStyle;
    sheetStyle.enableHoverMode = true;
    sheetStyle.hoverModeArea = HoverModeAreaType::TOP_SCREEN;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->UpdateSheetType();
    sheetPattern->InitSheetObject();
    ASSERT_NE(sheetPattern->GetSheetObject(), nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = false;
    sheetPattern->sheetThemeType_ = "popup";
    Rect windowRect = { 0.0f, 0.0f, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx(), 0.0f };
    MockPipelineContext::SetCurrentWindowRect(windowRect);
    sheetPattern->sheetKey_.hasValidTargetNode = true;
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetTheme->sheetType_ = "popup";
    /**
     * @tc.steps: step3. Set sheet type and run IsCurSheetNeedHalfFoldHover.
     * @tc.expected: sheet is in half fold status.
     */
    pipeline->isHalfFoldHoverStatus_ = true;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propSheetStyle_ = sheetStyle;
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    EXPECT_TRUE(sheetPattern->IsCurSheetNeedHalfFoldHover());

    /**
     * @tc.steps: step4. run OnDirtyLayoutWrapperSwap.
     * @tc.expected: sheet do not need avoid keybord.
     */
    auto dirty = sheetNode->CreateLayoutWrapper();
    DirtySwapConfig config;
    config.skipMeasure = false;
    sheetPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    EXPECT_EQ(sheetPattern->sheetHeightUp_, 0.0f);
}

/**
 * @tc.name: SheetHoverStatus007
 * @tc.desc: Test GetSheetHeightBeforeDragUpdate and GetMaxSheetHeightBeforeDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, SheetHoverStatus007, TestSize.Level1)
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
     * @tc.steps: step2. create sheet style.
     */
    SheetStyle sheetStyle;
    sheetStyle.enableHoverMode = true;
    sheetStyle.hoverModeArea = HoverModeAreaType::TOP_SCREEN;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    CreateSheetBuilder();
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetPresentationTestTwoNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step3. set sheet theme.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(
        "Sheet", 101, AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->isOuterBorderEnable_ = false;
    sheetPattern->sheetThemeType_ = "popup";
    Rect windowRect = { 0.0f, 0.0f, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx(), 0.0f };
    MockPipelineContext::SetCurrentWindowRect(windowRect);
    sheetPattern->sheetKey_.hasValidTargetNode = true;
    sheetTheme->sheetType_ = "popup";
    /**
     * @tc.steps: step4. Set sheet type and run IsCurSheetNeedHalfFoldHover.
     * @tc.expected: sheet is in half fold status.
     */
    CHECK_NULL_VOID(pipeline);
    pipeline->isHalfFoldHoverStatus_ = true;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    SheetPresentationTestTwoNg::SetSheetTheme(sheetTheme);
    EXPECT_TRUE(sheetPattern->IsCurSheetNeedHalfFoldHover());

    /**
     * @tc.steps: step5. Compute sheetHeight and max sheetHeight before drag.
     * @tc.expected: sheetHeight can be computed correctly.
     */
    sheetPattern->pageHeight_ = 2040;
    sheetPattern->sheetOffsetY_ = 1000;
    auto sheetHeight = sheetPattern->GetSheetHeightBeforeDragUpdate();
    auto sheetMaxHeight = sheetPattern->GetMaxSheetHeightBeforeDragUpdate();
    EXPECT_EQ(sheetHeight, 1040);
    EXPECT_EQ(sheetMaxHeight, 1040);
}

/**
 * @tc.name: CreateScrollNode001
 * @tc.desc: Branch: if (sheetStyle.sheetEffectEdge.has_value()
 *                      && sheetStyle.sheetEffectEdge.value() == NG::SheetEffectEdge::NONE).
 *           Condition: 1.sheetStyle.sheetEffectEdge.has_value(),
 *                      2.sheetStyle.sheetEffectEdge.value() = NG::SheetEffectEdge::NONE.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, CreateScrollNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scroll node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetStyle style;
    style.sheetEffectEdge = NG::SheetEffectEdge::NONE;
    auto scrollNode = SheetView::CreateScrollNode(style);
    ASSERT_NE(scrollNode, nullptr);
    
    /**
     * @tc.steps: step2. create scroll pattern, test target branch.
     * @tc.expected: scrollPattern->GetEffectEdge() == EffectEdge::NONE.
     */
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    EXPECT_EQ(scrollPattern->GetEdgeEffect(), EdgeEffect::NONE);
    EXPECT_FALSE(scrollPattern->GetAlwaysEnabled());
    EXPECT_EQ(scrollPattern->GetEdgeEffect(), EdgeEffect::NONE);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: CreateScrollNode002
 * @tc.desc: Branch: if (sheetStyle.sheetEffectEdge.has_value()
 *                      && sheetStyle.sheetEffectEdge.value() == NG::SheetEffectEdge::NONE).
 *           Condition: !sheetStyle.sheetEffectEdge.has_value().
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, CreateScrollNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scroll node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetStyle style;
    auto scrollNode = SheetView::CreateScrollNode(style);
    ASSERT_NE(scrollNode, nullptr);
    
    /**
     * @tc.steps: step2. create scroll pattern, test target branch.
     * @tc.expected: scrollPattern->GetEffectEdge() == EffectEdge::NONE.
     */
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    EXPECT_EQ(scrollPattern->GetEdgeEffect(), EdgeEffect::SPRING);
    EXPECT_FALSE(scrollPattern->GetAlwaysEnabled());
    EXPECT_EQ(scrollPattern->GetEffectEdge(), EffectEdge::ALL);
    SheetPresentationTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: CreateScrollNode003
 * @tc.desc: Branch: if (sheetStyle.sheetEffectEdge.has_value()
 *                      && sheetStyle.sheetEffectEdge.value() == NG::SheetEffectEdge::NONE).
 *           Condition: 1.sheetStyle.sheetEffectEdge.has_value(),
 *                      2.sheetStyle.sheetEffectEdge.value() = NG::SheetEffectEdge::START.
 * @tc.type: FUNC
 */
HWTEST_F(SheetPresentationTestTwoNg, CreateScrollNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create scroll node.
     */
    SheetPresentationTestTwoNg::SetUpTestCase();
    SheetStyle style;
    style.sheetEffectEdge = NG::SheetEffectEdge::START;
    auto scrollNode = SheetView::CreateScrollNode(style);
    ASSERT_NE(scrollNode, nullptr);
    
    /**
     * @tc.steps: step2. create scroll pattern, test target branch.
     * @tc.expected: scrollPattern->GetEffectEdge() == EffectEdge::START.
     */
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    EXPECT_EQ(scrollPattern->GetEdgeEffect(), EdgeEffect::SPRING);
    EXPECT_FALSE(scrollPattern->GetAlwaysEnabled());
    EXPECT_EQ(scrollPattern->GetEffectEdge(), EffectEdge::START);
    SheetPresentationTestTwoNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG