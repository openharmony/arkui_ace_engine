/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"

export enum ArkAlignment {
    TopStart,
    Top,
    TopEnd,
    Start,
    Center,
    End,
    BottomStart,
    Bottom,
    BottomEnd,
}

export function parseLength(parentValue: number, value: number, unit: int32): number {
    switch (unit) {
        //PX
        case 0: {
            const scale = 1 // TODO: need getting current device scale
            return value * scale
        }
        //PERCENTAGE
        case 3: {
            return parentValue / 100 * value
        }
        default:
            // VP, FP, LPX, UndefinedDimensionUnit: TODO: parse properly this units
            return value
    }
}

export function align(
    alignment: ArkAlignment,
    width: number,
    height: number,
    childWidth: number,
    childHeight: number,
    args: Float32Array
) {
    switch (alignment) {
        case ArkAlignment.TopStart: {
            break
        }
        case ArkAlignment.Start: {
            args[1] += (height - childHeight) / 2
            break
        }
        case ArkAlignment.BottomStart: {
            args[1] += height - childHeight
            break
        }
        case ArkAlignment.Top: {
            args[0] += (width - childWidth) / 2
            break
        }
        case ArkAlignment.Center: {
            args[0] += (width - childWidth) / 2
            args[1] += (height - childHeight) / 2
            break
        }
        case ArkAlignment.Bottom: {
            args[0] += (width - childWidth) / 2
            args[1] += height - childHeight
            break
        }
        case ArkAlignment.TopEnd: {
            args[0] += width - childWidth
            break
        }
        case ArkAlignment.End: {
            args[0] += width - childWidth
            args[1] += (height - childHeight) / 2
            break
        }
        case ArkAlignment.BottomEnd: {
            args[0] += width - childWidth
            args[1] += height - childHeight
            break
        }
    }
}