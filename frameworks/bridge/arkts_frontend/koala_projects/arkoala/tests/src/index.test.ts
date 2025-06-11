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

import { ArkoalaControl, nativeModule, startApplication, UIStructureCapture } from "@koalaui/arkoala"
import { NativeModuleRecorder } from "@koalaui/arkoala-arkui"
import { ArkRooted, ArkUINodeType } from "@koalaui/arkoala-arkui"
import { Empty } from  "../generated/ets-test/pages/Empty"
import { registerRoutes } from  "../generated/ets-test/__router_initialization"
import * as path from "path"
import * as fs from "fs/promises"
import { int32 } from "@koalaui/compat"
import { withStringResult } from "@koalaui/interop"

export function startTest(): Promise<ArkoalaControl> {
    registerRoutes()
    return startApplication(ArkRooted(Empty), {
        waitForVSync: () => new Promise((resolve) => setTimeout(resolve, 1)),
        nativeModule: new NativeModuleRecorder((type: ArkUINodeType) => ArkUINodeType[type])
    })
}

interface TestDescriptor {
    page: string
    skipFrames: number
    before?: (control: ArkoalaControl) => Promise<void>
}

let allTests: TestDescriptor[] = [
    {
        page: "pages/Column.test",
        skipFrames: 1
    },
    {
        page: "pages/Row.test",
        skipFrames: 1
    },
    {
        page: "pages/CustomComponentBox.test",
        skipFrames: 1
    },
    {
        page: "pages/Span.test",
        skipFrames: 1
    },
    {
        page: "pages/Click.test",
        skipFrames: 2,
        before: async (control) => {
            await waitFrames(control, 1)
            sendClick(control, elementById("TheButton"), 100, 50)
        }
    },
    // {
    //     page: "pages/Progress.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/Slider.test",
        skipFrames: 1
    },
    {
        page: "pages/Search.test",
        skipFrames: 1
    },
    {
        page: "pages/Select.test",
        skipFrames: 1
    },
    {
        page: "pages/Text.test",
        skipFrames: 1
    },
    {
        page: "pages/Menu.test",
        skipFrames: 1
    },
    {
        page: "pages/MenuItem.test",
        skipFrames: 1
    },
    {
        page: "pages/MenuItemGroup.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/Marquee.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/ImageAnimator.test",
        skipFrames: 1
    },
    {
        page: "pages/Checkbox.test",
        skipFrames: 1
    },
    {
        page: "pages/CheckboxGroup.test",
        skipFrames: 1
    },
    {
        page: "pages/List.test",
        skipFrames: 1
    },
    {
        page: "pages/ListItem.test",
        skipFrames: 1
    },
    {
        page: "pages/ListItemGroup.test",
        skipFrames: 1
    },
    {
        page: "pages/TextArea.test",
        skipFrames: 1
    },
    {
        page: "pages/Grid.test",
        skipFrames: 1
    },
    {
        page: "pages/GridItem.test",
        skipFrames: 1
    },
    {
        page: "pages/GridCol.test",
        skipFrames: 1
    },
    {
        page: "pages/GridRow.test",
        skipFrames: 1
    },
    {
        page: "pages/Tabs.test",
        skipFrames: 1
    },
    {
        page: "pages/TextClock.test",
        skipFrames: 1
    },
    {
        page: "pages/Scroll.test",
        skipFrames: 1
    },
    {
        page: "pages/Navigation.test",
        skipFrames: 1
    },
    {
        page: "pages/Swiper.test",
        skipFrames: 1
    },
    {
        page: "pages/Navigator.test",
        skipFrames: 1
    },
    {
        page: "pages/TextInput.test",
        skipFrames: 1
    },
    {
        page: "pages/Image.test",
        skipFrames: 1
    },
    {
        page: "pages/TextPicker.test",
        skipFrames: 1
    },
    {
        page: "pages/Stack.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/ScrollBar.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/Divider.test",
        skipFrames: 1
    },
    {
        page: "pages/TextTimer.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/DatePicker.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/Radio.test",
        skipFrames: 1
    },
    {
        page: "pages/Blank.test",
        skipFrames: 1
    },
    {
        page: "pages/Flex.test",
        skipFrames: 1
    },
    {
        page: "pages/LoadingProgress.test",
        skipFrames: 1
    },
    {
        page: "pages/NavDestination.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/XComponent.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/SideBarContainer.test",
        skipFrames: 1
    },
    {
        page: "pages/Toggle.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/Web.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/AlphabetIndexer.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/Video.test",
    //     skipFrames: 1
    // },
    // {
    //     page: "pages/DataPanel.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/Shape.test",
        skipFrames: 1
    },
    {
        page: "pages/FormLink.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/Gauge.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/Button.test",
        skipFrames: 1
    },
    {
        page: "pages/Rating.test",
        skipFrames: 1
    },
    {
        page: "pages/Line.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/PatternLock.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/ColumnSplit.test",
        skipFrames: 1
    },
    {
        page: "pages/RowSplit.test",
        skipFrames: 1
    },
    // {
    //     page: "pages/Panel.test",
    //     skipFrames: 1
    // },
    // {
    //     page: "pages/TimePicker.test",
    //     skipFrames: 1
    // },
    {
        page: "pages/Path.test",
        skipFrames: 1
    },
    {
        page: "pages/QRCode.test",
        skipFrames: 1
    }
]

function waitFrames(control: ArkoalaControl, numFrames: int32): Promise<void> {
    return new Promise(resolve => {
        control.sendMessage("arkoala.wait.frames", {
            numFrames: numFrames,
            callback: resolve
        })
    })
}

function elementById(id: string): int32 {
    return nativeModule()._ElementById(id)
}

function replacePage(control: ArkoalaControl, url: string, params: any, callback: ()=> void): void {
    control.sendMessage("arkoala.router.replace", {
        url: url,
        params: params,
        callback: callback
    })
}

function sendPointer(control: ArkoalaControl, target: int32, x: int32, y: int32, status: int32): void {
    control.sendMessage("arkoala.press", {
        kind: 1,
        nodeId: target,
        x: x,
        y: y,
        status: status
    })
}

function sendClick(control: ArkoalaControl, target: int32, x: int32, y: int32): void {
    sendPointer(control, target, x, y, 1)
    sendPointer(control, target, x, y, 0)
}

function exitApp(control: ArkoalaControl): void {
    control.sendMessage("arkoala.app.exit", {})
}

async function delay(timeout: number) {
    await new Promise((resolve) => setTimeout(resolve, timeout))
}

function lastRouterPage(raw: UIStructureCapture): UIStructureCapture {
    return { rootElement: raw.rootElement.children![raw.rootElement.children!.length - 1]!}
}

let generate = process.argv.length > 2 && process.argv[2] == "generate"

startTest()
    .then(async (control) => {
        for (let i = 0; i < allTests.length; i++) {
            let test = allTests[i]
            let page = test.page
            console.log(`Executing ${page}`)
            let capture = await new Promise<UIStructureCapture>((resolve, reject) => {
                replacePage(control, page, {}, async () => {
                    if (test.before) {
                        await test.before(control)
                    }
                    if (test.skipFrames > 0)
                        await waitFrames(control, test.skipFrames)
                    let uiStructure = withStringResult(nativeModule()._CaptureUIStructure())
                    if (uiStructure && uiStructure.length > 0) {
                        resolve(JSON.parse(uiStructure))
                    } else {
                        reject(new Error("Cannot capture structure"))
                    }
                })
            })
            let lastPage = lastRouterPage(capture)
            let fileName = path.join("golden", page.replace("/", "_"))
            let output = JSON.stringify(lastPage, undefined, 2)
            if (generate) {
                await fs.writeFile(fileName, output)
            } else {
                let golden = await fs.readFile(fileName, { encoding: 'utf8' })
                if (golden != output) {
                    console.log(`TEST ${page} failed: expected ${golden} got ${output}`)
                    process.exit(1)
                }
            }
        }
        await delay(500)
        exitApp(control)
    })