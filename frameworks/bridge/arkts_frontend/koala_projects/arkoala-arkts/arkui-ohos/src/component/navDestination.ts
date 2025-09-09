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

import { NavPathInfo, NavPathInfoInternal, NavPathStack, NavPathStackInternal, NavigationMenuItem, NavigationOperation, NavigationTitleOptions, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions } from "./navigation"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, LayoutSafeAreaType, LayoutSafeAreaEdge, ArkCommonMethodComponent, ArkCommonMethodStyle, Callback } from "./common"
import { ResourceStr, Length } from "./units"
import { PixelMap } from "./arkui-pixelmap"
import { SymbolGlyphModifier } from "./arkui-external"
import { SystemBarStyle } from "./arkui-custom"
import { Scroller } from "./scroll"
import { Resource } from "global.resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { TitleHeight, Curve } from "./enums"

export interface NavDestinationContext {
    pathInfo: NavPathInfo
    pathStack: NavPathStack
    navDestinationId?: string | undefined
    getConfigInRouteMap(): RouteMapConfig | undefined
}
export class NavDestinationContextInternal implements MaterializedBase,NavDestinationContext {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get pathInfo(): NavPathInfo {
        return this.getPathInfo()
    }
    set pathInfo(pathInfo: NavPathInfo) {
        this.setPathInfo(pathInfo)
    }
    get pathStack(): NavPathStack {
        return this.getPathStack()
    }
    set pathStack(pathStack: NavPathStack) {
        this.setPathStack(pathStack)
    }
    get navDestinationId(): string | undefined {
        return this.getNavDestinationId()
    }
    set navDestinationId(navDestinationId: string | undefined) {
        const navDestinationId_NonNull  = (navDestinationId as string)
        this.setNavDestinationId(navDestinationId_NonNull)
    }
    static ctor_navdestinationcontext(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = NavDestinationContextInternal.ctor_navdestinationcontext()
        this.peer = new Finalizable(ctorPtr, NavDestinationContextInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavDestinationContext_getFinalizer()
    }
    public getConfigInRouteMap(): RouteMapConfig | undefined {
        return this.getConfigInRouteMap_serialize()
    }
    private getPathInfo(): NavPathInfo {
        return this.getPathInfo_serialize()
    }
    private setPathInfo(pathInfo: NavPathInfo): void {
        const pathInfo_casted = pathInfo as (NavPathInfo)
        this.setPathInfo_serialize(pathInfo_casted)
        return
    }
    private getPathStack(): NavPathStack {
        return this.getPathStack_serialize()
    }
    private setPathStack(pathStack: NavPathStack): void {
        const pathStack_casted = pathStack as (NavPathStack)
        this.setPathStack_serialize(pathStack_casted)
        return
    }
    private getNavDestinationId(): string | undefined {
        return this.getNavDestinationId_serialize()
    }
    private setNavDestinationId(navDestinationId: string): void {
        const navDestinationId_casted = navDestinationId as (string)
        this.setNavDestinationId_serialize(navDestinationId_casted)
        return
    }
    private getConfigInRouteMap_serialize(): RouteMapConfig | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getConfigInRouteMap(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getPathInfo_serialize(): NavPathInfo {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getPathInfo(this.peer!.ptr)
        const obj : NavPathInfo = NavPathInfoInternal.fromPtr(retval)
        return obj
    }
    private setPathInfo_serialize(pathInfo: NavPathInfo): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setPathInfo(this.peer!.ptr, toPeerPtr(pathInfo))
    }
    private getPathStack_serialize(): NavPathStack {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getPathStack(this.peer!.ptr)
        const obj : NavPathStack = NavPathStackInternal.fromPtr(retval)
        return obj
    }
    private setPathStack_serialize(pathStack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setPathStack(this.peer!.ptr, toPeerPtr(pathStack))
    }
    private getNavDestinationId_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getNavDestinationId(this.peer!.ptr)
        return retval
    }
    private setNavDestinationId_serialize(navDestinationId: string): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setNavDestinationId(this.peer!.ptr, navDestinationId)
    }
    public static fromPtr(ptr: KPointer): NavDestinationContextInternal {
        const obj : NavDestinationContextInternal = new NavDestinationContextInternal()
        obj.peer = new Finalizable(ptr, NavDestinationContextInternal.getFinalizer())
        return obj
    }
}
export class ArkNavDestinationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkNavDestinationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._NavDestination_construct(peerId, flags)
        const _peer  = new ArkNavDestinationPeer(_peerPtr, peerId, "NavDestination", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavDestinationOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._NavDestinationInterface_setNavDestinationOptions(this.peer.ptr)
    }
    hideTitleBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8(hide_type as int32)
        if ((RuntimeType.UNDEFINED) != (hide_type)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideBackButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideBackButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onShownAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onShown(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHiddenAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBackPressedAttribute(value: (() => boolean) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onBackPressed(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onResultAttribute(value: ((parameter: Object) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavDestinationMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavDestinationMode)
            thisSerializer.writeInt32(TypeChecker.NavDestinationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_mode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backButtonIcon0Attribute(value: ResourceStr | PixelMap | SymbolGlyphModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_1)
                }
            }
            else if (TypeChecker.isPixelMap(value_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as PixelMap
                thisSerializer.writePixelMap(value_value_1)
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as SymbolGlyphModifier
                thisSerializer.writeSymbolGlyphModifier(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_backButtonIcon0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backButtonIcon1Attribute(icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let icon_type : int32 = RuntimeType.UNDEFINED
        icon_type = runtimeType(icon)
        thisSerializer.writeInt8(icon_type as int32)
        if ((RuntimeType.UNDEFINED) != (icon_type)) {
            const icon_value  = icon!
            let icon_value_type : int32 = RuntimeType.UNDEFINED
            icon_value_type = runtimeType(icon_value)
            if ((RuntimeType.STRING == icon_value_type) || TypeChecker.isResource(icon_value_type, false, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const icon_value_0  = icon_value as ResourceStr
                let icon_value_0_type : int32 = RuntimeType.UNDEFINED
                icon_value_0_type = runtimeType(icon_value_0)
                if (RuntimeType.STRING == icon_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const icon_value_0_0  = icon_value_0 as string
                    thisSerializer.writeString(icon_value_0_0)
                }
                else if (TypeChecker.isResource(icon_value_type, false, false, false, false, false)) {
                    thisSerializer.writeInt8(1 as int32)
                    const icon_value_0_1  = icon_value_0 as Resource
                    thisSerializer.writeResource(icon_value_0_1)
                }
            }
            else if (TypeChecker.isPixelMap(icon_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const icon_value_1  = icon_value as PixelMap
                thisSerializer.writePixelMap(icon_value_1)
            }
            else if (TypeChecker.isSymbolGlyphModifier(icon_value)) {
                thisSerializer.writeInt8(2 as int32)
                const icon_value_2  = icon_value as SymbolGlyphModifier
                thisSerializer.writeSymbolGlyphModifier(icon_value_2)
            }
        }
        let accessibilityText_type : int32 = RuntimeType.UNDEFINED
        accessibilityText_type = runtimeType(accessibilityText)
        thisSerializer.writeInt8(accessibilityText_type as int32)
        if ((RuntimeType.UNDEFINED) != (accessibilityText_type)) {
            const accessibilityText_value  = accessibilityText!
            let accessibilityText_value_type : int32 = RuntimeType.UNDEFINED
            accessibilityText_value_type = runtimeType(accessibilityText_value)
            if (RuntimeType.STRING == accessibilityText_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const accessibilityText_value_0  = accessibilityText_value as string
                thisSerializer.writeString(accessibilityText_value_0)
            }
            else if (RuntimeType.OBJECT == accessibilityText_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const accessibilityText_value_1  = accessibilityText_value as Resource
                thisSerializer.writeResource(accessibilityText_value_1)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_backButtonIcon1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menus0Attribute(value: Array<NavigationMenuItem> | CustomBuilder | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : NavigationMenuItem = value_value_0[i]
                    thisSerializer.writeNavigationMenuItem(value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_menus0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menus1Attribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let items_type : int32 = RuntimeType.UNDEFINED
        items_type = runtimeType(items)
        thisSerializer.writeInt8(items_type as int32)
        if ((RuntimeType.UNDEFINED) != (items_type)) {
            const items_value  = items!
            let items_value_type : int32 = RuntimeType.UNDEFINED
            items_value_type = runtimeType(items_value)
            if (RuntimeType.OBJECT == items_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const items_value_0  = items_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32(items_value_0.length as int32)
                for (let i = 0; i < items_value_0.length; i++) {
                    const items_value_0_element : NavigationMenuItem = items_value_0[i]
                    thisSerializer.writeNavigationMenuItem(items_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == items_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const items_value_1  = items_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(items_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_menus1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: Callback<NavDestinationContext> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillAppearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDisappearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillDisappear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillShowAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillHideAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarStyleAttribute(value: SystemBarStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSystemBarStyle(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    recoverableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_recoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemTransitionAttribute(value: NavigationSystemTransitionType | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavigationSystemTransitionType)
            thisSerializer.writeInt32(TypeChecker.NavigationSystemTransitionType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindToScrollableAttribute(value: Array<Scroller> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : Scroller = value_value[i]
                thisSerializer.writeScroller(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_bindToScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindToNestedScrollableAttribute(value: Array<NestedScrollInfo> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : NestedScrollInfo = value_value[i]
                thisSerializer.writeNestedScrollInfo(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_bindToNestedScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onActiveAttribute(value: ((parameter: NavDestinationActiveReason) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onActive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onInactiveAttribute(value: ((parameter: NavDestinationActiveReason) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onInactive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customTransitionAttribute(value: NavDestinationTransitionDelegate | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_customTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNewParamAttribute(value: ((parameter: Object | null | undefined) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onNewParam(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    preferredOrientationAttribute(value: Orientation | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeOrientation(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_preferredOrientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableNavigationIndicatorAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_enableNavigationIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    titleAttribute(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (TypeChecker.isNavDestinationCommonTitle(value_value, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as NavDestinationCommonTitle
                thisSerializer.writeNavDestinationCommonTitle(value_value_2)
            }
            else if (TypeChecker.isNavDestinationCustomTitle(value_value, false, false)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as NavDestinationCustomTitle
                thisSerializer.writeNavDestinationCustomTitle(value_value_3)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(4 as int32)
                const value_value_4  = value_value as Resource
                thisSerializer.writeResource(value_value_4)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationTitleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_title(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    toolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let toolbarParam_type : int32 = RuntimeType.UNDEFINED
        toolbarParam_type = runtimeType(toolbarParam)
        thisSerializer.writeInt8(toolbarParam_type as int32)
        if ((RuntimeType.UNDEFINED) != (toolbarParam_type)) {
            const toolbarParam_value  = toolbarParam!
            let toolbarParam_value_type : int32 = RuntimeType.UNDEFINED
            toolbarParam_value_type = runtimeType(toolbarParam_value)
            if (RuntimeType.OBJECT == toolbarParam_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const toolbarParam_value_0  = toolbarParam_value as Array<ToolbarItem>
                thisSerializer.writeInt32(toolbarParam_value_0.length as int32)
                for (let i = 0; i < toolbarParam_value_0.length; i++) {
                    const toolbarParam_value_0_element : ToolbarItem = toolbarParam_value_0[i]
                    thisSerializer.writeToolbarItem(toolbarParam_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == toolbarParam_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const toolbarParam_value_1  = toolbarParam_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(toolbarParam_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationToolbarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_toolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBarAttribute(hide: boolean | undefined, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8(hide_type as int32)
        if ((RuntimeType.UNDEFINED) != (hide_type)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideToolBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let types_type : int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8(types_type as int32)
        if ((RuntimeType.UNDEFINED) != (types_type)) {
            const types_value  = types!
            thisSerializer.writeInt32(types_value.length as int32)
            for (let i = 0; i < types_value.length; i++) {
                const types_value_element : LayoutSafeAreaType = types_value[i]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaType_ToNumeric(types_value_element))
            }
        }
        let edges_type : int32 = RuntimeType.UNDEFINED
        edges_type = runtimeType(edges)
        thisSerializer.writeInt8(edges_type as int32)
        if ((RuntimeType.UNDEFINED) != (edges_type)) {
            const edges_value  = edges!
            thisSerializer.writeInt32(edges_value.length as int32)
            for (let i = 0; i < edges_value.length; i++) {
                const edges_value_element : LayoutSafeAreaEdge = edges_value[i]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaEdge_ToNumeric(edges_value_element))
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_ignoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableStatusBarAttribute(enabled: boolean | undefined, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let enabled_type : int32 = RuntimeType.UNDEFINED
        enabled_type = runtimeType(enabled)
        thisSerializer.writeInt8(enabled_type as int32)
        if ((RuntimeType.UNDEFINED) != (enabled_type)) {
            const enabled_value  = enabled!
            thisSerializer.writeBoolean(enabled_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_enableStatusBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface Orientation {
    _OrientationStub: string;
}
export interface NavDestinationCommonTitle {
    main: string | Resource;
    sub: string | Resource;
}
export interface NavDestinationCustomTitle {
    builder: CustomBuilder;
    height: TitleHeight | Length;
}
export enum NavigationSystemTransitionType {
    DEFAULT = 0,
    NONE = 1,
    TITLE = 2,
    CONTENT = 3,
    FADE = 4,
    EXPLODE = 5,
    SLIDE_RIGHT = 6,
    SLIDE_BOTTOM = 7
}
export enum NavDestinationMode {
    STANDARD = 0,
    DIALOG = 1
}
export enum NavDestinationActiveReason {
    TRANSITION = 0,
    CONTENT_COVER = 1,
    SHEET = 2,
    DIALOG = 3,
    OVERLAY = 4,
    APP_STATE = 5
}
export type NavDestinationInterface = () => NavDestinationAttribute;
export interface RouteMapConfig {
    name: string;
    pageSourceFile: string;
    data: Object;
}
export interface NestedScrollInfo {
    parent: Scroller;
    child: Scroller;
}
export interface NavDestinationTransition {
    onTransitionEnd?: (() => void);
    duration?: number;
    curve?: Curve;
    delay?: number;
    event: (() => void);
}
export type Callback_Boolean = () => boolean;
export type Callback_Object_Void = (parameter: Object) => void;
export type Callback_NavDestinationActiveReason_Void = (parameter: NavDestinationActiveReason) => void;
export interface NavDestinationAttribute extends CommonMethod {
    hideTitleBar(hide: boolean | undefined, animated?: boolean): this
    hideBackButton(value: boolean | undefined): this
    onShown(value: (() => void) | undefined): this
    onHidden(value: (() => void) | undefined): this
    onBackPressed(value: (() => boolean) | undefined): this
    onResult(value: ((parameter: Object) => void) | undefined): this
    mode(value: NavDestinationMode | undefined): this
    backButtonIcon(icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this
    onReady(value: Callback<NavDestinationContext> | undefined): this
    onWillAppear(value: Callback<void> | undefined): this
    onWillDisappear(value: Callback<void> | undefined): this
    onWillShow(value: Callback<void> | undefined): this
    onWillHide(value: Callback<void> | undefined): this
    systemBarStyle(value: SystemBarStyle | undefined): this
    recoverable(value: boolean | undefined): this
    systemTransition(value: NavigationSystemTransitionType | undefined): this
    bindToScrollable(value: Array<Scroller> | undefined): this
    bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this
    onActive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this
    onInactive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this
    customTransition(value: NavDestinationTransitionDelegate | undefined): this
    onNewParam(value: ((parameter: Object | null | undefined) => void) | undefined): this
    preferredOrientation(value: Orientation | undefined): this
    enableNavigationIndicator(value: boolean | undefined): this
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this
    hideToolBar(hide: boolean | undefined, animated?: boolean): this
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this
    enableStatusBar(enabled: boolean | undefined, animated?: boolean): this
}
export class ArkNavDestinationStyle extends ArkCommonMethodStyle implements NavDestinationAttribute {
    hideTitleBar_value?: boolean | undefined
    hideBackButton_value?: boolean | undefined
    onShown_value?: (() => void) | undefined
    onHidden_value?: (() => void) | undefined
    onBackPressed_value?: (() => boolean) | undefined
    onResult_value?: ((parameter: Object) => void) | undefined
    mode_value?: NavDestinationMode | undefined
    backButtonIcon_value?: ResourceStr | PixelMap | SymbolGlyphModifier | undefined
    menus_value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    onReady_value?: Callback<NavDestinationContext> | undefined
    onWillAppear_value?: Callback<void> | undefined
    onWillDisappear_value?: Callback<void> | undefined
    onWillShow_value?: Callback<void> | undefined
    onWillHide_value?: Callback<void> | undefined
    systemBarStyle_value?: SystemBarStyle | undefined
    recoverable_value?: boolean | undefined
    systemTransition_value?: NavigationSystemTransitionType | undefined
    bindToScrollable_value?: Array<Scroller> | undefined
    bindToNestedScrollable_value?: Array<NestedScrollInfo> | undefined
    onActive_value?: ((parameter: NavDestinationActiveReason) => void) | undefined
    onInactive_value?: ((parameter: NavDestinationActiveReason) => void) | undefined
    customTransition_value?: NavDestinationTransitionDelegate | undefined
    onNewParam_value?: ((parameter: Object | null | undefined) => void) | undefined
    preferredOrientation_value?: Orientation | undefined
    enableNavigationIndicator_value?: boolean | undefined
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this {
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        return this
    }
    public onShown(value: (() => void) | undefined): this {
        return this
    }
    public onHidden(value: (() => void) | undefined): this {
        return this
    }
    public onBackPressed(value: (() => boolean) | undefined): this {
        return this
    }
    public onResult(value: ((parameter: Object) => void) | undefined): this {
        return this
    }
    public mode(value: NavDestinationMode | undefined): this {
        return this
    }
    public backButtonIcon(icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        return this
    }
    public onReady(value: Callback<NavDestinationContext> | undefined): this {
        return this
    }
    public onWillAppear(value: Callback<void> | undefined): this {
        return this
    }
    public onWillDisappear(value: Callback<void> | undefined): this {
        return this
    }
    public onWillShow(value: Callback<void> | undefined): this {
        return this
    }
    public onWillHide(value: Callback<void> | undefined): this {
        return this
    }
    public systemBarStyle(value: SystemBarStyle | undefined): this {
        return this
    }
    public recoverable(value: boolean | undefined): this {
        return this
    }
    public systemTransition(value: NavigationSystemTransitionType | undefined): this {
        return this
    }
    public bindToScrollable(value: Array<Scroller> | undefined): this {
        return this
    }
    public bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        return this
    }
    public onActive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this {
        return this
    }
    public onInactive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this {
        return this
    }
    public customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        return this
    }
    public onNewParam(value: ((parameter: Object | null | undefined) => void) | undefined): this {
        return this
    }
    public preferredOrientation(value: Orientation | undefined): this {
        return this
    }
    public enableNavigationIndicator(value: boolean | undefined): this {
        return this
    }
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
        return this
    }
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        return this
    }
    public enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        return this
        }
}
export type NavDestinationTransitionDelegate = (operation: NavigationOperation, isEnter: boolean) => Array<NavDestinationTransition> | undefined;
export type Callback_NavDestinationContext_Void = (parameter: NavDestinationContext) => void;
export class ArkNavDestinationComponent extends ArkCommonMethodComponent implements NavDestinationAttribute {
    getPeer(): ArkNavDestinationPeer {
        return (this.peer as ArkNavDestinationPeer)
    }
    public setNavDestinationOptions(): this {
        if (this.checkPriority("setNavDestinationOptions")) {
            this.getPeer()?.setNavDestinationOptionsAttribute()
            return this
        }
        return this
    }
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("hideTitleBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && (RuntimeType.UNDEFINED == animated_type)) {
                const value_casted = hide as (boolean | undefined)
                this.getPeer()?.hideTitleBar0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
                const hide_casted = hide as (boolean | undefined)
                const animated_casted = animated as (boolean | undefined)
                this.getPeer()?.hideTitleBar1Attribute(hide_casted, animated_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        if (this.checkPriority("hideBackButton")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.hideBackButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public onShown(value: (() => void) | undefined): this {
        if (this.checkPriority("onShown")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onShownAttribute(value_casted)
            return this
        }
        return this
    }
    public onHidden(value: (() => void) | undefined): this {
        if (this.checkPriority("onHidden")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    public onBackPressed(value: (() => boolean) | undefined): this {
        if (this.checkPriority("onBackPressed")) {
            const value_casted = value as ((() => boolean) | undefined)
            this.getPeer()?.onBackPressedAttribute(value_casted)
            return this
        }
        return this
    }
    public onResult(value: ((parameter: Object) => void) | undefined): this {
        if (this.checkPriority("onResult")) {
            const value_casted = value as (((parameter: Object) => void) | undefined)
            this.getPeer()?.onResultAttribute(value_casted)
            return this
        }
        return this
    }
    public mode(value: NavDestinationMode | undefined): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavDestinationMode | undefined)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    public backButtonIcon(icon: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (this.checkPriority("backButtonIcon")) {
            const icon_type = runtimeType(icon)
            const accessibilityText_type = runtimeType(accessibilityText)
            if (((RuntimeType.STRING == icon_type) || (RuntimeType.OBJECT == icon_type) ||
                (RuntimeType.UNDEFINED == icon_type)) && (RuntimeType.UNDEFINED == accessibilityText_type)) {
                const value_casted = icon as (ResourceStr | PixelMap | SymbolGlyphModifier | undefined)
                this.getPeer()?.backButtonIcon0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.STRING == icon_type) || (RuntimeType.OBJECT == icon_type) ||
                (RuntimeType.UNDEFINED == icon_type)) && ((RuntimeType.STRING == accessibilityText_type) ||
                (RuntimeType.OBJECT == accessibilityText_type))) {
                const icon_casted = icon as (ResourceStr | PixelMap | SymbolGlyphModifier | undefined)
                const accessibilityText_casted = accessibilityText as (ResourceStr)
                this.getPeer()?.backButtonIcon1Attribute(icon_casted, accessibilityText_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (this.checkPriority("menus")) {
            const items_type = runtimeType(items)
            const options_type = runtimeType(options)
            if ((RuntimeType.OBJECT == items_type) || (RuntimeType.FUNCTION == items_type) || (RuntimeType.UNDEFINED == items_type)) {
                const value_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
                this.getPeer()?.menus0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == items_type) || (RuntimeType.FUNCTION == items_type) || (RuntimeType.UNDEFINED == items_type)) {
                const items_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
                const options_casted = options as (NavigationMenuOptions)
                this.getPeer()?.menus1Attribute(items_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public onReady(value: Callback<NavDestinationContext> | undefined): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (Callback<NavDestinationContext> | undefined)
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillAppear(value: Callback<void> | undefined): this {
        if (this.checkPriority("onWillAppear")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onWillAppearAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillDisappear(value: Callback<void> | undefined): this {
        if (this.checkPriority("onWillDisappear")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onWillDisappearAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillShow(value: Callback<void> | undefined): this {
        if (this.checkPriority("onWillShow")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillHide(value: Callback<void> | undefined): this {
        if (this.checkPriority("onWillHide")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    public systemBarStyle(value: SystemBarStyle | undefined): this {
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (SystemBarStyle | undefined)
            this.getPeer()?.systemBarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public recoverable(value: boolean | undefined): this {
        if (this.checkPriority("recoverable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.recoverableAttribute(value_casted)
            return this
        }
        return this
    }
    public systemTransition(value: NavigationSystemTransitionType | undefined): this {
        if (this.checkPriority("systemTransition")) {
            const value_casted = value as (NavigationSystemTransitionType | undefined)
            this.getPeer()?.systemTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public bindToScrollable(value: Array<Scroller> | undefined): this {
        if (this.checkPriority("bindToScrollable")) {
            const value_casted = value as (Array<Scroller> | undefined)
            this.getPeer()?.bindToScrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        if (this.checkPriority("bindToNestedScrollable")) {
            const value_casted = value as (Array<NestedScrollInfo> | undefined)
            this.getPeer()?.bindToNestedScrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public onActive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this {
        if (this.checkPriority("onActive")) {
            const value_casted = value as (((parameter: NavDestinationActiveReason) => void) | undefined)
            this.getPeer()?.onActiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onInactive(value: ((parameter: NavDestinationActiveReason) => void) | undefined): this {
        if (this.checkPriority("onInactive")) {
            const value_casted = value as (((parameter: NavDestinationActiveReason) => void) | undefined)
            this.getPeer()?.onInactiveAttribute(value_casted)
            return this
        }
        return this
    }
    public customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        if (this.checkPriority("customTransition")) {
            const value_casted = value as (NavDestinationTransitionDelegate | undefined)
            this.getPeer()?.customTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public onNewParam(value: ((parameter: Object | null | undefined) => void) | undefined): this {
        if (this.checkPriority("onNewParam")) {
            const value_casted = value as (((parameter: Object | null | undefined) => void) | undefined)
            this.getPeer()?.onNewParamAttribute(value_casted)
            return this
        }
        return this
    }
    public preferredOrientation(value: Orientation | undefined): this {
        if (this.checkPriority("preferredOrientation")) {
            const value_casted = value as (Orientation | undefined)
            this.getPeer()?.preferredOrientationAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNavigationIndicator(value: boolean | undefined): this {
        if (this.checkPriority("enableNavigationIndicator")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableNavigationIndicatorAttribute(value_casted)
            return this
        }
        return this
    }
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const toolbarParam_casted = toolbarParam as (Array<ToolbarItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(toolbarParam_casted, options_casted)
            return this
        }
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_casted = hide as (boolean | undefined)
            const animated_casted = animated as (boolean)
            this.getPeer()?.hideToolBarAttribute(hide_casted, animated_casted)
            return this
        }
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType>)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge>)
            this.getPeer()?.ignoreLayoutSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    public enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("enableStatusBar")) {
            const enabled_casted = enabled as (boolean | undefined)
            const animated_casted = animated as (boolean)
            this.getPeer()?.enableStatusBarAttribute(enabled_casted, animated_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function NavDestination(
    /** @memo */
    style: ((attributes: NavDestinationAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkNavDestinationComponent()
    })
    NodeAttach<ArkNavDestinationPeer>((): ArkNavDestinationPeer => ArkNavDestinationPeer.create(receiver), (_: ArkNavDestinationPeer) => {
        receiver.setNavDestinationOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
