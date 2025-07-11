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
import * as fs from "fs"

export class PropertyDescriptor {
    constructor(public name: string, public decorators: string[]) {}
}

export class StructDescriptor {
    constructor(public name: string, public properties: PropertyDescriptor[]) {}
    static fromJSON(parsed: any): StructDescriptor[] {
        return parsed.structs.map((struct: any) => new StructDescriptor(struct.name,
            struct.properties.map((property: any) =>
                new PropertyDescriptor(property.name, property.decorators)
            )
        ))
    }

    decoratorsFor(name: string): string[] | undefined {
        return this.properties.find(it => it.name == name)?.decorators
    }
}

export class StructTable {
    structByName = new Map<string, StructDescriptor>()

    findStruct(name: arkts.Identifier): StructDescriptor | undefined {
        return this.structByName.get(name.name)
    }
    addStruct(declaration: arkts.ETSStructDeclaration) {
        this.addDescriptor(this.toDescriptor(declaration))
    }
    addDescriptor(descriptor: StructDescriptor) {
        this.structByName.set(descriptor.name, descriptor)
    }
    addDescriptors(descriptors: StructDescriptor[]) {
        descriptors.forEach(it => this.addDescriptor(it))
    }

    toDescriptor(declaration: arkts.ETSStructDeclaration): StructDescriptor {
        return new StructDescriptor(
            declaration.definition?.ident?.name!,
            declaration.definition!.body
                .filter(arkts.isClassProperty)
                .map((classProperty: arkts.ClassProperty) =>
                    new PropertyDescriptor((classProperty.key as arkts.Identifier).name!,
                            this.extractDecorators(classProperty))
                )
            )
    }
    extractDecorators(property: arkts.ClassProperty): string[] {
        let decorators = property.decorators
            .filter(it => arkts.isIdentifier(it.expr))
            .map(it => (it.expr as arkts.Identifier).name!)
        let annotations = property.annotations
            .filter(it => arkts.isIdentifier(it.expr))
            .map(it => (it.expr as arkts.Identifier).name!)
        return decorators.concat(annotations)
    }
}

export class StructRecorder extends arkts.AbstractVisitor {
    constructor(private table: StructTable) {
        super()
        const database = "./structs.json"
        if (fs.existsSync(database)) {
            try {
                table.addDescriptors(StructDescriptor.fromJSON(JSON.parse(fs.readFileSync(database, "utf-8"))))
            } catch (e: any) {
                console.log(e.stack)
            }
        }
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isETSStructDeclaration(node)) {
            this.table.addStruct(node)
        }
        this.visitEachChild(node)
        return node
    }
}
