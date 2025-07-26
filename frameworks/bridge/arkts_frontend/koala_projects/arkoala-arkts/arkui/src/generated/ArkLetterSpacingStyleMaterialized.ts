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
export class LetterSpacingStyleInternal {
    public static fromPtr(ptr: KPointer): LetterSpacingStyle {
        const obj : LetterSpacingStyle = new LetterSpacingStyle(undefined)
        obj.peer = new Finalizable(ptr, LetterSpacingStyle.getFinalizer())
        return obj
    }
}
export class LetterSpacingStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get letterSpacing(): number {
        return this.getLetterSpacing()
    }
    static ctor_letterspacingstyle(value: LengthMetrics): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LetterSpacingStyle_ctor(toPeerPtr(value))
        return retval
    }
    constructor(value?: LengthMetrics) {
        if ((value) !== (undefined))
        {
            const ctorPtr : KPointer = LetterSpacingStyle.ctor_letterspacingstyle((value)!)
            this.peer = new Finalizable(ctorPtr, LetterSpacingStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LetterSpacingStyle_getFinalizer()
    }
    private getLetterSpacing(): number {
        return this.getLetterSpacing_serialize()
    }
    private getLetterSpacing_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LetterSpacingStyle_getLetterSpacing(this.peer!.ptr)
        return retval
    }
}
