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
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include <string>

#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
namespace OHOS::Ace::NG {
constexpr int32_t ATOMIC_SERVICE_MIN_SIZE = 2;
constexpr int32_t FIRST_OVERLAY_INDEX = 1;

std::atomic<int32_t> g_nextListenerId = 1;

std::function<void(RefPtr<FrameNode> host, std::optional<bool> settedColorMode)>
    AtomicServicePattern::beforeCreateLayoutBuilder_ = nullptr;

void AtomicServicePattern::RegisterBeforeCreateLayoutBuilder(
    std::function<void(RefPtr<FrameNode> host, std::optional<bool> settedColorMode)> beforeCreateLayoutBuilder)
{
    beforeCreateLayoutBuilder_ = beforeCreateLayoutBuilder;
}

void AtomicServicePattern::BeforeCreateLayoutWrapper()
{
    // before create layout builder for cj frontend
    if (beforeCreateLayoutBuilder_) {
        beforeCreateLayoutBuilder_(GetHost(), settedColorMode);
        return;
    }
    MenuBarSafeAreaCallBack();
    ContentSafeAreaCallBack();
    ColorConfigurationCallBack();
}

void AtomicServicePattern::MenuBarSafeAreaCallBack()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    manager->SetIsAtomicService(true);
    manager->AddGeoRestoreNode(host);
    auto systemSafeArea = manager->GetSystemSafeArea();
    auto menuSafeTopValue = systemSafeArea.top_.Length();
    auto menuSafeTopVp = Dimension(menuSafeTopValue, DimensionUnit::PX).ConvertToVp();
    auto customAppBar = GetJSAppBarContainer();
    CHECK_NULL_VOID(customAppBar);
    customAppBar->FireCustomCallback(ARKUI_APP_BAR_MENU_SAFE_AREA, std::to_string(menuSafeTopVp));
}

void AtomicServicePattern::ContentSafeAreaCallBack()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    if (manager->KeyboardSafeAreaEnabled()) {
        safeArea.bottom_ = safeArea.bottom_.Combine(manager->GetKeyboardInset());
    }
    auto left = Dimension(safeArea.left_.Length(), DimensionUnit::PX).ConvertToVp();
    auto right = Dimension(safeArea.right_.Length(), DimensionUnit::PX).ConvertToVp();
    auto top = Dimension(safeArea.top_.Length(), DimensionUnit::PX).ConvertToVp();
    auto bottom = Dimension(safeArea.bottom_.Length(), DimensionUnit::PX).ConvertToVp();
    auto customAppBar = GetJSAppBarContainer();
    CHECK_NULL_VOID(customAppBar);
    std::vector<float> values = { top, left, right, bottom };
    std::string result;
    for (size_t i = 0; i < values.size(); ++i) {
        result += std::to_string(values[i]);
        if (i < values.size() - 1) {
            result += "|";
        }
    }
    customAppBar->FireCustomCallback(ARKUI_APP_BAR_CONTENT_SAFE_AREA, result);
}

void AtomicServicePattern::ColorConfigurationCallBack()
{
    auto customAppBar = GetJSAppBarContainer();
    CHECK_NULL_VOID(customAppBar);
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    customAppBar->FireCustomCallback(ARKUI_APP_BAR_COLOR_CONFIGURATION,
        settedColorMode.has_value() ? !settedColorMode.value() : context->GetColorMode() == ColorMode::DARK);
}

void AtomicServicePattern::AppInfoCallBack()
{
    auto atom = GetHost();
    CHECK_NULL_VOID(atom);
    auto pipeline = atom->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_VOID(themeConstants);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    auto customAppBar = GetJSAppBarContainer();
    CHECK_NULL_VOID(customAppBar);
    auto id = windowManager->GetAppIconId();
    auto pixelMap = themeConstants->GetPixelMap(id);
    if (pixelMap) {
        const RefPtr<PixelMap> icon = PixelMap::CreatePixelMap(&pixelMap);
        customAppBar->FireAppIconCallback(icon);
    } else {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "App bar Cannot get pixelmap, try media path.");
    }
    auto result = AceApplicationInfo::GetInstance().GetProcessName() + "|" +
                  themeConstants->GetString(windowManager->GetAppLabelId());
    customAppBar->FireCustomCallback(ARKUI_APP_BAR_BAR_INFO, result);
}

void AtomicServicePattern::AppScreenCallBack()
{
    auto customAppBar = GetJSAppBarContainer();
    CHECK_NULL_VOID(customAppBar);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    customAppBar->FireCustomCallback(ARKUI_APP_BAR_SCREEN, container->UIExtensionIsHalfScreen());
}

void AtomicServicePattern::SetOnBackPressedConsumed()
{
    if (onBackPressedConsumed_.has_value()) {
        onBackPressedConsumed_ = true;
    }
}

bool AtomicServicePattern::OnBackPressedCallback()
{
    auto customAppBar = GetJSAppBarContainer();
    CHECK_NULL_RETURN(customAppBar, false);
    onBackPressedConsumed_ = false;
    customAppBar->FireCustomCallback(ARKUI_APP_BAR_ON_BACK_PRESSED, true);
    bool consumed = onBackPressedConsumed_.value();
    onBackPressedConsumed_.reset();
    return consumed;
}

void AtomicServicePattern::AppBgColorCallBack()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto customAppBar = GetJSAppBarContainer();
    CHECK_NULL_VOID(customAppBar);
    customAppBar->FireCustomCallback(ARKUI_APP_BG_COLOR, pipeline->GetAppBgColor().ColorToString());
}

void AtomicServicePattern::UpdateLayoutMargin()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();
    auto atom = GetHost();
    CHECK_NULL_VOID(atom);
    MarginProperty margin;
    margin.left = CalcLength(safeArea.left_.Length());
    margin.right = CalcLength(safeArea.right_.Length());
    margin.top = CalcLength(safeArea.top_.Length());
    margin.bottom = CalcLength(safeArea.bottom_.Length());
    // update stage margin
    auto stage = GetContent();
    CHECK_NULL_VOID(stage);
    auto layoutProperty = stage->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMargin(margin);
    stage->MarkModifyDone();
    stage->MarkDirtyNode();
}

void AtomicServicePattern::UpdateOverlayLayout()
{
    auto atom = GetHost();
    CHECK_NULL_VOID(atom);
    if (atom->GetChildren().size() <= ATOMIC_SERVICE_MIN_SIZE) {
        return;
    }
    for (int index = FIRST_OVERLAY_INDEX;
        index <= static_cast<int32_t>(atom->GetChildren().size()) - ATOMIC_SERVICE_MIN_SIZE; index++) {
        auto overlay = AceType::DynamicCast<FrameNode>(atom->GetChildAtIndex(index));
        CHECK_NULL_VOID(overlay);
        auto overlayRender = overlay->GetRenderContext();
        overlayRender->UpdatePosition(OffsetT<Dimension>());
        overlay->MarkModifyDone();
        overlay->MarkDirtyNode();
    }
}

void AtomicServicePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    AppBgColorCallBack();
}

void AtomicServicePattern::OnColorConfigurationUpdate()
{
    AppBgColorCallBack();
    ColorConfigurationCallBack();
}

void AtomicServicePattern::OnLanguageConfigurationUpdate()
{
    AppInfoCallBack();
}

RefPtr<CustomAppBarNode> AtomicServicePattern::GetJSAppBarContainer()
{
    return customAppBarNodeNode_;
}

RefPtr<FrameNode> AtomicServicePattern::GetStageNodeWrapper()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceStageId");
}

RefPtr<FrameNode> AtomicServicePattern::GetContent()
{
    auto stageNodeWrapper = GetStageNodeWrapper();
    CHECK_NULL_RETURN(stageNodeWrapper, nullptr);
    return AceType::DynamicCast<FrameNode>(stageNodeWrapper->GetChildAtIndex(0));
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuBarRow()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceMenubarRowId");
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuBar()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceMenubarId");
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuButton()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceMenuId");
}

RefPtr<FrameNode> AtomicServicePattern::GetDivider()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceDividerId");
}

RefPtr<FrameNode> AtomicServicePattern::GetCloseButton()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceCloseId");
}

RefPtr<FrameNode> AtomicServicePattern::GetMenuIcon()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceMenuIconId");
}

RefPtr<FrameNode> AtomicServicePattern::GetCloseIcon()
{
    return NG::Inspector::GetFrameNodeByKey("AtomicServiceCloseIconId");
}

void AtomicServicePattern::UpdateColor(std::optional<bool> isLight)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    if (!(isLight.has_value())) {
        isLight = pipeline->GetColorMode() != ColorMode::DARK;
    }
    auto menuButton = GetMenuButton();
    UpdateButtonColor(theme, menuButton, isLight.value());
    auto divider = GetDivider();
    UpdateDividerColor(theme, divider, isLight.value());
    auto closeButton = GetCloseButton();
    UpdateButtonColor(theme, closeButton, isLight.value());

    auto menuIcon = GetMenuIcon();
    UpdateIconColor(theme, menuIcon, isLight.value());
    auto closeIcon = GetCloseIcon();
    UpdateIconColor(theme, closeIcon, isLight.value());
}

void AtomicServicePattern::UpdateMenuBarColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(menuBar);
    auto renderContext = menuBar->GetRenderContext();
    // background effect、border color
    EffectOption option;
    BorderColorProperty borderColor;
    option.radius = theme->GetBlurRadius();
    if (isLight) {
        option.color = theme->GetBlurColorLight();
        borderColor.SetColor(theme->GetBorderColorLight());
    } else {
        option.color = theme->GetBlurColorDark();
        borderColor.SetColor(theme->GetBorderColorDark());
    }
    renderContext->UpdateBackgroundEffect(option);
    renderContext->UpdateBorderColor(borderColor);

    menuBar->MarkModifyDone();
    menuBar->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void AtomicServicePattern::UpdateButtonColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& button, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(button);
    // pressed color
    auto buttonPattern = button->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    if (isLight) {
        buttonPattern->SetClickedColor(theme->GetClickEffectColorLight());
    } else {
        buttonPattern->SetClickedColor(theme->GetClickEffectColorDark());
    }
    // focus border color
    if (isLight) {
        buttonPattern->SetFocusBorderColor(theme->GetFocusedOutlineColorLight());
    } else {
        buttonPattern->SetFocusBorderColor(theme->GetFocusedOutlineColorDark());
    }

    button->MarkModifyDone();
    button->MarkDirtyNode();
}

void AtomicServicePattern::UpdateDividerColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& divider, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(divider);

    auto renderProperty = divider->GetPaintProperty<DividerRenderProperty>();
    if (isLight) {
        renderProperty->UpdateDividerColor(theme->GetDividerColorLight());
    } else {
        renderProperty->UpdateDividerColor(theme->GetDividerColorDark());
    }

    divider->MarkModifyDone();
    divider->MarkDirtyNode();
}

void AtomicServicePattern::UpdateIconColor(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& icon, bool isLight)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(icon);
    // fill color
    auto color = isLight ? theme->GetIconColorLight() : theme->GetIconColorDark();
    ACE_UPDATE_NODE_PAINT_PROPERTY(ImageRenderProperty, SvgFillColor, color, icon);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, color, icon);
    icon->MarkModifyDone();
    icon->MarkDirtyNode();
}

void AtomicServicePattern::UpdateLayout()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<AppBarTheme>();
    CHECK_NULL_VOID(theme);
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();

    auto menuBar = GetMenuBar();
    UpdateMenuBarLayout(theme, menuBar, isRtl);

    auto menuButton = GetMenuButton();
    UpdateButtonLayout(theme, menuButton, !isRtl);
    auto closeButton = GetCloseButton();
    UpdateButtonLayout(theme, closeButton, isRtl);

    auto menuIcon = GetMenuIcon();
    UpdateIconLayout(theme, menuIcon, !isRtl);
    auto closeIcon = GetCloseIcon();
    UpdateIconLayout(theme, closeIcon, isRtl);
}

void AtomicServicePattern::UpdateMenuBarLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& menuBar, bool isRtl)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(menuBar);

    MarginProperty margin;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();

    Dimension safeAreaLeft(pipeline->Px2VpWithCurrentDensity(safeArea.left_.Length()), DimensionUnit::VP);
    Dimension safeAreaRight(pipeline->Px2VpWithCurrentDensity(safeArea.right_.Length()), DimensionUnit::VP);

    if (isRtl) {
        margin.left = CalcLength(theme->GetMenuBarRightMargin() + safeAreaLeft);
        margin.right = CalcLength(theme->GetMenuBarLeftMargin() + safeAreaRight);
    } else {
        margin.left = CalcLength(theme->GetMenuBarLeftMargin() + safeAreaLeft);
        margin.right = CalcLength(theme->GetMenuBarRightMargin() + safeAreaRight);
    }
    menuBar->GetLayoutProperty<LinearLayoutProperty>()->UpdateMargin(margin);

    menuBar->MarkModifyDone();
    menuBar->MarkDirtyNode();
}

void AtomicServicePattern::UpdateButtonLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& button, bool isLeft)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(button);

    auto bent = theme->GetBentRadius();
    auto rightAngle = theme->GetRightAngle();
    auto leftBorderRadius = BorderRadiusProperty(bent, rightAngle, rightAngle, bent);
    auto rightBorderRadius = BorderRadiusProperty(rightAngle, bent, bent, rightAngle);

    auto layoutProperty = button->GetLayoutProperty<ButtonLayoutProperty>();
    layoutProperty->UpdateBorderRadius(isLeft ? leftBorderRadius : rightBorderRadius);

    button->MarkModifyDone();
    button->MarkDirtyNode();
}

void AtomicServicePattern::UpdateIconLayout(RefPtr<AppBarTheme>& theme, RefPtr<FrameNode>& icon, bool isLeft)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(icon);

    MarginProperty margin;
    margin.top = CalcLength(theme->GetIconVerticalMargin());
    margin.bottom = CalcLength(theme->GetIconVerticalMargin());
    if (isLeft) {
        margin.left = CalcLength(theme->GetIconOutsideMargin());
        margin.right = CalcLength(theme->GetIconInsideMargin());
    } else {
        margin.left = CalcLength(theme->GetIconInsideMargin());
        margin.right = CalcLength(theme->GetIconOutsideMargin());
    }
    auto layoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMargin(margin);

    icon->MarkModifyDone();
    icon->MarkDirtyNode();
}

bool AtomicServicePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto atom = GetHost();
    CHECK_NULL_RETURN(atom, false);
    auto pipeline = atom->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    pipeline->AddAfterLayoutTask([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CallRectChange();
    });
    return false;
}

int32_t AtomicServicePattern::AddRectChangeListener(std::function<void(const RectF& rect)>&& listener)
{
    auto id = g_nextListenerId.fetch_add(1);
    rectChangeListeners_.emplace(id, listener);
    return id;
}

void AtomicServicePattern::RemoveRectChangeListener(int32_t id)
{
    auto it = rectChangeListeners_.find(id);
    if (it != rectChangeListeners_.end()) {
        rectChangeListeners_.erase(it);
    }
}

void AtomicServicePattern::NotifyRectChange(const RectF& rect)
{
    for (auto& pair : rectChangeListeners_) {
        if (pair.second) {
            pair.second(rect);
        }
    }
}

void AtomicServicePattern::CallRectChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto container = Container::GetContainer(pipeline->GetInstanceId());
    CHECK_NULL_VOID(container);
    auto appbar = container->GetAppBar();
    CHECK_NULL_VOID(appbar);
    auto rect = appbar->GetAppBarRect();
    if (!rect.has_value()) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "Get rect of app bar failed, app bar is hidden");
        return;
    }
    if (appBarRect_.has_value() && appBarRect_.value() == rect.value()) {
        TAG_LOGD(AceLogTag::ACE_APPBAR, "App bar rect is not changed, no need to notify");
        return;
    }
    NotifyRectChange(rect.value());
    appBarRect_ = rect;
}
} // namespace OHOS::Ace::NG
