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
import { VoidCallback, Length, Dimension, ResourceStr, ResourceColor } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./resource"
import { image_PixelMap_serializer, image } from "./ohos.multimedia.image"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./ark.SymbolGlyphModifier"
import { window_SystemBarStyle_serializer, window } from "./ohos.window"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer } from "./common"
import { CustomBuilder, PageMapBuilder } from "./builder"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics, LengthMetrics_serializer } from "./ark.Graphics"
import { TextModifier, TextModifier_serializer } from "./ark.TextModifier"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NavDestinationContext, NavDestinationMode, NavDestinationContext_serializer } from "./navDestination"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_ctor()
        return retval
    }
    constructor() {
        this(NavigationTransitionProxyInternal.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavigationTransitionProxy_getFinalizer()
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
    private setIsInteractive(isInteractive: boolean): void {
        const isInteractive_casted = isInteractive as (boolean)
        this.setIsInteractive_serialize(isInteractive_casted)
        return
    }
    private getCancelTransition(): VoidCallback | undefined {
        return this.getCancelTransition_serialize()
    }
    private setCancelTransition(cancelTransition: VoidCallback): void {
        const cancelTransition_casted = cancelTransition as (VoidCallback)
        this.setCancelTransition_serialize(cancelTransition_casted)
        return
    }
    private getUpdateTransition(): UpdateTransitionCallback | undefined {
        return this.getUpdateTransition_serialize()
    }
    private setUpdateTransition(updateTransition: UpdateTransitionCallback): void {
        const updateTransition_casted = updateTransition as (UpdateTransitionCallback)
        this.setUpdateTransition_serialize(updateTransition_casted)
        return
    }
    private finishTransition_serialize(): void {
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
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private setIsInteractive_serialize(isInteractive: boolean): void {
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setIsInteractive(this.peer!.ptr, isInteractive ? 1 : 0)
    }
    private getCancelTransition_serialize(): VoidCallback | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getCancelTransition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : VoidCallback | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = ():void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    InteropNativeModule._CallCallback(-2038961969, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : VoidCallback | undefined = buffer
        return returnResult
    }
    private setCancelTransition_serialize(cancelTransition: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(cancelTransition)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setCancelTransition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getUpdateTransition_serialize(): UpdateTransitionCallback | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getUpdateTransition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : UpdateTransitionCallback | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (progress: number):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    buffer__argsSerializer.writeNumber(progress);
    InteropNativeModule._CallCallback(-448105339, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : UpdateTransitionCallback | undefined = buffer
        return returnResult
    }
    private setUpdateTransition_serialize(updateTransition: UpdateTransitionCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(updateTransition)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setUpdateTransition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): NavigationTransitionProxyInternal {
        return new NavigationTransitionProxyInternal(ptr)
    }
}
export class NavPathInfoInternal {
    public static fromPtr(ptr: KPointer): NavPathInfo {
        return new NavPathInfo(ptr)
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
    get param(): Object | undefined {
        return this.getParam()
    }
    set param(param: Object | undefined) {
        const param_NonNull  = (param as Object | undefined)
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
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, NavPathInfo.getFinalizer())
    }
    static ctor(name: string, param: Object | undefined, onPop?: ((value0: PopInfo) => void), isEntry?: boolean): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let param_type : int32 = RuntimeType.UNDEFINED
        param_type = runtimeType(param)
        thisSerializer.writeInt8(param_type)
        if ((RuntimeType.UNDEFINED) != (param_type)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        let onPop_type : int32 = RuntimeType.UNDEFINED
        onPop_type = runtimeType(onPop)
        thisSerializer.writeInt8(onPop_type)
        if ((RuntimeType.UNDEFINED) != (onPop_type)) {
            const onPop_value  = onPop!
            thisSerializer.holdAndWriteCallback(onPop_value)
        }
        let isEntry_type : int32 = RuntimeType.UNDEFINED
        isEntry_type = runtimeType(isEntry)
        thisSerializer.writeInt8(isEntry_type)
        if ((RuntimeType.UNDEFINED) != (isEntry_type)) {
            const isEntry_value  = isEntry!
            thisSerializer.writeBoolean(isEntry_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_ctor(name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(name: string, param: Object | undefined, onPop?: ((value0: PopInfo) => void), isEntry?: boolean) {
        this(NavPathInfo.ctor((name)!, param, onPop, isEntry))
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
    private getParam(): Object | undefined {
        return this.getParam_serialize()
    }
    private setParam(param: Object | undefined): void {
        const param_casted = param as (Object | undefined)
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
    private getName_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getName(this.peer!.ptr)
        return retval
    }
    private setName_serialize(name: string): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setName(this.peer!.ptr, name)
    }
    private getParam_serialize(): Object | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getParam(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : Object | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (retvalDeserializer.readObject() as object)
        }
        const returnResult : Object | undefined = buffer
        return returnResult
    }
    private setParam_serialize(param: Object | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let param_type : int32 = RuntimeType.UNDEFINED
        param_type = runtimeType(param)
        thisSerializer.writeInt8(param_type)
        if ((RuntimeType.UNDEFINED) != (param_type)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setParam(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnPop_serialize(): ((value0: PopInfo) => void) | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getOnPop(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : ((value0: PopInfo) => void) | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (value0: PopInfo):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    PopInfo_serializer.write(buffer__argsSerializer, value0);
    InteropNativeModule._CallCallback(624053870, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : ((value0: PopInfo) => void) | undefined = buffer
        return returnResult
    }
    private setOnPop_serialize(onPop: ((value0: PopInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let onPop_type : int32 = RuntimeType.UNDEFINED
        onPop_type = runtimeType(onPop)
        thisSerializer.writeInt8(onPop_type)
        if ((RuntimeType.UNDEFINED) != (onPop_type)) {
            const onPop_value  = onPop!
            thisSerializer.holdAndWriteCallback(onPop_value)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setOnPop(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsEntry_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getIsEntry(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private setIsEntry_serialize(isEntry: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let isEntry_type : int32 = RuntimeType.UNDEFINED
        isEntry_type = runtimeType(isEntry)
        thisSerializer.writeInt8(isEntry_type)
        if ((RuntimeType.UNDEFINED) != (isEntry_type)) {
            const isEntry_value  = isEntry!
            thisSerializer.writeBoolean(isEntry_value)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setIsEntry(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getNavDestinationId_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getNavDestinationId(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : string | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
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
        thisSerializer.writeInt8(navDestinationId_type)
        if ((RuntimeType.UNDEFINED) != (navDestinationId_type)) {
            const navDestinationId_value  = navDestinationId!
            thisSerializer.writeString(navDestinationId_value)
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_ctor()
        return retval
    }
    constructor() {
        this(NavPathStack.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavPathStack_getFinalizer()
    }
    public pushPath(info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): void {
        const info_type = runtimeType(info)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const animated_casted = animated as (boolean | undefined)
            this.pushPath0_serialize(info_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            this.pushPath1_serialize(info_casted, options_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public pushDestination(info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): Promise<void> {
        const info_type = runtimeType(info)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const animated_casted = animated as (boolean | undefined)
            return this.pushDestination0_serialize(info_casted, animated_casted)
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            return this.pushDestination1_serialize(info_casted, options_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public pushPathByName(name: string, param: Object | Object | undefined, onPop?: ((value0: PopInfo) => void) | boolean | undefined, animated?: boolean): void {
        const name_type = runtimeType(name)
        const param_type = runtimeType(param)
        const onPop_type = runtimeType(onPop)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BIGINT == param_type) || (RuntimeType.BOOLEAN == param_type) || (RuntimeType.FUNCTION == param_type) || (RuntimeType.MATERIALIZED == param_type) || (RuntimeType.NUMBER == param_type) || (RuntimeType.OBJECT == param_type) || (RuntimeType.STRING == param_type) || (RuntimeType.SYMBOL == param_type)) && (RuntimeType.FUNCTION == onPop_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const onPop_casted = onPop as (((value0: PopInfo) => void))
            const animated_casted = animated as (boolean | undefined)
            this.pushPathByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
            return
        }
        if (((RuntimeType.BIGINT == param_type) || (RuntimeType.BOOLEAN == param_type) || (RuntimeType.FUNCTION == param_type) || (RuntimeType.MATERIALIZED == param_type) || (RuntimeType.NUMBER == param_type) || (RuntimeType.OBJECT == param_type) || (RuntimeType.STRING == param_type) || (RuntimeType.SYMBOL == param_type) || (RuntimeType.UNDEFINED == param_type)) && ((RuntimeType.BOOLEAN == onPop_type) || (RuntimeType.UNDEFINED == onPop_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const name_casted = name as (string)
            const param_casted = param as (Object | undefined)
            const animated_casted = onPop as (boolean | undefined)
            this.pushPathByName0_serialize(name_casted, param_casted, animated_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public pushDestinationByName(name: string, param: Object, onPop?: boolean | undefined | ((value0: PopInfo) => void), animated?: boolean): Promise<void> {
        const name_type = runtimeType(name)
        const param_type = runtimeType(param)
        const onPop_type = runtimeType(onPop)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == onPop_type) || (RuntimeType.UNDEFINED == onPop_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const animated_casted = onPop as (boolean | undefined)
            return this.pushDestinationByName0_serialize(name_casted, param_casted, animated_casted)
        }
        if ((RuntimeType.FUNCTION == onPop_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const onPop_casted = onPop as (((value0: PopInfo) => void))
            const animated_casted = animated as (boolean | undefined)
            return this.pushDestinationByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public replacePath(info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): void {
        const info_type = runtimeType(info)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const animated_casted = animated as (boolean | undefined)
            this.replacePath0_serialize(info_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            this.replacePath1_serialize(info_casted, options_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
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
    public removeByIndexes(indexes: Array<number>): number {
        const indexes_casted = indexes as (Array<number>)
        return this.removeByIndexes_serialize(indexes_casted)
    }
    public removeByName(name: string): number {
        const name_casted = name as (string)
        return this.removeByName_serialize(name_casted)
    }
    public removeByNavDestinationId(navDestinationId: string): boolean {
        const navDestinationId_casted = navDestinationId as (string)
        return this.removeByNavDestinationId_serialize(navDestinationId_casted)
    }
    public pop(result?: boolean | undefined | Object, animated?: boolean): NavPathInfo | undefined {
        const result_type = runtimeType(result)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == result_type) || (RuntimeType.UNDEFINED == result_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const animated_casted = result as (boolean | undefined)
            return this.pop0_serialize(animated_casted)
        }
        if (((RuntimeType.BIGINT == result_type) || (RuntimeType.BOOLEAN == result_type) || (RuntimeType.FUNCTION == result_type) || (RuntimeType.MATERIALIZED == result_type) || (RuntimeType.NUMBER == result_type) || (RuntimeType.OBJECT == result_type) || (RuntimeType.STRING == result_type) || (RuntimeType.SYMBOL == result_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const result_casted = result as (Object)
            const animated_casted = animated as (boolean | undefined)
            return this.pop1_serialize(result_casted, animated_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public popToName(name: string, result?: boolean | undefined | Object, animated?: boolean): number {
        const name_type = runtimeType(name)
        const result_type = runtimeType(result)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == result_type) || (RuntimeType.UNDEFINED == result_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const name_casted = name as (string)
            const animated_casted = result as (boolean | undefined)
            return this.popToName0_serialize(name_casted, animated_casted)
        }
        if (((RuntimeType.BIGINT == result_type) || (RuntimeType.BOOLEAN == result_type) || (RuntimeType.FUNCTION == result_type) || (RuntimeType.MATERIALIZED == result_type) || (RuntimeType.NUMBER == result_type) || (RuntimeType.OBJECT == result_type) || (RuntimeType.STRING == result_type) || (RuntimeType.SYMBOL == result_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const result_casted = result as (Object)
            const animated_casted = animated as (boolean | undefined)
            return this.popToName1_serialize(name_casted, result_casted, animated_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public popToIndex(index: number, result?: boolean | undefined | Object, animated?: boolean): void {
        const index_type = runtimeType(index)
        const result_type = runtimeType(result)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == result_type) || (RuntimeType.UNDEFINED == result_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const index_casted = index as (number)
            const animated_casted = result as (boolean | undefined)
            this.popToIndex0_serialize(index_casted, animated_casted)
            return
        }
        if (((RuntimeType.BIGINT == result_type) || (RuntimeType.BOOLEAN == result_type) || (RuntimeType.FUNCTION == result_type) || (RuntimeType.MATERIALIZED == result_type) || (RuntimeType.NUMBER == result_type) || (RuntimeType.OBJECT == result_type) || (RuntimeType.STRING == result_type) || (RuntimeType.SYMBOL == result_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const index_casted = index as (number)
            const result_casted = result as (Object)
            const animated_casted = animated as (boolean | undefined)
            this.popToIndex1_serialize(index_casted, result_casted, animated_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public moveToTop(name: string, animated?: boolean): number {
        const name_casted = name as (string)
        const animated_casted = animated as (boolean | undefined)
        return this.moveToTop_serialize(name_casted, animated_casted)
    }
    public moveIndexToTop(index: number, animated?: boolean): void {
        const index_casted = index as (number)
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
    public getParamByIndex(index: number): Object | undefined {
        const index_casted = index as (number)
        return this.getParamByIndex_serialize(index_casted)
    }
    public getParamByName(name: string): Array<Object | undefined> {
        const name_casted = name as (string)
        return this.getParamByName_serialize(name_casted)
    }
    public getIndexByName(name: string): Array<number> {
        const name_casted = name as (string)
        return this.getIndexByName_serialize(name_casted)
    }
    public getParent(): NavPathStack | undefined {
        return this.getParent_serialize()
    }
    public size(): number {
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
    private pushPath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushPath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            NavigationOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushDestination0_serialize(info: NavPathInfo, animated?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushDestination1_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            NavigationOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushPathByName0_serialize(name: string, param: Object | undefined, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let param_type : int32 = RuntimeType.UNDEFINED
        param_type = runtimeType(param)
        thisSerializer.writeInt8(param_type)
        if ((RuntimeType.UNDEFINED) != (param_type)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushPathByName1_serialize(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        thisSerializer.holdAndWriteCallback(onPop)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushDestinationByName0_serialize(name: string, param: Object, animated?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushDestinationByName1_serialize(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        thisSerializer.holdAndWriteCallback(onPop)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private replacePath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private replacePath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            NavigationOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private replaceDestination_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            NavigationOptions_serializer.write(thisSerializer, options_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_replaceDestination(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private replacePathByName_serialize(name: string, param: Object, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(param)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePathByName(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeByIndexes_serialize(indexes: Array<number>): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32(indexes.length as int32)
        for (let i = 0; i < indexes.length; i++) {
            const indexes_element : number = indexes[i]
            thisSerializer.writeNumber(indexes_element)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByIndexes(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeByName_serialize(name: string): number {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByName(this.peer!.ptr, name)
        return retval
    }
    private removeByNavDestinationId_serialize(navDestinationId: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByNavDestinationId(this.peer!.ptr, navDestinationId)
        return retval
    }
    private pop0_serialize(animated?: boolean): NavPathInfo | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : NavPathInfo | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (NavPathInfo_serializer.read(retvalDeserializer) as NavPathInfo)
        }
        const returnResult : NavPathInfo | undefined = buffer
        return returnResult
    }
    private pop1_serialize(result: Object, animated?: boolean): NavPathInfo | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(result)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : NavPathInfo | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (NavPathInfo_serializer.read(retvalDeserializer) as NavPathInfo)
        }
        const returnResult : NavPathInfo | undefined = buffer
        return returnResult
    }
    private popToName0_serialize(name: string, animated?: boolean): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_popToName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private popToName1_serialize(name: string, result: Object, animated?: boolean): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(result)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_popToName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private popToIndex0_serialize(index: number, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex0(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private popToIndex1_serialize(index: number, result: Object, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(result)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex1(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private moveToTop_serialize(name: string, animated?: boolean): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_moveToTop(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private moveIndexToTop_serialize(index: number, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_moveIndexToTop(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private clear_serialize(animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_clear(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getAllPathName_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getAllPathName(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private getParamByIndex_serialize(index: number): Object | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParamByIndex(this.peer!.ptr, index)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : Object | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (retvalDeserializer.readObject() as object)
        }
        const returnResult : Object | undefined = buffer
        return returnResult
    }
    private getParamByName_serialize(name: string): Array<Object | undefined> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParamByName(this.peer!.ptr, name)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<Object | undefined> = new Array<Object | undefined>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            const buffer_buf_runtimeType  = (retvalDeserializer.readInt8() as int32)
            let buffer_buf : Object | undefined
            if ((RuntimeType.UNDEFINED) != (buffer_buf_runtimeType))
            {
                buffer_buf = (retvalDeserializer.readObject() as object)
            }
            buffer[buffer_i] = buffer_buf
        }
        const returnResult : Array<Object | undefined> = buffer
        return returnResult
    }
    private getIndexByName_serialize(name: string): Array<number> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getIndexByName(this.peer!.ptr, name)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<number> = new Array<number>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : Array<number> = buffer
        return returnResult
    }
    private getParent_serialize(): NavPathStack | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParent(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = (retvalDeserializer.readInt8() as int32)
        let buffer : NavPathStack | undefined
        if ((RuntimeType.UNDEFINED) != (buffer_runtimeType))
        {
            buffer = (NavPathStack_serializer.read(retvalDeserializer) as NavPathStack)
        }
        const returnResult : NavPathStack | undefined = buffer
        return returnResult
    }
    private size_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_size(this.peer!.ptr)
        return retval
    }
    private disableAnimation_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._NavPathStack_disableAnimation(this.peer!.ptr, value ? 1 : 0)
    }
    private setInterception_serialize(interception: NavigationInterception): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationInterception_serializer.write(thisSerializer, interception)
        ArkUIGeneratedNativeModule._NavPathStack_setInterception(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getPathStack_serialize(): Array<NavPathInfo> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getPathStack(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<NavPathInfo> = new Array<NavPathInfo>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (NavPathInfo_serializer.read(retvalDeserializer) as NavPathInfo)
        }
        const returnResult : Array<NavPathInfo> = buffer
        return returnResult
    }
    private setPathStack_serialize(pathStack: Array<NavPathInfo>, animated?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32(pathStack.length as int32)
        for (let i = 0; i < pathStack.length; i++) {
            const pathStack_element : NavPathInfo = pathStack[i]
            NavPathInfo_serializer.write(thisSerializer, pathStack_element)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_setPathStack(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkNavigationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavigationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Navigation_construct(peerId, flags)
        const _peer  = new ArkNavigationPeer(_peerPtr, peerId, "Navigation", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavigationOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions0(this.peer.ptr)
    }
    setNavigationOptions1Attribute(pathInfos: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions1(this.peer.ptr, toPeerPtr(pathInfos))
    }
    navBarWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navBarPositionAttribute(value: NavBarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavBarPosition)
            thisSerializer.writeInt32(TypeChecker.NavBarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navBarWidthRangeAttribute(value: [ Dimension, Dimension ] | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_0  = value_value[0]
            let value_value_0_type : int32 = RuntimeType.UNDEFINED
            value_value_0_type = runtimeType(value_value_0)
            if (RuntimeType.STRING == value_value_0_type) {
                thisSerializer.writeInt8(0)
                const value_value_0_0  = value_value_0 as string
                thisSerializer.writeString(value_value_0_0)
            }
            else if (RuntimeType.NUMBER == value_value_0_type) {
                thisSerializer.writeInt8(1)
                const value_value_0_1  = value_value_0 as number
                thisSerializer.writeNumber(value_value_0_1)
            }
            else if (RuntimeType.OBJECT == value_value_0_type) {
                thisSerializer.writeInt8(2)
                const value_value_0_2  = value_value_0 as Resource
                Resource_serializer.write(thisSerializer, value_value_0_2)
            }
            const value_value_1  = value_value[1]
            let value_value_1_type : int32 = RuntimeType.UNDEFINED
            value_value_1_type = runtimeType(value_value_1)
            if (RuntimeType.STRING == value_value_1_type) {
                thisSerializer.writeInt8(0)
                const value_value_1_0  = value_value_1 as string
                thisSerializer.writeString(value_value_1_0)
            }
            else if (RuntimeType.NUMBER == value_value_1_type) {
                thisSerializer.writeInt8(1)
                const value_value_1_1  = value_value_1 as number
                thisSerializer.writeNumber(value_value_1_1)
            }
            else if (RuntimeType.OBJECT == value_value_1_type) {
                thisSerializer.writeInt8(2)
                const value_value_1_2  = value_value_1 as Resource
                Resource_serializer.write(thisSerializer, value_value_1_2)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarWidthRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minContentWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_minContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavigationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavigationMode)
            thisSerializer.writeInt32(TypeChecker.NavigationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_mode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backButtonIcon0Attribute(value: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (TypeChecker.isimage_PixelMap(value_value, false, false)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_backButtonIcon0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backButtonIcon1Attribute(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let icon_type : int32 = RuntimeType.UNDEFINED
        icon_type = runtimeType(icon)
        thisSerializer.writeInt8(icon_type)
        if ((RuntimeType.UNDEFINED) != (icon_type)) {
            const icon_value  = icon!
            let icon_value_type : int32 = RuntimeType.UNDEFINED
            icon_value_type = runtimeType(icon_value)
            if (RuntimeType.STRING == icon_value_type) {
                thisSerializer.writeInt8(0)
                const icon_value_0  = icon_value as string
                thisSerializer.writeString(icon_value_0)
            }
            else if (TypeChecker.isimage_PixelMap(icon_value, false, false)) {
                thisSerializer.writeInt8(1)
                const icon_value_1  = icon_value as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, icon_value_1)
            }
            else if (TypeChecker.isResource(icon_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(2)
                const icon_value_2  = icon_value as Resource
                Resource_serializer.write(thisSerializer, icon_value_2)
            }
            else if (TypeChecker.isSymbolGlyphModifier(icon_value)) {
                thisSerializer.writeInt8(3)
                const icon_value_3  = icon_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, icon_value_3)
            }
        }
        let accessibilityText_type : int32 = RuntimeType.UNDEFINED
        accessibilityText_type = runtimeType(accessibilityText)
        thisSerializer.writeInt8(accessibilityText_type)
        if ((RuntimeType.UNDEFINED) != (accessibilityText_type)) {
            const accessibilityText_value  = accessibilityText!
            let accessibilityText_value_type : int32 = RuntimeType.UNDEFINED
            accessibilityText_value_type = runtimeType(accessibilityText_value)
            if (RuntimeType.STRING == accessibilityText_value_type) {
                thisSerializer.writeInt8(0)
                const accessibilityText_value_0  = accessibilityText_value as string
                thisSerializer.writeString(accessibilityText_value_0)
            }
            else if (RuntimeType.OBJECT == accessibilityText_value_type) {
                thisSerializer.writeInt8(1)
                const accessibilityText_value_1  = accessibilityText_value as Resource
                Resource_serializer.write(thisSerializer, accessibilityText_value_1)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_backButtonIcon1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideNavBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideNavBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideTitleBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8(hide_type)
        if ((RuntimeType.UNDEFINED) != (hide_type)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideBackButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideBackButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    titleModeAttribute(value: NavigationTitleMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavigationTitleMode)
            thisSerializer.writeInt32(TypeChecker.NavigationTitleMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_titleMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menus0Attribute(value: Array<NavigationMenuItem> | CustomBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : NavigationMenuItem = value_value_0[i]
                    NavigationMenuItem_serializer.write(thisSerializer, value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_menus0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menus1Attribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let items_type : int32 = RuntimeType.UNDEFINED
        items_type = runtimeType(items)
        thisSerializer.writeInt8(items_type)
        if ((RuntimeType.UNDEFINED) != (items_type)) {
            const items_value  = items!
            let items_value_type : int32 = RuntimeType.UNDEFINED
            items_value_type = runtimeType(items_value)
            if (RuntimeType.OBJECT == items_value_type) {
                thisSerializer.writeInt8(0)
                const items_value_0  = items_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32(items_value_0.length as int32)
                for (let i = 0; i < items_value_0.length; i++) {
                    const items_value_0_element : NavigationMenuItem = items_value_0[i]
                    NavigationMenuItem_serializer.write(thisSerializer, items_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == items_value_type) {
                thisSerializer.writeInt8(1)
                const items_value_1  = items_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(items_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            NavigationMenuOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_menus1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideToolBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8(hide_type)
        if ((RuntimeType.UNDEFINED) != (hide_type)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideToolBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableToolBarAdaptationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_enableToolBarAdaptation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTitleModeChangeAttribute(value: ((titleMode: NavigationTitleMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_onTitleModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavBarStateChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_onNavBarStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavigationModeChangeAttribute(value: ((mode: NavigationMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_onNavigationModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navDestinationAttribute(value: PageMapBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navDestination(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customNavContentTransitionAttribute(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_customNavContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarStyleAttribute(value: window.SystemBarStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            window_SystemBarStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_systemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    recoverableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_recoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDragBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_enableDragBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableModeChangeAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_enableModeChangeAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    titleAttribute(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_1)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (TypeChecker.isNavigationCommonTitle(value_value, false, false)) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as NavigationCommonTitle
                NavigationCommonTitle_serializer.write(thisSerializer, value_value_2)
            }
            else if (TypeChecker.isNavigationCustomTitle(value_value, false, false)) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as NavigationCustomTitle
                NavigationCustomTitle_serializer.write(thisSerializer, value_value_3)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            NavigationTitleOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_title(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    toolbarConfigurationAttribute(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Array<ToolbarItem>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : ToolbarItem = value_value_0[i]
                    ToolbarItem_serializer.write(thisSerializer, value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            NavigationToolbarOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_toolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let types_type : int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8(types_type)
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
        thisSerializer.writeInt8(edges_type)
        if ((RuntimeType.UNDEFINED) != (edges_type)) {
            const edges_value  = edges!
            thisSerializer.writeInt32(edges_value.length as int32)
            for (let i = 0; i < edges_value.length; i++) {
                const edges_value_element : LayoutSafeAreaEdge = edges_value[i]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaEdge_ToNumeric(edges_value_element))
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_ignoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type SystemBarStyle = window.SystemBarStyle;
export interface NavigationCommonTitle {
    main: string | Resource;
    sub: string | Resource;
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
    value: ResourceStr;
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
    navBarWidth(value: Length | undefined): this
    navBarPosition(value: NavBarPosition | undefined): this
    navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this
    minContentWidth(value: Dimension | undefined): this
    mode(value: NavigationMode | undefined): this
    backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this
    hideNavBar(value: boolean | undefined): this
    hideTitleBar(hide: boolean | undefined, animated?: boolean): this
    hideBackButton(value: boolean | undefined): this
    titleMode(value: NavigationTitleMode | undefined): this
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this
    hideToolBar(hide: boolean | undefined, animated?: boolean): this
    enableToolBarAdaptation(value: boolean | undefined): this
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this
    navDestination(value: PageMapBuilder | undefined): this
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this
    systemBarStyle(value: window.SystemBarStyle | undefined): this
    recoverable(value: boolean | undefined): this
    enableDragBar(value: boolean | undefined): this
    enableModeChangeAnimation(value: boolean | undefined): this
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this
    attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkNavigationStyle extends ArkCommonMethodStyle implements NavigationAttribute {
    navBarWidth_value?: Length | undefined
    navBarPosition_value?: NavBarPosition | undefined
    navBarWidthRange_value?: [ Dimension, Dimension ] | undefined
    minContentWidth_value?: Dimension | undefined
    mode_value?: NavigationMode | undefined
    backButtonIcon_value?: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined
    hideNavBar_value?: boolean | undefined
    hideTitleBar_value?: boolean | undefined
    hideBackButton_value?: boolean | undefined
    titleMode_value?: NavigationTitleMode | undefined
    menus_value?: Array<NavigationMenuItem> | CustomBuilder | undefined
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
    attributeModifier_value?: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined
    public navBarWidth(value: Length | undefined): this {
        return this
    }
    public navBarPosition(value: NavBarPosition | undefined): this {
        return this
    }
    public navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        return this
    }
    public mode(value: NavigationMode | undefined): this {
        return this
    }
    public backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        return this
    }
    public hideNavBar(value: boolean | undefined): this {
        return this
    }
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this {
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        return this
    }
    public titleMode(value: NavigationTitleMode | undefined): this {
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        return this
    }
    public enableToolBarAdaptation(value: boolean | undefined): this {
        return this
    }
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        return this
    }
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        return this
    }
    public navDestination(value: PageMapBuilder | undefined): this {
        return this
    }
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        return this
    }
    public systemBarStyle(value: window.SystemBarStyle | undefined): this {
        return this
    }
    public recoverable(value: boolean | undefined): this {
        return this
    }
    public enableDragBar(value: boolean | undefined): this {
        return this
    }
    public enableModeChangeAnimation(value: boolean | undefined): this {
        return this
    }
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: NavigationAttribute): void {
        super.apply(target)
        if (this.navBarWidth_value !== undefined)
            target.navBarWidth(this.navBarWidth_value!)
        if (this.navBarPosition_value !== undefined)
            target.navBarPosition(this.navBarPosition_value!)
        if (this.navBarWidthRange_value !== undefined)
            target.navBarWidthRange(this.navBarWidthRange_value!)
        if (this.minContentWidth_value !== undefined)
            target.minContentWidth(this.minContentWidth_value!)
        if (this.mode_value !== undefined)
            target.mode(this.mode_value!)
        if (this.backButtonIcon_value !== undefined)
            target.backButtonIcon(this.backButtonIcon_value!)
        if (this.hideNavBar_value !== undefined)
            target.hideNavBar(this.hideNavBar_value!)
        if (this.hideTitleBar_value !== undefined)
            target.hideTitleBar(this.hideTitleBar_value!)
        if (this.hideBackButton_value !== undefined)
            target.hideBackButton(this.hideBackButton_value!)
        if (this.titleMode_value !== undefined)
            target.titleMode(this.titleMode_value!)
        if (this.menus_value !== undefined)
            target.menus(this.menus_value!)
        if (this.hideToolBar_value !== undefined)
            target.hideToolBar(this.hideToolBar_value!)
        if (this.enableToolBarAdaptation_value !== undefined)
            target.enableToolBarAdaptation(this.enableToolBarAdaptation_value!)
        if (this.onTitleModeChange_value !== undefined)
            target.onTitleModeChange(this.onTitleModeChange_value!)
        if (this.onNavBarStateChange_value !== undefined)
            target.onNavBarStateChange(this.onNavBarStateChange_value!)
        if (this.onNavigationModeChange_value !== undefined)
            target.onNavigationModeChange(this.onNavigationModeChange_value!)
        if (this.navDestination_value !== undefined)
            target.navDestination(this.navDestination_value!)
        if (this.customNavContentTransition_value !== undefined)
            target.customNavContentTransition(this.customNavContentTransition_value!)
        if (this.systemBarStyle_value !== undefined)
            target.systemBarStyle(this.systemBarStyle_value!)
        if (this.recoverable_value !== undefined)
            target.recoverable(this.recoverable_value!)
        if (this.enableDragBar_value !== undefined)
            target.enableDragBar(this.enableDragBar_value!)
        if (this.enableModeChangeAnimation_value !== undefined)
            target.enableModeChangeAnimation(this.enableModeChangeAnimation_value!)
    }
}
export interface NavigationAnimatedTransition {
    onTransitionEnd?: ((isVisible: boolean) => void);
    timeout?: number;
    isInteractive?: boolean;
    transition: ((transitionProxy: NavigationTransitionProxy) => void);
}
export type UpdateTransitionCallback = (progress: number) => void;
export interface NavContentInfo {
    name?: string;
    index: number;
    mode?: NavDestinationMode;
    param?: Object;
    navDestinationId?: string;
}

export class ArkNavigationComponent extends ArkCommonMethodComponent implements NavigationAttribute {
    getPeer(): ArkNavigationPeer {
        return (this.peer as ArkNavigationPeer)
    }
    public setNavigationOptions(pathInfos?: NavPathStack): this {
        if (this.checkPriority("setNavigationOptions")) {
            const pathInfos_type = runtimeType(pathInfos)
            if (RuntimeType.UNDEFINED == pathInfos_type) {
                this.getPeer()?.setNavigationOptions0Attribute()
                return this
            }
            if (RuntimeType.OBJECT == pathInfos_type) {
                const pathInfos_casted = pathInfos as (NavPathStack)
                this.getPeer()?.setNavigationOptions1Attribute(pathInfos_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public navBarWidth(value: Length | undefined): this {
        if (this.checkPriority("navBarWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.navBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public navBarPosition(value: NavBarPosition | undefined): this {
        if (this.checkPriority("navBarPosition")) {
            const value_casted = value as (NavBarPosition | undefined)
            this.getPeer()?.navBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        if (this.checkPriority("navBarWidthRange")) {
            const value_casted = value as ([ Dimension, Dimension ] | undefined)
            this.getPeer()?.navBarWidthRangeAttribute(value_casted)
            return this
        }
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.minContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public mode(value: NavigationMode | undefined): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavigationMode | undefined)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    public backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (this.checkPriority("backButtonIcon")) {
            const icon_type = runtimeType(icon)
            const accessibilityText_type = runtimeType(accessibilityText)
            if (((RuntimeType.STRING == icon_type) || (RuntimeType.OBJECT == icon_type) || (RuntimeType.OBJECT == icon_type) || (RuntimeType.OBJECT == icon_type) || (RuntimeType.UNDEFINED == icon_type)) && (RuntimeType.UNDEFINED == accessibilityText_type)) {
                const value_casted = icon as (string | image.PixelMap | Resource | SymbolGlyphModifier | undefined)
                this.getPeer()?.backButtonIcon0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.STRING == icon_type) || (RuntimeType.OBJECT == icon_type) || (RuntimeType.OBJECT == icon_type) || (RuntimeType.OBJECT == icon_type) || (RuntimeType.UNDEFINED == icon_type)) && ((RuntimeType.STRING == accessibilityText_type) || (RuntimeType.OBJECT == accessibilityText_type) || (RuntimeType.UNDEFINED == accessibilityText_type))) {
                const icon_casted = icon as (string | image.PixelMap | Resource | SymbolGlyphModifier | undefined)
                const accessibilityText_casted = accessibilityText as (ResourceStr | undefined)
                this.getPeer()?.backButtonIcon1Attribute(icon_casted, accessibilityText_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public hideNavBar(value: boolean | undefined): this {
        if (this.checkPriority("hideNavBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.hideNavBarAttribute(value_casted)
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
    public titleMode(value: NavigationTitleMode | undefined): this {
        if (this.checkPriority("titleMode")) {
            const value_casted = value as (NavigationTitleMode | undefined)
            this.getPeer()?.titleModeAttribute(value_casted)
            return this
        }
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (this.checkPriority("menus")) {
            const items_type = runtimeType(items)
            const options_type = runtimeType(options)
            if (((RuntimeType.OBJECT == items_type) || (RuntimeType.FUNCTION == items_type) || (RuntimeType.UNDEFINED == items_type)) && (RuntimeType.UNDEFINED == options_type)) {
                const value_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
                this.getPeer()?.menus0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.OBJECT == items_type) || (RuntimeType.FUNCTION == items_type) || (RuntimeType.UNDEFINED == items_type)) && ((RuntimeType.OBJECT == options_type) || (RuntimeType.UNDEFINED == options_type))) {
                const items_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
                const options_casted = options as (NavigationMenuOptions | undefined)
                this.getPeer()?.menus1Attribute(items_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && (RuntimeType.UNDEFINED == animated_type)) {
                const value_casted = hide as (boolean | undefined)
                this.getPeer()?.hideToolBar0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
                const hide_casted = hide as (boolean | undefined)
                const animated_casted = animated as (boolean | undefined)
                this.getPeer()?.hideToolBar1Attribute(hide_casted, animated_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public enableToolBarAdaptation(value: boolean | undefined): this {
        if (this.checkPriority("enableToolBarAdaptation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableToolBarAdaptationAttribute(value_casted)
            return this
        }
        return this
    }
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        if (this.checkPriority("onTitleModeChange")) {
            const value_casted = value as (((titleMode: NavigationTitleMode) => void) | undefined)
            this.getPeer()?.onTitleModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onNavBarStateChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onNavBarStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        if (this.checkPriority("onNavigationModeChange")) {
            const value_casted = value as (((mode: NavigationMode) => void) | undefined)
            this.getPeer()?.onNavigationModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public navDestination(value: PageMapBuilder | undefined): this {
        if (this.checkPriority("navDestination")) {
            const value_casted = value as (PageMapBuilder | undefined)
            this.getPeer()?.navDestinationAttribute(value_casted)
            return this
        }
        return this
    }
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        if (this.checkPriority("customNavContentTransition")) {
            const value_casted = value as (((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined)
            this.getPeer()?.customNavContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public systemBarStyle(value: window.SystemBarStyle | undefined): this {
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (window.SystemBarStyle | undefined)
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
    public enableDragBar(value: boolean | undefined): this {
        if (this.checkPriority("enableDragBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableDragBarAttribute(value_casted)
            return this
        }
        return this
    }
    public enableModeChangeAnimation(value: boolean | undefined): this {
        if (this.checkPriority("enableModeChangeAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableModeChangeAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const value_casted = value as (Array<ToolbarItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType> | undefined)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge> | undefined)
            this.getPeer()?.ignoreLayoutSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withNavigationStyle(receiver: NavigationAttribute, modifier: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkNavigationStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("NavigationImpl")
export function Navigation(
    pathInfos?: NavPathStack | undefined,
    @memo
    content_?: () => void,
): NavigationAttribute {
    throw new Error("Not implemented")
}

@memo
export function NavigationImpl(
    @memo
    style: ((attributes: NavigationAttribute) => void) | undefined,
    pathInfos?: NavPathStack | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkNavigationComponent>((): ArkNavigationComponent => {
        return new ArkNavigationComponent()
    })
    NodeAttach<ArkNavigationPeer>((): ArkNavigationPeer => ArkNavigationPeer.create(receiver), (_: ArkNavigationPeer): void => {
        receiver.setNavigationOptions(pathInfos)
        style?.(receiver)
        withNavigationStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
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
        const value_name  = value.name
        let value_name_type : int32 = RuntimeType.UNDEFINED
        value_name_type = runtimeType(value_name)
        valueSerializer.writeInt8(value_name_type)
        if ((RuntimeType.UNDEFINED) != (value_name_type)) {
            const value_name_value  = value_name!
            valueSerializer.writeString(value_name_value)
        }
        const value_index  = value.index
        valueSerializer.writeNumber(value_index)
        const value_mode  = value.mode
        let value_mode_type : int32 = RuntimeType.UNDEFINED
        value_mode_type = runtimeType(value_mode)
        valueSerializer.writeInt8(value_mode_type)
        if ((RuntimeType.UNDEFINED) != (value_mode_type)) {
            const value_mode_value  = (value_mode as NavDestinationMode)
            valueSerializer.writeInt32(TypeChecker.NavDestinationMode_ToNumeric(value_mode_value))
        }
        const value_param  = value.param
        let value_param_type : int32 = RuntimeType.UNDEFINED
        value_param_type = runtimeType(value_param)
        valueSerializer.writeInt8(value_param_type)
        if ((RuntimeType.UNDEFINED) != (value_param_type)) {
            const value_param_value  = value_param!
            valueSerializer.holdAndWriteObject(value_param_value)
        }
        const value_navDestinationId  = value.navDestinationId
        let value_navDestinationId_type : int32 = RuntimeType.UNDEFINED
        value_navDestinationId_type = runtimeType(value_navDestinationId)
        valueSerializer.writeInt8(value_navDestinationId_type)
        if ((RuntimeType.UNDEFINED) != (value_navDestinationId_type)) {
            const value_navDestinationId_value  = value_navDestinationId!
            valueSerializer.writeString(value_navDestinationId_value)
        }
    }
    public static read(buffer: DeserializerBase): NavContentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const name_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let name_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (name_buf_runtimeType))
        {
            name_buf = (valueDeserializer.readString() as string)
        }
        const name_result : string | undefined = name_buf
        const index_result : number = (valueDeserializer.readNumber() as number)
        const mode_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let mode_buf : NavDestinationMode | undefined
        if ((RuntimeType.UNDEFINED) != (mode_buf_runtimeType))
        {
            mode_buf = TypeChecker.NavDestinationMode_FromNumeric(valueDeserializer.readInt32())
        }
        const mode_result : NavDestinationMode | undefined = mode_buf
        const param_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let param_buf : Object | undefined
        if ((RuntimeType.UNDEFINED) != (param_buf_runtimeType))
        {
            param_buf = (valueDeserializer.readObject() as object)
        }
        const param_result : Object | undefined = param_buf
        const navDestinationId_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let navDestinationId_buf : string | undefined
        if ((RuntimeType.UNDEFINED) != (navDestinationId_buf_runtimeType))
        {
            navDestinationId_buf = (valueDeserializer.readString() as string)
        }
        const navDestinationId_result : string | undefined = navDestinationId_buf
        let value : NavContentInfo = ({name: name_result, index: index_result, mode: mode_result, param: param_result, navDestinationId: navDestinationId_result} as NavContentInfo)
        return value
    }
}
export class NavigationAnimatedTransition_serializer {
    public static write(buffer: SerializerBase, value: NavigationAnimatedTransition): void {
        let valueSerializer : SerializerBase = buffer
        const value_onTransitionEnd  = value.onTransitionEnd
        let value_onTransitionEnd_type : int32 = RuntimeType.UNDEFINED
        value_onTransitionEnd_type = runtimeType(value_onTransitionEnd)
        valueSerializer.writeInt8(value_onTransitionEnd_type)
        if ((RuntimeType.UNDEFINED) != (value_onTransitionEnd_type)) {
            const value_onTransitionEnd_value  = value_onTransitionEnd!
            valueSerializer.holdAndWriteCallback(value_onTransitionEnd_value)
        }
        const value_timeout  = value.timeout
        let value_timeout_type : int32 = RuntimeType.UNDEFINED
        value_timeout_type = runtimeType(value_timeout)
        valueSerializer.writeInt8(value_timeout_type)
        if ((RuntimeType.UNDEFINED) != (value_timeout_type)) {
            const value_timeout_value  = value_timeout!
            valueSerializer.writeNumber(value_timeout_value)
        }
        const value_isInteractive  = value.isInteractive
        let value_isInteractive_type : int32 = RuntimeType.UNDEFINED
        value_isInteractive_type = runtimeType(value_isInteractive)
        valueSerializer.writeInt8(value_isInteractive_type)
        if ((RuntimeType.UNDEFINED) != (value_isInteractive_type)) {
            const value_isInteractive_value  = value_isInteractive!
            valueSerializer.writeBoolean(value_isInteractive_value)
        }
        const value_transition  = value.transition
        valueSerializer.holdAndWriteCallback(value_transition)
    }
    public static read(buffer: DeserializerBase): NavigationAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const onTransitionEnd_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onTransitionEnd_buf : ((isVisible: boolean) => void) | undefined
        if ((RuntimeType.UNDEFINED) != (onTransitionEnd_buf_runtimeType))
        {
            const onTransitionEnd_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onTransitionEnd_buf__call : KPointer = valueDeserializer.readPointer()
            const onTransitionEnd_buf__callSync : KPointer = valueDeserializer.readPointer()
            onTransitionEnd_buf = (isVisible: boolean):void => { 
    const onTransitionEnd_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onTransitionEnd_buf__argsSerializer.writeInt32(onTransitionEnd_buf__resource.resourceId);
    onTransitionEnd_buf__argsSerializer.writePointer(onTransitionEnd_buf__call);
    onTransitionEnd_buf__argsSerializer.writePointer(onTransitionEnd_buf__callSync);
    onTransitionEnd_buf__argsSerializer.writeBoolean(isVisible);
    InteropNativeModule._CallCallback(313269291, onTransitionEnd_buf__argsSerializer.asBuffer(), onTransitionEnd_buf__argsSerializer.length());
    onTransitionEnd_buf__argsSerializer.release();
    return; }
        }
        const onTransitionEnd_result : ((isVisible: boolean) => void) | undefined = onTransitionEnd_buf
        const timeout_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let timeout_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (timeout_buf_runtimeType))
        {
            timeout_buf = (valueDeserializer.readNumber() as number)
        }
        const timeout_result : number | undefined = timeout_buf
        const isInteractive_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let isInteractive_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (isInteractive_buf_runtimeType))
        {
            isInteractive_buf = valueDeserializer.readBoolean()
        }
        const isInteractive_result : boolean | undefined = isInteractive_buf
        const transition_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const transition_buf_call : KPointer = valueDeserializer.readPointer()
        const transition_buf_callSync : KPointer = valueDeserializer.readPointer()
        const transition_result : ((transitionProxy: NavigationTransitionProxy) => void) = (transitionProxy: NavigationTransitionProxy):void => { 
    const transition_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    transition_buf_argsSerializer.writeInt32(transition_buf_resource.resourceId);
    transition_buf_argsSerializer.writePointer(transition_buf_call);
    transition_buf_argsSerializer.writePointer(transition_buf_callSync);
    NavigationTransitionProxy_serializer.write(transition_buf_argsSerializer, transitionProxy);
    InteropNativeModule._CallCallback(-1375731066, transition_buf_argsSerializer.asBuffer(), transition_buf_argsSerializer.length());
    transition_buf_argsSerializer.release();
    return; }
        let value : NavigationAnimatedTransition = ({onTransitionEnd: onTransitionEnd_result, timeout: timeout_result, isInteractive: isInteractive_result, transition: transition_result} as NavigationAnimatedTransition)
        return value
    }
}
export class NavigationInterception_serializer {
    public static write(buffer: SerializerBase, value: NavigationInterception): void {
        let valueSerializer : SerializerBase = buffer
        const value_willShow  = value.willShow
        let value_willShow_type : int32 = RuntimeType.UNDEFINED
        value_willShow_type = runtimeType(value_willShow)
        valueSerializer.writeInt8(value_willShow_type)
        if ((RuntimeType.UNDEFINED) != (value_willShow_type)) {
            const value_willShow_value  = value_willShow!
            valueSerializer.holdAndWriteCallback(value_willShow_value)
        }
        const value_didShow  = value.didShow
        let value_didShow_type : int32 = RuntimeType.UNDEFINED
        value_didShow_type = runtimeType(value_didShow)
        valueSerializer.writeInt8(value_didShow_type)
        if ((RuntimeType.UNDEFINED) != (value_didShow_type)) {
            const value_didShow_value  = value_didShow!
            valueSerializer.holdAndWriteCallback(value_didShow_value)
        }
        const value_modeChange  = value.modeChange
        let value_modeChange_type : int32 = RuntimeType.UNDEFINED
        value_modeChange_type = runtimeType(value_modeChange)
        valueSerializer.writeInt8(value_modeChange_type)
        if ((RuntimeType.UNDEFINED) != (value_modeChange_type)) {
            const value_modeChange_value  = value_modeChange!
            valueSerializer.holdAndWriteCallback(value_modeChange_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationInterception {
        let valueDeserializer : DeserializerBase = buffer
        const willShow_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let willShow_buf : InterceptionShowCallback | undefined
        if ((RuntimeType.UNDEFINED) != (willShow_buf_runtimeType))
        {
            const willShow_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const willShow_buf__call : KPointer = valueDeserializer.readPointer()
            const willShow_buf__callSync : KPointer = valueDeserializer.readPointer()
            willShow_buf = (from: NavDestinationContext | NavBar, to: NavDestinationContext | NavBar, operation: NavigationOperation, isAnimated: boolean):void => { 
    const willShow_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    willShow_buf__argsSerializer.writeInt32(willShow_buf__resource.resourceId);
    willShow_buf__argsSerializer.writePointer(willShow_buf__call);
    willShow_buf__argsSerializer.writePointer(willShow_buf__callSync);
    let from_type : int32 = RuntimeType.UNDEFINED;
    from_type = runtimeType(from);
    if (RuntimeType.OBJECT == from_type) {
        willShow_buf__argsSerializer.writeInt8(0);
        const from_0  = from as NavDestinationContext;
        NavDestinationContext_serializer.write(willShow_buf__argsSerializer, from_0);
    }
    else if (RuntimeType.STRING == from_type) {
        willShow_buf__argsSerializer.writeInt8(1);
        const from_1  = from as NavBar;
        willShow_buf__argsSerializer.writeString(from_1);
    }
    let to_type : int32 = RuntimeType.UNDEFINED;
    to_type = runtimeType(to);
    if (RuntimeType.OBJECT == to_type) {
        willShow_buf__argsSerializer.writeInt8(0);
        const to_0  = to as NavDestinationContext;
        NavDestinationContext_serializer.write(willShow_buf__argsSerializer, to_0);
    }
    else if (RuntimeType.STRING == to_type) {
        willShow_buf__argsSerializer.writeInt8(1);
        const to_1  = to as NavBar;
        willShow_buf__argsSerializer.writeString(to_1);
    }
    willShow_buf__argsSerializer.writeInt32(TypeChecker.NavigationOperation_ToNumeric(operation));
    willShow_buf__argsSerializer.writeBoolean(isAnimated);
    InteropNativeModule._CallCallback(1852781814, willShow_buf__argsSerializer.asBuffer(), willShow_buf__argsSerializer.length());
    willShow_buf__argsSerializer.release();
    return; }
        }
        const willShow_result : InterceptionShowCallback | undefined = willShow_buf
        const didShow_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let didShow_buf : InterceptionShowCallback | undefined
        if ((RuntimeType.UNDEFINED) != (didShow_buf_runtimeType))
        {
            const didShow_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const didShow_buf__call : KPointer = valueDeserializer.readPointer()
            const didShow_buf__callSync : KPointer = valueDeserializer.readPointer()
            didShow_buf = (from: NavDestinationContext | NavBar, to: NavDestinationContext | NavBar, operation: NavigationOperation, isAnimated: boolean):void => { 
    const didShow_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    didShow_buf__argsSerializer.writeInt32(didShow_buf__resource.resourceId);
    didShow_buf__argsSerializer.writePointer(didShow_buf__call);
    didShow_buf__argsSerializer.writePointer(didShow_buf__callSync);
    let from_type : int32 = RuntimeType.UNDEFINED;
    from_type = runtimeType(from);
    if (RuntimeType.OBJECT == from_type) {
        didShow_buf__argsSerializer.writeInt8(0);
        const from_0  = from as NavDestinationContext;
        NavDestinationContext_serializer.write(didShow_buf__argsSerializer, from_0);
    }
    else if (RuntimeType.STRING == from_type) {
        didShow_buf__argsSerializer.writeInt8(1);
        const from_1  = from as NavBar;
        didShow_buf__argsSerializer.writeString(from_1);
    }
    let to_type : int32 = RuntimeType.UNDEFINED;
    to_type = runtimeType(to);
    if (RuntimeType.OBJECT == to_type) {
        didShow_buf__argsSerializer.writeInt8(0);
        const to_0  = to as NavDestinationContext;
        NavDestinationContext_serializer.write(didShow_buf__argsSerializer, to_0);
    }
    else if (RuntimeType.STRING == to_type) {
        didShow_buf__argsSerializer.writeInt8(1);
        const to_1  = to as NavBar;
        didShow_buf__argsSerializer.writeString(to_1);
    }
    didShow_buf__argsSerializer.writeInt32(TypeChecker.NavigationOperation_ToNumeric(operation));
    didShow_buf__argsSerializer.writeBoolean(isAnimated);
    InteropNativeModule._CallCallback(1852781814, didShow_buf__argsSerializer.asBuffer(), didShow_buf__argsSerializer.length());
    didShow_buf__argsSerializer.release();
    return; }
        }
        const didShow_result : InterceptionShowCallback | undefined = didShow_buf
        const modeChange_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let modeChange_buf : InterceptionModeCallback | undefined
        if ((RuntimeType.UNDEFINED) != (modeChange_buf_runtimeType))
        {
            const modeChange_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const modeChange_buf__call : KPointer = valueDeserializer.readPointer()
            const modeChange_buf__callSync : KPointer = valueDeserializer.readPointer()
            modeChange_buf = (mode: NavigationMode):void => { 
    const modeChange_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    modeChange_buf__argsSerializer.writeInt32(modeChange_buf__resource.resourceId);
    modeChange_buf__argsSerializer.writePointer(modeChange_buf__call);
    modeChange_buf__argsSerializer.writePointer(modeChange_buf__callSync);
    modeChange_buf__argsSerializer.writeInt32(TypeChecker.NavigationMode_ToNumeric(mode));
    InteropNativeModule._CallCallback(1502213270, modeChange_buf__argsSerializer.asBuffer(), modeChange_buf__argsSerializer.length());
    modeChange_buf__argsSerializer.release();
    return; }
        }
        const modeChange_result : InterceptionModeCallback | undefined = modeChange_buf
        let value : NavigationInterception = ({willShow: willShow_result, didShow: didShow_result, modeChange: modeChange_result} as NavigationInterception)
        return value
    }
}
export class NavigationOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_launchMode  = value.launchMode
        let value_launchMode_type : int32 = RuntimeType.UNDEFINED
        value_launchMode_type = runtimeType(value_launchMode)
        valueSerializer.writeInt8(value_launchMode_type)
        if ((RuntimeType.UNDEFINED) != (value_launchMode_type)) {
            const value_launchMode_value  = (value_launchMode as LaunchMode)
            valueSerializer.writeInt32(TypeChecker.LaunchMode_ToNumeric(value_launchMode_value))
        }
        const value_animated  = value.animated
        let value_animated_type : int32 = RuntimeType.UNDEFINED
        value_animated_type = runtimeType(value_animated)
        valueSerializer.writeInt8(value_animated_type)
        if ((RuntimeType.UNDEFINED) != (value_animated_type)) {
            const value_animated_value  = value_animated!
            valueSerializer.writeBoolean(value_animated_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const launchMode_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let launchMode_buf : LaunchMode | undefined
        if ((RuntimeType.UNDEFINED) != (launchMode_buf_runtimeType))
        {
            launchMode_buf = TypeChecker.LaunchMode_FromNumeric(valueDeserializer.readInt32())
        }
        const launchMode_result : LaunchMode | undefined = launchMode_buf
        const animated_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let animated_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (animated_buf_runtimeType))
        {
            animated_buf = valueDeserializer.readBoolean()
        }
        const animated_result : boolean | undefined = animated_buf
        let value : NavigationOptions = ({launchMode: launchMode_result, animated: animated_result} as NavigationOptions)
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
        const value_info  = value.info
        NavPathInfo_serializer.write(valueSerializer, value_info)
        const value_result  = value.result
        valueSerializer.holdAndWriteObject(value_result)
    }
    public static read(buffer: DeserializerBase): PopInfo {
        let valueDeserializer : DeserializerBase = buffer
        const info_result : NavPathInfo = (NavPathInfo_serializer.read(valueDeserializer) as NavPathInfo)
        const result_result : Object = (valueDeserializer.readObject() as object)
        let value : PopInfo = ({info: info_result, result: result_result} as PopInfo)
        return value
    }
}
export class NavigationCommonTitle_serializer {
    public static write(buffer: SerializerBase, value: NavigationCommonTitle): void {
        let valueSerializer : SerializerBase = buffer
        const value_main  = value.main
        let value_main_type : int32 = RuntimeType.UNDEFINED
        value_main_type = runtimeType(value_main)
        if (RuntimeType.STRING == value_main_type) {
            valueSerializer.writeInt8(0)
            const value_main_0  = value_main as string
            valueSerializer.writeString(value_main_0)
        }
        else if (RuntimeType.OBJECT == value_main_type) {
            valueSerializer.writeInt8(1)
            const value_main_1  = value_main as Resource
            Resource_serializer.write(valueSerializer, value_main_1)
        }
        const value_sub  = value.sub
        let value_sub_type : int32 = RuntimeType.UNDEFINED
        value_sub_type = runtimeType(value_sub)
        if (RuntimeType.STRING == value_sub_type) {
            valueSerializer.writeInt8(0)
            const value_sub_0  = value_sub as string
            valueSerializer.writeString(value_sub_0)
        }
        else if (RuntimeType.OBJECT == value_sub_type) {
            valueSerializer.writeInt8(1)
            const value_sub_1  = value_sub as Resource
            Resource_serializer.write(valueSerializer, value_sub_1)
        }
    }
    public static read(buffer: DeserializerBase): NavigationCommonTitle {
        let valueDeserializer : DeserializerBase = buffer
        const main_buf_selector : int32 = valueDeserializer.readInt8()
        let main_buf : string | Resource | undefined
        if (main_buf_selector == 0) {
            main_buf = (valueDeserializer.readString() as string)
        }
        else if (main_buf_selector == 1) {
            main_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for main_buf has to be chosen through deserialisation.")
        }
        const main_result : string | Resource = (main_buf as string | Resource)
        const sub_buf_selector : int32 = valueDeserializer.readInt8()
        let sub_buf : string | Resource | undefined
        if (sub_buf_selector == 0) {
            sub_buf = (valueDeserializer.readString() as string)
        }
        else if (sub_buf_selector == 1) {
            sub_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for sub_buf has to be chosen through deserialisation.")
        }
        const sub_result : string | Resource = (sub_buf as string | Resource)
        let value : NavigationCommonTitle = ({main: main_result, sub: sub_result} as NavigationCommonTitle)
        return value
    }
}
export class NavigationMenuItem_serializer {
    public static write(buffer: SerializerBase, value: NavigationMenuItem): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        if (RuntimeType.STRING == value_value_type) {
            valueSerializer.writeInt8(0)
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8(1)
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8(value_icon_type)
        if ((RuntimeType.UNDEFINED) != (value_icon_type)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8(0)
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8(1)
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8(value_symbolIcon_type)
        if ((RuntimeType.UNDEFINED) != (value_symbolIcon_type)) {
            const value_symbolIcon_value  = value_symbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolIcon_value)
        }
        const value_isEnabled  = value.isEnabled
        let value_isEnabled_type : int32 = RuntimeType.UNDEFINED
        value_isEnabled_type = runtimeType(value_isEnabled)
        valueSerializer.writeInt8(value_isEnabled_type)
        if ((RuntimeType.UNDEFINED) != (value_isEnabled_type)) {
            const value_isEnabled_value  = value_isEnabled!
            valueSerializer.writeBoolean(value_isEnabled_value)
        }
        const value_action  = value.action
        let value_action_type : int32 = RuntimeType.UNDEFINED
        value_action_type = runtimeType(value_action)
        valueSerializer.writeInt8(value_action_type)
        if ((RuntimeType.UNDEFINED) != (value_action_type)) {
            const value_action_value  = value_action!
            valueSerializer.holdAndWriteCallback(value_action_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationMenuItem {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == 0) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : string | Resource = (value_buf as string | Resource)
        const icon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let icon_buf : string | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (icon_buf_runtimeType))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == 0) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == 1) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : string | Resource | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((RuntimeType.UNDEFINED) != (symbolIcon_buf_runtimeType))
        {
            symbolIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolIcon_result : SymbolGlyphModifier | undefined = symbolIcon_buf
        const isEnabled_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let isEnabled_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (isEnabled_buf_runtimeType))
        {
            isEnabled_buf = valueDeserializer.readBoolean()
        }
        const isEnabled_result : boolean | undefined = isEnabled_buf
        const action_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let action_buf : (() => void) | undefined
        if ((RuntimeType.UNDEFINED) != (action_buf_runtimeType))
        {
            const action_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const action_buf__call : KPointer = valueDeserializer.readPointer()
            const action_buf__callSync : KPointer = valueDeserializer.readPointer()
            action_buf = ():void => { 
    const action_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    action_buf__argsSerializer.writeInt32(action_buf__resource.resourceId);
    action_buf__argsSerializer.writePointer(action_buf__call);
    action_buf__argsSerializer.writePointer(action_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, action_buf__argsSerializer.asBuffer(), action_buf__argsSerializer.length());
    action_buf__argsSerializer.release();
    return; }
        }
        const action_result : (() => void) | undefined = action_buf
        let value : NavigationMenuItem = ({value: value_result, icon: icon_result, symbolIcon: symbolIcon_result, isEnabled: isEnabled_result, action: action_result} as NavigationMenuItem)
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
        const value_value  = value.value
        let value_value_type : int32 = RuntimeType.UNDEFINED
        value_value_type = runtimeType(value_value)
        if (RuntimeType.STRING == value_value_type) {
            valueSerializer.writeInt8(0)
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8(1)
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8(value_icon_type)
        if ((RuntimeType.UNDEFINED) != (value_icon_type)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8(0)
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8(1)
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8(value_symbolIcon_type)
        if ((RuntimeType.UNDEFINED) != (value_symbolIcon_type)) {
            const value_symbolIcon_value  = value_symbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolIcon_value)
        }
        const value_action  = value.action
        let value_action_type : int32 = RuntimeType.UNDEFINED
        value_action_type = runtimeType(value_action)
        valueSerializer.writeInt8(value_action_type)
        if ((RuntimeType.UNDEFINED) != (value_action_type)) {
            const value_action_value  = value_action!
            valueSerializer.holdAndWriteCallback(value_action_value)
        }
        const value_status  = value.status
        let value_status_type : int32 = RuntimeType.UNDEFINED
        value_status_type = runtimeType(value_status)
        valueSerializer.writeInt8(value_status_type)
        if ((RuntimeType.UNDEFINED) != (value_status_type)) {
            const value_status_value  = (value_status as ToolbarItemStatus)
            valueSerializer.writeInt32(TypeChecker.ToolbarItemStatus_ToNumeric(value_status_value))
        }
        const value_activeIcon  = value.activeIcon
        let value_activeIcon_type : int32 = RuntimeType.UNDEFINED
        value_activeIcon_type = runtimeType(value_activeIcon)
        valueSerializer.writeInt8(value_activeIcon_type)
        if ((RuntimeType.UNDEFINED) != (value_activeIcon_type)) {
            const value_activeIcon_value  = value_activeIcon!
            let value_activeIcon_value_type : int32 = RuntimeType.UNDEFINED
            value_activeIcon_value_type = runtimeType(value_activeIcon_value)
            if (RuntimeType.STRING == value_activeIcon_value_type) {
                valueSerializer.writeInt8(0)
                const value_activeIcon_value_0  = value_activeIcon_value as string
                valueSerializer.writeString(value_activeIcon_value_0)
            }
            else if (RuntimeType.OBJECT == value_activeIcon_value_type) {
                valueSerializer.writeInt8(1)
                const value_activeIcon_value_1  = value_activeIcon_value as Resource
                Resource_serializer.write(valueSerializer, value_activeIcon_value_1)
            }
        }
        const value_activeSymbolIcon  = value.activeSymbolIcon
        let value_activeSymbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_activeSymbolIcon_type = runtimeType(value_activeSymbolIcon)
        valueSerializer.writeInt8(value_activeSymbolIcon_type)
        if ((RuntimeType.UNDEFINED) != (value_activeSymbolIcon_type)) {
            const value_activeSymbolIcon_value  = value_activeSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_activeSymbolIcon_value)
        }
    }
    public static read(buffer: DeserializerBase): ToolbarItem {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == 0) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == 1) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : ResourceStr = (value_buf as string | Resource)
        const icon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let icon_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (icon_buf_runtimeType))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == 0) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == 1) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((RuntimeType.UNDEFINED) != (symbolIcon_buf_runtimeType))
        {
            symbolIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolIcon_result : SymbolGlyphModifier | undefined = symbolIcon_buf
        const action_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let action_buf : (() => void) | undefined
        if ((RuntimeType.UNDEFINED) != (action_buf_runtimeType))
        {
            const action_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const action_buf__call : KPointer = valueDeserializer.readPointer()
            const action_buf__callSync : KPointer = valueDeserializer.readPointer()
            action_buf = ():void => { 
    const action_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    action_buf__argsSerializer.writeInt32(action_buf__resource.resourceId);
    action_buf__argsSerializer.writePointer(action_buf__call);
    action_buf__argsSerializer.writePointer(action_buf__callSync);
    InteropNativeModule._CallCallback(-1867723152, action_buf__argsSerializer.asBuffer(), action_buf__argsSerializer.length());
    action_buf__argsSerializer.release();
    return; }
        }
        const action_result : (() => void) | undefined = action_buf
        const status_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let status_buf : ToolbarItemStatus | undefined
        if ((RuntimeType.UNDEFINED) != (status_buf_runtimeType))
        {
            status_buf = TypeChecker.ToolbarItemStatus_FromNumeric(valueDeserializer.readInt32())
        }
        const status_result : ToolbarItemStatus | undefined = status_buf
        const activeIcon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let activeIcon_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (activeIcon_buf_runtimeType))
        {
            const activeIcon_buf__selector : int32 = valueDeserializer.readInt8()
            let activeIcon_buf_ : string | Resource | undefined
            if (activeIcon_buf__selector == 0) {
                activeIcon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (activeIcon_buf__selector == 1) {
                activeIcon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for activeIcon_buf_ has to be chosen through deserialisation.")
            }
            activeIcon_buf = (activeIcon_buf_ as string | Resource)
        }
        const activeIcon_result : ResourceStr | undefined = activeIcon_buf
        const activeSymbolIcon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let activeSymbolIcon_buf : SymbolGlyphModifier | undefined
        if ((RuntimeType.UNDEFINED) != (activeSymbolIcon_buf_runtimeType))
        {
            activeSymbolIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const activeSymbolIcon_result : SymbolGlyphModifier | undefined = activeSymbolIcon_buf
        let value : ToolbarItem = ({value: value_result, icon: icon_result, symbolIcon: symbolIcon_result, action: action_result, status: status_result, activeIcon: activeIcon_result, activeSymbolIcon: activeSymbolIcon_result} as ToolbarItem)
        return value
    }
}
export class MoreButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: MoreButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_backgroundBlurStyle  = value.backgroundBlurStyle
        let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
        valueSerializer.writeInt8(value_backgroundBlurStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyle_type)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8(value_backgroundBlurStyleOptions_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyleOptions_type)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8(value_backgroundEffect_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundEffect_type)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
    }
    public static read(buffer: DeserializerBase): MoreButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundBlurStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundBlurStyle_buf_runtimeType))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundBlurStyleOptions_buf_runtimeType))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundEffect_buf_runtimeType))
        {
            backgroundEffect_buf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffect_result : BackgroundEffectOptions | undefined = backgroundEffect_buf
        let value : MoreButtonOptions = ({backgroundBlurStyle: backgroundBlurStyle_result, backgroundBlurStyleOptions: backgroundBlurStyleOptions_result, backgroundEffect: backgroundEffect_result} as MoreButtonOptions)
        return value
    }
}
export class NavigationCustomTitle_serializer {
    public static write(buffer: SerializerBase, value: NavigationCustomTitle): void {
        let valueSerializer : SerializerBase = buffer
        const value_builder  = value.builder
        valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_builder))
        const value_height  = value.height
        let value_height_type : int32 = RuntimeType.UNDEFINED
        value_height_type = runtimeType(value_height)
        if (TypeChecker.isTitleHeight(value_height)) {
            valueSerializer.writeInt8(0)
            const value_height_0  = value_height as TitleHeight
            valueSerializer.writeInt32(TypeChecker.TitleHeight_ToNumeric(value_height_0))
        }
        else if ((RuntimeType.STRING == value_height_type) || (RuntimeType.NUMBER == value_height_type) || (RuntimeType.OBJECT == value_height_type)) {
            valueSerializer.writeInt8(1)
            const value_height_1  = value_height as Length
            let value_height_1_type : int32 = RuntimeType.UNDEFINED
            value_height_1_type = runtimeType(value_height_1)
            if (RuntimeType.STRING == value_height_1_type) {
                valueSerializer.writeInt8(0)
                const value_height_1_0  = value_height_1 as string
                valueSerializer.writeString(value_height_1_0)
            }
            else if (RuntimeType.NUMBER == value_height_1_type) {
                valueSerializer.writeInt8(1)
                const value_height_1_1  = value_height_1 as number
                valueSerializer.writeNumber(value_height_1_1)
            }
            else if (RuntimeType.OBJECT == value_height_1_type) {
                valueSerializer.writeInt8(2)
                const value_height_1_2  = value_height_1 as Resource
                Resource_serializer.write(valueSerializer, value_height_1_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): NavigationCustomTitle {
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
        if (height_buf_selector == 0) {
            height_buf = TypeChecker.TitleHeight_FromNumeric(valueDeserializer.readInt32())
        }
        else if (height_buf_selector == 1) {
            const height_buf_u_selector : int32 = valueDeserializer.readInt8()
            let height_buf_u : string | number | Resource | undefined
            if (height_buf_u_selector == 0) {
                height_buf_u = (valueDeserializer.readString() as string)
            }
            else if (height_buf_u_selector == 1) {
                height_buf_u = (valueDeserializer.readNumber() as number)
            }
            else if (height_buf_u_selector == 2) {
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
        let value : NavigationCustomTitle = ({builder: builder_result, height: height_result} as NavigationCustomTitle)
        return value
    }
}
export class NavigationTitleOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationTitleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_backgroundColor  = value.backgroundColor
        let value_backgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_backgroundColor_type = runtimeType(value_backgroundColor)
        valueSerializer.writeInt8(value_backgroundColor_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundColor_type)) {
            const value_backgroundColor_value  = value_backgroundColor!
            let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
            if (TypeChecker.isColor(value_backgroundColor_value)) {
                valueSerializer.writeInt8(0)
                const value_backgroundColor_value_0  = value_backgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_backgroundColor_value_1  = value_backgroundColor_value as number
                valueSerializer.writeNumber(value_backgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_backgroundColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_backgroundColor_value_2  = value_backgroundColor_value as string
                valueSerializer.writeString(value_backgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundColor_value_3)
            }
        }
        const value_backgroundBlurStyle  = value.backgroundBlurStyle
        let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
        valueSerializer.writeInt8(value_backgroundBlurStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyle_type)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8(value_backgroundBlurStyleOptions_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyleOptions_type)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8(value_backgroundEffect_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundEffect_type)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
        const value_barStyle  = value.barStyle
        let value_barStyle_type : int32 = RuntimeType.UNDEFINED
        value_barStyle_type = runtimeType(value_barStyle)
        valueSerializer.writeInt8(value_barStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_barStyle_type)) {
            const value_barStyle_value  = (value_barStyle as BarStyle)
            valueSerializer.writeInt32(TypeChecker.BarStyle_ToNumeric(value_barStyle_value))
        }
        const value_paddingStart  = value.paddingStart
        let value_paddingStart_type : int32 = RuntimeType.UNDEFINED
        value_paddingStart_type = runtimeType(value_paddingStart)
        valueSerializer.writeInt8(value_paddingStart_type)
        if ((RuntimeType.UNDEFINED) != (value_paddingStart_type)) {
            const value_paddingStart_value  = value_paddingStart!
            LengthMetrics_serializer.write(valueSerializer, value_paddingStart_value)
        }
        const value_paddingEnd  = value.paddingEnd
        let value_paddingEnd_type : int32 = RuntimeType.UNDEFINED
        value_paddingEnd_type = runtimeType(value_paddingEnd)
        valueSerializer.writeInt8(value_paddingEnd_type)
        if ((RuntimeType.UNDEFINED) != (value_paddingEnd_type)) {
            const value_paddingEnd_value  = value_paddingEnd!
            LengthMetrics_serializer.write(valueSerializer, value_paddingEnd_value)
        }
        const value_mainTitleModifier  = value.mainTitleModifier
        let value_mainTitleModifier_type : int32 = RuntimeType.UNDEFINED
        value_mainTitleModifier_type = runtimeType(value_mainTitleModifier)
        valueSerializer.writeInt8(value_mainTitleModifier_type)
        if ((RuntimeType.UNDEFINED) != (value_mainTitleModifier_type)) {
            const value_mainTitleModifier_value  = value_mainTitleModifier!
            TextModifier_serializer.write(valueSerializer, value_mainTitleModifier_value)
        }
        const value_subTitleModifier  = value.subTitleModifier
        let value_subTitleModifier_type : int32 = RuntimeType.UNDEFINED
        value_subTitleModifier_type = runtimeType(value_subTitleModifier)
        valueSerializer.writeInt8(value_subTitleModifier_type)
        if ((RuntimeType.UNDEFINED) != (value_subTitleModifier_type)) {
            const value_subTitleModifier_value  = value_subTitleModifier!
            TextModifier_serializer.write(valueSerializer, value_subTitleModifier_value)
        }
        const value_enableHoverMode  = value.enableHoverMode
        let value_enableHoverMode_type : int32 = RuntimeType.UNDEFINED
        value_enableHoverMode_type = runtimeType(value_enableHoverMode)
        valueSerializer.writeInt8(value_enableHoverMode_type)
        if ((RuntimeType.UNDEFINED) != (value_enableHoverMode_type)) {
            const value_enableHoverMode_value  = value_enableHoverMode!
            valueSerializer.writeBoolean(value_enableHoverMode_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationTitleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundColor_buf_runtimeType))
        {
            const backgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundColor_buf_ : Color | number | string | Resource | undefined
            if (backgroundColor_buf__selector == 0) {
                backgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (backgroundColor_buf__selector == 1) {
                backgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundColor_buf__selector == 2) {
                backgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundColor_buf__selector == 3) {
                backgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundColor_buf_ has to be chosen through deserialisation.")
            }
            backgroundColor_buf = (backgroundColor_buf_ as Color | number | string | Resource)
        }
        const backgroundColor_result : ResourceColor | undefined = backgroundColor_buf
        const backgroundBlurStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundBlurStyle_buf_runtimeType))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundBlurStyleOptions_buf_runtimeType))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundEffect_buf_runtimeType))
        {
            backgroundEffect_buf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffect_result : BackgroundEffectOptions | undefined = backgroundEffect_buf
        const barStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let barStyle_buf : BarStyle | undefined
        if ((RuntimeType.UNDEFINED) != (barStyle_buf_runtimeType))
        {
            barStyle_buf = TypeChecker.BarStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const barStyle_result : BarStyle | undefined = barStyle_buf
        const paddingStart_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let paddingStart_buf : LengthMetrics | undefined
        if ((RuntimeType.UNDEFINED) != (paddingStart_buf_runtimeType))
        {
            paddingStart_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const paddingStart_result : LengthMetrics | undefined = paddingStart_buf
        const paddingEnd_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let paddingEnd_buf : LengthMetrics | undefined
        if ((RuntimeType.UNDEFINED) != (paddingEnd_buf_runtimeType))
        {
            paddingEnd_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const paddingEnd_result : LengthMetrics | undefined = paddingEnd_buf
        const mainTitleModifier_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let mainTitleModifier_buf : TextModifier | undefined
        if ((RuntimeType.UNDEFINED) != (mainTitleModifier_buf_runtimeType))
        {
            mainTitleModifier_buf = TextModifier_serializer.read(valueDeserializer)
        }
        const mainTitleModifier_result : TextModifier | undefined = mainTitleModifier_buf
        const subTitleModifier_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let subTitleModifier_buf : TextModifier | undefined
        if ((RuntimeType.UNDEFINED) != (subTitleModifier_buf_runtimeType))
        {
            subTitleModifier_buf = TextModifier_serializer.read(valueDeserializer)
        }
        const subTitleModifier_result : TextModifier | undefined = subTitleModifier_buf
        const enableHoverMode_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let enableHoverMode_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (enableHoverMode_buf_runtimeType))
        {
            enableHoverMode_buf = valueDeserializer.readBoolean()
        }
        const enableHoverMode_result : boolean | undefined = enableHoverMode_buf
        let value : NavigationTitleOptions = ({backgroundColor: backgroundColor_result, backgroundBlurStyle: backgroundBlurStyle_result, backgroundBlurStyleOptions: backgroundBlurStyleOptions_result, backgroundEffect: backgroundEffect_result, barStyle: barStyle_result, paddingStart: paddingStart_result, paddingEnd: paddingEnd_result, mainTitleModifier: mainTitleModifier_result, subTitleModifier: subTitleModifier_result, enableHoverMode: enableHoverMode_result} as NavigationTitleOptions)
        return value
    }
}
export class NavigationMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_moreButtonOptions  = value.moreButtonOptions
        let value_moreButtonOptions_type : int32 = RuntimeType.UNDEFINED
        value_moreButtonOptions_type = runtimeType(value_moreButtonOptions)
        valueSerializer.writeInt8(value_moreButtonOptions_type)
        if ((RuntimeType.UNDEFINED) != (value_moreButtonOptions_type)) {
            const value_moreButtonOptions_value  = value_moreButtonOptions!
            MoreButtonOptions_serializer.write(valueSerializer, value_moreButtonOptions_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const moreButtonOptions_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let moreButtonOptions_buf : MoreButtonOptions | undefined
        if ((RuntimeType.UNDEFINED) != (moreButtonOptions_buf_runtimeType))
        {
            moreButtonOptions_buf = MoreButtonOptions_serializer.read(valueDeserializer)
        }
        const moreButtonOptions_result : MoreButtonOptions | undefined = moreButtonOptions_buf
        let value : NavigationMenuOptions = ({moreButtonOptions: moreButtonOptions_result} as NavigationMenuOptions)
        return value
    }
}
export class NavigationToolbarOptions_serializer {
    public static write(buffer: SerializerBase, value: NavigationToolbarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_backgroundColor  = value.backgroundColor
        let value_backgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_backgroundColor_type = runtimeType(value_backgroundColor)
        valueSerializer.writeInt8(value_backgroundColor_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundColor_type)) {
            const value_backgroundColor_value  = value_backgroundColor!
            let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
            if (TypeChecker.isColor(value_backgroundColor_value)) {
                valueSerializer.writeInt8(0)
                const value_backgroundColor_value_0  = value_backgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_backgroundColor_value_1  = value_backgroundColor_value as number
                valueSerializer.writeNumber(value_backgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_backgroundColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_backgroundColor_value_2  = value_backgroundColor_value as string
                valueSerializer.writeString(value_backgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundColor_value_3)
            }
        }
        const value_backgroundBlurStyle  = value.backgroundBlurStyle
        let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
        valueSerializer.writeInt8(value_backgroundBlurStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyle_type)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8(value_backgroundBlurStyleOptions_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundBlurStyleOptions_type)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8(value_backgroundEffect_type)
        if ((RuntimeType.UNDEFINED) != (value_backgroundEffect_type)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
        const value_moreButtonOptions  = value.moreButtonOptions
        let value_moreButtonOptions_type : int32 = RuntimeType.UNDEFINED
        value_moreButtonOptions_type = runtimeType(value_moreButtonOptions)
        valueSerializer.writeInt8(value_moreButtonOptions_type)
        if ((RuntimeType.UNDEFINED) != (value_moreButtonOptions_type)) {
            const value_moreButtonOptions_value  = value_moreButtonOptions!
            MoreButtonOptions_serializer.write(valueSerializer, value_moreButtonOptions_value)
        }
        const value_barStyle  = value.barStyle
        let value_barStyle_type : int32 = RuntimeType.UNDEFINED
        value_barStyle_type = runtimeType(value_barStyle)
        valueSerializer.writeInt8(value_barStyle_type)
        if ((RuntimeType.UNDEFINED) != (value_barStyle_type)) {
            const value_barStyle_value  = (value_barStyle as BarStyle)
            valueSerializer.writeInt32(TypeChecker.BarStyle_ToNumeric(value_barStyle_value))
        }
        const value_hideItemValue  = value.hideItemValue
        let value_hideItemValue_type : int32 = RuntimeType.UNDEFINED
        value_hideItemValue_type = runtimeType(value_hideItemValue)
        valueSerializer.writeInt8(value_hideItemValue_type)
        if ((RuntimeType.UNDEFINED) != (value_hideItemValue_type)) {
            const value_hideItemValue_value  = value_hideItemValue!
            valueSerializer.writeBoolean(value_hideItemValue_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationToolbarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundColor_buf_runtimeType))
        {
            const backgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundColor_buf_ : Color | number | string | Resource | undefined
            if (backgroundColor_buf__selector == 0) {
                backgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (backgroundColor_buf__selector == 1) {
                backgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundColor_buf__selector == 2) {
                backgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundColor_buf__selector == 3) {
                backgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundColor_buf_ has to be chosen through deserialisation.")
            }
            backgroundColor_buf = (backgroundColor_buf_ as Color | number | string | Resource)
        }
        const backgroundColor_result : ResourceColor | undefined = backgroundColor_buf
        const backgroundBlurStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundBlurStyle_buf_runtimeType))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundBlurStyleOptions_buf_runtimeType))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((RuntimeType.UNDEFINED) != (backgroundEffect_buf_runtimeType))
        {
            backgroundEffect_buf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffect_result : BackgroundEffectOptions | undefined = backgroundEffect_buf
        const moreButtonOptions_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let moreButtonOptions_buf : MoreButtonOptions | undefined
        if ((RuntimeType.UNDEFINED) != (moreButtonOptions_buf_runtimeType))
        {
            moreButtonOptions_buf = MoreButtonOptions_serializer.read(valueDeserializer)
        }
        const moreButtonOptions_result : MoreButtonOptions | undefined = moreButtonOptions_buf
        const barStyle_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let barStyle_buf : BarStyle | undefined
        if ((RuntimeType.UNDEFINED) != (barStyle_buf_runtimeType))
        {
            barStyle_buf = TypeChecker.BarStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const barStyle_result : BarStyle | undefined = barStyle_buf
        const hideItemValue_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let hideItemValue_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (hideItemValue_buf_runtimeType))
        {
            hideItemValue_buf = valueDeserializer.readBoolean()
        }
        const hideItemValue_result : boolean | undefined = hideItemValue_buf
        let value : NavigationToolbarOptions = ({backgroundColor: backgroundColor_result, backgroundBlurStyle: backgroundBlurStyle_result, backgroundBlurStyleOptions: backgroundBlurStyleOptions_result, backgroundEffect: backgroundEffect_result, moreButtonOptions: moreButtonOptions_result, barStyle: barStyle_result, hideItemValue: hideItemValue_result} as NavigationToolbarOptions)
        return value
    }
}
