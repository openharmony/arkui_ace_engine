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
namespace drawing_LatticeAccessor {
void DestroyPeerImpl(Ark_drawing_Lattice peer)
{
}
Ark_drawing_Lattice ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_drawing_Lattice CreateImageLatticeImpl(const Array_Number* xDivs,
                                           const Array_Number* yDivs,
                                           const Ark_Number* fXCount,
                                           const Ark_Number* fYCount,
                                           const Opt_common2D_Rect* fBounds,
                                           const Opt_Array_drawing_RectType* fRectTypes,
                                           const Opt_Array_CustomObject* fColors)
{
    return {};
}
} // drawing_LatticeAccessor
const GENERATED_ArkUIDrawing_LatticeAccessor* GetDrawing_LatticeAccessor()
{
    static const GENERATED_ArkUIDrawing_LatticeAccessor Drawing_LatticeAccessorImpl {
        drawing_LatticeAccessor::DestroyPeerImpl,
        drawing_LatticeAccessor::ConstructImpl,
        drawing_LatticeAccessor::GetFinalizerImpl,
        drawing_LatticeAccessor::CreateImageLatticeImpl,
    };
    return &Drawing_LatticeAccessorImpl;
}

}
