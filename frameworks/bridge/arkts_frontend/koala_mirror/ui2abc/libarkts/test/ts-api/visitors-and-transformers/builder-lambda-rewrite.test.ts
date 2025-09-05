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

// import * as util from "../../test-util"
// import * as ts from "../../../src/ts-api"
// import { factory } from "../../../src/ts-api"
// import { BuilderLambdaTransformer } from "../../../plugins/src/builder-lambda-transformer"
//
// suite.skip(util.getSuiteTitle(__filename), () => {
//     test("builder-lambda-transformer-sample-1", function() {
//         // foo((instance: string) => {
//         //     return instance;
//         // }, "label");
//
//         const sample_in =
//         `
//         _BuilderLambdaCall_foo("label")
//         `
//
//         let sourceFile = factory.createSourceFile(sample_in)
//         util.assert(ts.isSourceFile(sourceFile))
//
//         const builderLambdaTransformer = new BuilderLambdaTransformer()
//
//         const result = builderLambdaTransformer.visitor(sourceFile)
//         util.assert(ts.isSourceFile(result))
//
//         util.TS_TEST_ASSERTION(
//             result,
//             `
//             foo(((instance: string) => {
//                 return instance;
//             }), "label")
//             `,
//             ts.ContextState.ES2PANDA_STATE_PARSED,
//         )
//     })
//
//     test("builder-lambda-transformer-sample-2", function() {
//         // foo((instance: string) => {
//         //     return instance.bar().qux();
//         // }, "label1", "label2");
//
//         const sample_in =
//         `
//         _BuilderLambdaCall_foo("label1", "label2").bar().qux()
//         `
//
//         let sourceFile = factory.createSourceFile(sample_in)
//         util.assert(ts.isSourceFile(sourceFile))
//
//         const builderLambdaTransformer = new BuilderLambdaTransformer()
//
//         const result = builderLambdaTransformer.visitor(sourceFile)
//         util.assert(ts.isSourceFile(result))
//
//         util.TS_TEST_ASSERTION(
//             result,
//             `
//             foo(((instance: string) => {
//                 return instance.bar().qux();
//             }), "label1", "label2")
//             `,
//             ts.ContextState.ES2PANDA_STATE_PARSED,
//         )
//     })
//
//     // Improve: update nodes properly (now failing to generate bin)
//     test("builder-lambda-transformer-sample-3", function() {
//         // function Foo(builder: (instance: string) => string, arg1: string): void {
//         //     console.log(arg1 + builder("ABC"))
//         // }
//         // Foo((instance: string) => {
//         //     return instance.charAt(1)
//         // }, "> second_char_of_ABC: ")
//
//         const sample_in =
//         `
//         function Foo(builder: (instance: string) => string, arg1: string): void {
//             console.log(arg1 + builder("ABC"))
//         }
//
//         _BuilderLambdaCall_Foo("> second_char_of_ABC: ").charAt(1)
//         `
//
//         let sourceFile = factory.createSourceFile(sample_in)
//         util.assert(ts.isSourceFile(sourceFile))
//
//         const builderLambdaTransformer = new BuilderLambdaTransformer()
//
//         const result = builderLambdaTransformer.visitor(sourceFile)
//         util.assert(ts.isSourceFile(result))
//
//         util.TS_TEST_ASSERTION(
//             result,
//             `
//             function Foo(builder: ((instance: string)=> string), arg1: string): void {
//                 console.log(((arg1) + (builder("ABC"))));
//             }
//
//             Foo(((instance: string) => {
//                 return instance.charAt(1);
//             }), "> second_char_of_ABC: ")
//             `,
//             ts.ContextState.ES2PANDA_STATE_PARSED,
//         )
//     })
// })
