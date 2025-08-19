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

import * as fs from "node:fs"
import * as path from "node:path"

export class Tracer {
    static GlobalTracer: Tracer

    static startGlobalTracing(outDir: string) {
        const traceDir = path.join(outDir, 'trace')
        fs.rmSync(traceDir, { force: true, recursive: true })
        fs.mkdirSync(traceDir, { recursive: true })
        const globalTraceFile = path.join(traceDir, '.global.txt')
        
        Tracer.GlobalTracer = new Tracer(globalTraceFile)
        Tracer.pushContext('tracer')
        trace(() => `Trace file created at ${globalTraceFile}`, true)
    }

    constructor(private filePath: string) {
        
    }

    trace(traceLog: string | undefined | void) {
        if (!traceLog) {
            return
        }
        const lastContext = Tracer.lastContext()
        fs.appendFileSync(this.filePath, `[${lastContext.padStart(12)}] ${traceLog}\n`, 'utf-8')
    }

    private static contexts: string[] = []

    static lastContext() {
        return Tracer.contexts[Tracer.contexts.length - 1]
    }

    static pushContext(newContext: string) {
        Tracer.contexts.push(newContext)
    }

    static popContext() {
        Tracer.contexts.push()
    }
}

export function trace(traceLog: () => string | undefined | void, forceLogToConsole: boolean = false) {
    if (forceLogToConsole) {
        const result = traceLog()
        if (result) {
            console.log(`[${Tracer.lastContext()}] ${result}`)
        }
    }
    if (!Tracer.GlobalTracer) {
        return
    }
    Tracer.GlobalTracer.trace(traceLog())
}
