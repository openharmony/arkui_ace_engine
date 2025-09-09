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

import { AtomicRef } from "@koalaui/common"

/**
 * A markable queue that allows to accumulate callbacks and to call them to the latest set marker.
 */
export interface MarkableQueue {
    /** Sets the new marker to the queue. */
    setMarker(): void
    /** Adds the given callback to the queue. */
    addCallback(callback: () => void): void
    /** Calls all accumulated callbacks to the latest set marker. */
    callCallbacks(): void
    /** Clears the queue. */
    clear(): void
}

/**
 * Creates a new markable queue to safely process callbacks across several threads or tasks.
 * @param reversed - `true` changes the order of calling callbacks
 */
export function markableQueue(reversed: boolean = false): MarkableQueue {
    return reversed ? new ReversedQueue() : new DefaultQueue()
}

class DefaultQueue implements MarkableQueue {
    private readonly last = new AtomicRef<Block>(new Block())
    private readonly first = new AtomicRef<Block>(this.last.value)
    private readonly marker = new AtomicRef<Block | undefined>(undefined)

    setMarker(): void {
        const marker = new Block()
        this.last.getAndSet(marker).next.value = marker
        this.marker.value = marker
    }

    addCallback(callback: () => void): void {
        const block = new Block(callback)
        this.last.getAndSet(block).next.value = block
    }

    callCallbacks(): void {
        const marker = this.marker.getAndSet(undefined)
        if (marker) {
            let block = this.first.getAndSet(marker)
            while (block !== marker) {
                block.callback?.()
                block = block.next.value!
            }
        }
    }

    clear(): void {
        this.last.value = this.first.value
        this.marker.value = undefined
    }
}

class ReversedQueue implements MarkableQueue {
    private readonly last = new AtomicRef<Block | undefined>(undefined)
    private readonly marker = new AtomicRef<Block | undefined>(undefined)

    setMarker(): void {
        const marker = new Block()
        marker.next.value = this.last.getAndSet(marker)
        this.marker.value = marker
    }

    addCallback(callback: () => void): void {
        const block = new Block(callback)
        block.next.value = this.last.getAndSet(block)
    }

    callCallbacks(): void {
        const marker = this.marker.getAndSet(undefined)
        if (marker) {
            let block = marker.next.getAndSet(undefined)
            while (block) {
                block!.callback?.()
                block = block!.next.value
            }
        }
    }

    clear(): void {
        this.last.value = undefined
        this.marker.value = undefined
    }
}

class Block {
    readonly next = new AtomicRef<Block | undefined>(undefined)
    readonly callback: (() => void) | undefined

    constructor(callback?: () => void) {
        this.callback = callback
    }
}
