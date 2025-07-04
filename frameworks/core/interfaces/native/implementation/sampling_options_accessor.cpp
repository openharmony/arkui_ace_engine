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
namespace drawing_SamplingOptionsAccessor {
void DestroyPeerImpl(Ark_drawing_SamplingOptions peer)
{
}
Ark_drawing_SamplingOptions Construct0Impl()
{
    return {};
}
Ark_drawing_SamplingOptions Construct1Impl(Ark_drawing_FilterMode filterMode)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
} // drawing_SamplingOptionsAccessor
const GENERATED_ArkUIDrawing_SamplingOptionsAccessor* GetDrawing_SamplingOptionsAccessor()
{
    static const GENERATED_ArkUIDrawing_SamplingOptionsAccessor Drawing_SamplingOptionsAccessorImpl {
        drawing_SamplingOptionsAccessor::DestroyPeerImpl,
        drawing_SamplingOptionsAccessor::Construct0Impl,
        drawing_SamplingOptionsAccessor::Construct1Impl,
        drawing_SamplingOptionsAccessor::GetFinalizerImpl,
    };
    return &Drawing_SamplingOptionsAccessorImpl;
}

}
