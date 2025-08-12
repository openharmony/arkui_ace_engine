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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { NavPathInfo, NavPathInfoInternal, NavPathStack, NavPathStackInternal, NavigationMenuItem_serializer, NavigationTitleOptions_serializer, NavigationMenuOptions_serializer, ToolbarItem_serializer, NavigationToolbarOptions_serializer, NavigationMenuItem, NavigationOperation, NavigationTitleOptions, NavigationMenuOptions, ToolbarItem, NavigationToolbarOptions, BarStyle, MoreButtonOptions, ToolbarItemStatus } from "./navigation"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { window_SystemBarStyle_serializer, window } from "./../generated/ohos.window"
import { Scroller_serializer, Scroller } from "./scroll"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { ResourceStr, Length, ResourceColor } from "./units"
import { CustomBuilder } from "./builder"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics } from "./../generated/arkui.Graphics"
import { TextModifier } from "./../generated/arkui.TextModifier"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { curves } from "./../generated/ohos.curves"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
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
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
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
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (retvalDeserializer.readString() as string)
        }
        const returnResult : string | undefined = buffer
        return returnResult
    }
    private setNavDestinationId_serialize(navDestinationId: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (navDestinationId !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const navDestinationIdTmpValue  = navDestinationId!
            thisSerializer.writeString(navDestinationIdTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        const _peer  = new ArkNavDestinationPeer(_peerPtr, peerId, 'NavDestination', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavDestinationOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._NavDestinationInterface_setNavDestinationOptions(this.peer.ptr)
    }
    setHideTitleBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideTitleBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideBackButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideBackButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnShownAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnShown(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHiddenAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnBackPressedAttribute(value: (() => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnBackPressed(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnResultAttribute(value: ((value0: Object | undefined) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnResult(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setModeAttribute(value: NavDestinationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as NavDestinationMode)
            thisSerializer.writeInt32(TypeChecker.NavDestinationMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackButtonIcon0Attribute(value: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ResourceStr) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceStr
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx1)
                }
            } else if (valueTmpValue instanceof image.PixelMap) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof SymbolGlyphModifier) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBackButtonIcon0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenus0Attribute(value: Array<NavigationMenuItem> | CustomBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (TypeChecker.isArray_NavigationMenuItem(valueTmpValue)) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Array<NavigationMenuItem>
                thisSerializer.writeInt32((valueTmpValueForIdx0.length).toInt())
                for (let valueTmpValueForIdx0CounterI = 0; valueTmpValueForIdx0CounterI < valueTmpValueForIdx0.length; valueTmpValueForIdx0CounterI++) {
                    const valueTmpValueForIdx0TmpElement : NavigationMenuItem = valueTmpValueForIdx0[valueTmpValueForIdx0CounterI]
                    NavigationMenuItem_serializer.write(thisSerializer, valueTmpValueForIdx0TmpElement)
                }
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx1))
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMenus0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnReadyAttribute(value: ((value0: NavDestinationContext) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillAppearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillDisappearAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillDisappear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillShowAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillHideAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSystemBarStyleAttribute(value: window.SystemBarStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            window_SystemBarStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setSystemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRecoverableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setRecoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSystemTransitionAttribute(value: NavigationSystemTransitionType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as NavigationSystemTransitionType)
            thisSerializer.writeInt32(TypeChecker.NavigationSystemTransitionType_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setSystemTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindToScrollableAttribute(value: Array<Scroller> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : Scroller = valueTmpValue[valueTmpValueCounterI]
                Scroller_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBindToScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindToNestedScrollableAttribute(value: Array<NestedScrollInfo> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : NestedScrollInfo = valueTmpValue[valueTmpValueCounterI]
                NestedScrollInfo_serializer.write(thisSerializer, valueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBindToNestedScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnActiveAttribute(value: ((value0: NavDestinationActiveReason) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnActive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnInactiveAttribute(value: ((value0: NavDestinationActiveReason) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnInactive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomTransitionAttribute(value: NavDestinationTransitionDelegate | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setCustomTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNewParamAttribute(value: ((value0: Object | undefined) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setOnNewParam(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPreferredOrientationAttribute(value: Orientation | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeCustomObject('object', valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setPreferredOrientation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableNavigationIndicatorAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setEnableNavigationIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTitleAttribute(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx1))
            } else if (valueTmpValue instanceof NavDestinationCommonTitle) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as NavDestinationCommonTitle
                NavDestinationCommonTitle_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof NavDestinationCustomTitle) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as NavDestinationCustomTitle
                NavDestinationCustomTitle_serializer.write(thisSerializer, valueTmpValueForIdx3)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((4).toChar())
                const valueTmpValueForIdx4  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx4)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            NavigationTitleOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setTitle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (hide !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const hideTmpValue  = hide!
            thisSerializer.writeBoolean(hideTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideTitleBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackButtonIcon1Attribute(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (icon !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const iconTmpValue  = icon!
            if (iconTmpValue instanceof ResourceStr) {
                thisSerializer.writeInt8((0).toChar())
                const iconTmpValueForIdx0  = iconTmpValue as ResourceStr
                if (iconTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toChar())
                    const iconTmpValueForIdx0ForIdx0  = iconTmpValueForIdx0 as string
                    thisSerializer.writeString(iconTmpValueForIdx0ForIdx0)
                } else if (iconTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((1).toChar())
                    const iconTmpValueForIdx0ForIdx1  = iconTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, iconTmpValueForIdx0ForIdx1)
                }
            } else if (iconTmpValue instanceof image.PixelMap) {
                thisSerializer.writeInt8((1).toChar())
                const iconTmpValueForIdx1  = iconTmpValue as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, iconTmpValueForIdx1)
            } else if (iconTmpValue instanceof SymbolGlyphModifier) {
                thisSerializer.writeInt8((2).toChar())
                const iconTmpValueForIdx2  = iconTmpValue as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, iconTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (accessibilityText !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const accessibilityTextTmpValue  = accessibilityText!
            if (accessibilityTextTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const accessibilityTextTmpValueForIdx0  = accessibilityTextTmpValue as string
                thisSerializer.writeString(accessibilityTextTmpValueForIdx0)
            } else if (accessibilityTextTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const accessibilityTextTmpValueForIdx1  = accessibilityTextTmpValue as Resource
                Resource_serializer.write(thisSerializer, accessibilityTextTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBackButtonIcon1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenus1Attribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (items !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const itemsTmpValue  = items!
            if (TypeChecker.isArray_NavigationMenuItem(itemsTmpValue)) {
                thisSerializer.writeInt8((0).toChar())
                const itemsTmpValueForIdx0  = itemsTmpValue as Array<NavigationMenuItem>
                thisSerializer.writeInt32((itemsTmpValueForIdx0.length).toInt())
                for (let itemsTmpValueForIdx0CounterI = 0; itemsTmpValueForIdx0CounterI < itemsTmpValueForIdx0.length; itemsTmpValueForIdx0CounterI++) {
                    const itemsTmpValueForIdx0TmpElement : NavigationMenuItem = itemsTmpValueForIdx0[itemsTmpValueForIdx0CounterI]
                    NavigationMenuItem_serializer.write(thisSerializer, itemsTmpValueForIdx0TmpElement)
                }
            } else if (itemsTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toChar())
                const itemsTmpValueForIdx1  = itemsTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(itemsTmpValueForIdx1))
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            NavigationMenuOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMenus1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setToolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (toolbarParam !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const toolbarParamTmpValue  = toolbarParam!
            if (TypeChecker.isArray_ToolbarItem(toolbarParamTmpValue)) {
                thisSerializer.writeInt8((0).toChar())
                const toolbarParamTmpValueForIdx0  = toolbarParamTmpValue as Array<ToolbarItem>
                thisSerializer.writeInt32((toolbarParamTmpValueForIdx0.length).toInt())
                for (let toolbarParamTmpValueForIdx0CounterI = 0; toolbarParamTmpValueForIdx0CounterI < toolbarParamTmpValueForIdx0.length; toolbarParamTmpValueForIdx0CounterI++) {
                    const toolbarParamTmpValueForIdx0TmpElement : ToolbarItem = toolbarParamTmpValueForIdx0[toolbarParamTmpValueForIdx0CounterI]
                    ToolbarItem_serializer.write(thisSerializer, toolbarParamTmpValueForIdx0TmpElement)
                }
            } else if (toolbarParamTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toChar())
                const toolbarParamTmpValueForIdx1  = toolbarParamTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(toolbarParamTmpValueForIdx1))
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            NavigationToolbarOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setToolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideToolBarAttribute(hide: boolean | undefined, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (hide !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const hideTmpValue  = hide!
            thisSerializer.writeBoolean(hideTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setHideToolBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIgnoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (types !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const typesTmpValue  = types!
            thisSerializer.writeInt32((typesTmpValue.length).toInt())
            for (let typesTmpValueCounterI = 0; typesTmpValueCounterI < typesTmpValue.length; typesTmpValueCounterI++) {
                const typesTmpValueTmpElement : LayoutSafeAreaType = typesTmpValue[typesTmpValueCounterI]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaType_ToNumeric(typesTmpValueTmpElement))
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (edges !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const edgesTmpValue  = edges!
            thisSerializer.writeInt32((edgesTmpValue.length).toInt())
            for (let edgesTmpValueCounterI = 0; edgesTmpValueCounterI < edgesTmpValue.length; edgesTmpValueCounterI++) {
                const edgesTmpValueTmpElement : LayoutSafeAreaEdge = edgesTmpValue[edgesTmpValueCounterI]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaEdge_ToNumeric(edgesTmpValueTmpElement))
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setIgnoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableStatusBarAttribute(enabled: boolean | undefined, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (enabled !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enabledTmpValue  = enabled!
            thisSerializer.writeBoolean(enabledTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class NavDestinationModifier extends CommonMethodModifier implements NavDestinationAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _hideTitleBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_0_0value?: boolean | undefined
    _hideBackButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideBackButton_0_0value?: boolean | undefined
    _onShown_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onShown_0_0value?: (() => void) | undefined
    _onHidden_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHidden_0_0value?: (() => void) | undefined
    _onBackPressed_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onBackPressed_0_0value?: (() => boolean) | undefined
    _onResult_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onResult_0_0value?: ((value0: Object | undefined) => void) | undefined
    _mode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mode_0_0value?: NavDestinationMode | undefined
    _backButtonIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_0_0value?: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined
    _menus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_0_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _onReady_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onReady_0_0value?: ((value0: NavDestinationContext) => void) | undefined
    _onWillAppear_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillAppear_0_0value?: (() => void) | undefined
    _onWillDisappear_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillDisappear_0_0value?: (() => void) | undefined
    _onWillShow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillShow_0_0value?: (() => void) | undefined
    _onWillHide_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillHide_0_0value?: (() => void) | undefined
    _systemBarStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _systemBarStyle_0_0value?: window.SystemBarStyle | undefined
    _recoverable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _recoverable_0_0value?: boolean | undefined
    _systemTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _systemTransition_0_0value?: NavigationSystemTransitionType | undefined
    _bindToScrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindToScrollable_0_0value?: Array<Scroller> | undefined
    _bindToNestedScrollable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindToNestedScrollable_0_0value?: Array<NestedScrollInfo> | undefined
    _onActive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onActive_0_0value?: ((value0: NavDestinationActiveReason) => void) | undefined
    _onInactive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onInactive_0_0value?: ((value0: NavDestinationActiveReason) => void) | undefined
    _customTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customTransition_0_0value?: NavDestinationTransitionDelegate | undefined
    _onNewParam_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onNewParam_0_0value?: ((value0: Object | undefined) => void) | undefined
    _preferredOrientation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _preferredOrientation_0_0value?: Orientation | undefined
    _enableNavigationIndicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableNavigationIndicator_0_0value?: boolean | undefined
    _title_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _title_0_0value?: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined
    _title_0_1value?: NavigationTitleOptions | undefined
    _hideTitleBar_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideTitleBar_1_0value?: boolean | undefined
    _hideTitleBar_1_1value?: boolean | undefined
    _backButtonIcon_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backButtonIcon_1_0value?: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined
    _backButtonIcon_1_1value?: ResourceStr | undefined
    _menus_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _menus_1_0value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _menus_1_1value?: NavigationMenuOptions | undefined
    _toolbarConfiguration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _toolbarConfiguration_0_0value?: Array<ToolbarItem> | CustomBuilder | undefined
    _toolbarConfiguration_0_1value?: NavigationToolbarOptions | undefined
    _hideToolBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hideToolBar_0_0value?: boolean | undefined
    _hideToolBar_0_1value?: boolean | undefined
    _ignoreLayoutSafeArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _ignoreLayoutSafeArea_0_0value?: Array<LayoutSafeAreaType> | undefined
    _ignoreLayoutSafeArea_0_1value?: Array<LayoutSafeAreaEdge> | undefined
    _enableStatusBar_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableStatusBar_0_0value?: boolean | undefined
    _enableStatusBar_0_1value?: boolean | undefined
    applyModifierPatch(peer: ArkNavDestinationPeer): void {
        super.applyModifierPatch(peer)
        if (this._hideTitleBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideTitleBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideTitleBar0Attribute((this._hideTitleBar_0_0value as boolean | undefined));
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideTitleBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideTitleBar0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._hideBackButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideBackButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideBackButtonAttribute((this._hideBackButton_0_0value as boolean | undefined));
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideBackButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideBackButtonAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onShown_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onShown_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnShownAttribute((this._onShown_0_0value as (() => void) | undefined));
                    this._onShown_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onShown_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onShown_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnShownAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHiddenAttribute((this._onHidden_0_0value as (() => void) | undefined));
                    this._onHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHidden_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHiddenAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onBackPressed_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onBackPressed_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnBackPressedAttribute((this._onBackPressed_0_0value as (() => boolean) | undefined));
                    this._onBackPressed_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onBackPressed_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onBackPressed_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnBackPressedAttribute((undefined as (() => boolean) | undefined));
                }
            }
        }
        if (this._onResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnResultAttribute((this._onResult_0_0value as ((value0: Object | undefined) => void) | undefined));
                    this._onResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onResult_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onResult_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnResultAttribute((undefined as ((value0: Object | undefined) => void) | undefined));
                }
            }
        }
        if (this._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setModeAttribute((this._mode_0_0value as NavDestinationMode | undefined));
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setModeAttribute((undefined as NavDestinationMode | undefined));
                }
            }
        }
        if (this._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackButtonIcon0Attribute((this._backButtonIcon_0_0value as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined));
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackButtonIcon0Attribute((undefined as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (this._menus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenus0Attribute((this._menus_0_0value as Array<NavigationMenuItem> | CustomBuilder | undefined));
                    this._menus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenus0Attribute((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined));
                }
            }
        }
        if (this._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnReadyAttribute((this._onReady_0_0value as ((value0: NavDestinationContext) => void) | undefined));
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onReady_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onReady_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnReadyAttribute((undefined as ((value0: NavDestinationContext) => void) | undefined));
                }
            }
        }
        if (this._onWillAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillAppearAttribute((this._onWillAppear_0_0value as (() => void) | undefined));
                    this._onWillAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillAppear_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillAppearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onWillDisappear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillDisappear_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillDisappearAttribute((this._onWillDisappear_0_0value as (() => void) | undefined));
                    this._onWillDisappear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillDisappear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillDisappear_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillDisappearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillShowAttribute((this._onWillShow_0_0value as (() => void) | undefined));
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillShow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillShowAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillHideAttribute((this._onWillHide_0_0value as (() => void) | undefined));
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillHide_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillHideAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._systemBarStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._systemBarStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSystemBarStyleAttribute((this._systemBarStyle_0_0value as window.SystemBarStyle | undefined));
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._systemBarStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSystemBarStyleAttribute((undefined as window.SystemBarStyle | undefined));
                }
            }
        }
        if (this._recoverable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._recoverable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRecoverableAttribute((this._recoverable_0_0value as boolean | undefined));
                    this._recoverable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._recoverable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._recoverable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRecoverableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._systemTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._systemTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSystemTransitionAttribute((this._systemTransition_0_0value as NavigationSystemTransitionType | undefined));
                    this._systemTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._systemTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._systemTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSystemTransitionAttribute((undefined as NavigationSystemTransitionType | undefined));
                }
            }
        }
        if (this._bindToScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindToScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindToScrollableAttribute((this._bindToScrollable_0_0value as Array<Scroller> | undefined));
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindToScrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindToScrollableAttribute((undefined as Array<Scroller> | undefined));
                }
            }
        }
        if (this._bindToNestedScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindToNestedScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindToNestedScrollableAttribute((this._bindToNestedScrollable_0_0value as Array<NestedScrollInfo> | undefined));
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindToNestedScrollableAttribute((undefined as Array<NestedScrollInfo> | undefined));
                }
            }
        }
        if (this._onActive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onActive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnActiveAttribute((this._onActive_0_0value as ((value0: NavDestinationActiveReason) => void) | undefined));
                    this._onActive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onActive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onActive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnActiveAttribute((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
                }
            }
        }
        if (this._onInactive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onInactive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnInactiveAttribute((this._onInactive_0_0value as ((value0: NavDestinationActiveReason) => void) | undefined));
                    this._onInactive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onInactive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onInactive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnInactiveAttribute((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
                }
            }
        }
        if (this._customTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomTransitionAttribute((this._customTransition_0_0value as NavDestinationTransitionDelegate | undefined));
                    this._customTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomTransitionAttribute((undefined as NavDestinationTransitionDelegate | undefined));
                }
            }
        }
        if (this._onNewParam_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onNewParam_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnNewParamAttribute((this._onNewParam_0_0value as ((value0: Object | undefined) => void) | undefined));
                    this._onNewParam_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onNewParam_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onNewParam_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnNewParamAttribute((undefined as ((value0: Object | undefined) => void) | undefined));
                }
            }
        }
        if (this._preferredOrientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._preferredOrientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPreferredOrientationAttribute((this._preferredOrientation_0_0value as Orientation | undefined));
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._preferredOrientation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPreferredOrientationAttribute((undefined as Orientation | undefined));
                }
            }
        }
        if (this._enableNavigationIndicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableNavigationIndicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableNavigationIndicatorAttribute((this._enableNavigationIndicator_0_0value as boolean | undefined));
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableNavigationIndicatorAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._title_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._title_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTitleAttribute((this._title_0_0value as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (this._title_0_1value as NavigationTitleOptions | undefined));
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._title_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._title_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTitleAttribute((undefined as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (this._hideTitleBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideTitleBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideTitleBar1Attribute((this._hideTitleBar_1_0value as boolean | undefined), (this._hideTitleBar_1_1value as boolean | undefined));
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideTitleBar_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideTitleBar1Attribute((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._backButtonIcon_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backButtonIcon_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackButtonIcon1Attribute((this._backButtonIcon_1_0value as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined), (this._backButtonIcon_1_1value as ResourceStr | undefined));
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backButtonIcon_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackButtonIcon1Attribute((undefined as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
        if (this._menus_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._menus_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMenus1Attribute((this._menus_1_0value as Array<NavigationMenuItem> | CustomBuilder | undefined), (this._menus_1_1value as NavigationMenuOptions | undefined));
                    this._menus_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._menus_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._menus_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMenus1Attribute((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (this._toolbarConfiguration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._toolbarConfiguration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setToolbarConfigurationAttribute((this._toolbarConfiguration_0_0value as Array<ToolbarItem> | CustomBuilder | undefined), (this._toolbarConfiguration_0_1value as NavigationToolbarOptions | undefined));
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setToolbarConfigurationAttribute((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (this._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHideToolBarAttribute((this._hideToolBar_0_0value as boolean | undefined), (this._hideToolBar_0_1value as boolean | undefined));
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hideToolBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHideToolBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._ignoreLayoutSafeArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._ignoreLayoutSafeArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIgnoreLayoutSafeAreaAttribute((this._ignoreLayoutSafeArea_0_0value as Array<LayoutSafeAreaType> | undefined), (this._ignoreLayoutSafeArea_0_1value as Array<LayoutSafeAreaEdge> | undefined));
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIgnoreLayoutSafeAreaAttribute((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (this._enableStatusBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableStatusBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableStatusBarAttribute((this._enableStatusBar_0_0value as boolean | undefined), (this._enableStatusBar_0_1value as boolean | undefined));
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableStatusBar_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableStatusBarAttribute((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: NavDestinationModifier): void {
        super.mergeModifier(modifier)
        if (modifier._hideTitleBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideTitleBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideTitleBar(modifier._hideTitleBar_0_0value);
                    break;
                }
                default: {
                    this.hideTitleBar((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._hideBackButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideBackButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideBackButton(modifier._hideBackButton_0_0value);
                    break;
                }
                default: {
                    this.hideBackButton((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onShown_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onShown_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onShown(modifier._onShown_0_0value);
                    break;
                }
                default: {
                    this.onShown((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHidden(modifier._onHidden_0_0value);
                    break;
                }
                default: {
                    this.onHidden((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onBackPressed_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onBackPressed_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onBackPressed(modifier._onBackPressed_0_0value);
                    break;
                }
                default: {
                    this.onBackPressed((undefined as (() => boolean) | undefined));
                }
            }
        }
        if (modifier._onResult_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onResult_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onResult(modifier._onResult_0_0value);
                    break;
                }
                default: {
                    this.onResult((undefined as ((value0: Object | undefined) => void) | undefined));
                }
            }
        }
        if (modifier._mode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mode(modifier._mode_0_0value);
                    break;
                }
                default: {
                    this.mode((undefined as NavDestinationMode | undefined));
                }
            }
        }
        if (modifier._backButtonIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backButtonIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backButtonIcon(modifier._backButtonIcon_0_0value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (modifier._menus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menus(modifier._menus_0_0value);
                    break;
                }
                default: {
                    this.menus((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined));
                }
            }
        }
        if (modifier._onReady_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onReady_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onReady(modifier._onReady_0_0value);
                    break;
                }
                default: {
                    this.onReady((undefined as ((value0: NavDestinationContext) => void) | undefined));
                }
            }
        }
        if (modifier._onWillAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillAppear(modifier._onWillAppear_0_0value);
                    break;
                }
                default: {
                    this.onWillAppear((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onWillDisappear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillDisappear_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillDisappear(modifier._onWillDisappear_0_0value);
                    break;
                }
                default: {
                    this.onWillDisappear((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onWillShow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillShow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillShow(modifier._onWillShow_0_0value);
                    break;
                }
                default: {
                    this.onWillShow((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onWillHide_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillHide_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillHide(modifier._onWillHide_0_0value);
                    break;
                }
                default: {
                    this.onWillHide((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._systemBarStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._systemBarStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.systemBarStyle(modifier._systemBarStyle_0_0value);
                    break;
                }
                default: {
                    this.systemBarStyle((undefined as window.SystemBarStyle | undefined));
                }
            }
        }
        if (modifier._recoverable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._recoverable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.recoverable(modifier._recoverable_0_0value);
                    break;
                }
                default: {
                    this.recoverable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._systemTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._systemTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.systemTransition(modifier._systemTransition_0_0value);
                    break;
                }
                default: {
                    this.systemTransition((undefined as NavigationSystemTransitionType | undefined));
                }
            }
        }
        if (modifier._bindToScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindToScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindToScrollable(modifier._bindToScrollable_0_0value);
                    break;
                }
                default: {
                    this.bindToScrollable((undefined as Array<Scroller> | undefined));
                }
            }
        }
        if (modifier._bindToNestedScrollable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindToNestedScrollable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindToNestedScrollable(modifier._bindToNestedScrollable_0_0value);
                    break;
                }
                default: {
                    this.bindToNestedScrollable((undefined as Array<NestedScrollInfo> | undefined));
                }
            }
        }
        if (modifier._onActive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onActive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onActive(modifier._onActive_0_0value);
                    break;
                }
                default: {
                    this.onActive((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
                }
            }
        }
        if (modifier._onInactive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onInactive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onInactive(modifier._onInactive_0_0value);
                    break;
                }
                default: {
                    this.onInactive((undefined as ((value0: NavDestinationActiveReason) => void) | undefined));
                }
            }
        }
        if (modifier._customTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customTransition(modifier._customTransition_0_0value);
                    break;
                }
                default: {
                    this.customTransition((undefined as NavDestinationTransitionDelegate | undefined));
                }
            }
        }
        if (modifier._onNewParam_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onNewParam_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onNewParam(modifier._onNewParam_0_0value);
                    break;
                }
                default: {
                    this.onNewParam((undefined as ((value0: Object | undefined) => void) | undefined));
                }
            }
        }
        if (modifier._preferredOrientation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._preferredOrientation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.preferredOrientation(modifier._preferredOrientation_0_0value);
                    break;
                }
                default: {
                    this.preferredOrientation((undefined as Orientation | undefined));
                }
            }
        }
        if (modifier._enableNavigationIndicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableNavigationIndicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableNavigationIndicator(modifier._enableNavigationIndicator_0_0value);
                    break;
                }
                default: {
                    this.enableNavigationIndicator((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._title_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._title_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.title(modifier._title_0_0value, modifier._title_0_1value);
                    break;
                }
                default: {
                    this.title((undefined as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined), (undefined as NavigationTitleOptions | undefined | undefined));
                }
            }
        }
        if (modifier._hideTitleBar_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideTitleBar_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideTitleBar(modifier._hideTitleBar_1_0value, modifier._hideTitleBar_1_1value);
                    break;
                }
                default: {
                    this.hideTitleBar((undefined as boolean | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._backButtonIcon_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backButtonIcon_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backButtonIcon(modifier._backButtonIcon_1_0value, modifier._backButtonIcon_1_1value);
                    break;
                }
                default: {
                    this.backButtonIcon((undefined as ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined), (undefined as ResourceStr | undefined | undefined));
                }
            }
        }
        if (modifier._menus_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._menus_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.menus(modifier._menus_1_0value, modifier._menus_1_1value);
                    break;
                }
                default: {
                    this.menus((undefined as Array<NavigationMenuItem> | CustomBuilder | undefined), (undefined as NavigationMenuOptions | undefined | undefined));
                }
            }
        }
        if (modifier._toolbarConfiguration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._toolbarConfiguration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.toolbarConfiguration(modifier._toolbarConfiguration_0_0value, modifier._toolbarConfiguration_0_1value);
                    break;
                }
                default: {
                    this.toolbarConfiguration((undefined as Array<ToolbarItem> | CustomBuilder | undefined), (undefined as NavigationToolbarOptions | undefined | undefined));
                }
            }
        }
        if (modifier._hideToolBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hideToolBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hideToolBar(modifier._hideToolBar_0_0value, modifier._hideToolBar_0_1value);
                    break;
                }
                default: {
                    this.hideToolBar((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._ignoreLayoutSafeArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._ignoreLayoutSafeArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.ignoreLayoutSafeArea(modifier._ignoreLayoutSafeArea_0_0value, modifier._ignoreLayoutSafeArea_0_1value);
                    break;
                }
                default: {
                    this.ignoreLayoutSafeArea((undefined as Array<LayoutSafeAreaType> | undefined | undefined), (undefined as Array<LayoutSafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (modifier._enableStatusBar_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableStatusBar_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableStatusBar(modifier._enableStatusBar_0_0value, modifier._enableStatusBar_0_1value);
                    break;
                }
                default: {
                    this.enableStatusBar((undefined as boolean | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
    }
    hideTitleBar(value: boolean | undefined): this {
        if (((this._hideTitleBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideTitleBar_0_0value) !== (value)))
        {
            this._hideTitleBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideTitleBar_0_0value = value
        } else
        {
            this._hideTitleBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideBackButton(value: boolean | undefined): this {
        if (((this._hideBackButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideBackButton_0_0value) !== (value)))
        {
            this._hideBackButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideBackButton_0_0value = value
        } else
        {
            this._hideBackButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onShown(value: (() => void) | undefined): this {
        if (((this._onShown_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onShown_0_flag = AttributeUpdaterFlag.UPDATE
            this._onShown_0_0value = value
        } else
        {
            this._onShown_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHidden(value: (() => void) | undefined): this {
        if (((this._onHidden_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHidden_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHidden_0_0value = value
        } else
        {
            this._onHidden_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onBackPressed(value: (() => boolean) | undefined): this {
        if (((this._onBackPressed_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onBackPressed_0_flag = AttributeUpdaterFlag.UPDATE
            this._onBackPressed_0_0value = value
        } else
        {
            this._onBackPressed_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onResult(value: ((value0: Object | undefined) => void) | undefined): this {
        if (((this._onResult_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onResult_0_flag = AttributeUpdaterFlag.UPDATE
            this._onResult_0_0value = value
        } else
        {
            this._onResult_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mode(value: NavDestinationMode | undefined): this {
        if (((this._mode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mode_0_flag = AttributeUpdaterFlag.UPDATE
            this._mode_0_0value = value
        } else
        {
            this._mode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backButtonIcon(value: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined): this {
        if (((this._backButtonIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._backButtonIcon_0_0value = value
        } else
        {
            this._backButtonIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        if (((this._menus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._menus_0_flag = AttributeUpdaterFlag.UPDATE
            this._menus_0_0value = value
        } else
        {
            this._menus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        if (((this._onReady_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onReady_0_flag = AttributeUpdaterFlag.UPDATE
            this._onReady_0_0value = value
        } else
        {
            this._onReady_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillAppear(value: (() => void) | undefined): this {
        if (((this._onWillAppear_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillAppear_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillAppear_0_0value = value
        } else
        {
            this._onWillAppear_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillDisappear(value: (() => void) | undefined): this {
        if (((this._onWillDisappear_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillDisappear_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillDisappear_0_0value = value
        } else
        {
            this._onWillDisappear_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillShow(value: (() => void) | undefined): this {
        if (((this._onWillShow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillShow_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillShow_0_0value = value
        } else
        {
            this._onWillShow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillHide(value: (() => void) | undefined): this {
        if (((this._onWillHide_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillHide_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillHide_0_0value = value
        } else
        {
            this._onWillHide_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    systemBarStyle(value: window.SystemBarStyle | undefined): this {
        if (((this._systemBarStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._systemBarStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._systemBarStyle_0_0value = value
        } else
        {
            this._systemBarStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    recoverable(value: boolean | undefined): this {
        if (((this._recoverable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._recoverable_0_0value) !== (value)))
        {
            this._recoverable_0_flag = AttributeUpdaterFlag.UPDATE
            this._recoverable_0_0value = value
        } else
        {
            this._recoverable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    systemTransition(value: NavigationSystemTransitionType | undefined): this {
        if (((this._systemTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._systemTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._systemTransition_0_0value = value
        } else
        {
            this._systemTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindToScrollable(value: Array<Scroller> | undefined): this {
        if (((this._bindToScrollable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._bindToScrollable_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindToScrollable_0_0value = value
        } else
        {
            this._bindToScrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        if (((this._bindToNestedScrollable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindToNestedScrollable_0_0value = value
        } else
        {
            this._bindToNestedScrollable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        if (((this._onActive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onActive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onActive_0_0value = value
        } else
        {
            this._onActive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        if (((this._onInactive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onInactive_0_flag = AttributeUpdaterFlag.UPDATE
            this._onInactive_0_0value = value
        } else
        {
            this._onInactive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        if (((this._customTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._customTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._customTransition_0_0value = value
        } else
        {
            this._customTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onNewParam(value: ((value0: Object | undefined) => void) | undefined): this {
        if (((this._onNewParam_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onNewParam_0_flag = AttributeUpdaterFlag.UPDATE
            this._onNewParam_0_0value = value
        } else
        {
            this._onNewParam_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    preferredOrientation(value: Orientation | undefined): this {
        if (((this._preferredOrientation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._preferredOrientation_0_flag = AttributeUpdaterFlag.UPDATE
            this._preferredOrientation_0_0value = value
        } else
        {
            this._preferredOrientation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableNavigationIndicator(value: boolean | undefined): this {
        if (((this._enableNavigationIndicator_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableNavigationIndicator_0_0value) !== (value)))
        {
            this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableNavigationIndicator_0_0value = value
        } else
        {
            this._enableNavigationIndicator_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
        if (((this._title_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._title_0_flag = AttributeUpdaterFlag.UPDATE
            this._title_0_0value = value
            this._title_0_1value = options
        } else
        {
            this._title_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (((this._hideTitleBar_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideTitleBar_1_0value) !== (hide)) || ((this._hideTitleBar_1_1value) !== (animated)))
        {
            this._hideTitleBar_1_flag = AttributeUpdaterFlag.UPDATE
            this._hideTitleBar_1_0value = hide
            this._hideTitleBar_1_1value = animated
        } else
        {
            this._hideTitleBar_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backButtonIcon(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (((this._backButtonIcon_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._backButtonIcon_1_flag = AttributeUpdaterFlag.UPDATE
            this._backButtonIcon_1_0value = icon
            this._backButtonIcon_1_1value = accessibilityText
        } else
        {
            this._backButtonIcon_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (((this._menus_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._menus_1_flag = AttributeUpdaterFlag.UPDATE
            this._menus_1_0value = items
            this._menus_1_1value = options
        } else
        {
            this._menus_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (((this._toolbarConfiguration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.UPDATE
            this._toolbarConfiguration_0_0value = toolbarParam
            this._toolbarConfiguration_0_1value = options
        } else
        {
            this._toolbarConfiguration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        if (((this._hideToolBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hideToolBar_0_0value) !== (hide)) || ((this._hideToolBar_0_1value) !== (animated)))
        {
            this._hideToolBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._hideToolBar_0_0value = hide
            this._hideToolBar_0_1value = animated
        } else
        {
            this._hideToolBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (((this._ignoreLayoutSafeArea_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.UPDATE
            this._ignoreLayoutSafeArea_0_0value = types
            this._ignoreLayoutSafeArea_0_1value = edges
        } else
        {
            this._ignoreLayoutSafeArea_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        if (((this._enableStatusBar_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableStatusBar_0_0value) !== (enabled)) || ((this._enableStatusBar_0_1value) !== (animated)))
        {
            this._enableStatusBar_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableStatusBar_0_0value = enabled
            this._enableStatusBar_0_1value = animated
        } else
        {
            this._enableStatusBar_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class NavDestinationTransition_serializer {
    public static write(buffer: SerializerBase, value: NavDestinationTransition): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnTransitionEnd  = value.onTransitionEnd
        if (valueHolderForOnTransitionEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnTransitionEndTmpValue  = valueHolderForOnTransitionEnd!
            valueSerializer.holdAndWriteCallback(valueHolderForOnTransitionEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDuration  = value.duration
        if (valueHolderForDuration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDurationTmpValue  = valueHolderForDuration!
            valueSerializer.writeNumber(valueHolderForDurationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCurve  = value.curve
        if (valueHolderForCurve !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurveTmpValue  = (valueHolderForCurve as curves.Curve)
            valueSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(valueHolderForCurveTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDelay  = value.delay
        if (valueHolderForDelay !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDelayTmpValue  = valueHolderForDelay!
            valueSerializer.writeNumber(valueHolderForDelayTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEvent  = value.event
        valueSerializer.holdAndWriteCallback(valueHolderForEvent)
    }
    public static read(buffer: DeserializerBase): NavDestinationTransition {
        let valueDeserializer : DeserializerBase = buffer
        const onTransitionEndTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onTransitionEndTmpBuf : (() => void) | undefined
        if ((onTransitionEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onTransitionEndTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onTransitionEndTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onTransitionEndTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onTransitionEndTmpBuf = ():void => {
                const onTransitionEndTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onTransitionEndTmpBuf_BufArgsSerializer.writeInt32(onTransitionEndTmpBuf_BufResource.resourceId);
                onTransitionEndTmpBuf_BufArgsSerializer.writePointer(onTransitionEndTmpBuf_BufCall);
                onTransitionEndTmpBuf_BufArgsSerializer.writePointer(onTransitionEndTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-1867723152, onTransitionEndTmpBuf_BufArgsSerializer.asBuffer(), onTransitionEndTmpBuf_BufArgsSerializer.length());
                onTransitionEndTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onTransitionEndTmpResult : (() => void) | undefined = onTransitionEndTmpBuf
        const durationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let durationTmpBuf : number | undefined
        if ((durationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            durationTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const durationTmpResult : number | undefined = durationTmpBuf
        const curveTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let curveTmpBuf : curves.Curve | undefined
        if ((curveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            curveTmpBuf = TypeChecker.curves_Curve_FromNumeric(valueDeserializer.readInt32())
        }
        const curveTmpResult : curves.Curve | undefined = curveTmpBuf
        const delayTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let delayTmpBuf : number | undefined
        if ((delayTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            delayTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const delayTmpResult : number | undefined = delayTmpBuf
        const eventTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const eventTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const eventTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const eventTmpResult : (() => void) = ():void => {
            const eventTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            eventTmpBufBufArgsSerializer.writeInt32(eventTmpBufBufResource.resourceId);
            eventTmpBufBufArgsSerializer.writePointer(eventTmpBufBufCall);
            eventTmpBufBufArgsSerializer.writePointer(eventTmpBufBufCallSync);
            InteropNativeModule._CallCallback(-1867723152, eventTmpBufBufArgsSerializer.asBuffer(), eventTmpBufBufArgsSerializer.length());
            eventTmpBufBufArgsSerializer.release();
            return;
        }
        let value : NavDestinationTransition = ({onTransitionEnd: onTransitionEndTmpResult, duration: durationTmpResult, curve: curveTmpResult, delay: delayTmpResult, event: eventTmpResult} as NavDestinationTransition)
        return value
    }
}
export class NestedScrollInfo_serializer {
    public static write(buffer: SerializerBase, value: NestedScrollInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForParent  = value.parent
        Scroller_serializer.write(valueSerializer, valueHolderForParent)
        const valueHolderForChild  = value.child
        Scroller_serializer.write(valueSerializer, valueHolderForChild)
    }
    public static read(buffer: DeserializerBase): NestedScrollInfo {
        let valueDeserializer : DeserializerBase = buffer
        const parentTmpResult : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        const childTmpResult : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        let value : NestedScrollInfo = ({parent: parentTmpResult, child: childTmpResult} as NestedScrollInfo)
        return value
    }
}
export class RouteMapConfig_serializer {
    public static write(buffer: SerializerBase, value: RouteMapConfig): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForPageSourceFile  = value.pageSourceFile
        valueSerializer.writeString(valueHolderForPageSourceFile)
        const valueHolderForData  = value.data
        valueSerializer.holdAndWriteObject(valueHolderForData)
    }
    public static read(buffer: DeserializerBase): RouteMapConfig {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const pageSourceFileTmpResult : string = (valueDeserializer.readString() as string)
        const dataTmpResult : Object = (valueDeserializer.readObject() as object)
        let value : RouteMapConfig = ({name: nameTmpResult, pageSourceFile: pageSourceFileTmpResult, data: dataTmpResult} as RouteMapConfig)
        return value
    }
}
export class NavDestinationCommonTitle_serializer {
    public static write(buffer: SerializerBase, value: NavDestinationCommonTitle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMain  = value.main
        if (valueHolderForMain instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForMainForIdx0  = valueHolderForMain as string
            valueSerializer.writeString(valueHolderForMainForIdx0)
        } else if (valueHolderForMain instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForMainForIdx1  = valueHolderForMain as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMainForIdx1)
        }
        const valueHolderForSub  = value.sub
        if (valueHolderForSub instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForSubForIdx0  = valueHolderForSub as string
            valueSerializer.writeString(valueHolderForSubForIdx0)
        } else if (valueHolderForSub instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForSubForIdx1  = valueHolderForSub as Resource
            Resource_serializer.write(valueSerializer, valueHolderForSubForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): NavDestinationCommonTitle {
        let valueDeserializer : DeserializerBase = buffer
        const mainTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let mainTmpBuf : string | Resource | undefined
        if (mainTmpBufUnionSelector == (0).toChar()) {
            mainTmpBuf = (valueDeserializer.readString() as string)
        } else if (mainTmpBufUnionSelector == (1).toChar()) {
            mainTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for mainTmpBuf has to be chosen through deserialisation.")
        }
        const mainTmpResult : string | Resource = (mainTmpBuf as string | Resource)
        const subTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let subTmpBuf : string | Resource | undefined
        if (subTmpBufUnionSelector == (0).toChar()) {
            subTmpBuf = (valueDeserializer.readString() as string)
        } else if (subTmpBufUnionSelector == (1).toChar()) {
            subTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for subTmpBuf has to be chosen through deserialisation.")
        }
        const subTmpResult : string | Resource = (subTmpBuf as string | Resource)
        let value : NavDestinationCommonTitle = ({main: mainTmpResult, sub: subTmpResult} as NavDestinationCommonTitle)
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
        const valueHolderForBuilder  = value.builder
        valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForBuilder))
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight instanceof TitleHeight) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForHeightForIdx0  = valueHolderForHeight as TitleHeight
            valueSerializer.writeInt32(TypeChecker.TitleHeight_ToNumeric(valueHolderForHeightForIdx0))
        } else if (valueHolderForHeight instanceof Length) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForHeightForIdx1  = valueHolderForHeight as Length
            if (valueHolderForHeightForIdx1 instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForHeightForIdx1ForIdx0  = valueHolderForHeightForIdx1 as string
                valueSerializer.writeString(valueHolderForHeightForIdx1ForIdx0)
            } else if (valueHolderForHeightForIdx1 instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForHeightForIdx1ForIdx1  = valueHolderForHeightForIdx1 as number
                valueSerializer.writeNumber(valueHolderForHeightForIdx1ForIdx1)
            } else if (valueHolderForHeightForIdx1 instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForHeightForIdx1ForIdx2  = valueHolderForHeightForIdx1 as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightForIdx1ForIdx2)
            }
        }
    }
    public static read(buffer: DeserializerBase): NavDestinationCustomTitle {
        let valueDeserializer : DeserializerBase = buffer
        const builderTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const builderTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const builderTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const builderTmpResult : CustomBuilder = ():void => {
            const builderTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            builderTmpBufBufArgsSerializer.writeInt32(builderTmpBufBufResource.resourceId);
            builderTmpBufBufArgsSerializer.writePointer(builderTmpBufBufCall);
            builderTmpBufBufArgsSerializer.writePointer(builderTmpBufBufCallSync);
            InteropNativeModule._CallCallback(737226752, builderTmpBufBufArgsSerializer.asBuffer(), builderTmpBufBufArgsSerializer.length());
            builderTmpBufBufArgsSerializer.release();
            return;
        }
        const heightTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let heightTmpBuf : TitleHeight | Length | undefined
        if (heightTmpBufUnionSelector == (0).toChar()) {
            heightTmpBuf = TypeChecker.TitleHeight_FromNumeric(valueDeserializer.readInt32())
        } else if (heightTmpBufUnionSelector == (1).toChar()) {
            const heightTmpBufBufUUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufBufU : string | number | Resource | undefined
            if (heightTmpBufBufUUnionSelector == (0).toChar()) {
                heightTmpBufBufU = (valueDeserializer.readString() as string)
            } else if (heightTmpBufBufUUnionSelector == (1).toChar()) {
                heightTmpBufBufU = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBufBufUUnionSelector == (2).toChar()) {
                heightTmpBufBufU = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBufBufU has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBufBufU as string | number | Resource)
        } else {
            throw new Error("One of the branches for heightTmpBuf has to be chosen through deserialisation.")
        }
        const heightTmpResult : TitleHeight | Length = (heightTmpBuf as TitleHeight | Length)
        let value : NavDestinationCustomTitle = ({builder: builderTmpResult, height: heightTmpResult} as NavDestinationCustomTitle)
        return value
    }
}
