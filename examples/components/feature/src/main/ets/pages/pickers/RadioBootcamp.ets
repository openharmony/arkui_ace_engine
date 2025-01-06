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
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';

@Builder
function radioBuilder(config: RadioConfiguration) {
  Row({ space: 30 }) {
    Circle({ width: 50, height: 50 })
      .stroke(Color.Black)
      .fill(config.checked ? (config.contentModifier as MyRadioStyle).selectedColor : Color.White)
    Button(config.checked ? 'off' : 'on' )
      .width(100)
      .type(config.checked ? (config.contentModifier as MyRadioStyle).type : ButtonType.Normal)
      .backgroundColor('#2787D9')
      .onClick(() => {
        if (config.checked) {
          config.triggerChange(false)
        } else {
          config.triggerChange(true)
        }
        config.triggerChange(!config.checked);
      })
  }
}

class MyRadioStyle implements ContentModifier<RadioConfiguration> {
  public type: number = 0
  public selectedColor: ResourceColor = Color.Black
  constructor(numberType: number, colorType: ResourceColor) {
    this.type = numberType;
    this.selectedColor = colorType
  }
  applyContent(): WrappedBuilder<[RadioConfiguration]> {
    return wrapBuilder(radioBuilder)
  }
}

@Component
export struct RadioBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableChecked: boolean = false;
  @State checked: boolean = false;
  @State enableRadioWidth: boolean = false;
  @State radioWidth: number = 10;
  @State enableCheckedBackgroundColor: boolean = false;
  @State checkedBackgroundColor: ResourceColor = '#007DFF';
  @State enableUncheckedBorderColor: boolean = false;
  @State uncheckedBorderColor: ResourceColor = '#182431';
  @State enableIndicatorColor: boolean = false;
  @State indicatorColor: ResourceColor = '#FFFFFF';
  @State enableIndicatorType: boolean = false;
  @State indicatorType: RadioIndicatorType = RadioIndicatorType.TICK;
  @State enableContentModifier: boolean = false;
  @State contentModifier: MyRadioStyle = new MyRadioStyle(1, '#004AAF');

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
  indicatorBuilder() {
    Image('src/main/resources/base/media/star.png')
      .width(5)
      .height(5)
  }

  @Builder
  Content() {
    Column() {
      Row() {
        if (this.enableContentModifier) {
          Radio({
            value: 'Radio1',
            group: 'radioGroup',
            indicatorType: useEnabled(this.enableIndicatorType, this.indicatorType),
            indicatorBuilder: () => {
              this.indicatorBuilder()
            }
          })
            .checked(useEnabled(this.enableChecked, this.checked))
            .width(useEnabled(this.enableRadioWidth, this.radioWidth))
            .radioStyle({
              checkedBackgroundColor: useEnabled(this.enableCheckedBackgroundColor, this.checkedBackgroundColor),
              uncheckedBorderColor: useEnabled(this.enableUncheckedBorderColor, this.uncheckedBorderColor),
              indicatorColor: useEnabled(this.enableIndicatorColor, this.indicatorColor),
            })
            .contentModifier(this.contentModifier)
        } else {
          Radio({
            value: 'Radio1',
            group: 'radioGroup',
            indicatorType: useEnabled(this.enableIndicatorType, this.indicatorType),
            indicatorBuilder: () => {
              this.indicatorBuilder()
            }
          })
            .checked(useEnabled(this.enableChecked, this.checked))
            .width(useEnabled(this.enableRadioWidth, this.radioWidth))
            .radioStyle({
              checkedBackgroundColor: useEnabled(this.enableCheckedBackgroundColor, this.checkedBackgroundColor),
              uncheckedBorderColor: useEnabled(this.enableUncheckedBorderColor, this.uncheckedBorderColor),
              indicatorColor: useEnabled(this.enableIndicatorColor, this.indicatorColor),
            })
        }
      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'indicatorType',
          isEnabled: this.enableIndicatorType,
          value: this.indicatorType,
          dataSource: [
            { label: 'TICK', value: RadioIndicatorType.TICK },
            { label: 'DOT', value: RadioIndicatorType.DOT },
            { label: 'CUSTOM', value: RadioIndicatorType.CUSTOM },
          ]
        })
        ColorBlock({
          title: 'checkedBackgroundColor',
          isEnabled: this.enableCheckedBackgroundColor,
          color: this.checkedBackgroundColor
        })
        ColorBlock({
          title: 'uncheckedBorderColor',
          isEnabled: this.enableUncheckedBorderColor,
          color: this.uncheckedBorderColor
        })
        ColorBlock({
          title: 'indicatorColor',
          isEnabled: this.enableIndicatorColor,
          color: this.indicatorColor
        })
        SliderBlock({
          title: 'radioWidth',
          isEnabled: this.enableRadioWidth,
          value: this.radioWidth,
          min: 0,
          max: 50
        })
        RadioBlock({
          title: 'contentModifier',
          isEnabled: this.enableContentModifier,
          value: this.contentModifier,
          dataSource: [
            { label: 'example1', value: new MyRadioStyle(1, '#004AAF') },
            { label: 'example2', value: new MyRadioStyle(2, '#004AAF') },
          ]
        })
      }.width('100%')
    }
  }
}

@Preview
@Component
struct RadioBootcampPreviewer {
  build() {
    RadioBootcamp({
      title: '单选框/Radio'
    })
  }
}