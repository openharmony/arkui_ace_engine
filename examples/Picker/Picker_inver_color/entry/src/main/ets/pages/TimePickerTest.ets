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

import { CalleeCallback, ConfigurationConstant } from '@kit.AbilityKit';
import { Callback } from '@ohos.base';
import { LengthMetrics } from '@kit.ArkUI';

class CustomModifier implements AttributeModifier<TimePickerAttribute> {
  public disappearStyle?: PickerTextStyle = undefined;
  public selectedStyle?: PickerTextStyle = undefined;
  public textStyle?: PickerTextStyle = undefined;
  public isWithTheme: boolean = false;

  applyNormalAttribute(instance: TimePickerAttribute): void {
    instance.disappearTextStyle(this.disappearStyle)
    instance.selectedTextStyle(this.selectedStyle)
    instance.textStyle(this.textStyle)
    if (this.isWithTheme) {
      instance.backgroundColor($r('app.color.picker_bak_theme'))
    }
  }
}

interface pickerCategories<T> {
  id?: string,
  text: string,
  value?: T
}

@Entry
@Component
struct TimePickerExample {
  @State myModifier: CustomModifier = new CustomModifier();
  @State currentPicker: string = '原生设置属性Picker';
  @State isModifier: boolean = false;
  @State isNoneProperty: boolean = false;

  @State isWithTheme: boolean = false;
  @State themeColorMode: ThemeColorMode = ThemeColorMode.DARK;
  @State themeColorModeStr: string = 'DARK';

  @State textColorList: (pickerCategories<PickerTextStyle>)[] = [
    {
      text: 'Color.Red',
      value: { color: Color.Red }
    },
    {
      text: 'Color.Transparent',
      value: { color: Color.Transparent }
    },
    {
      text: '0x008080',
      value: { color: '0x008080' }
    },
    {
      text: 'rgb(255, 100, 255)',
      value: { color: 'rgb(255, 100, 255)' }
    },
    {
      text: 'rgba(255, 100, 255, 0.5)',
      value: { color: 'rgba(255, 100, 255, 0.5)' }
    },
    {
      text: '#00FFFF',
      value: { color: '#00FFFF' }
    },
    {
      text: '#00FFFFCF',
      value: { color: '#00FFFFCF' }
    },
    {
      text: '$r_red_base_dark',
      value: { color: $r('app.color.red') }
    },
    {
      text: '$r_green_base',
      value: { color: $r('app.color.green') }
    },
    {
      text: 'null',
      value: { color: 'null' }
    },
    {
      text: 'undefined',
      value: { color: undefined }
    },
    {
      text: '-10',
      value: { color: -10 }
    },
    {
      text: 'xxx',
      value: { color: 'xxx' }
    }
  ];
  @State textStyle?: PickerTextStyle = undefined;
  @State disappearStyle?: PickerTextStyle = undefined;
  @State selectedStyle?: PickerTextStyle = undefined;

  @State styles: string[] = [ 'selectedTextStyle', 'textStyle', 'disappearTextStyle' ];
  @State currentStyle?: string = undefined;

  @Builder
  clickComponent(id?: string, text?: string, click?: Callback<ClickEvent>) {
    Column() {
      Button(text).fontSize(12)
    }
    .id(id)
    .onClick(click)
  }

  build() {
    Column({space: 5}) {
      Text('TimePicker invert color')
      Row({space: 5}) {
        this.clickComponent(undefined, '深色', (event: ClickEvent) => {
          let context = this.getUIContext().getHostContext()?.getApplicationContext();
          context?.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
        })
        this.clickComponent(undefined, '浅色', (event: ClickEvent) => {
          let context = this.getUIContext().getHostContext()?.getApplicationContext();
          context?.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
        })
      }.width('100%')

      Text('WithTheme: ' + this.isWithTheme).width('100%')
      Row({space: 5}) {
        this.clickComponent(undefined, 'true', (event: ClickEvent) => {
          this.isWithTheme = true;
          this.myModifier.isWithTheme = true;
        })
        this.clickComponent(undefined, 'false', (event: ClickEvent) => {
          this.isWithTheme = false;
          this.myModifier.isWithTheme = false;
        })
      }.width('100%')

      if (this.isWithTheme) {
        Text('withTheme color mode: ' + this.themeColorModeStr).width('100%')
        Row({space: 5}) {
          this.clickComponent(undefined, 'DARK', (event: ClickEvent) => {
            this.themeColorMode = ThemeColorMode.DARK;
            this.themeColorModeStr = 'DARK';
          })
          this.clickComponent(undefined, 'SYSTEM', (event: ClickEvent) => {
            this.themeColorMode = ThemeColorMode.SYSTEM;
            this.themeColorModeStr = 'SYSTEM';
          })
          this.clickComponent(undefined, 'LIGHT', (event: ClickEvent) => {
            this.themeColorMode = ThemeColorMode.LIGHT;
            this.themeColorModeStr = 'LIGHT';
          })
        }.width('100%')
      }

      Text('选择一个Picker: ' + this.currentPicker).width('100%')
      Row({space: 5}) {
        this.clickComponent(undefined, '原生设置属性', (event: ClickEvent) => {
          this.isNoneProperty = false;
          this.isModifier = false;
          this.currentPicker = '原生设置属性';
        })
        this.clickComponent(undefined, 'Modifier设置属性', (event: ClickEvent) => {
          this.isNoneProperty = false;
          this.isModifier = true;
          this.currentPicker = 'Modifier设置属性';
        })
        this.clickComponent(undefined, '不设置属性', (event: ClickEvent) => {
          this.isNoneProperty = true;
          this.currentPicker = '不设置属性';
        })
      }.width('100%')

      if (this.isNoneProperty == false) {
        Scroll() {
          Column() {
            Text('选择为哪个style赋值: ' + this.currentStyle).width('100%').fontSize(12)
            Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
              ForEach(this.styles, (item: string, index: number) => {
                this.clickComponent(item, item, (event: ClickEvent) => {
                  this.currentStyle = item;
                })
              })
            }.width('100%')

            Text('style值选项: ').width('100%').fontSize(12)
            Flex({wrap: FlexWrap.Wrap, alignContent: FlexAlign.Center, space: {main: LengthMetrics.vp(5)}}) {
              ForEach(this.textColorList, (item: pickerCategories<PickerTextStyle>, index: number) => {
                this.clickComponent(item.id, item.text, (event: ClickEvent) => {
                  if (this.currentStyle == 'disappearTextStyle') {
                    this.disappearStyle = item.value;
                    this.myModifier.disappearStyle = item.value;
                  }

                  if (this.currentStyle == 'selectedTextStyle') {
                    this.selectedStyle = item.value;
                    this.myModifier.selectedStyle = item.value;
                  }

                  if (this.currentStyle == 'textStyle') {
                    this.textStyle = item.value;
                    this.myModifier.textStyle = item.value;
                  }
                })
              })
            }.width('100%')
          }
        }.constraintSize({maxHeight: '200vp'})
      }

      if (this.isWithTheme) {
        WithTheme({ colorMode: this.themeColorMode }) {
          if (this.isNoneProperty) {
            TimePicker()
              .backgroundColor($r('app.color.picker_bak_theme'))
          } else {
            if (this.isModifier) {
              TimePicker({})
                .attributeModifier(this.myModifier)
            } else {
              TimePicker({})
                .disappearTextStyle(this.disappearStyle)
                .selectedTextStyle(this.selectedStyle)
                .textStyle(this.textStyle)
                .backgroundColor($r('app.color.picker_bak_theme'))
            }
          }
        }
      } else {
        if (this.isNoneProperty) {
          TimePicker()
        } else {
          if (this.isModifier) {
            TimePicker({})
              .attributeModifier(this.myModifier)
          } else {
            TimePicker({})
              .disappearTextStyle(this.disappearStyle)
              .selectedTextStyle(this.selectedStyle)
              .textStyle(this.textStyle)
          }
        }
      }
    }.width('100%')
  }
}