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
export class LineHeightStyleInternal {
    public static fromPtr(ptr: KPointer): LineHeightStyle {
        const obj : LineHeightStyle = new LineHeightStyle(undefined)
        obj.peer = new Finalizable(ptr, LineHeightStyle.getFinalizer())
        return obj
    }
}
export class LineHeightStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get lineHeight(): number {
        return this.getLineHeight()
    }
    static ctor_lineheightstyle(lineHeight: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LineHeightStyle_ctor(toPeerPtr(lineHeight))
        return retval
    }
    constructor(lineHeight?: LengthMetrics) {
        if ((lineHeight) !== (undefined))
        {
            const ctorPtr : KPointer = LineHeightStyle.ctor_lineheightstyle((lineHeight)!)
            this.peer = new Finalizable(ctorPtr, LineHeightStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LineHeightStyle_getFinalizer()
    }
    private getLineHeight(): number {
        return this.getLineHeight_serialize()
    }
    private getLineHeight_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LineHeightStyle_getLineHeight(this.peer!.ptr)
        return retval
    }
}
