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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PolygonModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // PolygonModifier
namespace PolygonInterfaceModifier {
void SetPolygonOptionsImpl(Ark_NativePointer node,
                           const Opt_PolygonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //PolygonModelNG::SetSetPolygonOptions(frameNode, convValue);
}
} // PolygonInterfaceModifier
namespace PolygonAttributeModifier {
void PointsImpl(Ark_NativePointer node,
                const Array_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //PolygonModelNG::SetPoints(frameNode, convValue);
}
} // PolygonAttributeModifier
const GENERATED_ArkUIPolygonModifier* GetPolygonModifier()
{
    static const GENERATED_ArkUIPolygonModifier ArkUIPolygonModifierImpl {
        PolygonModifier::ConstructImpl,
        PolygonInterfaceModifier::SetPolygonOptionsImpl,
        PolygonAttributeModifier::PointsImpl,
    };
    return &ArkUIPolygonModifierImpl;
}

}
