/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { extractors } from '#handwritten'
import { FrameNode, InteractionEventBindingInfo, LayoutConstraint } from 'arkui.FrameNode'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
import { Size_serializer } from './Graphics'
import { Size } from 'arkui.Graphics'
export class FrameNode_serializer {
    public static write(buffer: SerializerBase, value: FrameNode): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(extractors.toFrameNodePtr(value))
    }
    public static read(buffer: DeserializerBase): FrameNode {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return extractors.fromFrameNodePtr(ptr)
    }
}
export class InteractionEventBindingInfo_serializer {
    public static write(buffer: SerializerBase, value: InteractionEventBindingInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForBaseEventRegistered = value.baseEventRegistered
        valueSerializer.writeBoolean(valueHolderForBaseEventRegistered)
        const valueHolderForNodeEventRegistered = value.nodeEventRegistered
        valueSerializer.writeBoolean(valueHolderForNodeEventRegistered)
        const valueHolderForNativeEventRegistered = value.nativeEventRegistered
        valueSerializer.writeBoolean(valueHolderForNativeEventRegistered)
        const valueHolderForBuiltInEventRegistered = value.builtInEventRegistered
        valueSerializer.writeBoolean(valueHolderForBuiltInEventRegistered)
    }
    public static read(buffer: DeserializerBase): InteractionEventBindingInfo {
        let valueDeserializer: DeserializerBase = buffer
        const baseEventRegisteredTmpResult: boolean = valueDeserializer.readBoolean()
        const nodeEventRegisteredTmpResult: boolean = valueDeserializer.readBoolean()
        const nativeEventRegisteredTmpResult: boolean = valueDeserializer.readBoolean()
        const builtInEventRegisteredTmpResult: boolean = valueDeserializer.readBoolean()
        let value: InteractionEventBindingInfo = ({baseEventRegistered: baseEventRegisteredTmpResult, nodeEventRegistered: nodeEventRegisteredTmpResult, nativeEventRegistered: nativeEventRegisteredTmpResult, builtInEventRegistered: builtInEventRegisteredTmpResult} as InteractionEventBindingInfo)
        return value
    }
}
export class LayoutConstraint_serializer {
    public static write(buffer: SerializerBase, value: LayoutConstraint): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForMaxSize = value.maxSize
        Size_serializer.write(valueSerializer, valueHolderForMaxSize)
        const valueHolderForMinSize = value.minSize
        Size_serializer.write(valueSerializer, valueHolderForMinSize)
        const valueHolderForPercentReference = value.percentReference
        Size_serializer.write(valueSerializer, valueHolderForPercentReference)
    }
    public static read(buffer: DeserializerBase): LayoutConstraint {
        let valueDeserializer: DeserializerBase = buffer
        const maxSizeTmpResult: Size = Size_serializer.read(valueDeserializer)
        const minSizeTmpResult: Size = Size_serializer.read(valueDeserializer)
        const percentReferenceTmpResult: Size = Size_serializer.read(valueDeserializer)
        let value: LayoutConstraint = ({maxSize: maxSizeTmpResult, minSize: minSizeTmpResult, percentReference: percentReferenceTmpResult} as LayoutConstraint)
        return value
    }
}
