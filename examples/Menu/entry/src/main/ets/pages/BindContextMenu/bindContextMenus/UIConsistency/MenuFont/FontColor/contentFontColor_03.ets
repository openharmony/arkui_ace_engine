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
struct MenuFont_FontColor_03 {
  @Builder
  MyMenu(){
    Menu() {
      // pink
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1', endIcon: $r('app.media.app_icon') }).contentFontColor(0xffc0cb)
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2', endIcon: $r('app.media.app_icon') }).contentFontColor(0xffc0cb)
      MenuItemGroup({ header: '二级标题' }) {
        // blue
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3', labelInfo: '标签介绍1', endIcon: $r('app.media.app_icon') }).labelFontColor(0x0000ff)
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项4', labelInfo: '标签介绍2', endIcon: $r('app.media.app_icon') }).labelFontColor(0x0000ff)
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项5', labelInfo: '标签介绍3', endIcon: $r('app.media.app_icon') }).labelFontColor(0x0000ff)
      }
    }.width('100%')
  }
  build() {
    Row() {
      Text('点击展示菜单')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
    }
    .bindMenu(this.MyMenu)
  }
}