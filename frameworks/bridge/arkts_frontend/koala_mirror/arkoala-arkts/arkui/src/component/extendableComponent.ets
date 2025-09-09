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

import { UIContext, UIContextInternal } from "./../generated/ohos.arkui.UIContext"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
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
    private getUIContext_serialize(): UIContext {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_getUIContext(this.peer!.ptr)
        const obj : UIContext = UIContextInternal.fromPtr(retval)
        return obj
    }
    private getUniqueId_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._ExtendableComponent_getUniqueId(this.peer!.ptr)
        return retval
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
