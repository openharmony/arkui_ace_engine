/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { KNativePointer } from "@koalaui/interop"
import { defaultFilter, listPrograms } from "./plugins"
import { Program } from "../generated"

export class ProgramProvider {
    // Improve: migrate to wrappers instead of pointers
    seenPrograms: Set<KNativePointer> = new Set<KNativePointer>()
    queue: Program[] = []

    constructor(private mainProgram: Program, private readonly filter: (name: string) => boolean = defaultFilter) {
        this.seenPrograms.add(mainProgram.peer)
        this.queue = [mainProgram]
    }

    updateQueue() {
        const listed = listPrograms(this.mainProgram, this.filter)
        for (const program of listed) {
            if (!this.seenPrograms.has(program.peer)) {
                this.seenPrograms.add(program.peer)
                this.queue.push(program)
            }
        }
    }

    next(): Program | undefined {
        if (this.queue.length == 0) {
            this.updateQueue()
            if (this.queue.length == 0) {
                // console.log("PROGRAMS:", this.seenPrograms.size)
                return undefined
            }
        }
        return this.queue.shift()
    }
}
