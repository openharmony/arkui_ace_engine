/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import * as arkts from "@koalaui/libarkts"
import {
    BuilderLambdaNames,
    CustomComponentNames,
    InternalAnnotations
} from "./utils";
import { annotation } from "./common/arkts-utils";

export class factory {
    /**
     * create `instance: <typeName>` as identifier
     */
    static createInstanceIdentifier(typeName: string): arkts.Identifier {
        return arkts.factory.createIdentifier(
            BuilderLambdaNames.STYLE_ARROW_PARAM_NAME,
            factory.createTypeReferenceFromString(typeName)
        )
    }

    /**
     * create `instance: <typeName>` as parameter
     */
    static createInstanceParameter(typeName: string): arkts.ETSParameterExpression {
        return arkts.factory.createETSParameterExpression(
            factory.createInstanceIdentifier(typeName),
            false
        )
    }

    /**
     * create `(instance: <typeName>) => void`
     */
    static createStyleLambdaFunctionType(typeName: string): arkts.ETSFunctionType {
        return arkts.factory.createETSFunctionType(
            undefined,
            [
                factory.createInstanceParameter(typeName)
            ],
            arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
            false,
            arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW
        );
    }

    /**
     * create `style: ((instance: <typeName>) => void) | undefined` as identifier
     */
    static createStyleIdentifier(typeName: string): arkts.Identifier {
        return arkts.factory.createIdentifier(
            BuilderLambdaNames.STYLE_PARAM_NAME,
            arkts.factory.createETSUnionType([
                factory.createStyleLambdaFunctionType(typeName),
                arkts.factory.createETSUndefinedType()
            ])
        )
    }

    /**
     * create `@memo() style: ((instance: <typeName>) => void) | undefined` as parameter
     */
    static createStyleParameter(typeName: string): arkts.ETSParameterExpression {
        const styleParam: arkts.Identifier = factory.createStyleIdentifier(typeName);
        const param = arkts.factory.createETSParameterExpression(styleParam, false);
        param.setAnnotations([annotation(InternalAnnotations.MEMO)]);
        return param;
    }

    /**
     * create `initializers: <optionsName> | undefined` as identifier
     */
    static createInitializerOptionsIdentifier(optionsName: string): arkts.Identifier {
        return arkts.factory.createIdentifier(
            CustomComponentNames.COMPONENT_INITIALIZERS_NAME,
            arkts.factory.createETSUnionType([
                factory.createTypeReferenceFromString(optionsName),
                arkts.factory.createETSUndefinedType()
            ])
        )
    }

    /**
     * create `initializers: <optionsName> | undefined` as parameter
     */
    static createInitializersOptionsParameter(optionsName: string): arkts.ETSParameterExpression {
        return arkts.factory.createETSParameterExpression(
            factory.createInitializerOptionsIdentifier(
                optionsName
            ),
            false
        )
    }

    /**
     * create `content: (() => void) | undefined` as identifier
     */
    static createContentIdentifier(): arkts.Identifier {
        return arkts.factory.createIdentifier(
            BuilderLambdaNames.CONTENT_PARAM_NAME,
            arkts.factory.createETSUnionType([
                factory.createLambdaFunctionType(),
                arkts.factory.createETSUndefinedType()
            ])
        );
    }

    /**
     * create `@memo() content: (() => void) | undefined` as parameter
     */
    static createContentParameter(): arkts.ETSParameterExpression {
        const contentParam: arkts.Identifier = factory.createContentIdentifier();
        const param = arkts.factory.createETSParameterExpression(contentParam, false);
        param.setAnnotations([annotation(InternalAnnotations.MEMO)]);
        return param;
    }

    /**
     * create type from string
     */
    static createTypeReferenceFromString(name: string): arkts.TypeNode {
        return arkts.factory.createETSTypeReference(
            arkts.factory.createETSTypeReferencePart(
                arkts.factory.createIdentifier(name, undefined), undefined, undefined
            )
        );
    }

    /**
     * create `(<params>) => <returnType>`. If returnType is not given, then using `void`.
     */
    static createLambdaFunctionType(
        params?: arkts.Expression[],
        returnType?: arkts.TypeNode | undefined
    ): arkts.ETSFunctionType {
        return arkts.factory.createETSFunctionType(
            undefined,
            params ?? [],
            returnType
                ?? arkts.factory.createETSPrimitiveType(arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_VOID),
            false,
            arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_ARROW
        )
    }
}
