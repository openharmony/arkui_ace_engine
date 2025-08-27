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

import { GestureInterface, PanDirection } from "./ArkGestureInterfaces"
import { SourceTool } from "./ArkCommonInterfaces"
import { Literal_Number_distance_fingers_PanDirection_direction, Callback_GestureEvent_Void, Callback_Void } from "./SyntheticDeclarations"
import { PanGestureOptions, PanGestureOptionsInternal } from "./ArkPanGestureOptionsMaterialized"
import { GestureEvent, GestureEventInternal } from "./ArkGestureEventMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface PanGestureInterface {
    onActionStart(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionEnd(event: ((event: GestureEvent) => void)): PanGestureInterface
    onActionCancel(event: (() => void)): PanGestureInterface
}
export class PanGestureInterfaceInternal implements MaterializedBase,GestureInterface<PanGestureInterface>,PanGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_pangestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = PanGestureInterfaceInternal.ctor_pangestureinterface()
        this.peer = new Finalizable(ctorPtr, PanGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PanGestureInterface_getFinalizer()
    }
    public onActionStart(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionStart_serialize(event_casted)
    }
    public onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionUpdate_serialize(event_casted)
    }
    public onActionEnd(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onActionEnd_serialize(event_casted)
    }
    public onActionCancel(event: (() => void)): PanGestureInterface {
        const event_casted = event as ((() => void))
        return this.onActionCancel_serialize(event_casted)
    }
    private onActionStart_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionStart(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionUpdate_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionUpdate(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionEnd_serialize(event: ((event: GestureEvent) => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionEnd(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    private onActionCancel_serialize(event: (() => void)): PanGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._PanGestureInterface_onActionCancel(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : PanGestureInterface = PanGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): PanGestureInterfaceInternal {
        const obj : PanGestureInterfaceInternal = new PanGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, PanGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
