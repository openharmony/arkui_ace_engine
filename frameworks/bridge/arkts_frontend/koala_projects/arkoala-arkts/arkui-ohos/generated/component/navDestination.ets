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
import { Resource_serializer } from "./../framework/resource"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
import { SymbolGlyphModifier_serializer } from "./../SymbolGlyphModifier"
import { window_SystemBarStyle_serializer } from "./../framework/ohos.window"
import { Scroller_serializer, Scroller } from "./scroll"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceStr, Length, ResourceColor } from "./units"
import { Resource } from "global.resource"
import { extractors, AttributeModifier, hookNavDestinationAttributeModifier, AttributeUpdater, hookGetConfigInRouteMap } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { default as image } from "@ohos.multimedia.image"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { CustomBuilder } from "./builder"
import { default as window } from "@ohos.window"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics } from "arkui.Graphics"
import { TextModifier } from "arkui.TextModifier"
import { AsyncCallback, BusinessError } from "@ohos.base"
import { default as colorSpaceManager } from "@ohos.graphics.colorSpaceManager"
import { default as rpc } from "@ohos.rpc"
import { SymbolGlyphAttribute } from "./symbolglyph"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { default as curves } from "@ohos.curves"
import { NavDestinationModifier } from "./../NavDestinationModifier"
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
        return hookGetConfigInRouteMap(this)
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
    getConfigInRouteMap_serialize(): RouteMapConfig | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getConfigInRouteMap(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RouteMapConfig | undefined = undefined
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
        let buffer : string | undefined = undefined
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
    attributeSet?: NavDestinationModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavDestinationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._NavDestination_construct(peerId, flags)
        const _peer  = new ArkNavDestinationPeer(_peerPtr, peerId, 'NavDestination', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavDestinationOptionsAttribute(moduleInfo?: NavDestinationModuleInfo): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (moduleInfo !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const moduleInfoTmpValue  = moduleInfo!
            NavDestinationModuleInfo_serializer.write(thisSerializer, moduleInfoTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationInterface_setNavDestinationOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    setOnResultAttribute(value: ((value0: Object | null | undefined) => void) | undefined): void {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setOnNewParamAttribute(value: ((value0: Object | null | undefined) => void) | undefined): void {
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
    setPreferredOrientationAttribute(value: window.Orientation | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as window.Orientation)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx1))
            } else if (valueTmpValue instanceof NavDestinationCommonTitle) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as NavDestinationCommonTitle
                NavDestinationCommonTitle_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof NavDestinationCustomTitle) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as NavDestinationCustomTitle
                NavDestinationCustomTitle_serializer.write(thisSerializer, valueTmpValueForIdx3)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((4).toByte())
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
    setBackButtonIconAttribute(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (icon !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const iconTmpValue  = icon!
            if (iconTmpValue instanceof ResourceStr) {
                thisSerializer.writeInt8((0).toByte())
                const iconTmpValueForIdx0  = iconTmpValue as ResourceStr
                if (iconTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const iconTmpValueForIdx0ForIdx0  = iconTmpValueForIdx0 as string
                    thisSerializer.writeString(iconTmpValueForIdx0ForIdx0)
                } else if (iconTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((1).toByte())
                    const iconTmpValueForIdx0ForIdx1  = iconTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, iconTmpValueForIdx0ForIdx1)
                }
            } else if (iconTmpValue instanceof image.PixelMap) {
                thisSerializer.writeInt8((1).toByte())
                const iconTmpValueForIdx1  = iconTmpValue as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, iconTmpValueForIdx1)
            } else if (iconTmpValue instanceof SymbolGlyphModifier) {
                thisSerializer.writeInt8((2).toByte())
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
                thisSerializer.writeInt8((0).toByte())
                const accessibilityTextTmpValueForIdx0  = accessibilityTextTmpValue as string
                thisSerializer.writeString(accessibilityTextTmpValueForIdx0)
            } else if (accessibilityTextTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const accessibilityTextTmpValueForIdx1  = accessibilityTextTmpValue as Resource
                Resource_serializer.write(thisSerializer, accessibilityTextTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setBackButtonIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMenusAttribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (items !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const itemsTmpValue  = items!
            if (TypeChecker.isArray_NavigationMenuItem(itemsTmpValue)) {
                thisSerializer.writeInt8((0).toByte())
                const itemsTmpValueForIdx0  = itemsTmpValue as Array<NavigationMenuItem>
                thisSerializer.writeInt32((itemsTmpValueForIdx0.length).toInt())
                for (let itemsTmpValueForIdx0CounterI = 0; itemsTmpValueForIdx0CounterI < itemsTmpValueForIdx0.length; itemsTmpValueForIdx0CounterI++) {
                    const itemsTmpValueForIdx0TmpElement : NavigationMenuItem = itemsTmpValueForIdx0[itemsTmpValueForIdx0CounterI]
                    NavigationMenuItem_serializer.write(thisSerializer, itemsTmpValueForIdx0TmpElement)
                }
            } else if (itemsTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toByte())
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
        ArkUIGeneratedNativeModule._NavDestinationAttribute_setMenus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setToolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (toolbarParam !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const toolbarParamTmpValue  = toolbarParam!
            if (TypeChecker.isArray_ToolbarItem(toolbarParamTmpValue)) {
                thisSerializer.writeInt8((0).toByte())
                const toolbarParamTmpValueForIdx0  = toolbarParamTmpValue as Array<ToolbarItem>
                thisSerializer.writeInt32((toolbarParamTmpValueForIdx0.length).toInt())
                for (let toolbarParamTmpValueForIdx0CounterI = 0; toolbarParamTmpValueForIdx0CounterI < toolbarParamTmpValueForIdx0.length; toolbarParamTmpValueForIdx0CounterI++) {
                    const toolbarParamTmpValueForIdx0TmpElement : ToolbarItem = toolbarParamTmpValueForIdx0[toolbarParamTmpValueForIdx0CounterI]
                    ToolbarItem_serializer.write(thisSerializer, toolbarParamTmpValueForIdx0TmpElement)
                }
            } else if (toolbarParamTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toByte())
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
                thisSerializer.writeInt32(typesTmpValueTmpElement.valueOf())
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
                thisSerializer.writeInt32(edgesTmpValueTmpElement.valueOf())
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
export type Orientation = window.Orientation;
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
    duration?: int32;
    curve?: curves.Curve;
    delay?: int32;
    event: (() => void);
}
export interface NavDestinationAttribute extends CommonMethod {
    setNavDestinationOptions(moduleInfo?: NavDestinationModuleInfo): this {
        throw new Error("Unimplemented method setNavDestinationOptions")
    }
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
    onResult(value: ((value0: Object | null | undefined) => void) | undefined): this {
        throw new Error("Unimplemented method onResult")
    }
    mode(value: NavDestinationMode | undefined): this {
        throw new Error("Unimplemented method mode")
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
    onNewParam(value: ((value0: Object | null | undefined) => void) | undefined): this {
        throw new Error("Unimplemented method onNewParam")
    }
    preferredOrientation(value: window.Orientation | undefined): this {
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
    onResult_value?: ((value0: Object | null | undefined) => void) | undefined
    mode_value?: NavDestinationMode | undefined
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
    onNewParam_value?: ((value0: Object | null | undefined) => void) | undefined
    preferredOrientation_value?: window.Orientation | undefined
    enableNavigationIndicator_value?: boolean | undefined
    setNavDestinationOptions(moduleInfo?: NavDestinationModuleInfo): this {
        return this
    }
    hideTitleBar(value: boolean | undefined): this {
        return this
    }
    hideBackButton(value: boolean | undefined): this {
        return this
    }
    onShown(value: (() => void) | undefined): this {
        return this
    }
    onHidden(value: (() => void) | undefined): this {
        return this
    }
    onBackPressed(value: (() => boolean) | undefined): this {
        return this
    }
    onResult(value: ((value0: Object | null | undefined) => void) | undefined): this {
        return this
    }
    mode(value: NavDestinationMode | undefined): this {
        return this
    }
    onReady(value: ((value0: NavDestinationContext) => void) | undefined): this {
        return this
    }
    onWillAppear(value: (() => void) | undefined): this {
        return this
    }
    onWillDisappear(value: (() => void) | undefined): this {
        return this
    }
    onWillShow(value: (() => void) | undefined): this {
        return this
    }
    onWillHide(value: (() => void) | undefined): this {
        return this
    }
    systemBarStyle(value: window.SystemBarStyle | undefined): this {
        return this
    }
    recoverable(value: boolean | undefined): this {
        return this
    }
    systemTransition(value: NavigationSystemTransitionType | undefined): this {
        return this
    }
    bindToScrollable(value: Array<Scroller> | undefined): this {
        return this
    }
    bindToNestedScrollable(value: Array<NestedScrollInfo> | undefined): this {
        return this
    }
    onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        return this
    }
    onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): this {
        return this
    }
    customTransition(value: NavDestinationTransitionDelegate | undefined): this {
        return this
    }
    onNewParam(value: ((value0: Object | null | undefined) => void) | undefined): this {
        return this
    }
    preferredOrientation(value: window.Orientation | undefined): this {
        return this
    }
    enableNavigationIndicator(value: boolean | undefined): this {
        return this
    }
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions): this {
        return this
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        return this
    }
    backButtonIcon(icon: ResourceStr | image.PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        return this
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        return this
    }
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        return this
    }
    hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        return this
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        return this
    }
    enableStatusBar(enabled: boolean | undefined, animated?: boolean): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type NavDestinationTransitionDelegate = (operation: NavigationOperation, isEnter: boolean) => Array<NavDestinationTransition> | undefined;
export interface NavDestinationModuleInfo {
    moduleName: string;
    pagePath: string;
}

export class ArkNavDestinationComponent extends ArkCommonMethodComponent implements NavDestinationAttribute {
    getPeer(): ArkNavDestinationPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkNavDestinationPeer)
    }
    public setNavDestinationOptions(moduleInfo?: NavDestinationModuleInfo): this {
        if (this.checkPriority("setNavDestinationOptions")) {
            const moduleInfo_casted = moduleInfo as (NavDestinationModuleInfo | undefined)
            this.getPeer()?.setNavDestinationOptionsAttribute(moduleInfo_casted)
            this.applyOptionsFinish('NavDestinationAttribute');
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
    public onResult(value: ((value0: Object | null | undefined) => void) | undefined): this {
        if (this.checkPriority("onResult")) {
            const value_casted = value as (((value0: Object | null | undefined) => void) | undefined)
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
    public onNewParam(value: ((value0: Object | null | undefined) => void) | undefined): this {
        if (this.checkPriority("onNewParam")) {
            const value_casted = value as (((value0: Object | null | undefined) => void) | undefined)
            this.getPeer()?.setOnNewParamAttribute(value_casted)
            return this
        }
        return this
    }
    public preferredOrientation(value: window.Orientation | undefined): this {
        if (this.checkPriority("preferredOrientation")) {
            const value_casted = value as (window.Orientation | undefined)
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
            this.getPeer()?.setBackButtonIconAttribute(icon_casted, accessibilityText_casted)
            return this
        }
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (this.checkPriority("menus")) {
            const items_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationMenuOptions | undefined)
            this.getPeer()?.setMenusAttribute(items_casted, options_casted)
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
        ModifierStateManager.INSTANCE.scope(() => {
          hookNavDestinationAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function NavDestinationImpl(
    @memo
    style: ((attributes: NavDestinationAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkNavDestinationComponent>((): ArkNavDestinationComponent => {
        return new ArkNavDestinationComponent()
    })
    NodeAttach<ArkNavDestinationPeer>((): ArkNavDestinationPeer => ArkNavDestinationPeer.create(receiver), (peer: ArkNavDestinationPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class NavDestinationModuleInfo_serializer {
    public static write(buffer: SerializerBase, value: NavDestinationModuleInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForModuleName  = value.moduleName
        valueSerializer.writeString(valueHolderForModuleName)
        const valueHolderForPagePath  = value.pagePath
        valueSerializer.writeString(valueHolderForPagePath)
    }
    public static read(buffer: DeserializerBase): NavDestinationModuleInfo {
        let valueDeserializer : DeserializerBase = buffer
        const moduleNameTmpResult : string = (valueDeserializer.readString() as string)
        const pagePathTmpResult : string = (valueDeserializer.readString() as string)
        let value : NavDestinationModuleInfo = ({moduleName: moduleNameTmpResult, pagePath: pagePathTmpResult} as NavDestinationModuleInfo)
        return value
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
            valueSerializer.writeInt32(valueHolderForDurationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCurve  = value.curve
        if (valueHolderForCurve !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurveTmpValue  = (valueHolderForCurve as curves.Curve)
            valueSerializer.writeInt32(valueHolderForCurveTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDelay  = value.delay
        if (valueHolderForDelay !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDelayTmpValue  = valueHolderForDelay!
            valueSerializer.writeInt32(valueHolderForDelayTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEvent  = value.event
        valueSerializer.holdAndWriteCallback(valueHolderForEvent)
    }
    public static read(buffer: DeserializerBase): NavDestinationTransition {
        let valueDeserializer : DeserializerBase = buffer
        const onTransitionEndTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onTransitionEndTmpBuf : (() => void) | undefined = undefined
        if ((onTransitionEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onTransitionEndTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onTransitionEndTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onTransitionEndTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onTransitionEndTmpBuf = ():void => {
                const onTransitionEndTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onTransitionEndTmpBuf_BufArgsSerializer.writeInt32(onTransitionEndTmpBuf_BufResource.resourceId);
                onTransitionEndTmpBuf_BufArgsSerializer.writePointer(onTransitionEndTmpBuf_BufCall);
                onTransitionEndTmpBuf_BufArgsSerializer.writePointer(onTransitionEndTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onTransitionEndTmpBuf_BufArgsSerializer.asBuffer(), onTransitionEndTmpBuf_BufArgsSerializer.length());
                onTransitionEndTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onTransitionEndTmpResult : (() => void) | undefined = onTransitionEndTmpBuf
        const durationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let durationTmpBuf : int32 | undefined = undefined
        if ((durationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            durationTmpBuf = valueDeserializer.readInt32()
        }
        const durationTmpResult : int32 | undefined = durationTmpBuf
        const curveTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let curveTmpBuf : curves.Curve | undefined = undefined
        if ((curveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            curveTmpBuf = curves.Curve.fromValue(valueDeserializer.readInt32())
        }
        const curveTmpResult : curves.Curve | undefined = curveTmpBuf
        const delayTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let delayTmpBuf : int32 | undefined = undefined
        if ((delayTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            delayTmpBuf = valueDeserializer.readInt32()
        }
        const delayTmpResult : int32 | undefined = delayTmpBuf
        const eventTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const eventTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const eventTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const eventTmpResult : (() => void) = ():void => {
            const eventTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            eventTmpBufBufArgsSerializer.writeInt32(eventTmpBufBufResource.resourceId);
            eventTmpBufBufArgsSerializer.writePointer(eventTmpBufBufCall);
            eventTmpBufBufArgsSerializer.writePointer(eventTmpBufBufCallSync);
            InteropNativeModule._CallCallbackSync(10, -1867723152, eventTmpBufBufArgsSerializer.asBuffer(), eventTmpBufBufArgsSerializer.length());
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
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForMainForIdx0  = valueHolderForMain as string
            valueSerializer.writeString(valueHolderForMainForIdx0)
        } else if (valueHolderForMain instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForMainForIdx1  = valueHolderForMain as Resource
            Resource_serializer.write(valueSerializer, valueHolderForMainForIdx1)
        }
        const valueHolderForSub  = value.sub
        if (valueHolderForSub instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSubForIdx0  = valueHolderForSub as string
            valueSerializer.writeString(valueHolderForSubForIdx0)
        } else if (valueHolderForSub instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
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
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForHeightForIdx0  = valueHolderForHeight as TitleHeight
            valueSerializer.writeInt32(valueHolderForHeightForIdx0.valueOf())
        } else if (valueHolderForHeight instanceof Length) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForHeightForIdx1  = valueHolderForHeight as Length
            if (valueHolderForHeightForIdx1 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightForIdx1ForIdx0  = valueHolderForHeightForIdx1 as string
                valueSerializer.writeString(valueHolderForHeightForIdx1ForIdx0)
            } else if (valueHolderForHeightForIdx1 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightForIdx1ForIdx1  = valueHolderForHeightForIdx1 as number
                valueSerializer.writeNumber(valueHolderForHeightForIdx1ForIdx1)
            } else if (valueHolderForHeightForIdx1 instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
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
            InteropNativeModule._CallCallbackSync(10, 737226752, builderTmpBufBufArgsSerializer.asBuffer(), builderTmpBufBufArgsSerializer.length());
            builderTmpBufBufArgsSerializer.release();
            return;
        }
        const heightTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let heightTmpBuf : TitleHeight | Length | undefined
        if (heightTmpBufUnionSelector == (0).toChar()) {
            heightTmpBuf = TitleHeight.fromValue(valueDeserializer.readInt32())
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
