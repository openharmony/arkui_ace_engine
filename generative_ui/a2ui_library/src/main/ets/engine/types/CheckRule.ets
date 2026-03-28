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

import { DynamicBoolean } from './DynamicBoolean'

export class A2UICheckRule {
  condition: boolean | Object = false
  message: string = ''

  static schema(): string {
    return `{
  "type": "object",
  "description": "A single validation rule applied to an input component.",
  "properties": {
    "condition": ${DynamicBoolean.schema()},
    "message": {
      "type": "string",
      "description": "The error message to display if the check fails."
    }
  },
  "required": ["condition", "message"],
  "additionalProperties": false
}`
  }
}
