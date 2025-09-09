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
 
import * as arkts from "../../../../../src/arkts-api"

export function addUseImportClassSameFile(program: arkts.Program, options: arkts.CompilationOptions) {
    if (options.isMainProgram) {
        const module = program.ast as arkts.ETSModule
        program.setAst(
            arkts.factory.updateETSModule(
                module,
                [
                    // import { C as C } from "./library"
                    arkts.factory.createETSImportDeclaration(
                        arkts.factory.createStringLiteral(
                            './library'
                        ),
                        [
                            arkts.factory.createImportSpecifier(
                                arkts.factory.createIdentifier(
                                    'C'
                                ),
                                arkts.factory.createIdentifier(
                                    'C'
                                )
                            )
                        ],
                        arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL
                    ),
                    ...module.statements,
                    // class D {
                    //     c = new C()
                    // }
                    arkts.factory.createClassDeclaration(
                        arkts.factory.createClassDefinition(
                            arkts.factory.createIdentifier("D"),
                            undefined,
                            undefined,
                            [],
                            undefined,
                            undefined,
                            [
                                arkts.factory.createClassProperty(
                                    arkts.factory.createIdentifier("c"),
                                    arkts.factory.createETSNewClassInstanceExpression(
                                        arkts.factory.createETSTypeReference(
                                            arkts.factory.createETSTypeReferencePart(
                                                arkts.factory.createIdentifier("C")
                                            )
                                        ),
                                        []
                                    ),
                                    undefined,
                                    arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                                    false,
                                )
                            ],
                            arkts.Es2pandaClassDefinitionModifiers.CLASS_DEFINITION_MODIFIERS_CLASS_DECL,
                            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_NONE,
                        )
                    )
                ],
                module.ident,
                module.getNamespaceFlag(),
                module.program,
            )
        )
    }
    return program
}
