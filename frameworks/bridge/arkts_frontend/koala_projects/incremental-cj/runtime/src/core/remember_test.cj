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
public class RememberTest {
    @TestCase
    public func checkComputesOnce(): Unit {
        testPrepareOnStart()
        let state = mutableState("first")
        let root = testRoot {
            remember {collector.append("inner")}
            collector.append("outer")
        }
        testCollector("inner", "outer")
        testTick(root)
        testCollector()
    }
    @TestCase
    public func checkComputesOnceEvenIfInnerStateChanged(): Unit {
        testPrepareOnStart()
        let state = mutableState(false)
        let root = testRoot {
            remember {
                state.getValue() // not depended
                collector.append("inner")
            }
            collector.append("outer")
        }
        testCollector("inner", "outer")
        testTick(root)
        testCollector()
        state.setValue(true)
        testTick(root)
        testCollector()
    }
    @TestCase
    public func checkComputesOnceEvenIfOuterStateChanged(): Unit {
        testPrepareOnStart()
        let state = mutableState(false)
        let root = testRoot {
            remember {collector.append("inner")}
            state.getValue() // depended
            collector.append("outer")
        }
        testCollector("inner", "outer")
        testTick(root)
        testCollector()
        state.setValue(true)
        testTick(root)
        testCollector("outer")
    }
    @TestCase
    public func checkNoConflicts(): Unit {
        testPrepareOnStart()
        let state = mutableState(false)
        let root = testRoot {
            if (state.getValue()) {
                remember {collector.append("positive")}
            } else {
                remember {collector.append("negative")}
            }
        }
        testCollector("negative")
        state.setValue(true)
        testTick(root)
        testCollector("positive")
        state.setValue(false)
        testTick(root)
        testCollector("negative")
        state.setValue(false)
        testTick(root)
        testCollector()
    }
    @TestCase
    public func checkThatDisposedAccordingly(): Unit {
        testPrepareOnStart()
        let state = mutableState(false)
        let root = testRoot {
            if (state.getValue()) {
                rememberDisposable(
                    {=> collector.append("create")},
                    {_ => collector.append("dispose")}
                )
            }
        }
        testCollector()
        state.setValue(true)
        testTick(root)
        testCollector("create")
        state.setValue(false)
        testTick(root)
        testCollector("dispose")
        state.setValue(false)
        testTick(root)
        testCollector()
    }
    @TestCase
    public func checkMutableStateComputesOnce(): Unit {
        testPrepareOnStart()
        let global = mutableState(0)
        let root = testRoot {
            let local = rememberMutableState(global.getValue())
            collector.append("global=${global.getValue()}")
            collector.append("local=${local.getValue()}")
        }
        testCollector("global=0", "local=0")
        global.setValue(global.getValue() + 1)
        testTick(root)
        testCollector("global=1", "local=0")
        global.setValue(global.getValue() + 1)
        testTick(root)
        testCollector("global=2", "local=0")
    }
}
