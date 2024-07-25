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

#include "core/components_ng/pattern/canvas/custom_paint_util.h"

#include "base/utils/string_utils.h"

namespace OHOS::Ace::NG {

const int32_t MIME_TYPE_COLUMN_NUM = 2;

// If args is empty or invalid format, use default: image/png
std::string GetMimeType(const std::string& args)
{
    // args example: ["image/png", 0.8]
    std::vector<std::string> values;
    StringUtils::StringSplitter(args, ',', values);
    if ((values.size() > MIME_TYPE_COLUMN_NUM) || values.empty()) {
        return IMAGE_PNG;
    }
    // convert to lowercase string, e.g. "image/png"
    for (size_t i = 0; i < values[0].size(); ++i) {
        values[0][i] = static_cast<uint8_t>(tolower(values[0][i]));
    }
    return values[0];
}

// Quality needs to be between 0.0 and 1.0 for MimeType jpeg and webp
double GetQuality(const std::string& args)
{
    // Args example: ["image/jpeg", 0.8]
    std::vector<std::string> values;
    StringUtils::StringSplitter(args, ',', values);
    if (values.size() < MIME_TYPE_COLUMN_NUM) {
        return DEFAULT_QUALITY;
    }
    auto mimeType = GetMimeType(args);
    if (mimeType != IMAGE_JPEG && mimeType != IMAGE_WEBP) {
        return DEFAULT_QUALITY;
    }
    double quality = StringUtils::StringToDouble(values[1]);
    if (quality < 0.0 || quality > 1.0) {
        return DEFAULT_QUALITY;
    }
    return quality;
}
} // namespace OHOS::Ace::NG
