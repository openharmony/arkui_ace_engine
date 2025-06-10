/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

// CalendarPicker modifier 使用$r设置edgeAlign
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';

class MyCalendarPickerModifier implements AttributeModifier<CalendarPickerAttribute> {
  public flag = false;
  applyNormalAttribute(instance: CalendarPickerAttribute): void {
    if (this.flag == false) {
      instance.edgeAlign(
        CalendarAlign.END,
        {
          dx: $r('app.float.calendar_picker_edge_align_offset'),
          dy: $r('app.float.calendar_picker_edge_align_offset')
        }
      )
    }
  }
}

@Entry
@Component
struct Index {
  @State calendarPickerModifier: MyCalendarPickerModifier = new MyCalendarPickerModifier();
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;


  build() {
    Column() {
      Button('flag: ' + this.calendarPickerModifier.flag)
        .onClick(() => {
          this.calendarPickerModifier.flag = !this.calendarPickerModifier.flag;
        })
        .margin(20)

      Button('isDark: ' + this.isDark)
        .onClick(() => {
          if (this.isDark) {
            this.isDark = !this.isDark;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
          } else {
            this.isDark = !this.isDark;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
          }
        })
        .margin(20)

      Text('modifier')
      CalendarPicker({
      })
        .attributeModifier(this.calendarPickerModifier)
        .onChange(() => {
          /*
           * switch the color mode
           */
          if (this.isDark) {
            this.isDark = !this.isDark;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
          } else {
            this.isDark = !this.isDark;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
          }
        })
    }
    .width('100%')
  }
}
