/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import * as os from 'os'

const nativeModuleLibraries: Map<string, string> = new Map()

export function loadNativeLibrary(name: string): Record<string, object> {
    const isHZVM = !!(globalThis as any).requireNapi
    let nameWithoutSuffix = name.endsWith('.node') ? name.slice(0, name.length - 5) : name
    let candidates: string[] = [
        name,
        `${nameWithoutSuffix}.node`,
        `${nameWithoutSuffix}_${os.arch()}.node`,
        `${nameWithoutSuffix}_${os.platform()}_${os.arch()}.node`,
    ]
    const errors: { candidate: string, command: string, error: any }[] = []
    if (!isHZVM)
        try {
            candidates.push(eval(`require.resolve(${JSON.stringify((nameWithoutSuffix + '.node'))})`))
        } catch (e) {
            errors.push({ candidate: `${nameWithoutSuffix}.node`, command: `resolve(...)`, error: e })
        }

    for (const candidate of candidates) {
        try {
            if (isHZVM)
                return (globalThis as any).requireNapi(candidate, true)
            else
                return eval(`let exports = {}; process.dlopen({ exports }, ${JSON.stringify(candidate)}, 2); exports`)
        } catch (e) {
            errors.push({ candidate: candidate, command: `dlopen`, error: e })
        }
    }
    errors.forEach((e, i) => {
        console.error(`Error ${i} of ${errors.length} command: ${e.command}, candidate: ${e.candidate}, message: ${e.error}`)
    })
    throw new Error(`Failed to load native library ${name}. dlopen candidates: ${candidates.join(':')}`)
}

export function registerNativeModuleLibraryName(nativeModule: string, libraryName: string) {
    nativeModuleLibraries.set(nativeModule, libraryName)
}

export function loadNativeModuleLibrary(moduleName: string, module?: object) {
    if (!module)
        throw new Error('<module> argument is required and optional only for compatibility with ArkTS')
    const library = loadNativeLibrary(nativeModuleLibraries.get(moduleName) ?? moduleName)
    if (!library || !library[moduleName]) {
        console.error(`Failed to load library for module ${moduleName}`)
        return
    }
    Object.assign(module, library[moduleName])
}
