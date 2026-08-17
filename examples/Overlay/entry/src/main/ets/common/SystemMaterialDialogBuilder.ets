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

@CustomDialog
export struct SystemMaterialDialogBasic {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  styleName: string = 'REGULAR'

  build() {
    Column({ space: 10 }) {
      Text('SystemMaterial 弹窗')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
      Text('当前材质样式: ' + this.styleName)
        .fontSize(16)
        .fontColor(0x666666)
        .margin({ bottom: 8 })
      Text('此弹窗使用 systemMaterial 接口设置沉浸式材质效果，弹窗背景将呈现系统级材质模糊与光影。')
        .fontSize(14)
        .fontColor(0x999999)
        .margin({ left: 16, right: 16 })
      Divider().margin({ top: 8, bottom: 8 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确认')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 16 })
    }
    .width('80%')
    .padding({ top: 10, bottom: 10 })
  }
}

@CustomDialog
export struct SystemMaterialDialogWithColor {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  materialColorValue: number = 0x80FFFFFF
  colorDesc: string = '半透明白'

  build() {
    Column({ space: 10 }) {
      Text('材质颜色弹窗')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
      Text('材质颜色: ' + this.colorDesc)
        .fontSize(16)
        .fontColor(0x666666)
        .margin({ bottom: 8 })
      Row({ space: 12 }) {
        Text('色值:')
          .fontSize(14)
        Text('0x' + this.materialColorValue.toString(16).toUpperCase().padStart(8, '0'))
          .fontSize(14)
          .fontColor(0x317aff)
      }.margin({ bottom: 12 })
      Text('通过 ImmersiveOptions.materialColor 设置材质层颜色，影响材质的视觉呈现。')
        .fontSize(13)
        .fontColor(0x999999)
        .margin({ left: 16, right: 16 })
      Divider().margin({ top: 8, bottom: 8 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确认')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 16 })
    }
    .width('80%')
    .padding({ top: 10, bottom: 10 })
  }
}

@CustomDialog
export struct SystemMaterialDialogWithShadow {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  applyShadow: boolean = true
  shadowDesc: string = '应用材质阴影'

  build() {
    Column({ space: 10 }) {
      Text('材质阴影弹窗')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
      Text('阴影设置: ' + this.shadowDesc)
        .fontSize(16)
        .fontColor(0x666666)
        .margin({ bottom: 8 })
      Text('applyShadow 为 true 时使用材质自带阴影效果，优先级高于通用 shadow 属性。')
        .fontSize(13)
        .fontColor(0x999999)
        .margin({ left: 16, right: 16 })
      Divider().margin({ top: 8, bottom: 8 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确认')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 16 })
    }
    .width('80%')
    .padding({ top: 10, bottom: 10 })
  }
}

@CustomDialog
export struct SystemMaterialDialogWithLightEffect {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  lightColorValue: number = 0xFFFFFFFF
  lightDesc: string = '白色光效'

  build() {
    Column({ space: 10 }) {
      Text('材质光效弹窗')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
      Text('光效设置: ' + this.lightDesc)
        .fontSize(16)
        .fontColor(0x666666)
        .margin({ bottom: 8 })
      Row({ space: 12 }) {
        Text('光效色值:')
          .fontSize(14)
        Text('0x' + this.lightColorValue.toString(16).toUpperCase().padStart(8, '0'))
          .fontSize(14)
          .fontColor(0x317aff)
      }.margin({ bottom: 12 })
      Text('通过 LightEffectOptions.color 设置材质边缘光效颜色，传 null 可关闭光效。')
        .fontSize(13)
        .fontColor(0x999999)
        .margin({ left: 16, right: 16 })
      Divider().margin({ top: 8, bottom: 8 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确认')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 16 })
    }
    .width('80%')
    .padding({ top: 10, bottom: 10 })
  }
}

@CustomDialog
export struct SystemMaterialDialogInteractive {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  interactiveValue: boolean = true
  interactiveDesc: string = '可交互'

  build() {
    Column({ space: 10 }) {
      Text('材质交互弹窗')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
      Text('交互设置: ' + this.interactiveDesc)
        .fontSize(16)
        .fontColor(0x666666)
        .margin({ bottom: 8 })
      Text('interactive 为 true 时材质层可交互，为 false 时材质层不交互。未设置时跟随组件行为。')
        .fontSize(13)
        .fontColor(0x999999)
        .margin({ left: 16, right: 16 })
      Divider().margin({ top: 8, bottom: 8 })
      TextInput({ placeholder: '尝试在此输入验证交互' })
        .height(48)
        .width('90%')
        .margin({ bottom: 12 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确认')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 16 })
    }
    .width('80%')
    .padding({ top: 10, bottom: 10 })
  }
}

@CustomDialog
export struct SystemMaterialDialogCombined {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  configDesc: string = '组合配置'

  build() {
    Column({ space: 10 }) {
      Text('SystemMaterial 组合弹窗')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
      Text('配置: ' + this.configDesc)
        .fontSize(16)
        .fontColor(0x666666)
        .margin({ bottom: 8 })
      Column({ space: 6 }) {
        Text('1. systemMaterial 指定沉浸式材质样式')
          .fontSize(13)
          .fontColor(0x999999)
        Text('2. backgroundColor 与材质颜色叠加')
          .fontSize(13)
          .fontColor(0x999999)
        Text('3. cornerRadius 设置弹窗圆角')
          .fontSize(13)
          .fontColor(0x999999)
        Text('4. shadow 通用阴影与材质阴影对比')
          .fontSize(13)
          .fontColor(0x999999)
        Text('5. alignment 控制弹窗位置')
          .fontSize(13)
          .fontColor(0x999999)
      }.margin({ left: 16, right: 16, bottom: 12 })
      Divider().margin({ top: 8, bottom: 8 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确认')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 16 })
    }
    .width('80%')
    .padding({ top: 10, bottom: 10 })
  }
}

export class SystemMaterialFactory {
  static createUltraThin(): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: uiMaterial.ImmersiveStyle.ULTRA_THIN,
    })
  }

  static createThin(): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: uiMaterial.ImmersiveStyle.THIN,
    })
  }

  static createRegular(): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: uiMaterial.ImmersiveStyle.REGULAR,
    })
  }

  static createThick(): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: uiMaterial.ImmersiveStyle.THICK,
    })
  }

  static createUltraThick(): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: uiMaterial.ImmersiveStyle.ULTRA_THICK,
    })
  }

  static createWithColor(style: uiMaterial.ImmersiveStyle, color: number): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: style,
      materialColor: color,
    })
  }

  static createWithShadow(style: uiMaterial.ImmersiveStyle, applyShadow: boolean): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: style,
      applyShadow: applyShadow,
    })
  }

  static createWithInteractive(style: uiMaterial.ImmersiveStyle, interactive: boolean): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: style,
      interactive: interactive,
    })
  }

  static createWithLightEffect(style: uiMaterial.ImmersiveStyle, lightColor: number): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: style,
      lightEffect: { color: lightColor },
    })
  }

  static createWithNoLightEffect(style: uiMaterial.ImmersiveStyle): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: style,
      lightEffect: null,
    })
  }

  static createFull(style: uiMaterial.ImmersiveStyle, color: number, applyShadow: boolean,
    interactive: boolean, lightColor: number): uiMaterial.ImmersiveMaterial {
    return new uiMaterial.ImmersiveMaterial({
      style: style,
      materialColor: color,
      applyShadow: applyShadow,
      interactive: interactive,
      lightEffect: { color: lightColor },
    })
  }
}
