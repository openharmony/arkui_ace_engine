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

import { Matrix2D, Matrix2DInternal } from "./ArkMatrix2DMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface CanvasPattern {
    setTransform(transform?: Matrix2D): void
}
export class CanvasPatternInternal implements MaterializedBase,CanvasPattern {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_canvaspattern(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CanvasPattern_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CanvasPatternInternal.ctor_canvaspattern()
        this.peer = new Finalizable(ctorPtr, CanvasPatternInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CanvasPattern_getFinalizer()
    }
    public setTransform(transform?: Matrix2D): void {
        const transform_casted = transform as (Matrix2D | undefined)
        this.setTransform_serialize(transform_casted)
        return
    }
    private setTransform_serialize(transform?: Matrix2D): void {
        const thisSerializer : Serializer = Serializer.hold()
        let transform_type : int32 = RuntimeType.UNDEFINED
        transform_type = runtimeType(transform)
        thisSerializer.writeInt8(transform_type as int32)
        if ((RuntimeType.UNDEFINED) != (transform_type)) {
            const transform_value  = transform!
            thisSerializer.writeMatrix2D(transform_value)
        }
        ArkUIGeneratedNativeModule._CanvasPattern_setTransform(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): CanvasPatternInternal {
        const obj : CanvasPatternInternal = new CanvasPatternInternal()
        obj.peer = new Finalizable(ptr, CanvasPatternInternal.getFinalizer())
        return obj
    }
}
