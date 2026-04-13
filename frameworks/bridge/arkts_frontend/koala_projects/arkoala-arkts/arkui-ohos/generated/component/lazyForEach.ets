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
import { CallbackTransformer } from './../CallbackTransformer'
export enum DataOperationType {
    ADD = 'add',
    DELETE = 'delete',
    EXCHANGE = 'exchange',
    MOVE = 'move',
    CHANGE = 'change',
    RELOAD = 'reload'
}
export enum LazyForEachReleaseStrategy {
    BATCH = 0,
    PROGRESSIVE = 1
}
export enum LazyForEachCustomComponentFreezeMode {
    AUTO = 0,
    DISABLED = 1,
    ENABLED = 2
}
export interface LazyForEachOptions {
    customComponentFreezeMode?: LazyForEachCustomComponentFreezeMode;
    releaseStrategy?: LazyForEachReleaseStrategy;
}
export interface DataAddOperation {
    type: DataOperationType;
    index: int32;
    count?: int32;
    key?: string | Array<string>;
}
export interface DataDeleteOperation {
    type: DataOperationType;
    index: int32;
    count?: int32;
}
export interface DataChangeOperation {
    type: DataOperationType;
    index: int32;
    key?: string;
}
export interface MoveIndex {
    from: int32;
    to: int32;
}
export interface ExchangeIndex {
    start: int32;
    end: int32;
}
export interface ExchangeKey {
    start: string;
    end: string;
}
export interface DataMoveOperation {
    type: DataOperationType;
    index: MoveIndex;
    key?: string;
}
export interface DataExchangeOperation {
    type: DataOperationType;
    index: ExchangeIndex;
    key?: ExchangeKey;
}
export interface DataReloadOperation {
    type: DataOperationType;
}
export type DataOperation = DataAddOperation | DataDeleteOperation | DataChangeOperation | DataMoveOperation | DataExchangeOperation | DataReloadOperation;
export class LazyForEachOptions_serializer {
    public static write(buffer: SerializerBase, value: LazyForEachOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForCustomComponentFreezeMode = value.customComponentFreezeMode
        if (valueHolderForCustomComponentFreezeMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomComponentFreezeModeTmpValue = (valueHolderForCustomComponentFreezeMode as LazyForEachCustomComponentFreezeMode)
            valueSerializer.writeInt32(valueHolderForCustomComponentFreezeModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForReleaseStrategy = value.releaseStrategy
        if (valueHolderForReleaseStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForReleaseStrategyTmpValue = (valueHolderForReleaseStrategy as LazyForEachReleaseStrategy)
            valueSerializer.writeInt32(valueHolderForReleaseStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LazyForEachOptions {
        let valueDeserializer: DeserializerBase = buffer
        const customComponentFreezeModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let customComponentFreezeModeTmpBuf: LazyForEachCustomComponentFreezeMode | undefined = undefined
        if ((customComponentFreezeModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            customComponentFreezeModeTmpBuf = LazyForEachCustomComponentFreezeMode.fromValue(valueDeserializer.readInt32())
        }
        const customComponentFreezeModeTmpResult: LazyForEachCustomComponentFreezeMode | undefined = customComponentFreezeModeTmpBuf
        const releaseStrategyTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let releaseStrategyTmpBuf: LazyForEachReleaseStrategy | undefined = undefined
        if ((releaseStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            releaseStrategyTmpBuf = LazyForEachReleaseStrategy.fromValue(valueDeserializer.readInt32())
        }
        const releaseStrategyTmpResult: LazyForEachReleaseStrategy | undefined = releaseStrategyTmpBuf
        let value: LazyForEachOptions = ({customComponentFreezeMode: customComponentFreezeModeTmpResult, releaseStrategy: releaseStrategyTmpResult} as LazyForEachOptions)
        return value
    }
}
