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

// TextPicker modifier 使用$r设置defaultTextStyle
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';

class MyTextPickerModifier implements AttributeModifier<TextPickerAttribute> {
  public flag = false;
  applyNormalAttribute(instance: TextPickerAttribute): void {
    if (this.flag == false) {
      instance.disableTextStyleAnimation(true)
      instance.defaultTextStyle({
        color: $r('app.color.picker_text_style_color'),
        font: {
          size: $r('app.float.picker_text_style_font_size'),
          weight: FontWeight.Bold,
          family: $r('app.string.picker_text_style_font_family')
        },
        minFontSize: $r('app.float.picker_text_style_min_font_size'),
        maxFontSize: $r('app.float.picker_text_style_max_font_size')
      })

    }
  }
}

@Entry
@Component
struct Index {
  @State textPickerModifier: MyTextPickerModifier = new MyTextPickerModifier();
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  private appleArr: string[] = ['apple1', 'apple2', 'apple3', 'apple4'];
  private orangeArr: string[] = ['orange1', 'orange2', 'orange3', 'orange4'];
  private peachArr: string[] = ['peach1', 'peach2', 'peach3', 'peach4'];
  private multi: string[][] = [this.appleArr, this.orangeArr, this.peachArr];

  build() {
    Column() {
      Button('flag: ' + this.textPickerModifier.flag)
        .onClick(() => {
          this.textPickerModifier.flag = !this.textPickerModifier.flag;
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
      TextPicker({
        range: this.multi
      })
        .attributeModifier(this.textPickerModifier)
    }
    .width('100%')
  }
}
