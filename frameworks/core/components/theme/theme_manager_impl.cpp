/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "core/components/theme/theme_manager_impl.h"

#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/resource/resource_manager.h"
#include "core/components/badge/badge_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/camera/camera_theme.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/clock/clock_theme.h"
#include "core/components/close_icon/close_icon_theme.h"
#include "core/components/counter/counter_theme.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/divider/divider_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/focus_animation/focus_animation_theme.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components/image/image_theme.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components/list/list_item_theme.h"
#include "core/components/list/list_theme.h"
#include "core/components/list/arc_list_item_theme.h"
#include "core/components/list/arc_list_theme.h"
#include "core/components/marquee/marquee_theme.h"
#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/piece/piece_theme.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/progress/progress_theme.h"
#include "core/components/qrcode/qrcode_theme.h"
#include "core/components/rating/rating_theme.h"
#include "core/components/refresh/refresh_theme.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components/search/search_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/semi_modal/semi_modal_theme.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/stepper/stepper_theme.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/advanced_pattern_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components/theme/blur_style_theme.h"
#include "core/components/theme/card_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components/tool_bar/tool_bar_theme.h"
#include "core/components/video/video_theme.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/form/form_theme.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/side_bar/side_bar_theme.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "core/components_ng/pattern/grid/grid_item_theme.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_theme.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/components_ng/pattern/select/select_theme_wrapper.h"
#include "core/components_ng/pattern/swiper/swiper_theme.h"
#include "core/components_ng/pattern/toggle/switch_theme_wrapper.h"
#include "core/components_ng/pattern/toggle/toggle_theme_wrapper.h"
#include "core/components_ng/token_theme/token_theme_storage.h"
#include "core/components_ng/pattern/checkbox/checkbox_theme_wrapper.h"
#include "core/components_ng/pattern/counter/counter_theme_wrapper.h"
#include "frameworks/core/components/text_clock/text_clock_theme.h"
#include "core/components_ng/pattern/text_clock/text_clock_theme_wrapper.h"
#include "core/components_ng/pattern/progress/progress_theme_wrapper.h"
#include "core/components_ng/pattern/divider/divider_theme_wrapper.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme_wrapper.h"
#include "core/components_ng/pattern/search/search_theme_wrapper.h"
#include "core/components_ng/pattern/slider/slider_theme_wrapper.h"
#include "core/components_ng/pattern/text/text_theme_wrapper.h"
#include "core/components_ng/pattern/text_field/text_field_theme_wrapper.h"
#include "core/components_ng/pattern/picker/picker_theme_wrapper.h"
#include "core/components_ng/pattern/navigation/navigation_bar_theme_wrapper.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme_wrapper.h"
#include "core/components_ng/pattern/side_bar/side_bar_theme_wrapper.h"

namespace OHOS::Ace {
namespace {
template<class T>
RefPtr<Theme> ThemeBuildFunc(const RefPtr<ThemeConstants>& themeConstants)
{
    return T().Build(themeConstants);
}

const std::unordered_map<ThemeType, RefPtr<Theme>(*)(const RefPtr<ThemeConstants>& themeConstants)> THEME_BUILDERS = {
    { AppTheme::TypeId(), &ThemeBuildFunc<AppTheme::Builder> },
    { ButtonTheme::TypeId(), &ThemeBuildFunc<ButtonTheme::Builder> },
    { PickerTheme::TypeId(), &ThemeBuildFunc<PickerTheme::Builder> },
    { CheckboxTheme::TypeId(), &ThemeBuildFunc<CheckboxTheme::Builder> },
    { SwitchTheme::TypeId(), &ThemeBuildFunc<SwitchTheme::Builder> },
    { RadioTheme::TypeId(), &ThemeBuildFunc<RadioTheme::Builder> },
    { DialogTheme::TypeId(), &ThemeBuildFunc<DialogTheme::Builder> },
    { MarqueeTheme::TypeId(), &ThemeBuildFunc<MarqueeTheme::Builder> },
    { NavigationBarTheme::TypeId(), &ThemeBuildFunc<NavigationBarTheme::Builder> },
    { SelectTheme::TypeId(), &ThemeBuildFunc<SelectTheme::Builder> },
    { SliderTheme::TypeId(), &ThemeBuildFunc<SliderTheme::Builder> },
    { SwiperIndicatorTheme::TypeId(), &ThemeBuildFunc<SwiperIndicatorTheme::Builder> },
    { PopupTheme::TypeId(), &ThemeBuildFunc<PopupTheme::Builder> },
    { ProgressTheme::TypeId(), &ThemeBuildFunc<ProgressTheme::Builder> },
    { VideoTheme::TypeId(), &ThemeBuildFunc<VideoTheme::Builder> },
    { TabTheme::TypeId(), &ThemeBuildFunc<TabTheme::Builder> },
    { RefreshTheme::TypeId(), &ThemeBuildFunc<RefreshTheme::Builder> },
    { ListTheme::TypeId(), &ThemeBuildFunc<ListTheme::Builder> },
    { ListItemTheme::TypeId(), &ThemeBuildFunc<ListItemTheme::Builder> },
    { ArcListTheme::TypeId(), &ThemeBuildFunc<ArcListTheme::Builder> },
    { ArcListItemTheme::TypeId(), &ThemeBuildFunc<ArcListItemTheme::Builder> },
    { ToastTheme::TypeId(), &ThemeBuildFunc<ToastTheme::Builder> },
    { TextTheme::TypeId(), &ThemeBuildFunc<TextTheme::Builder> },
    { TextClockTheme::TypeId(), &ThemeBuildFunc<TextClockTheme::Builder> },
    { RatingTheme::TypeId(), &ThemeBuildFunc<RatingTheme::Builder> },
    { TextFieldTheme::TypeId(), &ThemeBuildFunc<TextFieldTheme::Builder> },
    { FocusAnimationTheme::TypeId(), &ThemeBuildFunc<FocusAnimationTheme::Builder> },
    { ScrollBarTheme::TypeId(), &ThemeBuildFunc<ScrollBarTheme::Builder> },
    { CalendarTheme::TypeId(), &ThemeBuildFunc<CalendarTheme::Builder> },
    { SearchTheme::TypeId(), &ThemeBuildFunc<SearchTheme::Builder> },
    { TextOverlayTheme::TypeId(), &ThemeBuildFunc<TextOverlayTheme::Builder> },
    { DividerTheme::TypeId(), &ThemeBuildFunc<DividerTheme::Builder> },
    { ToggleTheme::TypeId(), &ThemeBuildFunc<ToggleTheme::Builder> },
    { ClockTheme::TypeId(), &ThemeBuildFunc<ClockTheme::Builder> },
    { DataPanelTheme::TypeId(), &ThemeBuildFunc<DataPanelTheme::Builder> },
    { BadgeTheme::TypeId(), &ThemeBuildFunc<BadgeTheme::Builder> },
    { PieceTheme::TypeId(), &ThemeBuildFunc<PieceTheme::Builder> },
    { StepperTheme::TypeId(), &ThemeBuildFunc<StepperTheme::Builder> },
    { ToolBarTheme::TypeId(), &ThemeBuildFunc<ToolBarTheme::Builder> },
    { CardTheme::TypeId(), &ThemeBuildFunc<CardTheme::Builder> },
    { QrcodeTheme::TypeId(), &ThemeBuildFunc<QrcodeTheme::Builder> },
    { CameraTheme::TypeId(), &ThemeBuildFunc<CameraTheme::Builder> },
    { HyperlinkTheme::TypeId(), &ThemeBuildFunc<HyperlinkTheme::Builder> },
    { ImageTheme::TypeId(), &ThemeBuildFunc<ImageTheme::Builder> },
    { CounterTheme::TypeId(), &ThemeBuildFunc<CounterTheme::Builder> },
    { DragBarTheme::TypeId(), &ThemeBuildFunc<DragBarTheme::Builder> },
    { SemiModalTheme::TypeId(), &ThemeBuildFunc<SemiModalTheme::Builder> },
    { IconTheme::TypeId(), &ThemeBuildFunc<IconTheme::Builder> },
    { V2::PatternLockTheme::TypeId(), &ThemeBuildFunc<V2::PatternLockTheme::Builder> },
    { IndexerTheme::TypeId(), &ThemeBuildFunc<IndexerTheme::Builder> },
    { NG::AppBarTheme::TypeId(), &ThemeBuildFunc<NG::AppBarTheme::Builder> },
    { AdvancedPatternTheme::TypeId(), &ThemeBuildFunc<AdvancedPatternTheme::Builder> },
    { NG::SecurityComponentTheme::TypeId(), &ThemeBuildFunc<NG::SecurityComponentTheme::Builder> },
    { NG::FormTheme::TypeId(), &ThemeBuildFunc<NG::FormTheme::Builder> },
    { CloseIconTheme::TypeId(), &ThemeBuildFunc<CloseIconTheme::Builder> },
    { NG::SideBarTheme::TypeId(), &ThemeBuildFunc<NG::SideBarTheme::Builder> },
    { NG::RichEditorTheme::TypeId(), &ThemeBuildFunc<NG::RichEditorTheme::Builder> },
    { NG::GridItemTheme::TypeId(), &ThemeBuildFunc<NG::GridItemTheme::Builder> },
    { NG::MenuTheme::TypeId(), &ThemeBuildFunc<NG::MenuTheme::Builder> },
    { NG::GaugeTheme::TypeId(), &ThemeBuildFunc<NG::GaugeTheme::Builder> },
    { NG::SheetTheme::TypeId(), &ThemeBuildFunc<NG::SheetTheme::Builder> },
    { BlurStyleTheme::TypeId(), &ThemeBuildFunc<BlurStyleTheme::Builder> },
    { ShadowTheme::TypeId(), &ThemeBuildFunc<ShadowTheme::Builder> },
    { NG::ContainerModalTheme::TypeId(), &ThemeBuildFunc<NG::ContainerModalTheme::Builder> },
    { AgingAdapationDialogTheme::TypeId(), &ThemeBuildFunc<AgingAdapationDialogTheme::Builder> },
    { NG::ScrollableTheme::TypeId(), &ThemeBuildFunc<NG::ScrollableTheme::Builder> },
    { NG::SwiperTheme::TypeId(), &ThemeBuildFunc<NG::SwiperTheme::Builder> },
    { NG::LinearIndicatorTheme::TypeId(), &ThemeBuildFunc<NG::LinearIndicatorTheme::Builder> },
};

template<class T>
RefPtr<TokenThemeWrapper> ThemeWrapperBuildFunc(const RefPtr<ThemeConstants>& themeConstants)
{
    return T().BuildWrapper(themeConstants);
}

const std::unordered_map<ThemeType, RefPtr<TokenThemeWrapper>(*)(const RefPtr<ThemeConstants>&)>
    TOKEN_THEME_WRAPPER_BUILDERS = {
        { CheckboxTheme::TypeId(), &ThemeWrapperBuildFunc<NG::CheckboxThemeWrapper::WrapperBuilder> },
        { SwitchTheme::TypeId(), &ThemeWrapperBuildFunc<NG::SwitchThemeWrapper::WrapperBuilder> },
        { ToggleTheme::TypeId(), &ThemeWrapperBuildFunc<NG::ToggleThemeWrapper::WrapperBuilder> },
        { CounterTheme::TypeId(), &ThemeWrapperBuildFunc<NG::CounterThemeWrapper::WrapperBuilder> },
        { TextClockTheme::TypeId(), &ThemeWrapperBuildFunc<NG::TextClockThemeWrapper::WrapperBuilder> },
        { DividerTheme::TypeId(), &ThemeWrapperBuildFunc<NG::DividerThemeWrapper::WrapperBuilder> },
        { NG::RichEditorTheme::TypeId(), &ThemeWrapperBuildFunc<NG::RichEditorThemeWrapper::WrapperBuilder> },
        { SearchTheme::TypeId(), &ThemeWrapperBuildFunc<NG::SearchThemeWrapper::WrapperBuilder> },
        { SliderTheme::TypeId(), &ThemeWrapperBuildFunc<NG::SliderThemeWrapper::WrapperBuilder> },
        { TextTheme::TypeId(), &ThemeWrapperBuildFunc<NG::TextThemeWrapper::WrapperBuilder> },
        { TextFieldTheme::TypeId(), &ThemeWrapperBuildFunc<NG::TextFieldThemeWrapper::WrapperBuilder> },
        { PickerTheme::TypeId(), &ThemeWrapperBuildFunc<NG::PickerThemeWrapper::WrapperBuilder> },
        { ProgressTheme::TypeId(), &ThemeWrapperBuildFunc<NG::ProgressThemeWrapper::WrapperBuilder> },
        { SelectTheme::TypeId(), &ThemeWrapperBuildFunc<NG::SelectThemeWrapper::WrapperBuilder> },
        { NavigationBarTheme::TypeId(), &ThemeWrapperBuildFunc<NG::NavigationBarThemeWrapper::WrapperBuilder> },
        { AgingAdapationDialogTheme::TypeId(),
            &ThemeWrapperBuildFunc<NG::AgingAdapationDialogThemeWrapper::WrapperBuilder> },
        { NG::SideBarTheme::TypeId(), &ThemeWrapperBuildFunc<NG::SideBarThemeWrapper::WrapperBuilder> }
    };

std::unordered_map<ThemeType, Ace::Kit::BuildFunc> THEME_BUILDERS_KIT;
std::unordered_map<ThemeType, Ace::Kit::BuildThemeWrapperFunc> TOKEN_THEME_WRAPPER_BUILDERS_KIT;
} // namespace

ThemeManagerImpl::ThemeManagerImpl()
{
    auto resAdapter = ResourceAdapter::Create();
    themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(resAdapter);
}

ThemeManagerImpl::ThemeManagerImpl(RefPtr<ResourceAdapter>& resourceAdapter)
{
    themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(resourceAdapter);
}

void ThemeManagerImpl::RegisterThemeKit(ThemeType type, Ace::Kit::BuildFunc func)
{
    auto findIter = themes_.find(type);
    if (findIter != themes_.end()) {
        return;
    }
    THEME_BUILDERS_KIT.insert({ type, func });
}

RefPtr<Theme> ThemeManagerImpl::GetTheme(ThemeType type)
{
    auto findIter = themes_.find(type);
    if (findIter != themes_.end()) {
        return findIter->second;
    }

    auto theme = GetThemeKit(type);
    CHECK_NULL_RETURN(theme, GetThemeOrigin(type));
    return theme;
}

RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type)
{
    auto builderIter = THEME_BUILDERS.find(type);
    if (builderIter == THEME_BUILDERS.end()) {
        return nullptr;
    }

    if (auto pipelineContext = NG::PipelineContext::GetCurrentContext(); pipelineContext) {
        ColorMode localMode = pipelineContext->GetLocalColorMode();
        ColorMode systemMode = pipelineContext->GetColorMode();
        bool needRestore = false;
        if (localMode != ColorMode::COLOR_MODE_UNDEFINED && localMode != systemMode) {
            // Ordinary themes should work in system color mode. Only theme wrappers support local color mode.
            ResourceManager::GetInstance().UpdateColorMode(systemMode);
            pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
            needRestore = true;
        }
        auto theme = builderIter->second(themeConstants_);
        if (needRestore) {
            pipelineContext->SetLocalColorMode(localMode);
            ResourceManager::GetInstance().UpdateColorMode(localMode);
        }
        themes_.emplace(type, theme);
        return theme;
    }
    
    auto theme = builderIter->second(themeConstants_);
    themes_.emplace(type, theme);
    return theme;
}

RefPtr<Theme> ThemeManagerImpl::GetThemeKit(ThemeType type)
{
    auto builderIterKit = THEME_BUILDERS_KIT.find(type);
    if (builderIterKit == THEME_BUILDERS_KIT.end()) {
        return nullptr;
    }

    if (auto pipelineContext = NG::PipelineContext::GetCurrentContext(); pipelineContext) {
        ColorMode localMode = pipelineContext->GetLocalColorMode();
        ColorMode systemMode = pipelineContext->GetColorMode();
        bool needRestore = false;
        if (localMode != ColorMode::COLOR_MODE_UNDEFINED && localMode != systemMode) {
            // Ordinary themes should work in system color mode. Only theme wrappers support local color mode.
            ResourceManager::GetInstance().UpdateColorMode(systemMode);
            pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
            needRestore = true;
        }
        auto theme = builderIterKit->second();
        if (needRestore) {
            pipelineContext->SetLocalColorMode(localMode);
            ResourceManager::GetInstance().UpdateColorMode(localMode);
        }
        themes_.emplace(type, theme);
        return theme;
    }
    
    auto theme = builderIterKit->second();
    themes_.emplace(type, theme);
    return theme;
}


void ThemeManagerImpl::RegisterCustomThemeKit(ThemeType type, Ace::Kit::BuildThemeWrapperFunc func)
{
    auto findIter = TOKEN_THEME_WRAPPER_BUILDERS_KIT.find(type);
    if (findIter != TOKEN_THEME_WRAPPER_BUILDERS_KIT.end()) {
        return;
    }
    TOKEN_THEME_WRAPPER_BUILDERS_KIT.insert({ type, func });
}

RefPtr<Theme> ThemeManagerImpl::GetTheme(ThemeType type, TokenThemeScopeId themeScopeId)
{
    auto theme = GetThemeKit(type, themeScopeId);
    CHECK_NULL_RETURN(theme, GetThemeOrigin(type, themeScopeId));
    return theme;
}

RefPtr<Theme> ThemeManagerImpl::GetThemeOrigin(ThemeType type, int32_t themeScopeId)
{
    auto tokenTheme = NG::TokenThemeStorage::GetInstance()->GetTheme(themeScopeId);
    if (!tokenTheme) {
        return GetTheme(type);
    }

    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, GetTheme(type));
    ColorMode currentMode = GetCurrentColorMode();
    ColorMode themeMode = tokenTheme->GetColorMode();
    auto& themeWrappers = GetThemeWrappers(themeMode == ColorMode::COLOR_MODE_UNDEFINED ? currentMode : themeMode);
    auto findIter = themeWrappers.find(type);
    if (findIter != themeWrappers.end()) {
        auto wrapper = findIter->second;
        wrapper->ApplyTokenTheme(*tokenTheme);
        return AceType::DynamicCast<Theme>(wrapper);
    }

    auto builderIter = TOKEN_THEME_WRAPPER_BUILDERS.find(type);
    if (builderIter == TOKEN_THEME_WRAPPER_BUILDERS.end()) {
        return GetTheme(type);
    }

    bool needRestore = false;
    if (themeMode != ColorMode::COLOR_MODE_UNDEFINED && themeMode != currentMode) {
        // Local color mode of the current theme does not match actual color scheme.
        // Current color mode is system. Need to switch to local color mode temporarily.
        ResourceManager::GetInstance().UpdateColorMode(themeMode);
        pipelineContext->SetLocalColorMode(themeMode);
        needRestore = true;
    }
    auto wrapper = builderIter->second(themeConstants_);
    if (needRestore) {
        // Switching resource manager back into system color mode
        pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
        ResourceManager::GetInstance().UpdateColorMode(currentMode);
    }
    wrapper->ApplyTokenTheme(*tokenTheme);
    themeWrappers.emplace(type, wrapper);
    return AceType::DynamicCast<Theme>(wrapper);
}

RefPtr<Theme> ThemeManagerImpl::GetThemeKit(ThemeType type, int32_t themeScopeId)
{
    auto tokenTheme = NG::TokenThemeStorage::GetInstance()->GetTheme(themeScopeId);
    if (!tokenTheme) {
        return GetTheme(type);
    }

    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, GetTheme(type));
    ColorMode currentMode = GetCurrentColorMode();
    ColorMode themeMode = tokenTheme->GetColorMode();
    auto& themeWrappers = GetThemeWrappers(themeMode == ColorMode::COLOR_MODE_UNDEFINED ? currentMode : themeMode);
    auto findIter = themeWrappers.find(type);
    if (findIter != themeWrappers.end()) {
        auto wrapper = findIter->second;
        wrapper->ApplyTokenTheme(*tokenTheme);
        return AceType::DynamicCast<Theme>(wrapper);
    }

    auto builderIter = TOKEN_THEME_WRAPPER_BUILDERS_KIT.find(type);
    if (builderIter == TOKEN_THEME_WRAPPER_BUILDERS_KIT.end()) {
        return nullptr;
    }

    bool needRestore = false;
    if (themeMode != ColorMode::COLOR_MODE_UNDEFINED && themeMode != currentMode) {
        // Local color mode of the current theme does not match actual color scheme.
        // Current color mode is system. Need to switch to local color mode temporarily.
        ResourceManager::GetInstance().UpdateColorMode(themeMode);
        pipelineContext->SetLocalColorMode(themeMode);
        needRestore = true;
    }
    auto wrapper = builderIter->second();
    if (needRestore) {
        // Switching resource manager back into system color mode
        pipelineContext->SetLocalColorMode(ColorMode::COLOR_MODE_UNDEFINED);
        ResourceManager::GetInstance().UpdateColorMode(currentMode);
    }
    wrapper->ApplyTokenTheme(*tokenTheme);
    themeWrappers.emplace(type, wrapper);
    return AceType::DynamicCast<Theme>(wrapper);
}

Color ThemeManagerImpl::GetBackgroundColor() const
{
    auto findIter = themes_.find(AppTheme::TypeId());
    if (findIter != themes_.end()) {
        auto appTheme = AceType::DynamicCast<AppTheme>(findIter->second);
        if (appTheme) {
            return appTheme->GetBackgroundColor();
        }
    }
    // Parse attr from system theme style.
    auto themeStyle = themeConstants_->GetThemeStyle();
    auto prebuildColor = themeConstants_->GetColor(THEME_APP_BACKGROUND);
    if (!themeStyle) {
        return prebuildColor;
    }
    if (themeStyle->HasAttr(THEME_ATTR_BG_COLOR) && !themeConstants_->HasCustomStyle(THEME_APP_BACKGROUND)) {
        // Get from resource.
        return themeStyle->GetAttr<Color>(THEME_ATTR_BG_COLOR, Color::BLACK);
    } else {
        // Get from prebuild or custom color.
        return prebuildColor;
    }
}

void ThemeManagerImpl::LoadResourceThemes()
{
    themes_.clear();
    themeWrappersLight_.clear();
    themeWrappersDark_.clear();
    themeConstants_->LoadTheme(currentThemeId_);
}

ThemeManagerImpl::ThemeWrappers& ThemeManagerImpl::GetThemeWrappers(ColorMode mode)
{
    return mode == ColorMode::DARK ? themeWrappersDark_ : themeWrappersLight_;
}

ColorMode ThemeManagerImpl::GetCurrentColorMode() const
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    ColorMode systemMode = Container::CurrentColorMode();
    CHECK_NULL_RETURN(pipelineContext, systemMode);
    ColorMode localMode = pipelineContext->GetLocalColorMode();
    return localMode == ColorMode::COLOR_MODE_UNDEFINED ? systemMode : localMode;
}
} // namespace OHOS::Ace
