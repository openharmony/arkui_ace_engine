/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_v2/inspector/navigation_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {

namespace {

const std::unordered_map<std::string, std::function<std::string(const NavigationComposedElement&)>>
    CREATE_JSON_STRING_MAP {
        { "title",
            [](const NavigationComposedElement& inspector) { return inspector.GetNavigationTitle(); } },
        { "subtitle",
            [](const NavigationComposedElement& inspector) { return inspector.GetNavigationSubTitle(); } }
    };

const std::unordered_map<std::string, std::function<bool(const NavigationComposedElement&)>>
    CREATE_JSON_BOOL_MAP {
        { "hideBackButton",
            [](const NavigationComposedElement& inspector) { return inspector.GetHideNavigationBackButton(); } },
        { "hideTitleBar",
            [](const NavigationComposedElement& inspector) { return inspector.GetHideNavigationBar(); } }
    };

}

void NavigationComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("navigationTitle: ").append(GetNavigationTitle()));
    DumpLog::GetInstance().AddDesc(
        std::string("navigationSubTitle: ").append(GetNavigationSubTitle()));
    DumpLog::GetInstance().AddDesc(
        std::string("hideNavigationBackButton: ").append(GetHideNavigationBackButton() ? "true" : "false"));
    DumpLog::GetInstance().AddDesc(
        std::string("hideNavigationBar: ").append(GetHideNavigationBar() ? "true" : "false"));
}

std::unique_ptr<JsonValue> NavigationComposedElement::ToJsonObject() const
{
    LOGI("raul ToJsonObject11");
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_STRING_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    for (const auto& value : CREATE_JSON_BOOL_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this));
    }
    return resultJson;
}

std::string NavigationComposedElement::GetNavigationTitle() const
{
    auto render = GetRenderNavigation();
    if (!render) {
        return "";
    }
    return render->GetTitle();
}

std::string NavigationComposedElement::GetNavigationSubTitle() const
{
    auto render = GetRenderNavigation();
    if (!render) {
        return "";
    }
    return render->GetSubTitle();
}

bool NavigationComposedElement::GetHideNavigationBackButton() const
{
    auto render = GetRenderNavigation();
    if (!render) {
        return false;
    }
    return render->GetHideBackButton();
}

bool NavigationComposedElement::GetHideNavigationBar() const
{
    auto render = GetRenderNavigation();
    if (!render) {
        return false;
    }
    return render->GetHideNavigationBar();
}

RefPtr<RenderNavigationContainer> NavigationComposedElement::GetRenderNavigation() const
{
    auto node = GetInspectorNode(NavigationContainerElement::TypeId());
    if (!node) {
        return nullptr;
    }
    return AceType::DynamicCast<RenderNavigationContainer>(node);
}

} // namespace OHOS::Ace::V2