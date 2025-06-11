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
import { AbstractVisitor } from "./AbstractVisitor"
import { Rewrite } from './transformation-context';
import {
    FunctionKind,
    Tracer,
    findSourceFile,
    error,
    asString,
    RuntimeNames,
    isFunctionOrMethod,
    getComment,
    arrayAt,
    getDeclarationsByNode,
    findFunctionDeclaration,
    isMemoEntry,
    skipParenthesizedExpression,
} from "./util"
import { ImportExport } from './import-export';

function parseCommentDetails(comment: string, annotation: RuntimeNames): boolean {
    if (!comment.includes(annotation)) return false
    if (comment != `/** ${annotation} */`) {
        console.log(`Warning: The /** ${annotation} */ should be a single jsdoc comment.`)
        return true
    }
    return true
}

function parseComment(comment: string): FunctionKind {
    let kind = FunctionKind.REGULAR
    if (parseCommentDetails(comment, RuntimeNames.ANNOTATION_INTRINSIC)) {
        kind = FunctionKind.MEMO_INTRINSIC
    } else if (parseCommentDetails(comment, RuntimeNames.ANNOTATION_ENTRY)) {
        // Do nothing
    } else if (parseCommentDetails(comment, RuntimeNames.ANNOTATION)) {
        kind = FunctionKind.MEMO
    }
    return kind
}

export class AnalysisVisitor extends AbstractVisitor {
    constructor(
        public tracer: Tracer,
        public typechecker: ts.TypeChecker,
        public sourceFile: ts.SourceFile,
        public rewrite: Rewrite,
        ctx: ts.TransformationContext
    ) {
        super(ctx)
    }

    private importExport = new ImportExport(this.typechecker, this.sourceFile)

    trace(msg: any) {
        this.tracer.trace(msg)
    }

    traceAnnotation(nodeName: string, kind: FunctionKind, node: ts.Node) {
        if (kind) {
            this.trace(`${nodeName} HAS annotation: ${asString(node)} to ${FunctionKind[kind]}`)
        } else {
            this.trace(`${nodeName} doesn't have annotations: ${asString(node)}`)
        }
    }

    immediateFunctionKind(source: ts.SourceFile, node: ts.Node, name: string): FunctionKind {
        const comment = getComment(source, node)
        let kind = parseComment(comment)
        this.traceAnnotation(name, kind, node)
        return kind
    }

    callIsEligible(identifier: ts.Identifier|undefined): FunctionKind {

        if (!identifier) return FunctionKind.REGULAR

        const decl = this.importExport.findRealDeclaration(identifier)
        if (!decl) return FunctionKind.REGULAR

        const source = findSourceFile(decl)
        if (!source) return FunctionKind.REGULAR

        return this.variableDeclarationAnnotation(source, decl)
    }

    methodCallIsEligible(name: ts.MemberName): FunctionKind {

        if (!ts.isIdentifier(name)) return FunctionKind.REGULAR

        const decl = this.findRealMethodDeclaration(name)
        if (!decl) return FunctionKind.REGULAR

        const source = findSourceFile(decl)
        if (!source) return FunctionKind.REGULAR

        return this.immediateFunctionKind(source, decl, "METHOD CALL")
    }

    isInMemoEntry(node: ts.CallExpression): boolean {
        const enclosingFunction = findFunctionDeclaration(node)
        if (enclosingFunction === undefined) return false
        return isMemoEntry(this.sourceFile, enclosingFunction)
    }

    parameterHasAnnotation(parameter: ts.ParameterDeclaration): FunctionKind {
        const source = findSourceFile(parameter)
        if (!source) return FunctionKind.REGULAR

        return this.immediateFunctionKind(source, parameter, "Parameter")
    }

    parameterDeclarationHasAnnotation(functionIdentifier: ts.Identifier|undefined, parameterIndex: number): FunctionKind {
        if (!functionIdentifier) return FunctionKind.REGULAR

        const functionDeclaration = this.importExport.findRealDeclaration(functionIdentifier)
        if (!functionDeclaration) return FunctionKind.REGULAR
        if (!isFunctionOrMethod(functionDeclaration)) return FunctionKind.REGULAR

        const parameterDeclaration = functionDeclaration.parameters[parameterIndex]
        return this.parameterHasAnnotation(parameterDeclaration)
    }

    variableDeclarationAnnotation(sourceFile: ts.SourceFile, variable: ts.Node): FunctionKind {
        let immediateFunctionKind = this.immediateFunctionKind(sourceFile, variable, "Variable")
        if (immediateFunctionKind != FunctionKind.REGULAR) {
            return immediateFunctionKind
        }

        let parent = variable.parent
        if (!ts.isVariableDeclarationList(parent)) {
            return FunctionKind.REGULAR
        }

        return this.immediateFunctionKind(sourceFile, parent, "VariableDeclarationList")
    }

    variableDeclarationListAnnotation(sourceFile: ts.SourceFile, variableList: ts.VariableDeclarationList): FunctionKind {
        return this.immediateFunctionKind(this.sourceFile, variableList, "VariableDeclarationList")
    }

    propertyHasAnnotation(sourceFile: ts.SourceFile, property: ts.PropertyDeclaration): FunctionKind {
        return this.immediateFunctionKind(sourceFile, property, "Property")
    }

    propertySignatureHasAnnotation(sourceFile: ts.SourceFile, property: ts.PropertySignature): FunctionKind {
        return this.immediateFunctionKind(sourceFile, property, "Property signature")
    }

    functionTypeHasAnnotation(sourceFile: ts.SourceFile, functionType: ts.FunctionTypeNode): FunctionKind {
        return this.immediateFunctionKind(sourceFile, functionType, "Function type")
    }

    methodSignatureHasAnnotation(sourceFile: ts.SourceFile, signature: ts.MethodSignature): FunctionKind {
        return this.immediateFunctionKind(sourceFile, signature, "Method signature")
    }

    getterHasAnnotation(sourceFile: ts.SourceFile, getter: ts.GetAccessorDeclaration): FunctionKind {
        return this.immediateFunctionKind(sourceFile, getter, "Getter")
    }

    setterHasAnnotation(sourceFile: ts.SourceFile, setter: ts.SetAccessorDeclaration): FunctionKind {
        return this.immediateFunctionKind(sourceFile, setter, "Setter")
    }

    isDirectMemoVariableInitializer(sourceFile: ts.SourceFile, node: ts.Node): boolean {
        if (!ts.isVariableDeclaration(node.parent)) return false
        const variable = node.parent
        let kind = this.variableDeclarationAnnotation(sourceFile, variable)
        return kind != FunctionKind.REGULAR
    }

    isDirectArgumentForMemoParameter(sourceFile: ts.SourceFile, node: ts.Node): boolean {
        const parent = node.parent
        if (!ts.isCallExpression(parent)) return false

        let callable: ts.Identifier
        if (ts.isIdentifier(parent.expression)) {
            callable = parent.expression
        } else if (ts.isPropertyAccessExpression(parent.expression)) {
            if (ts.isPrivateIdentifier(parent.expression.name)) return false
            callable = parent.expression.name
        } else {
            return false
        }

        const index = parent.arguments.findIndex(it => it === node)
        if (index < 0) return false

        return this.parameterDeclarationHasAnnotation(callable, index) != FunctionKind.REGULAR

    }

    getAssigneeTransformation(sourceFile: ts.SourceFile, node: ts.Node): FunctionKind {
        if (this.isDirectMemoVariableInitializer(sourceFile, node)) return FunctionKind.MEMO
        if (this.isDirectArgumentForMemoParameter(sourceFile, node)) return FunctionKind.MEMO
        else return FunctionKind.REGULAR
    }

    declarationTransformKind(node: ts.FunctionLikeDeclarationBase|undefined): FunctionKind {
        if (node === undefined) return FunctionKind.REGULAR

        const name = node.name
        const nameString = (name && ts.isIdentifier(name)) ?
            ts.idText(name) :
            "Couldn't take declaration name"

        let immediateFunctionKind = this.immediateFunctionKind(this.sourceFile, node, "Declaration")
        if (immediateFunctionKind != FunctionKind.REGULAR) {
            return immediateFunctionKind
        }

        let transform = this.getAssigneeTransformation(this.sourceFile, node)

        if (transform != FunctionKind.REGULAR) {
            this.trace(`DECLARATION is ELIGIBLE to ${FunctionKind[transform]}: ${nameString}`)
        }

        return transform
    }

    findRealMethodDeclaration(member: ts.MemberName): ts.Node|undefined {
        if (!ts.isIdentifier(member)) return undefined
        const declarations = getDeclarationsByNode(this.typechecker, member)
        return declarations[0]
    }

    visitor(node: ts.Node): ts.Node {
        if (ts.getOriginalNode(node) !== node) throw new Error("Analysis phase is expected to work on original nodes")

        if (ts.isCallExpression(node)) {
            let node_expr: ts.Expression = node.expression
            if (ts.isParenthesizedExpression(node.expression)) {
                node_expr = skipParenthesizedExpression(node.expression)
            }
            if (ts.isIdentifier(node_expr)) {
                const kind = this.callIsEligible(node_expr)
                if (kind) {
                    this.rewrite.callTable.set(node, kind)
                }
            } else if (ts.isPropertyAccessExpression(node_expr)) {
                const member = node_expr.name
                const kind = this.methodCallIsEligible(member)
                if (kind) {
                    this.rewrite.callTable.set(node, kind)
                }
            }
            if (this.isInMemoEntry(node)) {
                this.rewrite.entryTable.add(node)
            }
        } else if (ts.isFunctionDeclaration(node)) {
            switch (this.declarationTransformKind(node)) {
                case FunctionKind.MEMO:
                    this.rewrite.functionTable.set(node, FunctionKind.MEMO)
                    break;
                case FunctionKind.MEMO_INTRINSIC:
                    this.rewrite.functionTable.set(node, FunctionKind.MEMO_INTRINSIC)
                    break;
            }
        } else if (ts.isMethodDeclaration(node)) {
            switch (this.declarationTransformKind(node)) {
                case FunctionKind.MEMO:
                    this.rewrite.functionTable.set(node, FunctionKind.MEMO)
                    break;
                case FunctionKind.MEMO_INTRINSIC:
                    this.rewrite.functionTable.set(node, FunctionKind.MEMO_INTRINSIC)
                    break;
            }
        } else if (ts.isArrowFunction(node)) {
            if (this.declarationTransformKind(node) == FunctionKind.MEMO) {
                this.rewrite.functionTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isFunctionExpression(node)) {
            if (this.declarationTransformKind(node) == FunctionKind.MEMO) {
                this.rewrite.functionTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isParameter(node)) {
            if (this.parameterHasAnnotation(node) == FunctionKind.MEMO) {
                this.rewrite.variableTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isVariableDeclaration(node)) {
            if (this.variableDeclarationAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                this.rewrite.variableTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isVariableDeclarationList(node)) {
            if (this.variableDeclarationListAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                node.declarations.forEach(declaration => {
                    this.rewrite.variableTable.set(declaration, FunctionKind.MEMO)
                })
            }
        } else if (ts.isPropertyDeclaration(node)) {
            if (this.propertyHasAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                this.rewrite.variableTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isPropertySignature(node)) {
            if (this.propertySignatureHasAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                this.rewrite.variableTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isFunctionTypeNode(node)) {
            if (this.functionTypeHasAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                this.rewrite.functionTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isMethodSignature(node)) {
            if (this.methodSignatureHasAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                this.rewrite.functionTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isGetAccessorDeclaration(node)) {
            if (this.getterHasAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                this.rewrite.functionTable.set(node, FunctionKind.MEMO)
            }
        } else if (ts.isSetAccessorDeclaration(node)) {
            if (this.setterHasAnnotation(this.sourceFile, node) == FunctionKind.MEMO) {
                this.rewrite.functionTable.set(node, FunctionKind.MEMO)
            }
        }
        return this.visitEachChild(node)
    }
}
