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

/**
 * Image component copyOptions property examples
 */
@Entry
@Component
struct ImageCopyOptionsExample {
  @State currentOption: CopyOptions = CopyOptions.InApp

  build() {
    Column({ space: 20 }) {
      Text('CopyOptions 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // InApp - 在应用内复制
      Column({ space: 15 }) {
        Text('InApp (在应用内)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .copyOptions(CopyOptions.InApp)
            .border({ width: 2, color: this.currentOption === CopyOptions.InApp ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentOption = CopyOptions.InApp
            })
        Text('在应用内复制，复制的图片和内容仅在应用内可用')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // LocalDevice - 在本设备复制
      Column({ space: 15 }) {
        Text('LocalDevice (在本设备)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .copyOptions(CopyOptions.LocalDevice)
            .border({ width: 2, color: this.currentOption === CopyOptions.LocalDevice ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentOption = CopyOptions.LocalDevice
            })
        Text('在本设备复制，复制的图片和内容可跨应用使用')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // Distributed - 分布式复制
      Column({ space: 15 }) {
        Text('Distributed (分布式)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .copyOptions(CopyOptions.Distributed)
            .border({ width: 2, color: this.currentOption === CopyOptions.Distributed ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentOption = CopyOptions.Distributed
            })
        Text('通过分布式软总线跨设备复制数据')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      Divider().strokeWidth(2)

      Text('当前复制选项: ' + this.currentOption)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Text('copyOptions 属性控制图片长按后的复制行为')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
