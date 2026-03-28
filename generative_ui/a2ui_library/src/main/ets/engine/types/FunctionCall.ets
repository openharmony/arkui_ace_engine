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

import { DynamicValue, A2UIDynamicValue } from './DynamicValue'

export type A2UIFunctionReturnType = 'string' | 'number' | 'boolean' | 'array' | 'object' | 'any' | 'void'
export type A2UIFunctionArgs = Record<string, A2UIDynamicValue | Record<string, Object>>

export class A2UIFunctionCall {
  call: string = ''
  args?: A2UIFunctionArgs
  returnType?: A2UIFunctionReturnType

  static schemaRef(): string {
    return '{ "$ref": "#/$defs/FunctionCall" }'
  }

  static schema(): string {
    return `{
  "type": "object",
  "description": "Invokes a named function on the client.",
  "properties": {
    "call": {
      "type": "string",
      "description": "The name of the function to call."
    },
    "args": {
      "type": "object",
      "description": "Arguments passed to the function.",
      "additionalProperties": {
        "anyOf": [
          ${A2UIFunctionCall.argumentValueSchema()},
          {
            "type": "object",
            "description": "A literal object argument (e.g. configuration)."
          }
        ]
      }
    },
    "returnType": {
      "type": "string",
      "description": "The expected return type of the function call.",
      "enum": ["string", "number", "boolean", "array", "object", "any", "void"],
      "default": "boolean"
    }
  },
  "required": ["call"]
}`
  }

  private static argumentValueSchema(): string {
    return `{
  "description": "A function argument value.",
  "oneOf": [
    { "type": "string" },
    { "type": "number" },
    { "type": "boolean" },
    { "type": "array" },
    ${DynamicValue.schemaLiteralOnly()},
    {
      "type": "object",
      "description": "A nested function call.",
      "properties": {
        "call": {
          "type": "string"
        },
        "args": {
          "type": "object",
          "description": "Arguments for the nested function call."
        },
        "returnType": {
          "type": "string",
          "enum": ["string", "number", "boolean", "array", "object", "any", "void"],
          "default": "boolean"
        }
      },
      "required": ["call"]
    }
  ]
}`
  }
}
