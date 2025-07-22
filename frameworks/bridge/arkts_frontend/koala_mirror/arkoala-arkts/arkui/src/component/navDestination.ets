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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { NavPathInfo, NavPathInfoInternal, NavPathStack, NavPathStackInternal, NavigationMenuItem_serializer, NavigationTitleOptions_serializer, NavigationMenuOptions_serializer, ToolbarItem_serializer, NavigationToolbarOptions_serializer, NavigationMenuItem, NavigationOperation, NavigationTitleOptions, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions, BarStyle, MoreButtonOptions, ToolbarItemStatus } from "./navigation"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { window_SystemBarStyle_serializer, window } from "./../generated/ohos.window"
import { Scroller_serializer, Scroller } from "./scroll"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceStr, Length, ResourceColor } from "./units"
import { CustomBuilder } from "./builder"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics } from "./../generated/arkui.Graphics"
import { TextModifier } from "./../generated/arkui.TextModifier"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { curves } from "./../generated/ohos.curves"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, NavDestinationContextInternal.getFinalizer())
    }
    constructor() {
        this(NavDestinationContextInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavDestinationContext_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): NavDestinationContextInternal {
        return new NavDestinationContextInternal(ptr)
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
    private setNavDestinationId(navDestinationId: string | undefined): void {
        const navDestinationId_casted = navDestinationId as (string | undefined)
        this.setNavDestinationId_serialize(navDestinationId_casted)
        return
    }
    private getConfigInRouteMap_serialize(): RouteMapConfig | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getConfigInRouteMap(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RouteMapConfig | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = RouteMapConfig_serializer.read(retvalDeserializer)
        }
        const returnResult : RouteMapConfig | undefined = buffer
        return returnResult
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : string | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = (retvalDeserializer.readString() as string)
        }
        const returnResult : string | undefined = buffer
        return returnResult
    }
    private setNavDestinationId_serialize(navDestinationId: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let navDestinationId_type : int32 = RuntimeType.UNDEFINED
        navDestinationId_type = runtimeType(navDestinationId)
        thisSerializer.writeInt8((navDestinationId_type).toChar())
        if ((navDestinationId_type) != (RuntimeType.UNDEFINED)) {
            const navDestinationId_value  = navDestinationId!
            thisSerializer.writeString(navDestinationId_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationContext_setNavDestinationId(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkNavDestinationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavDestinationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._NavDestination_construct(peerId, flags)
        const _peer  = new ArkNavDestinationPeer(_peerPtr, peerId, "NavDestination", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavDestinationOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._NavDestinationInterface_setNavDestinationOptions(this.peer.ptr)
    }
    setHideTitleBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideTitleBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideBackButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideBackButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnShownAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnShown(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHiddenAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBackPressedAttribute(value: (() => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnBackPressed(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnResultAttribute(value: ((value0: Object | undefined) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setModeAttribute(value: NavDestinationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as NavDestinationMode)
            thisSerializer.writeInt32(TypeChecker.NavDestinationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackButtonIcon0Attribute(value: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_1)
                }
            }
            else if (TypeChecker.isimage_PixelMap(value_value, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBackButtonIcon0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenus0Attribute(value: Array<NavigationMenuItem> | CustomBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32((value_value_0.length).toInt())
                for (let value_value_0_counter_i = 0; value_value_0_counter_i < value_value_0.length; value_value_0_counter_i++) {
                    const value_value_0_element : NavigationMenuItem = value_value_0[value_value_0_counter_i]
                    NavigationMenuItem_serializer.write(thisSerializer, value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMenus0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnReadyAttribute(value: ((value0: NavDestinationContext) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillAppearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillDisappearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillDisappear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillShowAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillHideAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSystemBarStyleAttribute(value: window.SystemBarStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            window_SystemBarStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setSystemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRecoverableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setRecoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSystemTransitionAttribute(value: NavigationSystemTransitionType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as NavigationSystemTransitionType)
            thisSerializer.writeInt32(TypeChecker.NavigationSystemTransitionType_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setSystemTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindToScrollableAttribute(value: Array<Scroller> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : Scroller = value_value[value_value_counter_i]
                Scroller_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBindToScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindToNestedScrollableAttribute(value: Array<NestedScrollInfo> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : NestedScrollInfo = value_value[value_value_counter_i]
                NestedScrollInfo_serializer.write(thisSerializer, value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBindToNestedScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnActiveAttribute(value: ((value0: NavDestinationActiveReason) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnActive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInactiveAttribute(value: ((value0: NavDestinationActiveReason) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnInactive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomTransitionAttribute(value: NavDestinationTransitionDelegate | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setCustomTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNewParamAttribute(value: ((value0: Object | undefined) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnNewParam(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPreferredOrientationAttribute(value: Orientation | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeCustomObject("object", value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setPreferredOrientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNavigationIndicatorAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setEnableNavigationIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTitleAttribute(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (TypeChecker.isNavDestinationCommonTitle(value_value, false, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as NavDestinationCommonTitle
                NavDestinationCommonTitle_serializer.write(thisSerializer, value_value_2)
            }
            else if (TypeChecker.isNavDestinationCustomTitle(value_value, false, false)) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as NavDestinationCustomTitle
                NavDestinationCustomTitle_serializer.write(thisSerializer, value_value_3)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8((4).toChar())
                const value_value_4  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_4)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            NavigationTitleOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setTitle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8((hide_type).toChar())
        if ((hide_type) != (RuntimeType.UNDEFINED)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideTitleBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackButtonIcon1Attribute(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let icon_type : int32 = RuntimeType.UNDEFINED
        icon_type = runtimeType(icon)
        thisSerializer.writeInt8((icon_type).toChar())
        if ((icon_type) != (RuntimeType.UNDEFINED)) {
            const icon_value  = icon!
            let icon_value_type : int32 = RuntimeType.UNDEFINED
            icon_value_type = runtimeType(icon_value)
            if ((RuntimeType.STRING == icon_value_type) || (RuntimeType.OBJECT == icon_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const icon_value_0  = icon_value as ResourceStr
                let icon_value_0_type : int32 = RuntimeType.UNDEFINED
                icon_value_0_type = runtimeType(icon_value_0)
                if (RuntimeType.STRING == icon_value_0_type) {
                    thisSerializer.writeInt8((0).toChar())
                    const icon_value_0_0  = icon_value_0 as string
                    thisSerializer.writeString(icon_value_0_0)
                }
                else if (RuntimeType.OBJECT == icon_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const icon_value_0_1  = icon_value_0 as Resource
                    Resource_serializer.write(thisSerializer, icon_value_0_1)
                }
            }
            else if (TypeChecker.isimage_PixelMap(icon_value, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const icon_value_1  = icon_value as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, icon_value_1)
            }
            else if (TypeChecker.isSymbolGlyphModifier(icon_value)) {
                thisSerializer.writeInt8((2).toChar())
                const icon_value_2  = icon_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, icon_value_2)
            }
        }
        let accessibilityText_type : int32 = RuntimeType.UNDEFINED
        accessibilityText_type = runtimeType(accessibilityText)
        thisSerializer.writeInt8((accessibilityText_type).toChar())
        if ((accessibilityText_type) != (RuntimeType.UNDEFINED)) {
            const accessibilityText_value  = accessibilityText!
            let accessibilityText_value_type : int32 = RuntimeType.UNDEFINED
            accessibilityText_value_type = runtimeType(accessibilityText_value)
            if (RuntimeType.STRING == accessibilityText_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const accessibilityText_value_0  = accessibilityText_value as string
                thisSerializer.writeString(accessibilityText_value_0)
            }
            else if (RuntimeType.OBJECT == accessibilityText_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const accessibilityText_value_1  = accessibilityText_value as Resource
                Resource_serializer.write(thisSerializer, accessibilityText_value_1)
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBackButtonIcon1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenus1Attribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let items_type : int32 = RuntimeType.UNDEFINED
        items_type = runtimeType(items)
        thisSerializer.writeInt8((items_type).toChar())
        if ((items_type) != (RuntimeType.UNDEFINED)) {
            const items_value  = items!
            let items_value_type : int32 = RuntimeType.UNDEFINED
            items_value_type = runtimeType(items_value)
            if (RuntimeType.OBJECT == items_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const items_value_0  = items_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32((items_value_0.length).toInt())
                for (let items_value_0_counter_i = 0; items_value_0_counter_i < items_value_0.length; items_value_0_counter_i++) {
                    const items_value_0_element : NavigationMenuItem = items_value_0[items_value_0_counter_i]
                    NavigationMenuItem_serializer.write(thisSerializer, items_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == items_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const items_value_1  = items_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(items_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            NavigationMenuOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMenus1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setToolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let toolbarParam_type : int32 = RuntimeType.UNDEFINED
        toolbarParam_type = runtimeType(toolbarParam)
        thisSerializer.writeInt8((toolbarParam_type).toChar())
        if ((toolbarParam_type) != (RuntimeType.UNDEFINED)) {
            const toolbarParam_value  = toolbarParam!
            let toolbarParam_value_type : int32 = RuntimeType.UNDEFINED
            toolbarParam_value_type = runtimeType(toolbarParam_value)
            if (RuntimeType.OBJECT == toolbarParam_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const toolbarParam_value_0  = toolbarParam_value as Array<ToolbarItem>
                thisSerializer.writeInt32((toolbarParam_value_0.length).toInt())
                for (let toolbarParam_value_0_counter_i = 0; toolbarParam_value_0_counter_i < toolbarParam_value_0.length; toolbarParam_value_0_counter_i++) {
                    const toolbarParam_value_0_element : ToolbarItem = toolbarParam_value_0[toolbarParam_value_0_counter_i]
                    ToolbarItem_serializer.write(thisSerializer, toolbarParam_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == toolbarParam_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const toolbarParam_value_1  = toolbarParam_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(toolbarParam_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            NavigationToolbarOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setToolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideToolBarAttribute(hide: boolean | undefined, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8((hide_type).toChar())
        if ((hide_type) != (RuntimeType.UNDEFINED)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideToolBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIgnoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let types_type : int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8((types_type).toChar())
        if ((types_type) != (RuntimeType.UNDEFINED)) {
            const types_value  = types!
            thisSerializer.writeInt32((types_value.length).toInt())
            for (let types_value_counter_i = 0; types_value_counter_i < types_value.length; types_value_counter_i++) {
                const types_value_element : LayoutSafeAreaType = types_value[types_value_counter_i]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaType_ToNumeric(types_value_element))
            }
        }
        let edges_type : int32 = RuntimeType.UNDEFINED
        edges_type = runtimeType(edges)
        thisSerializer.writeInt8((edges_type).toChar())
        if ((edges_type) != (RuntimeType.UNDEFINED)) {
            const edges_value  = edges!
            thisSerializer.writeInt32((edges_value.length).toInt())
            for (let edges_value_counter_i = 0; edges_value_counter_i < edges_value.length; edges_value_counter_i++) {
                const edges_value_element : LayoutSafeAreaEdge = edges_value[edges_value_counter_i]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaEdge_ToNumeric(edges_value_element))
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setIgnoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableStatusBarAttribute(enabled: boolean | undefined, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let enabled_type : int32 = RuntimeType.UNDEFINED
        enabled_type = runtimeType(enabled)
        thisSerializer.writeInt8((enabled_type).toChar())
        if ((enabled_type) != (RuntimeType.UNDEFINED)) {
            const enabled_value  = enabled!
            thisSerializer.writeBoolean(enabled_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setEnableStatusBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type Orientation = object;
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
    curve?: curves.Curve;
    delay?: number;
    event: (() => void);
}
export interface NavDestinationAttribute extends CommonMethod {
    hideTitleBar(value: boolean | undefined): this {
        throw new Error("Unimplemented method hideTitleBar")
    }
    hideBackButton(value: boolean | undefined): this {
        throw new Error("Unimplemented method hideBackButton")
    }
    onShown(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onShown")
    }
    onHidden(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onHidden")
    }
    onBackPressed(value: (() => boolean) | undefined): this {
        throw new Error("Unimplemented method onBackPressed")
    }
    onResult(value: ((value0: Object | undefined) => void) | undefined): this {
        throw new Error("Unimplemented method onResult")
    }
    mode(value: NavDestinationMode | undefined): this {
        throw new Error("Unimplemented method mode")
    }
    backButtonIcon(value: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method backButtonIcon")
    }
    menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        throw new Error("Unimplemented method menus")
    }
    onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        throw new Error("Unimplemented method onReady")
    }
    onWillAppear(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onWillAppear")
    }
    onWillDisappear(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onWillDisappear")
    }
    onWillShow(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onWillShow")
    }
    onWillHide(value: (() => void) | undefined): this {
        throw new Error("Unimplemented method onWillHide")
    }
    systemBarStyle(value: window.SystemBarStyle | undefined): this {
        throw new Error("Unimplemented method systemBarStyle")
    }
    recoverable(value: boolean | undefined): this {
        throw new Error("Unimplemented method recoverable")
    }
    systemTransition(value: NavigationSystemTransitionType | undefined): this {
        throw new Error("Unimplemented method systemTransition")
    }
    bindToScrollable(value: Array<Scroller> | undefined): this {
        throw new Error("Unimplemented method bindToScrollable")
    }
    bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        throw new Error("Unimplemented method bindToNestedScrollable")
    }
    onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        throw new Error("Unimplemented method onActive")
    }
    onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        throw new Error("Unimplemented method onInactive")
    }
    customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        throw new Error("Unimplemented method customTransition")
    }
    onNewParam(value: ((value0: Object | undefined) => void) | undefined): this {
        throw new Error("Unimplemented method onNewParam")
    }
    preferredOrientation(value: Orientation | undefined): this {
        throw new Error("Unimplemented method preferredOrientation")
    }
    enableNavigationIndicator(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableNavigationIndicator")
    }
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
        throw new Error("Unimplemented method title")
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        throw new Error("Unimplemented method hideTitleBar")
    }
    backButtonIcon(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        throw new Error("Unimplemented method backButtonIcon")
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        throw new Error("Unimplemented method menus")
    }
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        throw new Error("Unimplemented method toolbarConfiguration")
    }
    hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        throw new Error("Unimplemented method hideToolBar")
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        throw new Error("Unimplemented method ignoreLayoutSafeArea")
    }
    enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        throw new Error("Unimplemented method enableStatusBar")
    }
    attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkNavDestinationStyle extends ArkCommonMethodStyle implements NavDestinationAttribute {
    hideTitleBar_value?: boolean | undefined
    hideBackButton_value?: boolean | undefined
    onShown_value?: (() => void) | undefined
    onHidden_value?: (() => void) | undefined
    onBackPressed_value?: (() => boolean) | undefined
    onResult_value?: ((value0: Object | undefined) => void) | undefined
    mode_value?: NavDestinationMode | undefined
    backButtonIcon_value?: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined
    menus_value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    onReady_value?: ((value0: NavDestinationContext) => void) | undefined
    onWillAppear_value?: (() => void) | undefined
    onWillDisappear_value?: (() => void) | undefined
    onWillShow_value?: (() => void) | undefined
    onWillHide_value?: (() => void) | undefined
    systemBarStyle_value?: window.SystemBarStyle | undefined
    recoverable_value?: boolean | undefined
    systemTransition_value?: NavigationSystemTransitionType | undefined
    bindToScrollable_value?: Array<Scroller> | undefined
    bindToNestedScrollable_value?: Array<NestedScrollInfo> | undefined
    onActive_value?: ((value0: NavDestinationActiveReason) => void) | undefined
    onInactive_value?: ((value0: NavDestinationActiveReason) => void) | undefined
    customTransition_value?: NavDestinationTransitionDelegate | undefined
    onNewParam_value?: ((value0: Object | undefined) => void) | undefined
    preferredOrientation_value?: Orientation | undefined
    enableNavigationIndicator_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined
    public hideTitleBar(value: boolean | undefined): this {
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
    public onResult(value: ((value0: Object | undefined) => void) | undefined): this {
        return this
    }
    public mode(value: NavDestinationMode | undefined): this {
        return this
    }
    public backButtonIcon(value: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined): this {
        return this
    }
    public menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        return this
    }
    public onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        return this
    }
    public onWillAppear(value: (() => void) | undefined): this {
        return this
    }
    public onWillDisappear(value: (() => void) | undefined): this {
        return this
    }
    public onWillShow(value: (() => void) | undefined): this {
        return this
    }
    public onWillHide(value: (() => void) | undefined): this {
        return this
    }
    public systemBarStyle(value: window.SystemBarStyle | undefined): this {
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
    public onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        return this
    }
    public onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        return this
    }
    public customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        return this
    }
    public onNewParam(value: ((value0: Object | undefined) => void) | undefined): this {
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
    public hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        return this
    }
    public backButtonIcon(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
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
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: NavDestinationAttribute): void {
        super.apply(target)
        if (this.hideTitleBar_value !== undefined)
            target.hideTitleBar(this.hideTitleBar_value!)
        if (this.hideBackButton_value !== undefined)
            target.hideBackButton(this.hideBackButton_value!)
        if (this.onShown_value !== undefined)
            target.onShown(this.onShown_value!)
        if (this.onHidden_value !== undefined)
            target.onHidden(this.onHidden_value!)
        if (this.onBackPressed_value !== undefined)
            target.onBackPressed(this.onBackPressed_value!)
        if (this.onResult_value !== undefined)
            target.onResult(this.onResult_value!)
        if (this.mode_value !== undefined)
            target.mode(this.mode_value!)
        if (this.backButtonIcon_value !== undefined)
            target.backButtonIcon(this.backButtonIcon_value!)
        if (this.menus_value !== undefined)
            target.menus(this.menus_value!)
        if (this.onReady_value !== undefined)
            target.onReady(this.onReady_value!)
        if (this.onWillAppear_value !== undefined)
            target.onWillAppear(this.onWillAppear_value!)
        if (this.onWillDisappear_value !== undefined)
            target.onWillDisappear(this.onWillDisappear_value!)
        if (this.onWillShow_value !== undefined)
            target.onWillShow(this.onWillShow_value!)
        if (this.onWillHide_value !== undefined)
            target.onWillHide(this.onWillHide_value!)
        if (this.systemBarStyle_value !== undefined)
            target.systemBarStyle(this.systemBarStyle_value!)
        if (this.recoverable_value !== undefined)
            target.recoverable(this.recoverable_value!)
        if (this.systemTransition_value !== undefined)
            target.systemTransition(this.systemTransition_value!)
        if (this.bindToScrollable_value !== undefined)
            target.bindToScrollable(this.bindToScrollable_value!)
        if (this.bindToNestedScrollable_value !== undefined)
            target.bindToNestedScrollable(this.bindToNestedScrollable_value!)
        if (this.onActive_value !== undefined)
            target.onActive(this.onActive_value!)
        if (this.onInactive_value !== undefined)
            target.onInactive(this.onInactive_value!)
        if (this.customTransition_value !== undefined)
            target.customTransition(this.customTransition_value!)
        if (this.onNewParam_value !== undefined)
            target.onNewParam(this.onNewParam_value!)
        if (this.preferredOrientation_value !== undefined)
            target.preferredOrientation(this.preferredOrientation_value!)
        if (this.enableNavigationIndicator_value !== undefined)
            target.enableNavigationIndicator(this.enableNavigationIndicator_value!)
    }
}
export type NavDestinationTransitionDelegate = (operation: NavigationOperation, isEnter: boolean) => Array<NavDestinationTransition> | undefined;

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
    public hideTitleBar(value: boolean | undefined): this {
        if (this.checkPriority("hideTitleBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHideTitleBar0Attribute(value_casted)
            return this
        }
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        if (this.checkPriority("hideBackButton")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHideBackButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public onShown(value: (() => void) | undefined): this {
        if (this.checkPriority("onShown")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnShownAttribute(value_casted)
            return this
        }
        return this
    }
    public onHidden(value: (() => void) | undefined): this {
        if (this.checkPriority("onHidden")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    public onBackPressed(value: (() => boolean) | undefined): this {
        if (this.checkPriority("onBackPressed")) {
            const value_casted = value as ((() => boolean) | undefined)
            this.getPeer()?.setOnBackPressedAttribute(value_casted)
            return this
        }
        return this
    }
    public onResult(value: ((value0: Object | undefined) => void) | undefined): this {
        if (this.checkPriority("onResult")) {
            const value_casted = value as (((value0: Object | undefined) => void) | undefined)
            this.getPeer()?.setOnResultAttribute(value_casted)
            return this
        }
        return this
    }
    public mode(value: NavDestinationMode | undefined): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavDestinationMode | undefined)
            this.getPeer()?.setModeAttribute(value_casted)
            return this
        }
        return this
    }
    public backButtonIcon(value: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("backButtonIcon")) {
            const value_casted = value as (ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined)
            this.getPeer()?.setBackButtonIcon0Attribute(value_casted)
            return this
        }
        return this
    }
    public menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        if (this.checkPriority("menus")) {
            const value_casted = value as (Array<NavigationMenuItem> | CustomBuilder | undefined)
            this.getPeer()?.setMenus0Attribute(value_casted)
            return this
        }
        return this
    }
    public onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (((value0: NavDestinationContext) => void) | undefined)
            this.getPeer()?.setOnReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillAppear(value: (() => void) | undefined): this {
        if (this.checkPriority("onWillAppear")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnWillAppearAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillDisappear(value: (() => void) | undefined): this {
        if (this.checkPriority("onWillDisappear")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnWillDisappearAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillShow(value: (() => void) | undefined): this {
        if (this.checkPriority("onWillShow")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillHide(value: (() => void) | undefined): this {
        if (this.checkPriority("onWillHide")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.setOnWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    public systemBarStyle(value: window.SystemBarStyle | undefined): this {
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (window.SystemBarStyle | undefined)
            this.getPeer()?.setSystemBarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public recoverable(value: boolean | undefined): this {
        if (this.checkPriority("recoverable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setRecoverableAttribute(value_casted)
            return this
        }
        return this
    }
    public systemTransition(value: NavigationSystemTransitionType | undefined): this {
        if (this.checkPriority("systemTransition")) {
            const value_casted = value as (NavigationSystemTransitionType | undefined)
            this.getPeer()?.setSystemTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public bindToScrollable(value: Array<Scroller> | undefined): this {
        if (this.checkPriority("bindToScrollable")) {
            const value_casted = value as (Array<Scroller> | undefined)
            this.getPeer()?.setBindToScrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        if (this.checkPriority("bindToNestedScrollable")) {
            const value_casted = value as (Array<NestedScrollInfo> | undefined)
            this.getPeer()?.setBindToNestedScrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        if (this.checkPriority("onActive")) {
            const value_casted = value as (((value0: NavDestinationActiveReason) => void) | undefined)
            this.getPeer()?.setOnActiveAttribute(value_casted)
            return this
        }
        return this
    }
    public onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        if (this.checkPriority("onInactive")) {
            const value_casted = value as (((value0: NavDestinationActiveReason) => void) | undefined)
            this.getPeer()?.setOnInactiveAttribute(value_casted)
            return this
        }
        return this
    }
    public customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        if (this.checkPriority("customTransition")) {
            const value_casted = value as (NavDestinationTransitionDelegate | undefined)
            this.getPeer()?.setCustomTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public onNewParam(value: ((value0: Object | undefined) => void) | undefined): this {
        if (this.checkPriority("onNewParam")) {
            const value_casted = value as (((value0: Object | undefined) => void) | undefined)
            this.getPeer()?.setOnNewParamAttribute(value_casted)
            return this
        }
        return this
    }
    public preferredOrientation(value: Orientation | undefined): this {
        if (this.checkPriority("preferredOrientation")) {
            const value_casted = value as (Orientation | undefined)
            this.getPeer()?.setPreferredOrientationAttribute(value_casted)
            return this
        }
        return this
    }
    public enableNavigationIndicator(value: boolean | undefined): this {
        if (this.checkPriority("enableNavigationIndicator")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableNavigationIndicatorAttribute(value_casted)
            return this
        }
        return this
    }
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.setTitleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (this.checkPriority("hideTitleBar")) {
            const hide_casted = hide as (boolean | undefined)
            const animated_casted = animated as (boolean | undefined)
            this.getPeer()?.setHideTitleBar1Attribute(hide_casted, animated_casted)
            return this
        }
        return this
    }
    public backButtonIcon(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (this.checkPriority("backButtonIcon")) {
            const icon_casted = icon as (ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined)
            const accessibilityText_casted = accessibilityText as (ResourceStr | undefined)
            this.getPeer()?.setBackButtonIcon1Attribute(icon_casted, accessibilityText_casted)
            return this
        }
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (this.checkPriority("menus")) {
            const items_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationMenuOptions | undefined)
            this.getPeer()?.setMenus1Attribute(items_casted, options_casted)
            return this
        }
        return this
    }
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const toolbarParam_casted = toolbarParam as (Array<ToolbarItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.setToolbarConfigurationAttribute(toolbarParam_casted, options_casted)
            return this
        }
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_casted = hide as (boolean | undefined)
            const animated_casted = animated as (boolean | undefined)
            this.getPeer()?.setHideToolBarAttribute(hide_casted, animated_casted)
            return this
        }
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType> | undefined)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge> | undefined)
            this.getPeer()?.setIgnoreLayoutSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    public enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("enableStatusBar")) {
            const enabled_casted = enabled as (boolean | undefined)
            const animated_casted = animated as (boolean | undefined)
            this.getPeer()?.setEnableStatusBarAttribute(enabled_casted, animated_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withNavDestinationStyle(receiver: NavDestinationAttribute, modifier: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkNavDestinationStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("NavDestination")
// export function NavDestination(
//     
//     @memo
//     content_?: () => void,
// ): NavDestinationAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function NavDestination(
    @memo
    style: ((attributes: NavDestinationAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkNavDestinationComponent>((): ArkNavDestinationComponent => {
        return new ArkNavDestinationComponent()
    })
    NodeAttach<ArkNavDestinationPeer>((): ArkNavDestinationPeer => ArkNavDestinationPeer.create(receiver), (_: ArkNavDestinationPeer): void => {
        receiver.setNavDestinationOptions()
        style?.(receiver)
        withNavDestinationStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkNavDestinationSet extends ArkCommonMethodSet implements NavDestinationAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _hideTitleBar_flag?: boolean
    _hideTitleBar0_value?: boolean | undefined
    _hideTitleBar1_value?: boolean | undefined
    _hideBackButton_flag?: boolean
    _hideBackButton0_value?: boolean | undefined
    _onShown_flag?: boolean
    _onShown0_value?: (() => void) | undefined
    _onHidden_flag?: boolean
    _onHidden0_value?: (() => void) | undefined
    _onBackPressed_flag?: boolean
    _onBackPressed0_value?: (() => boolean) | undefined
    _onResult_flag?: boolean
    _onResult0_value?: ((value0: Object | undefined) => void) | undefined
    _mode_flag?: boolean
    _mode0_value?: NavDestinationMode | undefined
    _backButtonIcon_flag?: boolean
    _backButtonIcon0_value?: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined
    _backButtonIcon1_value?: ResourceStr | undefined
    _menus_flag?: boolean
    _menus0_value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _menus1_value?: NavigationMenuOptions | undefined
    _onReady_flag?: boolean
    _onReady0_value?: ((value0: NavDestinationContext) => void) | undefined
    _onWillAppear_flag?: boolean
    _onWillAppear0_value?: (() => void) | undefined
    _onWillDisappear_flag?: boolean
    _onWillDisappear0_value?: (() => void) | undefined
    _onWillShow_flag?: boolean
    _onWillShow0_value?: (() => void) | undefined
    _onWillHide_flag?: boolean
    _onWillHide0_value?: (() => void) | undefined
    _systemBarStyle_flag?: boolean
    _systemBarStyle0_value?: window.SystemBarStyle | undefined
    _recoverable_flag?: boolean
    _recoverable0_value?: boolean | undefined
    _systemTransition_flag?: boolean
    _systemTransition0_value?: NavigationSystemTransitionType | undefined
    _bindToScrollable_flag?: boolean
    _bindToScrollable0_value?: Array<Scroller> | undefined
    _bindToNestedScrollable_flag?: boolean
    _bindToNestedScrollable0_value?: Array<NestedScrollInfo> | undefined
    _onActive_flag?: boolean
    _onActive0_value?: ((value0: NavDestinationActiveReason) => void) | undefined
    _onInactive_flag?: boolean
    _onInactive0_value?: ((value0: NavDestinationActiveReason) => void) | undefined
    _customTransition_flag?: boolean
    _customTransition0_value?: NavDestinationTransitionDelegate | undefined
    _onNewParam_flag?: boolean
    _onNewParam0_value?: ((value0: Object | undefined) => void) | undefined
    _preferredOrientation_flag?: boolean
    _preferredOrientation0_value?: Orientation | undefined
    _enableNavigationIndicator_flag?: boolean
    _enableNavigationIndicator0_value?: boolean | undefined
    _title_flag?: boolean
    _title0_value?: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined
    _title1_value?: NavigationTitleOptions | undefined
    _toolbarConfiguration_flag?: boolean
    _toolbarConfiguration0_value?: Array<ToolbarItem> | CustomBuilder | undefined
    _toolbarConfiguration1_value?: NavigationToolbarOptions | undefined
    _hideToolBar_flag?: boolean
    _hideToolBar0_value?: boolean | undefined
    _hideToolBar1_value?: boolean | undefined
    _ignoreLayoutSafeArea_flag?: boolean
    _ignoreLayoutSafeArea0_value?: Array<LayoutSafeAreaType> | undefined
    _ignoreLayoutSafeArea1_value?: Array<LayoutSafeAreaEdge> | undefined
    _enableStatusBar_flag?: boolean
    _enableStatusBar0_value?: boolean | undefined
    _enableStatusBar1_value?: boolean | undefined
    applyModifierPatch(component: NavDestinationAttribute): void {
        if (this._hideTitleBar_flag)
            component.hideTitleBar((this._hideTitleBar0_value as boolean | undefined), (this._hideTitleBar1_value as boolean | undefined))
        if (this._hideBackButton_flag)
            component.hideBackButton((this._hideBackButton0_value as boolean | undefined))
        if (this._onShown_flag)
            component.onShown((this._onShown0_value as (() => void) | undefined))
        if (this._onHidden_flag)
            component.onHidden((this._onHidden0_value as (() => void) | undefined))
        if (this._onBackPressed_flag)
            component.onBackPressed((this._onBackPressed0_value as (() => boolean) | undefined))
        if (this._onResult_flag)
            component.onResult((this._onResult0_value as ((value0: Object | undefined) => void) | undefined))
        if (this._mode_flag)
            component.mode((this._mode0_value as NavDestinationMode | undefined))
        if (this._backButtonIcon_flag)
            component.backButtonIcon((this._backButtonIcon0_value as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined), (this._backButtonIcon1_value as ResourceStr | undefined))
        if (this._menus_flag)
            component.menus((this._menus0_value as Array<NavigationMenuItem> | CustomBuilder | undefined), (this._menus1_value as NavigationMenuOptions | undefined))
        if (this._onReady_flag)
            component.onReady((this._onReady0_value as ((value0: NavDestinationContext) => void) | undefined))
        if (this._onWillAppear_flag)
            component.onWillAppear((this._onWillAppear0_value as (() => void) | undefined))
        if (this._onWillDisappear_flag)
            component.onWillDisappear((this._onWillDisappear0_value as (() => void) | undefined))
        if (this._onWillShow_flag)
            component.onWillShow((this._onWillShow0_value as (() => void) | undefined))
        if (this._onWillHide_flag)
            component.onWillHide((this._onWillHide0_value as (() => void) | undefined))
        if (this._systemBarStyle_flag)
            component.systemBarStyle((this._systemBarStyle0_value as window.SystemBarStyle | undefined))
        if (this._recoverable_flag)
            component.recoverable((this._recoverable0_value as boolean | undefined))
        if (this._systemTransition_flag)
            component.systemTransition((this._systemTransition0_value as NavigationSystemTransitionType | undefined))
        if (this._bindToScrollable_flag)
            component.bindToScrollable((this._bindToScrollable0_value as Array<Scroller> | undefined))
        if (this._bindToNestedScrollable_flag)
            component.bindToNestedScrollable((this._bindToNestedScrollable0_value as Array<NestedScrollInfo> | undefined))
        if (this._onActive_flag)
            component.onActive((this._onActive0_value as ((value0: NavDestinationActiveReason) => void) | undefined))
        if (this._onInactive_flag)
            component.onInactive((this._onInactive0_value as ((value0: NavDestinationActiveReason) => void) | undefined))
        if (this._customTransition_flag)
            component.customTransition((this._customTransition0_value as NavDestinationTransitionDelegate | undefined))
        if (this._onNewParam_flag)
            component.onNewParam((this._onNewParam0_value as ((value0: Object | undefined) => void) | undefined))
        if (this._preferredOrientation_flag)
            component.preferredOrientation((this._preferredOrientation0_value as Orientation | undefined))
        if (this._enableNavigationIndicator_flag)
            component.enableNavigationIndicator((this._enableNavigationIndicator0_value as boolean | undefined))
        if (this._title_flag)
            component.title((this._title0_value as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (this._title1_value as NavigationTitleOptions | undefined))
        if (this._toolbarConfiguration_flag)
            component.toolbarConfiguration((this._toolbarConfiguration0_value as Array<ToolbarItem> | CustomBuilder | undefined), (this._toolbarConfiguration1_value as NavigationToolbarOptions | undefined))
        if (this._hideToolBar_flag)
            component.hideToolBar((this._hideToolBar0_value as boolean | undefined), (this._hideToolBar1_value as boolean | undefined))
        if (this._ignoreLayoutSafeArea_flag)
            component.ignoreLayoutSafeArea((this._ignoreLayoutSafeArea0_value as Array<LayoutSafeAreaType> | undefined), (this._ignoreLayoutSafeArea1_value as Array<LayoutSafeAreaEdge> | undefined))
        if (this._enableStatusBar_flag)
            component.enableStatusBar((this._enableStatusBar0_value as boolean | undefined), (this._enableStatusBar1_value as boolean | undefined))
    }
    public hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        this._hideTitleBar_flag = true
        this._hideTitleBar0_value = hide
        this._hideTitleBar1_value = animated
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        this._hideBackButton_flag = true
        this._hideBackButton0_value = value
        return this
    }
    public onShown(value: (() => void) | undefined): this {
        this._onShown_flag = true
        this._onShown0_value = value
        return this
    }
    public onHidden(value: (() => void) | undefined): this {
        this._onHidden_flag = true
        this._onHidden0_value = value
        return this
    }
    public onBackPressed(value: (() => boolean) | undefined): this {
        this._onBackPressed_flag = true
        this._onBackPressed0_value = value
        return this
    }
    public onResult(value: ((value0: Object | undefined) => void) | undefined): this {
        this._onResult_flag = true
        this._onResult0_value = value
        return this
    }
    public mode(value: NavDestinationMode | undefined): this {
        this._mode_flag = true
        this._mode0_value = value
        return this
    }
    public backButtonIcon(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        this._backButtonIcon_flag = true
        this._backButtonIcon0_value = icon
        this._backButtonIcon1_value = accessibilityText
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        this._menus_flag = true
        this._menus0_value = items
        this._menus1_value = options
        return this
    }
    public onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        this._onReady_flag = true
        this._onReady0_value = value
        return this
    }
    public onWillAppear(value: (() => void) | undefined): this {
        this._onWillAppear_flag = true
        this._onWillAppear0_value = value
        return this
    }
    public onWillDisappear(value: (() => void) | undefined): this {
        this._onWillDisappear_flag = true
        this._onWillDisappear0_value = value
        return this
    }
    public onWillShow(value: (() => void) | undefined): this {
        this._onWillShow_flag = true
        this._onWillShow0_value = value
        return this
    }
    public onWillHide(value: (() => void) | undefined): this {
        this._onWillHide_flag = true
        this._onWillHide0_value = value
        return this
    }
    public systemBarStyle(value: window.SystemBarStyle | undefined): this {
        this._systemBarStyle_flag = true
        this._systemBarStyle0_value = value
        return this
    }
    public recoverable(value: boolean | undefined): this {
        this._recoverable_flag = true
        this._recoverable0_value = value
        return this
    }
    public systemTransition(value: NavigationSystemTransitionType | undefined): this {
        this._systemTransition_flag = true
        this._systemTransition0_value = value
        return this
    }
    public bindToScrollable(value: Array<Scroller> | undefined): this {
        this._bindToScrollable_flag = true
        this._bindToScrollable0_value = value
        return this
    }
    public bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        this._bindToNestedScrollable_flag = true
        this._bindToNestedScrollable0_value = value
        return this
    }
    public onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        this._onActive_flag = true
        this._onActive0_value = value
        return this
    }
    public onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        this._onInactive_flag = true
        this._onInactive0_value = value
        return this
    }
    public customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        this._customTransition_flag = true
        this._customTransition0_value = value
        return this
    }
    public onNewParam(value: ((value0: Object | undefined) => void) | undefined): this {
        this._onNewParam_flag = true
        this._onNewParam0_value = value
        return this
    }
    public preferredOrientation(value: Orientation | undefined): this {
        this._preferredOrientation_flag = true
        this._preferredOrientation0_value = value
        return this
    }
    public enableNavigationIndicator(value: boolean | undefined): this {
        this._enableNavigationIndicator_flag = true
        this._enableNavigationIndicator0_value = value
        return this
    }
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
        this._title_flag = true
        this._title0_value = value
        this._title1_value = options
        return this
    }
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        this._toolbarConfiguration_flag = true
        this._toolbarConfiguration0_value = toolbarParam
        this._toolbarConfiguration1_value = options
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        this._hideToolBar_flag = true
        this._hideToolBar0_value = hide
        this._hideToolBar1_value = animated
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        this._ignoreLayoutSafeArea_flag = true
        this._ignoreLayoutSafeArea0_value = types
        this._ignoreLayoutSafeArea1_value = edges
        return this
    }
    public enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        this._enableStatusBar_flag = true
        this._enableStatusBar0_value = enabled
        this._enableStatusBar1_value = animated
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class NavDestinationTransition_serializer {
    public static write(buffer: SerializerBase, value: NavDestinationTransition): void {
        let valueSerializer : SerializerBase = buffer
        const value_onTransitionEnd  = value.onTransitionEnd
        let value_onTransitionEnd_type : int32 = RuntimeType.UNDEFINED
        value_onTransitionEnd_type = runtimeType(value_onTransitionEnd)
        valueSerializer.writeInt8((value_onTransitionEnd_type).toChar())
        if ((value_onTransitionEnd_type) != (RuntimeType.UNDEFINED)) {
            const value_onTransitionEnd_value  = value_onTransitionEnd!
            valueSerializer.holdAndWriteCallback(value_onTransitionEnd_value)
        }
        const value_duration  = value.duration
        let value_duration_type : int32 = RuntimeType.UNDEFINED
        value_duration_type = runtimeType(value_duration)
        valueSerializer.writeInt8((value_duration_type).toChar())
        if ((value_duration_type) != (RuntimeType.UNDEFINED)) {
            const value_duration_value  = value_duration!
            valueSerializer.writeNumber(value_duration_value)
        }
        const value_curve  = value.curve
        let value_curve_type : int32 = RuntimeType.UNDEFINED
        value_curve_type = runtimeType(value_curve)
        valueSerializer.writeInt8((value_curve_type).toChar())
        if ((value_curve_type) != (RuntimeType.UNDEFINED)) {
            const value_curve_value  = (value_curve as curves.Curve)
            valueSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(value_curve_value))
        }
        const value_delay  = value.delay
        let value_delay_type : int32 = RuntimeType.UNDEFINED
        value_delay_type = runtimeType(value_delay)
        valueSerializer.writeInt8((value_delay_type).toChar())
        if ((value_delay_type) != (RuntimeType.UNDEFINED)) {
            const value_delay_value  = value_delay!
            valueSerializer.writeNumber(value_delay_value)
        }
        const value_event  = value.event
        valueSerializer.holdAndWriteCallback(value_event)
    }
    public static read(buffer: DeserializerBase): NavDestinationTransition {
        let valueDeserializer : DeserializerBase = buffer
        const onTransitionEnd_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onTransitionEnd_buf : (() => void) | undefined
        if ((onTransitionEnd_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onTransitionEnd_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onTransitionEnd_buf__call : KPointer = valueDeserializer.readPointer()
            const onTransitionEnd_buf__callSync : KPointer = valueDeserializer.readPointer()
            onTransitionEnd_buf = ():void => { 
    const onTransitionEnd_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onTransitionEnd_buf__argsSerializer.writeInt32(onTransitionEnd_buf__resource.resourceId);
    onTransitionEnd_buf__argsSerializer.writePointer(onTransitionEnd_buf__call);
    onTransitionEnd_buf__argsSerializer.writePointer(onTransitionEnd_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, onTransitionEnd_buf__argsSerializer.asBuffer(), onTransitionEnd_buf__argsSerializer.length());
    onTransitionEnd_buf__argsSerializer.release();
    return; }
        }
        const onTransitionEnd_result : (() => void) | undefined = onTransitionEnd_buf
        const duration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let duration_buf : number | undefined
        if ((duration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            duration_buf = (valueDeserializer.readNumber() as number)
        }
        const duration_result : number | undefined = duration_buf
        const curve_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let curve_buf : curves.Curve | undefined
        if ((curve_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            curve_buf = TypeChecker.curves_Curve_FromNumeric(valueDeserializer.readInt32())
        }
        const curve_result : curves.Curve | undefined = curve_buf
        const delay_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let delay_buf : number | undefined
        if ((delay_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            delay_buf = (valueDeserializer.readNumber() as number)
        }
        const delay_result : number | undefined = delay_buf
        const event_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const event_buf_call : KPointer = valueDeserializer.readPointer()
        const event_buf_callSync : KPointer = valueDeserializer.readPointer()
        const event_result : (() => void) = ():void => { 
    const event_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    event_buf_argsSerializer.writeInt32(event_buf_resource.resourceId);
    event_buf_argsSerializer.writePointer(event_buf_call);
    event_buf_argsSerializer.writePointer(event_buf_callSync);
    InteropNativeModule._CallCallback(-1867723152, event_buf_argsSerializer.asBuffer(), event_buf_argsSerializer.length());
    event_buf_argsSerializer.release();
    return; }
        let value : NavDestinationTransition = ({onTransitionEnd: onTransitionEnd_result, duration: duration_result, curve: curve_result, delay: delay_result, event: event_result} as NavDestinationTransition)
        return value
    }
}
export class NestedScrollInfo_serializer {
    public static write(buffer: SerializerBase, value: NestedScrollInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_parent  = value.parent
        Scroller_serializer.write(valueSerializer, value_parent)
        const value_child  = value.child
        Scroller_serializer.write(valueSerializer, value_child)
    }
    public static read(buffer: DeserializerBase): NestedScrollInfo {
        let valueDeserializer : DeserializerBase = buffer
        const parent_result : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        const child_result : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        let value : NestedScrollInfo = ({parent: parent_result, child: child_result} as NestedScrollInfo)
        return value
    }
}
export class RouteMapConfig_serializer {
    public static write(buffer: SerializerBase, value: RouteMapConfig): void {
        let valueSerializer : SerializerBase = buffer
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_pageSourceFile  = value.pageSourceFile
        valueSerializer.writeString(value_pageSourceFile)
        const value_data  = value.data
        valueSerializer.holdAndWriteObject(value_data)
    }
    public static read(buffer: DeserializerBase): RouteMapConfig {
        let valueDeserializer : DeserializerBase = buffer
        const name_result : string = (valueDeserializer.readString() as string)
        const pageSourceFile_result : string = (valueDeserializer.readString() as string)
        const data_result : Object = (valueDeserializer.readObject() as object)
        let value : RouteMapConfig = ({name: name_result, pageSourceFile: pageSourceFile_result, data: data_result} as RouteMapConfig)
        return value
    }
}
export class NavDestinationCommonTitle_serializer {
    public static write(buffer: SerializerBase, value: NavDestinationCommonTitle): void {
        let valueSerializer : SerializerBase = buffer
        const value_main  = value.main
        let value_main_type : int32 = RuntimeType.UNDEFINED
        value_main_type = runtimeType(value_main)
        if (RuntimeType.STRING == value_main_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_main_0  = value_main as string
            valueSerializer.writeString(value_main_0)
        }
        else if (RuntimeType.OBJECT == value_main_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_main_1  = value_main as Resource
            Resource_serializer.write(valueSerializer, value_main_1)
        }
        const value_sub  = value.sub
        let value_sub_type : int32 = RuntimeType.UNDEFINED
        value_sub_type = runtimeType(value_sub)
        if (RuntimeType.STRING == value_sub_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_sub_0  = value_sub as string
            valueSerializer.writeString(value_sub_0)
        }
        else if (RuntimeType.OBJECT == value_sub_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_sub_1  = value_sub as Resource
            Resource_serializer.write(valueSerializer, value_sub_1)
        }
    }
    public static read(buffer: DeserializerBase): NavDestinationCommonTitle {
        let valueDeserializer : DeserializerBase = buffer
        const main_buf_selector : int32 = valueDeserializer.readInt8()
        let main_buf : string | Resource | undefined
        if (main_buf_selector == (0).toChar()) {
            main_buf = (valueDeserializer.readString() as string)
        }
        else if (main_buf_selector == (1).toChar()) {
            main_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for main_buf has to be chosen through deserialisation.")
        }
        const main_result : string | Resource = (main_buf as string | Resource)
        const sub_buf_selector : int32 = valueDeserializer.readInt8()
        let sub_buf : string | Resource | undefined
        if (sub_buf_selector == (0).toChar()) {
            sub_buf = (valueDeserializer.readString() as string)
        }
        else if (sub_buf_selector == (1).toChar()) {
            sub_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for sub_buf has to be chosen through deserialisation.")
        }
        const sub_result : string | Resource = (sub_buf as string | Resource)
        let value : NavDestinationCommonTitle = ({main: main_result, sub: sub_result} as NavDestinationCommonTitle)
        return value
    }
}
export class NavDestinationContext_serializer {
    public static write(buffer: SerializerBase, value: NavDestinationContext): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): NavDestinationContext {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return NavDestinationContextInternal.fromPtr(ptr)
    }
}
export class NavDestinationCustomTitle_serializer {
    public static write(buffer: SerializerBase, value: NavDestinationCustomTitle): void {
        let valueSerializer : SerializerBase = buffer
        const value_builder  = value.builder
        valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_builder))
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        if (TypeChecker.isTitleHeight(value_height)) {
            valueSerializer.writeInt8((0).toChar())
            const value_height_0  = value_height as TitleHeight
            valueSerializer.writeInt32(TypeChecker.TitleHeight_ToNumeric(value_height_0))
        }
        else if ((RuntimeType.STRING == value_height_type) || (RuntimeType.NUMBER == value_height_type) || (RuntimeType.OBJECT == value_height_type)) {
            valueSerializer.writeInt8((1).toChar())
            const value_height_1  = value_height as Length
            let value_height_1_type : int32 = RuntimeType.UNDEFINED
            value_height_1_type = runtimeType(value_height_1)
            if (RuntimeType.STRING == value_height_1_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_height_1_0  = value_height_1 as string
                valueSerializer.writeString(value_height_1_0)
            }
            else if (RuntimeType.NUMBER == value_height_1_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_height_1_1  = value_height_1 as number
                valueSerializer.writeNumber(value_height_1_1)
            }
            else if (RuntimeType.OBJECT == value_height_1_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_height_1_2  = value_height_1 as Resource
                Resource_serializer.write(valueSerializer, value_height_1_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): NavDestinationCustomTitle {
        let valueDeserializer : DeserializerBase = buffer
        const builder_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const builder_buf_call : KPointer = valueDeserializer.readPointer()
        const builder_buf_callSync : KPointer = valueDeserializer.readPointer()
        const builder_result : CustomBuilder = ():void => { 
    const builder_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    builder_buf_argsSerializer.writeInt32(builder_buf_resource.resourceId);
    builder_buf_argsSerializer.writePointer(builder_buf_call);
    builder_buf_argsSerializer.writePointer(builder_buf_callSync);
    InteropNativeModule._CallCallback(737226752, builder_buf_argsSerializer.asBuffer(), builder_buf_argsSerializer.length());
    builder_buf_argsSerializer.release();
    return; }
        const height_buf_selector : int32 = valueDeserializer.readInt8()
        let height_buf : TitleHeight | Length | undefined
        if (height_buf_selector == (0).toChar()) {
            height_buf = TypeChecker.TitleHeight_FromNumeric(valueDeserializer.readInt32())
        }
        else if (height_buf_selector == (1).toChar()) {
            const height_buf_u_selector : int32 = valueDeserializer.readInt8()
            let height_buf_u : string | number | Resource | undefined
            if (height_buf_u_selector == (0).toChar()) {
                height_buf_u = (valueDeserializer.readString() as string)
            }
            else if (height_buf_u_selector == (1).toChar()) {
                height_buf_u = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf_u_selector == (2).toChar()) {
                height_buf_u = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for height_buf_u has to be chosen through deserialisation.")
            }
            height_buf = (height_buf_u as string | number | Resource)
        }
        else {
            throw new Error("One of the branches for height_buf has to be chosen through deserialisation.")
        }
        const height_result : TitleHeight | Length = (height_buf as TitleHeight | Length)
        let value : NavDestinationCustomTitle = ({builder: builder_result, height: height_result} as NavDestinationCustomTitle)
        return value
    }
}
