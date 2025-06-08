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

import {
    createGetter,
    createSetter,
} from "./utils";
import { PropertyTranslator } from "./base";
import {
    GetterSetter,
    InitializerConstructor
} from "./types";
import {
    backingField,
    expectName
} from "../common/arkts-utils";

export class regularPropertyTranslator extends PropertyTranslator implements InitializerConstructor, GetterSetter {
    translateMember(): arkts.AstNode[] {
        const originalName: string = expectName(this.property.key);
        const newName: string = backingField(originalName);
        this.cacheTranslatedInitializer(newName, originalName); // TODO: need to release cache after some point...
        return this.translateWithoutInitializer(newName, originalName);
    }

    cacheTranslatedInitializer(newName: string, originalName: string): void {}

    translateWithoutInitializer(newName: string, originalName: string): arkts.AstNode[] {
        return [this.property];
    }

    translateGetter(
        originalName: string,
        typeAnnotation: arkts.TypeNode | undefined,
        returnValue: arkts.Expression
    ): arkts.MethodDefinition {
        return createGetter(originalName, typeAnnotation, returnValue);
    }

    translateSetter(
        originalName: string,
        typeAnnotation: arkts.TypeNode | undefined,
        left: arkts.MemberExpression
    ): arkts.MethodDefinition {
        const right: arkts.Identifier = arkts.factory.createIdentifier('value', undefined)
        return createSetter(originalName, typeAnnotation, left, right);
    }

    generateInitializeStruct(
        newName: string,
        originalName: string
    ): arkts.AstNode {
        return arkts.factory.createAssignmentExpression(
            arkts.factory.createMemberExpression(
                arkts.factory.createIdentifier('this', undefined),
                arkts.factory.createIdentifier(originalName, undefined),
                arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                false,
                false
            ),
            this.property.value ?? arkts.factory.createIdentifier('undefined', undefined),
            arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_SUBSTITUTION
        );
    }
}