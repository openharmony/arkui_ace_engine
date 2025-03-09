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

import { ShadowOptions, ShadowType } from "./ArkCommonInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Color, ColoringStrategy } from "./ArkEnumsInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class TextShadowStyleInternal {
    public static fromPtr(ptr: KPointer): TextShadowStyle {
        const obj: TextShadowStyle = new TextShadowStyle(undefined)
        obj.peer = new Finalizable(ptr, TextShadowStyle.getFinalizer())
        return obj
    }
}
export class TextShadowStyle implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get textShadow(): Array<ShadowOptions> {
        throw new Error("Not implemented")
    }
    static ctor_textshadowstyle(value: ShadowOptions | Array<ShadowOptions>): KPointer {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("radius")))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ShadowOptions>(value)
            thisSerializer.writeShadowOptions(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof Array<ShadowOptions>)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Array<ShadowOptions>>(value)
            thisSerializer.writeInt32(value_1.length)
            for (let i = 0; i < value_1.length; i++) {
                const value_1_element: ShadowOptions = value_1[i]
                thisSerializer.writeShadowOptions(value_1_element)
            }
        }
        const retval = ArkUIGeneratedNativeModule._TextShadowStyle_ctor(thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
     constructor(value?: ShadowOptions | Array<ShadowOptions>) {
        if ((value) !== (undefined))
        {
            const ctorPtr: KPointer = TextShadowStyle.ctor_textshadowstyle((value)!)
            this.peer = new Finalizable(ctorPtr, TextShadowStyle.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextShadowStyle_getFinalizer()
    }
    private getTextShadow(): Array<ShadowOptions> {
        return this.getTextShadow_serialize()
    }
    private getTextShadow_serialize(): Array<ShadowOptions> {
        const retval = ArkUIGeneratedNativeModule._TextShadowStyle_getTextShadow(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<ShadowOptions> = new Array<ShadowOptions>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readShadowOptions()
        }
        const returnResult: Array<ShadowOptions> = buffer
        return returnResult
    }
}
