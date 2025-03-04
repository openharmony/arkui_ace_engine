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
namespace ParagraphStyleAccessor {
void DestroyPeerImpl(Ark_ParagraphStyle peer)
{
}
Ark_ParagraphStyle CtorImpl(const Opt_ParagraphStyleInterface* value)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TextAlign GetTextAlignImpl(Ark_ParagraphStyle peer)
{
    return {};
}
Ark_Number GetTextIndentImpl(Ark_ParagraphStyle peer)
{
    return {};
}
Ark_Number GetMaxLinesImpl(Ark_ParagraphStyle peer)
{
    return {};
}
Ark_TextOverflow GetOverflowImpl(Ark_ParagraphStyle peer)
{
    return {};
}
Ark_WordBreak GetWordBreakImpl(Ark_ParagraphStyle peer)
{
    return {};
}
} // ParagraphStyleAccessor
const GENERATED_ArkUIParagraphStyleAccessor* GetParagraphStyleAccessor()
{
    static const GENERATED_ArkUIParagraphStyleAccessor ParagraphStyleAccessorImpl {
        ParagraphStyleAccessor::DestroyPeerImpl,
        ParagraphStyleAccessor::CtorImpl,
        ParagraphStyleAccessor::GetFinalizerImpl,
        ParagraphStyleAccessor::GetTextAlignImpl,
        ParagraphStyleAccessor::GetTextIndentImpl,
        ParagraphStyleAccessor::GetMaxLinesImpl,
        ParagraphStyleAccessor::GetOverflowImpl,
        ParagraphStyleAccessor::GetWordBreakImpl,
    };
    return &ParagraphStyleAccessorImpl;
}

}
