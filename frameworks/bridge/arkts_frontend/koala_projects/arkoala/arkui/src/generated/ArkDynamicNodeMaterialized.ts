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

import { OnMoveHandler } from "./ArkCommonInterfaces"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class DynamicNodeInternal {
    public static fromPtr<T>(ptr: KPointer): DynamicNode<T> {
        const obj: DynamicNode<T> = new DynamicNode<T>()
        obj.peer = new Finalizable(ptr, DynamicNode.getFinalizer())
        return obj
    }
}
export class DynamicNode<T> implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_dynamicnode(): KPointer {
        const retval = ArkUIGeneratedNativeModule._DynamicNode_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = DynamicNode.ctor_dynamicnode()
        this.peer = new Finalizable(ctorPtr, DynamicNode.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._DynamicNode_getFinalizer()
    }
    public onMove(handler?: OnMoveHandler): T {
        const handler_casted = handler as (OnMoveHandler | undefined)
        return this.onMove_serialize(handler_casted)
    }
    private onMove_serialize(handler?: OnMoveHandler): T {
        const thisSerializer: Serializer = Serializer.hold()
        let handler_type: int32 = RuntimeType.UNDEFINED
        handler_type = runtimeType(handler)
        thisSerializer.writeInt8(handler_type)
        if ((RuntimeType.UNDEFINED) != (handler_type)) {
            const handler_value = handler!
            thisSerializer.holdAndWriteCallback(handler_value)
        }
        const retval = ArkUIGeneratedNativeModule._DynamicNode_onMove(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
    }
}
