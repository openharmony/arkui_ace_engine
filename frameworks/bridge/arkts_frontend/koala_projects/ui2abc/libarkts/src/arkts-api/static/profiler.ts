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
    performanceFile = path.resolve(performanceFile)
    if (!fs.existsSync(performanceFile)) return undefined

    const fileData = fs.readFileSync(performanceFile).toString()
    if (!fileData.length) return undefined
    try {
        return JSON.parse(fileData) as PerformanceDataFile
    } catch (error) {
        return undefined
    }
}

export class Profiler implements PerformanceData {
    filePath: string = ""
    visitedNodes: number = 0
    createdNodes: number = 0
    restartTime: number = 0
    proceedTime: number = 0
    totalTime: number = 0
    pluginsByName: Record<string, PluginData> = {}

    private curPlugin: string = ""
    private curContextState?: Es2pandaContextState

    private getPluginData(pluginName: string, contextState?: Es2pandaContextState): PluginData {
        if (!(pluginName in this.pluginsByName)) {
            this.pluginsByName[pluginName] = emptyPluginData(contextState)
        }
        return this.pluginsByName[pluginName]
    }

    nodeCreated() {
        this.createdNodes++
        if (this.curPlugin) this.getPluginData(this.curPlugin, this.curContextState).createdNodes++
    }

    nodeVisited() {
        this.visitedNodes++
        if (this.curPlugin) this.getPluginData(this.curPlugin, this.curContextState).visitedNodes++
    }

    private transformStartTime = 0
    transformStarted(state: Es2pandaContextState, pluginName: string) {
        this.curPlugin = pluginName
        this.curContextState = state
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
        this.curPlugin = ""
        this.curContextState = undefined
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
        this.compilationStartTime = Date.now()
    }

    compilationEnded() {
        const consumedTime: number = Date.now() - this.compilationStartTime
        this.totalTime = consumedTime
    }

    report() {
        Object.entries(this.pluginsByName).forEach(([pluginName, data], key) => {
            console.log(pluginName, "totalTransformTime =", data.transformTime, "ms")
            console.log(pluginName, "totalDepsTransformTime =", data.transformTimeDeps, "ms")
        })
    }

    reportToFile(withSummary: boolean = false) {
        const outDir = path.resolve(global.outDir, "./performance-results/")
        if (!fs.existsSync(outDir)) fs.mkdirSync(outDir)
        const outFilePath = path.resolve(outDir, path.basename(this.filePath)) + ".json"
    
        const curData: PerformanceDataFile = { data: [this as PerformanceData] }
        if (!fs.existsSync(outFilePath)) {
            fs.writeFileSync(outFilePath, JSON.stringify(curData))
        } else {
            const savedData: PerformanceDataFile | undefined = parseFile(outFilePath) ?? curData
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
