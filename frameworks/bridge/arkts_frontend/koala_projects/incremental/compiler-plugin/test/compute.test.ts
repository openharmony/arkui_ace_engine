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

import { checkDump } from "./util.test"

suite("Compute", () => {

    /** @memo */
    test("Compute AsExpression", () => {
        class ArkFlexComponent {}
        interface FlexOptions {}
        /** @memo */
        function ArkFlex(
            /** @memo */
            style: ((attributes: ArkFlexComponent) => void) | undefined,
            /** @memo */
            content_: (() => void) | undefined,
            value?: FlexOptions | undefined
        ) {}

        /** @memo */
        function usage() {
            ArkFlex((instance: ArkFlexComponent) => {
            }, () => {
            }, { } as FlexOptions)
        }
    })

    checkDump("usage", "compute")
})
