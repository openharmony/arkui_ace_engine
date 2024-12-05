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
import { SelectionMenu, EditorMenuOptions, ExpandedMenuOptions, EditorEventInfo, SelectionMenuOptions } from '@kit.ArkUI'
import { Drawer, RadioBlock } from 'common';
@Component
export struct SelectionMenuBootcamp {
  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller }
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableSelectionMenuOptions: boolean = false;
  @State enableEditorMenuOptions: boolean = false;
  @State enableExpandedMenuOptions: boolean = false;
  @State enableOnCut: boolean = false;
  @State enableOnPaste: boolean = false;
  @State enableOnCopy: boolean = false;
  @State enableOnSelectAll: boolean = false;
  @State select: boolean = true;
  @State message: string = 'Hello word';
  @State textSize: number = 30;
  @State start: number = -1;
  @State end: number = -1;
  @State fontWeight: FontWeight = FontWeight.Normal;
  @State visibleValue: Visibility = Visibility.Visible;
  @State colorTransparent: Color = Color.Transparent;
  @State textStyle: RichEditorTextStyle = {};
  @State editorMenuOptions: Array<EditorMenuOptions> =
    [
      { icon: $r('app.media.text_bold'), action: () => {
        if (this.controller) {
          let selection = this.controller.getSelection();
          let spans = selection.spans
          spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
            if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
              let span = item as RichEditorTextSpanResult;
              this.textStyle = span.textStyle;
              let start = span.offsetInSpan[0];
              let end = span.offsetInSpan[1];
              let offset = span.spanPosition.spanRange[0];
              if (this.textStyle.fontWeight != 11) {
                this.textStyle.fontWeight = FontWeight.Bolder;
              } else {
                this.textStyle.fontWeight = FontWeight.Normal;
              }
              this.controller.updateSpanStyle({
                start: offset + start,
                end: offset + end,
                textStyle: this.textStyle
              })
            }
          })
        }
      } },
      { icon: $r('app.media.text_tiltle'), action: () => {
        if (this.controller) {
          let selection = this.controller.getSelection();
          let spans = selection.spans;
          spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
            if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
              let span = item as RichEditorTextSpanResult;
              this.textStyle = span.textStyle;
              let start = span.offsetInSpan[0];
              let end = span.offsetInSpan[1];
              let offset = span.spanPosition.spanRange[0];
              if (this.textStyle.fontStyle == FontStyle.Italic) {
                this.textStyle.fontStyle = FontStyle.Normal;
              } else {
                this.textStyle.fontStyle = FontStyle.Italic;
              }
              this.controller.updateSpanStyle({
                start: offset + start,
                end: offset + end,
                textStyle: this.textStyle
              })
            }
          })
        }
      } },
      { icon: $r('app.media.underline'), action: () => {
          if (this.controller) {
            let selection = this.controller.getSelection();
            let spans = selection.spans;
            spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
              if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
                let span = item as RichEditorTextSpanResult;
                this.textStyle = span.textStyle;
                let start = span.offsetInSpan[0];
                let end = span.offsetInSpan[1];
                let offset = span.spanPosition.spanRange[0];
                if (this.textStyle.decoration) {
                  if (this.textStyle.decoration.type == TextDecorationType.Underline) {
                    this.textStyle.decoration.type = TextDecorationType.None;
                  } else {
                    this.textStyle.decoration.type = TextDecorationType.Underline;
                  }
                } else {
                  this.textStyle.decoration = { type: TextDecorationType.Underline, color: Color.Black }
                }
                this.controller.updateSpanStyle({
                  start: offset + start,
                  end: offset + end,
                  textStyle: this.textStyle
                })
              }
            })
          }
        } },
      { icon: $r('app.media.app_icon'), action: () => {},
        builder: (): void => this.sliderPanel() },
      { icon: $r('app.media.text_color'), action: () => {
        if (this.controller) {
          let selection = this.controller.getSelection();
          let spans = selection.spans;
          spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
            if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
              let span = item as RichEditorTextSpanResult;
              this.textStyle = span.textStyle;
              let start = span.offsetInSpan[0];
              let end = span.offsetInSpan[1];
              let offset = span.spanPosition.spanRange[0];
              if (this.textStyle.fontColor == Color.Orange || this.textStyle.fontColor == '#FFFFA500') {
                this.textStyle.fontColor = Color.Black;
              } else {
                this.textStyle.fontColor = Color.Orange;
              }
              this.controller.updateSpanStyle({
                start: offset + start,
                end: offset + end,
                textStyle: this.textStyle
              })
            }
          })
        }
      } }
    ]

  @State expandedMenuOptions: Array<ExpandedMenuOptions> =
    [
      { startIcon: $r('app.media.icon'), content: '词典', action: () => {} },
      { startIcon: $r('app.media.icon'), content: '翻译', action: () => {} },
      { startIcon: $r('app.media.icon'), content: '搜索', action: () => {} }
    ]
  @State onCut: SelectionMenuOptions = {
    controller: this.controller,
    onCut: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test cut' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    }
  }
  @State onPaste: SelectionMenuOptions = {
    controller: this.controller,
    onPaste: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test onPaste' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    }
  }
  @State onCopy: SelectionMenuOptions = {
    controller: this.controller,
    onCopy: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test cut' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    },
  }
  @State onSelectAll: SelectionMenuOptions = {
    controller: this.controller,
    onSelectAll: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test onPaste' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    }
  }

  @State selectionMenuOptions: SelectionMenuOptions = {
    editorMenuOptions: this.editorMenuOptions,
    expandedMenuOptions: this.expandedMenuOptions,
    controller: this.controller,
    onCut: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test cut' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    },
    onPaste: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test onPaste' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    },
    onCopy: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test cut' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    },
    onSelectAll: (event?: EditorEventInfo) => {
      if (event && event.content) {
        event.content.spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
          if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
            let span = item as RichEditorTextSpanResult
            console.info('test onPaste' + span.value)
            console.info('test start ' + span.offsetInSpan[0] + ' end: ' + span.offsetInSpan[1])
          }
        })
      }
    }
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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column(){
      Button('SetSelection')
        .onClick((event: ClickEvent) => {
          if (this.controller) {
            this.controller.setSelection(0, 2)
          }
        })
      RichEditor(this.options)
        .onReady(() => {
          this.controller.addTextSpan(this.message, { style: { fontColor: Color.Orange, fontSize: 30 } })
          this.controller.addTextSpan(this.message, { style: { fontColor: Color.Black, fontSize: 25 } })
        })
        .onSelect((value: RichEditorSelection) => {
          if (value.selection[0] == -1 && value.selection[1] == -1) {
            return
          }
          this.start = value.selection[0]
          this.end = value.selection[1]
        })
        .bindSelectionMenu(RichEditorSpanType.TEXT, this.Menu(), RichEditorResponseType.SELECT)
        .borderWidth(1)
        .borderColor(Color.Red)
        .width(200)
        .height(200)
    }
    .width('100%')
  }

  @Builder
  Parameters() {
    Scroll(){
      Column({ space: 8 }) {
        RadioBlock({
          title: 'selectionMenuOptions',
          isEnabled: $enableSelectionMenuOptions,
          value: $selectionMenuOptions,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'editorMenuOptions',
          isEnabled: $enableEditorMenuOptions,
          value: $editorMenuOptions,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'expandedMenuOptions',
          isEnabled: $enableExpandedMenuOptions,
          value: $expandedMenuOptions,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'onCut',
          isEnabled: $enableOnCut,
          value: $onCut,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'onPaste',
          isEnabled: $enableOnPaste,
          value: $onPaste,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'onCopy',
          isEnabled: $enableOnCopy,
          value: $onCopy,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'onSelectAll',
          isEnabled: $enableOnSelectAll,
          value: $onSelectAll,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
      }
      .width('100%')
    }
    .height('52%')
  }


  @Builder Menu() {
    Column() {
      SelectionMenu({
        editorMenuOptions: this.editorMenuOptions,
        expandedMenuOptions: this.expandedMenuOptions,
        controller: this.controller,
      })
    }
    .width(256)
    .backgroundColor(Color.Transparent)
  }

  @Builder sliderPanel() {
    Column() {
      Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        Text('A').fontSize(15)
        Slider({ value: this.textSize, step: 10, style: SliderStyle.InSet })
          .width(210)
          .onChange((value: number, mode: SliderChangeMode) => {
            if (this.controller) {
              let selection = this.controller.getSelection();
              if (mode == SliderChangeMode.End) {
                if (this.textSize == undefined) {
                  this.textSize = 0
                }
                let spans = selection.spans
                spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
                  if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
                    this.textSize = Math.max(this.textSize, (item as RichEditorTextSpanResult).textStyle.fontSize)
                  }
                })
              }
              if (mode == SliderChangeMode.Moving || mode == SliderChangeMode.Click) {
                this.start = selection.selection[0]
                this.end = selection.selection[1]
                this.textSize = value
                this.controller.updateSpanStyle({
                  start: this.start,
                  end: this.end,
                  textStyle: { fontSize: this.textSize }
                })
              }
            }
          })
        Text('A').fontSize(20).fontWeight(FontWeight.Medium)
      }.borderRadius($r('sys.float.ohos_id_corner_radius_card'))
    }
    .shadow(ShadowStyle.OUTER_DEFAULT_MD)
    .backgroundColor(Color.White)
    .borderRadius($r('sys.float.ohos_id_corner_radius_card'))
    .padding(15)
    .height(48)
  }

}

@Preview
@Component
struct SelectionMenuBootcampPreviewer{
  build() {
    SelectionMenuBootcamp({
      title: '文本选择菜单/SelectionMenu'
    })
  }
}
