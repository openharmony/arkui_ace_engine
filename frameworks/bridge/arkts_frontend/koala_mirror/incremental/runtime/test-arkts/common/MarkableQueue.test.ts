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
import { MarkableQueue, markableQueue } from "@koalaui/common"

const collector = new Array<string>()

function testQueue(queue: MarkableQueue, expected: Array<string>) {
    collector.length = 0
    queue.callCallbacks()
    Assert.deepEqual(collector, expected)
}

suite("MarkableQueue tests", () => {

    test("nothing to call without marker", () => {
        const queue = markableQueue()
        queue.addCallback(() => { collector.push("1a") })
        queue.addCallback(() => { collector.push("1b") })
        queue.addCallback(() => { collector.push("1c") })
        testQueue(queue, Array.of<string>())
    })

    test("call only marked callbacks", () => {
        const queue = markableQueue()
        queue.addCallback(() => { collector.push("1a") })
        queue.addCallback(() => { collector.push("1b") })
        queue.addCallback(() => { collector.push("1c") })
        queue.setMarker()
        queue.addCallback(() => { collector.push("2a") })
        queue.addCallback(() => { collector.push("2b") })
        queue.addCallback(() => { collector.push("2c") })
        testQueue(queue, Array.of<string>("1a", "1b", "1c"))
        testQueue(queue, Array.of<string>()) // called only once
    })

    test("call marked callbacks to the latest marker", () => {
        const queue = markableQueue()
        queue.addCallback(() => { collector.push("1a") })
        queue.addCallback(() => { collector.push("1b") })
        queue.addCallback(() => { collector.push("1c") })
        queue.setMarker()
        queue.addCallback(() => { collector.push("2a") })
        queue.addCallback(() => { collector.push("2b") })
        queue.addCallback(() => { collector.push("2c") })
        queue.setMarker()
        queue.addCallback(() => { collector.push("3a") })
        queue.addCallback(() => { collector.push("3b") })
        queue.addCallback(() => { collector.push("3c") })
        testQueue(queue, Array.of<string>("1a", "1b", "1c", "2a", "2b", "2c"))
        testQueue(queue, Array.of<string>()) // called only once
    })
})

suite("MarkableQueue reversed tests", () => {

    test("nothing to call without marker", () => {
        const queue = markableQueue(true)
        queue.addCallback(() => { collector.push("1a") })
        queue.addCallback(() => { collector.push("1b") })
        queue.addCallback(() => { collector.push("1c") })
        testQueue(queue, Array.of<string>())
    })

    test("call only marked callbacks", () => {
        const queue = markableQueue(true)
        queue.addCallback(() => { collector.push("1a") })
        queue.addCallback(() => { collector.push("1b") })
        queue.addCallback(() => { collector.push("1c") })
        queue.setMarker()
        queue.addCallback(() => { collector.push("2a") })
        queue.addCallback(() => { collector.push("2b") })
        queue.addCallback(() => { collector.push("2c") })
        testQueue(queue, Array.of<string>("1c", "1b", "1a"))
        testQueue(queue, Array.of<string>()) // called only once
    })

    test("call marked callbacks from the latest marker", () => {
        const queue = markableQueue(true)
        queue.addCallback(() => { collector.push("1a") })
        queue.addCallback(() => { collector.push("1b") })
        queue.addCallback(() => { collector.push("1c") })
        queue.setMarker()
        queue.addCallback(() => { collector.push("2a") })
        queue.addCallback(() => { collector.push("2b") })
        queue.addCallback(() => { collector.push("2c") })
        queue.setMarker()
        queue.addCallback(() => { collector.push("3a") })
        queue.addCallback(() => { collector.push("3b") })
        queue.addCallback(() => { collector.push("3c") })
        testQueue(queue, Array.of<string>("2c", "2b", "2a", "1c", "1b", "1a"))
        testQueue(queue, Array.of<string>()) // called only once
    })
})
export const __ARKTEST__ = "common/MarkableQueue.test"
