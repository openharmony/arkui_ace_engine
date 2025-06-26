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

import {
  CustomDialogController_with_radius,
  CustomDialogController_with_backgroundColor,
  CustomDialogController_with_backgroundColor_radius
} from '../../../../common/CustomDialogController'
import { MyComponent } from '../../../../common/MyComponent';

class SetParam {
  public title?: string
  public func?: () => void
}

@Entry
@Component
struct CustomDialogTestLevel0_1 {
  @State toastInfo: string = '初始设置'
  @State calcIndex: number = -1
  private index: number = -1
  private lastIndex: number = -1
  @State inputValue: string = 'customDialog: click me '
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogController_with_backgroundColor_radius({
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),

    backgroundColor: 0xd9ffffff,
    cornerRadius: 10,
  })
  private setsBackgroundColor: SetParam[] = [
    {
      title: 'Color:Color', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
      })

      this.toastInfo = '1.1 Color.Pink '
    }
    },
    {
      title: 'Color:Str', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: '#fffcacfc',
      })

      this.toastInfo = '1.2 Color: #fffcacfc '
    }
    },
    {
      title: 'Color:Num', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: 0xFCACFC,
      })

      this.toastInfo = '1.3 Color: 0xFCACFC '
    }
    },
    {
      title: 'Color:Res', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: $r('app.color.Color_pink'),
      })

      this.toastInfo = '1.4 Color: app.color.Color_pink'
    }
    },
    {
      title: 'Color:UN', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: undefined,
      })

      this.toastInfo = '1.5 Color: undefined '
    }
    },
    {
      title: 'Color:Valid', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: 'rgb(-128, 256, 0, 1.5)',
      })

      this.toastInfo = '1.6 Color: rgb --> 走默认值'
    }
    },

  ]
  private setsCornerRadius: SetParam[] = [
    {
      title: 'Rd:12', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: 12,
      })

      this.toastInfo = '2.1 cornerRadius:12'
    }
    },
    {
      title: 'Rd:30', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: $r('app.string.Length_30'),
      })

      this.toastInfo = '2.2 cornerRadius:30'
    }
    },
    {
      title: 'Rd:0', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: 0,
      })

      this.toastInfo = '2.3  cornerRadius:0'
    }
    },
    {
      title: 'Rd:-12 ', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: -12,
      })

      this.toastInfo = '2.4  cornerRadius:-12 --> 走直角设置'
    }
    },
    {
      title: 'Rd:36px', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: '36px',
      })

      this.toastInfo = '2.5 cornerRadius: 36px'
    }
    },
    {
      title: 'Rd:UN', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: undefined,
      })

      this.toastInfo = '2.6 cornerRadius: undefined --> 走直角设置'
    }
    },
  ]
  private setsRadiusColor: SetParam[] = [
    {
      title: 'R12_Green', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: 12,
        backgroundColor: Color.Green
      })

      this.toastInfo = '3.1 Radius:12, Color:Green'
    }
    },
    {
      title: 'R24_Green', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: 24,
        backgroundColor: Color.Green
      })

      this.toastInfo = '3.2 Radius:24, Color:Green'
    }
    },
    {
      title: 'R36_Green', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: 36,
        backgroundColor: Color.Green
      })

      this.toastInfo = '3.3 Radius:36, Color:Green'
    }
    },
    {
      title: 'R120_Green', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: 120,
        backgroundColor: Color.Green
      })

      this.toastInfo = '3.4 Radius:120, Color:Green'
    }
    },
    {
      title: 'R24_Trans', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: 24,
        backgroundColor: Color.Transparent
      })

      this.toastInfo = '3.5 Radius:24, Color:Transparent'
    }
    },
    {
      title: 'RUn_Un', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        cornerRadius: undefined,
        backgroundColor: undefined
      })

      this.toastInfo = '3.6 Radius&Color: undefined'
    }
    },
  ]

  // 在自定义组件即将析构销毁时将dialogController删除和置空
  aboutToDisappear() {
    this.dialogController = null // 将dialogController置空
  }

  onCancel() {
    console.info('Callback when the first button is clicked')
  }

  onAccept() {
    console.info('Callback when the second button is clicked')
  }

  existApp() {
    console.info('Click the callback in the blank area')
  }

  build() {
    Column({ space: 10 }) {

      Text('验证自定义弹窗：backgroundColor, cornerRadius功能:')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10, top: 10 })

      Text('backgroundColor参数切换：')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Row({ space: 2 }) {
        ForEach(this.setsBackgroundColor, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
        }, (item: SetParam) => item.title)
      }

      Text('cornerRadius参数切换：')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Row({ space: 2 }) {
        ForEach(this.setsCornerRadius, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
        }, (item: SetParam) => item.title)
      }

      Text('Radius&Color: builder&custom的参数切换：')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Row({ space: 2 }) {
        ForEach(this.setsRadiusColor, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
        }, (item: SetParam) => item.title)
      }

      Button(this.inputValue)
        .onClick(() => {
          this.dialogController!.open()
        }).backgroundColor(0x317aff)

      Text('配置信息显示: ' + ' \n ' +
        '    ' + this.toastInfo)
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })
    }.width('100%').margin({ top: 5 })
  }
}