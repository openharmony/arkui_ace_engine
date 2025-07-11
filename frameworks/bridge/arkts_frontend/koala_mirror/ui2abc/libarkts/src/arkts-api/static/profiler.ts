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

import * as fs from "fs"
import * as path from "path"
import { Es2pandaContextState } from "../../generated/Es2pandaEnums"
import { global } from "./global"

const PERFORMANCE_DATA_DIR = "./performance-results/"

interface PluginData {
    transformTime: number
    transformTimeDeps: number
    visitedNodes: number
    createdNodes: number
    contextState?: Es2pandaContextState
}

function emptyPluginData(contextState?: Es2pandaContextState): PluginData {
    return {
        transformTime: 0,
        transformTimeDeps: 0,
        visitedNodes: 0,
        createdNodes: 0,
        contextState: contextState
    }
}

interface PerformanceData {
    filePath: string

    visitedNodes: number
    createdNodes: number
    restartTime: number
    proceedTime: number
    totalTime: number

    pluginsByName: Record<string, PluginData>
}

interface PerformanceDataFile {
    data: PerformanceData[]
    summary?: PerformanceData
}

function parseFile(performanceFile: string): PerformanceDataFile | undefined {
    if (!fs.existsSync(performanceFile)) return undefined

    const data = fs.readFileSync(path.resolve(performanceFile)).toString()
    if (!data.length) return undefined
    return JSON.parse(data) as PerformanceDataFile
}

export class Profiler implements PerformanceData {
    filePath: string = ""
    visitedNodes: number = 0
    createdNodes: number = 0
    restartTime: number = 0
    proceedTime: number = 0
    totalTime: number = 0
    pluginsByName: Record<string, PluginData> = {}

    curPlugin: string = ""
    curContextState?: Es2pandaContextState

    private getPluginData(pluginName: string, contextState?: Es2pandaContextState): PluginData {
        if (!(pluginName in this.pluginsByName)) {
            this.pluginsByName[pluginName] = emptyPluginData(contextState)
        }
        return this.pluginsByName[pluginName]
    }

    disableReport = false

    nodeCreated() {
        this.createdNodes++
        if (this.curPlugin) this.getPluginData(this.curPlugin, this.curContextState).createdNodes++
    }

    nodeVisited() {
        this.visitedNodes++
        if (this.curPlugin) this.getPluginData(this.curPlugin, this.curContextState).visitedNodes++
    }

    private transformStartTime = 0
    transformStarted() {
        this.transformStartTime = Date.now()
    }
    private transformDepStartTime = 0
    transformDepStarted() {
        this.transformDepStartTime = Date.now()
    }

    transformEnded(state: Es2pandaContextState, pluginName: string) {
        const transformEndTime = Date.now()
        const consumedTime = transformEndTime - this.transformStartTime
        this.getPluginData(pluginName, state).transformTime += consumedTime
    }

    transformDepEnded(state: Es2pandaContextState, pluginName: string) {
        const transformEndTime = Date.now()
        const consumedTime = transformEndTime - this.transformDepStartTime
        this.getPluginData(pluginName, state).transformTimeDeps += consumedTime
    }

    restarted(consumedTime: number) {
        this.restartTime += consumedTime
    }

    proceededToState(consumedTime: number) {
        this.proceedTime += consumedTime
    }

    private compilationStartTime = 0
    compilationStarted(filePath: string) {
        this.filePath = filePath

        this.visitedNodes = 0
        this.createdNodes = 0
        this.restartTime = 0
        this.proceedTime = 0
        this.totalTime = 0
        this.pluginsByName = {}

        this.curPlugin = ""
        this.compilationStartTime = Date.now()
    }

    compilationEnded() {
        const consumedTime: number = Date.now() - this.compilationStartTime
        this.totalTime = consumedTime
    }

    report() {
        Object.entries(this.pluginsByName).forEach((data, key) => {
            console.log(data[0], "totalTransformTime =", data[1].transformTime, "ms")
            console.log(data[0], "totalDepsTransformTime =", data[1].transformTimeDeps, "ms")
        })
    }

    reportToFile(withSummary: boolean = false) {
        if (this.disableReport) return
        const outDir = path.resolve(global.arktsconfig!.outDir, PERFORMANCE_DATA_DIR)
        fs.mkdirSync(outDir, { recursive: true })
        const outFilePath = path.resolve(outDir, path.basename(this.filePath)) + ".json"
    
        const data: PerformanceDataFile = { data: [this as PerformanceData] }
        if (!fs.existsSync(outFilePath)) {
            fs.writeFileSync(outFilePath, JSON.stringify(data))
        } else {
            const savedData: PerformanceDataFile | undefined = parseFile(outFilePath) ?? data
            savedData.data.push(this as PerformanceData)

            if (withSummary) {
                const summary: PerformanceData = {
                    filePath: this.filePath,
                    visitedNodes: savedData.data.map(it => it.visitedNodes).reduce((sum, it) => sum + it),
                    createdNodes: savedData.data.map(it => it.createdNodes).reduce((sum, it) => sum + it),
                    restartTime: savedData.data.map(it => it.restartTime).reduce((sum, it) => sum + it),
                    proceedTime: savedData.data.map(it => it.proceedTime).reduce((sum, it) => sum + it),
                    totalTime: savedData.data.map(it => it.totalTime).reduce((sum, it) => sum + it),
                    pluginsByName: {}
                }
                const pluginNames = new Set(savedData.data.flatMap(it => Object.keys(it.pluginsByName)))
                for (const pluginName of pluginNames) {
                    const sumTransformTime = savedData.data.map(it => it.pluginsByName).filter(it => !!it[pluginName]).map(it => it[pluginName].transformTime).reduce((sum, it) => sum+it)
                    const sumTransformTimeDeps = savedData.data.map(it => it.pluginsByName).filter(it => !!it[pluginName]).map(it => it[pluginName].transformTimeDeps).reduce((sum, it) => sum+it)
                    const sumCreatedNodes = savedData.data.map(it => it.pluginsByName).filter(it => !!it[pluginName]).map(it => it[pluginName].createdNodes).reduce((sum, it) => sum+it)
                    const sumVisitedNodes = savedData.data.map(it => it.pluginsByName).filter(it => !!it[pluginName]).map(it => it[pluginName].visitedNodes).reduce((sum, it) => sum+it)

                    summary.pluginsByName[pluginName] = {
                        transformTime: sumTransformTime,
                        transformTimeDeps: sumTransformTimeDeps,
                        createdNodes: sumCreatedNodes,
                        visitedNodes: sumVisitedNodes,
                    }
                }

                savedData.summary = summary
            }

            fs.writeFileSync(outFilePath, JSON.stringify(savedData))
        }
    }
}
