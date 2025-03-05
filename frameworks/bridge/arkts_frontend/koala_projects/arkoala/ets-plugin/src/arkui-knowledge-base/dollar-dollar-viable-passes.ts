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

import * as ts from "@koalaui/ets-tsc"

abstract class PassType {
    protected constructor(
        public parameter: string,
        public type: ts.TypeNode
    ) {}
}

class InitializerObject extends PassType {
    constructor(
        parameter: string,
        type: ts.TypeNode,
        public readonly component: string,
    ) {
        super(parameter, type)
    }
}

class ComponentMethodCall extends PassType {
    constructor(
        parameter: string,
        type: ts.TypeNode,
        public readonly component: string,
        public readonly method: string,
    ) {
        super(parameter, type)
    }
}

class MethodCall extends PassType {
    constructor(
        parameter: string,
        type: ts.TypeNode,
        public readonly method: string,
    ) {
        super(parameter, type)
    }
}

export function isInitializerObject(value: PassType): value is InitializerObject {
    return value instanceof InitializerObject
}

export function isComponentMethodCall(value: PassType): value is ComponentMethodCall {
    return value instanceof ComponentMethodCall
}

export const dollarDollarViablePasses: PassType[] = [
    new ComponentMethodCall(`value`, ts.factory.createKeywordTypeNode(ts.SyntaxKind.BooleanKeyword), `Checkbox`, `select`),
    new ComponentMethodCall(`value`, ts.factory.createKeywordTypeNode(ts.SyntaxKind.BooleanKeyword), `CheckboxGroup`, `selectAll`),
    new InitializerObject(`selected`, ts.factory.createTypeReferenceNode(`Date`), `DatePicker`),
    new InitializerObject(`selected`, ts.factory.createTypeReferenceNode(`Date`), `TimePicker`),
    new InitializerObject(`isOn`, ts.factory.createKeywordTypeNode(ts.SyntaxKind.BooleanKeyword), `Toggle`),
    new ComponentMethodCall(`value`, ts.factory.createKeywordTypeNode(ts.SyntaxKind.BooleanKeyword), `MenuItem`, `selected`),
    new ComponentMethodCall(`value`, ts.factory.createKeywordTypeNode(ts.SyntaxKind.BooleanKeyword), `Select`, `value`),
    new ComponentMethodCall(`value`, ts.factory.createKeywordTypeNode(ts.SyntaxKind.BooleanKeyword), `Select`, `selected`),
    new InitializerObject(`value`, ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword), `Search`),
    // new ComponentMethodCall(`value`, `Panel`, `mode`),
    // new InitializerObject(`value`, `Search`),
    // TODO
]
