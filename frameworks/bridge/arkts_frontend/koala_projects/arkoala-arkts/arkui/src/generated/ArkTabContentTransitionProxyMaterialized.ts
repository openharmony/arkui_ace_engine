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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface TabContentTransitionProxy {
    from: number
    to: number
    finishTransition(): void
}
export class TabContentTransitionProxyInternal implements MaterializedBase,TabContentTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get from(): number {
        return this.getFrom()
    }
    set from(from: number) {
        this.setFrom(from)
    }
    get to(): number {
        return this.getTo()
    }
    set to(to: number) {
        this.setTo(to)
    }
    static ctor_tabcontenttransitionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TabContentTransitionProxyInternal.ctor_tabcontenttransitionproxy()
        this.peer = new Finalizable(ctorPtr, TabContentTransitionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFinalizer()
    }
    public finishTransition(): void {
        this.finishTransition_serialize()
        return
    }
    private getFrom(): number {
        return this.getFrom_serialize()
    }
    private setFrom(from: number): void {
        const from_casted = from as (number)
        this.setFrom_serialize(from_casted)
        return
    }
    private getTo(): number {
        return this.getTo_serialize()
    }
    private setTo(to: number): void {
        const to_casted = to as (number)
        this.setTo_serialize(to_casted)
        return
    }
    private finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private getFrom_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getFrom(this.peer!.ptr)
        return retval
    }
    private setFrom_serialize(from: number): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_setFrom(this.peer!.ptr, from)
    }
    private getTo_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TabContentTransitionProxy_getTo(this.peer!.ptr)
        return retval
    }
    private setTo_serialize(to: number): void {
        ArkUIGeneratedNativeModule._TabContentTransitionProxy_setTo(this.peer!.ptr, to)
    }
    public static fromPtr(ptr: KPointer): TabContentTransitionProxyInternal {
        const obj : TabContentTransitionProxyInternal = new TabContentTransitionProxyInternal()
        obj.peer = new Finalizable(ptr, TabContentTransitionProxyInternal.getFinalizer())
        return obj
    }
}
