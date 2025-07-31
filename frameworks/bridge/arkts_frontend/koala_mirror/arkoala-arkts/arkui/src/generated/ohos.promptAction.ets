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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, DeserializerBase, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class LevelOrderInternal {
    public static fromPtr(ptr: KPointer): LevelOrder {
        return new LevelOrder(ptr)
    }
}
export class LevelOrder implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LevelOrder.getFinalizer())
    }
    constructor() {
        this(LevelOrder.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LevelOrder_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LevelOrder_getFinalizer()
    }
    private static clamp_serialize(order: number): LevelOrder {
        const retval  = ArkUIGeneratedNativeModule._LevelOrder_clamp(order)
        const obj : LevelOrder = LevelOrderInternal.fromPtr(retval)
        return obj
    }
    public static clamp(order: number): LevelOrder {
        const order_casted = order as (number)
        return LevelOrder.clamp_serialize(order_casted)
    }
    public getOrder(): number {
        return this.getOrder_serialize()
    }
    private getOrder_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LevelOrder_getOrder(this.peer!.ptr)
        return retval
    }
}
export enum LevelMode {
    OVERLAY = 0,
    EMBEDDED = 1
}
export enum ImmersiveMode {
    DEFAULT = 0,
    EXTEND = 1
}
export class LevelOrder_serializer {
    public static write(buffer: SerializerBase, value: LevelOrder): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LevelOrder {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LevelOrderInternal.fromPtr(ptr)
    }
}
export namespace promptAction {
    export interface DialogController {
    }
}
