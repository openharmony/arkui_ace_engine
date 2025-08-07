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

import { registerPageByNameFunction } from "./TestHarness"
import { StateChangePage } from "./pages/StateChangePage"

@memo
function pageByName(name: string): void {
    switch (name) {
        case "StateChangePage": StateChangePage(); break
        case "": break
        default: throw new Error(`No test case ${name} provided!`)
    }
}

export function initPages() {
    registerPageByNameFunction(pageByName)
}