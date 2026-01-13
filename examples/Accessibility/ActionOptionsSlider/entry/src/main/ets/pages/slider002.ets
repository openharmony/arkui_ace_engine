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

@Entry
@Component
struct SliderExample2 {
  @State outSetValueOne: number = 40;
  @State inSetValueOne: number = 40;
  @State noneValueOne: number = 40;
  @State outSetValueTwo: number = 40;
  @State inSetValueTwo: number = 40;
  @State vOutSetValueOne: number = 40;
  @State vInSetValueOne: number = 40;
  @State vOutSetValueTwo: number = 40;
  @State vInSetValueTwo: number = 40;

  build() {
    Scroll() {
      Column({ space: 5 }) {
        Text('outset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(5)
        Text('scrollStep:20').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Row() {
          Slider({
            value: this.outSetValueOne,
            min: 0,
            max: 100,
            style: SliderStyle.OutSet
          })
            .accessibilityActionOptions({ scrollStep: 20 })
            .showTips(true)
            .onChange((value: number, mode: SliderChangeMode) => {
              this.outSetValueOne = value;
              console.info('value:' + value + 'mode:' + mode.toString());
            })
          // toFixed(0)将滑动条返回值处理为整数精度
          Text(this.outSetValueOne.toFixed(0)).fontSize(12)
        }
        .width('80%')
        Text('step为10,scrollStep:35').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Row() {
          Slider({
            value: this.outSetValueTwo,
            step: 10,
            style: SliderStyle.OutSet
          })
            .accessibilityActionOptions({ scrollStep:35})
            .showSteps(true)

          Text(this.outSetValueTwo.toFixed(0)).fontSize(12)
        }
        .width('80%')

        Text('step为20,scrollStep:10').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Row() {
          Slider({
            value: this.outSetValueTwo,
            step: 20,
            style: SliderStyle.OutSet
          })
            .accessibilityActionOptions({scrollStep:10})
            .showSteps(true)
          Text(this.outSetValueTwo.toFixed(0)).fontSize(12)
        }
        .width('80%')

        Text('inset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(5)
        Text('scrollStep:20').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Row() {
          Slider({
            value: this.inSetValueOne,
            min: 0,
            max: 100,
            style: SliderStyle.InSet
          })
            .accessibilityActionOptions({scrollStep:20})
            .blockColor('#191970')
            .trackColor('#ADD8E6')
            .selectedColor('#4169E1')
            .showTips(true)
          Text(this.inSetValueOne.toFixed(0)).fontSize(12)
        }
        .width('80%')

        Text('step为10,scrollStep:5').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Row() {
          Slider({
            value: this.inSetValueTwo,
            step: 10,
            style: SliderStyle.InSet
          })
            .accessibilityActionOptions({scrollStep:5})
            .blockColor('#191970')
            .trackColor('#ADD8E6')
            .selectedColor('#4169E1')
            .showSteps(true)
          Text(this.inSetValueTwo.toFixed(0)).fontSize(12)
        }
        .width('80%')

        Text('step为1,scrollStep:20').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Row() {
          Slider({
            value: this.inSetValueTwo,
            step: 1,
            style: SliderStyle.InSet
          })
            .accessibilityActionOptions({scrollStep:20})
            .blockColor('#191970')
            .trackColor('#ADD8E6')
            .selectedColor('#4169E1')
            .showSteps(true)
          Text(this.inSetValueTwo.toFixed(0)).fontSize(12)
        }
        .width('80%')

        Text('none slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(5)
        Text('scrollStep:20').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Row() {
          Slider({
            value: this.noneValueOne,
            min: 0,
            max: 100,
            style: SliderStyle.NONE
          })
            .accessibilityActionOptions({scrollStep:20})
            .blockColor('#191970')
            .trackColor('#ADD8E6')
            .selectedColor('#4169E1')
            .showTips(true)

          Text(this.noneValueOne.toFixed(0)).fontSize(12)
        }
        .width('80%')

        Row() {
          Column() {
            Text('vertical outset slider').fontSize(9).fontColor(0xCCCCCC).width('50%').margin(5)
            Text('1：scrollStep:20；2：step为10，scrollStep:35；3：step为10，scrollStep:5')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('90%')
            Row() {
              Text().width('10%')
              Slider({
                value: this.vOutSetValueOne,
                style: SliderStyle.OutSet,
                direction: Axis.Vertical
              })
                .accessibilityActionOptions({scrollStep:20})
                .blockColor('#191970')
                .trackColor('#ADD8E6')
                .selectedColor('#4169E1')
                .showTips(true)

              Slider({
                value: this.vOutSetValueTwo,
                step: 10,
                style: SliderStyle.OutSet,
                direction: Axis.Vertical
              })
                .accessibilityActionOptions({scrollStep:35})
                .blockColor('#191970')
                .trackColor('#ADD8E6')
                .selectedColor('#4169E1')
                .showSteps(true)

              Slider({
                value: this.vOutSetValueTwo,
                step: 10,
                style: SliderStyle.OutSet,
                direction: Axis.Vertical
              })
                .accessibilityActionOptions({scrollStep:5})
                .blockColor('#191970')
                .trackColor('#ADD8E6')
                .selectedColor('#4169E1')
                .showSteps(true)

            }
          }.width('50%').height(300)

          Column() {
            Text('vertical inset slider').fontSize(9).fontColor(0xCCCCCC).width('50%').margin(5)
            Row() {
              Slider({
                value: this.vInSetValueOne,
                style: SliderStyle.InSet,
                direction: Axis.Vertical,
                reverse: true // 竖向的Slider默认是上端是min值，下端是max值，因此想要从下往上滑动，需要设置reverse为true
              })
                .accessibilityActionOptions({scrollStep:20})
                .showTips(true)

              Slider({
                value: this.vInSetValueTwo,
                step: 10,
                style: SliderStyle.InSet,
                direction: Axis.Vertical,
                reverse: true
              })
                .accessibilityActionOptions({scrollStep:35})
                .showSteps(true)

              Slider({
                value: this.vInSetValueTwo,
                step: 10,
                style: SliderStyle.InSet,
                direction: Axis.Vertical,
                reverse: true
              })
                .accessibilityActionOptions({scrollStep:5})
                .showSteps(true)

            }
          }.width('50%').height(300)
        }
      }.width('100%')
    }
  }
}