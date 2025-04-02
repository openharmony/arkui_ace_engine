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

import * as ts from '@koalaui/ets-tsc';
import { MemoArgumentDetector } from './MemoArgumentDetector';
import { ScopedVisitor } from './ScopedVisitor';
import { Rewrite } from './transformation-context';
import {
    FunctionKind,
    Tracer,
    isFunctionOrMethod,
    isAnyMemoKind,
    RuntimeNames,
    getDeclarationsByNode,
    isMemoKind
} from "./util"

enum MessageCode {
    CALLINNG_MEMO_FROM_NON_MEMO = 10001,
    SHORTHAND_PROPERTY_ASSIGNMENT_IS_NOT_ALLOWED = 10002,
    CAN_NOT_CALL_MEMO_FUNCTION_IN_PARAMETER_DEFAULT_VALUE = 10003,
    CHANGING_STATE_IN_MEMO_CONTEXT_IS_NOT_ALLOWED = 10004,
    CAN_NOT_ASSIGN_TO_MEMO_FUNCTION_PARAMETER = 10005,
    MEMO_MUST_HAVE_ITS_TYPE_EXPLICITLY_SPECIFIED = 10006,
    MEMO_ARROW_MUST_HAVE_ITS_TYPE_EXPLICITLY_SPECIFIED = 10007,
}

export class DiagnosticsVisitor extends ScopedVisitor<ts.FunctionLikeDeclaration> {
    constructor(
        public tracer: Tracer,
        public typechecker: ts.TypeChecker,
        public sourceFile: ts.SourceFile,
        public rewrite: Rewrite,
        public extras: ts.TransformerExtras|undefined,
        ctx: ts.TransformationContext
    ) {
        super(rewrite.functionTable, ctx)
    }

    reportError(code: number, text: string, node: ts.Node) {
        const lineAndChar = ts.getLineAndCharacterOfPosition(this.sourceFile, node.pos)
        this.extras?.addDiagnostic({
            code: code,
            messageText: text,
            category: ts.DiagnosticCategory.Error,
            file: this.sourceFile,
            start: node.pos,
            length: node.end - node.pos
        })
    }

    reportCallingMemoFromNonMemo(node: ts.CallExpression) {
        const name = ts.isIdentifier(node.expression) ? `"${ts.idText(node.expression)}"` : ""
        this.reportError(
            MessageCode.CALLINNG_MEMO_FROM_NON_MEMO,
            `Calling a ${RuntimeNames.ANNOTATION} function ${name} from a non-${RuntimeNames.ANNOTATION} context`,
            node.expression,
        )
    }

    reportShorthandPropertyInMemo(node: ts.ShorthandPropertyAssignment) {
        const name = ts.idText(node.name)
        this.reportError(
            MessageCode.SHORTHAND_PROPERTY_ASSIGNMENT_IS_NOT_ALLOWED,
            `Shorthand property assignment is not allowed in ${RuntimeNames.ANNOTATION} code: ${name}`,
            node,
        )
    }

    functionName(node: ts.CallExpression): string {
        return this.nameOrFunction(node.expression)
    }

    nameOrFunction(node: ts.Node|undefined): string {
        let name : string
        if (node && ts.isIdentifier(node)) {
            name = `"` + ts.idText(node) + `"`
        } else {
            name = `function`
        }
        return name
    }

    reportMemoArgument(name: ts.BindingName, initializer: ts.CallExpression) {
        let parameter : string
        if(ts.isIdentifier(name)) {
            parameter = ` "` + ts.idText(name) + `"`
        }
        else { parameter = "" }

        this.reportError(
            MessageCode.CAN_NOT_CALL_MEMO_FUNCTION_IN_PARAMETER_DEFAULT_VALUE,
            `Can not call ${RuntimeNames.ANNOTATION} ${this.functionName(initializer)} in parameter${parameter} default value expression`,
            name,
        )
    }

    reportChangingStateInMemo(node: ts.PropertyAccessExpression) {
        const name = ts.isIdentifier(node.expression) ? `"${ts.idText(node.expression)}"` : ""
        this.reportError(
            MessageCode.CHANGING_STATE_IN_MEMO_CONTEXT_IS_NOT_ALLOWED,
            `Changing state ${name} in ${RuntimeNames.ANNOTATION} context is not allowed`,
            node.expression,
        )
    }

    reportAssignToParameterOfMemo(node: ts.Identifier) {
        const name = ts.idText(node)
        this.reportError(
            MessageCode.CAN_NOT_ASSIGN_TO_MEMO_FUNCTION_PARAMETER,
            `Can not assign to memo function parameter: ${name}`,
            node,
        )
    }

    isParameterOfMemo(node: ts.Expression): boolean {
        if (!ts.isIdentifier(node)) return false
        const declarations = getDeclarationsByNode(this.typechecker, node)
        if (!declarations || declarations.length == 0) return false
        const firstDeclaration = declarations[0]
        if (!ts.isParameter(firstDeclaration)) return false
        const parent = firstDeclaration.parent
        if (!ts.isFunctionDeclaration(parent)) return false

        return isMemoKind(this.declarationKind(parent))
    }

    isAssignment(node: ts.Node): boolean {
        if (node.kind >= ts.SyntaxKind.FirstAssignment && node.kind <= ts.SyntaxKind.LastAssignment) { return true }
        else { return false }
    }

    isStateVariable(node: ts.Node): boolean {
        if (!ts.isPropertyAccessExpression(node)) return false
        if (!ts.isIdentifier(node.name)) return false
        if (!(ts.idText(node.name) == "value")) return false
        const declarations = getDeclarationsByNode(this.typechecker, node)
        if(!declarations.length) return false
        let suspect = declarations[0].parent
        if (!ts.isInterfaceDeclaration(suspect)) return false
        if (!suspect.heritageClauses) return false
        for (const postsuspect of suspect.heritageClauses) {
            for (const parent of postsuspect.types) {
                if (ts.isIdentifier(parent.expression)) {
                    if (ts.idText(parent.expression) == "State") return true
                }
            }
        }
        return false
    }

    containsMemoCall(parameter: ts.ParameterDeclaration) {
        const memoArgumentDetector = new MemoArgumentDetector(this.typechecker, this.rewrite, parameter, this.ctx)
        if (parameter.initializer) {
            const hasMemoArgument = memoArgumentDetector.usingMemoFunction(parameter.initializer)
            if (hasMemoArgument && ts.isCallExpression(memoArgumentDetector.memoArgument)) {
                this.reportMemoArgument(parameter.name, memoArgumentDetector.memoArgument)
            }
        }
    }

    checkReturnType(returnNode: ts.ReturnStatement, functionNode: ts.FunctionLikeDeclaration | undefined) {
        if (!functionNode) return
        if (returnNode.expression !== undefined && functionNode.type === undefined) {
            this.reportError(
                MessageCode.MEMO_MUST_HAVE_ITS_TYPE_EXPLICITLY_SPECIFIED,
                `${RuntimeNames.ANNOTATION} ${this.nameOrFunction(functionNode.name)} must have its type specified explicitly`,
                functionNode,
            )
        }
    }

    canFindVoidType(body: ts.Expression): boolean {
        const type = this.typechecker.getTypeAtLocation(body)
        const text = this.typechecker.typeToString(type)
        // Oh my. Can we detect void|undefined in a some faster way?
        return (text == "void" || text == "void | undefined" || text == "undefined | void" )
    }

    checkArrowReturnType(arrow: ts.ArrowFunction) {
        if (!ts.isBlock(arrow.body) && arrow.type === undefined) {
            // So we have an arrow function like
            //   (some args) => some_expression
            // we need to check if some_expression has type void
            if (!ts.isBlock(arrow.body) && // The Block case is handled in checkReturnType()
                !this.canFindVoidType(arrow.body)
            ) {
                this.reportError(
                    MessageCode.MEMO_ARROW_MUST_HAVE_ITS_TYPE_EXPLICITLY_SPECIFIED,
                    `${RuntimeNames.ANNOTATION} arrow must have its type specified explicitly`,
                    arrow,
                )
            }
        }
    }

    indent = 0
    visitor(node: ts.Node): ts.Node {
        if (isFunctionOrMethod(node)) {
            const kind = this.declarationKind(node)
            if (ts.isArrowFunction(node) && isMemoKind(kind)) {
                this.checkArrowReturnType(node)
            }
            return this.withFunctionScope<ts.Node>(kind, node, () => {
                return this.visitEachChild(node)
            })
        } else if (ts.isCallExpression(node)) {
            const callKind = this.rewrite.callTable.get(node) ?? FunctionKind.REGULAR
            const scopeKind = this.currentKind()
            if (isAnyMemoKind(callKind) && !isAnyMemoKind(scopeKind)) {
                if (!this.rewrite.entryTable.has(node)) {
                    this.reportCallingMemoFromNonMemo(node)
                }
            }
            return this.visitEachChild(node)
        } else if (ts.isBinaryExpression(node) &&
            this.isAssignment(node.operatorToken)) {

            if (this.isStateVariable(node.left)) {
                const scopeKind = this.currentKind()
                if (isAnyMemoKind(scopeKind)) {
                    if (ts.isPropertyAccessExpression(node.left)) {
                        this.reportChangingStateInMemo(node.left)
                    }

                }
            }
            if (this.isParameterOfMemo(node.left)) {
                this.reportAssignToParameterOfMemo(node.left as ts.Identifier)
            }
            return this.visitEachChild(node)
        } else if (ts.isPrefixUnaryExpression(node) || ts.isPostfixUnaryExpression(node)) {
            if (node.operator == ts.SyntaxKind.PlusPlusToken || node.operator == ts.SyntaxKind.MinusMinusToken) {
                if (this.isStateVariable(node.operand)) {
                    const scopeKind = this.currentKind()
                    if (isAnyMemoKind(scopeKind)) {
                        if (ts.isPropertyAccessExpression(node.operand)) {
                            this.reportChangingStateInMemo(node.operand)
                        }

                    }
                }
            }
            return this.visitEachChild(node)
        } else if (ts.isParameter(node)) {
            this.containsMemoCall(node)
            return this.visitEachChild(node)
        } else if (ts.isShorthandPropertyAssignment(node)) {
            const scopeKind = this.currentKind()
            if (isAnyMemoKind(scopeKind)) {
                this.reportShorthandPropertyInMemo(node)
            }
            return this.visitEachChild(node)
        } else if (ts.isReturnStatement(node)) {
            if (isMemoKind(this.currentKind())) {
                this.checkReturnType(node, this.functionScopes.peek()?.data)
            }
            return this.visitEachChild(node)
        } else {
            return this.visitEachChild(node)
        }
    }
}
