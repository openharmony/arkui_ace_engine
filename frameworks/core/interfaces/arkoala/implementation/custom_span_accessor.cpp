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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CustomSpanAccessor {
Ark_NativePointer CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
Ark_NativePointer OnMeasureImpl(CustomSpanPeer* peer,
                                const Ark_CustomSpanMeasureInfo* measureInfo)
{
    return 0;
}
void OnDrawImpl(CustomSpanPeer* peer,
                const Ark_CustomObject* context,
                const Ark_CustomSpanDrawInfo* drawInfo)
{
}
void InvalidateImpl(CustomSpanPeer* peer)
{
}
} // CustomSpanAccessor
const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor()
{
    static const GENERATED_ArkUICustomSpanAccessor CustomSpanAccessorImpl {
        CustomSpanAccessor::CtorImpl,
        CustomSpanAccessor::GetFinalizerImpl,
        CustomSpanAccessor::OnMeasureImpl,
        CustomSpanAccessor::OnDrawImpl,
        CustomSpanAccessor::InvalidateImpl,
    };
    return &CustomSpanAccessorImpl;
}

}