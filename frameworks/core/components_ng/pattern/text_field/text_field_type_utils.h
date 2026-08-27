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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TYPE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TYPE_UTILS_H

#include <string>

#include "base/utils/macros.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"

namespace OHOS::Ace::NG::TextFieldTypeUtils {

ACE_FORCE_EXPORT std::string ToInputTypeString(TextInputType type, bool isTextArea, bool isTextInput);

ACE_FORCE_EXPORT std::string ToContentTypeString(TextContentType type);

std::string ToInputTypeName(TextInputType type, bool isTextArea, bool isTextInput);

std::string ToContentTypeName(TextContentType type);

} // namespace OHOS::Ace::NG::TextFieldTypeUtils

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TYPE_UTILS_H
