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


import { Drawer } from 'common/src/main/ets/components/Drawer';

@Component
export struct CalendarPickerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State duration : number = 2000;
  private selectedDate: Date = new Date();

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
    Column() {
      Column() {
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
          .onChange((value) => {
            console.info('CalendarPicker onChange:' + JSON.stringify(value))
          })
      }
    }.width('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct CalendarPickerBootcampPreviewer {
  build() {
    CalendarPickerBootcamp({
      title: '日历选择器/CalendarPicker'
    })
  }
}