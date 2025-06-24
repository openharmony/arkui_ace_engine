    /*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import * as arkts from "@koalaui/libarkts"
import { DecoratorNames, hasDecorator, hasBuilderDecorator } from "./property-translators/utils"
import { annotation } from "./common/arkts-utils"
import { CustomComponentNames, InternalAnnotations } from "./utils"

export class AnnotationsTransformer extends arkts.AbstractVisitor {

    constructor(options?: arkts.VisitorOptions) {
        super(options)
        this.program = arkts.global.compilerContext.program
    }


    inStruct = false

    visitor(beforeVisit: arkts.AstNode): arkts.AstNode {
        if (arkts.isClassDefinition(beforeVisit) && hasDecorator(beforeVisit, DecoratorNames.COMPONENT)) {
            this.inStruct = true
        }
        // console.log(`builder transform ${node.dumpSrc()} ${arkts.isAnnotationUsage(node)}`)
        const node = this.visitEachChild(beforeVisit)

        if (arkts.isFunctionDeclaration(node) && hasBuilderDecorator(node)) {
            return arkts.factory.updateFunctionDeclaration(node, node.function, [
                annotation(InternalAnnotations.MEMO)], node.isAnonymous)
        }
        if (this.inStruct && arkts.isMethodDefinition(node) && (
            hasBuilderDecorator(node) ||
            node.function?.id?.name == CustomComponentNames.COMPONENT_BUILD_ORI)
        ) {
            node.function!.setAnnotations([annotation(InternalAnnotations.MEMO)])
            return node
        }
        if (this.inStruct && arkts.isClassProperty(node) && hasDecorator(node, DecoratorNames.BUILDER_PARAM)) {
            return node
        }
        if (arkts.isClassDefinition(node) && hasDecorator(node, DecoratorNames.COMPONENT)) {
            this.inStruct = false
            return node
        }
        return node
    }
}
