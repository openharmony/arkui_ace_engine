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

// TODO: the real chai exports 'assert', but 'assert' is still a keyword in ArkTS
import { Assert, suite, test } from "@koalaui/harness"
import { float64, int32 } from "@koalaui/common"
import { Easing, EasingCurve, EasingStepJump } from "../../src/animation/Easing"

function assertEasing(easing: EasingCurve, ...expected: int32[]) {
    const last = expected.length - 1
    for (let i = 0; i <= last; i++) {
        Assert.equal(Math.round(100 * easing((i as float64) / last)), expected[i], `i=${i}: expected=${expected[i]} - ${i / last} => ${easing(i / last)} => ${Math.round(100 * easing(i / last))}`)
    }
}

suite("Easing", () => {
    test("Linear", () => { assertEasing(Easing.Linear, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100) })
    test("Linear.inverted", () => { assertEasing(Easing.inverted(Easing.Linear), 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100) })
    test("Linear.reversed", () => { assertEasing(Easing.reversed(Easing.Linear), 100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0) })
    test("Linear.restarted", () => { assertEasing(Easing.restarted(Easing.Linear), 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 0) })
    test("Linear.repeated twice", () => { assertEasing(Easing.repeated(Easing.Linear, 2), 0, 20, 40, 60, 80, 0, 20, 40, 60, 80, 100) })
    test("Linear.repeated 4 times", () => { assertEasing(Easing.repeated(Easing.Linear, 4), 0, 40, 80, 20, 60, 0, 40, 80, 20, 60, 100) })
    test("Linear.joined with Linear.reversed", () => { assertEasing(Easing.joined(Easing.Linear, Easing.reversed(Easing.Linear)), 0, 20, 40, 60, 80, 100, 80, 60, 40, 20, 0) })
    test("Linear.thereAndBackAgain (as above)", () => { assertEasing(Easing.thereAndBackAgain(Easing.Linear), 0, 20, 40, 60, 80, 100, 80, 60, 40, 20, 0) })
    test("EaseInSine", () => { assertEasing(Easing.EaseInSine, 0, 1, 5, 11, 19, 29, 41, 55, 69, 84, 100) })
    test("EaseInSine.inverted", () => { assertEasing(Easing.inverted(Easing.EaseInSine), 0, 16, 31, 45, 59, 71, 81, 89, 95, 99, 100) })
    test("EaseInSine.reversed", () => { assertEasing(Easing.reversed(Easing.EaseInSine), 100, 84, 69, 55, 41, 29, 19, 11, 5, 1, 0) })
    test("EaseOutSine", () => { assertEasing(Easing.EaseOutSine, 0, 16, 31, 45, 59, 71, 81, 89, 95, 99, 100) })
    test("EaseOutSine.inverted", () => { assertEasing(Easing.inverted(Easing.EaseOutSine), 0, 1, 5, 11, 19, 29, 41, 55, 69, 84, 100) })
    test("EaseOutSine.reversed", () => { assertEasing(Easing.reversed(Easing.EaseOutSine), 100, 99, 95, 89, 81, 71, 59, 45, 31, 16, 0) })
    test("EaseInOutSine", () => { assertEasing(Easing.EaseInOutSine, 0, 2, 10, 21, 35, 50, 65, 79, 90, 98, 100) })
    test("EaseInOutSine.inverted", () => { assertEasing(Easing.inverted(Easing.EaseInOutSine), 0, 2, 10, 21, 35, 50, 65, 79, 90, 98, 100) })
    test("EaseInOutSine.reversed", () => { assertEasing(Easing.reversed(Easing.EaseInOutSine), 100, 98, 90, 79, 65, 50, 35, 21, 10, 2, 0) })
    test("Ease", () => { assertEasing(Easing.Ease, 0, 10, 30, 51, 68, 80, 89, 94, 98, 99, 100) })
    test("Ease.inverted", () => { assertEasing(Easing.inverted(Easing.Ease), 0, 1, 2, 6, 11, 20, 32, 49, 70, 90, 100) })
    test("Ease.reversed", () => { assertEasing(Easing.reversed(Easing.Ease), 100, 99, 98, 94, 89, 80, 68, 51, 30, 10, 0) })
    test("EaseIn", () => { assertEasing(Easing.EaseIn, 0, 2, 6, 13, 21, 32, 43, 55, 69, 84, 100) })
    test("EaseIn.inverted", () => { assertEasing(Easing.inverted(Easing.EaseIn), 0, 16, 31, 45, 57, 68, 79, 87, 94, 98, 100) })
    test("EaseIn.reversed", () => { assertEasing(Easing.reversed(Easing.EaseIn), 100, 84, 69, 55, 43, 32, 21, 13, 6, 2, 0) })
    test("EaseOut", () => { assertEasing(Easing.EaseOut, 0, 16, 31, 45, 57, 69, 79, 87, 94, 98, 100) })
    test("EaseOut.inverted", () => { assertEasing(Easing.inverted(Easing.EaseOut), 0, 2, 6, 13, 21, 31, 43, 55, 69, 84, 100) })
    test("EaseOut.reversed", () => { assertEasing(Easing.reversed(Easing.EaseOut), 100, 98, 94, 87, 79, 69, 57, 45, 31, 16, 0) })
    test("EaseInOut", () => { assertEasing(Easing.EaseInOut, 0, 2, 8, 19, 33, 50, 67, 81, 92, 98, 100) })
    test("EaseInOut.inverted", () => { assertEasing(Easing.inverted(Easing.EaseInOut), 0, 2, 8, 19, 33, 50, 67, 81, 92, 98, 100) })
    test("EaseInOut.reversed", () => { assertEasing(Easing.reversed(Easing.EaseInOut), 100, 98, 92, 81, 67, 50, 33, 19, 8, 2, 0) })
    test("custom bezier with small overflow", () => { assertEasing(Easing.cubicBezier(.3, -.3, .7, 1.3), 0, -4, 3, 15, 32, 50, 68, 85, 97, 104, 100) })
    test("custom bezier with large overflow", () => { assertEasing(Easing.cubicBezier(.3, -.7, .7, 1.7), 0, -13, -9, 6, 26, 50, 74, 95, 109, 113, 100) })
    test("6 steps with EasingStepJump.None", () => { assertEasing(Easing.steps(6, EasingStepJump.None), 0, 0, 20, 20, 40, 40, 60, 60, 80, 80, 100, 100) })
    test("11 steps with EasingStepJump.None", () => { assertEasing(Easing.steps(11, EasingStepJump.None), 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100) })
    test("10 steps with EasingStepJump.Start", () => { assertEasing(Easing.steps(10, EasingStepJump.Start), 10, 20, 30, 40, 50, 60, 70, 80, 90, 100) })
    test("10 steps with EasingStepJump.End", () => { assertEasing(Easing.steps(10, EasingStepJump.End), 0, 10, 20, 30, 40, 50, 60, 70, 80, 90) })
    test("9 steps with EasingStepJump.Both", () => { assertEasing(Easing.steps(9, EasingStepJump.Both), 10, 20, 30, 40, 50, 60, 70, 80, 90) })
})
export const __ARKTEST__ = "animation/Easing.test"
