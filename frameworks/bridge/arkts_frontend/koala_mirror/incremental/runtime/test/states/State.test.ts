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

import { Assert as assert, suite, test } from "@koalaui/harness"
import { hashCodeFromString as key } from "@koalaui/common"
import { IncrementalNode, MutableState, State, TestNode, testUpdate, ValueTracker } from "../../src"
import { createStateManager } from "../../src/states/State"

export function assertNode(state: State<TestNode>, presentation: string) {
    assert.isFalse(state.modified) // the same node
    assert.equal(state.value.toHierarchy(), presentation)
}

function assertState<Value>(state: State<Value>, value: Value, modified = false) {
    assert.equal(state.modified, modified)
    assert.equal(state.value, value)
    assert.equal(state.modified, modified)
}

function assertModifiedState<Value>(state: State<Value>, value: Value, modified = false) {
    assertState(state, value, true)
}

function assertStringsAndCleanup(array: string[], presentation: string) {
    assert.isNotEmpty(array)
    assert.equal(array.join(" ; "), presentation)
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
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, 404)
    })
    test("managed state is not modified on next snapshot update", () => {
        let manager = createStateManager()
        let state = manager.mutableState(200)
        state.value = 404
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, 404)
    })
    test("managed state is not modified if the same value is set", () => {
        let manager = createStateManager()
        let state = manager.mutableState(200)
        for (let index = 0; index <= 200; index++) {
            state.value = index
        }
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, 200)
    })
    test("unmanaged named state does not exist anymore", () => {
        let manager = createStateManager()
        const state = manager.namedState<number>("named", () => 200)
        assert.equal(state, manager.stateBy("named")!)
        assert.isDefined<State<number>>(manager.stateBy<number>("named")!)
        state.dispose()
        assert.isUndefined(manager.stateBy<number>("named")!)
        state.dispose()
        assert.isUndefined(manager.stateBy<number>("named")!)
    })
    test("managed named state is not modified immediately", () => {
        let manager = createStateManager()
        manager.frozen = true
        manager.namedState("named", () => 200)
        manager.stateBy<number>("named")!.value = 404
        assert.equal(manager.valueBy<number>("named"), 200)
        assert.isFalse(manager.stateBy<number>("named")?.modified)
    })
    test("managed named state is modified on first snapshot update", () => {
        let manager = createStateManager()
        manager.namedState("named", () => 200)
        manager.stateBy<number>("named")!.value = 404
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(manager.valueBy<number>("named"), 404)
        assert.isTrue(manager.stateBy<number>("named")?.modified)
    })
    test("managed named state is not modified on next snapshot update", () => {
        let manager = createStateManager()
        manager.namedState("named", () => 200)
        manager.stateBy<number>("named")!.value = 404
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(manager.valueBy<number>("named"), 404)
        assert.isFalse(manager.stateBy<number>("named")?.modified)
    })
    test("managed named state is not modified if the same value is set", () => {
        let manager = createStateManager()
        manager.namedState("named", () => 200)
        for (let index = 0; index <= 200; index++) {
            manager.stateBy<number>("named")!.value = index
        }
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(manager.valueBy<number>("named"), 200)
        assert.isFalse(manager.stateBy<number>("named")?.modified)
    })
    test("do not allow to dispose parameter state", () => {
        const name = "parameter"
        const manager = createStateManager()
        manager.computableState(context => {
            const scope = context.scope<void>(0, 1)
            const param = scope.paramEx(0, 200, undefined, name, true) // can be found by name
            if (scope.unchanged) return scope.cached
            const state = manager.stateBy<number>(name)!
            assert.isDefined(state)
            assert.equal(state, param)
            assert.throws(() => state.dispose())
            scope.recache()
        }).value
    })
    test("managed parameter state is modified immediately", () => {
        const name = "parameter"
        const manager = createStateManager()
        manager.computableState(context => {
            const scope = context.scope<void>(0, 1)
            const param = scope.paramEx(0, 200, undefined, name, true) // can be found by name
            if (scope.unchanged) return scope.cached
            const state = manager.stateBy<number>(name)!
            assert.isDefined(state)
            assert.equal(state, param)
            state.value = 404
            assertModifiedState(state, 404)
            // check that modified state is updated
            state.value = 404
            assertState(state, 404)
            scope.recache()
        }).value
    })
    test("updatable node should be recomputable state", () => {
        const manager = createStateManager()
        const mutableState = manager.mutableState(true)
        const updatableNode = manager.updatableNode(new IncrementalNode(), () => mutableState.value)
        // updatable node needs to be recomputed after creation
        assert.isTrue(updatableNode.recomputeNeeded)
        updatableNode.value
        // updatable node is already computed after accessing
        assert.isFalse(updatableNode.recomputeNeeded)
        assert.equal(testUpdate(false, manager), 0)
        // updatable node is already computed because nothing is changed
        assert.isFalse(updatableNode.recomputeNeeded)
        mutableState.value = !mutableState.value
        // updatable node does not know that the mutable state is changed
        assert.isFalse(updatableNode.recomputeNeeded)
        assert.equal(testUpdate(false, manager), 1)
        // updatable node needs to be recomputed because the mutable state is changed
        assert.isTrue(updatableNode.recomputeNeeded)
    })
    test("updatable node should not use StateManager.updateSnapshot()", () => {
        const manager = createStateManager()
        const state = manager.updatableNode(new IncrementalNode(), () => manager.updateSnapshot())
        assert.throws(() => state.value)
    })
    test("updatable node should not use StateManager.updatableNode(...)", () => {
        const manager = createStateManager()
        const state = manager.updatableNode(new IncrementalNode(), () => manager.updatableNode(new IncrementalNode(), () => { }))
        assert.throws(() => state.value)
    })
    test("updatable node should not use StateManager.computableState(...)", () => {
        const manager = createStateManager()
        const state = manager.updatableNode(new IncrementalNode(), () => manager.updateSnapshot())
        assert.throws(() => state.value)
    })
    test("computable state should be recomputable state", () => {
        const manager = createStateManager()
        const mutableState = manager.mutableState(true)
        const computableState = manager.computableState(() => mutableState.value)
        // computable state needs to be recomputed after creation
        assert.isTrue(computableState.recomputeNeeded)
        computableState.value
        // computable state is already computed after accessing
        assert.isFalse(computableState.recomputeNeeded)
        assert.equal(testUpdate(false, manager), 0)
        // computable state is already computed because nothing is changed
        assert.isFalse(computableState.recomputeNeeded)
        mutableState.value = !mutableState.value
        // computable state does not know that the mutable state is changed
        assert.isFalse(computableState.recomputeNeeded)
        assert.equal(testUpdate(false, manager), 1)
        // computable state needs to be recomputed because the mutable state is changed
        assert.isTrue(computableState.recomputeNeeded)
    })
    test("computable state should not use StateManager.updateSnapshot()", () => {
        const manager = createStateManager()
        const state = manager.computableState(() => manager.updateSnapshot())
        assert.throws(() => state.value)
    })
    test("computable state should not use StateManager.updatableNode(...)", () => {
        const manager = createStateManager()
        const state = manager.computableState(() => manager.updatableNode(new IncrementalNode(), () => { }))
        assert.throws(() => state.value)
    })
    test("computable state depends on managed state", () => {
        let manager = createStateManager()
        let name = manager.mutableState("NAME")
        // create computable state that tracks computing inner scopes
        let computing: string[] = []
        let result = manager.computableState(context => {
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
        assertState(result, "<= NAME =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assertState(result, "<= NAME =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        name.value = "Sergey Malenkov"
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(result, "<= Sergey Malenkov =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state depends on named state managed globally", () => {
        let manager = createStateManager()
        // create named scope managed globally and schedule its updating
        manager.namedState("global", () => "NAME")
        // create computable state that tracks computing inner scopes
        let computing: string[] = []
        let result = manager.computableState(context => {
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
        assertState(result, "<= NAME =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assertState(result, "<= NAME =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        manager.stateBy<string>("global")!.value = "Sergey Malenkov"
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(result, "<= Sergey Malenkov =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state depends on named state managed locally", () => {
        let manager = createStateManager()
        // create computable state that tracks computing inner scopes
        let computing: string[] = []
        let result = manager.computableState(context => {
            computing.push("main")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("name"), () => {
                computing.push("name")
                const state = context.namedState("local", () => 1)
                manager.scheduleCallback(() => state.value++)
                return state.value
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState(result, "<= 1 =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        assertState(result, "<= 1 =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(result, "<= 2 =>")
        assertStringsAndCleanup(computing, "main ; name")
        // compute state on next snapshot update
        assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(result, "<= 3 =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state depends on named state managed locally from managed inner scope", () => {
        let manager = createStateManager()
        let computing: string[] = []
        let result = manager.computableState(context => {
            context.namedState("local", () => 1)
            computing.push("main")
            return context.compute(key("left"), () => {
                computing.push("left")
                return "<= "
            }) + context.compute(key("name"), () => {
                computing.push("name")
                const state = context.stateBy<number>("local")!
                manager.scheduleCallback(() => state.value++)
                return context.valueBy<number>("local").toString()
            }) + context.compute(key("right"), () => {
                computing.push("right")
                return " =>"
            })
        })
        // initial computation
        assertState(result, "<= 1 =>")
        assertStringsAndCleanup(computing, "main ; left ; name ; right")
        // computable state is not modified
        assertState(result, "<= 1 =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(result, "<= 2 =>")
        assertStringsAndCleanup(computing, "main ; name")
        // compute state on next snapshot update
        assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(result, "<= 3 =>")
        assertStringsAndCleanup(computing, "main ; name")
    })
    test("computable state allows to cleanup disposed scopes", () => {
        let manager = createStateManager()
        let computing: string[] = []
        let result = manager.computableState<string>(context => {
            let name = context.compute<string>(key("value"), () => {
                computing.push("compute:value")
                return "value"
            })
            let condition = context.compute<boolean>(key("condition"), () => {
                computing.push("compute:condition")
                return context.valueBy<boolean>("condition")
            })
            let value = condition
                ? context.compute<string>(key("true"), () => {
                    computing.push("compute:true")
                    return context.compute<string>(key("true"), () => {
                        context.namedState("true", () => true)
                        computing.push("compute:inner:true")
                        return "true"
                    }, old => {
                        assert.isUndefined(context.stateBy<boolean>("false")!)
                        assert.isDefined<State<boolean>>(context.stateBy<boolean>("true")!)
                        assert.isTrue(context.valueBy<boolean>("true"))
                        assert.equal(old, "true")
                        computing.push("cleanup:inner:true")
                    })
                }, () => computing.push("cleanup:true"))
                : context.compute<string>(key("false"), () => {
                    computing.push("compute:false")
                    return context.compute<string>(key("false"), () => {
                        context.namedState("false", () => false)
                        computing.push("compute:inner:false")
                        return "false"
                    }, old => {
                        assert.isUndefined(context.stateBy<boolean>("true")!)
                        assert.isDefined<State<boolean>>(context.stateBy<boolean>("false")!)
                        assert.isFalse(context.valueBy<boolean>("false"))
                        assert.equal(old, "false")
                        computing.push("cleanup:inner:false")
                    })
                }, () => computing.push("cleanup:false"))
            return name + " is " + value
        })
        let condition = manager.namedState("condition", () => true)
        // initial computation
        assert.equal(result.value, "value is true")
        assertStringsAndCleanup(computing, "compute:value ; compute:condition ; compute:true ; compute:inner:true")
        // condition changed from true to false
        condition.value = false
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "value is false")
        assertStringsAndCleanup(computing, "compute:condition ; compute:false ; compute:inner:false ; cleanup:true ; cleanup:inner:true")
        // condition changed from false to true
        condition.value = true
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "value is true")
        assertStringsAndCleanup(computing, "compute:condition ; compute:true ; compute:inner:true ; cleanup:false ; cleanup:inner:false")
    })
    test.skip("computable state does not support non-unique ids on add", () => {
        let manager = createStateManager()
        let computing: string[] = []
        let result = manager.computableState(context => {
            let condition = context.compute(key("condition"), () => {
                computing.push("compute:condition")
                return context.valueBy<boolean>("condition")
            })
            let first = condition ? undefined : context.compute(key("<NON-UNIQUE>"), () => {
                computing.push("compute:first")
                return "first"
            })
            let second = context.compute(key("<NON-UNIQUE>"), () => {
                computing.push("compute:second")
                return "second"
            })
            return (first ? first + " & " : "only ") + second
        })
        let condition = manager.namedState("condition", () => true)
        // initial computation
        assert.equal(result.value, "only second")
        assertStringsAndCleanup(computing, "compute:condition ; compute:second")
        // condition changed from true to false
        condition.value = false
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "first & second")
        assertStringsAndCleanup(computing, "compute:condition ; compute:first")
    })
    test.skip("computable state does not support non-unique ids on remove", () => {
        let manager = createStateManager()
        let computing: string[] = []
        let result = manager.computableState(context => {
            let condition = context.compute(key("condition"), () => {
                computing.push("compute:condition")
                return context.valueBy<boolean>("condition")
            })
            let first = condition ? undefined : context.compute(key("<NON-UNIQUE>"), () => {
                computing.push("compute:first")
                return "first"
            })
            let second = context.compute(key("<NON-UNIQUE>"), () => {
                computing.push("compute:second")
                return "second"
            })
            return (first ? first + " & " : "only ") + second
        })
        let condition = manager.namedState("condition", () => false)
        // initial computation
        assert.equal(result.value, "first & second")
        assertStringsAndCleanup(computing, "compute:condition ; compute:first ; compute:second")
        // condition changed from false to true
        condition.value = true
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "only second")
        assertStringsAndCleanup(computing, "compute:condition")
    })
    test("global named state must be created only once", () => {
        let manager = createStateManager()
        let created = manager.namedState("named", () => 200)
        let existed = manager.namedState("named", () => {
            assert.fail()
            return 200
        })
        assert.equal(created, existed)
        assert.equal(created, manager.stateBy("named"))
        assert.equal(existed, manager.stateBy("named"))
    })
    test("local named state must be created only once", () => {
        createStateManager().computableState(context => {
            let created = context.namedState("named", () => 200)
            let existed = context.namedState("named", () => {
                assert.fail()
                return 200
            })
            assert.equal(created, existed)
            assert.equal(created, context.stateBy("named"))
            assert.equal(existed, context.stateBy("named"))
        }).value
    })
    test("global named state must not be created when creating another one", () => {
        let manager = createStateManager()
        manager.namedState("named", () => {
            assert.throws(() => {
                manager.namedState("unnamed", () => 200)
            })
            return 200
        })
    })
    test("local named state must not be created when creating another one", () => {
        createStateManager().computableState(context => {
            context.namedState("named", () => {
                assert.throws(() => {
                    context.namedState("unnamed", () => 200)
                })
                return 200
            })
        }).value
    })
    test("do not allow to dispose global mutable state when creating global named state", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState("value")
        manager.namedState("prohibited", () => {
            assert.throws(() => mutable.dispose())
            return mutable.value
        })
    })
    test("do not allow to dispose global mutable state when creating local named state", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState("value")
        const state = manager.computableState(context => {
            context.namedState("prohibited", () => {
                assert.throws(() => mutable.dispose())
                return mutable.value
            })
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose global named state when creating global named state", () => {
        const manager = createStateManager()
        const named = manager.namedState("state", () => "value")
        manager.namedState("prohibited", () => {
            assert.equal(named, manager.stateBy("state"))
            assert.throws(() => named.dispose())
            return named.value
        })
    })
    test("do not allow to dispose local named state when creating local named state", () => {
        const manager = createStateManager()
        const state = manager.computableState(context => {
            const named = context.namedState("state", () => "")
            context.namedState("prohibited", () => {
                assert.equal(named, manager.stateBy("state"))
                assert.throws(() => named.dispose())
                return named.value
            })
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose global mutable state when updating computable state", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState("value")
        const state = manager.computableState(context => {
            assert.throws(() => mutable.dispose())
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose global named state when updating computable state", () => {
        const manager = createStateManager()
        const named = manager.namedState("state", () => "")
        const state = manager.computableState(context => {
            assert.throws(() => named.dispose())
        })
        state.value
        state.dispose()
    })
    test("do not allow to dispose local named state when updating computable state", () => {
        const manager = createStateManager()
        const state = manager.computableState(context => {
            const named = context.namedState("state", () => "")
            assert.throws(() => named.dispose())
        })
        state.value
        state.dispose()
    })
    test("do not allow to update snapshot when updating computable state", () => {
        const manager = createStateManager()
        const state = manager.computableState(context => {
            assert.equal(context, manager)
            assert.throws(() => manager.updateSnapshot())
        })
        state.value
        state.dispose()
    })
    test("do not allow to create updatable node when updating computable state", () => {
        const manager = createStateManager()
        const state = manager.computableState(context => {
            assert.equal(context, manager)
            assert.throws(() => manager.updatableNode(new TestNode(), () => { }))
        })
        state.value
        state.dispose()
    })
    test("computable state must not compute something when creating local named state", () => {
        createStateManager().computableState(context => {
            context.namedState("name", () => {
                assert.throws(() => {
                    context.compute(key("compute"), () => 200)
                })
                return "NAME"
            })
            return context.valueBy<string>("name")
        }).value
    })
    test("computable state must not depend on managed state when creating another one", () => {
        let manager = createStateManager()
        let mutable = manager.mutableState("NAME")
        let computable = manager.computableState(context => {
            context.namedState("name", () => mutable.value)
            return context.valueBy<string>("name")
        })
        // initial computation
        assertState(computable, "NAME")
        // do not update result when snapshot updated
        mutable.value = "Sergey Malenkov"
        assert.equal(testUpdate(false, manager), 1)
        assertState(computable, "NAME")
    })
    test("computable state from specific scope must be forgotten on dispose automatically", () => {
        const manager = createStateManager()
        const state = manager.mutableState(-1)
        const selector = manager.mutableState(true)
        const computable = manager.computableState(context => selector.value
            ? context.compute(key("first"), () => context.computableState(() => state.value), undefined, true)
            : context.compute(key("second"), () => context.computableState(() => state.value), undefined, true))
        // initial computation
        const initial = computable.value
        assertState(initial, -1)
        // ensure that initial state is managed
        state.value = -10
        assertState(initial, -1)
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, -10)
        assertModifiedState(initial, -10)
        // dispose first inner scope
        assert.strictEqual(computable.value, initial)
        selector.value = false
        assert.equal(testUpdate(false, manager), 1)
        assert.notStrictEqual(computable.value, initial)
        // ensure that initial state is not managed
        assertState(initial, -10)
        state.value = -100
        assert.equal(testUpdate(false, manager), 1)
        assertState(initial, -10)
    })
    test("named state from specific scope must be forgotten on dispose automatically", () => {
        const manager = createStateManager()
        manager.frozen = true
        const selector = manager.mutableState(true)
        const computable = manager.computableState(context => selector.value
            ? context.compute(key("first"), () => context.namedState("name", () => -1))
            : context.compute(key("second"), () => context.namedState("name", () => 1)))
        // initial computation
        const initial = computable.value
        assertState(initial, -1)
        // ensure that initial state is managed
        initial.value = -10
        assertState(initial, -1)
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(initial, -10)
        // dispose first inner scope
        assert.strictEqual(computable.value, initial)
        selector.value = false
        assert.equal(testUpdate(false, manager), 1)
        assert.notStrictEqual(computable.value, initial)
        // ensure that initial state is not managed
        assertState(initial, -10)
        initial.value = -100
        assertModifiedState(initial, -100)
    })
    test("mutable state from specific scope must be forgotten on dispose too", () => {
        const manager = createStateManager()
        manager.frozen = true
        const selector = manager.mutableState(true)
        const computable = manager.computableState(context => selector.value
            ? context.compute(key("first"), () => context.mutableState(-1), undefined, true)
            : context.compute(key("second"), () => context.mutableState(1), undefined, true))
        // initial computation
        const initial = computable.value
        assertState(initial, -1)
        // ensure that initial state is managed
        initial.value = -10
        assertState(initial, -1)
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(initial, -10)
        // dispose first inner scope
        assert.strictEqual(computable.value, initial)
        selector.value = false
        assert.equal(testUpdate(false, manager), 1)
        assert.notStrictEqual(computable.value, initial)
        // ensure that initial state is not managed
        assertState(initial, -10)
        initial.value = -100
        assertModifiedState(initial, -100)
    })
    test("mutable state must not be changed during recomposition", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        const increment = () => {
            assert.throws(() => state.value++)
            return state.value
        }
        const computable = manager.computableState(context =>
            context.compute(key("a"), increment) +
            context.compute(key("b"), increment) +
            context.compute(key("c"), increment))
        assert.equal(computable.value, 0)
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(computable.value, 0)
        state.value++
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(computable.value, 3)
    })
    test("allow to compute once within a leaf scope", () => {
        const computable = createStateManager().computableState(context =>
            context.compute(key("leaf"), () =>
                context.compute(key("allowed"), () => 0, undefined, true),
                undefined, true))
        assert.equal(computable.value, 0)
    })
    test("create global mutable state in local context", () => {
        const manager = createStateManager()
        const computable = manager.computableState(context => context.mutableState(0, true))
        const globalState = computable.value
        assert.equal("GlobalState=0", globalState.toString())
        globalState.value = 1
        assert.equal(testUpdate(false, manager), 1)
        assert.equal("GlobalState,modified=1", globalState.toString())
        assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        assert.equal("GlobalState=1", globalState.toString())
        globalState.dispose()
        assert.equal("GlobalState,disposed=1", globalState.toString())
    })
    test("create local mutable state in local context within remember", () => {
        const manager = createStateManager()
        const computable = manager.computableState(context => context.compute(0, () => context.mutableState(0, false), undefined, true))
        const localState = computable.value
        assert.equal("LocalState=0", localState.toString())
        localState.value = 1
        assert.equal(testUpdate(false, manager), 1)
        assert.equal("LocalState,modified=1", localState.toString())
        assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        assert.equal("LocalState,disposed=1", localState.toString())
        localState.dispose()
        assert.equal("LocalState,disposed=1", localState.toString())
    })
    test("create global named state in local context", () => {
        const manager = createStateManager()
        const computable = manager.computableState<MutableState<number>>(context => {
            const state = context.namedState<number>("global", () => 0, true)
            assert.equal(state, manager.stateBy("global")!)
            assert.isDefined<State<number>>(manager.stateBy<number>("global", true)!)
            assert.isUndefined(manager.stateBy<number>("global", false)!)
            return state
        })
        const globalState = computable.value
        assert.equal(globalState, manager.stateBy("global"))
        assert.equal("GlobalState(global)=0", globalState.toString())
        globalState.value = 1
        assert.equal(testUpdate(false, manager), 1)
        assert.equal("GlobalState(global),modified=1", globalState.toString())
        assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        assert.equal("GlobalState(global)=1", globalState.toString())
        globalState.dispose()
        assert.equal("GlobalState(global),disposed=1", globalState.toString())
    })
    test("create local named state in local context", () => {
        const manager = createStateManager()
        const globalState = manager.namedState<number>("global", () => Number.MAX_SAFE_INTEGER + 1)
        const computable = manager.computableState<MutableState<number>>(context => {
            assert.equal(globalState, manager.stateBy("global")!)
            assert.isDefined<State<number>>(manager.stateBy<number>("global", true)!)
            assert.isUndefined(manager.stateBy<number>("global", false)!)
            const state = context.namedState<number>("local", () => 0, false)
            assert.equal(state, manager.stateBy("local")!)
            assert.isUndefined(manager.stateBy<number>("local", true)!)
            assert.isDefined<State<number>>(manager.stateBy<number>("local", false)!)
            return state
        })
        const localState = computable.value
        assert.isUndefined(manager.stateBy<number>("local")!)
        assert.equal("LocalState(local)=0", localState.toString())
        localState.value = 1
        assert.equal(testUpdate(false, manager), 1)
        assert.equal("LocalState(local),modified=1", localState.toString())
        assert.equal(testUpdate(false, manager), 0)
        computable.dispose()
        assert.equal("LocalState(local),disposed=1", localState.toString())
        localState.dispose()
        assert.equal("LocalState(local),disposed=1", localState.toString())
    })
    test("prohibit to create local mutable state in global context", () => {
        assert.throws(() => createStateManager().mutableState(0, false))
    })
    test("prohibit to create local named state in global context", () => {
        assert.throws(() => createStateManager().namedState("name", () => 0, false))
    })
    test("prohibit to create local mutable state in local context", () => {
        const computable = createStateManager().computableState(context => context.mutableState(0, false))
        assert.throws(() => computable.value)
    })
    test("prohibit to compute within a leaf scope", () => {
        const computable = createStateManager().computableState(context =>
            context.compute(key("leaf"), () =>
                context.compute(key("prohibit"), () => 0),
                undefined, true))
        assert.throws(() => computable.value)
    })
    test("prohibit to build tree within a leaf scope", () => {
        const computable = createStateManager().updatableNode(new TestNode(), context =>
            context.compute(key("leaf"), () =>
                context.attach(key("prohibit"), () => new TestNode(), () => { }),
                undefined, true))
        assert.throws(() => computable.value)
    })
    test("prohibit to build tree within a computable state", () => {
        const computable = createStateManager().computableState(context =>
            context.attach(key("prohibit"), () => new TestNode(), () => { }))
        assert.throws(() => computable.value)
    })
    test("leaf scope must not depend on managed state", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        const computing: string[] = []
        const computable = manager.computableState(context => {
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
        assert.equal(testUpdate(false, manager), 1)
        assertState(computable, 0)
        assert.isEmpty(computing)
    })
    test("0. amount of modified states including computable states that have dependants", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState(false)
        let computableCounter = 0
        const computable = manager.computableState(context => {
            computableCounter++
            return mutable.value
        })
        let stateCounter = 0
        const state = manager.computableState(context => {
            stateCounter++
            return computable.value
        })
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(computableCounter, 0) // computable is not recomputed
        assert.equal(stateCounter, 0) // state is not recomputed
        assertState(state, false)
        assert.equal(computableCounter, 1) // computable is recomputed
        assert.equal(stateCounter, 1) // state is recomputed
        mutable.value = true
        assert.equal(testUpdate(false, manager), 2)
        assert.equal(computableCounter, 2) // computable is recomputed automatically
        assert.equal(stateCounter, 1) // state is not recomputed
        assertModifiedState(state, true)
        assert.equal(computableCounter, 2) // computable is not recomputed
        assert.equal(stateCounter, 2) // state is recomputed by request
    })
    test("1. amount of modified states including computable states that have dependants", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState(false)
        let computableCounter = 0
        const computable = manager.computableState(context => {
            computableCounter++
            return mutable.value && false
        })
        let stateCounter = 0
        const state = manager.computableState(context => {
            stateCounter++
            return computable.value
        })
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(computableCounter, 0) // computable is not recomputed
        assert.equal(stateCounter, 0) // state is not recomputed
        assertState(state, false)
        assert.equal(computableCounter, 1) // computable is recomputed
        assert.equal(stateCounter, 1) // state is recomputed
        mutable.value = true
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(computableCounter, 2) // computable is recomputed automatically
        assert.equal(stateCounter, 1) // state is not recomputed
        assertState(state, false)
        assert.equal(computableCounter, 2) // computable is not recomputed
        assert.equal(stateCounter, 1) // state is not recomputed because computable is not modified
    })
    test("2. amount of modified states including computable states that have dependants", () => {
        const manager = createStateManager()
        const mutable = manager.mutableState(false)
        let computableCounter = 0
        const computable = manager.computableState(context => {
            computableCounter++
            return mutable.value
        })
        let stateCounter = 0
        const state = manager.computableState(context => {
            stateCounter++
            return computable.value && false
        })
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(computableCounter, 0) // computable is not recomputed
        assert.equal(stateCounter, 0) // state is not recomputed
        assertState(state, false)
        assert.equal(computableCounter, 1) // computable is recomputed
        assert.equal(stateCounter, 1) // state is recomputed
        mutable.value = true
        assert.equal(testUpdate(false, manager), 2)
        assert.equal(computableCounter, 2) // computable is recomputed automatically
        assert.equal(stateCounter, 1) // state is not recomputed
        assertState(state, false)
        assert.equal(computableCounter, 2) // computable is not recomputed
        assert.equal(stateCounter, 2) // state is recomputed by request but it is not modified
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
        assertState(computable, 1)
        assertStringsAndCleanup(computing, "recomputed")
        // do not recompute if nothing changed
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(computable.value, 1)
        assert.isEmpty(computing)
        // recompute if used stateT changed
        stateT.value = -1
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(computable.value, -1)
        assertStringsAndCleanup(computing, "recomputed")
        // do not recompute if stateF changed
        stateF.value = -2
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(computable.value, -1)
        assert.isEmpty(computing)
        // switch flag and recompute
        stateB.value = false
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(computable.value, -2)
        assertStringsAndCleanup(computing, "recomputed")
        // recompute if used stateF changed
        stateF.value = 2
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(computable.value, 2)
        assertStringsAndCleanup(computing, "recomputed")
        // do not recompute if stateT changed
        stateT.value = 1
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(computable.value, 2)
        assert.isEmpty(computing)
    })
    test("build and update simple tree", () => {
        let manager = createStateManager()
        let count = manager.mutableState(30)
        let first = manager.mutableState("first node")
        let second = manager.mutableState("second node")
        let computing: string[] = []
        const rootNode = new TestNode()
        let firstNode: TestNode
        let secondNode: TestNode
        let root = manager.updatableNode(rootNode, context => {
            computing.push("update root")
            assert.equal(context.node, rootNode)
            context.compute(key("init"), () => {
                computing.push("init root")
                assert.equal(context.node, rootNode)
                rootNode.content = "root"
            })
            if (count.value < 40) {
                context.attach(key("first"), () => {
                    computing.push("create first")
                    assert.equal(context.node, undefined)
                    return firstNode = new TestNode()
                }, () => {
                    computing.push("update first")
                    assert.equal(context.node, firstNode)
                    context.compute(key("init"), () => {
                        computing.push("init first")
                        assert.equal(context.node, firstNode)
                        firstNode.content = first.value
                    })
                }, () => {
                    computing.push("detach&dispose first")
                    assert.equal(context.node, firstNode)
                })
            }
            if (count.value > 20) {
                context.attach(key("second"), () => {
                    computing.push("create second")
                    assert.equal(context.node, undefined)
                    return secondNode = new TestNode()
                }, () => {
                    computing.push("update second")
                    assert.equal(context.node, secondNode)
                    context.compute(key("init"), () => {
                        computing.push("init second")
                        assert.equal(context.node, secondNode)
                        secondNode.content = second.value
                    })
                }, () => {
                    computing.push("detach&dispose second")
                    assert.equal(context.node, secondNode)
                })
            }
        })
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")

        assertStringsAndCleanup(computing, "update root ; init root ; create first ; update first ; init first ; create second ; update second ; init second")

        assert.equal(testUpdate(false, manager), 0)
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  second node")

        assert.isEmpty(computing)

        count.value = 20
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  first node")

        assertStringsAndCleanup(computing, "update root ; detach&dispose second")

        second.value = "last node"
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  first node")

        assert.isEmpty(computing)

        count.value = 40
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  last node")

        assertStringsAndCleanup(computing, "update root ; create second ; update second ; init second ; detach&dispose first")

        count.value = 30
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  first node\n" +
            "  last node")

        assertStringsAndCleanup(computing, "update root ; create first ; update first ; init first")

        count.value = 40
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  last node")

        assertStringsAndCleanup(computing, "update root ; detach&dispose first")

        second.value = "second node"
        assert.equal(testUpdate(false, manager), 1)
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
        let computing: string[] = []
        const rootNode = new TestNode()
        let parentNode: TestNode
        let childNode: TestNode
        let leafNode: TestNode
        let root = manager.updatableNode(rootNode, context => {
            computing.push("update root")
            assert.equal(context.node, rootNode)
            context.compute(key("init"), () => {
                computing.push("init root")
                assert.equal(context.node, rootNode)
                rootNode.content = "root"
            })
            if (context.valueBy<string>("parent").length > 0) {
                context.attach(key("parent"), () => {
                    computing.push("create parent")
                    assert.equal(context.node, undefined)
                    return parentNode = new TestNode()
                }, () => {
                    computing.push("update parent")
                    assert.equal(context.node, parentNode)
                    context.compute(key("init"), () => {
                        computing.push("init parent")
                        assert.equal(context.node, parentNode)
                        parentNode.content = context.valueBy<string>("parent")
                    })
                    if (context.valueBy<string>("child").length > 0) {
                        context.attach(key("child"), () => {
                            computing.push("create child")
                            assert.equal(context.node, undefined)
                            return childNode = new TestNode()
                        }, () => {
                            computing.push("update child")
                            assert.equal(context.node, childNode)
                            context.compute(key("init"), () => {
                                computing.push("init child")
                                assert.equal(context.node, childNode)
                                childNode.content = context.valueBy<string>("child")
                            })
                            if (context.valueBy<string>("leaf").length > 0) {
                                context.attach(key("leaf"), () => {
                                    computing.push("create leaf")
                                    assert.equal(context.node, undefined)
                                    return leafNode = new TestNode()
                                }, () => {
                                    computing.push("update leaf")
                                    assert.equal(context.node, leafNode)
                                    context.compute(key("init"), () => {
                                        computing.push("init leaf")
                                        assert.equal(context.node, leafNode)
                                        leafNode.content = context.valueBy<string>("leaf")
                                    })
                                }, () => {
                                    computing.push("detach&dispose leaf")
                                    assert.equal(context.node, leafNode)
                                })
                            }
                        }, () => {
                            computing.push("detach&dispose child")
                            assert.equal(context.node, childNode)
                        })
                    }
                }, () => {
                    computing.push("detach&dispose parent")
                    assert.equal(context.node, parentNode)
                })
            }
        })
        assertNode(root,
            "root\n" +
            "  parent\n" +
            "    child\n" +
            "      leaf")

        assertStringsAndCleanup(computing, "update root ; init root ; create parent ; update parent ; init parent ; create child ; update child ; init child ; create leaf ; update leaf ; init leaf")

        assert.equal(testUpdate(false, manager), 0)
        assertNode(root,
            "root\n" +
            "  parent\n" +
            "    child\n" +
            "      leaf")

        assert.isEmpty(computing)

        manager.stateBy<string>("leaf")!.value = "leaf node"
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  parent\n" +
            "    child\n" +
            "      leaf node")

        assertStringsAndCleanup(computing, "update root ; update parent ; update child ; update leaf ; init leaf")

        manager.stateBy<string>("parent")!.value = ""
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root")

        assertStringsAndCleanup(computing, "update root ; detach&dispose parent ; detach&dispose child ; detach&dispose leaf")

        manager.stateBy<string>("child")!.value = "child node"
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root")

        assert.isEmpty(computing)

        manager.stateBy<string>("parent")!.value = "parent node"
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  parent node\n" +
            "    child node\n" +
            "      leaf node")

        assertStringsAndCleanup(computing, "update root ; create parent ; update parent ; init parent ; create child ; update child ; init child ; create leaf ; update leaf ; init leaf")

        manager.stateBy<string>("leaf")!.value = ""
        assert.equal(testUpdate(false, manager), 1)
        assertNode(root,
            "root\n" +
            "  parent node\n" +
            "    child node")

        assertStringsAndCleanup(computing, "update root ; update parent ; update child ; detach&dispose leaf")
    })
    test("schedule state updating to the next frame", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        manager.scheduleCallback(() => state.value = 10)
        assertState(state, 0)
        // first frame
        assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(state, 10)
    })
    test("schedule state updating to the second next frame", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        manager.scheduleCallback(() => manager.scheduleCallback(() => state.value = 10))
        assertState(state, 0)
        // first frame
        assert.equal(testUpdate(true, manager), 0)
        assertState(state, 0)
        // second frame
        assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(state, 10)
    })
    test("schedule state updating to the third next frame", () => {
        const manager = createStateManager()
        const state = manager.mutableState(0)
        manager.scheduleCallback(() => manager.scheduleCallback(() => manager.scheduleCallback(() => state.value = 10)))
        assertState(state, 0)
        // first frame
        assert.equal(testUpdate(true, manager), 0)
        assertState(state, 0)
        // second frame
        assert.equal(testUpdate(true, manager), 0)
        assertState(state, 0)
        // third frame
        assert.equal(testUpdate(true, manager), 1)
        assertModifiedState(state, 10)
    })
})


class Data {
    name: string
    value: number

    constructor(name: string, value: number) {
        this.name = name
        this.value = value
    }

    static equivalent(oldD: Data, newD: Data): boolean {
        return oldD.name === newD.name && oldD.value === newD.value
    }
}

suite("Equivalent", () => {
    const age16 = new Data("age", 16)
    test("initial state is not modified", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, age16)
    })
    test("state is modified on first snapshot update", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const age64 = new Data("age", 64)
        assert.notEqual(age16, age64)
        state.value = age64
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, age64)
        assert.notEqual(state.value, age16)
    })
    test("state is not modified on next snapshot update", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const age64 = new Data("age", 64)
        state.value = age64
        assert.equal(testUpdate(false, manager), 1)
        assertModifiedState(state, age64)
        assert.notEqual(state.value, age16)
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, age64)
    })
    test("state is not modified if values are equivalent, but returns new value", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const equal = new Data("age", 16)
        assert.notEqual(equal, age16)
        assert.isTrue(Data.equivalent(equal, age16))
        state.value = equal
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, equal)
        assert.notEqual(state.value, age16)
    })
    test("frozen state is not modified if values are equivalent, but returns new value", () => {
        const manager = createStateManager()
        manager.frozen = true // NB!
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        const equal = new Data("age", 16)
        assert.notEqual(equal, age16)
        assert.isTrue(Data.equivalent(equal, age16))
        state.value = equal
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, equal)
        assert.notEqual(state.value, age16)
    })
    test("state is not modified if the equivalent value is set, but returns new value", () => {
        const manager = createStateManager()
        const state = manager.mutableState(age16, undefined, Data.equivalent)
        assertState(state, age16)
        let value = age16
        for (let age = 0; age <= 16; age++) {
            state.value = value = new Data("age", age)
        }
        assert.equal(testUpdate(false, manager), 0)
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
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, value)
    })
})


function tracker<Value>(onCreate: (value: Value) => Value, onUpdate: (value: Value) => Value): ValueTracker<Value> {
    return { onCreate, onUpdate }
}

function onCreate<Value>(onCreate: (value: Value) => Value): ValueTracker<Value> {
    return tracker(onCreate, value => value)
}

function onUpdate<Value>(onUpdate: (value: Value) => Value): ValueTracker<Value> {
    return tracker(value => value, onUpdate)
}

suite("ValueTracker", () => {
    test("track state creation", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onCreate(value => value * value))
        assertState(state, 25)
    })
    test("disable state modification", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onUpdate(value => {
            throw new Error("cannot set " + value)
        }))
        assertState(state, 5)
        assert.throws(() => state.value = 404)
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, 5)
    })
    test("disable state modification silently", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onUpdate(() => 5))
        assertState(state, 5)
        state.value = 404
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, 5)
    })
    test("disposed state ignores tracker", () => {
        const manager = createStateManager()
        const state = manager.mutableState(5, undefined, undefined, onUpdate(() => 5))
        assertState(state, 5)
        state.value = 404
        assert.equal(testUpdate(false, manager), 0)
        assertState(state, 5)
        state.dispose()
        state.value = 999
        assertModifiedState(state, 999)
    })
})

suite("ArrayState", () => {
    test("managed array state supports #at getter", () => {
        const manager = createStateManager()
        const array = manager.arrayState(["one", "two", "three"])
        assert.equal(array.length, 3)
        assert.equal(array.at(0), "one")
        assert.equal(array.at(1), "two")
        assert.equal(array.at(2), "three")
        assert.equal(array.at(-1), "three")
        assert.equal(array.at(-2), "two")
        assert.equal(array.at(-3), "one")
    })
    test("computable state depends on managed array state", () => {
        const manager = createStateManager()
        const state = manager.mutableState(1)
        const array = manager.arrayState(["item"])
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<= 1: item =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= 1: item =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        state.value = 2
        array.set(0, "value")
        assert.equal(testUpdate(false, manager), 2)
        assert.equal(result.value, "<= 2: value =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        state.value = 3
        array.set(0, "value")
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= 3: value =>")
        assertStringsAndCleanup(computing, "outer ; center")
        // compute state only when snapshot updated
        state.value = 4
        array.length = 0
        assert.equal(testUpdate(false, manager), 2)
        assert.equal(result.value, "<= 4:  =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= 4:  =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #copyWithin", () => {
        const manager = createStateManager()
        const array = manager.arrayState(["one", "two", "three"])
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= one two three =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.copyWithin(0, 1, 2)
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= two two three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.copyWithin(2, 0, 1)
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= two two two =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.copyWithin(1, 2, 0)
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= two two two =>")
        assert.isEmpty(computing)
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= two two two =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #fill", () => {
        const manager = createStateManager()
        const array = manager.arrayState(["one", "two", "three"])
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= one two three =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.fill("X", 1, 2)
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= one X three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.fill("X")
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= X X X =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.fill("X", 1)
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= X X X =>")
        assert.isEmpty(computing)
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= X X X =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #pop", () => {
        const manager = createStateManager()
        const array = manager.arrayState(["first", "last"])
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<= first last =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= first last =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(array.pop(), "last")
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= first =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        assert.equal(array.pop(), "first")
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        assert.isUndefined(array.pop())
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #push", () => {
        const manager = createStateManager()
        const array = manager.arrayState()
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(array.push(), 0)
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(array.push("one"), 1)
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        assert.equal(array.push("two", "three"), 3)
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= one two three =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #reverse", () => {
        const manager = createStateManager()
        const array = manager.arrayState(["one", "two", "three"])
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= one two three =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.reverse()
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= three two one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= three two one =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #shift", () => {
        const manager = createStateManager()
        const array = manager.arrayState(["first", "last"])
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<= first last =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= first last =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(array.shift(), "first")
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= last =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        assert.equal(array.shift(), "last")
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        assert.isUndefined(array.shift())
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #sort", () => {
        const manager = createStateManager()
        const array = manager.arrayState(["one", "two", "three"])
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= one two three =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.sort()
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= one three two =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        array.sort()
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= one three two =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        array.sort((s1, s2) => s1.length < s2.length ? -1 : s1.length > s2.length ? 1 : s1.localeCompare(s2))
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= one two three =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= one two three =>")
        assert.isEmpty(computing)
    })
    test("computable state depends on managed array state #unshift", () => {
        const manager = createStateManager()
        const array = manager.arrayState()
        // create computable state that tracks computing inner scopes
        const computing: string[] = []
        const result = manager.computableState(context => {
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
        assertState(result, "<=  =>")
        assertStringsAndCleanup(computing, "outer ; left ; center ; inner ; right")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(array.unshift(), 0)
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<=  =>")
        assert.isEmpty(computing)
        // compute state only when snapshot updated
        assert.equal(array.unshift("one"), 1)
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // compute state only when snapshot updated
        assert.equal(array.unshift("two", "three"), 3)
        assert.equal(testUpdate(false, manager), 1)
        assert.equal(result.value, "<= two three one =>")
        assertStringsAndCleanup(computing, "outer ; center ; inner")
        // computable state is not modified
        assert.equal(testUpdate(false, manager), 0)
        assert.equal(result.value, "<= two three one =>")
        assert.isEmpty(computing)
    })
})
