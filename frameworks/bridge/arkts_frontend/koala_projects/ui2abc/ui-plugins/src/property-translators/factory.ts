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

import * as arkts from "@koalaui/libarkts";
import { GenSymGenerator } from "../common/gensym-generator";

export class factory {
    /**
     * generate an substitution for optional expression ?., e.g. `{let _tmp = xxx; _tmp == null ? undefined : xxx}`.
     *
     * @param object item before ?..
     * @param key item after ?..
     */
    static createBlockStatementForOptionalExpression(object: arkts.Expression, key: string): arkts.Expression {
        let id = GenSymGenerator.getInstance().id(key);
        const statements: arkts.Statement[] = [
            factory.generateLetVariableDecl(
                arkts.factory.createIdentifier(id, undefined),
                object
            ),
            factory.generateTernaryExpression(id, key)
        ];
        return arkts.factory.createBlockExpression(statements);
    }

    /**
     * generate a variable declaration, e.g. `let <left> = <right>`;
     *
     * @param left left expression.
     * @param right right expression.
     */
    static generateLetVariableDecl(left: arkts.Identifier , right: arkts.Expression): arkts.VariableDeclaration {
        return arkts.factory.createVariableDeclaration(
            arkts.Es2pandaVariableDeclarationKind.VARIABLE_DECLARATION_KIND_LET,
            [
                arkts.factory.createVariableDeclarator(
                    arkts.Es2pandaVariableDeclaratorFlag.VARIABLE_DECLARATOR_FLAG_LET,
                    left,
                    right
                )
            ]
        );
    }

    /**
     * generate a ternary expression, e.g. `<test> ? <consequent> : <alternate>`;
     *
     * @param testLeft the left hand of the test condition.
     * @param key item after ?.
     */
    static generateTernaryExpression(testLeft: string, key: string): arkts.ExpressionStatement {
        const test = arkts.factory.createBinaryExpression(
            arkts.factory.createIdentifier(testLeft, undefined),
            arkts.factory.createNullLiteral(),
            arkts.Es2pandaTokenType.TOKEN_TYPE_PUNCTUATOR_EQUAL
        );
        const consequent: arkts.Expression = arkts.factory.createUndefinedLiteral();
        const alternate: arkts.MemberExpression = arkts.factory.createMemberExpression(
            arkts.factory.createIdentifier(testLeft, undefined),
            arkts.factory.createIdentifier(key, undefined),
            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
            false,
            false
        );
        return arkts.factory.createExpressionStatement(
            arkts.factory.createConditionalExpression(test, consequent, alternate)
        );
    }

    /**
     * generate an substitution for two optional expression ?., e.g. a?.b?.c.
     *
     * @param node entry wrapper class declaration node.
     */
    static createDoubleBlockStatementForOptionalExpression(
        object: arkts.Expression,
        key1: string,
        key2: string
    ): arkts.Expression {
        let id = GenSymGenerator.getInstance().id(key1);
        let initial: arkts.Expression = factory.createBlockStatementForOptionalExpression(object, key1)
        const statements: arkts.Statement[] = [
            factory.generateLetVariableDecl(
                arkts.factory.createIdentifier(id, undefined),
                initial
            ),
            factory.generateTernaryExpression(id, key2)
        ];
        return arkts.factory.createBlockExpression(statements);
    }


}