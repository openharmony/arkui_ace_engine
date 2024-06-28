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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_UTIL_H
#include <string>

namespace OHOS::Ace::NG {

const std::string UNSUPPORTED = "data:image/png";
const std::string URL_PREFIX = "data:";
const std::string URL_SYMBOL = ";base64,";
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";

constexpr int32_t MAX_LENGTH = 2048 * 2048;
constexpr double HANGING_PERCENT = 0.8;
constexpr double DEFAULT_QUALITY = 0.92;

// If args is empty or invalid format, use default: image/png
std::string GetMimeType(const std::string& args);

// Quality need between 0.0 and 1.0 for MimeType jpeg and webp
double GetQuality(const std::string& args);
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_CUSTOM_PAINT_UTIL_H