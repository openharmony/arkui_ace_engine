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

#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/components_ng/pattern/shape/path_model_ng.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"


namespace OHOS::Ace::NG {
namespace {
struct PathOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
    std::optional<std::string> commands;
};
}

namespace Converter {
template<>
PathOptions Convert(const Ark_Literal_Union_Number_String_height_width_String_commands& src)
{
    return {
        .width = Converter::OptConvert<Dimension>(src.width),
        .height = Converter::OptConvert<Dimension>(src.height),
        .commands = OptConvert<std::string>(src.commands),
    };
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PathInterfaceModifier {
void SetPathOptionsImpl(Ark_NativePointer node,
                        const Opt_Literal_Union_Number_String_height_width_String_commands* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::OptConvert<PathOptions>(*value);
    if (options && options->width) {
        ShapeAbstractModelNG::SetWidth(frameNode, *(options->width));
    }
    if (options && options->height) {
        ShapeAbstractModelNG::SetHeight(frameNode, *(options->height));
    }
    if (options && options->commands) {
        PathModelNG::SetCommands(frameNode, *(options->commands));
    }
}
} // PathInterfaceModifier
namespace PathAttributeModifier {
void CommandsImpl(Ark_NativePointer node,
                  const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    PathModelNG::SetCommands(frameNode, Converter::Convert<std::string>(*value));
}
} // PathAttributeModifier
const GENERATED_ArkUIPathModifier* GetPathModifier()
{
    static const GENERATED_ArkUIPathModifier ArkUIPathModifierImpl {
        PathInterfaceModifier::SetPathOptionsImpl,
        PathAttributeModifier::CommandsImpl,
    };
    return &ArkUIPathModifierImpl;
}

}
