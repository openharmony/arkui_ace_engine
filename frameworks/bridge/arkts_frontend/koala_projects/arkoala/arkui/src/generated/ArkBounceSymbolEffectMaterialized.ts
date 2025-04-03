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

import { SymbolEffect, EffectScope, EffectDirection } from "./ArkArkuiExternalInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class BounceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): BounceSymbolEffect {
        const obj: BounceSymbolEffect = new BounceSymbolEffect(undefined, undefined)
        obj.peer = new Finalizable(ptr, BounceSymbolEffect.getFinalizer())
        return obj
    }
}
export class BounceSymbolEffect implements MaterializedBase,SymbolEffect {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get scope(): EffectScope {
        return this.getScope()
    }
    set scope(scope: EffectScope) {
        const scope_NonNull = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    get direction(): EffectDirection {
        return this.getDirection()
    }
    set direction(direction: EffectDirection) {
        const direction_NonNull = (direction as EffectDirection)
        this.setDirection(direction_NonNull)
    }
    static ctor_bouncesymboleffect(scope?: EffectScope, direction?: EffectDirection): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let scope_type: int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value = scope!
            thisSerializer.writeInt32(scope_value)
        }
        let direction_type: int32 = RuntimeType.UNDEFINED
        direction_type = runtimeType(direction)
        thisSerializer.writeInt8(direction_type)
        if ((RuntimeType.UNDEFINED) != (direction_type)) {
            const direction_value = direction!
            thisSerializer.writeInt32(direction_value)
        }
        const retval = ArkUIGeneratedNativeModule._BounceSymbolEffect_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(scope?: EffectScope, direction?: EffectDirection) {
        const ctorPtr: KPointer = BounceSymbolEffect.ctor_bouncesymboleffect((scope)!, (direction)!)
        this.peer = new Finalizable(ctorPtr, BounceSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BounceSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this?.setScope_serialize(scope_casted)
        return
    }
    private getDirection(): EffectDirection {
        return this.getDirection_serialize()
    }
    private setDirection(direction: EffectDirection): void {
        const direction_casted = direction as (EffectDirection)
        this?.setDirection_serialize(direction_casted)
        return
    }
    private getScope_serialize(): EffectScope {
        const retval = ArkUIGeneratedNativeModule._BounceSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setScope(this.peer!.ptr, scope)
    }
    private getDirection_serialize(): EffectDirection {
        const retval = ArkUIGeneratedNativeModule._BounceSymbolEffect_getDirection(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setDirection_serialize(direction: EffectDirection): void {
        ArkUIGeneratedNativeModule._BounceSymbolEffect_setDirection(this.peer!.ptr, direction)
    }
}
