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

import { CatalogCategory, CatalogItem } from "../../core/CatalogItem";
import { PromptProvider, PromptProvideResult, SchemaPromptCombineMode, SchemaProvider } from "../../types/types";

export class A2UIButton {
  // 禁止构造
  private constructor() {
  }

  private static type: string = "Button";

  private static schemaProvider: SchemaProvider = () => {
    return '';
  }

  private static promptProvider: PromptProvider = () => {
    let customPrompt: string = '';
    return { mode: SchemaPromptCombineMode.COMBINE, prompt: customPrompt } as PromptProvideResult;
  }

  public static asCatalogItem(): CatalogItem {
    let catalogItem =
      CatalogItem.forComponent(A2UIButton.type, A2UIButton.schemaProvider, undefined, A2UIButton.promptProvider);
    catalogItem.markCategory(CatalogCategory.A2UI_STANDARD).markInnerNative(true);
    return catalogItem
  }
}
