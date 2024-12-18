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
import { RadioBlock, ColorBlock, useEnabled } from 'common';
import { LengthMetrics, SelectionMenu, EditorMenuOptions, ExpandedMenuOptions, SelectionMenuOptions } from '@kit.ArkUI';

@Component
export struct TextBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State isShow: boolean = false;
  @State enableBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = 'rgb(255, 0, 0, 0.9)';
  @State enableCaretColor: boolean = false;
  @State caretColor: ResourceColor = 'rgb(255, 0, 0, 0.9)';
  @State enableTextAlign: boolean = false;
  @State textAlign: TextAlign = TextAlign.Center;
  @State sliderShow: boolean = false;
  @State enableCustomSelectionMenu: boolean = true;
  @State customSelectionMenu: boolean = false;
  @State enableSystemSelectionMenu: boolean = true;
  @State systemSelectionMenu: boolean = true;
  @State start: number = 0;
  @State end: number = 0;
  paragraph1: string =
    'They can be classified as built-in components–those directly provided by the ArkUI framework and custom components – \n\n';
  paragraph2: string =
    'those defined by developers. The built-in components include buttons radio buttonsprogress indicators and text.\n\n';
  paragraph3: string =
    'You can set the rendering effect of these components in method chaining mode, page components are divided into\n\n';
  paragraph4: string =
    'independent UI units to implement independent creation development and reuse of different units on pages making pages more engineering-oriented.';
  paragraphStyleAttr: ParagraphStyle = new ParagraphStyle({ textIndent: LengthMetrics.vp(0) });
  mutableStyledString1: MutableStyledString = new MutableStyledString(
    this.paragraph1 + this.paragraph2 + this.paragraph3 + this.paragraph4, [
    {
      start: 0,
      length: this.paragraph1.length + this.paragraph2.length + this.paragraph3.length + this.paragraph4.length,
      styledKey: StyledStringKey.PARAGRAPH_STYLE,
      styledValue: this.paragraphStyleAttr
    },
  ])
  controller: TextController = new TextController();
  private expandedMenuOptions: Array<ExpandedMenuOptions> =
    [
      {
        startIcon: $r('sys.media.ohos_ic_public_select_all'), content: '全选', action: () => {
        if (!this.controller) {
          return;
        }
        this.start = 0;
        this.end = this.mutableStyledString1.length;
      }
      },
      {
        startIcon: $r('app.media.indent_plus'), content: '首行缩进+', action: () => {
        if (!this.controller) {
          return;
        }
        let textStyle = this.mutableStyledString1.getStyles(0, 1, StyledStringKey.PARAGRAPH_STYLE);
        let paraAttr = textStyle[0].styledValue as ParagraphStyle;
        let paraAttrIndent = paraAttr.textIndent! + 10;
        this.mutableStyledString1.setStyle({
          start: 0,
          length: this.paragraph1.length + this.paragraph2.length +
          this.paragraph3.length + this.paragraph4.length,
          styledKey: StyledStringKey.PARAGRAPH_STYLE,
          styledValue: new ParagraphStyle({ textIndent: LengthMetrics.vp(paraAttrIndent) })
        })
        this.controller.setStyledString(this.mutableStyledString1)
      }
      },
      {
        startIcon: $r('app.media.indent_minus'), content: '首行缩进-', action: () => {
        if (!this.controller) {
          return;
        }
        let textStyle = this.mutableStyledString1.getStyles(0, 1, StyledStringKey.PARAGRAPH_STYLE);
        let paraAttr = textStyle[0].styledValue as ParagraphStyle;
        let paraAttrIndent = paraAttr.textIndent! - 10;
        this.mutableStyledString1.setStyle({
          start: 0,
          length: this.paragraph1.length + this.paragraph2.length +
          this.paragraph3.length + this.paragraph4.length,
          styledKey: StyledStringKey.PARAGRAPH_STYLE,
          styledValue: new ParagraphStyle({ textIndent: LengthMetrics.vp(paraAttrIndent) })
        })
        this.controller.setStyledString(this.mutableStyledString1);
      }
      }]
  private selectionMenuOptions: SelectionMenuOptions = {
    expandedMenuOptions: this.expandedMenuOptions,
  }

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
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Text(undefined, { controller: this.controller })
        .bindSelectionMenu(
          useEnabled(this.customSelectionMenu, TextSpanType.TEXT),
          this.customSelectionMenu ? this.MyMenu() : undefined,
          useEnabled(this.customSelectionMenu, TextResponseType.SELECT),
          this.customSelectionMenu ? {
            onDisappear: () => {
              this.sliderShow = false;
            }
          } : undefined)
        .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
          this.start = selectionStart;
          this.end = selectionEnd;
        })
        .copyOption(CopyOptions.LocalDevice)
        .draggable(true)
        .textAlign(useEnabled(this.enableTextAlign, this.textAlign))
        .caretColor(useEnabled(this.enableCaretColor, this.caretColor))
        .selectedBackgroundColor(useEnabled(this.enableBackgroundColor, this.compBackgroundColor))
        .selection(this.start, this.end)
        .margin({
          start: LengthMetrics.vp(24),
          end: LengthMetrics.vp(24)
        })
    }
    .justifyContent(FlexAlign.Start)
    .onAttach(() => {
      this.controller.setStyledString(this.mutableStyledString1);
    })
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'textAlign',
          isEnabled: $enableTextAlign,
          value: $textAlign,
          dataSource: [
            { label: 'Start', value: TextAlign.Start },
            { label: 'Center', value: TextAlign.Center },
            { label: 'End', value: TextAlign.End },
            { label: 'JUSTIFY', value: TextAlign.JUSTIFY }
          ]
        })
        RadioBlock({
          title: '是否设置自定义选择菜单',
          isEnabled: this.enableCustomSelectionMenu,
          value: this.customSelectionMenu,
          dataSource: [
            { label: '自定义', value: true },
            { label: '默认', value: false }
          ]
        })
        if (this.customSelectionMenu) {
          RadioBlock({
            title: '是否显示首行缩进菜单',
            isEnabled: this.enableSystemSelectionMenu,
            value: this.systemSelectionMenu,
            dataSource: [
              { label: '显示', value: true },
              { label: '隐藏', value: false }
            ]
          })
        }
        ColorBlock({
          title: '背景颜色',
          isEnabled: this.enableBackgroundColor,
          color: this.compBackgroundColor

        })
        ColorBlock({
          title: '光标颜色',
          isEnabled: this.enableCaretColor,
          color: this.caretColor
        })
      }
      .width('100%')
      .height('100%')
      .onAttach(() => {
        this.controller.setStyledString(this.mutableStyledString1);
      })
    }
  }

  @Builder
  MyMenu() {
    Column() {
      if (this.systemSelectionMenu) {
        SelectionMenu(this.selectionMenuOptions)
      }
    }
    .width(256)
  }
}

@Preview
@Component
struct TextInputBootcampPreviewer {
  build() {
    TextBootcamp({
      title: '文本/Text'
    })
  }
}