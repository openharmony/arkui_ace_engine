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

import { LengthMetrics } from '@kit.ArkUI';
import { common } from '@kit.AbilityKit';

@Entry
@Component
struct Index_ImageSpan {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text(' 测试点 ImageSpan create ')
          Text() {
            ImageSpan($r('app.media.onIcon'))
              .width(200)
              .height(200)
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 ImageSpan textBackgroundStyle ')
          Text() {
            ImageSpan($r('app.media.onIcon'))
              .width(200)
              .height(200)
              .textBackgroundStyle({
                color: $r('app.color.ModeColor'),
                radius: {
                  topLeft: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                    .id),
                  topRight: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                    .id),
                  bottomLeft: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                    .id),
                  bottomRight: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                    .id),
                }
              })
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 ImageSpan border ')
          Text() {
            ImageSpan($r('app.media.onIcon'))
              .width(200)
              .height(200)
              .border({
                width: {
                  top: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                    .id),
                  right: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                    .id),
                  bottom: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                    .id),
                  left: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                    .id),
                },
                color: {
                  top: $r('app.color.ModeColor'),
                  right: $r('app.color.ModeColorYellow_Pink'),
                  bottom: $r('app.color.ModeColor'),
                  left: $r('app.color.ModeColorYellow_Pink'),
                },
                radius: {
                  topLeft: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                    .id),
                  topRight: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                    .id),
                  bottomLeft: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                    .id),
                  bottomRight: (this.getUIContext()
                    .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                    .id),
                }
              })
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 ImageSpan borderRadius ')
          Text() {
            ImageSpan($r('app.media.onIcon'))
              .width(200)
              .height(200)
              .borderRadius({
                topLeft: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                  .id),
                topRight: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                  .id),
                bottomLeft: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                  .id),
                bottomRight: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                  .id),
              })
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 ImageSpan baselineOffset ')
          Text(' 浅色 5，深色 20 ')
          Text() {
            ImageSpan($r('app.media.onIcon'))
              .width(200)
              .height(200)
              .baselineOffset(LengthMetrics.vp((this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLineSpacing')
                .id)))
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

      }
    }
  }
}