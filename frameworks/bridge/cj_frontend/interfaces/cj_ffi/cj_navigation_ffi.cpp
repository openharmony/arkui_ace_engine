/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navigation_ffi.h"

#include "cj_lambda.h"
#include "pixel_map_impl.h"

#include "base/system_bar/system_bar_style.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navigation_stack_ffi.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/navigation/navigation_model.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
constexpr Dimension DEFAULT_MIN_CONTENT_WIDTH = 360.0_vp;
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
void ParseToolbarItems(const std::vector<NavigationItem>& items, std::vector<NG::BarItem>& barItems)
{
    for (size_t i = 0; i < items.size(); i++) {
        NG::BarItem toolBarItem;
        toolBarItem.text = items[i].value;
        if (!items[i].icon.empty()) {
            toolBarItem.icon = items[i].icon;
        }
        auto actionFunc = items[i].action;
        auto onItemClick = [func = std::move(actionFunc)]() { func(); };
        LOGD("ParseToolbarItems text: %{public}s, icon: %{public}s", toolBarItem.text->c_str(),
            toolBarItem.icon->c_str());
        toolBarItem.action = onItemClick;
        toolBarItem.status = static_cast<NG::NavToolbarItemStatus>(items[i].status);
        if (!items[i].activeIcon.empty()) {
            toolBarItem.activeIcon = items[i].activeIcon;
        }
        barItems.push_back(toolBarItem);
    }
}

void ParseMenuItem(const std::vector<NavigationItem>& items, std::vector<NG::BarItem>& barItems)
{
    for (size_t i = 0; i < items.size(); i++) {
        NG::BarItem toolBarItem;
        toolBarItem.text = items[i].value;
        if (!items[i].icon.empty()) {
            toolBarItem.icon = items[i].icon;
        }
        toolBarItem.isEnabled = items[i].isEnable;
        auto actionFunc = items[i].action;
        auto onItemClick = [func = std::move(actionFunc)]() { func(); };
        LOGD("ParseMenuItem text: %{public}s, icon: %{public}s", toolBarItem.text->c_str(), toolBarItem.icon->c_str());
        toolBarItem.action = onItemClick;
        barItems.push_back(toolBarItem);
    }
}

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

void ParseTitlebarOptions(const CJNavigationTitleOptions& info, NG::NavigationTitlebarOptions& options)
{
    options.bgOptions.color.reset();
    options.bgOptions.blurStyle.reset();
    options.brOptions.barStyle.reset();
    options.brOptions.paddingStart.reset();
    options.brOptions.paddingEnd.reset();
    options.textOptions.Reset();

    if (info.isBackgroundColorValid) {
        options.bgOptions.color = Color(ColorAlphaAdapt(info.backgroundColor));
    }
    if (info.isBackgroundBlurStyleValid) {
        if (info.backgroundBlurStyle >= static_cast<int32_t>(BlurStyle::NO_MATERIAL) &&
            info.backgroundBlurStyle <= static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            options.bgOptions.blurStyle = static_cast<BlurStyle>(info.backgroundBlurStyle);
        }
    }
    if (info.isBarStyleValid) {
        if (info.barStyle >= static_cast<int32_t>(NG::BarStyle::STANDARD) &&
            info.barStyle <= static_cast<int32_t>(NG::BarStyle::SAFE_AREA_PADDING)) {
            options.brOptions.barStyle = static_cast<NG::BarStyle>(info.barStyle);
        } else {
            options.brOptions.barStyle = NG::BarStyle::STANDARD;
        }
    }
    if (info.isPaddingStartValid) {
        options.brOptions.paddingStart = CalcDimension(info.paddingStart, DimensionUnit(info.paddingStartUnit));
    }
    if (info.isPaddingEndValid) {
        options.brOptions.paddingEnd = CalcDimension(info.paddingEnd, DimensionUnit(info.paddingEndUnit));
    }
}

void ParseToolbarOptions(const CJNavigationToolbarOptions& info, NG::NavigationToolbarOptions& options)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<NavigationBarTheme>();
        CHECK_NULL_VOID(theme);
        auto blurStyle = static_cast<BlurStyle>(theme->GetToolbarBackgroundBlurStyle());
        if (blurStyle != BlurStyle::NO_MATERIAL) {
            options.bgOptions.blurStyle = blurStyle;
            options.bgOptions.color = Color::TRANSPARENT;
        }
    }
    options.bgOptions.color.reset();
    options.bgOptions.blurStyle.reset();
    options.brOptions.barStyle.reset();

    if (info.isBackgroundColorValid) {
        options.bgOptions.color = Color(info.backgroundColor);
    }
    if (info.isBackgroundBlurStyleValid) {
        if (info.backgroundBlurStyle >= static_cast<int32_t>(BlurStyle::NO_MATERIAL) &&
            info.backgroundBlurStyle <= static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            options.bgOptions.blurStyle = static_cast<BlurStyle>(info.backgroundBlurStyle);
        }
    }
    if (info.isBarStyleValid) {
        if (info.barStyle >= static_cast<int32_t>(NG::BarStyle::STANDARD) &&
            info.barStyle <= static_cast<int32_t>(NG::BarStyle::SAFE_AREA_PADDING)) {
            options.brOptions.barStyle = static_cast<NG::BarStyle>(info.barStyle);
        } else {
            options.brOptions.barStyle = NG::BarStyle::STANDARD;
        }
    }
}

} // namespace OHOS::Ace
extern "C" {
void FfiOHOSAceFrameworkNavigationCreate()
{
    NavigationModel::GetInstance()->Create();
}

void FfiOHOSAceFrameworkNavigationCreateWithPathInfos(int64_t pathInfos)
{
    NavigationModel::GetInstance()->Create();
    auto stackCreator = []() -> RefPtr<CJNavigationStack> { return AceType::MakeRefPtr<CJNavigationStack>(); };
    auto stackUpdater = [pathInfos](RefPtr<NG::NavigationStack> stack) {
        NavigationModel::GetInstance()->SetNavigationStackProvided(true);
        auto cjStack = AceType::DynamicCast<CJNavigationStack>(stack);
        CHECK_NULL_VOID(cjStack);
        cjStack->SetDataSourceObj(pathInfos);
    };
    NavigationModel::GetInstance()->SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    NavigationModel::GetInstance()->SetNavigationPathInfo("", "");
}

void FfiOHOSAceFrameworkNavigationSetNavDestination(void (*builder)(const char*))
{
    auto navDestination = CJLambda::Create(builder);
    auto navDestinationFunc = [func = std::move(navDestination)](
                                  std::string name, std::string param) { func(name.c_str()); };

    auto navigationStack = NavigationModel::GetInstance()->GetNavigationStack();
    auto cjNavigationStack = AceType::DynamicCast<CJNavigationStack>(navigationStack);
    if (cjNavigationStack) {
        cjNavigationStack->SetNavDestBuilderFunc(navDestinationFunc);
    }
}

void FfiOHOSAceFrameworkNavigationSetTitle(const char *title)
{
    NavigationModel::GetInstance()->SetTitle(title);
}

void FfiOHOSAceFrameworkNavigationSetTitleWithBuilder(void (*builder)())
{
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        builderFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    NavigationModel::GetInstance()->SetCustomTitle(customNode);
}

void FfiOHOSAceFrameworkNavigationSetSubTitle(const char *subTitle)
{
    NavigationModel::GetInstance()->SetSubtitle(subTitle);
}

void FfiOHOSAceFrameworkNavigationSetTitleWithOptions(
    const char* title, bool withOptions, CJNavigationTitleOptions options)
{
    NavigationModel::GetInstance()->ParseCommonTitle(false, true, "", title);
    if (withOptions) {
        NG::NavigationTitlebarOptions optionsNG;
        ParseTitlebarOptions(options, optionsNG);
        NavigationModel::GetInstance()->SetTitlebarOptions(std::move(optionsNG));
    }
}

void FfiOHOSAceFrameworkNavigationSetTitleWithBuilderWithOptions(
    void (*builder)(), bool withOptions, CJNavigationTitleOptions options)
{
    CalcDimension titleHeight;
    NavigationModel::GetInstance()->SetTitleHeight(titleHeight, false);
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        builderFunc();
        customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
    }
    NavigationModel::GetInstance()->SetCustomTitle(customNode);
    if (withOptions) {
        NG::NavigationTitlebarOptions optionsNG;
        ParseTitlebarOptions(options, optionsNG);
        NavigationModel::GetInstance()->SetTitlebarOptions(std::move(optionsNG));
    }
}

void FfiOHOSAceFrameworkNavigationSetTitleWithCommon(
    const char* mainTitle, const char* subTitle, bool withOptions, CJNavigationTitleOptions options)
{
    NavigationModel::GetInstance()->ParseCommonTitle(true, true, subTitle, mainTitle);
    if (withOptions) {
        NG::NavigationTitlebarOptions optionsNG;
        ParseTitlebarOptions(options, optionsNG);
        NavigationModel::GetInstance()->SetTitlebarOptions(std::move(optionsNG));
    }
}

void FfiOHOSAceFrameworkNavigationSetTitleWithCustom(
    void (*builder)(), double height, int32_t heightUnit, bool withOptions, CJNavigationTitleOptions options)
{
    NavigationModel::GetInstance()->SetTitleHeight(CalcDimension(height, DimensionUnit(heightUnit)));
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        builderFunc();
        customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
    }
    NavigationModel::GetInstance()->SetCustomTitle(customNode);
    if (withOptions) {
        NG::NavigationTitlebarOptions optionsNG;
        ParseTitlebarOptions(options, optionsNG);
        NavigationModel::GetInstance()->SetTitlebarOptions(std::move(optionsNG));
    }
}

void FfiOHOSAceFrameworkNavigationSetMenus(VectorNavigationItemHandle menus)
{
    const auto& menuVector = *reinterpret_cast<std::vector<NavigationItem>*>(menus);
    std::vector<NG::BarItem> menuItems;
    ParseMenuItem(menuVector, menuItems);
    NavigationModel::GetInstance()->SetMenuItems(std::move(menuItems));
}

void FfiOHOSAceFrameworkNavigationSetMenusWithBuilder(void (*builder)())
{
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        builderFunc();
        customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
    }
    NavigationModel::GetInstance()->SetCustomMenu(customNode);
}

void FfiOHOSAceFrameworkNavigationSetTitleMode(int32_t titleMode)
{
    NavigationModel::GetInstance()->SetTitleMode(static_cast<NG::NavigationTitleMode>(titleMode));
}

void FfiOHOSAceFrameworkNavigationSetToolBar(VectorNavigationItemHandle toolBars)
{
    const auto &toolBarVector = *reinterpret_cast<std::vector<NavigationItem> *>(toolBars);
    std::vector<NG::BarItem> toolBarItems;
    ParseToolbarItems(toolBarVector, toolBarItems);
    NavigationModel::GetInstance()->SetToolBarItems(std::move(toolBarItems));
}

void FfiOHOSAceFrameworkNavigationSetToolBarWithBuilder(void (*builder)())
{
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        builderFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    NavigationModel::GetInstance()->SetCustomToolBar(customNode);
}

void FfiOHOSAceFrameworkNavigationSetToolBarWithOptions(
    VectorNavigationItemHandle toolBars, bool withOptions, CJNavigationToolbarOptions options)
{
    const auto& toolBarVector = *reinterpret_cast<std::vector<NavigationItem>*>(toolBars);
    std::vector<NG::BarItem> toolBarItems;
    ParseToolbarItems(toolBarVector, toolBarItems);
    NavigationModel::GetInstance()->SetToolbarConfiguration(std::move(toolBarItems));
    if (withOptions) {
        NG::NavigationToolbarOptions optionsNG;
        ParseToolbarOptions(options, optionsNG);
        NavigationModel::GetInstance()->SetToolbarOptions(std::move(optionsNG));
    }
}

void FfiOHOSAceFrameworkNavigationSetToolBarWithBuilderWithOptions(
    void (*builder)(), bool withOptions, CJNavigationToolbarOptions options)
{
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        builderFunc();
        customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
    }
    NavigationModel::GetInstance()->SetCustomToolBar(customNode);
    if (withOptions) {
        NG::NavigationToolbarOptions optionsNG;
        ParseToolbarOptions(options, optionsNG);
        NavigationModel::GetInstance()->SetToolbarOptions(std::move(optionsNG));
    }
}

void FfiOHOSAceFrameworkNavigationSetHideToolBar(bool isHide)
{
    NavigationModel::GetInstance()->SetHideToolBar(isHide);
}

void FfiOHOSAceFrameworkNavigationSetHideTitleBar(bool isHide)
{
    NavigationModel::GetInstance()->SetHideTitleBar(isHide);
}

void FfiOHOSAceFrameworkNavigationSetHideBackButton(bool isHide)
{
    NavigationModel::GetInstance()->SetHideBackButton(isHide);
}

void FfiOHOSAceFrameworkNavigationSetNavBarWidth(double width, int32_t widthUnit)
{
    NavigationModel::GetInstance()->SetNavBarWidth(CalcDimension(width, DimensionUnit(widthUnit)));
}

void FfiOHOSAceFrameworkNavigationSetNavBarPosition(int32_t position)
{
    NavigationModel::GetInstance()->SetNavBarPosition(static_cast<NG::NavBarPosition>(position));
}

void FfiOHOSAceFrameworkNavigationSetMode(int32_t value)
{
    NavigationModel::GetInstance()->SetUsrNavigationMode(static_cast<NG::NavigationMode>(value));
}

void FfiOHOSAceFrameworkNavigationSetBackButtonIcon(const char* icon)
{
    std::string src = icon;
    std::vector<std::string> nameList;
    NG::ImageOption imageOption;
    RefPtr<PixelMap> pixelMap = nullptr;

    nameList.emplace_back(std::string());
    nameList.emplace_back(std::string());
    imageOption.noPixMap = true;
    imageOption.isValidImage = true;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    NavigationModel::GetInstance()->SetBackButtonIcon(iconSymbol, src, imageOption, pixelMap, nameList);
}

void FfiOHOSAceFrameworkNavigationSetBackButtonIconWithPixelMap(int64_t id)
{
    std::string src;
    std::vector<std::string> nameList;
    NG::ImageOption imageOption;
    auto instance = OHOS::FFI::FFIData::GetData<OHOS::Media::PixelMapImpl>(id);
    if (!instance) {
        LOGE("[PixelMap] instance not exist %{public}" PRId64, id);
        return;
    }
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapPtr = instance->GetRealPixelMap();
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(&pixelMapPtr);

    nameList.emplace_back(std::string());
    nameList.emplace_back(std::string());
    imageOption.noPixMap = false;
    imageOption.isValidImage = true;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    NavigationModel::GetInstance()->SetBackButtonIcon(iconSymbol, src, imageOption, pixelMap, nameList);
}

void FfiOHOSAceFrameworkNavigationSetHideNavBar(bool isHide)
{
    NavigationModel::GetInstance()->SetHideNavBar(isHide);
}

void FfiOHOSAceFrameworkNavigationSetNavBarWidthRange(double min, int32_t minUnit, double max, int32_t maxUnit)
{
    CalcDimension minNavBarWidth;
    CalcDimension maxNavBarWidth;
    if (min < 0.0) {
        minNavBarWidth = CalcDimension(0.0, DimensionUnit::VP);
    } else {
        minNavBarWidth = CalcDimension(min, DimensionUnit(minUnit));
    }
    NavigationModel::GetInstance()->SetMinNavBarWidth(minNavBarWidth);

    if (max < 0.0) {
        maxNavBarWidth = CalcDimension(0.0, DimensionUnit::VP);
    } else {
        maxNavBarWidth = CalcDimension(max, DimensionUnit(minUnit));
    }
    NavigationModel::GetInstance()->SetMaxNavBarWidth(maxNavBarWidth);
}

void FfiOHOSAceFrameworkNavigationSetMinContentWidth(double min, int32_t minUnit)
{
    CalcDimension minContentWidth;
    if (min < 0.0) {
        minContentWidth = DEFAULT_MIN_CONTENT_WIDTH;
    } else {
        minContentWidth = CalcDimension(min, DimensionUnit(minUnit));
    }
    NavigationModel::GetInstance()->SetMinContentWidth(minContentWidth);
}

void FfiOHOSAceFrameworkNavigationSetSystemBarStyle(uint32_t color)
{
    RefPtr<SystemBarStyle> style = SystemBarStyle::CreateStyleFromColor(color);
    NavigationModel::GetInstance()->SetSystemBarStyle(style);
}

void FfiOHOSAceFrameworkNavigationSetOnNavBarStateChange(void (*callback)(bool))
{
    auto onChange = CJLambda::Create(callback);
    auto onNavBarStateChange = [func = std::move(onChange)](bool isVisible) { func(isVisible); };
    NavigationModel::GetInstance()->SetOnNavBarStateChange(std::move(onNavBarStateChange));
}

void FfiOHOSAceFrameworkNavigationSetOnNavigationModeChange(void (*callback)(int32_t))
{
    auto onChange = CJLambda::Create(callback);
    auto onNavigationModeChange = [func = std::move(onChange)](
                                      NG::NavigationMode mode) { func(static_cast<int32_t>(mode)); };
    NavigationModel::GetInstance()->SetOnNavigationModeChange(std::move(onNavigationModeChange));
}

void FfiOHOSAceFrameworkNavigationSetOnTitleModeChanged(void (*callback)(int32_t))
{
    auto onChange = CJLambda::Create(callback);
    auto func = std::move(onChange);
    auto onTitleModeChange = [func](NG::NavigationTitleMode mode) { func(static_cast<int32_t>(mode)); };

    auto eventInfoFunc = [func](const BaseEventInfo* baseInfo) {
        auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(baseInfo);
        if (!eventInfo) {
            return;
        }
        auto mode = eventInfo->IsMiniBar() ? NG::NavigationTitleMode::MINI : NG::NavigationTitleMode::FULL;
        func(static_cast<int32_t>(mode));
    };
    NavigationModel::GetInstance()->SetOnTitleModeChange(std::move(onTitleModeChange), std::move(eventInfoFunc));
}
}
