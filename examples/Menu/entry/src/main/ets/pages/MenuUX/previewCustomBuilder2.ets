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
struct previewMenuBuilder2 {
  @State select: boolean = true
  @State text: string = ''

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: 'menu1'})
      MenuItem({ content: 'menu2'})
    }
  }

  @Builder btnBuilder(){
    Button('click to show menu')
      .onKeyEvent((event: KeyEvent) => {
        this.text = 'onKeyEvent 被触发'
      })
      .bindMenu(this.SubMenu())
  }

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单1'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单2'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单3'})
    }
  }

  build() {
    Column() {
      Text('preview: CustomBuilder 按键').margin({ top:10,bottom:30 })
      Text('LongPress to show Button' + this.text)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MyMenu, ResponseType.LongPress, {
          preview: this.btnBuilder
        })
    }
    .width('100%')

    .height('100%')
  }
}