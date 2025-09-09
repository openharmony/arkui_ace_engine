/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { MyComponent} from  '../../../../common/MyComponent'

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

//自定义弹窗builder
@CustomDialog
struct CustomDialogBuilder {

  columnWidth: Dimension = '80%'
  columnHeight: Dimension = '50%'

  @Link textValue: string
  @Link inputValue: string
  controller?: CustomDialogController

  build() {
    Column() {
      Text('Change text').fontSize(20).margin({ top: 10, bottom: 10 })
      TextInput({ placeholder: '', text: this.textValue }).height(60).width('90%')
        .onChange((value: string) => {
          this.textValue = value
        })
      Text('Whether to change a text?').fontSize(16).margin({ bottom: 10 })
    }
    .width(this.columnWidth).height(this.columnHeight)
    .borderRadius(10)
    .backgroundColor('#A6C2BE')
  }
}

@CustomDialog
struct CustomDialogSetBuilder {

  columnWidth: Dimension = '80%'
  columnHeight: Dimension = '50%'

  @Link textValue: string
  @Link inputValue: string
  controller?: CustomDialogController

  build() {
    Column() {
      Text('Change text').fontSize(20).margin({ top: 10, bottom: 10 })
      TextInput({ placeholder: '', text: this.textValue }).height(60).width('90%')
        .onChange((value: string) => {
          this.textValue = value
        })
      Text('Whether to change a text?').fontSize(16).margin({ bottom: 10 })
    }
    .width(this.columnWidth).height(this.columnHeight)
    .borderRadius(10)
    .backgroundColor('#A6C2BE')
  }
}

@Entry
@Component
struct CustomDialogTestLevel0_6 {
  scroller: Scroller = new Scroller()
  @State index: number [] = [0, 0, 0]

  @State builderColumnWidth: Dimension = '80%'
  @State builderColumnHeight: Dimension = '80%'
  @State textValue: string = ''
  @State inputValue: string = 'click me'

  //不设置属性的controller
  dialogController: CustomDialogController | null = new CustomDialogController({

    builder: CustomDialogBuilder({
      textValue: $textValue,
      inputValue: $inputValue,
    }),
    alignment: DialogAlignment.Default,
    cornerRadius: 10,
  })

  //设置边框属性的controller
  dialogControllerSetBorder: CustomDialogController | null = new CustomDialogController({

    builder: CustomDialogSetBuilder({
      textValue: $textValue,
      inputValue: $inputValue,
    }),
    alignment: DialogAlignment.Default,
    cornerRadius: 10,
  })
  customDialogControllerSetBorderList: CustomDialogController[] = [
    // 1
    new CustomDialogController({

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 2
    new CustomDialogController({
      borderWidth: undefined,
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 3
    new CustomDialogController({
      borderWidth: { top: 0, bottom: 0, left: 0, right: 0},  //NA
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 4
    new CustomDialogController({
      borderWidth: { top: '-10', bottom: '0', left: '5vp', right: '5lpx'},  //单位不同，数值相同：横竖屏效果也不一样
      borderColor: Color.Orange,
      borderStyle: BorderStyle.Dotted,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 20,
    }),
    // 5
    new CustomDialogController({
      borderWidth: { top: 2, bottom: $r('app.float.float_2'), left: '2px', right: '10%'},
      borderColor: 'Color.Black',
      borderStyle: BorderStyle.Dashed,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 6
    new CustomDialogController({
      borderWidth: { top: '10aa', bottom: $r('app.string.MainAbility_label'), left: undefined, right: '5%'},
      borderColor: '#D2C3B2',
      borderStyle: BorderStyle.Solid,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 20,
    }),
    // 7
    new CustomDialogController({
      borderWidth: undefined,  //NA
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 8
    new CustomDialogController({
      borderWidth: '0vp',  //NA
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 9
    new CustomDialogController({
      borderWidth: '5px',
      borderColor: 'rgba(135, 43, 148, 1.00)',
      borderStyle: 7,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 20,
    }),
    // 10
    new CustomDialogController({
      borderWidth: '10lpx',
      borderColor: $r('app.string.MainAbility_label'),
      borderStyle: {top: BorderStyle.Dotted, bottom: BorderStyle.Dashed, left: BorderStyle.Solid, right: undefined},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 20,
    }),
    // 11
    new CustomDialogController({
      borderWidth: '15fp',
      borderColor: $r('app.color.Color_green'),
      borderStyle: {top: BorderStyle.Dashed},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 20,
    }),
    // 12
    new CustomDialogController({
      borderWidth: $r('app.float.float_20'),
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 13
    new CustomDialogController({
      borderWidth: '5%',
      borderColor: 0x4A4333,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 20,
    }),
    // 14
    new CustomDialogController({
      borderWidth: $r('app.string.MainAbility_label'),  //NA
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 15
    new CustomDialogController({
      borderWidth: '-20vp',  //NA
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 16
    new CustomDialogController({
      borderWidth: 60,
      borderColor: undefined,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 17
    new CustomDialogController({
      borderWidth: 40,
      borderColor: Color.Transparent,
      borderStyle: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 18
    new CustomDialogController({
      borderWidth: 300,
      borderColor: Color.Green,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
  ]

  //设置尺寸属性的controller
  dialogControllerSetSize: CustomDialogController | null = new CustomDialogController({

    builder: CustomDialogSetBuilder({
      textValue: $textValue,
      inputValue: $inputValue,
    }),
    alignment: DialogAlignment.Default,
    cornerRadius: 10,
  })
  customDialogControllerSetSizeList: CustomDialogController[] = [
  // 1
    new CustomDialogController({
      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 2
    new CustomDialogController({
      width: undefined,
      height: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 3
    new CustomDialogController({
      width: '320vp',
      height: '600vp',

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 4
    new CustomDialogController({
      width: '320px',
      height: '600px',

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 5
    new CustomDialogController({
      width: '320fp',
      height: '600fp',

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 6
    new CustomDialogController({
      width: '320lpx',
      height: '600lpx',

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 7
    new CustomDialogController({
      width: 320,
      height: 600,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 8
    new CustomDialogController({
      width: '-300vp',
      height: '-600vp',

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 9
    new CustomDialogController({
      width: 0,
      height: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 10
    new CustomDialogController({
      width: '380vp',
      height: '100%',

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 11
    new CustomDialogController({
      width: 800,
      height: 1200,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 12
    new CustomDialogController({
      width: 1200,
      height: 1600,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 13
    new CustomDialogController({
      width: '100%',
      height: '100%',

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 14
    new CustomDialogController({
      width: $r('app.float.float_400'),
      height: $r('app.float.float_780'),

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 15
    new CustomDialogController({
      width: $r('app.string.MainAbility_label'),
      height: $r('app.string.MainAbility_label'),

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 16
    new CustomDialogController({
      width: undefined,
      height: 0,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 17
    new CustomDialogController({
      width: undefined,
      height: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
  ]

  //设置阴影属性的controller
  dialogControllerSetShadow: CustomDialogController | null = new CustomDialogController({

    builder: CustomDialogSetBuilder({
      textValue: $textValue,
      inputValue: $inputValue,
    }),
    alignment: DialogAlignment.Default,
    cornerRadius: 10,
  })
  customDialogControllerSetShadowList: CustomDialogController[] = [
    // 1
    new CustomDialogController({
      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 2
    new CustomDialogController({
      shadow: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 3
    new CustomDialogController({
      shadow: ShadowStyle.OUTER_DEFAULT_XS,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 4
    new CustomDialogController({
      shadow: ShadowStyle.OUTER_DEFAULT_SM,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 5
    new CustomDialogController({
      shadow: ShadowStyle.OUTER_DEFAULT_MD,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 6
    new CustomDialogController({
      shadow: ShadowStyle.OUTER_DEFAULT_LG,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 7
    new CustomDialogController({
      shadow: ShadowStyle.OUTER_FLOATING_SM,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 8
    new CustomDialogController({
      shadow: undefined,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 9
    new CustomDialogController({
      shadow: ShadowStyle.OUTER_FLOATING_MD,

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 10
    new CustomDialogController({
      shadow: {radius: 10},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 11
    new CustomDialogController({
      shadow: {radius: 10, type: undefined, color: undefined,  offsetX: undefined, offsetY: undefined, fill: undefined},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 12
    new CustomDialogController({
      shadow: {radius: $r('app.float.float_minus_10')},  //NA

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 13
    new CustomDialogController({
      shadow: {radius: 0},  //NA

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 14
    new CustomDialogController({
      shadow: {radius: 30, type: 7, color: Color.Orange, offsetX: -20, offsetY: -20, fill: true},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 15
    new CustomDialogController({
      shadow: {radius: $r('app.string.MainAbility_label'), color: Color.Orange, offsetX: -20, offsetY: -20,},  //NA 阴影圆角异常值

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 16
    new CustomDialogController({
    shadow: {radius: 10, type: ShadowType.BLUR, color: '#ED6F21', offsetX: -40, offsetY: -40, fill: false},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 17
    new CustomDialogController({
      shadow: {radius: 10, type: ShadowType.COLOR, color: 'rgba(237, 111, 33, 1.0)', offsetX: $r('app.float.float_20'), offsetY: $r('app.float.float_20'), fill: true},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 18
    new CustomDialogController({
      shadow: {radius: 10, type: ShadowType.COLOR, color: 'rgba(237, 111, 33, 0.2)', offsetX: $r('app.string.MainAbility_label'), offsetY: $r('app.string.MainAbility_label')},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 19
    new CustomDialogController({
      shadow: {radius: 10, type: ShadowType.COLOR, color: 'rgba(237aa, 111aa, 33bb, 0.2cc)', offsetX: 100, offsetY: 100, },

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 20
    new CustomDialogController({
      shadow: {radius: 10, type: ShadowType.COLOR, color: $r('app.color.Color_purple'), fill: true},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 21
    new CustomDialogController({
      shadow: {radius: 10, type: ShadowType.COLOR, color: $r('app.string.MainAbility_label')},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 22
    new CustomDialogController({
      shadow: {radius: 10, type: ShadowType.COLOR, color: 0xED6F21, },

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
    // 23
    new CustomDialogController({
      shadow: {radius: $r('app.string.string_20'), type: ShadowType.COLOR, color: 'rgba(237, 111, 33, 0.2)', offsetX: $r('app.string.string_20percent'), offsetY: $r('app.string.string_20')},

      builder: CustomDialogSetBuilder({
        textValue: $textValue,
        inputValue: $inputValue,
      }),
      alignment: DialogAlignment.Default,
      cornerRadius: 10,
    }),
  ]

  // 在自定义组件即将析构销毁时将dialogController置空
  aboutToDisappear() {
    this.dialogController = null
    this.dialogControllerSetBorder = null
    this.dialogControllerSetSize = null
    this.dialogControllerSetShadow = null
  }

  build() {
    Scroll(this.scroller){
      Column({space: 5}) {
        Text(`验证自定义弹窗设置圆角 | 边框 | 宽度/高度 | 阴影`)
          .paramTextStyle()

        Column({space: 5}){
          Text(`不设置新增属性`)
            .paramTextStyle()
          Text(`CustomDialog: unset`)
            .backgroundColor(Color.Orange)
            .onClick( () => {
              if (this.dialogController != null) {
                this.dialogController.open()
              }
            })

          Text(`自定义弹窗设置边框`)
            .paramTextStyle()
          Row({space:2}){
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.customDialogControllerSetBorderList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({ title: 'Test0+', func: () => {
              this.index[0]++
              if (this.index[0] == this.customDialogControllerSetBorderList.length) {
                this.index[0] = 0
              }
              this.dialogControllerSetBorder = this.customDialogControllerSetBorderList[this.index[0]]
            } })
            MyComponent({ title: 'Test0-', func: () => {
              this.index[0]--
              if (this.index[0] <= -1) {
                this.index[0] = this.customDialogControllerSetBorderList.length - 1
              }
              this.dialogControllerSetBorder = this.customDialogControllerSetBorderList[this.index[0]]
            }})
          }
          Text(`CustomDialog: set_border`)
            .key(`CustomDialog: set_border`)
            .backgroundColor(Color.Orange)
            .onClick( () => {
              if (this.dialogControllerSetBorder != null) {
                this.dialogControllerSetBorder.open()
              }
            })
          Text(`自定义弹窗设置宽度 | 高度`)
            .paramTextStyle()
          Row({space:2}){
            Text(`${this.index[1] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.customDialogControllerSetSizeList.length}`)
              .key('paramSets_key_1')
              .fontSize(9)
            MyComponent({ title: 'Test1+', func: () => {
              this.index[1]++
              if (this.index[1] == this.customDialogControllerSetSizeList.length) {
                this.index[1] = 0
              }
              this.dialogControllerSetSize = this.customDialogControllerSetSizeList[this.index[1]]
            } })
            MyComponent({ title: 'Test1-', func: () => {
              this.index[1]--
              if (this.index[1] <= -1) {
                this.index[1] = this.customDialogControllerSetSizeList.length - 1
              }
              this.dialogControllerSetSize = this.customDialogControllerSetSizeList[this.index[1]]
            }})
          }
          Text(`CustomDialog: set_width_height`)
            .key(`CustomDialog: set_width_height`)
            .backgroundColor(Color.Orange)
            .onClick( () => {
              if (this.dialogControllerSetSize != null) {
                this.dialogControllerSetSize.open()
              }
            })

          Text(`自定义弹窗设置阴影`)
            .paramTextStyle()
          Row({space:2}){
            Text(`${this.index[2] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.customDialogControllerSetShadowList.length}`)
              .key('paramSets_key_2')
              .fontSize(9)
            MyComponent({ title: 'Test2+', func: () => {
              this.index[2]++
              if (this.index[2] == this.customDialogControllerSetShadowList.length) {
                this.index[2] = 0
              }
              this.dialogControllerSetShadow = this.customDialogControllerSetShadowList[this.index[2]]
            } })
            MyComponent({ title: 'Test2-', func: () => {
              this.index[2]--
              if (this.index[2] <= -1) {
                this.index[2] = this.customDialogControllerSetShadowList.length - 1
              }
              this.dialogControllerSetShadow = this.customDialogControllerSetShadowList[this.index[2]]
            }})
          }
          Text(`CustomDialog: set_shadow`)
            .key(`CustomDialog: set_shadow`)
            .backgroundColor(Color.Orange)
            .onClick( () => {
              if (this.dialogControllerSetShadow != null) {
                this.dialogControllerSetShadow.open()
              }
            })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }
}
