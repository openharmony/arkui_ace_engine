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
 *图片列表展示示例
 */
@Entry
@Component
struct ImageExample074 {
  @State images: Array<Resource> = [
    $r('app.media.png'),
    $r('app.media.jpg'),
    $r('app.media.gif'),
    $r('app.media.svg'),
    $r('app.media.app_icon')
  ]

  build() {
    Column() {
      Text('图片列表展示示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      List() {
        ForEach(this.images, (image: Resource, index: number) => {
          ListItem() {
            Row() {
              Image(image)
                .width(80)
                .height(80)
                .borderRadius(10)
                .objectFit(ImageFit.Cover)
                .margin({ right: 15 })

              Column({ space: 5 }) {
                Text('图片 ' + (index + 1))
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
                Text('这是图片' + (index + 1) + '的描述信息')
                  .fontSize(14)
                  .fontColor(Color.Gray)
              }
              .alignItems(HorizontalAlign.Start)
              .layoutWeight(1)
            }
            .width('100%')
            .padding(10)
          }
        })
      }
      .width('100%')
      .layoutWeight(1)
      .divider({ strokeWidth: 1, color: '#e0e0e0' })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
