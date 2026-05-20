/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/distortion_component/distortion_component_node.h"
#include "core/components_ng/pattern/distortion_component/distortion_component_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DistortionComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = DistortionComponentNode::GetOrCreateDistortionComponentNode(
        V2::DISTORTION_COMPONENT_ETS_TAG, id, []() { return AceType::MakeRefPtr<DistortionComponentPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto pattern = frameNode->GetPattern<DistortionComponentPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->CreateContentNode();
    return AceType::RawPtr(frameNode);
}
} // DistortionComponentModifier
namespace DistortionComponentInterfaceModifier {
void SetDistortionComponentOptionsImpl(Ark_NativePointer node,
                                       const Opt_DistortionComponentOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<DistortionComponentPattern>();
    CHECK_NULL_VOID(pattern);
    if (!options || options->tag == INTEROP_TAG_UNDEFINED) {
        return;
    }
    NG::DistortionParam distortionParam;
    const auto& distortion = options->value.distortion;
    if (distortion.tag != INTEROP_TAG_UNDEFINED) {
        const auto& value = distortion.value;
        distortionParam.luCorner = NG::VectorF(
            static_cast<float>(value.topLeft.x), static_cast<float>(value.topLeft.y));
        distortionParam.ruCorner = NG::VectorF(
            static_cast<float>(value.topRight.x), static_cast<float>(value.topRight.y));
        distortionParam.lbCorner = NG::VectorF(
            static_cast<float>(value.bottomLeft.x), static_cast<float>(value.bottomLeft.y));
        distortionParam.rbCorner = NG::VectorF(
            static_cast<float>(value.bottomRight.x), static_cast<float>(value.bottomRight.y));
        distortionParam.barrelDistortion = NG::Vector4F(
            value.barrelDistortion.x,
            value.barrelDistortion.y,
            value.barrelDistortion.w,
            value.barrelDistortion.z);
    }
    pattern->SetDistortion(distortionParam);
}
} // DistortionComponentInterfaceModifier
const GENERATED_ArkUIDistortionComponentModifier* GetDistortionComponentModifier()
{
    static const GENERATED_ArkUIDistortionComponentModifier ArkUIDistortionComponentModifierImpl {
        DistortionComponentModifier::ConstructImpl,
        DistortionComponentInterfaceModifier::SetDistortionComponentOptionsImpl,
    };
    return &ArkUIDistortionComponentModifierImpl;
}

}
