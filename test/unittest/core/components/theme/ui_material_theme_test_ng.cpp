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

#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_resource_adapter_v2.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/common/resource/resource_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components/theme/resource_adapter.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/ui_material_theme.h"
#include "interfaces/inner_api/ace_kit/include/ui/view/theme/token_colors.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class OverrideResourceAdapter : public MockResourceAdapterV2 {
    DECLARE_ACE_TYPE(OverrideResourceAdapter, MockResourceAdapterV2);

public:
    RefPtr<ResourceAdapter> GetOverrideResourceAdapter(
        const ResourceConfiguration& config, const ConfigurationChange& configurationChange) override
    {
        return AceType::MakeRefPtr<OverrideResourceAdapter>();
    }
};

class UiMaterialThemeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> frameNode_;
    void SetupMockThemeManager();
};

void UiMaterialThemeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void UiMaterialThemeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void UiMaterialThemeTestNg::SetUp()
{
    frameNode_ = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode_, nullptr);
}

void UiMaterialThemeTestNg::TearDown()
{
    frameNode_ = nullptr;
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    ResetMockResourceData();
    auto instanceId = MockContainer::Current()->GetInstanceId();
    ResourceManager::GetInstance().RemoveResourceAdapter("", "", instanceId);
}

void UiMaterialThemeTestNg::SetupMockThemeManager()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(ResourceAdapter::Create());
    EXPECT_CALL(*themeManager, GetThemeConstants()).WillRepeatedly(Return(themeConstants));
    auto shadowTheme = AceType::MakeRefPtr<ShadowTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(shadowTheme));

    RefPtr<ResourceAdapter> overrideAdapter = AceType::MakeRefPtr<OverrideResourceAdapter>();
    auto instanceId = MockContainer::Current()->GetInstanceId();
    ResourceManager::GetInstance().UpdateMainResourceAdapter("", "", instanceId, overrideAdapter);

    auto resId = TokenColors::GetSystemColorResIdByIndex(TokenColors::COMP_FOREGROUND_PRIMARY);
    AddMockResourceData(static_cast<uint32_t>(resId), Color(0xFF000000));
}

/**
 * @tc.name: GetUiMaterialParamWithColorMode_PriorityAndInvalidType
 * @tc.desc: Three-param overload: invalid type returns nullopt, UNDEFINED falls back to node colorMode,
 *           explicit LIGHT/DARK override node local mode and produce different cached results.
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialThemeTestNg, GetUiMaterialParamWithColorModePriorityAndInvalidType, TestSize.Level1)
{
    UiMaterialTheme theme;

    auto paramsInvalidType = theme.GetUiMaterialParam(static_cast<MaterialType>(-1), frameNode_, ColorMode::LIGHT);
    EXPECT_EQ(paramsInvalidType, std::nullopt);

    UiMaterialParam lightParam;
    lightParam.backgroundColor = Color(0xF2F1F3F5);
    UiMaterialParam darkParam;
    darkParam.backgroundColor = Color(0xF2303131);

    uint32_t lightKey = theme.GetKeyOfUiMaterial(MaterialType::IMMERSIVE, ColorMode::LIGHT);
    uint32_t darkKey = theme.GetKeyOfUiMaterial(MaterialType::IMMERSIVE, ColorMode::DARK);
    theme.materialParams_.emplace(lightKey, lightParam);
    theme.materialParams_.emplace(darkKey, darkParam);

    auto paramsUndefined =
        theme.GetUiMaterialParam(MaterialType::IMMERSIVE, frameNode_, ColorMode::COLOR_MODE_UNDEFINED);
    ASSERT_NE(paramsUndefined, std::nullopt);
    EXPECT_EQ(paramsUndefined->backgroundColor, lightParam.backgroundColor);

    auto paramsLight = theme.GetUiMaterialParam(MaterialType::IMMERSIVE, frameNode_, ColorMode::LIGHT);
    ASSERT_NE(paramsLight, std::nullopt);
    EXPECT_EQ(paramsLight->backgroundColor, lightParam.backgroundColor);

    auto paramsDark = theme.GetUiMaterialParam(MaterialType::IMMERSIVE, frameNode_, ColorMode::DARK);
    ASSERT_NE(paramsDark, std::nullopt);
    EXPECT_EQ(paramsDark->backgroundColor, darkParam.backgroundColor);
}

/**
 * @tc.name: ParseUiMaterialParam_AllBranchesWithColorMode
 * @tc.desc: ParseUiMaterialParam NONE→transparent, SEMI_TRANSPARENT→LIGHT/DARK backgroundColor,
 *           IMMERSIVE→LIGHT/DARK backgroundColor + shadow; unknown type→false.
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialThemeTestNg, ParseUiMaterialParamAllBranchesWithColorMode, TestSize.Level1)
{
    SetupMockThemeManager();

    UiMaterialTheme theme;
    UiMaterialParam noneParam;
    auto noneResult = theme.ParseUiMaterialParam(MaterialType::NONE, frameNode_, ColorMode::LIGHT, noneParam);
    EXPECT_TRUE(noneResult);
    EXPECT_EQ(noneParam.backgroundColor, Color::TRANSPARENT);
    EXPECT_EQ(noneParam.borderColor.leftColor.value_or(Color::BLACK), Color::TRANSPARENT);
    EXPECT_EQ(noneParam.borderWidth.leftDimen.value_or(Dimension(-1)), Dimension(0));

    UiMaterialParam semiLightParam;
    auto semiLightResult =
        theme.ParseUiMaterialParam(MaterialType::SEMI_TRANSPARENT, frameNode_, ColorMode::LIGHT, semiLightParam);
    EXPECT_TRUE(semiLightResult);
    EXPECT_EQ(semiLightParam.backgroundColor, Color(0xF2F1F3F5));

    theme.materialParams_.clear();
    UiMaterialParam semiDarkParam;
    auto semiDarkResult =
        theme.ParseUiMaterialParam(MaterialType::SEMI_TRANSPARENT, frameNode_, ColorMode::DARK, semiDarkParam);
    EXPECT_TRUE(semiDarkResult);
    EXPECT_EQ(semiDarkParam.backgroundColor, Color(0xF2303131));

    theme.materialParams_.clear();
    UiMaterialParam immersiveLightParam;
    auto immersiveLightResult =
        theme.ParseUiMaterialParam(MaterialType::IMMERSIVE, frameNode_, ColorMode::LIGHT, immersiveLightParam);
    EXPECT_TRUE(immersiveLightResult);
    EXPECT_EQ(immersiveLightParam.backgroundColor, Color(0xF2F1F3F5));
    EXPECT_NE(immersiveLightParam.shadow, Shadow());

    theme.materialParams_.clear();
    UiMaterialParam immersiveDarkParam;
    auto immersiveDarkResult =
        theme.ParseUiMaterialParam(MaterialType::IMMERSIVE, frameNode_, ColorMode::DARK, immersiveDarkParam);
    EXPECT_TRUE(immersiveDarkResult);
    EXPECT_EQ(immersiveDarkParam.backgroundColor, Color(0xF2303131));
    EXPECT_NE(immersiveDarkParam.shadow, Shadow());

    UiMaterialParam unknownParam;
    auto unknownResult =
        theme.ParseUiMaterialParam(static_cast<MaterialType>(-1), frameNode_, ColorMode::LIGHT, unknownParam);
    EXPECT_FALSE(unknownResult);
}

} // namespace OHOS::Ace::NG
