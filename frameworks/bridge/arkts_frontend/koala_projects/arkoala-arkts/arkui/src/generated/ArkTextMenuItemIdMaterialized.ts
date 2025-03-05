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

import { ResourceStr } from "./ArkUnitsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class TextMenuItemIdInternal {
    public static fromPtr(ptr: KPointer): TextMenuItemId {
        const obj : TextMenuItemId = new TextMenuItemId()
        obj.peer = new Finalizable(ptr, TextMenuItemId.getFinalizer())
        return obj
    }
}
export class TextMenuItemId implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static get CUT(): TextMenuItemId {
        throw new Error("Not implemented")
    }
    static get COPY(): TextMenuItemId {
        throw new Error("Not implemented")
    }
    static get PASTE(): TextMenuItemId {
        throw new Error("Not implemented")
    }
    static get SELECT_ALL(): TextMenuItemId {
        throw new Error("Not implemented")
    }
    static get COLLABORATION_SERVICE(): TextMenuItemId {
        throw new Error("Not implemented")
    }
    static get CAMERA_INPUT(): TextMenuItemId {
        throw new Error("Not implemented")
    }
    static get AI_WRITER(): TextMenuItemId {
        throw new Error("Not implemented")
    }
    static ctor_textmenuitemid(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = TextMenuItemId.ctor_textmenuitemid()
        this.peer = new Finalizable(ctorPtr, TextMenuItemId.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextMenuItemId_getFinalizer()
    }
    public static of(id: ResourceStr): TextMenuItemId {
        const id_casted = id as (ResourceStr)
        return TextMenuItemId.of_serialize(id_casted)
    }
    public equals(id: TextMenuItemId): boolean {
        const id_casted = id as (TextMenuItemId)
        return this.equals_serialize(id_casted)
    }
    private static of_serialize(id: ResourceStr): TextMenuItemId {
        const thisSerializer : Serializer = Serializer.hold()
        let id_type : int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        if (RuntimeType.STRING == id_type) {
            thisSerializer.writeInt8(0 as int32)
            const id_0  = id as string
            thisSerializer.writeString(id_0)
        }
        else if (RuntimeType.OBJECT == id_type) {
            thisSerializer.writeInt8(1 as int32)
            const id_1  = id as Resource
            thisSerializer.writeResource(id_1)
        }
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_of(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private equals_serialize(id: TextMenuItemId): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextMenuItemId(id)
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_equals(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
