/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {
    global,
    passNode,
    passNodeArray,
    unpackNonNullableNode,
    unpackNode,
    unpackNodeArray,
    assertValidPeer,
    AstNode,
    KNativePointer,
    nodeByType,
    ArktsObject,
    unpackString
} from "../../reexport-for-generated"

import { AnnotationUsage } from "./AnnotationUsage"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Es2pandaModifierFlags } from "./../Es2pandaEnums"
import { Es2pandaScriptFunctionFlags } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { FunctionSignature } from "./FunctionSignature"
import { Identifier } from "./Identifier"
import { ReturnStatement } from "./ReturnStatement"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { TypeNode } from "./TypeNode"
export class ScriptFunction extends AstNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 59)
        super(pointer)
    }
    static createScriptFunction(databody: AstNode | undefined, datasignature: FunctionSignature | undefined, datafuncFlags: number, dataflags: number): ScriptFunction {
        return new ScriptFunction(global.generatedEs2panda._CreateScriptFunction(global.context, passNode(databody), passNode(datasignature), datafuncFlags, dataflags))
    }
    static updateScriptFunction(original: ScriptFunction | undefined, databody: AstNode | undefined, datasignature: FunctionSignature | undefined, datafuncFlags: number, dataflags: number): ScriptFunction {
        return new ScriptFunction(global.generatedEs2panda._UpdateScriptFunction(global.context, passNode(original), passNode(databody), passNode(datasignature), datafuncFlags, dataflags))
    }
    get id(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ScriptFunctionId(global.context, this.peer))
    }
    get params(): readonly Expression[] {
        return unpackNodeArray(global.generatedEs2panda._ScriptFunctionParams(global.context, this.peer))
    }
    get returnStatements(): readonly ReturnStatement[] {
        return unpackNodeArray(global.generatedEs2panda._ScriptFunctionReturnStatements(global.context, this.peer))
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._ScriptFunctionTypeParams(global.context, this.peer))
    }
    get body(): AstNode | undefined {
        return unpackNode(global.generatedEs2panda._ScriptFunctionBody(global.context, this.peer))
    }
    /** @deprecated */
    addReturnStatement(returnStatement?: ReturnStatement): this {
        global.generatedEs2panda._ScriptFunctionAddReturnStatement(global.context, this.peer, passNode(returnStatement))
        return this
    }
    /** @deprecated */
    setBody(body?: AstNode): this {
        global.generatedEs2panda._ScriptFunctionSetBody(global.context, this.peer, passNode(body))
        return this
    }
    get returnTypeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._ScriptFunctionReturnTypeAnnotation(global.context, this.peer))
    }
    /** @deprecated */
    setReturnTypeAnnotation(node?: TypeNode): this {
        global.generatedEs2panda._ScriptFunctionSetReturnTypeAnnotation(global.context, this.peer, passNode(node))
        return this
    }
    get isEntryPoint(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsEntryPointConst(global.context, this.peer)
    }
    get isGenerator(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsGeneratorConst(global.context, this.peer)
    }
    get isAsyncFunc(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsAsyncFuncConst(global.context, this.peer)
    }
    get isAsyncImplFunc(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsAsyncImplFuncConst(global.context, this.peer)
    }
    get isArrow(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsArrowConst(global.context, this.peer)
    }
    get isOverload(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsOverloadConst(global.context, this.peer)
    }
    get isExternalOverload(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsExternalOverloadConst(global.context, this.peer)
    }
    get isConstructor(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsConstructorConst(global.context, this.peer)
    }
    get isGetter(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsGetterConst(global.context, this.peer)
    }
    get isSetter(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsSetterConst(global.context, this.peer)
    }
    get isExtensionAccessor(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsExtensionAccessorConst(global.context, this.peer)
    }
    get isMethod(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsMethodConst(global.context, this.peer)
    }
    get isProxy(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsProxyConst(global.context, this.peer)
    }
    get isStaticBlock(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsStaticBlockConst(global.context, this.peer)
    }
    get isEnum(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsEnumConst(global.context, this.peer)
    }
    get isHidden(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsHiddenConst(global.context, this.peer)
    }
    get isExternal(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsExternalConst(global.context, this.peer)
    }
    get isImplicitSuperCallNeeded(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsImplicitSuperCallNeededConst(global.context, this.peer)
    }
    get hasBody(): boolean {
        return global.generatedEs2panda._ScriptFunctionHasBodyConst(global.context, this.peer)
    }
    get hasRestParameter(): boolean {
        return global.generatedEs2panda._ScriptFunctionHasRestParameterConst(global.context, this.peer)
    }
    get hasReturnStatement(): boolean {
        return global.generatedEs2panda._ScriptFunctionHasReturnStatementConst(global.context, this.peer)
    }
    get hasThrowStatement(): boolean {
        return global.generatedEs2panda._ScriptFunctionHasThrowStatementConst(global.context, this.peer)
    }
    get isThrowing(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsThrowingConst(global.context, this.peer)
    }
    get isRethrowing(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsRethrowingConst(global.context, this.peer)
    }
    get isDynamic(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsDynamicConst(global.context, this.peer)
    }
    get isExtensionMethod(): boolean {
        return global.generatedEs2panda._ScriptFunctionIsExtensionMethodConst(global.context, this.peer)
    }
    get flags(): Es2pandaScriptFunctionFlags {
        return global.generatedEs2panda._ScriptFunctionFlagsConst(global.context, this.peer)
    }
    get hasReceiver(): boolean {
        return global.generatedEs2panda._ScriptFunctionHasReceiverConst(global.context, this.peer)
    }
    /** @deprecated */
    setIdent(id: Identifier): this {
        global.generatedEs2panda._ScriptFunctionSetIdent(global.context, this.peer, passNode(id))
        return this
    }
    /** @deprecated */
    addFlag(flags: Es2pandaScriptFunctionFlags): this {
        global.generatedEs2panda._ScriptFunctionAddFlag(global.context, this.peer, flags)
        return this
    }
    /** @deprecated */
    clearFlag(flags: Es2pandaScriptFunctionFlags): this {
        global.generatedEs2panda._ScriptFunctionClearFlag(global.context, this.peer, flags)
        return this
    }
    /** @deprecated */
    addModifier(flags: Es2pandaModifierFlags): this {
        global.generatedEs2panda._ScriptFunctionAddModifier(global.context, this.peer, flags)
        return this
    }
    get formalParamsLength(): number {
        return global.generatedEs2panda._ScriptFunctionFormalParamsLengthConst(global.context, this.peer)
    }
    /** @deprecated */
    setIsolatedDeclgenReturnType(type: string): this {
        global.generatedEs2panda._ScriptFunctionSetIsolatedDeclgenReturnType(global.context, this.peer, type)
        return this
    }
    get isolatedDeclgenReturnType(): string {
        return unpackString(global.generatedEs2panda._ScriptFunctionGetIsolatedDeclgenReturnTypeConst(global.context, this.peer))
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ScriptFunctionAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._ScriptFunctionSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isScriptFunction(node: object | undefined): node is ScriptFunction {
    return node instanceof ScriptFunction
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_SCRIPT_FUNCTION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_SCRIPT_FUNCTION, (peer: KNativePointer) => new ScriptFunction(peer))
}