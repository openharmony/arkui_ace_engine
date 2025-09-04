/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import * as fs from "node:fs"
import * as child_process from "node:child_process"
import * as path from "node:path"
import { Assert, suite, test } from "@koalaui/harness"

function makeFilesEqual(filePath: string) {
    const out = fs.readFileSync(`./out/${filePath}.ets`, 'utf-8')
    fs.mkdirSync(path.dirname(`./golden/${filePath}`), { recursive: true })
    fs.writeFileSync(`./golden/${filePath}.ets`, out)
}

function filterGensym(value: string): string {
    return value.replaceAll(/gensym%%_[0-9]*/g, "gensym_XXX")
}

function assertFilesEqual(filePath: string) {
    const golden = fs.readFileSync(`./golden/${filePath}.ets`, 'utf-8')
    const out = fs.readFileSync(`./out/${filePath}.ets`, 'utf-8')
    Assert.equal(filterGensym(out), filterGensym(golden))
}

function testBody(path: string) {
    if (process.env.TEST_GOLDEN == "1") {
        makeFilesEqual(path)
    } else {
        assertFilesEqual(path)
    }
}

suite("golden tests", () => {

    test.expectFailure("Description of the problem", "compile", () => {
        child_process.execSync("rm -rf ../build/golden", { stdio: "inherit" })
        child_process.execSync("rm -rf out", { stdio: "inherit" })
        child_process.execSync("npx fast-arktsc --config ./input/arktsconfig.json --compiler ../../../incremental/tools/panda/arkts/ui2abc --link-name ../build/golden/all.abc && ninja -f ../build/golden/build.ninja -k 1000", { stdio: "inherit" })
    })

    suite("basic", () => {
        test("function", () => {
            testBody("basic/function")
        })

        test("method", () => {
            testBody("basic/method")
        })

        test("arrow", () => {
            testBody("basic/arrow")
        })
    })

    suite("HQ", () => {
        test.skip("memo class property implemented from interface", () => {
            testBody("HQ/implemented-property")
        })

        test("memo class method with memo argument with void return type", () => {
            testBody("HQ/void-compute")
        })

        test("memo class method with memo argument with argument with void return type", () => {
            testBody("HQ/string-compute")
        })

        test("memo class method with memo argument with void return type and call the memo argument within the method", () => {
            testBody("HQ/content-usage")
        })

        test("memo class method with memo argument with void return type (for `compute` function)", () => {
            testBody("HQ/compute")
        })

        test("callable class with memo $_invoke", () => {
            testBody("HQ/invoke")
        })

        test("callable class with non-memo $_invoke with memo argument", () => {
            testBody("HQ/invoke-param")
        })

        test("callable class with $_instantiate with memo argument", () => {
            testBody("HQ/instantiate")
        })

        test("declared abstract class with memo method with argument", () => {
            testBody("HQ/abstract")
        })

        test("memo class method with internal call", () => {
            testBody("HQ/internal-call")
        })

        test("memo class method with internal __context() and __id()", () => {
            testBody("HQ/internals")
        })

        test("class method with internal memo lambda", () => {
            testBody("HQ/arrow")
        })

        test("memo class method with internal variables assigned to memo lambda", () => {
            testBody("HQ/arrow-assignment")
        })

        test("memo class method with internal function calls that has default value in parameter", () => {
            testBody("HQ/param-calls")
        })

        test("memo class method with internal function calls that is optional parameter", () => {
            testBody("HQ/param-calls-optional")
        })

        test("memo class method with internal argument call with reffered memo type", () => {
            testBody("HQ/call-type")
        })

        test("memo class method with void return type", () => {
            testBody("HQ/void-method")
        })

        test("memo class method with non-void return type", () => {
            testBody("HQ/string-method")
        })

        test("memo class method with type parameter", () => {
            testBody("HQ/type-param-method")
        })

        test("memo class method with @memo_intrinsic", () => {
            testBody("HQ/intrinsic")
        })

        test("memo class method with @memo_intrinsic and internal call memo method", () => {
            testBody("HQ/intrinsic-call")
        })

        test("memo class method with @memo_entry", () => {
            testBody("HQ/entry")
        })

        test("memo class method with implicit return type", () => {
            testBody("HQ/implicit-void-method")
        })

        test("memo class method with parameter with void return type", () => {
            testBody("HQ/void-method-with-param")
        })

        test("memo class method with return in function body with void return type", () => {
            testBody("HQ/void-method-with-return")
        })

        test("memo static class method with void return type", () => {
            testBody("HQ/static-void-method")
        })

        test("memo class method with object parameter with void return type", () => {
            testBody("HQ/object-param")
        })

        test("class constructor has parameter that is referred to a defined interface with memo property", () => {
            testBody("HQ/property-constructor")
        })

        test("non memo class property", () => {
            testBody("HQ/non-memo-property")
        })

        test("memo class property", () => {
            testBody("HQ/memo-property")
        })

        test("optional memo class property", () => {
            testBody("HQ/memo-property-optional")
        })

        test("union memo class property with default value", () => {
            testBody("HQ/memo-property-union-type")
        })

        test("class property with memo type", () => {
            testBody("HQ/memo-property-type")
        })

        test("non-memo interface property", () => {
            testBody("HQ/non-memo-interface-property")
        })

        test("memo interface property", () => {
            testBody("HQ/memo-interface-property")
        })

        test("optional memo interface property", () => {
            testBody("HQ/memo-interface-property-optional")
        })

        test("memo interface property with union type", () => {
            testBody("HQ/memo-interface-property-union-type")
        })

        test("interface property with memo type", () => {
            testBody("HQ/memo-interface-property-type")
        })
    })
})
