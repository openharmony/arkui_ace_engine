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

import { MyComponent } from './MyComponenet'

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Builder
export function PopupBorderBuilder(name: string, param: Object) {
  PopupBorderExample()
}

@Entry
@Component
struct PopupBorderExample {
  pathStack: NavPathStack = new NavPathStack()

  @State index: number[] = [0, 0, 0]
  @State show: boolean = false
  @State show_1: boolean = false
  @State linearGradientColors: Array<[ResourceColor, number]> = [
    ['#564AF7', 0.1],
    ['#46B1E3', 0.2],
    ['#61CFBE', 0.3],
    ['#64BB5C', 0.4],
    ['#A5D61D', 0.5],
    ['#AC49F5', 0.6],
    ['#E64566', 0.7],
    ['#E84026', 0.8],
    ['#ED6F21', 0.9],
    ['#F9A01E', 1.0],
    ['#F7CE00', 1.1]
  ]

  //
  @Builder PopupBuilder() {
    Row({ space: 2 }) {
      Image($r('app.media.app_icon'))
        .width(24)
        .height(24)
        .margin({ left: -5 })
      Text('Custom Popup')
        .fontSize(10)
    }
    .width(100)
    .height(50)
    .padding(5)
  }

  //
  @State popupOption: CustomPopupOptions = {
    builder: undefined,
    outlineLinearGradient: {
      direction: GradientDirection.Bottom,
      colors: [[Color.Blue, 1.0]]
    }
  }

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text(`验证气泡描边属性的绘制`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`气泡箭头/R角`)
            .paramTextStyle()
          Select([
            { value:'不设置箭头/R角' },
            { value:'设置箭头/R角' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '不设置箭头/R角':
                  this.popupOption.enableArrow = false
                  this.popupOption.radius = undefined
                  break;
                case '设置箭头/R角':
                  this.popupOption.enableArrow = true
                  this.popupOption.radius = 6
                  break;
              }
            })
            .key('select_popupArrowRadius')

          Text('气泡对齐位置')
            .paramTextStyle()

          Select([
            { value:'Placement.Bottom' },
            { value:'Placement.Top' },
            { value:'Placement.Right' },
            { value:'Placement.Left' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'Placement.Bottom':
                  this.popupOption.placement = Placement.Bottom
                  break;
                case 'Placement.Top':
                  this.popupOption.placement = Placement.Top
                  break;
                case 'Placement.Right':
                  this.popupOption.placement = Placement.Right
                  break;
                case 'Placement.Left':
                  this.popupOption.placement = Placement.Left
                  break;
              }
            })
            .key('select_popupPlacement')
        }
        .columnStyle()

        Column({space: 5}){
          Text(`选择描边的宽度`)
            .paramTextStyle()
          Select([
            { value:'设置描边10px' },
            { value:'设置描边10vp' },
            { value:'设置描边负10vp' },
            { value:'设置描边10fp' },
            { value:'设置描边0vp' },
            { value:'设置描边10lpx' },
            { value:'设置描边10%' },
            { value:'设置描边正常$r宽度' },
            { value:'设置描边异常$r宽度' },
            { value:'设置描边UN' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '设置描边UN':
                  this.popupOption.outlineWidth = undefined
                  break;
                case '设置描边10px':
                  this.popupOption.outlineWidth = '10px'
                  break;
                case '设置描边10vp':
                  this.popupOption.outlineWidth = '10vp'
                  break;
                case '设置描边负10vp':
                  this.popupOption.outlineWidth = '-10vp'
                  break;
                case '设置描边10fp':
                  this.popupOption.outlineWidth = '10fp'
                  break;
                case '设置描边10lpx':
                  this.popupOption.outlineWidth = '10lpx'
                  break;
                case '设置描边0vp':
                  this.popupOption.outlineWidth = '0vp'
                  break;
                case '设置描边10%':
                  this.popupOption.outlineWidth = '10%'
                  break;
                case '设置描边正常$r宽度':
                  this.popupOption.outlineWidth = $r('app.float.float_5')
                  break;
                case '设置描边异常$r宽度':
                  this.popupOption.outlineWidth = $r('app.string.label')
                  break;
              }
            })
            .key('popupLineWidth')

          Text(`选择描边的线性渐变方向`)
            .paramTextStyle()
          Select([
            { value: 'Left' },
            { value: 'Top' },
            { value: 'Right' },
            { value: 'Bottom' },
            { value: 'LeftTop' },
            { value: 'LeftBottom' },
            { value: 'RightTop' },
            { value: 'RightBottom' },
            { value: 'None' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {

              switch (value) {
                case 'Left':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.Left
                  break;
                case 'Top':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.Top
                  break;
                case 'Right':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.Right
                  break;
                case 'Bottom':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.Bottom
                  break;
                case 'LeftTop':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.LeftTop
                  break;
                case 'LeftBottom':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.LeftBottom
                  break;
                case 'RightTop':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.RightTop
                  break;
                case 'RightBottom':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.RightBottom
                  break;
                case 'None':
                  this.popupOption.outlineLinearGradient!.direction = GradientDirection.None
                  break;
              }
            })
            .key('popupLineLinearGradient.direction')

          Text(`选择描边的线性渐变颜色`)
            .paramTextStyle()

          Select([
            { value:'Str蓝色' },
            { value:'Str异常值' },
            { value:'Num绿色' },
            { value:'Res紫色' },
            { value:'Res异常' },
            { value:'Color橙色' },
            { value:'空[]' },
            { value:'3个[],正常渐变色,正常num' },
            { value:'3个[],异常渐变色,正常num' },
            { value:'3个[],正常渐变色,num有负值' },
            { value:'3个[],正常渐变色,num有1.0' },
            { value:'3个[],正常渐变色,num超过1.0' },
            { value:'3个[],正常渐变色,num顺序异常' },
            { value:'9个[],正常渐变色,正常num' },
            { value:'11个[],正常渐变色,正常num' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case 'Str蓝色':
                  this.popupOption.outlineLinearGradient!.colors = [['rgba(10,89,247,1)', 0.7]]
                  break;
                case 'Str异常值':
                  this.popupOption.outlineLinearGradient!.colors = [['validColor', 0.7]]
                  break;
                case 'Num绿色':
                  this.popupOption.outlineLinearGradient!.colors = [[0x64BB5C, 0.7]]
                  break;
                case 'Res紫色':
                  this.popupOption.outlineLinearGradient!.colors = [[$r('app.color.Color_purple'), 0.7]]
                  break;
                case 'Res异常':
                  this.popupOption.outlineLinearGradient!.colors = [[$r('app.string.label'), 0.7]]
                  break;
                case 'Color橙色':
                  this.popupOption.outlineLinearGradient!.colors = [[Color.Orange, 0.7]]
                  break;
                case '空[]':
                  this.popupOption.outlineLinearGradient!.colors = []
                  break;
                case '3个[],正常渐变色,正常num':
                  this.popupOption.outlineLinearGradient!.colors = [[Color.Red, 0.2], [Color.Blue, 0.4], [Color.Green, 0.7]]
                  break;
                case '3个[],异常渐变色,正常num':
                  this.popupOption.outlineLinearGradient!.colors = [[Color.Red, 0.2], ['ColorBLue', 0.4], [Color.Green, 0.7]]
                  break;
                case '3个[],正常渐变色,num有负值':
                  this.popupOption.outlineLinearGradient!.colors = [[Color.Red, 0.2], [Color.Blue, -0.4], [Color.Green, 0.7]]
                  break;
                case '3个[],正常渐变色,num有1.0':
                  this.popupOption.outlineLinearGradient!.colors = [[Color.Red, 0.2], [Color.Blue, 0.4], [Color.Green, 1.0]]
                case '3个[],正常渐变色,num超过1.0':
                  this.popupOption.outlineLinearGradient!.colors = [[Color.Red, 0.2], [Color.Blue, 0.4], [Color.Green, 1.1]]
                  break;
                case '3个[],正常渐变色,num顺序异常':
                  this.popupOption.outlineLinearGradient!.colors = [[Color.Red, 0.2], [Color.Blue, 0.7], [Color.Green, 0.4]]
                  break;
                case '9个[],正常渐变色,正常num':
                  this.popupOption.outlineLinearGradient!.colors = this.linearGradientColors.slice(0, 9)
                  break;
                case '11个[],正常渐变色,正常num':
                  this.popupOption.outlineLinearGradient!.colors = this.linearGradientColors
                  break;
              }
            })
            .key('popupLineLinearGradient.colors')

          Divider()

          Text(`气泡: 内描边属性`)
            .componentTextStyle()
            .bindPopup(this.show!!, {
              builder: this.PopupBuilder(),
              width: 240,
              placement: this.popupOption.placement,
              enableArrow: this.popupOption.enableArrow,
              radius: this.popupOption.radius,

              outlineWidth: '3vp',
              outlineLinearGradient: {
                direction: undefined,
                colors: [['#64BB5C', 1.0]]
              },
              borderWidth: this.popupOption.outlineWidth,
              borderLinearGradient: this.popupOption.outlineLinearGradient
            })
            .onClick( () => {
              this.show = true
            })

          Text(`气泡：外描边属性`)
            .componentTextStyle()
            .bindPopup(this.show_1!!, {
              builder: this.PopupBuilder(),
              width: 240,
              placement: this.popupOption.placement,
              enableArrow: this.popupOption.enableArrow,
              radius: this.popupOption.radius,

              outlineWidth: this.popupOption.outlineWidth,
              outlineLinearGradient: this.popupOption.outlineLinearGradient,
              borderWidth: '3vp',
              borderLinearGradient: {
                direction: undefined,
                colors: [['#64BB5C', 1.0]]
              }
            })
            .onClick( () => {
              this.show_1 = true
            })
        }
        .columnStyle()
      }.width('100%').margin({ top: 5 })
    }
    .title('PopupBorderTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}