/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
namespace BottomTabBarStyleAccessor {
void DestroyPeerImpl(Ark_BottomTabBarStyle peer)
{
}
Ark_BottomTabBarStyle ConstructImpl(const Ark_Union_ResourceStr_TabBarSymbol* icon,
                                    const Ark_ResourceStr* text)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_BottomTabBarStyle OfImpl(const Ark_Union_ResourceStr_TabBarSymbol* icon,
                             const Ark_ResourceStr* text)
{
    return {};
}
Ark_BottomTabBarStyle LabelStyleImpl(Ark_BottomTabBarStyle peer,
                                     const Ark_TabBarLabelStyle* style)
{
    return {};
}
Ark_BottomTabBarStyle PaddingImpl(Ark_BottomTabBarStyle peer,
                                  const Ark_Union_Padding_Dimension_LocalizedPadding* value)
{
    return {};
}
Ark_BottomTabBarStyle LayoutModeImpl(Ark_BottomTabBarStyle peer,
                                     Ark_LayoutMode value)
{
    return {};
}
Ark_BottomTabBarStyle VerticalAlignImpl(Ark_BottomTabBarStyle peer,
                                        Ark_VerticalAlign value)
{
    return {};
}
Ark_BottomTabBarStyle SymmetricExtensibleImpl(Ark_BottomTabBarStyle peer,
                                              Ark_Boolean value)
{
    return {};
}
Ark_BottomTabBarStyle IdImpl(Ark_BottomTabBarStyle peer,
                             const Ark_String* value)
{
    return {};
}
Ark_BottomTabBarStyle IconStyleImpl(Ark_BottomTabBarStyle peer,
                                    const Ark_TabBarIconStyle* style)
{
    return {};
}
} // BottomTabBarStyleAccessor
const GENERATED_ArkUIBottomTabBarStyleAccessor* GetBottomTabBarStyleAccessor()
{
    static const GENERATED_ArkUIBottomTabBarStyleAccessor BottomTabBarStyleAccessorImpl {
        BottomTabBarStyleAccessor::DestroyPeerImpl,
        BottomTabBarStyleAccessor::ConstructImpl,
        BottomTabBarStyleAccessor::GetFinalizerImpl,
        BottomTabBarStyleAccessor::OfImpl,
        BottomTabBarStyleAccessor::LabelStyleImpl,
        BottomTabBarStyleAccessor::PaddingImpl,
        BottomTabBarStyleAccessor::LayoutModeImpl,
        BottomTabBarStyleAccessor::VerticalAlignImpl,
        BottomTabBarStyleAccessor::SymmetricExtensibleImpl,
        BottomTabBarStyleAccessor::IdImpl,
        BottomTabBarStyleAccessor::IconStyleImpl,
    };
    return &BottomTabBarStyleAccessorImpl;
}

}
