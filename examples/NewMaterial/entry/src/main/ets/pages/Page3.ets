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
@Entry
@Component
struct Page3 {
  @State material: uiMaterial.Material | undefined | null = undefined;
  @State radius1: number = 30;
  @State offsetY: number = 20;
  @State color1: number | string = "#30000000";

  build() {
    Column() {
      Stack() {
        Text("hello")
          .width(200)
          .height(100)
        Column()
          .width(200)
          .height(100)
          .borderRadius(10)
          .systemMaterial(this.material)
      }

      Column()
        .width(200)
        .height(100)
        .borderRadius(10)
        // .borderWidth(this.borderwidth1)
        .shadow({ radius: this.radius1, color: this.color1, offsetY: this.offsetY })

      Column() {
        Button("type NONE")
          .onClick(() => {
            this.getUIContext().animateTo({}, () => {
              this.material = new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE });
              this.radius1 = 0;
              this.offsetY = 0;
              this.color1 = "#ff000000";
            });
            console.info("material type none click");
          })
        Button("type SEMI_TRANSPARENT")
          .onClick(() => {
            this.getUIContext().animateTo({}, () => {
              this.material = new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT });
              this.radius1 = 30;
              this.offsetY = 20;
              this.color1 = "#30000000";
            });
            console.info("material type SEMI_TRANSPARENT click");
          })
      }.margin({ top: 30 })
    }.position({ x: 50, y: 50 })
  }
}