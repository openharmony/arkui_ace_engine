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

import { LengthMetrics, LengthMetricsInternal } from "./ArkLengthMetricsMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class BaselineOffsetStyleInternal {
    public static fromPtr(ptr: KPointer): BaselineOffsetStyle {
        const obj : BaselineOffsetStyle = new BaselineOffsetStyle(undefined)
        obj.peer = new Finalizable(ptr, BaselineOffsetStyle.getFinalizer())
        return obj
    }
}
export class BaselineOffsetStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get baselineOffset(): number {
        return this.getBaselineOffset()
    }
    static ctor_baselineoffsetstyle(value: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaselineOffsetStyle_ctor(toPeerPtr(value))
        return retval
    }
    constructor(value?: LengthMetrics) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = BaselineOffsetStyle.ctor_baselineoffsetstyle((value)!)
            this.peer = new Finalizable(ctorPtr, BaselineOffsetStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaselineOffsetStyle_getFinalizer()
    }
    private getBaselineOffset(): number {
        return this.getBaselineOffset_serialize()
    }
    private getBaselineOffset_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._BaselineOffsetStyle_getBaselineOffset(this.peer!.ptr)
        return retval
    }
}
