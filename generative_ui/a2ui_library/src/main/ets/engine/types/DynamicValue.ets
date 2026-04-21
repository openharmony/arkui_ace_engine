/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { A2UIValueType } from './types'
import { A2UIDataBinding } from './DataBinding'
import { A2UIFunctionCall } from './FunctionCall'
import { A2UIResolveContext } from './runtime/ResolveContext'
import { DynamicValueResolver } from './runtime/DynamicValueResolver'

export type A2UIDynamicValue = A2UIValueType | A2UIDataBinding | A2UIFunctionCall

export class DynamicValue {
  static schemaRef(): string {
    return '{ "$ref": "#/$defs/DynamicValue" }'
  }

  static schema(): string {
    return `{
  "description": "A value that can be a literal, a path, or a function call returning any type.",
  "oneOf": [
    { "type": "string" },
    { "type": "number" },
    { "type": "boolean" },
    { "type": "array" },
    ${A2UIDataBinding.schema()},
    ${A2UIFunctionCall.schema()}
  ]
}`
  }

  static schemaLiteralOnly(): string {
    return A2UIDataBinding.schema()
  }

  static asStringWithDefault(value: string | undefined, defaultValue: string): string {
    return value !== undefined ? value : defaultValue
  }

  static asNumberWithDefault(value: number | undefined, defaultValue: number): number {
    return value !== undefined && Number.isFinite(value) ? value : defaultValue
  }

  static asBoolean(value: boolean | undefined, defaultValue: boolean = false): boolean {
    return value !== undefined ? value : defaultValue
  }

  static resolve(value: A2UIDynamicValue | undefined, context?: A2UIResolveContext) {
    return DynamicValueResolver.resolveValue(value, context)
  }
}
