/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navdestination_ffi.h"

#include "cj_lambda.h"
#include "pixel_map_impl.h"

#include "base/system_bar/system_bar_style.h"
#include "base/utils/utils.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_navigation_stack_ffi.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/property/safe_area_insets.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<Dimension> TITLE_HEIGHT = { NG::SINGLE_LINE_TITLEBAR_HEIGHT, NG::DOUBLE_LINE_TITLEBAR_HEIGHT };

constexpr uint32_t SAFE_AREA_TYPE_LIMIT = 3;
constexpr uint32_t SAFE_AREA_EDGE_LIMIT = 4;
constexpr uint32_t SAFE_AREA_EDGE_SYSTEM = 0;
constexpr uint32_t SAFE_AREA_EDGE_TOP = 0;
constexpr uint32_t SAFE_AREA_EDGE_BOTTOM = 1;
} // namespace

namespace OHOS::Ace {
std::unique_ptr<NavDestinationModel> NavDestinationModel::instance_ = nullptr;
std::mutex NavDestinationModel::mutex_;

NavDestinationModel* NavDestinationModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        instance_.reset(new NG::NavDestinationModelNG());
    }
    return instance_.get();
}
} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkNavdestinationCreate()
{
    auto builderFunc = []() {};
    auto ctx = AceType::MakeRefPtr<NG::NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<CJNavPathInfoNG>();
    ctx->SetNavPathInfo(navPathInfo);
    NavDestinationModel::GetInstance()->Create(std::move(builderFunc), std::move(ctx));
}

void FfiOHOSAceFrameworkNavdestinationSetOnBackPressed(bool (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnBackPressed(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkNavdestinationSetOnReady(void (*callback)(CJNavDestinationContext context))
{
    auto onReadyCallback = [ffiCallback = CJLambda::Create(callback)](RefPtr<NG::NavDestinationContext> context) {
        auto pathInfo = context->GetNavPathInfo();
        CJNavPathInfoFFi info = CJNavPathInfoFFi();
        char* temp = strdup(pathInfo->GetName().c_str());
        info.name = temp;
        int64_t pathStackId = 0;
        auto stack = context->GetNavigationStack().Upgrade();
        if (stack) {
            auto cjStack = AceType::DynamicCast<CJNavigationStack>(stack);
            if (cjStack) {
                pathStackId = cjStack->GetDataSourceObjId();
            }
        }
        CJNavDestinationContext cjContext = CJNavDestinationContext();
        cjContext.navDestinationId = context->GetNavDestinationId();
        cjContext.pathStack = pathStackId;
        cjContext.pathInfo = info;
        ffiCallback(cjContext);
        if (temp != nullptr) {
            free(temp);
        }
    };
    NavDestinationModel::GetInstance()->SetOnReady(std::move(onReadyCallback));
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithString(const char* value)
{
    NavDestinationModel::GetInstance()->ParseCommonTitle(false, true, "", std::string(value));
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithBuilder(void (*builder)())
{
    auto buildFunc = CJLambda::Create(builder);
    RefPtr<AceType> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        buildFunc();
        customNode = ViewStackModel::GetInstance()->Finish();
    }
    NavDestinationModel::GetInstance()->SetCustomTitle(customNode);
    CalcDimension titleHeight;
    NavDestinationModel::GetInstance()->SetTitleHeight(titleHeight, false);
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithCommonTitle(const char* main, const char* sub)
{
    bool hasSub = (sub != nullptr);
    bool hasMain = (main != nullptr);
    NG::NavDestinationModelNG::GetInstance()->ParseCommonTitle(hasSub, hasMain, std::string(sub), std::string(main));
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithTitleHeight(void (*builder)(), int32_t titleHeightMode)
{
    auto buildFunc = CJLambda::Create(builder);
    RefPtr<AceType> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        buildFunc();
        customNode = ViewStackModel::GetInstance()->Finish();
    }
    NavDestinationModel::GetInstance()->SetCustomTitle(customNode);

    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(titleHeightMode, TITLE_HEIGHT.size())) {
        LOGE("invalid value for title height mode");
        return;
    }
    NavDestinationModel::GetInstance()->SetTitleHeight(TITLE_HEIGHT[titleHeightMode]);
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithHeight(void (*builder)(), double height, int32_t heightUnit)
{
    auto buildFunc = CJLambda::Create(builder);
    RefPtr<AceType> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        buildFunc();
        customNode = ViewStackModel::GetInstance()->Finish();
    }
    NavDestinationModel::GetInstance()->SetCustomTitle(customNode);

    if (height < 0) {
        NavDestinationModel::GetInstance()->SetTitleHeight(Dimension(), true);
    } else {
        auto titleHeight = CalcDimension(height, static_cast<DimensionUnit>(heightUnit));
        NavDestinationModel::GetInstance()->SetTitleHeight(titleHeight);
    }
}

void ParseTitlebarOptions(CJNavigationTitleOptions options)
{
    NG::NavigationTitlebarOptions titlebarOptions;
    titlebarOptions.bgOptions.color.reset();
    titlebarOptions.bgOptions.color = Color(options.backgroundColor);
    titlebarOptions.bgOptions.blurStyleOption.reset();
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = static_cast<BlurStyle>(options.backgroundBlurStyle);
    titlebarOptions.bgOptions.blurStyleOption = blurStyleOption;
    titlebarOptions.brOptions.paddingStart.reset();
    titlebarOptions.brOptions.paddingStart =
        CalcDimension(options.paddingStart, static_cast<DimensionUnit>(options.paddingStartUnit));
    titlebarOptions.brOptions.paddingEnd.reset();
    titlebarOptions.brOptions.paddingEnd =
        CalcDimension(options.paddingEnd, static_cast<DimensionUnit>(options.paddingEndUnit));
    titlebarOptions.brOptions.barStyle.reset();
    titlebarOptions.brOptions.barStyle = static_cast<NG::BarStyle>(options.barStyle);
    NavDestinationModel::GetInstance()->SetTitlebarOptions(std::move(titlebarOptions));
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithStringOptions(const char* value, CJNavigationTitleOptions options)
{
    FfiOHOSAceFrameworkNavdestinationSetTitleWithString(value);
    ParseTitlebarOptions(options);
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithBuilderOptions(void (*builder)(), CJNavigationTitleOptions options)
{
    FfiOHOSAceFrameworkNavdestinationSetTitleWithBuilder(builder);
    ParseTitlebarOptions(options);
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithCommonTitleOptions(
    const char* main, const char* sub, CJNavigationTitleOptions options)
{
    FfiOHOSAceFrameworkNavdestinationSetTitleWithCommonTitle(main, sub);
    ParseTitlebarOptions(options);
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithTitleHeightOptions(
    void (*builder)(), int32_t titleHeightMode, CJNavigationTitleOptions options)
{
    FfiOHOSAceFrameworkNavdestinationSetTitleWithTitleHeight(builder, titleHeightMode);
    ParseTitlebarOptions(options);
}

void FfiOHOSAceFrameworkNavdestinationSetTitleWithHeightOptions(
    void (*builder)(), double height, int32_t heightUnit, CJNavigationTitleOptions options)
{
    FfiOHOSAceFrameworkNavdestinationSetTitleWithHeight(builder, height, heightUnit);
    ParseTitlebarOptions(options);
}

void FfiOHOSAceFrameworkNavdestinationSetHideTitleBar(bool value)
{
    NavDestinationModel::GetInstance()->SetHideTitleBar(value, false);
}

void FfiOHOSAceFrameworkNavdestinationSetMode(int32_t mode)
{
    NavDestinationModel::GetInstance()->SetNavDestinationMode(static_cast<NG::NavDestinationMode>(mode));
}

void FfiOHOSAceFrameworkNavdestinationSetBackButtonIconWithUrl(const char* url)
{
    NG::ImageOption imageOption;
    imageOption.noPixMap = true;
    imageOption.isValidImage = (url != nullptr);
    RefPtr<PixelMap> pixelMapRef = nullptr;
    std::vector<std::string> nameList;
    nameList.emplace_back("");
    nameList.emplace_back("");
    NavDestinationModel::GetInstance()->SetBackButtonIcon(
        nullptr, std::string(url), imageOption, pixelMapRef, nameList);
}

void FfiOHOSAceFrameworkNavdestinationSetBackButtonIconWithPixelMap(int64_t pixelMapId)
{
    RefPtr<PixelMap> pixelMapRef = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    auto instance = OHOS::FFI::FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
    if (!instance) {
        LOGE("[PixelMap] instance not exist %{public}" PRId64, pixelMapId);
        return;
    }
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap = instance->GetRealPixelMap();
    pixelMapRef = PixelMap::CreatePixelMap(&pixelMap);
#endif
    NG::ImageOption imageOption;
    imageOption.noPixMap = false;
    imageOption.isValidImage = (pixelMapRef != nullptr);
    std::vector<std::string> nameList;
    nameList.emplace_back("");
    nameList.emplace_back("");
    NavDestinationModel::GetInstance()->SetBackButtonIcon(nullptr, "", imageOption, pixelMapRef, nameList);
}

void FfiOHOSAceFrameworkNavdestinationSetMenus(VectorNavigationItemHandle menuItemHandle)
{
    auto menuItemVec = *reinterpret_cast<std::vector<NavigationItem>*>(menuItemHandle);
    std::vector<NG::BarItem> menuItems;
    for (size_t i = 0; i < menuItemVec.size(); i++) {
        auto menuItem = menuItemVec[i];
        NG::BarItem toolBarItem;
        toolBarItem.text = menuItem.value;
        if (!menuItem.icon.empty()) {
            toolBarItem.icon = menuItem.icon;
        }
        toolBarItem.isEnabled = menuItem.isEnable;
        toolBarItem.action = menuItem.action;
        toolBarItem.status = static_cast<NG::NavToolbarItemStatus>(menuItem.status);
        if (!menuItem.activeIcon.empty()) {
            toolBarItem.activeIcon = menuItem.activeIcon;
        }
        menuItems.push_back(toolBarItem);
    }
    NavDestinationModel::GetInstance()->SetMenuItems(std::move(menuItems));
}

void FfiOHOSAceFrameworkNavdestinationSetMenusWithBuilder(void (*builder)())
{
    auto buildFunc = CJLambda::Create(builder);
    RefPtr<AceType> customNode;
    {
        ViewStackModel::GetInstance()->NewScope();
        buildFunc();
        customNode = ViewStackModel::GetInstance()->Finish();
    }
    NavDestinationModel::GetInstance()->SetCustomMenu(customNode);
}

void FfiOHOSAceFrameworkNavdestinationIgnoreLayoutSafeArea(VectorInt32Ptr types, VectorInt32Ptr edges)
{
    const auto& typesArray = *reinterpret_cast<std::vector<int32_t>*>(types);
    const auto& edgeArray = *reinterpret_cast<std::vector<int32_t>*>(edges);
    NG::SafeAreaExpandOpts opts { .type = NG::SAFE_AREA_TYPE_SYSTEM, .edges = NG::SAFE_AREA_EDGE_ALL };
    if (typesArray.size() > 0) {
        uint32_t safeAreaType = NG::SAFE_AREA_TYPE_NONE;
        for (size_t i = 0; i < typesArray.size(); ++i) {
            auto value = typesArray.at(i);
            if (value >= static_cast<int32_t>(SAFE_AREA_TYPE_LIMIT) ||
                value == static_cast<int32_t>(SAFE_AREA_EDGE_SYSTEM)) {
                safeAreaType = NG::SAFE_AREA_TYPE_SYSTEM;
                break;
            }
        }
        opts.type = safeAreaType;
    }
    if (edgeArray.size() > 0) {
        uint32_t safeAreaEdge = NG::SAFE_AREA_EDGE_NONE;
        for (size_t i = 0; i < edgeArray.size(); ++i) {
            auto value = edgeArray.at(i);
            if (value >= static_cast<int32_t>(SAFE_AREA_EDGE_LIMIT)) {
                safeAreaEdge = NG::SAFE_AREA_EDGE_ALL;
                break;
            }
            if (value == SAFE_AREA_EDGE_TOP || value == SAFE_AREA_EDGE_BOTTOM) {
                safeAreaEdge |= (1 << (uint32_t)value);
            }
        }
        opts.edges = safeAreaEdge;
    }
    NavDestinationModel::GetInstance()->SetIgnoreLayoutSafeArea(opts);
}

void FfiOHOSAceFrameworkNavdestinationSetSystemBarStyle(uint32_t styleColor)
{
    RefPtr<SystemBarStyle> style = SystemBarStyle::CreateStyleFromColor(styleColor);
    NavDestinationModel::GetInstance()->SetSystemBarStyle(style);
}

void FfiOHOSAceFrameworkNavdestinationSetOnShown(void (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnShown(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkNavdestinationSetOnHidden(void (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnHidden(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkNavdestinationSetOnWillAppear(void (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnWillAppear(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkNavdestinationSetOnWillShow(void (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnWillShow(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkNavdestinationSetOnWillHide(void (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnWillHide(CJLambda::Create(callback));
}

void FfiOHOSAceFrameworkNavdestinationSetOnWillDisappear(void (*callback)())
{
    NavDestinationModel::GetInstance()->SetOnWillDisAppear(CJLambda::Create(callback));
}
} // extern "C"
