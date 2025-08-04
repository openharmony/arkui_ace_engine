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
namespace text_LineTypesetAccessor {
void DestroyPeerImpl(Ark_text_LineTypeset peer)
{
}
Ark_text_LineTypeset ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetLineBreakImpl(Ark_text_LineTypeset peer,
                            const Ark_Number* startIndex,
                            const Ark_Number* width)
{
    return {};
}
Ark_text_TextLine CreateLineImpl(Ark_text_LineTypeset peer,
                                 const Ark_Number* startIndex,
                                 const Ark_Number* count)
{
    return {};
}
} // text_LineTypesetAccessor
const GENERATED_ArkUIText_LineTypesetAccessor* GetText_LineTypesetAccessor()
{
    static const GENERATED_ArkUIText_LineTypesetAccessor Text_LineTypesetAccessorImpl {
        text_LineTypesetAccessor::DestroyPeerImpl,
        text_LineTypesetAccessor::ConstructImpl,
        text_LineTypesetAccessor::GetFinalizerImpl,
        text_LineTypesetAccessor::GetLineBreakImpl,
        text_LineTypesetAccessor::CreateLineImpl,
    };
    return &Text_LineTypesetAccessorImpl;
}

}
