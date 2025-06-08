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

import { GestureRecognizer, GestureRecognizerInternal } from "./ArkGestureRecognizerMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureRecognizerState } from "./ArkGestureInterfaces"
import { EventTargetInfo, EventTargetInfoInternal } from "./ArkEventTargetInfoMaterialized"
import { PanGestureOptions, PanGestureOptionsInternal } from "./ArkPanGestureOptionsMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class PanRecognizerInternal {
    public static fromPtr(ptr: KPointer): PanRecognizer {
        const obj : PanRecognizer = new PanRecognizer()
        obj.peer = new Finalizable(ptr, PanRecognizer.getFinalizer())
        return obj
    }
}
export class PanRecognizer extends GestureRecognizer implements MaterializedBase {
    static ctor_panrecognizer(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanRecognizer_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = PanRecognizer.ctor_panrecognizer()
        this.peer = new Finalizable(ctorPtr, PanRecognizer.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanRecognizer_getFinalizer()
    }
    public getPanGestureOptions(): PanGestureOptions {
        return this.getPanGestureOptions_serialize()
    }
    private getPanGestureOptions_serialize(): PanGestureOptions {
        const retval  = ArkUIGeneratedNativeModule._PanRecognizer_getPanGestureOptions(this.peer!.ptr)
        const obj : PanGestureOptions = PanGestureOptionsInternal.fromPtr(retval)
        return obj
    }
}
