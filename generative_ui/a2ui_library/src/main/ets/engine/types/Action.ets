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
import { A2UIFunctionCall } from './FunctionCall'

export class A2UIEventAction {
  name: string = ''
  context?: Record<string, Object>

  static schema(): string {
    return `{
  "type": "object",
  "description": "The event to dispatch to the server.",
  "properties": {
    "name": {
      "type": "string",
      "description": "The name of the action to be dispatched to the server."
    },
    "context": {
      "type": "object",
      "description": "A JSON object containing the key-value pairs for the action context. Values can be literals or paths.",
      "additionalProperties": ${DynamicValue.schema()}
    }
  },
  "required": ["name"],
  "additionalProperties": false
}`
  }
}

export class A2UIServerAction {
  event: A2UIEventAction = new A2UIEventAction()

  static schema(): string {
    return `{
  "type": "object",
  "description": "Triggers a server-side event.",
  "properties": {
    "event": ${A2UIEventAction.schema()}
  },
  "required": ["event"],
  "additionalProperties": false
}`
  }
}

export class A2UILocalFunctionAction {
  functionCall: A2UIFunctionCall = new A2UIFunctionCall()

  static schema(): string {
    return `{
  "type": "object",
  "description": "Executes a local client-side function.",
  "properties": {
    "functionCall": ${A2UIFunctionCall.schema()}
  },
  "required": ["functionCall"],
  "additionalProperties": false
}`
  }
}

export class A2UIAction {
  static schema(): string {
    return `{
  "description": "Defines an interaction handler that can either trigger a server-side event or execute a local client-side function.",
  "oneOf": [
    ${A2UIServerAction.schema()},
    ${A2UILocalFunctionAction.schema()}
  ]
}`
  }
}
