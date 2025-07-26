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

import { SymbolEffect, SymbolEffectInternal } from "./ArkSymbolEffectMaterialized"
import { EffectFillStyle } from "./ArkSymbolglyphInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class HierarchicalSymbolEffectInternal {
    public static fromPtr(ptr: KPointer): HierarchicalSymbolEffect {
        const obj : HierarchicalSymbolEffect = new HierarchicalSymbolEffect(undefined)
        obj.peer = new Finalizable(ptr, HierarchicalSymbolEffect.getFinalizer())
        return obj
    }
}
export class HierarchicalSymbolEffect extends SymbolEffect implements MaterializedBase {
    get fillStyle(): EffectFillStyle | undefined {
        return this.getFillStyle()
    }
    set fillStyle(fillStyle: EffectFillStyle | undefined) {
        const fillStyle_NonNull  = (fillStyle as EffectFillStyle)
        this.setFillStyle(fillStyle_NonNull)
    }
    static ctor_hierarchicalsymboleffect(fillStyle?: EffectFillStyle): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let fillStyle_type : int32 = RuntimeType.UNDEFINED
        fillStyle_type = runtimeType(fillStyle)
        thisSerializer.writeInt8(fillStyle_type as int32)
        if ((RuntimeType.UNDEFINED) != (fillStyle_type)) {
            const fillStyle_value  = (fillStyle as EffectFillStyle)
            thisSerializer.writeInt32(fillStyle_value.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(fillStyle?: EffectFillStyle) {
        super()
        const ctorPtr : KPointer = HierarchicalSymbolEffect.ctor_hierarchicalsymboleffect((fillStyle)!)
        this.peer = new Finalizable(ctorPtr, HierarchicalSymbolEffect.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFinalizer()
    }
    private getFillStyle(): EffectFillStyle {
        return this.getFillStyle_serialize()
    }
    private setFillStyle(fillStyle: EffectFillStyle): void {
        const fillStyle_casted = fillStyle as (EffectFillStyle)
        this.setFillStyle_serialize(fillStyle_casted)
        return
    }
    private getFillStyle_serialize(): EffectFillStyle {
        const retval  = ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_getFillStyle(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setFillStyle_serialize(fillStyle: EffectFillStyle): void {
        ArkUIGeneratedNativeModule._HierarchicalSymbolEffect_setFillStyle(this.peer!.ptr, fillStyle.valueOf())
    }
}
