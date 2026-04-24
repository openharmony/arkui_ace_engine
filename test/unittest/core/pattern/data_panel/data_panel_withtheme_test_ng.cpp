/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_data_panel_theme.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_style.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "core/components_ng/pattern/data_panel/data_panel_theme_wrapper.h"
#include "core/components_ng/token_theme/token_colors.h"
#include "core/components_ng/syntax/with_theme_node.h"
#include "ui/view/theme/token_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
std::map<int32_t, JSTheme> JSThemeScope::jsThemes = {};
std::optional<JSTheme> JSThemeScope::jsCurrentTheme = std::nullopt;
bool JSThemeScope::isCurrentThemeDefault = true;

void JSThemeColors::SetColors(const std::vector<ResourceValue>& colors)
{
    colors_ = colors;
}
} // namespace OHOS::Ace::Framework

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t THEME_SCOPE_ID = 10001;
const Color THEME_BACKGROUND_COLOR = Color::RED;
const Color USER_TRACK_BACKGROUND_COLOR = Color::BLUE;
const Color THEME_EMPHASIZE_COLOR = Color::GREEN;
const Color TOKEN_THEME_BACKGROUND_COLOR = Color::BLACK;
const Color TOKEN_THEME_EMPHASIZE_COLOR = Color::WHITE;
constexpr size_t EXPECTED_THEME_COLOR_COUNT = 9;
constexpr Dimension THEME_THICKNESS = 20.0_vp;

class JSThemeScopeGuard {
public:
    explicit JSThemeScopeGuard(std::optional<Framework::JSTheme> theme) : theme_(std::move(theme))
    {
        Framework::JSThemeUtils::SwapCurrentTheme(theme_);
    }

    ~JSThemeScopeGuard()
    {
        Framework::JSThemeUtils::SwapCurrentTheme(theme_);
    }

private:
    std::optional<Framework::JSTheme> theme_;
};

std::optional<Framework::JSTheme> CreateDataPanelJsTheme(const Color& backgroundColor, const Color& emphasizeColor)
{
    std::vector<Framework::ResourceValue> colors(TokenColors::TOTAL_NUMBER);
    for (auto& item : colors) {
        item.colorValue = Color::TRANSPARENT;
    }
    colors[COMP_BACKGROUND_TERTIARY].colorValue = backgroundColor;
    colors[COMP_BACKGROUND_EMPHASIZE].colorValue = emphasizeColor;

    Framework::JSThemeColors jsThemeColors;
    jsThemeColors.SetColors(colors);
    Framework::JSTheme theme;
    theme.SetColors(jsThemeColors);
    theme.SetDarkColors(jsThemeColors);
    return theme;
}
} // namespace

class DataPanelWithThemeTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void DataPanelWithThemeTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void DataPanelWithThemeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void DataPanelWithThemeTestNg::SetUp()
{
    TestNG::SetUp();
}

void DataPanelWithThemeTestNg::TearDown()
{
    TestNG::TearDown();
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Test DataPanelPattern OnThemeScopeUpdate updates paint properties from theme
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelWithThemeTestNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    // Set API target version to VERSION_TWENTY_SIX to enable theme scope update
    int32_t backupApiVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(26); // VERSION_TWENTY_SIX

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);

    auto themeConstants = TestNG::CreateThemeConstants(THEME_PATTERN_DATA_PANEL);
    ASSERT_NE(themeConstants, nullptr);

    auto dataPanelStyle = AceType::MakeRefPtr<ThemeStyle>();
    dataPanelStyle->SetAttr(PATTERN_BG_COLOR,
        ResValueWrapper { .type = ThemeConstantsType::COLOR, .value = THEME_BACKGROUND_COLOR });
    dataPanelStyle->SetAttr("datapanel_thickness",
        ResValueWrapper { .type = ThemeConstantsType::DIMENSION, .value = THEME_THICKNESS });
    dataPanelStyle->SetAttr(DATA_PANEL_COLOR_1_START,
        ResValueWrapper { .type = ThemeConstantsType::COLOR, .value = Color::GREEN });
    dataPanelStyle->SetAttr(DATA_PANEL_COLOR_1_END,
        ResValueWrapper { .type = ThemeConstantsType::COLOR, .value = Color::BLUE });

    ResValueWrapper patternValue;
    patternValue.type = ThemeConstantsType::PATTERN;
    patternValue.value = dataPanelStyle;
    themeConstants->GetThemeStyle()->SetAttr(THEME_PATTERN_DATA_PANEL, patternValue);

    auto dataPanelTheme = AceType::DynamicCast<OHOS::Ace::DataPanelTheme>(
        DataPanelThemeWrapper::WrapperBuilder().BuildWrapper(themeConstants));
    ASSERT_NE(dataPanelTheme, nullptr);

    // 修改：匹配任何 scopeId 参数
    EXPECT_CALL(*themeManager, GetTheme(testing::_, testing::_))
        .WillRepeatedly(testing::Return(dataPanelTheme));

    auto withThemeNode = WithThemeNode::CreateWithThemeNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withThemeNode, nullptr);
    withThemeNode->SetThemeScopeId(THEME_SCOPE_ID);

    auto frameNode = FrameNode::CreateFrameNode(
        "data-panel", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DataPanelPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(withThemeNode);

    frameNode->AttachToMainTree(true, pipeline.GetRawPtr());

    auto pattern = frameNode->GetPattern<DataPanelPattern>();
    ASSERT_NE(pattern, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    bool updateResult = pattern->OnThemeScopeUpdate(THEME_SCOPE_ID);
    EXPECT_TRUE(updateResult);
    EXPECT_EQ(paintProperty->GetTrackBackgroundValue(), THEME_BACKGROUND_COLOR);
    EXPECT_FALSE(paintProperty->GetValueColorsValue().empty());
    
    // Restore API target version
    Container::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: JSDataPanelThemeApplyTheme001
 * @tc.desc: Test ApplyTheme updates track background when it is not set by user.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelWithThemeTestNg, JSDataPanelThemeApplyTheme001, TestSize.Level1)
{
    JSThemeScopeGuard themeGuard(CreateDataPanelJsTheme(THEME_BACKGROUND_COLOR, THEME_EMPHASIZE_COLOR));

    DataPanelModelNG dataPanel;
    dataPanel.Create({ 1.0, 2.0 }, 100.0, 0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateTrackBackground(USER_TRACK_BACKGROUND_COLOR);
    paintProperty->UpdateTrackBackgroundSetByUser(false);

    Framework::JSDataPanelTheme::ApplyTheme();

    EXPECT_EQ(paintProperty->GetTrackBackgroundValue(), THEME_BACKGROUND_COLOR);
    EXPECT_EQ(paintProperty->GetTrackBackgroundSetByUser(), false);
    EXPECT_EQ(paintProperty->GetValueColorsValue().size(), 1u);
}

/**
 * @tc.name: JSDataPanelThemeApplyTheme002
 * @tc.desc: Test ApplyTheme keeps track background when it is set by user.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelWithThemeTestNg, JSDataPanelThemeApplyTheme002, TestSize.Level1)
{
    JSThemeScopeGuard themeGuard(CreateDataPanelJsTheme(THEME_BACKGROUND_COLOR, THEME_EMPHASIZE_COLOR));

    DataPanelModelNG dataPanel;
    dataPanel.Create({ 1.0, 2.0 }, 100.0, 0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto paintProperty = frameNode->GetPaintProperty<DataPanelPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateTrackBackground(USER_TRACK_BACKGROUND_COLOR);
    paintProperty->UpdateTrackBackgroundSetByUser(true);

    Framework::JSDataPanelTheme::ApplyTheme();

    EXPECT_EQ(paintProperty->GetTrackBackgroundValue(), USER_TRACK_BACKGROUND_COLOR);
    EXPECT_EQ(paintProperty->GetTrackBackgroundSetByUser(), true);
    EXPECT_EQ(paintProperty->GetValueColorsValue().size(), 1u);
}

/**
 * @tc.name: DataPanelThemeWrapperApplyTokenTheme001
 * @tc.desc: Test ApplyTokenTheme expands DataPanel theme colors to the full expected color count.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelWithThemeTestNg, DataPanelThemeWrapperApplyTokenTheme001, TestSize.Level1)
{
    auto wrapper = AceType::DynamicCast<DataPanelThemeWrapper>(
        DataPanelThemeWrapper::WrapperBuilder().BuildWrapper(TestNG::CreateThemeConstants(THEME_PATTERN_DATA_PANEL)));
    ASSERT_NE(wrapper, nullptr);

    auto tokenColors = AceType::MakeRefPtr<TokenColors>();
    ASSERT_NE(tokenColors, nullptr);
    tokenColors->SetColor(COMP_BACKGROUND_TERTIARY, TOKEN_THEME_BACKGROUND_COLOR);
    tokenColors->SetColor(COMP_BACKGROUND_EMPHASIZE, TOKEN_THEME_EMPHASIZE_COLOR);

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(1);
    ASSERT_NE(tokenTheme, nullptr);
    tokenTheme->SetColors(tokenColors);

    wrapper->ApplyTokenTheme(*tokenTheme);

    auto colors = wrapper->GetColorsArray();
    EXPECT_EQ(wrapper->GetBackgroundColor(), TOKEN_THEME_BACKGROUND_COLOR);
    EXPECT_EQ(colors.size(), EXPECTED_THEME_COLOR_COUNT);
    EXPECT_EQ(colors.front().first, TOKEN_THEME_EMPHASIZE_COLOR);
    EXPECT_EQ(colors.front().second, TOKEN_THEME_BACKGROUND_COLOR);
    EXPECT_EQ(colors.back().first, TOKEN_THEME_EMPHASIZE_COLOR);
    EXPECT_EQ(colors.back().second, TOKEN_THEME_BACKGROUND_COLOR);
}

/**
 * @tc.name: DataPanelThemeWrapperApplyTokenTheme002
 * @tc.desc: Test ApplyTokenTheme keeps original values when token theme has no colors.
 * @tc.type: FUNC
 */
HWTEST_F(DataPanelWithThemeTestNg, DataPanelThemeWrapperApplyTokenTheme002, TestSize.Level1)
{
    auto wrapper = AceType::DynamicCast<DataPanelThemeWrapper>(
        DataPanelThemeWrapper::WrapperBuilder().BuildWrapper(TestNG::CreateThemeConstants(THEME_PATTERN_DATA_PANEL)));
    ASSERT_NE(wrapper, nullptr);

    auto backgroundBefore = wrapper->GetBackgroundColor();
    auto colorsBefore = wrapper->GetColorsArray();

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(2);
    ASSERT_NE(tokenTheme, nullptr);

    wrapper->ApplyTokenTheme(*tokenTheme);

    auto colorsAfter = wrapper->GetColorsArray();
    EXPECT_EQ(wrapper->GetBackgroundColor(), backgroundBefore);
    EXPECT_EQ(colorsAfter.size(), colorsBefore.size());
    EXPECT_EQ(colorsAfter.front().first, colorsBefore.front().first);
    EXPECT_EQ(colorsAfter.front().second, colorsBefore.front().second);
    EXPECT_EQ(colorsAfter.back().first, colorsBefore.back().first);
    EXPECT_EQ(colorsAfter.back().second, colorsBefore.back().second);
}

} // namespace OHOS::Ace::NG