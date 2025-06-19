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

import * as ts from "@koalaui/libarkts"
import { AbstractVisitor } from "./AbstractVisitor";

import { Rewrite } from './transformation-context';
import {
    FunctionKind,
    Tracer,
    // findSourceFile,
    // error,
    asString,
    RuntimeNames,
    // isFunctionOrMethod,
    // getComment,
    // arrayAt,
    // getDeclarationsByNode,
    findFunctionDeclaration,
    // isMemoEntry,
    // skipParenthesizedExpression,
} from "./util"

function parseComment(comment: string): FunctionKind {
    let kind = FunctionKind.REGULAR
    if (comment.includes(RuntimeNames.ANNOTATION_INTRINSIC)) {
        kind = FunctionKind.MEMO_INTRINSIC
    } else if (comment.includes(RuntimeNames.ANNOTATION_ENTRY)) {
        // Do nothing
    } else if (comment.includes(RuntimeNames.ANNOTATION)) {
        kind = FunctionKind.MEMO
    }
    return kind
}

export class AnalysisVisitor extends AbstractVisitor {
    constructor(
        public tracer: Tracer,
        // public typechecker: arkts.TypeChecker,
        // public sourceFile: arkts.SourceFile,
        public rewrite: Rewrite,
        ctx?: ts.TransformationContext
    ) {
        super(ctx)
    }

    // private importExport = new ImportExport(this.typechecker, this.sourceFile)

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

    // TODO: get real annotation
    getFunctionKindByIdent(node: ts.Identifier | undefined, traceAnnotation: string): FunctionKind {
        if (node === undefined) {
            return FunctionKind.REGULAR
        }
        if (!ts.isIdentifier(node)) {
            throw new Error('node expected to be Identifier')
        }
        const kind = parseComment(node.text)
        this.traceAnnotation(traceAnnotation, kind, node)
        return kind
    }

    updateFunctionTableByKind(node: ts.SignatureDeclarationBase, kind: FunctionKind): void {
        if (kind === FunctionKind.REGULAR) {
            return
        }
        this.rewrite.functionTable.set(node, kind)
    }

    updateFunctionTableByIdent(node: ts.SignatureDeclarationBase, ident: ts.Identifier | undefined, traceMessage: string): void {
        if (ident === undefined) {
            return
        }
        this.updateFunctionTableByKind(node, this.getFunctionKindByIdent(ident, traceMessage))
    }

    updateVariableTableByKind(node: ts.VariableLikeDeclaration, kind: FunctionKind): void {
        if (kind === FunctionKind.REGULAR) {
            return
        }
        this.rewrite.variableTable.set(node, kind)
    }

    updateVariableTableByIdent(node: ts.VariableLikeDeclaration, ident: ts.Identifier, traceMessage: string): void {
        this.updateVariableTableByKind(node, this.getFunctionKindByIdent(ident, traceMessage))
    }

    updateCallTableByKind(node: ts.CallExpression, kind: FunctionKind): void {
        if (kind === FunctionKind.REGULAR) {
            return
        }
        this.rewrite.callTable.set(node, kind)
    }

    updateCallTableByIdent(node: ts.CallExpression, ident: ts.Identifier, traceMessage: string): void {
        this.updateCallTableByKind(node, this.getFunctionKindByIdent(ident, traceMessage))
    }

    isMemoEntry(node: ts.CallExpression): boolean {
        const enclosingFunction = findFunctionDeclaration(node)
        if (enclosingFunction === undefined) {
            return false
        }
        return this.getFunctionKindByIdent(enclosingFunction.name, "isMemoEntry") === FunctionKind.MEMO
    }

    processCallExpression(node: ts.CallExpression): void {
        if (ts.isIdentifier(node.expression)) {
            this.updateCallTableByIdent(node, node.expression, "CallExpression")
        } else if (ts.isPropertyAccessExpression(node.expression)) {
            // TODO: fix maybe (copied from compiler-plugin)
            const kind = this.getFunctionKindByIdent(node.expression.name, "CallExpression")
            if (kind !== FunctionKind.REGULAR) {
                this.rewrite.callTable.set(node, kind)
            }
            return
        }
        if (this.isMemoEntry(node)) {
            this.rewrite.entryTable.add(node)
        }
    }

    processFunctionDeclaration(node: ts.FunctionDeclaration): void {
        this.updateFunctionTableByIdent(node, node.name, "FunctionDeclaration")
    }

    processMethodDeclaration(node: ts.MethodDeclaration): void {
        this.updateFunctionTableByIdent(node, node.name, "MethodDeclaration")
    }

    // TODO: unavailable now (ArrowFunction doesn't have a name)
    processArrowFunction(node: ts.ArrowFunction): void {
        // this.updateFunctionTableByIdent(node, node.name, "ArrowFunction")
        return
    }

    processFunctionExpression(node: ts.FunctionExpression): void {
        this.updateFunctionTableByIdent(node, node.name, "MethodDeclaration")
    }

    processParameter(node: ts.ParameterDeclaration): void {
        this.updateVariableTableByIdent(node, node.name, "ParameterDeclaration")
    }

    processVariableDeclaration(node: ts.VariableDeclaration): void {
        this.updateVariableTableByIdent(node, node.name, "ParameterDeclaration")
    }

    processVariableDeclarationList(node: ts.VariableDeclarationList): void {
        node.declarations.forEach(declaration => {
            this.processVariableDeclaration(declaration)
        })
    }

    processPropertyDeclaration(node: ts.PropertyDeclaration): void {
        // TODO: support non Identifier properties
        this.updateVariableTableByIdent(node, node.name as ts.Identifier, "PropertyDeclaration")
    }

    processPropertySignature(node: ts.PropertySignature): void {
        if (node.name === undefined) {
            return
        }
        // TODO: support non Identifier properties
        this.updateVariableTableByIdent(node, node.name as ts.Identifier, "PropertySignature")
    }

    processFunctionTypeNode(node: ts.FunctionTypeNode): void {
        if (node.name === undefined) {
            return
        }
        // TODO: support non Identifier properties
        this.updateFunctionTableByIdent(node, node.name as ts.Identifier, "FunctionTypeNode")
    }

    processMethodSignature(node: ts.MethodSignature): void {
        if (node.name === undefined) {
            return
        }
        // TODO: support non Identifier properties
        this.updateFunctionTableByIdent(node, node.name as ts.Identifier, "MethodSignature")
    }

    processGetAccessorDeclaration(node: ts.GetAccessorDeclaration): void {
        this.updateFunctionTableByIdent(node, node.name, "GetAccessorDeclaration")
    }

    processSetAccessorDeclaration(node: ts.SetAccessorDeclaration): void {
        this.updateFunctionTableByIdent(node, node.name, "SetAccessorDeclaration")
    }

    visitor(node: ts.Node): ts.Node {
        // TODO: comparison shouldn't work now
        if (ts.getOriginalNode(node) !== node) {
            throw new Error("Analysis phase is expected to work on original nodes")
        }

        if (ts.isCallExpression(node)) {
            this.processCallExpression(node)
        } else if (ts.isFunctionDeclaration(node)) {
            this.processFunctionDeclaration(node)
        } else if (ts.isMethodDeclaration(node)) {
            this.processMethodDeclaration(node)
        } else if (ts.isArrowFunction(node)) {
            this.processArrowFunction(node)
        } else if (ts.isFunctionExpression(node)) {
            this.processFunctionExpression(node)
        } else if (ts.isParameter(node)) {
            this.processParameter(node)
        } else if (ts.isVariableDeclaration(node)) {
            this.processVariableDeclaration(node)
        } else if (ts.isVariableDeclarationList(node)) {
            this.processVariableDeclarationList(node)
        } else if (ts.isPropertyDeclaration(node)) {
            this.processPropertyDeclaration(node)
        } else if (ts.isPropertySignature(node)) {
            this.processPropertySignature(node)
        } else if (ts.isFunctionTypeNode(node)) {
            this.processFunctionTypeNode(node)
        } else if (ts.isMethodSignature(node)) {
            this.processMethodSignature(node)
        } else if (ts.isGetAccessorDeclaration(node)) {
            this.processGetAccessorDeclaration(node)
        } else if (ts.isSetAccessorDeclaration(node)) {
            this.processSetAccessorDeclaration(node)
        }

        return this.visitEachChild(node)
    }
}
