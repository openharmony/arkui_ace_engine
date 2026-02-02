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
  title_2?: string
  subtitle_2?: string
  message_2?: string
  autoCancel?: boolean
  alignment?: DialogAlignment
  offset?: Offset
  gridCount?: number
  p_Button_value?: string
  s_Button_value?: string
  fontColor_p?: ResourceColor
  backgroundColor_p?: ResourceColor
  fontColor_s?: ResourceColor
  backgroundColor_s?: ResourceColor
  maskRect?: Rectangle
  alignment_m?: DialogAlignment
  offset_m?: Offset
  font_set?: boolean
  background_set?: boolean
  style_1?: DialogButtonStyle
  defaultFocus_1?: boolean
}

@Entry
@Component
struct AlertDialogTestLevel0_1 {
  @State title_2: string = 'two buttons title'
  @State message_2: string = 'this is the message of two buttons alertdialog'
  @State subtitle_2: string = 'two buttons subtitle'
  @State autoCancel?: boolean = undefined
  @State alignment?: DialogAlignment = undefined
  @State offset_dialog?: Offset = undefined
  @State gridCount?: number = undefined
  @State p_Button_value: string = 'primary button '
  @State s_Button_value: string = 'secondary button '
  @State enabled_2?: boolean = undefined
  @State fontColor_2: ResourceColor = ''
  @State backgroundColor_2: ResourceColor = ''
  @State fontColor_3?: ResourceColor = undefined
  @State backgroundColor_3?: ResourceColor = undefined
  //新增接口验证
  @State maskRect?: Rectangle = undefined
  @State offset_m?: Offset = undefined
  @State alignment_m?: DialogAlignment = undefined
  @State fontColor_1: string = 'rgba(255, 128, 0, 1.00)'
  @State backgroundColor_1: Color = Color.Pink
  @State style_1?: DialogButtonStyle = undefined
  @State defaultFocus_1?: boolean = undefined
  @State font_set: boolean = true
  @State background_set: boolean = true
  @State toastInfo: string = '初始设置'
  @State calc_index: number = -1
  private index: number = -1
  private lastIndex: number = -1
  private sets: SetsOption[] = [
    {
      //正常字符串，其他默认
      toastInfo: '1.1 一行字符串，其他默认  \n     1.2 蒙版大小100%, 偏移x0y0; 弹窗default对齐，偏移x0y0  \n     1.3 p_button: 粉底黄字； s_button: 粉底黄字',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: $r('app.float.float_0'),
        y: $r('app.float.float_0'),
        width: $r('app.string.Length_100percent'),
        height: $r('app.string.Length_100percent')
      },
      alignment_m: DialogAlignment.Default,
      offset_m: { dx: 0, dy: 0 },

      font_set: true,
      background_set: true,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
    },

    {
      //长字符串
      toastInfo: '2.1长字符串， 右下对齐，x0y0偏移，其他默认  \n     2.2 蒙版大小100%, 偏移x30y30; 弹窗左上对齐，偏移x30y30  \n     2.3 p_button: 粉底黄字； s_button: 粉底黄字',

      title_2: 'two buttons title'.repeat(10),
      subtitle_2: 'two buttons subtitle'.repeat(10),
      message_2: 'This is the message of two buttons alertdialog'.repeat(100),

      autoCancel: true,
      alignment: DialogAlignment.BottomEnd,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      p_Button_value: 'primary button '.repeat(10),
      s_Button_value: 'secondary button '.repeat(10),
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: $r('app.float.float_30'),
        y: $r('app.float.float_30'),
        width: $r('app.string.Length_100percent'),
        height: $r('app.string.Length_100percent')
      },
      alignment_m: DialogAlignment.TopStart,
      offset_m: { dx: 30, dy: 30 },

      font_set: true,
      background_set: true,
      style_1: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_1: false,
    },

    {
      //空字符串
      toastInfo: '3.1 title空字符串（不绘制）  \n     3.2 蒙版大小0（不绘制）, 偏移x-30y-30; 弹窗右下对齐，偏移x-30y-30  \n     3.3 p_button: 白底黄字； s_button: 蓝底黄字',

      title_2: 'two buttons title'.repeat(0),
      subtitle_2: 'two buttons subtitle'.repeat(0),
      message_2: 'This is the message of two buttons alertdialog'.repeat(0),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      p_Button_value: 'primary button '.repeat(0),
      s_Button_value: 'secondary button '.repeat(0),
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: $r('app.float.float_minus30'),
        y: $r('app.float.float_minus30'),
        width: $r('app.float.float_o'),
        height: $r('app.float.float_o')
      },
      alignment_m: DialogAlignment.BottomEnd,
      offset_m: { dx: -30, dy: -30 },

      font_set: true,
      background_set: false,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
    },

    {
      //
      toastInfo: '4.1. title空字符串，message和button设置单行字符串（对齐方式）；  \n     4.2 蒙版大小360/780, 偏移x-30y-30; 弹窗右下对齐，偏移x-30y-30  \n    4.3 p_button: 蓝底黄字； s_button: 白底黄字',

      title_2: 'two buttons title'.repeat(0),
      subtitle_2: 'two buttons subtitle'.repeat(0),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      p_Button_value: 'primary button '.repeat(1),
      s_Button_value: 'secondary button '.repeat(1),
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: $r('app.string.Length_minus30'),
        y: $r('app.string.Length_minus30'),
        width: $r('app.float.float_360'),
        height: $r('app.float.float_780')
      },
      alignment_m: DialogAlignment.BottomEnd,
      offset_m: { dx: -30, dy: -30 },

      font_set: true,
      background_set: false,
      style_1: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_1: false,
    },

    {
      //字符串默认
      toastInfo: '5.1 字符串默认（不绘制）  \n     5.2 蒙版大小360vp/780vp, 偏移x30y30; 弹窗左上对齐，偏移x30y30  \n     5.3 p_button: 粉底蓝字； s_button: 粉底白字',

      title_2: '',
      subtitle_2: '',
      message_2: '',

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      p_Button_value: '',
      s_Button_value: '',
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: $r('app.string.Length_30'),
        y: $r('app.string.Length_30'),
        width: $r('app.string.Length_360vp'),
        height: $r('app.string.Length_780vp')
      },
      alignment_m: DialogAlignment.TopStart,
      offset_m: { dx: 30, dy: 30 },

      font_set: false,
      background_set: true,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
    },

    {
      //
      toastInfo: '6.1 auto:undefined, gridCount:-3, 对齐:左上, offset:{-20，-20};  \n     6.2 蒙版大小100%, 偏移x30y30; 弹窗左上对齐，偏移x30y30  \n     6.3 p_button: 粉底白字； s_button: 粉底蓝字',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: false,
      alignment: DialogAlignment.TopStart,
      offset: { dx: -20, dy: -20 },
      gridCount: -3,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: '#ff0000ff',
      backgroundColor_p: '#ffff7eff',
      fontColor_s: $r('app.color.Color_blue'),
      backgroundColor_s: $r('app.color.Color_pink'),

      maskRect: {
        x: $r('app.string.Length_30vp'),
        y: $r('app.string.Length_30vp'),
        width: $r('app.string.Length_100percent'),
        height: $r('app.string.Length_100percent')
      },
      alignment_m: DialogAlignment.TopStart,
      offset_m: { dx: 30, dy: 30 },

      font_set: false,
      background_set: true,
      style_1: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_1: false,
    },

    {
      //
      toastInfo: '7.1 auto:undefined, gridCount:0, 对齐:default, offset: undefined;  \n     7.2 蒙版大小100%, 偏移x90px;y90px; 弹窗左上对齐，偏移x30y30  \n     7.3 p_button: 白底蓝字； s_button: 蓝底白字',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 0,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: $r('app.string.Length_90px'),
        y: $r('app.string.Length_90px'),
        width: $r('app.string.Length_100percent'),
        height: $r('app.string.Length_100percent')
      },
      alignment_m: DialogAlignment.TopStart,
      offset_m: { dx: 30, dy: 30 },

      font_set: false,
      background_set: false,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: true,
    },
    {
      //
      toastInfo: '8.1 auto:undefined, gridCount:2, 对齐:default, offset: {dx:0, dy:0}, s/p的button恢复默认色；  \n     8.2 蒙版大小125%, 偏移x50%y50%; 弹窗default对齐，偏移x0y0  \n     8.3 p_button: 蓝底白字； s_button: 白底蓝字',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 2,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: $r('app.string.Length_50percent'),
        y: $r('app.string.Length_50percent'),
        width: $r('app.string.Length_125percent'),
        height: $r('app.string.Length_125percent')
      },
      alignment_m: DialogAlignment.Default,
      offset_m: { dx: '0', dy: '0' },

      font_set: false,
      background_set: false,
      style_1: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_1: false,
    },

    {
      //
      toastInfo: '9.1 auto:true, gridCount:2, 对齐:BottomStart, offset:undefined;  \n     9.2 蒙版大小-150%, 偏移x50%y50%; 弹窗default对齐，偏移x0y0  \n     9.3 p_button: 白底蓝字； s_button: 白底蓝字',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.BottomStart,
      offset: { dx: 0, dy: 0 },
      gridCount: 2,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: '#ff0000ff',
      backgroundColor_p: '#ffff7eff',
      fontColor_s: $r('app.color.Color_blue'),
      backgroundColor_s: $r('app.color.Color_pink'),

      maskRect: {
        x: $r('app.string.Length_50percent'),
        y: $r('app.string.Length_50percent'),
        width: $r('app.string.Length_minus150percent'),
        height: $r('app.string.Length_minus150percent')
      },
      alignment_m: DialogAlignment.Default,
      offset_m: { dx: '0', dy: '0' },

      font_set: false,
      background_set: false,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: false,
    },

    {
      //
      toastInfo: '10.1 auto:true, gridCount:2, 对齐:BottomStart, offset:{0,0};  \n     10.2 蒙版大小75%, 偏移x0y0; 弹窗undefined对齐，偏移x0y0',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),


      autoCancel: true,
      alignment: DialogAlignment.BottomStart,
      offset: { dx: 0, dy: 0 },
      gridCount: 2,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: '#ffffffff',
      backgroundColor_p: '#ff000000',
      fontColor_s: $r('app.color.Color_white'),
      backgroundColor_s: $r('app.color.Color_black'),

      maskRect: {
        x: undefined,
        y: undefined,
        width: $r('app.string.Length_75percent'),
        height: $r('app.string.Length_75percent')
      },
      alignment_m: DialogAlignment.Default,
      offset_m: { dx: 0, dy: 0 },

      font_set: false,
      background_set: false,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: false,
    },

    {
      //
      toastInfo: '11.1 auto:true, gridCount:4, 对齐:undefined, offset:undefined, 非法颜色值；  \n     11.2 蒙版大小100%, 偏移x105pix;y105pix; 弹窗undefined对齐，偏移x0y0值',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 4,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: 'color_invalid',
      backgroundColor_p: 'color_invalid',
      fontColor_s: $r('app.string.Color_invalid'),
      backgroundColor_s: $r('app.string.Color_invalid'),

      maskRect: {
        x: $r('app.string.Length_105pix'),
        y: $r('app.string.Length_105pix'),
        width: $r('app.string.Length_100percent'),
        height: $r('app.string.Length_100percent')
      },
      alignment_m: DialogAlignment.Default,
      offset_m: { dx: 0, dy: 0 },

      font_set: false,
      background_set: false,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: false,
    },

    {
      //
      toastInfo: '12.1 auto:undefined, gridCount:20, 对齐:default, offset:{0,0}, 颜色值:undefined;  \n     12.2 蒙版大小100%, 偏移x100%y100%; 弹窗undefined对齐，偏移x0y0',

      title_2: 'two buttons title'.repeat(1),
      subtitle_2: 'two buttons subtitle'.repeat(1),
      message_2: 'This is the message of two buttons alertdialog'.repeat(1),

      autoCancel: true,
      alignment: DialogAlignment.Default,
      offset: { dx: 0, dy: 0 },
      gridCount: 20,

      p_Button_value: 'primary button'.repeat(1),
      s_Button_value: 'secondary button'.repeat(1),
      fontColor_p: undefined,
      backgroundColor_p: undefined,
      fontColor_s: undefined,
      backgroundColor_s: undefined,

      maskRect: {
        x: '100%',
        y: '100%',
        width: $r('app.string.Length_100percent'),
        height: $r('app.string.Length_100percent')
      },
      alignment_m: DialogAlignment.Default,
      offset_m: { dx: 0, dy: 0 },

      font_set: false,
      background_set: false,
      style_1: DialogButtonStyle.DEFAULT,
      defaultFocus_1: false,
    },

  ]

  private setParam(): void {
    // set parameter
    this.toastInfo = this.sets[this.index].toastInfo!

    this.title_2 = this.sets[this.index].title_2!
    this.subtitle_2 = this.sets[this.index].subtitle_2!
    this.message_2 = this.sets[this.index].message_2!

    this.autoCancel = this.sets[this.index].autoCancel
    this.alignment = this.sets[this.index].alignment
    this.offset_dialog = this.sets[this.index].offset
    this.gridCount = this.sets[this.index].gridCount

    this.s_Button_value = this.sets[this.index].s_Button_value!
    this.p_Button_value = this.sets[this.index].p_Button_value!
    this.fontColor_2 = this.sets[this.index].fontColor_p!
    this.backgroundColor_2 = this.sets[this.index].backgroundColor_p!
    this.fontColor_3 = this.sets[this.index].fontColor_s
    this.backgroundColor_3 = this.sets[this.index].backgroundColor_s

    this.maskRect = this.sets[this.index].maskRect
    this.offset_m = this.sets[this.index].offset_m
    this.alignment_m = this.sets[this.index].alignment_m

    this.font_set = this.sets[this.index].font_set!
    this.background_set = this.sets[this.index].background_set!
    this.style_1 = this.sets[this.index].style_1
    this.defaultFocus_1 = this.sets[this.index].defaultFocus_1
  }

  build() {
    Column({ space: 10 }) {

      Text('验证警告弹窗基本功能')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Button('two button dialog')
        .key('two_button')
        .onClick(() => {
          AlertDialog.show(
            {
              title: this.title_2,
              subtitle: this.subtitle_2,
              message: this.message_2,

              autoCancel: this.autoCancel,
              alignment: this.alignment,
              gridCount: this.gridCount,
              offset: this.offset_dialog,

              primaryButton: {
                value: this.p_Button_value,

                fontColor: this.fontColor_2,
                backgroundColor: this.backgroundColor_2,
                action: () => {
                  console.info('Buttons AlertDialog First Button-clicking callback')
                }
              },
              secondaryButton: {
                value: this.s_Button_value,

                fontColor: this.fontColor_3,
                backgroundColor: this.backgroundColor_3,
                action: () => {
                  console.info('Buttons AlertDialog Second Button-clicking callback')
                }
              },
              cancel: () => {
                console.info('Closed callbacks')
              }
            }
          )
        }).backgroundColor(0x317aff)

      Button('two button dialog mask')
        .key('two_button_mask')
        .onClick(() => {
          AlertDialog.show(
            {
              title: 'two button dialog mask title',
              subtitle: 'two button dialog mask subtitle',
              message: 'two button dialog mask message',

              autoCancel: true,
              gridCount: 4,

              alignment: this.alignment_m,
              offset: this.offset_m,
              maskRect: this.maskRect,

              primaryButton: {
                value: 'p button',
                action: () => {
                  console.info('Buttons AlertDialog First Button-clicking callback')
                }
              },
              secondaryButton: {
                value: 's button',
                action: () => {
                  console.info('Buttons AlertDialog Second Button-clicking callback')
                }
              },
              cancel: () => {
                console.info('Closed callbacks')
              }
            }
          )
        }).backgroundColor(0x317aff)

      Button('two button dialog style')
        .key('two_button_style')
        .onClick(() => {
          if (this.font_set === true) {
            if (this.background_set === true) {
              AlertDialog.show(
                {
                  title: 'two button dialog style title',
                  subtitle: 'two button dialog style subtitle',
                  message: 'font&background + style/focus',

                  primaryButton: {
                    value: 'style p button',
                    fontColor: this.fontColor_1,
                    backgroundColor: this.backgroundColor_1,
                    style: this.style_1,
                    action: () => {
                      console.info('Buttons AlertDialog First Button-clicking callback')
                    }
                  },
                  secondaryButton: {
                    value: 'style s button',
                    fontColor: this.fontColor_1,
                    backgroundColor: this.backgroundColor_1,
                    defaultFocus: this.defaultFocus_1,
                    action: () => {
                      console.info('Buttons AlertDialog Second Button-clicking callback')
                    }
                  },
                }
              )
            } else {
              AlertDialog.show(
                {
                  title: 'two button dialog style title',
                  subtitle: 'two button dialog style subtitle',
                  message: 'font + style/focus',

                  primaryButton: {
                    value: 'style p button',
                    fontColor: this.fontColor_1,
                    style: this.style_1,
                    action: () => {
                      console.info('Buttons AlertDialog First Button-clicking callback')
                    }
                  },
                  secondaryButton: {
                    value: 'style s button',
                    fontColor: this.fontColor_1,
                    defaultFocus: this.defaultFocus_1,
                    action: () => {
                      console.info('Buttons AlertDialog Second Button-clicking callback')
                    }
                  },
                }
              )
            }
          } else {
            if (this.background_set === true) {
              AlertDialog.show(
                {
                  title: 'two button dialog style title',
                  subtitle: 'two button dialog style subtitle',
                  message: 'background + style/focus',

                  primaryButton: {
                    value: 'style p button',
                    backgroundColor: this.backgroundColor_1,
                    style: this.style_1,
                    action: () => {
                      console.info('Buttons AlertDialog First Button-clicking callback')
                    }
                  },
                  secondaryButton: {
                    value: 'style s button',
                    backgroundColor: this.backgroundColor_1,
                    defaultFocus: this.defaultFocus_1,
                    action: () => {
                      console.info('Buttons AlertDialog Second Button-clicking callback')
                    }
                  },
                }
              )
            } else {
              AlertDialog.show(
                {
                  title: 'two button dialog style title',
                  subtitle: 'two button dialog style subtitle',
                  message: ' + style/focus',

                  primaryButton: {
                    value: 'style p button',
                    style: this.style_1,
                    action: () => {
                      console.info('Buttons AlertDialog First Button-clicking callback')
                    }
                  },
                  secondaryButton: {
                    value: 'style s button',
                    defaultFocus: this.defaultFocus_1,
                    action: () => {
                      console.info('Buttons AlertDialog Second Button-clicking callback')
                    }
                  },
                }
              )
            }
          }
        }).backgroundColor(0x317aff)

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