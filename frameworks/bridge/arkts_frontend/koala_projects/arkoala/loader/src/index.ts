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

import { ArkoalaControl, startApplication } from "@koalaui/arkoala"
import { MyPage } from "../generated/ets/page"
import { ArkRooted } from "@koalaui/arkoala-arkui"
import { MyStack } from "../generated/ets/stack"

export { startApplication } from "@koalaui/arkoala"

export function getEntry() {
    return ArkRooted(MyStack)
}

export function getPage() {
    return MyPage
}

function sendUserClick(control: ArkoalaControl, target: number, status: number) {
    control.sendMessage("arkoala.press", {
        kind: 1, /* SinglePointerInput */
        nodeId: target,
        x: 22,
        y: 33,
        status: status
    })
}

// Note that loader case uses version from loader.js.
export function startArkoala(): Promise<ArkoalaControl> {
    return startApplication(getEntry()).then(control => {
            // Emulate input events.
            sendUserClick(control, 1004, 0) // pointer down
            sendUserClick(control, 1005, 0) // pointer down
            sendUserClick(control, 1004, 1) // pointer up
            sendUserClick(control, 1005, 1) // pointer up
            sendUserClick(control, 1012, 1) // pointer up
            return control
        })
}
