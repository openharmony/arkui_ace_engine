/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { RadioBlock, useEnabled } from 'common';
import { Drawer } from 'common/src/main/ets/components/Drawer';


@Component
export struct TimePickerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableIsMilitaryTime: boolean = false;
  @State isMilitaryTime: boolean = false;
  @State isEnableCascade: boolean = false;
  @State enableCascade: boolean = false;
  private selectedTime: Date = new Date('2022-07-22T12:00:00')

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column({ space: 8 }) {
      Column() {
        TimePicker({
          selected: this.selectedTime,
        })
          .useMilitaryTime(useEnabled(this.enableIsMilitaryTime, this.isMilitaryTime))
          .enableCascade(useEnabled(this.isEnableCascade, this.enableCascade))
          .onChange((value: TimePickerResult) => {
            if(value.hour >= 0) {
              this.selectedTime.setHours(value.hour, value.minute)
              console.info('select current date is: ' + JSON.stringify(value))
            }
          })
      }
    }.width('100%').height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '切换12小时制/24小时制',
          isEnabled: this.enableIsMilitaryTime,
          value: this.isMilitaryTime,
          dataSource: [
            { label: '12小时制', value: false },
            { label: '24小时制', value: true }
          ]
        })
        RadioBlock({
          title: '切换12小时制上午下午跟随小时联动/不随小时联动',
          isEnabled: this.isEnableCascade,
          value: this.enableCascade,
          dataSource: [
            { label: '不随小时联动', value: false },
            { label: '跟随小时联动', value: true }
          ]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct TimePickerBootcampPreviewer {
  build() {
    TimePickerBootcamp({
      title: '时间选择器/TimePicker'
    })
  }
}