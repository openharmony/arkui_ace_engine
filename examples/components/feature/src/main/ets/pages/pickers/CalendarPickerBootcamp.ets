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
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';


@Component
export struct CalendarPickerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableEdgeAlign: boolean = false;
  @State edgeAlign: CalendarAlign = CalendarAlign.CENTER;
  @State enableAlignItems: boolean = false;
  @State alignItems: HorizontalAlign = HorizontalAlign.Center;
  @State enableTextColor: boolean = false;
  @State textColor: ResourceColor = 'rgb(255, 0, 0, 0.9)';
  @State hintRadius: number = 10;
  @State enableHintRadius: boolean = false;
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
    Column({ space: 8 }) {
      Column() {
        CalendarPicker({ hintRadius: useEnabled(this.enableHintRadius, this.hintRadius), selected: this.selectedDate })
          .edgeAlign(useEnabled(this.enableEdgeAlign, this.edgeAlign))
          .onChange((value) => {
            console.info('CalendarPicker onChange:' + JSON.stringify(value))
          })
      }
    }.width('100%').height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '选择器与入口组件的对齐方式',
          isEnabled: this.enableAlignItems,
          value: this.edgeAlign,
          dataSource: [
            { label: 'START', value: CalendarAlign.START },
            { label: 'CENTER', value: CalendarAlign.CENTER },
            { label: 'END', value: CalendarAlign.END }
          ]
        })
        RadioBlock({
          title: '选择器在容器内的对齐方式',
          isEnabled: this.enableEdgeAlign,
          value: this.alignItems,
          dataSource: [
            { label: 'START', value: HorizontalAlign.Start },
            { label: 'CENTER', value: HorizontalAlign.Center },
            { label: 'END', value: HorizontalAlign.End }
          ]
        })
        ColorBlock({
          title: '字体颜色',
          isEnabled: this.enableTextColor,
          color: this.textColor
        })
        SliderBlock({
          title: '日期选中态底板样式',
          isEnabled: this.enableHintRadius,
          value: this.hintRadius,
          min: 0,
          max: 16
        })
      }.width('100%')
    }
    .height('52%')
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