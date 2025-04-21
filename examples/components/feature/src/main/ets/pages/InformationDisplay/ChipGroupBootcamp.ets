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
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';
import { ChipSize, ChipGroup } from '@kit.ArkUI'

@Component
export struct ChipGroupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableChipGroupItemStyleSize: boolean = false
  @State chipGroupItemStyleSize: ChipSize = ChipSize.NORMAL
  @State enableChipGroupItemStyleBackgroundColor: boolean = false
  @State chipGroupItemStyleBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_button_normal')
  @State enableChipGroupItemStyleFontColor: boolean = false
  @State chipGroupItemStyleFontColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary')
  @State enableChipGroupItemStyleSelectedFontColor: boolean = false
  @State chipGroupItemStyleSelectedFontColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary')
  @State enableChipGroupItemStyleSelectedBackgroundColor: boolean = false
  @State chipGroupItemStyleSelectedBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_emphasize')
  @State enableChipGroupSelectedIndexes: boolean = false
  @State chipGroupSelectedIndexes: Array<number> = [0, 1, 2, 3, 4, 5]
  @State enableChipGroupMultiple: boolean = false
  @State chipGroupMultiple: boolean = false
  @State enableChipGroupChipGroupSpaceItemSpace: boolean = false
  @State chipGroupChipGroupSpaceItemSpace: number = 8
  @State enableChipGroupChipGroupSpaceStartSpace: boolean = false
  @State chipGroupChipGroupSpaceStartSpace: number = 16
  @State enableChipGroupChipGroupSpaceEndSpace: boolean = false
  @State chipGroupChipGroupSpaceEndSpace: number = 16
  @State enableChipGroupChipGroupPaddingTop: boolean = false
  @State chipGroupChipGroupPaddingTop: number = 14
  @State enableChipGroupChipGroupPaddingBottom: boolean = false
  @State chipGroupChipGroupPaddingBottom: number = 14
  @State selection: string | null = null;
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        generic: () => {
          this.Generic()
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
      ChipGroup({
        items: [
          {
            prefixIcon: { src: $r('app.media.app_icon') },
            label: { text: '操作块1' },
            suffixIcon: { src: $r('sys.media.ohos_ic_public_cut') },
            allowClose: false
          },
          {
            prefixIcon: { src: $r('sys.media.ohos_ic_public_copy') },
            label: { text: '操作块2' },
            allowClose: true
          },
          {
            prefixIcon: { src: $r('sys.media.ohos_ic_public_clock') },
            label: { text: '操作块3' },
            allowClose: true
          },
          {
            prefixIcon: { src: $r('sys.media.ohos_ic_public_cast_stream') },
            label: { text: '操作块4' },
            allowClose: true
          },
          {
            prefixIcon: { src: $r('sys.media.ohos_ic_public_cast_mirror') },
            label: { text: '操作块5' },
            allowClose: true
          },
          {
            prefixIcon: { src: $r('sys.media.ohos_ic_public_cast_stream') },
            label: { text: '操作块6' },
            allowClose: true
          },
        ],
        itemStyle: {
          size:
          useEnabled(this.enableChipGroupItemStyleSize,
            this.chipGroupItemStyleSize),
          backgroundColor:
          useEnabled(this.enableChipGroupItemStyleBackgroundColor,
            this.chipGroupItemStyleBackgroundColor),
          fontColor:
          useEnabled(this.enableChipGroupItemStyleFontColor,
            this.chipGroupItemStyleFontColor),
          selectedBackgroundColor:
          useEnabled(this.enableChipGroupItemStyleSelectedBackgroundColor,
            this.chipGroupItemStyleSelectedBackgroundColor),
          selectedFontColor:
          useEnabled(this.enableChipGroupItemStyleSelectedFontColor,
            this.chipGroupItemStyleSelectedFontColor),
        },
        selectedIndexes:
        useEnabled(this.enableChipGroupSelectedIndexes,
          this.chipGroupSelectedIndexes),
        multiple:
        useEnabled(this.enableChipGroupMultiple,
          this.chipGroupMultiple),
        chipGroupSpace: {
          itemSpace:
          useEnabled(this.enableChipGroupChipGroupSpaceItemSpace,
            this.chipGroupChipGroupSpaceItemSpace),
          startSpace:
          useEnabled(this.enableChipGroupChipGroupSpaceStartSpace,
            this.chipGroupChipGroupSpaceStartSpace),
          endSpace:
          useEnabled(this.enableChipGroupChipGroupSpaceEndSpace,
            this.chipGroupChipGroupSpaceEndSpace)
        },
        chipGroupPadding: {
          top:
          useEnabled(this.enableChipGroupChipGroupPaddingTop,
            this.chipGroupChipGroupPaddingTop) as number,
          bottom:
          useEnabled(this.enableChipGroupChipGroupPaddingBottom,
            this.chipGroupChipGroupPaddingBottom) as number
        },
        onChange: (activatedChipsIndex: Array<number>) => {
          console.log('chips on clicked, activated index ' + activatedChipsIndex)
        },
      })
        .id('ChipGroup')
    }
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'options.itemStyle.size',
          isEnabled: this.enableChipGroupItemStyleSize,
          value: this.chipGroupItemStyleSize,
          dataSource: [
            { label: 'NORMAL', value: ChipSize.NORMAL },
            { label: 'SMALL', value: ChipSize.SMALL }
          ]
        })
        ColorBlock({
          title: 'options.itemStyle.backgroundColor',
          isEnabled: this.enableChipGroupItemStyleBackgroundColor,
          color: this.chipGroupItemStyleBackgroundColor
        })
        ColorBlock({
          title: 'options.itemStyle.fontColor',
          isEnabled: this.enableChipGroupItemStyleFontColor,
          color: this.chipGroupItemStyleFontColor
        })
        ColorBlock({
          title: 'options.itemStyle.selectedFontColor',
          isEnabled: this.enableChipGroupItemStyleSelectedFontColor,
          color: this.chipGroupItemStyleSelectedFontColor
        })
        ColorBlock({
          title: 'options.itemStyle.selectedBackgroundColor',
          isEnabled: this.enableChipGroupItemStyleSelectedBackgroundColor,
          color: this.chipGroupItemStyleSelectedBackgroundColor
        })
        RadioBlock({
          title: 'options.selectedIndexes',
          isEnabled: this.enableChipGroupSelectedIndexes,
          value: this.chipGroupSelectedIndexes,
          dataSource: [
            { label: 'selectAll', value: [0, 1, 2, 3, 4, 5] },
            { label: '024', value: [0, 2, 4,] },
            { label: '135', value: [1, 3, 5,] }
          ]
        })
        RadioBlock({
          title: 'options.multiple',
          isEnabled: this.enableChipGroupMultiple,
          value: this.chipGroupMultiple,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        SliderBlock({
          title: 'options.chipGroupSpace.itemSpace',
          isEnabled: this.enableChipGroupChipGroupSpaceItemSpace,
          value: this.chipGroupChipGroupSpaceItemSpace,
          min: 0,
          max: 16
        })
        SliderBlock({
          title: 'options.chipGroupSpace.startSpace',
          isEnabled: this.enableChipGroupChipGroupSpaceStartSpace,
          value: this.chipGroupChipGroupSpaceStartSpace,
          min: 0,
          max: 16
        })
        SliderBlock({
          title: 'options.chipGroupSpace.endSpace',
          isEnabled: this.enableChipGroupChipGroupSpaceEndSpace,
          value: this.chipGroupChipGroupSpaceEndSpace,
          min: 0,
          max: 16
        })
        SliderBlock({
          title: 'options.ChipGroupPadding.top',
          isEnabled: this.enableChipGroupChipGroupPaddingTop,
          value: this.chipGroupChipGroupPaddingTop,
          min: 0,
          max: 28
        })
        SliderBlock({
          title: 'options.ChipGroupPadding.bottom',
          isEnabled: this.enableChipGroupChipGroupPaddingBottom,
          value: this.chipGroupChipGroupPaddingBottom,
          min: 0,
          max: 28
        })
      }
    }
    .height('52%')
    .id('scroll')
  }

  @Builder
  Generic() {
    Column() {

    }
    .height('52%')
  }
}

@Preview
@Component
struct ChipGroupBootcampPreviewer {
  build() {
    ChipGroupBootcamp({
      title: '操作块群组/ChipGroup'
    })
  }
}