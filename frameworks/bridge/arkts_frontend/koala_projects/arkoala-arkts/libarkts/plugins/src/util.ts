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

import * as ts from "@koalaui/libarkts"
import * as fs from 'fs'

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

export function asString(node: ts.Node | undefined): string {
    if (node === undefined) {
        return "undefined node"
    }
    if (ts.isIdentifier(node)) {
        return node.text
    }
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
    // Replace extension for output TS files
    extension?: string,
}

function baseName(path: string): string {
    return path.replace(/^.*\/(.*)$/, "$1")
}

export class Tracer {
    constructor (
        public options: TransformerOptions,
        // TODO: implement ts.Printer
        // public printer: arkts.Printer
    ) {}

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

    dumpFileName(sourceFile: ts.SourceFile, transformed: ts.FunctionLikeDeclarationBase): string | undefined {
        if (!this.options.keepTransformed) {
            return undefined
        }

        const outDir = (this.options.keepTransformed[0] == "/") ?
            this.options.keepTransformed :
            `${__dirname}/${this.options.keepTransformed}`

        this.createDirs(outDir)

        const sourceBaseName = baseName(sourceFile.fileName)
        if (!transformed.name) return
        if (!ts.isIdentifier(transformed.name)) return
        const fileName = `${transformed.name.text}_${sourceBaseName}`
        return `${outDir}/${fileName}_dump`
    }

    keepTransformedFunction(transformed: ts.FunctionLikeDeclarationBase, sourceFile: ts.SourceFile) {
        const fileName = this.dumpFileName(sourceFile, transformed)
        if (!fileName) return

        // TODO: implement ts.Printer
        // const content = this.printer.printNode(arkts.EmitHint.Unspecified, transformed, sourceFile)
        // this.writeTextToFile(content+"\n", fileName)
    }
}

export enum RuntimeNames {
    // COMPUTE = "compute",
    // CONTEXT = "__memo_context",
    // ID = "__memo_id",
    // SCOPE = "__memo_scope",
    // INTERNAL_PARAMETER_STATE = "param",
    // INTERNAL_VALUE = "cached",
    // INTERNAL_VALUE_NEW = "recache",
    // INTERNAL_SCOPE = "scope",
    // INTERNAL_VALUE_OK = "unchanged",
    // CONTENT = "content",
    // VALUE = "value",
    // __CONTEXT = "__context",
    // __ID = "__id",
    // __KEY = "__key",
    // __STATE = "__state",
    // CONTEXT_TYPE = "__memo_context_type",
    // ID_TYPE = "__memo_id_type",
    // TRANSFORMED_TYPE = "__memo_transformed",
    // SYNTHETIC_RETURN_MARK = "__synthetic_return_value",
    // CONTEXT_TYPE_DEFAULT_IMPORT = "@koalaui/runtime",
    ANNOTATION = "_memo",
    ANNOTATION_INTRINSIC = "_memo:intrinsic",
    ANNOTATION_ENTRY = "_memo:entry",
    ANNOTATION_SKIP = "_skip:memo", // skip binding to parameter changes
    ANNOTATION_STABLE = "_memo:stable", // assume this should not be tracked
}

export function findFunctionDeclaration(node: ts.Node): ts.FunctionDeclaration | undefined {
    while (node.kind !== ts.SyntaxKind.SourceFile) {
        if (ts.isFunctionDeclaration(node)) {
            return node
        }
        node = node.parent
    }
    return undefined
}
