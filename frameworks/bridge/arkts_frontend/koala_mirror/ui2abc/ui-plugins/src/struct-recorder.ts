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
import * as path from "path"
import { CustomComponentNames } from "./utils"
import { programGetExternalSources, metaDatabase } from "@koalaui/libarkts"

export class PropertyDescriptor {
    constructor(public name: string, public decorators: string[]) { }
    toJSON(): string {
        return `{"name": "${this.name}", "decorators": [${this.decorators.map(it => `"${it}"`).join(",")}]}`
    }
}

export class StructDescriptor {
    constructor(public name: string, public annotations: string[], public properties: PropertyDescriptor[]) { }
    static fromJSON(parsed: any): StructDescriptor[] {
        return parsed.structs.map((struct: any) => new StructDescriptor(struct.name, struct.annotations,
            struct.properties.map((property: any) =>
                new PropertyDescriptor(property.name, property.decorators)
            )
        ))
    }
    toJSON(): string {
        return `{ "name": "${this.name}", `
            + `"annotations": [${this.annotations.map(it => `"${it}"`).join(",")}], `
            + `"properties": [${this.properties.map(it => it.toJSON()).join(", ")}] }`
    }

    decoratorsFor(name: string): string[] | undefined {
        return this.properties.find(it => it.name == name)?.decorators
    }

    hasDecorator(property: string, decorator: string): boolean {
        return this.decoratorsFor(property)?.includes(decorator) ?? false
    }

    hasAnnotation(annotation: string): boolean {
        return this.annotations?.includes(annotation) ?? false
    }
}
export class StructsResolver {
    private structByFile = new Map<string, StructTable>()

    constructor(private restart: boolean) {
        this.init()
    }

    init() {
        for (let source of programGetExternalSources(arkts.global.compilerContext.program)) {
            const name = source.getName()
            if (name.startsWith("std.")) continue
            if (name.startsWith("escompat")) continue
            if (name.startsWith("@ohos.arkui")) continue
            if (name.startsWith("@koalaui")) continue
            if (name.startsWith("arkui.stateManagement")) continue

            let program = source.programs[0]
            let table = this.getOrCreateTable(program.sourceFilePath, this.restart)
            table.recordStructs(program, this.restart)
            this.addTable(program.sourceFilePath, table)
        }
    }

    addTable(fileName: string, table: StructTable) {
        this.structByFile.set(fileName, table)
    }

    getOrCreateTable(fileName: string, restart: boolean) {
        let result = this.structByFile.get(fileName)
        if (!result) {
            result = new StructTable(fileName, restart)
            this.addTable(fileName, result)
        }
        return result
    }

    findDeclarationFile(declaration: arkts.AstNode): string {
        let current:  arkts.AstNode|undefined  = declaration
        while (current && !arkts.isETSModule(current)) {
            current = current.parent
        }
        if (!current) throw new Error(`Is not part of module`)
        let module = current as arkts.ETSModule
        return module.program!.sourceFilePath
    }

    private declarationToTable(declaration: arkts.AstNode): StructTable {
        const declarationFile = this.findDeclarationFile(declaration)
        if (!declarationFile) throw new Error(`No declaration file`)
        let structs = this.structByFile.get(declarationFile)
        if (!structs) {
            structs = new StructTable(declarationFile, this.restart)
            this.addTable(declarationFile, structs)
        }
        return structs
    }

    findStructByOptions(name: arkts.AstNode|undefined): StructDescriptor | undefined {
        if (!name) return undefined
        const declaration = arkts.getDecl(name)
        if (!declaration || !arkts.isTSInterfaceDeclaration(declaration)) return undefined
        const structName = declaration.id!.name.replace(CustomComponentNames.COMPONENT_INTERFACE_PREFIX, "")
        return this.declarationToTable(declaration).findStruct(structName)
    }

    findStruct(name: arkts.Identifier): StructDescriptor | undefined {
        const declaration = arkts.getDecl(name)
        if (!declaration) return undefined
        return this.declarationToTable(declaration).findStruct(name.name)
    }

    hasDefinition(filename: string): boolean {
        return this.structByFile.has(filename)
    }
}

export class StructTable {
    private structByName = new Map<string, StructDescriptor>()
    constructor(private fileName: string, private restart: boolean) {
        if (this.restart) {
            this.readDB()
        }
    }
    readDB() {
        const db = metaDatabase(this.fileName)
        if (fs.existsSync(db)) {
            try {
                this.addDescriptors(
                    StructDescriptor.fromJSON(
                        JSON.parse(
                            fs.readFileSync(db, "utf-8")
                        )
                    )
                )
            } catch (e: any) {
                console.log(e.stack)
            }
        }
    }
    recordStructs(program: arkts.Program, restart: boolean = false) {
        new StructRecorder(this, restart).visitor(program.ast)
    }
    findStruct(name: string): StructDescriptor|undefined {
        return this.structByName.get(name)
    }
    addStruct(declaration: arkts.ETSStructDeclaration) {
        if (this.structByName.has(declaration.definition?.ident?.name!)) return
        const descriptor = StructTable.toDescriptor(declaration)
        this.addDescriptor(descriptor)
    }
    addDescriptor(descriptor: StructDescriptor) {
        this.structByName.set(descriptor.name, descriptor)
    }
    addDescriptors(descriptors: StructDescriptor[]) {
        descriptors.forEach(it => this.addDescriptor(it))
    }
    static toDescriptor(declaration: arkts.ETSStructDeclaration): StructDescriptor {
        return new StructDescriptor(
            declaration.definition?.ident?.name!,
            StructTable.extractAnnotations(declaration),
            declaration.definition!.body
                .filter(arkts.isClassProperty)
                .map((classProperty: arkts.ClassProperty) =>
                    new PropertyDescriptor((classProperty.key as arkts.Identifier).name!,
                        StructTable.extractDecorators(classProperty))
                )
        )
    }
    static extractDecorators(property: arkts.ClassProperty): string[] {
        let decorators = property.decorators
            .filter(it => arkts.isIdentifier(it.expr))
            .map(it => (it.expr as arkts.Identifier).name!)
        let annotations = property.annotations
            .filter(it => arkts.isIdentifier(it.expr))
            .map(it => (it.expr as arkts.Identifier).name!)
        return decorators.concat(annotations)
    }
    static extractAnnotations(declaration: arkts.ETSStructDeclaration): string[] {
        let annotations = declaration?.definition?.annotations
            .filter(it => arkts.isIdentifier(it.expr))
            .map(it => (it.expr as arkts.Identifier).name!) ?? []
        return annotations
    }
    update() {
        if (!this.restart) return
        if (this.structByName.size == 0) return
        let lines = []
        for (let desc of this.structByName.values()) {
            lines.push(desc.toJSON())
        }
        let result = `{"structs": [ ${lines.join(",")} ]}`
        const filePath = metaDatabase(
            path.resolve(arkts.global.arktsconfig!.outDir, path.relative(arkts.global.arktsconfig!.baseUrl, arkts.global.filePath))
        )
        fs.mkdirSync(path.dirname(filePath), { recursive: true })
        fs.writeFileSync(filePath, result)
    }
}

export class StructRecorder extends arkts.AbstractVisitor {
    constructor(private table: StructTable, private restart: boolean = false) {
        super()
    }

    visitor(node: arkts.AstNode): arkts.AstNode {
        if (arkts.isETSModule(node)) {
            const result = this.visitEachChild(node)
            this.table.update()
            return result
        }
        if (arkts.isETSStructDeclaration(node)) {
            this.table.addStruct(node)
            return node
        }
        // Do not go inside classes, structs cannot be there.
        if (arkts.isClassDeclaration(node)) {
            return node
        }
        if (arkts.isFunctionDeclaration(node)) {
            return node
        }
        if (arkts.isInterfaceDecl(node)) {
            return node
        }
        return this.visitEachChild(node)
    }
}
