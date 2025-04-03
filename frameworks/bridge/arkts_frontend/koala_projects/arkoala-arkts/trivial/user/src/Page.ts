/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { Page1 } from "app/page1"
import { Page2 } from "app/page2"
import { UserView, UserViewBuilder } from "@koalaui/arkts-arkui"
import { benchmark } from "./Perf"

export class ComExampleTrivialApplication extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        console.log(`getBuilder() ComExampleTrivialApplication`)
        /** @memo */
        let wrapper = () => {
            Page1()
        }
        return wrapper
    }
}


export class ComExampleTrivialApplicationPage2 extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        console.log(`getBuilder() ComExampleTrivialApplicationPage2`)
        /** @memo */
        let wrapper = () => {
            Page2()
        }
        return wrapper
    }
}


export class ComExampleTrivialApplicationPerf extends UserView {
    private params: String
    constructor(params: String) {
        super()
        this.params = params
    }
    getBuilder(): UserViewBuilder {
        benchmark()
        /** @memo */
        let wrapper = () => {
        }
        return wrapper
    }
}
