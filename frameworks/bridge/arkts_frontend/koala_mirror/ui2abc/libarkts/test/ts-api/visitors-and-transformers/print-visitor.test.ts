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

// import * as ts from "../../../src/ts-api"
// import * as util from "../../test-util"
// import { PrintVisitor } from "../../../plugins/src/print-visitor"
//
// suite.skip(util.getSuiteTitle(__filename), () => {
//     test("sample-1", function() {
//         const source =
//         `
//         class Base {
//             public a: int = 1;
//             public method() {
//                 this.a = 2;
//             }
//         }
//         class Derived extends Base {}
//         function foo() {
//         }
//         function goo() {
//         }
//         function main(): void {
//             let derived: Base = new Derived();
//             derived.method();
//         }
//         `
//         const expected =
//         `
//         SourceFile (mods: [])
//             ClassDeclaration (mods: [1,4])
//                 Identifier (mods: [])
//                 PropertyDeclaration (mods: [4])
//                 MethodDeclaration (mods: [4])
//                     Identifier (mods: [])
//                     Block (mods: [])
//                         ExpressionStatement (mods: [])
//                             AssignmentExpression (mods: [])
//                 MethodDeclaration (mods: [])
//                     Identifier (mods: [])
//                     Block (mods: [])
//             ClassDeclaration (mods: [1,4])
//                 Identifier (mods: [])
//                 MethodDeclaration (mods: [])
//                     Identifier (mods: [])
//                     Block (mods: [])
//             FunctionDeclaration (mods: [1,4])
//                 Identifier (mods: [])
//                 Block (mods: [])
//             FunctionDeclaration (mods: [1,4])
//                 Identifier (mods: [])
//                 Block (mods: [])
//             FunctionDeclaration (mods: [1,4])
//                 Identifier (mods: [])
//                 ETSPrimitiveType (mods: [])
//                 Block (mods: [])
//                     VariableStatement (mods: [])
//                         VariableDeclarationList (mods: [])
//                             VariableDeclaration (mods: [])
//                     ExpressionStatement (mods: [])
//                         CallExpression (mods: [])
//                             PropertyAccessExpression (mods: [])
//                                 Identifier (mods: [])
//                                 Identifier (mods: [])
//         `
//         let sourceFile = ts.factory.createSourceFile(source)
//         const output = (new PrintVisitor()).astToString(sourceFile)
//
//         util.assert.equal(util.alignText(output), util.alignText(expected))
//     })
// })
