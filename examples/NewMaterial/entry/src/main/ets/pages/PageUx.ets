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
import curves from '@ohos.curves';
@Entry
@Component
struct PageEts {
  @State y1: number = 0;
  @State spacing: number = 50;
  @State duration: number = 150;
  @State curve: ICurve | Curve = Curve.EaseInOut;

  build() {
    Column() {
      UnionEffectContainer({ spacing: this.spacing }) {
        Column({ space: 40 }) {
          Column()
            .width(100)
            .height(100)
            .borderRadius(50) // 圆
            .useUnionEffect(true)
            .translate({ x: 0, y: this.y1 }) //或offset、position之类的改变其位置

          Column()
            .width(300)
            .height(30)
            .useUnionEffect(true)
            .useUnionEffect(true)
        }
      }
      .width("80%")
      .height("50%")
      .systemMaterial(new hdsMaterial.Material({
        backgroundMaterial: {
          type: hdsMaterial.MaterialType.IMMERSIVE,
          scenario: hdsMaterial.ScenarioType.ULTRA_THIN,
          level: hdsMaterial.MaterialLevel.EXQUISITE,
          darkMode: hdsMaterial.DarkMode.ADAPTIVE
        }
      })) // 设置新材质

      Row() {
        Text("inner button:")
        Button("down")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: this.duration, curve: this.curve }, () => {
              this.y1 = this.y1 + 10;
            })
          })
        Button("up")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: this.duration, curve: this.curve }, () => {
              this.y1 = this.y1 - 10;
            })
          })
      }.width('100%')

      Row() {
        Text("spacing:")
        Button("0")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: this.duration, curve: this.curve }, () => {
              this.spacing = 0;
            })
          })
        Button("50")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: this.duration, curve: this.curve }, () => {
              this.spacing = 50;
            })
          })
        Button("100")
          .width(100)
          .onClick(() => {
            this.getUIContext().animateTo({ duration: this.duration, curve: this.curve }, () => {
              this.spacing = 100;
            })
          })
      }.width('100%')

      Row() {
        Text("duration:")
        Button("150")
          .width(100)
          .onClick(() => {
            this.duration = 150;
          })
        Button("300")
          .width(100)
          .onClick(() => {
            this.duration = 300;
          })
        Button("600")
          .width(100)
          .onClick(() => {
            this.duration = 600;
          })
      }.width('100%')

      Row() {
        Text("curve:")
        Button("easeInout")
          .width(100)
          .onClick(() => {
            this.curve = Curve.EaseInOut;
          })
        Button("linear")
          .width(100)
          .onClick(() => {
            this.curve = Curve.Linear;
          })

      }.width('100%')

      Row() {
        Button("springMotion(0.3,0.6)")
          .width(200)
          .onClick(() => {
            this.curve = curves.springMotion(0.3, 0.6);
          })
        Button("springMotion(0.6,0.6)")
          .width(200)
          .onClick(() => {
            this.curve = curves.springMotion(0.6, 0.6);
          })
      }.width('100%')

      Row() {
        Button("springMotion(0.3,0.4)")
          .width(200)
          .onClick(() => {
            this.curve = curves.springMotion(0.3, 0.4);
          })
        Button("springMotion(0.6,0.4)")
          .width(200)
          .onClick(() => {
            this.curve = curves.springMotion(0.6, 0.4);
          })
      }.width('100%')
    }
    .width('100%')
    .height('100%')
  }
}