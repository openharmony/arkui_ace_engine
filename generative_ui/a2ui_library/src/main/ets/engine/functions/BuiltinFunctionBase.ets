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

import { common } from '@kit.AbilityKit';

import { CatalogCategory, CatalogItem } from '../core/CatalogItem';
import { A2UIValueType, PromptProvideResult, PromptProvider, SchemaPromptCombineMode, SchemaProvider } from '../types/types';
import { LocalFunctionHandler } from './LocalFunction';

function emptyFunctionCall(): A2UIValueType {
  return undefined;
}

export class BuiltinFunctionBase {
  private readonly name: string;
  private readonly category: CatalogCategory;

  constructor(name: string, category: CatalogCategory = CatalogCategory.A2UI_STANDARD) {
    this.name = name;
    this.category = category;
  }

  public asCatalogItem(): CatalogItem {
    let catalogItem = CatalogItem.forFunction(
      this.name,
      this.schemaProvider(),
      emptyFunctionCall,
      this.promptProvider()
    );
    catalogItem.markCategory(this.category);
    return catalogItem;
  }

  public createHandler(): LocalFunctionHandler {
    throw new Error(`Builtin function handler is not implemented: ${this.name}`);
  }

  public setHostContext(_hostContext: common.UIAbilityContext | undefined): void {
  }

  protected schemaProvider(): SchemaProvider {
    return () => '';
  }

  protected promptProvider(): PromptProvider {
    return () => {
      let customPrompt: string = '';
      return { mode: SchemaPromptCombineMode.COMBINE, prompt: customPrompt } as PromptProvideResult;
    };
  }
}
