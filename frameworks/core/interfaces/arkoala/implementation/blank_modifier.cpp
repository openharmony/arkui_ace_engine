/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_api.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BlankInterface {
void _setBlankOptionsImpl(Ark_NativePointer node, const Opt_Type_BlankInterface__setBlankOptions_Arg0 *min) {
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    std::tuple<Ark_Float32, Ark_Int32> dimension = Converter::ConvertOrDefault(
        *min, std::make_tuple(0.0f, (int)DimensionUnit::PX));
    BlankModelNG::SetBlankMin(
        frameNode, CalcDimension(std::get<0>(dimension),
                                (DimensionUnit)std::get<1>(dimension)));
}
} // BlankInterface

namespace BlankAttribute {
void ColorImpl(Ark_NativePointer node, const ResourceColor *value) {
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        BlankModelNG::SetColor(frameNode, color.value());
        LOGI("#### BlankAttribute::Color impl: color is %{public}s", color.value().ToString().c_str());
    } else {
        LOGI("#### BlankAttribute::Color impl: color is empty");
    }
}
} // BlankAttribute

const GENERATED_ArkUIBlankModifier *GetBlankModifier() {
    static GENERATED_ArkUIBlankModifier ArkUIBlankModifierImpl{
        BlankInterface::_setBlankOptionsImpl,
        BlankAttribute::ColorImpl,
    };

  return &ArkUIBlankModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
