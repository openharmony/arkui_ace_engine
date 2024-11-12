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
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
struct LineOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};
}

namespace OHOS::Ace::NG::Converter {
template<>
LineOptions Convert(const Ark_Literal_Union_String_Number_height_width& src)
{
    LineOptions options;
    options.width = Converter::OptConvert<Dimension>(src.width);
    options.height = Converter::OptConvert<Dimension>(src.height);
    return options;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LineInterfaceModifier {

void SetLineOptionsImpl(Ark_NativePointer node,
                        const Opt_Literal_Union_String_Number_height_width* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<LineOptions>(*value);
    CHECK_NULL_VOID(options);
    if (options->width) {
        ShapeAbstractModelNG::SetWidth(frameNode, options->width.value());
    }

    if (options->height) {
        ShapeAbstractModelNG::SetHeight(frameNode, options->height.value());
    }
}
} // LineInterfaceModifier
namespace LineAttributeModifier {
void StartPointImpl(Ark_NativePointer node,
                    const Array_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //LineModelNG::SetStartPoint(frameNode, convValue);
}
void EndPointImpl(Ark_NativePointer node,
                  const Array_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //LineModelNG::SetEndPoint(frameNode, convValue);
}
} // LineAttributeModifier
const GENERATED_ArkUILineModifier* GetLineModifier()
{
    static const GENERATED_ArkUILineModifier ArkUILineModifierImpl {
        LineInterfaceModifier::SetLineOptionsImpl,
        LineAttributeModifier::StartPointImpl,
        LineAttributeModifier::EndPointImpl,
    };
    return &ArkUILineModifierImpl;
}

}
