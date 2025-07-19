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

import { global } from '../static/global';
import { isNumber, throwError, getEnumName } from '../../../utils';
import { KNativePointer, KInt, nullptr } from '@koalaui/interop';
import { passNode, passString, passStringArray, unpackNodeArray, unpackNonNullableNode, unpackString } from './private';
import { isFunctionDeclaration, isMemberExpression, isMethodDefinition, isNumberLiteral } from '../factory/nodeTests';
import {
    Es2pandaContextState,
    Es2pandaMethodDefinitionKind,
    Es2pandaModifierFlags,
} from '../../../generated/Es2pandaEnums';
import type { AstNode } from '../peers/AstNode';
import {
    ClassDefinition,
    ClassProperty,
    ETSImportDeclaration,
    ImportSpecifier,
    isClassDefinition,
    isIdentifier,
    isObjectExpression,
    isProperty,
    isScriptFunction,
    isTSInterfaceDeclaration,
    Property,
    type AnnotationUsage,
} from '../../../generated';
import { Program } from '../peers/Program';
import { clearNodeCache, nodeByType } from '../class-by-peer';
import { SourcePosition } from '../../../arkts-api/peers/SourcePosition';
import { MemberExpression } from '../to-be-generated/MemberExpression';

export function proceedToState(state: Es2pandaContextState, context: KNativePointer, forceDtsEmit = false): void {
    console.log('[TS WRAPPER] PROCEED TO STATE: ', getEnumName(Es2pandaContextState, state));
    if (global.es2panda._ContextState(context) === Es2pandaContextState.ES2PANDA_STATE_ERROR) {
        clearNodeCache();
        processErrorState(state, context, forceDtsEmit);
    }
    if (state <= global.es2panda._ContextState(context)) {
        console.log('[TS WRAPPER] PROCEED TO STATE: SKIPPING');
        return;
    }
    clearNodeCache();
    global.es2panda._ProceedToState(context, state);
    processErrorState(state, context, forceDtsEmit);
}

function processErrorState(state: Es2pandaContextState, context: KNativePointer, forceDtsEmit = false): void {
    try {
        if (global.es2panda._ContextState(context) === Es2pandaContextState.ES2PANDA_STATE_ERROR && !forceDtsEmit) {
            const errorMessage = unpackString(global.es2panda._ContextErrorMessage(context));
            if (errorMessage === undefined) {
                throwError(`Could not get ContextErrorMessage`);
            }
            throwError([`Failed to proceed to ${Es2pandaContextState[state]}`, errorMessage].join(`\n`));
        }
    } catch (e) {
        global.es2panda._DestroyContext(context);
        throw e;
    }
}

export function startChecker(): boolean {
    return global.es2panda._CheckerStartChecker(global.context);
}

export function recheckSubtree(node: AstNode): void {
    global.es2panda._AstNodeRecheck(global.context, node.peer);
}

export function rebindSubtree(node: AstNode): void {
    global.es2panda._AstNodeRebind(global.context, node.peer);
}

export function getDecl(node: AstNode): AstNode | undefined {
    if (isMemberExpression(node)) {
        return getDeclFromArrayOrObjectMember(node);
    }
    if (isObjectExpression(node)) {
        return getPeerObjectDecl(passNode(node));
    }
    const decl = getPeerDecl(passNode(node));
    if (!!decl) {
        return decl;
    }
    if (!!node.parent && isProperty(node.parent)) {
        return getDeclFromProperty(node.parent);
    }
    return undefined;
}

function getDeclFromProperty(node: Property): AstNode | undefined {
    if (!node.key) {
        return undefined;
    }
    if (!!node.parent && !isObjectExpression(node.parent)) {
        return getPeerDecl(passNode(node.key));
    }
    return getDeclFromObjectExpressionProperty(node);
}

function getDeclFromObjectExpressionProperty(node: Property): AstNode | undefined {
    const declNode = getPeerObjectDecl(passNode(node.parent));
    if (!declNode || !node.key || !isIdentifier(node.key)) {
        return undefined;
    }
    let body: readonly AstNode[] = [];
    if (isClassDefinition(declNode)) {
        body = declNode.body;
    } else if (isTSInterfaceDeclaration(declNode)) {
        body = declNode.body?.body ?? [];
    }
    return body.find(
        (statement) =>
            isMethodDefinition(statement) &&
            statement.kind === Es2pandaMethodDefinitionKind.METHOD_DEFINITION_KIND_GET &&
            !!statement.name &&
            !!node.key &&
            isIdentifier(node.key) &&
            statement.name.name === node.key.name
    );
}

function getDeclFromArrayOrObjectMember(node: MemberExpression): AstNode | undefined {
    if (isNumberLiteral(node.property)) {
        return getDecl(node.object);
    }
    return getDecl(node.property);
}

export function getPeerDecl(peer: KNativePointer): AstNode | undefined {
    const decl = global.es2panda._DeclarationFromIdentifier(global.context, peer);
    if (decl === nullptr) {
        return undefined;
    }
    return unpackNonNullableNode(decl);
}

export function getPeerObjectDecl(peer: KNativePointer): AstNode | undefined {
    const decl = global.es2panda._ClassVariableDeclaration(global.context, peer);
    if (decl === nullptr) {
        return undefined;
    }
    return unpackNonNullableNode(decl);
}

export function getAnnotations(node: AstNode): readonly AnnotationUsage[] {
    if (!isFunctionDeclaration(node) && !isScriptFunction(node) && !isClassDefinition(node)) {
        throwError('for now annotations allowed only for: functionDeclaration, scriptFunction, classDefinition');
    }
    return unpackNodeArray(global.es2panda._AnnotationAllowedAnnotations(global.context, node.peer, nullptr));
}

export function getOriginalNode(node: AstNode): AstNode {
    if (node === undefined) {
        // Improve: fix this
        throwError('there is no arkts pair of ts node (unable to getOriginalNode)');
    }
    if (node.originalPeer === nullptr) {
        return node;
    }
    return unpackNonNullableNode(node.originalPeer);
}

export function getFileName(): string {
    return global.filePath;
}

export function classDefinitionSetFromStructModifier(node: ClassDefinition): void {
    global.generatedEs2panda._ClassDefinitionSetFromStructModifier(global.context, node.peer);
}

export function classDefinitionIsFromStructConst(node: ClassDefinition): boolean {
    return global.generatedEs2panda._ClassDefinitionIsFromStructConst(global.context, node.peer);
}

export function ImportSpecifierSetRemovable(node: ImportSpecifier): void {
    global.generatedEs2panda._ImportSpecifierSetRemovable(global.context, node.peer, true);
}

export function ImportSpecifierIsRemovableConst(node: ImportSpecifier): boolean {
    return global.generatedEs2panda._ImportSpecifierIsRemovableConst(global.context, node.peer);
}

// Improve: It seems like Definition overrides AstNode  modifiers
// with it's own modifiers which is completely unrelated set of flags.
// Use this function if you need
// the language level modifiers: public, declare, export, etc.
export function classDefinitionFlags(node: ClassDefinition): Es2pandaModifierFlags {
    return global.generatedEs2panda._AstNodeModifiers(global.context, node.peer);
}

// Improve: Import statements should be inserted to the statements
export function importDeclarationInsert(node: ETSImportDeclaration, program: Program): void {
    global.es2panda._InsertETSImportDeclarationAndParse(global.context, program.peer, node.peer);
}

export function getProgramFromAstNode(node: AstNode): Program {
    return new Program(global.es2panda._AstNodeProgram(global.context, node.peer));
}

export function hasModifierFlag(node: AstNode, flag: Es2pandaModifierFlags): boolean {
    if (!node) return false;

    let modifiers;
    if (isClassDefinition(node)) {
        modifiers = classDefinitionFlags(node);
    } else {
        modifiers = node.modifiers;
    }
    return (modifiers & flag) === flag;
}

// Improve: ClassProperty's optional flag is set by AstNode's modifiers flags.
export function classPropertySetOptional(node: ClassProperty, value: boolean): ClassProperty {
    if (value) {
        node.modifiers |= Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL;
    } else {
        node.modifiers &= Es2pandaModifierFlags.MODIFIER_FLAGS_OPTIONAL;
    }
    return node;
}

export function modifiersToString(modifiers: Es2pandaModifierFlags): string {
    return Object.values(Es2pandaModifierFlags)
        .filter(isNumber)
        .map((it) => {
            console.log(it.valueOf(), Es2pandaModifierFlags[it], modifiers.valueOf() & it);
            return (modifiers.valueOf() & it) === it ? Es2pandaModifierFlags[it] : '';
        })
        .join(' ');
}
export function destroyConfig(config: KNativePointer): void {
    global.es2panda._DestroyConfig(config);
    global.resetConfig();
}

export function setAllParents(ast: AstNode): void {
    global.es2panda._AstNodeUpdateAll(global.context, ast.peer);
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

export function generateStaticDeclarationsFromContext(outputPath: string): KInt {
    return global.es2panda._GenerateStaticDeclarationsFromContext(
        global.context,
        passString(outputPath)
    );
}

export function isDefaultAccessModifierClassProperty(property: ClassProperty): boolean {
    return global.generatedEs2panda._ClassPropertyIsDefaultAccessModifierConst(global.context, property.peer);
}

export function getStartPosition(node: AstNode): SourcePosition {
    return new SourcePosition(global.generatedEs2panda._AstNodeStartConst(global.context, node.peer));
}

export function getEndPosition(node: AstNode): SourcePosition {
    return new SourcePosition(global.generatedEs2panda._AstNodeEndConst(global.context, node.peer));
}

export function MemInitialize(): void {
    global.es2panda._MemInitialize();
}

export function MemFinalize(): void {
    global.es2panda._MemFinalize();
}

export function CreateGlobalContext(
    config: KNativePointer,
    externalFileList: string[],
    fileNum: KInt,
    lspUsage: boolean
): KNativePointer {
    return global.es2panda._CreateGlobalContext(config, passStringArray(externalFileList), fileNum, lspUsage);
}

export function DestroyGlobalContext(context: KNativePointer): void {
    global.es2panda._DestroyGlobalContext(context);
}

export function CreateCacheContextFromFile(
    configPtr: KNativePointer,
    filename: string,
    globalContext: KNativePointer,
    isExternal: Boolean
): KNativePointer {
    return global.es2panda._CreateCacheContextFromFile(configPtr, passString(filename), globalContext, isExternal);
}

export function insertGlobalStructInfo(structName: string): void {
    global.es2panda._InsertGlobalStructInfo(global.context, passString(structName));
}

export function hasGlobalStructInfo(structName: string): boolean {
    return global.es2panda._HasGlobalStructInfo(global.context, passString(structName));
}
