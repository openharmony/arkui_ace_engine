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
import { common } from '@kit.AbilityKit';
import {
  Entry,
  Component,
  State,
  NavDestination,
  Column,
  Grid,
  GridItem,
  Text,
  ForEach,
  ResourceStr,
  $r
} from '@kit.ArkUI';
// [Start build_a_office_services_grid_of_foreach]
@Entry
@Component
export struct DataInGrid {
  // [StartExclude build_a_office_services_grid_of_foreach]
  context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;
  // [EndExclude build_a_office_services_grid_of_foreach]

  @State
  services: string[] = [] as string[];

  // [StartExclude build_a_office_services_grid_of_foreach]
  aboutToAppear(): void {
    // app.string.Meeting资源文件中的value值为'会议'
    this.services.push(this.context.resourceManager.getStringSync($r('app.string.Meeting').id));
    // app.string.Check_in资源文件中的value值为'签到'
    this.services.push(this.context.resourceManager.getStringSync($r('app.string.Check_in').id));
    // app.string.Voting资源文件中的value值为'投票'
    this.services.push(this.context.resourceManager.getStringSync($r('app.string.Voting').id));
    // app.string.Printing资源文件中的value值为'打印'
    this.services.push(this.context.resourceManager.getStringSync($r('app.string.Printing').id));
  }
  // [EndExclude build_a_office_services_grid_of_foreach]

  build(): void {
    // [StartExclude build_a_office_services_grid_of_foreach]
    NavDestination() {
      // [EndExclude build_a_office_services_grid_of_foreach]
      Column() {
        // [StartExclude build_a_office_services_grid_of_foreach]
        ComponentCard({ title: $r('app.string.DataInGrid_titleOfficeServices') }) {
          // [Start build_a_office_services_grid]
          // [Start build_a_office_services_meeting]
          Grid() {
            GridItem() {
              // app.string.Meeting资源文件中的value值为'会议'
              Text($r('app.string.Meeting'))
              // [StartExclude build_a_office_services_meeting]
                .fontSize(24)
              // [EndExclude build_a_office_services_meeting]
            }

            GridItem() {
              // app.string.Check_in资源文件中的value值为'签到'
              Text($r('app.string.Check_in'))
              // [StartExclude build_a_office_services_meeting]
                .fontSize(24)
              // [EndExclude build_a_office_services_meeting]
            }

            GridItem() {
              // app.string.Voting资源文件中的value值为'投票'
              Text($r('app.string.Voting'))
              // [StartExclude build_a_office_services_meeting]
                .fontSize(24)
              // [EndExclude build_a_office_services_meeting]
            }

            GridItem() {
              // app.string.Printing资源文件中的value值为'打印'
              Text($r('app.string.Printing'))
              // [StartExclude build_a_office_services_meeting]
                .fontSize(24)
              // [EndExclude build_a_office_services_meeting]
            }
          }
          // [StartExclude build_a_office_services_meeting]
          // [StartExclude build_a_office_services_grid]
          .height(200)
          // [EndExclude build_a_office_services_grid]
          .columnsGap(6)
          .rowsGap(6)
          // [EndExclude build_a_office_services_meeting]
          .rowsTemplate('1fr 1fr')
          .columnsTemplate('1fr 1fr')
          // [End build_a_office_services_meeting]
          // [End build_a_office_services_grid]
        }

        // app.string.DataInGrid_titleForEach资源文件中的value值为'办公服务网格ForEach语句示例'
        ComponentCard({ title: $r('app.string.DataInGrid_titleForEach') }) {
          // [EndExclude build_a_office_services_grid_of_foreach]
          Grid() {
            ForEach(this.services, (service: string) => {
              GridItem() {
                Text(service)
              }
              // [StartExclude build_a_office_services_grid_of_foreach]
              .backgroundColor('#FFF1F3F5')
              // [EndExclude build_a_office_services_grid_of_foreach]
            }, (service: string): string => service)
          }
          .rowsTemplate(('1fr 1fr') as string)
          .columnsTemplate(('1fr 1fr') as string)
          // [StartExclude build_a_office_services_grid_of_foreach]
          .height(200)
          .columnsGap(6)
          .rowsGap(6)
        }
        // [EndExclude build_a_office_services_grid_of_foreach]
      }
      // [StartExclude build_a_office_services_grid_of_foreach]
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // app.string.DataInGrid_title资源文件中的value值为'网格显示数据'
    .title($r('app.string.DataInGrid_title'))
    // [EndExclude build_a_office_services_grid_of_foreach]
  }
}
// [End build_a_office_services_grid_of_foreach]
