/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 
@Entry
@Component
struct QRCodeExample {
  private value: string = 'hello world'

  build() {
    Column({ space: 5 }) {
      Text('normal')
        .fontSize(9)
        .width('90%')
        .fontColor(0xCCCCCC)
        .fontSize(30)
      QRCode(this.value)
        .width(140)
        .height(140)

      Text('color')
        .fontSize(9)
        .width('90%')
        .fontColor(0xCCCCCC)
        .fontSize(30)
      QRCode(this.value)
        .color(0xF7CE00)
        .width(140)
        .height(140)

      Text('backgroundColor')
        .fontSize(9)
        .width('90%')
        .fontColor(0xCCCCCC)
        .fontSize(30)
      QRCode(this.value)
        .width(140)
        .height(140)
        .backgroundColor(Color.Orange)

      Text('contentOpacity')
        .fontSize(9)
        .width('90%')
        .fontColor(0xCCCCCC)
        .fontSize(30)
      QRCode(this.value)
        .width(140)
        .height(140)
        .color(Color.Black)
        .contentOpacity(0.1)
    }.width('100%')
    .margin({ top: 5 })
  }
}