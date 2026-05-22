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

import router from '@ohos.router'
@Entry
@Component
struct BuilderRightClickBindContextMenu {

  @Builder
  SubMenu(){
    Menu() {
      MenuItem({ content: '跳转百度' })
        .onClick(() => {
          router.pushUrl({
            url: 'pages/baidu'
          })
        })
      MenuItem({ content: '跳转Index' })
        .onClick(() => {
          router.pushUrl({
            url:  'pages/Index',
          })
        })
    }
  }

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单',
        builder: ():void=>this.SubMenu()
      })
    }
  }

  build() {
    Row(){
      Column() {
        Text('右击展示菜单')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .bindContextMenu(this.MyMenu, ResponseType.RightClick)
    }
    .width('100%')
    .height('100%')
  }
}