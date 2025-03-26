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

import { CanvasPath, CanvasPathInternal } from "./ArkCanvasPathMaterialized"
import { LengthMetricsUnit } from "./ArkUnitsInterfaces"
import { Matrix2D, Matrix2DInternal } from "./ArkMatrix2DMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class Path2DInternal {
    public static fromPtr(ptr: KPointer): Path2D {
        const obj : Path2D = new Path2D()
        obj.peer = new Finalizable(ptr, Path2D.getFinalizer())
        return obj
    }
}
export class Path2D extends CanvasPath implements MaterializedBase {
    static ctor_path2d(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Path2D_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = Path2D.ctor_path2d()
        this.peer = new Finalizable(ctorPtr, Path2D.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Path2D_getFinalizer()
    }
    public addPath(path: Path2D, transform?: Matrix2D): void {
        const path_casted = path as (Path2D)
        const transform_casted = transform as (Matrix2D | undefined)
        this.addPath_serialize(path_casted, transform_casted)
        return
    }
    private addPath_serialize(path: Path2D, transform?: Matrix2D): void {
        const thisSerializer : Serializer = Serializer.hold()
        let transform_type : int32 = RuntimeType.UNDEFINED
        transform_type = runtimeType(transform)
        thisSerializer.writeInt8(transform_type as int32)
        if ((RuntimeType.UNDEFINED) != (transform_type)) {
            const transform_value  = transform!
            thisSerializer.writeMatrix2D(transform_value)
        }
        ArkUIGeneratedNativeModule._Path2D_addPath(this.peer!.ptr, toPeerPtr(path), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
