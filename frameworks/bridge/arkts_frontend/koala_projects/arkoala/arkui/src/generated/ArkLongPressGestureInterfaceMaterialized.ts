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

import { GestureInterface, FingerInfo } from "./ArkGestureInterfaces"
import { SourceTool, EventTarget, SourceType } from "./ArkCommonInterfaces"
import { GestureEvent, GestureEventInternal } from "./ArkGestureEventMaterialized"
import { BaseEvent, BaseEventInternal } from "./ArkBaseEventMaterialized"
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
export interface LongPressGestureInterface {
    onAction(event: ((event: GestureEvent) => void)): LongPressGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureInterface
    onActionCancel(event: (() => void)): LongPressGestureInterface
}
export class LongPressGestureInterfaceInternal implements MaterializedBase,GestureInterface<LongPressGestureInterface>,LongPressGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_longpressgestureinterface(): KPointer {
        const retval = ArkUIGeneratedNativeModule._LongPressGestureInterface_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = LongPressGestureInterfaceInternal.ctor_longpressgestureinterface()
        this.peer = new Finalizable(ctorPtr, LongPressGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LongPressGestureInterface_getFinalizer()
    }
    public onAction(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onAction_serialize(event_casted)
    }
    public onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionEnd_serialize(event_casted)
    }
    public onActionCancel(event: (() => void)): LongPressGestureInterface {
        const event_casted = event as ((() => void))
        return this.onActionCancel_serialize(event_casted)
    }
    private onAction_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval = ArkUIGeneratedNativeModule._LongPressGestureInterface_onAction(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): LongPressGestureInterface {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel_serialize(event: (() => void)): LongPressGestureInterface {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval = ArkUIGeneratedNativeModule._LongPressGestureInterface_onActionCancel(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: LongPressGestureInterface = LongPressGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): LongPressGestureInterfaceInternal {
        const obj: LongPressGestureInterfaceInternal = new LongPressGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, LongPressGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
