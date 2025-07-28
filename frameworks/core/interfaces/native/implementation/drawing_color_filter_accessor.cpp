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
namespace DrawingColorFilterAccessor {
void DestroyPeerImpl(Ark_DrawingColorFilter peer)
{
}
Ark_DrawingColorFilter CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_DrawingColorFilter CreateBlendModeColorFilter0Impl(Ark_Color color,
                                                       Ark_BlendMode mode)
{
    return {};
}
Ark_DrawingColorFilter CreateBlendModeColorFilter1Impl(const Ark_Number* color,
                                                       Ark_BlendMode mode)
{
    return {};
}
Ark_DrawingColorFilter CreateComposeColorFilterImpl(Ark_DrawingColorFilter outer,
                                                    Ark_DrawingColorFilter inner)
{
    return {};
}
Ark_DrawingColorFilter CreateLinearToSRGBGammaImpl()
{
    return {};
}
Ark_DrawingColorFilter CreateSRGBGammaToLinearImpl()
{
    return {};
}
Ark_DrawingColorFilter CreateLumaColorFilterImpl()
{
    return {};
}
Ark_DrawingColorFilter CreateMatrixColorFilterImpl(const Array_Number* matrix)
{
    return {};
}
} // DrawingColorFilterAccessor
const GENERATED_ArkUIDrawingColorFilterAccessor* GetDrawingColorFilterAccessor()
{
    static const GENERATED_ArkUIDrawingColorFilterAccessor DrawingColorFilterAccessorImpl {
        DrawingColorFilterAccessor::DestroyPeerImpl,
        DrawingColorFilterAccessor::CtorImpl,
        DrawingColorFilterAccessor::GetFinalizerImpl,
        DrawingColorFilterAccessor::CreateBlendModeColorFilter0Impl,
        DrawingColorFilterAccessor::CreateBlendModeColorFilter1Impl,
        DrawingColorFilterAccessor::CreateComposeColorFilterImpl,
        DrawingColorFilterAccessor::CreateLinearToSRGBGammaImpl,
        DrawingColorFilterAccessor::CreateSRGBGammaToLinearImpl,
        DrawingColorFilterAccessor::CreateLumaColorFilterImpl,
        DrawingColorFilterAccessor::CreateMatrixColorFilterImpl,
    };
    return &DrawingColorFilterAccessorImpl;
}

}
