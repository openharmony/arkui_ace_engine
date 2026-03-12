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
  style_opt?: DialogButtonStyle
  defaultFocus_opt?: boolean
  buttons?: Array<AlertDialogButtonOptions>
  buttonDirection?: DialogButtonDirection
}

@Entry
@Component
struct AlertDialogTestLevel0_2 {
  @State title_opt: string = 'option buttons title'
  @State message_opt: string = 'this is the message of option buttons alertdialog'
  @State subtitle_opt: string = 'option buttons subtitle'
  @State fontColor_opt: Color = Color.Red
  @State backgroundColor_opt: Color = Color.Pink
  @State style_opt: DialogButtonStyle = DialogButtonStyle.DEFAULT
  @State defaultFocus_opt: boolean = false
  @State buttons: Array<AlertDialogButtonOptions> = []
  @State buttonDirection?: DialogButtonDirection = undefined
  @State toastInfo: string = '初始设置'
  @State calc_index: number = -1
  private index: number = -1
  private lastIndex: number = -1
  private sets: SetsOption[] = [

    {
      toastInfo: '1. 红字粉底 | 红字白底 | 粉底蓝字 | 白底蓝字 \n         2个button, AUTO布局（横向布局）',

      style_opt: DialogButtonStyle.DEFAULT,
      defaultFocus_opt: true,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.AUTO
    },
    {
      toastInfo: '2. 红字粉底 | 红字白底 | 粉底蓝字 | 白底蓝字 \n         4个button, AUTO布局（纵向布局）',

      style_opt: DialogButtonStyle.DEFAULT,
      defaultFocus_opt: false,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.AUTO
    },
    {
      toastInfo: '3. 红字粉底 | 红字白底 | 粉底蓝字 | 白底蓝字 \n         6个button, AUTO布局（纵向布局）',

      style_opt: DialogButtonStyle.DEFAULT,
      defaultFocus_opt: false,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.AUTO
    },
    {
      toastInfo: '4. 红字粉底 | 红字蓝底 | 粉底白字 | 蓝底白字 \n         2个button, AUTO布局（横向布局）',

      style_opt: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_opt: true,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.HORIZONTAL
    },
    {
      toastInfo: '5. 红字粉底 | 红字蓝底 | 粉底白字 | 蓝底白字 \n         4个button, AUTO布局（横向布局）',

      style_opt: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_opt: false,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.HORIZONTAL
    },
    {
      toastInfo: '6. 红字粉底 | 红字蓝底 | 粉底白字 | 蓝底白字 \n         6个button, AUTO布局（横向布局）',

      style_opt: DialogButtonStyle.HIGHLIGHT,
      defaultFocus_opt: false,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.HORIZONTAL
    },
    {
      //2023年10月10日14:49:53， 第二个和第四个button的底色不一致，确认style设置undefined时的走值规范？
      toastInfo: '7. 红字粉底 | 红字蓝底 | 粉底白字 | 蓝底白字 \n         2个button, AUTO布局（纵向布局）',

      style_opt: undefined,
      defaultFocus_opt: true,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.VERTICAL
    },
    {
      toastInfo: '8. 红字粉底 | 红字白底 | 粉底蓝字 | 白底蓝字 \n         4个button, AUTO布局（纵向布局）',

      style_opt: undefined,
      defaultFocus_opt: false,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.VERTICAL
    },
    {
      toastInfo: '9. 红字粉底 | 红字白底 | 粉底蓝字 | 白底蓝字 \n         6个button, AUTO布局（纵向布局）',

      style_opt: undefined,
      defaultFocus_opt: false,

      buttons: [
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
        {
          value: 'button',
          style: DialogButtonStyle.HIGHLIGHT,
          action: () => {
            console.info('Callback when button is clicked')
          }
        },
      ],
      buttonDirection: DialogButtonDirection.VERTICAL
    },
  ]

  private setParam(): void {
    // set parameter
    this.toastInfo = this.sets[this.index].toastInfo!

    this.style_opt = this.sets[this.index].style_opt!
    this.defaultFocus_opt = this.sets[this.index].defaultFocus_opt!

    this.buttons = this.sets[this.index].buttons!
    this.buttonDirection = this.sets[this.index].buttonDirection
  }

  build() {
    Column({ space: 10 }) {

      Text('验证警告弹窗基本功能')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Button('option button dialog')
        .key('option_button')
        .onClick(() => {
          AlertDialog.show(
            {
              title: this.title_opt,
              subtitle: this.subtitle_opt,
              message: this.message_opt,

              buttons: [

                {
                  // fontColor,backgroundColor > style > defaultFocus
                  value: 'opt button 1',

                  fontColor: this.fontColor_opt,
                  backgroundColor: this.backgroundColor_opt,
                  style: this.style_opt,
                  defaultFocus: this.defaultFocus_opt,

                  action: () => {
                    console.info('Buttons AlertDialog Button1-clicking callback')
                  }
                },
                {
                  // fontColor > style > defaultFocus
                  value: 'opt button 2',

                  fontColor: this.fontColor_opt,
                  style: this.style_opt,
                  defaultFocus: this.defaultFocus_opt,

                  action: () => {
                    console.info('Buttons AlertDialog Button2-clicking callback')
                  }
                },
                {
                  // backgroundColor > style > defaultFocus
                  value: 'opt button 3',

                  backgroundColor: this.backgroundColor_opt,
                  style: this.style_opt,
                  defaultFocus: this.defaultFocus_opt,

                  action: () => {
                    console.info('Buttons AlertDialog Button3-clicking callback')
                  }
                },
                {
                  //  style > defaultFocus
                  value: 'opt button 4',

                  style: this.style_opt,
                  defaultFocus: this.defaultFocus_opt,

                  action: () => {
                    console.info('Buttons AlertDialog Button4-clicking callback')
                  }
                },
              ],
            }
          )
        }).backgroundColor(0x317aff)

      Button('option button dialog buttons')
        .key('option_button_buttons')
        .onClick(() => {
          AlertDialog.show(
            {
              title: this.title_opt,
              subtitle: this.subtitle_opt,
              message: this.message_opt,

              buttons: this.buttons,
              buttonDirection: this.buttonDirection
            }
          )
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