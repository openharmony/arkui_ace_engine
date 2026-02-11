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

@Entry
@Component
struct previewNONE {
  @State select: boolean = true

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制'})
      MenuItem({ content: '粘贴'})
    }
  }

  @Builder MenuBuilder(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项'})
        .enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        builder: ():void=>this.SubMenu()
      })
    }
  }

  build() {
    Column() {
      Text('LongPress MenuPreviewMode.NONE').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          enableArrow: true,
          preview: MenuPreviewMode.NONE
        })
    }
    .width('100%')

    .height('100%')
  }
}