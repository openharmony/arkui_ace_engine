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

import { UIGestureEvent, SourceTool } from "./ArkCommonInterfaces"
import { GestureHandler, GesturePriority, GestureMask, GestureInterface } from "./ArkGestureInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface GestureModifier {
    applyGesture(event: UIGestureEvent): void
}
export class GestureModifierInternal implements MaterializedBase,GestureModifier {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_gesturemodifier(): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureModifier_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = GestureModifierInternal.ctor_gesturemodifier()
        this.peer = new Finalizable(ctorPtr, GestureModifierInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._GestureModifier_getFinalizer()
    }
    public applyGesture(event: UIGestureEvent): void {
        const event_casted = event as (UIGestureEvent)
        this?.applyGesture_serialize(event_casted)
        return
    }
    private applyGesture_serialize(event: UIGestureEvent): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeUIGestureEvent(event)
        ArkUIGeneratedNativeModule._GestureModifier_applyGesture(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): GestureModifierInternal {
        const obj: GestureModifierInternal = new GestureModifierInternal()
        obj.peer = new Finalizable(ptr, GestureModifierInternal.getFinalizer())
        return obj
    }
}
