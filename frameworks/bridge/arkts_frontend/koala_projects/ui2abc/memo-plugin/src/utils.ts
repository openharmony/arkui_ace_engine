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

import { UniqueId } from "@koalaui/common"
import * as arkts from "@koalaui/libarkts"
import * as fs from "node:fs"
import * as path from "node:path"
import { correctFunctionParamType, correctObjectExpression, MemoAnnotatable, MemoSkipAnnotatable, MemoStableAnnotatable } from "./api-utils"

export enum RuntimeNames {
    __CONTEXT = "__context",
    __ID = "__id",
    __KEY = "__key",
    ANNOTATION = "memo",
    ANNOTATION_ENTRY = "memo_entry",
    ANNOTATION_INTRINSIC = "memo_intrinsic",
    ANNOTATION_SKIP = "memo_skip",
    ANNOTATION_STABLE = "memo_stable",
    COMPUTE = "compute",
    CONTENT = "content",
    CONTEXT = "__memo_context",
    CONTEXT_TYPE = "__memo_context_type",
    CONTEXT_TYPE_DEFAULT_IMPORT = "@koalaui/runtime",
    GENSYM = "gensym%%_",
    HASH = "__hash",
    ID = "__memo_id",
    ID_TYPE = "__memo_id_type",
    INTERNAL_PARAMETER_STATE = "param",
    INTERNAL_SCOPE = "scope",
    INTERNAL_VALUE = "cached",
    INTERNAL_VALUE_NEW = "recache",
    INTERNAL_VALUE_OK = "unchanged",
    PARAMETER = "__memo_parameter",
    SCOPE = "__memo_scope",
    THIS = "this",
    VALUE = "value",
}

export enum DebugNames {
    BANNER_PARAMETER = "[MEMO PARAMETER DEBUG]",
    BANNER_UNCHANGED = "[MEMO UNCHANGED DEBUG]",
    CONSOLE = "console",
    LOG = "log",
}

function baseName(path: string): string {
    return path.replace(/^.*\/(.*)$/, "$1")
}

export class PositionalIdTracker {
    // Global for the whole program.
    static callCount: number = 0

    // Set `stable` to true if you want to have more predictable values.
    // For example for tests.
    // Don't use it in production!
    constructor(public filename: string, public stableForTests: boolean = false) {
        if (stableForTests) PositionalIdTracker.callCount = 0
    }

    sha1Id(callName: string, fileName: string): string {
        const uniqId = new UniqueId()
        uniqId.addString("memo call uniqid")
        uniqId.addString(fileName)
        uniqId.addString(callName)
        uniqId.addI32(PositionalIdTracker.callCount++)
        return uniqId.compute().substring(0, 7)
    }

    stringId(callName: string, fileName: string): string {
        if (this.stableForTests) {
            return `id_${callName}_${fileName}`
        }
        return `${PositionalIdTracker.callCount++}_${callName}_${fileName}`
    }

    id(callName: string = ""): arkts.Expression {

        const fileName = this.stableForTests ?
            baseName(this.filename) :
            this.filename

        const positionId = (this.stableForTests) ?
            this.stringId(callName, fileName) :
            this.sha1Id(callName, fileName)


        return this.stableForTests
            ? arkts.factory.createCallExpression(
                arkts.factory.createIdentifier(RuntimeNames.HASH),
                [arkts.factory.createStringLiteral(positionId)],
                undefined,
                false,
                false,
                undefined
            )
            : arkts.factory.createNumberLiteral(parseInt(positionId, 16))
    }
}

export enum MemoFunctionKind {
    NONE = 0,
    MEMO = 1,
    INTRINSIC = 2,
    ENTRY = 4,
}

function hasMemoAnnotation(node: MemoAnnotatable) {
    return node.annotations.some((it) =>
        it.expr !== undefined && arkts.isIdentifier(it.expr) && it.expr.name === RuntimeNames.ANNOTATION
    )
}

function hasMemoEntryAnnotation(node: MemoAnnotatable) {
    return node.annotations.some((it) =>
        it.expr !== undefined && arkts.isIdentifier(it.expr) && it.expr.name === RuntimeNames.ANNOTATION_ENTRY
    )
}

function hasMemoIntrinsicAnnotation(node: MemoAnnotatable) {
    return node.annotations.some((it) =>
        it.expr !== undefined && arkts.isIdentifier(it.expr) && it.expr.name === RuntimeNames.ANNOTATION_INTRINSIC
    )
}

function hasMemoSkipAnnotation(node: MemoSkipAnnotatable) {
    return node.annotations.some((it) =>
        it.expr !== undefined && arkts.isIdentifier(it.expr) && it.expr.name === RuntimeNames.ANNOTATION_SKIP
    )
}

export function hasMemoStableAnnotation(node: MemoStableAnnotatable) {
    return node.annotations.some((it) =>
        it.expr !== undefined && arkts.isIdentifier(it.expr) && it.expr.name === RuntimeNames.ANNOTATION_STABLE
    )
}

export function getMemoFunctionKind(node: MemoAnnotatable): MemoFunctionKind {
    const mask = (+hasMemoEntryAnnotation(node) << 2) + (+hasMemoIntrinsicAnnotation(node) << 1) + (+hasMemoAnnotation(node))
    switch (mask) {
        case 0:
            return MemoFunctionKind.NONE
        case 1:
            return MemoFunctionKind.MEMO
        case 2:
            return MemoFunctionKind.INTRINSIC
        case 4:
            return MemoFunctionKind.ENTRY
        default:
            console.error(`Conflicting @memo annotations are not allowed`)
            throw new Error(`Invalid @memo usage`)
    }
}

export function isWrappable(type: arkts.TypeNode | undefined, arg: arkts.Expression) {
    return (type && correctFunctionParamType(arg)) || correctObjectExpression(arg)
}

export function isTrackableParam(node: arkts.ETSParameterExpression, isLast: boolean) {
    return !hasMemoSkipAnnotation(node) && !(isLast && node.ident?.name == RuntimeNames.CONTENT)
}

export function shouldWrap(param: arkts.ETSParameterExpression, isLastParam: boolean, arg: arkts.Expression) {
    return isWrappable(param.typeAnnotation, arg) && isTrackableParam(param, isLastParam)
}

export function dumpAstToFile(node: arkts.AstNode, keepTransformed: string) {
    const fileName = path.isAbsolute(keepTransformed) ?
        path.join(keepTransformed, arkts.getFilePathFromPackageRoot()) : path.join(__dirname, keepTransformed, arkts.getFilePathFromPackageRoot())
    fs.mkdirSync(path.dirname(fileName), { recursive: true })
    fs.writeFileSync(fileName, node.dumpSrc())
}

/**
 * Checks that node was obtained from MemoFactory.createSyntheticReturnStatement
 *
 * TODO: remove when node updates are done in place
 * @deprecated
 */
export function isSyntheticReturnStatement(node: arkts.AstNode) {
    return (
        arkts.isReturnStatement(node) &&
        node.argument && arkts.isMemberExpression(node.argument) &&
        arkts.isIdentifier(node.argument.object) &&
        node.argument.object.name === RuntimeNames.SCOPE &&
        arkts.isIdentifier(node.argument.property) &&
        node.argument.property.name === RuntimeNames.INTERNAL_VALUE
    ) || (
        arkts.isBlockStatement(node) &&
        node.statements.length === 2 &&
        arkts.isExpressionStatement(node.statements[0]) &&
        arkts.isMemberExpression(node.statements[0].expression) &&
        arkts.isIdentifier(node.statements[0].expression.object) &&
        node.statements[0].expression.object.name === RuntimeNames.SCOPE &&
        arkts.isIdentifier(node.statements[0].expression.property) &&
        node.statements[0].expression.property.name === RuntimeNames.INTERNAL_VALUE &&
        arkts.isReturnStatement(node.statements[1]) &&
        node.statements[1].argument &&
        arkts.isThisExpression(node.statements[1].argument)
    ) || (
        arkts.isBlockStatement(node) &&
        node.statements.length === 2 &&
        arkts.isExpressionStatement(node.statements[0]) &&
        arkts.isMemberExpression(node.statements[0].expression) &&
        arkts.isIdentifier(node.statements[0].expression.object) &&
        node.statements[0].expression.object.name === RuntimeNames.SCOPE &&
        arkts.isIdentifier(node.statements[0].expression.property) &&
        node.statements[0].expression.property.name === RuntimeNames.INTERNAL_VALUE &&
        arkts.isReturnStatement(node.statements[1]) &&
        node.statements[1].argument == undefined
    )
}

/**
 * Checks that node was obtained from MemoFactory.createMemoParameterDeclaration
 *
 * TODO: remove when node updates are done in place
 * @deprecated
 */
export function isMemoParametersDeclaration(node: arkts.AstNode) {
    return arkts.isVariableDeclaration(node) &&
        node.declarators.every(
            (it) => {
                if (!arkts.isIdentifier(it.id)) {
                    return false
                }
                return it.id.name.startsWith(RuntimeNames.PARAMETER)
            }
        )
}


/**
 * Checks type node refers to void type
 *
 * TODO: remove when es2panda API allows to read return type
 * @deprecated
 */
export function isVoidType(node: arkts.TypeNode) {
    return node.dumpSrc() == "void"
}

export function isVoidReturn(returnTypeAnnotation: arkts.TypeNode | undefined) {
    return !returnTypeAnnotation || isVoidType(returnTypeAnnotation)
}

export function getDeclResolveGensym(node: arkts.AstNode): arkts.AstNode | undefined {
    const decl = arkts.getDecl(node)
    if (arkts.isIdentifier(decl) && decl.name.startsWith(RuntimeNames.GENSYM)) {
        if (arkts.isVariableDeclarator(decl.parent)) {
            if (arkts.isIdentifier(decl.parent.init)) {
                return getDeclResolveGensym(decl.parent.init)
            }
            if (arkts.isMemberExpression(decl.parent.init)) {
                return getDeclResolveGensym(decl.parent.init.property!)
            }
        }
    }
    return decl
}

export function moveToFront<T>(arr: T[], idx: number): T[] {
    if (idx >= arr.length) {
        throw new Error(`Invalid argument, size of array: ${arr.length}, idx: ${idx}`)
    }
    return [arr[idx], ...arr.slice(0, idx), ...arr.slice(idx + 1)]
}
