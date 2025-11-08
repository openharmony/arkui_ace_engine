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

#include "core/interfaces/native/utility/converter.h"
#include "core/components_ng/pattern/select/select_model_static.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SelectExtenderAccessor {
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_DividerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto divider = SelectModelStatic::GetDefaultDivider(frameNode);
    if (options->tag == INTEROP_TAG_UNDEFINED) {
        SelectModelStatic::SetDivider(frameNode, divider);
        return;
    }
    auto dividerOptions = options->value;
    auto strokeWidthOpt = Converter::OptConvert<Dimension>(dividerOptions.strokeWidth);
    Validator::ValidateNonNegative(strokeWidthOpt);
    Validator::ValidateNonPercent(strokeWidthOpt);
    if (strokeWidthOpt.has_value()) {
        divider.strokeWidth = strokeWidthOpt.value();
    }
    auto colorOpt = Converter::OptConvert<Color>(dividerOptions.color);
    if (colorOpt.has_value()) {
        divider.color = colorOpt.value();
    }
    auto startMarginOpt = Converter::OptConvert<Dimension>(dividerOptions.startMargin);
    Validator::ValidateNonNegative(startMarginOpt);
    Validator::ValidateNonPercent(startMarginOpt);
    if (startMarginOpt.has_value()) {
        divider.startMargin = startMarginOpt.value();
    }
    auto endMarginOpt = Converter::OptConvert<Dimension>(dividerOptions.endMargin);
    Validator::ValidateNonNegative(endMarginOpt);
    Validator::ValidateNonPercent(endMarginOpt);
    if (endMarginOpt.has_value()) {
        divider.endMargin = endMarginOpt.value();
    }
    std::optional<SelectDivider> dividerOpt = divider;
    SelectModelStatic::SetDivider(frameNode, dividerOpt);
}
} // SelectExtenderAccessor
const GENERATED_ArkUISelectExtenderAccessor* GetSelectExtenderAccessor()
{
    static const GENERATED_ArkUISelectExtenderAccessor SelectExtenderAccessorImpl {
        SelectExtenderAccessor::SetDividerImpl,
    };
    return &SelectExtenderAccessorImpl;
}

}