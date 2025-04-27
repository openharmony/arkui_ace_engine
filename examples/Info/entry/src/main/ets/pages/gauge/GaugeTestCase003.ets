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

class GaugeColor {
  public color: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]>
    | undefined | null = undefined
}

@Entry
@Component
struct GaugeLevel0_1 {
  @State gaugeType1Size: number[] = [100, 100];
  @State value: number = 50;
  @State gaugeSize: number[] = [1, 100];
  @State strokeWidth: number = 8;
  @State angles: number[] = [210, 120, 150, 200];
  @State descriptionStr: string = 'AA';
  @State color1: LinearGradient = new LinearGradient([
    { color: Color.Yellow, offset: 0 },
    { color: Color.Red, offset: 1 }
  ]);
  private colors: LinearGradient[] = [
    new LinearGradient([
      { color: '#e84026', offset: 0 },
      { color: '#f7ce00', offset: 0.6 },
      { color: '#64bb5c', offset: 1 }
    ]),
    new LinearGradient([{ color: '#b5e0f4', offset: 0 }, { color: '#46b1e3', offset: 1 }]),
    new LinearGradient([{ color: '#c0ece5', offset: 0 }, { color: '#61cfbe', offset: 1 }]),
    new LinearGradient([{ color: '#c1e4be', offset: 0 }, { color: '#64bb5c', offset: 1 }]),
    new LinearGradient([{ color: '#dbefa5', offset: 0 }, { color: '#a5d61d', offset: 1 }]),
    new LinearGradient([{ color: '#fceb99', offset: 0 }, { color: '#f7ce00', offset: 1 }]),
    new LinearGradient([{ color: '#f8c5a6', offset: 0 }, { color: '#ed6f21', offset: 1 }]),
    new LinearGradient([{ color: '#f5b5c2', offset: 0 }, { color: '#e64566', offset: 1 }]),
    new LinearGradient([{ color: '#bbb7fc', offset: 0 }, { color: '#564af7', offset: 1 }]),
    new LinearGradient([{ color: '#deb6fb', offset: 0 }, { color: '#ac49f5', offset: 1 }]),
  ];
  @State text: string | undefined = undefined;
  @State showText: boolean = false;
  @State index: number = 0;
  // c1：ResourceColor，c2：LinearGradient(colorStops: ColorStop[])，c3：Array<[ResourceColor | LinearGradient, number]>
  private testCases1: GaugeColor[] = [
  // 0 c1：Blue
    { color: Color.Blue },
    // 1 c1：number黄
    { color: 0xffa500 },
    // 2 c1：rgb粉
    { color: 'rgb(255, 100, 255)' },
    // 3 c1：string绿
    { color: '#32cd32' },
    // 4 c1：rgba 粉
    { color: 'rgba(255, 100, 255, 0.5)' },
    // 5 c1：Resource 绿
    { color: $r('app.string.Color_green') },
    // 6 c1：异常值aa，使用默认值0xFFE84026
    { color: 'aa' },
    // 7 c1：负数-999.33
    { color: -999.33 },
    // 8 c1：空字符串
    { color: '' },
    // 9 c3：空数组
    { color: [] },
    // 10 c3：多于9段，分段渐变环最大显示段数为9段，若多于9段，则多于部分不显示
    {
      color: [
        [Color.Grey, 9],
        [0xffa500, 8],
        [$r('app.color.Red2'), 7],
        ['rgb(255, 100, 255)', 6],
        ['#FFFF00', 5],
        [this.colors[4], 4],
        [this.colors[3], 3],
        [this.colors[2], 2],
        [this.colors[1], 1],
        [this.colors[9], 9],
        [this.colors[8], 8],
        [this.colors[7], 7]
      ]
    },
    // 11 c3：比重有负数
    {
      color: [
        [Color.Grey, 9],
        [0xffa500, -8],
        [$r('app.color.Red2'), 7],
        ['rgb(255, 100, 255)', 0],
        ['#FFFF00', 5],
        [this.colors[4], 40]
      ]
    },
    // 12 c2：Color绿
    { color: new LinearGradient([{ color: Color.Green, offset: 0 }]) },
    // 13 c2：string黄
    { color: new LinearGradient([{ color: '#FFFF00', offset: -0.8 }]) },
  ];
  private testCases2: GaugeColor[] = [
  // 0 c2：number橘
    { color: new LinearGradient([{ color: 0xffa500, offset: 0.5 }]) },
    // 1 c2：Resource绿
    { color: new LinearGradient([{ color: $r('app.string.Color_green'), offset: 1.5 }]) },
    // 2 c2：异常值aa
    { color: new LinearGradient([{ color: 'aa', offset: 0.5 }]) },
    // 3 c2：断点非法值
    { color: new LinearGradient([{ color: Color.Green, offset: 'aa' }]) },
    // 4 c2:：空
    { color: new LinearGradient([{ color: '', offset: 0.5 }]) },
    // 5 c2：渐变0~1
    {
      color: new LinearGradient([
        { color: 0xFFFF0000, offset: 0 },
        { color: Color.Blue, offset: 1 }])
    },
    // 6 c2：渐变1~0
    {
      color: new LinearGradient([
        { color: 0xFFFF0000, offset: $r('app.float.float_1') },
        { color: Color.Blue, offset: $r('app.float.float_0') }])
    },
    // 7 c2：渐变0~0.5~1
    {
      color: new LinearGradient([
        { color: 'rgb(255, 100, 255)', offset: 0 },
        { color: $r('app.color.Red2'), offset: '0.5' },
        { color: '#FFeeaa', offset: 1 }])
    },
    // 8 c2：-3~0.5~2
    {
      color: new LinearGradient([
        { color: Color.Orange, offset: -3 },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 2 }])
    },
    // 9 c2：0.3~0.5~2000
    {
      color: new LinearGradient([
        { color: Color.Orange, offset: 0.3 },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 2000 }])
    },
    // 10 c2：0.3~0.5~0.8
    {
      color: new LinearGradient([
        { color: Color.Orange, offset: $r('app.float.float_03') },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 0.8 }])
    },
    // 11 c2：0.5~0.5~0.8
    {
      color: new LinearGradient([
        { color: Color.Orange, offset: 0.5 },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 0.8 }])
    },
    // 12 c2：0.5~0.3~0.8
    {
      color: new LinearGradient([
        { color: Color.Orange, offset: 0.5 },
        { color: Color.Green, offset: 0.3 },
        { color: Color.Red, offset: 0.8 }])
    },
    // 13 c2：0~0.8~0.5
    {
      color: new LinearGradient([
        { color: Color.Orange, offset: 0 },
        { color: Color.Green, offset: 0.8 },
        { color: Color.Red, offset: 0.5 }])
    }
  ];

  @Builder
  DescriptionBuilder() {
    Text(this.descriptionStr)
      .fontColor('#fffa2a2d')
      .width('100%')
      .height('200')
      .textAlign(TextAlign.Start)
      .align(Alignment.TopStart)
      .borderWidth(2)
  }

  build() {
    Column() {
      Text('Gauge组件colors属性测试[第1行Gauge]').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
      Text('Gauge组件description属性测试[第2-4行Gauge]')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ top: 5, bottom: 5 })
      Text('切换参数').fontSize(9).fontColor(0xCCCCCC).width('100%')
        .onClick(() => {
          this.showText = !this.showText;
        })
      Row({ space: 2 }) {
        Text(`${this.testCases2.length}`).key('Gauge01_cycles')
        Text('Test++')
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .onClick(() => {
            this.text = `index = ${this.index}`;
            this.index++;
            if (this.index == this.testCases1.length) {
              this.index = 0;
            }
          })
        Text('Test--')
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .onClick(() => {
            this.index--;
            if (this.index == -1) {
              this.index = this.testCases1.length - 1;
            }
            this.text = `index = ${this.index}`;
          })
      }

      if (this.showText) {
        Text(this.text)
      }


      Column() {
        Row({ space: 2 }) {
          Gauge({ value: this.value, min: this.gaugeSize[0], max: this.gaugeSize[1] })
            .width(150)
            .height(150)
            .strokeWidth(15)
            .startAngle(this.angles[0])
            .endAngle(this.angles[2])
            .colors(this.testCases1[this.index].color)
            .margin({ right: 20 })
          Gauge({ value: 80, min: this.gaugeSize[0], max: this.gaugeSize[1] })
            .width(150)
            .height(150)
            .strokeWidth(15)
            .startAngle(this.angles[0])
            .endAngle(this.angles[2])
            .colors(this.testCases2[this.index].color)
        }

        Divider().strokeWidth('1px').margin({ top: 5, bottom: 5 })

        Row({ space: 10 }) {
          Column() {
            Gauge({ value: this.value, min: this.gaugeSize[0], max: this.gaugeSize[1] }) {
              Text(this.descriptionStr)
                .fontWeight(FontWeight.Medium)
                .width('62%')
                .height('44.4%')
                .textAlign(TextAlign.Center)
                .maxFontSize('80sp')
                .minFontSize('60.0vp')
                .margin({ top: '22.2%', left: '19%' })
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .maxLines(1)
            }
            .startAngle(this.angles[0])
            .endAngle(this.angles[1])
            .colors(this.color1)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .description(null)

            Text('null').fontSize(9).fontColor(0xCCCCCC).margin({ top: 5 }).height(this.showText ? '1%' : 0)
          }

          Column() {
            Gauge({ value: this.value, min: this.gaugeSize[0], max: this.gaugeSize[1] }) {
              Text(this.descriptionStr)
                .fontWeight(FontWeight.Medium)
                .width('62%')
                .height('44.4%')
                .textAlign(TextAlign.Center)
                .maxFontSize('80sp')
                .minFontSize('60.0vp')
                .margin({ top: '22.2%', left: '19%' })
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .maxLines(1)
            }
            .startAngle(this.angles[0])
            .endAngle(this.angles[3])
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .description(undefined)

            Text('undefined').fontSize(9).fontColor(0xCCCCCC).margin({ top: 5 }).height(this.showText ? '1%' : 0)
          }

          Column() {
            Gauge({ value: this.value, max: this.gaugeSize[1] }) {
              Text(this.descriptionStr)
                .fontWeight(FontWeight.Medium)
                .width('62%')
                .height('44.4%')
                .textAlign(TextAlign.Center)
                .maxFontSize('80sp')
                .minFontSize('60.0vp')
                .margin({ top: '22.2%', left: '19%' })
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .maxLines(1)
            }
            .startAngle(this.angles[0])
            .endAngle(this.angles[1])
            .colors(this.color1)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)

            Text('不设置，只设置最大值')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .margin({ top: 5 })
              .height(this.showText ? '1%' : 0)
          }
        }

        Row({ space: 10 }) {
          Column() {
            Gauge({ value: this.value, min: this.gaugeSize[0] }) {
              Text(this.descriptionStr)
                .fontWeight(FontWeight.Medium)
                .width('62%')
                .height('44.4%')
                .textAlign(TextAlign.Center)
                .maxFontSize('80sp')
                .minFontSize('60.0vp')
                .margin({ top: '22.2%', left: '19%' })
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .maxLines(1)
            }
            .startAngle(this.angles[0])
            .endAngle(this.angles[1])
            .colors(this.color1)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .description(undefined)

            Text('undefined，只设置最小值')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .margin({ top: 5 })
              .height(this.showText ? '1%' : 0)
          }

          Column() {
            Gauge({ value: this.value, min: this.gaugeSize[0] }) {
              Text(this.descriptionStr)
                .fontWeight(FontWeight.Medium)
                .width('62%')
                .height('44.4%')
                .textAlign(TextAlign.Center)
                .maxFontSize('80sp')
                .minFontSize('60.0vp')
                .margin({ top: '22.2%', left: '19%' })
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .maxLines(1)
            }
            .startAngle(this.angles[0])
            .endAngle(this.angles[1])
            .colors(this.color1)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)

            Text('不设置，只设置最小值')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .margin({ top: 5 })
              .height(this.showText ? '1%' : 0)
          }

          Column() {
            Gauge({ value: this.value }) {
              Text(this.descriptionStr)
                .fontWeight(FontWeight.Medium)
                .width('62%')
                .height('44.4%')
                .textAlign(TextAlign.Center)
                .maxFontSize('80sp')
                .minFontSize('60.0vp')
                .margin({ top: '22.2%', left: '19%' })
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .maxLines(1)
            }
            .startAngle(this.angles[0])
            .endAngle(this.angles[1])
            .colors(this.color1)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)

            Text('不设置，也不设置最大小值')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .margin({ top: 5 })
              .height(this.showText ? '1%' : 0)
          }
        }
        .margin({ top: 5, bottom: 10 })

        Gauge({ value: this.value, min: this.gaugeSize[0], max: this.gaugeSize[1] }) {
          Text(this.descriptionStr)
            .fontWeight(FontWeight.Medium)
            .width('62%')
            .height('44.4%')
            .textAlign(TextAlign.Center)
            .maxFontSize('80sp')
            .minFontSize('60.0vp')
            .margin({ top: '22.2%', left: '19%' })
            .textOverflow({ overflow: TextOverflow.Ellipsis })
        }
        .startAngle(150)
        .endAngle(this.angles[1])
        .colors(this.color1)
        .width(150)
        .height(150)
        .strokeWidth(this.strokeWidth)
        .description(this.DescriptionBuilder)

        Text('设置最大小值')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .margin({ top: 5 })
          .height(this.showText ? '1%' : 0)
      }.key('testArea')

      Text('修改str值').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ bottom: 5 })
      Row({ space: 2 }) {
        Button('-10px').onClick((event: ClickEvent) => {
          this.descriptionStr = '-10px';
        })
          .width('18%')
          .height(30)
        Button('+0px').onClick((event: ClickEvent) => {
          this.descriptionStr = this.descriptionStr + '0px';
        })
          .width('18%')
          .height(30)
        Button('+测试').onClick((event: ClickEvent) => {
          this.descriptionStr = this.descriptionStr + '测试';
        })
          .width('18%')
          .height(30)
        Button('80px').onClick((event: ClickEvent) => {
          this.descriptionStr = '80px';
        })
          .width('18%')
          .height(30)
        Button('80000px').onClick((event: ClickEvent) => {
          this.descriptionStr = '80000px';
        })
          .width('25%')
          .height(30)
      }
    }
    .width('100%')
    .height('100%')
  }
}