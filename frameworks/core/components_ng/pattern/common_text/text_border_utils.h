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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_TEXT_BORDER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_TEXT_BORDER_UTILS_H

#include "core/components_ng/property/border_property.h"
#include "core/common/resource/resource_object.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
class FrameNode;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

// Shared border style conversion (identical in RichEditor and TextArea)
BorderStyle ConvertBorderStyle(int32_t value);

// Shared border color resource parsing (identical in RichEditor and TextArea)
void ParseBorderColor(NG::BorderColorProperty& borderColors, const RefPtr<ResourceObject>& topResObj,
    const RefPtr<ResourceObject>& rightResObj, const RefPtr<ResourceObject>& bottomResObj,
    const RefPtr<ResourceObject>& leftResObj);

// Function pointer types for model-specific set functions
using SetBorderWidthFunc = void (*)(NG::FrameNode*, const NG::BorderWidthProperty&);
using SetBorderColorFunc = void (*)(NG::FrameNode*, const NG::BorderColorProperty&);
using SetBorderStyleFunc = void (*)(NG::FrameNode*, const NG::BorderStyleProperty&);
using SetBorderRadiusFunc = void (*)(NG::FrameNode*, const NG::BorderRadiusProperty&);

// Shared set functions (identical except for the model set function called)
void SetBorderWidthCommon(ArkUINodeHandle node, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length, SetBorderWidthFunc setFunc);
void SetBorderColorCommon(ArkUINodeHandle node, const ArkUI_Uint32* colors,
    void* res, SetBorderColorFunc setFunc);
void SetBorderStyleCommon(ArkUINodeHandle node, const ArkUI_Int32* styles,
    ArkUI_Int32 length, SetBorderStyleFunc setFunc);
void SetBorderRadiusCommon(ArkUINodeHandle node, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length, SetBorderRadiusFunc setFunc);

// Shared reset functions (identical except for the model set function called)
void ResetBorderWidthCommon(ArkUINodeHandle node, SetBorderWidthFunc setFunc);
void ResetBorderColorCommon(ArkUINodeHandle node, SetBorderColorFunc setFunc);
void ResetBorderStyleCommon(ArkUINodeHandle node, SetBorderStyleFunc setFunc);
void ResetBorderRadiusCommon(ArkUINodeHandle node, SetBorderRadiusFunc setFunc);

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_TEXT_BORDER_UTILS_H
