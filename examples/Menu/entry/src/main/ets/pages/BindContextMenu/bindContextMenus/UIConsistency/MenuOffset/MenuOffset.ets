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
struct MenuOffset {
  @State offsetX1: number = 10
  @State offsetX2: number = -10
  @State offsetY1: number = 10
  @State offsetY2: number = -10


  @Builder
  MyMenu1(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3' })
    }
    .backgroundColor('gray')
    .offset({ x: this.offsetX1, y: this.offsetY1 })
  }

  @Builder
  MyMenu2(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3' })
    }
    .backgroundColor('green')
    .offset({ x: this.offsetX2, y: this.offsetY2 })
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceEvenly }) {
      Row() {
        Text('点击展示菜单1')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .bindMenu(this.MyMenu1)

      Row() {
        Text('点击展示菜单2')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }.bindMenu(this.MyMenu2)
    }
  }
}