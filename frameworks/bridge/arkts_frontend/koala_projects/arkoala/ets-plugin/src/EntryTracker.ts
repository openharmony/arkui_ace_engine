/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import * as ts  from '@koalaui/ets-tsc'
import * as path from 'path'

export class EntryTracker {
    // route to its @entry name
    entries = new Map<string, string>()

    constructor(private sourceRoot: string) { }

    fileNameToRoute(fileName: string): string {
        return path.relative(this.sourceRoot, fileName)
            .replace(/\.ets$/, "")
            .replace(/\\/g, '/') // make sure we get forward slashes
    }

    sourceFileToRoute(sourceFile: ts.SourceFile): string {
        return this.fileNameToRoute(sourceFile.fileName)
    }

    addEntry(name: string, sourceFile: ts.SourceFile) {
        const route = this.sourceFileToRoute(sourceFile)
        this.entries.set(route, name)
    }
}