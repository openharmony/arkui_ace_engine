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
import { Changes, Journal } from "../../src/states/Journal"

function assertChange<Value>(changes: Changes | undefined, state: Object, expected: Value) {
    const change = changes?.getChange<Value>(state)
    Assert.isDefined(change)
    Assert.equal(change?.value, expected)
}

function assertNoChange(changes: Changes | undefined, state: Object) {
    const change = changes?.getChange<string>(state)
    Assert.isUndefined(change)
}

function assertNoChanges(journal: Journal) {
    Assert.isUndefined(journal.getChanges())
}

suite("Journal tests", () => {

    test("new journal has no any changes", () => {
        const journal = new Journal()
        assertNoChanges(journal)
    })

    test("add changes to journal", () => {
        const state = new Object()
        const journal = new Journal()
        journal.addChange(state, "value1")
        journal.addChange(state, "value2")
        assertChange(journal, state, "value2")
        assertNoChanges(journal)
    })

    test("add marked changes to journal", () => {
        const state = new Object()
        const journal = new Journal()
        journal.addChange(state, "value1")
        journal.addChange(state, "value2")
        journal.setMarker()
        assertChange(journal, state, "value2")
        assertChange(journal.getChanges(), state, "value2")
    })

    test("add changes to journal after marker", () => {
        const state = new Object()
        const journal = new Journal()
        journal.addChange(state, "value1")
        journal.addChange(state, "value2")
        journal.setMarker()
        journal.addChange(state, "value3")
        journal.addChange(state, "value4")
        assertChange(journal, state, "value4")
        assertChange(journal.getChanges(), state, "value2")
    })

    test("remove all changes from journal", () => {
        const state = new Object()
        const journal = new Journal()
        journal.addChange(state, "value1")
        journal.addChange(state, "value2")
        journal.setMarker()
        journal.addChange(state, "value3")
        journal.addChange(state, "value4")
        journal.clear()
        assertNoChange(journal, state)
        assertNoChanges(journal)
    })

    test("remove marked changes from journal", () => {
        const state = new Object()
        const journal = new Journal()
        journal.addChange(state, "value1")
        journal.addChange(state, "value2")
        journal.setMarker()
        journal.addChange(state, "value3")
        journal.addChange(state, "value4")
        const changes = journal.getChanges()
        Assert.isDefined(changes)
        changes?.clear()
        assertChange(journal, state, "value4")
        assertNoChanges(journal)
    })
})
export const __ARKTEST__ = "states/Journal.test"
