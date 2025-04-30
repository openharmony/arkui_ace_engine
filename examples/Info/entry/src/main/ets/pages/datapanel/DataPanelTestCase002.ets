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

interface setsObject {
  max: number | undefined
  valueColors: Array<ResourceColor | LinearGradient> | undefined
  trackBackgroundColor: ResourceColor | undefined
  strokeWidth: Length | undefined
  radius: number | Resource | undefined
  colors: Array<ResourceColor | LinearGradient> | undefined
  offsetX: number | Resource | undefined
  offsetY: number | Resource | undefined
  borderRadius: Length | BorderRadiuses | undefined

}

@Entry
@Component
struct DataPanelLevel0_0 {
  @Styles
  pressedStyle(){
    .backgroundColor(0x238E23)
  }

  @Styles
  normalStyles() {
    .backgroundColor(0x0000ff)
  }

  public color1: LinearGradient =
    new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#FFEF629F', offset: 1 }])
  public color2: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: $r('app.color.yellow'), offset: 1 }])
  public color3: LinearGradient =
    new LinearGradient([{ color: '#65e26709', offset: -10 }, { color: 0XFF03CDF1, offset: 0.5 },
      { color: '#6508efa6', offset: 2 }])
  @State valuesValue: number[][] =
    [[10, -10, 20, 30, 60, 80, 0, 50, -100, 90], [500, 400, 300, 200], [50, 33.3, 300], [10, 20, 30, 40, 50, 60],
      [40, 50]]
  @State values: number[] = [10]
  @State max: number | undefined = undefined
  @State valueColors: Array<ResourceColor | LinearGradient> | undefined = undefined
  @State trackBackgroundColor: ResourceColor | undefined = undefined
  @State strokeWidth: Length | undefined = undefined
  @State radius: number | Resource | undefined = undefined
  @State borderradius: Length | BorderRadiuses | undefined = undefined
  @State colors: Array<ResourceColor | LinearGradient> | undefined = undefined
  @State offsetX: number | Resource | undefined = undefined
  @State offsetY: number | Resource | undefined = undefined
  @State closeEffect: boolean | undefined = false
  @State info: string | undefined = undefined
  @State show: boolean = false
  private index: number = -1
  private testCase: Array<setsObject> = [
  // case0：黄、粉、紫、深蓝、蓝、绿色（第一个DataPanel无绿色）
    {
      max: 0, //max等于value数组各项的和
      valueColors: ['hhh'],
      trackBackgroundColor: 'hhh',
      strokeWidth: -100,
      radius: -10,
      colors: ['hhh'],
      offsetX: 0,
      offsetY: 0,
      borderRadius: 100
    },
    // case1：绿、黄、红、蓝（第一个DataPanel黄色渐变）
    {
      max: -10, //max等于value数组各项的和
      valueColors: [Color.Green, $r('app.color.yellow'), '#fff10303', 0XFF03CDF1],
      trackBackgroundColor: '#c60b29ec',
      strokeWidth: 10,
      radius: 0,
      colors: [Color.Red], //数据段个数设置4个，投影颜色设置1个，只显示一个投影颜色
      offsetX: -5,
      offsetY: -5,
      borderRadius: {
        topLeft: 10,
        topRight: 10,
        bottomLeft: 10,
        bottomRight: 10
      }
    },
    // case2：绿（第一个DataPanel黄、橙、粉）
    {
      max: 10,
      valueColors: ['rgb(11,236,85)'],
      trackBackgroundColor: 0x2f817171,
      strokeWidth: '40vp',
      radius: $r('app.string.string_10vp'),
      colors: ['#e4efdf12', Color.Gray, 0XFF03CDF6],
      offsetX: 15,
      offsetY: $r('app.string.string_15vp'),
      borderRadius: {
        topLeft: '5px',
        topRight: '20vp',
        bottomLeft: '5.5',
        bottomRight: '20%'
      }
    },
    // case3：红、黄、天蓝、深蓝、紫、绿（第一个DataPanel黄、橙、粉、紫）
    {
      max: 500,
      valueColors: ['#e6f60202', this.color2, $r('app.color.yellow'), this.color3, Color.Blue, 0xe67c02f6],
      trackBackgroundColor: Color.Green,
      strokeWidth: $r('app.string.string_15vp'),
      radius: $r('app.string.string_20vp'),
      colors: [this.color2, Color.Blue, 0xe67c02f6, this.color3, Color.Gray, 0XFF03CDF6, $r('app.color.yellow')],
      offsetX: $r('app.string.string_50vp'),
      offsetY: 50,
      borderRadius: {
        topLeft: 0,
        topRight: '',
        bottomLeft: 99999,
        bottomRight: $r('app.string.rRadius')
      }
    },
    // case4：红、绿粉渐变、绿（第一个DataPanel黄、橙）
    {
      max: 500,
      valueColors: ['#e6f60202', this.color1, $r('app.color.yellow'), this.color2, Color.Blue, 0xe67c02f6],
      trackBackgroundColor: Color.Green,
      strokeWidth: '50%',
      radius: $r('app.string.string_20vp'),
      colors: [this.color1, Color.Blue, 0xe67c02f6, '#e4efdf12', Color.Gray, 0XFF03CDF6, $r('app.color.yellow')],
      offsetX: $r('app.string.string_50vp'),
      offsetY: 50,
      borderRadius: {
        topLeft: -5,
        topRight: -5.5,
        bottomLeft: 'abdresd',
        bottomRight: $r('app.color.start_window_background')
      }
    },
    // case5：预期是黄色渐变，实际是红、绿粉渐变、绿（第一个DataPanel黄、橙），原因是undefined未按照默认值生效， 预期版本5.1解决
    {
      max: undefined,
      valueColors: undefined,
      trackBackgroundColor: undefined,
      strokeWidth: undefined,
      radius: undefined,
      colors: undefined,
      offsetX: undefined,
      offsetY: undefined,
      borderRadius: undefined
    },
  ]

  private setParam(): void {
    // 1. 参数赋值
    this.max = this.testCase[this.index].max
    this.valueColors = this.testCase[this.index].valueColors
    this.trackBackgroundColor = this.testCase[this.index].trackBackgroundColor
    this.strokeWidth = this.testCase[this.index].strokeWidth
    this.radius = this.testCase[this.index].radius
    this.colors = this.testCase[this.index].colors
    this.offsetX = this.testCase[this.index].offsetX
    this.offsetY = this.testCase[this.index].offsetY
    this.borderradius = this.testCase[this.index].borderRadius

    // 2. 参数打印
    this.info = 'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index +
      '\nmax: ' + this.max +
      '\nvalueColors: ' + this.valueColors + ',trackBackgroundColor: ' + this.trackBackgroundColor + ',strokeWidth: ' +
    this.strokeWidth +
      '\nradius: ' + this.radius + ',colors: ' + this.colors + ',offsetX: ' + this.offsetX + ',offsetY: ' +
    this.offsetY + 'borderRadius: ' + this.borderradius
  }

  build() {
    Scroll() {
      Column() {
        Column() {
          Text('DataPanel组件 入参及属性测试').fontSize(12).fontColor(Color.Black).width('100%').margin({ top: 10 })
          Text('DataPanel组件设置宽高且只传入参中的必参数').fontSize(9).width('100%').margin({ top: 10, bottom: 10 })
          DataPanel({ values: this.values })
            .width(200).aspectRatio(1.5).closeEffect(this.closeEffect)
            .borderRadius(this.borderradius)

          Text('DataPanel组件设置宽高且面板类型为Line').fontSize(9).width('100%').margin({ top: 10, bottom: 10 })
          //面板类型为Line时strokeWidth属性不生效
          DataPanel({ values: this.values, max: this.max, type: DataPanelType.Line })
            .size({ width: '300', height: '100' })
            .closeEffect(this.closeEffect)
            .valueColors(this.valueColors)
            .trackBackgroundColor(this.trackBackgroundColor)
            .strokeWidth(this.strokeWidth)
            .trackShadow({
              radius: this.radius,
              colors: this.colors,
              offsetX: this.offsetX,
              offsetY: this.offsetY
            })
            .borderRadius(this.borderradius)

          Text('DataPanel组件设置宽高且面板类型为Circle').fontSize(9).width('100%').margin({ top: 10, bottom: 10 })
          DataPanel({ values: this.values, max: this.max, type: DataPanelType.Circle })
            .width(150)
            .height(150)
            .closeEffect(this.closeEffect)
            .valueColors(this.valueColors)
            .trackBackgroundColor(this.trackBackgroundColor)
            .strokeWidth(this.strokeWidth)
            .trackShadow({
              radius: this.radius,
              colors: this.colors,
              offsetX: this.offsetX,
              offsetY: this.offsetY
            })
            .borderRadius(this.borderradius)

          Text('DataPanel组件设置宽高且面板类型为Undefined').fontSize(9).width('100%').margin({ top: 10, bottom: 10 })
          DataPanel({ values: this.values, max: this.max, type: undefined })
            .width(300)
            .height(200)
            .layoutWeight('1')
            .margin(10)
            .align(Alignment.BottomEnd)
            .closeEffect(this.closeEffect)
            .valueColors(this.valueColors)
            .trackBackgroundColor(this.trackBackgroundColor)
            .strokeWidth(this.strokeWidth)
            .trackShadow({
              radius: this.radius,
              colors: this.colors,
              offsetX: this.offsetX,
              offsetY: this.offsetY
            })
            .borderRadius(this.borderradius)
        }.width('100%').height('85%')

        Divider()

        Text('是否关闭旋转动效及阴影效果：' + this.closeEffect).fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 2 }) {
          Text('CloseEffect:True')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.closeEffect = true
            })
            .stateStyles({ pressed: this.pressedStyle, normal: this.normalStyles })

          Text('CloseEffect:False')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.closeEffect = false
            })
            .stateStyles({ pressed: this.pressedStyle, normal: this.normalStyles })

          Text('CloseEffect:Undefined')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.closeEffect = undefined
            })
            .stateStyles({ pressed: this.pressedStyle, normal: this.normalStyles })
        }

        Text('切换参数，显示参数=' + this.show).fontSize(9).fontColor(0xCCCCCC).width('100%').onClick(() => {
          this.show = !this.show
        })

        Row({ space: 2 }) {
          Text(`${this.testCase.length}`).key('datapanel00_cycles')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index++
              // 控制循环
              if (this.index == this.testCase.length) {
                this.index = 0
              }
              this.setParam()
              this.values = this.valuesValue[this.index]
            })

          Text('Test--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              // 控制循环
              this.index--
              if (this.index == -1) {
                this.index = this.testCase.length - 1
              }
              this.setParam()
              this.values = this.valuesValue[this.index]
            })
        }

        if (this.show) {
          Text(this.info).fontSize(10)
        }
      }
    }.scrollBar(BarState.Off)
  }
}