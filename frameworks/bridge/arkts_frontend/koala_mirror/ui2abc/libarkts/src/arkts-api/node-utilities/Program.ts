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

import { ExternalSource } from "../peers/ExternalSource"
import { acceptNativeObjectArrayResult } from "../utilities/private"
import { KNativePointer } from "@koalaui/interop"
import { global } from "../static/global"
import { Program } from "../../generated"

export function programGetExternalSources(program: Program, context: KNativePointer = global.context): ExternalSource[] {
    return acceptNativeObjectArrayResult<ExternalSource>(
        global.es2panda._ProgramExternalSources(context, program.peer),
        (instance: KNativePointer) => new ExternalSource(instance)
    )
}

export function dumpProgramInfo(program: Program) {
    console.log(`Program info:`)
    console.log(`\tAbsoluteName:          ${program.absoluteName}`)
    console.log(`\tFileName:              ${program.fileName}`)
    console.log(`\tFileNameWithExtension: ${program.fileNameWithExtension}`)
    console.log(`\tModuleName:            ${program.moduleName}`)
    console.log(`\tModulePrefix:          ${program.modulePrefix}`)
    console.log(`\tRelativeFilePath:      ${program.relativeFilePath}`)
    console.log(`\tResolvedFilePath:      ${program.resolvedFilePath}`)
    console.log(`\tSourceFileFolder:      ${program.sourceFileFolder}`)
    console.log(`\tSourceFilePath:        ${program.sourceFilePath}`)
}

export function dumpProgramSrcFormatted(program: Program, withLines: boolean = true) {
    const lines = program.ast.dumpSrc()
    console.log(`// file: ${program.absoluteName}`)
    if (withLines) {
        console.log(lines.split('\n').map((it, index) => `${`${index + 1}`.padStart(4)} |${it}`).join('\n'))
    } else {
        console.log(lines)
    }
}
