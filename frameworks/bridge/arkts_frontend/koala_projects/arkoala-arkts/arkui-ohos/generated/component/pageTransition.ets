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

import { int32, int64, float32 } from '@koalaui/common'
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr } from '@koalaui/interop'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Curve } from './enums'
import { default as curves } from '@ohos.curves'
import { ICurve } from './common'
import { extractors } from '#handwritten'
export enum RouteType {
    None = 0,
    Push = 1,
    Pop = 2,
    NONE = 0,
    PUSH = 1,
    POP = 2
}
export enum SlideEffect {
    Left = 0,
    Right = 1,
    Top = 2,
    Bottom = 3,
    START = 5,
    END = 6,
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3,
    START_DUMMY = 5,
    END_DUMMY = 6
}
export interface PageTransitionOptions {
    type?: RouteType;
    duration?: int32;
    curve?: Curve | string | ICurve;
    delay?: int32;
}
export type PageTransitionCallback = (type: RouteType, progress: double) => void;
