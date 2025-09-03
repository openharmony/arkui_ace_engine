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

import * as ts from '@koalaui/ets-tsc'
import { CallTable, EntryTable, FunctionKind, FunctionTable, PositionalIdTracker, TransformerOptions, VariableTable } from "./util"

export class Rewrite {
    public functionTable: FunctionTable
    public callTable: CallTable
    public variableTable: VariableTable
    public entryTable: EntryTable
    public positionalIdTracker: PositionalIdTracker

    constructor(sourceFile: ts.SourceFile, public pluginOptions: TransformerOptions) {
        this.functionTable = new Map<ts.SignatureDeclarationBase, FunctionKind>()
        this.callTable = new Map<ts.CallExpression, FunctionKind>()
        this.variableTable = new Map<ts.VariableLikeDeclaration, FunctionKind>()
        this.entryTable = new Set<ts.CallExpression>()
        this.positionalIdTracker = new PositionalIdTracker(sourceFile, pluginOptions.stableForTest ?? false)

    }

    public importTypesFrom: string|undefined = undefined
}