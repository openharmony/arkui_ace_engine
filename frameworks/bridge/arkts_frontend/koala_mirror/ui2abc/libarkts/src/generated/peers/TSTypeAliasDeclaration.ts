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

import { AnnotatedStatement } from "./AnnotatedStatement"
import { AnnotationUsage } from "./AnnotationUsage"
import { Decorator } from "./Decorator"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Identifier } from "./Identifier"
import { TSTypeParameterDeclaration } from "./TSTypeParameterDeclaration"
import { TypeNode } from "./TypeNode"
export class TSTypeAliasDeclaration extends AnnotatedStatement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 127)
        super(pointer)
    }
    static createTSTypeAliasDeclaration(id?: Identifier, typeParams?: TSTypeParameterDeclaration, typeAnnotation?: TypeNode): TSTypeAliasDeclaration {
        return new TSTypeAliasDeclaration(global.generatedEs2panda._CreateTSTypeAliasDeclaration(global.context, passNode(id), passNode(typeParams), passNode(typeAnnotation)))
    }
    static updateTSTypeAliasDeclaration(original?: TSTypeAliasDeclaration, id?: Identifier, typeParams?: TSTypeParameterDeclaration, typeAnnotation?: TypeNode): TSTypeAliasDeclaration {
        return new TSTypeAliasDeclaration(global.generatedEs2panda._UpdateTSTypeAliasDeclaration(global.context, passNode(original), passNode(id), passNode(typeParams), passNode(typeAnnotation)))
    }
    static update1TSTypeAliasDeclaration(original?: TSTypeAliasDeclaration, id?: Identifier): TSTypeAliasDeclaration {
        return new TSTypeAliasDeclaration(global.generatedEs2panda._UpdateTSTypeAliasDeclaration1(global.context, passNode(original), passNode(id)))
    }
    get id(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeAliasDeclarationId(global.context, this.peer))
    }
    get typeParams(): TSTypeParameterDeclaration | undefined {
        return unpackNode(global.generatedEs2panda._TSTypeAliasDeclarationTypeParamsConst(global.context, this.peer))
    }
    get decorators(): readonly Decorator[] {
        return unpackNodeArray(global.generatedEs2panda._TSTypeAliasDeclarationDecoratorsConst(global.context, this.peer))
    }
    /** @deprecated */
    setTypeParameters(typeParams?: TSTypeParameterDeclaration): this {
        global.generatedEs2panda._TSTypeAliasDeclarationSetTypeParameters(global.context, this.peer, passNode(typeParams))
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._TSTypeAliasDeclarationAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._TSTypeAliasDeclarationSetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
    get typeAnnotation(): TypeNode {
        return unpackNonNullableNode(global.generatedEs2panda._TSTypeAliasDeclarationTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTsTypeAnnotation(typeAnnotation?: TypeNode): this {
        global.generatedEs2panda._TSTypeAliasDeclarationSetTsTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
}
export function isTSTypeAliasDeclaration(node: object | undefined): node is TSTypeAliasDeclaration {
    return node instanceof TSTypeAliasDeclaration
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_ALIAS_DECLARATION)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_TYPE_ALIAS_DECLARATION, (peer: KNativePointer) => new TSTypeAliasDeclaration(peer))
}