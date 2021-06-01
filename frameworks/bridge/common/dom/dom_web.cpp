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

#include "frameworks/bridge/common/dom/dom_web.h"

#include "base/log/log.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

DOMWeb::DOMWeb(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    webChild_ = AceType::MakeRefPtr<WebComponent>(nodeName);
}

bool DOMWeb::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<void (*)(const std::string&, WebComponent&)>
        webAttrOperators[] = {
            { DOM_WEB_WEBSRC, [](const std::string& val, WebComponent& webCom) { webCom.SetSrc(val); } },
        };
    auto operatorIter = BinarySearchFindIndex(webAttrOperators, ArraySize(webAttrOperators),
                                              attr.first.c_str());
    if (operatorIter != -1) {
        webAttrOperators[operatorIter].value(attr.second, *webChild_);
        return true;
    }
    return false;
}

bool DOMWeb::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    // Operator map for event
    static const std::unordered_map<std::string, void (*)(const RefPtr<WebComponent>&, const EventMarker&)>
            eventOperators = {
                { DOM_PAGESTART, [](const RefPtr<WebComponent>& web,
                                const EventMarker& event) { web->SetPageStartedEventId(event); } },
                { DOM_PAGEFINISH, [](const RefPtr<WebComponent>& web,
                                 const EventMarker& event) { web->SetPageFinishedEventId(event); } },
                { DOM_PAGEERROR, [](const RefPtr<WebComponent>& web,
                                const EventMarker& event) { web->SetPageErrorEventId(event); } },
    };
    auto operatorIter = eventOperators.find(event);
    if (operatorIter != eventOperators.end()) {
        operatorIter->second(webChild_, EventMarker(GetNodeIdForEvent(), event, pageId));
        return true;
    }
    return false;
}

void DOMWeb::CallSpecializedMethod(const std::string& method, const std::string& args)
{
    // Operator map for method
    static const std::unordered_map<std::string, void (*)(const RefPtr<WebComponent>&, const std::string&)>
            methedOperators = {
                { DOM_METHOD_RELOAD, [](const RefPtr<WebComponent>& web, const std::string& args) {
                    web->Reload();
                } },
    };
    auto operatorIter = methedOperators.find(method);
    if (operatorIter != methedOperators.end()) {
        operatorIter->second(webChild_, args);
    }
}

} // namespace OHOS::Ace::Framework
