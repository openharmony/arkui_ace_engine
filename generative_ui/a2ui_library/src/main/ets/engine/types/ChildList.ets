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

import { A2UIComponentId } from './ComponentCommon'

export type A2UIChildListValue = string[] | A2UIDynamicChildListTemplate

export class A2UIDynamicChildListTemplate {
  componentId: string = ''
  path: string = ''

  static schema(): string {
    return `{
  "type": "object",
  "description": "A template for generating a dynamic list of children from a data model list. The componentId is the component to use as a template.",
  "properties": {
    "componentId": ${A2UIComponentId.schema()},
    "path": {
      "type": "string",
      "description": "The path to the list of component property objects in the data model."
    }
  },
  "required": ["componentId", "path"],
  "additionalProperties": false
}`
  }
}

export class A2UIChildList {
  static schema(): string {
    return `{
  "oneOf": [
    {
      "type": "array",
      "items": ${A2UIComponentId.schema()},
      "description": "A static list of child component IDs."
    },
    ${A2UIDynamicChildListTemplate.schema()}
  ]
}`
  }
}
