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

import * as arkts from "@koalaui/libarkts"

export function annotation(name: string): arkts.AnnotationUsage {
    const ident: arkts.Identifier = arkts.factory.createIdentifier(name, undefined).setAnnotationUsage()
    const annotation: arkts.AnnotationUsage = arkts.factory.createAnnotationUsage(ident, [])

    annotation.modifierFlags = arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_ANNOTATION_USAGE
    ident.parent = annotation

    return annotation
}

export function isAnnotation(node: arkts.AnnotationUsage, annoName: string) {
    return node.expr !== undefined && arkts.isIdentifier(node.expr) && node.expr.name === annoName;
}

export function removeAnnotationByName(
    annotations: readonly arkts.AnnotationUsage[],
    annoName: string
): arkts.AnnotationUsage[] {
    return annotations.filter((it) => !isAnnotation(it, annoName));
}

export function expectName(node: arkts.AstNode | undefined): string {
    if (!node) {
        throw new Error("Expected an identifier, got empty node");
    }
    if (!arkts.isIdentifier(node)) {
        throw new Error("Expected an identifier, got: " + arkts.nodeType(node).toString());
    }
    return node.name;
}

export function mangle(value: string): string {
    return `__${value}`;
}

export function backingField(originalName: string): string {
    return mangle(`backing_${originalName}`);
}

export function filterDefined<T>(value: (T | undefined)[]): T[] {
    return value.filter((it: T | undefined): it is T => it != undefined);
}

export function collect<T>(...value: (ReadonlyArray<T> | T | undefined)[]): T[] {
    const empty: (T | undefined)[] = []
    return filterDefined(empty.concat(...value))
}

export function matchPrefix(prefixCollection: string[], name: string): boolean {
    for (const prefix of prefixCollection) {
        if (name.startsWith(prefix)) {
            return true;
        }
    }
    return false;
}

export function classMethods(clazz: arkts.ClassDeclaration, predicate?: (method: arkts.MethodDefinition) => boolean): arkts.MethodDefinition[] {
    const body = clazz.definition?.body ?? []
    const methods = body.filter(arkts.isMethodDefinition)
    return predicate ? methods.filter(predicate) : methods
}
