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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Curve } from "./ArkEnumsInterfaces"
import { ICurve } from "./ArkICurveMaterialized"
export type Callback_Extender_OnProgress = (value: float32) => void;
export type Callback_Extender_OnFinish = () => void;
export interface DoubleAnimationParam {
    propertyName: string;
    startValue: float32;
    endValue: float32;
    duration: int32;
    delay: int32;
    curve: Curve | string | ICurve;
    onProgress?: Callback_Extender_OnProgress;
    onFinish?: Callback_Extender_OnFinish;
}
