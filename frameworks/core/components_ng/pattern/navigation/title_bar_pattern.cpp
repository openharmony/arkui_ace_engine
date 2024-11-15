/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/animation/spring_curve.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t DEFAULT_ANIMATION_DURATION = 200;
constexpr int32_t TITLE_RATIO = 2;

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

void UpdateSymbolBackButton(const RefPtr<FrameNode>& backButtonNode, const RefPtr<FrameNode>& backButtonIconNode,
    const RefPtr<TitleBarLayoutProperty>& titleBarLayoutProperty)
{
    auto theme = NavigationGetTheme();
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
        symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetBackSymbolId()));
        symbolProperty->UpdateSymbolColorList({ theme->GetBackButtonIconColor() });
        if (theme) {
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
        auto iconColor = theme->GetBackButtonIconColor();
        auto backResourceId = theme->GetBackResourceId();

        imageSourceInfo.SetResourceId(backResourceId);
        imageSourceInfo.SetFillColor(iconColor);
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
        UpdateSymbolBackButton(backButtonNode, backButtonIconNode, titleBarLayoutProperty);
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

void MountSubTitle(const RefPtr<TitleBarNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto subtitleNode = AceType::DynamicCast<FrameNode>(hostNode->GetSubtitle());
    CHECK_NULL_VOID(subtitleNode);
    auto titleLayoutProperty = subtitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(titleLayoutProperty);

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto subTitleSize = theme->GetSubTitleFontSize();
    auto textHeightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        subTitleSize = theme->GetSubTitleFontSizeS();
        textHeightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::MINI) {
        titleLayoutProperty->UpdateHeightAdaptivePolicy(textHeightAdaptivePolicy);
    }
    titleLayoutProperty->UpdateAdaptMinFontSize(MIN_ADAPT_SUBTITLE_FONT_SIZE);
    titleLayoutProperty->UpdateAdaptMaxFontSize(subTitleSize);
    titleLayoutProperty->UpdateMaxFontScale(STANDARD_FONT_SCALE);

    // set titleBar subTitle inspectorId
    auto parentType = titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR);
    std::string parentId = hostNode->GetInnerParentId();
    std::string field = NG::NAV_FIELD;
    if (parentType == TitleBarParentType::NAV_DESTINATION) {
        field = NG::DES_FIELD;
    }
    NavigationTitleUtil::SetInnerChildId(subtitleNode, field, subtitleNode->GetTag(), "SubTitle", parentId);
    subtitleNode->MarkModifyDone();
}

} // namespace

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
    std::string parentId = hostNode->GetInnerParentId();
    NavigationTitleUtil::SetInnerChildId(titleNode, NG::NAV_FIELD, titleNode->GetTag(), "MainTitle", parentId);

    // update main title layout property
    auto titleLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(titleLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto currentFontSize = titleLayoutProperty->GetFontSizeValue(Dimension(0));
    auto currentMaxLine = titleLayoutProperty->GetMaxLinesValue(0);
    auto titleMode = titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE);
    auto titleFontSize = theme->GetTitleFontSizeBig();
    auto maxFontSize = theme->GetTitleFontSizeBig();
    auto miniTitleFontSize = theme->GetTitleFontSize();
    auto miniTitleFontSizeMin = theme->GetTitleFontSizeMin();
    auto textHeightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        titleFontSize = theme->GetMainTitleFontSizeL();
        maxFontSize = theme->GetMainTitleFontSizeL();
        miniTitleFontSize = theme->GetMainTitleFontSizeM();
        miniTitleFontSizeMin = theme->GetMainTitleFontSizeS();
        textHeightAdaptivePolicy = hostNode->GetSubtitle() ? TextHeightAdaptivePolicy::MAX_LINES_FIRST :
            TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    }
    if (titleMode == NavigationTitleMode::MINI) {
        if (titleBarLayoutProperty->HasHideBackButton() && titleBarLayoutProperty->GetHideBackButtonValue()) {
            titleLayoutProperty->UpdateFontSize(miniTitleFontSize);
            titleLayoutProperty->UpdateAdaptMaxFontSize(miniTitleFontSize);
        } else {
            titleLayoutProperty->UpdateFontSize(miniTitleFontSizeMin);
            titleLayoutProperty->UpdateAdaptMaxFontSize(miniTitleFontSizeMin);
        }
        UpdateSubTitleOpacity(1.0);
    } else if (titleMode == NavigationTitleMode::FULL) {
        titleLayoutProperty->UpdateFontSize(titleFontSize);
        titleLayoutProperty->UpdateAdaptMaxFontSize(maxFontSize);
        UpdateSubTitleOpacity(1.0);
    } else {
        if (fontSize_.has_value()) {
            titleLayoutProperty->UpdateFontSize(fontSize_.value());
            titleLayoutProperty->UpdateAdaptMaxFontSize(fontSize_.value());
        } else {
            titleLayoutProperty->UpdateFontSize(titleFontSize);
            titleLayoutProperty->UpdateAdaptMaxFontSize(maxFontSize);
        }
        if (opacity_.has_value()) {
            UpdateSubTitleOpacity(opacity_.value());
        } else {
            UpdateSubTitleOpacity(1.0);
        }
    }

    titleLayoutProperty->UpdateAdaptMinFontSize(MIN_ADAPT_TITLE_FONT_SIZE);
    titleLayoutProperty->UpdateHeightAdaptivePolicy(textHeightAdaptivePolicy);
    titleLayoutProperty->UpdateMaxFontScale(STANDARD_FONT_SCALE);
    auto maxLines = hostNode->GetSubtitle() ? 1 : TITLEBAR_MAX_LINES;
    titleLayoutProperty->UpdateMaxLines(maxLines);
    if (currentFontSize != titleLayoutProperty->GetFontSizeValue(Dimension(0)) ||
        currentMaxLine != titleLayoutProperty->GetMaxLinesValue(0)) {
        titleLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
    titleNode->MarkModifyDone();
    titleNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void TitleBarPattern::UpdateNavDesTitleProperty(const RefPtr<TitleBarNode>& hostNode)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetParent());
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto titleNode = AceType::DynamicCast<FrameNode>(hostNode->GetTitle());
    CHECK_NULL_VOID(titleNode);

    // if navdestination titleBar main title is custom, just return
    if (navDestinationGroupNode->GetPrevTitleIsCustomValue(false)) {
        return;
    }
    // if navdestination titleBar main title is not custom, set inspectorId
    std::string parentId = hostNode->GetInnerParentId();
    NavigationTitleUtil::SetInnerChildId(titleNode, NG::DES_FIELD, titleNode->GetTag(),
        "MainTitle", parentId);
}

void TitleBarPattern::MountTitle(const RefPtr<TitleBarNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    UpdateNavDesTitleProperty(hostNode);
    UpdateNavBarTitleProperty(hostNode);
}

void TitleBarPattern::MountMenu(const RefPtr<TitleBarNode>& hostNode, bool isWindowSizeChange)
{
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) !=
        TitleBarParentType::NAV_DESTINATION) {
        return;
    }
    if (hostNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        hostNode->RemoveChild(hostNode->GetPrevMenu());
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (hostNode->GetPrevMenuIsCustomValue(false)) {
        if (hostNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
            return;
        }
        hostNode->SetPrevMenu(hostNode->GetMenu());
        hostNode->AddChild(hostNode->GetMenu());
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        auto titleBarMenuItems = GetTitleBarMenuItems();
        if (HasMenuNodeId()) {
            if (hostNode->GetChildIndexById(GetMenuNodeId()) > -1 && !isWindowSizeChange) {
                return;
            }
            auto navDesNode = AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetParent());
            CHECK_NULL_VOID(navDesNode);
            auto hub = navDesNode->GetEventHub<EventHub>();
            CHECK_NULL_VOID(hub);
            auto isButtonEnabled = hub->IsEnabled();
            auto menuNode =
                NavigationTitleUtil::CreateMenuItems(GetMenuNodeId(), titleBarMenuItems, hostNode, isButtonEnabled);
            CHECK_NULL_VOID(menuNode);
            hostNode->SetMenu(menuNode);
            hostNode->SetPrevMenu(menuNode);
            hostNode->AddChild(hostNode->GetMenu());
            hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void TitleBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (isInitialTitle_) {
        InitTitleParam();
    }
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountBackButton(hostNode);
    MountTitle(hostNode);
    MountSubTitle(hostNode);
    MountMenu(hostNode);
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

void TitleBarPattern::ProcessTitleDragStart(float offset)
{
    if (Positive(overDragOffset_)) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE ||
        IsHidden()) {
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
    SetMaxTitleBarHeight();
    SetTempTitleBarHeight(offset);
    minTitleOffsetY_ = (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - minTitleHeight_) / 2.0f;
    maxTitleOffsetY_ = initialTitleOffsetY_;
    moveRatio_ = (maxTitleOffsetY_ - minTitleOffsetY_) /
                 (maxTitleBarHeight_ - static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    titleMoveDistance_ = (GetTempTitleBarHeight() - defaultTitleBarHeight_) * moveRatio_;
    defaultTitleOffsetY_ = currentTitleOffsetY_;
    SetTempTitleOffsetY();
    defaultSubtitleOffsetY_ = GetSubTitleOffsetY();
    SetTempSubTitleOffsetY();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    // title font size
    SetDefaultTitleFontSize();
    auto mappedOffset = GetMappedOffset(offset);
    auto tempFontSize = GetFontSize(mappedOffset);
    UpdateTitleFontSize(tempFontSize);

    // subTitle Opacity
    SetDefaultSubtitleOpacity();
    auto tempOpacity = GetSubtitleOpacity();
    UpdateSubTitleOpacity(tempOpacity);

    isFreeTitleUpdated_ = true;
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

void TitleBarPattern::ProcessTitleDragEnd()
{
    if (Positive(overDragOffset_)) {
        return;
    }
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) != NavigationTitleMode::FREE ||
        IsHidden()) {
        return;
    }

    if (Positive(overDragOffset_)) {
        SpringAnimation(overDragOffset_, 0);
    }
    if (CanOverDrag_ || isTitleScaleChange_) {
        auto titleMiddleValue =
            (static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) + maxTitleBarHeight_) / TITLE_RATIO;
        if (LessNotEqual(GetTempTitleBarHeight(), titleMiddleValue) ||
            NearEqual(GetTempTitleBarHeight(), titleMiddleValue)) {
            AnimateTo(static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()) - defaultTitleBarHeight_);
            return;
        } else if (GreatNotEqual(GetTempTitleBarHeight(), titleMiddleValue)) {
            AnimateTo(maxTitleBarHeight_ - defaultTitleBarHeight_);
            return;
        }
    }
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
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
        }, [weakPattern = AceType::WeakClaim(this)]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->CleanSpringAnimation();
        });
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

void TitleBarPattern::AnimateTo(float offset)
{
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);

    animation_ = AnimationUtils::StartAnimation(
        option,
        [weakPattern = AceType::WeakClaim(this), offset]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            pattern->ProcessTitleDragUpdate(offset);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto pipeline = PipelineContext::GetCurrentContext();
            if (pipeline) {
                pipeline->FlushUITasks();
            }
        }, [weakPattern = AceType::WeakClaim(this)]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->CleanAnimation();
        });
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
    host->GetRenderContext()->SetClipToFrame(true);

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_TOP };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
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
    } else if (GreatNotEqual(finalHeight, middleHeight) && LessNotEqual(finalHeight, maxTitleBarHeight_)) {
        // The finalHeight is between the middleHeight and the maxTitleBarHeight_, so animate to max title.
        AnimateTo(maxTitleBarHeight_ - defaultTitleBarHeight_);
    } else if (GreatNotEqual(finalHeight, maxTitleBarHeight_)) {
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

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(host);
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
    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting height of this update is greater than the maxTitleBarHeight_, so the navigation component
        // does not handle the offset.
        offsetHandled = 0.0f;
    } else if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting position height of this update is smaller than the minHeight, so the navigation component
        // only handles offsets from minHeight to maxTitleBarHeight_.
        offsetHandled = maxTitleBarHeight_ - minHeight;
    } else {
        // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
        // navigation component only handles offsets from defaultTitleBarHeight_ to maxTitleBarHeight_.
        offsetHandled = offset - (coordScrollOffset_ - (maxTitleBarHeight_ - defaultTitleBarHeight_));
    }
    return offsetHandled;
}

float TitleBarPattern::CalculateHandledOffsetBetweenMinAndMaxTitle(float offset, float lastCordScrollOffset)
{
    float offsetHandled = 0.0f;
    float minHeight = static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
    if (LessOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, minHeight)) {
        // The starting height of this update is smaller than the minHeight, so the navigation component only
        // handles offsets from minHeight to target height.
        offsetHandled = defaultTitleBarHeight_ + coordScrollOffset_ - minHeight;
    } else if (GreatOrEqual(defaultTitleBarHeight_ + lastCordScrollOffset, maxTitleBarHeight_)) {
        // The starting position height of this update is greater than the maxTitleBarHeight_, so the navigation
        // component only handles offsets from maxTitleBarHeight_ to target height.
        offsetHandled = coordScrollOffset_ - (maxTitleBarHeight_ - defaultTitleBarHeight_);
    } else {
        // The starting position height of this update is between the minHeight and the maxTitleBarHeight_, so the
        // navigation component handles all of the offset.
        offsetHandled = offset;
    }
    return offsetHandled;
}

void TitleBarPattern::SetTitlebarOptions(NavigationTitlebarOptions&& opt)
{
    if (opt == options_) {
        return;
    }

    options_ = std::move(opt);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateBackgroundStyle(host);
}

void TitleBarPattern::UpdateBackgroundStyle(RefPtr<FrameNode>& host)
{
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (options_.bgOptions.color.has_value()) {
        renderContext->UpdateBackgroundColor(options_.bgOptions.color.value());
    } else {
        renderContext->ResetBackgroundColor();
    }
    if (options_.bgOptions.blurStyle.has_value()) {
        BlurStyleOption blur;
        blur.blurStyle = options_.bgOptions.blurStyle.value();
        renderContext->UpdateBackBlurStyle(blur);
    } else {
        renderContext->ResetBackBlurStyle();
    }
}

void TitleBarPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
}

void TitleBarPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (titleBarLayoutProperty->GetTitleBarParentTypeValue(TitleBarParentType::NAVBAR) !=
        TitleBarParentType::NAV_DESTINATION) {
        return;
    }
    // change menu num in landscape and orientation
    do {
        if (titleBarNode->GetPrevMenuIsCustomValue(false)) {
            break;
        }
        auto targetNum = SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE ? MAX_MENU_NUM_LARGE
                                                                                                  : MAX_MENU_NUM_SMALL;
        if (targetNum == maxMenuNums_) {
            break;
        }
        maxMenuNums_ = targetNum;
        MountMenu(titleBarNode, true);
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } while (0);
}
} // namespace OHOS::Ace::NG
