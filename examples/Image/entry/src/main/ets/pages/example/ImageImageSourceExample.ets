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
 * Image component source (src) property examples
 */
@Entry
@Component
struct ImageImageSourceExample {
  @State networkImage: string = ''
  @State localImage: string = ''
  @State dataImage: string = ''

  build() {
    Column({ space: 20 }) {
      Text('Source 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 网络 - $r('app.media.network')
      Column({ space: 15 }) {
        Text('网络图片 ($r)')
          .fontSize(16)
        Image($r('app.media.network'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Blue })
        Text('通过 $r() 函数加载网络资源')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // 本地资源 - $r('app.media.local')
      Column({ space: 15 }) {
        Text('本地资源 (local)')
          .fontSize(16)
        Image($r('app.media.local'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Green })
        Text('在应用内使用本地资源图片')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // Data - 'data://hello'
      Column({ space: 15 }) {
        Text('Data (data:)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Orange })
        Text('使用 data 协议加载 Base64 编码数据')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // 应用沙箱 - $r('app.media.file')
      Column({ space: 15 }) {
        Text('应用沙箱 (app:)')
          .fontSize(16)
        Image($r('app.media.file'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Pink })
        Text('读取应用沙箱中的文件资源')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // 多媒体资源 - $r('app.multimedia.person'
      Column({ space: 15 }) {
        Text('多媒体资源 (multimedia:)')
          .fontSize(16)
        Image($r('app.multimedia.person'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Red })
        Text('访问多媒体库中的图片资源')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      // 资源 Base64 编码
      Column({ space: 15 }) {
        Text('Base64 编码')
          .fontSize(16)
        Image($r('app.media.base64_icon'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Gray })
        Text('字符串包含 Base64 编码数据 (data:image/png;base64,...)')
          .fontSize(14)
          .fontColor(Color.Gray)
      }

      Divider().strokeWidth(2)

      Text('src 属性支持多种资源格式')
        .fontSize(18)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
