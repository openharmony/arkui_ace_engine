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
  SystemMaterialDialogWithColor,
  SystemMaterialDialogWithShadow,
  SystemMaterialDialogWithLightEffect,
  SystemMaterialDialogInteractive,
  SystemMaterialFactory,
} from '../../../../common/SystemMaterialDialogBuilder'

class SetParam {
  public title?: string
  public func?: () => void
}

@Entry
@Component
struct CustomDialogSystemMaterial_Properties {
  scroller: Scroller = new Scroller()
  @State toastInfo: string = '请选择材质属性后打开弹窗'
  @State currentDesc: string = '未设置'

  private dialogController: CustomDialogController | null = new CustomDialogController({
    builder: SystemMaterialDialogWithColor({
      cancel: this.onCancel,
      confirm: this.onAccept,
      materialColorValue: 0x80FFFFFF,
      colorDesc: '半透明白',
    }),
    systemMaterial: SystemMaterialFactory.createWithColor(uiMaterial.ImmersiveStyle.REGULAR, 0x80FFFFFF),
    alignment: DialogAlignment.Center,
  })

  private setsMaterialColor: SetParam[] = [
    {
      title: 'Color:半透明白', func: () => {
        this.currentDesc = 'materialColor: 0x80FFFFFF (半透明白)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithColor({
            cancel: this.onCancel,
            confirm: this.onAccept,
            materialColorValue: 0x80FFFFFF,
            colorDesc: '半透明白',
          }),
          systemMaterial: SystemMaterialFactory.createWithColor(uiMaterial.ImmersiveStyle.THICK, 0x80FFFFFF),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'materialColor: 0x80FFFFFF, 材质层颜色为半透明白色，叠加模糊效果'
      }
    },
    {
      title: 'Color:不透明白', func: () => {
        this.currentDesc = 'materialColor: 0xFFFFFFFF (不透明白)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithColor({
            cancel: this.onCancel,
            confirm: this.onAccept,
            materialColorValue: 0xFFFFFFFF,
            colorDesc: '不透明白',
          }),
          systemMaterial: SystemMaterialFactory.createWithColor(uiMaterial.ImmersiveStyle.THICK, 0xFFFFFFFF),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'materialColor: 0xFFFFFFFF, 材质层颜色为不透明白色'
      }
    },
    {
      title: 'Color:半透明黑', func: () => {
        this.currentDesc = 'materialColor: 0x80000000 (半透明黑)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithColor({
            cancel: this.onCancel,
            confirm: this.onAccept,
            materialColorValue: 0x80000000,
            colorDesc: '半透明黑',
          }),
          systemMaterial: SystemMaterialFactory.createWithColor(uiMaterial.ImmersiveStyle.THICK, 0x80000000),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'materialColor: 0x80000000, 材质层颜色为半透明黑色，深色材质效果'
      }
    },
    {
      title: 'Color:透明', func: () => {
        this.currentDesc = 'materialColor: 0x00000000 (透明)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithColor({
            cancel: this.onCancel,
            confirm: this.onAccept,
            materialColorValue: 0x00000000,
            colorDesc: '透明',
          }),
          systemMaterial: SystemMaterialFactory.createWithColor(uiMaterial.ImmersiveStyle.THICK, 0x00000000),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'materialColor: 0x00000000, 材质层颜色为透明，仅显示模糊效果'
      }
    },
    {
      title: 'Color:不设置', func: () => {
        this.currentDesc = 'materialColor: 未设置(默认)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithColor({
            cancel: this.onCancel,
            confirm: this.onAccept,
            materialColorValue: 0xFFFFFFFF,
            colorDesc: '未设置(跟随等级默认)',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'materialColor: 未设置, 精致/柔和等级下材质颜色为透明，流畅等级使用默认背景色'
      }
    },
  ]

  private setsApplyShadow: SetParam[] = [
    {
      title: 'Shadow:Y', func: () => {
        this.currentDesc = 'applyShadow: true (应用材质阴影)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithShadow({
            cancel: this.onCancel,
            confirm: this.onAccept,
            applyShadow: true,
            shadowDesc: '应用材质阴影',
          }),
          systemMaterial: SystemMaterialFactory.createWithShadow(uiMaterial.ImmersiveStyle.THICK, true),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'applyShadow: true, 使用材质自带阴影效果，优先级高于通用 shadow 属性'
      }
    },
    {
      title: 'Shadow:N', func: () => {
        this.currentDesc = 'applyShadow: false (不应用材质阴影)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithShadow({
            cancel: this.onCancel,
            confirm: this.onAccept,
            applyShadow: false,
            shadowDesc: '不应用材质阴影',
          }),
          systemMaterial: SystemMaterialFactory.createWithShadow(uiMaterial.ImmersiveStyle.THICK, false),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'applyShadow: false, 材质无阴影效果，可使用通用 shadow 属性设置阴影'
      }
    },
    {
      title: 'Shadow:Y+ULTRA_THIN', func: () => {
        this.currentDesc = 'applyShadow: true + ULTRA_THIN'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithShadow({
            cancel: this.onCancel,
            confirm: this.onAccept,
            applyShadow: true,
            shadowDesc: 'ULTRA_THIN + 材质阴影',
          }),
          systemMaterial: SystemMaterialFactory.createWithShadow(uiMaterial.ImmersiveStyle.ULTRA_THIN, true),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'applyShadow: true, style: ULTRA_THIN, 超薄材质 + 材质阴影'
      }
    },
    {
      title: 'Shadow:N+ULTRA_THICK', func: () => {
        this.currentDesc = 'applyShadow: false + ULTRA_THICK'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithShadow({
            cancel: this.onCancel,
            confirm: this.onAccept,
            applyShadow: false,
            shadowDesc: 'ULTRA_THICK + 无材质阴影',
          }),
          systemMaterial: SystemMaterialFactory.createWithShadow(uiMaterial.ImmersiveStyle.ULTRA_THICK, false),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'applyShadow: false, style: ULTRA_THICK, 超厚材质但无材质阴影'
      }
    },
  ]

  private setsInteractive: SetParam[] = [
    {
      title: 'Interactive:Y', func: () => {
        this.currentDesc = 'interactive: true (可交互)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogInteractive({
            cancel: this.onCancel,
            confirm: this.onAccept,
            interactiveValue: true,
            interactiveDesc: '可交互',
          }),
          systemMaterial: SystemMaterialFactory.createWithInteractive(uiMaterial.ImmersiveStyle.REGULAR, true),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'interactive: true, 材质层可交互，弹窗内组件可正常响应'
      }
    },
    {
      title: 'Interactive:N', func: () => {
        this.currentDesc = 'interactive: false (不可交互)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogInteractive({
            cancel: this.onCancel,
            confirm: this.onAccept,
            interactiveValue: false,
            interactiveDesc: '不可交互',
          }),
          systemMaterial: SystemMaterialFactory.createWithInteractive(uiMaterial.ImmersiveStyle.REGULAR, false),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'interactive: false, 材质层不可交互，材质层不响应触摸事件'
      }
    },
    {
      title: 'Interactive:Y+THICK', func: () => {
        this.currentDesc = 'interactive: true + THICK'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogInteractive({
            cancel: this.onCancel,
            confirm: this.onAccept,
            interactiveValue: true,
            interactiveDesc: 'THICK + 可交互',
          }),
          systemMaterial: SystemMaterialFactory.createWithInteractive(uiMaterial.ImmersiveStyle.THICK, true),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'interactive: true, style: THICK, 厚材质 + 可交互'
      }
    },
    {
      title: 'Interactive:N+THIN', func: () => {
        this.currentDesc = 'interactive: false + THIN'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogInteractive({
            cancel: this.onCancel,
            confirm: this.onAccept,
            interactiveValue: false,
            interactiveDesc: 'THIN + 不可交互',
          }),
          systemMaterial: SystemMaterialFactory.createWithInteractive(uiMaterial.ImmersiveStyle.THIN, false),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'interactive: false, style: THIN, 薄材质 + 不可交互'
      }
    },
  ]

  private setsLightEffect: SetParam[] = [
    {
      title: 'Light:白色', func: () => {
        this.currentDesc = 'lightEffect.color: 0xFFFFFFFF (白色)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithLightEffect({
            cancel: this.onCancel,
            confirm: this.onAccept,
            lightColorValue: 0xFFFFFFFF,
            lightDesc: '白色光效',
          }),
          systemMaterial: SystemMaterialFactory.createWithLightEffect(uiMaterial.ImmersiveStyle.THICK, 0xFFFFFFFF),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'lightEffect: { color: 0xFFFFFFFF }, 白色边缘光效'
      }
    },
    {
      title: 'Light:黄色', func: () => {
        this.currentDesc = 'lightEffect.color: 0xFFFF0000 (红色)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithLightEffect({
            cancel: this.onCancel,
            confirm: this.onAccept,
            lightColorValue: 0xFFFF0000,
            lightDesc: '红色光效',
          }),
          systemMaterial: SystemMaterialFactory.createWithLightEffect(uiMaterial.ImmersiveStyle.THICK, 0xFFFF0000),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'lightEffect: { color: 0xFFFF0000 }, 红色边缘光效'
      }
    },
    {
      title: 'Light:蓝色', func: () => {
        this.currentDesc = 'lightEffect.color: 0xFF0000FF (蓝色)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithLightEffect({
            cancel: this.onCancel,
            confirm: this.onAccept,
            lightColorValue: 0xFF0000FF,
            lightDesc: '蓝色光效',
          }),
          systemMaterial: SystemMaterialFactory.createWithLightEffect(uiMaterial.ImmersiveStyle.THICK, 0xFF0000FF),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'lightEffect: { color: 0xFF0000FF }, 蓝色边缘光效'
      }
    },
    {
      title: 'Light:半透明白', func: () => {
        this.currentDesc = 'lightEffect.color: 0x80FFFFFF (半透明白)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithLightEffect({
            cancel: this.onCancel,
            confirm: this.onAccept,
            lightColorValue: 0x80FFFFFF,
            lightDesc: '半透明白光效',
          }),
          systemMaterial: SystemMaterialFactory.createWithLightEffect(uiMaterial.ImmersiveStyle.THICK, 0x80FFFFFF),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'lightEffect: { color: 0x80FFFFFF }, 半透明白色光效'
      }
    },
    {
      title: 'Light:关闭(null)', func: () => {
        this.currentDesc = 'lightEffect: null (关闭光效)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithLightEffect({
            cancel: this.onCancel,
            confirm: this.onAccept,
            lightColorValue: 0x00000000,
            lightDesc: '光效已关闭(null)',
          }),
          systemMaterial: SystemMaterialFactory.createWithNoLightEffect(uiMaterial.ImmersiveStyle.THICK),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'lightEffect: null, 关闭边缘光效，材质无边缘光效'
      }
    },
    {
      title: 'Light:未设置', func: () => {
        this.currentDesc = 'lightEffect: 未设置(跟随组件)'
        this.dialogController = new CustomDialogController({
          builder: SystemMaterialDialogWithLightEffect({
            cancel: this.onCancel,
            confirm: this.onAccept,
            lightColorValue: 0xFFFFFFFF,
            lightDesc: '未设置(跟随组件)',
          }),
          systemMaterial: SystemMaterialFactory.createThick(),
          alignment: DialogAlignment.Center,
        })
        this.toastInfo = 'lightEffect: 未设置, 跟随组件默认行为'
      }
    },
  ]

  aboutToDisappear() {
    this.dialogController = null
  }

  onCancel() {
    console.info('SystemMaterial Properties: onCancel callback')
  }

  onAccept() {
    console.info('SystemMaterial Properties: onAccept callback')
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 10 }) {
        Text('验证 CustomDialog systemMaterial 材质属性:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10, top: 10 })

        Text('材质颜色 (materialColor) 切换:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsMaterialColor, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('25%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Text('材质阴影 (applyShadow) 切换:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsApplyShadow, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('30%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Text('材质交互 (interactive) 切换:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsInteractive, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('30%')
          }, (item: SetParam) => item.title)
        }.width('90%')

        Text('材质光效 (lightEffect) 切换:')
          .fontSize(9)
          .fontColor(0xCCCCCC)
          .width('100%')
          .margin({ left: 10 })

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.setsLightEffect, (item: SetParam) => {
            MyComponent({ title: item.title, func: item.func })
              .margin({ top: 5, bottom: 5 })
              .width('25%')
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
