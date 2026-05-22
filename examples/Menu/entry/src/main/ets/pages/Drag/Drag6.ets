/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

// xxx.ets
@Entry
@Component
struct Drag6 {
  private iconStr: ResourceStr = $r('app.media.app_icon')

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
    }
  }
  @Builder
  PreviewImage() {
    Text('CustomBuilderText')
      .width(200)
      .height(100)
      .backgroundColor('#e23c2f')
  }

  build() {
    Column({ space: 50 }) {
      Column() {
        Column() {
          Button('preview-image')
            .draggable(true)
            .onDragStart((event)=>{
            })
            .width(200)
            .height(100)
            .margin(100)
            .fontSize(30)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              { preview: this.PreviewImage(),
                previewAnimationOptions: {scale: [0.8, 1.0]},
              })
            .backgroundColor('#ff3df2f5')
        }
      }.width('100%')
    }
  }
}