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
import { TSTypeParameterInstantiation } from "./TSTypeParameterInstantiation"
import { TypeNode } from "./TypeNode"
export class TSImportType extends TypeNode {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 112)
        super(pointer)
    }
    static createTSImportType(param: Expression | undefined, typeParams: TSTypeParameterInstantiation | undefined, qualifier: Expression | undefined, isTypeof: boolean): TSImportType {
        return new TSImportType(global.generatedEs2panda._CreateTSImportType(global.context, passNode(param), passNode(typeParams), passNode(qualifier), isTypeof))
    }
    static updateTSImportType(original: TSImportType | undefined, param: Expression | undefined, typeParams: TSTypeParameterInstantiation | undefined, qualifier: Expression | undefined, isTypeof: boolean): TSImportType {
        return new TSImportType(global.generatedEs2panda._UpdateTSImportType(global.context, passNode(original), passNode(param), passNode(typeParams), passNode(qualifier), isTypeof))
    }
    get param(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSImportTypeParamConst(global.context, this.peer))
    }
    get typeParams(): TSTypeParameterInstantiation | undefined {
        return unpackNode(global.generatedEs2panda._TSImportTypeTypeParamsConst(global.context, this.peer))
    }
    get qualifier(): Expression | undefined {
        return unpackNode(global.generatedEs2panda._TSImportTypeQualifierConst(global.context, this.peer))
    }
    get isTypeof(): boolean {
        return global.generatedEs2panda._TSImportTypeIsTypeofConst(global.context, this.peer)
    }
}
export function isTSImportType(node: object | undefined): node is TSImportType {
    return node instanceof TSImportType
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_TS_IMPORT_TYPE)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_TS_IMPORT_TYPE, (peer: KNativePointer) => new TSImportType(peer))
}