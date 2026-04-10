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

import { DynamicValue } from './DynamicValue'
import { A2UIDataBinding } from './DataBinding'
import { A2UIFunctionCall } from './FunctionCall'
import { A2UIResolveContext } from './runtime/ResolveContext'
import { DynamicValueResolver } from './runtime/DynamicValueResolver'

export type A2UIDynamicNumber = number | A2UIDataBinding | A2UIFunctionCall

export class DynamicNumber {
  static schemaRef(): string {
    return '{ "$ref": "#/$defs/DynamicNumber" }'
  }

  static schema(): string {
    return `{
  "description": "Represents a value that can be either a literal number, a path to a number in the data model, or a function call returning a number.",
  "oneOf": [
    {
      "type": "number"
    },
    ${A2UIDataBinding.schema()},
    {
      "allOf": [
        ${A2UIFunctionCall.schema()},
        {
          "properties": {
            "returnType": {
              "const": "number"
            }
          }
        }
      ]
    }
  ]
}`
  }

  static read(value: A2UIDynamicNumber | undefined, defaultValue: number, context?: A2UIResolveContext): number {
    let resolvedValue: number = DynamicValueResolver.resolveNumber(value, defaultValue, context)
    return DynamicValue.asNumberWithDefault(resolvedValue, defaultValue)
  }
}
