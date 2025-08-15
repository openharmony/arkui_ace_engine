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
import { Program } from "./generated"
import { global } from "./arkts-api/static/global"

export class Tracer {
    static traceDir: string
    static GlobalTracer: Tracer
    static Tracers: Map<string, Tracer>
    static LRUTracer: Tracer | undefined

    static startGlobalTracing(outDir: string) {
        Tracer.traceDir = path.join(outDir, 'trace')
        fs.rmSync(Tracer.traceDir, { force: true, recursive: true })
        const globalTraceFile = path.join(Tracer.traceDir, '.global.txt')
        
        Tracer.GlobalTracer = new Tracer(globalTraceFile)
        Tracer.pushContext('tracer')
        traceGlobal(() => `Trace file created at ${globalTraceFile}`, true)

        Tracer.Tracers = new Map<string, Tracer>()
    }

    static startProgramTracing(program: Program) {
        if (!Tracer.GlobalTracer) {
            return
        }
        const programPath = program.absoluteName
        if (programPath == "") {
            return
        }
        const suggestedTracer = Tracer.Tracers.get(programPath)
        if (suggestedTracer) {
            Tracer.LRUTracer = suggestedTracer
            return
        }
        if (!global.arktsconfig) {
            throw new Error("global.arktsconfig should be set for tracer usage")
        }
        const relative = path.relative(global.arktsconfig?.baseUrl, programPath)
        const traceFileSuggestedPath = relative.startsWith('..')
            ? path.join(this.traceDir, 'external', program.absoluteName.slice(1))
            : path.join(this.traceDir, relative)
        Tracer.LRUTracer = new Tracer(
            path.join(path.dirname(traceFileSuggestedPath), path.basename(traceFileSuggestedPath, path.extname(traceFileSuggestedPath)) + '.txt'),
            programPath
        )
    }

    static stopProgramTracing() {
        Tracer.LRUTracer = undefined
    }

    static stopGlobalTracing() {
        Tracer.GlobalTracer.traceEventsStats()
    }

    private constructor(private traceFilePath: string, inputFilePath?: string) {
        if (!fs.existsSync(path.dirname(traceFilePath))) {
            fs.mkdirSync(path.dirname(traceFilePath), { recursive: true })
        }
        if (inputFilePath) {
            Tracer.Tracers.set(inputFilePath, this)
        }
    }

    trace(traceLog: string | undefined | void) {
        if (!traceLog) {
            return
        }
        const lastContext = Tracer.lastContext()
        fs.appendFileSync(this.traceFilePath, `[${lastContext.padStart(12)}] ${traceLog}\n`, 'utf-8')
    }

    events: Map<string, number> | undefined
    eventsPerContext: Map<string, Map<string, number> > | undefined

    recordEvent(event: string) {
        if (!this.events) {
            this.events = new Map<string, number>()
        }
        this.events.set(event, (this.events.get(event) ?? 0) + 1)

        if (!this.eventsPerContext) {
            this.eventsPerContext = new Map<string, Map<string, number> >()
        }
        if (!this.eventsPerContext.has(Tracer.lastContext())) {
            this.eventsPerContext.set(Tracer.lastContext(), new Map<string, number>())
        }
        const eventsPerContext = this.eventsPerContext.get(Tracer.lastContext())
        eventsPerContext?.set(event, (eventsPerContext.get(event) ?? 0) + 1)
    }

    traceEventsStats() {
        if (this.events && this.eventsPerContext) {
            const maxLength = Math.max(
                ...[...this.events.keys()].map(it => `Event "${it}"`.length),
                ...[...this.eventsPerContext?.keys()].map(it => `  in context [${it}]`.length),
            )
            this.trace(`Events stats:`)
            this.events.forEach((eventCnt: number, event: string) => {
                this.trace(`${`Event "${event}"`.padEnd(maxLength)}: ${eventCnt}`)
                this.eventsPerContext?.forEach((localizedEventsMap: Map<string, number>, context: string) => {
                    localizedEventsMap.forEach((localizedEventCnt: number, localizedEvent: string) => {
                        if (localizedEvent == event) {
                            this.trace(`${`  in context [${context}]`.padEnd(maxLength)}: ${localizedEventCnt}`)
                        }
                    })
                })
            })
        } else {
            this.trace('No events recorded')
        }
        Tracer.popContext()
    }

    private static contexts: string[] = []

    static lastContext() {
        return Tracer.contexts[Tracer.contexts.length - 1]
    }

    static pushContext(newContext: string) {
        Tracer.contexts.push(newContext)
    }

    static popContext() {
        Tracer.contexts.pop()
    }
}

export function traceGlobal(traceLog: () => string | undefined | void, forceLogToConsole: boolean = false) {
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

export function trace(event: string, traceLog: () => string | undefined | void, forceLogToConsole: boolean = false) {
    if (forceLogToConsole) {
        const result = traceLog()
        if (result) {
            console.log(`[${Tracer.lastContext()}] ${result}`)
        }
    }
    if (!Tracer.GlobalTracer) {
        return
    }
    Tracer.LRUTracer?.trace(traceLog())
    Tracer.GlobalTracer.recordEvent(event)
}
