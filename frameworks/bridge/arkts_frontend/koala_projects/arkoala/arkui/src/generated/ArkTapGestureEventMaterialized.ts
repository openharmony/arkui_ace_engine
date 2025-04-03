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

import { BaseGestureEvent, BaseGestureEventInternal } from "./ArkBaseGestureEventMaterialized"
import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { FingerInfo } from "./ArkGestureInterfaces"
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
export interface TapGestureEvent {
}
export class TapGestureEventInternal extends BaseGestureEventInternal implements MaterializedBase,TapGestureEvent {
    static ctor_tapgestureevent(): KPointer {
        const retval = ArkUIGeneratedNativeModule._TapGestureEvent_ctor()
        return retval
    }
     constructor() {
        super()
        const ctorPtr: KPointer = TapGestureEventInternal.ctor_tapgestureevent()
        this.peer = new Finalizable(ctorPtr, TapGestureEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TapGestureEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TapGestureEventInternal {
        const obj: TapGestureEventInternal = new TapGestureEventInternal()
        obj.peer = new Finalizable(ptr, TapGestureEventInternal.getFinalizer())
        return obj
    }
}
