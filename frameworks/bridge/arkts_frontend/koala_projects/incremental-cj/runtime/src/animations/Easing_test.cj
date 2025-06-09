/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
package KoalaRuntime.animations

import std.math.*

func assertEasing(easing: EasingCurve, expected: Array<Int64>): Unit {
    let last = expected.size - 1
    for (i in 0..last) {
        @Assert(expected[i], Int64(round(100.0 * easing(Float64(i) / Float64(last)))))
    }
}

@Test
public class EasingTest {
    @TestCase
    public func testLinear(): Unit {
        assertEasing(Easing.Linear, [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
    }
    @TestCase
    public func testLinearInverted(): Unit {
        assertEasing(Easing.inverted(Easing.Linear), [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
    }
    @TestCase
    public func testLinearReversed(): Unit {
        assertEasing(Easing.reversed(Easing.Linear), [100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0])
    }
    @TestCase
    public func testLinearRestarted(): Unit {
        assertEasing(Easing.restarted(Easing.Linear), [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 0])
    }
    @TestCase
    public func testLinearRepeatedTwice(): Unit {
        assertEasing(Easing.repeated(Easing.Linear, 2), [0, 20, 40, 60, 80, 0, 20, 40, 60, 80, 100])
    }
    @TestCase
    public func testLinearRepeated4times(): Unit {
        assertEasing(Easing.repeated(Easing.Linear, 4), [0, 40, 80, 20, 60, 0, 40, 80, 20, 60, 100])
    }
    @TestCase
    public func testLinearJoinedWithReversed(): Unit {
        assertEasing(Easing.joined(Easing.Linear, Easing.reversed(Easing.Linear)), [0, 20, 40, 60, 80, 100, 80, 60, 40, 20, 0])
    }
    @TestCase
    public func testLinearThereAndBackAgain(): Unit {
        assertEasing(Easing.thereAndBackAgain(Easing.Linear), [0, 20, 40, 60, 80, 100, 80, 60, 40, 20, 0])
    }
    @TestCase
    public func testEaseInSine(): Unit {
        assertEasing(Easing.EaseInSine, [0, 1, 5, 11, 19, 29, 41, 55, 69, 84, 100])
    }
    @TestCase
    public func testEaseInSineInverted(): Unit {
        assertEasing(Easing.inverted(Easing.EaseInSine), [0, 16, 31, 45, 59, 71, 81, 89, 95, 99, 100])
    }
    @TestCase
    public func testEaseInSineReversed(): Unit {
        assertEasing(Easing.reversed(Easing.EaseInSine), [100, 84, 69, 55, 41, 29, 19, 11, 5, 1, 0])
    }
    @TestCase
    public func testEaseOutSine(): Unit {
        assertEasing(Easing.EaseOutSine, [0, 16, 31, 45, 59, 71, 81, 89, 95, 99, 100])
    }
    @TestCase
    public func testEaseOutSineInverted(): Unit {
        assertEasing(Easing.inverted(Easing.EaseOutSine), [0, 1, 5, 11, 19, 29, 41, 55, 69, 84, 100])
    }
    @TestCase
    public func testEaseOutSineReversed(): Unit {
        assertEasing(Easing.reversed(Easing.EaseOutSine), [100, 99, 95, 89, 81, 71, 59, 45, 31, 16, 0])
    }
    @TestCase
    public func testEaseInOutSine(): Unit {
        assertEasing(Easing.EaseInOutSine, [0, 2, 10, 21, 35, 50, 65, 79, 90, 98, 100])
    }
    @TestCase
    public func testEaseInOutSineInverted(): Unit {
        assertEasing(Easing.inverted(Easing.EaseInOutSine), [0, 2, 10, 21, 35, 50, 65, 79, 90, 98, 100])
    }
    @TestCase
    public func testEaseInOutSineReversed(): Unit {
        assertEasing(Easing.reversed(Easing.EaseInOutSine), [100, 98, 90, 79, 65, 50, 35, 21, 10, 2, 0])
    }
    @TestCase
    public func testEase(): Unit {
        assertEasing(Easing.Ease, [0, 10, 30, 51, 68, 80, 89, 94, 98, 99, 100])
    }
    @TestCase
    public func testEaseInverted(): Unit {
        assertEasing(Easing.inverted(Easing.Ease), [0, 1, 2, 6, 11, 20, 32, 49, 70, 90, 100])
    }
    @TestCase
    public func testEaseReversed(): Unit {
        assertEasing(Easing.reversed(Easing.Ease), [100, 99, 98, 94, 89, 80, 68, 51, 30, 10, 0])
    }
    @TestCase
    public func testEaseIn(): Unit {
        assertEasing(Easing.EaseIn, [0, 2, 6, 13, 21, 32, 43, 55, 69, 84, 100])
    }
    @TestCase
    public func testEaseInInverted(): Unit {
        assertEasing(Easing.inverted(Easing.EaseIn), [0, 16, 31, 45, 57, 68, 79, 87, 94, 98, 100])
    }
    @TestCase
    public func testEaseInReversed(): Unit {
        assertEasing(Easing.reversed(Easing.EaseIn), [100, 84, 69, 55, 43, 32, 21, 13, 6, 2, 0])
    }
    @TestCase
    public func testEaseOut(): Unit {
        assertEasing(Easing.EaseOut, [0, 16, 31, 45, 57, 69, 79, 87, 94, 98, 100])
    }
    @TestCase
    public func testEaseOutInverted(): Unit {
        assertEasing(Easing.inverted(Easing.EaseOut), [0, 2, 6, 13, 21, 31, 43, 55, 69, 84, 100])
    }
    @TestCase
    public func testEaseOutReversed(): Unit {
        assertEasing(Easing.reversed(Easing.EaseOut), [100, 98, 94, 87, 79, 69, 57, 45, 31, 16, 0])
    }
    @TestCase
    public func testEaseInOut(): Unit {
        assertEasing(Easing.EaseInOut, [0, 2, 8, 19, 33, 50, 67, 81, 92, 98, 100])
    }
    @TestCase
    public func testEaseInOutInverted(): Unit {
        assertEasing(Easing.inverted(Easing.EaseInOut), [0, 2, 8, 19, 33, 50, 67, 81, 92, 98, 100])
    }
    @TestCase
    public func testEaseInOutReversed(): Unit {
        assertEasing(Easing.reversed(Easing.EaseInOut), [100, 98, 92, 81, 67, 50, 33, 19, 8, 2, 0])
    }
    @TestCase
    public func testCustomBezierWithSmallOverflow(): Unit {
        assertEasing(Easing.cubicBezier(.3, -.3, .7, 1.3), [0, -4, 3, 15, 32, 50, 68, 85, 97, 104, 100])
    }
    @TestCase
    public func testCustomBezierWithLargeOverflow(): Unit {
        assertEasing(Easing.cubicBezier(.3, -.7, .7, 1.7), [0, -13, -9, 6, 26, 50, 74, 95, 109, 113, 100])
    }
    @TestCase
    public func test6stepsWithEasingStepJumpNone(): Unit {
        assertEasing(Easing.steps(6, EasingStepJump.None), [0, 0, 20, 20, 40, 40, 60, 60, 80, 80, 100, 100])
    }
    @TestCase
    public func test11stepsWithEasingStepJumpNone(): Unit {
        assertEasing(Easing.steps(11, EasingStepJump.None), [0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
    }
    @TestCase
    public func test10stepsWithEasingStepJumpStart(): Unit {
        assertEasing(Easing.steps(10, EasingStepJump.Start), [10, 20, 30, 40, 50, 60, 70, 80, 90, 100])
    }
    @TestCase
    public func test10stepsWithEasingStepJumpEnd(): Unit {
        assertEasing(Easing.steps(10, EasingStepJump.End), [0, 10, 20, 30, 40, 50, 60, 70, 80, 90])
    }
    @TestCase
    public func test9stepsWithEasingStepJumpBoth(): Unit {
        assertEasing(Easing.steps(9, EasingStepJump.Both), [10, 20, 30, 40, 50, 60, 70, 80, 90])
    }
}
