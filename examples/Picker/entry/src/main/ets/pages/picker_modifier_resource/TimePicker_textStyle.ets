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

// TimePicker modifier 使用$r设置textStyle
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';

class MyTimePickerModifier implements AttributeModifier<TimePickerAttribute> {
  public flag = false;
  applyNormalAttribute(instance: TimePickerAttribute): void {
    if (this.flag == false) {
      instance.disappearTextStyle({
        color: $r('app.color.picker_text_style_color'),
        font: {
          size: $r('app.float.picker_text_style_font_size'),
          weight: FontWeight.Bold,
          family: $r('app.string.picker_text_style_font_family')
        }
      })
      instance.textStyle({
        color: $r('app.color.picker_text_style_color'),
        font: {
          size: $r('app.float.picker_text_style_font_size'),
          weight: FontWeight.Bold,
          family: $r('app.string.picker_text_style_font_family')
        }
      })
    } else {
      instance.selectedTextStyle({
        color: $r('app.color.picker_text_style_color'),
        font: {
          size: $r('app.float.picker_text_style_font_size'),
          weight: FontWeight.Bold,
          family: $r('app.string.picker_text_style_font_family')
        }
      })
    }
  }
}

@Entry
@Component
struct Index {
  @State timePickerModifier: MyTimePickerModifier = new MyTimePickerModifier();
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;


  build() {
    Column() {
      Button('flag: ' + this.timePickerModifier.flag)
        .onClick(() => {
          this.timePickerModifier.flag = !this.timePickerModifier.flag;
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
      TimePicker({
      })
        .attributeModifier(this.timePickerModifier)
    }
    .width('100%')
  }
}
