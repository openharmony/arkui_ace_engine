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

import { MyComponent } from '../../../../common/MyComponent';

class SetsOption {
  toastInfo?: string
  title_1?: string
  subtitle_1?: string
  message_1?: string
  confirm_value_1?: string
  autoCancel?: boolean
  alignment?: DialogAlignment
  offset?: Offset
  gridCount?: number
  fontColor?: Color
  backgroundColor?: Color
  maskRect?: Rectangle
  alignment_1?: DialogAlignment
  offset_1?: Offset
  style_1?: DialogButtonStyle
  defaultFocus_1?: boolean
  style_set?: boolean
}

@Entry
@Component
struct AlertDialogTestLevel0_0 {
  @State title_1: string = 'one button title'
  @State subtitle_1: string = 'one button subtitle'
  @State message_1: string = 'This is the message of one button alertdialog'
  @State autoCancel?: boolean = undefined
  @State alignment?: DialogAlignment = undefined
  @State offset_dialog?: Offset = undefined
  @State gridCount?: number = undefined
  @State confirm_value_1: string = 'confirm value '
  @State enabled_1?: boolean = undefined
  @State fontColor_0?: Color = undefined
  @State backgroundColor_0?: Color = undefined
  //新增接口验证
  @State maskRect?: Rectangle = undefined
  @State offset_1?: Offset = undefined
  @State alignment_1?: DialogAlignment = undefined
  @State style_1?: DialogButtonStyle = undefined
  @State defaultFocus_1?: boolean = undefined
  @State style_set: boolean = false
  @State toastInfo: string = '初始设置'
  @State calc_index: number = -1
  private index: number = -1
  private lastIndex: number = -1
  private sets: SetsOption[] = [
    {
      toastInfo: '1.1 一行字符串，其他默认  \n     1.2 蒙版大小100%, 偏移x0y0; 弹窗default对齐，偏移x0y0  \n     1.3 button: 蓝底白字',

      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      fontColor: undefined,
      backgroundColor: undefined,

      //默认值设置
      maskRect: {
        x: 0,
        y: 0,
        width: '100%',
        height: '100%'
      },
      alignment_1: DialogAlignment.Default,
      offset_1: { dx: 0, dy: 0 },

      style_1: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_1: false,
      style_set: true,
    },

    {
      //长字符串
      toastInfo: '2.1长字符串， 右下对齐，x0y0偏移，其他默认  \n     2.2 蒙版大小100%, 偏移x30y30; 弹窗左上对齐，偏移x30y30  \n     2.3 button: 蓝底白字',
      title_1: 'one button title'.repeat(10),
      subtitle_1: 'one button subtitle'.repeat(10),
      message_1: 'This is the message of one button alertdialog'.repeat(100),
      confirm_value_1: 'confirm value '.repeat(10),

      autoCancel: true,
      alignment: DialogAlignment.BottomEnd,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      fontColor: undefined,
      backgroundColor: undefined,

      //x:30,y:30
      maskRect: {
        x: 30,
        y: 30,
        width: '100%',
        height: '100%'
      },
      alignment_1: DialogAlignment.TopStart,
      offset_1: { dx: 30, dy: 30 },

      style_1: undefined,
      defaultFocus_1: true,
      style_set: true,
    },

    {
      //空字符串
      toastInfo: '3.1 title空字符串（不绘制）  \n     3.2 蒙版大小0（不绘制）, 偏移x-30y-30; 弹窗右下对齐，偏移x-30y-30  \n     3.3 button: 白底蓝字',
      title_1: 'one button title'.repeat(0),
      subtitle_1: 'one button subtitle'.repeat(0),
      message_1: 'This is the message of one button alertdialog'.repeat(0),
      confirm_value_1: 'confirm value '.repeat(0),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      fontColor: undefined,
      backgroundColor: undefined,

      //x:-30,y:-30
      maskRect: {
        x: -30,
        y: -30,
        width: 0,
        height: 0
      },
      alignment_1: DialogAlignment.BottomEnd,
      offset_1: { dx: -30, dy: -30 },

      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
      style_set: true,
    },

    {
      //
      toastInfo: '4.1. title空字符串，message和button设置单行字符串（对齐方式）；  \n     4.2 蒙版大小360/780, 偏移x-30y-30; 弹窗右下对齐，偏移x-30y-30  \n     4.3 button: 白底蓝字',
      title_1: 'one button title'.repeat(0),
      subtitle_1: 'one button subtitle'.repeat(0),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      fontColor: undefined,
      backgroundColor: undefined,

      //x:'-30',y:'-30'
      maskRect: {
        x: '-30',
        y: '-30',
        width: '360',
        height: '780'
      },
      alignment_1: DialogAlignment.BottomEnd,
      offset_1: { dx: -30, dy: -30 },


      style_1: undefined,
      defaultFocus_1: false,
      style_set: false,
    },

    {
      //字符串默认
      toastInfo: '5.1 字符串默认（不绘制）  \n     5.2 蒙版大小360VP/780VP, 偏移x30y30; 弹窗左上对齐，偏移x30y30  \n     5.3 button: 白底蓝字',
      title_1: '',
      subtitle_1: '',
      message_1: '',
      confirm_value_1: '',

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      fontColor: undefined,
      backgroundColor: undefined,

      //x:'30',y:'30'
      maskRect: {
        x: '30',
        y: '30',
        width: '360vp',
        height: '780vp'
      },
      alignment_1: DialogAlignment.TopStart,
      offset_1: { dx: 30, dy: 30 },

      style_1: undefined,
      defaultFocus_1: false,
      style_set: false,
    },

    {
      //
      toastInfo: '6.1 auto:undefined, gridCount:-3, 对齐:左上, offset:{-20，-20};  \n     6.2 蒙版大小100%, 偏移x30y30; 弹窗左上对齐，偏移x30y30  \n     6.3 button: 蓝底白字',
      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: false,
      alignment: DialogAlignment.TopStart,
      offset: { dx: -20, dy: -20 },
      gridCount: -3,

      fontColor: undefined,
      backgroundColor: undefined,

      //x:'30vp',y:'30vp'
      maskRect: {
        x: '30vp',
        y: '30vp',
        width: '100%',
        height: '100%'
      },
      alignment_1: DialogAlignment.TopStart,
      offset_1: { dx: 30, dy: 30 },

      style_1: undefined,
      defaultFocus_1: true,
      style_set: false,
    },

    {
      //
      toastInfo: '7.1 auto:undefined, gridCount:0, 对齐:default, offset: undefined;  \n     7.2 蒙版大小100%, 偏移x90px;y90px; 弹窗左上对齐，偏移x30y30',
      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 0,

      fontColor: Color.Blue,
      backgroundColor: Color.Pink,

      //x:'105px',y:'105px'
      maskRect: {
        x: '90px',
        y: '90px',
        width: '100%',
        height: '100%'
      },
      alignment_1: DialogAlignment.TopStart,
      offset_1: { dx: 30, dy: 30 },

      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
      style_set: true,
    },
    {
      //
      toastInfo: '8.1 auto:undefined, gridCount:2, 对齐:default, offset: {dx:0, dy:0} s/p的button恢复默认色；  \n     8.2 蒙版大小125%, 偏移x-50%y-50%; 弹窗default对齐，偏移x0y0',
      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 2,

      fontColor: Color.Blue,
      backgroundColor: Color.Pink,

      //x:'-50%',y:'-50%'
      maskRect: {
        x: '-50%',
        y: '-50%',
        width: '125%',
        height: '125%'
      },
      alignment_1: DialogAlignment.Default,
      offset_1: { dx: '0', dy: '0' },

      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
      style_set: true,
    },

    {
      //
      toastInfo: '9.1 auto:true, gridCount:2, 对齐:BottomStart, offset:undefined;  \n     9.2 蒙版大小-150%, 偏移x50%y50%; 弹窗default对齐，偏移x0y0',
      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.BottomStart,
      offset: { dx: 0, dy: 0 },
      gridCount: 2,

      fontColor: Color.Blue,
      backgroundColor: Color.Pink,

      //x:'-50%',y:'-50%'
      maskRect: {
        x: '50%',
        y: '50%',
        width: '-150%',
        height: '-150%'
      },
      alignment_1: DialogAlignment.Default,
      offset_1: { dx: '0', dy: '0' },

      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
      style_set: true,
    },

    {
      //
      toastInfo: '10.1 auto:true, gridCount:2, 对齐:BottomStart, offset:{0,0};  \n     10.2 蒙版大小75%, 偏移x0y0; 弹窗undefined对齐，偏移x0y0',
      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.BottomStart,
      offset: { dx: 0, dy: 0 },
      gridCount: 2,

      fontColor: Color.White,
      backgroundColor: Color.Black,

      //x/y：undefined
      maskRect: {
        x: undefined,
        y: undefined,
        width: '75%',
        height: '75%'
      },
      alignment_1: undefined,
      offset_1: { dx: 0, dy: 0 },

      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
      style_set: true,
    },

    {
      //
      toastInfo: '11.1 auto:true, gridCount:4, 对齐:undefined, offset:undefined, 非法颜色值；  \n     11.2 蒙版大小100%, 偏移x30pix;y30pix; 弹窗undefined对齐，偏移x0y0',
      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      fontColor: Color.White,
      backgroundColor: Color.Black,

      //x:'30pix',y:'30pix'
      maskRect: {
        x: '30pix',
        y: '30pix',
        width: '100%',
        height: '100%'
      },
      alignment_1: undefined,
      offset_1: { dx: 0, dy: 0 },

      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
      style_set: true,
    },

    {
      //
      toastInfo: '12.1 auto:undefined, gridCount:20, 对齐:default, offset:{0,0}, 颜色值:undefined;  \n     12.2 蒙版大小100%, 偏移x0y0; 弹窗undefined对齐，偏移x0y0',
      title_1: 'one button title'.repeat(1),
      subtitle_1: 'one button subtitle'.repeat(1),
      message_1: 'This is the message of one button alertdialog'.repeat(1),
      confirm_value_1: 'confirm value '.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 20,

      fontColor: Color.Blue,
      backgroundColor: Color.Orange,

      //x/y：undefined
      maskRect: {
        x: undefined,
        y: undefined,
        width: '100%',
        height: '100%'
      },
      alignment_1: undefined,
      offset_1: { dx: 0, dy: 0 },

      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
      style_set: true,
    },

  ]

  private setParam(): void {
    // set parameter
    this.toastInfo = this.sets[this.index].toastInfo!

    this.title_1 = this.sets[this.index].title_1!
    this.subtitle_1 = this.sets[this.index].subtitle_1!
    this.message_1 = this.sets[this.index].message_1!

    this.autoCancel = this.sets[this.index].autoCancel
    this.alignment = this.sets[this.index].alignment
    this.offset_dialog = this.sets[this.index].offset
    this.gridCount = this.sets[this.index].gridCount

    this.confirm_value_1 = this.sets[this.index].confirm_value_1!
    this.fontColor_0 = this.sets[this.index].fontColor
    this.backgroundColor_0 = this.sets[this.index].backgroundColor

    this.maskRect = this.sets[this.index].maskRect
    this.offset_1 = this.sets[this.index].offset_1
    this.alignment_1 = this.sets[this.index].alignment_1

    this.style_1 = this.sets[this.index].style_1
    this.defaultFocus_1 = this.sets[this.index].defaultFocus_1
    this.style_set = this.sets[this.index].style_set!

  }

  build() {
    Column({ space: 10 }) {
      Text('验证警告弹窗基本功能')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Button('one button dialog')
        .key('one_button')
        .onClick(() => {

          AlertDialog.show(
            {
              title: this.title_1,
              subtitle: this.subtitle_1,
              message: this.message_1,

              autoCancel: this.autoCancel,
              alignment: this.alignment,
              offset: this.offset_dialog,
              gridCount: this.gridCount,

              confirm: {
                value: this.confirm_value_1,
                fontColor: this.fontColor_0,
                backgroundColor: this.backgroundColor_0,
                action: () => {
                  console.info('Confirm AlertDialog Button-clicking callback')
                }
              },
              cancel: () => {
                console.info('Confirm AlertDialog Closed callbacks')
              }
            }
          )
        })
        .backgroundColor(0x317aff)

      Button('one button dialog mask')
        .key('one_button_mask')
        .onClick(() => {
          AlertDialog.show(
            {
              title: 'one button dialog_1 title',
              subtitle: 'one button dialog_1 subtitle',
              message: 'message .'.repeat(15),

              autoCancel: true,
              gridCount: 4,

              alignment: this.alignment_1,
              offset: this.offset_1,
              maskRect: this.maskRect,

              confirm: {
                value: 'confirm button',
                action: () => {
                  console.info('Confirm_1 AlertDialog Button-clicking callback')
                }
              },
            }
          )
        })
        .backgroundColor(0x317aff)

      Button('one button dialog style')
        .key('one_button_style')
        .onClick(() => {
          if (this.style_set === true) {
            AlertDialog.show(
              {
                title: 'one button dialog_1 title',
                subtitle: 'one button dialog_1 subtitle',
                message: 'style and defaultFocus .',

                autoCancel: true,
                gridCount: 4,

                confirm: {
                  value: 'confirm button',
                  style: this.style_1,
                  defaultFocus: this.defaultFocus_1,
                  action: () => {
                    console.info('Confirm_1 AlertDialog Button-clicking callback')
                  }
                },
              }
            )
          } else {
            AlertDialog.show(
              {
                title: 'one button dialog_1 title',
                subtitle: 'one button dialog_1 subtitle',
                message: 'defaultFocus .',

                autoCancel: true,
                gridCount: 4,

                confirm: {
                  value: 'confirm button',
                  defaultFocus: this.defaultFocus_1,
                  action: () => {
                    console.info('Confirm_1 AlertDialog Button-clicking callback')
                  }
                },
              }
            )
          }
        })
        .backgroundColor(0x317aff)

      Text('切换测试参数')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Row({ space: 2 }) {

        Text(`${this.calc_index + 1}` + ' / ')
          .fontSize(9)
          .fontColor(0xCCCCCC)
        Text(`${this.sets.length}`)
          .key('paramSets_key')
          .fontSize(9)
          .fontColor(0xCCCCCC)


        MyComponent({
          title: 'Test ++', func: () => {

            this.index++
            if (this.index == this.sets.length) {
              this.index = 0
            }
            this.setParam()
            this.lastIndex = this.index
            this.calc_index = this.index

          }
        })

        MyComponent({
          title: 'Test --', func: () => {
            this.index--
            if (this.index <= -1) {
              this.index = this.sets.length - 1
            }
            this.setParam()
            this.lastIndex = this.index
            this.calc_index = this.index

          }
        })
      }
      .margin({ top: 10 })

      Text('配置信息显示: ' + ' \n ' +
        '    ' + this.toastInfo)
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

    }.width('100%').margin({ top: 20 })
  }
}