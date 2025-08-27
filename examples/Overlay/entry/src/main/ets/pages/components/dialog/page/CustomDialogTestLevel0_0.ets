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
  CustomDialogController_with_backgroundColor_radius,
  CustomDialogController_with_size_inBuilder
} from '../../../../common/CustomDialogController'
import { MyComponent } from '../../../../common/MyComponent';

class SetParam {
  public title?: string
  public func?: () => void
}

@Entry
@Component
struct CustomDialogTestLevel0_0 {
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
  private setsGridCount: SetParam[] = [
    {
      title: 'Count:-3', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: -3,
      })

      this.toastInfo = 'gridCount： -3, 实际绘制gridCount:4'
    }
    },
    {
      title: 'Count:0', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 0,
      })

      this.toastInfo = 'gridCount: 0, 实际不绘制'
    }
    },
    {
      title: 'Count:2', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 2,
      })

      this.toastInfo = 'gridCount: 2'
    }
    },
    {
      title: 'Count:4', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 4,
      })

      this.toastInfo = 'gridCount: 4'
    }
    },
    {
      title: 'Count:6', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 6,
      })

      this.toastInfo = 'gridCount: 6, NOH竖屏绘制为gridCount:4'
    }
    },
    {
      title: 'Count:10', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 10,
      })

      this.toastInfo = 'gridCount: 10, NOH竖屏绘制为gridCount:4'
    }
    },
    {
      title: 'Count:UN', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: undefined,
      })

      this.toastInfo = 'gridCount: undefined, NOH竖屏绘制为gridCount:4'
    }
    },

  ]
  private setsCustomStyle: SetParam[] = [
    {
      title: 'Style:Y,CT:2', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 2,
        customStyle: true,
      })

      this.toastInfo = 'customStyle:true; gridCount:2; builder: no size  实际绘制：屏幕宽度'
    }
    },
    {
      title: 'Style:N,CT:2', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 2,
        customStyle: false,
      })

      this.toastInfo = 'customStyle:false; gridCount:2; builder: no size  实际绘制：gridCount:2'
    }
    },
    {
      title: 'Style:Y,CT:4', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 4,
        customStyle: true,
        cornerRadius: 10,
      })

      this.toastInfo = 'customStyle:true; cornerRadius:10; builder: no borderRadius  实际绘制:直角'
    }
    },
    {
      title: 'Style:N,CT:4', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        gridCount: 4,
        customStyle: false,
        cornerRadius: 10,
      })

      this.toastInfo = 'customStyle:false; cornerRadius:10; builder: no borderRadius  实际绘制:R10'
    }
    },
    {
      title: 'Style:Y,builder', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
          radius: 30,
          backgroundColorBuilder: Color.Pink

        }),
        gridCount: 4,
        customStyle: true,
        cornerRadius: 10,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:true, 绘制builder的设置'
    }
    },
    {
      title: 'Style:N,builder', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
          radius: 30,
          backgroundColorBuilder: Color.Pink

        }),
        gridCount: 4,
        customStyle: false,
        cornerRadius: 10,
        backgroundColor: Color.Orange
      })

      this.toastInfo = ' customStyle:false, builder和弹窗的设置一起绘制'
    }
    },
    {
      title: 'Style:Y,color', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
          radius: 30,
        }),
        gridCount: 4,
        customStyle: true,
        cornerRadius: 10,
        backgroundColor: Color.Orange
      })

      this.toastInfo = ' customStyle:true, builder不设置背景色， 绘制为透明色 '
    }
    },
    {
      title: 'Style:N,color', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
          radius: 30,
        }),
        gridCount: 4,
        customStyle: false,
        cornerRadius: 10,
        backgroundColor: Color.Orange
      })

      this.toastInfo = ' customStyle:false, builder不设置背景色，绘制弹窗设置的橙色'
    }
    },

    {
      title: 'cStyle:Y,Size_1', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '80%',
          heightBuilder: '100%'
        }),
        gridCount: 4,
        customStyle: true,

        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:true, builder设置width:`80%`对比gridCount：4; 设置height:`100%`验证弹窗高度限制90% '
    }
    },
    {
      title: 'cStyle:Y,Size_2', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '80%',
          heightBuilder: '120%'
        }),
        gridCount: 4,
        customStyle: true,

        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:true, builder设置width:`80%`对比gridCount：4; 设置height:`120%`验证弹窗高度限制90% '
    }
    },
    {
      title: 'cStyle:Y,Size_3', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '120%',
          heightBuilder: '80%'
        }),
        gridCount: 4,
        customStyle: true,

        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:true, builder设置width:`120%`对比gridCount：4; 设置height:`80%` '
    }
    },
    {
      title: 'cStyle:Y,Size_4', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '75%',
          heightBuilder: '80%'
        }),
        gridCount: 4,
        customStyle: true,

        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:true, builder设置width:`80%`对比gridCount：4; 设置height:`80%` '
    }
    },
    {
      title: 'cStyle:N,Size_1', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '80%',
          heightBuilder: '100%'
        }),
        gridCount: 4,
        customStyle: false,
        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:false, builder设置width:`80%`,设置height:`100%` '
    }
    },
    {
      title: 'cStyle:N,Size_2', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '80%',
          heightBuilder: '200%'
        }),
        gridCount: 4,
        customStyle: false,
        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:false, builder设置width:`80%`,设置height:`200%` '
    }
    },
    {
      title: 'cStyle:N,Size_3', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '120%',
          heightBuilder: '100%'
        }),
        gridCount: 4,
        customStyle: false,
        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:false, builder设置width:`120%`,设置height:`100%` '
    }
    },
    {
      title: 'cStyle:N,Size_4', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '80%',
          heightBuilder: '50%'
        }),
        gridCount: 4,
        customStyle: false,
        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = 'customStyle:false, builder设置width:`80%`,设置height:`50%` '
    }
    },
    {
      title: 'cStyle: UN', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '80%',
          heightBuilder: '100%'
        }),
        gridCount: 4,
        customStyle: undefined,
        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })

      this.toastInfo = '验证弹窗的customStyle:undefined, builder设置width:`80%`,设置height:`100%` '
    }
    },
    {
      title: 'cStyle:N, wClip', func: () => {
      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_size_inBuilder({
          cancel: this.onCancel,
          confirm: this.onAccept,
          widthBuilder: '60%',
          heightBuilder: '50%',
          widthBuilderText: '200%'
        }),
        gridCount: 4,
        customStyle: undefined,
        alignment: DialogAlignment.Bottom,
        backgroundColor: Color.Orange
      })
      this.toastInfo = '验证弹窗width的剪裁：customStyle:undefined, builder设置width:`60%`,设置height:`50%` '
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

      Text('验证自定义弹窗：customStyle, gridCount功能:')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10, top: 10 })

      Text('gridCount参数切换：')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Row({ space: 2 }) {
        ForEach(this.setsGridCount, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
        }, (item: SetParam) => item.title)
      }

      Text('customStyle参数切换：')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({ left: 10 })

      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(this.setsCustomStyle, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
            .margin({ top: 5, bottom: 5 })
            .width('25%')
        }, (item: SetParam) => item.title)
      }
      .width('90%')

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