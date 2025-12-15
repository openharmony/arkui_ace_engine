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

#include "core/components_ng/pattern/web/web_dom_document.h"

#include "base/log/dump_log.h"

namespace OHOS::Ace::NG {

WebDomDocument::WebDomDocument()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebDomDocument::WebDomDocument");
}

std::pair<int32_t, RectF> WebDomDocument::GetScrollAreaInfoById(int32_t id)
{
    return {-1, RectF()};
}

std::string WebDomDocument::GetXpathById(int32_t id)
{
    return "";
}

std::string WebDomDocument::GetImageUrlById(int32_t id)
{
    return "";
}
} // namespace OHOS::Ace::NG