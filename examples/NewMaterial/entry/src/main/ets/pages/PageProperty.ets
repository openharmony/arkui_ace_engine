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
@Entry
@Component
struct PageProperty {
  @State y1: number = 0;
  @State spacing: number = 30;
  @State borderWidth1: number = 1;
  @State color1: ResourceColor = Color.Transparent;

  build() {
    Column() {
      UnionEffectContainer({ spacing: this.spacing }) {
        Column({ space: 20 }) {
          Text("no union") // 不使用新材质效果

          Column()
            .width(100)
            .height(100)
            .borderRadius(50) // 圆
            .useUnionEffect(true)
            .translate({ x: 0, y: this.y1 }) //或offset、position之类的改变其位置

          Column()
            .width(100)
            .height(30)
            .useUnionEffect(true)
        }
      }
      .width("80%")
      .height("50%")
      .borderWidth(this.borderWidth1)
      .backgroundColor(this.color1)

      Row() {
        Text("borderWidth:")
        Button("0")
          .width(100)
          .onClick(() => {
            this.borderWidth1 = 0;
          })
        Button("1")
          .width(100)
          .onClick(() => {
            this.borderWidth1 = 1;
          })
        Button("10")
          .width(100)
          .onClick(() => {
            this.borderWidth1 = 10;
          })
      }.width('100%')

      Row() {
        Text("color:")
        Button("transparent")
          .width(100)
          .onClick(() => {
            this.color1 = Color.Transparent;
          })
        Button("red")
          .width(100)
          .onClick(() => {
            this.color1 = Color.Red;
          })
        Button("blue")
          .width(100)
          .onClick(() => {
            this.color1 = Color.Blue;
          })
      }.width('100%')
    }
    .width('100%')
    .height('100%')
  }
}