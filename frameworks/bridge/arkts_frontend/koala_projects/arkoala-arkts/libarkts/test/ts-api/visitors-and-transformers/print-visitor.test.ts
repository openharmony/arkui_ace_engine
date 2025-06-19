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
