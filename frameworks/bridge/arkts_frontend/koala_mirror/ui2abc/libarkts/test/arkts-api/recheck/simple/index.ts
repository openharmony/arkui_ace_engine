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
 
import * as arkts from "../../../../src/arkts-api"

export function updateTopLevelClass(
    module: arkts.ETSModule,
    update: (node: arkts.ClassDefinition) => arkts.ClassDefinition
) {
    return arkts.factory.updateETSModule(
        module,
        [
            ...module.statements.map((node) => {
                if (!arkts.isClassDeclaration(node)) {
                    return node
                }
                if (!arkts.isClassDefinition(node.definition)) {
                    return node
                }
                if (node.definition.ident?.name == "C") {
                    return arkts.factory.updateClassDeclaration(
                        node,
                        update(node.definition)
                    )
                }
                return node
            })
        ],
        module.ident,
        module.getNamespaceFlag(),
        module.program,
    )
}
