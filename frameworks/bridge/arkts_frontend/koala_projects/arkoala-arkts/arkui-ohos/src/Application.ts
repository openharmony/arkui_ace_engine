/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { InteropNativeModule, pointer, registerNativeModuleLibraryName } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { ArkUINativeModule } from "#components"

export type UserViewBuilder =
/** @memo */
(/*root: PeerNode*/) => void

/** @memo */
function rootView(): void {
    console.log("Root")
}

export class UserView {
    constructor(param: string) {
        console.log(`UserView: ${param}`)
    }
    getBuilder(): UserViewBuilder {
        return rootView
    }
}

export class Application {
    constructor(userView: UserView, useNativeLog: boolean) {
        console.log("Create app")
    }

    start(): pointer {
        console.log("start")
        return InteropNativeModule._GetStringFinalizer()
    }
    enter(arg0: int32, arg1: int32, foreignContext: pointer): boolean {
        return true
    }
    static createApplication(appUrl: string, params: string, useNativeLog: boolean): Application {
        registerNativeModuleLibraryName("InteropNativeModule", "ArkoalaNative_ani")
        registerNativeModuleLibraryName("ArkUINativeModule", "ArkoalaNative_ani")
        registerNativeModuleLibraryName("ArkUIGeneratedNativeModule", "ArkoalaNative_ani")
        registerNativeModuleLibraryName("TestNativeModule", "ArkoalaNative_ani")
        const userView = ArkUINativeModule._LoadUserView(appUrl, params)
        if (userView == undefined) throw new Error("Cannot load user view");
        return new Application(userView as UserView, useNativeLog)
    }
    emitEvent(type: int32, target: int32, arg0: int32, arg1: int32): string {
        return "0"
    }
}
