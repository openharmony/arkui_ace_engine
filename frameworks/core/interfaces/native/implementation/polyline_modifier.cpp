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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"
#include "core/components_ng/pattern/shape/shape_abstract_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
struct PolylineOptions {
    std::optional<Dimension> width;
    std::optional<Dimension> height;
};
namespace {
    constexpr int POINTS_NUMBER_MIN = 2;
}
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
PolylineOptions Convert(const Ark_PolylineOptions& src)
{
    PolylineOptions options;
    options.width = Converter::OptConvert<Dimension>(src.width);
    options.height = Converter::OptConvert<Dimension>(src.height);
    return options;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PolylineModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // auto frameNode = PolygonModelNG::CreateFrameNode(id, false);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
    return nullptr;
}
} // PolylineModifier
namespace PolylineInterfaceModifier {
void SetPolylineOptionsImpl(Ark_NativePointer node,
                            const Opt_PolylineOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto opt = Converter::OptConvert<PolylineOptions>(*options);
    CHECK_NULL_VOID(opt);
    Validator::ValidateNonNegative(opt->width);
    // ShapeAbstractModelNG::SetWidth(frameNode, opt->width);
    Validator::ValidateNonNegative(opt->height);
    // ShapeAbstractModelNG::SetHeight(frameNode, opt->height);
}
} // PolylineInterfaceModifier
namespace PolylineAttributeModifier {
void PointsImpl(Ark_NativePointer node,
                const Array_Point* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<ShapePoints> points = Converter::Convert<std::vector<ShapePoint>>(*value);
    if (points->size() < POINTS_NUMBER_MIN) {
        points.reset();
    }
    // PolygonModelNG::SetPoints(frameNode, points);
}
} // PolylineAttributeModifier
const GENERATED_ArkUIPolylineModifier* GetPolylineModifier()
{
    static const GENERATED_ArkUIPolylineModifier ArkUIPolylineModifierImpl {
        PolylineModifier::ConstructImpl,
        PolylineInterfaceModifier::SetPolylineOptionsImpl,
        PolylineAttributeModifier::PointsImpl,
    };
    return &ArkUIPolylineModifierImpl;
}

}
