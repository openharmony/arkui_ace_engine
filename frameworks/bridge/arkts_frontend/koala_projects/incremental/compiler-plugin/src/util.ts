/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
import * as fs from "fs"
import { UniqueId } from "@koalaui/common"
import { Rewrite } from './transformation-context';


export enum FunctionKind {
    REGULAR,
    MEMO,
    MEMO_INTRINSIC,
}

export type FunctionTable = Map<ts.SignatureDeclarationBase, FunctionKind>
export type CallTable = Map<ts.CallExpression, FunctionKind>
export type EntryTable = Set<ts.CallExpression>
export type VariableTable = Map<ts.VariableLikeDeclaration, FunctionKind>

export function isNamedDeclaration(node: ts.Node): node is ts.NamedDeclaration {
    return ("name" in node )
}

export function asString(node: ts.Node|undefined): string {
    if (node === undefined) return "undefined node"
    if (ts.isIdentifier(node)) return ts.idText(node)
    if (isNamedDeclaration(node)) {
        if (node.name === undefined) {
            return `${ts.SyntaxKind[node.kind]}(undefined name)`
        } else {

            return `${ts.SyntaxKind[node.kind]}(${asString(node.name)})`
        }
    } else {
        return `${ts.SyntaxKind[node.kind]}`
    }
}

export function isFunctionOrMethod(node: ts.Node): node is ts.FunctionLikeDeclaration {
    return ts.isFunctionDeclaration(node) ||
           ts.isMethodDeclaration(node) ||
           ts.isFunctionExpression(node) ||
           ts.isArrowFunction(node)
}

export enum RuntimeNames {
    COMPUTE = "compute",
    CONTEXT = "__memo_context",
    ID = "__memo_id",
    SCOPE = "__memo_scope",
    INTERNAL_PARAMETER_STATE = "param",
    INTERNAL_VALUE = "cached",
    INTERNAL_VALUE_NEW = "recache",
    INTERNAL_SCOPE = "scope",
    INTERNAL_VALUE_OK = "unchanged",
    CONTENT = "content",
    VALUE = "value",
    __CONTEXT = "__context",
    __ID = "__id",
    __KEY = "__key",
    __STATE = "__state",
    CONTEXT_TYPE = "__memo_context_type",
    ID_TYPE = "__memo_id_type",
    TRANSFORMED_TYPE = "__memo_transformed",
    SYNTHETIC_RETURN_MARK = "__synthetic_return_value",
    CONTEXT_TYPE_DEFAULT_IMPORT = "@koalaui/runtime",
    ANNOTATION = "@memo",
    ANNOTATION_INTRINSIC = "@memo:intrinsic",
    ANNOTATION_ENTRY = "@memo:entry",
    ANNOTATION_SKIP = "@skip:memo", // skip binding to parameter changes
    ANNOTATION_STABLE = "@memo:stable", // assume this should not be tracked
}

export function runtimeIdentifier(name: RuntimeNames): ts.Identifier {
    return ts.factory.createIdentifier(name)
}

export function componentTypeName(functionName: ts.PropertyName|undefined): ts.Identifier {
    if (!functionName || !ts.isIdentifier(functionName) && !ts.isPrivateIdentifier(functionName)) {
        throw new Error("Expected an identifier: " + asString(functionName))
    }
    return ts.factory.createIdentifier(ts.idText(functionName)+"Node")
}

export function isSpecialContentParameter(param: ts.ParameterDeclaration): boolean {
    if (!param.type) return false
    if (!param.name) return false
    return (
        ts.isFunctionTypeNode(param.type) &&
        ts.isIdentifier(param.name) &&
        ts.idText(param.name) == RuntimeNames.CONTENT
    )
}

export function isSpecialContextParameter(parameter: ts.ParameterDeclaration): boolean {
    return !!parameter.name && ts.isIdentifier(parameter.name) && ts.idText(parameter.name) == RuntimeNames.CONTEXT
}

export function isSpecialIdParameter(parameter: ts.ParameterDeclaration): boolean {
    return !!parameter.name && ts.isIdentifier(parameter.name) && ts.idText(parameter.name) == RuntimeNames.ID
}

export function isSkippedParameter(sourceFile: ts.SourceFile, parameter: ts.ParameterDeclaration): boolean {
    return getComment(sourceFile, parameter).includes(RuntimeNames.ANNOTATION_SKIP)
}

export function isStableClass(sourceFile: ts.SourceFile, clazz: ts.ClassDeclaration): boolean {
    return getComment(sourceFile, clazz).includes(RuntimeNames.ANNOTATION_STABLE)
}

export function hasMemoEntry(sourceFile: ts.SourceFile, node: ts.Node): boolean {
    const comment = getComment(sourceFile, node)
    return comment.includes(RuntimeNames.ANNOTATION_ENTRY)
}

export function isMemoEntry(sourceFile: ts.SourceFile, func: ts.FunctionDeclaration): boolean {
    const name = func.name
    if (!name) return false
    if (!ts.isIdentifier(name)) return false

    return hasMemoEntry(sourceFile, func)
}

export function isTrackableParameter(sourceFile: ts.SourceFile, parameter: ts.ParameterDeclaration): boolean {
    return !isSpecialContentParameter(parameter)
        && !isSpecialContextParameter(parameter)
        && !isSpecialIdParameter(parameter)
        && !isSkippedParameter(sourceFile, parameter)
}

export function parameterStateName(original: string): string {
    return `__memo_parameter_${original}`
}

export function getSymbolByNode(typechecker: ts.TypeChecker, node: ts.Node) : ts.Symbol|undefined {
      return typechecker.getSymbolAtLocation(node)
}

export function getDeclarationsByNode(typechecker: ts.TypeChecker, node: ts.Node) : ts.Declaration[] {
    const symbol = getSymbolByNode(typechecker, node)
    const declarations =  symbol?.getDeclarations() ?? []
    return declarations
}

export function findSourceFile(node: ts.Node): ts.SourceFile|undefined {
    let element = node
    while(element) {
        if (ts.isSourceFile(element)) return element
        element = element.parent
    }
    return undefined
}

export function findFunctionDeclaration(node: ts.Node): ts.FunctionDeclaration|undefined {
    let element = node
    while(element) {
        if (ts.isFunctionDeclaration(element)) return element
        element = element.parent
    }
    return undefined
}

export function isMethodOfStableClass(sourceFile: ts.SourceFile, method: ts.MethodDeclaration): boolean {
    const original = ts.getOriginalNode(method)
    const parent = original.parent
    if (!parent) return false
    if (!ts.isClassDeclaration(parent)) return false
    return isStableClass(sourceFile, parent)
}

export function arrayAt<T>(array: T[] | undefined, index: number): T|undefined {
    return array ? array[index >= 0 ? index : array.length + index] : undefined
}

export function getComment(sourceFile: ts.SourceFile, node: ts.Node): string {
    const commentRanges = ts.getLeadingCommentRanges(
        sourceFile.getFullText(),
        node.getFullStart()
    )

    const commentRange = arrayAt(commentRanges, -1)
    if (!commentRange) return ""

    const comment = sourceFile.getFullText()
        .slice(commentRange.pos, commentRange.end)
    return comment
}

export function isVoidOrNotSpecified(type: ts.TypeNode | undefined): boolean {
    return type === undefined
        || type.kind === ts.SyntaxKind.VoidKeyword
        || ts.isTypeReferenceNode(type)
        && ts.isIdentifier(type.typeName)
        && ts.idText(type.typeName) == "void"
}

export function isThis(type: ts.TypeNode | undefined): type is ts.ThisTypeNode {
    return type !== undefined
        && ts.isThisTypeNode(type)
}

export function isThisStable(typechecker: ts.TypeChecker, sourceFile: ts.SourceFile, node: ts.ThisExpression | ts.ThisTypeNode): boolean {
    const declarations = getDeclarationsByNode(typechecker, node)
    const firstDeclaration = declarations[0]
    if (!firstDeclaration) return false
    if (!ts.isClassDeclaration(firstDeclaration)) return false
    return isStableClass(sourceFile, firstDeclaration)
}

export class PositionalIdTracker {
    // Global for the whole program.
    static callCount: number = 0

    // Set `stable` to true if you want to have more predictable values.
    // For example for tests.
    // Don't use it in production!
    constructor(public sourceFile: ts.SourceFile, public stableForTests: boolean = false) {
        if (stableForTests) PositionalIdTracker.callCount = 0
    }

    sha1Id(callName: string, fileName: string): string {
        const uniqId = new UniqueId()
        uniqId.addString("memo call uniqid")
        uniqId.addString(fileName)
        uniqId.addString(callName)
        uniqId.addI32(PositionalIdTracker.callCount++)
        return uniqId.compute().substring(0,10)
    }

    stringId(callName: string, fileName: string): string {
        return `${PositionalIdTracker.callCount++}_${callName}_id_DIRNAME/${fileName}`
    }

    id(callName: string): ts.Expression {

        const fileName = this.stableForTests ?
            baseName(this.sourceFile.fileName) :
            this.sourceFile.fileName

        const positionId = (this.stableForTests) ?
            this.stringId(callName, fileName) :
            this.sha1Id(callName, fileName)


        return this.stableForTests ?
            ts.factory.createStringLiteral(positionId) :
            ts.factory.createNumericLiteral("0x"+positionId)

    }
}

export function wrapInCompute(node: ts.ConciseBody, id: ts.Expression): ts.Expression {
    return ts.factory.createCallExpression(
        ts.factory.createPropertyAccessExpression(
            runtimeIdentifier(RuntimeNames.CONTEXT),
            runtimeIdentifier(RuntimeNames.COMPUTE)
        ),
        /*typeArguments*/ undefined,
        [
            id,
            ts.factory.createArrowFunction(
                /*modifiers*/ undefined,
                /*typeParameters*/ undefined,
                /*parameters*/ [],
                /*type*/ undefined,
                ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
                node
            )
        ]
    )
}

export function createComputeScope(pseudoStateCount: number, id: ts.Expression, typeArgument: ts.TypeNode | undefined): ts.VariableStatement {
    return constVariable(RuntimeNames.SCOPE,
        ts.factory.createCallExpression(
            ts.factory.createPropertyAccessExpression(
                runtimeIdentifier(RuntimeNames.CONTEXT),
                runtimeIdentifier(RuntimeNames.INTERNAL_SCOPE)
            ),
            typeArgument ? [typeArgument] : undefined,
            pseudoStateCount > 0
                ? [id, ts.factory.createNumericLiteral(pseudoStateCount)]
                : [id]
        )
    )
}

export function constVariable(name: string, initializer: ts.Expression): ts.VariableStatement {
    return ts.factory.createVariableStatement(
        undefined,
        ts.factory.createVariableDeclarationList(
            [ts.factory.createVariableDeclaration(
                ts.factory.createIdentifier(name),
                undefined,
                undefined,
                initializer
            )],
            ts.NodeFlags.Const
        )
    )
}

export function idPlusKey(positionalIdTracker: PositionalIdTracker): ts.Expression {
    return ts.factory.createBinaryExpression(
        runtimeIdentifier(RuntimeNames.ID),
        ts.factory.createToken(ts.SyntaxKind.PlusToken),
        ts.factory.createAsExpression(
            positionalIdTracker.id(RuntimeNames.__KEY),
            ts.factory.createTypeReferenceNode(RuntimeNames.ID_TYPE)
        )
    )
}

export function isAnyMemoKind(kind: FunctionKind|undefined): boolean {
    switch(kind) {
        case FunctionKind.MEMO:
        case FunctionKind.MEMO_INTRINSIC:
            return true
    }
    return false
}

export function isMemoKind(kind: FunctionKind|undefined): boolean {
    switch(kind) {
        case FunctionKind.MEMO:
            return true
    }
    return false
}

export function createContextType(): ts.TypeNode {
    return ts.factory.createTypeReferenceNode(
        runtimeIdentifier(RuntimeNames.CONTEXT_TYPE),
        undefined
    )
}

export function createIdType(): ts.TypeNode {
    return ts.factory.createTypeReferenceNode(
        runtimeIdentifier(RuntimeNames.ID_TYPE),
        undefined
    )
}

export function createHiddenParameters(): ts.ParameterDeclaration[] {
    const context = ts.factory.createParameterDeclaration(
        /*modifiers*/ undefined,
        /*dotDotDotToken*/ undefined,
        RuntimeNames.CONTEXT,
        /* questionToken */ undefined,
        createContextType(),
        /* initializer */ undefined

    )
    const id = ts.factory.createParameterDeclaration(
        /*modifiers*/ undefined,
        /*dotDotDotToken*/ undefined,
        RuntimeNames.ID,
        /* questionToken */ undefined,
        createIdType(),
        /* initializer */ undefined
    )

    return [context, id]
}

export function createContextTypeImport(importSource: string): ts.Statement {
    return ts.factory.createImportDeclaration(
        undefined,
        ts.factory.createImportClause(
          false,
          undefined,
            ts.factory.createNamedImports(
                [
                    ts.factory.createImportSpecifier(
                        false,
                        undefined,
                        ts.factory.createIdentifier(RuntimeNames.CONTEXT_TYPE)
                    ),
                    ts.factory.createImportSpecifier(
                        false,
                        undefined,
                        ts.factory.createIdentifier(RuntimeNames.ID_TYPE)
                    )
                ]
            )
        ),
        ts.factory.createStringLiteral(importSource),
        undefined
      )
}

export function setNeedTypeImports(rewrite: Rewrite) {
    rewrite.importTypesFrom = rewrite.pluginOptions.contextImport ?? RuntimeNames.CONTEXT_TYPE_DEFAULT_IMPORT
}

export function hiddenParameters(rewriter: Rewrite): ts.ParameterDeclaration[] {
    setNeedTypeImports(rewriter)
    return createHiddenParameters()
}

export function skipParenthesizedType(type: ts.TypeNode | undefined): ts.TypeNode | undefined {
    let current: ts.TypeNode|undefined = type
    while (current && ts.isParenthesizedTypeNode(current)) {
        current = current.type
    }
    return current
}

export function skipParenthesizedExpression(expr: ts.ParenthesizedExpression): ts.Expression {
    let current: ts.ParenthesizedExpression = expr
    while (ts.isParenthesizedExpression(current.expression)) {
        current = current.expression
    }
    return current.expression
}

export function localStateStatement(
    stateName: string,
    referencedEntity: ts.Expression,
    parameterIndex: number
): ts.Statement {
    return ts.factory.createVariableStatement(
        undefined,
        ts.factory.createVariableDeclarationList(
            [
                ts.factory.createVariableDeclaration(
                    parameterStateName(stateName),
                    undefined,
                    undefined,
                    ts.factory.createCallExpression(
                        ts.factory.createPropertyAccessExpression(
                            runtimeIdentifier(RuntimeNames.SCOPE),
                            runtimeIdentifier(RuntimeNames.INTERNAL_PARAMETER_STATE)
                        ),
                        undefined,
                        [ts.factory.createNumericLiteral(parameterIndex), referencedEntity]
                    )
                )
            ],
            ts.NodeFlags.Const
        )
    )
}

export function hasStaticModifier(node: ts.MethodDeclaration): boolean {
    return node.modifiers?.find(it => it.kind == ts.SyntaxKind.StaticKeyword) != undefined
}

export function error(message: any): any {
    console.log(message)
    console.trace()
    return undefined
}

export interface TransformerOptions {
    // Emit transformed functions to the console.
    trace?: boolean,
    // Store the transformed functions to this directory.
    keepTransformed?: string,
    // Use human readable call site IDs without directory paths.
    stableForTest?: boolean,
    // Import context and id types from alternative source
    contextImport?: string,
    // Dump sources with resolved memo annotations to unmemoized directory
    only_unmemoize?: boolean,
    // Target dir for unmemoization
    unmemoizeDir?: string,
    // Replace extension for output TS files
    extension?: string,
}

function baseName(path: string): string {
    return path.replace(/^.*\/(.*)$/, "$1")
}

export class Tracer {
    constructor (public options: TransformerOptions, public printer: ts.Printer) {
    }

    trace(msg: any) {
        if (!this.options.trace) return
        console.log(msg)
    }

    writeTextToFile(text: string, file: string) {
        fs.writeFileSync(file, text, 'utf8')
        this.trace("DUMP TO: " + file)
    }

    createDirs(dirs: string) {
        fs.mkdirSync(dirs, { recursive: true });
    }

    dumpFileName(sourceFile: ts.SourceFile, transformed: ts.FunctionLikeDeclarationBase): string|undefined {
        if (!this.options.keepTransformed) return undefined

        const outDir = (this.options.keepTransformed[0] == "/") ?
            this.options.keepTransformed :
            `${__dirname}/${this.options.keepTransformed}`

        this.createDirs(outDir)

        const sourceBaseName = baseName(sourceFile.fileName)
        if (!transformed.name) return
        if (!ts.isIdentifier(transformed.name)) return
        const fileName = `${ts.idText(transformed.name)}_${sourceBaseName}`
        return `${outDir}/${fileName}_dump`
    }

    keepTransformedFunction(transformed: ts.FunctionLikeDeclarationBase, sourceFile: ts.SourceFile) {
        const fileName = this.dumpFileName(sourceFile, transformed)
        if (!fileName) return

        const content = this.printer.printNode(ts.EmitHint.Unspecified, transformed, sourceFile)
        this.writeTextToFile(content+"\n", fileName)
    }
}
