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

import { int64 } from "../common"
import { TimeAnimation } from "./TimeAnimation"
import { MutableState, State } from "../states/State"
export declare interface AnimatedState<Value> extends State<Value> {
    animation: TimeAnimation<Value>
    readonly running: boolean
    paused: boolean
}
export declare function animatedState<V>(animation: TimeAnimation<V>, startNow: boolean = false, timeProvider?: () => int64): AnimatedState<V>
export declare interface MutableAnimatedState<Value> extends MutableState<Value> {
    animation: TimeAnimation<Value>
    readonly running: boolean
}
export declare function mutableAnimatedState<Value>(initial: Value, animationProvider: ImplicitAnimationProvider<Value>): MutableAnimatedState<Value>
export type ImplicitAnimationProvider<Value> = (from: Value, to: Value) => TimeAnimation<Value>
export declare interface StateAnimator<Parameter, Value> {
    parameter: Parameter
    readonly value: Value
    onValueChange(action: (newValue: Value) => void): void
}
export declare function stateAnimator<P, V>(parameter: P, animationProvider: ParametrizedAnimationProvider<P, V>): StateAnimator<P, V>
export type ParametrizedAnimationProvider<P, V> = (parameter: P, value: V | undefined) => TimeAnimation<V>
