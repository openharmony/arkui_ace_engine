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

/**
 * Image syncLoad 示例 - 同步加载图片
 * API 8+
 */
@Entry
@Component
struct ImageSyncLoadExample {
  @State syncLoadEnabled: boolean = false;

  build() {
    Column({ space: 20 }) {
      Text('Image SyncLoad')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Text('syncLoad 属性控制图片是否同步加载')
        .fontSize(14)
        .fontColor(0x999999)

      Row({ space: 10 }) {
        Button('启用同步加载')
          .onClick(() => {
            this.syncLoadEnabled = true;
          })

        Button('禁用同步加载')
          .onClick(() => {
            this.syncLoadEnabled = false;
          })
      }

      Divider()

      Scroll() {
        Column({ space: 15 }) {
          Text('同步加载状态: ' + (this.syncLoadEnabled ? '已启用' : '已禁用'))
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          // 本地资源图片 - 同步加载
          Text('本地资源图片 (同步加载)')
            .fontSize(14)
          Image($r('app.media.img'))
            .width(200)
            .height(200)
            .border({ width: 1, color: Color.Gray })
            .syncLoad(this.syncLoadEnabled)

          // 网络图片 - 同步加载
          Text('网络图片 (同步加载)')
            .fontSize(14)
          Image('https://xxx',)
            .width(200)
            .height(200)
            .border({ width: 1, color: Color.Gray })
            .syncLoad(this.syncLoadEnabled)
            .alt($r('app.media.img'))

          // PNG 图片 - 同步加载
          Text('PNG 图片 (同步加载)')
            .fontSize(14)
          Image($r('app.media.png'))
            .width(200)
            .height(200)
            .border({ width: 1, color: Color.Gray })
            .syncLoad(this.syncLoadEnabled)

          // SVG 图片 - 同步加载
          Text('SVG 图片 (同步加载)')
            .fontSize(14)
          Image($r('app.media.svg'))
            .width(200)
            .height(200)
            .border({ width: 1, color: Color.Gray })
            .syncLoad(this.syncLoadEnabled)

          // GIF 图片 - 同步加载
          Text('GIF 图片 (同步加载)')
            .fontSize(14)
          Image($r('app.media.gif'))
            .width(200)
            .height(200)
            .border({ width: 1, color: Color.Gray })
            .syncLoad(this.syncLoadEnabled)
        }
        .padding(10)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
