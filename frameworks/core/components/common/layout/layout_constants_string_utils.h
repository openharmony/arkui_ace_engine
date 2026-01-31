/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_STRING_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_STRING_UTILS_H

#include <string>

#include "ui/base/macros.h"

namespace OHOS::Ace {

// Forward declarations for enums (defined in constants.h with underlying type)
enum class TextAlign;
enum class TextVerticalAlign;
enum class TextSelectableMode;
enum class TextOverflow;
enum class TextDecoration;
enum class TextDecorationStyle;
enum class ImageFit;
enum class RenderStrategy;
enum class VerticalAlign;
enum class CopyOptions;

namespace StringUtils {

// Function declarations for ToString methods (implementations in .cpp)
ACE_FORCE_EXPORT std::string ToString(const TextAlign& textAlign);
ACE_FORCE_EXPORT std::string ToString(const TextVerticalAlign& textVerticalAlign);
ACE_FORCE_EXPORT std::string ToString(const TextSelectableMode& textSelectableMode);
ACE_FORCE_EXPORT std::string ToString(const TextOverflow& textOverflow);
ACE_FORCE_EXPORT std::string ToString(const TextDecoration& textDecoration);
ACE_FORCE_EXPORT std::string ToString(const TextDecorationStyle& textDecorationStyle);
ACE_FORCE_EXPORT std::string ToString(const ImageFit& imageFit);
ACE_FORCE_EXPORT std::string ToString(const RenderStrategy& renderStrategy);
ACE_FORCE_EXPORT std::string ToString(const VerticalAlign& verticalAlign);
ACE_FORCE_EXPORT std::string ToString(const CopyOptions& copyOptions);

} // namespace StringUtils

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_STRING_UTILS_H
