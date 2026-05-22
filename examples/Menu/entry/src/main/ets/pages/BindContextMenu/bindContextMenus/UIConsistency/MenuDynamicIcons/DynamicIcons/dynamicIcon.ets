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
struct DynamicIcons_dynamicIcon {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon') })
      MenuItem({ startIcon: $r('app.media.app_icon') })
      MenuItem({ endIcon: $r('app.media.app_icon') })
      MenuItem({ endIcon: $r('app.media.app_icon') })
      MenuItem({ endIcon: $r('app.media.app_icon') })
    }
  }
  build() {
    Row() {
      Text('点击展示菜单')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
      Text('查看动态图标是否显示')
        .fontSize(14)
        .fontColor('blue')
      }
    .bindMenu(this.MyMenu)
  }
}