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

import { ArkRooted } from "@koalaui/arkoala-arkui"
import { ArkoalaControl, ArkoalaHost, ArkUINativeModuleEmpty, runApplication } from "@koalaui/arkoala"
import { __Entry } from "../generated/ets/perf"

// Some environment for console-less ark_js_vm
function myPrint(x: any) {
    return console.log(x)
}
declare function print(arg:string):string;
const myConsole = {
    log(...args: any) {
        args.forEach((it: any) => print(it))
    }
}

if ("console" in globalThis) {
    (globalThis.print as any) = myPrint as any;
}else {
     (globalThis as any).console = myConsole as any;
}

async function runArkoala(host: Partial<ArkoalaHost>|undefined, callback: (control: ArkoalaControl) => void) {
    return runApplication(
        ArkRooted(__Entry),
        callback,
        error => print(error.toString()),
        {
            waitForVSync: () => Promise.resolve(),
            arkUINativeModule: host?.arkUINativeModule ?? new ArkUINativeModuleEmpty()
        }
    )
}

function sendClick(control: any, target: any, status: any, x: any, y: any) {
    control.sendMessage("arkoala.press", {
        kind: 1,
        nodeId: target,
        x: x,
        y: y,
        status: status
    })
}


function waitFrames(control: ArkoalaControl, numFrames: number): Promise<void> {
    return new Promise(resolve => {
        control.sendMessage("arkoala.wait.frames", {
            numFrames: numFrames,
            callback: resolve
        })
    })
}


await runArkoala(undefined, async (control: ArkoalaControl) => {
    await waitFrames(control, 2)
    sendClick(control, 1003, 1, 10, 10)
    await waitFrames(control, 1)
    sendClick(control, 1003, 1, 10, 10)
    await waitFrames(control, 3)
    sendClick(control, 1003, 1, 10, 10)
    await waitFrames(control, 2)
    control.sendMessage("arkoala.app.exit", {})
})


