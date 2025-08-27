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

@Builder
export function SliderBlockStyleBuilder(name: string, param: Object) {
  SliderBlockStyleExample()
}

@Entry
@Component
struct SliderBlockStyleExample {
  pathStack: NavPathStack = new NavPathStack()
  @State tipsValue: number = 40;

  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Text('block')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .margin(15)
          .width('90%')
        Slider({ style: SliderStyle.OutSet, value: 40 })
          .blockSize({ width: 40, height: 40 })
          .blockBorderColor(Color.Red)
          .blockBorderWidth(5)
        Divider()
        Text('step')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .margin(15)
          .width('90%')
        Slider({ style: SliderStyle.InSet, value: 40, step: 10 })
          .showSteps(true)
          .stepSize(8)
          .stepColor(Color.Yellow)
        Divider()
        Text('track')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .margin(15)
          .width('90%')
        Slider({ style: SliderStyle.InSet, value: 40 })
          .trackBorderRadius(2)
        Divider()
        Text('selected')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .margin(15)
          .width('90%')
        Slider({ style: SliderStyle.InSet, value: 40 })
          .selectedBorderRadius(2)
        Divider()
        Text('blockStyle')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .margin(15)
          .width('90%')
        Slider({ style: SliderStyle.OutSet, value: 40 })
          .blockStyle({ type: SliderBlockType.DEFAULT })
        Slider({ style: SliderStyle.OutSet, value: 40 })
          .blockStyle({ type: SliderBlockType.IMAGE, image: $r('sys.media.ohos_app_icon') })
        Slider({ style: SliderStyle.OutSet, value: 40 })
          .blockSize({ width: '60px', height: '60px' })
          .blockColor(Color.Red)
          .blockStyle({ type: SliderBlockType.SHAPE, shape: new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) })
        Divider()
        Text('tips')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .margin(15)
          .width('90%')
        Slider({ style: SliderStyle.InSet, value: this.tipsValue })
          .showTips(true, this.tipsValue.toFixed())
          .onChange(value => {
            this.tipsValue = value;
          })
      }
    }
    .title('SliderBlockStyle')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}