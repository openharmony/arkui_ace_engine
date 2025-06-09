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

import { float64, uint32 } from "../common"
export type EasingCurve = (value: float64) => float64
export declare class Easing {
    static readonly Linear: EasingCurve
    static readonly LinearReversed: EasingCurve
    static readonly EaseInSine: EasingCurve
    static readonly EaseOutSine: EasingCurve
    static readonly EaseInOutSine: EasingCurve
    static readonly Ease: EasingCurve
    static readonly EaseIn: EasingCurve
    static readonly EaseOut: EasingCurve
    static readonly EaseInOut: EasingCurve
    static readonly ViscousFluid: EasingCurve
    static readonly Bubble: EasingCurve
    static inverted(easing: EasingCurve): EasingCurve
    static reversed(easing: EasingCurve): EasingCurve
    static restarted(easing: EasingCurve): EasingCurve
    static repeated(easing: EasingCurve, count: uint32): EasingCurve
    static joined(...easing: EasingCurve[]): EasingCurve
    static thereAndBackAgain(easing: EasingCurve): EasingCurve
    static cubicBezier(p1x: float64, p1y: float64, p2x: float64, p2y: float64): EasingCurve
    static steps(stops: uint32, jump: EasingStepJump = EasingStepJump.None): EasingCurve
    static viscousFluid(v0: float64 = 1, f: float64 = 3): EasingCurve
}
export enum EasingStepJump {
    Start,
    End,
    None,
    Both,
}
