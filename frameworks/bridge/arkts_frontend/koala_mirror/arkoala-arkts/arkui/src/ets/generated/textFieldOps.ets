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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { ResourceStr } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
export class TextFieldOps {
    public static registerTextFieldValueCallback(node: KPointer, value: ResourceStr, callback: TextFieldValueCallback): KPointer {
        const node_casted = node as (KPointer)
        const value_casted = value as (ResourceStr)
        const callback_casted = callback as (TextFieldValueCallback)
        return TextFieldOps.registerTextFieldValueCallback_serialize(node_casted, value_casted, callback_casted)
    }
    private static registerTextFieldValueCallback_serialize(node: KPointer, value: ResourceStr, callback: TextFieldValueCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            Resource_serializer.write(thisSerializer, value_1)
        }
        thisSerializer.holdAndWriteCallback(callback)
        const retval  = ArkUIGeneratedNativeModule._TextFieldOps_registerTextFieldValueCallback(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export type TextFieldValueCallback = (value: ResourceStr) => void;
