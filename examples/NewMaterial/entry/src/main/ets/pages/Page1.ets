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

import uiMaterial from "@ohos.arkui.uiMaterial";
//import { uiMaterial } from '@kit.ArkUI';

class A {

}
@Entry
@Component
struct Page1 {
  @State material: uiMaterial.Material | undefined | null =
    new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT });

  build() {
    Column() {
      Column()
        .width(200)
        .height(100)
        .systemMaterial(this.material)
        .position({ x: 30, y: 50 })
        .onClick(() => {
          console.info("onClick uiMaterial");
        })

      Column()
        .width(200)
        .height(100)
        .systemMaterial(this.material)
        .position({ x: 50, y: 200 })

      Column()
        .width(200)
        .height(100)
        .systemMaterial(this.material)
        .position({ x: 100, y: 400 })
    }
    .width("100%")
    .height("100%")
    .backgroundImage($r('app.media.startIcon'))
    .backgroundImageSize({ width: "100%", height: "100%" })
  }
}