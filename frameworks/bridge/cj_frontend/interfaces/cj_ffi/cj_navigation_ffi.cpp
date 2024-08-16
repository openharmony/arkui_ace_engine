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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "core/components_ng/pattern/navigation/navigation_model.h"
#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {

void ParseBarItems(const std::vector<NavigationItem> &items, std::vector<NG::BarItem>& barItems)
{
    for (size_t i = 0; i < items.size(); i++) {
        NG::BarItem toolBarItem;
        toolBarItem.text = items[i].value;
        toolBarItem.icon = items[i].icon;
        auto builderFunc = items[i].builder;
        auto onItemClick = [func = std::move(builderFunc)]() {
            func();
        };
        LOGD("ParseBarItems text: %{public}s, icon: %{public}s", toolBarItem.text->c_str(), toolBarItem.icon->c_str());
        toolBarItem.action = onItemClick;
        barItems.push_back(toolBarItem);
    }
}

}
extern "C" {
void FfiOHOSAceFrameworkNavigationCreate()
{
    NavigationModel::GetInstance()->Create();
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

void FfiOHOSAceFrameworkNavigationSetMenus(VectorNavigationItemHandle menus)
{
    const auto &menuVector = *reinterpret_cast<std::vector<NavigationItem> *>(menus);
    std::vector<NG::BarItem> menuItems;
    ParseBarItems(menuVector, menuItems);
    NavigationModel::GetInstance()->SetMenuItems(std::move(menuItems));
}

void FfiOHOSAceFrameworkNavigationSetMenusWithBuilder(void (*builder)())
{
    auto builderFunc = CJLambda::Create(builder);
    RefPtr<NG::UINode> customNode;
    {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        builderFunc();
        customNode = NG::ViewStackProcessor::GetInstance()->Finish();
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
    ParseBarItems(toolBarVector, toolBarItems);
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

void FfiOHOSAceFrameworkNavigationSetOnTitleModeChanged(void (*callback)(int32_t))
{
    auto onChange = CJLambda::Create(callback);
    auto onTitleModeChange = [func = std::move(onChange)](NG::NavigationTitleMode mode) {
        func(static_cast<int32_t>(mode));
    };
    NavigationModel::GetInstance()->SetOnTitleModeChange(std::move(onTitleModeChange), [](auto) {});
}
}
