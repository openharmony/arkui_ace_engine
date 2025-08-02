/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr int32_t SHAPE_POINT_DIM = 2;
} // namespace
struct LineOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};
}

namespace OHOS::Ace::NG::Converter {
template<>
LineOptions Convert(const Ark_LineOptions& src)
{
    LineOptions options;
    options.width = Converter::OptConvert<Dimension>(src.width);
    options.height = Converter::OptConvert<Dimension>(src.height);
    return options;
}

}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LineModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // auto frameNode = LineModelNG::CreateFrameNode(id);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
    return nullptr;
}
} // LineModifier
namespace LineInterfaceModifier {

void SetLineOptionsImpl(Ark_NativePointer node,
                        const Opt_LineOptions* options)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(options);
    // auto opt = Converter::OptConvert<LineOptions>(*options);
    // CHECK_NULL_VOID(opt);
    // if (opt->width) {
    //     ShapeAbstractModelNG::SetWidth(frameNode, opt->width);
    // }
    // if (opt->height) {
    //     ShapeAbstractModelNG::SetHeight(frameNode, opt->height);
    // }
}
} // LineInterfaceModifier
namespace LineAttributeModifier {
void StartPointImpl(Ark_NativePointer node,
                    const Opt_ShapePoint* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ShapePoint>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    LineModelNG::StartPoint(frameNode, *convValue);
}
void EndPointImpl(Ark_NativePointer node,
                  const Opt_ShapePoint* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<ShapePoint>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    LineModelNG::EndPoint(frameNode, *convValue);
}
} // LineAttributeModifier
const GENERATED_ArkUILineModifier* GetLineModifier()
{
    static const GENERATED_ArkUILineModifier ArkUILineModifierImpl {
        LineModifier::ConstructImpl,
        LineInterfaceModifier::SetLineOptionsImpl,
        LineAttributeModifier::StartPointImpl,
        LineAttributeModifier::EndPointImpl,
    };
    return &ArkUILineModifierImpl;
}

}
