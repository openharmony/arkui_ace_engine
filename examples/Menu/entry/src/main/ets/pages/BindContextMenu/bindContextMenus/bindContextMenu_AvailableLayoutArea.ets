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

import { MyComponent } from '../../common/MyComponent'
@Entry
@Component
struct bindContextMenu_AvailableLayoutArea {
  // $r('app.media.icon')需要替换为开发者所需的图像资源文件。
  private iconStr: ResourceStr = $r("app.media.app_icon");
  @State previewScaleMode: PreviewScaleMode |undefined = undefined
  @State availableLayoutArea: AvailableLayoutArea |undefined = undefined
  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
    }
  }

  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(800)
        .height(800)
    }
  }

  build() {
    Column({ space: 50 }) {
      Column() {
        Column() {
          Text('preview-builder')
            .width(200)
            .height(100)
            .textAlign(TextAlign.Center)
            .margin(100)
            .fontSize(30)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview,
                previewScaleMode: this.previewScaleMode,
                placement:Placement.Bottom,
                availableLayoutArea: this.availableLayoutArea
              })
          Text(`availableLayoutArea: ${this.availableLayoutArea}`)

          Row({ space: 5 }) {
            MyComponent({
              title: 'SAFE_AREA', func: () => {
                this.availableLayoutArea = 	AvailableLayoutArea.SAFE_AREA
              }
            })

            MyComponent({
              title: 'UN', func: () => {
                this.availableLayoutArea = undefined
              }
            })
          }
        }
      }.width('100%')
    }
  }
}