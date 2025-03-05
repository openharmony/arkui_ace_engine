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
namespace TextStyle_styled_stringAccessor {
void DestroyPeerImpl(Ark_TextStyle_styled_string peer)
{
}
Ark_TextStyle_styled_string CtorImpl(const Opt_TextStyleInterface* value)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetFontFamilyImpl(Ark_TextStyle_styled_string peer)
{
    return {};
}
Ark_Number GetFontSizeImpl(Ark_TextStyle_styled_string peer)
{
    return {};
}
Ark_Number GetFontWeightImpl(Ark_TextStyle_styled_string peer)
{
    return {};
}
Ark_FontStyle GetFontStyleImpl(Ark_TextStyle_styled_string peer)
{
    return {};
}
} // TextStyle_styled_stringAccessor
const GENERATED_ArkUITextStyle_styled_stringAccessor* GetTextStyle_styled_stringAccessor()
{
    static const GENERATED_ArkUITextStyle_styled_stringAccessor TextStyle_styled_stringAccessorImpl {
        TextStyle_styled_stringAccessor::DestroyPeerImpl,
        TextStyle_styled_stringAccessor::CtorImpl,
        TextStyle_styled_stringAccessor::GetFinalizerImpl,
        TextStyle_styled_stringAccessor::GetFontFamilyImpl,
        TextStyle_styled_stringAccessor::GetFontSizeImpl,
        TextStyle_styled_stringAccessor::GetFontWeightImpl,
        TextStyle_styled_stringAccessor::GetFontStyleImpl,
    };
    return &TextStyle_styled_stringAccessorImpl;
}

}
