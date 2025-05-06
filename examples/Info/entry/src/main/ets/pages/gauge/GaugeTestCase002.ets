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

class Model {
  public value: number | undefined | null = 0
  public startAngle: number | undefined | null = 0
  public endAngle: number | undefined | null = 360
  public strokeWidth: Length | undefined | null = 4
  public colors: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]> | undefined | null =
    new LinearGradient([
      { color: 0xFF64BB5C, offset: 0 },
      { color: 0xFFF7CE00, offset: 0.5 },
      { color: 0xFFF7CE00, offset: 1 }
    ])
  public descriptionStr: string | undefined | null = ''
  public trackShadow: GaugeShadowOptions | undefined | null = {}
  public indicator: GaugeIndicatorOptions | undefined | null = {}
}

class Model2 {
  public colors: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]> | undefined | null =
    new LinearGradient([
      { color: 0xFF64BB5C, offset: 0 },
      { color: 0xFFF7CE00, offset: 0.5 },
      { color: 0xFFF7CE00, offset: 1 }
    ])
  public indicator: GaugeIndicatorOptions | undefined | null = {}
  public strokeWidth: Length | undefined | null = 4
}

@Entry
@Component
struct GaugeLevel0_0 {
  @State value1: number | undefined = undefined;
  @State min: number | undefined = undefined;
  @State max: number | undefined = undefined;
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
  @State index1: number = 0;
  // c1：ResourceColor，c2：LinearGradient(colorStops: ColorStop[])，c3：Array<[ResourceColor | LinearGradient, number]>
  private testCases1: Model[] = [
  // 0
    {
      value: -16.8,
      startAngle: 0,
      endAngle: 240,
      colors: [], // c3：空数组
      strokeWidth: 18,
      descriptionStr: '$#@$^&^gvgfc测试',
      trackShadow: {
        radius: -10,
        offsetX: -30,
        offsetY: -50
      },
      indicator: { icon: $r('app.float.float_0'), space: '-10px' }
    },
    // 1
    {
      value: -20,
      startAngle: 0,
      endAngle: 300,
      colors: [
        [Color.Pink, 0.1],
        [0x5BA854, 0.2],
        ['#ffff00', 0.3],
        ['rgb(255,0,255)', 0.4],
        [$r('sys.color.ohos_id_color_warning'), 0.1],
        ['rgba(0, 255, 255, 0.5)', 0.2]
      ], // c3：正常值,
      strokeWidth: 60, // 超过组件宽度的一半
      descriptionStr: 'AA',
      trackShadow: {
        radius: $r('app.string.kong'),
        offsetX: $r('app.string.kong'),
        offsetY: $r('app.string.kong')
      },
      indicator: { icon: $r('app.media.pen'), space: $r('app.string.app_name') },
    },
    // 2
    {
      value: 15.5,
      startAngle: -30,
      endAngle: 360,
      colors: [
        [Color.Grey, 9],
        [0xffa500, 8],
        [$r('app.color.Red2'), 7],
        ['rgb(255, 100, 255)', 6],
        ['#FFFF00', 5],
        ['zzz', 0.3],
        [this.colors[4], 4],
        [this.colors[3], 3],
        [this.colors[2], 2],
        [this.colors[1], 1],
        [this.colors[9], 9],
        [this.colors[8], 8],
        [this.colors[7], 7]
      ], // c3：分段渐变环最大显示段数为9段，若多于9段，则多于部分不显示；颜色异常值取默认值0xFFE84026
      strokeWidth: '180', // 超过组件宽度，箭头可见，圆环不可见
      descriptionStr: '-10px',
      trackShadow: {
        radius: 0,
        offsetX: -10,
        offsetY: -10
      },
      indicator: { icon: $r('app.string.20fp'), space: '0px' }
    },
    // 3
    {
      value: 20,
      startAngle: 15,
      endAngle: 330,
      colors: [
        [Color.Grey, 9],
        [0xffa500, -8],
        [$r('app.color.Red2'), 7],
        ['rgb(255, 100, 255)', 0],
        [$r('app.string.module_desc'), 0.4],
        ['#FFFF00', 5],
        [this.colors[4], 40]
      ], // c3：比重若设置为负数或是非数值类型，则将比重置为0，颜色异常值走默认值0xFFE84026
      strokeWidth: $r('app.string.250vp'), // 超过组件宽度两倍，箭头圆环都不可见
      descriptionStr: '-10px0px0px0px0px0px0px0px0px0px0px0px0px0px0px0px0px0px0px',
      trackShadow: {
        radius: 5,
        offsetX: 0,
        offsetY: 0
      },
      indicator: { icon: $r('app.media.app_icon'), space: '20px' }
    },
    // 4
    {
      value: 25.4,
      startAngle: 30, // 两个数相等
      endAngle: 30,
      colors: '', // c1：空字符串
      strokeWidth: -1, // 取默认值4vp
      descriptionStr: 'AA测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试',
      trackShadow: {
        radius: 8.5,
        offsetX: 15.8,
        offsetY: -20.3
      },
      indicator: { icon: $r('app.media.pen'), space: '80px' }
    },
    // 5
    {
      value: 30,
      startAngle: 150,
      endAngle: 0,
      colors: Color.Blue, // c1：Blue
      strokeWidth: 'zzz', // 异常值，取默认值4vp
      descriptionStr: '80px',
      trackShadow: {
        radius: 10,
        offsetX: 20,
        offsetY: 20
      },
      indicator: { icon: $r('app.media.img'), space: '800px' }
    },
    // 6
    {
      value: 50,
      startAngle: 30.5,
      endAngle: 210,
      colors: 0xffa500, // c1：number黄
      strokeWidth: $r('app.string.module_desc'), // 异常值，取默认值4vp
      descriptionStr: '80000px',
      trackShadow: {
        radius: 15,
        offsetX: -20,
        offsetY: -20
      },
      indicator: { icon: $r('app.media.lock'), space: '-10vp' }
    },
    // 7
    {
      value: 80,
      startAngle: 210,
      endAngle: 150,
      colors: 'rgb(255, 100, 255)', // c1：rgb粉
      strokeWidth: 0, // 预期为默认值4vp
      descriptionStr: '-10px测试0px测试0px测试测试0px0px测试0px测试',
      trackShadow: {
        radius: 20,
        offsetX: 40,
        offsetY: 60
      },
      indicator: { icon: $r('app.media.ic_public_save'), space: 0 }
    },
    // 8
    {
      value: 0,
      startAngle: -15.5,
      endAngle: 270,
      colors: '#32cd32', // c1：string绿
      strokeWidth: '20abc', // 预期为默认值4vp
      descriptionStr: 'bir koruxum bilanla sini yahturup kaldim wesalingga yatmay turup dart alamda man',
      trackShadow: {
        radius: 40,
        offsetX: 80
      },
      indicator: { icon: $r('app.media.icon_play'), space: 20 }
    },
    // 9
    {
      value: 100,
      startAngle: 600,
      endAngle: 120,
      colors: 'rgba(255, 100, 255, 0.5)', // c1：rgba 粉
      strokeWidth: '30%', // 预期为默认值4vp
      descriptionStr: null,
      trackShadow: {
        radius: $r('app.float.float_fu20'),
        offsetX: $r('app.float.float_0'),
        offsetY: $r('app.float.float_0')
      },
      indicator: { icon: $r('app.float.float_0'), space: '30vp' }
    },
    // 10
    {
      value: 50,
      startAngle: 30,
      endAngle: 210,
      colors: $r('app.string.Color_green'), // c1：Resource 绿
      strokeWidth: '10vp',
      descriptionStr: null,
      trackShadow: {
        radius: $r('app.float.float_0'),
        offsetX: $r('app.float.float_fu20'),
        offsetY: $r('app.float.float_fu20')
      },
      indicator: { icon: $r('app.string.20fp'), space: '80vp' }
    },
    // 11
    {
      value: 60,
      startAngle: 0,
      endAngle: 240,
      colors: 'aa', // c1：异常值aa，使用默认值0xFFE84026
      strokeWidth: '10px',
      descriptionStr: null,
      trackShadow: {
        radius: $r('app.float.float_10'),
        offsetX: $r('app.float.float_30_6'),
        offsetY: $r('app.float.float_30_6')
      },
      indicator: { icon: $r('app.media.app_icon'), space: '-10fp' }
    },
    // 12
    {
      value: 80,
      startAngle: 20,
      endAngle: 320,
      colors: -999.33, // c1：负数-999.33
      strokeWidth: '0px', // 预期为默认值4vp
      descriptionStr: null,
      trackShadow: {
        radius: $r('app.float.float_30_6'),
        offsetX: $r('app.float.float_10'),
        offsetY: $r('app.float.float_10')
      },
      indicator: { icon: $r('app.media.wifi'), space: '0fp' }
    },
    // 13
    {
      value: 66,
      startAngle: 0,
      endAngle: 320,
      colors: 999.33, // c1：正999.33
      strokeWidth: '-10px', // 预期为默认值4vp
      descriptionStr: null,
      trackShadow: {
        radius: $r('app.color.Red2'),
        offsetX: $r('app.color.Red2'),
        offsetY: $r('app.color.Red2')
      },
      indicator: { icon: $r('app.media.img'), space: $r('app.string.20') }
    },
    // 14
    {
      value: undefined, // 0
      startAngle: undefined, // 取默认值0
      endAngle: undefined, // 取默认值360
      colors: undefined, // 默认值'0xFF64BB5C'、'0xFFF7CE00'、'0xFFE84026'的渐变环
      strokeWidth: undefined, // 取默认值4vp
      descriptionStr: undefined,
      trackShadow: undefined, // 取默认值 { radius: 20, offsetX: 5, offsetY: 5 }
      indicator: undefined // 默认的三角形样式指针，space为8vp
    },
    // 15
    {
      value: -60,
      startAngle: -240,
      endAngle: 30,
      colors: new LinearGradient([{ color: Color.Green, offset: 0 }]), // c2：Color绿
      strokeWidth: '-10fp', // 预期为默认值4vp
      descriptionStr: null,
      trackShadow: {
        radius: $r('app.float.float_20'),
        offsetX: $r('app.float.float_50'),
        offsetY: $r('app.float.float_50')
      },
      indicator: { icon: $r('app.media.pen'), space: '20fp' }
    },
    // 16
    {
      value: null,
      startAngle: null,
      endAngle: null,
      colors: new LinearGradient([{ color: '#FFFF00', offset: -0.8 }]), // c2：string黄
      strokeWidth: null,
      descriptionStr: null,
      trackShadow: null,
      indicator: { icon: $r('app.media.icon_pause'), space: '30fp' }
    }
  ];
  private testCases2: Model2[] = [
  // 0
    {
      colors: new LinearGradient([{ color: 0xffa500, offset: 0.5 }]), // number橘
      indicator: { icon: $r('app.media.icon_play'), space: '80fp' },
      strokeWidth: '0fp'
    },
    // 1
    {
      colors: new LinearGradient([{ color: $r('app.string.Color_green'), offset: 1.5 }]), // Resource绿
      indicator: { icon: $r('app.float.float_0'), space: '0lpx' },
      strokeWidth: '10fp'
    },
    // 2
    {
      colors: new LinearGradient([{ color: 'aa', offset: 0.5 }]), // 异常值aa
      indicator: { icon: $r('app.float.float_0'), space: '20lpx' },
      strokeWidth: '20fp'
    },
    // 3
    {
      colors: new LinearGradient([{ color: Color.Green, offset: 'aa' }]), // 断点非法值
      indicator: { icon: $r('app.media.icon_pause'), space: '-10lpx' },
      strokeWidth: '-10lpx'
    },
    // 4
    {
      colors: new LinearGradient([{ color: '', offset: 0.5 }]), // 空
      indicator: { icon: $r('app.media.app_icon'), space: '80lpx' },
      strokeWidth: '0lpx'
    },
    // 5
    {
      colors: new LinearGradient([
        { color: 0xFFFF0000, offset: 0 },
        { color: Color.Blue, offset: 1 }]), // 渐变0~1
      indicator: { icon: $r('app.media.app_icon'), space: '80lpx' },
      strokeWidth: '20lpx'
    },
    // 6
    {
      colors: new LinearGradient([
        { color: 0xFFFF0000, offset: $r('app.float.float_1') },
        { color: Color.Blue, offset: $r('app.float.float_0') }]), // 渐变1~0
      indicator: { icon: $r('app.media.img'), space: '180lpx' },
      strokeWidth: $r('app.float.float_30_6')
    },
    // 7
    {
      colors: new LinearGradient([
        { color: 'rgb(255, 100, 255)', offset: 0 },
        { color: $r('app.color.Red2'), offset: '0.5' },
        { color: '#FFeeaa', offset: 1 }]), // 渐变0~0.5~1
      indicator: { icon: $r('app.media.image_animator_1'), space: '-10%' },
      strokeWidth: $r('app.float.float_fu20')
    },
    // 8
    {
      colors: new LinearGradient([
        { color: Color.Orange, offset: -3 },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 2 }]), // -3~0.5~2
      indicator: { icon: $r('app.media.ic_public_back'), space: 30 },
      strokeWidth: $r('app.float.float_0')
    },
    // 9
    {
      colors: new LinearGradient([
        { color: Color.Orange, offset: 0.3 },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 2000 }]), // 0.3~0.5~2000
      indicator: { icon: $r('app.media.ic_public_ring'), space: '50%' },
      strokeWidth: $r('app.string.kong')
    },
    // 10
    {
      colors: new LinearGradient([
        { color: Color.Orange, offset: $r('app.float.float_03') },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 0.8 }]), // 0.3~0.5~0.8
      indicator: { icon: $r('app.media.image_animator_4'), space: $r('app.float.float_30_6') },
      strokeWidth: $r('app.string.app_name')
    },
    // 11
    {
      colors: new LinearGradient([
        { color: Color.Orange, offset: 0.5 },
        { color: Color.Green, offset: 0.5 },
        { color: Color.Red, offset: 0.8 }]), // 0.5~0.5~0.8
      indicator: { icon: $r('app.float.float_0'), space: $r('app.float.float_fu20') },
      strokeWidth: $r('app.string.20')
    },
    // 12
    {
      colors: new LinearGradient([
        { color: Color.Orange, offset: 0.5 },
        { color: Color.Green, offset: 0.3 },
        { color: Color.Red, offset: 0.8 }]), // 0.5~0.3~0.8
      indicator: { icon: $r('app.string.20fp'), space: $r('app.float.float_0') },
      strokeWidth: $r('app.string.20lpx')
    },
    // 13
    {
      colors: new LinearGradient([
        { color: Color.Orange, offset: 0 },
        { color: Color.Green, offset: 0.8 },
        { color: Color.Red, offset: 0.5 }]), // 0~0.8~0.5
      indicator: { icon: $r('app.media.app_icon'), space: $r('app.string.kong') },
      strokeWidth: $r('app.string.20fp')
    },
    // 14
    {
      colors: new LinearGradient([
        { color: Color.Pink, offset: 0.5 },
        { color: $r('app.string.Color_green'), offset: 0.3 },
        { color: '#9400D3', offset: 0.8 }]), // 0.2~0.4~0.6
      indicator: { icon: $r('app.media.ic_public_help'), space: $r('app.string.20lpx') },
      strokeWidth: '80lpx'
    },
    // 15
    {
      colors: new LinearGradient([
        { color: Color.Orange, offset: 0 },
        { color: $r('app.string.Color_green'), offset: 0.8 },
        { color: '#9400D3', offset: 0.5 }]), // 0.9~0.7~0.5
      indicator: { icon: $r('app.media.ic_cancel'), space: $r('app.string.20fp') },
      strokeWidth: '-20%'
    },
    // 16
    {
      colors: null,
      indicator: null,
      strokeWidth: null
    },
  ];

  @Builder
  DescriptionBuilder() {
    Text(this.testCases1[this.index1].descriptionStr)
      .fontColor('#fffa2a2d')
      .width('100%')
      .height('200')
      .textAlign(TextAlign.Start)
      .align(Alignment.TopStart)
      .borderWidth(2)
  }

  build() {
    Scroll() {
      Column({ space: 5 }) {
        Text('Gauge接口测试').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 5 })
        Row({ space: 2 }) {
          Gauge({ value: 30 }).width(50).height(50)
          Gauge({ value: 30, min: 20, max: 40 }).width(50).height(50)
          Gauge({ value: 30, min: -50, max: 50 }).width(50).height(50)
          Gauge({ value: 30, min: 50, max: 100 }).width(50).height(50)
          Gauge({ value: 30, min: 50, max: 0 }).width(50).height(50)
          Gauge({ value: this.value1, min: this.min, max: this.max }).width(50).height(50)
        }

        Text('动态修改').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 2 }) {
          Text('正常值')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.value1 = 10;
              this.min = 0;
              this.max = 50;
            })
          Text('undefined')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.value1 = undefined;
              this.min = undefined;
              this.max = undefined;
            })
        }

        Divider().strokeWidth('1px').margin({ top: 5 })

        Text('Gauge属性测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 10 }) {
          Column() {
            Gauge({ value: 30, min: 1, max: 100 })
              .width(140)
              .height(140)
              .margin({ right: 20 })
              .value(this.testCases1[this.index1].value)
              .startAngle(this.testCases1[this.index1].startAngle)
              .endAngle(this.testCases1[this.index1].endAngle)
              .colors(this.testCases2[this.index1].colors)
              .strokeWidth(this.testCases1[this.index1].strokeWidth)
              .description(this.DescriptionBuilder())
              .trackShadow(this.testCases1[this.index1].trackShadow)
              .indicator(this.testCases1[this.index1].indicator)
          }

          Column() {
            Gauge({ value: 30 })
              .width(150)
              .height(150)
              .colors(this.testCases1[this.index1].colors)
              .strokeWidth(this.testCases2[this.index1].strokeWidth)
              .description(this.DescriptionBuilder())
              .trackShadow(this.testCases1[this.index1].trackShadow)
              .indicator(this.testCases2[this.index1].indicator)
          }
        }

        Text('切换参数').fontSize(9).fontColor(0xCCCCCC).width('100%')
          .onClick(() => {
            this.showText = !this.showText
          })
        Row({ space: 2 }) {
          Text(`${this.testCases1.length}`).key('Gauge00_cycles')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              // 控制循环
              this.index1++;
              if (this.index1 == this.testCases1.length) {
                this.index1 = 0;
              }
              this.text = 'index1 = ' + this.index1;
            })
          Text('Test--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              // 控制循环
              this.index1--;
              if (this.index1 == -1) {
                this.index1 = this.testCases1.length - 1;
              }
              this.text = 'index1 = ' + this.index1;
            })
        }

        if (this.showText) {
          Text(this.text)
        }
        Divider().strokeWidth('1px').margin({ top: 5 })

        Text('Gauge布局相关通用属性组合').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 2 }) {
          Row() {
            Gauge({ value: 30 })
              .margin(5)
              .padding(5)
              .strokeWidth(20)
              .colors([[0x317AF7, 0.1], [0x5BA854, 0.2], [0xE08C3A, 0.3], [0x9C554B, 0.4]])
              .borderWidth(1)
          }.width(100).height(100).borderWidth(1)

          Gauge({ value: 30 }).width('20%').borderWidth(1)

          Stack() {
            Gauge({ value: 30 }).width(40).borderWidth(1)
          }.width(100).height(70).backgroundColor(0xFFE4C4).align(Alignment.TopStart)

          Row() {
            Gauge({ value: 30 }).width(70).height(50)
          }.width(50).height(50).borderWidth(1).clip(true)
        }

        Row() {
          Gauge({ value: 30 }).borderWidth(1).layoutWeight(2)
          Gauge({ value: 30 }).borderWidth(1).layoutWeight(3)
          Gauge({ value: 30 }).borderWidth(1).layoutWeight(5).aspectRatio(2)
        }.borderWidth(1).width(250)

        Text('Gauge颜色相关通用属性组合').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 5 })
        Gauge({ value: 30, min: 0, max: 100 })
          .colors([[0x317AF7, 0.1], [0x5BA854, 0.2], [0xE08C3A, 0.3], [0x9C554B, 0.4]])
          .width(100)
          .height(100)
          .strokeWidth(10)
          .backgroundColor(Color.Pink)
          .foregroundColor(Color.Green)
          .linearGradient({
            angle: 90,
            colors: [[Color.Pink, 0.0], [Color.Green, 0.5], [Color.Yellow, 1.0]]
          })
      }.borderWidth(2).margin(5)
    }.height('100%').width('100%').align(Alignment.Top)
  }
}