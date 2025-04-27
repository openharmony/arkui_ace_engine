/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
} // namespace

class TitleBarPatternTestNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void MockPipelineContextGetTheme();
    static RefPtr<FrameNode> CreateDialogNode();
};

RefPtr<NavigationBarTheme> TitleBarPatternTestNg::navigationBarTheme_ = nullptr;

void TitleBarPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == AgingAdapationDialogTheme::TypeId()) {
            return AceType::MakeRefPtr<AgingAdapationDialogTheme>();
        } else if (type == NavigationBarTheme::TypeId()) {
            return navigationBarTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TitleBarPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> TitleBarPatternTestNg::CreateDialogNode()
{
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    DialogProperties dialogProperties {
        .title = "Title",
        .content = "Content",
        .width = 300,
        .height = 200,
    };
    return DialogView::CreateDialogNode(dialogProperties, contentNode);
}

void TitleBarPatternTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<ButtonTheme>()));
}

/**
 * @tc.name: UpdateTitleModeChange001
 * @tc.desc: Branch: if ((GetTitleModeValue == FREE) && !NearZero(maxTitleBarHeight_)) = false
 *           Condition: GetTitleModeValue == FREE = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    titleBarPattern->titleMode_ = NavigationTitleMode::FREE;

    titleBarPattern->UpdateTitleModeChange();
    EXPECT_EQ(titleBarPattern->titleMode_, NavigationTitleMode::FREE);
}

/**
 * @tc.name: UpdateTitleModeChange002
 * @tc.desc: Branch: if ((GetTitleModeValue == FREE) && !NearZero(maxTitleBarHeight_)) = false
 *           Condition: GetTitleModeValue == FREE = true, !NearZero(maxTitleBarHeight_) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->maxTitleBarHeight_ = 0.0f;
    titleBarPattern->titleMode_ = NavigationTitleMode::FREE;

    titleBarPattern->UpdateTitleModeChange();
    EXPECT_EQ(titleBarPattern->titleMode_, NavigationTitleMode::FREE);
}

/**
 * @tc.name: UpdateTitleModeChange003
 * @tc.desc: Branch: if ((GetTitleModeValue == FREE) && !NearZero(maxTitleBarHeight_)) = true
 *           Condition: GetTitleModeValue == FREE = true, !NearZero(maxTitleBarHeight_) = true
 *           Branch: if (titleBarHeight >= maxTitleBarHeight_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->maxTitleBarHeight_ = 10.0f;
    auto geometryNode = titleBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF frameSize(10.0f, titleBarPattern->maxTitleBarHeight_ + 10.0f);
    geometryNode->SetFrameSize(frameSize);
    titleBarPattern->titleMode_ = NavigationTitleMode::FREE;

    titleBarPattern->UpdateTitleModeChange();
    EXPECT_EQ(titleBarPattern->titleMode_, NavigationTitleMode::FULL);
}

/**
 * @tc.name: UpdateTitleModeChange004
 * @tc.desc: Branch: if ((GetTitleModeValue == FREE) && !NearZero(maxTitleBarHeight_)) = true
 *           Condition: GetTitleModeValue == FREE = true, !NearZero(maxTitleBarHeight_) = true
 *           Branch: if (titleBarHeight >= maxTitleBarHeight_) = false
 *           Branch: if (NearEqual(titleBarHeight, TITLEBAR_HEIGHT_MINI)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->maxTitleBarHeight_ = static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx()) + 10.0f;
    auto geometryNode = titleBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF frameSize(10.0f, titleBarPattern->maxTitleBarHeight_ - 10.0f);
    geometryNode->SetFrameSize(frameSize);
    titleBarPattern->titleMode_ = NavigationTitleMode::FREE;

    titleBarPattern->UpdateTitleModeChange();
    EXPECT_EQ(titleBarPattern->titleMode_, NavigationTitleMode::MINI);
}

/**
 * @tc.name: UpdateTitleModeChange005
 * @tc.desc: Branch: if ((GetTitleModeValue == FREE) && !NearZero(maxTitleBarHeight_)) = true
 *           Condition: GetTitleModeValue == FREE = true, !NearZero(maxTitleBarHeight_) = true
 *           Branch: if (titleBarHeight >= maxTitleBarHeight_) = false
 *           Branch: if (NearEqual(titleBarHeight, TITLEBAR_HEIGHT_MINI)) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange005, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->maxTitleBarHeight_ = static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx()) + 20.0f;
    auto geometryNode = titleBarNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF frameSize(10.0f, titleBarPattern->maxTitleBarHeight_ - 10.0f);
    geometryNode->SetFrameSize(frameSize);
    titleBarPattern->titleMode_ = NavigationTitleMode::FREE;

    titleBarPattern->UpdateTitleModeChange();
    EXPECT_EQ(titleBarPattern->titleMode_, NavigationTitleMode::FREE);
}

/**
 * @tc.name: UpdateTitleBarByCoordScroll001
 * @tc.desc: Branch: if (GetTitleModeValue != FREE) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleBarByCoordScroll001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->SetTempTitleBarHeightVp(1.0f);
    titleBarPattern->overDragOffset_ = 10.0f;
    titleBarPattern->maxTitleBarHeight_ = 100.0f;

    float tempTitleBarHeight = titleBarPattern->maxTitleBarHeight_ + titleBarPattern->overDragOffset_ / 6.0f;
    titleBarPattern->UpdateTitleBarByCoordScroll(0.0f);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(), tempTitleBarHeight);
}

/**
 * @tc.name: UpdateTitleBarByCoordScroll002
 * @tc.desc: Branch: if (GetTitleModeValue != FREE) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleBarByCoordScroll002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    titleBarPattern->SetTempTitleBarHeightVp(1.0f);
    titleBarPattern->overDragOffset_ = 10.0f;
    titleBarPattern->maxTitleBarHeight_ = 100.0f;

    titleBarPattern->UpdateTitleBarByCoordScroll(0.0f);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(), 1.0f);
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: Branch: if (mainTitle) = false
 *           Branch: if (subTitle) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    DumpLog::GetInstance().description_.clear();

    titleBarPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.size(), 0);
}

/**
 * @tc.name: DumpInfo002
 * @tc.desc: Branch: if (mainTitle) = true
 *           Branch: if (property) = false
 *           Branch: if (subTitle) = true
 *           Branch: if (property) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto mainTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(mainTitleNode);
    mainTitleNode->layoutProperty_ = nullptr;
    auto subTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetSubtitle(subTitleNode);
    subTitleNode->layoutProperty_ = nullptr;
    DumpLog::GetInstance().description_.clear();

    titleBarPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.size(), 0);
}

/**
 * @tc.name: DumpInfo003
 * @tc.desc: Branch: if (mainTitle) = true
 *           Branch: if (property) = true
 *           Branch: if (subTitle) = true
 *           Branch: if (property) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto mainTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(mainTitleNode);
    auto subTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetSubtitle(subTitleNode);
    DumpLog::GetInstance().description_.clear();

    EXPECT_NE(titleBarNode->GetTitle(), nullptr);
    auto mainTitleProperty = mainTitleNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(mainTitleProperty, nullptr);
    titleBarPattern->DumpInfo();
    ASSERT_EQ(DumpLog::GetInstance().description_.size(), 2);
    EXPECT_EQ(DumpLog::GetInstance().description_[0].substr(0, 9), "MainTitle");
    EXPECT_EQ(DumpLog::GetInstance().description_[1].substr(0, 8), "SubTitle");
}

/**
 * @tc.name: GetTitleBarHeightLessThanMaxBarHeight001
 * @tc.desc: Branch: if (titleMode != NavigationTitleMode::FREE) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetTitleBarHeightLessThanMaxBarHeight001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;

    float ret = titleBarPattern->GetTitleBarHeightLessThanMaxBarHeight();
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: GetTitleBarHeightLessThanMaxBarHeight002
 * @tc.desc: Branch: if (titleMode != NavigationTitleMode::FREE) = false
 *           Branch: if (barStyle != BarStyle::STACK) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetTitleBarHeightLessThanMaxBarHeight002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->options_.brOptions.barStyle = BarStyle::STANDARD;

    float ret = titleBarPattern->GetTitleBarHeightLessThanMaxBarHeight();
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: GetTitleBarHeightLessThanMaxBarHeight003
 * @tc.desc: Branch: if (titleMode != NavigationTitleMode::FREE) = false
 *           Branch: if (barStyle != BarStyle::STACK) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetTitleBarHeightLessThanMaxBarHeight003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->options_.brOptions.barStyle = BarStyle::STACK;
    titleBarPattern->maxTitleBarHeight_ = 100.0f;
    titleBarPattern->currentTitleBarHeight_ = 50.0f;

    float ret = titleBarPattern->GetTitleBarHeightLessThanMaxBarHeight();
    EXPECT_EQ(ret, 50.0f);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: Branch: if (dialogNode_ != nullptr) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, HandleLongPress001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarPattern->dialogNode_ = TitleBarPatternTestNg::CreateDialogNode();

    titleBarPattern->HandleLongPress(backButtonNode);
    EXPECT_EQ(titleBarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: Branch: if (dialogNode_ != nullptr) = false
 *           Branch: if (backButtonIconNode->GetTag() == V2::SYMBOL_ETS_TAG) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, HandleLongPress002, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = nullptr;
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    textLayoutProperty->propSymbolSourceInfo_ = SymbolSourceInfo();
    symbolNode->layoutProperty_ = textLayoutProperty;
    backButtonNode->children_.emplace_back(symbolNode);

    titleBarPattern->HandleLongPress(backButtonNode);
    EXPECT_EQ(titleBarPattern->dialogNode_, nullptr);
    // Calling TearDownTestSuite will cause crash.
}

/**
 * @tc.name: HandleLongPress003
 * @tc.desc: Branch: if (dialogNode_ != nullptr) = false
 *           Branch: if (backButtonIconNode->GetTag() == V2::SYMBOL_ETS_TAG) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, HandleLongPress003, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = nullptr;
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    imageLayoutProperty->propImageSourceInfo_ = ImageSourceInfo();
    textNode->layoutProperty_ = imageLayoutProperty;
    backButtonNode->children_.emplace_back(textNode);

    titleBarPattern->HandleLongPress(backButtonNode);
    EXPECT_EQ(titleBarPattern->dialogNode_, nullptr);
    // Calling TearDownTestSuite will cause crash.
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate001
 * @tc.desc: if (LessNotEqual(GetFontScale(), GetDialogBigFontSizeScale())) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnFontScaleConfigurationUpdate001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto longPressCallback = [](GestureEvent& info) { };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    gestureHub->SetLongPressEvent(longPressEvent);

    titleBarPattern->OnFontScaleConfigurationUpdate();
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_EQ(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate002
 * @tc.desc: if (LessNotEqual(GetFontScale(), GetDialogBigFontSizeScale())) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnFontScaleConfigurationUpdate002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() + 1.0f;
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(nullptr);

    titleBarPattern->OnFontScaleConfigurationUpdate();
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_NE(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Branch: if (isInitialTitle_) = false
 *           Branch: if (GreatOrEqual(GetFontScale(), GetDialogBigFontSizeScale())) = false
 *           Branch: if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) = false
 *           Condition: options_.enableHoverMode = false
 *           Branch: if (GetTitleModeValue() != FREE || isInitialTitle_ || !isTitleChanged_) = true
 *           Condition: GetTitleModeValue() != FREE = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = false;
    titleBarPattern->currentFoldCreaseRegion_.clear();
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FULL;
    // Set InitTitleParam testing parameters
    titleBarPattern->isFreeTitleUpdated_ = true;
    // Set InitBackButtonLongPressEvent testing parameters
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(nullptr);
    // Set InitFoldCreaseRegion testing parameters
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> currentFoldCreaseRegion = { Rect(0.0f, 0.0f, 1000.0f, 800.0f) };
    displayInfo->SetCurrentFoldCreaseRegion(currentFoldCreaseRegion);
    titleBarPattern->isTitleChanged_ = true;

    titleBarPattern->OnModifyDone();
    EXPECT_TRUE(titleBarPattern->isFreeTitleUpdated_);
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_EQ(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
    ASSERT_EQ(titleBarPattern->currentFoldCreaseRegion_.size(), 0);
    EXPECT_TRUE(titleBarPattern->isTitleChanged_);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Branch: if (isInitialTitle_) = true
 *           Branch: if (GreatOrEqual(GetFontScale(), GetDialogBigFontSizeScale())) = true
 *           Branch: if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) = false
 *           Condition: options_.enableHoverMode = true, currentFoldCreaseRegion_.empty() = false
 *           Branch: if (GetTitleModeValue() != FREE || isInitialTitle_ || !isTitleChanged_) = true
 *           Condition: GetTitleModeValue() != FREE = false, isInitialTitle_ = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = true;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() + 1.0f;
    titleBarPattern->options_.enableHoverMode = true;
    titleBarPattern->currentFoldCreaseRegion_.emplace_back(Rect());
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    // Set InitTitleParam testing parameters
    titleBarPattern->isFreeTitleUpdated_ = true;
    // Set InitBackButtonLongPressEvent testing parameters
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(nullptr);
    // Set InitFoldCreaseRegion testing parameters
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> currentFoldCreaseRegion = { Rect(0.0f, 0.0f, 1000.0f, 800.0f) };
    displayInfo->SetCurrentFoldCreaseRegion(currentFoldCreaseRegion);
    titleBarPattern->isTitleChanged_ = true;

    titleBarPattern->OnModifyDone();
    EXPECT_FALSE(titleBarPattern->isFreeTitleUpdated_);
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_NE(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
    ASSERT_EQ(titleBarPattern->currentFoldCreaseRegion_.size(), 1);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_[0].Width(), 0.0f);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_[0].Height(), 0.0f);
    EXPECT_TRUE(titleBarPattern->isTitleChanged_);
}

/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Branch: if (isInitialTitle_) = false
 *           Branch: if (GreatOrEqual(GetFontScale(), GetDialogBigFontSizeScale())) = false
 *           Branch: if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) = true
 *           Condition: options_.enableHoverMode = true, currentFoldCreaseRegion_.empty() = true
 *           Branch: if (GetTitleModeValue() != FREE || isInitialTitle_ || !isTitleChanged_) = true
 *           Condition: GetTitleModeValue() != FREE = false, isInitialTitle_ = false, !isTitleChanged_ = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = true;
    titleBarPattern->currentFoldCreaseRegion_.clear();
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isTitleChanged_ = false;
    // Set InitTitleParam testing parameters
    titleBarPattern->isFreeTitleUpdated_ = true;
    // Set InitBackButtonLongPressEvent testing parameters
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(nullptr);
    // Set InitFoldCreaseRegion testing parameters
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> currentFoldCreaseRegion = { Rect(0.0f, 0.0f, 1000.0f, 800.0f) };
    displayInfo->SetCurrentFoldCreaseRegion(currentFoldCreaseRegion);

    titleBarPattern->OnModifyDone();
    EXPECT_TRUE(titleBarPattern->isFreeTitleUpdated_);
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_EQ(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
    ASSERT_EQ(titleBarPattern->currentFoldCreaseRegion_.size(), 1);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_[0].Width(), 1000.0f);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_[0].Height(), 800.0f);
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
}

/**
 * @tc.name: OnModifyDone004
 * @tc.desc: Branch: if (isInitialTitle_) = false
 *           Branch: if (GreatOrEqual(GetFontScale(), GetDialogBigFontSizeScale())) = false
 *           Branch: if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) = false
 *           Condition: options_.enableHoverMode = false
 *           Branch: if (GetTitleModeValue() != FREE || isInitialTitle_ || !isTitleChanged_) = false
 *           Condition: GetTitleModeValue() != FREE = false, isInitialTitle_ = false, !isTitleChanged_ = false
 *           Branch: if (NearEqual(GetTempTitleBarHeight(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT) ||
 *               NearEqual(GetTempTitleBarHeight(), FULL_SINGLE_LINE_TITLEBAR_HEIGHT)) = true
 *           Condition: NearEqual(GetTempTitleBarHeight(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = false;
    titleBarPattern->currentFoldCreaseRegion_.clear();
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = FULL_DOUBLE_LINE_TITLEBAR_HEIGHT;
    // Set InitTitleParam testing parameters
    titleBarPattern->isFreeTitleUpdated_ = true;
    // Set InitBackButtonLongPressEvent testing parameters
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(nullptr);
    // Set InitFoldCreaseRegion testing parameters
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> currentFoldCreaseRegion = { Rect(0.0f, 0.0f, 1000.0f, 800.0f) };
    displayInfo->SetCurrentFoldCreaseRegion(currentFoldCreaseRegion);

    titleBarPattern->OnModifyDone();
    EXPECT_TRUE(titleBarPattern->isFreeTitleUpdated_);
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_EQ(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_.size(), 0);
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: OnModifyDone005
 * @tc.desc: Branch: if (isInitialTitle_) = false
 *           Branch: if (GreatOrEqual(GetFontScale(), GetDialogBigFontSizeScale())) = false
 *           Branch: if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) = false
 *           Condition: options_.enableHoverMode = false
 *           Branch: if (GetTitleModeValue() != FREE || isInitialTitle_ || !isTitleChanged_) = false
 *           Condition: GetTitleModeValue() != FREE = false, isInitialTitle_ = false, !isTitleChanged_ = false
 *           Branch: if (NearEqual(GetTempTitleBarHeight(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT) ||
 *               NearEqual(GetTempTitleBarHeight(), FULL_SINGLE_LINE_TITLEBAR_HEIGHT)) = true
 *           Condition: NearEqual(GetTempTitleBarHeight(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT) = false
 *                      NearEqual(GetTempTitleBarHeight(), FULL_SINGLE_LINE_TITLEBAR_HEIGHT) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone005, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = false;
    titleBarPattern->currentFoldCreaseRegion_.clear();
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = FULL_SINGLE_LINE_TITLEBAR_HEIGHT;
    // Set InitTitleParam testing parameters
    titleBarPattern->isFreeTitleUpdated_ = true;
    // Set InitBackButtonLongPressEvent testing parameters
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(nullptr);
    // Set InitFoldCreaseRegion testing parameters
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> currentFoldCreaseRegion = { Rect(0.0f, 0.0f, 1000.0f, 800.0f) };
    displayInfo->SetCurrentFoldCreaseRegion(currentFoldCreaseRegion);

    titleBarPattern->OnModifyDone();
    EXPECT_TRUE(titleBarPattern->isFreeTitleUpdated_);
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_EQ(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_.size(), 0);
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: OnModifyDone006
 * @tc.desc: Branch: if (isInitialTitle_) = false
 *           Branch: if (GreatOrEqual(GetFontScale(), GetDialogBigFontSizeScale())) = false
 *           Branch: if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) = false
 *           Condition: options_.enableHoverMode = false
 *           Branch: if (GetTitleModeValue() != FREE || isInitialTitle_ || !isTitleChanged_) = false
 *           Condition: GetTitleModeValue() != FREE = false, isInitialTitle_ = false, !isTitleChanged_ = false
 *           Branch: if (NearEqual(GetTempTitleBarHeight(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT) ||
 *               NearEqual(GetTempTitleBarHeight(), FULL_SINGLE_LINE_TITLEBAR_HEIGHT)) = false
 *           Condition: NearEqual(GetTempTitleBarHeight(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT) = false
 *                      NearEqual(GetTempTitleBarHeight(), FULL_SINGLE_LINE_TITLEBAR_HEIGHT) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone006, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = false;
    titleBarPattern->currentFoldCreaseRegion_.clear();
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = 0.0_vp;
    // Set InitTitleParam testing parameters
    titleBarPattern->isFreeTitleUpdated_ = true;
    // Set InitBackButtonLongPressEvent testing parameters
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(V2::BACK_BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarNode->SetBackButton(backButtonNode);
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(nullptr);
    // Set InitFoldCreaseRegion testing parameters
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> currentFoldCreaseRegion = { Rect(0.0f, 0.0f, 1000.0f, 800.0f) };
    displayInfo->SetCurrentFoldCreaseRegion(currentFoldCreaseRegion);

    titleBarPattern->OnModifyDone();
    EXPECT_TRUE(titleBarPattern->isFreeTitleUpdated_);
    ASSERT_NE(gestureHub->longPressEventActuator_, nullptr);
    EXPECT_EQ(gestureHub->longPressEventActuator_->longPressEvent_, nullptr);
    ASSERT_EQ(titleBarPattern->currentFoldCreaseRegion_.size(), 0);
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(), 0.0f);
}

/**
 * @tc.name: ProcessTitleDragUpdate001
 * @tc.desc: Branch: if (GetTitleModeValue || IsHidden) = true
 *           Condition: GetTitleModeValue = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, ProcessTitleDragUpdate001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    titleBarPattern->opacity_ = titleBarPattern->GetSubtitleOpacity() + 0.5f;

    titleBarPattern->ProcessTitleDragUpdate(0.0f);
    EXPECT_NE(titleBarPattern->opacity_, titleBarPattern->GetSubtitleOpacity());
}

/**
 * @tc.name: ProcessTitleDragUpdate002
 * @tc.desc: Branch: if (GetTitleModeValue || IsHidden) = true
 *           Condition: GetTitleModeValue = false, IsHidden = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, ProcessTitleDragUpdate002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        "NavBar", 201, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    titleBarNode->SetParent(navBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);
    navBarLayoutProperty->propHideTitleBar_ = true;
    titleBarPattern->opacity_ = titleBarPattern->GetSubtitleOpacity() + 0.5f;

    titleBarPattern->ProcessTitleDragUpdate(0.0f);
    EXPECT_NE(titleBarPattern->opacity_, titleBarPattern->GetSubtitleOpacity());
}

/**
 * @tc.name: ProcessTitleDragUpdate003
 * @tc.desc: Branch: if (GetTitleModeValue || IsHidden) = false
 *           Condition: GetTitleModeValue = false, IsHidden = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, ProcessTitleDragUpdate003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        "NavBar", 201, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    titleBarNode->SetParent(navBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);
    navBarLayoutProperty->propHideTitleBar_ = false;
    titleBarPattern->opacity_ = titleBarPattern->GetSubtitleOpacity() + 0.5f;

    titleBarPattern->ProcessTitleDragUpdate(0.0f);
    EXPECT_EQ(titleBarPattern->opacity_, titleBarPattern->GetSubtitleOpacity());
}

/**
 * @tc.name: SetTempTitleOffsetY001
 * @tc.desc: Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = false
 *           Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempTitleOffsetY001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->minTitleOffsetY_ = 10.0f;
    titleBarPattern->maxTitleOffsetY_ = 100.0f;
    titleBarPattern->defaultTitleOffsetY_ = 0.0f;
    titleBarPattern->titleMoveDistance_ = 20.0f;
    auto tempTitleOffsetY = titleBarPattern->defaultTitleOffsetY_ + titleBarPattern->titleMoveDistance_;

    titleBarPattern->SetTempTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempTitleOffsetY_, tempTitleOffsetY);
}

/**
 * @tc.name: SetTempTitleOffsetY002
 * @tc.desc: Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempTitleOffsetY002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->minTitleOffsetY_ = 10.0f;
    titleBarPattern->maxTitleOffsetY_ = 100.0f;
    titleBarPattern->defaultTitleOffsetY_ = 0.0f;
    titleBarPattern->titleMoveDistance_ = 0.0f;

    titleBarPattern->SetTempTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempTitleOffsetY_, titleBarPattern->minTitleOffsetY_);
}

/**
 * @tc.name: SetTempTitleOffsetY003
 * @tc.desc: Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempTitleOffsetY003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->minTitleOffsetY_ = 10.0f;
    titleBarPattern->maxTitleOffsetY_ = 100.0f;
    titleBarPattern->defaultTitleOffsetY_ = 10.0f;
    titleBarPattern->titleMoveDistance_ = 100.0f;

    titleBarPattern->SetTempTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempTitleOffsetY_, titleBarPattern->maxTitleOffsetY_);
}

/**
 * @tc.name: SetTempSubTitleOffsetY001
 * @tc.desc: Branch: if (GreatOrEqualTargetAPIVersion) = false
 *           Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = false
 *           Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempSubTitleOffsetY001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    auto titleHeight = titleBarPattern->GetTitleHeight();
    titleBarPattern->tempTitleOffsetY_ = 0.0f;
    titleBarPattern->minTitleOffsetY_ = titleHeight - 10.0f;
    titleBarPattern->maxTitleOffsetY_ = titleHeight + 10.0f;

    titleBarPattern->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempSubTitleOffsetY_, titleBarPattern->tempTitleOffsetY_ + titleHeight);
}

/**
 * @tc.name: SetTempSubTitleOffsetY002
 * @tc.desc: Branch: if (GreatOrEqualTargetAPIVersion) = true
 *           Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = false
 *           Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempSubTitleOffsetY002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto titleHeight = titleBarPattern->GetTitleHeight();
    titleBarPattern->tempTitleOffsetY_ = 0.0f;
    titleBarPattern->minTitleOffsetY_ = titleHeight - 10.0f;
    titleBarPattern->maxTitleOffsetY_ = titleHeight + 10.0f;
    titleBarPattern->titleSpaceVertical_ = 10.0_vp;

    titleBarPattern->SetTempSubTitleOffsetY();
    auto titleSpaceVertical = static_cast<float>(titleBarPattern->titleSpaceVertical_.ConvertToPx());
    EXPECT_EQ(titleBarPattern->tempSubTitleOffsetY_,
        titleBarPattern->tempTitleOffsetY_ + titleHeight + titleSpaceVertical);
}

/**
 * @tc.name: SetTempSubTitleOffsetY003
 * @tc.desc: Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempSubTitleOffsetY003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    auto titleHeight = titleBarPattern->GetTitleHeight();
    titleBarPattern->tempTitleOffsetY_ = 0.0f;
    titleBarPattern->minTitleOffsetY_ = titleHeight + 10.0f;
    titleBarPattern->maxTitleOffsetY_ = titleHeight + 20.0f;

    titleBarPattern->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempSubTitleOffsetY_, titleBarPattern->minTitleOffsetY_);
}

/**
 * @tc.name: SetTempSubTitleOffsetY004
 * @tc.desc: Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempSubTitleOffsetY004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    auto titleHeight = titleBarPattern->GetTitleHeight();
    titleBarPattern->tempTitleOffsetY_ = 0.0f;
    titleBarPattern->minTitleOffsetY_ = titleHeight - 20.0f;
    titleBarPattern->maxTitleOffsetY_ = titleHeight - 10.0f;

    titleBarPattern->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempSubTitleOffsetY_, titleBarPattern->maxTitleOffsetY_);
}

/**
 * @tc.name: UpdateTitleFontSize001
 * @tc.desc: Branch: if (isFontSizeSettedByDeveloper_) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleFontSize001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(titleNode);
    titleBarPattern->isFontSizeSettedByDeveloper_ = false;

    Dimension tempTitleFontSize = 20.0_vp;
    titleBarPattern->UpdateTitleFontSize(tempTitleFontSize);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_TRUE(textLayoutProperty->GetFontSize() == tempTitleFontSize);
    EXPECT_TRUE(textLayoutProperty->GetAdaptMaxFontSize() == tempTitleFontSize);
}

/**
 * @tc.name: UpdateTitleFontSize002
 * @tc.desc: Branch: if (isFontSizeSettedByDeveloper_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleFontSize002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(titleNode);
    titleBarPattern->isFontSizeSettedByDeveloper_ = true;

    Dimension tempTitleFontSize = 20.0_vp;
    titleBarPattern->UpdateTitleFontSize(tempTitleFontSize);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_FALSE(textLayoutProperty->GetFontSize() == tempTitleFontSize);
}

/**
 * @tc.name: InitMenuDragEvent001
 * @tc.desc: Branch: if (dialogNode && index >= 0 && index < totalCount) = false
 *           Condition: dialogNode = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, InitMenuDragEvent001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto eventHub = titleBarNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        "Menu", 201, AceType::MakeRefPtr<MenuPattern>(1, "Menu", MenuType::MENU));
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, 301, []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->isActive_ = true;
    auto textGeometryNode = textNode->GetGeometryNode();
    textGeometryNode->frame_.rect_.width_ = 50.0f;
    textGeometryNode->frame_.rect_.height_ = 50.0f;
    menuNode->children_.push_back(textNode);
    std::vector<NG::BarItem> menuItems;
    titleBarPattern->InitMenuDragEvent(gestureHub, menuNode, menuItems);
    titleBarPattern->moveIndex_ = std::nullopt;

    ASSERT_NE(gestureHub->dragEventActuator_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_->userCallback_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_->userCallback_->actionUpdate_, nullptr);
    GestureEvent info;
    gestureHub->dragEventActuator_->userCallback_->actionUpdate_(info);
    EXPECT_EQ(titleBarPattern->moveIndex_, std::nullopt);
}

/**
 * @tc.name: InitMenuDragEvent002
 * @tc.desc: Branch: if (dialogNode && index >= 0 && index < totalCount) = true
 *           Condition: dialogNode = true, index >= 0 = true, index < totalCount = true
 *           Branch: if (!pattern->GetMoveIndex().has_value()) = true
 *           Branch: if (pattern->GetMoveIndex().value() != index) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, InitMenuDragEvent002, TestSize.Level1)
{
    TitleBarPatternTestNg::MockPipelineContextGetTheme();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto eventHub = titleBarNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        "Menu", 201, AceType::MakeRefPtr<MenuPattern>(1, "Menu", MenuType::MENU));
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 301, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->isActive_ = true;
    auto buttonGeometryNode = buttonNode->GetGeometryNode();
    buttonGeometryNode->frame_.rect_.width_ = 50.0f;
    buttonGeometryNode->frame_.rect_.height_ = 50.0f;
    menuNode->children_.push_back(buttonNode);
    auto dialogNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, 401, []() { return AceType::MakeRefPtr<TextPattern>(); });
    titleBarPattern->largeFontPopUpDialogNode_ = AceType::WeakClaim(AceType::RawPtr(dialogNode));
    std::vector<NG::BarItem> menuItems;
    titleBarPattern->InitMenuDragEvent(gestureHub, menuNode, menuItems);
    titleBarPattern->moveIndex_ = std::nullopt;

    ASSERT_NE(gestureHub->dragEventActuator_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_->userCallback_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_->userCallback_->actionUpdate_, nullptr);
    GestureEvent info;
    auto menuItemNode =
        menuNode->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    ASSERT_NE(menuItemNode, nullptr);
    EXPECT_NE(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
    auto index = menuNode->GetChildIndex(menuItemNode);
    gestureHub->dragEventActuator_->userCallback_->actionUpdate_(info);
    EXPECT_EQ(titleBarPattern->moveIndex_, index);
    ASSERT_NE(titleBarPattern->largeFontPopUpDialogNode_.Upgrade(), nullptr);
    EXPECT_EQ(titleBarPattern->largeFontPopUpDialogNode_.Upgrade()->GetId(), dialogNode->GetId());
}

/**
 * @tc.name: InitMenuDragEvent003
 * @tc.desc: Branch: if (!pattern->GetMoveIndex().has_value()) = false
 *           Branch: if (pattern->GetMoveIndex().value() != index) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, InitMenuDragEvent003, TestSize.Level1)
{
    TitleBarPatternTestNg::MockPipelineContextGetTheme();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto eventHub = titleBarNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        "Menu", 201, AceType::MakeRefPtr<MenuPattern>(1, "Menu", MenuType::MENU));
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 301, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->isActive_ = true;
    auto buttonGeometryNode = buttonNode->GetGeometryNode();
    buttonGeometryNode->frame_.rect_.width_ = 50.0f;
    buttonGeometryNode->frame_.rect_.height_ = 50.0f;
    menuNode->children_.push_back(buttonNode);
    auto dialogNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, 401, []() { return AceType::MakeRefPtr<TextPattern>(); });
    titleBarPattern->largeFontPopUpDialogNode_ = AceType::WeakClaim(AceType::RawPtr(dialogNode));
    std::vector<NG::BarItem> menuItems;
    titleBarPattern->InitMenuDragEvent(gestureHub, menuNode, menuItems);
    titleBarPattern->moveIndex_ = 10;

    ASSERT_NE(gestureHub->dragEventActuator_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_->userCallback_, nullptr);
    ASSERT_NE(gestureHub->dragEventActuator_->userCallback_->actionUpdate_, nullptr);
    GestureEvent info;
    auto menuItemNode =
        menuNode->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    ASSERT_NE(menuItemNode, nullptr);
    EXPECT_NE(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
    auto index = menuNode->GetChildIndex(menuItemNode);
    gestureHub->dragEventActuator_->userCallback_->actionUpdate_(info);
    EXPECT_EQ(titleBarPattern->moveIndex_, index);
    ASSERT_EQ(titleBarPattern->largeFontPopUpDialogNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: CalculateHandledOffsetMinTitle001
 * @tc.desc: Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetMinTitle001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight - titleBarPattern->defaultTitleBarHeight_ - 10.00f;

    float ret = titleBarPattern->CalculateHandledOffsetMinTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: CalculateHandledOffsetMinTitle002
 * @tc.desc: Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = false
 *           Branch: if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetMinTitle002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight + 10.00f;
    titleBarPattern->maxTitleBarHeight_ = minHeight + 5.00f;

    float ret = titleBarPattern->CalculateHandledOffsetMinTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, minHeight - titleBarPattern->maxTitleBarHeight_);
}

/**
 * @tc.name: CalculateHandledOffsetMinTitle003
 * @tc.desc: Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = false
 *           Branch: if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetMinTitle003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight + 10.00f;
    titleBarPattern->maxTitleBarHeight_ = minHeight + 20.00f;

    float ret = titleBarPattern->CalculateHandledOffsetMinTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, offset -
        (titleBarPattern->coordScrollOffset_ - (minHeight - titleBarPattern->defaultTitleBarHeight_)));
}

/**
 * @tc.name: CalculateHandledOffsetMaxTitle001
 * @tc.desc: Branch: if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetMaxTitle001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float lastCordScrollOffset = 56.00f;
    titleBarPattern->maxTitleBarHeight_ = lastCordScrollOffset - 10.00f;

    float heightTemp = titleBarPattern->defaultTitleBarHeight_ + lastCordScrollOffset;
    EXPECT_TRUE(GreatOrEqual(heightTemp, titleBarPattern->maxTitleBarHeight_));
    float ret = titleBarPattern->CalculateHandledOffsetMaxTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: CalculateHandledOffsetMaxTitle002
 * @tc.desc: Branch: if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) = false
 *           Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetMaxTitle002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight - 10.00f;
    titleBarPattern->maxTitleBarHeight_ = lastCordScrollOffset + 10.00f;

    float ret = titleBarPattern->CalculateHandledOffsetMaxTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, minHeight - titleBarPattern->maxTitleBarHeight_);
}

/**
 * @tc.name: CalculateHandledOffsetMaxTitle003
 * @tc.desc: Branch: if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) = false
 *           Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetMaxTitle003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight + 10.00f;
    titleBarPattern->maxTitleBarHeight_ = lastCordScrollOffset + 10.00f;

    float ret = titleBarPattern->CalculateHandledOffsetMaxTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, offset - (titleBarPattern->coordScrollOffset_ -
        (titleBarPattern->maxTitleBarHeight_ - titleBarPattern->defaultTitleBarHeight_)));
}

/**
 * @tc.name: CalculateHandledOffsetBetweenMinAndMaxTitle001
 * @tc.desc: Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetBetweenMinAndMaxTitle001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight - 10.00f;

    float ret = titleBarPattern->CalculateHandledOffsetBetweenMinAndMaxTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, titleBarPattern->defaultTitleBarHeight_ + titleBarPattern->coordScrollOffset_ - minHeight);
}

/**
 * @tc.name: CalculateHandledOffsetBetweenMinAndMaxTitle002
 * @tc.desc: Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = false
 *           Branch: if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetBetweenMinAndMaxTitle002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight + 10.00f;
    titleBarPattern->maxTitleBarHeight_ = lastCordScrollOffset - 10.00f;

    float ret = titleBarPattern->CalculateHandledOffsetBetweenMinAndMaxTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, titleBarPattern->coordScrollOffset_ -
        (titleBarPattern->maxTitleBarHeight_ - titleBarPattern->defaultTitleBarHeight_));
}

/**
 * @tc.name: CalculateHandledOffsetBetweenMinAndMaxTitle003
 * @tc.desc: Branch: if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) = false
 *           Branch: if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, CalculateHandledOffsetBetweenMinAndMaxTitle003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);
    titleBarPattern->defaultTitleBarHeight_ = 0.00f;
    float offset = 0.00f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float lastCordScrollOffset = minHeight + 10.00f;
    titleBarPattern->maxTitleBarHeight_ = lastCordScrollOffset + 10.00f;

    float ret = titleBarPattern->CalculateHandledOffsetBetweenMinAndMaxTitle(offset, lastCordScrollOffset);
    EXPECT_EQ(ret, offset);
}

/**
 * @tc.name: UpdateScaleByDragOverDragOffset001
 * @tc.desc: Branch: if (Negative(overDragOffset)) = false
 *           Branch: if (navBarNode->GetPrevTitleIsCustomValue(true)) = false
 *           Branch: if (subtitleNode) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateScaleByDragOverDragOffset001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    titleBarNode->SetParent(navBarNode);
    auto title = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    float overDragOffset = 10.0f;
    navBarNode->propPrevTitleIsCustom_ = false;
    // Set MarkDirtyNode testing parameters
    titleBarNode->isFreeze_ = true;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);

    titleBarPattern->UpdateScaleByDragOverDragOffset(overDragOffset);
    EXPECT_EQ(titleBarLayoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateScaleByDragOverDragOffset002
 * @tc.desc: Branch: if (Negative(overDragOffset)) = false
 *           Branch: if (navBarNode->GetPrevTitleIsCustomValue(true)) = false
 *           Branch: if (subtitleNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateScaleByDragOverDragOffset002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    titleBarNode->SetParent(navBarNode);
    auto title = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    auto subtitle = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->subtitle_ = subtitle;
    float overDragOffset = 10.0f;
    navBarNode->propPrevTitleIsCustom_ = false;
    // Set TransformScale testing parameters
    auto subtitleRenderContext = subtitle->GetRenderContext();
    ASSERT_NE(subtitleRenderContext, nullptr);
    subtitleRenderContext->UpdateTransformScale(VectorF(0.0f, 0.0f));
    // Set MarkDirtyNode testing parameters
    titleBarNode->isFreeze_ = true;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_NORMAL);

    titleBarPattern->UpdateScaleByDragOverDragOffset(overDragOffset);
    EXPECT_EQ(titleBarLayoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    EXPECT_NE(subtitleRenderContext->GetTransformScale()->x, 0.0f);
    EXPECT_NE(subtitleRenderContext->GetTransformScale()->y, 0.0f);
}

/**
 * @tc.name: UpdateScaleByDragOverDragOffset003
 * @tc.desc: Branch: if (Negative(overDragOffset)) = false
 *           Branch: if (navBarNode->GetPrevTitleIsCustomValue(true)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateScaleByDragOverDragOffset003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    titleBarNode->SetParent(navBarNode);
    auto title = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    float overDragOffset = 10.0f;
    navBarNode->propPrevTitleIsCustom_ = true;
    // Set MarkDirtyNode testing parameters
    titleBarNode->isFreeze_ = true;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    titleBarPattern->UpdateScaleByDragOverDragOffset(overDragOffset);
    EXPECT_EQ(titleBarLayoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: UpdateScaleByDragOverDragOffset004
 * @tc.desc: Branch: if (Negative(overDragOffset)) = false
 *           Branch: if (navBarNode->GetPrevTitleIsCustomValue(true)) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateScaleByDragOverDragOffset004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    titleBarNode->SetParent(navBarNode);
    auto title = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    float overDragOffset = -10.0f;
    // Set MarkDirtyNode testing parameters
    titleBarNode->isFreeze_ = true;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    titleBarPattern->UpdateScaleByDragOverDragOffset(overDragOffset);
    EXPECT_EQ(titleBarLayoutProperty->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
}

/**
 * @tc.name: GetFontSize001
 * @tc.desc: Branch: if (GreatOrEqualTargetAPIVersion(VERSION_TWELVE)) = false
 *           Branch: if (!NearZero(titleBarHeightDiff)) = false
 *           Branch: if (GreatNotEqual(tempFontSize, titleL.Value())) = false
 *           Branch: if (LessNotEqual(tempFontSize, titleM.Value())) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetFontSize001, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    navigationBarTheme_->titleFontSizeBig_.SetValue(30.0f);
    navigationBarTheme_->titleFontSize_.SetValue(16.0f);
    float singleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern->maxTitleBarHeight_ = singleHeight;
    titleBarPattern->defaultTitleBarHeight_ = singleHeight + 10.0f;
    titleBarPattern->fontSizeRatio_ = 1.0f;

    auto fontSize = titleBarPattern->GetFontSize(0.0f);
    EXPECT_EQ(fontSize.Value(), 26.0f);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: GetFontSize002
 * @tc.desc: Branch: if (GreatOrEqualTargetAPIVersion(VERSION_TWELVE)) = true
 *           Branch: if (!NearZero(titleBarHeightDiff)) = true
 *           Branch: if (GreatNotEqual(tempFontSize, titleL.Value())) = true
 *           Branch: if (LessNotEqual(tempFontSize, titleM.Value())) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetFontSize002, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);
    navigationBarTheme_->mainTitleFontSizeL_.SetValue(26.0f);
    navigationBarTheme_->mainTitleFontSizeM_.SetValue(16.0f);
    float singleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern->maxTitleBarHeight_ = singleHeight + 10.0f;
    titleBarPattern->defaultTitleBarHeight_ = singleHeight + 20.0f;
    titleBarPattern->fontSizeRatio_ = 1.0f;

    auto fontSize = titleBarPattern->GetFontSize(0.0f);
    EXPECT_EQ(fontSize.Value(), 26.0f);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: GetFontSize003
 * @tc.desc: Branch: if (GreatOrEqualTargetAPIVersion(VERSION_TWELVE)) = true
 *           Branch: if (!NearZero(titleBarHeightDiff)) = true
 *           Branch: if (GreatNotEqual(tempFontSize, titleL.Value())) = false
 *           Branch: if (LessNotEqual(tempFontSize, titleM.Value())) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetFontSize003, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);
    navigationBarTheme_->mainTitleFontSizeL_.SetValue(26.0f);
    navigationBarTheme_->mainTitleFontSizeM_.SetValue(16.0f);
    float singleHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    titleBarPattern->maxTitleBarHeight_ = singleHeight + 10.0f;
    titleBarPattern->defaultTitleBarHeight_ = singleHeight - 20.0f;
    titleBarPattern->fontSizeRatio_ = 1.0f;

    auto fontSize = titleBarPattern->GetFontSize(0.0f);
    EXPECT_EQ(fontSize.Value(), 16.0f);
    TitleBarPatternTestNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG