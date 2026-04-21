/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { TitleBar } from '../common/TitleBar'

@Entry
@Component
struct NavigationAdaptationImageIndex {
  private caseList: string[] = [
    'ArkUIHDS_Navigation_0030',
    'ArkUIHDS_Navigation_0060',
    'ArkUIHDS_Navigation_0070',
    'ArkUIHDS_Navigation_0080',
  ]

  build() {
    Scroll() {
      Column() {
        TitleBar({ name: 'Navigation Case List' })
        List() {
          ForEach(this.caseList, (item: string) => {
            ListItem() {
              Button(item)
                .margin(10)
                .width('90%')
                .height(45)
                .fontSize(15)
                .fontColor(Color.White)
                .type(ButtonType.Capsule)
                .stateEffect(true)
                .onClick(() => {
                  router.pushUrl({
                    url: 'pages/NavigationAdaptationImage/' + item
                  })
                })
            }
          }, (item: string) => item)
        }
        .width('100%')
      }
      .width('100%')
    }
  }
}