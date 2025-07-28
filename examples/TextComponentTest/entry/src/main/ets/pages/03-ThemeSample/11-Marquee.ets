/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { common } from '@kit.AbilityKit';

@Entry
@Component
struct Index_Marquee {
  build() {
    Scroll() {
      Column() {

        Column() {
          Text(' 测试点 Marquee create ')
          Marquee({
            start: false,
            step: 10,
            loop: 1,
            fromStart: true,
            src: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Marquee fontColor ')
          Marquee({
            start: false,
            step: 10,
            loop: 1,
            fromStart: true,
            src: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .fontColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Marquee fontSize ')
          Marquee({
            start: false,
            step: 10,
            loop: 1,
            fromStart: true,
            src: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .fontSize($r('app.float.ModeNumber20_50'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Marquee fontFamily ')
          Text(' 浅色 Sans，深色 Sans Condensed ')
          Marquee({
            start: false,
            step: 10,
            loop: 1,
            fromStart: true,
            src: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .fontFamily($r('app.string.TextFontFamily'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


      }
    }
  }
}