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

@Reusable
@Component
export struct NewsItem {
  @Prop index: number = 0; // 索引值，默认值为0

  build() {
    Row() {
      Column() {
        // $r('app.string.news_item_content')需要替换为开发者所需的资源文件
        Text($r('app.string.news_item_content', this.index))
          .lineHeight(23)
          .fontWeight(500)
          .fontSize(16)
          // $r('sys.color.ohos_id_color_text_primary')需要替换为开发者所需的资源文件
          .fontColor($r('sys.color.ohos_id_color_text_primary'))
          .maxLines(2)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
        // 请将$r('app.string.news_item_publish_date')替换为实际资源文件，在本示例中该资源文件的value值为"January 1, 2025"
        Text($r('app.string.news_item_publish_date'))
          .fontSize(12)
          // $r('sys.color.ohos_id_color_text_tertiary')需要替换为开发者所需的资源文件
          .fontColor($r('sys.color.ohos_id_color_text_tertiary'))
      }
      .height('100%')
      .margin({ right: 8 })
      .alignItems(HorizontalAlign.Start)
      .justifyContent(FlexAlign.SpaceBetween)
      .layoutWeight(1)
      // 请将$r('app.media.item_pic')替换为实际资源文件
      Image($r('app.media.item_pic'))
        .height(81)
        .width(108)
        .objectFit(ImageFit.Cover)
        .borderRadius(8)
    }
    .width('100%')
    .borderRadius(16)
    .backgroundColor(Color.White)
    .height(105)
    .padding({
      top: 12,
      bottom: 12,
      left: 16,
      right: 16
    })
  }
}