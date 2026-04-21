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

export type A2UIDynamicBoolean = boolean | A2UIDataBinding | A2UIFunctionCall

export class DynamicBoolean {
  static schemaRef(): string {
    return '{ "$ref": "#/$defs/DynamicBoolean" }'
  }

  static schema(): string {
    return `{
  "description": "A boolean value that can be a literal, a path, or a function call returning a boolean.",
  "oneOf": [
    {
      "type": "boolean"
    },
    ${A2UIDataBinding.schema()},
    {
      "allOf": [
        ${A2UIFunctionCall.schema()},
        {
          "properties": {
            "returnType": {
              "const": "boolean"
            }
          }
        }
      ]
    }
  ]
}`
  }

  static read(value: A2UIDynamicBoolean | undefined, defaultValue: boolean = false,
    context?: A2UIResolveContext): boolean {
    let resolvedValue: boolean = DynamicValueResolver.resolveBoolean(value, defaultValue, context)
    return DynamicValue.asBoolean(resolvedValue, defaultValue)
  }
}
