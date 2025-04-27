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
struct GaugeLevel0_2 {
  @State value: number = 50;
  @State gaugeSize: number[] = [1, 100];
  @State angles: number[] = [210, 120, 150];
  @State strokeWidth: number = 5;
  @State color2: LinearGradient = new LinearGradient([
    { color: Color.Yellow, offset: 0 },
    { color: Color.Red, offset: 1 }
  ]);
  @State descriptionStr: string = 'AA';
  @State gaugeType1Size: number[] = [128, 80];
  @State gaugeType2Size: number[] = [80, 80];
  @State text: string | undefined = undefined;
  @State showText: boolean = false;
  @State index: number = 0;
  private testCases1: GaugeShadowOptions[] = [
  // 0
    {
      radius: -10,
      offsetX: -30,
      offsetY: -50
    },
    // 1
    {
      radius: 0,
      offsetX: -10,
      offsetY: -10
    },
    // 2
    {
      radius: 5,
      offsetX: 0,
      offsetY: 0
    },
    // 3
    {
      radius: 8.5,
      offsetX: 15.8,
      offsetY: -20.3
    },
    // 4
    {
      radius: 10,
      offsetX: 20,
      offsetY: 20
    },
    // 5
    {
      radius: 15,
      offsetX: -20,
      offsetY: -20
    },
    // 6
    {
      radius: 20,
      offsetX: 40,
      offsetY: 60
    },
    // 7
    {
      radius: 40,
      offsetX: 80
    },
    // 8
    {
      radius: $r('app.float.float_fu20'),
      offsetX: $r('app.float.float_0'),
      offsetY: $r('app.float.float_0')
    },
    // 9
    {
      radius: $r('app.float.float_0'),
      offsetX: $r('app.float.float_fu20'),
      offsetY: $r('app.float.float_fu20')
    },
    // 10
    {
      radius: $r('app.float.float_10'),
      offsetX: $r('app.float.float_30_6'),
      offsetY: $r('app.float.float_30_6')
    },
    // 11
    {
      radius: $r('app.float.float_30_6'),
      offsetX: $r('app.float.float_10'),
      offsetY: $r('app.float.float_10')
    },
    // 12
    {
      radius: $r('app.float.float_20'),
      offsetX: $r('app.float.float_50'),
      offsetY: $r('app.float.float_50')
    },
    // 13
    {
      radius: $r('app.string.app_name'),
      offsetX: $r('app.string.app_name'),
      offsetY: $r('app.string.app_name')
    },
    // 14
    {
      radius: $r('app.color.Red2'),
      offsetX: $r('app.color.Red2'),
      offsetY: $r('app.color.Red2')
    },
    // 15
    {
      radius: $r('app.string.kong'),
      offsetX: $r('app.string.kong'),
      offsetY: $r('app.string.kong')
    },
  ];
  private testCases2: GaugeIndicatorOptions[] = [
    { icon: $r('app.float.float_0'), space: '-10px' },
    { icon: $r('app.string.20fp'), space: '0px' },
    { icon: $r('app.media.app_icon'), space: '20px' },
    { icon: $r('app.media.img'), space: '80px' },
    { icon: $r('app.media.image_animator_2'), space: '800px' },
    { icon: $r('app.media.pen'), space: '-10vp' },
    { icon: $r('app.media.icon_pause'), space: 0 },
    { icon: $r('app.media.icon_play'), space: 20 },
    { icon: $r('app.float.float_0'), space: '30vp' },
    { icon: $r('app.string.20fp'), space: '80vp' },
    { icon: $r('app.media.app_icon'), space: '-10fp' },
    { icon: $r('app.media.img'), space: '0fp' },
    { icon: $r('app.media.image_animator_2'), space: '20fp' },
    { icon: $r('app.media.pen'), space: '30fp' },
    { icon: $r('app.media.icon_pause'), space: '80fp' },
    { icon: $r('app.media.icon_play'), space: '-10lpx' },
  ];
  private testCases3: GaugeIndicatorOptions[] = [
    { icon: $r('app.float.float_0'), space: '0lpx' },
    { icon: $r('app.string.20fp'), space: '20lpx' },
    { icon: $r('app.media.app_icon'), space: '80lpx' },
    { icon: $r('app.media.img'), space: '180lpx' },
    { icon: $r('app.media.image_animator_2'), space: '-10%' },
    { icon: $r('app.media.pen'), space: '50%' },
    { icon: $r('app.media.icon_pause'), space: '80%' },
    { icon: $r('app.media.icon_play'), space: $r('app.float.float_30_6') },
    { icon: $r('app.float.float_0'), space: $r('app.float.float_fu20') },
    { icon: $r('app.string.20fp'), space: $r('app.float.float_0') },
    { icon: $r('app.media.app_icon'), space: $r('app.string.kong') },
    { icon: $r('app.media.img'), space: $r('app.string.app_name') },
    { icon: $r('app.media.image_animator_2'), space: $r('app.string.20') },
    { icon: $r('app.media.pen'), space: $r('app.string.20lpx') },
    { icon: $r('app.media.icon_pause'), space: $r('app.string.20fp') },
    { icon: $r('app.media.icon_play'), space: 30 },
  ];

  build() {
    Column() {
      Text('切换参数').fontSize(9).fontColor(0xCCCCCC).width('100%')
        .onClick(() => {
          this.showText = !this.showText;
        })
      Row({ space: 2 }) {
        Text(`${this.testCases1.length}`).key('Gauge02_cycles')
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
        Text('Gauge组件indicator属性测试[上]')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ top: 5, bottom: 5 })

        Text('Gauge组件trackShadow属性测试[下]')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ top: 5, bottom: 5 })

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
            .colors(Color.Blue)
            .width(this.gaugeType2Size[0])
            .height(this.gaugeType2Size[1])
            .strokeWidth(this.strokeWidth)
            .indicator(null)

            Text('null').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
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
            .endAngle(this.angles[1])
            .colors(Color.Blue)
            .width(this.gaugeType2Size[0])
            .height(this.gaugeType2Size[1])
            .strokeWidth(this.strokeWidth)
            .indicator(undefined)

            Text('undefined').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
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
            .endAngle(this.angles[1])
            .colors(Color.Blue)
            .width(this.gaugeType2Size[0])
            .height(this.gaugeType2Size[1])
            .strokeWidth(this.strokeWidth)

            Text('不设置').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
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
            .endAngle(this.angles[1])
            .colors(Color.Blue)
            .width(this.gaugeType2Size[0])
            .height(this.gaugeType2Size[1])
            .strokeWidth(this.strokeWidth)
            .indicator({ space: undefined })

            Text('space为undefined').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
          }
        }

        Row({ space: 10 }) {
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
          .endAngle(this.angles[2])
          .colors(this.color2)
          .width(150)
          .height(150)
          .strokeWidth(this.strokeWidth)
          .indicator({ space: this.testCases2[this.index].space, icon: this.testCases2[this.index].icon })

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
          .endAngle(this.angles[2])
          .colors(Color.Orange)
          .width(150)
          .height(150)
          .strokeWidth(this.strokeWidth)
          .indicator({ space: this.testCases3[this.index].space, icon: this.testCases3[this.index].icon })
        }
        .margin({ top: 5, bottom: 5 })

        Divider().strokeWidth('1px').margin({ top: 5, bottom: 5 })

        Row({ space: 10 }) {
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
          .endAngle(this.angles[2])
          .colors(Color.Blue)
          .width(150)
          .height(150)
          .strokeWidth(this.strokeWidth)
          .trackShadow({
            radius: this.testCases1[this.index].radius,
            offsetX: this.testCases1[this.index].offsetX,
            offsetY: this.testCases1[this.index].offsetY
          })

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
          .endAngle(this.angles[2])
          .colors(this.color2)
          .width(150)
          .height(150)
          .strokeWidth(this.strokeWidth)
          .trackShadow({
            radius: this.testCases1[this.index].radius,
            offsetX: this.testCases1[this.index].offsetX,
            offsetY: this.testCases1[this.index].offsetY
          })
        }
        .margin({ top: 10, bottom: 5 })

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
            .colors(Color.Blue)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .trackShadow(null)

            Text('null').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
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
            .endAngle(this.angles[1])
            .colors(Color.Blue)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .trackShadow(undefined)

            Text('undefined').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
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
            .colors(this.color2)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)

            Text('不设置').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
          }
        }
        .margin({ bottom: 5 })

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
            .colors(Color.Blue)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .trackShadow({ radius: 20, offsetX: 5, offsetY: 5 })

            Text('设置默认值').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
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
            .colors(Color.Blue)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .trackShadow({ radius: undefined, offsetY: 5 })

            Text('模糊半径为undefined').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
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
            .colors(Color.Blue)
            .width(this.gaugeType1Size[0])
            .height(this.gaugeType1Size[1])
            .strokeWidth(this.strokeWidth)
            .trackShadow({ radius: undefined, offsetX: undefined, offsetY: undefined })

            Text('全部为undefined').fontSize(9).fontColor(0xCCCCCC).height(this.showText ? '1%' : 0)
          }
        }
      }.key('testArea')
    }
    .width('100%')
    .height('100%')
  }
}