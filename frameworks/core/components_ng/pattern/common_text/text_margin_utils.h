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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_TEXT_MARGIN_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_TEXT_MARGIN_UTILS_H

#include "core/components_ng/property/measure_property.h"
#include "core/common/resource/resource_object.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace::NG {
class FrameNode;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

// Bundles the four ArkUISizeType sides of a margin (top/right/bottom/left) that always travel
// together, to keep the shared margin util signatures concise.
struct MarginSizeTypes {
    const struct ArkUISizeType* top;
    const struct ArkUISizeType* right;
    const struct ArkUISizeType* bottom;
    const struct ArkUISizeType* left;
};

// Function pointer types for model-specific set/get functions
using SetMarginFunc = void (*)(NG::FrameNode*, const NG::PaddingProperty&);
using GetMarginFunc = NG::PaddingProperty (*)(NG::FrameNode*);

// Shared CalcLength conversion from ArkUISizeType (identical in RichEditor, TextArea, TextInput)
NG::CalcLength CalcLengthFromSizeType(const struct ArkUISizeType* size);

// Shared margin resource registration (identical in RichEditor, TextArea, TextInput)
void RegisterMarginResource(NG::FrameNode* frameNode, const MarginSizeTypes& sizes,
    ArkUIPaddingRes* marginRes);

// Shared set/reset/get functions (identical except for model-specific function pointers)
void SetMarginCommon(ArkUINodeHandle node, const MarginSizeTypes& sizes,
    ArkUIPaddingRes* marginRes, SetMarginFunc setFunc);
void ResetMarginCommon(ArkUINodeHandle node, SetMarginFunc setFunc);
void GetMarginCommon(ArkUINodeHandle node, ArkUI_Float32 (*values)[4],
    ArkUI_Int32 length, ArkUI_Int32 unit, GetMarginFunc getFunc);

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_TEXT_MARGIN_UTILS_H
