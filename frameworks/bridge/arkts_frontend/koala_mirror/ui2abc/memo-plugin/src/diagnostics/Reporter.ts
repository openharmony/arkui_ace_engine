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

export class Reporter {
    /*
        No diagnostics API from es2panda yet, so using `console.error` for now
     */
    static reportOutOfContextMemoCall(callName: string | undefined, contextName: string | undefined): void {
        const call = callName !== undefined
            ? `function ${callName}`
            : `anonymous function`
        const context = contextName !== undefined
            ? `context ${contextName}`
            : `anonymous context`
        console.error(`Calling @memo ${call} from non-@memo ${context}`)
    }

    static reportDefaultValueMemoCall(parameterName: string | undefined): void {
        console.error(`Can not call @memo function at parameter default value expression. Parameter: ${parameterName}`)
    }

    static reportMemoFunctionIsNotExplicitlyTyped(functionName: string | undefined): void {
        const func = functionName ?? `anonymous function`
        console.error(`@memo ${func} must have it's return type explicitly specified`)
    }

    static reportParameterReassignment(parameterName: string, contextName: string | undefined): void {
        const context = contextName !== undefined
            ? contextName
            : `anonymous function`
        console.error(
            `@memo function parameter reassignment is forbidden: parameter ${parameterName} at function ${context}`
        )
    }
}