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
namespace SubTabBarStyleAccessor {
void DestroyPeerImpl(Ark_SubTabBarStyle peer)
{
}
Ark_SubTabBarStyle ConstructImpl(const Ark_Union_ResourceStr_ComponentContentBase* content)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_SubTabBarStyle OfImpl(const Ark_Union_ResourceStr_ComponentContentBase* content)
{
    return {};
}
Ark_SubTabBarStyle Indicator0Impl(Ark_SubTabBarStyle peer,
                                  const Ark_SubTabBarIndicatorStyle* style)
{
    return {};
}
Ark_SubTabBarStyle Indicator1Impl(Ark_SubTabBarStyle peer,
                                  const Ark_Union_SubTabBarIndicatorStyle_DrawableTabBarIndicator* value)
{
    return {};
}
Ark_SubTabBarStyle SelectedModeImpl(Ark_SubTabBarStyle peer,
                                    Ark_SelectedMode value)
{
    return {};
}
Ark_SubTabBarStyle BoardImpl(Ark_SubTabBarStyle peer,
                             const Ark_BoardStyle* value)
{
    return {};
}
Ark_SubTabBarStyle LabelStyleImpl(Ark_SubTabBarStyle peer,
                                  const Ark_TabBarLabelStyle* style)
{
    return {};
}
Ark_SubTabBarStyle Padding0Impl(Ark_SubTabBarStyle peer,
                                const Ark_Union_Padding_Dimension* value)
{
    return {};
}
Ark_SubTabBarStyle Padding1Impl(Ark_SubTabBarStyle peer,
                                const Ark_LocalizedPadding* padding)
{
    return {};
}
Ark_SubTabBarStyle IdImpl(Ark_SubTabBarStyle peer,
                          const Ark_String* value)
{
    return {};
}
} // SubTabBarStyleAccessor
const GENERATED_ArkUISubTabBarStyleAccessor* GetSubTabBarStyleAccessor()
{
    static const GENERATED_ArkUISubTabBarStyleAccessor SubTabBarStyleAccessorImpl {
        SubTabBarStyleAccessor::DestroyPeerImpl,
        SubTabBarStyleAccessor::ConstructImpl,
        SubTabBarStyleAccessor::GetFinalizerImpl,
        SubTabBarStyleAccessor::OfImpl,
        SubTabBarStyleAccessor::Indicator0Impl,
        SubTabBarStyleAccessor::Indicator1Impl,
        SubTabBarStyleAccessor::SelectedModeImpl,
        SubTabBarStyleAccessor::BoardImpl,
        SubTabBarStyleAccessor::LabelStyleImpl,
        SubTabBarStyleAccessor::Padding0Impl,
        SubTabBarStyleAccessor::Padding1Impl,
        SubTabBarStyleAccessor::IdImpl,
    };
    return &SubTabBarStyleAccessorImpl;
}

}
