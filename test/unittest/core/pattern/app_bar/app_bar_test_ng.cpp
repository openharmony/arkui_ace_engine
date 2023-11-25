/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include <vector>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/calc_length.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class AppBarTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void ClickBtn(RefPtr<FrameNode> frameNode);
};

void AppBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppBarTheme>()));
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
}

void AppBarTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void AppBarTestNg::SetUp() {}

void AppBarTestNg::TearDown() {}

void AppBarTestNg::ClickBtn(RefPtr<FrameNode> frameNode)
{
    auto eventHub = frameNode->GetOrCreateGestureEventHub();
    EXPECT_TRUE(eventHub->clickEventActuator_);
    auto clickEvents = eventHub->clickEventActuator_->clickEvents_;
    GestureEvent info;
    EXPECT_FALSE(clickEvents.empty());
    clickEvents.front()->GetGestureEventFunc()(info);
}

/**
 * @tc.name: Test001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, Test001, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AppBarView::Create(test);
    EXPECT_EQ(frameNode->GetChildren().size(), 3);
    auto titleBar = frameNode->GetChildAtIndex(0);
    EXPECT_EQ(titleBar->GetChildren().size(), 2);
}

/**
 * @tc.name: Test002
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, Test002, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>("stage", 1, AceType::MakeRefPtr<StagePattern>());
    auto frameNode = AppBarView::Create(stage);
    auto appBar = Referenced::MakeRefPtr<AppBarView>(frameNode);
    appBar->iniBehavior();
    stage->GetPattern<StagePattern>()->OnRebuildFrame();
    auto titleBar = frameNode->GetChildAtIndex(0);
    auto backbtn = AceType::DynamicCast<FrameNode>(titleBar->GetFirstChild());
    EXPECT_EQ(backbtn->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);

    auto test2 = AceType::MakeRefPtr<FrameNode>("test", 2, AceType::MakeRefPtr<Pattern>());
    auto test3 = AceType::MakeRefPtr<FrameNode>("test", 3, AceType::MakeRefPtr<Pattern>());
    stage->AddChild(test2);
    stage->AddChild(test3);
    frameNode = AppBarView::Create(stage);
    appBar = Referenced::MakeRefPtr<AppBarView>(frameNode);
    appBar->iniBehavior();
    stage->GetPattern<StagePattern>()->OnRebuildFrame();
    titleBar = frameNode->GetChildAtIndex(0);
    backbtn = AceType::DynamicCast<FrameNode>(titleBar->GetFirstChild());
    EXPECT_EQ(backbtn->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: Test003
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, Test003, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    SystemProperties::SetExtSurfaceEnabled(true);
    auto frameNode = AppBarView::Create(test);
    AppBarView::BindContentCover(nullptr);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetChildren().size(), 3);
    auto titleBar = frameNode->GetChildAtIndex(0);
    EXPECT_TRUE(titleBar);
    EXPECT_EQ(titleBar->GetChildren().size(), 2);
    auto backBtn = AceType::DynamicCast<FrameNode>(titleBar->GetChildAtIndex(0));
    EXPECT_TRUE(backBtn);
    ClickBtn(backBtn);
    auto shareBtn = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(2));
    EXPECT_TRUE(shareBtn);
    SUCCEED();
}

/**
 * @tc.name: AppBarSetVisible004
 * @tc.desc: Test use of SetVisible
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, AppBarSetVisible004, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto atom = AppBarView::Create(test);
    auto appBar = Referenced::MakeRefPtr<AppBarView>(atom);
    auto titleBar = AceType::DynamicCast<FrameNode>(atom->GetFirstChild());
    appBar->SetVisible(false);
    EXPECT_EQ(titleBar->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);
    appBar->SetVisible(true);
    EXPECT_EQ(titleBar->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: AppBarSetRowColor005
 * @tc.desc: Test use of SetRowColor
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, AppBarSetRowColor005, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto atom = AppBarView::Create(test);
    auto appBar = Referenced::MakeRefPtr<AppBarView>(atom);
    auto titleBar = AceType::DynamicCast<FrameNode>(atom->GetFirstChild());
    auto renderContext = titleBar->GetRenderContext();
    auto originColor = renderContext->GetBackgroundColorValue();
    appBar->SetRowColor(Color::RED);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::RED);
    std::optional<Color> NonColor = std::nullopt;
    appBar->SetRowColor(NonColor);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), originColor);
}

/**
 * @tc.name: AppBarSetContent006
 * @tc.desc: Test use of SetContent
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, AppBarSetContent006, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto atom = AppBarView::Create(test);
    auto appBar = Referenced::MakeRefPtr<AppBarView>(atom);
    auto titleBar = atom->GetFirstChild();
    auto label = AceType::DynamicCast<FrameNode>(titleBar->GetLastChild());
    auto property = label->GetLayoutProperty<TextLayoutProperty>();
    appBar->SetContent("content of test");
    EXPECT_EQ(property->GetContent(), "content of test");
}

/**
 * @tc.name: AppBarSetFontStyle007
 * @tc.desc: Test use of SetFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, AppBarSetFontStyle007, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto atom = AppBarView::Create(test);
    auto appBar = Referenced::MakeRefPtr<AppBarView>(atom);
    auto titleBar = AceType::DynamicCast<FrameNode>(atom->GetFirstChild());
    auto label = AceType::DynamicCast<FrameNode>(titleBar->GetLastChild());
    auto property = label->GetLayoutProperty<TextLayoutProperty>();
    appBar->SetFontStyle(Ace::FontStyle::NORMAL);
    std::optional<Ace::FontStyle> fontStyle = property->GetItalicFontStyle();
    ASSERT_NE(fontStyle, std::nullopt);
    EXPECT_EQ(fontStyle.value(), Ace::FontStyle::NORMAL);
    appBar->SetFontStyle(Ace::FontStyle::ITALIC);
    fontStyle = property->GetItalicFontStyle();
    ASSERT_NE(fontStyle, std::nullopt);
    EXPECT_EQ(fontStyle.value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: AppBarSetIconColor008
 * @tc.desc: Test use of SetIconColor
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, AppBarSetIconColor008, TestSize.Level1)
{
    auto test = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    auto atom = AppBarView::Create(test);
    auto appBar = Referenced::MakeRefPtr<AppBarView>(atom);
    auto faBtn = atom->GetLastChild();
    auto faIcon = AceType::DynamicCast<FrameNode>(faBtn->GetFirstChild());
    auto property = faIcon->GetLayoutProperty<ImageLayoutProperty>();
    auto originColor = property->GetImageSourceInfo()->GetFillColor();
    appBar->SetIconColor(Color::RED);
    EXPECT_EQ(property->GetImageSourceInfo()->GetFillColor(), Color::RED);
    std::optional<Color> NonColor = std::nullopt;
    appBar->SetIconColor(NonColor);
    EXPECT_EQ(property->GetImageSourceInfo()->GetFillColor(), originColor);
}

/**
 * @tc.name: AppBarWithNavigation009
 * @tc.desc: Test when exist navigation hide appbar
 * @tc.type: FUNC
 */
HWTEST_F(AppBarTestNg, AppBarWithNavigation009, TestSize.Level1)
{
    auto stage = AceType::MakeRefPtr<FrameNode>(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<StagePattern>());
    auto atom = AppBarView::Create(stage);
    auto appBar = Referenced::MakeRefPtr<AppBarView>(atom);
    appBar->iniBehavior();
    stage->GetPattern<StagePattern>()->OnRebuildFrame();
    auto titleBar = AceType::DynamicCast<FrameNode>(atom->GetFirstChild());
    EXPECT_EQ(titleBar->GetLayoutProperty()->GetVisibility(), VisibleType::GONE);

    auto page2 = AceType::MakeRefPtr<FrameNode>("test", 2, AceType::MakeRefPtr<Pattern>());
    auto page3 = AceType::MakeRefPtr<FrameNode>("test", 3, AceType::MakeRefPtr<Pattern>());
    stage->AddChild(page2);
    stage->AddChild(page3);
    atom = AppBarView::Create(stage);
    appBar = Referenced::MakeRefPtr<AppBarView>(atom);
    appBar->iniBehavior();
    stage->GetPattern<StagePattern>()->OnRebuildFrame();
    titleBar = AceType::DynamicCast<FrameNode>(atom->GetFirstChild());
    EXPECT_EQ(titleBar->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
}
} // namespace OHOS::Ace::NG
