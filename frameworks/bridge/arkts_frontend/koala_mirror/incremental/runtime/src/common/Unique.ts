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

import { int32 } from "@koalaui/common"

export type UID = int32

export interface Unique {
    readonly uid: UID
}

export class UniqueSet<U extends Unique> {
    private array: Array<U> | undefined = undefined
    private latest: U | undefined = undefined

    get empty(): boolean {
        return this.size <= 0
    }

    /**
     * @returns the number of unique elements
     */
    get size(): number {
        const array = this.array
        return array ? array.length : this.latest ? 1 : 0
    }

    /**
     * @returns a boolean indicating whether the given element exists or not
     */
    has(element: U): boolean {
        const latest = this.latest
        if (latest && latest.uid == element.uid) return true

        const array = this.array
        if (array) {
            const index = find(array, element.uid)
            if (found(array, element.uid, index)) return true
        }
        return false
    }

    /**
     * Adds the given element if it is not already present.
     */
    add(element: U) {
        const latest = this.latest
        if (latest && latest.uid == element.uid) return

        let array = this.array
        if (array) {
            const index = find(array, element.uid)
            if (!found(array, element.uid, index)) {
                array.splice(index, 0, element)
            }
        } else if (latest) {
            array = new Array<U>()
            array.push(latest)
            array.splice(find(array, element.uid), 0, element)
            this.array = array
        }
        this.latest = element
    }

    /**
     * Removes the given element if it is present.
     */
    delete(element: U) {
        const array = this.array
        if (array) {
            const index = find(array, element.uid)
            if (found(array, element.uid, index)) {
                array.splice(index, 1)
            }
        }
        const latest = this.latest
        if (latest && latest.uid == element.uid) {
            this.latest = undefined
        }
    }

    /**
     * Removes all elements for which the given predicate returns true.
     */
    deleteIf(predicate: (element: U) => boolean) {
        const latest = this.latest
        const array = this.array
        if (array) {
            let index = array.length
            while (0 < index--) {
                const element = array![index]
                if (predicate(element)) {
                    array.splice(index, 1)
                    if (element === latest) {
                        this.latest = undefined
                    }
                }
            }
        } else if (latest && predicate(latest)) {
            this.latest = undefined
        }
    }

    /**
     * Performs the given action for each element.
     */
    forEach(action: (element: U) => void) {
        const array = this.array
        if (array) {
            let index = array.length
            while (0 < index--) {
                action((array![index]))
            }
        } else {
            const latest = this.latest
            if (latest) action(latest)
        }
    }

    /**
     * Removes all of the elements.
     */
    clear() {
        this.array = undefined
        this.latest = undefined
    }
}

export class UniqueMap<U extends Unique, V> {
    private array: Array<Entry<U, V>> | undefined = undefined
    private latest: Entry<U, V> | undefined = undefined

    get empty(): boolean {
        return this.size <= 0
    }

    /**
     * @returns the number of unique keys
     */
    get size(): number {
        const array = this.array
        return array ? array.length : this.latest ? 1 : 0
    }

    /**
     * @returns a boolean indicating whether a mapping for the given key exists or not
     */
    has(key: U): boolean {
        const latest = this.latest
        if (latest && latest.uid == key.uid) return true

        const array = this.array
        if (array) {
            const index = find(array, key.uid)
            if (found(array, key.uid, index)) return true
        }
        return false
    }

    /**
     * @returns the value to which the given key is mapped, or `undefined` if a mapping does not exist.
     */
    get(key: U): V | undefined {
        const latest = this.latest
        if (latest && latest.uid == key.uid) return latest.value

        const array = this.array
        if (array) {
            const index = find(array, key.uid)
            const entry = found(array, key.uid, index)
            if (entry) return entry.value
        }
        return undefined
    }

    /**
     * Associates the specified value with the given key.
     * If a mapping for the given key exists, the old value is replaced by the specified value.
     */
    set(key: U, value: V) {
        const latest = this.latest
        if (latest && latest.uid == key.uid) {
            latest.value = value
        } else {
            let array = this.array
            if (array) {
                const index = find(array, key.uid)
                let entry = found(array, key.uid, index)
                if (entry) {
                    entry.value = value
                } else {
                    entry = new Entry<U, V>(key, value)
                    array.splice(index, 0, entry)
                }
                this.latest = entry
            } else {
                const entry = new Entry<U, V>(key, value)
                if (latest) {
                    array = new Array<Entry<U, V>>()
                    array.push(latest)
                    array.splice(find(array, key.uid), 0, entry)
                    this.array = array
                }
                this.latest = entry
            }
        }
    }

    /**
     * Removes a mapping for the given key if it is present.
     */
    delete(key: U) {
        const array = this.array
        if (array) {
            const index = find(array, key.uid)
            if (found(array, key.uid, index)) {
                array.splice(index, 1)
            }
        }
        const latest: Entry<U, V> | undefined = this.latest
        if (latest && latest.uid == key.uid) {
            this.latest = undefined
        }
    }

    /**
     * Removes all mappings for which the given predicate returns true.
     */
    deleteIf(predicate: (key: U, value: V) => boolean) {
        const latest = this.latest
        const array = this.array
        if (array) {
            let index = array.length
            while (0 < index--) {
                const entry = array![index]
                if (predicate(entry.key, entry.value)) {
                    array.splice(index, 1)
                    if (entry === latest) {
                        this.latest = undefined
                    }
                }
            }
        } else if (latest && predicate(latest!.key, latest!.value)) {
            this.latest = undefined
        }
    }

    /**
     * Performs the given action for each mapping.
     */
    forEach(action: (key: U, value: V) => void) {
        const array = this.array
        if (array) {
            let index = array.length
            while (0 < index--) {
                const entry = array![index]
                action(entry.key, entry.value)
            }
        } else {
            const latest = this.latest
            if (latest) action(latest!.key, latest!.value)
        }
    }

    /**
     * Removes all of the mappings.
     */
    clear() {
        this.array = undefined
        this.latest = undefined
    }
}

class Entry<U extends Unique, V> implements Unique {
    readonly key: U
    value: V
    constructor(key: U, value: V) {
        this.key = key
        this.value = value
    }
    get uid(): UID {
        return this.key.uid
    }
}

function found<U extends Unique>(array: Array<U>, uid: UID, index: number): U | undefined {
    if (index < array.length) {
        const element = array[index]
        if (element.uid == uid) return element
    }
    return undefined
}

function find<U extends Unique>(array: Array<U>, uid: UID): number {
    let left = 0
    let right = array.length
    while (left < right) {
        const center = ((left + right) >>> 1) as int32
        if (array[center].uid < uid) left = center + 1
        else right = center
    }
    return left
}
