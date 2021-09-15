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

#include "core/components_v2/inspector/tab_content_composed_element.h"

#include <unordered_map>

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const TabContentComposedElement&)>> CREATE_JSON_MAP {
    { "icon", [](const TabContentComposedElement& inspector) { return inspector.GetIcon(); } },
    { "text", [](const TabContentComposedElement& inspector) { return inspector.GetText(); } }
};

} // namespace

void TabContentComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("icon: ").append(GetIcon()));
    DumpLog::GetInstance().AddDesc(std::string("text: ").append(GetText()));
}

std::unique_ptr<JsonValue> TabContentComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string TabContentComposedElement::GetIcon() const
{
    auto element = GetTabContentItemElement();
    return element ? element->GetIcon() : "";
}

std::string TabContentComposedElement::GetText() const
{
    auto element = GetTabContentItemElement();
    return element ? element->GetText() : "";
}

RefPtr<TabContentItemElement> TabContentComposedElement::GetTabContentItemElement() const
{
    auto parent = GetElementParent().Upgrade();
    while (parent) {
        auto tabContentItem = AceType::DynamicCast<TabContentItemElement>(parent);
        if (tabContentItem) {
            return tabContentItem;
        }
        parent = parent->GetElementParent().Upgrade();
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2