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
struct Index_ContainerSpan {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text(' 测试点 ContainerSpan create ')
          Text() {
            ContainerSpan() {
              Span('   Hello World !   ').fontSize('16fp').fontColor(Color.White)
            }
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
      }
    }
  }
}