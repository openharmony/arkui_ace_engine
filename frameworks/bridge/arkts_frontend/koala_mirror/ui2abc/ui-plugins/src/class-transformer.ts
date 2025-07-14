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

import * as arkts from "@koalaui/libarkts"

import { classProperties } from "./common/arkts-utils"
import { CustomComponentNames } from "./utils"

export class ClassTransformer extends arkts.AbstractVisitor {

    constructor(options?: arkts.VisitorOptions) {
        super(options)
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isETSModule(node)) {
            const program = (node as arkts.ETSModule).program
            if (program
                && (!program.modulePrefix
                    || (!program.modulePrefix.startsWith(CustomComponentNames.COMPONENT_DEFAULT_IMPORT)
                        && !program.modulePrefix.startsWith("@koalaui")))) {
                return this.visitEachChild(node)
            }
        }
        if (arkts.isClassDeclaration(node) && !arkts.isETSStructDeclaration(node)) {
            const props = classProperties(node, propertyVerifier)
            return props.length > 0 ? this.updateClass(node, props) : node
        }
        return node
    }

    updateClass(clazz: arkts.ClassDeclaration, properties: arkts.ClassProperty[]): arkts.ClassDeclaration {
        const node = clazz.definition;
        return node
            ? arkts.factory.updateClassDeclaration(
                clazz,
                arkts.factory.updateClassDefinition(
                    node,
                    node.ident,
                    node.typeParams,
                    node.superTypeParams,
                    node.implements,
                    undefined,
                    node.super,
                    this.rewriteClassProperties(clazz, properties, node.body as arkts.ClassElement[] ?? []),
                    node.modifiers,
                    node.modifierFlags
                )
            )
            : clazz
    }

    rewriteClassProperties(clazz: arkts.ClassDeclaration, properties: arkts.ClassProperty[], body: readonly arkts.ClassElement[]): arkts.ClassElement[] {
        const result: arkts.ClassElement[] = []
        body.forEach(node => {
            if (arkts.isClassProperty(node) && propertyVerifier(node)) {
                this.rewriteProperty(node, result)
            } else if (arkts.isMethodDefinition(node) && node.isConstructor) {
                result.push(this.updateConstructor(node, properties))
            } else {
                result.push(node)
            }
        })
        return result
    }

    rewriteProperty(property: arkts.ClassProperty, result: arkts.ClassElement[]) {
        const backing = arkts.factory.createClassProperty(
            createBackingIdentifier(property),
            property.value,
            property.typeAnnotation,
            arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PRIVATE,
            false
        )
        backing.setAnnotations(property.annotations)
        result.push(backing)

        result.push(createGetterSetter(property, []))
    }

    updateConstructor(method: arkts.MethodDefinition, properties: arkts.ClassProperty[]) {
        const originalBody = method.function?.body as arkts.BlockStatement
        if (!method.function || !originalBody) {
            return method
        }

        const statements: arkts.Statement[] = []
        originalBody.statements.forEach(state => {
            if (arkts.isExpressionStatement(state)
                && arkts.isAssignmentExpression((state as arkts.ExpressionStatement).expression)) {
                statements.push(this.rewriteStatement(state, properties))
            } else {
                statements.push(state)
            }
        })

        return arkts.factory.updateMethodDefinition(
            method,
            method.kind,
            method.id,
            arkts.factory.createFunctionExpression(
                method.id,
                arkts.factory.createScriptFunction(
                    arkts.factory.createBlockStatement(statements),
                    method.function.typeParams,
                    method.function.params ?? [],
                    method.function.returnTypeAnnotation,
                    method.function.hasReceiver,
                    method.function.flags,
                    method.function.modifierFlags,
                    method.function.id,
                    method.function.annotations
                )
            ),
            method.modifierFlags,
            method.isComputed
        )
    }

    rewriteStatement(state: arkts.ExpressionStatement, properties: arkts.ClassProperty[]): arkts.ExpressionStatement {
        const expr = state.expression as arkts.AssignmentExpression
        if (arkts.isMemberExpression(expr.left)
            && arkts.isThisExpression(expr.left.object)
            && arkts.isIdentifier(expr.left.property))
        {
            const propertyName = expr.left.property.name
            const property = properties.find(it => it.id?.name == propertyName)
            if (property) {
                return arkts.factory.createExpressionStatement(
                    arkts.factory.createAssignmentExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createThisExpression(),
                            createBackingIdentifier(property),
                            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                            false,
                            false
                        ),
                        expr.right,
                        expr.operatorType
                    )
                )
            }
        }
        return state
    }
}

function propertyVerifier(property: arkts.ClassProperty): boolean {
    return arkts.hasModifierFlag(property, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC)
        && !arkts.hasModifierFlag(property, arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC)
}

function createBackingIdentifier(property: arkts.ClassProperty): arkts.Identifier {
    return arkts.factory.createIdentifier("__backing_" + property.id!.name)
}

function createGetterSetter(property: arkts.ClassProperty, setterStatements: arkts.Statement[]): arkts.MethodDefinition {
    const name = property.id!.name
    const getterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            arkts.factory.createReturnStatement(
                arkts.factory.createMemberExpression(
                    arkts.factory.createThisExpression(),
                    createBackingIdentifier(property),
                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                    false,
                    false
                )
            )
        ]),
        undefined,
        [
        ],
        property.typeAnnotation,
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_GETTER,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        []
    )

    const setterFunction = arkts.factory.createScriptFunction(
        arkts.factory.createBlockStatement([
            arkts.factory.createExpressionStatement(
                arkts.factory.createAssignmentExpression(
                    arkts.factory.createMemberExpression(
                        arkts.factory.createThisExpression(),
                        createBackingIdentifier(property),
                        arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                        false,
                        false
                    ),
                    arkts.factory.createIdentifier("value"),
                    arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_SUBSTITUTION
                )
            )
        ]),
        undefined,
        [
            arkts.factory.createETSParameterExpression(
                arkts.factory.createIdentifier("value"),
                false,
                undefined,
                property.typeAnnotation!
            )
        ],
        undefined,
        true,
        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_METHOD | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_SETTER | arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_OVERLOAD,
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        arkts.factory.createIdentifier(name),
        []
    )

    let setter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_SET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), setterFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false
    )

    let getter = arkts.factory.createMethodDefinition(
        arkts.Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_GET,
        arkts.factory.createIdentifier(name),
        arkts.factory.createFunctionExpression(arkts.factory.createIdentifier(name), getterFunction),
        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC,
        false,
        [setter]
    )
    setter.parent = getter

    return getter
}
