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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_SAPN_STRING_HTML_CONVERT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_SAPN_STRING_HTML_CONVERT_H

#include <cstdint>
#include <string>
#include <vector>

#ifndef ACE_EXPORT
#define ACE_EXPORT __attribute__((visibility("default")))
#endif

namespace OHOS::Ace {
class ACE_EXPORT HtmlConvert {
public:
    ~HtmlConvert();
    std::string SpanStringToHtml(std::vector<uint8_t> &spanString);
private:
    void* handle_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_SAPN_STRING_HTML_CONVERT_H
