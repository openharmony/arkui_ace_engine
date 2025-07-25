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

import { CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo } from "./ArkStyledStringInterfaces"
import { DrawContext } from "./ArkCommonInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class CustomSpanInternal {
    public static fromPtr(ptr: KPointer): CustomSpan {
        const obj : CustomSpan = new CustomSpan()
        obj.peer = new Finalizable(ptr, CustomSpan.getFinalizer())
        return obj
    }
}
export class CustomSpan implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_customspan(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CustomSpan.ctor_customspan()
        this.peer = new Finalizable(ctorPtr, CustomSpan.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CustomSpan_getFinalizer()
    }
    public onMeasure(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics {
        const measureInfo_casted = measureInfo as (CustomSpanMeasureInfo)
        return this.onMeasure_serialize(measureInfo_casted)
    }
    public onDraw(context: DrawContext, drawInfo: CustomSpanDrawInfo): void {
        const context_casted = context as (DrawContext)
        const drawInfo_casted = drawInfo as (CustomSpanDrawInfo)
        this.onDraw_serialize(context_casted, drawInfo_casted)
        return
    }
    public invalidate(): void {
        this.invalidate_serialize()
        return
    }
    private onMeasure_serialize(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCustomSpanMeasureInfo(measureInfo)
        const retval  = ArkUIGeneratedNativeModule._CustomSpan_onMeasure(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : CustomSpanMetrics = retvalDeserializer.readCustomSpanMetrics()
        return returnResult
    }
    private onDraw_serialize(context: DrawContext, drawInfo: CustomSpanDrawInfo): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDrawContext(context)
        thisSerializer.writeCustomSpanDrawInfo(drawInfo)
        ArkUIGeneratedNativeModule._CustomSpan_onDraw(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private invalidate_serialize(): void {
        ArkUIGeneratedNativeModule._CustomSpan_invalidate(this.peer!.ptr)
    }
}
