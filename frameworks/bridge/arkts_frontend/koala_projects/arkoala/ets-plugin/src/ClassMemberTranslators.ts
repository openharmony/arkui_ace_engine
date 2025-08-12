/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import * as ts from '@koalaui/ets-tsc'
import {
    createObservableProxy,
    createStateOf,
    getPropertyType,
    PropertyTranslatorContext,
} from './PropertyTranslators'
import {
    backingField,
    createBlock,
    createValueAccessor,
    dropDecorators,
    idTextOrError,
} from './utils'
import {
    assignment,
    hasDecorator,
    id,
    isStatic,
    makePrivate,
    parameter,
} from './ApiUtils'

const ObservedDecorator = "Observed"
const TrackDecorator = "Track"

export function translateClass(node: ts.ClassDeclaration, context: PropertyTranslatorContext): ts.ClassDeclaration {
    const hasObservedDecorator = hasDecorator(node, ObservedDecorator)
    const hasTrackProperties = node.members.some(isTrackPropertyToTranslate)
    if (!hasObservedDecorator && !hasTrackProperties) return node // nothing to rewrite
    const modifiers = dropDecorators(node.modifiers, ObservedDecorator)
    // convert needed properties to private states with getter and setter
    const canTranslate = hasObservedDecorator && !hasTrackProperties
        ? isPropertyToTranslate
        : isTrackPropertyToTranslate
    let members = node.members.flatMap(it => canTranslate(it)
        ? translateClassProperty(it, context)
        : it
    )
    return ts.factory.updateClassDeclaration(node, modifiers, node.name, node.typeParameters, node.heritageClauses, members)
}

function isPropertyToTranslate(element: ts.ClassElement): element is ts.PropertyDeclaration {
    return ts.isPropertyDeclaration(element) && !isStatic(element)
}

function isTrackPropertyToTranslate(element: ts.ClassElement): element is ts.PropertyDeclaration {
    return isPropertyToTranslate(element) && hasDecorator(element, TrackDecorator)
}

function translateClassProperty(property: ts.PropertyDeclaration, context: PropertyTranslatorContext): ts.ClassElement[] {
    const propertyType = getPropertyType(property, context)
    const propertyName = idTextOrError(property.name)
    const backingStateName = backingField(propertyName)
    const modifiers = dropDecorators(property.modifiers, TrackDecorator)

    let safe = false
    let initializer = property.initializer
    if (initializer) {
        initializer = createStateOf(context.importer, propertyType, initializer)
        safe = true
    }
    let className: string | undefined = undefined
    if (property.parent.name && modifiers?.some(it => it.kind === ts.SyntaxKind.StaticKeyword)) {
        className = ts.idText(property.parent.name)
    }
    return [
        // create backing field
        ts.factory.updatePropertyDeclaration(
            property,
            makePrivate(modifiers),
            backingStateName,
            safe ? undefined : ts.factory.createToken(ts.SyntaxKind.QuestionToken),
            ts.factory.createTypeReferenceNode(
                context.importer.withRuntimeImport("MutableState"),
                [propertyType]
            ),
            initializer
        ),
        // create corresponding getter
        ts.factory.createGetAccessorDeclaration(
            modifiers,
            propertyName,
            [],
            propertyType,
            createBlock(
                ts.factory.createReturnStatement(
                    createClassStateValueAccess(backingStateName, className, safe)
                )
            )
        ),
        // create corresponding setter
        ts.factory.createSetAccessorDeclaration(
            modifiers,
            propertyName,
            [parameter("value", propertyType)],
            createBlock(
                safe
                    ? assignment(
                        createClassStateValueAccess(backingStateName, className, true),
                        createObservableProxy(context.importer, undefined, id("value")))
                    : ts.factory.createIfStatement(
                        createClassStateAccess(backingStateName, className),
                        assignment(
                            createClassStateValueAccess(backingStateName, className, false),
                            createObservableProxy(context.importer, undefined, id("value"))),
                        assignment(
                            createClassStateAccess(backingStateName, className),
                            createStateOf(context.importer, propertyType, id("value")))
                    )
            )
        )
    ]
}

function createClassStateAccess(memberName: string, className?: string): ts.Expression {
    return ts.factory.createPropertyAccessExpression(className ? id(className) : ts.factory.createThis(), memberName)
}

function createClassStateValueAccess(memberName: string, className: string | undefined, safe: boolean): ts.Expression {
    const access = createClassStateAccess(memberName, className)
    return createValueAccessor(safe ? access : ts.factory.createNonNullExpression(access))
}
