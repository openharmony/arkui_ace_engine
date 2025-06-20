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

import { Es2pandaContextState } from "../generated/Es2pandaEnums"
import { ExternalSource, Program } from "./peers/Program"

export interface CompilationOptions {
    readonly isMainProgram: boolean,
    readonly name: string,
    readonly stage: Es2pandaContextState,
}

export interface PluginContext {
    setParameter<V>(name: string, value: V): void
    parameter<V>(name: string) : V | undefined

}
export class PluginContextImpl implements PluginContext {
    map = new Map<String, Object|undefined>()
    parameter<V>(name: string): V|undefined {
        return this.map.get(name) as (V|undefined)
    }
    setParameter<V>(name: string, value: V) {
        this.map.set(name, value as Object)
    }
}

export type ProgramTransformer = (program: Program, compilationOptions: CompilationOptions, context: PluginContext) => void

export function defaultFilter(name: string) {
    if (name.startsWith("std.")) return false
    if (name.startsWith("escompat")) return false
    return true
}

export interface ProgramWithName {
    program: Program,
    name: string
}

export function listPrograms(program: Program, filter: (name: string) => boolean = defaultFilter): ProgramWithName[] {
    return [
        { program, name: "" },
        ...program.externalSources.flatMap((it: ExternalSource) => {
            if (filter(it.getName())) {
                return it.programs.map(program => ({ program, name: it.getName() } as ProgramWithName))
            }
            return []
        })
    ]
}
