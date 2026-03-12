/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct BorderExample1 {
  build() {
    Column() {
      Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
        // 线段
        Text('dashed1')
          .borderStyle(BorderStyle.Dashed)
          .borderWidth(5)
          .borderColor(0xAFEEEE)
          .borderRadius(10)
          .width(120)
          .height(120)
          .textAlign(TextAlign.Center)
          .fontSize(16)
        Text('dashed2')
          .borderStyle(BorderStyle.Dashed)
          .borderWidth('5')
          .borderColor(0xAFEEEE)
          .borderRadius(10)
          .width(120)
          .height(120)
          .textAlign(TextAlign.Center)
          .fontSize(16)
        Text('dashed3')
          .borderStyle(BorderStyle.Dashed)
          .borderWidth($r('app.float.borderWidth'))
          .borderColor(0xAFEEEE)
          .borderRadius(10)
          .width(120)
          .height(120)
          .textAlign(TextAlign.Center)
          .fontSize(16)
        Text('dashed4')
          .borderStyle(BorderStyle.Dashed)
          .borderWidth({
            left: 5,
            right: 5,
            top: 5,
            bottom: 5
          })
          .borderColor(0xAFEEEE)
          .borderRadius(10)
          .width(120)
          .height(120)
          .textAlign(TextAlign.Center)
          .fontSize(16)
        // 点线
        Text('dotted')
          .border({
            width: 5,
            color: 0x317AF7,
            radius: 10,
            style: BorderStyle.Dotted
          })
          .width(120)
          .height(120)
          .textAlign(TextAlign.Center)
          .fontSize(16)
      }.width('100%').height(150)
      Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
      Text('dashed5')
        .borderStyle(BorderStyle.Dashed)
        .borderWidth({
          left: 5,
          right: 5,
          top: 5,
          bottom: 5
        })
        .borderColor(Color.Red)
        .borderRadius(10)
        .width(120)
        .height(120)
        .textAlign(TextAlign.Center)
        .fontSize(16)

      Text('dashed6')
        .borderStyle(BorderStyle.Dashed)
        .borderWidth({
          left: 5,
          right: 5,
          top: 5,
          bottom: 5
        })
        .borderColor('rgb(255, 100, 255)')
        .borderRadius(10)
        .width(120)
        .height(120)
        .textAlign(TextAlign.Center)
        .fontSize(16)

      Text('dashed6')
        .borderStyle(BorderStyle.Dashed)
        .borderWidth({
          left: 5,
          right: 5,
          top: 5,
          bottom: 5
        })
        .borderColor($r('app.color.Gray'))
        .borderRadius(10)
        .width(120)
        .height(120)
        .textAlign(TextAlign.Center)
        .fontSize(16)
        }

      Text('.border')
        .fontSize(50)
        .width(300)
        .height(300)
        .border({
          width: {
            left: 3,
            right: 6,
            top: 10,
            bottom: 15
          },
          color: {
            left: '#e3bbbb',
            right: Color.Blue,
            top: Color.Red,
            bottom: Color.Green
          },
          radius: {
            topLeft: 10,
            topRight: 20,
            bottomLeft: 40,
            bottomRight: 80
          },
          style: {
            left: BorderStyle.Dotted,
            right: BorderStyle.Dotted,
            top: BorderStyle.Solid,
            bottom: BorderStyle.Dashed
          }
        })
        .textAlign(TextAlign.Center)
    }
  }
}