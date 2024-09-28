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

#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

class SheetPresentationTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
    static void TearDownTestCase();
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
} // namespace OHOS::Ace::NG