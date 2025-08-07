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
import { ClassElement } from "./ClassElement"
import { Es2pandaAstNodeType } from "./../Es2pandaEnums"
import { Es2pandaModifierFlags } from "./../Es2pandaEnums"
import { Expression } from "./Expression"
import { TypeNode } from "./TypeNode"
export class ClassProperty extends ClassElement {
    constructor(pointer: KNativePointer) {
        assertValidPeer(pointer, 17)
        super(pointer)
    }
    static createClassProperty(key: Expression | undefined, value: Expression | undefined, typeAnnotation: TypeNode | undefined, modifiers: Es2pandaModifierFlags, isComputed: boolean): ClassProperty {
        return new ClassProperty(global.generatedEs2panda._CreateClassProperty(global.context, passNode(key), passNode(value), passNode(typeAnnotation), modifiers, isComputed))
    }
    static updateClassProperty(original: ClassProperty | undefined, key: Expression | undefined, value: Expression | undefined, typeAnnotation: TypeNode | undefined, modifiers: Es2pandaModifierFlags, isComputed: boolean): ClassProperty {
        return new ClassProperty(global.generatedEs2panda._UpdateClassProperty(global.context, passNode(original), passNode(key), passNode(value), passNode(typeAnnotation), modifiers, isComputed))
    }
    get isDefaultAccessModifier(): boolean {
        return global.generatedEs2panda._ClassPropertyIsDefaultAccessModifierConst(global.context, this.peer)
    }
    /** @deprecated */
    setDefaultAccessModifier(isDefault: boolean): this {
        global.generatedEs2panda._ClassPropertySetDefaultAccessModifier(global.context, this.peer, isDefault)
        return this
    }
    get typeAnnotation(): TypeNode | undefined {
        return unpackNode(global.generatedEs2panda._ClassPropertyTypeAnnotationConst(global.context, this.peer))
    }
    /** @deprecated */
    setTypeAnnotation(typeAnnotation?: TypeNode): this {
        global.generatedEs2panda._ClassPropertySetTypeAnnotation(global.context, this.peer, passNode(typeAnnotation))
        return this
    }
    get needInitInStaticBlock(): boolean {
        return global.generatedEs2panda._ClassPropertyNeedInitInStaticBlockConst(global.context, this.peer)
    }
    /** @deprecated */
    setInitInStaticBlock(needInitInStaticBlock: boolean): this {
        global.generatedEs2panda._ClassPropertySetInitInStaticBlock(global.context, this.peer, needInitInStaticBlock)
        return this
    }
    get annotations(): readonly AnnotationUsage[] {
        return unpackNodeArray(global.generatedEs2panda._ClassPropertyAnnotations(global.context, this.peer))
    }
    /** @deprecated */
    setAnnotations(annotations: readonly AnnotationUsage[]): this {
        global.generatedEs2panda._ClassPropertySetAnnotations(global.context, this.peer, passNodeArray(annotations), annotations.length)
        return this
    }
}
export function isClassProperty(node: object | undefined): node is ClassProperty {
    return node instanceof ClassProperty
}
if (!nodeByType.has(Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_PROPERTY)) {
    nodeByType.set(Es2pandaAstNodeType.AST_NODE_TYPE_CLASS_PROPERTY, (peer: KNativePointer) => new ClassProperty(peer))
}