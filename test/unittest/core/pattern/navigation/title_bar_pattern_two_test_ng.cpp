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
#include "mock_navigation_route.h"

#define protected public
#define private public

#include "core/common/ace_application_info.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navdestination_layout_property_base.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/token_theme/token_theme.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/components_ng/token_theme/token_colors.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t TEST_LUMINANCE_LOW = 100;
constexpr uint32_t TEST_LUMINANCE_HIGH = 250;
constexpr double TEST_SCROLL_SCALE_MID = 0.5;
constexpr size_t TEST_DEFAULT_GRADIENT_STOP_COUNT = 22;
constexpr size_t TEST_SMOOTH_GRADIENT_STOP_COUNT = 21;
constexpr int32_t TEST_THEME_ID_BASE = 10000;
constexpr int32_t TEST_THEME_SCOPE_ID_BASE = 20000;
constexpr int32_t TEST_MASK_ZINDEX = -1;
constexpr int32_t TEST_MASK_BLUR_ZINDEX = -2;
const Color TEST_LIGHT_BG_GRAY = Color(0xFFF5F5F5);
const Color TEST_DARK_BG_GRAY = Color(0xFF202020);
const Color TEST_LIGHT_BG_TERTIARY = Color(0xFFE7E7E7);
const Color TEST_DARK_BG_TERTIARY = Color(0xFF303030);
const Color TEST_LIGHT_FONT = Color(0xFF111111);
const Color TEST_DARK_FONT = Color(0xFFF2F2F2);
const Color TEST_LIGHT_ICON = Color(0xFF2A2A2A);
const Color TEST_DARK_ICON = Color(0xFFEAEAEA);

class ScopeUiMaterialLevel {
public:
    explicit ScopeUiMaterialLevel(UiMaterialLevel level)
    {
        backupLevel_ = g_uiMaterialLevel;
        g_uiMaterialLevel = level;
    }
    ~ScopeUiMaterialLevel()
    {
        g_uiMaterialLevel = backupLevel_;
    }

private:
    UiMaterialLevel backupLevel_;
};

class ScopeUIMaterialState {
public:
    explicit ScopeUIMaterialState(const std::string& state)
    {
        backupState_ = AceApplicationInfo::GetInstance().GetUIMaterialState();
        AceApplicationInfo::GetInstance().SetUIMaterialState(state);
    }
    ~ScopeUIMaterialState()
    {
        AceApplicationInfo::GetInstance().SetUIMaterialState(backupState_);
    }

private:
    std::string backupState_;
};

RefPtr<TitleBarNode> CreateTitleBarNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        nodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    node->InitializePatternAndContext();
    return node;
}

RefPtr<NavBarNode> CreateNavBarNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = NavBarNode::GetOrCreateNavBarNode(
        V2::NAVBAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    node->InitializePatternAndContext();
    return node;
}

RefPtr<FrameNode> CreateSymbolNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    node->InitializePatternAndContext();
    return node;
}

RefPtr<FrameNode> CreateImageNode(bool isSvg)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    auto layoutProperty = node->GetLayoutProperty<ImageLayoutProperty>();
    if (layoutProperty) {
        ImageSourceInfo imageSourceInfo;
        if (isSvg) {
            imageSourceInfo.SetSrc("test.svg");
        } else {
            imageSourceInfo.SetSrc("test.png");
        }
        layoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    }
    node->InitializePatternAndContext();
    return node;
}

RefPtr<FrameNode> CreateFramePatternNode(const std::string& tag)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<Pattern>());
    node->InitializePatternAndContext();
    return node;
}

std::vector<Color> CreateScrollEffectTokenColors(
    const Color& bgGray, const Color& bgTertiary, const Color& font, const Color& icon)
{
    std::vector<Color> colors(TokenColors::TOTAL_NUMBER, Color::TRANSPARENT);
    colors[TokenColors::COMP_BACKGROUND_GRAY] = bgGray;
    colors[TokenColors::COMP_BACKGROUND_TERTIARY] = bgTertiary;
    colors[TokenColors::FONT_PRIMARY] = font;
    colors[TokenColors::ICON_PRIMARY] = icon;
    return colors;
}

class ScopedTitleBarTokenTheme {
public:
    explicit ScopedTitleBarTokenTheme(const RefPtr<TitleBarNode>& titleBarNode)
        : storage_(TokenThemeStorage::GetInstance()),
          backupColorMode_(MockContainer::GetMockColorMode()),
          themeId_(TEST_THEME_ID_BASE + ElementRegister::GetInstance()->MakeUniqueId()),
          themeScopeId_(TEST_THEME_SCOPE_ID_BASE + ElementRegister::GetInstance()->MakeUniqueId())
    {
        CHECK_NULL_VOID(titleBarNode);
        auto lightColors = AceType::MakeRefPtr<TokenColors>();
        lightColors->SetColors(CreateScrollEffectTokenColors(
            TEST_LIGHT_BG_GRAY, TEST_LIGHT_BG_TERTIARY, TEST_LIGHT_FONT, TEST_LIGHT_ICON));
        auto darkColors = AceType::MakeRefPtr<TokenColors>();
        darkColors->SetColors(
            CreateScrollEffectTokenColors(TEST_DARK_BG_GRAY, TEST_DARK_BG_TERTIARY, TEST_DARK_FONT, TEST_DARK_ICON));
        theme_ = AceType::MakeRefPtr<TokenTheme>(themeId_);
        theme_->SetColors(lightColors);
        theme_->SetDarkColors(darkColors);
        storage_->CacheSet(theme_);
        storage_->StoreThemeScope(themeScopeId_, themeId_);
        titleBarNode->SetThemeScopeId(themeScopeId_);
    }

    ~ScopedTitleBarTokenTheme()
    {
        storage_->RemoveThemeScope(themeScopeId_, true);
        MockContainer::SetMockColorMode(backupColorMode_);
    }

    void SetColorMode(ColorMode mode) const
    {
        CHECK_NULL_VOID(theme_);
        theme_->SetColorMode(mode);
        MockContainer::SetMockColorMode(mode);
    }

private:
    TokenThemeStorage* storage_ = nullptr;
    ColorMode backupColorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
    RefPtr<TokenTheme> theme_;
    int32_t themeId_ = 0;
    int32_t themeScopeId_ = 0;
};

struct ScrollEffectTestContext {
    RefPtr<NavBarNode> navBarNode;
    RefPtr<TitleBarNode> titleBarNode;
    RefPtr<TitleBarPattern> titleBarPattern;
    RefPtr<FrameNode> maskNode;
    RefPtr<FrameNode> maskBlurNode;
};

ScrollEffectTestContext CreateScrollEffectTestContext(ScrollEffectType scrollEffectType)
{
    ScrollEffectTestContext context;
    context.navBarNode = CreateNavBarNode();
    context.titleBarNode = CreateTitleBarNode();
    context.titleBarPattern = context.titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(context.navBarNode && context.titleBarNode && context.titleBarPattern, context);
    context.navBarNode->SetTitleBarNode(context.titleBarNode);
    context.navBarNode->AddChild(context.titleBarNode);
    context.titleBarPattern->options_.bgOptions.scrollEffectOptions = ScrollEffectOptions();
    context.titleBarPattern->options_.bgOptions.scrollEffectOptions->scrollEffectType = scrollEffectType;
    return context;
}

void InitScrollEffectForContext(ScrollEffectTestContext& context)
{
    ASSERT_NE(context.titleBarPattern, nullptr);
    context.titleBarPattern->InitScrollEffectOptions();
    context.maskNode = context.titleBarPattern->GetTitleBarMaskNode();
    context.maskBlurNode = context.titleBarPattern->GetTitleBarMaskBlurNode();
    ASSERT_NE(context.maskNode, nullptr);
    ASSERT_NE(context.maskBlurNode, nullptr);
}

void SetHideTitleBar(const ScrollEffectTestContext& context, bool hide)
{
    ASSERT_NE(context.navBarNode, nullptr);
    auto layoutProperty = context.navBarNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideTitleBar(hide);
}

void ReparentNode(const RefPtr<FrameNode>& node, const RefPtr<UINode>& newParent)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(newParent);
    auto parent = node->GetParent();
    if (parent) {
        parent->RemoveChild(node);
        node->MountToParent(nullptr);
    }
    newParent->AddChild(node);
}

double GetScrollEffectOpacity(const RefPtr<TitleBarPattern>& titleBarPattern)
{
    CHECK_NULL_RETURN(titleBarPattern, 0.0);
    auto startOpacity = titleBarPattern->GetOriginalTitleBarBgStyle().backgroundStyle.opacity;
    auto endOpacity = titleBarPattern->GetScrollEffectTitleBarBgStyle().backgroundStyle.opacity;
    return startOpacity + titleBarPattern->GetScrollScale() * (endOpacity - startOpacity);
}

std::vector<std::pair<float, float>> GetGradientFractionStops(const RefPtr<TitleBarPattern>& titleBarPattern)
{
    if (!titleBarPattern) {
        return {};
    }
    auto gradientBlurOpt = titleBarPattern->GetOriginalTitleBarBgStyle().backgroundStyle.linearGradientBlur;
    EXPECT_TRUE(gradientBlurOpt.has_value());
    return gradientBlurOpt.has_value() ? gradientBlurOpt->fractionStops_ : std::vector<std::pair<float, float>> {};
}

void ExpectSafeAreaExpandTop(const RefPtr<FrameNode>& node)
{
    ASSERT_NE(node, nullptr);
    auto layoutProperty = node->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(layoutProperty->GetSafeAreaExpandOpts(), nullptr);
    EXPECT_EQ(layoutProperty->GetSafeAreaExpandOpts()->type, SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT);
    EXPECT_EQ(layoutProperty->GetSafeAreaExpandOpts()->edges, SAFE_AREA_EDGE_TOP);
}

void ExpectEffectNodeState(const RefPtr<FrameNode>& node, const RefPtr<TitleBarNode>& titleBarNode, int32_t zIndex)
{
    ASSERT_NE(node, nullptr);
    auto parentNode = node->GetParent();
    EXPECT_EQ(AceType::RawPtr(parentNode), AceType::RawPtr(titleBarNode));
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetZIndexValue(0), zIndex);
    ExpectSafeAreaExpandTop(node);
}

void ExpectShadowColor(const std::optional<std::vector<Shadow>>& shadows, const Color& color)
{
    ASSERT_TRUE(shadows.has_value());
    ASSERT_FALSE(shadows->empty());
    EXPECT_EQ(shadows->front().GetColor(), color);
}

void ExpectGradientMatchesColor(const Gradient& gradient, const Color& baseColor, double opacity,
    const std::vector<std::pair<float, float>>& fractionStops)
{
    ASSERT_NE(gradient.GetLinearGradient(), nullptr);
    ASSERT_TRUE(gradient.GetLinearGradient()->linearY.has_value());
    EXPECT_EQ(gradient.GetLinearGradient()->linearY.value(), GradientDirection::BOTTOM);
    const auto& colors = gradient.GetColors();
    ASSERT_EQ(colors.size(), fractionStops.size());
    auto blendedColor = baseColor.BlendOpacity(opacity);
    for (size_t i = 0; i < colors.size(); ++i) {
        EXPECT_EQ(colors[i].GetColor(), blendedColor.BlendOpacity(fractionStops[i].first));
    }
}
} // namespace

class TitleBarPatternTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TitleBarPatternTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TitleBarPatternTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: IsSymbolOrSVGIcon001
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon001, TestSize.Level1)
{
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(nullptr);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSymbolOrSVGIcon002
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is Symbol node
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon002, TestSize.Level1)
{
    auto symbolNode = CreateSymbolNode();
    ASSERT_NE(symbolNode, nullptr);
    
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(symbolNode);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSymbolOrSVGIcon003
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is Image node with SVG source
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon003, TestSize.Level1)
{
    auto imageNode = CreateImageNode(true);
    ASSERT_NE(imageNode, nullptr);
    
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(imageNode);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsSymbolOrSVGIcon004
 * @tc.desc: Test IsSymbolOrSVGIcon when iconNode is Image node with PNG source
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsSymbolOrSVGIcon004, TestSize.Level1)
{
    auto imageNode = CreateImageNode(false);
    ASSERT_NE(imageNode, nullptr);
    
    bool result = TitleBarPattern::IsSymbolOrSVGIcon(imageNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetCurrentColorMode001
 * @tc.desc: Test GetCurrentColorMode when enableColorInvert is true and isColorPickerDark_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, GetCurrentColorMode001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = true;
    
    ColorMode colorMode = titleBarPattern->GetCurrentColorMode(true);
    EXPECT_EQ(colorMode, ColorMode::DARK);
}

/**
 * @tc.name: GetCurrentColorMode002
 * @tc.desc: Test GetCurrentColorMode when enableColorInvert is true and isColorPickerDark_ is false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, GetCurrentColorMode002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = false;
    
    ColorMode colorMode = titleBarPattern->GetCurrentColorMode(true);
    EXPECT_EQ(colorMode, ColorMode::LIGHT);
}

/**
 * @tc.name: GetCurrentColorMode003
 * @tc.desc: Test GetCurrentColorMode when enableColorInvert is false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, GetCurrentColorMode003, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = std::nullopt;
    titleBarPattern->isBackgroundDark_ = true;
    
    ColorMode colorMode = titleBarPattern->GetCurrentColorMode(false);
    EXPECT_NE(colorMode, ColorMode::COLOR_MODE_UNDEFINED);
}

/**
 * @tc.name: OnLuminanceUpdate001
 * @tc.desc: Test OnLuminanceUpdate when luminance is below threshold LOW
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, OnLuminanceUpdate001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = std::nullopt;
    
    titleBarPattern->OnLuminanceUpdate(TEST_LUMINANCE_LOW);
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.has_value());
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.value());
}

/**
 * @tc.name: OnLuminanceUpdate002
 * @tc.desc: Test OnLuminanceUpdate when luminance is above threshold HIGH
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, OnLuminanceUpdate002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->isColorPickerDark_ = std::nullopt;
    
    titleBarPattern->OnLuminanceUpdate(TEST_LUMINANCE_HIGH);
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.has_value());
    EXPECT_FALSE(titleBarPattern->isColorPickerDark_.value());
}

/**
 * @tc.name: UnregisterColorPicker001
 * @tc.desc: Test UnregisterColorPicker when hasRegisterColorPicker_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, UnregisterColorPicker001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->hasRegisterColorPicker_ = true;
    titleBarPattern->isColorPickerDark_ = true;
    
    titleBarPattern->UnregisterColorPicker();
    EXPECT_FALSE(titleBarPattern->hasRegisterColorPicker_);
    EXPECT_FALSE(titleBarPattern->isColorPickerDark_.has_value());
}

/**
 * @tc.name: UnregisterColorPicker002
 * @tc.desc: Test UnregisterColorPicker when hasRegisterColorPicker_ is false
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, UnregisterColorPicker002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    
    titleBarPattern->hasRegisterColorPicker_ = false;
    titleBarPattern->isColorPickerDark_ = true;
    
    titleBarPattern->UnregisterColorPicker();
    EXPECT_FALSE(titleBarPattern->hasRegisterColorPicker_);
    EXPECT_TRUE(titleBarPattern->isColorPickerDark_.has_value());
}

/**
 * @tc.name: IsColorInvertEnabled001
 * @tc.desc: Branch: materialLevel != EXQUISITE && materialLevel != GENTLE => false
 *           IsColorInvertEnabled returns false when material level is not EXQUISITE or GENTLE
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsColorInvertEnabled001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("enable");
    ScopeUiMaterialLevel level(UiMaterialLevel::SMOOTH);
    EXPECT_FALSE(titleBarPattern->IsColorInvertEnabled());
}

/**
 * @tc.name: IsColorInvertEnabled002
 * @tc.desc: Branch: GetCurrentMaterial() returns nullptr => false
 *           IsColorInvertEnabled returns false when material is null
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsColorInvertEnabled002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("enable");
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    titleBarPattern->options_.bgOptions.scrollEffectOptions = std::nullopt;
    EXPECT_FALSE(titleBarPattern->IsColorInvertEnabled());
}

/**
 * @tc.name: IsColorInvertEnabled003
 * @tc.desc: Branch: GetCurrentMaterial() returns material but immersiveOptions is null => false
 *           IsColorInvertEnabled returns false when immersive options is null
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsColorInvertEnabled003, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("enable");
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    titleBarPattern->options_.bgOptions.scrollEffectOptions = ScrollEffectOptions();
    titleBarPattern->options_.bgOptions.scrollEffectOptions->scrollEffectType = ScrollEffectType::GRADUAL_BLUR;

    auto material = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(material, nullptr);
    titleBarPattern->gradualBlurMaterial_ = material;
    EXPECT_FALSE(titleBarPattern->IsColorInvertEnabled());
}

/**
 * @tc.name: IsColorInvertEnabled004
 * @tc.desc: Branch: immersiveOptions exists but colorInvert is false => false
 *           IsColorInvertEnabled returns false when colorInvert is disabled
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsColorInvertEnabled004, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("enable");
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    titleBarPattern->options_.bgOptions.scrollEffectOptions = ScrollEffectOptions();
    titleBarPattern->options_.bgOptions.scrollEffectOptions->scrollEffectType = ScrollEffectType::GRADUAL_BLUR;

    auto material = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(material, nullptr);
    ImmersiveOptions options;
    options.colorInvert = false;
    material->SetImmersiveOptions(options);
    titleBarPattern->gradualBlurMaterial_ = material;
    EXPECT_FALSE(titleBarPattern->IsColorInvertEnabled());
}

/**
 * @tc.name: IsColorInvertEnabled005
 * @tc.desc: Branch: Material is disabled via UIMaterialState => GetCurrentMaterial returns nullptr
 *           IsColorInvertEnabled returns false when material is disabled globally
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsColorInvertEnabled005, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("disable");
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    titleBarPattern->options_.bgOptions.scrollEffectOptions = ScrollEffectOptions();
    titleBarPattern->options_.bgOptions.scrollEffectOptions->scrollEffectType = ScrollEffectType::GRADUAL_BLUR;

    auto material = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(material, nullptr);
    ImmersiveOptions options;
    options.colorInvert = true;
    material->SetImmersiveOptions(options);
    titleBarPattern->gradualBlurMaterial_ = material;
    EXPECT_FALSE(titleBarPattern->IsColorInvertEnabled());
}

/**
 * @tc.name: IsColorInvertEnabled006
 * @tc.desc: Branch: Material state is "default" => MaterialUtils::IsMaterialEnabled() returns false
 *           IsColorInvertEnabled returns false when material state is default
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsColorInvertEnabled006, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("default");
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    titleBarPattern->options_.bgOptions.scrollEffectOptions = ScrollEffectOptions();
    titleBarPattern->options_.bgOptions.scrollEffectOptions->scrollEffectType = ScrollEffectType::GRADUAL_BLUR;
    EXPECT_FALSE(titleBarPattern->IsColorInvertEnabled());
}

/**
 * @tc.name: IsApplyShadowEnabled001
 * @tc.desc: Branch: material is nullptr => false
 *           IsApplyShadowEnabled returns false when material is null
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsApplyShadowEnabled001, TestSize.Level1)
{
    RefPtr<UiMaterial> nullMaterial = nullptr;
    EXPECT_FALSE(TitleBarPattern::IsApplyShadowEnabled(nullMaterial));
}

/**
 * @tc.name: IsApplyShadowEnabled002
 * @tc.desc: Branch: material->GetImmersiveOptions() returns nullptr => false
 *           IsApplyShadowEnabled returns false when immersive options is null
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsApplyShadowEnabled002, TestSize.Level1)
{
    auto material = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(material, nullptr);
    EXPECT_FALSE(TitleBarPattern::IsApplyShadowEnabled(material));
}

/**
 * @tc.name: IsApplyShadowEnabled003
 * @tc.desc: Branch: immersiveOptions exists, applyShadow is false => false
 *           IsApplyShadowEnabled returns false when applyShadow is disabled
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsApplyShadowEnabled003, TestSize.Level1)
{
    auto material = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(material, nullptr);
    ImmersiveOptions options;
    options.applyShadow = false;
    material->SetImmersiveOptions(options);
    EXPECT_FALSE(TitleBarPattern::IsApplyShadowEnabled(material));
}

/**
 * @tc.name: IsApplyShadowEnabled004
 * @tc.desc: Branch: immersiveOptions exists, applyShadow is true => true
 *           IsApplyShadowEnabled returns true when applyShadow is enabled
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsApplyShadowEnabled004, TestSize.Level1)
{
    auto material = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(material, nullptr);
    ImmersiveOptions options;
    options.applyShadow = true;
    material->SetImmersiveOptions(options);
    EXPECT_TRUE(TitleBarPattern::IsApplyShadowEnabled(material));
}

/**
 * @tc.name: IsTransparencyListenerNeeded001
 * @tc.desc: Branch: materialLevel != EXQUISITE && materialLevel != GENTLE => false
 *           IsTransparencyListenerNeeded returns false when material level is not supported
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsTransparencyListenerNeeded001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    ScopeUiMaterialLevel level(UiMaterialLevel::SMOOTH);
    EXPECT_FALSE(titleBarPattern->IsTransparencyListenerNeeded());
}

/**
 * @tc.name: IsTransparencyListenerNeeded002
 * @tc.desc: Branch: GetCurrentMaterial() returns nullptr => false
 *           IsTransparencyListenerNeeded returns false when material is null
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsTransparencyListenerNeeded002, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("enable");
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    EXPECT_FALSE(titleBarPattern->IsTransparencyListenerNeeded());
}

/**
 * @tc.name: IsTransparencyListenerNeeded003
 * @tc.desc: Branch: immersiveOptions exists but colorInvert is false => false
 *           IsTransparencyListenerNeeded returns false when colorInvert is disabled
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, IsTransparencyListenerNeeded003, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    ScopeUIMaterialState state("enable");
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    titleBarPattern->options_.bgOptions.scrollEffectOptions = ScrollEffectOptions();
    titleBarPattern->options_.bgOptions.scrollEffectOptions->scrollEffectType = ScrollEffectType::GRADUAL_BLUR;

    auto material = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(material, nullptr);
    ImmersiveOptions options;
    options.colorInvert = false;
    material->SetImmersiveOptions(options);
    titleBarPattern->gradualBlurMaterial_ = material;
    EXPECT_FALSE(titleBarPattern->IsTransparencyListenerNeeded());
}

/**
 * @tc.name: GetOrCreateGradualBlurMaterial001
 * @tc.desc: Branch: gradualBlurMaterial_ already exists => return existing material
 *           GetOrCreateGradualBlurMaterial returns cached material
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, GetOrCreateGradualBlurMaterial001, TestSize.Level1)
{
    auto titleBarNode = CreateTitleBarNode();
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    auto existingMaterial = AceType::MakeRefPtr<UiMaterial>();
    ASSERT_NE(existingMaterial, nullptr);
    titleBarPattern->gradualBlurMaterial_ = existingMaterial;

    auto result = titleBarPattern->GetOrCreateGradualBlurMaterial();
    EXPECT_EQ(result, existingMaterial);
}

/**
 * @tc.name: InitScrollEffectOptions_CommonBlur_CreatesEffectNodes
 * @tc.desc: Verify common blur init creates effect nodes with expected parent, safe area, zIndex and clip state.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, InitScrollEffectOptions_CommonBlur_CreatesEffectNodes, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);

    context.titleBarPattern->InitScrollEffectOptions();

    auto hostParentNode = context.titleBarPattern->GetHostParentNode();
    EXPECT_EQ(
        AceType::RawPtr(hostParentNode), AceType::RawPtr(context.navBarNode));
    EXPECT_TRUE(context.titleBarPattern->IsScrollEffectEnabled());
    EXPECT_EQ(
        context.titleBarPattern->GetCurrentTitleBarBgStyle(), context.titleBarPattern->GetOriginalTitleBarBgStyle());
    ExpectEffectNodeState(context.titleBarPattern->GetTitleBarMaskNode(), context.titleBarNode, TEST_MASK_ZINDEX);
    ExpectEffectNodeState(
        context.titleBarPattern->GetTitleBarMaskBlurNode(), context.titleBarNode, TEST_MASK_BLUR_ZINDEX);

    auto titleBarRenderContext = context.titleBarNode->GetRenderContext();
    ASSERT_NE(titleBarRenderContext, nullptr);
    ASSERT_TRUE(titleBarRenderContext->GetClipEdge().has_value());
    EXPECT_TRUE(titleBarRenderContext->GetClipEdge().value());
}

/**
 * @tc.name: InitScrollEffectOptions_GradualBlur_DisablesClip
 * @tc.desc: Verify gradual blur init mounts effect nodes and disables title bar clip.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, InitScrollEffectOptions_GradualBlur_DisablesClip, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::GRADUAL_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::DARK);

    context.titleBarPattern->InitScrollEffectOptions();

    EXPECT_TRUE(context.titleBarPattern->IsScrollEffectEnabled());
    ExpectEffectNodeState(context.titleBarPattern->GetTitleBarMaskNode(), context.titleBarNode, TEST_MASK_ZINDEX);
    ExpectEffectNodeState(
        context.titleBarPattern->GetTitleBarMaskBlurNode(), context.titleBarNode, TEST_MASK_BLUR_ZINDEX);

    auto titleBarRenderContext = context.titleBarNode->GetRenderContext();
    ASSERT_NE(titleBarRenderContext, nullptr);
    ASSERT_TRUE(titleBarRenderContext->GetClipEdge().has_value());
    EXPECT_FALSE(titleBarRenderContext->GetClipEdge().value());
}

/**
 * @tc.name: InitScrollEffectOptions_Disabled_RemovesEffectNodes
 * @tc.desc: Verify disabling scroll effect removes nodes, resets blend apply type and restores clip.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, InitScrollEffectOptions_Disabled_RemovesEffectNodes, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);
    InitScrollEffectForContext(context);

    context.titleBarPattern->SetScrollScale(TEST_SCROLL_SCALE_MID);
    context.titleBarPattern->UpdateBackgroundBlurStyle();

    auto oldMaskNode = context.maskNode;
    auto oldMaskBlurNode = context.maskBlurNode;
    auto oldMaskRenderContext = oldMaskNode->GetRenderContext();
    ASSERT_NE(oldMaskRenderContext, nullptr);
    ASSERT_TRUE(oldMaskRenderContext->GetBackBlendApplyType().has_value());
    EXPECT_EQ(oldMaskRenderContext->GetBackBlendApplyType().value(), BlendApplyType::OFFSCREEN);

    context.titleBarPattern->options_.bgOptions.scrollEffectOptions.reset();
    context.titleBarPattern->InitScrollEffectOptions();

    EXPECT_FALSE(context.titleBarPattern->IsScrollEffectEnabled());
    EXPECT_EQ(context.titleBarPattern->GetTitleBarMaskNode(), nullptr);
    EXPECT_EQ(context.titleBarPattern->GetTitleBarMaskBlurNode(), nullptr);
    EXPECT_EQ(oldMaskNode->GetParent(), nullptr);
    EXPECT_EQ(oldMaskBlurNode->GetParent(), nullptr);
    ASSERT_TRUE(oldMaskRenderContext->GetBackBlendApplyType().has_value());
    EXPECT_EQ(oldMaskRenderContext->GetBackBlendApplyType().value(), BlendApplyType::FAST);

    auto titleBarRenderContext = context.titleBarNode->GetRenderContext();
    ASSERT_NE(titleBarRenderContext, nullptr);
    ASSERT_TRUE(titleBarRenderContext->GetClipEdge().has_value());
    EXPECT_TRUE(titleBarRenderContext->GetClipEdge().value());
}

/**
 * @tc.name: InitScrollEffectOptions_ReattachExistingEffectNodes
 * @tc.desc: Verify existing effect nodes mounted on wrong parent are reattached to title bar.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, InitScrollEffectOptions_ReattachExistingEffectNodes, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);
    InitScrollEffectForContext(context);

    auto wrongParent = CreateFramePatternNode("WrongParent");
    ASSERT_NE(wrongParent, nullptr);
    ReparentNode(context.maskNode, wrongParent);
    ReparentNode(context.maskBlurNode, wrongParent);
    auto maskParentNode = context.maskNode->GetParent();
    EXPECT_EQ(AceType::RawPtr(maskParentNode), AceType::RawPtr(wrongParent));
    auto maskBlurParentNode = context.maskNode->GetParent();
    EXPECT_EQ(AceType::RawPtr(maskBlurParentNode), AceType::RawPtr(wrongParent));

    context.titleBarPattern->InitScrollEffectOptions();

    ExpectEffectNodeState(context.titleBarPattern->GetTitleBarMaskNode(), context.titleBarNode, TEST_MASK_ZINDEX);
    ExpectEffectNodeState(
        context.titleBarPattern->GetTitleBarMaskBlurNode(), context.titleBarNode, TEST_MASK_BLUR_ZINDEX);
}

/**
 * @tc.name: PrepareScrollEffectTitleBarBgStyles_CommonBlur_Light
 * @tc.desc: Verify common blur styles use light token colors and expected shadow/blur values.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, PrepareScrollEffectTitleBarBgStyles_CommonBlur_Light, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);

    context.titleBarPattern->PrepareScrollEffectTitleBarBgStyles(ScrollEffectType::COMMON_BLUR);

    const auto& originalStyle = context.titleBarPattern->GetOriginalTitleBarBgStyle();
    const auto& scrollEffectStyle = context.titleBarPattern->GetScrollEffectTitleBarBgStyle();
    EXPECT_EQ(originalStyle.backgroundStyle.backgroundColor, TEST_LIGHT_BG_GRAY);
    EXPECT_EQ(scrollEffectStyle.backgroundStyle.backgroundColor, TEST_LIGHT_BG_GRAY);
    EXPECT_EQ(originalStyle.iconBackgroundStyle.backgroundColor, TEST_LIGHT_BG_TERTIARY);
    EXPECT_EQ(scrollEffectStyle.iconBackgroundStyle.backgroundColor, TEST_LIGHT_BG_TERTIARY);
    EXPECT_DOUBLE_EQ(originalStyle.backgroundStyle.opacity, 1.0);
    EXPECT_DOUBLE_EQ(scrollEffectStyle.backgroundStyle.opacity, 1.0);
    EXPECT_DOUBLE_EQ(originalStyle.backgroundStyle.blurRadius.Value(), 0.0);
    EXPECT_DOUBLE_EQ(scrollEffectStyle.backgroundStyle.blurRadius.Value(), 30.0);
    EXPECT_EQ(scrollEffectStyle.backgroundStyle.blurRadius.Unit(), DimensionUnit::VP);
    ExpectShadowColor(originalStyle.titleShadow, TEST_LIGHT_BG_GRAY.ChangeOpacity(0.0));
    ExpectShadowColor(originalStyle.subTitleShadow, TEST_LIGHT_BG_GRAY.ChangeOpacity(0.0));
    ExpectShadowColor(scrollEffectStyle.titleShadow, TEST_LIGHT_BG_GRAY.ChangeOpacity(0.8));
    ExpectShadowColor(scrollEffectStyle.subTitleShadow, TEST_LIGHT_BG_GRAY.ChangeOpacity(0.8));
}

/**
 * @tc.name: PrepareScrollEffectTitleBarBgStyles_GradualBlur_Dark
 * @tc.desc: Verify gradual blur styles use dark token colors and expected gradient blur values.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, PrepareScrollEffectTitleBarBgStyles_GradualBlur_Dark, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::GRADUAL_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::DARK);

    context.titleBarPattern->PrepareScrollEffectTitleBarBgStyles(ScrollEffectType::GRADUAL_BLUR);

    const auto& originalStyle = context.titleBarPattern->GetOriginalTitleBarBgStyle();
    const auto& scrollEffectStyle = context.titleBarPattern->GetScrollEffectTitleBarBgStyle();
    EXPECT_EQ(originalStyle.backgroundStyle.backgroundColor, TEST_DARK_BG_GRAY);
    EXPECT_EQ(scrollEffectStyle.backgroundStyle.backgroundColor, TEST_DARK_BG_GRAY);
    EXPECT_DOUBLE_EQ(originalStyle.backgroundStyle.opacity, 0.0);
    EXPECT_DOUBLE_EQ(scrollEffectStyle.backgroundStyle.opacity, 0.4);

    ASSERT_TRUE(originalStyle.backgroundStyle.linearGradientBlur.has_value());
    ASSERT_TRUE(scrollEffectStyle.backgroundStyle.linearGradientBlur.has_value());
    EXPECT_EQ(
        originalStyle.backgroundStyle.linearGradientBlur->fractionStops_.size(), TEST_DEFAULT_GRADIENT_STOP_COUNT);
    EXPECT_EQ(
        scrollEffectStyle.backgroundStyle.linearGradientBlur->fractionStops_.size(), TEST_DEFAULT_GRADIENT_STOP_COUNT);
    EXPECT_EQ(originalStyle.backgroundStyle.linearGradientBlur->direction_, GradientDirection::BOTTOM);
    EXPECT_EQ(scrollEffectStyle.backgroundStyle.linearGradientBlur->direction_, GradientDirection::BOTTOM);
    EXPECT_DOUBLE_EQ(originalStyle.backgroundStyle.linearGradientBlur->blurRadius_.Value(), 0.0);
    EXPECT_EQ(originalStyle.backgroundStyle.linearGradientBlur->blurRadius_.Unit(), DimensionUnit::VP);
    EXPECT_DOUBLE_EQ(scrollEffectStyle.backgroundStyle.linearGradientBlur->blurRadius_.Value(), 12.0);
    EXPECT_EQ(scrollEffectStyle.backgroundStyle.linearGradientBlur->blurRadius_.Unit(), DimensionUnit::VP);
    ExpectShadowColor(originalStyle.titleShadow, TEST_DARK_BG_GRAY.ChangeOpacity(0.2));
    ExpectShadowColor(scrollEffectStyle.titleShadow, TEST_DARK_BG_GRAY.ChangeOpacity(0.2));
}

/**
 * @tc.name: PrepareScrollEffectTitleBarBgStyles_SmoothMaterial_UsesSmoothStops
 * @tc.desc: Verify smooth material level uses the smooth gradient stop configuration.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, PrepareScrollEffectTitleBarBgStyles_SmoothMaterial_UsesSmoothStops,
    TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::SMOOTH);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::GRADUAL_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);

    context.titleBarPattern->PrepareScrollEffectTitleBarBgStyles(ScrollEffectType::GRADUAL_BLUR);

    auto originalStops = GetGradientFractionStops(context.titleBarPattern);
    ASSERT_EQ(originalStops.size(), TEST_SMOOTH_GRADIENT_STOP_COUNT);
    EXPECT_FLOAT_EQ(originalStops.front().first, 1.0f);
    EXPECT_FLOAT_EQ(originalStops.front().second, 0.0f);
    EXPECT_FLOAT_EQ(originalStops.back().first, 0.0f);
    EXPECT_FLOAT_EQ(originalStops.back().second, 1.0f);

    ASSERT_TRUE(
        context.titleBarPattern->GetScrollEffectTitleBarBgStyle().backgroundStyle.linearGradientBlur.has_value());
    auto scrollEffectStops =
        context.titleBarPattern->GetScrollEffectTitleBarBgStyle().backgroundStyle.linearGradientBlur->fractionStops_;
    ASSERT_EQ(scrollEffectStops.size(), TEST_SMOOTH_GRADIENT_STOP_COUNT);
    EXPECT_FLOAT_EQ(scrollEffectStops.front().first, 1.0f);
    EXPECT_FLOAT_EQ(scrollEffectStops.back().first, 0.0f);
}

/**
 * @tc.name: UpdateBackgroundBlurStyle_CommonBlur_RenderSeparation
 * @tc.desc: Verify common blur keeps color on maskNode and blur on maskBlurNode.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, UpdateBackgroundBlurStyle_CommonBlur_RenderSeparation, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);
    InitScrollEffectForContext(context);

    context.titleBarPattern->SetScrollScale(TEST_SCROLL_SCALE_MID);
    context.titleBarPattern->UpdateBackgroundBlurStyle();

    auto maskRenderContext = context.maskNode->GetRenderContext();
    auto maskBlurRenderContext = context.maskBlurNode->GetRenderContext();
    ASSERT_NE(maskRenderContext, nullptr);
    ASSERT_NE(maskBlurRenderContext, nullptr);
    EXPECT_EQ(maskRenderContext->GetBackgroundColorValue(Color::TRANSPARENT), TEST_LIGHT_BG_GRAY);
    EXPECT_FALSE(maskRenderContext->GetLinearGradient().has_value());
    ASSERT_TRUE(maskRenderContext->GetBackBlendApplyType().has_value());
    EXPECT_EQ(maskRenderContext->GetBackBlendApplyType().value(), BlendApplyType::OFFSCREEN);
    EXPECT_EQ(maskBlurRenderContext->GetBackgroundColorValue(Color::RED), Color::TRANSPARENT);
}

/**
 * @tc.name: UpdateBackgroundBlurStyle_GradualBlur_RenderSeparation
 * @tc.desc: Verify gradual blur keeps gradient on maskNode and radius blur reset path on maskBlurNode.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, UpdateBackgroundBlurStyle_GradualBlur_RenderSeparation, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::GRADUAL_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::DARK);
    InitScrollEffectForContext(context);

    context.titleBarPattern->SetScrollScale(TEST_SCROLL_SCALE_MID);
    context.titleBarPattern->UpdateBackgroundBlurStyle();

    auto maskRenderContext = context.maskNode->GetRenderContext();
    auto maskBlurRenderContext = context.maskBlurNode->GetRenderContext();
    ASSERT_NE(maskRenderContext, nullptr);
    ASSERT_NE(maskBlurRenderContext, nullptr);
    EXPECT_EQ(maskRenderContext->GetBackgroundColorValue(Color::RED), Color::TRANSPARENT);
    ASSERT_TRUE(maskRenderContext->GetLinearGradient().has_value());
    ASSERT_TRUE(maskRenderContext->GetBackBlendApplyType().has_value());
    EXPECT_EQ(maskRenderContext->GetBackBlendApplyType().value(), BlendApplyType::FAST);
    EXPECT_EQ(maskBlurRenderContext->GetBackgroundColorValue(Color::RED), Color::TRANSPARENT);
}

/**
 * @tc.name: UpdateBackgroundBlurStyle_Disabled_NoMutation
 * @tc.desc: Verify disabled scroll effect does not mutate existing render state.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, UpdateBackgroundBlurStyle_Disabled_NoMutation, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);
    InitScrollEffectForContext(context);

    auto maskRenderContext = context.maskNode->GetRenderContext();
    auto maskBlurRenderContext = context.maskBlurNode->GetRenderContext();
    ASSERT_NE(maskRenderContext, nullptr);
    ASSERT_NE(maskBlurRenderContext, nullptr);
    maskRenderContext->UpdateBackgroundColor(Color::BLUE);
    maskBlurRenderContext->UpdateBackgroundColor(Color::GREEN);
    context.titleBarPattern->isScrollEffectEnabled_ = false;

    context.titleBarPattern->UpdateBackgroundBlurStyle();

    EXPECT_EQ(maskRenderContext->GetBackgroundColorValue(Color::TRANSPARENT), Color::BLUE);
    EXPECT_EQ(maskBlurRenderContext->GetBackgroundColorValue(Color::TRANSPARENT), Color::GREEN);
}

/**
 * @tc.name: ApplyTitleBarBgStyle_Hidden_NoUpdate
 * @tc.desc: Verify hidden title bar blocks style application and keeps current render state unchanged.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, ApplyTitleBarBgStyle_Hidden_NoUpdate, TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::LIGHT);
    InitScrollEffectForContext(context);

    context.titleBarPattern->SetScrollScale(TEST_SCROLL_SCALE_MID);
    context.titleBarPattern->UpdateBackgroundBlurStyle();

    auto originalStyle = context.titleBarPattern->GetCurrentTitleBarBgStyle();
    auto maskRenderContext = context.maskNode->GetRenderContext();
    ASSERT_NE(maskRenderContext, nullptr);
    auto beforeBackgroundColor = maskRenderContext->GetBackgroundColorValue(Color::TRANSPARENT);
    SetHideTitleBar(context, true);

    auto customStyle = originalStyle;
    customStyle.backgroundStyle.backgroundColor = Color::RED;
    context.titleBarPattern->ApplyTitleBarBgStyle(customStyle);

    EXPECT_EQ(context.titleBarPattern->GetCurrentTitleBarBgStyle(), originalStyle);
    EXPECT_EQ(maskRenderContext->GetBackgroundColorValue(Color::TRANSPARENT), beforeBackgroundColor);
}

/**
 * @tc.name: OnColorConfigurationUpdate_GradualBlur_MidScroll_KeepsExistingLinearGradient
 * @tc.desc: Verify gradual blur mask gradient keeps the existing render state during theme switch at mid scroll.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, OnColorConfigurationUpdate_GradualBlur_MidScroll_KeepsExistingLinearGradient,
    TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::GRADUAL_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::DARK);
    InitScrollEffectForContext(context);

    context.titleBarPattern->SetScrollScale(TEST_SCROLL_SCALE_MID);
    context.titleBarPattern->UpdateBackgroundBlurStyle();

    auto beforeGradientOpt = context.maskNode->GetRenderContext()->GetLinearGradient();
    ASSERT_TRUE(beforeGradientOpt.has_value());
    auto beforeGradient = beforeGradientOpt.value();
    auto fractionStops = GetGradientFractionStops(context.titleBarPattern);
    auto darkOpacity = GetScrollEffectOpacity(context.titleBarPattern);
    ExpectGradientMatchesColor(beforeGradient, TEST_DARK_BG_GRAY, darkOpacity, fractionStops);

    scopedTheme.SetColorMode(ColorMode::LIGHT);
    context.titleBarPattern->OnColorConfigurationUpdate();

    auto afterGradientOpt = context.maskNode->GetRenderContext()->GetLinearGradient();
    ASSERT_TRUE(afterGradientOpt.has_value());
    auto afterGradient = afterGradientOpt.value();
    EXPECT_EQ(beforeGradient.GetColors().size(), afterGradient.GetColors().size());
    ExpectGradientMatchesColor(afterGradient, TEST_DARK_BG_GRAY, darkOpacity, fractionStops);
    EXPECT_EQ(beforeGradient.GetColors().front().GetColor(), afterGradient.GetColors().front().GetColor());
    auto maskRenderContext = context.maskNode->GetRenderContext();
    ASSERT_NE(maskRenderContext, nullptr);
    ASSERT_TRUE(maskRenderContext->GetBackBlendApplyType().has_value());
    EXPECT_EQ(maskRenderContext->GetBackBlendApplyType().value(), BlendApplyType::FAST);
}

/**
 * @tc.name: OnColorConfigurationUpdate_CommonBlur_MidScroll_KeepsExistingMaskBackgroundColor
 * @tc.desc: Verify common blur mask background keeps the existing render state during theme switch at mid scroll.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, OnColorConfigurationUpdate_CommonBlur_MidScroll_KeepsExistingMaskBackgroundColor,
    TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    auto context = CreateScrollEffectTestContext(ScrollEffectType::COMMON_BLUR);
    ASSERT_NE(context.titleBarNode, nullptr);
    ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
    scopedTheme.SetColorMode(ColorMode::DARK);
    InitScrollEffectForContext(context);

    context.titleBarPattern->SetScrollScale(TEST_SCROLL_SCALE_MID);
    context.titleBarPattern->UpdateBackgroundBlurStyle();

    auto maskRenderContext = context.maskNode->GetRenderContext();
    ASSERT_NE(maskRenderContext, nullptr);
    auto beforeBackgroundColor = maskRenderContext->GetBackgroundColorValue(Color::TRANSPARENT);
    EXPECT_EQ(beforeBackgroundColor, TEST_DARK_BG_GRAY.ChangeOpacity(GetScrollEffectOpacity(context.titleBarPattern)));

    scopedTheme.SetColorMode(ColorMode::LIGHT);
    context.titleBarPattern->OnColorConfigurationUpdate();

    auto afterBackgroundColor = maskRenderContext->GetBackgroundColorValue(Color::TRANSPARENT);
    EXPECT_EQ(afterBackgroundColor, beforeBackgroundColor);
    EXPECT_EQ(afterBackgroundColor, TEST_DARK_BG_GRAY.ChangeOpacity(GetScrollEffectOpacity(context.titleBarPattern)));
    ASSERT_TRUE(maskRenderContext->GetBackBlendApplyType().has_value());
    EXPECT_EQ(maskRenderContext->GetBackBlendApplyType().value(), BlendApplyType::OFFSCREEN);

    auto maskBlurRenderContext = context.maskBlurNode->GetRenderContext();
    ASSERT_NE(maskBlurRenderContext, nullptr);
    EXPECT_EQ(maskBlurRenderContext->GetBackgroundColorValue(Color::RED), Color::TRANSPARENT);
}

/**
 * @tc.name: OnColorConfigurationUpdate_ScrollScaleBoundary_KeepsExistingThemeColorState
 * @tc.desc: Verify gradual blur theme switching keeps the existing boundary render state.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarPatternTestTwoNg, OnColorConfigurationUpdate_ScrollScaleBoundary_KeepsExistingThemeColorState,
    TestSize.Level1)
{
    ScopeUiMaterialLevel level(UiMaterialLevel::EXQUISITE);
    const std::vector<double> scrollScales = { 0.0, 1.0 };
    for (auto scrollScale : scrollScales) {
        auto context = CreateScrollEffectTestContext(ScrollEffectType::GRADUAL_BLUR);
        ASSERT_NE(context.titleBarNode, nullptr);
        ScopedTitleBarTokenTheme scopedTheme(context.titleBarNode);
        scopedTheme.SetColorMode(ColorMode::DARK);
        InitScrollEffectForContext(context);

        context.titleBarPattern->SetScrollScale(scrollScale);
        if (scrollScale > TEST_SCROLL_SCALE_MID) {
            context.titleBarPattern->ApplyTitleBarBgStyle(context.titleBarPattern->GetScrollEffectTitleBarBgStyle());
        } else {
            context.titleBarPattern->ApplyTitleBarBgStyle(context.titleBarPattern->GetOriginalTitleBarBgStyle());
        }

        auto beforeGradientOpt = context.maskNode->GetRenderContext()->GetLinearGradient();
        ASSERT_TRUE(beforeGradientOpt.has_value());
        auto beforeGradient = beforeGradientOpt.value();
        auto fractionStops = GetGradientFractionStops(context.titleBarPattern);
        ExpectGradientMatchesColor(
            beforeGradient, TEST_DARK_BG_GRAY, GetScrollEffectOpacity(context.titleBarPattern), fractionStops);

        scopedTheme.SetColorMode(ColorMode::LIGHT);
        context.titleBarPattern->OnColorConfigurationUpdate();

        auto afterGradientOpt = context.maskNode->GetRenderContext()->GetLinearGradient();
        ASSERT_TRUE(afterGradientOpt.has_value());
        auto afterGradient = afterGradientOpt.value();
        ExpectGradientMatchesColor(
            afterGradient, TEST_DARK_BG_GRAY, GetScrollEffectOpacity(context.titleBarPattern), fractionStops);
        EXPECT_EQ(beforeGradient.GetColors().front().GetColor(), afterGradient.GetColors().front().GetColor());
        auto maskRenderContext = context.maskNode->GetRenderContext();
        ASSERT_NE(maskRenderContext, nullptr);
        ASSERT_TRUE(maskRenderContext->GetBackBlendApplyType().has_value());
        EXPECT_EQ(maskRenderContext->GetBackBlendApplyType().value(), BlendApplyType::FAST);
    }
}
} // namespace OHOS::Ace::NG
