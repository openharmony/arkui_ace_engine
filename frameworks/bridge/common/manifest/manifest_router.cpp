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

#include "frameworks/bridge/common/manifest/manifest_router.h"

#include <algorithm>

#include "base/log/event_report.h"

namespace OHOS::Ace::Framework {

std::string ManifestRouter::GetEntry(const std::string& suffix) const
{
    if (pages_.empty()) {
        LOGE("pages list is empty");
        return "";
    }
    return pages_.front() + suffix;
}

std::string ManifestRouter::GetPagePath(const std::string& uri, const std::string& suffix) const
{
    if (uri.empty()) {
        LOGW("page uri is empty");
        return "";
    }
    // the case uri is starts with "/" and "/" is the mainPage
    if (uri.front() == '/') {
        if (uri.size() == 1) {
            return pages_.front() + suffix;
        }
    } else {
        if (std::find(std::begin(pages_), std::end(pages_), uri) != std::end(pages_)) {
            return uri + suffix;
        }
    }
    LOGE("can't find this page %{private}s path", uri.c_str());
    return "";
}

const std::list<std::string>& ManifestRouter::GetPageList() const
{
    return pages_;
}

void ManifestRouter::RouterParse(const std::unique_ptr<JsonValue>& root)
{
    if (!root) {
        return;
    }

    auto pagesArray = root->GetValue("pages");
    if (pagesArray && pagesArray->IsArray()) {
        for (int32_t index = 0; index < pagesArray->GetArraySize(); index++) {
            auto page = pagesArray->GetArrayItem(index);
            if (page && page->IsString()) {
                pages_.emplace_back(page->GetString());
            } else {
                LOGW("page is not a string.");
            }
        }
    }

    if (pages_.empty()) {
        LOGE("Nothing is parsed for page list.");
        EventReport::SendPageRouterException(PageRouterExcepType::ROUTE_PARSE_ERR);
    }
}

} // namespace OHOS::Ace::Framework
