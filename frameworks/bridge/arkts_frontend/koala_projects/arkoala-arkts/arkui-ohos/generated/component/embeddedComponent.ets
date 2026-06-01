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

import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { extractors, EmbeddedComponentAttribute } from '#handwritten'
import { ComponentContentBase } from 'arkui.ComponentContent'
import { default as Want } from '@ohos.app.ability.Want'
import { EmbeddedType } from './enums'
import { ComponentContentBase_serializer } from './../framework/ComponentContent'
import { CallbackTransformer } from './../CallbackTransformer'
export enum EmbeddedDpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
export enum EmbeddedWindowModeFollowStrategy {
    FOLLOW_HOST_WINDOW_MODE = 0,
    FOLLOW_UI_EXTENSION_ABILITY_WINDOW_MODE = 1
}
export interface EmbeddedOptions {
    placeholder?: ComponentContentBase;
    areaChangePlaceholder?: Record<string, ComponentContentBase>;
    dpiFollowStrategy?: EmbeddedDpiFollowStrategy;
    windowModeFollowStrategy?: EmbeddedWindowModeFollowStrategy;
}

export class EmbeddedOptions_serializer {
    public static write(buffer: SerializerBase, value: EmbeddedOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForPlaceholder = value.placeholder
        if (valueHolderForPlaceholder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPlaceholderTmpValue = valueHolderForPlaceholder!
            ComponentContentBase_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAreaChangePlaceholder = value.areaChangePlaceholder
        if (valueHolderForAreaChangePlaceholder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAreaChangePlaceholderTmpValue = valueHolderForAreaChangePlaceholder!
            valueSerializer.writeInt32((valueHolderForAreaChangePlaceholderTmpValue.size).toInt())
            for (const pair of valueHolderForAreaChangePlaceholderTmpValue) {
                const valueHolderForAreaChangePlaceholderTmpValueKeyVar = pair[0]
                const valueHolderForAreaChangePlaceholderTmpValueValueVar = pair[1]
                valueSerializer.writeString(valueHolderForAreaChangePlaceholderTmpValueKeyVar)
                ComponentContentBase_serializer.write(valueSerializer, valueHolderForAreaChangePlaceholderTmpValueValueVar)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDpiFollowStrategy = value.dpiFollowStrategy
        if (valueHolderForDpiFollowStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDpiFollowStrategyTmpValue = (valueHolderForDpiFollowStrategy as EmbeddedDpiFollowStrategy)
            valueSerializer.writeInt32(valueHolderForDpiFollowStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWindowModeFollowStrategy = value.windowModeFollowStrategy
        if (valueHolderForWindowModeFollowStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWindowModeFollowStrategyTmpValue = (valueHolderForWindowModeFollowStrategy as EmbeddedWindowModeFollowStrategy)
            valueSerializer.writeInt32(valueHolderForWindowModeFollowStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmbeddedOptions {
        let valueDeserializer: DeserializerBase = buffer
        const placeholderTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let placeholderTmpBuf: ComponentContentBase | undefined = undefined
        if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            placeholderTmpBuf = (ComponentContentBase_serializer.read(valueDeserializer) as ComponentContentBase)
        }
        const placeholderTmpResult: ComponentContentBase | undefined = placeholderTmpBuf
        const areaChangePlaceholderTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let areaChangePlaceholderTmpBuf: Record<string, ComponentContentBase> | undefined = undefined
        if ((areaChangePlaceholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const areaChangePlaceholderTmpBufOptSizeVar: int32 = valueDeserializer.readInt32()
            let areaChangePlaceholderTmpBufOpt: Record<string, ComponentContentBase> = new Record<string, ComponentContentBase>()
            // TODO: TS map resize
            for (let areaChangePlaceholderTmpBufOptIVar = 0; areaChangePlaceholderTmpBufOptIVar < areaChangePlaceholderTmpBufOptSizeVar; areaChangePlaceholderTmpBufOptIVar++) {
                const areaChangePlaceholderTmpBufOptKeyVar: string = (valueDeserializer.readString() as string)
                const areaChangePlaceholderTmpBufOptValueVar: ComponentContentBase = (ComponentContentBase_serializer.read(valueDeserializer) as ComponentContentBase)
                areaChangePlaceholderTmpBufOpt.set(areaChangePlaceholderTmpBufOptKeyVar, areaChangePlaceholderTmpBufOptValueVar)
            }
            areaChangePlaceholderTmpBuf = areaChangePlaceholderTmpBufOpt
        }
        const areaChangePlaceholderTmpResult: Record<string, ComponentContentBase> | undefined = areaChangePlaceholderTmpBuf
        const dpiFollowStrategyTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let dpiFollowStrategyTmpBuf: EmbeddedDpiFollowStrategy | undefined = undefined
        if ((dpiFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dpiFollowStrategyTmpBuf = EmbeddedDpiFollowStrategy.fromValue(valueDeserializer.readInt32())
        }
        const dpiFollowStrategyTmpResult: EmbeddedDpiFollowStrategy | undefined = dpiFollowStrategyTmpBuf
        const windowModeFollowStrategyTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let windowModeFollowStrategyTmpBuf: EmbeddedWindowModeFollowStrategy | undefined = undefined
        if ((windowModeFollowStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            windowModeFollowStrategyTmpBuf = EmbeddedWindowModeFollowStrategy.fromValue(valueDeserializer.readInt32())
        }
        const windowModeFollowStrategyTmpResult: EmbeddedWindowModeFollowStrategy | undefined = windowModeFollowStrategyTmpBuf
        let value: EmbeddedOptions = ({placeholder: placeholderTmpResult, areaChangePlaceholder: areaChangePlaceholderTmpResult, dpiFollowStrategy: dpiFollowStrategyTmpResult, windowModeFollowStrategy: windowModeFollowStrategyTmpResult} as EmbeddedOptions)
        return value
    }
}
