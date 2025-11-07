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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, KInt32ArrayPtr } from "@koalaui/interop"
import { VoidCallback, Length, Dimension, ResourceStr, ResourceColor } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { hookPushPathMethod, hookPushPathByNameMethod, hookReplacePathMethod, hookReplacePathByNameMethod, hookPopMethod, hookPopToNameMethod, hookPopToIndexMethod, hookGetParamByIndexMethod, hookGetParamByNameMethod, extractors, AttributeModifier, hookSetNavigationOptions, hookSetNavDestination, hookNavigationAttributeModifier, AttributeUpdater } from "#handwritten"
import { Resource_serializer } from "./../framework/resource"
import { Bindable_Arkui_Component_Units_Length_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer } from "./common"
import { image_PixelMap_serializer } from "./../framework/ohos.multimedia.image"
import { SymbolGlyphModifier_serializer } from "./../SymbolGlyphModifier"
import { window_SystemBarStyle_serializer } from "./../framework/ohos.window"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Resource } from "global.resource"
import { default as image } from "@ohos.multimedia.image"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { CustomBuilder, PageMapBuilder } from "./builder"
import { default as window } from "@ohos.window"
import { AsyncCallback, BusinessError } from "@ohos.base"
import { default as colorSpaceManager } from "@ohos.graphics.colorSpaceManager"
import { default as rpc } from "@ohos.rpc"
import { SymbolGlyphAttribute } from "./symbolglyph"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics } from "arkui.Graphics"
import { TextModifier } from "arkui.TextModifier"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { NavDestinationContext, NavDestinationMode, NavDestinationContext_serializer } from "./navDestination"
import { NavigationModifier } from "./../NavigationModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics_serializer } from "./../Graphics"
import { TextModifier_serializer } from "./../TextModifier"
export interface NavigationTransitionProxy {
    from: NavContentInfo
    to: NavContentInfo
    isInteractive?: boolean | undefined
    cancelTransition?: VoidCallback | undefined
    updateTransition?: UpdateTransitionCallback | undefined
    finishTransition(): void
}
export class NavigationTransitionProxyInternal implements MaterializedBase,NavigationTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get from(): NavContentInfo {
        return this.getFrom()
    }
    set from(from: NavContentInfo) {
        this.setFrom(from)
    }
    get to(): NavContentInfo {
        return this.getTo()
    }
    set to(to: NavContentInfo) {
        this.setTo(to)
    }
    get isInteractive(): boolean | undefined {
        return this.getIsInteractive()
    }
    set isInteractive(isInteractive: boolean | undefined) {
        const isInteractive_NonNull  = (isInteractive as boolean)
        this.setIsInteractive(isInteractive_NonNull)
    }
    get cancelTransition(): VoidCallback | undefined {
        return this.getCancelTransition()
    }
    set cancelTransition(cancelTransition: VoidCallback | undefined) {
        const cancelTransition_NonNull  = (cancelTransition as VoidCallback)
        this.setCancelTransition(cancelTransition_NonNull)
    }
    get updateTransition(): UpdateTransitionCallback | undefined {
        return this.getUpdateTransition()
    }
    set updateTransition(updateTransition: UpdateTransitionCallback | undefined) {
        const updateTransition_NonNull  = (updateTransition as UpdateTransitionCallback)
        this.setUpdateTransition(updateTransition_NonNull)
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, NavigationTransitionProxyInternal.getFinalizer())
    }
    constructor() {
        this(NavigationTransitionProxyInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavigationTransitionProxy_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): NavigationTransitionProxyInternal {
        return new NavigationTransitionProxyInternal(ptr)
    }
    public finishTransition(): void {
        this.finishTransition_serialize()
        return
    }
    private getFrom(): NavContentInfo {
        return this.getFrom_serialize()
    }
    private setFrom(from: NavContentInfo): void {
        const from_casted = from as (NavContentInfo)
        this.setFrom_serialize(from_casted)
        return
    }
    private getTo(): NavContentInfo {
        return this.getTo_serialize()
    }
    private setTo(to: NavContentInfo): void {
        const to_casted = to as (NavContentInfo)
        this.setTo_serialize(to_casted)
        return
    }
    private getIsInteractive(): boolean | undefined {
        return this.getIsInteractive_serialize()
    }
    private setIsInteractive(isInteractive: boolean | undefined): void {
        const isInteractive_casted = isInteractive as (boolean | undefined)
        this.setIsInteractive_serialize(isInteractive_casted)
        return
    }
    private getCancelTransition(): VoidCallback | undefined {
        return this.getCancelTransition_serialize()
    }
    private setCancelTransition(cancelTransition: VoidCallback | undefined): void {
        const cancelTransition_casted = cancelTransition as (VoidCallback | undefined)
        this.setCancelTransition_serialize(cancelTransition_casted)
        return
    }
    private getUpdateTransition(): UpdateTransitionCallback | undefined {
        return this.getUpdateTransition_serialize()
    }
    private setUpdateTransition(updateTransition: UpdateTransitionCallback | undefined): void {
        const updateTransition_casted = updateTransition as (UpdateTransitionCallback | undefined)
        this.setUpdateTransition_serialize(updateTransition_casted)
        return
    }
    finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private getFrom_serialize(): NavContentInfo {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getFrom(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : NavContentInfo = NavContentInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setFrom_serialize(from: NavContentInfo): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavContentInfo_serializer.write(thisSerializer, from)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setFrom(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTo_serialize(): NavContentInfo {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getTo(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : NavContentInfo = NavContentInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setTo_serialize(to: NavContentInfo): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavContentInfo_serializer.write(thisSerializer, to)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsInteractive_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getIsInteractive(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private setIsInteractive_serialize(isInteractive: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (isInteractive !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isInteractiveTmpValue  = isInteractive!
            thisSerializer.writeBoolean(isInteractiveTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setIsInteractive(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getCancelTransition_serialize(): VoidCallback | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getCancelTransition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : VoidCallback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_BufResource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer_BufCall : KPointer = retvalDeserializer.readPointer()
            const buffer_BufCallSync : KPointer = retvalDeserializer.readPointer()
            buffer = ():void => {
                const buffer_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                buffer_BufArgsSerializer.writeInt32(buffer_BufResource.resourceId);
                buffer_BufArgsSerializer.writePointer(buffer_BufCall);
                buffer_BufArgsSerializer.writePointer(buffer_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -2038961969, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
                buffer_BufArgsSerializer.release();
                return;
            }
        }
        const returnResult : VoidCallback | undefined = buffer
        return returnResult
    }
    private setCancelTransition_serialize(cancelTransition: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (cancelTransition !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const cancelTransitionTmpValue  = cancelTransition!
            thisSerializer.holdAndWriteCallback(cancelTransitionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setCancelTransition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getUpdateTransition_serialize(): UpdateTransitionCallback | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getUpdateTransition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : UpdateTransitionCallback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_BufResource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer_BufCall : KPointer = retvalDeserializer.readPointer()
            const buffer_BufCallSync : KPointer = retvalDeserializer.readPointer()
            buffer = (progress: double):void => {
                const buffer_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                buffer_BufArgsSerializer.writeInt32(buffer_BufResource.resourceId);
                buffer_BufArgsSerializer.writePointer(buffer_BufCall);
                buffer_BufArgsSerializer.writePointer(buffer_BufCallSync);
                buffer_BufArgsSerializer.writeFloat64(progress);
                InteropNativeModule._CallCallbackSync(10, -448105339, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
                buffer_BufArgsSerializer.release();
                return;
            }
        }
        const returnResult : UpdateTransitionCallback | undefined = buffer
        return returnResult
    }
    private setUpdateTransition_serialize(updateTransition: UpdateTransitionCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (updateTransition !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const updateTransitionTmpValue  = updateTransition!
            thisSerializer.holdAndWriteCallback(updateTransitionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setUpdateTransition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class NavPathInfoInternal {
    public static fromPtr(ptr: KPointer): NavPathInfo {
        return new NavPathInfo(false, false, false, false, ptr)
    }
}
export class NavPathInfo implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get name(): string {
        return this.getName()
    }
    set name(name: string) {
        this.setName(name)
    }
    get param(): Object | null | undefined {
        return this.getParam()
    }
    set param(param: Object | null | undefined) {
        const param_NonNull  = (param as Object | null | undefined)
        this.setParam(param_NonNull)
    }
    get onPop(): ((value0: PopInfo) => void) | undefined {
        return this.getOnPop()
    }
    set onPop(onPop: ((value0: PopInfo) => void) | undefined) {
        const onPop_NonNull  = (onPop as ((value0: PopInfo) => void) | undefined)
        this.setOnPop(onPop_NonNull)
    }
    get isEntry(): boolean | undefined {
        return this.getIsEntry()
    }
    set isEntry(isEntry: boolean | undefined) {
        const isEntry_NonNull  = (isEntry as boolean | undefined)
        this.setIsEntry(isEntry_NonNull)
    }
    get navDestinationId(): string | undefined {
        return this.getNavDestinationId()
    }
    set navDestinationId(navDestinationId: string | undefined) {
        const navDestinationId_NonNull  = (navDestinationId as string | undefined)
        this.setNavDestinationId(navDestinationId_NonNull)
    }
    constructor(_0: boolean, _1: boolean, _2: boolean, _3: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, NavPathInfo.getFinalizer())
    }
    constructor(name: string, param: Object | null | undefined, onPop?: ((value0: PopInfo) => void), isEntry?: boolean) {
        this(false, false, false, false, NavPathInfo.construct(name, param, onPop, isEntry))
    }
    static construct(name: string, param: Object | null | undefined, onPop?: ((value0: PopInfo) => void), isEntry?: boolean): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (param !== undefined && param !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const paramTmpValue  = param!
            thisSerializer.holdAndWriteObject(paramTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (onPop !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onPopTmpValue  = onPop!
            thisSerializer.holdAndWriteCallback(onPopTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (isEntry !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isEntryTmpValue  = isEntry!
            thisSerializer.writeBoolean(isEntryTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_construct(name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavPathInfo_getFinalizer()
    }
    private getName(): string {
        return this.getName_serialize()
    }
    private setName(name: string): void {
        const name_casted = name as (string)
        this.setName_serialize(name_casted)
        return
    }
    private getParam(): Object | null | undefined {
        return this.getParam_serialize()
    }
    private setParam(param: Object | null | undefined): void {
        const param_casted = param as (Object | null | undefined)
        this.setParam_serialize(param_casted)
        return
    }
    private getOnPop(): ((value0: PopInfo) => void) | undefined {
        return this.getOnPop_serialize()
    }
    private setOnPop(onPop: ((value0: PopInfo) => void) | undefined): void {
        const onPop_casted = onPop as (((value0: PopInfo) => void) | undefined)
        this.setOnPop_serialize(onPop_casted)
        return
    }
    private getIsEntry(): boolean | undefined {
        return this.getIsEntry_serialize()
    }
    private setIsEntry(isEntry: boolean | undefined): void {
        const isEntry_casted = isEntry as (boolean | undefined)
        this.setIsEntry_serialize(isEntry_casted)
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
    // instructive change begin
    updateNavPathInfo(): void {
        this.setName_serialize(this.name)
        this.setIsEntry_serialize(this.isEntry!)
        this.setNavDestinationId_serialize(this.navDestinationId!)
    }
    // instructive change end
    private getName_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getName(this.peer!.ptr)
        return retval
    }
    private setName_serialize(name: string): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setName(this.peer!.ptr, name)
    }
    private getParam_serialize(): Object | null | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getParam(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : Object | null | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (retvalDeserializer.readObject() as object)
        }
        const returnResult : Object | null | undefined = buffer
        return returnResult
    }
    private setParam_serialize(param: Object | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (param !== undefined && param !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const paramTmpValue  = param!
            thisSerializer.holdAndWriteObject(paramTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setParam(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnPop_serialize(): ((value0: PopInfo) => void) | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getOnPop(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ((value0: PopInfo) => void) | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_BufResource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer_BufCall : KPointer = retvalDeserializer.readPointer()
            const buffer_BufCallSync : KPointer = retvalDeserializer.readPointer()
            buffer = (value0: PopInfo):void => {
                const buffer_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                buffer_BufArgsSerializer.writeInt32(buffer_BufResource.resourceId);
                buffer_BufArgsSerializer.writePointer(buffer_BufCall);
                buffer_BufArgsSerializer.writePointer(buffer_BufCallSync);
                PopInfo_serializer.write(buffer_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, 624053870, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
                buffer_BufArgsSerializer.release();
                return;
            }
        }
        const returnResult : ((value0: PopInfo) => void) | undefined = buffer
        return returnResult
    }
    private setOnPop_serialize(onPop: ((value0: PopInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (onPop !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onPopTmpValue  = onPop!
            thisSerializer.holdAndWriteCallback(onPopTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setOnPop(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsEntry_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getIsEntry(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private setIsEntry_serialize(isEntry: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (isEntry !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isEntryTmpValue  = isEntry!
            thisSerializer.writeBoolean(isEntryTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setIsEntry(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getNavDestinationId_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getNavDestinationId(this.peer!.ptr)
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
        ArkUIGeneratedNativeModule._NavPathInfo_setNavDestinationId(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class NavPathStackInternal {
    public static fromPtr(ptr: KPointer): NavPathStack {
        return new NavPathStack(ptr)
    }
}
export class NavPathStack implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, NavPathStack.getFinalizer())
    }
    constructor() {
        this(NavPathStack.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavPathStack_getFinalizer()
    }
    public pushPath(info: NavPathInfo, animated?: boolean): void {
        const info_casted = info as (NavPathInfo)
        const animated_casted = animated as (boolean | undefined)
        this.pushPath0_serialize(info_casted, animated_casted)
        return
    }
    public pushPath(info: NavPathInfo, options?: NavigationOptions): void {
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions | undefined)
        this.pushPath1_serialize(info_casted, options_casted)
        return
    }
    public pushDestination(info: NavPathInfo, animated?: boolean): Promise<void> {
        const info_casted = info as (NavPathInfo)
        const animated_casted = animated as (boolean | undefined)
        return this.pushDestination0_serialize(info_casted, animated_casted)
    }
    public pushDestination(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions | undefined)
        return this.pushDestination1_serialize(info_casted, options_casted)
    }
    public pushPathByName(name: string, param: Object | null | undefined, animated?: boolean): void {
        const name_casted = name as (string)
        const param_casted = param as (Object | null | undefined)
        const animated_casted = animated as (boolean | undefined)
        this.pushPathByName0_serialize(name_casted, param_casted, animated_casted)
        return
    }
    public pushPathByName(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): void {
        const name_casted = name as (string)
        const param_casted = param as (Object)
        const onPop_casted = onPop as (((value0: PopInfo) => void))
        const animated_casted = animated as (boolean | undefined)
        this.pushPathByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
        return
    }
    public pushDestinationByName(name: string, param: Object, animated?: boolean): Promise<void> {
        const name_casted = name as (string)
        const param_casted = param as (Object)
        const animated_casted = animated as (boolean | undefined)
        return this.pushDestinationByName0_serialize(name_casted, param_casted, animated_casted)
    }
    public pushDestinationByName(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): Promise<void> {
        const name_casted = name as (string)
        const param_casted = param as (Object)
        const onPop_casted = onPop as (((value0: PopInfo) => void))
        const animated_casted = animated as (boolean | undefined)
        return this.pushDestinationByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
    }
    public replacePath(info: NavPathInfo, animated?: boolean): void {
        const info_casted = info as (NavPathInfo)
        const animated_casted = animated as (boolean | undefined)
        this.replacePath0_serialize(info_casted, animated_casted)
        return
    }
    public replacePath(info: NavPathInfo, options?: NavigationOptions): void {
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions | undefined)
        this.replacePath1_serialize(info_casted, options_casted)
        return
    }
    public replaceDestination(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions | undefined)
        return this.replaceDestination_serialize(info_casted, options_casted)
    }
    public replacePathByName(name: string, param: Object, animated?: boolean): void {
        const name_casted = name as (string)
        const param_casted = param as (Object)
        const animated_casted = animated as (boolean | undefined)
        this.replacePathByName_serialize(name_casted, param_casted, animated_casted)
        return
    }
    public removeByIndexes(indexes: Array<int32>): int32 {
        const indexes_casted = indexes as (Array<int32>)
        return this.removeByIndexes_serialize(indexes_casted)
    }
    public removeByName(name: string): int32 {
        const name_casted = name as (string)
        return this.removeByName_serialize(name_casted)
    }
    public removeByNavDestinationId(navDestinationId: string): boolean {
        const navDestinationId_casted = navDestinationId as (string)
        return this.removeByNavDestinationId_serialize(navDestinationId_casted)
    }
    public pop(animated?: boolean): NavPathInfo | undefined {
        const animated_casted = animated as (boolean | undefined)
        return this.pop0_serialize(animated_casted)
    }
    public pop(result: Object, animated?: boolean): NavPathInfo | undefined {
        const result_casted = result as (Object)
        const animated_casted = animated as (boolean | undefined)
        return this.pop1_serialize(result_casted, animated_casted)
    }
    public popToName(name: string, animated?: boolean): int32 {
        const name_casted = name as (string)
        const animated_casted = animated as (boolean | undefined)
        return this.popToName0_serialize(name_casted, animated_casted)
    }
    public popToName(name: string, result: Object, animated?: boolean): int32 {
        const name_casted = name as (string)
        const result_casted = result as (Object)
        const animated_casted = animated as (boolean | undefined)
        return this.popToName1_serialize(name_casted, result_casted, animated_casted)
    }
    public popToIndex(index: int32, animated?: boolean): void {
        const index_casted = index as (int32)
        const animated_casted = animated as (boolean | undefined)
        this.popToIndex0_serialize(index_casted, animated_casted)
        return
    }
    public popToIndex(index: int32, result: Object, animated?: boolean): void {
        const index_casted = index as (int32)
        const result_casted = result as (Object)
        const animated_casted = animated as (boolean | undefined)
        this.popToIndex1_serialize(index_casted, result_casted, animated_casted)
        return
    }
    public moveToTop(name: string, animated?: boolean): int32 {
        const name_casted = name as (string)
        const animated_casted = animated as (boolean | undefined)
        return this.moveToTop_serialize(name_casted, animated_casted)
    }
    public moveIndexToTop(index: int32, animated?: boolean): void {
        const index_casted = index as (int32)
        const animated_casted = animated as (boolean | undefined)
        this.moveIndexToTop_serialize(index_casted, animated_casted)
        return
    }
    public clear(animated?: boolean): void {
        const animated_casted = animated as (boolean | undefined)
        this.clear_serialize(animated_casted)
        return
    }
    public getAllPathName(): Array<string> {
        return this.getAllPathName_serialize()
    }
    public getParamByIndex(index: int32): Object | null | undefined {
        const index_casted = index as (int32)
        return this.getParamByIndex_serialize(index_casted)
    }
    public getParamByName(name: string): Array<Object | null | undefined> {
        const name_casted = name as (string)
        return this.getParamByName_serialize(name_casted)
    }
    public getIndexByName(name: string): Array<int32> {
        const name_casted = name as (string)
        return this.getIndexByName_serialize(name_casted)
    }
    public getParent(): NavPathStack | null {
        return this.getParent_serialize()
    }
    public size(): int32 {
        return this.size_serialize()
    }
    public disableAnimation(value: boolean): void {
        const value_casted = value as (boolean)
        this.disableAnimation_serialize(value_casted)
        return
    }
    public setInterception(interception: NavigationInterception): void {
        const interception_casted = interception as (NavigationInterception)
        this.setInterception_serialize(interception_casted)
        return
    }
    public getPathStack(): Array<NavPathInfo> {
        return this.getPathStack_serialize()
    }
    public setPathStack(pathStack: Array<NavPathInfo>, animated?: boolean): void {
        const pathStack_casted = pathStack as (Array<NavPathInfo>)
        const animated_casted = animated as (boolean | undefined)
        this.setPathStack_serialize(pathStack_casted, animated_casted)
        return
    }
    pushPath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pushPath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            NavigationOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pushDestination0_serialize(info: NavPathInfo, animated?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    pushDestination1_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            NavigationOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    pushPathByName0_serialize(name: string, param: Object | null | undefined, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (param !== undefined && param !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const paramTmpValue  = param!
            thisSerializer.holdAndWriteObject(paramTmpValue)
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
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pushPathByName1_serialize(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        thisSerializer.holdAndWriteCallback(onPop)
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    pushDestinationByName0_serialize(name: string, param: Object, animated?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    pushDestinationByName1_serialize(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        thisSerializer.holdAndWriteCallback(onPop)
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    replacePath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    replacePath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            NavigationOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    replaceDestination_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            NavigationOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_replaceDestination(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    replacePathByName_serialize(name: string, param: Object, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePathByName(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    removeByIndexes_serialize(indexes: Array<int32>): int32 {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((indexes.length).toInt())
        for (let indexesCounterI = 0; indexesCounterI < indexes.length; indexesCounterI++) {
            const indexesTmpElement : int32 = indexes[indexesCounterI]
            thisSerializer.writeInt32(indexesTmpElement)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByIndexes(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    removeByName_serialize(name: string): int32 {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByName(this.peer!.ptr, name)
        return retval
    }
    removeByNavDestinationId_serialize(navDestinationId: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByNavDestinationId(this.peer!.ptr, navDestinationId)
        return retval
    }
    pop0_serialize(animated?: boolean): NavPathInfo | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : NavPathInfo | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (NavPathInfo_serializer.read(retvalDeserializer) as NavPathInfo)
        }
        const returnResult : NavPathInfo | undefined = buffer
        return returnResult
    }
    pop1_serialize(result: Object, animated?: boolean): NavPathInfo | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(result)
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : NavPathInfo | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (NavPathInfo_serializer.read(retvalDeserializer) as NavPathInfo)
        }
        const returnResult : NavPathInfo | undefined = buffer
        return returnResult
    }
    popToName0_serialize(name: string, animated?: boolean): int32 {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_popToName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    popToName1_serialize(name: string, result: Object, animated?: boolean): int32 {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(result)
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_popToName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    popToIndex0_serialize(index: int32, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex0(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popToIndex1_serialize(index: int32, result: Object, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(result)
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex1(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    moveToTop_serialize(name: string, animated?: boolean): int32 {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_moveToTop(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    moveIndexToTop_serialize(index: int32, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_moveIndexToTop(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    clear_serialize(animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_clear(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    getAllPathName_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getAllPathName(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    getParamByIndex_serialize(index: int32): Object | null | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParamByIndex(this.peer!.ptr, index)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : Object | null | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (retvalDeserializer.readObject() as object)
        }
        const returnResult : Object | null | undefined = buffer
        return returnResult
    }
    getParamByName_serialize(name: string): Array<Object | null | undefined> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParamByName(this.peer!.ptr, name)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Object | null | undefined> = new Array<Object | null | undefined>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            const bufferTempBuf_runtimeType  = retvalDeserializer.readInt8().toInt()
            let bufferTempBuf : Object | null | undefined = undefined
            if ((bufferTempBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
                bufferTempBuf = (retvalDeserializer.readObject() as object)
            }
            buffer[bufferBufCounterI] = bufferTempBuf
        }
        const returnResult : Array<Object | null | undefined> = buffer
        return returnResult
    }
    getIndexByName_serialize(name: string): Array<int32> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getIndexByName(this.peer!.ptr, name)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<int32> = new Array<int32>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = retvalDeserializer.readInt32()
        }
        const returnResult : Array<int32> = buffer
        return returnResult
    }
    getParent_serialize(): NavPathStack | null {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParent(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : NavPathStack | null = null
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (NavPathStack_serializer.read(retvalDeserializer) as NavPathStack)
        }
        const returnResult : NavPathStack | null = buffer
        return returnResult
    }
    size_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_size(this.peer!.ptr)
        return retval
    }
    disableAnimation_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._NavPathStack_disableAnimation(this.peer!.ptr, value ? 1 : 0)
    }
    setInterception_serialize(interception: NavigationInterception): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationInterception_serializer.write(thisSerializer, interception)
        ArkUIGeneratedNativeModule._NavPathStack_setInterception(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    getPathStack_serialize(): Array<NavPathInfo> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getPathStack(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<NavPathInfo> = new Array<NavPathInfo>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (NavPathInfo_serializer.read(retvalDeserializer) as NavPathInfo)
        }
        const returnResult : Array<NavPathInfo> = buffer
        return returnResult
    }
    setPathStack_serialize(pathStack: Array<NavPathInfo>, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((pathStack.length).toInt())
        for (let pathStackCounterI = 0; pathStackCounterI < pathStack.length; pathStackCounterI++) {
            const pathStackTmpElement : NavPathInfo = pathStack[pathStackCounterI]
            NavPathInfo_serializer.write(thisSerializer, pathStackTmpElement)
        }
        if (animated !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const animatedTmpValue  = animated!
            thisSerializer.writeBoolean(animatedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavPathStack_setPathStack(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkNavigationPeer extends ArkCommonMethodPeer {
    attributeSet?: NavigationModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavigationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Navigation_construct(peerId, flags)
        const _peer  = new ArkNavigationPeer(_peerPtr, peerId, 'Navigation', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavigationOptionsAttribute(pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (pathInfos !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const pathInfosTmpValue  = pathInfos!
            NavPathStack_serializer.write(thisSerializer, pathInfosTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (moduleInfo !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const moduleInfoTmpValue  = moduleInfo!
            NavigationModuleInfo_serializer.write(thisSerializer, moduleInfoTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNavBarWidthAttribute(value: Length | Bindable<Length> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Length) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Length
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof Bindable<Length>) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<Length>
                Bindable_Arkui_Component_Units_Length_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setNavBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNavBarPositionAttribute(value: NavBarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as NavBarPosition)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setNavBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNavBarWidthRangeAttribute(value: [ Dimension, Dimension ] | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            const valueTmpValue_0  = valueTmpValue[0]
            if (valueTmpValue_0 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValue_0ForIdx0  = valueTmpValue_0 as string
                thisSerializer.writeString(valueTmpValue_0ForIdx0)
            } else if (valueTmpValue_0 instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValue_0ForIdx1  = valueTmpValue_0 as number
                thisSerializer.writeNumber(valueTmpValue_0ForIdx1)
            } else if (valueTmpValue_0 instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValue_0ForIdx2  = valueTmpValue_0 as Resource
                Resource_serializer.write(thisSerializer, valueTmpValue_0ForIdx2)
            }
            const valueTmpValue_1  = valueTmpValue[1]
            if (valueTmpValue_1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValue_1ForIdx0  = valueTmpValue_1 as string
                thisSerializer.writeString(valueTmpValue_1ForIdx0)
            } else if (valueTmpValue_1 instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValue_1ForIdx1  = valueTmpValue_1 as number
                thisSerializer.writeNumber(valueTmpValue_1ForIdx1)
            } else if (valueTmpValue_1 instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValue_1ForIdx2  = valueTmpValue_1 as Resource
                Resource_serializer.write(thisSerializer, valueTmpValue_1ForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setNavBarWidthRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinContentWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setMinContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setModeAttribute(value: NavigationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as NavigationMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideNavBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideNavBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideTitleBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideBackButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTitleModeAttribute(value: NavigationTitleMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as NavigationTitleMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setTitleMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideToolBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideToolBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableToolBarAdaptationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setEnableToolBarAdaptation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTitleModeChangeAttribute(value: ((titleMode: NavigationTitleMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setOnTitleModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNavBarStateChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setOnNavBarStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNavigationModeChangeAttribute(value: ((mode: NavigationMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setOnNavigationModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomNavContentTransitionAttribute(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setCustomNavContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setSystemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setRecoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDragBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setEnableDragBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableModeChangeAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setEnableModeChangeAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackButtonIconAttribute(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (icon !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const iconTmpValue  = icon!
            if (iconTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const iconTmpValueForIdx0  = iconTmpValue as string
                thisSerializer.writeString(iconTmpValueForIdx0)
            } else if (iconTmpValue instanceof image.PixelMap) {
                thisSerializer.writeInt8((1).toByte())
                const iconTmpValueForIdx1  = iconTmpValue as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, iconTmpValueForIdx1)
            } else if (iconTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const iconTmpValueForIdx2  = iconTmpValue as Resource
                Resource_serializer.write(thisSerializer, iconTmpValueForIdx2)
            } else if (iconTmpValue instanceof SymbolGlyphModifier) {
                thisSerializer.writeInt8((3).toByte())
                const iconTmpValueForIdx3  = iconTmpValue as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, iconTmpValueForIdx3)
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setBackButtonIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTitleAttribute(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ResourceStr) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceStr
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx1)
                }
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx1))
            } else if (valueTmpValue instanceof NavigationCommonTitle) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as NavigationCommonTitle
                NavigationCommonTitle_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof NavigationCustomTitle) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as NavigationCustomTitle
                NavigationCustomTitle_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setTitle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideTitleBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setMenus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setToolbarConfigurationAttribute(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (TypeChecker.isArray_ToolbarItem(valueTmpValue)) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Array<ToolbarItem>
                thisSerializer.writeInt32((valueTmpValueForIdx0.length).toInt())
                for (let valueTmpValueForIdx0CounterI = 0; valueTmpValueForIdx0CounterI < valueTmpValueForIdx0.length; valueTmpValueForIdx0CounterI++) {
                    const valueTmpValueForIdx0TmpElement : ToolbarItem = valueTmpValueForIdx0[valueTmpValueForIdx0CounterI]
                    ToolbarItem_serializer.write(thisSerializer, valueTmpValueForIdx0TmpElement)
                }
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx1))
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setToolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideToolBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideToolBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setIgnoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type SystemBarStyle = window.SystemBarStyle;
export interface NavigationCommonTitle {
    main: string | Resource | undefined;
    sub: string | Resource | undefined;
}
export interface NavigationCustomTitle {
    builder: CustomBuilder;
    height: TitleHeight | Length;
}
export enum NavigationMode {
    STACK = 0,
    Stack = 0,
    SPLIT = 1,
    Split = 1,
    AUTO = 2,
    Auto = 2
}
export enum NavBarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export enum NavigationTitleMode {
    FREE = 0,
    Free = 0,
    FULL = 1,
    Full = 1,
    MINI = 2,
    Mini = 2
}
export interface NavigationMenuItem {
    value: string | Resource;
    icon?: string | Resource;
    symbolIcon?: SymbolGlyphModifier;
    isEnabled?: boolean;
    action?: (() => void);
}
export interface PopInfo {
    info: NavPathInfo;
    result: Object;
}
export enum LaunchMode {
    STANDARD = 0,
    MOVE_TO_TOP_SINGLETON = 1,
    POP_TO_SINGLETON = 2,
    NEW_INSTANCE = 3
}
export interface NavigationOptions {
    launchMode?: LaunchMode;
    animated?: boolean;
}
export type NavBar = string;
export type InterceptionShowCallback = (from: NavDestinationContext | NavBar, to: NavDestinationContext | NavBar, operation: NavigationOperation, isAnimated: boolean) => void;
export type InterceptionModeCallback = (mode: NavigationMode) => void;
export interface NavigationInterception {
    willShow?: InterceptionShowCallback;
    didShow?: InterceptionShowCallback;
    modeChange?: InterceptionModeCallback;
}
export enum ToolbarItemStatus {
    NORMAL = 0,
    DISABLED = 1,
    ACTIVE = 2
}
export enum NavigationOperation {
    PUSH = 1,
    POP = 2,
    REPLACE = 3
}
export interface ToolbarItem {
    value: ResourceStr | undefined;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    action?: (() => void);
    status?: ToolbarItemStatus;
    activeIcon?: ResourceStr;
    activeSymbolIcon?: SymbolGlyphModifier;
}
export interface NavigationTitleOptions {
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    barStyle?: BarStyle;
    paddingStart?: LengthMetrics;
    paddingEnd?: LengthMetrics;
    mainTitleModifier?: TextModifier;
    subTitleModifier?: TextModifier;
    enableHoverMode?: boolean;
}
export enum BarStyle {
    STANDARD = 0,
    STACK = 1,
    SAFE_AREA_PADDING = 2
}
export interface NavigationToolbarOptions {
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    moreButtonOptions?: MoreButtonOptions;
    barStyle?: BarStyle;
    hideItemValue?: boolean;
}
export interface NavigationMenuOptions {
    moreButtonOptions?: MoreButtonOptions;
}
export interface MoreButtonOptions {
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
}
export interface NavigationAttribute extends CommonMethod {
    setNavigationOptions(pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): this {
        throw new Error("Unimplemented method setNavigationOptions")
    }
    navBarWidth(value: Length | Bindable<Length> | undefined): this {
        throw new Error("Unimplemented method navBarWidth")
    }
    navBarPosition(value: NavBarPosition | undefined): this {
        throw new Error("Unimplemented method navBarPosition")
    }
    navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        throw new Error("Unimplemented method navBarWidthRange")
    }
    minContentWidth(value: Dimension | undefined): this {
        throw new Error("Unimplemented method minContentWidth")
    }
    mode(value: NavigationMode | undefined): this {
        throw new Error("Unimplemented method mode")
    }
    hideNavBar(value: boolean | undefined): this {
        throw new Error("Unimplemented method hideNavBar")
    }
    hideTitleBar(value: boolean | undefined): this {
        throw new Error("Unimplemented method hideTitleBar")
    }
    hideBackButton(value: boolean | undefined): this {
        throw new Error("Unimplemented method hideBackButton")
    }
    titleMode(value: NavigationTitleMode | undefined): this {
        throw new Error("Unimplemented method titleMode")
    }
    hideToolBar(value: boolean | undefined): this {
        throw new Error("Unimplemented method hideToolBar")
    }
    enableToolBarAdaptation(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableToolBarAdaptation")
    }
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        throw new Error("Unimplemented method onTitleModeChange")
    }
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onNavBarStateChange")
    }
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        throw new Error("Unimplemented method onNavigationModeChange")
    }
    navDestination(value: PageMapBuilder | undefined): this {
        throw new Error("Unimplemented method navDestination")
    }
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        throw new Error("Unimplemented method customNavContentTransition")
    }
    systemBarStyle(value: window.SystemBarStyle | undefined): this {
        throw new Error("Unimplemented method systemBarStyle")
    }
    recoverable(value: boolean | undefined): this {
        throw new Error("Unimplemented method recoverable")
    }
    enableDragBar(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableDragBar")
    }
    enableModeChangeAnimation(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableModeChangeAnimation")
    }
    backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        throw new Error("Unimplemented method backButtonIcon")
    }
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        throw new Error("Unimplemented method title")
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        throw new Error("Unimplemented method hideTitleBar")
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        throw new Error("Unimplemented method menus")
    }
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        throw new Error("Unimplemented method toolbarConfiguration")
    }
    hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this {
        throw new Error("Unimplemented method hideToolBar")
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        throw new Error("Unimplemented method ignoreLayoutSafeArea")
    }
    attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkNavigationStyle extends ArkCommonMethodStyle implements NavigationAttribute {
    navBarWidth_value?: Length | Bindable<Length> | undefined
    navBarPosition_value?: NavBarPosition | undefined
    navBarWidthRange_value?: [ Dimension, Dimension ] | undefined
    minContentWidth_value?: Dimension | undefined
    mode_value?: NavigationMode | undefined
    hideNavBar_value?: boolean | undefined
    hideTitleBar_value?: boolean | undefined
    hideBackButton_value?: boolean | undefined
    titleMode_value?: NavigationTitleMode | undefined
    hideToolBar_value?: boolean | undefined
    enableToolBarAdaptation_value?: boolean | undefined
    onTitleModeChange_value?: ((titleMode: NavigationTitleMode) => void) | undefined
    onNavBarStateChange_value?: ((isVisible: boolean) => void) | undefined
    onNavigationModeChange_value?: ((mode: NavigationMode) => void) | undefined
    navDestination_value?: PageMapBuilder | undefined
    customNavContentTransition_value?: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined
    systemBarStyle_value?: window.SystemBarStyle | undefined
    recoverable_value?: boolean | undefined
    enableDragBar_value?: boolean | undefined
    enableModeChangeAnimation_value?: boolean | undefined
    setNavigationOptions(pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): this {
        return this
    }
    navBarWidth(value: Length | Bindable<Length> | undefined): this {
        return this
    }
    navBarPosition(value: NavBarPosition | undefined): this {
        return this
    }
    navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        return this
    }
    minContentWidth(value: Dimension | undefined): this {
        return this
    }
    mode(value: NavigationMode | undefined): this {
        return this
    }
    hideNavBar(value: boolean | undefined): this {
        return this
    }
    hideTitleBar(value: boolean | undefined): this {
        return this
    }
    hideBackButton(value: boolean | undefined): this {
        return this
    }
    titleMode(value: NavigationTitleMode | undefined): this {
        return this
    }
    hideToolBar(value: boolean | undefined): this {
        return this
    }
    enableToolBarAdaptation(value: boolean | undefined): this {
        return this
    }
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        return this
    }
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        return this
    }
    navDestination(value: PageMapBuilder | undefined): this {
        return this
    }
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        return this
    }
    systemBarStyle(value: window.SystemBarStyle | undefined): this {
        return this
    }
    recoverable(value: boolean | undefined): this {
        return this
    }
    enableDragBar(value: boolean | undefined): this {
        return this
    }
    enableModeChangeAnimation(value: boolean | undefined): this {
        return this
    }
    backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        return this
    }
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        return this
    }
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        return this
    }
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        return this
    }
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        return this
    }
    hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this {
        return this
    }
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface NavigationAnimatedTransition {
    onTransitionEnd?: ((isVisible: boolean) => void);
    timeout?: int32;
    isInteractive?: boolean;
    transition: ((transitionProxy: NavigationTransitionProxy) => void);
}
export type UpdateTransitionCallback = (progress: double) => void;
export interface NavContentInfo {
    name?: string;
    index: int32;
    mode?: NavDestinationMode;
    param?: Object;
    navDestinationId?: string;
}
export interface NavigationModuleInfo {
    moduleName: string;
    pagePath: string;
    isUserCreateStack?: boolean;
}

export class ArkNavigationComponent extends ArkCommonMethodComponent implements NavigationAttribute {
    // instructive change begin
    /** @memo */
    _navDestination: (name: string, param: Object | null | undefined) => void =
        /** @memo */
        (name: string, param: object | null | undefined) => {
            InteropNativeModule._NativeLog("_navDestination attribute is undefined")
        }
    _needSync: boolean = false
    // instructive change end
    getPeer(): ArkNavigationPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkNavigationPeer)
    }
    public setNavigationOptions(pathInfos?: NavPathStack, moduleInfo?: NavigationModuleInfo): this {
        if (this.checkPriority("setNavigationOptions")) {
            hookSetNavigationOptions(this, pathInfos, moduleInfo)
        }
        return this
    }
    public navBarWidth(value: Length | Bindable<Length> | undefined): this {
        if (this.checkPriority("navBarWidth")) {
            const value_casted = value as (Length | Bindable<Length> | undefined)
            this.getPeer()?.setNavBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public navBarPosition(value: NavBarPosition | undefined): this {
        if (this.checkPriority("navBarPosition")) {
            const value_casted = value as (NavBarPosition | undefined)
            this.getPeer()?.setNavBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        if (this.checkPriority("navBarWidthRange")) {
            const value_casted = value as ([ Dimension, Dimension ] | undefined)
            this.getPeer()?.setNavBarWidthRangeAttribute(value_casted)
            return this
        }
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setMinContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public mode(value: NavigationMode | undefined): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavigationMode | undefined)
            this.getPeer()?.setModeAttribute(value_casted)
            return this
        }
        return this
    }
    public hideNavBar(value: boolean | undefined): this {
        if (this.checkPriority("hideNavBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHideNavBarAttribute(value_casted)
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
    public titleMode(value: NavigationTitleMode | undefined): this {
        if (this.checkPriority("titleMode")) {
            const value_casted = value as (NavigationTitleMode | undefined)
            this.getPeer()?.setTitleModeAttribute(value_casted)
            return this
        }
        return this
    }
    public hideToolBar(value: boolean | undefined): this {
        if (this.checkPriority("hideToolBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHideToolBar0Attribute(value_casted)
            return this
        }
        return this
    }
    public enableToolBarAdaptation(value: boolean | undefined): this {
        if (this.checkPriority("enableToolBarAdaptation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableToolBarAdaptationAttribute(value_casted)
            return this
        }
        return this
    }
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        if (this.checkPriority("onTitleModeChange")) {
            const value_casted = value as (((titleMode: NavigationTitleMode) => void) | undefined)
            this.getPeer()?.setOnTitleModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onNavBarStateChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.setOnNavBarStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        if (this.checkPriority("onNavigationModeChange")) {
            const value_casted = value as (((mode: NavigationMode) => void) | undefined)
            this.getPeer()?.setOnNavigationModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public navDestination(value: PageMapBuilder | undefined): this {
        if (this.checkPriority("navDestination")) {
            hookSetNavDestination(this, value)
        }
        return this
    }
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        if (this.checkPriority("customNavContentTransition")) {
            const value_casted = value as (((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined)
            this.getPeer()?.setCustomNavContentTransitionAttribute(value_casted)
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
    public enableDragBar(value: boolean | undefined): this {
        if (this.checkPriority("enableDragBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableDragBarAttribute(value_casted)
            return this
        }
        return this
    }
    public enableModeChangeAnimation(value: boolean | undefined): this {
        if (this.checkPriority("enableModeChangeAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableModeChangeAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (this.checkPriority("backButtonIcon")) {
            const icon_casted = icon as (string | image.PixelMap | Resource | SymbolGlyphModifier | undefined)
            const accessibilityText_casted = accessibilityText as (ResourceStr | undefined)
            this.getPeer()?.setBackButtonIconAttribute(icon_casted, accessibilityText_casted)
            return this
        }
        return this
    }
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined)
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
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (this.checkPriority("menus")) {
            const items_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationMenuOptions | undefined)
            this.getPeer()?.setMenusAttribute(items_casted, options_casted)
            return this
        }
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const value_casted = value as (Array<ToolbarItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.setToolbarConfigurationAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_casted = hide as (boolean | undefined)
            const animated_casted = animated as (boolean | undefined)
            this.getPeer()?.setHideToolBar1Attribute(hide_casted, animated_casted)
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
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookNavigationAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }

    // instructive change begin
    public updateNeedSync(needSync: boolean): void {
        this._needSync = needSync;
    }

    public isNeedSync(): boolean {
        return this._needSync;
    }

    public updateNavDestination(navdestination: PageMapBuilder): void {
        this._navDestination = navdestination;
    }
    // instructive change end
}

@memo
export function NavigationImpl(
    @memo
    style: ((attributes: NavigationAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkNavigationComponent>((): ArkNavigationComponent => {
        return new ArkNavigationComponent()
    })
    NodeAttach<ArkNavigationPeer>((): ArkNavigationPeer => ArkNavigationPeer.create(receiver), (peer: ArkNavigationPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class NavPathStack_serializer {
    public static write(buffer: SerializerBase, value: NavPathStack): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): NavPathStack {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return NavPathStackInternal.fromPtr(ptr)
    }
}
export class NavContentInfo_serializer {
    public static write(buffer: SerializerBase, value: NavContentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        if (valueHolderForName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNameTmpValue  = valueHolderForName!
            valueSerializer.writeString(valueHolderForNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndex  = value.index
        valueSerializer.writeInt32(valueHolderForIndex)
        const valueHolderForMode  = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue  = (valueHolderForMode as NavDestinationMode)
            valueSerializer.writeInt32(valueHolderForModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParam  = value.param
        if (valueHolderForParam !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamTmpValue  = valueHolderForParam!
            valueSerializer.holdAndWriteObject(valueHolderForParamTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNavDestinationId  = value.navDestinationId
        if (valueHolderForNavDestinationId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNavDestinationIdTmpValue  = valueHolderForNavDestinationId!
            valueSerializer.writeString(valueHolderForNavDestinationIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavContentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nameTmpBuf : string | undefined = undefined
        if ((nameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nameTmpBuf = (valueDeserializer.readString() as string)
        }
        const nameTmpResult : string | undefined = nameTmpBuf
        const indexTmpResult : int32 = valueDeserializer.readInt32()
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modeTmpBuf : NavDestinationMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = NavDestinationMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult : NavDestinationMode | undefined = modeTmpBuf
        const paramTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paramTmpBuf : Object | undefined = undefined
        if ((paramTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paramTmpBuf = (valueDeserializer.readObject() as object)
        }
        const paramTmpResult : Object | undefined = paramTmpBuf
        const navDestinationIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let navDestinationIdTmpBuf : string | undefined = undefined
        if ((navDestinationIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            navDestinationIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const navDestinationIdTmpResult : string | undefined = navDestinationIdTmpBuf
        let value : NavContentInfo = ({name: nameTmpResult, index: indexTmpResult, mode: modeTmpResult, param: paramTmpResult, navDestinationId: navDestinationIdTmpResult} as NavContentInfo)
        return value
    }
}
export class NavigationAnimatedTransition_serializer {
    public static write(buffer: SerializerBase, value: NavigationAnimatedTransition): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnTransitionEnd  = value.onTransitionEnd
        if (valueHolderForOnTransitionEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnTransitionEndTmpValue  = valueHolderForOnTransitionEnd!
            valueSerializer.holdAndWriteCallback(valueHolderForOnTransitionEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTimeout  = value.timeout
        if (valueHolderForTimeout !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeoutTmpValue  = valueHolderForTimeout!
            valueSerializer.writeInt32(valueHolderForTimeoutTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsInteractive  = value.isInteractive
        if (valueHolderForIsInteractive !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsInteractiveTmpValue  = valueHolderForIsInteractive!
            valueSerializer.writeBoolean(valueHolderForIsInteractiveTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTransition  = value.transition
        valueSerializer.holdAndWriteCallback(valueHolderForTransition)
    }
    public static read(buffer: DeserializerBase): NavigationAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const onTransitionEndTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onTransitionEndTmpBuf : ((isVisible: boolean) => void) | undefined = undefined
        if ((onTransitionEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onTransitionEndTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onTransitionEndTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onTransitionEndTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onTransitionEndTmpBuf = (isVisible: boolean):void => {
                const onTransitionEndTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onTransitionEndTmpBuf_BufArgsSerializer.writeInt32(onTransitionEndTmpBuf_BufResource.resourceId);
                onTransitionEndTmpBuf_BufArgsSerializer.writePointer(onTransitionEndTmpBuf_BufCall);
                onTransitionEndTmpBuf_BufArgsSerializer.writePointer(onTransitionEndTmpBuf_BufCallSync);
                onTransitionEndTmpBuf_BufArgsSerializer.writeBoolean(isVisible);
                InteropNativeModule._CallCallbackSync(10, 313269291, onTransitionEndTmpBuf_BufArgsSerializer.asBuffer(), onTransitionEndTmpBuf_BufArgsSerializer.length());
                onTransitionEndTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onTransitionEndTmpResult : ((isVisible: boolean) => void) | undefined = onTransitionEndTmpBuf
        const timeoutTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeoutTmpBuf : int32 | undefined = undefined
        if ((timeoutTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeoutTmpBuf = valueDeserializer.readInt32()
        }
        const timeoutTmpResult : int32 | undefined = timeoutTmpBuf
        const isInteractiveTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isInteractiveTmpBuf : boolean | undefined = undefined
        if ((isInteractiveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isInteractiveTmpBuf = valueDeserializer.readBoolean()
        }
        const isInteractiveTmpResult : boolean | undefined = isInteractiveTmpBuf
        const transitionTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const transitionTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const transitionTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const transitionTmpResult : ((transitionProxy: NavigationTransitionProxy) => void) = (transitionProxy: NavigationTransitionProxy):void => {
            const transitionTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            transitionTmpBufBufArgsSerializer.writeInt32(transitionTmpBufBufResource.resourceId);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCall);
            transitionTmpBufBufArgsSerializer.writePointer(transitionTmpBufBufCallSync);
            NavigationTransitionProxy_serializer.write(transitionTmpBufBufArgsSerializer, transitionProxy);
            InteropNativeModule._CallCallbackSync(10, -1375731066, transitionTmpBufBufArgsSerializer.asBuffer(), transitionTmpBufBufArgsSerializer.length());
            transitionTmpBufBufArgsSerializer.release();
            return;
        }
        let value : NavigationAnimatedTransition = ({onTransitionEnd: onTransitionEndTmpResult, timeout: timeoutTmpResult, isInteractive: isInteractiveTmpResult, transition: transitionTmpResult} as NavigationAnimatedTransition)
        return value
    }
}
export class NavigationInterception_serializer {
    public static write(buffer: SerializerBase, value: NavigationInterception): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWillShow  = value.willShow
        if (valueHolderForWillShow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWillShowTmpValue  = valueHolderForWillShow!
            valueSerializer.holdAndWriteCallback(valueHolderForWillShowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDidShow  = value.didShow
        if (valueHolderForDidShow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDidShowTmpValue  = valueHolderForDidShow!
            valueSerializer.holdAndWriteCallback(valueHolderForDidShowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForModeChange  = value.modeChange
        if (valueHolderForModeChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeChangeTmpValue  = valueHolderForModeChange!
            valueSerializer.holdAndWriteCallback(valueHolderForModeChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationInterception {
        let valueDeserializer : DeserializerBase = buffer
        const willShowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let willShowTmpBuf : InterceptionShowCallback | undefined = undefined
        if ((willShowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const willShowTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const willShowTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const willShowTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            willShowTmpBuf = (from: NavDestinationContext | NavBar, to: NavDestinationContext | NavBar, operation: NavigationOperation, isAnimated: boolean):void => {
                const willShowTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                willShowTmpBuf_BufArgsSerializer.writeInt32(willShowTmpBuf_BufResource.resourceId);
                willShowTmpBuf_BufArgsSerializer.writePointer(willShowTmpBuf_BufCall);
                willShowTmpBuf_BufArgsSerializer.writePointer(willShowTmpBuf_BufCallSync);
                if (from instanceof NavDestinationContext) {
                    willShowTmpBuf_BufArgsSerializer.writeInt8((0).toByte());
                    const fromForIdx0  = from as NavDestinationContext;
                    NavDestinationContext_serializer.write(willShowTmpBuf_BufArgsSerializer, fromForIdx0);
                } else if (from instanceof NavBar) {
                    willShowTmpBuf_BufArgsSerializer.writeInt8((1).toByte());
                    const fromForIdx1  = from as NavBar;
                    willShowTmpBuf_BufArgsSerializer.writeString(fromForIdx1);
                }
                if (to instanceof NavDestinationContext) {
                    willShowTmpBuf_BufArgsSerializer.writeInt8((0).toByte());
                    const toForIdx0  = to as NavDestinationContext;
                    NavDestinationContext_serializer.write(willShowTmpBuf_BufArgsSerializer, toForIdx0);
                } else if (to instanceof NavBar) {
                    willShowTmpBuf_BufArgsSerializer.writeInt8((1).toByte());
                    const toForIdx1  = to as NavBar;
                    willShowTmpBuf_BufArgsSerializer.writeString(toForIdx1);
                }
                willShowTmpBuf_BufArgsSerializer.writeInt32(operation.valueOf());
                willShowTmpBuf_BufArgsSerializer.writeBoolean(isAnimated);
                InteropNativeModule._CallCallbackSync(10, 1852781814, willShowTmpBuf_BufArgsSerializer.asBuffer(), willShowTmpBuf_BufArgsSerializer.length());
                willShowTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const willShowTmpResult : InterceptionShowCallback | undefined = willShowTmpBuf
        const didShowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let didShowTmpBuf : InterceptionShowCallback | undefined = undefined
        if ((didShowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const didShowTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const didShowTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const didShowTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            didShowTmpBuf = (from: NavDestinationContext | NavBar, to: NavDestinationContext | NavBar, operation: NavigationOperation, isAnimated: boolean):void => {
                const didShowTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                didShowTmpBuf_BufArgsSerializer.writeInt32(didShowTmpBuf_BufResource.resourceId);
                didShowTmpBuf_BufArgsSerializer.writePointer(didShowTmpBuf_BufCall);
                didShowTmpBuf_BufArgsSerializer.writePointer(didShowTmpBuf_BufCallSync);
                if (from instanceof NavDestinationContext) {
                    didShowTmpBuf_BufArgsSerializer.writeInt8((0).toByte());
                    const fromForIdx0  = from as NavDestinationContext;
                    NavDestinationContext_serializer.write(didShowTmpBuf_BufArgsSerializer, fromForIdx0);
                } else if (from instanceof NavBar) {
                    didShowTmpBuf_BufArgsSerializer.writeInt8((1).toByte());
                    const fromForIdx1  = from as NavBar;
                    didShowTmpBuf_BufArgsSerializer.writeString(fromForIdx1);
                }
                if (to instanceof NavDestinationContext) {
                    didShowTmpBuf_BufArgsSerializer.writeInt8((0).toByte());
                    const toForIdx0  = to as NavDestinationContext;
                    NavDestinationContext_serializer.write(didShowTmpBuf_BufArgsSerializer, toForIdx0);
                } else if (to instanceof NavBar) {
                    didShowTmpBuf_BufArgsSerializer.writeInt8((1).toByte());
                    const toForIdx1  = to as NavBar;
                    didShowTmpBuf_BufArgsSerializer.writeString(toForIdx1);
                }
                didShowTmpBuf_BufArgsSerializer.writeInt32(operation.valueOf());
                didShowTmpBuf_BufArgsSerializer.writeBoolean(isAnimated);
                InteropNativeModule._CallCallbackSync(10, 1852781814, didShowTmpBuf_BufArgsSerializer.asBuffer(), didShowTmpBuf_BufArgsSerializer.length());
                didShowTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const didShowTmpResult : InterceptionShowCallback | undefined = didShowTmpBuf
        const modeChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modeChangeTmpBuf : InterceptionModeCallback | undefined = undefined
        if ((modeChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const modeChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const modeChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const modeChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            modeChangeTmpBuf = (mode: NavigationMode):void => {
                const modeChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                modeChangeTmpBuf_BufArgsSerializer.writeInt32(modeChangeTmpBuf_BufResource.resourceId);
                modeChangeTmpBuf_BufArgsSerializer.writePointer(modeChangeTmpBuf_BufCall);
                modeChangeTmpBuf_BufArgsSerializer.writePointer(modeChangeTmpBuf_BufCallSync);
                modeChangeTmpBuf_BufArgsSerializer.writeInt32(mode.valueOf());
                InteropNativeModule._CallCallbackSync(10, 1502213270, modeChangeTmpBuf_BufArgsSerializer.asBuffer(), modeChangeTmpBuf_BufArgsSerializer.length());
                modeChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const modeChangeTmpResult : InterceptionModeCallback | undefined = modeChangeTmpBuf
        let value : NavigationInterception = ({willShow: willShowTmpResult, didShow: didShowTmpResult, modeChange: modeChangeTmpResult} as NavigationInterception)
        return value
    }
}
export class NavigationModuleInfo_serializer {
    public static write(buffer: SerializerBase, value: NavigationModuleInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForModuleName  = value.moduleName
        valueSerializer.writeString(valueHolderForModuleName)
        const valueHolderForPagePath  = value.pagePath
        valueSerializer.writeString(valueHolderForPagePath)
        const valueHolderForIsUserCreateStack  = value.isUserCreateStack
        if (valueHolderForIsUserCreateStack !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsUserCreateStackTmpValue  = valueHolderForIsUserCreateStack!
            valueSerializer.writeBoolean(valueHolderForIsUserCreateStackTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationModuleInfo {
        let valueDeserializer : DeserializerBase = buffer
        const moduleNameTmpResult : string = (valueDeserializer.readString() as string)
        const pagePathTmpResult : string = (valueDeserializer.readString() as string)
        const isUserCreateStackTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isUserCreateStackTmpBuf : boolean | undefined = undefined
        if ((isUserCreateStackTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isUserCreateStackTmpBuf = valueDeserializer.readBoolean()
        }
        const isUserCreateStackTmpResult : boolean | undefined = isUserCreateStackTmpBuf
        let value : NavigationModuleInfo = ({moduleName: moduleNameTmpResult, pagePath: pagePathTmpResult, isUserCreateStack: isUserCreateStackTmpResult} as NavigationModuleInfo)
        return value
    }
}
export class NavigationOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLaunchMode  = value.launchMode
        if (valueHolderForLaunchMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLaunchModeTmpValue  = (valueHolderForLaunchMode as LaunchMode)
            valueSerializer.writeInt32(valueHolderForLaunchModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAnimated  = value.animated
        if (valueHolderForAnimated !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAnimatedTmpValue  = valueHolderForAnimated!
            valueSerializer.writeBoolean(valueHolderForAnimatedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const launchModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let launchModeTmpBuf : LaunchMode | undefined = undefined
        if ((launchModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            launchModeTmpBuf = LaunchMode.fromValue(valueDeserializer.readInt32())
        }
        const launchModeTmpResult : LaunchMode | undefined = launchModeTmpBuf
        const animatedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let animatedTmpBuf : boolean | undefined = undefined
        if ((animatedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            animatedTmpBuf = valueDeserializer.readBoolean()
        }
        const animatedTmpResult : boolean | undefined = animatedTmpBuf
        let value : NavigationOptions = ({launchMode: launchModeTmpResult, animated: animatedTmpResult} as NavigationOptions)
        return value
    }
}
export class NavPathInfo_serializer {
    public static write(buffer: SerializerBase, value: NavPathInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): NavPathInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return NavPathInfoInternal.fromPtr(ptr)
    }
}
export class PopInfo_serializer {
    public static write(buffer: SerializerBase, value: PopInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForInfo  = value.info
        NavPathInfo_serializer.write(valueSerializer, valueHolderForInfo)
        const valueHolderForResult  = value.result
        valueSerializer.holdAndWriteObject(valueHolderForResult)
    }
    public static read(buffer: DeserializerBase): PopInfo {
        let valueDeserializer : DeserializerBase = buffer
        const infoTmpResult : NavPathInfo = (NavPathInfo_serializer.read(valueDeserializer) as NavPathInfo)
        const resultTmpResult : Object = (valueDeserializer.readObject() as object)
        let value : PopInfo = ({info: infoTmpResult, result: resultTmpResult} as PopInfo)
        return value
    }
}
export class NavigationCommonTitle_serializer {
    public static write(buffer: SerializerBase, value: NavigationCommonTitle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMain  = value.main
        if (valueHolderForMain !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMainTmpValue  = valueHolderForMain!
            if (valueHolderForMainTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMainTmpValueForIdx0  = valueHolderForMainTmpValue as string
                valueSerializer.writeString(valueHolderForMainTmpValueForIdx0)
            } else if (valueHolderForMainTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMainTmpValueForIdx1  = valueHolderForMainTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMainTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSub  = value.sub
        if (valueHolderForSub !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSubTmpValue  = valueHolderForSub!
            if (valueHolderForSubTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSubTmpValueForIdx0  = valueHolderForSubTmpValue as string
                valueSerializer.writeString(valueHolderForSubTmpValueForIdx0)
            } else if (valueHolderForSubTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSubTmpValueForIdx1  = valueHolderForSubTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSubTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationCommonTitle {
        let valueDeserializer : DeserializerBase = buffer
        const mainTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mainTmpBuf : string | Resource | undefined = undefined
        if ((mainTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const mainTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let mainTmpBuf_ : string | Resource | undefined
            if (mainTmpBuf_UnionSelector == (0).toChar()) {
                mainTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (mainTmpBuf_UnionSelector == (1).toChar()) {
                mainTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for mainTmpBuf_ has to be chosen through deserialisation.")
            }
            mainTmpBuf = (mainTmpBuf_ as string | Resource)
        }
        const mainTmpResult : string | Resource | undefined = mainTmpBuf
        const subTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let subTmpBuf : string | Resource | undefined = undefined
        if ((subTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const subTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let subTmpBuf_ : string | Resource | undefined
            if (subTmpBuf_UnionSelector == (0).toChar()) {
                subTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (subTmpBuf_UnionSelector == (1).toChar()) {
                subTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for subTmpBuf_ has to be chosen through deserialisation.")
            }
            subTmpBuf = (subTmpBuf_ as string | Resource)
        }
        const subTmpResult : string | Resource | undefined = subTmpBuf
        let value : NavigationCommonTitle = ({main: mainTmpResult, sub: subTmpResult} as NavigationCommonTitle)
        return value
    }
}
export class NavigationMenuItem_serializer {
    public static write(buffer: SerializerBase, value: NavigationMenuItem): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForValueForIdx0  = valueHolderForValue as string
            valueSerializer.writeString(valueHolderForValueForIdx0)
        } else if (valueHolderForValue instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForValueForIdx1  = valueHolderForValue as Resource
            Resource_serializer.write(valueSerializer, valueHolderForValueForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolIcon  = value.symbolIcon
        if (valueHolderForSymbolIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolIconTmpValue  = valueHolderForSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForSymbolIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsEnabled  = value.isEnabled
        if (valueHolderForIsEnabled !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsEnabledTmpValue  = valueHolderForIsEnabled!
            valueSerializer.writeBoolean(valueHolderForIsEnabledTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAction  = value.action
        if (valueHolderForAction !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForActionTmpValue  = valueHolderForAction!
            valueSerializer.holdAndWriteCallback(valueHolderForActionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationMenuItem {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let valueTmpBuf : string | Resource | undefined
        if (valueTmpBufUnionSelector == (0).toChar()) {
            valueTmpBuf = (valueDeserializer.readString() as string)
        } else if (valueTmpBufUnionSelector == (1).toChar()) {
            valueTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for valueTmpBuf has to be chosen through deserialisation.")
        }
        const valueTmpResult : string | Resource = (valueTmpBuf as string | Resource)
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : string | Resource | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBuf_ : string | Resource | undefined
            if (iconTmpBuf_UnionSelector == (0).toChar()) {
                iconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (iconTmpBuf_UnionSelector == (1).toChar()) {
                iconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for iconTmpBuf_ has to be chosen through deserialisation.")
            }
            iconTmpBuf = (iconTmpBuf_ as string | Resource)
        }
        const iconTmpResult : string | Resource | undefined = iconTmpBuf
        const symbolIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((symbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const symbolIconTmpResult : SymbolGlyphModifier | undefined = symbolIconTmpBuf
        const isEnabledTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isEnabledTmpBuf : boolean | undefined = undefined
        if ((isEnabledTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isEnabledTmpBuf = valueDeserializer.readBoolean()
        }
        const isEnabledTmpResult : boolean | undefined = isEnabledTmpBuf
        const actionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let actionTmpBuf : (() => void) | undefined = undefined
        if ((actionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const actionTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const actionTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const actionTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            actionTmpBuf = ():void => {
                const actionTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                actionTmpBuf_BufArgsSerializer.writeInt32(actionTmpBuf_BufResource.resourceId);
                actionTmpBuf_BufArgsSerializer.writePointer(actionTmpBuf_BufCall);
                actionTmpBuf_BufArgsSerializer.writePointer(actionTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, actionTmpBuf_BufArgsSerializer.asBuffer(), actionTmpBuf_BufArgsSerializer.length());
                actionTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const actionTmpResult : (() => void) | undefined = actionTmpBuf
        let value : NavigationMenuItem = ({value: valueTmpResult, icon: iconTmpResult, symbolIcon: symbolIconTmpResult, isEnabled: isEnabledTmpResult, action: actionTmpResult} as NavigationMenuItem)
        return value
    }
}
export class NavigationTransitionProxy_serializer {
    public static write(buffer: SerializerBase, value: NavigationTransitionProxy): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): NavigationTransitionProxy {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return NavigationTransitionProxyInternal.fromPtr(ptr)
    }
}
export class ToolbarItem_serializer {
    public static write(buffer: SerializerBase, value: ToolbarItem): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            if (valueHolderForValueTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as string
                valueSerializer.writeString(valueHolderForValueTmpValueForIdx0)
            } else if (valueHolderForValueTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolIcon  = value.symbolIcon
        if (valueHolderForSymbolIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolIconTmpValue  = valueHolderForSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForSymbolIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAction  = value.action
        if (valueHolderForAction !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForActionTmpValue  = valueHolderForAction!
            valueSerializer.holdAndWriteCallback(valueHolderForActionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStatus  = value.status
        if (valueHolderForStatus !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStatusTmpValue  = (valueHolderForStatus as ToolbarItemStatus)
            valueSerializer.writeInt32(valueHolderForStatusTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForActiveIcon  = value.activeIcon
        if (valueHolderForActiveIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForActiveIconTmpValue  = valueHolderForActiveIcon!
            if (valueHolderForActiveIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForActiveIconTmpValueForIdx0  = valueHolderForActiveIconTmpValue as string
                valueSerializer.writeString(valueHolderForActiveIconTmpValueForIdx0)
            } else if (valueHolderForActiveIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForActiveIconTmpValueForIdx1  = valueHolderForActiveIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForActiveIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForActiveSymbolIcon  = value.activeSymbolIcon
        if (valueHolderForActiveSymbolIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForActiveSymbolIconTmpValue  = valueHolderForActiveSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForActiveSymbolIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ToolbarItem {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let valueTmpBuf : ResourceStr | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBuf_ : string | Resource | undefined
            if (valueTmpBuf_UnionSelector == (0).toChar()) {
                valueTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (valueTmpBuf_UnionSelector == (1).toChar()) {
                valueTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for valueTmpBuf_ has to be chosen through deserialisation.")
            }
            valueTmpBuf = (valueTmpBuf_ as string | Resource)
        }
        const valueTmpResult : ResourceStr | undefined = valueTmpBuf
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : ResourceStr | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBuf_ : string | Resource | undefined
            if (iconTmpBuf_UnionSelector == (0).toChar()) {
                iconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (iconTmpBuf_UnionSelector == (1).toChar()) {
                iconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for iconTmpBuf_ has to be chosen through deserialisation.")
            }
            iconTmpBuf = (iconTmpBuf_ as string | Resource)
        }
        const iconTmpResult : ResourceStr | undefined = iconTmpBuf
        const symbolIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((symbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const symbolIconTmpResult : SymbolGlyphModifier | undefined = symbolIconTmpBuf
        const actionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let actionTmpBuf : (() => void) | undefined = undefined
        if ((actionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const actionTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const actionTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const actionTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            actionTmpBuf = ():void => {
                const actionTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                actionTmpBuf_BufArgsSerializer.writeInt32(actionTmpBuf_BufResource.resourceId);
                actionTmpBuf_BufArgsSerializer.writePointer(actionTmpBuf_BufCall);
                actionTmpBuf_BufArgsSerializer.writePointer(actionTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, actionTmpBuf_BufArgsSerializer.asBuffer(), actionTmpBuf_BufArgsSerializer.length());
                actionTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const actionTmpResult : (() => void) | undefined = actionTmpBuf
        const statusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let statusTmpBuf : ToolbarItemStatus | undefined = undefined
        if ((statusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            statusTmpBuf = ToolbarItemStatus.fromValue(valueDeserializer.readInt32())
        }
        const statusTmpResult : ToolbarItemStatus | undefined = statusTmpBuf
        const activeIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let activeIconTmpBuf : ResourceStr | undefined = undefined
        if ((activeIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const activeIconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let activeIconTmpBuf_ : string | Resource | undefined
            if (activeIconTmpBuf_UnionSelector == (0).toChar()) {
                activeIconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (activeIconTmpBuf_UnionSelector == (1).toChar()) {
                activeIconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for activeIconTmpBuf_ has to be chosen through deserialisation.")
            }
            activeIconTmpBuf = (activeIconTmpBuf_ as string | Resource)
        }
        const activeIconTmpResult : ResourceStr | undefined = activeIconTmpBuf
        const activeSymbolIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let activeSymbolIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((activeSymbolIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            activeSymbolIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const activeSymbolIconTmpResult : SymbolGlyphModifier | undefined = activeSymbolIconTmpBuf
        let value : ToolbarItem = ({value: valueTmpResult, icon: iconTmpResult, symbolIcon: symbolIconTmpResult, action: actionTmpResult, status: statusTmpResult, activeIcon: activeIconTmpResult, activeSymbolIcon: activeSymbolIconTmpResult} as ToolbarItem)
        return value
    }
}
export class MoreButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: MoreButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MoreButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        let value : MoreButtonOptions = ({backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult} as MoreButtonOptions)
        return value
    }
}
export class NavigationCustomTitle_serializer {
    public static write(buffer: SerializerBase, value: NavigationCustomTitle): void {
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
    public static read(buffer: DeserializerBase): NavigationCustomTitle {
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
        let value : NavigationCustomTitle = ({builder: builderTmpResult, height: heightTmpResult} as NavigationCustomTitle)
        return value
    }
}
export class NavigationTitleOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationTitleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBarStyle  = value.barStyle
        if (valueHolderForBarStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBarStyleTmpValue  = (valueHolderForBarStyle as BarStyle)
            valueSerializer.writeInt32(valueHolderForBarStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPaddingStart  = value.paddingStart
        if (valueHolderForPaddingStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPaddingStartTmpValue  = valueHolderForPaddingStart!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForPaddingStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPaddingEnd  = value.paddingEnd
        if (valueHolderForPaddingEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPaddingEndTmpValue  = valueHolderForPaddingEnd!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForPaddingEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMainTitleModifier  = value.mainTitleModifier
        if (valueHolderForMainTitleModifier !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMainTitleModifierTmpValue  = valueHolderForMainTitleModifier!
            TextModifier_serializer.write(valueSerializer, valueHolderForMainTitleModifierTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSubTitleModifier  = value.subTitleModifier
        if (valueHolderForSubTitleModifier !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSubTitleModifierTmpValue  = valueHolderForSubTitleModifier!
            TextModifier_serializer.write(valueSerializer, valueHolderForSubTitleModifierTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationTitleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const barStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let barStyleTmpBuf : BarStyle | undefined = undefined
        if ((barStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            barStyleTmpBuf = BarStyle.fromValue(valueDeserializer.readInt32())
        }
        const barStyleTmpResult : BarStyle | undefined = barStyleTmpBuf
        const paddingStartTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paddingStartTmpBuf : LengthMetrics | undefined = undefined
        if ((paddingStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paddingStartTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const paddingStartTmpResult : LengthMetrics | undefined = paddingStartTmpBuf
        const paddingEndTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paddingEndTmpBuf : LengthMetrics | undefined = undefined
        if ((paddingEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paddingEndTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const paddingEndTmpResult : LengthMetrics | undefined = paddingEndTmpBuf
        const mainTitleModifierTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mainTitleModifierTmpBuf : TextModifier | undefined = undefined
        if ((mainTitleModifierTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            mainTitleModifierTmpBuf = (TextModifier_serializer.read(valueDeserializer) as TextModifier)
        }
        const mainTitleModifierTmpResult : TextModifier | undefined = mainTitleModifierTmpBuf
        const subTitleModifierTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let subTitleModifierTmpBuf : TextModifier | undefined = undefined
        if ((subTitleModifierTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            subTitleModifierTmpBuf = (TextModifier_serializer.read(valueDeserializer) as TextModifier)
        }
        const subTitleModifierTmpResult : TextModifier | undefined = subTitleModifierTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        let value : NavigationTitleOptions = ({backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, barStyle: barStyleTmpResult, paddingStart: paddingStartTmpResult, paddingEnd: paddingEndTmpResult, mainTitleModifier: mainTitleModifierTmpResult, subTitleModifier: subTitleModifierTmpResult, enableHoverMode: enableHoverModeTmpResult} as NavigationTitleOptions)
        return value
    }
}
export class NavigationMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMoreButtonOptions  = value.moreButtonOptions
        if (valueHolderForMoreButtonOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMoreButtonOptionsTmpValue  = valueHolderForMoreButtonOptions!
            MoreButtonOptions_serializer.write(valueSerializer, valueHolderForMoreButtonOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const moreButtonOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moreButtonOptionsTmpBuf : MoreButtonOptions | undefined = undefined
        if ((moreButtonOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            moreButtonOptionsTmpBuf = MoreButtonOptions_serializer.read(valueDeserializer)
        }
        const moreButtonOptionsTmpResult : MoreButtonOptions | undefined = moreButtonOptionsTmpBuf
        let value : NavigationMenuOptions = ({moreButtonOptions: moreButtonOptionsTmpResult} as NavigationMenuOptions)
        return value
    }
}
export class NavigationToolbarOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationToolbarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMoreButtonOptions  = value.moreButtonOptions
        if (valueHolderForMoreButtonOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMoreButtonOptionsTmpValue  = valueHolderForMoreButtonOptions!
            MoreButtonOptions_serializer.write(valueSerializer, valueHolderForMoreButtonOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBarStyle  = value.barStyle
        if (valueHolderForBarStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBarStyleTmpValue  = (valueHolderForBarStyle as BarStyle)
            valueSerializer.writeInt32(valueHolderForBarStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHideItemValue  = value.hideItemValue
        if (valueHolderForHideItemValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHideItemValueTmpValue  = valueHolderForHideItemValue!
            valueSerializer.writeBoolean(valueHolderForHideItemValueTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NavigationToolbarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const moreButtonOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moreButtonOptionsTmpBuf : MoreButtonOptions | undefined = undefined
        if ((moreButtonOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            moreButtonOptionsTmpBuf = MoreButtonOptions_serializer.read(valueDeserializer)
        }
        const moreButtonOptionsTmpResult : MoreButtonOptions | undefined = moreButtonOptionsTmpBuf
        const barStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let barStyleTmpBuf : BarStyle | undefined = undefined
        if ((barStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            barStyleTmpBuf = BarStyle.fromValue(valueDeserializer.readInt32())
        }
        const barStyleTmpResult : BarStyle | undefined = barStyleTmpBuf
        const hideItemValueTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hideItemValueTmpBuf : boolean | undefined = undefined
        if ((hideItemValueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hideItemValueTmpBuf = valueDeserializer.readBoolean()
        }
        const hideItemValueTmpResult : boolean | undefined = hideItemValueTmpBuf
        let value : NavigationToolbarOptions = ({backgroundColor: backgroundColorTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, moreButtonOptions: moreButtonOptionsTmpResult, barStyle: barStyleTmpResult, hideItemValue: hideItemValueTmpResult} as NavigationToolbarOptions)
        return value
    }
}