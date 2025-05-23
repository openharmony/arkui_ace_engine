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

import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { Identifier } from "./Identifier"
import { Statement } from "./Statement"
export class ExportSpecifier extends Statement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 29)
        super(pointer)
    }
    static createExportSpecifier(local?: Identifier, exported?: Identifier): ExportSpecifier {
        return new ExportSpecifier(global.generatedEs2panda._CreateExportSpecifier(global.context, passNode(local), passNode(exported)))
    }
    static updateExportSpecifier(original?: ExportSpecifier, local?: Identifier, exported?: Identifier): ExportSpecifier {
        return new ExportSpecifier(global.generatedEs2panda._UpdateExportSpecifier(global.context, passNode(original), passNode(local), passNode(exported)))
    }
    get local(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ExportSpecifierLocalConst(global.context, this.peer))
    }
    get exported(): Identifier | undefined {
        return unpackNode(global.generatedEs2panda._ExportSpecifierExportedConst(global.context, this.peer))
    }
    /** @deprecated */
    setDefault(): this {
        global.generatedEs2panda._ExportSpecifierSetDefault(global.context, this.peer)
        return this
    }
    get isDefault(): boolean {
        return global.generatedEs2panda._ExportSpecifierIsDefaultConst(global.context, this.peer)
    }
    /** @deprecated */
    setConstantExpression(constantExpression?: Expression): this {
        global.generatedEs2panda._ExportSpecifierSetConstantExpression(global.context, this.peer, passNode(constantExpression))
        return this
    }
    get constantExpression(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._ExportSpecifierGetConstantExpressionConst(global.context, this.peer))
    }
}
export function isExportSpecifier(node: object | undefined): node is ExportSpecifier {
    return node instanceof ExportSpecifier
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_EXPORT_SPECIFIER)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_EXPORT_SPECIFIER, (peer: KNativePointer) => new ExportSpecifier(peer))
}