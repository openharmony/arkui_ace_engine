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

#include "html_convert.h"

#include <dlfcn.h>
#include <string>
#include <unistd.h>
#include <vector>

namespace OHOS::Ace {
const constexpr char* CONVERT_FUNC_NAME = "OHOS_ACE_ConvertHmtlToSpanString";

using ConvertHtmlToSpanStringFunc = int (*)(std::vector<uint8_t>&, std::string&);

HtmlConvert::~HtmlConvert()
{
    if (handle_ != nullptr) {
        dlclose(handle_);
        handle_ = nullptr;
    }
}
std::string HtmlConvert::SpanStringToHtml(std::vector<uint8_t> &spanString)
{
    if (handle_ == nullptr) {
        handle_= dlopen("libace_compatible.z.so", RTLD_LAZY);
        if (handle_ == nullptr) {
            return "";
        }
    }

    auto entry = reinterpret_cast<ConvertHtmlToSpanStringFunc>(dlsym(handle_, CONVERT_FUNC_NAME));
    if (entry == nullptr) {
        dlclose(handle_);
        return nullptr;
    }
    std::string html;
    entry(spanString, html);
    return html;
}

}
