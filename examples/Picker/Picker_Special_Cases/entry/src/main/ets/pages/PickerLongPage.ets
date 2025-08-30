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

import { LengthMetrics } from '@kit.ArkUI'

@Entry
@Component
struct TextPickerLong {
  scroller: Scroller = new Scroller()
  private select: number = 1
  private fruits1: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private fruits2: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private fruits3: string[] = ['peach1', 'peach2', 'peach3', 'peach4']
  private multi: string[][] = [this.fruits1, this.fruits2, this.fruits3]
  @State isEnabled: boolean = true;
  private cascade: TextCascadePickerRangeContent[] = [
    {
      text: '广东省',
      children: [
        { text: '广州市', children: [{ text: '天河区' }, { text: '越秀区' }, { text: '海珠区' }] },
        { text: '深圳市', children: [{ text: '南山区' }, { text: '福田区' }, { text: '罗湖区' }] },
        { text: '珠海市', children: [{ text: '香洲区' }, { text: '斗门区' }, { text: '金湾区' }] }
      ]
    },
    {
      text: '江苏省',
      children: [
        { text: '南京市', children: [{ text: '玄武区' }, { text: '秦淮区' }, { text: '鼓楼区' }] },
        { text: '苏州市', children: [{ text: '姑苏区' }, { text: '吴中区' }, { text: '相城区' }] },
        { text: '无锡市', children: [{ text: '梁溪区' }, { text: '锡山区' }, { text: '惠山区' }] }
      ]
    },
    {
      text: '四川省',
      children: [
        { text: '成都市', children: [{ text: '锦江区' }, { text: '青羊区' }, { text: '武侯区' }] },
        { text: '绵阳市', children: [{ text: '涪城区' }, { text: '游仙区' }, { text: '安州区' }] },
        { text: '德阳市', children: [{ text: '旌阳区' }, { text: '罗江区' }, { text: '广汉市' }] }
      ]
    }
  ];
  private singleColumnWidths: LengthMetrics[] = [
    LengthMetrics.percent(50)
  ];
  private multipleColumnWidths: LengthMetrics[] = [
    LengthMetrics.vp(100),
    LengthMetrics.vp(200),
    LengthMetrics.vp(100)
  ];
  private cascadeColumnWidths: LengthMetrics[] = [
    LengthMetrics.percent(20),
    LengthMetrics.percent(30),
    LengthMetrics.percent(50)
  ];

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('基础 TextPicker')
          .fontSize(30)
          .backgroundColor(Color.Pink)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        TextPicker({ range: this.cascade, selected: this.select })
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('Picker item changed, value: ' + value + ', index: ' + index)
          })
          .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
          .textStyle({ color: Color.Black, font: { size: 20, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Red, font: { size: 30, weight: FontWeight.Bolder } })
          .width(300)
          .canLoop(false)

        TextPicker({ range: this.fruits1, selected: this.select })
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('Picker item changed, value: ' + value + ', index: ' + index)
          }).margin(5).width(50)

        TextPicker({ range: this.multi })
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('TextPicker 多列:onChange ' + JSON.stringify(value) + ', ' + 'index: ' + JSON.stringify(index))
          }).margin(5)

        TextPicker({ range: this.cascade, selected: this.select, columnWidths: this.cascadeColumnWidths })
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('Picker item changed, value: ' + value + ', index: ' + index)
          })
          .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
          .textStyle({ color: Color.Black, font: { size: 20, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Red, font: { size: 30, weight: FontWeight.Bolder } })
          .width(300)
          .canLoop(false)


        TextPicker({ range: this.cascade, selected: this.select })
          .onChange((value: string | string[], index: number | number[]) => {
            console.info('Picker item changed, value: ' + value + ', index: ' + index)
          })
          .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
          .textStyle({ color: Color.Black, font: { size: 20, weight: FontWeight.Normal } })
          .selectedTextStyle({ color: Color.Red, font: { size: 30, weight: FontWeight.Bolder } })
          .width(300)
          .canLoop(false)

      }
      .backgroundColor('#90EE90')
      .width('100%')
      .height('300%')
    }
    .scrollable(ScrollDirection.Vertical)
    .scrollBar(BarState.On)
    .scrollBarColor(Color.Gray)
    .scrollBarWidth(3)
    .friction(0.6)
    .edgeEffect(EdgeEffect.Fade)
    .backgroundColor('#90EE90')
  }
}
