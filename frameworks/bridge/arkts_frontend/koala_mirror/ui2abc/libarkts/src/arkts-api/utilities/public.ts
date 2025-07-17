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

import { global } from "../static/global"
import { isNumber, throwError, withWarning } from "../../utils"
import { KNativePointer, nullptr, KInt} from "@koalaui/interop"
import { passNode, passNodeArray, unpackNodeArray, unpackNonNullableNode, passString } from "./private"
import { Es2pandaContextState, Es2pandaModifierFlags } from "../../generated/Es2pandaEnums"
import type { AstNode } from "../peers/AstNode"
import { isSameNativeObject } from "../peers/ArktsObject"
import {
    type AnnotationUsage,
    ClassDefinition,
    ClassProperty,
    ETSModule,
    isClassDefinition,
    isFunctionDeclaration,
    isMemberExpression,
    isScriptFunction,
    isIdentifier,
    isETSModule,
    ImportSpecifier
} from "../../generated"
import { Config } from "../peers/Config"
import { Context } from "../peers/Context"
import { NodeCache } from "../node-cache"
import { listPrograms } from "../plugins"

/**
 * Improve: Replace or remove with better naming
 * 
 * @deprecated
 */
export function createETSModuleFromContext(): ETSModule {
    let program = global.es2panda._ContextProgram(global.context)
    if (program == nullptr) {
        throw new Error(`Program is null for context ${global.context.toString(16)}`)
    }
    const ast = global.es2panda._ProgramAst(global.context, program)
    if (ast == nullptr) {
        throw new Error(`AST is null for program ${program.toString(16)}`)

    }
    return new ETSModule(ast)
}

/**
 * Now used only in tests
 * Improve: Remove or replace with better method
 * 
 * @deprecated
 */
export function createETSModuleFromSource(
    source: string,
    state: Es2pandaContextState = Es2pandaContextState.ES2PANDA_STATE_PARSED,
): ETSModule {
    if (!global.configIsInitialized()) {
        global.config = Config.createDefault().peer
    }
    global.compilerContext = Context.createFromString(source)
    proceedToState(state)
    let program = global.es2panda._ContextProgram(global.compilerContext.peer)
    if (program == nullptr)
        throw new Error(`Program is null for ${source} 0x${global.compilerContext.peer.toString(16)}`)
    return new ETSModule(global.es2panda._ProgramAst(global.context, program))
}

export function metaDatabase(fileName: string): string {
    if (fileName.endsWith(".meta.json")) throw new Error(`Must pass source, not database: ${fileName}`)
    return `${fileName}.meta.json`
}

export function checkErrors() {
    if (global.es2panda._ContextState(global.context) === Es2pandaContextState.ES2PANDA_STATE_ERROR) {
        console.log()
        global.es2panda._DestroyConfig(global.config)
        console.log()
        process.exit(1)
    }
}

export function proceedToState(state: Es2pandaContextState): void {
    if (state <= global.es2panda._ContextState(global.context)) {
        return
    }
    const before = Date.now()
    global.es2panda._ProceedToState(global.context, state)
    const after = Date.now()
    global.profiler.proceededToState(after-before)
    NodeCache.clear()
    checkErrors()
}

/** @deprecated Use {@link rebindContext} instead */
export function rebindSubtree(node: AstNode): void {
    global.es2panda._AstNodeRebind(global.context, node.peer)
    checkErrors()
}

/** @deprecated Use {@link recheckSubtree} instead */
export function recheckSubtree(node: AstNode): void {
    global.es2panda._AstNodeRecheck(global.context, node.peer)
    checkErrors()
}

export function rebindContext(context: KNativePointer = global.context): void {
    global.es2panda._AstNodeRebind(
        context,
        global.es2panda._ProgramAst(
            context,
            global.es2panda._ContextProgram(
                context
            )
        )
    )
    checkErrors()
}

export function recheckContext(context: KNativePointer = global.context): void {
    global.es2panda._AstNodeRecheck(
        context,
        global.es2panda._ProgramAst(
            context,
            global.es2panda._ContextProgram(
                context,
            )
        )
    )
    checkErrors()
}

export function getDecl(node: AstNode): AstNode | undefined {
    if (isMemberExpression(node)) {
        return getDecl(node.property!)
    }
    return getPeerDecl(passNode(node))
}

export function getPeerDecl(peer: KNativePointer): AstNode | undefined {
    const decl = global.es2panda._DeclarationFromIdentifier(global.context, peer)
    if (decl === nullptr) {
        return undefined
    }
    return unpackNonNullableNode(decl)
}

export function getAnnotations(node: AstNode): readonly AnnotationUsage[] {
    if (!isFunctionDeclaration(node) && !isScriptFunction(node) && !isClassDefinition(node)) {
        throwError('for now annotations allowed only for: functionDeclaration, scriptFunction, classDefinition')
    }
    return unpackNodeArray(global.es2panda._AnnotationAllowedAnnotations(global.context, node.peer, nullptr))
}

export function getOriginalNode(node: AstNode): AstNode {
    if (node === undefined) {
        // Improve: fix this
        throwError('there is no arkts pair of ts node (unable to getOriginalNode)')
    }
    if (node.originalPeer === nullptr) {
        return node
    }
    return unpackNonNullableNode(node.originalPeer)
}

export function getFileName(): string {
    return global.filePath
}

// Improve: It seems like Definition overrides AstNode  modifiers
// with it's own modifiers which is completely unrelated set of flags.
// Use this function if you need
// the language level modifiers: public, declare, export, etc.
export function classDefinitionFlags(node: ClassDefinition): Es2pandaModifierFlags {
    return global.generatedEs2panda._AstNodeModifiers(global.context, node.peer)
}

// Improve: ClassProperty's optional flag is set by AstNode's modifiers flags.
export function classPropertySetOptional(node: ClassProperty, value: boolean): ClassProperty {
    if (value) {
        node.modifierFlags |= Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL;
    } else {
        node.modifierFlags &= Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL;
    }
    return node;
}

export function hasModifierFlag(node: AstNode, flag: Es2pandaModifierFlags): boolean {
    if (!node) return false;

    let modifiers;
    if (isClassDefinition(node)) {
        modifiers = classDefinitionFlags(node);
    } else {
        modifiers = node.modifierFlags
    }
    return (modifiers & flag) === flag;
}

export function modifiersToString(modifiers: Es2pandaModifierFlags): string {
     return Object.values(Es2pandaModifierFlags)
            .filter(isNumber)
            .map(it => {
                console.log(it.valueOf(), Es2pandaModifierFlags[it], modifiers.valueOf() & it)
                return ((modifiers.valueOf() & it) === it) ? Es2pandaModifierFlags[it] : ""
            }).join(" ")
}

export function nameIfIdentifier(node: AstNode): string {
    return isIdentifier(node) ? `'${node.name}'` : ""
}

export function nameIfETSModule(node: AstNode): string {
    return isETSModule(node) ? `'${node.ident?.name}'` : ""
}

export function asString(node: AstNode|undefined): string {
    return `${node?.constructor.name} ${node ? nameIfIdentifier(node) : undefined}`
}

const defaultPandaSdk = "../../../incremental/tools/panda/node_modules/@panda/sdk"


export function findStdlib(): string {
    const sdk = process.env.PANDA_SDK_PATH ?? withWarning(
        defaultPandaSdk,
        `PANDA_SDK_PATH not set, assuming ${defaultPandaSdk}`
    )
    return `${sdk}/ets/stdlib`
}

export function collectDependencies(files: string[], configPath: string): string[] {
    const result = new Set<string>()
    for (let file of files) {
        const context = Context.createFromFile(file, configPath, findStdlib(), "/tmp/foo.abc")!
        global.compilerContext = context
        proceedToState(Es2pandaContextState.ES2PANDA_STATE_PARSED)
        listPrograms(context.program).forEach(it => result.add(it.absoluteName))
        context.destroy()
    }
    return Array.from(result)
}

export function generateTsDeclarationsFromContext(
  outputDeclEts: string,
  outputEts: string,
  exportAll: boolean,
  isolated: boolean
): KInt {
  return global.es2panda._GenerateTsDeclarationsFromContext(
    global.context,
    passString(outputDeclEts),
    passString(outputEts),
    exportAll,
    isolated
  );
}

export function setAllParents(ast: AstNode): void {
    global.es2panda._AstNodeUpdateAll(global.context, ast.peer);
}