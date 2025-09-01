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
namespace CustomSpanAccessor {
void DestroyPeerImpl(Ark_CustomSpan peer)
{
}
Ark_CustomSpan ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InvalidateImpl(Ark_CustomSpan peer)
{
}
Callback_CustomSpanMeasureInfo_CustomSpanMetrics GetOnMeasureImpl(Ark_CustomSpan peer)
{
    return {};
}
void SetOnMeasureImpl(Ark_CustomSpan peer,
                      const Callback_CustomSpanMeasureInfo_CustomSpanMetrics* onMeasure)
{
}
Callback_DrawContext_CustomSpanDrawInfo_Void GetOnDrawImpl(Ark_CustomSpan peer)
{
    return {};
}
void SetOnDrawImpl(Ark_CustomSpan peer,
                   const Callback_DrawContext_CustomSpanDrawInfo_Void* onDraw)
{
}
} // CustomSpanAccessor
const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor()
{
    static const GENERATED_ArkUICustomSpanAccessor CustomSpanAccessorImpl {
        CustomSpanAccessor::DestroyPeerImpl,
        CustomSpanAccessor::ConstructImpl,
        CustomSpanAccessor::GetFinalizerImpl,
        CustomSpanAccessor::InvalidateImpl,
        CustomSpanAccessor::GetOnMeasureImpl,
        CustomSpanAccessor::SetOnMeasureImpl,
        CustomSpanAccessor::GetOnDrawImpl,
        CustomSpanAccessor::SetOnDrawImpl,
    };
    return &CustomSpanAccessorImpl;
}

}
