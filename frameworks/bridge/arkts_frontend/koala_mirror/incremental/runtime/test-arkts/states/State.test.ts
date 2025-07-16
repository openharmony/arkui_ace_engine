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
import { float64, int32, hashCodeFromString as key } from "@koalaui/common"
import { IncrementalNode, State, StateContext, TestNode, testUpdate, ValueTracker } from "../../src"
import { createStateManager } from "../../src/states/State"

function assertNode(state: State<TestNode>, presentation: string) {
    Assert.isFalse(state.modified) // the same node
    Assert.equal(state.value.toHierarchy(), presentation)
}

function assertState<Value>(state: State<Value>, value: Value, modified: boolean = false) {
    Assert.equal(state.modified, modified)
    Assert.equal(state.value, value)
    Assert.equal(state.modified, modified)
}

function assertModifiedState<Value>(state: State<Value>, value: Value) {
    assertState(state, value, true)
}

function assertStringsAndCleanup(array: Array<string>, presentation: string) {
    Assert.isNotEmpty(array)
    Assert.equal(array.join(" ; "), presentation)
    array.splice(0, array.length)
}

suite("State", () => {
    test("initial state is not modified", () => {
        let manager = createStateManager()
        let state = manager.mutableState(200)
        assertState(state, 200)
    })
    test("unmanaged state is modified immediately", () => {
        let manager = createStateManager()
        manager.frozen = true
        let state = manager.mutableState(200)
        state.dispose()
        state.value = 404
        assertModifiedState(state, 404)
        // check that modified state is updated
        state.value = 404
        assertState(state, 404)
    })
    test("managed state is not modified immediately", () => {
        let manager = createStateManager()
        manager.frozen = true
        let state = manager.mutableState(200)
        state.value = 404
        assertState(state, 200)
    })
    test("managed state is modified on first snapshot update", () => {
        let manager = createStateManager()
        let state = manager.mutableState(200)
        state.value = 404
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, 404)
    })
    test("managed state is not modified on next snapshot update", () => {
        let manager = createStateManager()
        let state = manager.mutableState(200)
        state.value = 404
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, 404)
    })
    test("managed state is not modified if the same value is set", () => {
        let manager = createStateManager()
        let state = manager.mutableState(200)
        for (let index = 0; index <= 200; index++) {
            state.value = index
        }
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, 200)
    })
    test("unmanaged named state does not exist anymore", () => {
        let manager = createStateManager()
        const state = manager.namedState("named", (): float64 => 200)
        Assert.equal(state, manager.stateBy<float64>("named")!)
        Assert.isDefined(manager.stateBy<float64>("named"))
        state.dispose()
        Assert.isUndefined(manager.stateBy<float64>("named"))
        state.dispose()
        Assert.isUndefined(manager.stateBy<float64>("named"))
    })
    test("managed named state is not modified immediately", () => {
        let manager = createStateManager()
        manager.frozen = true
        manager.namedState("named", (): float64 => 200)
        manager.stateBy<float64>("named")!.value = 404
        Assert.equal(manager.valueBy<float64>("named"), 200)
        Assert.isFalse(manager.stateBy<float64>("named")?.modified)
    })
    test("managed named state is modified on first snapshot update", () => {
        let manager = createStateManager()
        manager.namedState("named", (): float64 => 200)
        manager.stateBy<float64>("named")!.value = 404
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(manager.valueBy<float64>("named"), 404)
        Assert.isTrue(manager.stateBy<float64>("named")?.modified)
    })
    test("managed named state is not modified on next snapshot update", () => {
        let manager = createStateManager()
        manager.namedState("named", (): float64 => 200)
        manager.stateBy<float64>("named")!.value = 404
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(manager.valueBy<float64>("named"), 404)
        Assert.isFalse(manager.stateBy<float64>("named")?.modified)
    })
    test("managed named state is not modified if the same value is set", () => {
        let manager = createStateManager()
        manager.namedState("named", (): float64 => 200)
        for (let index = 0; index <= 200; index++) {
            manager.stateBy<float64>("named")!.value = index
        }
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(manager.valueBy<float64>("named"), 200)
        Assert.isFalse(manager.stateBy<float64>("named")?.modified)
    })
    test("do not allow to dispose parameter state", () => {
        const name = "parameter"
        const manager = createStateManager()
        manager.computableState((context: StateContext) => {
            const scope = context.scope<void>(0, 1)
            const param = scope.paramEx<int32>(0, 200, undefined, name, true) // can be found by name
            if (scope.unchanged) { scope.cached } else {
                const state = manager.stateBy<int32>(name)!
                Assert.isDefined(state)
                Assert.equal<State<int32>>(state, param)
                Assert.throws(() => { state.dispose() })
                scope.recache()
            }
            return undefined
        }).value
    })
    test("managed parameter state is modified immediately", () => {
        const name = "parameter"
        const manager = createStateManager()
        manager.computableState((context: StateContext) => {
            const scope = context.scope<void>(0, 1)
            const param = scope.paramEx<int32>(0, 200, undefined, name, true) // can be found by name
            if (scope.unchanged) { scope.cached } else {
                const state = manager.stateBy<int32>(name)!
                Assert.isDefined(state)
                Assert.equal<State<int32>>(state, param)
                state.value = 404
                assertModifiedState(state, 404)
                // check that modified state is updated
                state.value = 404
                assertState(state, 404)
                scope.recache()
            }
            return undefined
        }).value
    })
    test("updatable node should be recomputable state", () => {
        const manager = createStateManager()
        const mutableState = manager.mutableState(true)
        const updatableNode = manager.updatableNode(new IncrementalNode(), (_: StateContext) => { mutableState.value })
        // updatable node needs to be recomputed after creation
        Assert.isTrue(updatableNode.recomputeNeeded)
        updatableNode.value
        // updatable node is already computed after accessing
        Assert.isFalse(updatableNode.recomputeNeeded)
        Assert.equal(testUpdate(false, manager), 0)
        // updatable node is already computed because nothing is changed
        Assert.isFalse(updatableNode.recomputeNeeded)
        mutableState.value = !mutableState.value
        // updatable node does not know that the mutable state is changed
        Assert.isFalse(updatableNode.recomputeNeeded)
        Assert.equal(testUpdate(false, manager), 1)
        // updatable node needs to be recomputed because the mutable state is changed
        Assert.isTrue(updatableNode.recomputeNeeded)
    })
    test("updatable node should not use StateManager.updateSnapshot()", () => {
        const manager = createStateManager()
        const state = manager.updatableNode(new IncrementalNode(), (_: StateContext) => {
            manager.updateSnapshot()
        })
        Assert.throws(() => { state.value })
    })
    test("updatable node should not use StateManager.updatableNode(...)", () => {
        const manager = createStateManager()
        const state = manager.updatableNode(new IncrementalNode(), (_: StateContext) => {
            manager.updatableNode(new IncrementalNode(), (_: StateContext) => { })
        })
        Assert.throws(() => { state.value })
    })
    test("updatable node should not use StateManager.computableState(...)", () => {
        const manager = createStateManager()
        const state = manager.updatableNode(new IncrementalNode(), (_: StateContext) => { manager.updateSnapshot() })
        Assert.throws(() => { state.value })
    })
    test("computable state should be recomputable state", () => {
        const manager = createStateManager()
        const mutableState = manager.mutableState(true)
        const computableState = manager.computableState((_: StateContext) => mutableState.value)
        // computable state needs to be recomputed after creation
        Assert.isTrue(computableState.recomputeNeeded)
        computableState.value
        // computable state is already computed after accessing
        Assert.isFalse(computableState.recomputeNeeded)
        Assert.equal(testUpdate(false, manager), 0)
        // computable state is already computed because nothing is changed
        Assert.isFalse(computableState.recomputeNeeded)
        mutableState.value = !mutableState.value
        // computable state does not know that the mutable state is changed
        Assert.isFalse(computableState.recomputeNeeded)
        Assert.equal(testUpdate(false, manager), 1)
        // computable state needs to be recomputed because the mutable state is changed
        Assert.isTrue(computableState.recomputeNeeded)
    })
    test("computable state should not use StateManager.updateSnapshot()", () => {
        const manager = createStateManager()
        const state = manager.computableState((_: StateContext) => {
            manager.updateSnapshot()
            return undefined
        })
        Assert.throws(() => { state.value })
    })
    test("computable state should not use StateManager.updatableNode(...)", () => {
        const manager = createStateManager()
        const state = manager.computableState((_: StateContext) => manager.updatableNode(new IncrementalNode(), (_: StateContext) => { }))
        Assert.throws(() => { state.value })
    })
    test("computable state depends on managed state", () => {
        let manager = createStateManager()
        let name = manager.mutableState<string>("NAME")
        // create computable state that tracks computing inner scopes
        let computing = new Array<string>()
        let result = manager.computableState((context: StateContext) => {
            computing.push("main")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("name"), () => {
                computing.push("name")
                return name.value
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= NAME =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        assertState<string>(result, "<= NAME =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        name.value = "Sergey Malenkov"
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState<string>(result, "<= Sergey Malenkov =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state depends on named state managed globally", () => {
        let manager = createStateManager()
        // create named scope managed globally and schedule its updating
        manager.namedState("global", () => "NAME")
        // create computable state that tracks computing inner scopes
        let computing = new Array<string>()
        let result = manager.computableState((context: StateContext) => {
            computing.push("main")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("name"), () => {
                computing.push("name")
                return context.valueBy<string>("global")
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= NAME =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        assertState<string>(result, "<= NAME =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        manager.stateBy<string>("global")!.value = "Sergey Malenkov"
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState<string>(result, "<= Sergey Malenkov =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state depends on named state managed locally", () => {
        let manager = createStateManager()
        // create computable state that tracks computing inner scopes
        let computing = new Array<string>()
        let result = manager.computableState((context: StateContext) => {
            computing.push("main")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("name"), () => {
                computing.push("name")
                const state = context.namedState("local", (): float64 => 1)
                manager.scheduleCallback(() => { state.value++ })
                return state.value
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= 1 =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        assertState<string>(result, "<= 1 =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(testUpdate(true, manager), 1)
        assertModifiedState<string>(result, "<= 2 =>")
        assertStringsAndCleanup(computing, "main ; name")
        // compute state on next snapshot update
        Assert.equal(testUpdate(true, manager), 1)
        assertModifiedState<string>(result, "<= 3 =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state depends on named state managed locally from managed inner scope", () => {
        let manager = createStateManager()
        let computing = new Array<string>()
        let result = manager.computableState((context: StateContext) => {
            context.namedState("local", (): float64 => 1)
            computing.push("main")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("name"), () => {
                computing.push("name")
                const state = context.stateBy<float64>("local")!
                manager.scheduleCallback(() => { state.value++ })
                return context.valueBy<float64>("local")
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= 1 =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        assertState<string>(result, "<= 1 =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(testUpdate(true, manager), 1)
        assertModifiedState<string>(result, "<= 2 =>")
        assertStringsAndCleanup(computing, "main ; name")
        // compute state on next snapshot update
        Assert.equal(testUpdate(true, manager), 1)
        assertModifiedState<string>(result, "<= 3 =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state allows to cleanup disposed scopes", () => {
        let manager = createStateManager()
        let computing = new Array<string>()
        let result = manager.computableState((context: StateContext) => {
            let name = context.compute(key("value"), () => {
                computing.push("compute:value")
                return "value"
            })
            let condition = context.compute(key("condition"), () => {
                computing.push("compute:condition")
                return context.valueBy<boolean>("condition")
            })
            let value = condition
                ? context.compute(key("true"), () => {
                    computing.push("compute:true")
                    return context.compute(key("true"), () => {
                        context.namedState("true", () => true)
                        computing.push("compute:inner:true")
                        return "true"
                    }, (old: string | undefined) => {
                        Assert.isUndefined(context.stateBy<boolean>("false"))
                        Assert.isDefined(context.stateBy<boolean>("true"))
                        Assert.isTrue(context.valueBy<boolean>("true"))
                        Assert.equal(old, "true")
                        computing.push("cleanup:inner:true")
                    })
                }, (_: string | undefined) => { computing.push("cleanup:true") })
                : context.compute(key("false"), () => {
                    computing.push("compute:false")
                    return context.compute(key("false"), () => {
                        context.namedState("false", () => false)
                        computing.push("compute:inner:false")
                        return "false"
                    }, (old: string | undefined) => {
                        Assert.isUndefined(context.stateBy<boolean>("true"))
                        Assert.isDefined(context.stateBy<boolean>("false"))
                        Assert.isFalse(context.valueBy<boolean>("false"))
                        Assert.equal(old, "false")
                        computing.push("cleanup:inner:false")
                    })
                }, (_: string | undefined) => { computing.push("cleanup:false") })
            return name + " is " + value
        })
        let condition = manager.namedState("condition", () => true)
        // initial computation
        Assert.equal(result.value, "value is true")
        assertStringsAndCleanup(computing, "compute:value ; compute:condition ; compute:true ; compute:inner:true")
        // condition changed from true to false
        condition.value = false
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "value is false")
        assertStringsAndCleanup(computing, "compute:condition ; compute:false ; compute:inner:false ; cleanup:true ; cleanup:inner:true")
        // condition changed from false to true
        condition.value = true
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "value is true")
        assertStringsAndCleanup(computing, "compute:condition ; compute:true ; compute:inner:true ; cleanup:false ; cleanup:inner:false")
    })
    test("global named state must be created only once", () => {
        let manager = createStateManager()
        let created = manager.namedState("named", (): int32 => 200)
        let existed = manager.namedState("named", (): int32 => {
            Assert.fail()
            return 200
        })
        Assert.equal(created, existed)
        Assert.equal(created, manager.stateBy<int32>("named")!)
        Assert.equal(existed, manager.stateBy<int32>("named")!)
    })
    test("local named state must be created only once", () => {
        createStateManager().computableState((context: StateContext) => {
            let created = context.namedState("named", (): int32 => 200)
            let existed = context.namedState("named", (): int32 => {
                Assert.fail()
                return 200
            })
            Assert.equal(created, existed)
            Assert.equal(created, context.stateBy<int32>("named")!)
            Assert.equal(existed, context.stateBy<int32>("named")!)
            return undefined
        }).value
    })
    test("global named state must not be created when creating another one", () => {
        let manager = createStateManager()
        manager.namedState("named", () => {
            Assert.throws(() => {
                manager.namedState("unnamed", () => 200)
            })
            return 200
        })
    })
    test("local named state must not be created when creating another one", () => {
        createStateManager().computableState((context: StateContext) => {
            context.namedState("named", (): float64 => {
                Assert.throws(() => {
                    context.namedState("unnamed", (): float64 => 200)
                })
                return 200
            })
            return undefined
        }).value
    })
    test("do not allow to dispose global mutable state when creating global named state", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState<string>("value")
        manager.namedState("prohibited", () => {
            Assert.throws(() => { mutable.dispose() })
            return mutable.value
        })
    })
    test("do not allow to dispose global mutable state when creating local named state", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState<string>("value")
        const state = manager.computableState((context: StateContext) => {
            context.namedState("prohibited", () => {
                Assert.throws(() => { mutable.dispose() })
                return mutable.value
            })
            return undefined
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose global named state when creating global named state", () => {
        const manager = createStateManager()
        const named = manager.namedState("state", () => "value")
        manager.namedState("prohibited", () => {
            Assert.equal(named, manager.stateBy<string>("state")!)
            Assert.throws(() => { named.dispose() })
            return named.value
        })
    })
    test("do not allow to dispose local named state when creating local named state", () => {
        const manager = createStateManager()
        const state = manager.computableState((context: StateContext) => {
            const named = context.namedState("state", () => "")
            context.namedState("prohibited", () => {
                Assert.equal(named, manager.stateBy<string>("state")!)
                Assert.throws(() => { named.dispose() })
                return named.value
            })
            return undefined
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose global mutable state when updating computable state", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState<string>("value")
        const state = manager.computableState((_: StateContext) => {
            Assert.throws(() => { mutable.dispose() })
            return undefined
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose global named state when updating computable state", () => {
        const manager = createStateManager()
        const named = manager.namedState("state", () => "")
        const state = manager.computableState((_: StateContext) => {
            Assert.throws(() => { named.dispose() })
            return undefined
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose local named state when updating computable state", () => {
        const manager = createStateManager()
        const state = manager.computableState((context: StateContext) => {
            const named = context.namedState("state", () => "")
            Assert.throws(() => { named.dispose() })
            return undefined
        })
        state.value
        state.dispose()
    })
    test("do not allow to update snapshot when updating computable state", () => {
        const manager = createStateManager()
        const state = manager.computableState((context: StateContext) => {
            Assert.equal(context, manager)
            Assert.throws(() => { manager.updateSnapshot() })
            return undefined
        })
        state.value
        state.dispose()
    })
    test("do not allow to create updatable node when updating computable state", () => {
        const manager = createStateManager()
        const state = manager.computableState((context: StateContext) => {
            Assert.equal(context, manager)
            Assert.throws(() => { manager.updatableNode(new TestNode(), (_: StateContext) => { }) })
            return undefined
        })
        state.value
        state.dispose()
    })
    test("computable state must not compute something when creating local named state", () => {
        createStateManager().computableState((context: StateContext) => {
            context.namedState("name", () => {
                Assert.throws(() => {
                    context.compute(key("compute"), () => 200)
                })
                return "NAME"
            })
            return context.valueBy<string>("name")
        }).value
    })
    test("computable state must not depend on managed state when creating another one", () => {
        let manager = createStateManager()
        let mutable = manager.mutableState<string>("NAME")
        let computable = manager.computableState((context: StateContext) => {
            context.namedState("name", () => mutable.value)
            return context.valueBy<string>("name")
        })
        // initial computation
        assertState<string>(computable, "NAME")
        // do not update result when snapshot updated
        mutable.value = "Sergey Malenkov"
        Assert.equal(testUpdate(false, manager), 1)
        assertState<string>(computable, "NAME")
    })
    test("computable state from specific scope must be forgotten on dispose automatically", () => {
        const manager = createStateManager()
        const state = manager.mutableState(-1)
        const selector = manager.mutableState(true)
        const computable = manager.computableState((context: StateContext) => selector.value
            ? context.compute(key("first"), () => context.computableState((_: StateContext): int32 => state.value), undefined, true)
            : context.compute(key("second"), () => context.computableState((_: StateContext): int32 => state.value), undefined, true))
        // initial computation
        const initial = computable.value
        assertState(initial, -1)
        // ensure that initial state is managed
        state.value = -10
        assertState(initial, -1)
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, -10)
        assertModifiedState(initial, -10)
        // dispose first inner scope
        Assert.strictEqual(computable.value, initial)
        selector.value = false
        Assert.equal(testUpdate(false, manager), 1)
        Assert.notStrictEqual(computable.value, initial)
        // ensure that initial state is not managed
        assertState(initial, -10)
        state.value = -100
        Assert.equal(testUpdate(false, manager), 1)
        assertState(initial, -10)
    })
    test("named state from specific scope must be forgotten on dispose automatically", () => {
        const manager = createStateManager()
        manager.frozen = true
        const selector = manager.mutableState(true)
        const computable = manager.computableState((context: StateContext) => selector.value
            ? context.compute(key("first"), () => context.namedState("name", (): int32 => -1))
            : context.compute(key("second"), () => context.namedState("name", (): int32 => 1)))
        // initial computation
        const initial = computable.value
        assertState(initial, -1)
        // ensure that initial state is managed
        initial.value = -10
        assertState(initial, -1)
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(initial, -10)
        // dispose first inner scope
        Assert.strictEqual(computable.value, initial)
        selector.value = false
        Assert.equal(testUpdate(false, manager), 1)
        Assert.notStrictEqual(computable.value, initial)
        // ensure that initial state is not managed
        assertState(initial, -10)
        initial.value = -100
        assertModifiedState(initial, -100)
    })
    test("mutable state from specific scope must be forgotten on dispose too", () => {
        const manager = createStateManager()
        manager.frozen = true
        const selector = manager.mutableState(true)
        const computable = manager.computableState((context: StateContext) => selector.value
            ? context.compute(key("first"), () => context.mutableState(-1), undefined, true)
            : context.compute(key("second"), () => context.mutableState(1), undefined, true))
        // initial computation
        const initial = computable.value
        assertState(initial, -1)
        // ensure that initial state is managed
        initial.value = -10
        assertState(initial, -1)
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(initial, -10)
        // dispose first inner scope
        Assert.strictEqual(computable.value, initial)
        selector.value = false
        Assert.equal(testUpdate(false, manager), 1)
        Assert.notStrictEqual(computable.value, initial)
        // ensure that initial state is not managed
        assertState(initial, -10)
        initial.value = -100
        assertModifiedState(initial, -100)
    })
    test("mutable state must not be changed during recomposition", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0 as float64)
        const increment = () => {
            Assert.throws(() => { state.value++ })
            return state.value
        }
        const computable = manager.computableState((context: StateContext): float64 =>
            context.compute(key("a"), increment) +
            context.compute(key("b"), increment) +
            context.compute(key("c"), increment))
        Assert.equal(computable.value, 0)
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(computable.value, 0)
        state.value++
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(computable.value, 3)
    })
    test("allow to compute once within a leaf scope", () => {
        const computable = createStateManager().computableState((context: StateContext) =>
            context.compute(key("leaf"), () =>
                context.compute(key("allowed"), (): float64 => 0, undefined, true),
                undefined, true))
        Assert.equal(computable.value, 0)
    })
    test("create global mutable state in local context", () => {
        const manager = createStateManager()
        const computable = manager.computableState((context: StateContext) => context.mutableState(0 as float64, true))
        const globalState = computable.value
        Assert.equal<string>("GlobalState=0", globalState.toString())
        globalState.value = 1
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal<string>("GlobalState,modified=1", globalState.toString())
        Assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        Assert.equal<string>("GlobalState=1", globalState.toString())
        globalState.dispose()
        Assert.equal<string>("GlobalState,disposed=1", globalState.toString())
    })
    test("create local mutable state in local context within remember", () => {
        const manager = createStateManager()
        const computable = manager.computableState((context: StateContext) => context.compute(0, () => context.mutableState(0 as float64, false), undefined, true))
        const localState = computable.value
        Assert.equal<string>("LocalState=0", localState.toString())
        localState.value = 1
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal<string>("LocalState,modified=1", localState.toString())
        Assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        Assert.equal<string>("LocalState,disposed=1", localState.toString())
        localState.dispose()
        Assert.equal<string>("LocalState,disposed=1", localState.toString())
    })
    test("create global named state in local context", () => {
        const manager = createStateManager()
        const computable = manager.computableState((context: StateContext) => {
            const state = context.namedState("global", (): int32 => 0, true)
            Assert.equal(state, manager.stateBy<int32>("global")!)
            Assert.isDefined(manager.stateBy<int32>("global", true))
            Assert.isUndefined(manager.stateBy<int32>("global", false))
            return state
        })
        const globalState = computable.value
        Assert.equal(globalState, manager.stateBy<int32>("global")!)
        Assert.equal<string>("GlobalState(global)=0", globalState.toString())
        globalState.value = 1
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal<string>("GlobalState(global),modified=1", globalState.toString())
        Assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        Assert.equal<string>("GlobalState(global)=1", globalState.toString())
        globalState.dispose()
        Assert.equal<string>("GlobalState(global),disposed=1", globalState.toString())
    })
    test("create local named state in local context", () => {
        const manager = createStateManager()
        const globalState = manager.namedState("global", (): float64 => Number.MAX_SAFE_INTEGER + 1)
        const computable = manager.computableState((context: StateContext) => {
            Assert.equal(globalState, manager.stateBy<float64>("global")!)
            Assert.isDefined(manager.stateBy<float64>("global", true))
            Assert.isUndefined(manager.stateBy<float64>("global", false))
            const state = context.namedState("local", (): float64 => 0, false)
            Assert.equal(state, manager.stateBy<float64>("local")!)
            Assert.isUndefined(manager.stateBy<float64>("local", true))
            Assert.isDefined(manager.stateBy<float64>("local", false))
            return state
        })
        const localState = computable.value
        Assert.isUndefined(manager.stateBy<float64>("local"))
        Assert.equal<string>("LocalState(local)=0", localState.toString())
        localState.value = 1
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal<string>("LocalState(local),modified=1", localState.toString())
        Assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        Assert.equal<string>("LocalState(local),disposed=1", localState.toString())
        localState.dispose()
        Assert.equal<string>("LocalState(local),disposed=1", localState.toString())
    })
    test("prohibit to create local mutable state in global context", () => {
        Assert.throws(() => { createStateManager().mutableState(0, false) })
    })
    test("prohibit to create local named state in global context", () => {
        Assert.throws(() => { createStateManager().namedState("name", (): int32 => 0, false) })
    })
    test("prohibit to create local mutable state in local context", () => {
        const computable = createStateManager().computableState((context: StateContext) => context.mutableState(0, false))
        Assert.throws(() => { computable.value })
    })
    test("prohibit to compute within a leaf scope", () => {
        const computable = createStateManager().computableState((context: StateContext) =>
            context.compute(key("leaf"), () =>
                context.compute(key("prohibit"), (): float64 => 0),
                undefined, true))
        Assert.throws(() => { computable.value })
    })
    test("prohibit to build tree within a leaf scope", () => {
        const computable = createStateManager().updatableNode(new TestNode(), (context: StateContext) => {
            context.compute(key("leaf"), () => {
                context.attach(key("prohibit"), () => new TestNode(), () => { })
                return undefined
            }, undefined, true)
        })
        Assert.throws(() => { computable.value })
    })
    test("prohibit to build tree within a computable state", () => {
        const computable = createStateManager().computableState((context: StateContext) => {
            context.attach(key("prohibit"), () => new TestNode(), () => { })
            return undefined
        })
        Assert.throws(() => { computable.value })
    })
    test("leaf scope must not depend on managed state", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        const computing = new Array<string>()
        const computable = manager.computableState((context: StateContext) => {
            computing.push("computable")
            return context.compute(key("name"), () => {
                computing.push("name")
                return state.value
            }, undefined, true)
        })
        // initial computation
        assertState(computable, 0)
        assertStringsAndCleanup(computing, "computable ; name")
        // compute state only when snapshot updated
        state.value = -1
        Assert.equal(testUpdate(false, manager), 1)
        assertState(computable, 0)
        Assert.isEmpty(computing)
    })
    test("0. amount of modified states including computable states that have dependants", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState(false)
        let computableCounter = 0
        const computable = manager.computableState((_: StateContext) => {
            computableCounter++
            return mutable.value
        })
        let stateCounter = 0
        const state = manager.computableState((_: StateContext) => {
            stateCounter++
            return computable.value
        })
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(computableCounter, 0) // computable is not recomputed
        Assert.equal(stateCounter, 0) // state is not recomputed
        assertState(state, false)
        Assert.equal(computableCounter, 1) // computable is recomputed
        Assert.equal(stateCounter, 1) // state is recomputed
        mutable.value = true
        Assert.equal(testUpdate(false, manager), 2)
        Assert.equal(computableCounter, 2) // computable is recomputed automatically
        Assert.equal(stateCounter, 1) // state is not recomputed
        assertModifiedState(state, true)
        Assert.equal(computableCounter, 2) // computable is not recomputed
        Assert.equal(stateCounter, 2) // state is recomputed by request
    })
    test("1. amount of modified states including computable states that have dependants", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState(false)
        let computableCounter = 0
        const computable = manager.computableState((_: StateContext) => {
            computableCounter++
            const value = mutable.value
            return value && false
        })
        let stateCounter = 0
        const state = manager.computableState((_: StateContext) => {
            stateCounter++
            return computable.value
        })
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(computableCounter, 0) // computable is not recomputed
        Assert.equal(stateCounter, 0) // state is not recomputed
        assertState(state, false)
        Assert.equal(computableCounter, 1) // computable is recomputed
        Assert.equal(stateCounter, 1) // state is recomputed
        mutable.value = true
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(computableCounter, 2) // computable is recomputed automatically
        Assert.equal(stateCounter, 1) // state is not recomputed
        assertState(state, false)
        Assert.equal(computableCounter, 2) // computable is not recomputed
        Assert.equal(stateCounter, 1) // state is not recomputed because computable is not modified
    })
    test("2. amount of modified states including computable states that have dependants", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState(false)
        let computableCounter = 0
        const computable = manager.computableState((_: StateContext) => {
            computableCounter++
            return mutable.value
        })
        let stateCounter = 0
        const state = manager.computableState((_: StateContext) => {
            stateCounter++
            const value = computable.value
            return value && false
        })
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(computableCounter, 0) // computable is not recomputed
        Assert.equal(stateCounter, 0) // state is not recomputed
        assertState(state, false)
        Assert.equal(computableCounter, 1) // computable is recomputed
        Assert.equal(stateCounter, 1) // state is recomputed
        mutable.value = true
        Assert.equal(testUpdate(false, manager), 2)
        Assert.equal(computableCounter, 2) // computable is recomputed automatically
        Assert.equal(stateCounter, 1) // state is not recomputed
        assertState(state, false)
        Assert.equal(computableCounter, 2) // computable is not recomputed
        Assert.equal(stateCounter, 2) // state is recomputed by request but it is not modified
    })
    test("do not recompute by state if it was not used during last computation", () => {
        const manager = createStateManager()
        const stateB = manager.mutableState(true)
        const stateT = manager.mutableState(1)
        const stateF = manager.mutableState(2)
        const computing = new Array<string>()
        const computable = manager.computableState(() => {
            computing.push("recomputed")
            return stateB.value ? stateT.value : stateF.value
        })
        // initial computation
        Assert.equal(computable.value, 1)
        assertStringsAndCleanup(computing, "recomputed")
        // do not recompute if nothing changed
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(computable.value, 1)
        Assert.isEmpty(computing)
        // recompute if used stateT changed
        stateT.value = -1
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(computable.value, -1)
        assertStringsAndCleanup(computing, "recomputed")
        // do not recompute if stateF changed
        stateF.value = -2
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(computable.value, -1)
        Assert.isEmpty(computing)
        // switch flag and recompute
        stateB.value = false
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(computable.value, -2)
        assertStringsAndCleanup(computing, "recomputed")
        // recompute if used stateF changed
        stateF.value = 2
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(computable.value, 2)
        assertStringsAndCleanup(computing, "recomputed")
        // do not recompute if stateT changed
        stateT.value = 1
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(computable.value, 2)
        Assert.isEmpty(computing)
    })
    test("build and update simple tree", () => {
        let manager = createStateManager()
        let count = manager.mutableState(30)
        let first = manager.mutableState<string>("first node")
        let second = manager.mutableState<string>("second node")
        let computing = new Array<string>()
        const rootNode = new TestNode()
        let firstNode: TestNode
        let secondNode: TestNode
        let root = manager.updatableNode(rootNode, (context: StateContext) => {
            computing.push("update root")
            Assert.equal(context.node, rootNode)
            context.compute(key("init"), () => {
                computing.push("init root")
                Assert.equal(context.node, rootNode)
                rootNode.content = "root"
                return undefined
            })
            if (count.value < 40) {
                context.attach(key("first"), () => {
                    computing.push("create first")
                    Assert.equal(context.node, undefined)
                    return firstNode = new TestNode()
                }, () => {
                    computing.push("update first")
                    Assert.equal(context.node, firstNode)
                    context.compute(key("init"), () => {
                        computing.push("init first")
                        Assert.equal(context.node, firstNode)
                        firstNode.content = first.value
                        return undefined
                    })
                }, () => {
                    computing.push("detach&dispose first")
                    Assert.equal(context.node, firstNode)
                })
            }
            if (count.value > 20) {
                context.attach(key("second"), () => {
                    computing.push("create second")
                    Assert.equal(context.node, undefined)
                    return secondNode = new TestNode()
                }, () => {
                    computing.push("update second")
                    Assert.equal(context.node, secondNode)
                    context.compute(key("init"), () => {
                        computing.push("init second")
                        Assert.equal(context.node, secondNode)
                        secondNode.content = second.value
                        return undefined
                    })
                }, () => {
                    computing.push("detach&dispose second")
                    Assert.equal(context.node, secondNode)
                })
            }
        })
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")

        assertStringsAndCleanup(computing, "update root ; init root ; create first ; update first ; init first ; create second ; update second ; init second")

        Assert.equal(testUpdate(false, manager), 0)
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")

        Assert.isEmpty(computing)

        count.value = 20
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  first node")

        assertStringsAndCleanup(computing, "update root ; detach&dispose second")

        second.value = "last node"
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  first node")

        Assert.isEmpty(computing)

        count.value = 40
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  last node")

        assertStringsAndCleanup(computing, "update root ; create second ; update second ; init second ; detach&dispose first")

        count.value = 30
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  last node")

        assertStringsAndCleanup(computing, "update root ; create first ; update first ; init first")

        count.value = 40
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  last node")

        assertStringsAndCleanup(computing, "update root ; detach&dispose first")

        second.value = "second node"
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  second node")

        assertStringsAndCleanup(computing, "update root ; update second ; init second")
    })
    test("build and update deep tree", () => {
        let manager = createStateManager()
        manager.namedState("parent", () => "parent")
        manager.namedState("child", () => "child")
        manager.namedState("leaf", () => "leaf")
        let computing = new Array<string>()
        const rootNode = new TestNode()
        let parentNode: TestNode
        let childNode: TestNode
        let leafNode: TestNode
        let root = manager.updatableNode(rootNode, (context: StateContext) => {
            computing.push("update root")
            Assert.equal(context.node, rootNode)
            context.compute(key("init"), () => {
                computing.push("init root")
                Assert.equal(context.node, rootNode)
                rootNode.content = "root"
                return undefined
            })
            if (context.valueBy<string>("parent").length > 0) {
                context.attach(key("parent"), () => {
                    computing.push("create parent")
                    Assert.equal(context.node, undefined)
                    return parentNode = new TestNode()
                }, () => {
                    computing.push("update parent")
                    Assert.equal(context.node, parentNode)
                    context.compute(key("init"), () => {
                        computing.push("init parent")
                        Assert.equal(context.node, parentNode)
                        parentNode.content = context.valueBy<string>("parent")
                        return undefined
                    })
                    if (context.valueBy<string>("child").length > 0) {
                        context.attach(key("child"), () => {
                            computing.push("create child")
                            Assert.equal(context.node, undefined)
                            return childNode = new TestNode()
                        }, () => {
                            computing.push("update child")
                            Assert.equal(context.node, childNode)
                            context.compute(key("init"), () => {
                                computing.push("init child")
                                Assert.equal(context.node, childNode)
                                childNode.content = context.valueBy<string>("child")
                                return undefined
                            })
                            if (context.valueBy<string>("leaf").length > 0) {
                                context.attach(key("leaf"), () => {
                                    computing.push("create leaf")
                                    Assert.equal(context.node, undefined)
                                    return leafNode = new TestNode()
                                }, () => {
                                    computing.push("update leaf")
                                    Assert.equal(context.node, leafNode)
                                    context.compute(key("init"), () => {
                                        computing.push("init leaf")
                                        Assert.equal(context.node, leafNode)
                                        leafNode.content = context.valueBy<string>("leaf")
                                        return undefined
                                    })
                                }, () => {
                                    computing.push("detach&dispose leaf")
                                    Assert.equal(context.node, leafNode)
                                })
                            }
                        }, () => {
                            computing.push("detach&dispose child")
                            Assert.equal(context.node, childNode)
                        })
                    }
                }, () => {
                    computing.push("detach&dispose parent")
                    Assert.equal(context.node, parentNode)
                })
            }
        })
        assertNode(root,
            "root\n" +
            "  parent\n" +
            "    child\n" +
            "      leaf")

        assertStringsAndCleanup(computing, "update root ; init root ; create parent ; update parent ; init parent ; create child ; update child ; init child ; create leaf ; update leaf ; init leaf")

        Assert.equal(testUpdate(false, manager), 0)
        assertNode(root,
            "root\n" +
            "  parent\n" +
            "    child\n" +
            "      leaf")

        Assert.isEmpty(computing)

        manager.stateBy<string>("leaf")!.value = "leaf node"
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  parent\n" +
            "    child\n" +
            "      leaf node")

        assertStringsAndCleanup(computing, "update root ; update parent ; update child ; update leaf ; init leaf")

        manager.stateBy<string>("parent")!.value = ""
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root")

        assertStringsAndCleanup(computing, "update root ; detach&dispose parent ; detach&dispose child ; detach&dispose leaf")

        manager.stateBy<string>("child")!.value = "child node"
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root")

        Assert.isEmpty(computing)

        manager.stateBy<string>("parent")!.value = "parent node"
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  parent node\n" +
            "    child node\n" +
            "      leaf node")

        assertStringsAndCleanup(computing, "update root ; create parent ; update parent ; init parent ; create child ; update child ; init child ; create leaf ; update leaf ; init leaf")

        manager.stateBy<string>("leaf")!.value = ""
        Assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  parent node\n" +
            "    child node")

        assertStringsAndCleanup(computing, "update root ; update parent ; update child ; detach&dispose leaf")
    })
    test("schedule state updating to the next frame", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        manager.scheduleCallback(() => { state.value = 10 })
        assertState(state, 0)
        // first frame
        Assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(state, 10)
    })
    test("schedule state updating to the second next frame", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        manager.scheduleCallback(() => { manager.scheduleCallback(() => { state.value = 10 }) })
        assertState(state, 0)
        // first frame
        Assert.equal(testUpdate(true, manager), 0)
        assertState(state, 0)
        // second frame
        Assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(state, 10)
    })
    test("schedule state updating to the third next frame", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        manager.scheduleCallback(() => { manager.scheduleCallback(() => { manager.scheduleCallback(() => { state.value = 10 }) }) })
        assertState(state, 0)
        // first frame
        Assert.equal(testUpdate(true, manager), 0)
        assertState(state, 0)
        // second frame
        Assert.equal(testUpdate(true, manager), 0)
        assertState(state, 0)
        // third frame
        Assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(state, 10)
    })
})


class Data {
    name: string
    value: float64

    constructor(name: string, value: float64) {
        this.name = name
        this.value = value
    }

    static equivalent(oldD: Data, newD: Data): boolean {
        return oldD.name == newD.name && oldD.value == newD.value
    }
}

suite("Equivalent", () => {
    const age16 = new Data("age", 16)
    test("initial state is not modified", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, age16)
    })
    test("state is modified on first snapshot update", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const age64 = new Data("age", 64)
        Assert.notEqual(age16, age64)
        state.value = age64
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, age64)
        Assert.notEqual(state.value, age16)
    })
    test("state is not modified on next snapshot update", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const age64 = new Data("age", 64)
        state.value = age64
        Assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, age64)
        Assert.notEqual(state.value, age16)
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, age64)
    })
    test("state is not modified if values are equivalent, but returns new value", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const equal = new Data("age", 16)
        Assert.notEqual(equal, age16)
        Assert.isTrue(Data.equivalent(equal, age16))
        state.value = equal
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, equal)
        Assert.notEqual(state.value, age16)
    })
    test("frozen state is not modified if values are equivalent, but returns new value", () => {
        const manager = createStateManager()
        manager.frozen = true // NB!
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const equal = new Data("age", 16)
        Assert.notEqual(equal, age16)
        Assert.isTrue(Data.equivalent(equal, age16))
        state.value = equal
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, equal)
        Assert.notEqual(state.value, age16)
    })
    test("state is not modified if the equivalent value is set, but returns new value", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        let value = age16
        for (let age = 0; age <= 16; age++) {
            state.value = value = new Data("age", age)
        }
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, value)
    })
    test("frozen state is not modified if the equivalent value is set, but returns new value", () => {
        const manager = createStateManager()
        manager.frozen = true // NB!
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        let value = age16
        for (let age = 0; age <= 16; age++) {
            state.value = value = new Data("age", age)
        }
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, value)
    })
})

class Tracker<Value> implements ValueTracker<Value> {
    private readonly onCreateFunc: (value: Value) => Value
    private readonly onUpdateFunc: (value: Value) => Value
    constructor(onCreate: (value: Value) => Value, onUpdate: (value: Value) => Value) {
        this.onCreateFunc = onCreate
        this.onUpdateFunc = onUpdate
    }
    onCreate(value: Value): Value {
        return this.onCreateFunc(value)
    }
    onUpdate(value: Value): Value {
        return this.onUpdateFunc(value)
    }
}

function onCreate<Value>(onCreate: (value: Value) => Value): ValueTracker<Value> {
    return new Tracker<Value>(onCreate, (value: Value): Value => value)
}

function onUpdate<Value>(onUpdate: (value: Value) => Value): ValueTracker<Value> {
    return new Tracker<Value>((value: Value): Value => value, onUpdate)
}

suite("ValueTracker", () => {
    test("track state creation", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onCreate((value: int32) => value * value))
        assertState(state, 25)
    })
    test("disable state modification", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onUpdate((value: int32): int32 => {
            throw new Error("cannot set " + value)
        }))
        assertState(state, 5)
        Assert.throws(() => { state.value = 404 })
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, 5)
    })
    test("disable state modification silently", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onUpdate((_: int32) => 5))
        assertState(state, 5)
        state.value = 404
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, 5)
    })
    test("disposed state ignores tracker", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onUpdate((_: int32) => 5))
        assertState(state, 5)
        state.value = 404
        Assert.equal(testUpdate(false, manager), 0)
        assertState(state, 5)
        state.dispose()
        state.value = 999
        assertModifiedState(state, 999)
    })
})

suite("ArrayState", () => {
    test("managed array state supports #at getter", () => {
        const manager = createStateManager()
        const array = manager.arrayState(Array.of<string>("one", "two", "three"))
        Assert.equal(array.length, 3)
        Assert.equal(array.at(0), "one")
        Assert.equal(array.at(1), "two")
        Assert.equal(array.at(2), "three")
        Assert.equal(array.at(-1), "three")
        Assert.equal(array.at(-2), "two")
        Assert.equal(array.at(-3), "one")
    })
    test("computable state depends on managed array state", () => {
        const manager = createStateManager()
        const state = manager.mutableState(1)
        const array = manager.arrayState(Array.of<string>("item"))
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                const prefix = state.value + ": "
                return prefix + context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= 1: item =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= 1: item =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        state.value = 2
        array.set(0, "value")
        Assert.equal(testUpdate(false, manager), 2)
        Assert.equal(result.value, "<= 2: value =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        state.value = 3
        array.set(0, "value")
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= 3: value =>")
        assertStringsAndCleanup(computing, "outer ; center")
        // compute state only when snapshot updated
        state.value = 4
        array.length = 0
        Assert.equal(testUpdate(false, manager), 2)
        Assert.equal(result.value, "<= 4:  =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= 4:  =>")
        Assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #copyWithin", () => {
        const manager = createStateManager()
        const array = manager.arrayState(Array.of<string>("one", "two", "three"))
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= one two three =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.copyWithin(0, 1, 2)
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= two two three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.copyWithin(2, 0, 1)
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= two two two =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.copyWithin(1, 2, 0)
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= two two two =>")
        Assert.isEmpty(computing)
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= two two two =>")
        Assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #fill", () => {
        const manager = createStateManager()
        const array = manager.arrayState(Array.of<string>("one", "two", "three"))
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= one two three =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.fill("X", 1, 2)
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= one X three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.fill("X")
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= X X X =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.fill("X", 1)
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= X X X =>")
        Assert.isEmpty(computing)
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= X X X =>")
        Assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #pop", () => {
        const manager = createStateManager()
        const array = manager.arrayState(Array.of<string>("first", "last"))
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= first last =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= first last =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(array.pop(), "last")
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= first =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        Assert.equal(array.pop(), "first")
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        Assert.isUndefined(array.pop())
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #push", () => {
        const manager = createStateManager()
        const array = manager.arrayState<string>()
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(array.push(), 0)
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(array.push("one"), 1)
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        Assert.equal(array.push("two", "three"), 3)
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= one two three =>")
        Assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #reverse", () => {
        const manager = createStateManager()
        const array = manager.arrayState(Array.of<string>("one", "two", "three"))
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= one two three =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.reverse()
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= three two one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= three two one =>")
        Assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #shift", () => {
        const manager = createStateManager()
        const array = manager.arrayState(Array.of<string>("first", "last"))
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= first last =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= first last =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(array.shift(), "first")
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= last =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        Assert.equal(array.shift(), "last")
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        Assert.isUndefined(array.shift())
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #sort", () => {
        const manager = createStateManager()
        const array = manager.arrayState(Array.of<string>("one", "two", "three"))
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= one two three =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.sort()
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= one three two =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.sort()
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= one three two =>")
        Assert.isEmpty(computing)
/* Improve: [TID 00edbb] F/ets: Failed to create the collator for en (US)
        // compute state only when snapshot updated
        array.sort((s1: string, s2: string) => s1.length < s2.length ? -1 : s1.length > s2.length ? 1 : s1.localeCompare(s2))
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= one two three =>")
        Assert.isEmpty(computing)
*/
    })
    test("computable state depends on managed array state #unshift", () => {
        const manager = createStateManager()
        const array = manager.arrayState<string>()
        // create computable state that tracks computing inner scopes
        const computing = new Array<string>()
        const result = manager.computableState((context: StateContext) => {
            computing.push("outer")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("center"), () => {
                computing.push("center")
                return context.compute(key("inner"), () => {
                    computing.push("inner")
                    return array.value.join(" ")
                })
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState<string>(result, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(array.unshift(), 0)
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<=  =>")
        Assert.isEmpty(computing)
        // compute state only when snapshot updated
        Assert.equal(array.unshift("one"), 1)
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        Assert.equal(array.unshift("two", "three"), 3)
        Assert.equal(testUpdate(false, manager), 1)
        Assert.equal(result.value, "<= two three one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        Assert.equal(testUpdate(false, manager), 0)
        Assert.equal(result.value, "<= two three one =>")
        Assert.isEmpty(computing)
    })
})
export const __ARKTEST__ = "states/State.test"
