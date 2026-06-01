/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/accessibility/accessibility_manager.h"

#include <sstream>

#include "base/i18n/localization.h"
#include "base/utils/multi_thread.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/common/visual_effect/transparency_utils.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_util.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/components_v2/inspector/utils.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui_effect/effect/include/background_color_effect_para.h"
#include "render_service_client/core/ui_effect/effect/include/brightness_blender.h"
#include "render_service_client/core/ui_effect/effect/include/visual_effect.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_ANIMATION_DURATION = 200;
constexpr int32_t TITLE_RATIO = 2;
constexpr int32_t LUMINANCE_SAMPLER_INTERVAL = 200;
constexpr uint32_t LUMINANCE_THRESHOLD_LOW = 150;
constexpr uint32_t LUMINANCE_THRESHOLD_HIGH = 220;
const Color DEFAULT_LIGHT_EFFECT_COLOR = Color::FromString("#33FFFFFF");
constexpr int32_t INVERT_COLOR_ANIMATION_DURATION = 133;

constexpr char ICON_PRIMARY_COLOR_NAME[] = "sys.color.icon_primary";
constexpr char ICON_ON_PRIMARY_COLOR_NAME[] = "sys.color.icon_on_primary";
constexpr char INTERACTIVE_HOVER_COLOR_NAME[] = "sys.color.interactive_hover";
constexpr char INTERACTIVE_PRESSED_COLOR_NAME[] = "sys.color.interactive_pressed";
constexpr char INTERACTIVE_FOCUS_COLOR_NAME[] = "sys.color.interactive_focus";
constexpr char COMP_BACKGROUND_GRAY_COLOR_NAME[] = "sys.color.comp_background_gray";

struct TitleBarTokenColors {
    Color iconPrimary;
    Color iconOnPrimary;
    Color interactiveHover;
    Color interactivePressed;
    Color interactiveFocus;
    Color compBackgroundGray;
};
struct TitleBarDefaultColors {
    TitleBarTokenColors lightColor;
    TitleBarTokenColors darkColor;
};

static std::once_flag g_initDefaultColorFlag;
static TitleBarDefaultColors g_titleBarDefaultColors;

const TitleBarTokenColors* GetOrCreateTitleBarTokenColors(const RefPtr<PipelineContext>& context, ColorMode mode)
{
    CHECK_NULL_RETURN(context, nullptr);
    std::call_once(g_initDefaultColorFlag, [weakContext = WeakPtr(context)]() {
        auto context = weakContext.Upgrade();
        CHECK_NULL_VOID(context);
        auto bundleName = context->GetBundleName();
        auto moduleName = context->GetModuleName();
        auto instanceId = context->GetInstanceId();
        auto resourceObject = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, instanceId);
        CHECK_NULL_VOID(resourceObject);
        auto adapterInCache = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
        CHECK_NULL_VOID(adapterInCache);
        ResourceConfiguration resConfig;
        resConfig.SetColorMode(ColorMode::LIGHT);
        ConfigurationChange configChange { .colorModeUpdate = true };
        auto lightResourceAdapter = adapterInCache->GetOverrideResourceAdapter(resConfig, configChange);
        CHECK_NULL_VOID(lightResourceAdapter);
        auto& lightColor = g_titleBarDefaultColors.lightColor;
        lightColor.iconPrimary = lightResourceAdapter->GetColorByName(ICON_PRIMARY_COLOR_NAME);
        lightColor.iconOnPrimary = lightResourceAdapter->GetColorByName(ICON_ON_PRIMARY_COLOR_NAME);
        lightColor.interactiveHover = lightResourceAdapter->GetColorByName(INTERACTIVE_HOVER_COLOR_NAME);
        lightColor.interactivePressed = lightResourceAdapter->GetColorByName(INTERACTIVE_PRESSED_COLOR_NAME);
        lightColor.interactiveFocus = lightResourceAdapter->GetColorByName(INTERACTIVE_FOCUS_COLOR_NAME);
        lightColor.compBackgroundGray = lightResourceAdapter->GetColorByName(COMP_BACKGROUND_GRAY_COLOR_NAME);

        resConfig.SetColorMode(ColorMode::DARK);
        auto darkResourceAdapter = adapterInCache->GetOverrideResourceAdapter(resConfig, configChange);
        CHECK_NULL_VOID(darkResourceAdapter);
        auto& darkColor = g_titleBarDefaultColors.darkColor;
        darkColor.iconPrimary = darkResourceAdapter->GetColorByName(ICON_PRIMARY_COLOR_NAME);
        darkColor.iconOnPrimary = darkResourceAdapter->GetColorByName(ICON_ON_PRIMARY_COLOR_NAME);
        darkColor.interactiveHover = darkResourceAdapter->GetColorByName(INTERACTIVE_HOVER_COLOR_NAME);
        darkColor.interactivePressed = darkResourceAdapter->GetColorByName(INTERACTIVE_PRESSED_COLOR_NAME);
        darkColor.interactiveFocus = darkResourceAdapter->GetColorByName(INTERACTIVE_FOCUS_COLOR_NAME);
        darkColor.compBackgroundGray = darkResourceAdapter->GetColorByName(COMP_BACKGROUND_GRAY_COLOR_NAME);
    });
    return mode == ColorMode::LIGHT ? &g_titleBarDefaultColors.lightColor : &g_titleBarDefaultColors.darkColor;
}

#ifdef ENABLE_ROSEN_BACKEND
struct BrightnessBlenderParam {
    float cubicRate;
    float quadRate;
    float linearRate;
    float degree;
    float saturation;
    Rosen::Vector3f positiveCoeff;
    Rosen::Vector3f negativeCoeff;
    float fraction;
};

const BrightnessBlenderParam LIGHT_ICON_FOREGROUND_BRIGHTNESS_BLENDER_PARAM = {
    0.0f, 0.0f, 0.35f, -0.1176f, 3.5f, { 0.7f, 1.7f, 0.5f }, { 1.0f, 1.0f, 1.0f }, 0.0f
};
const BrightnessBlenderParam DARK_ICON_FOREGROUND_BRIGHTNESS_BLENDER_PARAM = {
    0.0f, 0.0f, 0.1005f, 0.898f, 1.5f, { 1.0f, 0.5f, 0.5f }, { 2.0f, 2.5f, 0.5f }, 0.0f
};

std::shared_ptr<Rosen::BrightnessBlender> CreateBrightnessBlender(bool isLight)
{
    auto blender = std::make_shared<Rosen::BrightnessBlender>();
    const BrightnessBlenderParam* param = nullptr;
    if (isLight) {
        param = &LIGHT_ICON_FOREGROUND_BRIGHTNESS_BLENDER_PARAM;
    } else {
        param = &DARK_ICON_FOREGROUND_BRIGHTNESS_BLENDER_PARAM;
    }
    blender->SetCubicRate(param->cubicRate);
    blender->SetQuadRate(param->quadRate);
    blender->SetLinearRate(param->linearRate);
    blender->SetDegree(param->degree);
    blender->SetSaturation(param->saturation);
    blender->SetPositiveCoeff(param->positiveCoeff);
    blender->SetNegativeCoeff(param->negativeCoeff);
    blender->SetFraction(param->fraction);
    return blender;
}

// icon foreground
static const auto LIGHT_ICON_BRIGHTNESS_BLENDER = CreateBrightnessBlender(true);
static const auto DARK_ICON_BRIGHTNESS_BLENDER = CreateBrightnessBlender(false);
#endif

std::string TextLayoutPropertyToString(const RefPtr<TextLayoutProperty>& property)
{
    CHECK_NULL_RETURN(property, "");
    std::stringstream ss;
    auto fontSize = property->GetFontSize();
    ss << "FontSize: " << (fontSize.has_value() ? fontSize.value().ToString() : "NA") << ", ";

    auto adaptMinFontSize = property->GetAdaptMinFontSize();
    ss << "AdaptMinFontSize: " << (adaptMinFontSize.has_value() ? adaptMinFontSize.value().ToString() : "NA") << ", ";

    auto adaptMaxFontSize = property->GetAdaptMaxFontSize();
    ss << "AdaptMaxFontSize: " << (adaptMaxFontSize.has_value() ? adaptMaxFontSize.value().ToString() : "NA") << ", ";

    auto heightAdaptivePolicy = property->GetHeightAdaptivePolicy();
    ss << "TextHeightAdaptivePolicy: " << (heightAdaptivePolicy.has_value() ?
        V2::ConvertWrapTextHeightAdaptivePolicyToString(heightAdaptivePolicy.value()) : "NA") << ", ";

    auto textColor = property->GetTextColor();
    ss << "TextColor: " << (textColor.has_value() ? textColor.value().ToString() : "NA") << ", ";

    auto fontWeight = property->GetFontWeight();
    ss << "fontWeight: " << (fontWeight.has_value() ?
        V2::ConvertWrapFontWeightToStirng(fontWeight.value()) :"NA") << ", ";

    auto textShadow = property->GetTextShadow();
    ss << "TextShadow: " << (textShadow.has_value() ? "hasValue" : "NA") << ", ";

    auto maxLines = property->GetMaxLines();
    ss << "MaxLines: " << (maxLines.has_value() ? std::to_string(maxLines.value()) : "NA");

    return ss.str();
}

void DumpTitleProperty(const RefPtr<TextLayoutProperty>& property, bool isMainTitle)
{
    std::string info;
    if (isMainTitle) {
        info.append("MainTitle: ");
    } else {
        info.append("SubTitle: ");
    }
    info.append(TextLayoutPropertyToString(property));
    DumpLog::GetInstance().AddDesc(info);
}

void SetImageSourceInfoFillColor(ImageSourceInfo& imageSourceInfo)
{
    auto theme = NavigationGetTheme();
    if (theme) {
        imageSourceInfo.SetFillColor(theme->GetIconColor());
    }
}

void SetBackButtonImgAboveVersionTen(const RefPtr<FrameNode>& backButtonNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty,
    RefPtr<ImageLayoutProperty>& backButtonImageLayoutProperty)
{
    // API >= 10
    if (!backButtonNode || !titleBarLayoutProperty || !backButtonImageLayoutProperty) {
        return;
    }
    if (titleBarLayoutProperty->HasPixelMap() && titleBarLayoutProperty->GetPixelMapValue() != nullptr) {
        auto pixelMap = titleBarLayoutProperty->GetPixelMapValue();
        ImageSourceInfo imageSourceInfo = ImageSourceInfo(pixelMap);
        SetImageSourceInfoFillColor(imageSourceInfo);
        backButtonImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        backButtonNode->MarkModifyDone();
        return;
    }

    CHECK_NULL_VOID(titleBarLayoutProperty->HasImageSource());
    ImageSourceInfo imageSourceInfo = titleBarLayoutProperty->GetImageSourceValue();
    SetImageSourceInfoFillColor(imageSourceInfo);
    backButtonImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    backButtonNode->MarkModifyDone();
}

void SetBackButtonImgBelowVersionTen(const RefPtr<FrameNode>& backButtonNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty,
    RefPtr<ImageLayoutProperty>& backButtonImageLayoutProperty)
{
    // API < 10
    if (!backButtonNode || !titleBarLayoutProperty || !backButtonImageLayoutProperty) {
        return;
    }
    CHECK_NULL_VOID(titleBarLayoutProperty->HasImageSource());
    ImageSourceInfo imageSourceInfo = titleBarLayoutProperty->GetImageSourceValue();
    SetImageSourceInfoFillColor(imageSourceInfo);
    backButtonImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    backButtonNode->MarkModifyDone();
}

void HandleDefaultIconForNavDestination(
    const RefPtr<TitleBarNode>& hostNode, const RefPtr<FrameNode>& backButtonImageNode)
{
    auto navDestinationNode = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    CHECK_NULL_VOID(navDestinationNode);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto navDestinationEventHub = navDestinationNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(navDestinationEventHub);
    auto paintProperty = backButtonImageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(paintProperty);
    // If use defalut icon, need to set fill-color
    if (!navDestinationEventHub->IsEnabled()) {
        paintProperty->UpdateSvgFillColor(theme->GetBackButtonIconColor().BlendOpacity(theme->GetAlphaDisabled()));
    } else {
        paintProperty->UpdateSvgFillColor(theme->GetBackButtonIconColor());
    }
    backButtonImageNode->MarkModifyDone();
}

bool IsImageBackIcon(const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    CHECK_NULL_RETURN(titleBarLayoutProperty, false);
    if (titleBarLayoutProperty->HasIsValidImage() && titleBarLayoutProperty->GetIsValidImageValue()) {
        return true;
    }

    return false;
}

void ApplyImageSourceInfo(const RefPtr<FrameNode>& backButtonNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty,
    RefPtr<ImageLayoutProperty>& backButtonImageLayoutProperty)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        SetBackButtonImgBelowVersionTen(backButtonNode, titleBarLayoutProperty, backButtonImageLayoutProperty);
    } else {
        SetBackButtonImgAboveVersionTen(backButtonNode, titleBarLayoutProperty, backButtonImageLayoutProperty);
    }
}

void ApplyThemeIconSize(RefPtr<TextLayoutProperty>& symbolProperty)
{
    CHECK_NULL_VOID(symbolProperty);
    auto theme = NavigationGetTheme();
    if (theme) {
        symbolProperty->UpdateFontSize(theme->GetIconWidth());
    }
}

void UpdateSymbolEffect(RefPtr<TextLayoutProperty> symbolProperty, bool isActive)
{
    CHECK_NULL_VOID(symbolProperty);
    auto symbolEffectOptions = SymbolEffectOptions(SymbolEffectType::BOUNCE);
    symbolEffectOptions.SetIsTxtActive(isActive);
    symbolEffectOptions.SetIsTxtActiveSource(0);
    symbolProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
}

void UpdateSymbolBackButton(const RefPtr<TitleBarNode>& hostNode, const RefPtr<FrameNode>& backButtonNode,
    const RefPtr<FrameNode>& backButtonIconNode, const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    CHECK_NULL_VOID(hostNode);
    auto theme = NavigationGetTheme(hostNode->GetThemeScopeId());
    auto backIconSymbol = titleBarLayoutProperty->GetBackIconSymbol();
    if (backIconSymbol != nullptr) {
        // symbol -> symbol
        auto symbolProperty = backButtonIconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        symbolProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        if (theme) {
            symbolProperty->UpdateSymbolColorList({ theme->GetIconColor() });
        }
        // User-defined color overrides the default color of the theme
        backIconSymbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(backButtonIconNode)));
        ApplyThemeIconSize(symbolProperty);
        UpdateSymbolEffect(symbolProperty, false);
        backButtonIconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else if (IsImageBackIcon(titleBarLayoutProperty)) {
        // symbol -> image
        auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(backButtonImageNode);

        auto backButtonImageLayoutProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(backButtonImageLayoutProperty);
        backButtonImageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        ApplyImageSourceInfo(backButtonNode, titleBarLayoutProperty, backButtonImageLayoutProperty);
        backButtonImageNode->MountToParent(backButtonNode);
        backButtonNode->RemoveChild(backButtonIconNode);
        backButtonImageNode->MarkModifyDone();
    } else {
        auto symbolProperty = backButtonIconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        if (theme) {
            symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetBackSymbolId()));
            symbolProperty->UpdateSymbolColorList({ theme->GetBackButtonIconColor() });
            symbolProperty->UpdateFontSize(theme->GetIconWidth());
        }
        backButtonIconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void CreateDefaultBackButton(const RefPtr<FrameNode>& backButtonNode, const RefPtr<FrameNode>& backButtonIconNode)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        backButtonNode->RemoveChild(backButtonIconNode);
        auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(symbolNode);
        auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        symbolProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        auto iconColor = theme->GetIconColor();
        symbolProperty->UpdateSymbolColorList({ iconColor });
        symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetBackSymbolId()));
        symbolProperty->UpdateFontSize(theme->GetIconWidth());
        symbolNode->MountToParent(backButtonNode);
        symbolNode->MarkDirtyNode();
        symbolNode->MarkModifyDone();
    } else {
        auto backButtonImageLayoutProperty = backButtonIconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(backButtonImageLayoutProperty);

        ImageSourceInfo imageSourceInfo;
        imageSourceInfo.SetResourceId(theme->GetBackResourceId());
        imageSourceInfo.SetFillColor(theme->GetBackButtonIconColor());
        backButtonImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        backButtonImageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        backButtonIconNode->MarkModifyDone();
    }
}

void UpdateImageBackButton(const RefPtr<FrameNode>& backButtonNode, const RefPtr<FrameNode>& backButtonIconNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto backIconSymbol = titleBarLayoutProperty->GetBackIconSymbol();
    auto theme = NavigationGetTheme();
    if (backIconSymbol != nullptr) {
        // image -> symbol
        backButtonNode->RemoveChild(backButtonIconNode);
        auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(symbolNode);
        auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolProperty);
        symbolProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        if (theme) {
            symbolProperty->UpdateSymbolColorList({ theme->GetIconColor() });
        }
        backIconSymbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(symbolNode)));
        ApplyThemeIconSize(symbolProperty);
        UpdateSymbolEffect(symbolProperty, false);
        symbolNode->MountToParent(backButtonNode);
        symbolNode->MarkDirtyNode();
        symbolNode->MarkModifyDone();
    } else if (IsImageBackIcon(titleBarLayoutProperty)) {
        // image -> image
        auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(backButtonImageNode);
        CHECK_NULL_VOID(titleBarLayoutProperty->HasImageSource());
        ImageSourceInfo imageSourceInfo = titleBarLayoutProperty->GetImageSourceValue();
        auto backButtonImageLayoutProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(backButtonImageLayoutProperty);
        backButtonImageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
        ApplyImageSourceInfo(backButtonNode, titleBarLayoutProperty, backButtonImageLayoutProperty);
        backButtonImageNode->MountToParent(backButtonNode);
        backButtonNode->RemoveChild(backButtonIconNode);
        backButtonImageNode->MarkModifyDone();
    } else {
        CreateDefaultBackButton(backButtonNode, backButtonIconNode);
    }
}

void MountBackButton(const RefPtr<TitleBarNode>& hostNode)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(hostNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonIconNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    CHECK_NULL_VOID(backButtonIconNode);
    auto parentType = titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR);
    if (backButtonIconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        UpdateSymbolBackButton(hostNode, backButtonNode, backButtonIconNode, titleBarLayoutProperty);
    } else {
        UpdateImageBackButton(backButtonNode, backButtonIconNode, titleBarLayoutProperty);
    }
    std::string parentId = hostNode->GetInnerParentId();
    if (parentType == TitleBarParentType::NAVBAR) {
        auto navBarNode = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
        CHECK_NULL_VOID(navBarNode);
        auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
        CHECK_NULL_VOID(navBarLayoutProperty);
        auto hideBackButton = navBarLayoutProperty->GetHideBackButtonValue(false);
        auto backButtonLayoutProperty = AceType::DynamicCast<FrameNode>(backButtonNode)->GetLayoutProperty();
        CHECK_NULL_VOID(backButtonLayoutProperty);
        backButtonLayoutProperty->UpdateVisibility(hideBackButton ? VisibleType::GONE : VisibleType::VISIBLE);
        backButtonNode->SetJSViewActive(hideBackButton ? false : true);

        // set navigation titleBar backButton inspectorId
        NavigationTitleUtil::SetInnerChildId(backButtonNode, NG::NAV_FIELD,
            backButtonNode->GetTag(), "Back", parentId);
        backButtonNode->MarkModifyDone();
        return;
    }

    // set navdestination titleBar backButton inspectorId
    NavigationTitleUtil::SetInnerChildId(backButtonNode, NG::DES_FIELD,
        backButtonNode->GetTag(), "Back", parentId);
    if (!titleBarLayoutProperty->HasNoPixMap()) {
        if (parentType == TitleBarParentType::NAV_DESTINATION) {
            HandleDefaultIconForNavDestination(hostNode, backButtonIconNode);
        }
        backButtonNode->MarkModifyDone();
        return;
    }
}

void SetBackgroundBlurStyle(RefPtr<FrameNode>& host, const BlurStyleOption& bgBlurStyle)
{
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (bgBlurStyle.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(host->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(host->GetId());
    }
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        if (renderContext->GetBackgroundEffect().has_value()) {
            renderContext->UpdateBackgroundEffect(std::nullopt);
        }
        renderContext->UpdateBackBlurStyle(bgBlurStyle);
        if (renderContext->GetBackBlurRadius().has_value()) {
            renderContext->UpdateBackBlurRadius(Dimension());
        }
    }
}

void SetBackgroundEffect(RefPtr<FrameNode>& host, const EffectOption &effectOption)
{
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (effectOption.policy == BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) {
        pipeline->AddWindowFocusChangedCallback(host->GetId());
    } else {
        pipeline->RemoveWindowFocusChangedCallback(host->GetId());
    }
    auto renderContext = host->GetRenderContext();
    if (renderContext) {
        if (renderContext->GetBackBlurRadius().has_value()) {
            renderContext->UpdateBackBlurRadius(Dimension());
        }
        if (renderContext->GetBackBlurStyle().has_value()) {
            renderContext->UpdateBackBlurStyle(std::nullopt);
        }
        renderContext->UpdateBackgroundEffect(effectOption);
    }
}
} // namespace

void TitleBarPattern::MountSubTitle(const RefPtr<TitleBarNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto subtitleNode = AceType::DynamicCast<FrameNode>(hostNode->GetSubtitle());
    CHECK_NULL_VOID(subtitleNode);

    // set titleBar subTitle inspectorId
    auto parentType = titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR);
    std::string field = NG::NAV_FIELD;
    if (parentType == TitleBarParentType::NAV_DESTINATION) {
        field = NG::DES_FIELD;
    }
    NavigationTitleUtil::SetInnerChildId(subtitleNode, field, subtitleNode->GetTag(),
        "SubTitle", hostNode->GetInnerParentId());

    if (options_.textOptions.subTitleApplyFunc || shouldResetSubTitleProperty_) {
        auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
        ResetSubTitleProperty(subtitleNode, titleMode, parentType == TitleBarParentType::NAV_DESTINATION);
        shouldResetSubTitleProperty_ = false;
    }

    subtitleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    subtitleNode->MarkModifyDone();
}

void TitleBarPattern::InitTitleParam()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    if (titleBarNode->GetSubtitle()) {
        tempTitleBarHeight_.SetValue(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.Value());
    } else {
        tempTitleBarHeight_.SetValue(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.Value());
    }
    overDragOffset_ = 0.0f;
    tempTitleOffsetY_ = 0.0f;
    fontSize_.reset();
    opacity_.reset();
    isFreeTitleUpdated_ = false;
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    titleSpaceVertical_ = theme->GetTitleSpaceVertical();
}

bool TitleBarPattern::IsHidden()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(host->GetParent());
    CHECK_NULL_RETURN(navBarNode, false);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    CHECK_NULL_RETURN(navBarLayoutProperty, false);
    return navBarLayoutProperty->GetHideTitleBar().value_or(false);
}

void TitleBarPattern::UpdateNavBarTitleProperty(const RefPtr<TitleBarNode>& hostNode)
{
    auto titleNode = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetParent());
    CHECK_NULL_VOID(navBarNode);
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);

    // if title node is custom node markModifyDone and return
    if (navBarNode->GetPrevTitleIsCustomValue(false)) {
        titleNode->MarkModifyDone();
        return;
    }

    // set navbar titleBar main title inspectorId
    NavigationTitleUtil::SetInnerChildId(titleNode, NG::NAV_FIELD, titleNode->GetTag(),
        "MainTitle", hostNode->GetInnerParentId());

    // update main title layout property
    if (options_.textOptions.mainTitleApplyFunc || shouldResetMainTitleProperty_) {
        auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
        ResetMainTitleProperty(titleNode, titleBarLayoutProperty, titleMode, hostNode->GetSubtitle() != nullptr, false);
        shouldResetMainTitleProperty_ = false;
    }

    titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    titleNode->MarkModifyDone();
}

void TitleBarPattern::UpdateNavDesTitleProperty(const RefPtr<TitleBarNode>& hostNode)
{
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetParent());
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    CHECK_NULL_VOID(titleNode);

    // if navdestination titleBar main title is custom, just return
    if (navDestinationGroupNode->GetPrevTitleIsCustomValue(false)) {
        titleNode->MarkModifyDone();
        return;
    }
    // if navdestination titleBar main title is not custom, set inspectorId
    std::string parentId = hostNode->GetInnerParentId();
    NavigationTitleUtil::SetInnerChildId(titleNode, NG::DES_FIELD, titleNode->GetTag(),
        "MainTitle", parentId);

    if (options_.textOptions.mainTitleApplyFunc || shouldResetMainTitleProperty_) {
        auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
        ResetMainTitleProperty(titleNode, titleBarLayoutProperty, titleMode, hostNode->GetSubtitle() != nullptr, true);
        shouldResetMainTitleProperty_ = false;
    }

    titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    titleNode->MarkModifyDone();
}

void TitleBarPattern::ResetMainTitleProperty(const RefPtr<FrameNode>& textNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty,
    NavigationTitleMode titleMode, bool hasSubTitle, bool parentIsNavDest)
{
    // update main title layout property
    auto titleLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(titleLayoutProperty);

    auto host = GetHost();
    CHECK_NULL_VOID(host);

    std::u16string contentStr;
    if (titleLayoutProperty->HasContent()) {
        contentStr = titleLayoutProperty->GetContentValue(std::u16string());
    }
    titleLayoutProperty->Reset();
    titleLayoutProperty->UpdateContent(contentStr);

    auto theme = NavigationGetTheme(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    auto titleFontSize = theme->GetTitleFontSizeBig();
    auto maxFontSize = theme->GetTitleFontSizeBig();
    auto miniTitleFontSize = theme->GetTitleFontSize();
    auto miniTitleFontSizeMin = theme->GetTitleFontSizeMin();
    auto textHeightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    Color color = theme->GetTitleColor();
    FontWeight mainTitleWeight = FontWeight::MEDIUM;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        titleFontSize = theme->GetMainTitleFontSizeL();
        maxFontSize = theme->GetMainTitleFontSizeL();
        miniTitleFontSize = theme->GetMainTitleFontSizeM();
        miniTitleFontSizeMin = theme->GetMainTitleFontSizeS();
        textHeightAdaptivePolicy = hasSubTitle ? TextHeightAdaptivePolicy::MAX_LINES_FIRST :
            TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
        color = theme->GetMainTitleFontColor();
        mainTitleWeight = FontWeight::BOLD;
    }
    TitleBarPattern::SetTextColor(textNode, color);
    titleLayoutProperty->UpdateFontWeight(mainTitleWeight);
    titleLayoutProperty->UpdateMaxFontScale(STANDARD_FONT_SCALE);
    titleLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    auto maxLines = hasSubTitle ? 1 : TITLEBAR_MAX_LINES;
    titleLayoutProperty->UpdateMaxLines(maxLines);
    titleLayoutProperty->UpdateAdaptMinFontSize(MIN_ADAPT_TITLE_FONT_SIZE);
    NavigationTitleUtil::InitTextProperty(titleLayoutProperty);

    if (!parentIsNavDest) {
        titleLayoutProperty->UpdateHeightAdaptivePolicy(textHeightAdaptivePolicy);
    }

    if (parentIsNavDest) {
        titleLayoutProperty->ResetFontSize();
        titleLayoutProperty->UpdateAdaptMaxFontSize(miniTitleFontSizeMin);
        titleLayoutProperty->UpdateHeightAdaptivePolicy(hasSubTitle ? TextHeightAdaptivePolicy::MAX_LINES_FIRST :
            TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
        titleLayoutProperty->UpdateAdaptMinFontSize(theme->NavigationMiniMinFontSize());
    } else if (titleMode == NavigationTitleMode::MINI) {
        auto hideBackButtonValid = titleBarLayoutProperty->HasHideBackButton() &&
            titleBarLayoutProperty->GetHideBackButtonValue();
        titleLayoutProperty->UpdateFontSize(hideBackButtonValid ? miniTitleFontSize : miniTitleFontSizeMin);
        titleLayoutProperty->UpdateAdaptMaxFontSize(hideBackButtonValid ? miniTitleFontSize : miniTitleFontSizeMin);
        titleLayoutProperty->UpdateAdaptMinFontSize(theme->NavigationMiniMinFontSize());
        UpdateSubTitleOpacity(1.0);
    } else if (titleMode == NavigationTitleMode::FULL) {
        titleLayoutProperty->UpdateFontSize(titleFontSize);
        titleLayoutProperty->UpdateAdaptMaxFontSize(maxFontSize);
        titleLayoutProperty->UpdateAdaptMinFontSize(theme->NavigationFullMinFontSize());
        UpdateSubTitleOpacity(1.0);
    } else {
        titleLayoutProperty->UpdateFontSize(fontSize_.has_value() ? fontSize_.value() : titleFontSize);
        titleLayoutProperty->UpdateAdaptMaxFontSize(fontSize_.has_value() ? fontSize_.value() : maxFontSize);
        UpdateSubTitleOpacity(opacity_.has_value() ? opacity_.value() : 1.0);
    }
}

void TitleBarPattern::ResetSubTitleProperty(const RefPtr<FrameNode>& textNode,
    NavigationTitleMode titleMode, bool parentIsNavDest)
{
    CHECK_NULL_VOID(textNode);
    auto titleLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(titleLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::u16string contentStr;
    if (titleLayoutProperty->HasContent()) {
        contentStr = titleLayoutProperty->GetContentValue(std::u16string());
    }
    titleLayoutProperty->Reset();
    titleLayoutProperty->UpdateContent(contentStr);

    auto theme = NavigationGetTheme(host->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    auto subTitleSize = theme->GetSubTitleFontSize();
    Color color = theme->GetSubTitleColor();
    auto textHeightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        subTitleSize = theme->GetSubTitleFontSizeS();
        color = theme->GetSubTitleFontColor();
        textHeightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (parentIsNavDest) {
        titleLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    } else if (titleMode == NavigationTitleMode::MINI) {
        titleLayoutProperty->UpdateHeightAdaptivePolicy(textHeightAdaptivePolicy);
    } else if (titleMode == NavigationTitleMode::FREE) {
        UpdateSubTitleOpacity(opacity_.value_or(1.0f));
    } else {
        UpdateSubTitleOpacity(1.0);
    }
    titleLayoutProperty->UpdateAdaptMinFontSize(MIN_ADAPT_SUBTITLE_FONT_SIZE);
    titleLayoutProperty->UpdateAdaptMaxFontSize(subTitleSize);
    titleLayoutProperty->UpdateMaxFontScale(STANDARD_FONT_SCALE);
    titleLayoutProperty->UpdateMaxLines(1);
    titleLayoutProperty->UpdateFontWeight(FontWeight::REGULAR); // ohos_id_text_font_family_regular
    titleLayoutProperty->UpdateFontSize(subTitleSize);
    titleLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    NavigationTitleUtil::InitTextProperty(titleLayoutProperty);
    TitleBarPattern::SetTextColor(textNode, color);
}

void TitleBarPattern::MountTitle(const RefPtr<TitleBarNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    UpdateNavDesTitleProperty(hostNode);
    UpdateNavBarTitleProperty(hostNode);
}

RefPtr<LayoutAlgorithm> TitleBarPattern::CreateLayoutAlgorithm()
{
    ACE_UINODE_TRACE(GetHost());
    auto titleBarLayoutAlgorithm = MakeRefPtr<TitleBarLayoutAlgorithm>();
    titleBarLayoutAlgorithm->SetInitialTitleOffsetY(initialTitleOffsetY_);
    titleBarLayoutAlgorithm->MarkIsInitialTitle(isInitialTitle_);
    titleBarLayoutAlgorithm->SetInitialSubtitleOffsetY(initialSubtitleOffsetY_);
    titleBarLayoutAlgorithm->MarkIsInitialSubtitle(isInitialSubtitle_);
    titleBarLayoutAlgorithm->SetMinTitleHeight(minTitleHeight_);
    return titleBarLayoutAlgorithm;
}

bool TitleBarPattern::IsSymbolOrSVGIcon(const RefPtr<FrameNode>& iconNode)
{
    CHECK_NULL_RETURN(iconNode, false);
    auto tag = iconNode->GetTag();
    if (tag == V2::SYMBOL_ETS_TAG) {
        return true;
    }
    if (tag != V2::BACK_BUTTON_IMAGE_ETS_TAG && tag != V2::IMAGE_ETS_TAG) {
        return false;
    }
    auto iconProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(iconProperty, false);
    auto imageSourceInfo = iconProperty->GetImageSourceInfo();
    if (!imageSourceInfo.has_value()) {
        return false;
    }
    return imageSourceInfo.value().IsSvg();
}

bool TitleBarPattern::GetColorParamWithColorInvertSupported(IconColorParam& param)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_RETURN(context, false);
    auto theme = context->GetTheme<NavigationBarTheme>();
    CHECK_NULL_RETURN(theme, false);
    ColorMode colorMode = ColorMode::DARK;
    bool isColorInvertEnabled = IsColorInvertEnabled();
    const auto& options = options_.bgOptions.scrollEffectOptions;
    if (isColorInvertEnabled) {
        colorMode = GetCurrentColorMode(isColorInvertEnabled);
    } else {
        colorMode = GetCurrentColorMode(false);
    }
    const auto colors = GetOrCreateTitleBarTokenColors(context, colorMode);
    CHECK_NULL_RETURN(colors, false);
    if (options.has_value()) {
        param.iconColor = colors->iconPrimary;
        param.iconColor = param.iconColor.ChangeOpacity(1.0);
        param.hoverColor = colors->interactiveHover;
        param.focusColor = colors->interactiveFocus;
        return true;
    }
    param.iconColor = isColorInvertEnabled ? colors->iconPrimary : theme->GetIconColor();
    param.hoverColor = theme->GetBackgroundHoverColor();
    param.focusColor = theme->GetBackgroundFocusOutlineColor();
    return true;
}

std::optional<TitleBarPattern::IconColorParam> TitleBarPattern::GetCurrentIconColorParam()
{
    IconColorParam param;
    if (!GetColorParamWithColorInvertSupported(param)) {
        return std::nullopt;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_RETURN(context, std::nullopt);
    auto theme = context->GetTheme<NavigationBarTheme>();
    CHECK_NULL_RETURN(theme, std::nullopt);
    ColorMode colorMode = GetCurrentColorMode(false);
    const auto& options = options_.bgOptions.scrollEffectOptions;
    const auto colors = GetOrCreateTitleBarTokenColors(context, colorMode);
    CHECK_NULL_RETURN(colors, std::nullopt);
    if (!options.has_value()) {
        param.pressedColor = theme->GetBackgroundPressedColor();
        param.disableOpacity = theme->GetIconDisableAlpha();
        return param;
    }
    param.pressedColor = colors->interactivePressed;
    param.disableOpacity = theme->GetIconDisableAlpha();
    return param;
}

void TitleBarPattern::UpdateBackButtonUIEffect()
{
    UpdateBackButtonMaterial();
    UpdateBackButtonIconEffect();
    UpdateBackButtonBrightnessEffect();
}

void TitleBarPattern::UpdateBackButtonIconEffect(bool forceUpdate)
{
    if (!needUpdateBackButtonEffect_ && !forceUpdate) {
        return;
    }
    needUpdateBackButtonEffect_ = false;
    auto host = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(host->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto buttonPattern = backButtonNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    auto param = GetCurrentIconColorParam();
    if (!param.has_value()) {
        return;
    }
    buttonPattern->SetBlendColor(param->pressedColor, param->hoverColor);
    buttonPattern->SetFocusBorderColor(param->focusColor);
    if (backButtonNode->GetChildren().empty()) {
        return;
    }
    auto iconNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    CHECK_NULL_VOID(iconNode);
    if (iconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        UpdateSymbolIconColor(iconNode, param->iconColor);
        return;
    }
    if (iconNode->GetTag() != V2::BACK_BUTTON_IMAGE_ETS_TAG) {
        return;
    }
    UpdateSvgImageColor(iconNode, param->iconColor);
}

void TitleBarPattern::UpdateSymbolIconColor(const RefPtr<FrameNode>& iconNode, const Color& color)
{
    CHECK_NULL_VOID(iconNode);
    auto symbolProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    std::vector<Color> colors{ color };
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, SymbolColorList, colors, iconNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextColorFlagByUser, true, iconNode);
    iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    iconNode->MarkModifyDone();
}

void TitleBarPattern::UpdateSvgImageColor(const RefPtr<FrameNode>& iconNode, const Color& color)
{
    CHECK_NULL_VOID(iconNode);
    auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto info = imageLayoutProperty->GetImageSourceInfo();
    if (!info.has_value() || !info->IsSvg()) {
        return;
    }
    info->SetFillColor(color);
    imageLayoutProperty->UpdateImageSourceInfo(info.value());
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, color, iconNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, iconNode);

    auto renderContext = iconNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->GetForegroundColorStrategy().has_value()) {
        renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::NONE);
        renderContext->ResetForegroundColorStrategy();
    }
    renderContext->UpdateForegroundColor(Color::FOREGROUND);
    renderContext->UpdateForegroundColorFlag(true);
    iconNode->MarkModifyDone();
}

void TitleBarPattern::UpdateBackButtonMaterial()
{
    if (!needUpdateBackButtonMaterial_) {
        return;
    }
    needUpdateBackButtonMaterial_ = false;
    if (MaterialUtils::IsMaterialDisabled()) {
        return;
    }
    auto material = GetCurrentMaterial();
    UpdateBackButtonMaterialInner(material);
}

void TitleBarPattern::UpdateBackButtonMaterialInner(const RefPtr<UiMaterial>& material)
{
    InitColorPickerIfNeeded();
    InitTransparencyListenerIfNeeded();
    auto host = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(host->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto titleRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(titleRenderContext);
    if (IsApplyShadowEnabled(material)) {
        titleRenderContext->UpdateClipEdge(false);
    } else {
        titleRenderContext->UpdateClipEdge(true);
    }
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(backButtonNode), AceType::RawPtr(material));
}

void TitleBarPattern::UpdateBackButtonBrightnessEffect(bool forceUpdate)
{
    if (!needUpdateBackButtonBrightness_ && !forceUpdate) {
        return;
    }
    needUpdateBackButtonBrightness_ = false;
#ifdef ENABLE_ROSEN_BACKEND
    auto host = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(host->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    if (backButtonNode->GetChildren().empty()) {
        return;
    }
    auto iconNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetChildren().front());
    CHECK_NULL_VOID(iconNode);
    if (!IsSymbolOrSVGIcon(iconNode)) {
        return;
    }
    const Rosen::BrightnessBlender* blender = nullptr;
    auto materialLevel = SystemProperties::GetUiMaterialLevel();
    if (options_.bgOptions.scrollEffectOptions.has_value() && materialLevel != UiMaterialLevel::SMOOTH) {
        bool isColorInvertEnabled = IsColorInvertEnabled();
        auto colorMode = GetCurrentColorMode(isColorInvertEnabled);
        blender = colorMode == ColorMode::LIGHT ?
            LIGHT_ICON_BRIGHTNESS_BLENDER.get() : DARK_ICON_BRIGHTNESS_BLENDER.get();
    }
    // foreground
    ViewAbstract::SetBlender(AceType::RawPtr(iconNode), blender);
#endif
}

void TitleBarPattern::UpdateMenuUIEffect(const RefPtr<UINode>& menuNode, bool forceUpdate)
{
    CHECK_NULL_VOID(menuNode);
    UpdateMenuMaterial(menuNode, forceUpdate);
    UpdateMenuIconEffect(menuNode, forceUpdate);
    UpdateMenuBrightnessEffect(menuNode, forceUpdate);
}

void TitleBarPattern::UpdateMenuIconEffect(const RefPtr<UINode>& menuNode, bool forceUpdate)
{
    if (!needUpdateMenuEffect_ && !forceUpdate) {
        return;
    }
    needUpdateMenuEffect_ = false;
    CHECK_NULL_VOID(menuNode);
    if (menuNode->GetTag() != V2::NAVIGATION_MENU_ETS_TAG) {
        return;
    }
    auto param = GetCurrentIconColorParam();
    if (!param.has_value()) {
        return;
    }
    auto children = menuNode->GetChildren();
    for (auto& child : children) {
        auto menuItemNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_CONTINUE(menuItemNode);
        if (menuItemNode->GetTag() != V2::MENU_ITEM_ETS_TAG) {
            continue;
        }
        auto buttonPattern = menuItemNode->GetPattern<ButtonPattern>();
        CHECK_NULL_CONTINUE(buttonPattern);
        buttonPattern->SetBlendColor(param->pressedColor, param->hoverColor);
        buttonPattern->SetFocusBorderColor(param->focusColor);
        auto buttonEvent = menuItemNode->GetEventHub<ButtonEventHub>();
        CHECK_NULL_VOID(buttonEvent);
        bool isButtonEnabled = buttonEvent->IsEnabled();
        if (menuItemNode->GetChildren().empty()) {
            continue;
        }
        auto barItemNode = AceType::DynamicCast<FrameNode>(menuItemNode->GetChildren().front());
        CHECK_NULL_CONTINUE(barItemNode);
        if (barItemNode->GetTag() != V2::BAR_ITEM_ETS_TAG || barItemNode->GetChildren().empty()) {
            continue;
        }
        auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetChildren().front());
        CHECK_NULL_CONTINUE(iconNode);
        auto color = isButtonEnabled ? param->iconColor : param->iconColor.BlendOpacity(param->disableOpacity);
        if (iconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
            UpdateSymbolIconColor(iconNode, color);
            continue;
        } else if (iconNode->GetTag() == V2::IMAGE_ETS_TAG) {
            UpdateSvgImageColor(iconNode, color);
        }
    }
}

void TitleBarPattern::UpdateMenuMaterial(const RefPtr<UINode>& menuNode, bool forceUpdate)
{
    if (!needUpdateMenuMaterial_ && !forceUpdate) {
        return;
    }
    needUpdateMenuMaterial_ = false;
    if (MaterialUtils::IsMaterialDisabled()) {
        return;
    }
    CHECK_NULL_VOID(menuNode);
    if (menuNode->GetTag() != V2::NAVIGATION_MENU_ETS_TAG) {
        return;
    }
    auto material = GetCurrentMaterial();
    UpdateMenuMaterialInner(menuNode, material);
}

void TitleBarPattern::UpdateMenuMaterialInner(const RefPtr<UINode>& menuNode, const RefPtr<UiMaterial>& material)
{
    CHECK_NULL_VOID(menuNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto titleRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(titleRenderContext);
    if (IsApplyShadowEnabled(material)) {
        titleRenderContext->UpdateClipEdge(false);
    } else {
        titleRenderContext->UpdateClipEdge(true);
    }
    InitColorPickerIfNeeded();
    InitTransparencyListenerIfNeeded();
    auto children = menuNode->GetChildren();
    for (auto& child : children) {
        auto menuItemNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_CONTINUE(menuItemNode);
        if (menuItemNode->GetTag() != V2::MENU_ITEM_ETS_TAG) {
            continue;
        }
        ViewAbstract::SetSystemMaterial(AceType::RawPtr(menuItemNode), AceType::RawPtr(material));
    }
}

void TitleBarPattern::UpdateMenuBrightnessEffect(const RefPtr<UINode>& menuNode, bool forceUpdate)
{
    if (!needUpdateMenuBrightness_ && !forceUpdate) {
        return;
    }
    needUpdateMenuBrightness_ = false;
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(menuNode);
    const Rosen::BrightnessBlender* blender = nullptr;
    auto materialLevel = SystemProperties::GetUiMaterialLevel();
    if (options_.bgOptions.scrollEffectOptions.has_value() && materialLevel != UiMaterialLevel::SMOOTH) {
        bool isColorInvertEnabled = IsColorInvertEnabled();
        auto colorMode = GetCurrentColorMode(isColorInvertEnabled);
        blender = colorMode == ColorMode::LIGHT ?
            LIGHT_ICON_BRIGHTNESS_BLENDER.get() : DARK_ICON_BRIGHTNESS_BLENDER.get();
    }
    auto children = menuNode->GetChildren();
    for (auto& child : children) {
        auto menuItemNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_CONTINUE(menuItemNode);
        if (menuItemNode->GetTag() != V2::MENU_ITEM_ETS_TAG ||
            menuItemNode->GetChildren().empty()) {
            continue;
        }
        auto barItemNode = AceType::DynamicCast<FrameNode>(menuItemNode->GetChildren().front());
        if (!barItemNode || barItemNode->GetTag() != V2::BAR_ITEM_ETS_TAG || barItemNode->GetChildren().empty()) {
            continue;
        }
        auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetChildren().front());
        CHECK_NULL_CONTINUE(iconNode);
        if (!IsSymbolOrSVGIcon(iconNode)) {
            continue;
        }
        // foreground
        ViewAbstract::SetBlender(AceType::RawPtr(iconNode), blender);
    }
#endif
}

void TitleBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (isInitialTitle_) {
        InitTitleParam();
    }
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    ACE_UINODE_TRACE(hostNode);
    MountBackButton(hostNode);
    MountTitle(hostNode);
    MountSubTitle(hostNode);
    ApplyTitleModifierIfNeeded(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (GreatOrEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        auto backButtonNode = AceType::DynamicCast<FrameNode>(hostNode->GetBackButton());
        CHECK_NULL_VOID(backButtonNode);
        InitBackButtonLongPressEvent(backButtonNode);
    }
    if (options_.enableHoverMode && currentFoldCreaseRegion_.empty()) {
        InitFoldCreaseRegion();
    }
    UpdateBackButtonUIEffect();
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE ||
        isInitialTitle_ || !isTitleChanged_) {
        return;
    }
    isTitleChanged_ = false;
    if (NearEqual(GetTempTitleBarHeight(), static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())) ||
        NearEqual(GetTempTitleBarHeight(), static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()))) {
        tempTitleBarHeight_.SetValue(hostNode->GetSubtitle() ? FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.Value()
                                                             : FULL_SINGLE_LINE_TITLEBAR_HEIGHT.Value());
    }
}

void TitleBarPattern::ApplyTitleModifierIfNeeded(const RefPtr<TitleBarNode>& hostNode)
{
    isFontSizeSettedByDeveloper_ = false;
    CHECK_NULL_VOID(hostNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    if (options_.textOptions.mainTitleApplyFunc && titleNode) {
        ApplyTitleModifier(titleNode, options_.textOptions.mainTitleApplyFunc, true);
    }
    auto subtitleNode = AceType::DynamicCast<FrameNode>(hostNode->GetSubtitle());
    if (options_.textOptions.subTitleApplyFunc && subtitleNode) {
        ApplyTitleModifier(subtitleNode, options_.textOptions.subTitleApplyFunc, false);
    }
}

void TitleBarPattern::ApplyTitleModifier(const RefPtr<FrameNode>& textNode,
    const TextStyleApplyFunc& applyFunc, bool needCheckFontSizeIsSetted)
{
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(applyFunc);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    std::optional<Dimension> backupFontSize;
    std::optional<Dimension> backupMaxFontSize;
    std::optional<Dimension> backupMinFontSize;
    if (textLayoutProperty->HasFontSize()) {
        backupFontSize = textLayoutProperty->GetFontSizeValue(Dimension());
    }
    if (textLayoutProperty->HasAdaptMaxFontSize()) {
        backupMaxFontSize = textLayoutProperty->GetAdaptMaxFontSizeValue(Dimension());
    }
    if (textLayoutProperty->HasAdaptMinFontSize()) {
        backupMinFontSize = textLayoutProperty->GetAdaptMinFontSizeValue(Dimension());
    }
    textLayoutProperty->ResetFontSize();
    textLayoutProperty->ResetAdaptMaxFontSize();
    textLayoutProperty->ResetAdaptMinFontSize();
    applyFunc(AceType::WeakClaim(AceType::RawPtr(textNode)));

    if (!textLayoutProperty->HasFontSize() &&
        !textLayoutProperty->HasAdaptMinFontSize() &&
        !textLayoutProperty->HasAdaptMaxFontSize()) {
        // restore
        if (backupFontSize.has_value()) {
            textLayoutProperty->UpdateFontSize(backupFontSize.value());
        }
        if (backupMaxFontSize.has_value()) {
            textLayoutProperty->UpdateAdaptMaxFontSize(backupMaxFontSize.value());
        }
        if (backupMinFontSize.has_value()) {
            textLayoutProperty->UpdateAdaptMinFontSize(backupMinFontSize.value());
        }
    } else {
        TAG_LOGD(AceLogTag::ACE_NAVIGATION, "modifier set %{public}s, %{public}s, %{public}s",
            textLayoutProperty->HasFontSize() ? "FontSize" : "",
            textLayoutProperty->HasAdaptMinFontSize() ? "AdaptMinFontSize" : "",
            textLayoutProperty->HasAdaptMaxFontSize() ? "AdaptMaxFontSize" : "");
        if (needCheckFontSizeIsSetted) {
            isFontSizeSettedByDeveloper_ = true;
        }
    }

    textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    textNode->MarkModifyDone();
}

void TitleBarPattern::ProcessTitleDragUpdate(float offset)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE ||
        IsHidden()) {
        return;
    }
    SetTempTitleBarHeight(offset);
    titleMoveDistance_ = (GetTempTitleBarHeight() - defaultTitleBarHeight_) * moveRatio_;
    SetTempTitleOffsetY();
    SetTempSubTitleOffsetY();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // title font size
    auto mappedOffset = GetMappedOffset(offset);
    fontSize_ = GetFontSize(mappedOffset);
    UpdateTitleFontSize(fontSize_.value());

    // subTitle Opacity
    opacity_ = GetSubtitleOpacity();
    UpdateSubTitleOpacity(opacity_.value());
}

float TitleBarPattern::GetSubtitleOpacity()
{
    auto titleBarHeightDiff = maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    opacityRatio_ = 1.0f / titleBarHeightDiff;
    auto tempOpacity = static_cast<float>((GetTempTitleBarHeight() -
        static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())) * opacityRatio_ + 0.0f);
    return tempOpacity;
}

Dimension TitleBarPattern::GetFontSize(float offset)
{
    auto titleBarHeight = defaultTitleBarHeight_ + offset;
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, Dimension(0.0f, DimensionUnit::FP));
    Dimension titleL = theme->GetTitleFontSizeBig();
    Dimension titleM = theme->GetTitleFontSize();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        titleL = theme->GetMainTitleFontSizeL();
        titleM = theme->GetMainTitleFontSizeM();
    }
    auto titleFontSizeDiff = titleL - titleM;
    auto titleBarHeightDiff = maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (!NearZero(titleBarHeightDiff)) {
        fontSizeRatio_ = titleFontSizeDiff.Value() / titleBarHeightDiff;
    }
    auto tempFontSize = titleM.Value() +
        (titleBarHeight - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())) * fontSizeRatio_;
    if (GreatNotEqual(tempFontSize, titleL.Value())) {
        tempFontSize = titleL.Value();
    }
    if (LessNotEqual(tempFontSize, titleM.Value())) {
        tempFontSize = titleM.Value();
    }
    return Dimension(tempFontSize, DimensionUnit::FP);
}

float TitleBarPattern::GetMappedOffset(float offset)
{
    auto titleOffset = offset + defaultTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    auto heightDiff = maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float moveRatio = Curves::SHARP->MoveInternal(std::clamp(titleOffset / heightDiff, 0.0f, 1.0f));
    auto mappedTitleOffset = moveRatio * heightDiff;
    auto mappedOffset =
        mappedTitleOffset - defaultTitleBarHeight_ + static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    return mappedOffset;
}

void TitleBarPattern::SpringAnimation(float startPos, float endPos)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    SetOverDragOffset(overDragOffset_);
    SetTempTitleBarHeightVp(maxTitleBarHeight_ + overDragOffset_ / 6.0f);
    UpdateScaleByDragOverDragOffset(overDragOffset_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->FlushUITasks();
    }

    constexpr float velocity = 0.0f;
    constexpr float mass = 1.0f;        // The move animation spring curve mass is 1.0f
    constexpr float stiffness = 228.0f; // The move animation spring curve stiffness is 228.0f
    constexpr float damping = 30.0f;    // The move animation spring curve damping is 30.0f
    auto springCurve = AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);
    AnimationOption option;
    option.SetCurve(springCurve);

    springAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weakPattern = AceType::WeakClaim(this)]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            pattern->SetOverDragOffset(0.0f);
            pattern->SetTempTitleBarHeightVp(pattern->GetMaxTitleBarHeight());
            pattern->UpdateScaleByDragOverDragOffset(0.0f);
            pattern->tempTitleOffsetY_ = 0.0f;
            pattern->isFreeTitleUpdated_ = false;
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
        }, [weakPattern = AceType::WeakClaim(this)]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->CleanSpringAnimation();
        }, nullptr /* repeatCallback */, host->GetContextRefPtr());
}

void TitleBarPattern::ClearDragState()
{
    overDragOffset_ = 0.0f;
}

void TitleBarPattern::UpdateScaleByDragOverDragOffset(float overDragOffset)
{
    if (Negative(overDragOffset)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(host->GetParent());
    CHECK_NULL_VOID(navBarNode);
    if (navBarNode->GetPrevTitleIsCustomValue(true)) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleNode = titleBarNode->GetTitle();
    CHECK_NULL_VOID(titleNode);
    auto title = AceType::DynamicCast<FrameNode>(titleNode);
    TransformScale(overDragOffset, title);
    auto subtitleNode = titleBarNode->GetSubtitle();
    if (subtitleNode) {
        auto subtitle = AceType::DynamicCast<FrameNode>(subtitleNode);
        TransformScale(overDragOffset, subtitle);
    }

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TitleBarPattern::TransformScale(float overDragOffset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderCtx = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    auto offset = std::clamp(overDragOffset, 0.0f, static_cast<float>(MAX_OVER_DRAG_OFFSET.ConvertToPx()));
    auto scaleRatio = offset / static_cast<float>(MAX_OVER_DRAG_OFFSET.ConvertToPx());
    VectorF scaleValue = VectorF(scaleRatio * 0.1f + 1.0f, scaleRatio * 0.1f + 1.0f);
    renderCtx->UpdateTransformScale(scaleValue);
}

void TitleBarPattern::AnimateTo(float offset, bool isFullTitleMode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);

    animation_ = AnimationUtils::StartAnimation(
        option,
        [weakPattern = AceType::WeakClaim(this), offset, isFullTitleMode]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            pattern->ProcessTitleDragUpdate(offset);
            if (isFullTitleMode) {
                pattern->tempTitleOffsetY_ = 0.0f;
                pattern->isFreeTitleUpdated_ = false;
            }
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
        }, [weakPattern = AceType::WeakClaim(this)]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->CleanAnimation();
        }, nullptr /* repeatCallback */, host->GetContextRefPtr());
}

void TitleBarPattern::SetMaxTitleBarHeight()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    if (titleBarNode->GetSubtitle()) {
        maxTitleBarHeight_ = static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    } else {
        maxTitleBarHeight_ = static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }
}

void TitleBarPattern::SetTempTitleBarHeight(float offsetY)
{
    auto tmepTitleBarHeight = defaultTitleBarHeight_ + offsetY;
    if (tmepTitleBarHeight < static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx())) {
        tmepTitleBarHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    }
    if (tmepTitleBarHeight > maxTitleBarHeight_) {
        tmepTitleBarHeight = maxTitleBarHeight_;
    }
    SetTempTitleBarHeightVp(tmepTitleBarHeight);
}

void TitleBarPattern::SetTempTitleOffsetY()
{
    tempTitleOffsetY_ = defaultTitleOffsetY_ + titleMoveDistance_;
    if (tempTitleOffsetY_ < minTitleOffsetY_) {
        tempTitleOffsetY_ = minTitleOffsetY_;
    }
    if (tempTitleOffsetY_ > maxTitleOffsetY_) {
        tempTitleOffsetY_ = maxTitleOffsetY_;
    }
}

void TitleBarPattern::SetTempSubTitleOffsetY()
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        tempSubTitleOffsetY_ = tempTitleOffsetY_ + GetTitleHeight() +
            static_cast<float>(titleSpaceVertical_.ConvertToPx());
    } else {
        tempSubTitleOffsetY_ = tempTitleOffsetY_ + GetTitleHeight();
    }
    if (tempTitleOffsetY_ < minTitleOffsetY_) {
        tempSubTitleOffsetY_ = minTitleOffsetY_;
    }
    if (tempTitleOffsetY_ > maxTitleOffsetY_) {
        tempSubTitleOffsetY_ = maxTitleOffsetY_;
    }
}

void TitleBarPattern::SetDefaultTitleFontSize()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    CHECK_NULL_VOID(titleBarNode->GetTitle());
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    defaultTitleFontSize_ = theme->GetTitleFontSize();
}

void TitleBarPattern::SetDefaultSubtitleOpacity()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    CHECK_NULL_VOID(titleBarNode->GetSubtitle());
    auto subtitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    CHECK_NULL_VOID(subtitleNode);
    auto context = subtitleNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (defaultTitleBarHeight_ == maxTitleBarHeight_) {
        defaultSubtitleOpacity_ = context->GetOpacityValue(1.0f);
    } else {
        defaultSubtitleOpacity_ = context->GetOpacityValue(0.0f);
    }
}

float TitleBarPattern::GetTitleHeight()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_RETURN(titleNode, 0.0f);
    auto geometryNode = titleNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    return geometryNode->GetFrameSize().Height();
}

float TitleBarPattern::GetSubTitleOffsetY()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_RETURN(titleBarNode, 0.0f);
    auto subTitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    CHECK_NULL_RETURN(subTitleNode, 0.0f);
    auto geometryNode = subTitleNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    return geometryNode->GetMarginFrameOffset().GetY();
}

void TitleBarPattern::UpdateTitleFontSize(const Dimension& tempTitleFontSize)
{
    if (isFontSizeSettedByDeveloper_) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_VOID(titleNode);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateFontSize(tempTitleFontSize);
    textLayoutProperty->UpdateAdaptMaxFontSize(tempTitleFontSize);
    titleNode->MarkModifyDone();
}

void TitleBarPattern::UpdateSubTitleOpacity(const double& value)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto subTitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    CHECK_NULL_VOID(subTitleNode);
    auto context = subTitleNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateOpacity(value);
}

bool TitleBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto titleBarLayoutAlgorithm = DynamicCast<TitleBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(titleBarLayoutAlgorithm, false);
    UpdateTitleModeChange();

    initialTitleOffsetY_ = titleBarLayoutAlgorithm->GetInitialTitleOffsetY();
    isInitialTitle_ = titleBarLayoutAlgorithm->IsInitialTitle();
    initialSubtitleOffsetY_ = titleBarLayoutAlgorithm->GetInitialSubtitleOffsetY();
    isInitialSubtitle_ = titleBarLayoutAlgorithm->IsInitialSubtitle();
    minTitleHeight_ = titleBarLayoutAlgorithm->GetMinTitleHeight();
    return true;
}

void TitleBarPattern::UpdateTitleModeChange()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto geometryNode = titleBarNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto titleBarHeight = geometryNode->GetFrameSize().Height();
    if ((titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) &&
        !NearZero(maxTitleBarHeight_)) {
        if (titleBarHeight >= maxTitleBarHeight_) {
            titleMode_ = NavigationTitleMode::FULL;
        } else if (NearEqual(titleBarHeight, static_cast<float>(TITLEBAR_HEIGHT_MINI.ConvertToPx()))) {
            titleMode_ = NavigationTitleMode::MINI;
        }
    }
}

void TitleBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode);
    host->GetRenderContext()->SetClipToFrame(true);
    host->GetRenderContext()->UpdateClipEdge(true);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_TOP };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);

    auto halfFoldHoverCallbackId = pipelineContext->RegisterHalfFoldHoverChangedCallback(
        [weakHost = WeakPtr<FrameNode>(host)](bool isHalfFoldHover) {
            auto host = weakHost.Upgrade();
            CHECK_NULL_VOID(host);
            NavigationTitleUtil::FoldStatusChangedAnimation(host);
        });
    UpdateHalfFoldHoverChangedCallbackId(halfFoldHoverCallbackId);
}

void TitleBarPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    THREAD_SAFE_NODE_CHECK(host, OnAttachToMainTree);
    UpdateIsBackgroundDark();
}

void TitleBarPattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    THREAD_SAFE_NODE_CHECK(host, OnDetachFromMainTree);
    UnregisterColorPicker();
    UnregisterTransparencyListener();
}

void TitleBarPattern::InitFoldCreaseRegion()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    currentFoldCreaseRegion_ = displayInfo->GetCurrentFoldCreaseRegion();
}

void TitleBarPattern::OnCoordScrollStart()
{
    coordScrollOffset_ = 0.0f;
    coordScrollFinalOffset_ = 0.0f;
    isFreeTitleUpdated_ = true;

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        return;
    }
    if (springAnimation_) {
        AnimationUtils::StopAnimation(springAnimation_);
        springAnimation_.reset();
    }
    if (animation_) {
        AnimationUtils::StopAnimation(animation_);
        animation_.reset();
    }

    defaultTitleBarHeight_ = currentTitleBarHeight_;
    defaultTitleOffsetY_ = currentTitleOffsetY_;
    SetMaxTitleBarHeight();
    SetTempTitleBarHeight(0);
    minTitleOffsetY_ = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - minTitleHeight_) / 2.0f;
    maxTitleOffsetY_ = initialTitleOffsetY_;
    moveRatio_ = (maxTitleOffsetY_ - minTitleOffsetY_) /
                 (maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    titleMoveDistance_ = (GetTempTitleBarHeight() - defaultTitleBarHeight_) * moveRatio_;
}

float TitleBarPattern::OnCoordScrollUpdate(float offset)
{
    float lastOffset = coordScrollOffset_;
    coordScrollOffset_ += offset;

    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float titleBarOffset = coordScrollOffset_;
    if (LessNotEqual(defaultTitleBarHeight_ + titleBarOffset, minHeight)) {
        // The target height is smaller than the minHeight, so the titleBarOffset is adjusted to modify the height to
        // the minHeight.
        titleBarOffset = minHeight - defaultTitleBarHeight_;
        overDragOffset_ = 0.0f;
        offsetHandled = CalculateHandledOffsetMinTitle(offset, lastOffset);
    } else if (GreatNotEqual(defaultTitleBarHeight_ + titleBarOffset, maxTitleBarHeight_)) {
        // The target height is greater than the maxTitleBarHeight_, so overDragOffset_ needs to be updated.
        overDragOffset_ = defaultTitleBarHeight_ + titleBarOffset - maxTitleBarHeight_;
        offsetHandled = CalculateHandledOffsetMaxTitle(offset, lastOffset);
    } else {
        // The target height is between the minHeight and the maxTitleBarHeight_.
        overDragOffset_ = 0.0f;
        offsetHandled = CalculateHandledOffsetBetweenMinAndMaxTitle(offset, lastOffset);
    }
    UpdateTitleBarByCoordScroll(titleBarOffset);
    coordScrollFinalOffset_ = titleBarOffset;
    auto barStyle = options_.brOptions.barStyle.value_or(BarStyle::STANDARD);
    if (barStyle == BarStyle::STACK) {
        offsetHandled = 0.0f;
    }

    return offsetHandled;
}

void TitleBarPattern::OnCoordScrollEnd()
{
    if (NearZero(coordScrollOffset_)) {
        return;
    }
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    float middleHeight =
        (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) + maxTitleBarHeight_) / TITLE_RATIO;
    float finalHeight = defaultTitleBarHeight_ + coordScrollFinalOffset_;
    if (GreatNotEqual(finalHeight, minHeight) && LessOrEqual(finalHeight, middleHeight)) {
        // The finalHeight is between the minHeight and the middleHeight, so animate to min title.
        AnimateTo(static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - defaultTitleBarHeight_);
        return;
    }
    if (GreatNotEqual(finalHeight, middleHeight) && LessNotEqual(finalHeight, maxTitleBarHeight_)) {
        // The finalHeight is between the middleHeight and the maxTitleBarHeight_, so animate to max title.
        AnimateTo(maxTitleBarHeight_ - defaultTitleBarHeight_, true);
        return;
    }
    if (GreatNotEqual(finalHeight, maxTitleBarHeight_)) {
        // The finalHeight is bigger than the maxTitleBarHeight_, so animate to max title.
        SpringAnimation(finalHeight - maxTitleBarHeight_, 0);
    }
}

void TitleBarPattern::UpdateTitleBarByCoordScroll(float offset)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        return;
    }
    SetTitleStyleByCoordScrollOffset(offset);
    UpdateScaleByDragOverDragOffset(overDragOffset_);
}

void TitleBarPattern::SetTitleStyleByCoordScrollOffset(float offset)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE) {
        return;
    }
    if (Positive(overDragOffset_)) {
        SetTempTitleBarHeightVp(maxTitleBarHeight_ + overDragOffset_ / 6.0f);
        titleMoveDistance_ = (maxTitleBarHeight_ - defaultTitleBarHeight_) * moveRatio_ + overDragOffset_ / 6.0f;
    } else {
        SetTempTitleBarHeight(offset);
        titleMoveDistance_ = (GetTempTitleBarHeight() - defaultTitleBarHeight_) * moveRatio_;
    }

    SetTempTitleOffsetY();
    SetTempSubTitleOffsetY();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // title font size
    auto mappedOffset = GetMappedOffset(offset);
    fontSize_ = GetFontSize(mappedOffset);
    UpdateTitleFontSize(fontSize_.value());

    // subTitle Opacity
    opacity_ = GetSubtitleOpacity();
    UpdateSubTitleOpacity(opacity_.value());
}

void TitleBarPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateBackgroundStyle(host);
    SetNeedResetMainTitleProperty(true);
    SetNeedResetSubTitleProperty(true);
    UpdateBackButtonColor();
    UpdateIsBackgroundDark();
    UpdateTitleBarUIEffectForColorModeChange();
}

void TitleBarPattern::UpdateBackButtonColor()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto backButton = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButton);
    if (backButton->GetTag() == "Navigator") {
        backButton = AceType::DynamicCast<FrameNode>(backButton->GetChildren().front());
        CHECK_NULL_VOID(backButton);
    }
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto iconColor = theme->GetBackButtonIconColor();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        iconColor = theme->GetIconColor();
        auto backButtonColor = theme->GetCompBackgroundColor();
        auto renderContext = backButton->GetRenderContext();
        auto backButtonPattern = backButton->GetPattern<ButtonPattern>();
        backButtonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
        backButtonPattern->SetBlendColor(theme->GetBackgroundPressedColor(), theme->GetBackgroundHoverColor());
        backButtonPattern->SetFocusBorderColor(theme->GetBackgroundFocusOutlineColor());
        backButtonPattern->SetFocusBorderWidth(theme->GetBackgroundFocusOutlineWeight());
        renderContext->UpdateBackgroundColor(backButtonColor);
        auto backButtonLayoutProperty = backButtonPattern->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(backButtonLayoutProperty);
        backButtonLayoutProperty->UpdateBackgroundColorFlagByUser(true);
        backButton->MarkModifyDone();
    }
    auto backButtonImgNode = AceType::DynamicCast<FrameNode>(backButton->GetChildren().front());
    CHECK_NULL_VOID(backButtonImgNode);
    if (backButtonImgNode->GetTag() == V2::IMAGE_ETS_TAG) {
        auto backButtonImgRender = backButtonImgNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(backButtonImgRender);
        backButtonImgRender->UpdateSvgFillColor(iconColor);
    }
    backButtonImgNode->MarkModifyDone();
}

bool TitleBarPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    auto host = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_RETURN(host, false);
    shouldResetMainTitleProperty_ = true;
    shouldResetSubTitleProperty_ = true;
    host->MarkModifyDone();
    return false;
}

float TitleBarPattern::CalculateHandledOffsetMinTitle(float offset, float lastCordScrollOffset)
{
    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting height of this update is smaller than the minHeight, so the navigation component does
        // not handle the offset.
        offsetHandled = 0.0f;
    } else if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting position height of this update is greater than the maxTitleBarHeight_, so the navigation
        // component only handles offsets from maxTitleBarHeight_ to minHeight.
        offsetHandled = minHeight - maxTitleBarHeight_;
    } else {
        // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
        // navigation component only handles offsets from defaultTitleBarHeight_ to minHeight.
        offsetHandled = offset - (coordScrollOffset_ - (minHeight - defaultTitleBarHeight_));
    }
    return offsetHandled;
}

float TitleBarPattern::CalculateHandledOffsetMaxTitle(float offset, float lastCordScrollOffset)
{
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting height of this update is greater than the maxTitleBarHeight_, so the navigation component
        // does not handle the offset.
        return 0.0f;
    }
    if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting position height of this update is smaller than the minHeight, so the navigation component
        // only handles offsets from minHeight to maxTitleBarHeight_.
        return maxTitleBarHeight_ - minHeight;
    }
    // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
    // navigation component only handles offsets from defaultTitleBarHeight_ to maxTitleBarHeight_.
    return offset - (coordScrollOffset_ - (maxTitleBarHeight_ - defaultTitleBarHeight_));
}

float TitleBarPattern::CalculateHandledOffsetBetweenMinAndMaxTitle(float offset, float lastCordScrollOffset)
{
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting height of this update is smaller than the minHeight, so the navigation component only
        // handles offsets from minHeight to target height.
        return defaultTitleBarHeight_ + coordScrollOffset_ - minHeight;
    }
    if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting position height of this update is greater than the maxTitleBarHeight_, so the navigation
        // component only handles offsets from maxTitleBarHeight_ to target height.
        return coordScrollOffset_ - (maxTitleBarHeight_ - defaultTitleBarHeight_);
    }
    // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
    // navigation component handles all of the offset.
    return offset;
}

RefPtr<UiMaterial> TitleBarPattern::GetOrCreateGradualBlurMaterial()
{
    if (gradualBlurMaterial_) {
        return gradualBlurMaterial_;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto themeScopeId = host->GetThemeScopeId();
    auto tokenTheme = TokenThemeStorage::GetInstance()->GetTheme(themeScopeId);
    if (!tokenTheme) {
        tokenTheme = TokenThemeStorage::GetInstance()->ObtainSystemTheme();
    }
    CHECK_NULL_RETURN(tokenTheme, nullptr);
    const auto& tokenColors = tokenTheme->Colors();
    CHECK_NULL_RETURN(tokenColors, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    CHECK_NULL_RETURN(material, nullptr);
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    ImmersiveOptions options;
    options.style = UiMaterialStyle::ULTRA_THIN;
    options.colorInvert = true;
    options.materialColor = tokenColors->CompBackgroundGray();
    options.materialColor = options.materialColor.ChangeOpacity(0);
    options.applyShadow = true;
    options.interactive = true;
    LightEffectOptions lightEffectOptions;
    lightEffectOptions.color = DEFAULT_LIGHT_EFFECT_COLOR;
    options.lightEffectOptions = lightEffectOptions;
    material->SetImmersiveOptions(options);
    gradualBlurMaterial_ = material;
    return gradualBlurMaterial_;
}

RefPtr<UiMaterial> TitleBarPattern::GetCurrentMaterial()
{
    // disable
    if (MaterialUtils::IsMaterialDisabled()) {
        return nullptr;
    }
    if (options_.material) {
        return options_.material;
    }
    // default;
    if (!MaterialUtils::IsMaterialEnabled()) {
        return nullptr;
    }
    // enable
    const auto& options = options_.bgOptions.scrollEffectOptions;
    if (options.has_value() && options->scrollEffectType == ScrollEffectType::GRADUAL_BLUR) {
        return GetOrCreateGradualBlurMaterial();
    }
    return nullptr;
}

void TitleBarPattern::UpdateTitleBarUIEffectForColorModeChange()
{
    auto host = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto menuNode = host->GetMenu();
    const auto& options = options_.bgOptions.scrollEffectOptions;
    auto curMaterial = GetCurrentMaterial();
    if (!options.has_value() && !curMaterial) {
        return;
    }
    if (options.has_value()) {
        UpdateBackButtonIconEffect(true);
        UpdateMenuIconEffect(menuNode, true);
    }
    UpdateBackButtonBrightnessEffect(true);
    UpdateMenuBrightnessEffect(menuNode, true);
    if (MaterialUtils::IsMaterialDisabled()) {
        return;
    }
    auto mode = GetCurrentColorMode(false);
    const auto tokenColors = GetOrCreateTitleBarTokenColors(context, mode);
    CHECK_NULL_VOID(tokenColors);
    do {
        CHECK_NULL_BREAK(gradualBlurMaterial_);
        auto options = gradualBlurMaterial_->CopyImmersiveOptions();
        CHECK_NULL_BREAK(options);
        options->materialColor = tokenColors->compBackgroundGray;
        options->materialColor = options->materialColor.ChangeOpacity(0);
        gradualBlurMaterial_->SetImmersiveOptions(*options);
    } while (false);
    if (options_.material || !MaterialUtils::IsMaterialEnabled()) {
        return;
    }
    UpdateBackButtonMaterialInner(curMaterial);
    UpdateMenuMaterialInner(menuNode, curMaterial);
}

void TitleBarPattern::MarkMenuUIEffectNeedUpdate()
{
    const auto& options = options_.bgOptions.scrollEffectOptions;
    if (options.has_value()) {
        needUpdateMenuEffect_ = true;
        needUpdateMenuBrightness_ = true;
    }
    auto material = GetCurrentMaterial();
    if (material) {
        needUpdateMenuMaterial_ = true;
        needUpdateMenuEffect_ = true;
        needUpdateMenuBrightness_ = true;
    }
}

bool TitleBarPattern::IsColorInvertEnabled()
{
    auto materialLevel = SystemProperties::GetUiMaterialLevel();
    if (materialLevel != UiMaterialLevel::EXQUISITE && materialLevel != UiMaterialLevel::GENTLE) {
        return false;
    }
    auto material = GetCurrentMaterial();
    if (!material) {
        return false;
    }
    const auto& options = material->GetImmersiveOptions();
    if (!options || !options->colorInvert) {
        return false;
    }
    auto transparencyLevel = static_cast<UiMaterialTransparency>(
        TransparencyUtils::GetTransparencyLevel(static_cast<int32_t>(materialLevel)));
    if (materialLevel == UiMaterialLevel::EXQUISITE) {
        return transparencyLevel == UiMaterialTransparency::THIN ||
            transparencyLevel == UiMaterialTransparency::NORMAL;
    }
    return transparencyLevel == UiMaterialTransparency::GENTLE_THIN;
}

bool TitleBarPattern::IsApplyShadowEnabled(const RefPtr<UiMaterial>& material)
{
    if (!material) {
        return false;
    }
    const auto& options = material->GetImmersiveOptions();
    if (!options) {
        return false;
    }
    return options->applyShadow;
}

ColorMode TitleBarPattern::GetCurrentColorMode(bool enableColorInvert)
{
    if (enableColorInvert && isColorPickerDark_.has_value()) {
        return isColorPickerDark_.value() ? ColorMode::DARK : ColorMode::LIGHT;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ColorMode::COLOR_MODE_UNDEFINED);
    auto localMode = host->GetLocalColorMode();
    if (localMode != ColorMode::COLOR_MODE_UNDEFINED) {
        return localMode;
    }
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, ColorMode::COLOR_MODE_UNDEFINED);
    return context->GetColorMode();
}

bool TitleBarPattern::IsTransparencyListenerNeeded()
{
    auto materialLevel = SystemProperties::GetUiMaterialLevel();
    if (materialLevel != UiMaterialLevel::EXQUISITE && materialLevel != UiMaterialLevel::GENTLE) {
        return false;
    }
    auto material = GetCurrentMaterial();
    if (!material) {
        return false;
    }
    const auto& options = material->GetImmersiveOptions();
    if (!options || !options->colorInvert) {
        return false;
    }
    return true;
}

void TitleBarPattern::InitTransparencyListenerIfNeeded()
{
    if (!IsTransparencyListenerNeeded()) {
        UnregisterTransparencyListener();
        InitColorPickerIfNeeded();
        return;
    }
    if (transparencyListenerId_.has_value()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto listener = [weakPattern = WeakClaim(this)](int32_t level) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Transparency change to %{public}d", level);
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->InitColorPickerIfNeeded();
    };
    transparencyListenerId_ = TransparencyUtils::RegisterTransparencyListener(WeakPtr(host), std::move(listener));
}

void TitleBarPattern::UnregisterTransparencyListener()
{
    if (!transparencyListenerId_.has_value()) {
        return;
    }
    TransparencyUtils::UnRegisterTransparencyListener(transparencyListenerId_.value());
    transparencyListenerId_ = std::nullopt;
}

void TitleBarPattern::InitColorPickerIfNeeded()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (!IsColorInvertEnabled()) {
        auto isDark = isBackgroundDark_;
        UnregisterColorPicker();
        if (isDark != isBackgroundDark_) {
            StartColorInvertAnimation();
        }
        return;
    }
    if (hasRegisterColorPicker_) {
        return;
    }
    hasRegisterColorPicker_ = true;
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto navMgr = context->GetNavigationManager();
    CHECK_NULL_VOID(navMgr);
    navMgr->RegisterColorPicker(host, LUMINANCE_SAMPLER_INTERVAL, LUMINANCE_THRESHOLD_HIGH, LUMINANCE_THRESHOLD_LOW,
        [weakPattern = WeakClaim(this)](uint32_t luminance) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "titleBar luminance change to %{public}u", luminance);
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnLuminanceUpdate(luminance);
    });
}

void TitleBarPattern::UpdateIsBackgroundDark()
{
    isBackgroundDark_ = GetCurrentColorMode(true) == ColorMode::DARK;
}

void TitleBarPattern::OnLuminanceUpdate(uint32_t luminance)
{
    if (static_cast<int32_t>(luminance) < LUMINANCE_THRESHOLD_LOW) {
        isColorPickerDark_ = true;
    } else if (static_cast<int32_t>(luminance) > LUMINANCE_THRESHOLD_HIGH) {
        isColorPickerDark_ = false;
    }
    if (!IsColorInvertEnabled()) {
        return;
    }
    if (!isColorPickerDark_.has_value() || isColorPickerDark_.value() == isBackgroundDark_) {
        return;
    }
    isBackgroundDark_ = isColorPickerDark_.value();
    StartColorInvertAnimation();
}

void TitleBarPattern::UnregisterColorPicker()
{
    auto host = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(host);
    if (hasRegisterColorPicker_) {
        hasRegisterColorPicker_ = false;
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto navMgr = context->GetNavigationManager();
        CHECK_NULL_VOID(navMgr);
        navMgr->UnregisterColorPicker(host);
        isColorPickerDark_ = std::nullopt;
        UpdateIsBackgroundDark();
    }
}

void TitleBarPattern::StartColorInvertAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    AnimationOption option = AnimationOption();
    option.SetDuration(INVERT_COLOR_ANIMATION_DURATION);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::StartAnimation(option,
        [weakPattern = WeakClaim(this)]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleColorInvert();
        }, nullptr, nullptr, context);
}

void TitleBarPattern::HandleColorInvert()
{
    auto host = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto menuNode = AceType::DynamicCast<FrameNode>(host->GetMenu());
    CHECK_NULL_VOID(menuNode);
    UpdateMenuIconEffect(menuNode, true);
    UpdateMenuBrightnessEffect(menuNode, true);
    UpdateBackButtonIconEffect(true);
    UpdateBackButtonBrightnessEffect(true);
}

void TitleBarPattern::SetTitlebarOptions(NavigationTitlebarOptions& opt)
{
    bool needUpdateBgOptions = options_.bgOptions != opt.bgOptions;
    if (options_.textOptions.mainTitleApplyFunc && !opt.textOptions.mainTitleApplyFunc) {
        shouldResetMainTitleProperty_ = true;
    }
    if (options_.textOptions.subTitleApplyFunc && !opt.textOptions.subTitleApplyFunc) {
        shouldResetSubTitleProperty_ = true;
    }
    if (options_.bgOptions.blurStyleOption->blurOption != opt.bgOptions.blurStyleOption->blurOption) {
        needUpdateBgOptions = true;
    }
    if (options_.bgOptions.scrollEffectOptions != opt.bgOptions.scrollEffectOptions) {
        needUpdateBackButtonEffect_ = true;
        needUpdateBackButtonMaterial_ = true;
        needUpdateBackButtonBrightness_ = true;
        needUpdateMenuEffect_ = true;
        needUpdateMenuMaterial_ = true;
        needUpdateMenuBrightness_ = true;
    }
    if (!MaterialUtils::IsMaterialDisabled()) {
        // Default or Enable
        if (options_.material || opt.material) {
            needUpdateBackButtonMaterial_ = true;
            needUpdateBackButtonBrightness_ = true;
            needUpdateMenuMaterial_ = true;
            needUpdateMenuBrightness_ = true;
        }
    }
    options_ = opt;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (opt.brOptions.paddingStart.has_value()) {
        ACE_CHECK_NODE_LPX_ATTRIBUTE(opt.brOptions.paddingStart.value(), LpxAttribute::ALWAYS, host);
    }
    if (opt.brOptions.paddingEnd.has_value()) {
        ACE_CHECK_NODE_LPX_ATTRIBUTE(opt.brOptions.paddingEnd.value(), LpxAttribute::ALWAYS, host);
    }
    if (!needUpdateBgOptions) {
        return;
    }
    UpdateBackgroundStyle(host);
}

void TitleBarPattern::UpdateBackgroundStyle(RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    FREE_NODE_CHECK(host, UpdateBackgroundStyle, host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (options_.bgOptions.color.has_value()) {
        renderContext->UpdateBackgroundColor(options_.bgOptions.color.value());
    } else {
        renderContext->ResetBackgroundColor();
    }
    if (options_.bgOptions.blurStyleOption.has_value()) {
        BlurStyleOption styleOption = options_.bgOptions.blurStyleOption.value();
        SetBackgroundBlurStyle(host, styleOption);
    } else {
        renderContext->ResetBackBlurStyle();
    }
    if (options_.bgOptions.effectOption.has_value()) {
        EffectOption effectOption = options_.bgOptions.effectOption.value();
        SetBackgroundEffect(host, effectOption);
    }
}

void TitleBarPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    THREAD_SAFE_NODE_CHECK(frameNode, OnDetachFromFrameNode, frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (HasHalfFoldHoverChangedCallbackId()) {
        pipeline->UnRegisterHalfFoldHoverChangedCallback(halfFoldHoverChangedCallbackId_.value());
    }
}

void TitleBarPattern::DumpInfo()
{
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto mainTitle = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    if (mainTitle) {
        auto property = mainTitle->GetLayoutProperty<TextLayoutProperty>();
        if (property) {
            DumpTitleProperty(property, true);
        }
    }

    auto subTitle = AceType::DynamicCast<FrameNode>(hostNode->GetSubtitle());
    if (subTitle) {
        auto property = subTitle->GetLayoutProperty<TextLayoutProperty>();
        if (property) {
            DumpTitleProperty(property, false);
        }
    }
}

void TitleBarPattern::OnLanguageConfigurationUpdate()
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto theme = NavigationGetTheme();
    std::string message = theme ? theme->GetNavigationBack() : "";
    NavigationTitleUtil::SetAccessibility(backButtonNode, message);
}

float TitleBarPattern::GetTitleBarHeightLessThanMaxBarHeight() const
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_RETURN(titleBarNode, 0.f);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, 0.f);
    auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    if (titleMode != NavigationTitleMode::FREE) {
        return 0.f;
    }
    auto barStyle = options_.brOptions.barStyle.value_or(BarStyle::STANDARD);
    if (barStyle != BarStyle::STACK) {
        return 0.f;
    }
    return maxTitleBarHeight_ - currentTitleBarHeight_;
}

void TitleBarPattern::HandleLongPress(const RefPtr<FrameNode>& backButtonNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = backButtonNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto message = accessibilityProperty->GetAccessibilityText();
    if (dialogNode_ != nullptr) {
        HandleLongPressActionEnd();
    }

    auto backButtonIconNode = AceType::DynamicCast<FrameNode>(backButtonNode->GetFirstChild());
    CHECK_NULL_VOID(backButtonIconNode);
    if (backButtonIconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        dialogNode_ =
            AgingAdapationDialogUtil::ShowLongPressDialog(message, backButtonIconNode);
        return;
    }
    auto imageProperty = backButtonIconNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageProperty);
    ImageSourceInfo imageSourceInfo = imageProperty->GetImageSourceInfoValue();
    dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(message, imageSourceInfo, host->GetThemeScopeId());
}

void TitleBarPattern::HandleLongPressActionEnd()
{
    CHECK_NULL_VOID(dialogNode_);
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode_);
    dialogNode_ = nullptr;
}

void TitleBarPattern::InitBackButtonLongPressEvent(const RefPtr<FrameNode>& backButtonNode)
{
    ACE_UINODE_TRACE(GetHost());
    auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    auto longPressCallback = [weak = WeakClaim(this), weakNode = WeakClaim(RawPtr(backButtonNode))](
        GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto backButtonNode = weakNode.Upgrade();
        CHECK_NULL_VOID(backButtonNode);
        pattern->HandleLongPress(backButtonNode);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gestureHub->SetLongPressEvent(longPressEvent_);

    auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
    CHECK_NULL_VOID(longPressRecognizer);

    auto longPressEndCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPressActionEnd();
    };
    longPressRecognizer->SetOnActionEnd(longPressEndCallback);
}

void TitleBarPattern::OnFontScaleConfigurationUpdate()
{
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(hostNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    if (LessNotEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetLongPressEvent(nullptr);
        auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
        CHECK_NULL_VOID(longPressRecognizer);
        longPressRecognizer->SetOnActionEnd(nullptr);
        return;
    }
    InitBackButtonLongPressEvent(backButtonNode);
}

void TitleBarPattern::InitMenuDragAndLongPressEvent(
    const RefPtr<FrameNode>& menuNode, const std::vector<NG::BarItem>& menuItems)
{
    ACE_UINODE_TRACE(GetHost());
    CHECK_NULL_VOID(menuNode);
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (LessNotEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        return;
    }

    auto gestureHub = menuNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitMenuDragEvent(gestureHub, menuNode, menuItems);
    InitMenuLongPressEvent(gestureHub, menuNode, menuItems);
    auto accessibilityProperty = menuNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
}

void TitleBarPattern::InitMenuDragEvent(const RefPtr<GestureEventHub>& gestureHub, const RefPtr<FrameNode>& menuNode,
    const std::vector<NG::BarItem>& menuItems)
{
    auto actionUpdateTask = [weakMenuNode = WeakPtr<FrameNode>(menuNode), menuItems, weak = WeakClaim(this)](
                                const GestureEvent& info) {
        auto menuNode = weakMenuNode.Upgrade();
        CHECK_NULL_VOID(menuNode);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto menuItemNode =
            menuNode->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
        CHECK_NULL_VOID(menuItemNode);
        auto index = menuNode->GetChildIndex(menuItemNode);
        auto totalCount = menuNode->TotalChildCount();
        auto dialogNode = pattern->GetLargeFontPopUpDialogNode();
        if (dialogNode && index >= 0 && index < totalCount) {
            auto pipeline = menuNode->GetContextWithCheck();
            CHECK_NULL_VOID(pipeline);
            auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
            CHECK_NULL_VOID(buttonTheme);
            auto buttonPattern = menuItemNode->GetPattern<ButtonPattern>();
            CHECK_NULL_VOID(buttonPattern);
            buttonPattern->SetClickedColor(buttonTheme->GetClickedColor());
            if (!pattern->GetMoveIndex().has_value()) {
                pattern->SetMoveIndex(index);
            }
            if (pattern->GetMoveIndex().value() != index) {
                auto renderContext = menuItemNode->GetRenderContext();
                CHECK_NULL_VOID(renderContext);
                renderContext->UpdateBackgroundColor(buttonTheme->GetClickedColor());
                pattern->HandleMenuLongPressActionEnd();
                pattern->SetMoveIndex(index);
                pattern->SetLargeFontPopUpDialogNode(NavigationTitleUtil::CreatePopupDialogNode(
                    menuItemNode, menuItems, index, host->GetThemeScopeId()));
            }
        }
    };

    auto dragEvent = AceType::MakeRefPtr<DragEvent>(nullptr, std::move(actionUpdateTask), nullptr, nullptr);
    PanDirection panDirection = { .type = PanDirection::ALL };
    gestureHub->SetDragEvent(dragEvent, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void TitleBarPattern::InitMenuLongPressEvent(const RefPtr<GestureEventHub>& gestureHub,
    const RefPtr<FrameNode>& menuNode, const std::vector<NG::BarItem>& menuItems)
{
    auto longPressCallback = [weakTargetNode = WeakPtr<FrameNode>(menuNode), menuItems, weak = WeakClaim(this)](
                                 GestureEvent& info) {
        auto menuNode = weakTargetNode.Upgrade();
        CHECK_NULL_VOID(menuNode);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMenuLongPress(info, menuNode, menuItems);
    };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gestureHub->SetLongPressEvent(longPressEvent);

    auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
    CHECK_NULL_VOID(longPressRecognizer);

    auto longPressEndCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMenuLongPressActionEnd();
    };
    longPressRecognizer->SetOnActionEnd(longPressEndCallback);
}

void TitleBarPattern::HandleMenuLongPress(
    const GestureEvent& info, const RefPtr<FrameNode>& menuNode, const std::vector<NG::BarItem>& menuItems)
{
    CHECK_NULL_VOID(menuNode);
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<AgingAdapationDialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    float scale = pipeline->GetFontScale();
    if (LessNotEqual(scale, dialogTheme->GetBigFontSizeScale())) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "The current system font scale is %{public}f; dialogTheme font scale is %{public}f", scale,
            dialogTheme->GetBigFontSizeScale());
        return;
    }
    auto menuItemNode = menuNode->FindChildByPosition(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY());
    CHECK_NULL_VOID(menuItemNode);
    auto index = menuNode->GetChildIndex(menuItemNode);
    auto dialogNode =
        NavigationTitleUtil::CreatePopupDialogNode(menuItemNode, menuItems, index, hostNode->GetThemeScopeId());
    CHECK_NULL_VOID(dialogNode);
    if (GetLargeFontPopUpDialogNode()) {
        HandleMenuLongPressActionEnd();
    }
    SetLargeFontPopUpDialogNode(dialogNode);
}

void TitleBarPattern::HandleMenuLongPressActionEnd()
{
    auto dialogNode = GetLargeFontPopUpDialogNode();
    CHECK_NULL_VOID(dialogNode);
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto menuNode = AceType::DynamicCast<FrameNode>(hostNode->GetMenu());
    CHECK_NULL_VOID(menuNode);
    if (moveIndex_.has_value()) {
        auto menuItemNode = AceType::DynamicCast<FrameNode>(menuNode->GetChildAtIndex(moveIndex_.value()));
        CHECK_NULL_VOID(menuItemNode);
        auto renderContext = menuItemNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto theme = NavigationGetTheme();
        CHECK_NULL_VOID(theme);
        renderContext->UpdateBackgroundColor(theme->GetCompBackgroundColor());
        renderContext->ResetBlendBgColor();
        moveIndex_.reset();
    }
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode);
    SetLargeFontPopUpDialogNode(nullptr);
}

bool TitleBarPattern::CustomizeExpandSafeArea()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    return RunCustomizeExpandIfNeeded(host);
}

void TitleBarPattern::SetTextColor(const RefPtr<FrameNode>& textNode, const Color& color)
{
    CHECK_NULL_VOID(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    auto property = textNode->GetLayoutPropertyPtr<TextLayoutProperty>();
    CHECK_NULL_VOID(property);
    property->UpdateTextColor(color);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, textNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, textNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, textNode);
}

void TitleBarPattern::SetTextShadow(const RefPtr<FrameNode>& textNode, const std::vector<Shadow>& shadows)
{
    CHECK_NULL_VOID(textNode);
    TextModelNG::SetTextShadow(AceType::RawPtr(textNode), shadows);
}

void TitleBarPattern::SetBackButtonIconColor(const RefPtr<TitleBarNode>& titleBarNode, const Color& iconColor)
{
    CHECK_NULL_VOID(titleBarNode);
    auto backButton = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButton);
    if (backButton->GetTag() == "Navigator") {
        backButton = AceType::DynamicCast<FrameNode>(backButton->GetChildren().front());
        CHECK_NULL_VOID(backButton);
    }
    auto backButtonImgNode = AceType::DynamicCast<FrameNode>(backButton->GetChildren().front());
    CHECK_NULL_VOID(backButtonImgNode);
    if (backButtonImgNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto textLayoutProperty = backButtonImgNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateSymbolColorList({ iconColor });
    }
    backButtonImgNode->MarkModifyDone();
}

void TitleBarPattern::SetMenuItemsStyle(
    const RefPtr<TitleBarNode>& titleBarNode, const Color& iconColor, const Color& textColor)
{
    CHECK_NULL_VOID(titleBarNode);
    auto menuNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetMenu());
    CHECK_NULL_VOID(menuNode);
    for (const auto& child : menuNode->GetChildren()) {
        auto menuItemButton = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(menuItemButton);
        auto barItemNode = AceType::DynamicCast<BarItemNode>(menuItemButton->GetChildren().front());
        CHECK_NULL_VOID(barItemNode);
        auto iconNode = AceType::DynamicCast<FrameNode>(barItemNode->GetIconNode());
        if (iconNode && iconNode->GetTag() == V2::SYMBOL_ETS_TAG) {
            auto textLayoutProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
            if (textLayoutProperty) {
                textLayoutProperty->UpdateSymbolColorList({ iconColor });
            }
            iconNode->MarkModifyDone();
        }
        auto textNode = AceType::DynamicCast<FrameNode>(barItemNode->GetTextNode());
        if (textNode) {
            auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
            if (textLayoutProperty) {
                textLayoutProperty->UpdateTextColor(textColor);
            }
            textNode->MarkModifyDone();
        }
    }
}

void TitleBarPattern::SetDividerStyle(
    const RefPtr<FrameNode>& dividerNode, const NavigationTitleBarDividerStyle& dividerStyle)
{
    CHECK_NULL_VOID(dividerNode);
    auto renderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    if (renderProperty) {
        renderProperty->UpdateDividerColor(dividerStyle.color);
    }
    auto renderContext = dividerNode->GetRenderContext();
    if (renderContext) {
        renderContext->UpdateOpacity(dividerStyle.opacity);
    }
    dividerNode->MarkModifyDone();
}
} // namespace OHOS::Ace::NG
