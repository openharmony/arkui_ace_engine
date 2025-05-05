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

import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"

function createConfig() {
    arkts.arktsGlobal.config = arkts.Config.create([
        '_',
        '--arktsconfig',
        'arktsconfig.json',
        './plugins/input/main.ets',
        '--extension',
        'ets',
        '--stdlib',
        '../../incremental/tools/panda/node_modules/@panda/sdk/ets/stdlib',
        '--output',
        './build/main.abc'
    ]).peer
}

function updateTopLevelClass(
    module: arkts.ETSModule,
    className: string,
    update: (node: arkts.ClassDefinition) => arkts.ClassDefinition
) {
    return arkts.updateETSModuleByStatements(
        module, 
        [
            ...module.statements.map((node) => {
                if (!arkts.isClassDeclaration(node)) {
                    return node
                }
                if (!arkts.isClassDefinition(node.definition)) {
                    return node
                }
                if (node.definition.ident?.name == className) {
                    return arkts.factory.updateClassDeclaration(
                        node,
                        update(node.definition)
                    )
                }
                return node
            })
        ]
    )
}

suite(util.basename(__filename), () => {

    test("static (function)", function() {
        createConfig()
        
        const code =
        `
        function foo() {}
        `

        arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        arkts.recheckSubtree(arkts.createETSModuleFromContext())

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })

    test.skip("static (property)", function() {
        createConfig()
        
        const code =
        `
        interface I {
            prop: boolean
        }

        class C implements I {
            prop = true
        }
        `

        arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        arkts.recheckSubtree(arkts.createETSModuleFromContext())

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })

    test("rename class", function() {
        createConfig()
        
        const code =
        `
        class C {
            f(): void {
            }
        }
        `

        arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        const module = arkts.createETSModuleFromContext()

        updateTopLevelClass(module, "C", (node: arkts.ClassDefinition) => {
            return arkts.factory.updateClassDefinition(
                node,
                node.ident ? arkts.factory.updateIdentifier(
                    node.ident,
                    "D"
                ) : undefined,
                node.typeParams,
                node.superTypeParams,
                node.implements,
                undefined,
                node.super,
                node.body,
                node.modifiers,
                node.modifierFlags
            )
        })

        arkts.arktsGlobal.es2panda._AstNodeUpdateAll(arkts.arktsGlobal.context, module.peer)
        arkts.recheckSubtree(module)

        util.assert(
            module.dumpSrc() == `
function main() {}



class D {
  public f(): void {}
  
  public constructor() {}
  
}

`,
        `invalid result: ${module.dumpSrc()}`)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })

    test("add class method", function() {
        createConfig()
        
        const code =
        `
        class C {
        }
        `

        arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        const module = arkts.createETSModuleFromContext()

        updateTopLevelClass(module, "C", (node: arkts.ClassDefinition) => {
            return arkts.factory.updateClassDefinition(
                node,
                node.ident,
                node.typeParams,
                node.superTypeParams,
                node.implements,
                undefined,
                node.super,
                [
                    arkts.factory.createMethodDefinition(
                        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_METHOD,
                        arkts.factory.createIdentifier("g"),
                        arkts.factory.createFunctionExpression(
                            arkts.factory.createIdentifier("g"),
                            arkts.factory.createScriptFunction(
                                arkts.factory.createBlockStatement([
                                    arkts.factory.createReturnStatement(
                                        arkts.factory.createNumberLiteral(5)
                                    )
                                ]),
                                undefined,
                                [],
                                arkts.factory.createETSPrimitiveType(
                                    arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_DOUBLE,
                                ),
                                false,
                                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD,
                                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
                                arkts.factory.createIdentifier("g"),
                                undefined,
                            )
                        ),
                        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
                        false,
                    ),
                    ...node.body,
                ],
                node.modifiers,
                node.modifierFlags
            )
        })

        arkts.arktsGlobal.es2panda._AstNodeUpdateAll(arkts.arktsGlobal.context, module.peer)
        arkts.recheckSubtree(module)

        util.assert(
            module.dumpSrc() == `
function main() {}



class C {
  public g(): double {
    return 5;
  }
  
  public constructor() {}
  
}

`,
        `invalid result: ${module.dumpSrc()}`)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })

    test("add variable declaration", function() {
        createConfig()
        
        const code =
        `
        class C {
            f(): void {
            }
        }
        `

        arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        const module = arkts.createETSModuleFromContext()

        updateTopLevelClass(module, "C", (node: arkts.ClassDefinition) => {
            return arkts.factory.updateClassDefinition(
                node,
                node.ident,
                node.typeParams,
                node.superTypeParams,
                node.implements,
                undefined,
                node.super,
                [
                    ...node.body.map((node: arkts.AstNode) => {
                        if (!arkts.isMethodDefinition(node)) {
                            return node
                        }
                        if (node.id?.name != "f") {
                            return node
                        }
                        if (!arkts.isFunctionExpression(node.value)) {
                            return node
                        }
                        const func = node.value.function
                        if (!func || !arkts.isBlockStatement(func.body)) {
                            return node
                        }
                        return arkts.factory.updateMethodDefinition(
                            node,
                            node.kind,
                            node.key,
                            arkts.factory.updateFunctionExpression(
                                node.value,
                                node.id,
                                arkts.factory.updateScriptFunction(
                                    func,
                                    arkts.factory.updateBlockStatement(
                                        func.body,
                                        [
                                            arkts.factory.createVariableDeclaration(
                                                arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_CONST,
                                                [
                                                    arkts.factory.createVariableDeclarator(
                                                        arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_CONST,
                                                        arkts.factory.createIdentifier("x"),
                                                        arkts.factory.createBinaryExpression(
                                                            arkts.factory.createNumberLiteral(1),
                                                            arkts.factory.createNumberLiteral(4),
                                                            arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_PLUS,
                                                        ),
                                                    ),
                                                ],
                                            ),
                                            ...func.body.statements,
                                        ],
                                    ),
                                    func.typeParams,
                                    func.params,
                                    func.returnTypeAnnotation,
                                    func.hasReceiver,
                                    func.flags,
                                    func.modifierFlags,
                                    func.id,
                                    func.annotations,
                                ),
                            ),
                            node.modifierFlags,
                            node.isComputed,
                            node.overloads,
                        )
                    })
                ],
                node.modifiers,
                node.modifierFlags
            )
        })

        arkts.arktsGlobal.es2panda._AstNodeUpdateAll(arkts.arktsGlobal.context, module.peer)
        arkts.recheckSubtree(module)

        util.assert(
            module.dumpSrc() == `
function main() {}



class C {
  public f(): void {
    const x = ((1) + (4));
  }
  
  public constructor() {}
  
}

`,
        `invalid result: ${module.dumpSrc()}`)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })
})
