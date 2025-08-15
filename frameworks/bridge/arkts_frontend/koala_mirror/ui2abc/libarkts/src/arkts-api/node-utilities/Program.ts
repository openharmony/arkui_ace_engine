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

import { Program } from "../../generated"
import { traceGlobal } from "../../tracer"

export function dumpProgramInfo(program: Program) {
    traceGlobal(() => `Program info:`)
    traceGlobal(() => `\tAbsoluteName:          ${program.absoluteName}`)
    traceGlobal(() => `\tFileName:              ${program.fileName}`)
    traceGlobal(() => `\tFileNameWithExtension: ${program.fileNameWithExtension}`)
    traceGlobal(() => `\tModuleName:            ${program.moduleName}`)
    traceGlobal(() => `\tModulePrefix:          ${program.modulePrefix}`)
    traceGlobal(() => `\tRelativeFilePath:      ${program.relativeFilePath}`)
    traceGlobal(() => `\tResolvedFilePath:      ${program.resolvedFilePath}`)
    traceGlobal(() => `\tSourceFileFolder:      ${program.sourceFileFolder}`)
    traceGlobal(() => `\tSourceFilePath:        ${program.sourceFilePath}`)
}

export function dumpProgramSrcFormatted(program: Program, recursive: boolean, withLines: boolean = true) {
    const lines = program.ast.dumpSrc()
    console.log(`// file: ${program.absoluteName}`)
    if (withLines) {
        console.log(lines.split('\n').map((it, index) => `${`${index + 1}`.padStart(4)} |${it}`).join('\n'))
    } else {
        console.log(lines)
    }
}
