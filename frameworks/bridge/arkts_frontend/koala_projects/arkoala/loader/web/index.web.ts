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
import { startApplication } from "@koalaui/arkoala"
import { __Entry } from "../generated/ets/example_custom_component"
import "./NativeHeap"
import { NativeModuleWeb } from "./NativeModuleWeb"

// todo: fix me
export declare const document: any
export declare const name: any
export type HTMLElement = any
export type HTMLDivElement = any

export function startArkoalaWeb(rootId: string) {
    return startApplication(ArkRooted(__Entry), {
        waitForVSync: () => new Promise((resolve) => setTimeout(resolve, 1)),
        arkUINativeModule: new NativeModuleWeb(document.getElementById(rootId)!)
    })
}
