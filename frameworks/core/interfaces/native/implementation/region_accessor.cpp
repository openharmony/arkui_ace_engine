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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace drawing_RegionAccessor {
void DestroyPeerImpl(Ark_drawing_Region peer)
{
}
Ark_drawing_Region ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsPointContainedImpl(Ark_drawing_Region peer,
                                 const Ark_Number* x,
                                 const Ark_Number* y)
{
    return {};
}
Ark_Boolean IsRegionContainedImpl(Ark_drawing_Region peer,
                                  Ark_drawing_Region other)
{
    return {};
}
Ark_Boolean OpImpl(Ark_drawing_Region peer,
                   Ark_drawing_Region region,
                   Ark_drawing_RegionOp regionOp)
{
    return {};
}
Ark_Boolean QuickRejectImpl(Ark_drawing_Region peer,
                            const Ark_Number* left,
                            const Ark_Number* top,
                            const Ark_Number* right,
                            const Ark_Number* bottom)
{
    return {};
}
Ark_Boolean SetPathImpl(Ark_drawing_Region peer,
                        Ark_drawing_Path path,
                        Ark_drawing_Region clip)
{
    return {};
}
Ark_Boolean SetRectImpl(Ark_drawing_Region peer,
                        const Ark_Number* left,
                        const Ark_Number* top,
                        const Ark_Number* right,
                        const Ark_Number* bottom)
{
    return {};
}
} // drawing_RegionAccessor
const GENERATED_ArkUIDrawing_RegionAccessor* GetDrawing_RegionAccessor()
{
    static const GENERATED_ArkUIDrawing_RegionAccessor Drawing_RegionAccessorImpl {
        drawing_RegionAccessor::DestroyPeerImpl,
        drawing_RegionAccessor::ConstructImpl,
        drawing_RegionAccessor::GetFinalizerImpl,
        drawing_RegionAccessor::IsPointContainedImpl,
        drawing_RegionAccessor::IsRegionContainedImpl,
        drawing_RegionAccessor::OpImpl,
        drawing_RegionAccessor::QuickRejectImpl,
        drawing_RegionAccessor::SetPathImpl,
        drawing_RegionAccessor::SetRectImpl,
    };
    return &Drawing_RegionAccessorImpl;
}

}
