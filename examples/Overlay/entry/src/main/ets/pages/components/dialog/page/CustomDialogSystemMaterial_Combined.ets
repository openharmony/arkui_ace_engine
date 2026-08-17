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
import {
  SystemMaterialDialogCombined,
  SystemMaterialFactory,
} from '../../../../common/SystemMaterialDialogBuilder'

class SetParam {
  public title?: string
  public func?: () => void
}

@Entry
@Component
struct CustomDialogSystemMaterial_Combined {
  scroller: Scroller = new Scroller()
  @State toastInfo: string = '请选择组合场景后打开弹窗'
  @State currentDesc: string = '未设置'

  private dialogController: CustomDialogController | null = new CustomDialogController({
    builder: SystemMaterialDialogCombined({
      cancel: this.onCancel,
      confirm: this.onAccept,
      configDesc: 'THICK + backgroundColor + cornerRadius',
    }),
    systemMaterial: SystemMaterialFactory.createThick(),
    backgroundColor: 0x80FFFFFF,
    cornerRadius: 20,
    alignment: DialogAlignment.Center,
  })

  private setsBgAndMaterial: SetParam[] = [
    {
      title: 'Mat+bgColor:橙', func: () => {
        this.currentDesc = 'systemMaterial: THICK + backgroundColor: Orange'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + bg:Orange',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          backgroundColor: Color.Orange,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, backgroundColor: Orange, 材质效果与背景色叠加'
      }
    },
    {
      title: 'Mat+bgBlur', func: () => {
        this.currentDesc = 'systemMaterial: THICK + backgroundBlurStyle: Regular'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + bgBlur:Regular',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          backgroundBlurStyle: BlurStyle.Regular,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, backgroundBlurStyle: Regular, 材质与背景模糊叠加'
      }
    },
    {
      title: 'Mat+bgBlur:Thin', func: () => {
        this.currentDesc = 'systemMaterial: THICK + backgroundBlurStyle: Thin'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + bgBlur:Thin',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          backgroundBlurStyle: BlurStyle.Thin,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, backgroundBlurStyle: Thin, 材质与浅色背景模糊叠加'
      }
    },
  ]

  private setsRadiusAndBorder: SetParam[] = [
    {
      title: 'Mat+radius:0', func: () => {
        this.currentDesc = 'systemMaterial: THICK + cornerRadius: 0'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + radius:0',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          cornerRadius: 0,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, cornerRadius: 0, 材质弹窗为直角'
      }
    },
    {
      title: 'Mat+radius:10', func: () => {
        this.currentDesc = 'systemMaterial: THICK + cornerRadius: 10'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + radius:10',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          cornerRadius: 10,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, cornerRadius: 10, 材质弹窗圆角 10'
      }
    },
    {
      title: 'Mat+radius:30', func: () => {
        this.currentDesc = 'systemMaterial: THICK + cornerRadius: 30'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + radius:30',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          cornerRadius: 30,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, cornerRadius: 30, 材质弹窗圆角 30'
      }
    },
    {
      title: 'Mat+border', func: () => {
        this.currentDesc = 'systemMaterial: THICK + borderWidth: 2 + borderColor: Blue'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + border:Blue',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          borderWidth: 2,
          borderColor: Color.Blue,
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, borderWidth: 2, borderColor: Blue, 材质 + 蓝色边框'
      }
    },
    {
      title: 'Mat+borderStyle', func: () => {
        this.currentDesc = 'systemMaterial: THICK + borderStyle: Dashed'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + border:Dashed',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          borderWidth: 2,
          borderColor: Color.Green,
          borderStyle: BorderStyle.Dashed,
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, borderStyle: Dashed, 材质 + 虚线边框'
      }
    },
  ]

  private setsShadowAndSize: SetParam[] = [
    {
      title: 'Mat+shadow通用', func: () => {
        this.currentDesc = 'systemMaterial: THICK + shadow(通用) + applyShadow: false'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + shadow:通用',
          }),
          systemMaterial: SystemMaterialFactory.createWithShadow(uiMaterial.ImmersiveStyle.THICK, false),
          shadow: { radius: 20, color: Color.Black, offsetX: 0, offsetY: 10 },
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'applyShadow: false, 使用通用 shadow 属性, 材质阴影被禁用，通用阴影生效'
      }
    },
    {
      title: 'Mat+shadow材质', func: () => {
        this.currentDesc = 'systemMaterial: THICK + applyShadow: true(材质阴影优先)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + shadow:材质优先',
          }),
          systemMaterial: SystemMaterialFactory.createWithShadow(uiMaterial.ImmersiveStyle.THICK, true),
          shadow: { radius: 20, color: Color.Black, offsetX: 0, offsetY: 10 },
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'applyShadow: true, 材质阴影优先于通用 shadow 属性生效'
      }
    },
    {
      title: 'Mat+height', func: () => {
        this.currentDesc = 'systemMaterial: THICK + height: 50%'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + height:50%',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          height: '50%',
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, height: 50%, 材质弹窗高度 50% 屏幕高度'
      }
    },
    {
      title: 'Mat+size', func: () => {
        this.currentDesc = 'systemMaterial: THICK + width: 70% + height: 40%'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + w:70% h:40%',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          width: '70%',
          height: '40%',
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, width: 70%, height: 40%, 材质弹窗指定尺寸'
      }
    },
    {
      title: 'Mat+maskColor', func: () => {
        this.currentDesc = 'systemMaterial: THICK + maskColor: 半透明黑'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK + mask:半透明黑',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          maskColor: 0x80000000,
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'systemMaterial: THICK, maskColor: 0x80000000, 材质弹窗 + 半透明黑色遮罩'
      }
    },
  ]

  private setsFullConfig: SetParam[] = [
    {
      title: 'Full:薄+白+阴影+光效', func: () => {
        this.currentDesc = '完整配置: THIN + materialColor:白 + applyShadow + lightEffect:白'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THIN+白+阴影+白光效',
          }),
          systemMaterial: SystemMaterialFactory.createFull(
            uiMaterial.ImmersiveStyle.THIN, 0x80FFFFFF, true, true, 0xFFFFFFFF),
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '完整配置: THIN + materialColor:半透明白 + applyShadow:true + lightEffect:白色'
      }
    },
    {
      title: 'Full:厚+蓝+阴影+蓝光', func: () => {
        this.currentDesc = '完整配置: THICK + materialColor:蓝 + applyShadow + lightEffect:蓝'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'THICK+蓝+阴影+蓝光',
          }),
          systemMaterial: SystemMaterialFactory.createFull(
            uiMaterial.ImmersiveStyle.THICK, 0x800000FF, true, true, 0xFF0000FF),
          cornerRadius: 16,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '完整配置: THICK + materialColor:半透明蓝 + applyShadow:true + lightEffect:蓝色'
      }
    },
    {
      title: 'Full:超厚+黑+无阴影', func: () => {
        this.currentDesc = '完整配置: ULTRA_THICK + materialColor:黑 + applyShadow:false + interactive:true'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'ULTRA_THICK+黑+无阴影+可交互',
          }),
          systemMaterial: SystemMaterialFactory.createFull(
            uiMaterial.ImmersiveStyle.ULTRA_THICK, 0x80000000, false, true, 0xFFFFFFFF),
          cornerRadius: 20,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '完整配置: ULTRA_THICK + materialColor:半透明黑 + applyShadow:false + interactive:true'
      }
    },
    {
      title: 'Full:超薄+粉+光效', func: () => {
        this.currentDesc = '完整配置: ULTRA_THIN + materialColor:粉 + lightEffect:红'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogCombined({
            cancel: this.onCancel,
            confirm: this.onAccept,
            configDesc: 'ULTRA_THIN+粉+红光效',
          }),
          systemMaterial: SystemMaterialFactory.createFull(
            uiMaterial.ImmersiveStyle.ULTRA_THIN, 0x80FFC0CB, true, true, 0xFFFF0000),
          cornerRadius: 24,
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = '完整配置: ULTRA_THIN + materialColor:半透明粉 + lightEffect:红色'
      }
    },
  ]

  aboutToDisappear() {
    this.dialogController = null
  }

  onCancel() {
    console.info('SystemMaterial Combined: onCancel callback')
  }

  onAccept() {
    console.info('SystemMaterial Combined: onAccept callback')
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 10 }) {
        Text('验证 CustomDialog systemMaterial 与其他弹窗属性的组合场景:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10, top: 10 })

        Text('材质 + 背景色/背景模糊:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsBgAndMaterial, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('30%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Text('材质 + 圆角/边框:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsRadiusAndBorder, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('30%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Text('材质 + 阴影/尺寸/遮罩:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsShadowAndSize, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('30%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Text('完整材质配置 (样式+颜色+阴影+交互+光效):')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsFullConfig, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('45%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Button('打开 systemMaterial 组合弹窗')
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
