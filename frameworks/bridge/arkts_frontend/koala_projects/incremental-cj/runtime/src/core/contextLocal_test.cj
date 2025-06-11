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
public class ContextLocalTest {
    @TestCase
    public func checkNameNotChanged(): Unit {
        testPrepareOnStart()
        let state = mutableState("first")
        let root = testRoot {
            contextLocalScope(state.getValue(), "value") {
                collector.append(contextLocalValue(state.getValue()))
            }
        }
        testCollector("value")
        state.setValue("second")
        let exception = try {
            testTick(root)
            None<Exception>
        } catch (exception: Exception) {
            exception
        }
        @Assert(exception.isSome())
    }
    @TestCase
    public func checkStateImmediatelyPropagated(): Unit {
        testPrepareOnStart()
        let state = mutableState("first")
        let root = testRoot {
            collector.append("ui:" + state.getValue())
            contextLocalScope("parameter", state.getValue()) {
                collector.append("state:" + contextLocalValue("parameter"))
            }
        }
        testCollector("ui:first", "state:first")
        state.setValue("second")
        testTick(root)
        testCollector("ui:second", "state:second")
        state.setValue("third")
        testTick(root)
        testCollector("ui:third", "state:third")
    }
}
