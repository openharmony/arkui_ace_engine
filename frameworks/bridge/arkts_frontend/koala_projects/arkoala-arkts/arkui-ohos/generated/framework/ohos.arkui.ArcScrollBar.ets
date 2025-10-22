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

import { Scroller_serializer, Scroller } from "./../component/scroll"
import { ArcScrollBarOptions } from "@ohos.arkui.ArcScrollBar"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { BarState } from "./../component/enums"
export class ArcScrollBarOptions_serializer {
    public static write(buffer: SerializerBase, value: ArcScrollBarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScroller  = value.scroller
        Scroller_serializer.write(valueSerializer, valueHolderForScroller)
        const valueHolderForState  = value.state
        if (valueHolderForState !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStateTmpValue  = (valueHolderForState as BarState)
            valueSerializer.writeInt32(valueHolderForStateTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ArcScrollBarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scrollerTmpResult : Scroller = (Scroller_serializer.read(valueDeserializer) as Scroller)
        const stateTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stateTmpBuf : BarState | undefined = undefined
        if ((stateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stateTmpBuf = BarState.fromValue(valueDeserializer.readInt32())
        }
        const stateTmpResult : BarState | undefined = stateTmpBuf
        let value : ArcScrollBarOptions = ({scroller: scrollerTmpResult, state: stateTmpResult} as ArcScrollBarOptions)
        return value
    }
}
