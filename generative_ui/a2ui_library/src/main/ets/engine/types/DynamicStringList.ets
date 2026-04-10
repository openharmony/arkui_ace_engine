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

import { A2UIDataBinding } from './DataBinding'
import { A2UIFunctionCall } from './FunctionCall'
import { A2UIResolveContext } from './runtime/ResolveContext'
import { DynamicValueResolver } from './runtime/DynamicValueResolver'

export type A2UIDynamicStringList = string[] | A2UIDataBinding | A2UIFunctionCall

export class DynamicStringList {
  static schemaRef(): string {
    return '{ "$ref": "#/$defs/DynamicStringList" }'
  }

  static schema(): string {
    return `{
  "description": "Represents a value that can be either a literal array of strings, a path to a string array in the data model, or a function call returning a string array.",
  "oneOf": [
    {
      "type": "array",
      "items": {
        "type": "string"
      }
    },
    ${A2UIDataBinding.schema()},
    {
      "allOf": [
        ${A2UIFunctionCall.schema()},
        {
          "properties": {
            "returnType": {
              "const": "array"
            }
          }
        }
      ]
    }
  ]
}`
  }

  static read(value: A2UIDynamicStringList | undefined, defaultValue: string[] = [],
    context?: A2UIResolveContext): string[] {
    return DynamicValueResolver.resolveStringList(value, defaultValue, context)
  }
}
