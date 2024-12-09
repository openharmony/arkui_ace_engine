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

#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
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
 * @tc.desc: Increase the coverage of NavigationPattern::UpdateTitleModeChange function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::UpdateTitleModeChange function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::UpdateTitleModeChange function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::UpdateTitleModeChange function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::UpdateTitleModeChange function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::UpdateTitleBarByCoordScroll function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::UpdateTitleBarByCoordScroll function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::DumpInfo function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::DumpInfo function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::DumpInfo function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::DumpInfo function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::DumpInfo function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::DumpInfo function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::GetTitleBarHeightLessThanMaxBarHeight function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::GetTitleBarHeightLessThanMaxBarHeight function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::GetTitleBarHeightLessThanMaxBarHeight function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::GetTitleBarHeightLessThanMaxBarHeight function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::HandleLongPress function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::HandleLongPress function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::HandleLongPress function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::HandleLongPress function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::OnFontScaleConfigurationUpdate function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::OnFontScaleConfigurationUpdate function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::OnModifyDone function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::OnModifyDone function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::OnModifyDone function.
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
 * @tc.desc: Increase the coverage of NavigationPattern::OnModifyDone function.
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
} // namespace OHOS::Ace::NG