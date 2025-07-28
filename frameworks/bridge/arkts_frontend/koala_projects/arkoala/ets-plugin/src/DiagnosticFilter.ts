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

import * as ts from "@koalaui/ets-tsc";
import { IssueTable, NameTable } from "./utils";
import { getLineNumber } from "./ApiUtils";

// The ArkTS language sometimes allows "implicit this". Namely:
// this.$field can be shortened to $field
// In the mainline ArkTS compile this is handled by
// another run of the compiler with diagnosatics turned off.
// Here we filter out the messages and later rewrite the AST to provide the explicit this.
function isDollarIssue(sourceFile: ts.SourceFile, nameTable: NameTable, message: ts.Diagnostic, text: string): boolean {
    if (message.file == sourceFile &&
        // TODO: how stable are typescript message codes?
        (message.code == 2304 ||  message.code == 2552) &&
        text.startsWith("Cannot find name \'\$")
    ) {
        const variableName = text.substring(18).split("'")[0]
        // This one only checks that we have it in the same file.
        // But it can be an another struct.
        // TODO: may be check the line number range?
        if (nameTable.dollars.includes(variableName)) {
            // Keep it in the reverse order for convenient removal.
            return true
        }
    }
    return false
}

// When using @Styles marked functions
// There magically appear methods with the same name
// Like, for example:
// @Styles foo() {}
//
// Now we can write
// Text().foo().width(17)
//
// But there is no return type known for foo(),
// so width() can not know its receiver.

function isStylesIssue(sourceFile: ts.SourceFile, message: ts.Diagnostic, text: string): boolean {
    if (message.file == sourceFile &&
        // TODO: how stable are typescript message codes?
        message.code == 2339 &&
        text.includes("does not exist on type 'unknown'")
    ) {
        // TODO: this is too permissive :-(
        return true
    }
    return false
}

function isNewEtsWithPropIssue(sourceFile: ts.SourceFile, issueTable: IssueTable, message: ts.Diagnostic, text: string): boolean {
    if (message.file == sourceFile &&
        issueTable.newEtsWithProperty.includes(getLineNumber(sourceFile, message.start!)) &&
        // TODO: how stable are typescript message codes?
        message.code == 2350 &&
        text.includes("Only a void function can be called with the 'new' keyword")
    ) {
        // TODO: this is too permissive :-(
        return true
    }
    return false
}

function isNewEtsIssue(sourceFile: ts.SourceFile, issueTable: IssueTable, message: ts.Diagnostic, text: string): boolean {
    if (message.file == sourceFile &&
        issueTable.newEts.includes(getLineNumber(sourceFile, message.start!)) &&
        // TODO: how stable are typescript message codes?
        message.code == 2351 &&
        text.includes("This expression is not constructable")
    ) {
        // TODO: this is too permissive :-(
        return true
    }
    return false
}



function isBuilderLambdaIssue(sourceFile: ts.SourceFile, issueTable: IssueTable, message: ts.Diagnostic, text: string): boolean {
    if (message.file == sourceFile &&
        issueTable.builderLambda.includes(getLineNumber(sourceFile, message.start!)) &&
        // TODO: how stable are typescript message codes?
        message.code == 1206 &&
        text.startsWith("Decorators are not valid here")
    ) {
        return true
    }
    return false
}


export function filterOutDiagnostics(sourceFile: ts.SourceFile, nameTable: NameTable, issueTable: IssueTable, extras?: ts.TransformerExtras) {
    const indicesToRemove: number[] = []

    extras?.diagnostics.forEach((message, index) => {
        const messageText = message.messageText
        const text: string = typeof messageText === "string" ? messageText : messageText.messageText

        if (isDollarIssue(sourceFile, nameTable, message, text) ||
            isStylesIssue(sourceFile, message, text) ||
            isNewEtsIssue(sourceFile, issueTable, message, text) ||
            isNewEtsWithPropIssue(sourceFile, issueTable, message, text) ||
            isBuilderLambdaIssue(sourceFile, issueTable, message, text)
        ) {

            indicesToRemove.unshift(index)
        }
    })

    indicesToRemove.forEach(index => {
        extras?.removeDiagnostic(index)
    })
}