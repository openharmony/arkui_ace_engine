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
package KoalaRuntime.core

@Test
public class ChangeListenerTest {
    @TestCase
    public func checkRunEffect(): Unit {
        check({value => RunEffect(value, collector.append)}, "first")
    }
    @TestCase
    public func checkOnChange(): Unit {
        check({value => OnChange(value, collector.append)})
    }

    private func check(content: (value: String) -> Unit, expected: Array<String>) {
        testPrepareOnStart()
        let state = mutableState("first")
        let root = testRoot {
            content(state.getValue())
        }
        testCollectorAfterCallbacks(expected)
        state.setValue("f" + "i" + "r" + "s" + "t")
        testTick(root)
        testCollectorAfterCallbacks()
        state.setValue("second")
        testTick(root)
        testCollectorAfterCallbacks("second")
        state.setValue("third")
        testTick(root)
        testCollectorAfterCallbacks("third")
    }
}
