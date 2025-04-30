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
namespace NavExtenderAccessor {
void SetUpdateStackCallbackImpl(Ark_NavPathStack peer,
                                const NavExtender_OnUpdateStack* callback)
{
}
void SyncStackImpl(Ark_NavPathStack peer)
{
}
Ark_Boolean CheckNeedCreateImpl(Ark_NativePointer navigation,
                                Ark_Int32 index)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(navigation);
    //auto convValue = Converter::OptConvert<type>(navigation); // for enums
    //undefinedModelNG::SetCheckNeedCreate(frameNode, convValue);
    return {};
}
Ark_NativePointer NavigationCreateImpl(Ark_Int32 peer,
                                       Ark_Int32 flag)
{
    return {};
}
void SetNavigationOptionsImpl(Ark_NativePointer navigation,
                              Ark_NavPathStack stack)
{
}
void SetNavDestinationNodeImpl(Ark_NavPathStack peer,
                               Ark_Int32 index,
                               Ark_NativePointer node)
{
}
void SetNavigationModeImpl(Ark_NativePointer navigation,
                           Ark_NavigationMode mode)
{
}
void HideTitleBarImpl(Ark_NativePointer navigation,
                      Ark_Boolean isHide,
                      Ark_Boolean isAnimated)
{
}
void HideToolBarImpl(Ark_NativePointer navigation,
                     Ark_Boolean isHide,
                     Ark_Boolean isAnimated)
{
}
void HideNavBarImpl(Ark_NativePointer navigation,
                    Ark_Boolean hide)
{
}
void HideBackButtonImpl(Ark_NativePointer navigation,
                        Ark_Boolean hide)
{
}
void SetNavBarStateChangeImpl(Ark_NativePointer navigation,
                              const Callback_Boolean_Void* stateCallback)
{
}
void SetTitleModeChangeImpl(Ark_NativePointer navigation,
                            const Callback_NavigationTitleMode_Void* titleCallback)
{
}
void SetTitleModeImpl(Ark_NativePointer navigation,
                      Ark_NavigationTitleMode titleMode)
{
}
void TitleImpl(Ark_NativePointer navigation,
               const Ark_String* title,
               Ark_Boolean hasSubTitle)
{
}
void SubTitleImpl(Ark_NativePointer navigation,
                  const Ark_String* subTitle)
{
}
} // NavExtenderAccessor
const GENERATED_ArkUINavExtenderAccessor* GetNavExtenderAccessor()
{
    static const GENERATED_ArkUINavExtenderAccessor NavExtenderAccessorImpl {
        NavExtenderAccessor::SetUpdateStackCallbackImpl,
        NavExtenderAccessor::SyncStackImpl,
        NavExtenderAccessor::CheckNeedCreateImpl,
        NavExtenderAccessor::NavigationCreateImpl,
        NavExtenderAccessor::SetNavigationOptionsImpl,
        NavExtenderAccessor::SetNavDestinationNodeImpl,
        NavExtenderAccessor::SetNavigationModeImpl,
        NavExtenderAccessor::HideTitleBarImpl,
        NavExtenderAccessor::HideToolBarImpl,
        NavExtenderAccessor::HideNavBarImpl,
        NavExtenderAccessor::HideBackButtonImpl,
        NavExtenderAccessor::SetNavBarStateChangeImpl,
        NavExtenderAccessor::SetTitleModeChangeImpl,
        NavExtenderAccessor::SetTitleModeImpl,
        NavExtenderAccessor::TitleImpl,
        NavExtenderAccessor::SubTitleImpl,
    };
    return &NavExtenderAccessorImpl;
}

}
