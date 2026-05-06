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

#include <optional>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/blur_parameter.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/theme/blur_style_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/theme/theme_style.h"
#include "core/components/theme/theme_utils.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class ThemeTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ThemeTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void ThemeTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ParseThemeIdReference005
 * @tc.desc: Test parsing "@app.type.name" with null themeConstants
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ParseThemeIdReference005, TestSize.Level1)
{
    auto result = ThemeUtils::ParseThemeIdReference("@app.media.icon_name");
    EXPECT_FALSE(result.parseSuccess);
}

/**
 * @tc.name: ParseThemeIdReference006
 * @tc.desc: Test parsing invalid/empty/short strings
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ParseThemeIdReference006, TestSize.Level1)
{
    // Empty string
    auto result = ThemeUtils::ParseThemeIdReference("");
    EXPECT_FALSE(result.parseSuccess);
    // Plain text
    EXPECT_FALSE(ThemeUtils::ParseThemeIdReference("hello world").parseSuccess);
    // Too short for any format
    EXPECT_FALSE(ThemeUtils::ParseThemeIdReference("@id").parseSuccess);
}

// ============================================================================
// ShadowTheme
// ============================================================================

/**
 * @tc.name: ShadowThemeBuilder001
 * @tc.desc: Test ShadowTheme::Builder::Build with null ThemeConstants
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeBuilder001, TestSize.Level1)
{
    ShadowTheme::Builder builder;
    auto theme = builder.Build(nullptr);
    ASSERT_NE(theme, nullptr);
    auto shadow = theme->GetShadow(ShadowStyle::OuterDefaultXS, ColorMode::LIGHT);
    EXPECT_EQ(shadow.GetBlurRadius(), 0.0);
}

/**
 * @tc.name: ShadowThemeBuilder002
 * @tc.desc: Test ShadowTheme::Builder::Build with ThemeConstants containing shadow pattern
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeBuilder002, TestSize.Level1)
{
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    auto shadowStyle = AceType::MakeRefPtr<ThemeStyle>();
    shadowStyle->SetAttr("shadow_style_default_xs_shadow",
        { .type = ThemeConstantsType::DOUBLE, .value = 5.0 });
    shadowStyle->SetAttr("shadow_style_default_xs_offset_x",
        { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    shadowStyle->SetAttr("shadow_style_default_xs_offset_y",
        { .type = ThemeConstantsType::DOUBLE, .value = 1.0 });
    shadowStyle->SetAttr("shadow_style_default_xs_color",
        { .type = ThemeConstantsType::COLOR, .value = Color(0x33000000) });
    shadowStyle->SetAttr("shadow_style_default_xs_radius",
        { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    ResValueWrapper patternValue { .type = ThemeConstantsType::PATTERN, .value = shadowStyle };
    themeStyle->SetAttr("ohos_shadow_pattern", patternValue);
    themeConstants->currentThemeStyle_ = themeStyle;
    ShadowTheme::Builder builder;
    auto theme = builder.Build(themeConstants);
    ASSERT_NE(theme, nullptr);
    auto shadow = theme->GetShadow(ShadowStyle::OuterDefaultXS, ColorMode::LIGHT);
    EXPECT_EQ(shadow.GetOffset().GetY(), 1.0);
}

/**
 * @tc.name: ShadowThemeBuilder003
 * @tc.desc: Test ShadowTheme::Builder::Build with ThemeConstants but no shadow pattern
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeBuilder003, TestSize.Level1)
{
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeConstants->currentThemeStyle_ = themeStyle;
    ShadowTheme::Builder builder;
    auto theme = builder.Build(themeConstants);
    ASSERT_NE(theme, nullptr);
    // No shadow pattern in themeStyle, themeStyle_ should be null
    auto shadow = theme->GetShadow(ShadowStyle::OuterDefaultXS, ColorMode::LIGHT);
    EXPECT_EQ(shadow.GetBlurRadius(), 0.0);
}

/**
 * @tc.name: ShadowThemeGetShadow001
 * @tc.desc: Test GetShadow with invalid/null states returns default Shadow
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeGetShadow001, TestSize.Level1)
{
    // Invalid style (None not in validShadowStyles_)
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    theme->SetThemeStyle(themeStyle);
    EXPECT_EQ(theme->GetShadow(ShadowStyle::None, ColorMode::LIGHT).GetBlurRadius(), 0.0);
    // Null themeStyle_
    auto theme2 = AceType::MakeRefPtr<ShadowTheme>();
    EXPECT_EQ(theme2->GetShadow(ShadowStyle::OuterDefaultXS, ColorMode::LIGHT).GetBlurRadius(), 0.0);
}

/**
 * @tc.name: ShadowThemeGetShadow002
 * @tc.desc: Test GetShadow cache hit returns cached value
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeGetShadow002, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    Shadow cachedShadow(10.0, Offset(1.0, 2.0), Color(0xff000000), ShadowStyle::OuterDefaultXS);
    uint32_t key = (static_cast<uint32_t>(ColorMode::LIGHT) << 8) +
                   static_cast<uint32_t>(ShadowStyle::OuterDefaultXS);
    theme->shadowStyles_[key] = cachedShadow;
    theme->SetThemeStyle(themeStyle);
    auto shadow = theme->GetShadow(ShadowStyle::OuterDefaultXS, ColorMode::LIGHT);
    EXPECT_DOUBLE_EQ(shadow.GetBlurRadius(), 10.0);
    EXPECT_EQ(shadow.GetOffset().GetX(), 1.0);
    EXPECT_EQ(shadow.GetOffset().GetY(), 2.0);
}

/**
 * @tc.name: ShadowThemeGetShadow003
 * @tc.desc: Test GetShadow parses light and dark mode with radius
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeGetShadow003, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    // Light mode with radius (uses blur radius path)
    themeStyle->SetAttr("shadow_style_default_sm_shadow", { .type = ThemeConstantsType::DOUBLE, .value = 10.0 });
    themeStyle->SetAttr("shadow_style_default_sm_offset_x", { .type = ThemeConstantsType::DOUBLE, .value = 3.0 });
    themeStyle->SetAttr("shadow_style_default_sm_offset_y", { .type = ThemeConstantsType::DOUBLE, .value = 4.0 });
    themeStyle->SetAttr("shadow_style_default_sm_color",
        { .type = ThemeConstantsType::COLOR, .value = Color(0xff222222) });
    themeStyle->SetAttr("shadow_style_default_sm_radius", { .type = ThemeConstantsType::DOUBLE, .value = 8.0 });
    // Dark mode with elevation (radius=0, uses elevation path)
    themeStyle->SetAttr("shadow_style_default_sm_shadow_dark", { .type = ThemeConstantsType::DOUBLE, .value = 12.0 });
    themeStyle->SetAttr("shadow_style_default_sm_offset_x_dark", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    themeStyle->SetAttr("shadow_style_default_sm_offset_y_dark", { .type = ThemeConstantsType::DOUBLE, .value = 5.0 });
    themeStyle->SetAttr("shadow_style_default_sm_color_dark",
        { .type = ThemeConstantsType::COLOR, .value = Color(0xff111111) });
    themeStyle->SetAttr("shadow_style_default_sm_radius_dark", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    theme->SetThemeStyle(themeStyle);
    // Light: non-zero radius -> blur radius path
    auto lightShadow = theme->GetShadow(ShadowStyle::OuterDefaultSM, ColorMode::LIGHT);
    EXPECT_DOUBLE_EQ(lightShadow.GetBlurRadius(), 8.0);
    // Dark: zero radius -> elevation path
    auto darkShadow = theme->GetShadow(ShadowStyle::OuterDefaultSM, ColorMode::DARK);
    EXPECT_EQ(darkShadow.GetOffset().GetY(), 5.0);
}

/**
 * @tc.name: ShadowThemeGetShadow004
 * @tc.desc: Test GetShadow with OuterFloatingSM style
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeGetShadow004, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("shadow_style_floating_sm_shadow", { .type = ThemeConstantsType::DOUBLE, .value = 8.0 });
    themeStyle->SetAttr("shadow_style_floating_sm_offset_x", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    themeStyle->SetAttr("shadow_style_floating_sm_offset_y", { .type = ThemeConstantsType::DOUBLE, .value = 3.0 });
    themeStyle->SetAttr("shadow_style_floating_sm_color",
        { .type = ThemeConstantsType::COLOR, .value = Color(0x44000000) });
    themeStyle->SetAttr("shadow_style_floating_sm_radius", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    theme->SetThemeStyle(themeStyle);
    auto shadow = theme->GetShadow(ShadowStyle::OuterFloatingSM, ColorMode::LIGHT);
    EXPECT_EQ(shadow.GetOffset().GetY(), 3.0);
}

/**
 * @tc.name: ShadowThemeGetShadow005
 * @tc.desc: Test GetShadow with OuterFloatingMD style
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeGetShadow005, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("shadow_style_floating_md_shadow", { .type = ThemeConstantsType::DOUBLE, .value = 15.0 });
    themeStyle->SetAttr("shadow_style_floating_md_offset_x", { .type = ThemeConstantsType::DOUBLE, .value = 1.0 });
    themeStyle->SetAttr("shadow_style_floating_md_offset_y", { .type = ThemeConstantsType::DOUBLE, .value = 6.0 });
    themeStyle->SetAttr("shadow_style_floating_md_color",
        { .type = ThemeConstantsType::COLOR, .value = Color(0x66000000) });
    themeStyle->SetAttr("shadow_style_floating_md_radius", { .type = ThemeConstantsType::DOUBLE, .value = 12.0 });
    theme->SetThemeStyle(themeStyle);
    auto shadow = theme->GetShadow(ShadowStyle::OuterFloatingMD, ColorMode::LIGHT);
    EXPECT_DOUBLE_EQ(shadow.GetBlurRadius(), 12.0);
    EXPECT_EQ(shadow.GetOffset().GetX(), 1.0);
    EXPECT_EQ(shadow.GetOffset().GetY(), 6.0);
}

/**
 * @tc.name: ShadowThemeGetShadow006
 * @tc.desc: Test GetShadow multiple calls populate and use cache
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeGetShadow006, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("shadow_style_default_lg_shadow", { .type = ThemeConstantsType::DOUBLE, .value = 20.0 });
    themeStyle->SetAttr("shadow_style_default_lg_offset_x", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    themeStyle->SetAttr("shadow_style_default_lg_offset_y", { .type = ThemeConstantsType::DOUBLE, .value = 5.0 });
    themeStyle->SetAttr("shadow_style_default_lg_color",
        { .type = ThemeConstantsType::COLOR, .value = Color(0x55000000) });
    themeStyle->SetAttr("shadow_style_default_lg_radius", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    theme->SetThemeStyle(themeStyle);
    auto shadow1 = theme->GetShadow(ShadowStyle::OuterDefaultLG, ColorMode::LIGHT);
    auto shadow2 = theme->GetShadow(ShadowStyle::OuterDefaultLG, ColorMode::LIGHT);
    EXPECT_EQ(shadow1.GetOffset().GetY(), shadow2.GetOffset().GetY());
    // Verify cache was populated
    uint32_t key = (static_cast<uint32_t>(ColorMode::LIGHT) << 8) +
                   static_cast<uint32_t>(ShadowStyle::OuterDefaultLG);
    EXPECT_EQ(theme->shadowStyles_.size(), 1u);
    EXPECT_NE(theme->shadowStyles_.find(key), theme->shadowStyles_.end());
}

/**
 * @tc.name: ShadowThemeGetShadow007
 * @tc.desc: Test GetShadow with OuterDefaultMD style and default values
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeGetShadow007, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    // Only set some attributes, others will use defaults (0.0)
    themeStyle->SetAttr("shadow_style_default_md_shadow", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    themeStyle->SetAttr("shadow_style_default_md_offset_x", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    themeStyle->SetAttr("shadow_style_default_md_offset_y", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    themeStyle->SetAttr("shadow_style_default_md_color",
        { .type = ThemeConstantsType::COLOR, .value = Color(0x00000000) });
    themeStyle->SetAttr("shadow_style_default_md_radius", { .type = ThemeConstantsType::DOUBLE, .value = 0.0 });
    theme->SetThemeStyle(themeStyle);
    auto shadow = theme->GetShadow(ShadowStyle::OuterDefaultMD, ColorMode::LIGHT);
    // All defaults, elevation=0 and radius=0
    EXPECT_EQ(shadow.GetElevation(), 0.0f);
}

/**
 * @tc.name: ShadowThemeKeyGeneration001
 * @tc.desc: Test GetKeyOfShadowStyle key composition
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeKeyGeneration001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    uint32_t lightKey = theme->GetKeyOfShadowStyle(ShadowStyle::OuterDefaultXS, ColorMode::LIGHT);
    EXPECT_EQ(lightKey, (static_cast<uint32_t>(ColorMode::LIGHT) << 8) +
                        static_cast<uint32_t>(ShadowStyle::OuterDefaultXS));
    uint32_t darkKey = theme->GetKeyOfShadowStyle(ShadowStyle::OuterDefaultXS, ColorMode::DARK);
    EXPECT_NE(lightKey, darkKey);
}

/**
 * @tc.name: ShadowThemeSetThemeStyle001
 * @tc.desc: Test SetThemeStyle stores themeStyle
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, ShadowThemeSetThemeStyle001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<ShadowTheme>();
    EXPECT_EQ(theme->themeStyle_, nullptr);
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    theme->SetThemeStyle(themeStyle);
    EXPECT_EQ(theme->themeStyle_, themeStyle);
}

// ============================================================================
// BlurStyleTheme
// ============================================================================

/**
 * @tc.name: BlurStyleThemeBuilder001
 * @tc.desc: Test BlurStyleTheme::Builder::Build with null ThemeConstants
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeBuilder001, TestSize.Level1)
{
    BlurStyleTheme::Builder builder;
    auto theme = builder.Build(nullptr);
    ASSERT_NE(theme, nullptr);
    auto param = theme->GetBlurParameter(BlurStyle::THIN, ThemeColorMode::LIGHT);
    EXPECT_FALSE(param.has_value());
}

/**
 * @tc.name: BlurStyleThemeBuilder002
 * @tc.desc: Test BlurStyleTheme::Builder::Build with ThemeConstants containing blur pattern
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeBuilder002, TestSize.Level1)
{
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    auto blurStyle = AceType::MakeRefPtr<ThemeStyle>();
    blurStyle->SetAttr("blur_style_thin_radius", { .type = ThemeConstantsType::DOUBLE, .value = 20.0 });
    blurStyle->SetAttr("blur_style_thin_saturation", { .type = ThemeConstantsType::DOUBLE, .value = 1.0 });
    blurStyle->SetAttr("blur_style_thin_brightness", { .type = ThemeConstantsType::DOUBLE, .value = 0.5 });
    blurStyle->SetAttr("blur_style_thin_color", { .type = ThemeConstantsType::COLOR, .value = Color::WHITE });
    ResValueWrapper patternValue { .type = ThemeConstantsType::PATTERN, .value = blurStyle };
    themeStyle->SetAttr("blur_style_common", patternValue);
    themeConstants->currentThemeStyle_ = themeStyle;
    BlurStyleTheme::Builder builder;
    auto theme = builder.Build(themeConstants);
    ASSERT_NE(theme, nullptr);
    auto param = theme->GetBlurParameter(BlurStyle::THIN, ThemeColorMode::LIGHT);
    ASSERT_TRUE(param.has_value());
    EXPECT_FLOAT_EQ(param->radius, 20.0f);
}

/**
 * @tc.name: BlurStyleThemeBuilder003
 * @tc.desc: Test BlurStyleTheme::Builder::Build with ThemeConstants but no blur pattern
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeBuilder003, TestSize.Level1)
{
    auto themeConstants = AceType::MakeRefPtr<ThemeConstants>(nullptr);
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeConstants->currentThemeStyle_ = themeStyle;
    BlurStyleTheme::Builder builder;
    auto theme = builder.Build(themeConstants);
    ASSERT_NE(theme, nullptr);
    auto param = theme->GetBlurParameter(BlurStyle::THIN, ThemeColorMode::LIGHT);
    EXPECT_FALSE(param.has_value());
}

/**
 * @tc.name: BlurStyleThemeGetParam001
 * @tc.desc: Test GetBlurParameter with invalid/null states returns nullopt
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeGetParam001, TestSize.Level1)
{
    // Invalid style
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    theme->SetThemeStyle(themeStyle);
    auto param = theme->GetBlurParameter(static_cast<BlurStyle>(999), ThemeColorMode::LIGHT);
    EXPECT_FALSE(param.has_value());
    // Null themeStyle_
    auto theme2 = AceType::MakeRefPtr<BlurStyleTheme>();
    auto param2 = theme2->GetBlurParameter(BlurStyle::THIN, ThemeColorMode::LIGHT);
    EXPECT_FALSE(param2.has_value());
}

/**
 * @tc.name: BlurStyleThemeGetParam002
 * @tc.desc: Test GetBlurParameter cache hit returns cached value
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeGetParam002, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    BlurParameter cachedParam;
    cachedParam.radius = 15.0f;
    cachedParam.saturation = 1.5f;
    cachedParam.maskColor = Color(0x80000000);
    cachedParam.brightness = 0.8f;
    uint32_t key = (static_cast<uint32_t>(ThemeColorMode::LIGHT) << 8) +
                   static_cast<uint32_t>(BlurStyle::THIN);
    theme->blurParams_[key] = cachedParam;
    theme->SetThemeStyle(themeStyle);
    auto param = theme->GetBlurParameter(BlurStyle::THIN, ThemeColorMode::LIGHT);
    ASSERT_TRUE(param.has_value());
    EXPECT_FLOAT_EQ(param->radius, 15.0f);
    EXPECT_FLOAT_EQ(param->saturation, 1.5f);
    EXPECT_FLOAT_EQ(param->brightness, 0.8f);
}

/**
 * @tc.name: BlurStyleThemeGetParam003
 * @tc.desc: Test GetBlurParameter parses light and dark mode correctly
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeGetParam003, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    // Light mode for "thick" style
    themeStyle->SetAttr("blur_style_thick_radius", { .type = ThemeConstantsType::DOUBLE, .value = 40.0 });
    themeStyle->SetAttr("blur_style_thick_saturation", { .type = ThemeConstantsType::DOUBLE, .value = 1.0 });
    themeStyle->SetAttr("blur_style_thick_brightness", { .type = ThemeConstantsType::DOUBLE, .value = 0.6 });
    themeStyle->SetAttr("blur_style_thick_color", { .type = ThemeConstantsType::COLOR, .value = Color::WHITE });
    // Dark mode for "thick" style
    themeStyle->SetAttr("blur_style_thick_radius_dark", { .type = ThemeConstantsType::DOUBLE, .value = 50.0 });
    themeStyle->SetAttr("blur_style_thick_saturation_dark", { .type = ThemeConstantsType::DOUBLE, .value = 1.5 });
    themeStyle->SetAttr("blur_style_thick_brightness_dark", { .type = ThemeConstantsType::DOUBLE, .value = 0.4 });
    themeStyle->SetAttr("blur_style_thick_color_dark", { .type = ThemeConstantsType::COLOR, .value = Color::BLACK });
    theme->SetThemeStyle(themeStyle);
    auto lightParam = theme->GetBlurParameter(BlurStyle::THICK, ThemeColorMode::LIGHT);
    auto darkParam = theme->GetBlurParameter(BlurStyle::THICK, ThemeColorMode::DARK);
    ASSERT_TRUE(lightParam.has_value());
    ASSERT_TRUE(darkParam.has_value());
    EXPECT_FLOAT_EQ(lightParam->radius, 40.0f);
    EXPECT_FLOAT_EQ(darkParam->radius, 50.0f);
}

/**
 * @tc.name: BlurStyleThemeGetParam004
 * @tc.desc: Test GetBlurParameter with BACKGROUND_THIN style
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeGetParam004, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("blur_style_background_thin_radius",
        { .type = ThemeConstantsType::DOUBLE, .value = 10.0 });
    themeStyle->SetAttr("blur_style_background_thin_saturation",
        { .type = ThemeConstantsType::DOUBLE, .value = 1.2 });
    themeStyle->SetAttr("blur_style_background_thin_brightness",
        { .type = ThemeConstantsType::DOUBLE, .value = 0.7 });
    themeStyle->SetAttr("blur_style_background_thin_color",
        { .type = ThemeConstantsType::COLOR, .value = Color::WHITE });
    theme->SetThemeStyle(themeStyle);
    auto param = theme->GetBlurParameter(BlurStyle::BACKGROUND_THIN, ThemeColorMode::LIGHT);
    ASSERT_TRUE(param.has_value());
    EXPECT_FLOAT_EQ(param->radius, 10.0f);
}

/**
 * @tc.name: BlurStyleThemeGetParam005
 * @tc.desc: Test GetBlurParameter with COMPONENT_ULTRA_THIN style
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeGetParam005, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("blur_style_component_ultra_thin_radius",
        { .type = ThemeConstantsType::DOUBLE, .value = 5.0 });
    themeStyle->SetAttr("blur_style_component_ultra_thin_saturation",
        { .type = ThemeConstantsType::DOUBLE, .value = 1.0 });
    themeStyle->SetAttr("blur_style_component_ultra_thin_brightness",
        { .type = ThemeConstantsType::DOUBLE, .value = 0.9 });
    themeStyle->SetAttr("blur_style_component_ultra_thin_color",
        { .type = ThemeConstantsType::COLOR, .value = Color::WHITE });
    theme->SetThemeStyle(themeStyle);
    auto param = theme->GetBlurParameter(BlurStyle::COMPONENT_ULTRA_THIN, ThemeColorMode::LIGHT);
    ASSERT_TRUE(param.has_value());
    EXPECT_FLOAT_EQ(param->radius, 5.0f);
    EXPECT_FLOAT_EQ(param->brightness, 0.9f);
}

/**
 * @tc.name: BlurStyleThemeGetParam006
 * @tc.desc: Test GetBlurParameter with BACKGROUND_ULTRA_THICK style
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeGetParam006, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("blur_style_background_ultra_thick_radius",
        { .type = ThemeConstantsType::DOUBLE, .value = 60.0 });
    themeStyle->SetAttr("blur_style_background_ultra_thick_saturation",
        { .type = ThemeConstantsType::DOUBLE, .value = 2.5 });
    themeStyle->SetAttr("blur_style_background_ultra_thick_brightness",
        { .type = ThemeConstantsType::DOUBLE, .value = 0.2 });
    themeStyle->SetAttr("blur_style_background_ultra_thick_color",
        { .type = ThemeConstantsType::COLOR, .value = Color::BLACK });
    theme->SetThemeStyle(themeStyle);
    auto param = theme->GetBlurParameter(BlurStyle::BACKGROUND_ULTRA_THICK, ThemeColorMode::LIGHT);
    ASSERT_TRUE(param.has_value());
    EXPECT_FLOAT_EQ(param->radius, 60.0f);
    EXPECT_FLOAT_EQ(param->saturation, 2.5f);
}

/**
 * @tc.name: BlurStyleThemeGetParam007
 * @tc.desc: Test GetBlurParameter multiple calls populate and use cache
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeGetParam007, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    themeStyle->SetAttr("blur_style_regular_radius", { .type = ThemeConstantsType::DOUBLE, .value = 25.0 });
    themeStyle->SetAttr("blur_style_regular_saturation", { .type = ThemeConstantsType::DOUBLE, .value = 1.3 });
    themeStyle->SetAttr("blur_style_regular_brightness", { .type = ThemeConstantsType::DOUBLE, .value = 0.5 });
    themeStyle->SetAttr("blur_style_regular_color", { .type = ThemeConstantsType::COLOR, .value = Color::WHITE });
    theme->SetThemeStyle(themeStyle);
    auto param1 = theme->GetBlurParameter(BlurStyle::REGULAR, ThemeColorMode::LIGHT);
    auto param2 = theme->GetBlurParameter(BlurStyle::REGULAR, ThemeColorMode::LIGHT);
    ASSERT_TRUE(param1.has_value());
    ASSERT_TRUE(param2.has_value());
    EXPECT_FLOAT_EQ(param1->radius, param2->radius);
    EXPECT_EQ(theme->blurParams_.size(), 1u);
}

/**
 * @tc.name: BlurStyleThemeKeyGeneration001
 * @tc.desc: Test GetKeyOfBlurStyle key composition
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeKeyGeneration001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    uint32_t lightKey = theme->GetKeyOfBlurStyle(BlurStyle::THIN, ThemeColorMode::LIGHT);
    EXPECT_EQ(lightKey, (static_cast<uint32_t>(ThemeColorMode::LIGHT) << 8) +
                        static_cast<uint32_t>(BlurStyle::THIN));
    uint32_t darkKey = theme->GetKeyOfBlurStyle(BlurStyle::THIN, ThemeColorMode::DARK);
    EXPECT_NE(lightKey, darkKey);
    uint32_t regularKey = theme->GetKeyOfBlurStyle(BlurStyle::REGULAR, ThemeColorMode::LIGHT);
    EXPECT_NE(lightKey, regularKey);
}

/**
 * @tc.name: BlurStyleThemeSetThemeStyle001
 * @tc.desc: Test SetThemeStyle stores themeStyle
 * @tc.type: FUNC
 */
HWTEST_F(ThemeTest, BlurStyleThemeSetThemeStyle001, TestSize.Level1)
{
    auto theme = AceType::MakeRefPtr<BlurStyleTheme>();
    EXPECT_EQ(theme->themeStyle_, nullptr);
    auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
    theme->SetThemeStyle(themeStyle);
    EXPECT_EQ(theme->themeStyle_, themeStyle);
}

} // namespace OHOS::Ace::NG
