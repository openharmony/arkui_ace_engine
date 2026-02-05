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
import { AttributeUpdater } from '@kit.ArkUI';

class MyModifier implements AttributeModifier<CommonAttribute> {
  material: uiMaterial.Material | undefined | null = undefined;

  applyNormalAttribute(instance: CommonAttribute): void {
    console.info("applyNormalAttribute set systemMaterial");
    instance.systemMaterial(this.material);
  }
}
@Entry
@Component
struct Page2 {
  @State myModifier: MyModifier = new MyModifier();
  @State material: uiMaterial.Material | undefined | null = undefined;
  @State myUpdater: AttributeUpdater<CommonAttribute> = new AttributeUpdater<CommonAttribute>();

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

      // 使用ets接口

      Stack() {
        Text("hello")
          .width(200)
          .height(100)
        Column()
          .width(200)
          .height(100)
          .borderRadius(10)
          .attributeModifier(this.myModifier)
      }.margin({ top: 30 })

      // 使用attributeModifier

      Stack() {
        Text("hello")
          .width(200)
          .height(100)
        Column()
          .width(200)
          .height(100)
          .borderRadius(10)
          .attributeModifier(this.myUpdater)
      }
      .margin({ top: 30 })

      // 使用attributeUpdater

      Column() {
        Button("null")
          .onClick(() => {
            this.material = null;
            this.myModifier.material = this.material;
            this.myUpdater.attribute?.systemMaterial(this.material);
            console.info("material null click");
          })
        Button("undefined")
          .onClick(() => {
            this.material = undefined;
            this.myModifier.material = this.material;
            this.myUpdater.attribute?.systemMaterial(this.material);
            console.info("material undefined click");
          })
        Button("no type")
          .onClick(() => {
            this.material = new uiMaterial.Material();
            this.myModifier.material = this.material;
            this.myUpdater.attribute?.systemMaterial(this.material);
            console.info("material no type click");
          })
        Button("type NONE")
          .onClick(() => {
            this.material = new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE });
            this.myModifier.material = this.material;
            this.myUpdater.attribute?.systemMaterial(this.material);
            console.info("material type none click");
          })
        Button("type SEMI_TRANSPARENT")
          .onClick(() => {
            this.material = new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT });
            this.myModifier.material = this.material;
            this.myUpdater.attribute?.systemMaterial(this.material);
            console.info("material type SEMI_TRANSPARENT click");
          })
        Button("type -10")
          .onClick(() => {
            this.material = new uiMaterial.Material({ type: -10 });
            this.myModifier.material = this.material;
            this.myUpdater.attribute?.systemMaterial(this.material);
            console.info("material type -10 click");
          })
      }.margin({ top: 30 })
    }.position({ x: 50, y: 50 })
  }
}