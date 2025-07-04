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
namespace TextStyleAccessor {
void DestroyPeerImpl(Ark_TextStyle peer)
{
    auto peerImpl = reinterpret_cast<TextStylePeerImpl *>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_TextStyle ConstructImpl(const Opt_TextStyleInterface* value)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_ResourceColor GetFontColorImpl(Ark_TextStyle peer)
{
    return {};
}
Opt_String GetFontFamilyImpl(Ark_TextStyle peer)
{
    return {};
}
Opt_Number GetFontSizeImpl(Ark_TextStyle peer)
{
    return {};
}
Opt_Number GetFontWeightImpl(Ark_TextStyle peer)
{
    return {};
}
Opt_FontStyle GetFontStyleImpl(Ark_TextStyle peer)
{
    return {};
}
} // TextStyleAccessor
const GENERATED_ArkUITextStyleAccessor* GetTextStyleAccessor()
{
    static const GENERATED_ArkUITextStyleAccessor TextStyleAccessorImpl {
        TextStyleAccessor::DestroyPeerImpl,
        TextStyleAccessor::ConstructImpl,
        TextStyleAccessor::GetFinalizerImpl,
        TextStyleAccessor::GetFontColorImpl,
        TextStyleAccessor::GetFontFamilyImpl,
        TextStyleAccessor::GetFontSizeImpl,
        TextStyleAccessor::GetFontWeightImpl,
        TextStyleAccessor::GetFontStyleImpl,
    };
    return &TextStyleAccessorImpl;
}

struct TextStylePeer {
    virtual ~TextStylePeer() = default;
};
}
