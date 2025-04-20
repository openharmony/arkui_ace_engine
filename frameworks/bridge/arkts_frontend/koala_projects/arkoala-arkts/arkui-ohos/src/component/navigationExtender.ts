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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { NavPathStack, NavPathStackInternal, NavigationMode, Callback_Boolean_Void, Callback_NavigationTitleMode_Void, NavigationTitleMode } from "./navigation"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class NavExtender {
    public static setUpdateStackCallback(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const peer_casted = peer as (NavPathStack)
        const callback_casted = callback as (NavExtender_OnUpdateStack)
        NavExtender.setUpdateStackCallback_serialize(peer_casted, callback_casted)
        return
    }
    public static syncStack(peer: NavPathStack): void {
        const peer_casted = peer as (NavPathStack)
        NavExtender.syncStack_serialize(peer_casted)
        return
    }
    public static checkNeedCreate(navigation: KPointer, index: int32): boolean {
        const navigation_casted = navigation as (KPointer)
        const index_casted = index as (int32)
        return NavExtender.checkNeedCreate_serialize(navigation_casted, index_casted)
    }
    public static navigationCreate(peer: int32, flag: int32): KPointer {
        const peer_casted = peer as (int32)
        const flag_casted = flag as (int32)
        return NavExtender.navigationCreate_serialize(peer_casted, flag_casted)
    }
    public static setNavigationOptions(navigation: KPointer, stack: NavPathStack): void {
        const navigation_casted = navigation as (KPointer)
        const stack_casted = stack as (NavPathStack)
        NavExtender.setNavigationOptions_serialize(navigation_casted, stack_casted)
        return
    }
    public static setNavDestinationNode(peer: NavPathStack, index: int32, node: KPointer): void {
        const peer_casted = peer as (NavPathStack)
        const index_casted = index as (int32)
        const node_casted = node as (KPointer)
        NavExtender.setNavDestinationNode_serialize(peer_casted, index_casted, node_casted)
        return
    }
    public static setNavigationMode(navigation: KPointer, mode: NavigationMode): void {
        const navigation_casted = navigation as (KPointer)
        const mode_casted = mode as (NavigationMode)
        NavExtender.setNavigationMode_serialize(navigation_casted, mode_casted)
        return
    }
    public static hideTitleBar(navigation: KPointer, isHide: boolean, isAnimated: boolean): void {
        const navigation_casted = navigation as (KPointer)
        const isHide_casted = isHide as (boolean)
        const isAnimated_casted = isAnimated as (boolean)
        NavExtender.hideTitleBar_serialize(navigation_casted, isHide_casted, isAnimated_casted)
        return
    }
    public static hideToolBar(navigation: KPointer, isHide: boolean, isAnimated: boolean): void {
        const navigation_casted = navigation as (KPointer)
        const isHide_casted = isHide as (boolean)
        const isAnimated_casted = isAnimated as (boolean)
        NavExtender.hideToolBar_serialize(navigation_casted, isHide_casted, isAnimated_casted)
        return
    }
    public static hideNavBar(navigation: KPointer, hide: boolean): void {
        const navigation_casted = navigation as (KPointer)
        const hide_casted = hide as (boolean)
        NavExtender.hideNavBar_serialize(navigation_casted, hide_casted)
        return
    }
    public static hideBackButton(navigation: KPointer, hide: boolean): void {
        const navigation_casted = navigation as (KPointer)
        const hide_casted = hide as (boolean)
        NavExtender.hideBackButton_serialize(navigation_casted, hide_casted)
        return
    }
    public static setNavBarStateChange(navigation: KPointer, stateCallback: ((isVisible: boolean) => void)): void {
        const navigation_casted = navigation as (KPointer)
        const stateCallback_casted = stateCallback as (((isVisible: boolean) => void))
        NavExtender.setNavBarStateChange_serialize(navigation_casted, stateCallback_casted)
        return
    }
    public static setTitleModeChange(navigation: KPointer, titleCallback: ((titleMode: NavigationTitleMode) => void)): void {
        const navigation_casted = navigation as (KPointer)
        const titleCallback_casted = titleCallback as (((titleMode: NavigationTitleMode) => void))
        NavExtender.setTitleModeChange_serialize(navigation_casted, titleCallback_casted)
        return
    }
    public static setTitleMode(navigation: KPointer, titleMode: NavigationTitleMode): void {
        const navigation_casted = navigation as (KPointer)
        const titleMode_casted = titleMode as (NavigationTitleMode)
        NavExtender.setTitleMode_serialize(navigation_casted, titleMode_casted)
        return
    }
    public static title(navigation: KPointer, title: string, hasSubTitle: boolean): void {
        const navigation_casted = navigation as (KPointer)
        const title_casted = title as (string)
        const hasSubTitle_casted = hasSubTitle as (boolean)
        NavExtender.title_serialize(navigation_casted, title_casted, hasSubTitle_casted)
        return
    }
    public static subTitle(navigation: KPointer, subTitle: string): void {
        const navigation_casted = navigation as (KPointer)
        const subTitle_casted = subTitle as (string)
        NavExtender.subTitle_serialize(navigation_casted, subTitle_casted)
        return
    }
    private static setUpdateStackCallback_serialize(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setUpdateStackCallback(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static syncStack_serialize(peer: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_syncStack(toPeerPtr(peer))
    }
    private static checkNeedCreate_serialize(navigation: KPointer, index: int32): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_checkNeedCreate(navigation, index)
        return retval
    }
    private static navigationCreate_serialize(peer: int32, flag: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_navigationCreate(peer, flag)
        return retval
    }
    private static setNavigationOptions_serialize(navigation: KPointer, stack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavigationOptions(navigation, toPeerPtr(stack))
    }
    private static setNavDestinationNode_serialize(peer: NavPathStack, index: int32, node: KPointer): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavDestinationNode(toPeerPtr(peer), index, node)
    }
    private static setNavigationMode_serialize(navigation: KPointer, mode: NavigationMode): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavigationMode(navigation, TypeChecker.NavigationMode_ToNumeric(mode))
    }
    private static hideTitleBar_serialize(navigation: KPointer, isHide: boolean, isAnimated: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_hideTitleBar(navigation, isHide ? 1 : 0, isAnimated ? 1 : 0)
    }
    private static hideToolBar_serialize(navigation: KPointer, isHide: boolean, isAnimated: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_hideToolBar(navigation, isHide ? 1 : 0, isAnimated ? 1 : 0)
    }
    private static hideNavBar_serialize(navigation: KPointer, hide: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_hideNavBar(navigation, hide ? 1 : 0)
    }
    private static hideBackButton_serialize(navigation: KPointer, hide: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_hideBackButton(navigation, hide ? 1 : 0)
    }
    private static setNavBarStateChange_serialize(navigation: KPointer, stateCallback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stateCallback)
        ArkUIGeneratedNativeModule._NavExtender_setNavBarStateChange(navigation, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setTitleModeChange_serialize(navigation: KPointer, titleCallback: ((titleMode: NavigationTitleMode) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(titleCallback)
        ArkUIGeneratedNativeModule._NavExtender_setTitleModeChange(navigation, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setTitleMode_serialize(navigation: KPointer, titleMode: NavigationTitleMode): void {
        ArkUIGeneratedNativeModule._NavExtender_setTitleMode(navigation, TypeChecker.NavigationTitleMode_ToNumeric(titleMode))
    }
    private static title_serialize(navigation: KPointer, title: string, hasSubTitle: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_title(navigation, title, hasSubTitle ? 1 : 0)
    }
    private static subTitle_serialize(navigation: KPointer, subTitle: string): void {
        ArkUIGeneratedNativeModule._NavExtender_subTitle(navigation, subTitle)
    }
}
export type NavExtender_OnUpdateStack = (name: string) => void;
