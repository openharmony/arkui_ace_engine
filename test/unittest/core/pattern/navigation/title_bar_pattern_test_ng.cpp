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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components_ng/pattern/button/button_pattern.h"
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
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TitleBarPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TitleBarPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateTitleModeChange001
 * @tc.desc: Increase the coverage of TitleBarPattern::UpdateTitleModeChange function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;

    EXPECT_NE(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    titleBarPattern->UpdateTitleModeChange();
}

/**
 * @tc.name: UpdateTitleModeChange002
 * @tc.desc: Increase the coverage of TitleBarPattern::UpdateTitleModeChange function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->maxTitleBarHeight_ = 0.0f;

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_TRUE(NearZero(titleBarPattern->maxTitleBarHeight_));
    titleBarPattern->UpdateTitleModeChange();
}

/**
 * @tc.name: UpdateTitleModeChange003
 * @tc.desc: Increase the coverage of TitleBarPattern::UpdateTitleModeChange function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_FALSE(NearZero(titleBarPattern->maxTitleBarHeight_));
    EXPECT_TRUE(geometryNode->GetFrameSize().Height() >= titleBarPattern->maxTitleBarHeight_);
    titleBarPattern->UpdateTitleModeChange();
}

/**
 * @tc.name: UpdateTitleModeChange004
 * @tc.desc: Increase the coverage of TitleBarPattern::UpdateTitleModeChange function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_FALSE(NearZero(titleBarPattern->maxTitleBarHeight_));
    auto titleBarHeight = geometryNode->GetFrameSize().Height();
    EXPECT_FALSE(titleBarHeight >= titleBarPattern->maxTitleBarHeight_);
    EXPECT_TRUE(NearEqual(titleBarHeight, static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx())));
    titleBarPattern->UpdateTitleModeChange();
}

/**
 * @tc.name: UpdateTitleModeChange005
 * @tc.desc: Increase the coverage of TitleBarPattern::UpdateTitleModeChange function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleModeChange005, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_FALSE(NearZero(titleBarPattern->maxTitleBarHeight_));
    auto titleBarHeight = geometryNode->GetFrameSize().Height();
    EXPECT_FALSE(titleBarHeight >= titleBarPattern->maxTitleBarHeight_);
    EXPECT_FALSE(NearEqual(titleBarHeight, static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx())));
    titleBarPattern->UpdateTitleModeChange();
}

/**
 * @tc.name: UpdateTitleBarByCoordScroll001
 * @tc.desc: Increase the coverage of TitleBarPattern::UpdateTitleBarByCoordScroll function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleBarByCoordScroll001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    titleBarPattern->UpdateTitleBarByCoordScroll(0.0f);
}

/**
 * @tc.name: UpdateTitleBarByCoordScroll002
 * @tc.desc: Increase the coverage of TitleBarPattern::UpdateTitleBarByCoordScroll function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleBarByCoordScroll002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;

    EXPECT_NE(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    titleBarPattern->UpdateTitleBarByCoordScroll(0.0f);
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: Increase the coverage of TitleBarPattern::DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    EXPECT_EQ(titleBarNode->GetTitle(), nullptr);
    titleBarPattern->DumpInfo();
}

/**
 * @tc.name: DumpInfo002
 * @tc.desc: Increase the coverage of TitleBarPattern::DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto mainTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(mainTitleNode);
    mainTitleNode->layoutProperty_ = nullptr;

    EXPECT_NE(titleBarNode->GetTitle(), nullptr);
    auto mainTitleProperty = mainTitleNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(mainTitleProperty, nullptr);
    titleBarPattern->DumpInfo();
}

/**
 * @tc.name: DumpInfo003
 * @tc.desc: Increase the coverage of TitleBarPattern::DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto mainTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetTitle(mainTitleNode);

    EXPECT_NE(titleBarNode->GetTitle(), nullptr);
    auto mainTitleProperty = mainTitleNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(mainTitleProperty, nullptr);
    titleBarPattern->DumpInfo();
}

/**
 * @tc.name: DumpInfo004
 * @tc.desc: Increase the coverage of TitleBarPattern::DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    EXPECT_EQ(titleBarNode->GetSubtitle(), nullptr);
    titleBarPattern->DumpInfo();
}

/**
 * @tc.name: DumpInfo005
 * @tc.desc: Increase the coverage of TitleBarPattern::DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo005, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto subTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetSubtitle(subTitleNode);
    subTitleNode->layoutProperty_ = nullptr;

    EXPECT_NE(titleBarNode->GetSubtitle(), nullptr);
    auto subTitleProperty = subTitleNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(subTitleProperty, nullptr);
    titleBarPattern->DumpInfo();
}

/**
 * @tc.name: DumpInfo006
 * @tc.desc: Increase the coverage of TitleBarPattern::DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, DumpInfo006, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto subTitleNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 201, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->SetSubtitle(subTitleNode);

    EXPECT_NE(titleBarNode->GetSubtitle(), nullptr);
    auto subTitleProperty = subTitleNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(subTitleProperty, nullptr);
    titleBarPattern->DumpInfo();
}

/**
 * @tc.name: GetTitleBarHeightLessThanMaxBarHeight001
 * @tc.desc: Increase the coverage of TitleBarPattern::GetTitleBarHeightLessThanMaxBarHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetTitleBarHeightLessThanMaxBarHeight001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;

    EXPECT_NE(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    float ret = titleBarPattern->GetTitleBarHeightLessThanMaxBarHeight();
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: GetTitleBarHeightLessThanMaxBarHeight002
 * @tc.desc: Increase the coverage of TitleBarPattern::GetTitleBarHeightLessThanMaxBarHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetTitleBarHeightLessThanMaxBarHeight002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    titleBarPattern->GetTitleBarHeightLessThanMaxBarHeight();
}

/**
 * @tc.name: GetTitleBarHeightLessThanMaxBarHeight003
 * @tc.desc: Increase the coverage of TitleBarPattern::GetTitleBarHeightLessThanMaxBarHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetTitleBarHeightLessThanMaxBarHeight003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->options_.brOptions.barStyle = BarStyle::STANDARD;

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_NE(titleBarPattern->options_.brOptions.barStyle.value_or(BarStyle::STANDARD), BarStyle::STACK);
    titleBarPattern->GetTitleBarHeightLessThanMaxBarHeight();
}

/**
 * @tc.name: GetTitleBarHeightLessThanMaxBarHeight004
 * @tc.desc: Increase the coverage of TitleBarPattern::GetTitleBarHeightLessThanMaxBarHeight function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, GetTitleBarHeightLessThanMaxBarHeight004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->options_.brOptions.barStyle = BarStyle::STACK;

    EXPECT_EQ(titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE), NavigationTitleMode::FREE);
    EXPECT_EQ(titleBarPattern->options_.brOptions.barStyle.value_or(BarStyle::STANDARD), BarStyle::STACK);
    titleBarPattern->GetTitleBarHeightLessThanMaxBarHeight();
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: Increase the coverage of TitleBarPattern::HandleLongPress function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, HandleLongPress001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 201, []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    EXPECT_EQ(titleBarPattern->dialogNode_, nullptr);
    titleBarPattern->HandleLongPress(backButtonNode);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: Increase the coverage of TitleBarPattern::HandleLongPress function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, HandleLongPress002, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 201, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    titleBarPattern->dialogNode_ = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        301, AceType::MakeRefPtr<LinearLayoutPattern>(true));

    EXPECT_NE(titleBarPattern->dialogNode_, nullptr);
    titleBarPattern->HandleLongPress(backButtonNode);
}

/**
 * @tc.name: HandleLongPress003
 * @tc.desc: Increase the coverage of TitleBarPattern::HandleLongPress function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, HandleLongPress003, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 201, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto symbolNode = FrameNode::GetOrCreateFrameNode(
        V2::SYMBOL_ETS_TAG, 301, []() { return AceType::MakeRefPtr<TextPattern>(); });
    backButtonNode->children_.emplace_back(symbolNode);

    auto backButtonIconNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetFirstChild());
    ASSERT_NE(backButtonIconNode, nullptr);
    EXPECT_EQ(backButtonIconNode->GetTag(), V2::SYMBOL_ETS_TAG);
    titleBarPattern->HandleLongPress(backButtonNode);
}

/**
 * @tc.name: HandleLongPress004
 * @tc.desc: Increase the coverage of TitleBarPattern::HandleLongPress function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, HandleLongPress004, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 201, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, 301, []() { return AceType::MakeRefPtr<TextPattern>(); });
    backButtonNode->children_.emplace_back(textNode);

    auto backButtonIconNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetFirstChild());
    ASSERT_NE(backButtonIconNode, nullptr);
    EXPECT_NE(backButtonIconNode->GetTag(), V2::SYMBOL_ETS_TAG);
    titleBarPattern->HandleLongPress(backButtonNode);
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate001
 * @tc.desc: Increase the coverage of TitleBarPattern::OnFontScaleConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnFontScaleConfigurationUpdate001, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 201, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, 301, []() { return AceType::MakeRefPtr<TextPattern>(); });
    backButtonNode->children_.emplace_back(textNode);
    titleBarNode->SetBackButton(backButtonNode);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;

    EXPECT_TRUE(LessNotEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    titleBarPattern->OnFontScaleConfigurationUpdate();
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate002
 * @tc.desc: Increase the coverage of TitleBarPattern::OnFontScaleConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnFontScaleConfigurationUpdate002, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto backButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 201, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, 301, []() { return AceType::MakeRefPtr<TextPattern>(); });
    backButtonNode->children_.emplace_back(textNode);
    titleBarNode->SetBackButton(backButtonNode);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() + 1.0f;

    EXPECT_FALSE(LessNotEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    titleBarPattern->OnFontScaleConfigurationUpdate();
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Increase the coverage of TitleBarPattern::OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() + 1.0f;

    EXPECT_TRUE(GreatOrEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    titleBarPattern->OnModifyDone();
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Increase the coverage of TitleBarPattern::OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;

    EXPECT_FALSE(GreatOrEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    titleBarPattern->OnModifyDone();
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Increase the coverage of TitleBarPattern::OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone003, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = false;

    EXPECT_FALSE(GreatOrEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    EXPECT_FALSE(titleBarPattern->options_.enableHoverMode);
    titleBarPattern->OnModifyDone();
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone004
 * @tc.desc: Increase the coverage of TitleBarPattern::OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone004, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = true;
    titleBarPattern->currentFoldCreaseRegion_.emplace_back(Rect());

    EXPECT_FALSE(GreatOrEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale()));
    EXPECT_TRUE(titleBarPattern->options_.enableHoverMode);
    EXPECT_FALSE(titleBarPattern->currentFoldCreaseRegion_.empty());
    titleBarPattern->OnModifyDone();
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone005
 * @tc.desc: Branch: if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) = true
 *           Condition: options_.enableHoverMode = true, currentFoldCreaseRegion_.empty() = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone005, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    titleBarPattern->options_.enableHoverMode = true;
    titleBarPattern->currentFoldCreaseRegion_.clear();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> rects;
    Rect rect(0.0f, 0.0f, 50.0f, 1080.0f);
    rects.insert(rects.end(), rect);
    displayInfo->currentFoldCreaseRegion_ = rects;

    titleBarPattern->OnModifyDone();
    ASSERT_EQ(titleBarPattern->currentFoldCreaseRegion_.size(), 1);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_[0].width_, 50.0f);
    EXPECT_EQ(titleBarPattern->currentFoldCreaseRegion_[0].height_, 1080.0f);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone006
 * @tc.desc: Branch: if (GetTitleModeValue || isInitialTitle_ || !isTitleChanged_) = true
 *           Condition: GetTitleModeValue = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone006, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = FULL_DOUBLE_LINE_TITLEBAR_HEIGHT;
    std::cout << "LPC OnModifyDone006 GetTempTitleBarHeight_" << titleBarPattern->GetTempTitleBarHeight() << "\n";

    titleBarPattern->OnModifyDone();
    EXPECT_TRUE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone007
 * @tc.desc: Branch: if (GetTitleModeValue || isInitialTitle_ || !isTitleChanged_) = true
 *           Condition: GetTitleModeValue = false, isInitialTitle_ = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone007, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isInitialTitle_ = true;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = FULL_DOUBLE_LINE_TITLEBAR_HEIGHT;

    titleBarPattern->OnModifyDone();
    EXPECT_TRUE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone008
 * @tc.desc: Branch: if (GetTitleModeValue || isInitialTitle_ || !isTitleChanged_) = true
 *           Condition: GetTitleModeValue = false, isInitialTitle_ = false, !isTitleChanged_ = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone008, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isInitialTitle_ = false;
    titleBarPattern->isTitleChanged_ = false;
    titleBarPattern->tempTitleBarHeight_ = FULL_DOUBLE_LINE_TITLEBAR_HEIGHT;

    titleBarPattern->OnModifyDone();
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone009
 * @tc.desc: Branch: if (GetTitleModeValue || isInitialTitle_ || !isTitleChanged_) = false
 *           Condition: GetTitleModeValue = false, isInitialTitle_ = false, !isTitleChanged_ = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone009, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isInitialTitle_ = false;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = FULL_DOUBLE_LINE_TITLEBAR_HEIGHT;

    titleBarPattern->OnModifyDone();
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone0010
 * @tc.desc: Branch: if (NearEqual || NearEqual) = true
 *           Condition: NearEqual = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone0010, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isInitialTitle_ = false;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = FULL_DOUBLE_LINE_TITLEBAR_HEIGHT;

    titleBarPattern->OnModifyDone();
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone0011
 * @tc.desc: Branch: if (NearEqual || NearEqual) = true
 *           Condition: NearEqual = false, NearEqual = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone0011, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isInitialTitle_ = false;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = FULL_SINGLE_LINE_TITLEBAR_HEIGHT;
    titleBarNode->subtitle_ = FrameNode::CreateFrameNode("SubTitle", 201, AceType::MakeRefPtr<TextPattern>());

    titleBarPattern->OnModifyDone();
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(),
        static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone0012
 * @tc.desc: Branch: if (NearEqual || NearEqual) = false
 *           Condition: NearEqual = false, NearEqual = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, OnModifyDone0012, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->isInitialTitle_ = false;
    auto pipeline = titleBarNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->isInitialTitle_ = false;
    titleBarPattern->isTitleChanged_ = true;
    titleBarPattern->tempTitleBarHeight_ = 0.0_vp;

    titleBarPattern->OnModifyDone();
    EXPECT_FALSE(titleBarPattern->isTitleChanged_);
    EXPECT_EQ(titleBarPattern->GetTempTitleBarHeight(), 0.0f);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: ProcessTitleDragUpdate001
 * @tc.desc: Branch: if (GetTitleModeValue || IsHidden) = true
 *           Condition: GetTitleModeValue = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, ProcessTitleDragUpdate001, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    titleBarPattern->opacity_ = titleBarPattern->GetSubtitleOpacity() + 0.5f;

    titleBarPattern->ProcessTitleDragUpdate(0.0f);
    EXPECT_NE(titleBarPattern->opacity_, titleBarPattern->GetSubtitleOpacity());
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: ProcessTitleDragUpdate002
 * @tc.desc: Branch: if (GetTitleModeValue || IsHidden) = true
 *           Condition: GetTitleModeValue = false, IsHidden = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, ProcessTitleDragUpdate002, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: ProcessTitleDragUpdate003
 * @tc.desc: Branch: if (GetTitleModeValue || IsHidden) = false
 *           Condition: GetTitleModeValue = false, IsHidden = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, ProcessTitleDragUpdate003, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: SetTempTitleOffsetY001
 * @tc.desc: Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = false
 *           Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempTitleOffsetY001, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->minTitleOffsetY_ = 10.0f;
    titleBarPattern->maxTitleOffsetY_ = 100.0f;
    titleBarPattern->defaultTitleOffsetY_ = 0.0f;
    titleBarPattern->titleMoveDistance_ = 20.0f;
    auto tempTitleOffsetY = titleBarPattern->defaultTitleOffsetY_ + titleBarPattern->titleMoveDistance_;

    titleBarPattern->SetTempTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempTitleOffsetY_, tempTitleOffsetY);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: SetTempTitleOffsetY002
 * @tc.desc: Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempTitleOffsetY002, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->minTitleOffsetY_ = 10.0f;
    titleBarPattern->maxTitleOffsetY_ = 100.0f;
    titleBarPattern->defaultTitleOffsetY_ = 0.0f;
    titleBarPattern->titleMoveDistance_ = 0.0f;

    titleBarPattern->SetTempTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempTitleOffsetY_, titleBarPattern->minTitleOffsetY_);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: SetTempTitleOffsetY003
 * @tc.desc: Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempTitleOffsetY003, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->minTitleOffsetY_ = 10.0f;
    titleBarPattern->maxTitleOffsetY_ = 100.0f;
    titleBarPattern->defaultTitleOffsetY_ = 10.0f;
    titleBarPattern->titleMoveDistance_ = 100.0f;

    titleBarPattern->SetTempTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempTitleOffsetY_, titleBarPattern->maxTitleOffsetY_);
    TitleBarPatternTestNg::TearDownTestSuite();
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
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    auto titleHeight = titleBarPattern->GetTitleHeight();
    titleBarPattern->tempTitleOffsetY_ = 0.0f;
    titleBarPattern->minTitleOffsetY_ = titleHeight - 10.0f;
    titleBarPattern->maxTitleOffsetY_ = titleHeight + 10.0f;

    titleBarPattern->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempSubTitleOffsetY_, titleBarPattern->tempTitleOffsetY_ + titleHeight);
    TitleBarPatternTestNg::TearDownTestSuite();
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
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: SetTempSubTitleOffsetY003
 * @tc.desc: Branch: if (tempTitleOffsetY_ < minTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempSubTitleOffsetY003, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    auto titleHeight = titleBarPattern->GetTitleHeight();
    titleBarPattern->tempTitleOffsetY_ = 0.0f;
    titleBarPattern->minTitleOffsetY_ = titleHeight + 10.0f;
    titleBarPattern->maxTitleOffsetY_ = titleHeight + 20.0f;

    titleBarPattern->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempSubTitleOffsetY_, titleBarPattern->minTitleOffsetY_);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: SetTempSubTitleOffsetY004
 * @tc.desc: Branch: if (tempTitleOffsetY_ > maxTitleOffsetY_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, SetTempSubTitleOffsetY004, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    auto titleHeight = titleBarPattern->GetTitleHeight();
    titleBarPattern->tempTitleOffsetY_ = 0.0f;
    titleBarPattern->minTitleOffsetY_ = titleHeight - 20.0f;
    titleBarPattern->maxTitleOffsetY_ = titleHeight - 10.0f;

    titleBarPattern->SetTempSubTitleOffsetY();
    EXPECT_EQ(titleBarPattern->tempSubTitleOffsetY_, titleBarPattern->maxTitleOffsetY_);
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateTitleFontSize001
 * @tc.desc: Branch: if (isFontSizeSettedByDeveloper_) = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleFontSize001, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateTitleFontSize002
 * @tc.desc: Branch: if (isFontSizeSettedByDeveloper_) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, UpdateTitleFontSize002, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
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
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: InitMenuDragEvent001
 * @tc.desc: Branch: if (dialogNode && index >= 0 && index < totalCount) = false
 *           Condition: dialogNode = false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, InitMenuDragEvent001, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto eventHub = titleBarNode->GetEventHub<EventHub>();
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
    TitleBarPatternTestNg::TearDownTestSuite();
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
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto eventHub = titleBarNode->GetEventHub<EventHub>();
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
    TitleBarPatternTestNg::TearDownTestSuite();
}

/**
 * @tc.name: InitMenuDragEvent003
 * @tc.desc: Branch: if (!pattern->GetMoveIndex().has_value()) = false
 *           Branch: if (pattern->GetMoveIndex().value() != index) = true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestNg, InitMenuDragEvent003, TestSize.Level1)
{
    TitleBarPatternTestNg::SetUpTestSuite();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "TitleBar", 101, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    auto eventHub = titleBarNode->GetEventHub<EventHub>();
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
    TitleBarPatternTestNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG