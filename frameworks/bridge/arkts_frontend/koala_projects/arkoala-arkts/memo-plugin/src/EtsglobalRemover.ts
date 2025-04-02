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
import { AbstractVisitor } from "./AbstractVisitor"

export interface TransformerOptions {
    trace?: boolean,
}

const ETSGLOBAL = "ETSGLOBAL"

export class EtsglobalRemover extends AbstractVisitor {
    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isEtsScript(node)) {
            const idETSGLOBAL = node.statements.findIndex((it) => {
                return arkts.isClassDeclaration(it) && it.definition?.ident?.name == ETSGLOBAL
            })
            const keep = node.statements.filter((it, index) => {
                return !arkts.isClassDeclaration(it) || it.definition?.ident?.name != ETSGLOBAL || index == idETSGLOBAL
            })
            return arkts.factory.updateEtsScript(
                node,
                keep
            )
        }
        return node
    }
}
