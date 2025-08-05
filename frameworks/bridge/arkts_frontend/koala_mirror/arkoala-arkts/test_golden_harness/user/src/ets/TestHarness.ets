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
import { ScreenshotService, UserView, UserViewBuilder } from '@ohos.arkui'
import { initPages } from './AllPages'
import { memoBind } from '@koalaui/runtime'
import { int32 } from '@koalaui/common'
import { suite} from "@koalaui/harness"
import { suiteStateChange } from "./suites/StateChange"

@memo
function pageByName(name: string): void {
    console.log(`Default pageByName() called`)
}

export let pageByNameFunction: @memo(name: string) => void = pageByName
export function registerPageByNameFunction(@memo pageByName: (name: string) => void) {
    pageByNameFunction = pageByName
}

export interface TestController {
    getLog(): string
    emitTask(type: int32, target: string, arg1?: int32, arg2?: int32): TestController
    start(): TestController
    stop(): TestController
    nextFrame(): Promise<TestController>
    skipFrames(count: int32): Promise<TestController>
    loadPage(page: string): TestController
    notifyChange(id: string): TestController
    notifyClick(id: string): TestController
    snapshot(target: string, name: string): boolean
}

export type AppControl = TestController

function startTests(harness: TestHarness): void {
    harness.startTests()
}

export class TestHarness extends UserView implements TestController {
    private currentTest: string
    constructor() {
        super()
        this.currentTest = ""
        launch<void, (harness: TestHarness) => void>(startTests, this)
    }
    getLog(): string {
        return this.control!.getLog()
    }
    emitTask(type: int32, target: string, arg1?: int32, arg2?: int32): TestController {
        this.control!.emitTask(type, target, arg1, arg2)
        return this
    }
    start(): TestController {
        this.control!.startLog()
        return this
    }
    stop(): TestController {
        this.control!.stopLog()
        return this
    }
    async nextFrame(): Promise<TestController> {
        await this.control!.nextFrame()
        return this
    }
    async skipFrames(count: int32): Promise<TestController> {
        for (let i = 0; i < count; i++) {
            await this.nextFrame()
        }
        return this
    }
    loadPage(page: string): TestController {
        this.currentTest = page
        this.control!.reloadView()
        return this
    }

    notifyChange(id: string): TestController {
        this.control!.emitTask(1 /* TaskType.OnChange */, id)
        return this
    }

    notifyClick(id: string): TestController {
        this.control!.emitTask(0 /* TaskType.OnChange */, id)
        return this
    }

    snapshot(target: string, name: string): boolean {
        // Improve: native call to capture snapshot + compare + diff
        ScreenshotService.requestScreenshot(target, name)
        return true
    }

    startTests() {
        try {
            suite("GOLDEN HARNESS", () => {
                initPages()
                suiteStateChange(this)
            })
        } finally {
            this.control!.requestStopApp()
        }
    }

    getBuilder(): UserViewBuilder {
        return memoBind(pageByNameFunction, this.currentTest)
    }
}
