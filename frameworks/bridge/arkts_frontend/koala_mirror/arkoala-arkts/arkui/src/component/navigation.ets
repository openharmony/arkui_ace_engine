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
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { image_PixelMap_serializer, image } from "./../generated/ohos.multimedia.image"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { window_SystemBarStyle_serializer, window } from "./../generated/ohos.window"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer } from "./common"
import { CustomBuilder, PageMapBuilder } from "./builder"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { TextModifier, TextModifier_serializer } from "./../generated/arkui.TextModifier"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : boolean | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private setIsInteractive_serialize(isInteractive: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let isInteractive_type : int32 = RuntimeType.UNDEFINED
        isInteractive_type = runtimeType(isInteractive)
        thisSerializer.writeInt8((isInteractive_type).toChar())
        if ((isInteractive_type) != (RuntimeType.UNDEFINED)) {
            const isInteractive_value  = isInteractive!
            thisSerializer.writeBoolean(isInteractive_value)
        }
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setIsInteractive(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getCancelTransition_serialize(): VoidCallback | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getCancelTransition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : VoidCallback | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
    private setCancelTransition_serialize(cancelTransition: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let cancelTransition_type : int32 = RuntimeType.UNDEFINED
        cancelTransition_type = runtimeType(cancelTransition)
        thisSerializer.writeInt8((cancelTransition_type).toChar())
        if ((cancelTransition_type) != (RuntimeType.UNDEFINED)) {
            const cancelTransition_value  = cancelTransition!
            thisSerializer.holdAndWriteCallback(cancelTransition_value)
        }
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setCancelTransition(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getUpdateTransition_serialize(): UpdateTransitionCallback | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getUpdateTransition(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : UpdateTransitionCallback | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
    private setUpdateTransition_serialize(updateTransition: UpdateTransitionCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let updateTransition_type : int32 = RuntimeType.UNDEFINED
        updateTransition_type = runtimeType(updateTransition)
        thisSerializer.writeInt8((updateTransition_type).toChar())
        if ((updateTransition_type) != (RuntimeType.UNDEFINED)) {
            const updateTransition_value  = updateTransition!
            thisSerializer.holdAndWriteCallback(updateTransition_value)
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
    constructor(_0: boolean, _1: boolean, _2: boolean, _3: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, NavPathInfo.getFinalizer())
    }
    constructor(name: string, param: Object | undefined, onPop?: ((value0: PopInfo) => void), isEntry?: boolean) {
        this(false, false, false, false, NavPathInfo.construct(name, param, onPop, isEntry))
    }
    static construct(name: string, param: Object | undefined, onPop?: ((value0: PopInfo) => void), isEntry?: boolean): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let param_type : int32 = RuntimeType.UNDEFINED
        param_type = runtimeType(param)
        thisSerializer.writeInt8((param_type).toChar())
        if ((param_type) != (RuntimeType.UNDEFINED)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        let onPop_type : int32 = RuntimeType.UNDEFINED
        onPop_type = runtimeType(onPop)
        thisSerializer.writeInt8((onPop_type).toChar())
        if ((onPop_type) != (RuntimeType.UNDEFINED)) {
            const onPop_value  = onPop!
            thisSerializer.holdAndWriteCallback(onPop_value)
        }
        let isEntry_type : int32 = RuntimeType.UNDEFINED
        isEntry_type = runtimeType(isEntry)
        thisSerializer.writeInt8((isEntry_type).toChar())
        if ((isEntry_type) != (RuntimeType.UNDEFINED)) {
            const isEntry_value  = isEntry!
            thisSerializer.writeBoolean(isEntry_value)
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
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : Object | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
        thisSerializer.writeInt8((param_type).toChar())
        if ((param_type) != (RuntimeType.UNDEFINED)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setParam(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnPop_serialize(): ((value0: PopInfo) => void) | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getOnPop(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : ((value0: PopInfo) => void) | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
        thisSerializer.writeInt8((onPop_type).toChar())
        if ((onPop_type) != (RuntimeType.UNDEFINED)) {
            const onPop_value  = onPop!
            thisSerializer.holdAndWriteCallback(onPop_value)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setOnPop(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsEntry_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getIsEntry(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : boolean | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
        thisSerializer.writeInt8((isEntry_type).toChar())
        if ((isEntry_type) != (RuntimeType.UNDEFINED)) {
            const isEntry_value  = isEntry!
            thisSerializer.writeBoolean(isEntry_value)
        }
        ArkUIGeneratedNativeModule._NavPathInfo_setIsEntry(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getNavDestinationId_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getNavDestinationId(this.peer!.ptr)
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
    public pushPathByName(name: string, param: Object | undefined, animated?: boolean): void {
        const name_casted = name as (string)
        const param_casted = param as (Object | undefined)
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
    public pop(animated?: boolean): NavPathInfo | undefined {
        const animated_casted = animated as (boolean | undefined)
        return this.pop0_serialize(animated_casted)
    }
    public pop(result: Object, animated?: boolean): NavPathInfo | undefined {
        const result_casted = result as (Object)
        const animated_casted = animated as (boolean | undefined)
        return this.pop1_serialize(result_casted, animated_casted)
    }
    public popToName(name: string, animated?: boolean): number {
        const name_casted = name as (string)
        const animated_casted = animated as (boolean | undefined)
        return this.popToName0_serialize(name_casted, animated_casted)
    }
    public popToName(name: string, result: Object, animated?: boolean): number {
        const name_casted = name as (string)
        const result_casted = result as (Object)
        const animated_casted = animated as (boolean | undefined)
        return this.popToName1_serialize(name_casted, result_casted, animated_casted)
    }
    public popToIndex(index: number, animated?: boolean): void {
        const index_casted = index as (number)
        const animated_casted = animated as (boolean | undefined)
        this.popToIndex0_serialize(index_casted, animated_casted)
        return
    }
    public popToIndex(index: number, result: Object, animated?: boolean): void {
        const index_casted = index as (number)
        const result_casted = result as (Object)
        const animated_casted = animated as (boolean | undefined)
        this.popToIndex1_serialize(index_casted, result_casted, animated_casted)
        return
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((param_type).toChar())
        if ((param_type) != (RuntimeType.UNDEFINED)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePathByName(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeByIndexes_serialize(indexes: Array<number>): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((indexes.length).toInt())
        for (let indexes_counter_i = 0; indexes_counter_i < indexes.length; indexes_counter_i++) {
            const indexes_element : number = indexes[indexes_counter_i]
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : NavPathInfo | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : NavPathInfo | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : Object | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
            const buffer_buf_runtimeType  = retvalDeserializer.readInt8().toInt()
            let buffer_buf : Object | undefined
            if ((buffer_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : NavPathStack | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
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
        thisSerializer.writeInt32((pathStack.length).toInt())
        for (let pathStack_counter_i = 0; pathStack_counter_i < pathStack.length; pathStack_counter_i++) {
            const pathStack_element : NavPathInfo = pathStack[pathStack_counter_i]
            NavPathInfo_serializer.write(thisSerializer, pathStack_element)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8((animated_type).toChar())
        if ((animated_type) != (RuntimeType.UNDEFINED)) {
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
    setNavBarWidthAttribute(value: Length | undefined): void {
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
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setNavBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNavBarPositionAttribute(value: NavBarPosition | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as NavBarPosition)
            thisSerializer.writeInt32(TypeChecker.NavBarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setNavBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNavBarWidthRangeAttribute(value: [ Dimension, Dimension ] | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            const value_value_0  = value_value[0]
            let value_value_0_type : int32 = RuntimeType.UNDEFINED
            value_value_0_type = runtimeType(value_value_0)
            if (RuntimeType.STRING == value_value_0_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0_0  = value_value_0 as string
                thisSerializer.writeString(value_value_0_0)
            }
            else if (RuntimeType.NUMBER == value_value_0_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_0_1  = value_value_0 as number
                thisSerializer.writeNumber(value_value_0_1)
            }
            else if (RuntimeType.OBJECT == value_value_0_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_0_2  = value_value_0 as Resource
                Resource_serializer.write(thisSerializer, value_value_0_2)
            }
            const value_value_1  = value_value[1]
            let value_value_1_type : int32 = RuntimeType.UNDEFINED
            value_value_1_type = runtimeType(value_value_1)
            if (RuntimeType.STRING == value_value_1_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_1_0  = value_value_1 as string
                thisSerializer.writeString(value_value_1_0)
            }
            else if (RuntimeType.NUMBER == value_value_1_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1_1  = value_value_1 as number
                thisSerializer.writeNumber(value_value_1_1)
            }
            else if (RuntimeType.OBJECT == value_value_1_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_1_2  = value_value_1 as Resource
                Resource_serializer.write(thisSerializer, value_value_1_2)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setNavBarWidthRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinContentWidthAttribute(value: Dimension | undefined): void {
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
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setMinContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setModeAttribute(value: NavigationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as NavigationMode)
            thisSerializer.writeInt32(TypeChecker.NavigationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackButtonIcon0Attribute(value: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined): void {
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
            else if (TypeChecker.isimage_PixelMap(value_value, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, value_value_1)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setBackButtonIcon0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideNavBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideNavBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideTitleBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideBackButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTitleModeAttribute(value: NavigationTitleMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as NavigationTitleMode)
            thisSerializer.writeInt32(TypeChecker.NavigationTitleMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setTitleMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setMenus0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideToolBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideToolBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableToolBarAdaptationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setEnableToolBarAdaptation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTitleModeChangeAttribute(value: ((titleMode: NavigationTitleMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setOnTitleModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNavBarStateChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setOnNavBarStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnNavigationModeChangeAttribute(value: ((mode: NavigationMode) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setOnNavigationModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNavDestinationAttribute(value: PageMapBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setNavDestination(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomNavContentTransitionAttribute(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setCustomNavContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setSystemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setRecoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDragBarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setEnableDragBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableModeChangeAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setEnableModeChangeAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackButtonIcon1Attribute(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let icon_type : int32 = RuntimeType.UNDEFINED
        icon_type = runtimeType(icon)
        thisSerializer.writeInt8((icon_type).toChar())
        if ((icon_type) != (RuntimeType.UNDEFINED)) {
            const icon_value  = icon!
            let icon_value_type : int32 = RuntimeType.UNDEFINED
            icon_value_type = runtimeType(icon_value)
            if (RuntimeType.STRING == icon_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const icon_value_0  = icon_value as string
                thisSerializer.writeString(icon_value_0)
            }
            else if (TypeChecker.isimage_PixelMap(icon_value, false, false)) {
                thisSerializer.writeInt8((1).toChar())
                const icon_value_1  = icon_value as image.PixelMap
                image_PixelMap_serializer.write(thisSerializer, icon_value_1)
            }
            else if (TypeChecker.isResource(icon_value, false, false, false, false, false)) {
                thisSerializer.writeInt8((2).toChar())
                const icon_value_2  = icon_value as Resource
                Resource_serializer.write(thisSerializer, icon_value_2)
            }
            else if (TypeChecker.isSymbolGlyphModifier(icon_value)) {
                thisSerializer.writeInt8((3).toChar())
                const icon_value_3  = icon_value as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, icon_value_3)
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setBackButtonIcon1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTitleAttribute(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): void {
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
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (TypeChecker.isNavigationCommonTitle(value_value, false, false)) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as NavigationCommonTitle
                NavigationCommonTitle_serializer.write(thisSerializer, value_value_2)
            }
            else if (TypeChecker.isNavigationCustomTitle(value_value, false, false)) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as NavigationCustomTitle
                NavigationCustomTitle_serializer.write(thisSerializer, value_value_3)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            NavigationTitleOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setTitle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideTitleBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setMenus1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setToolbarConfigurationAttribute(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
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
                const value_value_0  = value_value as Array<ToolbarItem>
                thisSerializer.writeInt32((value_value_0.length).toInt())
                for (let value_value_0_counter_i = 0; value_value_0_counter_i < value_value_0.length; value_value_0_counter_i++) {
                    const value_value_0_element : ToolbarItem = value_value_0[value_value_0_counter_i]
                    ToolbarItem_serializer.write(thisSerializer, value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            NavigationToolbarOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_setToolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHideToolBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setHideToolBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_setIgnoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    navBarWidth(value: Length | undefined): this {
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
    backButtonIcon(value: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method backButtonIcon")
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
    menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        throw new Error("Unimplemented method menus")
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
    public backButtonIcon(value: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined): this {
        return this
    }
    public hideNavBar(value: boolean | undefined): this {
        return this
    }
    public hideTitleBar(value: boolean | undefined): this {
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        return this
    }
    public titleMode(value: NavigationTitleMode | undefined): this {
        return this
    }
    public menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        return this
    }
    public hideToolBar(value: boolean | undefined): this {
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
    public backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        return this
    }
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        return this
    }
    public hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): this {
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this {
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
    public setNavigationOptions(): this {
        if (this.checkPriority("setNavigationOptions")) {
            this.getPeer()?.setNavigationOptions0Attribute()
            return this
        }
        return this
    }
    public setNavigationOptions(pathInfos: NavPathStack): this {
        if (this.checkPriority("setNavigationOptions")) {
            const pathInfos_casted = pathInfos as (NavPathStack)
            this.getPeer()?.setNavigationOptions1Attribute(pathInfos_casted)
            return this
        }
        return this
    }
    public navBarWidth(value: Length | undefined): this {
        if (this.checkPriority("navBarWidth")) {
            const value_casted = value as (Length | undefined)
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
    public backButtonIcon(value: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("backButtonIcon")) {
            const value_casted = value as (string | image.PixelMap | Resource | SymbolGlyphModifier | undefined)
            this.getPeer()?.setBackButtonIcon0Attribute(value_casted)
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
    public menus(value: Array<NavigationMenuItem> | CustomBuilder | undefined): this {
        if (this.checkPriority("menus")) {
            const value_casted = value as (Array<NavigationMenuItem> | CustomBuilder | undefined)
            this.getPeer()?.setMenus0Attribute(value_casted)
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
            const value_casted = value as (PageMapBuilder | undefined)
            this.getPeer()?.setNavDestinationAttribute(value_casted)
            return this
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
            this.getPeer()?.setBackButtonIcon1Attribute(icon_casted, accessibilityText_casted)
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
            this.getPeer()?.setMenus1Attribute(items_casted, options_casted)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Navigation")
// export function Navigation(
//     
//     @memo
//     content_?: () => void,
// ): NavigationAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Navigation(
    @memo
    style: ((attributes: NavigationAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkNavigationComponent>((): ArkNavigationComponent => {
        return new ArkNavigationComponent()
    })
    NodeAttach<ArkNavigationPeer>((): ArkNavigationPeer => ArkNavigationPeer.create(receiver), (_: ArkNavigationPeer): void => {
        receiver.setNavigationOptions()
        style?.(receiver)
        withNavigationStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("Navigation")
// export function Navigation(
//     pathInfos: NavPathStack,
//     @memo
//     content_?: () => void,
// ): NavigationAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Navigation(
    @memo
    style: ((attributes: NavigationAttribute) => void) | undefined,
    pathInfos: NavPathStack,
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

export class ArkNavigationSet extends ArkCommonMethodSet implements NavigationAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _navBarWidth_flag?: boolean
    _navBarWidth0_value?: Length | undefined
    _navBarPosition_flag?: boolean
    _navBarPosition0_value?: NavBarPosition | undefined
    _navBarWidthRange_flag?: boolean
    _navBarWidthRange0_value?: [ Dimension, Dimension ] | undefined
    _minContentWidth_flag?: boolean
    _minContentWidth0_value?: Dimension | undefined
    _mode_flag?: boolean
    _mode0_value?: NavigationMode | undefined
    _backButtonIcon_flag?: boolean
    _backButtonIcon0_value?: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined
    _backButtonIcon1_value?: ResourceStr | undefined
    _hideNavBar_flag?: boolean
    _hideNavBar0_value?: boolean | undefined
    _hideTitleBar_flag?: boolean
    _hideTitleBar0_value?: boolean | undefined
    _hideTitleBar1_value?: boolean | undefined
    _hideBackButton_flag?: boolean
    _hideBackButton0_value?: boolean | undefined
    _titleMode_flag?: boolean
    _titleMode0_value?: NavigationTitleMode | undefined
    _menus_flag?: boolean
    _menus0_value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    _menus1_value?: NavigationMenuOptions | undefined
    _hideToolBar_flag?: boolean
    _hideToolBar0_value?: boolean | undefined
    _hideToolBar1_value?: boolean | undefined
    _enableToolBarAdaptation_flag?: boolean
    _enableToolBarAdaptation0_value?: boolean | undefined
    _onTitleModeChange_flag?: boolean
    _onTitleModeChange0_value?: ((titleMode: NavigationTitleMode) => void) | undefined
    _onNavBarStateChange_flag?: boolean
    _onNavBarStateChange0_value?: ((isVisible: boolean) => void) | undefined
    _onNavigationModeChange_flag?: boolean
    _onNavigationModeChange0_value?: ((mode: NavigationMode) => void) | undefined
    _navDestination_flag?: boolean
    _navDestination0_value?: PageMapBuilder | undefined
    _customNavContentTransition_flag?: boolean
    _customNavContentTransition0_value?: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined
    _systemBarStyle_flag?: boolean
    _systemBarStyle0_value?: window.SystemBarStyle | undefined
    _recoverable_flag?: boolean
    _recoverable0_value?: boolean | undefined
    _enableDragBar_flag?: boolean
    _enableDragBar0_value?: boolean | undefined
    _enableModeChangeAnimation_flag?: boolean
    _enableModeChangeAnimation0_value?: boolean | undefined
    _title_flag?: boolean
    _title0_value?: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined
    _title1_value?: NavigationTitleOptions | undefined
    _toolbarConfiguration_flag?: boolean
    _toolbarConfiguration0_value?: Array<ToolbarItem> | CustomBuilder | undefined
    _toolbarConfiguration1_value?: NavigationToolbarOptions | undefined
    _ignoreLayoutSafeArea_flag?: boolean
    _ignoreLayoutSafeArea0_value?: Array<LayoutSafeAreaType> | undefined
    _ignoreLayoutSafeArea1_value?: Array<LayoutSafeAreaEdge> | undefined
    applyModifierPatch(component: NavigationAttribute): void {
        if (this._navBarWidth_flag)
            component.navBarWidth((this._navBarWidth0_value as Length | undefined))
        if (this._navBarPosition_flag)
            component.navBarPosition((this._navBarPosition0_value as NavBarPosition | undefined))
        if (this._navBarWidthRange_flag)
            component.navBarWidthRange((this._navBarWidthRange0_value as [ Dimension, Dimension ] | undefined))
        if (this._minContentWidth_flag)
            component.minContentWidth((this._minContentWidth0_value as Dimension | undefined))
        if (this._mode_flag)
            component.mode((this._mode0_value as NavigationMode | undefined))
        if (this._backButtonIcon_flag)
            component.backButtonIcon((this._backButtonIcon0_value as string | image.PixelMap | Resource | SymbolGlyphModifier | undefined), (this._backButtonIcon1_value as ResourceStr | undefined))
        if (this._hideNavBar_flag)
            component.hideNavBar((this._hideNavBar0_value as boolean | undefined))
        if (this._hideTitleBar_flag)
            component.hideTitleBar((this._hideTitleBar0_value as boolean | undefined), (this._hideTitleBar1_value as boolean | undefined))
        if (this._hideBackButton_flag)
            component.hideBackButton((this._hideBackButton0_value as boolean | undefined))
        if (this._titleMode_flag)
            component.titleMode((this._titleMode0_value as NavigationTitleMode | undefined))
        if (this._menus_flag)
            component.menus((this._menus0_value as Array<NavigationMenuItem> | CustomBuilder | undefined), (this._menus1_value as NavigationMenuOptions | undefined))
        if (this._hideToolBar_flag)
            component.hideToolBar((this._hideToolBar0_value as boolean | undefined), (this._hideToolBar1_value as boolean | undefined))
        if (this._enableToolBarAdaptation_flag)
            component.enableToolBarAdaptation((this._enableToolBarAdaptation0_value as boolean | undefined))
        if (this._onTitleModeChange_flag)
            component.onTitleModeChange((this._onTitleModeChange0_value as ((titleMode: NavigationTitleMode) => void) | undefined))
        if (this._onNavBarStateChange_flag)
            component.onNavBarStateChange((this._onNavBarStateChange0_value as ((isVisible: boolean) => void) | undefined))
        if (this._onNavigationModeChange_flag)
            component.onNavigationModeChange((this._onNavigationModeChange0_value as ((mode: NavigationMode) => void) | undefined))
        if (this._navDestination_flag)
            component.navDestination((this._navDestination0_value as PageMapBuilder | undefined))
        if (this._customNavContentTransition_flag)
            component.customNavContentTransition((this._customNavContentTransition0_value as ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined))
        if (this._systemBarStyle_flag)
            component.systemBarStyle((this._systemBarStyle0_value as window.SystemBarStyle | undefined))
        if (this._recoverable_flag)
            component.recoverable((this._recoverable0_value as boolean | undefined))
        if (this._enableDragBar_flag)
            component.enableDragBar((this._enableDragBar0_value as boolean | undefined))
        if (this._enableModeChangeAnimation_flag)
            component.enableModeChangeAnimation((this._enableModeChangeAnimation0_value as boolean | undefined))
        if (this._title_flag)
            component.title((this._title0_value as ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined), (this._title1_value as NavigationTitleOptions | undefined))
        if (this._toolbarConfiguration_flag)
            component.toolbarConfiguration((this._toolbarConfiguration0_value as Array<ToolbarItem> | CustomBuilder | undefined), (this._toolbarConfiguration1_value as NavigationToolbarOptions | undefined))
        if (this._ignoreLayoutSafeArea_flag)
            component.ignoreLayoutSafeArea((this._ignoreLayoutSafeArea0_value as Array<LayoutSafeAreaType> | undefined), (this._ignoreLayoutSafeArea1_value as Array<LayoutSafeAreaEdge> | undefined))
    }
    public navBarWidth(value: Length | undefined): this {
        this._navBarWidth_flag = true
        this._navBarWidth0_value = value
        return this
    }
    public navBarPosition(value: NavBarPosition | undefined): this {
        this._navBarPosition_flag = true
        this._navBarPosition0_value = value
        return this
    }
    public navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        this._navBarWidthRange_flag = true
        this._navBarWidthRange0_value = value
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        this._minContentWidth_flag = true
        this._minContentWidth0_value = value
        return this
    }
    public mode(value: NavigationMode | undefined): this {
        this._mode_flag = true
        this._mode0_value = value
        return this
    }
    public backButtonIcon(icon: string | image.PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        this._backButtonIcon_flag = true
        this._backButtonIcon0_value = icon
        this._backButtonIcon1_value = accessibilityText
        return this
    }
    public hideNavBar(value: boolean | undefined): this {
        this._hideNavBar_flag = true
        this._hideNavBar0_value = value
        return this
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
    public titleMode(value: NavigationTitleMode | undefined): this {
        this._titleMode_flag = true
        this._titleMode0_value = value
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        this._menus_flag = true
        this._menus0_value = items
        this._menus1_value = options
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated: boolean | undefined): this {
        this._hideToolBar_flag = true
        this._hideToolBar0_value = hide
        this._hideToolBar1_value = animated
        return this
    }
    public enableToolBarAdaptation(value: boolean | undefined): this {
        this._enableToolBarAdaptation_flag = true
        this._enableToolBarAdaptation0_value = value
        return this
    }
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        this._onTitleModeChange_flag = true
        this._onTitleModeChange0_value = value
        return this
    }
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        this._onNavBarStateChange_flag = true
        this._onNavBarStateChange0_value = value
        return this
    }
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        this._onNavigationModeChange_flag = true
        this._onNavigationModeChange0_value = value
        return this
    }
    public navDestination(value: PageMapBuilder | undefined): this {
        this._navDestination_flag = true
        this._navDestination0_value = value
        return this
    }
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        this._customNavContentTransition_flag = true
        this._customNavContentTransition0_value = value
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
    public enableDragBar(value: boolean | undefined): this {
        this._enableDragBar_flag = true
        this._enableDragBar0_value = value
        return this
    }
    public enableModeChangeAnimation(value: boolean | undefined): this {
        this._enableModeChangeAnimation_flag = true
        this._enableModeChangeAnimation0_value = value
        return this
    }
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        this._title_flag = true
        this._title0_value = value
        this._title1_value = options
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        this._toolbarConfiguration_flag = true
        this._toolbarConfiguration0_value = value
        this._toolbarConfiguration1_value = options
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        this._ignoreLayoutSafeArea_flag = true
        this._ignoreLayoutSafeArea0_value = types
        this._ignoreLayoutSafeArea1_value = edges
        return this
    }
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        valueSerializer.writeInt8((value_name_type).toChar())
        if ((value_name_type) != (RuntimeType.UNDEFINED)) {
            const value_name_value  = value_name!
            valueSerializer.writeString(value_name_value)
        }
        const value_index  = value.index
        valueSerializer.writeNumber(value_index)
        const value_mode  = value.mode
        let value_mode_type : int32 = RuntimeType.UNDEFINED
        value_mode_type = runtimeType(value_mode)
        valueSerializer.writeInt8((value_mode_type).toChar())
        if ((value_mode_type) != (RuntimeType.UNDEFINED)) {
            const value_mode_value  = (value_mode as NavDestinationMode)
            valueSerializer.writeInt32(TypeChecker.NavDestinationMode_ToNumeric(value_mode_value))
        }
        const value_param  = value.param
        let value_param_type : int32 = RuntimeType.UNDEFINED
        value_param_type = runtimeType(value_param)
        valueSerializer.writeInt8((value_param_type).toChar())
        if ((value_param_type) != (RuntimeType.UNDEFINED)) {
            const value_param_value  = value_param!
            valueSerializer.holdAndWriteObject(value_param_value)
        }
        const value_navDestinationId  = value.navDestinationId
        let value_navDestinationId_type : int32 = RuntimeType.UNDEFINED
        value_navDestinationId_type = runtimeType(value_navDestinationId)
        valueSerializer.writeInt8((value_navDestinationId_type).toChar())
        if ((value_navDestinationId_type) != (RuntimeType.UNDEFINED)) {
            const value_navDestinationId_value  = value_navDestinationId!
            valueSerializer.writeString(value_navDestinationId_value)
        }
    }
    public static read(buffer: DeserializerBase): NavContentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const name_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let name_buf : string | undefined
        if ((name_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            name_buf = (valueDeserializer.readString() as string)
        }
        const name_result : string | undefined = name_buf
        const index_result : number = (valueDeserializer.readNumber() as number)
        const mode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mode_buf : NavDestinationMode | undefined
        if ((mode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            mode_buf = TypeChecker.NavDestinationMode_FromNumeric(valueDeserializer.readInt32())
        }
        const mode_result : NavDestinationMode | undefined = mode_buf
        const param_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let param_buf : Object | undefined
        if ((param_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            param_buf = (valueDeserializer.readObject() as object)
        }
        const param_result : Object | undefined = param_buf
        const navDestinationId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let navDestinationId_buf : string | undefined
        if ((navDestinationId_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_onTransitionEnd_type).toChar())
        if ((value_onTransitionEnd_type) != (RuntimeType.UNDEFINED)) {
            const value_onTransitionEnd_value  = value_onTransitionEnd!
            valueSerializer.holdAndWriteCallback(value_onTransitionEnd_value)
        }
        const value_timeout  = value.timeout
        let value_timeout_type : int32 = RuntimeType.UNDEFINED
        value_timeout_type = runtimeType(value_timeout)
        valueSerializer.writeInt8((value_timeout_type).toChar())
        if ((value_timeout_type) != (RuntimeType.UNDEFINED)) {
            const value_timeout_value  = value_timeout!
            valueSerializer.writeNumber(value_timeout_value)
        }
        const value_isInteractive  = value.isInteractive
        let value_isInteractive_type : int32 = RuntimeType.UNDEFINED
        value_isInteractive_type = runtimeType(value_isInteractive)
        valueSerializer.writeInt8((value_isInteractive_type).toChar())
        if ((value_isInteractive_type) != (RuntimeType.UNDEFINED)) {
            const value_isInteractive_value  = value_isInteractive!
            valueSerializer.writeBoolean(value_isInteractive_value)
        }
        const value_transition  = value.transition
        valueSerializer.holdAndWriteCallback(value_transition)
    }
    public static read(buffer: DeserializerBase): NavigationAnimatedTransition {
        let valueDeserializer : DeserializerBase = buffer
        const onTransitionEnd_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onTransitionEnd_buf : ((isVisible: boolean) => void) | undefined
        if ((onTransitionEnd_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        const timeout_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeout_buf : number | undefined
        if ((timeout_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            timeout_buf = (valueDeserializer.readNumber() as number)
        }
        const timeout_result : number | undefined = timeout_buf
        const isInteractive_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isInteractive_buf : boolean | undefined
        if ((isInteractive_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_willShow_type).toChar())
        if ((value_willShow_type) != (RuntimeType.UNDEFINED)) {
            const value_willShow_value  = value_willShow!
            valueSerializer.holdAndWriteCallback(value_willShow_value)
        }
        const value_didShow  = value.didShow
        let value_didShow_type : int32 = RuntimeType.UNDEFINED
        value_didShow_type = runtimeType(value_didShow)
        valueSerializer.writeInt8((value_didShow_type).toChar())
        if ((value_didShow_type) != (RuntimeType.UNDEFINED)) {
            const value_didShow_value  = value_didShow!
            valueSerializer.holdAndWriteCallback(value_didShow_value)
        }
        const value_modeChange  = value.modeChange
        let value_modeChange_type : int32 = RuntimeType.UNDEFINED
        value_modeChange_type = runtimeType(value_modeChange)
        valueSerializer.writeInt8((value_modeChange_type).toChar())
        if ((value_modeChange_type) != (RuntimeType.UNDEFINED)) {
            const value_modeChange_value  = value_modeChange!
            valueSerializer.holdAndWriteCallback(value_modeChange_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationInterception {
        let valueDeserializer : DeserializerBase = buffer
        const willShow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let willShow_buf : InterceptionShowCallback | undefined
        if ((willShow_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        willShow_buf__argsSerializer.writeInt8((0).toChar());
        const from_0  = from as NavDestinationContext;
        NavDestinationContext_serializer.write(willShow_buf__argsSerializer, from_0);
    }
    else if (RuntimeType.STRING == from_type) {
        willShow_buf__argsSerializer.writeInt8((1).toChar());
        const from_1  = from as NavBar;
        willShow_buf__argsSerializer.writeString(from_1);
    }
    let to_type : int32 = RuntimeType.UNDEFINED;
    to_type = runtimeType(to);
    if (RuntimeType.OBJECT == to_type) {
        willShow_buf__argsSerializer.writeInt8((0).toChar());
        const to_0  = to as NavDestinationContext;
        NavDestinationContext_serializer.write(willShow_buf__argsSerializer, to_0);
    }
    else if (RuntimeType.STRING == to_type) {
        willShow_buf__argsSerializer.writeInt8((1).toChar());
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
        const didShow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let didShow_buf : InterceptionShowCallback | undefined
        if ((didShow_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        didShow_buf__argsSerializer.writeInt8((0).toChar());
        const from_0  = from as NavDestinationContext;
        NavDestinationContext_serializer.write(didShow_buf__argsSerializer, from_0);
    }
    else if (RuntimeType.STRING == from_type) {
        didShow_buf__argsSerializer.writeInt8((1).toChar());
        const from_1  = from as NavBar;
        didShow_buf__argsSerializer.writeString(from_1);
    }
    let to_type : int32 = RuntimeType.UNDEFINED;
    to_type = runtimeType(to);
    if (RuntimeType.OBJECT == to_type) {
        didShow_buf__argsSerializer.writeInt8((0).toChar());
        const to_0  = to as NavDestinationContext;
        NavDestinationContext_serializer.write(didShow_buf__argsSerializer, to_0);
    }
    else if (RuntimeType.STRING == to_type) {
        didShow_buf__argsSerializer.writeInt8((1).toChar());
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
        const modeChange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modeChange_buf : InterceptionModeCallback | undefined
        if ((modeChange_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_launchMode_type).toChar())
        if ((value_launchMode_type) != (RuntimeType.UNDEFINED)) {
            const value_launchMode_value  = (value_launchMode as LaunchMode)
            valueSerializer.writeInt32(TypeChecker.LaunchMode_ToNumeric(value_launchMode_value))
        }
        const value_animated  = value.animated
        let value_animated_type : int32 = RuntimeType.UNDEFINED
        value_animated_type = runtimeType(value_animated)
        valueSerializer.writeInt8((value_animated_type).toChar())
        if ((value_animated_type) != (RuntimeType.UNDEFINED)) {
            const value_animated_value  = value_animated!
            valueSerializer.writeBoolean(value_animated_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const launchMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let launchMode_buf : LaunchMode | undefined
        if ((launchMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            launchMode_buf = TypeChecker.LaunchMode_FromNumeric(valueDeserializer.readInt32())
        }
        const launchMode_result : LaunchMode | undefined = launchMode_buf
        const animated_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let animated_buf : boolean | undefined
        if ((animated_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
    public static read(buffer: DeserializerBase): NavigationCommonTitle {
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
            valueSerializer.writeInt8((0).toChar())
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8((value_symbolIcon_type).toChar())
        if ((value_symbolIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_symbolIcon_value  = value_symbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolIcon_value)
        }
        const value_isEnabled  = value.isEnabled
        let value_isEnabled_type : int32 = RuntimeType.UNDEFINED
        value_isEnabled_type = runtimeType(value_isEnabled)
        valueSerializer.writeInt8((value_isEnabled_type).toChar())
        if ((value_isEnabled_type) != (RuntimeType.UNDEFINED)) {
            const value_isEnabled_value  = value_isEnabled!
            valueSerializer.writeBoolean(value_isEnabled_value)
        }
        const value_action  = value.action
        let value_action_type : int32 = RuntimeType.UNDEFINED
        value_action_type = runtimeType(value_action)
        valueSerializer.writeInt8((value_action_type).toChar())
        if ((value_action_type) != (RuntimeType.UNDEFINED)) {
            const value_action_value  = value_action!
            valueSerializer.holdAndWriteCallback(value_action_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationMenuItem {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == (0).toChar()) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == (1).toChar()) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : string | Resource = (value_buf as string | Resource)
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : string | Resource | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == (0).toChar()) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == (1).toChar()) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : string | Resource | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((symbolIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            symbolIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolIcon_result : SymbolGlyphModifier | undefined = symbolIcon_buf
        const isEnabled_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isEnabled_buf : boolean | undefined
        if ((isEnabled_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isEnabled_buf = valueDeserializer.readBoolean()
        }
        const isEnabled_result : boolean | undefined = isEnabled_buf
        const action_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let action_buf : (() => void) | undefined
        if ((action_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
            valueSerializer.writeInt8((0).toChar())
            const value_value_0  = value_value as string
            valueSerializer.writeString(value_value_0)
        }
        else if (RuntimeType.OBJECT == value_value_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_value_1  = value_value as Resource
            Resource_serializer.write(valueSerializer, value_value_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_symbolIcon  = value.symbolIcon
        let value_symbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_symbolIcon_type = runtimeType(value_symbolIcon)
        valueSerializer.writeInt8((value_symbolIcon_type).toChar())
        if ((value_symbolIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_symbolIcon_value  = value_symbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_symbolIcon_value)
        }
        const value_action  = value.action
        let value_action_type : int32 = RuntimeType.UNDEFINED
        value_action_type = runtimeType(value_action)
        valueSerializer.writeInt8((value_action_type).toChar())
        if ((value_action_type) != (RuntimeType.UNDEFINED)) {
            const value_action_value  = value_action!
            valueSerializer.holdAndWriteCallback(value_action_value)
        }
        const value_status  = value.status
        let value_status_type : int32 = RuntimeType.UNDEFINED
        value_status_type = runtimeType(value_status)
        valueSerializer.writeInt8((value_status_type).toChar())
        if ((value_status_type) != (RuntimeType.UNDEFINED)) {
            const value_status_value  = (value_status as ToolbarItemStatus)
            valueSerializer.writeInt32(TypeChecker.ToolbarItemStatus_ToNumeric(value_status_value))
        }
        const value_activeIcon  = value.activeIcon
        let value_activeIcon_type : int32 = RuntimeType.UNDEFINED
        value_activeIcon_type = runtimeType(value_activeIcon)
        valueSerializer.writeInt8((value_activeIcon_type).toChar())
        if ((value_activeIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_activeIcon_value  = value_activeIcon!
            let value_activeIcon_value_type : int32 = RuntimeType.UNDEFINED
            value_activeIcon_value_type = runtimeType(value_activeIcon_value)
            if (RuntimeType.STRING == value_activeIcon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_activeIcon_value_0  = value_activeIcon_value as string
                valueSerializer.writeString(value_activeIcon_value_0)
            }
            else if (RuntimeType.OBJECT == value_activeIcon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_activeIcon_value_1  = value_activeIcon_value as Resource
                Resource_serializer.write(valueSerializer, value_activeIcon_value_1)
            }
        }
        const value_activeSymbolIcon  = value.activeSymbolIcon
        let value_activeSymbolIcon_type : int32 = RuntimeType.UNDEFINED
        value_activeSymbolIcon_type = runtimeType(value_activeSymbolIcon)
        valueSerializer.writeInt8((value_activeSymbolIcon_type).toChar())
        if ((value_activeSymbolIcon_type) != (RuntimeType.UNDEFINED)) {
            const value_activeSymbolIcon_value  = value_activeSymbolIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, value_activeSymbolIcon_value)
        }
    }
    public static read(buffer: DeserializerBase): ToolbarItem {
        let valueDeserializer : DeserializerBase = buffer
        const value_buf_selector : int32 = valueDeserializer.readInt8()
        let value_buf : string | Resource | undefined
        if (value_buf_selector == (0).toChar()) {
            value_buf = (valueDeserializer.readString() as string)
        }
        else if (value_buf_selector == (1).toChar()) {
            value_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for value_buf has to be chosen through deserialisation.")
        }
        const value_result : ResourceStr = (value_buf as string | Resource)
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : ResourceStr | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == (0).toChar()) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == (1).toChar()) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const symbolIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolIcon_buf : SymbolGlyphModifier | undefined
        if ((symbolIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            symbolIcon_buf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const symbolIcon_result : SymbolGlyphModifier | undefined = symbolIcon_buf
        const action_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let action_buf : (() => void) | undefined
        if ((action_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        const status_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let status_buf : ToolbarItemStatus | undefined
        if ((status_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            status_buf = TypeChecker.ToolbarItemStatus_FromNumeric(valueDeserializer.readInt32())
        }
        const status_result : ToolbarItemStatus | undefined = status_buf
        const activeIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let activeIcon_buf : ResourceStr | undefined
        if ((activeIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const activeIcon_buf__selector : int32 = valueDeserializer.readInt8()
            let activeIcon_buf_ : string | Resource | undefined
            if (activeIcon_buf__selector == (0).toChar()) {
                activeIcon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (activeIcon_buf__selector == (1).toChar()) {
                activeIcon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for activeIcon_buf_ has to be chosen through deserialisation.")
            }
            activeIcon_buf = (activeIcon_buf_ as string | Resource)
        }
        const activeIcon_result : ResourceStr | undefined = activeIcon_buf
        const activeSymbolIcon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let activeSymbolIcon_buf : SymbolGlyphModifier | undefined
        if ((activeSymbolIcon_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_backgroundBlurStyle_type).toChar())
        if ((value_backgroundBlurStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8((value_backgroundBlurStyleOptions_type).toChar())
        if ((value_backgroundBlurStyleOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8((value_backgroundEffect_type).toChar())
        if ((value_backgroundEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
    }
    public static read(buffer: DeserializerBase): MoreButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundBlurStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((backgroundBlurStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((backgroundBlurStyleOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((backgroundEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_backgroundColor_type).toChar())
        if ((value_backgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundColor_value  = value_backgroundColor!
            let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
            if (TypeChecker.isColor(value_backgroundColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_backgroundColor_value_0  = value_backgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_backgroundColor_value_1  = value_backgroundColor_value as number
                valueSerializer.writeNumber(value_backgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_backgroundColor_value_2  = value_backgroundColor_value as string
                valueSerializer.writeString(value_backgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundColor_value_3)
            }
        }
        const value_backgroundBlurStyle  = value.backgroundBlurStyle
        let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
        valueSerializer.writeInt8((value_backgroundBlurStyle_type).toChar())
        if ((value_backgroundBlurStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8((value_backgroundBlurStyleOptions_type).toChar())
        if ((value_backgroundBlurStyleOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8((value_backgroundEffect_type).toChar())
        if ((value_backgroundEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
        const value_barStyle  = value.barStyle
        let value_barStyle_type : int32 = RuntimeType.UNDEFINED
        value_barStyle_type = runtimeType(value_barStyle)
        valueSerializer.writeInt8((value_barStyle_type).toChar())
        if ((value_barStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_barStyle_value  = (value_barStyle as BarStyle)
            valueSerializer.writeInt32(TypeChecker.BarStyle_ToNumeric(value_barStyle_value))
        }
        const value_paddingStart  = value.paddingStart
        let value_paddingStart_type : int32 = RuntimeType.UNDEFINED
        value_paddingStart_type = runtimeType(value_paddingStart)
        valueSerializer.writeInt8((value_paddingStart_type).toChar())
        if ((value_paddingStart_type) != (RuntimeType.UNDEFINED)) {
            const value_paddingStart_value  = value_paddingStart!
            LengthMetrics_serializer.write(valueSerializer, value_paddingStart_value)
        }
        const value_paddingEnd  = value.paddingEnd
        let value_paddingEnd_type : int32 = RuntimeType.UNDEFINED
        value_paddingEnd_type = runtimeType(value_paddingEnd)
        valueSerializer.writeInt8((value_paddingEnd_type).toChar())
        if ((value_paddingEnd_type) != (RuntimeType.UNDEFINED)) {
            const value_paddingEnd_value  = value_paddingEnd!
            LengthMetrics_serializer.write(valueSerializer, value_paddingEnd_value)
        }
        const value_mainTitleModifier  = value.mainTitleModifier
        let value_mainTitleModifier_type : int32 = RuntimeType.UNDEFINED
        value_mainTitleModifier_type = runtimeType(value_mainTitleModifier)
        valueSerializer.writeInt8((value_mainTitleModifier_type).toChar())
        if ((value_mainTitleModifier_type) != (RuntimeType.UNDEFINED)) {
            const value_mainTitleModifier_value  = value_mainTitleModifier!
            TextModifier_serializer.write(valueSerializer, value_mainTitleModifier_value)
        }
        const value_subTitleModifier  = value.subTitleModifier
        let value_subTitleModifier_type : int32 = RuntimeType.UNDEFINED
        value_subTitleModifier_type = runtimeType(value_subTitleModifier)
        valueSerializer.writeInt8((value_subTitleModifier_type).toChar())
        if ((value_subTitleModifier_type) != (RuntimeType.UNDEFINED)) {
            const value_subTitleModifier_value  = value_subTitleModifier!
            TextModifier_serializer.write(valueSerializer, value_subTitleModifier_value)
        }
        const value_enableHoverMode  = value.enableHoverMode
        let value_enableHoverMode_type : int32 = RuntimeType.UNDEFINED
        value_enableHoverMode_type = runtimeType(value_enableHoverMode)
        valueSerializer.writeInt8((value_enableHoverMode_type).toChar())
        if ((value_enableHoverMode_type) != (RuntimeType.UNDEFINED)) {
            const value_enableHoverMode_value  = value_enableHoverMode!
            valueSerializer.writeBoolean(value_enableHoverMode_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationTitleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColor_buf : ResourceColor | undefined
        if ((backgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const backgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundColor_buf_ : Color | number | string | Resource | undefined
            if (backgroundColor_buf__selector == (0).toChar()) {
                backgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (backgroundColor_buf__selector == (1).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundColor_buf__selector == (2).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundColor_buf__selector == (3).toChar()) {
                backgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundColor_buf_ has to be chosen through deserialisation.")
            }
            backgroundColor_buf = (backgroundColor_buf_ as Color | number | string | Resource)
        }
        const backgroundColor_result : ResourceColor | undefined = backgroundColor_buf
        const backgroundBlurStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((backgroundBlurStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((backgroundBlurStyleOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((backgroundEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundEffect_buf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffect_result : BackgroundEffectOptions | undefined = backgroundEffect_buf
        const barStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let barStyle_buf : BarStyle | undefined
        if ((barStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            barStyle_buf = TypeChecker.BarStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const barStyle_result : BarStyle | undefined = barStyle_buf
        const paddingStart_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paddingStart_buf : LengthMetrics | undefined
        if ((paddingStart_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            paddingStart_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const paddingStart_result : LengthMetrics | undefined = paddingStart_buf
        const paddingEnd_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paddingEnd_buf : LengthMetrics | undefined
        if ((paddingEnd_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            paddingEnd_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const paddingEnd_result : LengthMetrics | undefined = paddingEnd_buf
        const mainTitleModifier_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let mainTitleModifier_buf : TextModifier | undefined
        if ((mainTitleModifier_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            mainTitleModifier_buf = TextModifier_serializer.read(valueDeserializer)
        }
        const mainTitleModifier_result : TextModifier | undefined = mainTitleModifier_buf
        const subTitleModifier_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let subTitleModifier_buf : TextModifier | undefined
        if ((subTitleModifier_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            subTitleModifier_buf = TextModifier_serializer.read(valueDeserializer)
        }
        const subTitleModifier_result : TextModifier | undefined = subTitleModifier_buf
        const enableHoverMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverMode_buf : boolean | undefined
        if ((enableHoverMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_moreButtonOptions_type).toChar())
        if ((value_moreButtonOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_moreButtonOptions_value  = value_moreButtonOptions!
            MoreButtonOptions_serializer.write(valueSerializer, value_moreButtonOptions_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const moreButtonOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moreButtonOptions_buf : MoreButtonOptions | undefined
        if ((moreButtonOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_backgroundColor_type).toChar())
        if ((value_backgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundColor_value  = value_backgroundColor!
            let value_backgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_backgroundColor_value_type = runtimeType(value_backgroundColor_value)
            if (TypeChecker.isColor(value_backgroundColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_backgroundColor_value_0  = value_backgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_backgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_backgroundColor_value_1  = value_backgroundColor_value as number
                valueSerializer.writeNumber(value_backgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_backgroundColor_value_2  = value_backgroundColor_value as string
                valueSerializer.writeString(value_backgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_backgroundColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_backgroundColor_value_3  = value_backgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_backgroundColor_value_3)
            }
        }
        const value_backgroundBlurStyle  = value.backgroundBlurStyle
        let value_backgroundBlurStyle_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyle_type = runtimeType(value_backgroundBlurStyle)
        valueSerializer.writeInt8((value_backgroundBlurStyle_type).toChar())
        if ((value_backgroundBlurStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyle_value  = (value_backgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_backgroundBlurStyle_value))
        }
        const value_backgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        let value_backgroundBlurStyleOptions_type : int32 = RuntimeType.UNDEFINED
        value_backgroundBlurStyleOptions_type = runtimeType(value_backgroundBlurStyleOptions)
        valueSerializer.writeInt8((value_backgroundBlurStyleOptions_type).toChar())
        if ((value_backgroundBlurStyleOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundBlurStyleOptions_value  = value_backgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, value_backgroundBlurStyleOptions_value)
        }
        const value_backgroundEffect  = value.backgroundEffect
        let value_backgroundEffect_type : int32 = RuntimeType.UNDEFINED
        value_backgroundEffect_type = runtimeType(value_backgroundEffect)
        valueSerializer.writeInt8((value_backgroundEffect_type).toChar())
        if ((value_backgroundEffect_type) != (RuntimeType.UNDEFINED)) {
            const value_backgroundEffect_value  = value_backgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, value_backgroundEffect_value)
        }
        const value_moreButtonOptions  = value.moreButtonOptions
        let value_moreButtonOptions_type : int32 = RuntimeType.UNDEFINED
        value_moreButtonOptions_type = runtimeType(value_moreButtonOptions)
        valueSerializer.writeInt8((value_moreButtonOptions_type).toChar())
        if ((value_moreButtonOptions_type) != (RuntimeType.UNDEFINED)) {
            const value_moreButtonOptions_value  = value_moreButtonOptions!
            MoreButtonOptions_serializer.write(valueSerializer, value_moreButtonOptions_value)
        }
        const value_barStyle  = value.barStyle
        let value_barStyle_type : int32 = RuntimeType.UNDEFINED
        value_barStyle_type = runtimeType(value_barStyle)
        valueSerializer.writeInt8((value_barStyle_type).toChar())
        if ((value_barStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_barStyle_value  = (value_barStyle as BarStyle)
            valueSerializer.writeInt32(TypeChecker.BarStyle_ToNumeric(value_barStyle_value))
        }
        const value_hideItemValue  = value.hideItemValue
        let value_hideItemValue_type : int32 = RuntimeType.UNDEFINED
        value_hideItemValue_type = runtimeType(value_hideItemValue)
        valueSerializer.writeInt8((value_hideItemValue_type).toChar())
        if ((value_hideItemValue_type) != (RuntimeType.UNDEFINED)) {
            const value_hideItemValue_value  = value_hideItemValue!
            valueSerializer.writeBoolean(value_hideItemValue_value)
        }
    }
    public static read(buffer: DeserializerBase): NavigationToolbarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const backgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColor_buf : ResourceColor | undefined
        if ((backgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const backgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let backgroundColor_buf_ : Color | number | string | Resource | undefined
            if (backgroundColor_buf__selector == (0).toChar()) {
                backgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (backgroundColor_buf__selector == (1).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (backgroundColor_buf__selector == (2).toChar()) {
                backgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (backgroundColor_buf__selector == (3).toChar()) {
                backgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for backgroundColor_buf_ has to be chosen through deserialisation.")
            }
            backgroundColor_buf = (backgroundColor_buf_ as Color | number | string | Resource)
        }
        const backgroundColor_result : ResourceColor | undefined = backgroundColor_buf
        const backgroundBlurStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyle_buf : BlurStyle | undefined
        if ((backgroundBlurStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyle_buf = TypeChecker.BlurStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const backgroundBlurStyle_result : BlurStyle | undefined = backgroundBlurStyle_buf
        const backgroundBlurStyleOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptions_buf : BackgroundBlurStyleOptions | undefined
        if ((backgroundBlurStyleOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundBlurStyleOptions_buf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptions_result : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptions_buf
        const backgroundEffect_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffect_buf : BackgroundEffectOptions | undefined
        if ((backgroundEffect_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            backgroundEffect_buf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffect_result : BackgroundEffectOptions | undefined = backgroundEffect_buf
        const moreButtonOptions_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let moreButtonOptions_buf : MoreButtonOptions | undefined
        if ((moreButtonOptions_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            moreButtonOptions_buf = MoreButtonOptions_serializer.read(valueDeserializer)
        }
        const moreButtonOptions_result : MoreButtonOptions | undefined = moreButtonOptions_buf
        const barStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let barStyle_buf : BarStyle | undefined
        if ((barStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            barStyle_buf = TypeChecker.BarStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const barStyle_result : BarStyle | undefined = barStyle_buf
        const hideItemValue_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hideItemValue_buf : boolean | undefined
        if ((hideItemValue_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            hideItemValue_buf = valueDeserializer.readBoolean()
        }
        const hideItemValue_result : boolean | undefined = hideItemValue_buf
        let value : NavigationToolbarOptions = ({backgroundColor: backgroundColor_result, backgroundBlurStyle: backgroundBlurStyle_result, backgroundBlurStyleOptions: backgroundBlurStyleOptions_result, backgroundEffect: backgroundEffect_result, moreButtonOptions: moreButtonOptions_result, barStyle: barStyle_result, hideItemValue: hideItemValue_result} as NavigationToolbarOptions)
        return value
    }
}
