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

import { AppControl } from "../TestHarness"
import { Assert, suite, test } from "@koalaui/harness"

export function suiteStateChange(control: AppControl) {
    suite("StateChange", () => {
        test("StateChangePage", () => {
            control.loadPage("StateChangePage")
            await control.skipFrames(3)

            // increment
            control.notifyClick("inc")
            control.notifyClick("inc")
            await control.nextFrame()
            let result = control.snapshot("root", "StateChange_inc")
            Assert.isTrue(result)

            // decrement
            control.notifyClick("dec")
            control.notifyClick("dec")
            await control.nextFrame()
            result = control.snapshot("root", "StateChange_dec")
            Assert.isTrue(result)
        })
    })
}
