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
import { ColorBlock, IconBlock, RadioBlock, useEnabled } from 'common';
import { Chip, ChipSize, PrefixIconOptions, SuffixIconOptions } from '@ohos.arkui.advanced.Chip';

@Component
export struct ChipBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableActivated: boolean = false;
  @State activated: boolean = false;
  @State enableActivatedBackgroundColor: boolean = false;
  @State activatedBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_emphasize');
  @State enableInactivatedBackgroundColor: boolean = false;
  @State inactivatedBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_emphasize');
  @State enablePrefixIconActivatedFillColor: boolean = false;
  @State prefixIconActivatedFillColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary');
  @State enableSuffixIconActivatedFillColor: boolean = false;
  @State suffixIconActivatedFillColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary');
  @State enablePrefixIconInactivatedFillColor: boolean = false;
  @State prefixIconInactivatedFillColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary');
  @State enableSuffixIconInactivatedFillColor: boolean = false;
  @State suffixIconInactivatedFillColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary');
  @State enableActivatedFontColor: boolean = false;
  @State activatedFontColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary');
  @State enableInactivatedFontColor: boolean = false;
  @State inactivatedFontColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary');
  @State enableChipSize: boolean = false;
  @State chipSize: ChipSize = ChipSize.NORMAL;
  @State enablePrefixIcon: boolean = false;
  @State prefixIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State enableSuffixIcon: boolean = false;
  @State suffixIcon: ResourceStr = $r('sys.media.ohos_ic_public_device_phone');
  @State enableAllowClose: boolean = false;
  @State allowClose: boolean = true;

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
    Column({ space: 40 }) {
      Chip({
        prefixIcon: useEnabled<PrefixIconOptions>(this.enablePrefixIcon, {
          src: this.prefixIcon,
          activatedFillColor: useEnabled(this.enablePrefixIconActivatedFillColor, this.prefixIconActivatedFillColor),
          fillColor: useEnabled(this.enablePrefixIconInactivatedFillColor, this.prefixIconInactivatedFillColor),
        }),
        label: {
          text: '操作块',
          activatedFontColor: useEnabled(this.enableActivatedFontColor, this.activatedFontColor),
          fontColor: useEnabled(this.enableInactivatedFontColor, this.inactivatedFontColor),
        },
        suffixIcon: useEnabled<SuffixIconOptions>(this.enableSuffixIcon, {
          src: this.suffixIcon,
          activatedFillColor: useEnabled(this.enableSuffixIconActivatedFillColor, this.suffixIconActivatedFillColor),
          fillColor: useEnabled(this.enableSuffixIconInactivatedFillColor, this.suffixIconInactivatedFillColor),
        }),
        size: useEnabled(this.enableChipSize, this.chipSize),
        allowClose: useEnabled(this.enableAllowClose, this.allowClose),
        enabled: true,
        activated: useEnabled(this.enableActivated, this.activated),
        activatedBackgroundColor: useEnabled(this.enableActivatedBackgroundColor, this.activatedBackgroundColor),
        backgroundColor: useEnabled(this.enableInactivatedBackgroundColor, this.inactivatedBackgroundColor),
      })

    }

  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '尺寸',
          isEnabled: this.enableChipSize,
          value: this.chipSize,
          dataSource: [
            { label: '小尺寸', value: ChipSize.SMALL },
            { label: '正常尺寸', value: ChipSize.NORMAL },
          ]
        })

        RadioBlock({
          title: '是否允许关闭',
          isEnabled: this.enableAllowClose,
          value: this.allowClose,
          dataSource: [
            { label: '允许', value: true },
            { label: '禁止', value: false },
          ]
        })

        IconBlock({
          title: '是否显示前缀图标',
          isEnabled: this.enablePrefixIcon,
          icon: this.prefixIcon,
        })

        IconBlock({
          title: '是否显示后缀图标',
          isEnabled: this.enableSuffixIcon,
          icon: this.suffixIcon,
        })

        RadioBlock({
          title: '是否激活',
          isEnabled: this.enableActivated,
          value: this.activated,
          dataSource: [
            { label: '激活', value: true },
            { label: '去激活', value: false },
          ]
        })

        if (this.activated) {
          ColorBlock({
            title: '激活态背景色',
            isEnabled: this.enableActivatedBackgroundColor,
            color: this.activatedBackgroundColor,
          })

          ColorBlock({
            title: '激活态字体颜色',
            isEnabled: this.enableActivatedFontColor,
            color: this.activatedFontColor,
          })

          if (this.enablePrefixIcon) {
            ColorBlock({
              title: '激活态前缀图标颜色',
              isEnabled: this.enablePrefixIconActivatedFillColor,
              color: this.prefixIconActivatedFillColor,
            })
          }

          if (this.enableSuffixIcon) {
            ColorBlock({
              title: '激活态后缀图标颜色',
              isEnabled: this.enableSuffixIconActivatedFillColor,
              color: this.suffixIconActivatedFillColor,
            })
          }
        } else {
          ColorBlock({
            title: '去激活态背景色',
            isEnabled: this.enableInactivatedBackgroundColor,
            color: this.inactivatedBackgroundColor,
          })

          ColorBlock({
            title: '去激活态字体颜色',
            isEnabled: this.enableInactivatedFontColor,
            color: this.inactivatedFontColor,
          })

          if (this.enablePrefixIcon) {
            ColorBlock({
              title: '去激活态前缀图标颜色',
              isEnabled: this.enablePrefixIconInactivatedFillColor,
              color: this.prefixIconInactivatedFillColor,
            })
          }

          if (this.enableSuffixIcon) {
            ColorBlock({
              title: '去激活态后缀图标颜色',
              isEnabled: this.enableSuffixIconInactivatedFillColor,
              color: this.suffixIconInactivatedFillColor,
            })
          }
        }
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct ChipBootcampPreviewer {
  build() {
    ChipBootcamp({
      title: '操作块/Chip'
    })
  }
}