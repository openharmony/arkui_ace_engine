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

import { default as common2D } from "@ohos.graphics.common2D"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export class common2D_Rect_serializer {
    public static write(buffer: SerializerBase, value: common2D.Rect): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLeft  = value.left
        valueSerializer.writeFloat64(valueHolderForLeft)
        const valueHolderForTop  = value.top
        valueSerializer.writeFloat64(valueHolderForTop)
        const valueHolderForRight  = value.right
        valueSerializer.writeFloat64(valueHolderForRight)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeFloat64(valueHolderForBottom)
    }
    public static read(buffer: DeserializerBase): common2D.Rect {
        let valueDeserializer : DeserializerBase = buffer
        const leftTmpResult : double = valueDeserializer.readFloat64()
        const topTmpResult : double = valueDeserializer.readFloat64()
        const rightTmpResult : double = valueDeserializer.readFloat64()
        const bottomTmpResult : double = valueDeserializer.readFloat64()
        let value : common2D.Rect = ({left: leftTmpResult, top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult} as common2D.Rect)
        return value
    }
}
