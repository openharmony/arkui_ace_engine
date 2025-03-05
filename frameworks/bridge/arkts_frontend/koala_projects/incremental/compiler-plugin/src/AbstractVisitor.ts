/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import * as ts from '@koalaui/ets-tsc';

export abstract class AbstractVisitor {
    constructor(
        public ctx: ts.TransformationContext
    ) {}

    indentation = 0

    withIndentation<T>(exec: () => T) {
        this.indentation++
        const result = exec()
        this.indentation--
        return result
    }

    abstract visitor(node: ts.Node): ts.Node

    visitEachChild<T extends ts.Node>(node: T): T {
        return this.withIndentation(() =>
            ts.visitEachChild(
                node,
                it => this.visitor(it),
                this.ctx
            )
        )
    }
}
