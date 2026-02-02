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

import  {hdsMaterial}  from '@hms.hds.hdsMaterial';
import uiMaterial from '@ohos.arkui.uiMaterial';
@Entry
@Component
struct PageEts {
  @State y1: number = 0;
  @State y2: number = 0;
  @State x2: number = 0;
  @State spacing: number = 30;
  @State lightIntensity: number = 2;
  @State bloomValue: number = 1;
  @State useUnion1: boolean = true;
  @State useUnion2: boolean = true;

  build() {
    Column() {
      UnionEffectContainer({ spacing: this.spacing }) {
        Column({ space: 20 } as ColumnOptions) {
          Text("no union") // 不使用新材质效果

          Flex()
            .pointLight({ illuminated: IlluminatedType.BORDER_CONTENT })
            .backgroundColor(0x307af7)
            .size({ width: 50, height: 50 })

          Column()
            .width(100)
            .height(100)
            .borderRadius(50) // 圆
            .useUnionEffect(this.useUnion1)
            .translate({ x: 0, y: this.y1 }) //或offset、position之类的改变其位置

          Column()
            .width(100)
            .height(30)
            .useUnionEffect(true)
            .useUnionEffect(this.useUnion2)
        }
      }
      .width("80%")
      .height("50%")
      .systemMaterial(new hdsMaterial.Material({
        backgroundMaterial: {
          type: hdsMaterial.MaterialType.IMMERSIVE,
          scenario: hdsMaterial.ScenarioType.GENERAL,
          level: hdsMaterial.MaterialLevel.EXQUISITE,
          darkMode: hdsMaterial.DarkMode.ADAPTIVE
        }
      })) // 设置新材质
      .borderWidth(1)
      .borderWidth(1)
      .backgroundColor("#F2F1F3F5")
      .shadow(ShadowStyle.OUTER_DEFAULT_SM)
      .systemMaterial(new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT }))
      .pointLight({
        lightSource: {
          intensity: this.lightIntensity,
          positionX: "50%",
          positionY: "50%",
          positionZ: 80,
          color: "#ff0000"
        },
        illuminated: IlluminatedType.BORDER_CONTENT,
        bloom: this.bloomValue
      })
      .pointLight({ illuminated: IlluminatedType.BORDER_CONTENT })

      Flex()
        .pointLight({ illuminated: IlluminatedType.BORDER_CONTENT })
        .backgroundColor(0x307af7)
        .size({ width: 50, height: 50 })
        .pointLight({
          lightSource: {
            intensity: this.lightIntensity,
            positionX: "50%",
            positionY: "50%",
            positionZ: 80,
            color: "#ff0000"
          },
          bloom: this.bloomValue
        })
        .translate({ x: this.x2, y: this.y2 })

      Row() {
        Text("inner button:")
        Button("down")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.y1 = this.y1 + 10;
            })
          })
        Button("up")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.y1 = this.y1 - 10;
            })
          })
      }.width('100%')

      Row() {
        Text("light:")
        Button("down")
          .width(100)
          .onClick(() => {
            this.y2 = this.y2 + 10;
          })
        Button("up")
          .width(100)
          .onClick(() => {
            this.y2 = this.y2 - 10;
          })
        Button("left")
          .width(100)
          .onClick(() => {
            this.x2 = this.x2 - 10;
          })
        Button("right")
          .width(100)
          .onClick(() => {
            this.x2 = this.x2 + 10;
          })
      }.width('100%')

      Row() {
        Text("spacing:")
        Button("0")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.spacing = 0;
            })
          })
        Button("50")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.spacing = 50;
            })
          })
        Button("100")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: 300 }, () => {
              this.spacing = 100;
            })
          })
      }.width('100%')

      Row() {
        Text("light:")
        Button("0")
          .width(100)
          .onClick(() => {
            this.lightIntensity = 0;
            this.bloomValue = 0;
          })
        Button("2")
          .width(100)
          .onClick(() => {
            this.lightIntensity = 2;
            this.bloomValue = 1;
          })
        Button("10")
          .width(100)
          .onClick(() => {
            this.lightIntensity = 10; //点光源取值范围
            this.bloomValue = 1;
          })
      }.width('100%')

      Row() {
        Text("useUnion1:")
        Button("true")
          .width(100)
          .onClick(() => {
            this.useUnion1 = true;
          })
        Button("false")
          .width(100)
          .onClick(() => {
            this.useUnion1 = false;
          })
      }.width('100%')

      Row() {
        Text("useUnion2:")
        Button("true")
          .width(100)
          .onClick(() => {
            this.useUnion2 = true;
          })
        Button("false")
          .width(100)
          .onClick(() => {
            this.useUnion2 = false; //不能都置为false
          })
      }.width('100%')
    }
    .width('100%')
    .height('100%')
  }
}