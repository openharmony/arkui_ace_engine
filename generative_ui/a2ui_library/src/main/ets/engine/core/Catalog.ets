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

import { allA2UIBasicFunctions } from '../functions/A2UIBasicFunctions';
import { allA2UIBasicComponents } from "../components/A2UI/A2UIBasicComponents";
import { CatalogItem } from "./CatalogItem";

export interface ComponentType {
  name: string;
}

export class Catalog {
  private id: string;
  components: CatalogItem[];
  functions: CatalogItem[];

  constructor(id: string, components: CatalogItem[], functions: CatalogItem[] = []) {
    this.id = id;
    this.components = components;
    this.functions = functions;
  }

  public getCatalogId(): string {
    return this.id;
  }

  // a2ui basic
  public static basic(): Catalog {
    return new Catalog(
      'https://a2ui.org/specification/v0_9/standard_catalog.json',
      allA2UIBasicComponents(),
      allA2UIBasicFunctions()
    );
  }

  public hasFunction(name: string): boolean {
    return this.functions.find((item: CatalogItem) => item.name === name) !== undefined;
  }
}
