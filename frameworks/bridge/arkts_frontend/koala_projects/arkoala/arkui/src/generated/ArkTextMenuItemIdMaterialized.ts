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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class TextMenuItemIdInternal {
    public static fromPtr(ptr: KPointer): TextMenuItemId {
        const obj: TextMenuItemId = new TextMenuItemId()
        obj.peer = new Finalizable(ptr, TextMenuItemId.getFinalizer())
        return obj
    }
}
export class TextMenuItemId implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static get CUT(): TextMenuItemId {
        return TextMenuItemId.getCUT()
    }
    static get COPY(): TextMenuItemId {
        return TextMenuItemId.getCOPY()
    }
    static get PASTE(): TextMenuItemId {
        return TextMenuItemId.getPASTE()
    }
    static get SELECT_ALL(): TextMenuItemId {
        return TextMenuItemId.getSELECT_ALL()
    }
    static get COLLABORATION_SERVICE(): TextMenuItemId {
        return TextMenuItemId.getCOLLABORATION_SERVICE()
    }
    static get CAMERA_INPUT(): TextMenuItemId {
        return TextMenuItemId.getCAMERA_INPUT()
    }
    static get AI_WRITER(): TextMenuItemId {
        return TextMenuItemId.getAI_WRITER()
    }
    static ctor_textmenuitemid(): KPointer {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr: KPointer = TextMenuItemId.ctor_textmenuitemid()
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
    private static getCUT(): TextMenuItemId {
        return TextMenuItemId.getCUT_serialize()
    }
    private static getCOPY(): TextMenuItemId {
        return TextMenuItemId.getCOPY_serialize()
    }
    private static getPASTE(): TextMenuItemId {
        return TextMenuItemId.getPASTE_serialize()
    }
    private static getSELECT_ALL(): TextMenuItemId {
        return TextMenuItemId.getSELECT_ALL_serialize()
    }
    private static getCOLLABORATION_SERVICE(): TextMenuItemId {
        return TextMenuItemId.getCOLLABORATION_SERVICE_serialize()
    }
    private static getCAMERA_INPUT(): TextMenuItemId {
        return TextMenuItemId.getCAMERA_INPUT_serialize()
    }
    private static getAI_WRITER(): TextMenuItemId {
        return TextMenuItemId.getAI_WRITER_serialize()
    }
    private static of_serialize(id: ResourceStr): TextMenuItemId {
        const thisSerializer: Serializer = Serializer.hold()
        let id_type: int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        if (RuntimeType.STRING == id_type) {
            thisSerializer.writeInt8(0)
            const id_0 = unsafeCast<string>(id)
            thisSerializer.writeString(id_0)
        }
        else if (RuntimeType.OBJECT == id_type) {
            thisSerializer.writeInt8(1)
            const id_1 = unsafeCast<Resource>(id)
            thisSerializer.writeResource(id_1)
        }
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_of(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private equals_serialize(id: TextMenuItemId): boolean {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_equals(this.peer!.ptr, toPeerPtr(id))
        return retval
    }
    private static getCUT_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCUT()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCOPY_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCOPY()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getPASTE_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getPASTE()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getSELECT_ALL_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getSELECT_ALL()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCOLLABORATION_SERVICE_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCOLLABORATION_SERVICE()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCAMERA_INPUT_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCAMERA_INPUT()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getAI_WRITER_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getAI_WRITER()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
}
