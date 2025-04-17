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
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NavExtenderAccessor {
void SetUpdateStackCallbackImpl(Ark_NavPathStack peer,
                                const NavExtender_OnUpdateStack* callback)
{
    auto stack = peer;
    CHECK_NULL_VOID(stack);
    auto navigationStack = stack->GetNavPathStack();
    CHECK_NULL_VOID(navigationStack);
    auto updater = [callback = CallbackHelper(*callback)]() {
        Converter::ConvContext ctx;
        auto name = Converter::ArkValue<Ark_String>("", &ctx);
        callback.Invoke(name);
    };
    navigationStack->SetOnStateChangedCallback(std::move(updater));
}
void SyncStackImpl(Ark_NavPathStack peer)
{
    CHECK_NULL_VOID(peer);
    auto stack = peer->GetNavPathStack();
    CHECK_NULL_VOID(stack);
    auto navigationNode = AceType::DynamicCast<FrameNode>(stack->GetNavigationNode().Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    stack->ClearNodeList();
}
Ark_Boolean CheckNeedCreateImpl(Ark_NativePointer navigation,
                                Ark_Int32 index)
{
    auto invalidVal = Converter::ArkValue<Ark_Boolean>(false);
    auto navigationNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_RETURN(navigationNode, invalidVal);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(pattern, invalidVal);
    // need check
    // auto isCreated = pattern->CheckNeedCreate(index);
    return Converter::ArkValue<Ark_Boolean>(true);
}
Ark_NativePointer NavigationCreateImpl(Ark_Int32 peer,
                                       Ark_Int32 flag)
{
    auto frameNode = NavigationModelNG::CreateFrameNode(peer);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetNavigationOptionsImpl(Ark_NativePointer navigation,
                              Ark_NavPathStack stack)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(stack);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    auto navigationStack = stack->GetNavPathStack();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationStack->SetOnStateChangedCallback(nullptr);
}
void SetNavDestinationNodeImpl(Ark_NavPathStack peer,
                               Ark_Int32 index,
                               Ark_NativePointer node)
{
    CHECK_NULL_VOID(peer);
    auto stack = peer->GetNavPathStack();
    CHECK_NULL_VOID(stack);
    int32_t curIndex = Converter::Convert<int32_t>(index);
    stack->AddCustomNode(curIndex, Referenced::Claim(reinterpret_cast<UINode*>(node)));
}
void SetNavigationModeImpl(Ark_NativePointer navigation,
                           Ark_NavigationMode mode)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto navigationMode = static_cast<NavigationMode>(mode);
    NavigationModelNG::SetUsrNavigationMode(frameNode, navigationMode);
}
void HideTitleBarImpl(Ark_NativePointer navigation,
                      Ark_Boolean isHide,
                      Ark_Boolean isAnimated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto hide = Converter::Convert<bool>(isHide);
    auto animated = Converter::Convert<bool>(isAnimated);
    NavigationModelNG::SetHideTitleBar(frameNode, hide, animated);
}
void HideToolBarImpl(Ark_NativePointer navigation,
                     Ark_Boolean isHide,
                     Ark_Boolean isAnimated)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto hide = Converter::Convert<bool>(isHide);
    auto animated = Converter::Convert<bool>(isAnimated);
    NavigationModelNG::SetHideTitleBar(frameNode, hide, animated);
}
void HideNavBarImpl(Ark_NativePointer navigation,
                    Ark_Boolean hide)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto hideVal = Converter::Convert<bool>(hide);
    NavigationModelNG::SetHideNavBar(frameNode, hideVal);
}
void HideBackButtonImpl(Ark_NativePointer navigation,
                        Ark_Boolean hide)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto hideVal = Converter::Convert<bool>(hide);
    NavigationModelNG::SetHideBackButton(frameNode, hideVal);
}
void SetNavBarChangeImpl(Ark_NativePointer navigation,
                         const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto stateCallback = [changeCallback = CallbackHelper(*callback)](bool isVisible) {
    auto visible = Converter::ArkValue<Ark_Boolean>(isVisible);
        changeCallback.Invoke(visible);
    };
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnNavBarStateChange(stateCallback);
}
void SetTitleModeChangeImpl(Ark_NativePointer navigation,
                            const Callback_NavigationTitleMode_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto titleChange = [titleCallback = CallbackHelper(*callback)](NavigationTitleMode titleMode) {
        Ark_NavigationTitleMode mode = static_cast<Ark_NavigationTitleMode>(titleMode);
        titleCallback.Invoke(mode);
    };
    auto eventChange = [eventChange = CallbackHelper(*callback)](const BaseEventInfo* info) {
        auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(info);
        if (!eventInfo) {
            return;
        }
        Ark_NavigationTitleMode titleMode = Ark_NavigationTitleMode::ARK_NAVIGATION_TITLE_MODE_FREE;
        if (eventInfo->IsMiniBar()) {
            titleMode = Ark_NavigationTitleMode::ARK_NAVIGATION_TITLE_MODE_MINI;
        }
        eventChange.Invoke(titleMode);
    };
    auto eventHub = frameNode->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTitleModeChange(eventChange);
}
void SetTitleModeImpl(Ark_NativePointer navigation,
                      Ark_NavigationTitleMode titleMode)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto mode = static_cast<NavigationTitleMode>(titleMode);
    NavigationModelNG::SetTitleMode(frameNode, mode);
}
void TitleImpl(Ark_NativePointer navigation,
               const Ark_String* title,
               Ark_Boolean hasSubTitle)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto titleVal = Converter::Convert<std::string>(*title);
    auto hasSubTitleVal = Converter::Convert<bool>(hasSubTitle);
    NavigationTitleInfo info;
    info.hasMainTitle = true;
    info.hasSubTitle = hasSubTitle;
    info.title = titleVal;
    info.subtitle = "";
    NavigationModelNG::ParseCommonTitle(frameNode, info);
}
void SubTitleImpl(Ark_NativePointer navigation,
                  const Ark_String* subTitle)
{
    auto frameNode = reinterpret_cast<FrameNode*>(navigation);
    CHECK_NULL_VOID(frameNode);
    auto subTitleVal = Converter::Convert<std::string>(*subTitle);
    NavigationModelNG::SetSubTitle(frameNode, subTitleVal);
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
        NavExtenderAccessor::SetNavBarChangeImpl,
        NavExtenderAccessor::SetTitleModeChangeImpl,
        NavExtenderAccessor::SetTitleModeImpl,
        NavExtenderAccessor::TitleImpl,
        NavExtenderAccessor::SubTitleImpl,
    };
    return &NavExtenderAccessorImpl;
}

}
