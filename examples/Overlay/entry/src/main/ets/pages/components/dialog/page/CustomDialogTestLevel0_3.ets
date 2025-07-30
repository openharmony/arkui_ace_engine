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
 
import {CustomDialogController_with_backgroundColor_radius} from '../../../../common/CustomDialogController'

import { MyComponent } from '../../../../common/MyComponent';

class SetParam{
  public title?:string
  public func: () => void=()=>{}
}

@Entry
@Component
struct CustomDialogTestLevel0_3 {

  @State toastInfo: string = '初始设置'
  @State calcIndex: number = -1
  private  index: number = -1
  private  lastIndex: number = -1

  @State inputValue: string = 'customDialog: click me '

  dialogController: CustomDialogController|null = new CustomDialogController({
    builder: CustomDialogController_with_backgroundColor_radius({
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),
    backgroundColor: Color.Pink,
    cornerRadius: 24,
  })

  private setsAlignment: SetParam[] = [
    { title: 'Top', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Top,
        offset: {dx:0, dy:10},

      })
      this.toastInfo = '1. Alignment: Top'
    }
    },
    { title: 'Center', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Center,
        offset: undefined,

      })
      this.toastInfo = '2. Alignment: Center'
    }
    },
    { title: 'Bottom', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Bottom,
        offset: {dx:'0', dy:'-10'},
      })
      this.toastInfo = '3. Alignment: Bottom'
    }
    },
    { title: 'Default', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Default,
        offset: {dx:'0pixel', dy:'-10pixel'},
      })
      this.toastInfo = '4. Alignment: Default'
    }
    },
    { title: 'TopEnd', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment:  DialogAlignment.TopEnd,
        offset: {dx:-20, dy:10},
      })
      this.toastInfo = '5. Alignment: TopEnd'
    }
    },
    { title: 'TopStart', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.TopStart,
        offset: {dx:20, dy:10},
      })
      this.toastInfo = '6. Alignment: TopStart'
    }
    },
    { title: 'BottomEnd', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.BottomEnd,
        offset: {dx:'-20', dy:'-10vp'},
      })
      this.toastInfo = '7. Alignment: BottomEnd'
    }
    },
    { title: 'BottomStart', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.BottomStart,
        offset: {dx:'20', dy:'-30px'},
      })
      this.toastInfo = '8. Alignment: BottomStart'
    }
    },
    { title: 'CenterStart', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.CenterStart,
        offset: {dx:$r('app.float.float_20'), dy:$r('app.float.float_o')},
      })
      this.toastInfo = '9. Alignment: CenterStart'
    }
    },
    { title: 'CenterEnd', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.CenterEnd,
        offset: {dx:$r('app.string.Length_minus20'), dy:$r('app.string.Length_0')},
      })
      this.toastInfo = '10. Alignment: CenterEnd'
    }
    },
    { title: 'undefined', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: undefined,
        offset: undefined,
      })
      this.toastInfo = '11. Alignment: undefined'
    }
    },
]

  private setsMask: SetParam[] = [
    { title: 'mask_1', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Default,
        offset: {dx:0, dy:0},
        maskColor: Color.Pink,
        maskRect:{
          x:$r('app.float.float_0'),
          y:$r('app.float.float_0'),
          width: $r('app.string.Length_100percent'),
          height: $r('app.string.Length_100percent')
        },
      })
      this.toastInfo = '蒙版大小100%, 偏移x0y0; 弹窗default对齐，偏移x0y0'
    }
    },
    { title: 'mask_2', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.TopStart,
        offset: {dx:30, dy:30},
        maskColor: undefined,
        maskRect:{
          x: 30,
          y: 30,
          width: '100%',
          height: '100%'
        },
      })
      this.toastInfo = '蒙版大小100%, 偏移x30y30; 弹窗左上对齐，偏移x30y30'
    }
    },
    { title: 'mask_3', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.BottomEnd,
        offset: {dx:-30, dy:-30},
        maskColor: 'rgb(255, 192, 203)',
        maskRect:{
          x:$r('app.float.float_minus30'),
          y:$r('app.float.float_minus30'),
          width: '100%',
          height: '100%'
        },
      })
      this.toastInfo = '蒙版大小100%, 偏移x-30y-30; 弹窗右下对齐，偏移x-30y-30'
    }
    },
    { title: 'mask_4', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.BottomEnd,
        offset: {dx:-30, dy:-30},
        maskRect:{
          x: '-30',
          y: '-30',
          width: 360,
          height: 780
        },
      })
      this.toastInfo = '蒙版大小360/780, 偏移x-30y-30; 弹窗右下对齐，偏移x-30y-30'
    }
    },
    { title: 'mask_5', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.TopStart,
        offset: {dx:30, dy:30},
        maskColor: 'rgba(255, 192, 203, 1.00)',
        maskRect:{
          x:$r('app.string.Length_30'),
          y:$r('app.string.Length_30'),
          width: $r('app.string.Length_360vp'),
          height: $r('app.string.Length_780vp')
        },
      })
      this.toastInfo = '蒙版大小360vp/780vp, 偏移x30y30; 弹窗左上对齐，偏移x30y30'
    }
    },
    { title: 'mask_6', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.TopStart,
        offset: {dx:30, dy:30},
        maskColor: undefined,
        maskRect:{
          x: '30vp',
          y: '30vp',
          width: '100%',
          height: '100%'
        },
      })
      this.toastInfo = '蒙版大小100%, 偏移x30y30; 弹窗左上对齐，偏移x30y30'
    }
    },
    { title: 'mask_7', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.TopStart,
        offset: {dx:30, dy:30},
        maskColor: '#FFFFC0CB',
        maskRect:{
          x:$r('app.string.Length_90px'),
          y:$r('app.string.Length_90px'),
          width: $r('app.string.Length_100percent'),
          height: $r('app.string.Length_100percent')
        },
      })
      this.toastInfo = '蒙版大小100%, 偏移x90px;y90px; 弹窗左上对齐，偏移x30y30'
    }
    },
    { title: 'mask_8', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Default,
        offset: {dx:'0', dy:'0'},
        maskColor: undefined,
        maskRect:{
          x: '-50%',
          y: '-50%',
          width: '125%',
          height: '125%'
        },
      })
      this.toastInfo = '蒙版大小125%, 偏移x-50%y-50%; 弹窗default对齐，偏移x0y0'
    }
    },
    { title: 'mask_9', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Default,
        offset: {dx:'0', dy:'0'},
        maskColor: 0xffc0cb,
        maskRect:{
          x:$r('app.string.Length_50percent'),
          y:$r('app.string.Length_50percent'),
          width: $r('app.string.Length_100percent'),
          height: $r('app.string.Length_100percent')
        },
      })
      this.toastInfo = '蒙版大小100%, 偏移x50%y50%; 弹窗default对齐，偏移x0y0'
    }
    },
    { title: 'mask_10', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: undefined,
        offset: {dx:0, dy:0},
        maskColor: $r('app.color.Color_pink'),
        maskRect:{
          x: undefined,
          y: undefined,
          width: '75%',
          height: '75%'
        },
      })
      this.toastInfo = '蒙版大小75%, 偏移x0y0; 弹窗undefined对齐，偏移x0y0'
    }
    },
    { title: 'mask_11', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: undefined,
        offset: {dx:0, dy:0},
        maskColor: undefined,
        maskRect:{
          x:$r('app.string.Length_105pix'),
          y:$r('app.string.Length_105pix'),
          width: $r('app.string.Length_100percent'),
          height: $r('app.string.Length_100percent')
        },
      })
      this.toastInfo = '蒙版大小100%, 偏移x105pix;y105pix; 弹窗undefined对齐，偏移x0y0'
    }
    },
  ]

  private setsMaskRectValidSize: SetParam[] = [
    { title: 'width/height: 0 ', func: () => {

    this.dialogController = new CustomDialogController({
      builder: CustomDialogController_with_backgroundColor_radius({
        cancel: this.onCancel,
        confirm: this.onAccept,
      }),
      backgroundColor: Color.Pink,
      cornerRadius: 24,

      alignment: DialogAlignment.Default,
      offset: {dx:0 ,dy:0},
      maskRect:{
        x: 0,
        y: 0,
        width: $r('app.float.float_0'),
        height: $r('app.float.float_0')
      },
    })
    this.toastInfo = '蒙版大小0，不绘制'
  }
  },
    { title: 'width/height: minus ', func: () => {

      this.dialogController = new CustomDialogController({
        builder: CustomDialogController_with_backgroundColor_radius({
          cancel: this.onCancel,
          confirm: this.onAccept,
        }),
        backgroundColor: Color.Pink,
        cornerRadius: 24,

        alignment: DialogAlignment.Default,
        offset: {dx:0 ,dy:0},
        maskRect:{
          x: 0,
          y: 0,
          width: $r('app.string.Length_minus150percent'),
          height: -150
        },
      })
      this.toastInfo = '蒙版大小负值，不绘制'
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
    Column({space:10}) {

      Text('验证自定义弹窗：alignment, offset, mask功能:')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({left:10, top:10})

      Button(this.inputValue)
        .onClick(() => {
          this.dialogController!.open()
        }).backgroundColor(0x317aff)

      Text('alignment参数切换：')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({left:10})

      Flex({ wrap: FlexWrap.Wrap}) {
        ForEach(this.setsAlignment, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
            .margin({top:5, bottom:5})
            .width('25%')
        }, (item: SetParam) => item.title)
      }
      .width('90%')

      Text('mask参数切换：')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({left:10})

      Flex({ wrap: FlexWrap.Wrap}) {
        ForEach(this.setsMask, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
            .margin({top:5, bottom:5})
            .width('25%')
        }, (item: SetParam) => item.title)
      }
      .width('90%')

      Text('验证maskRect的特殊尺寸')
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({left:10})

      Row({ space: 2 }) {
        ForEach(this.setsMaskRectValidSize, (item: SetParam) => {
          MyComponent({ title: item.title, func: item.func })
        }, (item: SetParam) => item.title)
      }

      Text('配置信息显示: ' + ' \n '+
      '    ' + this.toastInfo)
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('100%')
        .margin({left:10})
    }.width('100%').margin({ top: 5 })
  }
}