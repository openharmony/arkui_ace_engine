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

import { Size } from "./ArkCanvasInterfaces"
import { DrawingCanvas, DrawingCanvasInternal } from "./ArkDrawingCanvasMaterialized"
import { LengthMetricsUnit } from "./ArkUnitsInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class DrawingRenderingContextInternal {
    public static fromPtr(ptr: KPointer): DrawingRenderingContext {
        const obj : DrawingRenderingContext = new DrawingRenderingContext(undefined)
        obj.peer = new Finalizable(ptr, DrawingRenderingContext.getFinalizer())
        return obj
    }
}
export class DrawingRenderingContext implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get size(): Size {
        throw new Error("Not implemented")
    }
    get canvas(): DrawingCanvas {
        return this.getCanvas()
    }
    static ctor_drawingrenderingcontext(unit?: LengthMetricsUnit): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        let unit_type : int32 = RuntimeType.UNDEFINED
        unit_type = runtimeType(unit)
        thisSerializer.writeInt8(unit_type as int32)
        if ((RuntimeType.UNDEFINED) != (unit_type)) {
            const unit_value  = unit!
            thisSerializer.writeLengthMetricsUnit(unit_value)
        }
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(unit?: LengthMetricsUnit) {
        const ctorPtr : KPointer = DrawingRenderingContext.ctor_drawingrenderingcontext((unit)!)
        this.peer = new Finalizable(ctorPtr, DrawingRenderingContext.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DrawingRenderingContext_getFinalizer()
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    private getSize(): Size {
        return this.getSize_serialize()
    }
    private getCanvas(): DrawingCanvas {
        return this.getCanvas_serialize()
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._DrawingRenderingContext_invalidate(this.peer!.ptr)
    }
    private getSize_serialize(): Size {
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_getSize(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : Size = retvalDeserializer.readSize()
        return returnResult
    }
    private getCanvas_serialize(): DrawingCanvas {
        const retval  = ArkUIGeneratedNativeModule._DrawingRenderingContext_getCanvas(this.peer!.ptr)
        const obj : DrawingCanvas = DrawingCanvasInternal.fromPtr(retval)
        return obj
    }
}
