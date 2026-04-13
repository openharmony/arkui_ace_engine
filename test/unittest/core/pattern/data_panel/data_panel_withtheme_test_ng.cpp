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

#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_style.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"
#include "core/components_ng/pattern/data_panel/data_panel_theme_wrapper.h"
#include "core/components_ng/syntax/with_theme_node.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t THEME_SCOPE_ID = 10001;
const Color THEME_BACKGROUND_COLOR = Color::RED;
constexpr Dimension THEME_THICKNESS = 20.0_vp;
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

} // namespace OHOS::Ace::NG