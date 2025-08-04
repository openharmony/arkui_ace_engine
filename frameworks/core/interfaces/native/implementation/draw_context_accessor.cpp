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
namespace DrawContextAccessor {
void DestroyPeerImpl(Ark_DrawContext peer)
{
}
Ark_DrawContext ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Size SizeImpl(Ark_DrawContext peer)
{
    return {};
}
Ark_Size SizeInPixelImpl(Ark_DrawContext peer)
{
    return {};
}
Ark_drawing_Canvas CanvasImpl(Ark_DrawContext peer)
{
    return {};
}
} // DrawContextAccessor
const GENERATED_ArkUIDrawContextAccessor* GetDrawContextAccessor()
{
    static const GENERATED_ArkUIDrawContextAccessor DrawContextAccessorImpl {
        DrawContextAccessor::DestroyPeerImpl,
        DrawContextAccessor::ConstructImpl,
        DrawContextAccessor::GetFinalizerImpl,
        DrawContextAccessor::SizeImpl,
        DrawContextAccessor::SizeInPixelImpl,
        DrawContextAccessor::CanvasImpl,
    };
    return &DrawContextAccessorImpl;
}

}
