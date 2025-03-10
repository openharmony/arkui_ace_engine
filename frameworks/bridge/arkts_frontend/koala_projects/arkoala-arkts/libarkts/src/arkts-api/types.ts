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
import { global } from "./static/global"
import { KInt, KNativePointer, KNativePointer as KPtr, nullptr } from "@koalaui/interop"
import {
    Es2pandaContextState,
    Es2pandaImportKinds,
    Es2pandaMethodDefinitionKind,
    Es2pandaModifierFlags,
    Es2pandaScriptFunctionFlags,
    Es2pandaVariableDeclarationKind,
    Es2pandaVariableDeclaratorFlag,
} from "../generated/Es2pandaEnums"
import {
    allFlags,
    arrayOfNullptr,
    assertValidPeer,
    nodeType,
    passNode,
    passNodeArray,
    unpackNode,
    unpackNodeArray,
    unpackNonNullableNode,
    updatePeerByNode,
} from "./utilities/private"
import { proceedToState } from "./utilities/public"
import { Es2pandaAstNodeType } from "../Es2pandaEnums"
import { AstNode } from "./peers/AstNode"
import { ArktsObject } from "./peers/ArktsObject"
import { Config } from "./peers/Config"
import { Context } from "./peers/Context"
import * as path from "node:path"
import { nodeByType } from "./class-by-peer"
import { MemberExpression } from "./to-be-generated/MemberExpression"
import {
    AnnotationUsage,
    BlockStatement,
    ClassDefinition,
    Expression,
    FunctionSignature,
    Identifier,
    ImportSpecifier,
    Literal,
    StringLiteral,
    TSTypeParameterDeclaration,
    TSTypeParameterInstantiation,
    TypeNode
} from "../generated"

export class EtsScript extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_ETS_MODULE)
        super(peer)
    }

    // TODO:
    // static create(
    //     statementList: Statement[]
    // ): EtsScript {
    // }

    static fromContext(): EtsScript {
        return new EtsScript(global.es2panda._ProgramAst(global.context, global.es2panda._ContextProgram(global.context)))
    }

    /**
     * @deprecated
     */
    static createFromSource(
        source: string,
        state: Es2pandaContextState = Es2pandaContextState.ES2PANDA_STATE_PARSED,
    ): EtsScript {
        if (!global.configIsInitialized()) {
            global.config = Config.createDefault().peer
        }
        global.compilerContext = Context.createFromString(source)
        proceedToState(state)
        return new EtsScript(global.es2panda._ProgramAst(global.context, global.es2panda._ContextProgram(global.context)))
    }

    /**
     * @deprecated
     */
    static updateByStatements(
        node: EtsScript,
        statements: readonly AstNode[],
    ): EtsScript {
        global.generatedEs2panda._BlockStatementSetStatements(global.context, node.peer, passNodeArray(statements), statements.length)
        return node
    }

    get statements(): readonly AstNode[] {
        return unpackNodeArray(global.generatedEs2panda._BlockStatementStatements(global.context, this.peer))
    }

    set statements(nodes: readonly AstNode[]) {
        global.generatedEs2panda._BlockStatementSetStatements(global.context, this.peer, passNodeArray(nodes), nodes.length)
    }
}

export class ExpressionStatement extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_EXPRESSION_STATEMENT)
        super(peer)
        this.expression = unpackNonNullableNode(global.generatedEs2panda._ExpressionStatementGetExpression(global.context, this.peer))
    }

    static create(
        expression: AstNode,
    ): ExpressionStatement {
        return new ExpressionStatement(
            global.generatedEs2panda._CreateExpressionStatement(
                global.context,
                expression.peer
            )
        )
    }

    readonly expression: AstNode
}

// TODO:
//  the CallExpression idl Create signature doesn't include the trailing block at all.
//  Need to clarify with the compiler people if they will provide create signature with a trailing block argument.
export class CallExpression extends Expression {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_CALL_EXPRESSION)
        super(peer)
        this.expression = unpackNonNullableNode(
            global.generatedEs2panda._CallExpressionCallee(global.context, this.peer))
        const tsTypeParameterInstantiation = unpackNode(global.generatedEs2panda._CallExpressionTypeParams(global.context, this.peer))
        this.typeArguments = tsTypeParameterInstantiation ?
            unpackNodeArray(global.generatedEs2panda._TSTypeParameterInstantiationParamsConst(global.context, tsTypeParameterInstantiation.peer)) : undefined
        this.arguments = unpackNodeArray(
            global.generatedEs2panda._CallExpressionArguments(global.context, this.peer))
        this.trailingBlock = unpackNode(
            global.generatedEs2panda._CallExpressionTrailingBlockConst(global.context, this.peer))
    }

    static create(
        expression: AstNode,
        typeArguments: readonly TypeNode[] | undefined,
        args: readonly AstNode[] | undefined,
        trailingBlock: AstNode | undefined = undefined
    ): CallExpression {
        const peer = global.generatedEs2panda._CreateCallExpression(
            global.context,
            passNode(expression),
            passNodeArray(args),
            args?.length ?? 0,
            typeArguments ? passNode(TSTypeParameterInstantiation.createTSTypeParameterInstantiation(typeArguments)) : nullptr,
            false,
            false
        )
        const call = new CallExpression(peer)
        if (trailingBlock) {
            global.generatedEs2panda._CallExpressionSetTrailingBlock(
                global.context, peer, trailingBlock?.peer
            )
        }
        return call
    }

    readonly expression: AstNode // Expression
    readonly typeArguments: readonly TypeNode[] | undefined
    readonly arguments: readonly Expression[]
    readonly trailingBlock: AstNode|undefined // BlockStatement
}

export class TSUnionType extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_TS_UNION_TYPE)
        super(peer)
        this.types = unpackNodeArray(global.generatedEs2panda._TSUnionTypeTypesConst(global.context, this.peer))
    }

    static create(
        node: undefined | TSUnionType,
        types: AstNode[],
    ): TSUnionType {
        return new TSUnionType(
            updatePeerByNode(
                global.generatedEs2panda._CreateTSUnionType(
                    global.context,
                    passNodeArray(types),
                    types.length
                ),
                node
            )
        )
    }

    readonly types: readonly AstNode[]
}

export class NumberLiteral extends Literal {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_NUMBER_LITERAL)
        super(peer)
        this.value = 0.0
    }

    static create(
        value: number,
    ): NumberLiteral {
        return new NumberLiteral(
            global.es2panda._CreateNumberLiteral(
                global.context,
                value
            )
        )
    }

    protected override dumpMessage(): string {
        return ` <value: ${this.value}>`
    }

    readonly value: number = 0.0
}

export class ScriptFunction extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_SCRIPT_FUNCTION)
        super(peer)
        this.parameters = unpackNodeArray(global.generatedEs2panda._ScriptFunctionParams(global.context, this.peer))
        this.typeParamsDecl = unpackNode(global.generatedEs2panda._ScriptFunctionTypeParams(global.context, this.peer))
        this.returnTypeAnnotation = unpackNode(global.generatedEs2panda._ScriptFunctionReturnTypeAnnotation(global.context, this.peer))
        this.body = unpackNode(global.generatedEs2panda._ScriptFunctionBody(global.context, this.peer))
        // this.signature = unpackNode(global.generatedEs2panda._ScriptFunctionSignature(global.context, this.peer))
        // this.declare = global.generatedEs2panda._ScriptFunctionDeclareConst(global.context, this.peer)
        this.ident = unpackNode(global.generatedEs2panda._ScriptFunctionId(global.context, this.peer))

        this.scriptFunctionFlags = this._correctScriptFunctionFlags()
    }

    static create(
        body: AstNode | undefined,
        functionFlags: Es2pandaScriptFunctionFlags,
        modifierFlags: Es2pandaModifierFlags,
        declare: boolean,
        ident: Identifier | undefined,
        parameters: ETSParameterExpression[]|undefined,
        typeParamsDecl: TSTypeParameterDeclaration|undefined,
        returnTypeAnnotation: TypeNode|undefined,
        annotations?: AnnotationUsage[],
    ): ScriptFunction {
        const peer = global.generatedEs2panda._CreateScriptFunction(
            global.context,
            passNode(body),
            FunctionSignature.createFunctionSignature(
                typeParamsDecl,
                parameters ?? [],
                returnTypeAnnotation,
                false
            ).peer,
            functionFlags,
            modifierFlags
        )
        if (ident !== undefined) {
            global.generatedEs2panda._ScriptFunctionSetIdent(global.context, peer, ident.peer)
        }
        const res = new ScriptFunction(peer)
        if (annotations) {
            res.annotations = annotations
        }
        return res
    }

    setIdent(id: Identifier): ScriptFunction {
        assertValidPeer(id.peer, Es2pandaAstNodeType.AST_NODE_TYPE_IDENTIFIER);
        global.generatedEs2panda._ScriptFunctionSetIdent(global.context, this.peer, id.peer);
        return this;
    }

    protected override dumpMessage(): string {
        const scriptFunctionFlags = global.generatedEs2panda._ScriptFunctionFlagsConst(global.context, this.peer)
        return ` <scriptFunctionFlags: ${scriptFunctionFlags} (${scriptFunctionFlags.toString(2).split("").reverse().join("")})>`
    }

    private _correctScriptFunctionFlags(): KInt {
        let flags: KInt = global.generatedEs2panda._ScriptFunctionFlagsConst(global.context, this.peer)
        if (this._hasReturn()) {
            flags |= Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_HAS_RETURN
            global.generatedEs2panda._ScriptFunctionAddFlag(global.context, this.peer, Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_HAS_RETURN)
        }
        if (this._isAsync()) {
            flags |= Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ASYNC
            global.generatedEs2panda._ScriptFunctionAddFlag(global.context, this.peer, Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ASYNC)
        }
        return flags
    }

    private _hasReturn(): boolean {
        if (this.body === undefined) {
            return false
        }
        let hasReturn: boolean = false
        // TODO: goes through whole subtree, optimizable (unnecessary now)
        this.body.getSubtree().forEach(
            (node: AstNode) => {
                hasReturn = hasReturn || nodeType(node) === Es2pandaAstNodeType.AST_NODE_TYPE_RETURN_STATEMENT
            }
        )
        return hasReturn
    }

    private _isAsync(): boolean {
        return (this.modifiers & Es2pandaModifierFlags.MODIFIER_FLAGS_ASYNC) !== 0
    }

    readonly parameters: ETSParameterExpression[]
    readonly typeParamsDecl?: TSTypeParameterDeclaration
    readonly returnTypeAnnotation: TypeNode | undefined
    readonly body?: BlockStatement
    // readonly signature: FunctionSignature
    readonly scriptFunctionFlags: KInt
    readonly ident?: Identifier

    get annotations(): AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ScriptFunctionAnnotations(
            global.context,
            this.peer
        ))
    }

    set annotations(newAnnotations: AnnotationUsage[]) {
        global.generatedEs2panda._ScriptFunctionSetAnnotations(
            global.context,
            this.peer,
            passNodeArray(newAnnotations),
            newAnnotations.length
        );
    }
}

export class ArrowFunctionExpression extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_ARROW_FUNCTION_EXPRESSION)
        super(peer)
        this.scriptFunction = unpackNonNullableNode(global.generatedEs2panda._ArrowFunctionExpressionFunction(global.context, this.peer))
    }

    static create(
        func: ScriptFunction,
    ): ArrowFunctionExpression {
        return new ArrowFunctionExpression(
            global.generatedEs2panda._CreateArrowFunctionExpression(
                global.context,
                passNode(func)
            )
        )
    }

    readonly scriptFunction: ScriptFunction
}

export class FunctionDeclaration extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_DECLARATION)
        super(peer)
        this.scriptFunction = unpackNonNullableNode(global.generatedEs2panda._FunctionDeclarationFunction(global.context, this.peer))
        this.parameters = unpackNodeArray(global.generatedEs2panda._ScriptFunctionParams(global.context, this.scriptFunction.peer))
        this.name = unpackNode(global.generatedEs2panda._ScriptFunctionId(global.context, this.scriptFunction.peer))
        this.body = unpackNode(global.generatedEs2panda._ScriptFunctionBody(global.context, this.scriptFunction.peer))
        this.typeParamsDecl = unpackNode(global.generatedEs2panda._ScriptFunctionTypeParams(global.context, this.scriptFunction.peer))
        this.returnType = unpackNode(global.generatedEs2panda._ScriptFunctionReturnTypeAnnotation(global.context, this.scriptFunction.peer))
        this.isAnon = global.generatedEs2panda._FunctionDeclarationIsAnonymousConst(global.context, this.peer)
    }

    static create(
        scriptFunction: ScriptFunction,
        isAnon: boolean,
        annotations?: AnnotationUsage[]
    ): FunctionDeclaration {
        const res = new FunctionDeclaration(
            global.generatedEs2panda._CreateFunctionDeclaration(
                global.context,
                scriptFunction.peer,
                // TODO: support annotations
                arrayOfNullptr,
                0,
                isAnon
            )
        )
        // TODO: maybe wrong
        res.modifiers = scriptFunction.modifiers
        if (annotations) {
            res.annotations = annotations
        }
        return res
    }

    get annotations(): AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._FunctionDeclarationAnnotationsConst(global.context, this.peer))
    }

    set annotations(newAnnotations: AnnotationUsage[]) {
        global.generatedEs2panda._FunctionDeclarationSetAnnotations(global.context, this.peer, passNodeArray(newAnnotations), newAnnotations.length)
    }

    readonly scriptFunction: ScriptFunction
    readonly parameters: readonly AstNode[]
    readonly name?: Identifier
    readonly body?: BlockStatement
    readonly typeParamsDecl?: TSTypeParameterDeclaration
    readonly returnType?: AstNode
    readonly isAnon: boolean
}

export class FunctionExpression extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_EXPRESSION)
        super(peer)
        this.scriptFunction = unpackNonNullableNode(global.generatedEs2panda._FunctionExpressionFunction(global.context, this.peer))
    }

    static create(
        expression: ScriptFunction,
    ): FunctionExpression {
        return new FunctionExpression(
            global.generatedEs2panda._CreateFunctionExpression(
                global.context,
                passNode(expression)
            )
        )
    }

    readonly scriptFunction: ScriptFunction
}

export class ETSParameterExpression extends Expression {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_ETS_PARAMETER_EXPRESSION)
        super(peer)
        this.identifier = unpackNonNullableNode(global.generatedEs2panda._ETSParameterExpressionIdent(global.context, this.peer))
    }

    static create(
        identifier: Identifier,
        initializer: AstNode | undefined
    ): ETSParameterExpression {
        if (initializer !== undefined) {
            return new ETSParameterExpression(
                global.generatedEs2panda._CreateETSParameterExpression1(
                    global.context,
                    passNode(identifier),
                    passNode(initializer),
                )
            )
        }
        return new ETSParameterExpression(
            global.generatedEs2panda._CreateETSParameterExpression(
                global.context,
                passNode(identifier),
                false
            )
        )
    }

    get annotations(): AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ETSParameterExpressionAnnotations(
            global.context,
            this.peer
        ))
    }

    set annotations(newAnnotations: AnnotationUsage[]) {
        global.generatedEs2panda._ETSParameterExpressionSetAnnotations(
            global.context,
            this.peer,
            passNodeArray(newAnnotations),
            newAnnotations.length
        );
    }

    get type(): AstNode | undefined {
        return unpackNode(global.generatedEs2panda._ETSParameterExpressionTypeAnnotation(global.context, this.peer))
    }

    set type(t: AstNode | undefined) {
        if (t === undefined)
            return
        global.generatedEs2panda._ETSParameterExpressionSetTypeAnnotation(global.context, this.peer, t.peer)
    }

    get optional(): Boolean {
        return global.generatedEs2panda._ETSParameterExpressionIsOptionalConst(global.context, this.peer)
    }

    identifier: Identifier
}

export class IfStatement extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_IF_STATEMENT)
        super(peer)
        this.test = unpackNonNullableNode(global.generatedEs2panda._IfStatementTest(global.context, this.peer))
        this.consequent = unpackNonNullableNode(global.generatedEs2panda._IfStatementConsequent(global.context, this.peer))
        this.alternate = unpackNode(global.generatedEs2panda._IfStatementAlternate(global.context, this.peer))
    }

    static create(
        test: AstNode,
        consequent: AstNode,
        alternate?: AstNode
    ): IfStatement {
        return new IfStatement(
            global.generatedEs2panda._CreateIfStatement(
                global.context,
                passNode(test),
                passNode(consequent),
                passNode(alternate)
            )
        )
    }

    test: AstNode
    consequent: AstNode
    alternate: AstNode | undefined
}

export class StructDeclaration extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_STRUCT_DECLARATION)
        super(peer)
        // TODO: is struct definition the same as struct definition?
        this.definition = unpackNonNullableNode(global.generatedEs2panda._ClassDeclarationDefinition(global.context, this.peer))
    }

    static create(
        definition: ClassDefinition,
    ): StructDeclaration {
        return new StructDeclaration(
            global.generatedEs2panda._CreateETSStructDeclaration(
                global.context,
                passNode(definition)
            )
        )
    }

    readonly definition: ClassDefinition
}

export class MethodDefinition extends AstNode {
    constructor(peer: KPtr, key?: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_METHOD_DEFINITION)
        super(peer)
        this.kind = global.generatedEs2panda._MethodDefinitionKindConst(global.context, this.peer);
        this.scriptFunction = unpackNonNullableNode(global.generatedEs2panda._MethodDefinitionFunction(global.context, this.peer))
        assertValidPeer(this.scriptFunction.peer, Es2pandaAstNodeType.AST_NODE_TYPE_SCRIPT_FUNCTION);

        // Somehow the scriptFunction cannot attach method's key to its ident after checker
        if (key) {
            assertValidPeer(key, Es2pandaAstNodeType.AST_NODE_TYPE_IDENTIFIER);
            const _name = unpackNonNullableNode(key);
            this.scriptFunction = this.scriptFunction.setIdent(_name as Identifier);
        }

        this.name = unpackNonNullableNode(global.generatedEs2panda._ScriptFunctionId(global.context, this.scriptFunction.peer))
        this.kind = global.generatedEs2panda._MethodDefinitionKindConst(global.context, this.peer)
    }

    static create(
        kind: Es2pandaMethodDefinitionKind,
        key: AstNode,
        value: AstNode,
        modifiers: KInt,
        isComputed: boolean
    ): MethodDefinition {
        return new MethodDefinition(
            global.generatedEs2panda._CreateMethodDefinition(
                global.context,
                kind,
                passNode(key),
                passNode(value),
                modifiers,
                isComputed
            ),
            key.peer
        )
    }

    // TODO: does not work
    isConstructor(): boolean {
        return global.generatedEs2panda._MethodDefinitionIsConstructorConst(global.context, this.peer);
    }

    readonly kind: Es2pandaMethodDefinitionKind;
    readonly scriptFunction: ScriptFunction
    readonly name: Identifier
}

export class VariableDeclaration extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATION)
        super(peer)
        this.declarationKind = global.generatedEs2panda._VariableDeclarationKindConst(global.context, this.peer)
        this.declarators = unpackNodeArray(global.generatedEs2panda._VariableDeclarationDeclaratorsConst(global.context, this.peer))
    }

    static create(
        modifiers: KInt,
        kind: Es2pandaVariableDeclarationKind,
        declarators: readonly VariableDeclarator[]
    ): VariableDeclaration {
        const peer = global.generatedEs2panda._CreateVariableDeclaration(
            global.context,
            kind,
            passNodeArray(declarators),
            declarators.length
        )
        global.generatedEs2panda._AstNodeClearModifier(global.context, peer, allFlags)
        global.generatedEs2panda._AstNodeAddModifier(global.context, peer, modifiers)
        return new VariableDeclaration(peer)
    }

    readonly declarationKind: Es2pandaVariableDeclarationKind
    readonly declarators: readonly VariableDeclarator[]
}

export class VariableDeclarator extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATOR)
        super(peer)
        this.name = unpackNonNullableNode(global.generatedEs2panda._VariableDeclaratorId(global.context, this.peer))
    }

    static create(
        flag: Es2pandaVariableDeclaratorFlag,
        name: Identifier,
        initializer: AstNode | undefined
    ): VariableDeclarator {
        const peer = global.generatedEs2panda._CreateVariableDeclarator(
            global.context,
            flag,
            passNode(name)
        )
        if (initializer !== undefined) {
            global.generatedEs2panda._VariableDeclaratorSetInit(global.context, peer, initializer.peer)
        }
        return new VariableDeclarator(peer)
    }

    get initializer(): AstNode | undefined {
        return unpackNode(global.generatedEs2panda._VariableDeclaratorInit(global.context, this.peer))
    }

    readonly name: Identifier
}

export class ETSUndefinedType extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_ETS_UNDEFINED_TYPE)
        super(peer)
    }
}

export class SuperExpression extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_SUPER_EXPRESSION)
        super(peer)
        this.id = unpackNode(global.generatedEs2panda._TSInterfaceDeclarationId(global.context, this.peer));
    }

    static create(
    ): SuperExpression {
        return new SuperExpression(
            global.generatedEs2panda._CreateSuperExpression(
                global.context,
            )
        )
    }

    readonly id?: Identifier;
}

export class ImportSource extends ArktsObject {
    constructor(peer: KPtr) {
        super(peer)
    }

    static create(
        source: StringLiteral,
        hasDecl: boolean,
    ): ImportSource {
        return new ImportSource(
            global.generatedEs2panda._CreateImportSource(
                global.context,
                source.peer,
                StringLiteral.create1StringLiteral(
                    path.resolve(source.str).toString()
                ).peer,
                hasDecl
            )
        )
    }
}

export class EtsImportDeclaration extends AstNode {
    constructor(peer: KPtr) {
        assertValidPeer(peer, Es2pandaAstNodeType.AST_NODE_TYPE_ETS_IMPORT_DECLARATION)
        super(peer)
        this.importSource = unpackNonNullableNode(global.generatedEs2panda._ETSImportDeclarationSourceConst(global.context, this.peer))
        this.importSpecifiers = unpackNodeArray(global.generatedEs2panda._ImportDeclarationSpecifiersConst(global.context, this.peer))
        this.resolvedSource = unpackNonNullableNode(global.generatedEs2panda._ETSImportDeclarationResolvedSource(global.context, this.peer))
        this.importKind = global.generatedEs2panda._ImportDeclarationIsTypeKindConst(global.context, this.peer)
        this.hasDecl = global.generatedEs2panda._ETSImportDeclarationHasDeclConst(global.context, this.peer)
    }

    static create(
        source: StringLiteral,
        specifiers: readonly ImportSpecifier[],
        importKind: Es2pandaImportKinds,
        hasDecl: boolean,
    ): EtsImportDeclaration {
        return new EtsImportDeclaration(
            global.generatedEs2panda._CreateETSImportDeclaration(
                global.context,
                ImportSource.create(
                    source,
                    hasDecl,
                ).peer,
                passNodeArray(specifiers),
                specifiers.length,
                +importKind
            )
        )
    }

    readonly importSource: StringLiteral
    readonly resolvedSource: StringLiteral
    readonly importSpecifiers: readonly ImportSpecifier[]
    readonly importKind: Es2pandaImportKinds
    readonly hasDecl: boolean
}

const pairs: [Es2pandaAstNodeType, { new(peer: KNativePointer): AstNode }][] = [
    [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_MODULE, EtsScript],
    [Es2pandaAstNodeType.AST_NODE_TYPE_IDENTIFIER, Identifier],
    [Es2pandaAstNodeType.AST_NODE_TYPE_NUMBER_LITERAL, NumberLiteral],
    [Es2pandaAstNodeType.AST_NODE_TYPE_EXPRESSION_STATEMENT, ExpressionStatement],
    [Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_DECLARATION, FunctionDeclaration],
    [Es2pandaAstNodeType.AST_NODE_TYPE_SCRIPT_FUNCTION, ScriptFunction],
    [Es2pandaAstNodeType.AST_NODE_TYPE_BLOCK_STATEMENT, BlockStatement],
    [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_PARAMETER_EXPRESSION, ETSParameterExpression],
    [Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_PARAMETER_DECLARATION, TSTypeParameterDeclaration],
    [Es2pandaAstNodeType.AST_NODE_TYPE_CALL_EXPRESSION, CallExpression],
    [Es2pandaAstNodeType.AST_NODE_TYPE_MEMBER_EXPRESSION, MemberExpression],
    [Es2pandaAstNodeType.AST_NODE_TYPE_IF_STATEMENT, IfStatement],
    [Es2pandaAstNodeType.AST_NODE_TYPE_ARROW_FUNCTION_EXPRESSION, ArrowFunctionExpression],
    [Es2pandaAstNodeType.AST_NODE_TYPE_STRUCT_DECLARATION, StructDeclaration],
    [Es2pandaAstNodeType.AST_NODE_TYPE_METHOD_DEFINITION, MethodDefinition],
    [Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATION, VariableDeclaration],
    [Es2pandaAstNodeType.AST_NODE_TYPE_VARIABLE_DECLARATOR, VariableDeclarator],
    [Es2pandaAstNodeType.AST_NODE_TYPE_FUNCTION_EXPRESSION, FunctionExpression],
    [Es2pandaAstNodeType.AST_NODE_TYPE_ETS_IMPORT_DECLARATION, EtsImportDeclaration],
]
pairs.forEach(([nodeType, astNode]) =>
    nodeByType.set(nodeType, astNode)
)