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

import { GestureInterface, SwipeDirection } from "./ArkGestureInterfaces"
import { SourceTool } from "./ArkCommonInterfaces"
import { Literal_Number_fingers_speed_SwipeDirection_direction, Callback_GestureEvent_Void } from "./SyntheticDeclarations"
import { GestureEvent, GestureEventInternal } from "./ArkGestureEventMaterialized"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface SwipeGestureInterface {
    onAction(event: ((event: GestureEvent) => void)): SwipeGestureInterface
}
export class SwipeGestureInterfaceInternal implements MaterializedBase,GestureInterface<SwipeGestureInterface>,SwipeGestureInterface {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_swipegestureinterface(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureInterface_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SwipeGestureInterfaceInternal.ctor_swipegestureinterface()
        this.peer = new Finalizable(ctorPtr, SwipeGestureInterfaceInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SwipeGestureInterface_getFinalizer()
    }
    public onAction(event: ((event: GestureEvent) => void)): SwipeGestureInterface {
        const event_casted = event as (((event: GestureEvent) => void))
        return this.onAction_serialize(event_casted)
    }
    private onAction_serialize(event: ((event: GestureEvent) => void)): SwipeGestureInterface {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        const retval  = ArkUIGeneratedNativeModule._SwipeGestureInterface_onAction(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SwipeGestureInterface = SwipeGestureInterfaceInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): SwipeGestureInterfaceInternal {
        const obj : SwipeGestureInterfaceInternal = new SwipeGestureInterfaceInternal()
        obj.peer = new Finalizable(ptr, SwipeGestureInterfaceInternal.getFinalizer())
        return obj
    }
}
