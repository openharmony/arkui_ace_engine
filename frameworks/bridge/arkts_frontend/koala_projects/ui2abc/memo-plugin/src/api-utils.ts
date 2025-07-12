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

import * as arkts from "@koalaui/libarkts"
import { getDeclResolveGensym, getMemoFunctionKind, MemoFunctionKind } from "./utils"

/**
 * Type of node which can be returned by getDecl and correspond to node which can have memo annotation
 *
 * @see getDecl
 * @see getDeclResolveGensym
 * @see MemoAnnotatable
 */
export type Memoizable =
      arkts.MethodDefinition
    | arkts.ETSParameterExpression
    | arkts.Identifier
    | arkts.ClassProperty

/**
 * Type of expression node which can have functional memo annotation
 */
export type MemoAnnotatableExpression =
      arkts.ScriptFunction
    | arkts.ArrowFunctionExpression
    | arkts.ETSParameterExpression
    | arkts.VariableDeclaration
    | arkts.ClassProperty
    | arkts.TSTypeAliasDeclaration

/**
 * Type of type node which can have functonal memo annotation
 */
export type MemoAnnotatableType =
      arkts.ETSFunctionType
    | arkts.ETSUnionType

/**
 * Type of node which can have functional memo annotation
 */
export type MemoAnnotatable = MemoAnnotatableExpression | MemoAnnotatableType

/**
 * Type of node which can have @memo_stable annotation
 */
export type MemoStableAnnotatable = arkts.ClassDefinition

/**
 * Type of node which can have @memo_skip annotation
 */
export type MemoSkipAnnotatable = arkts.ETSParameterExpression

export function isMemoizable(node: arkts.AstNode | undefined): node is Memoizable {
    return arkts.isMethodDefinition(node)
        || arkts.isETSParameterExpression(node)
        || arkts.isIdentifier(node)
        || arkts.isClassProperty(node)
}

export function isMemoAnnotatableExpression(node: arkts.AstNode | undefined): node is MemoAnnotatableExpression {
    return arkts.isScriptFunction(node)
        || arkts.isETSParameterExpression(node)
        || arkts.isArrowFunctionExpression(node)
        || arkts.isVariableDeclaration(node)
        || arkts.isClassProperty(node)
        || arkts.isTSTypeAliasDeclaration(node)
}

export function isMemoAnnotatableType(node: arkts.AstNode | undefined): node is MemoAnnotatableType {
    return arkts.isETSFunctionType(node) || arkts.isETSUnionType(node)
}

export function isMemoAnnotatable(node: arkts.AstNode | undefined): node is MemoAnnotatable {
    return isMemoAnnotatableExpression(node) || isMemoAnnotatableType(node)
}

export function getName(node: Memoizable): string {
    if (arkts.isMethodDefinition(node)) {
        return node.id!.name
    }
    if (arkts.isETSParameterExpression(node)) {
        return node.ident!.name
    }
    if (arkts.isIdentifier(node)) {
        return node.name
    }
    if (arkts.isClassProperty(node)) {
        return node.id!.name
    }
    assertIsNever(node)
}

// TODO: this should use info from AnalysisVisitor, not obtain it from the node
// but this require AnalysisVisitor to be run on all sources
export function isMemo(node: Memoizable) {
    if (arkts.isMethodDefinition(node)) {
        const kind = getMemoFunctionKind(node.function!)
        if (kind == MemoFunctionKind.MEMO || kind == MemoFunctionKind.INTRINSIC) {
            return true
        }
    }
    if (arkts.isETSParameterExpression(node)) {
        const kind = getMemoFunctionKind(node)
        if (kind == MemoFunctionKind.MEMO || kind == MemoFunctionKind.INTRINSIC) {
            return true
        }
        if (arkts.isETSTypeReference(node.typeAnnotation)) {
            const name = node.typeAnnotation.part?.name
            if (name) {
                const decl = getDeclResolveGensym(name)
                if (arkts.isTSTypeAliasDeclaration(decl)) {
                    const kind = isMemoAnnotatableType(decl.typeAnnotation) && getMemoFunctionKind(decl.typeAnnotation)
                    if (kind == MemoFunctionKind.MEMO || kind == MemoFunctionKind.INTRINSIC) {
                        return true
                    }
                    const kind2 = getMemoFunctionKind(decl)
                    if (kind2 == MemoFunctionKind.MEMO || kind2 == MemoFunctionKind.INTRINSIC) {
                        return true
                    }
                }
            }
        }
    }
    if (arkts.isIdentifier(node)) {
        if (arkts.isVariableDeclarator(node.parent) && arkts.isArrowFunctionExpression(node.parent.init)) {
            const kind = getMemoFunctionKind(node.parent.init)
            if (kind == MemoFunctionKind.MEMO || kind == MemoFunctionKind.INTRINSIC) {
                return true
            }
        }
        if (arkts.isVariableDeclarator(node.parent) && arkts.isVariableDeclaration(node.parent.parent)) {
            const kind = getMemoFunctionKind(node.parent.parent)
            if (kind == MemoFunctionKind.MEMO || kind == MemoFunctionKind.INTRINSIC) {
                return true
            }
        }
    }
    if (arkts.isClassProperty(node)) {
        const kind = getMemoFunctionKind(node)
        if (kind == MemoFunctionKind.MEMO || kind == MemoFunctionKind.INTRINSIC) {
            return true
        }
    }
    return false
}

/**
 * es2panda API is weird here
 *
 * @deprecated
 */
export function castParameters(params: readonly arkts.Expression[]): readonly arkts.ETSParameterExpression[] {
    return params as readonly arkts.ETSParameterExpression[]
}

export function correctObjectExpression(node: arkts.AstNode | undefined): boolean {
    return arkts.isObjectExpression(node) || (arkts.isTSAsExpression(node) && correctObjectExpression(node.expr))
}

export function correctFunctionParamType(arg: arkts.Expression): boolean {
    return arkts.isArrowFunctionExpression(arg)
}

function assertIsNever(isNever: never): never {
    throw new Error("Unreachable")
}

/**
 * This function is used to check whether some parameters of decl call should be rewritten
 *
 * For expressions that cannot accept @memo parameters it returns []
 */
export function getParams(decl: Memoizable) {
    if (arkts.isMethodDefinition(decl)) {
        return castParameters(decl.function!.params)
    }
    if (arkts.isETSParameterExpression(decl)) {
        if (arkts.isETSFunctionType(decl.typeAnnotation)) {
            return castParameters(decl.typeAnnotation.params)
        }
        if (arkts.isETSUnionType(decl.typeAnnotation)) {
            const nonUndefined: arkts.TypeNode[] = decl.typeAnnotation.types.filter((it) => {
                return !arkts.isETSUndefinedType(it)
            })
            if (nonUndefined.length != 1) {
                return []
            }
            if (arkts.isETSFunctionType(nonUndefined[0])) {
                return castParameters(nonUndefined[0].params)
            }
            return []
        }
        return []
    }
    if (arkts.isIdentifier(decl)) {
        if (arkts.isVariableDeclarator(decl.parent) && arkts.isArrowFunctionExpression(decl.parent.init)) {
            return castParameters(decl.parent.init.function!.params)
        }
        return []
    }
    if (arkts.isClassProperty(decl)) {
        if (arkts.isArrowFunctionExpression(decl.value)) {
            return castParameters(decl.value.function!.params)
        }
        return []
    }
    assertIsNever(decl)
}

function isThisParam(node: arkts.Expression | undefined): boolean {
    if (node === undefined || !arkts.isETSParameterExpression(node)) {
        return false
    }
    return node.ident?.isReceiver ?? false
}

export function parametersBlockHasReceiver(params: readonly arkts.Expression[]): boolean {
    return params.length > 0 && arkts.isETSParameterExpression(params[0]) && isThisParam(params[0])
}

export function parametrizedNodeHasReceiver(node: arkts.ScriptFunction | arkts.ETSFunctionType | undefined): boolean {
    if (node === undefined) {
        return false
    }
    return parametersBlockHasReceiver(node.params)
}

export function memoizableHasReceiver(node: Memoizable): boolean {
    if (arkts.isMethodDefinition(node)) {
        return parametrizedNodeHasReceiver(node.function)
    }
    if (arkts.isETSParameterExpression(node)) {
        if (arkts.isETSFunctionType(node.typeAnnotation)) {
            return isThisParam(node.typeAnnotation.params[0])
        }
        return false
    }
    if (arkts.isIdentifier(node)) {
        if (arkts.isVariableDeclarator(node.parent) && arkts.isArrowFunctionExpression(node.parent.init)) {
            return isThisParam(node.parent.init.function!.params[0])
        }
        return false
    }
    if (arkts.isClassProperty(node)) {
        if (arkts.isArrowFunctionExpression(node.value)) {
            return isThisParam(node.value.function!.params[0])
        }
        return false
    }
    assertIsNever(node)
}
