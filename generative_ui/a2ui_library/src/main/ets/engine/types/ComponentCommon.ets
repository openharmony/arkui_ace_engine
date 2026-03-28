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

import { DynamicString } from './DynamicString'

export type A2UIComponentIdValue = string

export class A2UIComponentId {
  static schema(): string {
    return `{
  "type": "string",
  "description": "The unique identifier for a component, used for both definitions and references within the same surface."
}`
  }
}

export class A2UIAccessibilityAttributes {
  label?: string | Object
  description?: string | Object

  static schema(): string {
    return `{
  "type": "object",
  "description": "Attributes to enhance accessibility when using assistive technologies like screen readers.",
  "properties": {
    "label": ${DynamicString.schema()},
    "description": ${DynamicString.schema()}
  }
}`
  }
}

export class A2UIComponentCommon {
  id: string = ''
  accessibility?: A2UIAccessibilityAttributes

  static schema(): string {
    return `{
  "type": "object",
  "properties": {
    "id": ${A2UIComponentId.schema()},
    "accessibility": ${A2UIAccessibilityAttributes.schema()}
  },
  "required": ["id"]
}`
  }
}
