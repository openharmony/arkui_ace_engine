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

import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { Area, Length, Position } from "./ArkUnitsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface HoverEvent {
    stopPropagation: (() => void)
}
export class HoverEventInternal extends BaseEventInternal implements MaterializedBase,HoverEvent {
    get stopPropagation(): (() => void) {
        throw new Error("Not implemented")
    }
    set stopPropagation(stopPropagation: (() => void)) {
        this.setStopPropagation(stopPropagation)
    }
    static ctor_hoverevent(): KPointer {
        const retval = ArkUIGeneratedNativeModule._HoverEvent_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = HoverEventInternal.ctor_hoverevent()
        this.peer = new Finalizable(ctorPtr, HoverEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._HoverEvent_getFinalizer()
    }
    private getStopPropagation(): (() => void) {
        return this.getStopPropagation_serialize()
    }
    private setStopPropagation(stopPropagation: (() => void)): void {
        const stopPropagation_casted = stopPropagation as ((() => void))
        this?.setStopPropagation_serialize(stopPropagation_casted)
        return
    }
    private getStopPropagation_serialize(): (() => void) {
        const retval = ArkUIGeneratedNativeModule._HoverEvent_getStopPropagation(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setStopPropagation_serialize(stopPropagation: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(stopPropagation)
        ArkUIGeneratedNativeModule._HoverEvent_setStopPropagation(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): HoverEventInternal {
        const obj: HoverEventInternal = new HoverEventInternal()
        obj.peer = new Finalizable(ptr, HoverEventInternal.getFinalizer())
        return obj
    }
}
