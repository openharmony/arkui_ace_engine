/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

export {
    int8,
    uint8,
    int32,
    int32toFloat32,
    int32toFloat64,
    int32to64,
    uint32,
    int64,
    int64toFloat32,
    int64toFloat64,
    int64to32,
    uint64,
    float32,
    float32to64,
    float32toInt32,
    float32toInt64,
    float64,
    float64to32,
    float64toInt32,
    float64toInt64,
    asFloat64,
    AtomicRef,
    CustomTextDecoder,
    CustomTextEncoder,
    className,
    functionOverValue,
    Observed,
    Observable,
    ObservableHandler,
    observableProxy,
    observableProxyArray,
    isFunction,
    propDeepCopy,
    errorAsString,
    unsafeCast,
    WorkerLocalValue,
    scheduleCoroutine,
    memoryStats,
    launchJob,
} from '@koalaui/compat';
export { clamp, lerp, modulo, parseNumber, isFiniteNumber, getDistancePx } from './math';
export { hashCodeFromString } from './stringUtils';
export * from './Finalization';
export { SHA1Hash, createSha1 } from './sha1';
export { UniqueId } from './uniqueId';
export * from './koalaKey';
