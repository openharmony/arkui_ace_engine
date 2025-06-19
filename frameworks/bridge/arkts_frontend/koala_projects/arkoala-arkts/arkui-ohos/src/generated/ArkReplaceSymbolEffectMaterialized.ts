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

import { SymbolEffect, EffectScope } from "./ArkArkuiExternalInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class ReplaceSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): ReplaceSymbolEffect {
        const obj : ReplaceSymbolEffect = new ReplaceSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, ReplaceSymbolEffect.getFinalizer())
        return obj
    }
}
export class ReplaceSymbolEffect implements MaterializedBase,SymbolEffect {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get scope(): EffectScope | undefined {
        return this.getScope()
    }
    set scope(scope: EffectScope | undefined) {
        const scope_NonNull  = (scope as EffectScope)
        this.setScope(scope_NonNull)
    }
    static ctor_replacesymboleffect(scope?: EffectScope): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let scope_type : int32 = RuntimeType.UNDEFINED
        scope_type = runtimeType(scope)
        thisSerializer.writeInt8(scope_type as int32)
        if ((RuntimeType.UNDEFINED) != (scope_type)) {
            const scope_value  = (scope as EffectScope)
            thisSerializer.writeInt32(scope_value.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._ReplaceSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(scope?: EffectScope) {
        const ctorPtr : KPointer = ReplaceSymbolEffect.ctor_replacesymboleffect((scope)!)
        this.peer = new Finalizable(ctorPtr, ReplaceSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ReplaceSymbolEffect_getFinalizer()
    }
    private getScope(): EffectScope {
        return this.getScope_serialize()
    }
    private setScope(scope: EffectScope): void {
        const scope_casted = scope as (EffectScope)
        this.setScope_serialize(scope_casted)
        return
    }
    private getScope_serialize(): EffectScope {
        const retval  = ArkUIGeneratedNativeModule._ReplaceSymbolEffect_getScope(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setScope_serialize(scope: EffectScope): void {
        ArkUIGeneratedNativeModule._ReplaceSymbolEffect_setScope(this.peer!.ptr, scope.valueOf())
    }
}
