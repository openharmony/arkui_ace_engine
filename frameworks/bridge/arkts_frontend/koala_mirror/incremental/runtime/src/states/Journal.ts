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

import { AtomicRef } from "@koalaui/common"

export interface Changes {
    /**
     * Finds the latest value change for the given state.
     * @param state - the state to search
     * @returns a reference to the latest value change for the given state,
     *          or `undefined` if there is no any registered changes
     */
    getChange<Value>(state: Object): AtomicRef<Value> | undefined

    /**
     * Removes all changes.
     */
    clear(): void
}

export class Journal implements Changes {
    private readonly current = new AtomicRef<Chunk>(new Chunk())

    /**
     * Sets the journal marker to separate changes.
     */
    setMarker(): void {
        if (this.current.value.map.size > 0) {
            const chunk = new Chunk()
            chunk.previous.value = this.current.getAndSet(chunk)
        }
    }

    /**
     * Registers the value change for the given state.
     * @param state - the state to update
     * @param value - the new value for the given state
     */
    addChange<Value>(state: Object, value: Value): void {
        this.current.value.map.set(state, new AtomicRef<Value>(value))
    }

    /**
     * @returns all marked changes to process,
     *          or `undefined` if there is no any registered changes
     */
    getChanges(): Changes | undefined {
        const reference = this.current.value.previous
        return reference.value ? new ChunkChanges(reference) : undefined
    }

    /**
     * Finds the latest value change for the given state.
     * @param state - the state to search
     * @returns a reference to the latest value change for the given state,
     *          or `undefined` if there is no any registered changes
     */
    getChange<Value>(state: Object): AtomicRef<Value> | undefined {
        return find<Value>(state, this.current.value)
    }

    /**
     * Removes all changes.
     */
    clear(): void {
        this.current.value = new Chunk()
    }

    /**
     * Returns the cached array to store changes.
     * The copy of the given array is created on first change.
     * @param state - the corresponding array state
     * @param array - current snapshot of the array state
     * @returns the cached array registered for the given state
     * @experimental
     */
    getCachedArray<Item>(state: Object, array: Array<Item>): Array<Item> {
        const chunk = this.current.value
        const change = chunk.get<Array<Item>>(state)
        if (change) return change.value
        const copy = Array.from<Item>(find<Array<Item>>(state, chunk.previous.value)?.value ?? array)
        chunk.map.set(state, new AtomicRef<Array<Item>>(copy))
        return copy
    }
}

class ChunkChanges implements Changes {
    private reference: AtomicRef<Chunk | undefined>

    constructor(reference: AtomicRef<Chunk | undefined>) {
        this.reference = reference
    }

    getChange<Value>(state: Object): AtomicRef<Value> | undefined {
        return find<Value>(state, this.reference.value)
    }

    clear(): void {
        this.reference.value = undefined
    }
}

class Chunk {
    readonly previous = new AtomicRef<Chunk | undefined>(undefined)
    readonly map = new Map<Object, Object>()

    get<Value>(state: Object): AtomicRef<Value> | undefined {
        const change = this.map.get(state)
        if (change) return change as AtomicRef<Value>
        return undefined
    }
}

/**
 * Finds the latest value change for the given state starting from the specified chunk.
 * @param state - the state to search
 * @param chunk - the chunk of changes to start search from
 * @returns a reference to the latest value change for the given state,
 *          or `undefined` if there is no any registered changes
 */
function find<Value>(state: Object, chunk?: Chunk): AtomicRef<Value> | undefined {
    while (chunk) {
        const change = chunk?.get<Value>(state)
        if (change) return change
        chunk = chunk?.previous.value
    }
    return undefined
}
