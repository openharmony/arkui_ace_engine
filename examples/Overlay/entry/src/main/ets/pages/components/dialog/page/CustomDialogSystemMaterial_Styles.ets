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

import uiMaterial from '@ohos.arkui.uiMaterial';
import { MyComponent } from '../../../../common/MyComponent'
import { SystemMaterialDialogBasic, SystemMaterialFactory } from '../../../../common/SystemMaterialDialogBuilder'

class SetParam {
  public title?: string
  public func?: () => void
}

@Entry
@Component
struct CustomDialogSystemMaterial_Styles {
  scroller: Scroller = new Scroller()
  @State toastInfo: string = '请选择材质样式后打开弹窗'
  @State currentStyleName: string = '未设置'
  private styleIndex: number = 2

  private dialogController: CustomDialogController | null = new CustomDialogController({
    builder: SystemMaterialDialogBasic({
      cancel: this.onCancel,
      confirm: this.onAccept,
      styleName: 'REGULAR',
    }),
    systemMaterial: SystemMaterialFactory.createRegular(),
    alignment: DialogAlignment.Center,
  })

  private setsStyle: SetParam[] = [
    {
      title: 'ULTRA_THIN', func: () => {
        this.currentStyleName = 'ULTRA_THIN'
        this.styleIndex = 0
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'ULTRA_THIN',
          }),
          systemMaterial: SystemMaterialFactory.createUltraThin(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '材质样式: ULTRA_THIN(超薄)，材质层极薄，透明效果非常强'
      }
    },
    {
      title: 'THIN', func: () => {
        this.currentStyleName = 'THIN'
        this.styleIndex = 1
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'THIN',
          }),
          systemMaterial: SystemMaterialFactory.createThin(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '材质样式: THIN(薄)，材质层较薄，透明效果强'
      }
    },
    {
      title: 'REGULAR', func: () => {
        this.currentStyleName = 'REGULAR'
        this.styleIndex = 2
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'REGULAR',
          }),
          systemMaterial: SystemMaterialFactory.createRegular(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '材质样式: REGULAR(常规)，材质层标准厚度，视觉效果均衡'
      }
    },
    {
      title: 'THICK', func: () => {
        this.currentStyleName = 'THICK'
        this.styleIndex = 3
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'THICK',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '材质样式: THICK(厚)，模糊效果较强'
      }
    },
    {
      title: 'ULTRA_THICK', func: () => {
        this.currentStyleName = 'ULTRA_THICK'
        this.styleIndex = 4
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'ULTRA_THICK',
          }),
          systemMaterial: SystemMaterialFactory.createUltraThick(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '材质样式: ULTRA_THICK(超厚)，材质层最厚，模糊效果最强'
      }
    },
  ]

  private setsAlignment: SetParam[] = [
    {
      title: 'Top+ULTRA_THIN', func: () => {
        this.currentStyleName = 'ULTRA_THIN'
        this.styleIndex = 0
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'ULTRA_THIN',
          }),
          systemMaterial: SystemMaterialFactory.createUltraThin(),
          alignment: DialogAlignment.Top,
        })
        this.toastInfo = 'alignment: Top, 材质样式: ULTRA_THIN，弹窗显示在顶部'
      }
    },
    {
      title: 'Center+THIN', func: () => {
        this.currentStyleName = 'THIN'
        this.styleIndex = 1
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'THIN',
          }),
          systemMaterial: SystemMaterialFactory.createThin(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'alignment: Center, 材质样式: THIN，弹窗居中显示'
      }
    },
    {
      title: 'Default+REGULAR', func: () => {
        this.currentStyleName = 'REGULAR'
        this.styleIndex = 2
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'REGULAR',
          }),
          systemMaterial: SystemMaterialFactory.createRegular(),
        })
        this.toastInfo = 'alignment: 默认(Center), 材质样式: REGULAR，不设置alignment使用默认值'
      }
    },
    {
      title: 'Top+Offset', func: () => {
        this.currentStyleName = 'ULTRA_THICK'
        this.styleIndex = 4
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'ULTRA_THICK',
          }),
          systemMaterial: SystemMaterialFactory.createUltraThick(),
          alignment: DialogAlignment.Top,
          offset: { dx: 0, dy: 100 },
        })
        this.toastInfo = 'alignment: Top, offset: dy=100, 材质: ULTRA_THICK，弹窗顶部偏移100'
      }
    },
  ]

  private setsCustomStyle: SetParam[] = [
    {
      title: 'customStyle:Y', func: () => {
        this.currentStyleName = 'REGULAR'
        this.styleIndex = 2
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'REGULAR',
          }),
          systemMaterial: SystemMaterialFactory.createRegular(),
          customStyle: true,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'customStyle: true, systemMaterial 仍生效，builder 自定义布局生效'
      }
    },
    {
      title: 'customStyle:N', func: () => {
        this.currentStyleName = 'REGULAR'
        this.styleIndex = 2
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'REGULAR',
          }),
          systemMaterial: SystemMaterialFactory.createRegular(),
          customStyle: false,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'customStyle: false, systemMaterial 生效，使用弹窗默认布局'
      }
    },
    {
      title: 'NoMaterial', func: () => {
        this.currentStyleName = '无 systemMaterial'
        this.styleIndex = -1
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: '无 systemMaterial',
          }),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '不设置 systemMaterial, 弹窗使用默认背景，无材质效果'
      }
    },
    {
      title: 'Material:UN', func: () => {
        this.currentStyleName = 'systemMaterial: undefined'
        this.styleIndex = -1
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogBasic({
            cancel: this.onCancel,
            confirm: this.onAccept,
            styleName: 'systemMaterial: undefined',
          }),
          systemMaterial: undefined,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: undefined, 等同不设置，弹窗无材质效果'
      }
    },
  ]

  aboutToDisappear() {
    this.dialogController = null
  }

  onCancel() {
    console.info('SystemMaterial Styles: onCancel callback')
  }

  onAccept() {
    console.info('SystemMaterial Styles: onAccept callback')
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 10 }) {
        Text('验证 CustomDialog systemMaterial 沉浸式材质样式:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10, top: 10 })

        Text('材质样式切换 (ImmersiveStyle):')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Row({ space: 2 }) {
          ForEach(this.setsStyle, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('材质样式 + 弹窗位置 (alignment):')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsAlignment, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('30%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Text('customStyle 与 systemMaterial 组合:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsCustomStyle, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('30%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Button('打开 systemMaterial 弹窗')
          .width('80%')
          .height(44)
          .margin({ top: 16 })
          .backgroundColor(0x317aff)
          .onClick(() => {
            if (this.dialogController != null) {
              this.dialogController!.open()
            }
          })

        Text('配置信息显示: ' + ' \n ' + '    ' + this.toastInfo)
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10, bottom: 20 })
      }.width('100%').margin({ top: 5 })
    }
    .scrollBar(BarState.Auto)
  }
}
