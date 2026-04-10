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

import {
  A2UIRenderComponent,
  Catalog,
  CatalogItem,
  createBlankDefinition,
  CustomComponentDefinition,
  CustomComponentFactory,
  SurfaceController,
  SurfaceEventCallback,
  SurfaceEventType
} from 'a2ui_library';

function createBlankDefinitions(): Array<CustomComponentDefinition> {
  return [createBlankDefinition()];
}

function createBlankShowcaseCatalog(definitions: Array<CustomComponentDefinition>): Catalog {
  for (const definition of definitions) {
    CustomComponentFactory.registerCustomComponent(definition);
  }

  let supportedNativeItems: CatalogItem[] = [];
  let basicItems: CatalogItem[] = Catalog.basic().components;
  for (const componentName of ['Column', 'Text']) {
    for (const item of basicItems) {
      if (item.name === componentName) {
        supportedNativeItems.push(item);
      }
    }
  }
  supportedNativeItems.push(CustomComponentFactory.createCatalogItem('Blank'));
  return new Catalog('blank-demo-catalog', supportedNativeItems);
}

@Entry
@Component
export struct SurfaceShowcase {
  private createMainJson: string =
    '{"version":"v0.9","createSurface":{"surfaceId":"main","catalogId":"https://a2ui.org/specification/v0_9/standard_catalog.json"}}';
  private updateMainJson: string =
    '{"version":"v0.9","updateComponents":{"surfaceId":"main","components":[{"id":"root","component":"Column","children":["checkoutTitle","checkinTitle"]}, {"id":"checkoutTitle","component":"Text","text":"Hello World 01!"}, {"id":"checkinTitle","component":"Text","text":"Hello World 02!"}]}}';
  private deleteMainJson: string =
    '{"version":"v0.9","deleteSurface":{"surfaceId":"main"}}';
  private createCustomJson: string =
    '{"version":"v0.9","createSurface":{"surfaceId":"blank-demo","catalogId":"blank-demo-catalog"}}';
  private updateCustomJson: string =
    '{"version":"v0.9","updateComponents":{"surfaceId":"blank-demo","components":[{"id":"root","component":"Column","widthPercent":100,"heightPercent":100,"children":["blank1"]},{"id":"blank1","component":"Blank","min":160,"color":"#552299FF"}]}}';
  private deleteCustomJson: string =
    '{"version":"v0.9","deleteSurface":{"surfaceId":"blank-demo"}}';

  private surfaceEventCallback: SurfaceEventCallback = (
    eventType: SurfaceEventType,
    controller: SurfaceController
  ) => {}

  private catalog: Catalog = Catalog.basic();
  private attr: Array<CustomComponentDefinition> = createBlankDefinitions();
  private blankCatalog: Catalog = createBlankShowcaseCatalog(this.attr);
  private mainSurfaceController: SurfaceController =
    new SurfaceController(this.catalog, this.surfaceEventCallback);
  private customSurfaceController: SurfaceController =
    new SurfaceController(this.blankCatalog, this.surfaceEventCallback);

  aboutToAppear(): void {
    CustomComponentFactory.InstallCustomComponent(this.getUIContext(), this.attr);
    setTimeout(() => {
      this.mainSurfaceController.onReceive(this.createMainJson);
      this.customSurfaceController.onReceive(this.createCustomJson);

      setTimeout(() => {
        this.mainSurfaceController.onReceive(this.updateMainJson);
        this.customSurfaceController.onReceive(this.updateCustomJson);

        setTimeout(() => {
          this.mainSurfaceController.onReceive(this.deleteMainJson);
          this.customSurfaceController.onReceive(this.deleteCustomJson);
        }, 1000);
      }, 500);
    }, 200);
  }

  build() {
    Column() {
      Column() {
        A2UIRenderComponent({ surfaceControllerBound: this.mainSurfaceController })
      }
      .width('100%')
      .layoutWeight(1)

      Column() {
        A2UIRenderComponent({ surfaceControllerBound: this.customSurfaceController })
      }
      .width('100%')
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
  }
}
