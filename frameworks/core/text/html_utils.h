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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_TEXT_ACE_TEXT_HTML_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_TEXT_ACE_TEXT_HTML_UTILS_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"

namespace OHOS::Ace {

class MutableSpanString;
class SpanString;

class ACE_FORCE_EXPORT HtmlUtils {
public:
    static RefPtr<MutableSpanString> FromHtml(const std::string& str);
    static std::string ToHtml(const SpanString* str);
    static std::string ToHtml(const std::list<RefPtr<NG::SpanItem>>& spanItems);
    static std::string ToHtmlForNormalType(const NG::FontStyle& fontStyle,
        const NG::TextLineStyle& textLineStyle, const std::u16string& contentStr);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_TEXT_ACE_TEXT_HTML_UTILS_H
