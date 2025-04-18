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
import { BlockTag } from 'common/src/main/ets/model/BlockTag';
import { formatDate } from 'common/src/main/ets/utils/timeUtil';

@Component
export struct BindSheetBootcamp {
  @Require @Prop title: ResourceStr
  @State showParameters: boolean = false;
  @State compBindSheetIsShow: boolean = false
  @State enableCompBindSheetOptionsHeight: boolean = false
  @State compBindSheetOptionsHeight: SheetSize = SheetSize.LARGE
  @State enableCompBindSheetOptionsDetents: boolean = false
  @State compBindSheetOptionsDetents: [(SheetSize | Length), (SheetSize | Length)?, (SheetSize | Length)?] =
    [SheetSize.LARGE]
  @State enableCompBindSheetOptionsPreferType: boolean = false
  @State compBindSheetOptionsPreferType: SheetType = SheetType.BOTTOM
  @State enableCompBindSheetOptionsShowClose: boolean = false
  @State compBindSheetOptionsShowClose: boolean = true
  @State enableCompBindSheetOptionsDragBar: boolean = false
  @State compBindSheetOptionsDragBar: boolean = false
  @State enableCompBindSheetOptionsBlurStyle: boolean = false
  @State compBindSheetOptionsBlurStyle: BlurStyle = BlurStyle.NONE
  @State enableCompBindSheetOptionsMaskColor: boolean = false
  @State compBindSheetOptionsMaskColor: ResourceColor | undefined = undefined
  @State enableCompBindSheetOptionsTitleTitle: boolean = false
  @State compBindSheetOptionsTitleTitle: boolean = false
  @State enableCompBindSheetOptionsTitleSubtitle: boolean = false
  @State compBindSheetOptionsTitleSubtitle: boolean = false
  @State enableCompBindSheetOptionsEnableOutsideInteractive: boolean = false
  @State compBindSheetOptionsEnableOutsideInteractive: boolean = false
  @State enableCompBindSheetOptionsBorderWidth: boolean = false
  @State compBindSheetOptionsBorderWidth: number = 0
  @State enableCompBindSheetOptionsBorderColor: boolean = false
  @State compBindSheetOptionsBorderColor: ResourceColor = Color.Black
  @State enableCompBindSheetOptionsBorderStyle: boolean = false
  @State compBindSheetOptionsBorderStyle: BorderStyle = BorderStyle.Solid
  @State enableCompBindSheetOptionWidth: boolean = false
  @State compBindSheetOptionsWidth: number = 200
  @State enableCompBindSheetOptionShadow: boolean = false
  @State compBindSheetOptionShadow: ShadowStyle = ShadowStyle.OUTER_DEFAULT_XS
  @State enableCompBindSheetOptionMode: boolean = false
  @State compBindSheetOptionMode: SheetMode = SheetMode.OVERLAY
  @State enableCompBindSheetOptionScrollSizeMode: boolean = false
  @State compBindSheetOptionScrollSizeMode: ScrollSizeMode = ScrollSizeMode.FOLLOW_DETENT
  @StorageLink('Block') listEventTriggeredTags: Array<BlockTag> = [];
  @State listEventTriggeredTagsTemp: Array<BlockTag> = [];
  scroller: Scroller = new Scroller();

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  compEventTriggeredLog(value: string) {
    let time = formatDate(new Date(Date.now()))
    this.listEventTriggeredTagsTemp.push(
      new BlockTag(time, value)
    )
    setTimeout(() => {
      if (AppStorage.get('Block')) {
        this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
          this.listEventTriggeredTagsTemp
        );
        this.listEventTriggeredTagsTemp = [];
      } else {
        if (this.listEventTriggeredTagsTemp) {
          this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
            this.listEventTriggeredTagsTemp
          );
        }
        if (this.listEventTriggeredTags) {
          this.listEventTriggeredTagsTemp = [];
        }
      }
    }, 200)
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
  bindSheetBuilder() {
    Text('bindSheet')
  }

  @Builder
  Content() {
    Column() {
      Button('点击唤出半模态界面')
        .onClick(() => {
          this.compBindSheetIsShow = !this.compBindSheetIsShow
        })
        .bindSheet(
          this.compBindSheetIsShow, this.bindSheetBuilder(),
          {
            shouldDismiss: () => {
              this.compBindSheetIsShow = false
              this.compEventTriggeredLog('BindSheet:shouldDismiss()')
            },
            height: useEnabled(this.enableCompBindSheetOptionsHeight, this.compBindSheetOptionsHeight),
            detents: useEnabled(this.enableCompBindSheetOptionsDetents, this.compBindSheetOptionsDetents),
            preferType: useEnabled(this.enableCompBindSheetOptionsPreferType, this.compBindSheetOptionsPreferType),
            showClose: useEnabled(this.enableCompBindSheetOptionsShowClose, this.compBindSheetOptionsShowClose),
            dragBar: useEnabled(this.enableCompBindSheetOptionsDragBar, this.compBindSheetOptionsDragBar),
            blurStyle: useEnabled(this.enableCompBindSheetOptionsBlurStyle, this.compBindSheetOptionsBlurStyle),
            maskColor: useEnabled(this.enableCompBindSheetOptionsMaskColor, this.compBindSheetOptionsMaskColor),
            title: {
              title: useEnabled(this.enableCompBindSheetOptionsTitleTitle, this.compBindSheetOptionsTitleTitle) ?
                'title' : '',
              subtitle: useEnabled(this.enableCompBindSheetOptionsTitleSubtitle,
                this.compBindSheetOptionsTitleSubtitle) ? 'subtitle' : ''
            },
            enableOutsideInteractive: useEnabled(this.enableCompBindSheetOptionsEnableOutsideInteractive,
              this.compBindSheetOptionsEnableOutsideInteractive),
            borderWidth: useEnabled(this.enableCompBindSheetOptionsBorderWidth,
              this.compBindSheetOptionsBorderWidth),
            borderColor: useEnabled(this.enableCompBindSheetOptionsBorderColor,
              this.compBindSheetOptionsBorderColor),
            borderStyle: useEnabled(this.enableCompBindSheetOptionsBorderStyle,
              this.compBindSheetOptionsBorderStyle),
            width: useEnabled(this.enableCompBindSheetOptionWidth, this.compBindSheetOptionsWidth),
            shadow: useEnabled(this.enableCompBindSheetOptionShadow, this.compBindSheetOptionShadow),
            mode: useEnabled(this.enableCompBindSheetOptionMode, this.compBindSheetOptionMode),
            scrollSizeMode: useEnabled(this.enableCompBindSheetOptionScrollSizeMode,
              this.compBindSheetOptionScrollSizeMode),
            onWillDismiss: () => {
              this.compEventTriggeredLog('BindSheet:onWillDismiss()')
            },
            onWillSpringBackWhenDismiss: () => {
              this.compEventTriggeredLog('BindSheet:onWillSpringBackWhenDismiss()')
            },
            onHeightDidChange: () => {
              this.compEventTriggeredLog('BindSheet:onHeightDidChange()')
            },
            onDetentsDidChange: () => {
              this.compEventTriggeredLog('BindSheet:onDetentsDidChange()')
            },
            onWidthDidChange: () => {
              this.compEventTriggeredLog('BindSheet:onWidthDidChange()')
            },
            onTypeDidChange: () => {
              this.compEventTriggeredLog('BindSheet:onTypeDidChange()')
            }
          }
        )
    }
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'sheetOptions.height',
          isEnabled: $enableCompBindSheetOptionsHeight,
          value: $compBindSheetOptionsHeight,
          dataSource: [
            { label: 'MEDIUM', value: SheetSize.MEDIUM },
            { label: 'LARGE', value: SheetSize.LARGE },
            { label: 'FIT_CONTENT', value: SheetSize.FIT_CONTENT },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.detents',
          isEnabled: $enableCompBindSheetOptionsDetents,
          value: $compBindSheetOptionsDetents,
          dataSource: [
            { label: 'MEDIUM,LARGE,FIT_CONTENT', value: [SheetSize.MEDIUM, SheetSize.LARGE, SheetSize.FIT_CONTENT] },
            { label: 'LARGE,FIT_CONTENT', value: [SheetSize.LARGE, SheetSize.FIT_CONTENT] },
            { label: 'FIT_CONTENT', value: SheetSize.FIT_CONTENT },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.preferType',
          isEnabled: $enableCompBindSheetOptionsPreferType,
          value: $compBindSheetOptionsPreferType,
          dataSource: [
            { label: 'BOTTOM', value: SheetType.BOTTOM },
            { label: 'CENTER', value: SheetType.CENTER },
            { label: 'POPUP', value: SheetType.POPUP },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.showClose',
          isEnabled: $enableCompBindSheetOptionsShowClose,
          value: $compBindSheetOptionsShowClose,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.dragBar',
          isEnabled: $enableCompBindSheetOptionsDragBar,
          value: $compBindSheetOptionsDragBar,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.blurStyle',
          isEnabled: $enableCompBindSheetOptionsBlurStyle,
          value: $compBindSheetOptionsBlurStyle,
          dataSource: [
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Regular', value: BlurStyle.Regular },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'BACKGROUND_THIN', value: BlurStyle.BACKGROUND_THIN },
            { label: 'BACKGROUND_REGULAR', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'BACKGROUND_THICK', value: BlurStyle.BACKGROUND_THICK },
            { label: 'BACKGROUND_ULTRA_THICK', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'COMPONENT_ULTRA_THIN', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'COMPONENT_THIN', value: BlurStyle.COMPONENT_THIN },
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })

        ColorBlock({
          title: 'sheetOptions.maskColor',
          isEnabled: $enableCompBindSheetOptionsMaskColor,
          color: $compBindSheetOptionsMaskColor
        })

        RadioBlock({
          title: 'sheetOptions.title.title',
          isEnabled: $enableCompBindSheetOptionsTitleTitle,
          value: $compBindSheetOptionsTitleTitle,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.title.subtitle',
          isEnabled: $enableCompBindSheetOptionsTitleSubtitle,
          value: $compBindSheetOptionsTitleSubtitle,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.enableOutsideInteractive',
          isEnabled: $enableCompBindSheetOptionsEnableOutsideInteractive,
          value: $compBindSheetOptionsEnableOutsideInteractive,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'sheetOptions.borderWidth',
          isEnabled: $enableCompBindSheetOptionsBorderWidth,
          value: $compBindSheetOptionsBorderWidth,
          min: 0,
          max: 32
        })

        ColorBlock({
          title: 'sheetOptions.borderColor',
          isEnabled: $enableCompBindSheetOptionsBorderColor,
          color: $compBindSheetOptionsBorderColor
        })

        RadioBlock({
          title: 'sheetOptions.borderStyle',
          isEnabled: $enableCompBindSheetOptionsBorderStyle,
          value: $compBindSheetOptionsBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid }
          ]
        })

        SliderBlock({
          title: 'sheetOptions.width',
          isEnabled: $enableCompBindSheetOptionWidth,
          value: $compBindSheetOptionsBorderWidth,
          min: 0,
          max: 32
        })

        RadioBlock({
          title: 'sheetOptions.shadow',
          isEnabled: $enableCompBindSheetOptionShadow,
          value: $compBindSheetOptionShadow,
          dataSource: [
            { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
            { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
            { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
            { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
            { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
            { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.mode',
          isEnabled: $enableCompBindSheetOptionMode,
          value: $compBindSheetOptionMode,
          dataSource: [
            { label: 'OVERLAY', value: SheetMode.OVERLAY },
            { label: 'EMBEDDED', value: SheetMode.EMBEDDED },
          ]
        })

        RadioBlock({
          title: 'sheetOptions.scrollSizeMode',
          isEnabled: $enableCompBindSheetOptionScrollSizeMode,
          value: $compBindSheetOptionScrollSizeMode,
          dataSource: [
            { label: 'FOLLOW_DETENT', value: ScrollSizeMode.FOLLOW_DETENT },
            { label: 'CONTINUOUS', value: ScrollSizeMode.CONTINUOUS },
          ]
        })

      }.width('100%')
    }.height('50%').id('scroll')
  }

  @Builder
  Generic() {

  }
}

@Preview
@Component
struct BindSheetBootcampPreviewer {
  build() {
    BindSheetBootcamp({
      title: '半模态/BindSheet'
    })
  }
}
