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

import { uiObserver_NavDestinationInfo_serializer, uiObserver_NavigationInfo_serializer, uiObserver_RouterPageInfo_serializer, uiObserver } from "./../generated/ohos.arkui.observer"
import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { UIContext, UIContextInternal } from "./../generated/ohos.arkui.UIContext"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
export class ExtendableComponentInternal {
    public static fromPtr(ptr: KPointer): ExtendableComponent {
        return new ExtendableComponent(ptr)
    }
}
export class ExtendableComponent implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ExtendableComponent.getFinalizer())
    }
    constructor() {
        this(ExtendableComponent.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ExtendableComponent_getFinalizer()
    }
    public getUIContext(): UIContext {
        return this.getUIContext_serialize()
    }
    public getUniqueId(): int32 {
        return this.getUniqueId_serialize()
    }
    public queryNavDestinationInfo(): uiObserver.NavDestinationInfo | undefined {
        return this.queryNavDestinationInfo0_serialize()
    }
    public queryNavDestinationInfo(isInner: boolean | undefined): uiObserver.NavDestinationInfo | undefined {
        const isInner_casted = isInner as (boolean | undefined)
        return this.queryNavDestinationInfo1_serialize(isInner_casted)
    }
    public queryNavigationInfo(): uiObserver.NavigationInfo | undefined {
        return this.queryNavigationInfo_serialize()
    }
    public queryRouterPageInfo(): uiObserver.RouterPageInfo | undefined {
        return this.queryRouterPageInfo_serialize()
    }
    private getUIContext_serialize(): UIContext {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_getUIContext(this.peer!.ptr)
        const obj : UIContext = UIContextInternal.fromPtr(retval)
        return obj
    }
    private getUniqueId_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_getUniqueId(this.peer!.ptr)
        return retval
    }
    private queryNavDestinationInfo0_serialize(): uiObserver.NavDestinationInfo | undefined {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_queryNavDestinationInfo0(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : uiObserver.NavDestinationInfo | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = uiObserver_NavDestinationInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : uiObserver.NavDestinationInfo | undefined = buffer
        return returnResult
    }
    private queryNavDestinationInfo1_serialize(isInner: boolean | undefined): uiObserver.NavDestinationInfo | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (isInner !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isInnerTmpValue  = isInner!
            thisSerializer.writeBoolean(isInnerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_queryNavDestinationInfo1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : uiObserver.NavDestinationInfo | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = uiObserver_NavDestinationInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : uiObserver.NavDestinationInfo | undefined = buffer
        return returnResult
    }
    private queryNavigationInfo_serialize(): uiObserver.NavigationInfo | undefined {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_queryNavigationInfo(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : uiObserver.NavigationInfo | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = uiObserver_NavigationInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : uiObserver.NavigationInfo | undefined = buffer
        return returnResult
    }
    private queryRouterPageInfo_serialize(): uiObserver.RouterPageInfo | undefined {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_queryRouterPageInfo(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : uiObserver.RouterPageInfo | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (uiObserver_RouterPageInfo_serializer.read(retvalDeserializer) as uiObserver.RouterPageInfo)
        }
        const returnResult : uiObserver.RouterPageInfo | undefined = buffer
        return returnResult
    }
}
export interface LifeCycle {
    aboutToAppear(): void
    aboutToDisappear(): void
    onDidBuild(): void
    build(): void
}
export class LifeCycleInternal implements MaterializedBase,LifeCycle {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LifeCycleInternal.getFinalizer())
    }
    constructor() {
        this(LifeCycleInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LifeCycle_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LifeCycle_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): LifeCycleInternal {
        return new LifeCycleInternal(ptr)
    }
    public aboutToAppear(): void {
        this.aboutToAppear_serialize()
        return
    }
    public aboutToDisappear(): void {
        this.aboutToDisappear_serialize()
        return
    }
    public onDidBuild(): void {
        this.onDidBuild_serialize()
        return
    }
    public build(): void {
        this.build_serialize()
        return
    }
    private aboutToAppear_serialize(): void {
        ArkUIGeneratedNativeModule._LifeCycle_aboutToAppear(this.peer!.ptr)
    }
    private aboutToDisappear_serialize(): void {
        ArkUIGeneratedNativeModule._LifeCycle_aboutToDisappear(this.peer!.ptr)
    }
    private onDidBuild_serialize(): void {
        ArkUIGeneratedNativeModule._LifeCycle_onDidBuild(this.peer!.ptr)
    }
    private build_serialize(): void {
        ArkUIGeneratedNativeModule._LifeCycle_build(this.peer!.ptr)
    }
}
export class ExtendableComponent_serializer {
    public static write(buffer: SerializerBase, value: ExtendableComponent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ExtendableComponent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ExtendableComponentInternal.fromPtr(ptr)
    }
}
export class LifeCycle_serializer {
    public static write(buffer: SerializerBase, value: LifeCycle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LifeCycle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LifeCycleInternal.fromPtr(ptr)
    }
}
