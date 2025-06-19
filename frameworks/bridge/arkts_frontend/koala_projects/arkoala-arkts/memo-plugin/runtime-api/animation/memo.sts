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

import { memo } from "../annotations"
import { float64, int64, uint32 } from "../common"
import { AnimatedState, ImplicitAnimationProvider, MutableAnimatedState, ParametrizedAnimationProvider, StateAnimator, animatedState, mutableAnimatedState, stateAnimator } from "./AnimatedState"
import { AnimationRange } from "./AnimationRange"
import { Easing, EasingCurve } from "./Easing"
import { AnimationSpec, TimeAnimation } from "./TimeAnimation"
@memo export declare function sampledValue<V>(sampleRate: uint32, generator: (tick: int64) => V): V
@memo export declare function rememberAnimatedState<V>(animation: () => TimeAnimation<V>, startNow: boolean = false): AnimatedState<V>
@memo export declare function rememberNumberTransition(on: boolean, duration: uint32, easing: EasingCurve = Easing.Linear, to: float64 = 1.0, from: float64 = 0.0): AnimatedState<float64>
@memo export declare function rememberTransition<Value>(on: boolean, duration: uint32, easing: EasingCurve, compute: AnimationRange<Value>, initial: boolean = on): AnimatedState<Value>
@memo export declare function rememberMutableAnimatedState<Value>(initial: Value, animationProvider: ImplicitAnimationProvider<Value>): MutableAnimatedState<Value>
@memo export declare function rememberMutableAnimatedStateNumber(initial: float64, animationSpec: Partial<AnimationSpec>): MutableAnimatedState<float64>
@memo export declare function rememberAnimator<P, V>(parameter: P, animationProvider: ParametrizedAnimationProvider<P, V>): StateAnimator<P, V>