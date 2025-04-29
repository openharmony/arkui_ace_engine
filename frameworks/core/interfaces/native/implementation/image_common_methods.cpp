/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/implementation/image_common_methods.h"

namespace OHOS::Ace::NG::GeneratedModifier {
void ImageCommonMethods::ApplyColorFilterValues(
    Ark_NativePointer node, const Opt_Union_ColorFilter_DrawingColorFilter* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    bool isValid = false;
    if (value) {
        Converter::VisitUnion(
            *value,
            [frameNode, &isValid](const Ark_ColorFilter& filter) {
                if (filter && filter->GetColorFilterMatrix().size() == COLOR_FILTER_MATRIX_SIZE) {
                    isValid = true;
                    ImageModelNG::SetColorFilterMatrix(frameNode, filter->GetColorFilterMatrix());
                    return;
                }
            },
            [frameNode](const Ark_DrawingColorFilter& colorStrategy) {
                LOGE("Arkoala: Image.ColorFilterImpl - doesn't support DrawinColorFilter");
            },
            []() {});
    }
    if (isValid)
        return;
    ImageModelNG::SetColorFilterMatrix(frameNode, DEFAULT_COLORFILTER_MATRIX);
}
} // namespace OHOS::Ace::NG::GeneratedModifier
