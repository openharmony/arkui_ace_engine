'use static'

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

import { ComponentCard } from '../../common/Card';
import { $r } from '@kit.ArkUI';
import {
  Entry,
  Component,
  Column,
  List,
  ListItem,
  Row,
  Text,
  Image,
  NavDestination,
  ListItemAlign
} from '@kit.ArkUI';

@Entry
@Component
export struct DataInList {
  build(): void {
    NavDestination() {
      Column() {
        ComponentCard({ title: $r('app.string.DataInList_titleCityList') }) {
          List() {
            ListItem() {
              // The value of app.string.city_beijing in resource file is 'Beijing'
              Text($r('app.string.city_beijing'))
                .fontSize(24)
            }

            ListItem() {
              // The value of app.string.city_hangzhou in resource file is 'Hangzhou'
              Text($r('app.string.city_hangzhou'))
                .fontSize(24)
            }

            ListItem() {
              // The value of app.string.city_shanghai in resource file is 'Shanghai'
              Text($r('app.string.city_shanghai'))
                .fontSize(24)
            }
          }
          .backgroundColor('#FFF1F3F5')
          .alignListItem(ListItemAlign.Center)
        }

        ComponentCard({ title: $r('app.string.DataInList_titleContactsList') }) {
          List() {
            ListItem() {
              Row() {
                // app.media.iconE is a custom resource
                Image($r('app.media.iconE'))
                  .width(40)
                  .height(40)
                  .margin(10)

                // The value of app.string.peopleOne in resource file is 'Xiao Ming'
                Text($r('app.string.peopleOne'))
                  .fontSize(20)
              }
            }

            ListItem() {
              Row() {
                // app.media.iconF is a custom resource
                Image($r('app.media.iconF'))
                  .width(40)
                  .height(40)
                  .margin(10)

                // The value of app.string.peopleTwo in resource file is 'Xiao Hong'
                Text($r('app.string.peopleTwo'))
                  .fontSize(20)
              }
            }
          }
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.DataInList_titlePage'))
  }
}
