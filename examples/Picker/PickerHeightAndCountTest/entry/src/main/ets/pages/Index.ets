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

import { router } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  build() {
    Column({ space: 20 }) {
      Text('Picker 测试首页')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 40 })

      Text('请选择测试类型')
        .fontSize(16)
        .fontColor('#666666')

      Button('ETS 接口测试')
        .width('80%')
        .height(48)
        .onClick(() => {
          router.pushUrl({ url: 'pages/EtsInterfaceTest' });
        })

      Button('Modifier 接口测试')
        .width('80%')
        .height(48)
        .onClick(() => {
          router.pushUrl({ url: 'pages/ModifierInterfaceTest' });
        })

      Button('CAPI 接口测试')
        .width('80%')
        .height(48)
        .onClick(() => {
          router.pushUrl({ url: 'pages/CapiInterfaceTest' });
        })

      Button('divider与itemHeight接口测试')
        .width('80%')
        .height(48)
        .onClick(() => {
          router.pushUrl({ url: 'pages/ItemHeightDividerComboTest' });
        })
    }
    .justifyContent(FlexAlign.Center)
    .backgroundColor('#F5F5F5')
    .height('100%')
    .width('100%')
  }
}
