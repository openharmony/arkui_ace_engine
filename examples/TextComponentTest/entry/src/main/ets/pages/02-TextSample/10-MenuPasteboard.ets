/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import pasteboard from '@ohos.pasteboard'
import { BusinessError } from '@ohos.base';
import image from '@ohos.multimedia.image';
import { Driver } from '@ohos.UiTest';

export interface SelectionMenuTheme {
  imageSize: number;
  buttonSize: number;
  menuSpacing: number;
  editorOptionMargin: number;
  expandedOptionPadding: number;
  defaultMenuWidth: number;
  imageFillColor: Resource;
  backGroundColor: Resource;
  iconBorderRadius: Resource;
  containerBorderRadius: Resource;
  cutIcon: Resource;
  copyIcon: Resource;
  pasteIcon: Resource;
  selectAllIcon: Resource;
  shareIcon: Resource;
  translateIcon: Resource;
  searchIcon: Resource;
  arrowDownIcon: Resource;
  iconPanelShadowStyle: ShadowStyle;
  iconFocusBorderColor: Resource;
}

export const defaultTheme: SelectionMenuTheme = {
  imageSize: 24,
  buttonSize: 48,
  menuSpacing: 8,
  editorOptionMargin: 1,
  expandedOptionPadding: 3,
  defaultMenuWidth: 256,
  imageFillColor: $r('sys.color.ohos_id_color_primary'),
  backGroundColor: $r('sys.color.ohos_id_color_dialog_bg'),
  iconBorderRadius: $r('sys.float.ohos_id_corner_radius_default_m'),
  containerBorderRadius: $r('sys.float.ohos_id_corner_radius_card'),
  cutIcon: $r("sys.media.ohos_ic_public_cut"),
  copyIcon: $r("sys.media.ohos_ic_public_copy"),
  pasteIcon: $r("sys.media.ohos_ic_public_paste"),
  selectAllIcon: $r("sys.media.ohos_ic_public_select_all"),
  shareIcon: $r("sys.media.ohos_ic_public_share"),
  translateIcon: $r("sys.media.ohos_ic_public_translate_c2e"),
  searchIcon: $r("sys.media.ohos_ic_public_search_filled"),
  arrowDownIcon: $r("sys.media.ohos_ic_public_arrow_down"),
  iconPanelShadowStyle: ShadowStyle.OUTER_DEFAULT_MD,
  iconFocusBorderColor: $r('sys.color.ohos_id_color_focused_outline'),
}

@Entry
@Component
struct SelectionMenu {
  @State message: string = 'Hello World'
  @State textSize: number = 40
  @State sliderShow: boolean = false
  @State start: number = -1
  @State end: number = -1
  @State colorTransparent: Color = Color.Transparent
  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller }
  private iconArr: Array<Resource> =
    [$r('app.media.icon'), $r("app.media.icon"), $r('app.media.icon'),
      $r("app.media.icon"), $r('app.media.icon')]
  @State iconBgColor: ResourceColor[] = new Array(this.iconArr.length).fill(this.colorTransparent)
  @State pasteEnable: boolean = false
  @State visibilityValue: Visibility = Visibility.Visible
  @State textStyle: RichEditorTextStyle = {}
  private fontWeightTable: string[] =
    ["100", "200", "300", "400", "500", "600", "700", "800", "900", "bold", "normal", "bolder", "lighter", "medium",
      "regular"]
  private theme: SelectionMenuTheme = defaultTheme;
  @State CaretOffset: string = ''
  @State copyOption: CopyOptions[] =
    [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2
  @State imagePixelMap: image.PixelMap | undefined = undefined

  aboutToAppear() {
    if (this.controller) {
      let richEditorSelection = this.controller.getSelection()
      if (richEditorSelection) {
        let start = richEditorSelection.selection[0]
        let end = richEditorSelection.selection[1]
        if (start === 0 && this.controller.getSpans({ start: end + 1, end: end + 1 }).length === 0) {
          this.visibilityValue = Visibility.None
        } else {
          this.visibilityValue = Visibility.Visible
        }
      }
    }
    let sysBoard = pasteboard.getSystemPasteboard()
    if (sysBoard && sysBoard.hasDataSync()) {
      this.pasteEnable = true
    } else {
      this.pasteEnable = false
    }
  }

  build() {
    Column() {
      Column() {
        Text("光标位置:" + this.CaretOffset).width("100%").fontColor('rgba(20, 207, 179, 1.00)')
        Row() {
          Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
            this.index++
            if (this.index > (this.copyOptionStr.length - 1)) {
              this.index = 0
            }
          })
        }

        Row() {
          Button("获取光标位置").onClick(() => {
            this.CaretOffset = '' + this.controller.getCaretOffset()

          })
          Button("光标前移").onClick(() => {
            let CaretOffset = this.controller.getCaretOffset()
            CaretOffset--
            this.controller.setCaretOffset(CaretOffset)
          })
          Button("光标后移").onClick(() => {
            let CaretOffset = this.controller.getCaretOffset()
            CaretOffset++
            this.controller.setCaretOffset(CaretOffset)
          })
        }

        RichEditor(this.options)
          .copyOptions(this.copyOption[this.index])
          .onReady(() => {
            this.controller.addTextSpan(this.message)
          })
          .onSelect((value: RichEditorSelection) => {
            if (value.selection[0] == -1 && value.selection[1] == -1) {
              return
            }
            this.start = value.selection[0]
            this.end = value.selection[1]
          })
          .bindSelectionMenu(RichEditorSpanType.IMAGE, this.panel, ResponseType.LongPress, {
            onDisappear: () => {
              this.sliderShow = false
            }
          })
          .bindSelectionMenu(RichEditorSpanType.MIXED, this.panel, ResponseType.LongPress, {
            onDisappear: () => {
              this.sliderShow = false
            }
          })
          .bindSelectionMenu(RichEditorSpanType.TEXT, this.panel, ResponseType.LongPress, {
            onDisappear: () => {
              this.sliderShow = false
            }
          })
          .bindSelectionMenu(RichEditorSpanType.TEXT, this.panel, ResponseType.RightClick, {
            onDisappear: () => {
              this.sliderShow = false
            }
          })
          .borderWidth(1)
          .borderColor(Color.Red)
          .width(200)
          .height(200)
      }.width('100%').backgroundColor(Color.White)
    }.height('100%')
  }

  PushDataToPasteboard(richEditorSelection: RichEditorSelection) {
    let sysBoard = pasteboard.getSystemPasteboard()
    let pasteData = pasteboard.createData(pasteboard.MIMETYPE_TEXT_PLAIN, '')
    if (richEditorSelection.spans && richEditorSelection.spans.length > 0) {
      let count = richEditorSelection.spans.length
      for (let i = count - 1; i >= 0; i--) {
        let item = richEditorSelection.spans[i]
        if ((item as RichEditorTextSpanResult)?.textStyle) {
          let span = item as RichEditorTextSpanResult
          let style = span.textStyle
          let data = pasteboard.createRecord(pasteboard.MIMETYPE_TEXT_PLAIN,
            span.value.substring(span.offsetInSpan[0], span.offsetInSpan[1]))
          let prop = pasteData.getProperty()
          let temp: Record<string, Object> = {
            'color': style.fontColor,
            'size': style.fontSize,
            'style': style.fontStyle,
            'weight': this.fontWeightTable[style.fontWeight],
            'fontFamily': style.fontFamily,
            'decorationType': style.decoration.type,
            'decorationColor': style.decoration.color
          }
          prop.additions[i] = temp;
          pasteData.addRecord(data)
          pasteData.setProperty(prop)
        }
        if ((item as RichEditorImageSpanResult)?.imageStyle) {
          let span = item as RichEditorImageSpanResult
          let style = span.imageStyle
          let prop = pasteData.getProperty()
          pasteData.addRecord(data)
          pasteData.setProperty(prop)
        }
      }
    }
    sysBoard.clearData()
    sysBoard.setData(pasteData).then(() => {
      console.info('SelectionMenu copy option, Succeeded in setting PasteData.');
      this.pasteEnable = true;
    }).catch((err: BusinessError) => {
      console.error('SelectionMenu copy option, Failed to set PasteData. Cause:' + err.message);
    })
  }

  PopDataFromPasteboard(richEditorSelection: RichEditorSelection) {
    let start = richEditorSelection.selection[0]
    let end = richEditorSelection.selection[1]
    if (start == end && this.controller) {
      start = this.controller.getCaretOffset()
      end = this.controller.getCaretOffset()
    }
    let moveOffset = 0
    let sysBoard = pasteboard.getSystemPasteboard()
    sysBoard.getData((err, data) => {
      if (err) {
        return
      }
      let count = data.getRecordCount()
      for (let i = 0; i < count; i++) {
        const element = data.getRecord(i);
        let tex: RichEditorImageSpanStyle = {
          size: [60, 60]
        }
        if (data.getProperty() && data.getProperty().additions[i]) {
          const tmp = data.getProperty().additions[i] as Record<string, Object | undefined>;
          if (tmp.size) {
            tex.size = tmp.size as [Dimension, Dimension];
          }

        }
        if (element && element.uri && element.mimeType == pasteboard.MIMETYPE_TEXT_URI && this.controller) {
          this.controller.addImageSpan(element.uri, {
            offset: start + moveOffset,
            imageStyle: {
              size: ["57px", "57px"]
            }
          })
          moveOffset += 1
        }
        if (element && element.plainText && element.mimeType === pasteboard.MIMETYPE_TEXT_PLAIN && this.controller) {
          this.controller.addTextSpan(element.plainText,
            {
              offset: start + moveOffset
            }
          )
          moveOffset += element.plainText.length
        }
      }
      if (this.controller) {
        this.controller.setCaretOffset(start + moveOffset)
        this.controller.closeSelectionMenu()
      }
      if (start != end && this.controller) {
        this.controller.deleteSpans({ start: start + moveOffset, end: end + moveOffset })
      }
    })
  }

  @Builder
  panel() {
    Column() {
      this.iconPanel()
      if (!this.sliderShow) {
        this.SystemMenu()
      } else {
        this.sliderPanel()
      }
    }.width(256)
  }

  @Builder
  iconPanel() {
    Column() {
      Row({ space: 2 }) {
        ForEach(this.iconArr, (item: Resource, index ?: number) => {
          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Image(item)
              .fillColor(this.theme.imageFillColor)
              .width(24)
              .height(24)
              .focusable(true)
              .draggable(false)
          }
          .borderRadius(this.theme.iconBorderRadius)
          .width(this.theme.buttonSize)
          .height(this.theme.buttonSize)
          .onClick(() => {
            if (index as number == 0) {
              this.sliderShow = false
              if (this.controller) {
                let selection = this.controller.getSelection();
                let spans = selection.spans
                spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
                  if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
                    let span = item as RichEditorTextSpanResult
                    this.textStyle = span.textStyle
                    let start = span.offsetInSpan[0]
                    let end = span.offsetInSpan[1]
                    let offset = span.spanPosition.spanRange[0]
                    if (this.textStyle.fontWeight != 11) {
                      this.textStyle.fontWeight = FontWeight.Bolder
                    } else {
                      this.textStyle.fontWeight = FontWeight.Normal
                    }
                    this.controller.updateSpanStyle({
                      start: offset + start,
                      end: offset + end,
                      textStyle: this.textStyle
                    })
                  }
                })
              }
            } else if (index as number == 1) {
              this.sliderShow = false
              if (this.controller) {
                let selection = this.controller.getSelection();
                let spans = selection.spans
                spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
                  if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
                    let span = item as RichEditorTextSpanResult
                    this.textStyle = span.textStyle
                    let start = span.offsetInSpan[0]
                    let end = span.offsetInSpan[1]
                    let offset = span.spanPosition.spanRange[0]
                    if (this.textStyle.fontStyle == FontStyle.Italic) {
                      this.textStyle.fontStyle = FontStyle.Normal
                    } else {
                      this.textStyle.fontStyle = FontStyle.Italic
                    }
                    this.controller.updateSpanStyle({
                      start: offset + start,
                      end: offset + end,
                      textStyle: this.textStyle
                    })
                  }
                })
              }
            } else if (index as number == 2) {
              this.sliderShow = false
              if (this.controller) {
                let selection = this.controller.getSelection();
                let spans = selection.spans
                spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
                  if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
                    let span = item as RichEditorTextSpanResult
                    this.textStyle = span.textStyle
                    let start = span.offsetInSpan[0]
                    let end = span.offsetInSpan[1]
                    let offset = span.spanPosition.spanRange[0]
                    if (this.textStyle.decoration) {
                      if (this.textStyle.decoration.type == TextDecorationType.Underline) {
                        this.textStyle.decoration.type = TextDecorationType.None
                      } else {
                        this.textStyle.decoration.type = TextDecorationType.Underline
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
            } else if (index as number == 3) {
              this.sliderShow = !this.sliderShow
            } else if (index as number == 4) {
              this.sliderShow = false
              if (this.controller) {
                let selection = this.controller.getSelection();
                let spans = selection.spans
                spans.forEach((item: RichEditorTextSpanResult | RichEditorImageSpanResult, index) => {
                  if (typeof (item as RichEditorTextSpanResult)['textStyle'] != 'undefined') {
                    let span = item as RichEditorTextSpanResult
                    this.textStyle = span.textStyle
                    let start = span.offsetInSpan[0]
                    let end = span.offsetInSpan[1]
                    let offset = span.spanPosition.spanRange[0]
                    if (this.textStyle.fontColor == Color.Orange || this.textStyle.fontColor == '#FFFFA500') {
                      this.textStyle.fontColor = Color.Black
                    } else {
                      this.textStyle.fontColor = Color.Orange
                    }
                    this.controller.updateSpanStyle({
                      start: offset + start,
                      end: offset + end,
                      textStyle: this.textStyle
                    })
                  }
                })
              }
            }
          })
          .onTouch((event?: TouchEvent | undefined) => {
            if (event != undefined) {
              if (event.type === TouchType.Down) {
                this.iconBgColor[index as number] = $r('sys.color.ohos_id_color_click_effect')
              }
              if (event.type === TouchType.Up) {
                this.iconBgColor[index as number] = this.colorTransparent
              }
            }
          })
          .onHover((isHover?: boolean, event?: HoverEvent) => {
            this.iconBgColor.forEach((icon: ResourceColor, index1) => {
              this.iconBgColor[index1] = this.colorTransparent
            })
            if (isHover != undefined) {
              this.iconBgColor[index as number] = $r('sys.color.ohos_id_color_hover')
            }
          })
          .backgroundColor(this.iconBgColor[index as number])
        })
      }
    }
    .clip(true)
    .width(this.theme.defaultMenuWidth)
    .padding(this.theme.expandedOptionPadding)
    .borderRadius(this.theme.containerBorderRadius)
    .margin({ bottom: this.theme.menuSpacing })
    .backgroundColor(this.theme.backGroundColor)
    .shadow(this.theme.iconPanelShadowStyle)
  }

  @Builder
  SystemMenu() {
    Column() {
      Menu() {
        if (this.controller) {
          MenuItemGroup() {
            MenuItem({ startIcon: this.theme.cutIcon, content: "剪切", labelInfo: "Ctrl+X" })
              .onClick(() => {
                if (!this.controller) {
                  return
                }
                let richEditorSelection = this.controller.getSelection()
                this.PushDataToPasteboard(richEditorSelection);
                this.controller.deleteSpans({
                  start: richEditorSelection.selection[0],
                  end: richEditorSelection.selection[1]
                })
              })
            MenuItem({ startIcon: this.theme.copyIcon, content: "复制", labelInfo: "Ctrl+C" })
              .onClick(() => {
                if (!this.controller) {
                  return
                }
                let richEditorSelection = this.controller.getSelection()
                this.PushDataToPasteboard(richEditorSelection);
                this.controller.closeSelectionMenu()


              })
            MenuItem({ startIcon: this.theme.pasteIcon, content: "粘贴", labelInfo: "Ctrl+V" })
              .enabled(this.pasteEnable)
              .onClick(() => {
                if (!this.controller) {
                  return
                }
                let richEditorSelection = this.controller.getSelection()
                this.PopDataFromPasteboard(richEditorSelection)


              })
            MenuItem({ startIcon: this.theme.selectAllIcon, content: "全选", labelInfo: "Ctrl+A" })
              .visibility(this.visibilityValue)
              .onClick(() => {
                if (!this.controller) {
                  return
                }
                this.controller.setSelection(-1, -1)
                this.visibilityValue = Visibility.None
              })
            MenuItem({ startIcon: this.theme.shareIcon, content: "分享", labelInfo: "" })
              .enabled(false)
            MenuItem({ startIcon: this.theme.translateIcon, content: "翻译", labelInfo: "" })
              .enabled(false)
            MenuItem({ startIcon: this.theme.searchIcon, content: "搜索", labelInfo: "" })
              .enabled(false)
          }
        }
      }
      .onVisibleAreaChange([0.0, 1.0], () => {
        if (!this.controller) {
          return
        }
        let richEditorSelection = this.controller.getSelection()
        let start = richEditorSelection.selection[0]
        let end = richEditorSelection.selection[1]
        if (start === 0 && this.controller.getSpans({ start: end + 1, end: end + 1 }).length === 0) {
          this.visibilityValue = Visibility.None
        } else {
          this.visibilityValue = Visibility.Visible
        }
      })
      .radius(this.theme.containerBorderRadius)
      .clip(true)
      .backgroundColor(Color.White)
      .width(this.theme.defaultMenuWidth)
    }
    .width(this.theme.defaultMenuWidth)
  }

  @Builder
  sliderPanel() {
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
      }.borderRadius(this.theme.containerBorderRadius)
    }
    .shadow(ShadowStyle.OUTER_DEFAULT_MD)
    .backgroundColor(Color.White)
    .borderRadius(this.theme.containerBorderRadius)
    .padding(15)
    .height(48)

    Text('error:' + this.errorText)
    Text('isEditing:' + this.isEditing)
    Text("insertValue:" + this.insertValue)
    Text("deleteValue:" + this.deleteValue)
    Text("previewRangeStart:" + this.previewRangeStart + "previewRangeEnd:" + this.previewRangeEnd)
    Search().margin({ top: 5 })
    Search().margin({ top: 5 })

    if (this.isShow === 0) {
      Search({ value: this.value, placeholder: 'input your word....', controller: this.controller })
        .enablePreviewText(this.enablePreviewText[this.enableIndex])
        .type(this.type[this.inputIndex])
        .enterKeyType(this.enterKeyType[this.enterKeyTypeIndex])
        .textIndent(this.textIndent[this.textIndentIndex])
        .margin({ top: 5 })
        .maxLength(this.maxLength)
        .decoration({
          type: this.decorationType[this.typeIndex],
          color: this.colorAll[this.decorationColor]
        })
        .cancelButton({
          style: this.cancelButton[this.cancelButtonIndex]
        })
        .onChange((value: string) => {
          this.value = value;

        })
        .onEditChange((isEditing: boolean) => {
          this.isEditing = isEditing
        })
        .onWillInsert((info: InsertValue) => {
          this.insertValue = info.insertValue
          return true;
        })
        .onWillDelete((info: DeleteValue) => {
          this.deleteValue = info.deleteValue
          info.direction
          return true;
        })

    } else if (this.isShow === 1) {
      Search({ value: this.value, placeholder: 'input your word....', controller: this.controller })
        .type(this.type[this.inputIndex])
        .enablePreviewText(this.enablePreviewText[this.enableIndex])
        .enterKeyType(this.enterKeyType[this.enterKeyTypeIndex])
        .textIndent(this.textIndent[this.textIndentIndex])
        .margin({ top: 5 })
        .maxLength(this.maxLength)
        .decoration({
          type: this.decorationType[this.typeIndex],
          color: this.colorAll[this.decorationColor]
        })
        .cancelButton({
          style: this.cancelButton[this.cancelButtonIndex]
        })
        .inputFilter('[a-z]', (value: string) => {
          this.errorText = value
        })
        .onEditChange((isEditing: boolean) => {
          this.isEditing = isEditing
        })
        .onWillInsert((info: InsertValue) => {
          this.insertValue = info.insertValue
          return true;
        })
        .onWillDelete((info: DeleteValue) => {
          this.deleteValue = info.deleteValue
          info.direction
          return true;
        })

    }


    Scroll() {
      Column({ space: 5 }) {

        Row() {
          Button('enablePreviewText:' + this.enablePreviewText[this.enableIndex])
            .width('80%')
            .onClick(() => {
              this.enableIndex = (this.enableIndex + 1) % this.enablePreviewText.length
            })
        }


        Row() {
          Button('inputFilter 不设置')
            .width('40%')
            .onClick(() => {
              this.isShow = 0
            })

          Button('inputFilter [a-z]')
            .width('40%')
            .onClick(() => {
              this.isShow = 1
            })
        }


        Row() {
          Button('decorationType')
            .width('40%')
            .onClick(() => {
              this.typeIndex = (this.typeIndex + 1) % this.decorationType.length
            })

          Button('decorationColor')
            .width('40%')
            .onClick(() => {
              this.decorationColor = (this.decorationColor + 1) % this.colorAll.length
            })
        }

        Row() {
          Button('CancelButtonStyle: ' + this.cancelButton[this.cancelButtonIndex])
            .width('40%')
            .onClick(() => {
              this.cancelButtonIndex = (this.cancelButtonIndex + 1) % this.cancelButton.length
            })

          Button('type:' + this.typeStr[this.inputIndex])
            .width('40%')
            .onClick(() => {
              this.inputIndex = (this.inputIndex + 1) % this.type.length
            })
        }


        Row() {

          Button('textIndent:' + this.textIndent[this.textIndentIndex])
            .width('40%')
            .onClick(() => {
              this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
            })

          Button('enterKeyType: ' + EnterKeyType[this.enterKeyTypeIndex])
            .width('40%')
            .onClick(() => {
              this.enterKeyTypeIndex = (this.enterKeyTypeIndex + 1) % this.enterKeyType.length
            })
        }


        Row() {
          Button('最大字符数+,' + this.maxLength)
            .width('40%')
            .onClick((event: ClickEvent) => {
              this.maxLength += 2
            })
          Button('最大字符数-,' + this.maxLength)
            .width('40%')
            .onClick((event: ClickEvent) => {
              this.maxLength -= 2
            })
        }.margin({ top: 5 })

      }.padding({ bottom: 150 })
    }.height('40%')

    Text('error:' + this.errorText)
    Text('isEditing:' + this.isEditing)
    Search()

    if (this.isShow === 0) {
      Search({ value: this.value, placeholder: 'input your word....', controller: this.controller })
        .type(this.type[this.inputIndex])
        .textIndent(this.textIndent[this.textIndentIndex])
        .selectedBackgroundColor(this.colorAll[this.selectedBackgroundColor])
        .padding(this.paddingTest)
        .width(this.widthTest)
        .height(this.heightTest)
        .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
        .caretStyle({
          width: this.caretWidthAll[this.caretWidth]
        })
        .onChange((value: string) => {
          this.value = value
        })
        .onEditChange((isEditing: boolean) => {
          this.isEditing = isEditing
        })

    } else if (this.isShow === 1) {
      Search({ value: this.value, placeholder: 'input your word....', controller: this.controller })
        .type(this.type[this.inputIndex])
        .textIndent(this.textIndent[this.textIndentIndex])
        .selectedBackgroundColor(this.colorAll[this.selectedBackgroundColor])
        .padding(this.paddingTest)
        .width(this.widthTest)
        .height(this.heightTest)
        .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
        .caretStyle({
          width: this.caretWidthAll[this.caretWidth]
        })
        .inputFilter('[a-z]', (value: string) => {
          this.errorText = value
        })
        .onChange((value: string) => {
          this.value = value
        })
        .onEditChange((isEditing: boolean) => {
          this.isEditing = isEditing
        })

    } else if (this.isShow === 2) {
      Search({ value: this.value, placeholder: 'input your word....', controller: this.controller })
        .type(this.type[this.inputIndex])
        .textIndent(this.textIndent[this.textIndentIndex])
        .selectedBackgroundColor(this.colorAll[this.selectedBackgroundColor])
        .padding(this.paddingTest)
        .width(this.widthTest)
        .height(this.heightTest)
        .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
        .caretStyle({
          width: this.caretWidthAll[this.caretWidth]
        })
        .inputFilter('[0-9.]', (value: string) => {
          this.errorText = value
        })
        .onChange((value: string) => {
          this.value = value
        })
        .onEditChange((isEditing: boolean) => {
          this.isEditing = isEditing
        })

    } else if (this.isShow === 3) {
      Search({ value: this.value, placeholder: 'input your word....', controller: this.controller })
        .type(this.type[this.inputIndex])
        .textIndent(this.textIndent[this.textIndentIndex])
        .selectedBackgroundColor(this.colorAll[this.selectedBackgroundColor])
        .padding(this.paddingTest)
        .width(this.widthTest)
        .height(this.heightTest)
        .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
        .caretStyle({
          width: this.caretWidthAll[this.caretWidth]
        })
        .inputFilter(null, (value: string) => {
          this.errorText = value
        })
        .onChange((value: string) => {
          this.value = value
        })
        .onEditChange((isEditing: boolean) => {
          this.isEditing = isEditing
        })

    }


    Scroll() {
      Column({ space: 5 }) {

        Row() {
          Button('stopEditing')
            .width('80%')
            .onClick(() => {
              this.controller.stopEditing()
            })
        }

        Row() {
          Button('inputFilter 不设置')
            .width('40%')
            .onClick(() => {
              this.isShow = 0
            })

          Button('inputFilter [a-z]')
            .width('40%')
            .onClick(() => {
              this.isShow = 1
            })
        }

        Row() {
          Button('inputFilter [0-9.]')
            .width('40%')
            .onClick(() => {
              this.isShow = 2
            })

          Button('inputFilter null')
            .width('40%')
            .onClick(() => {
              this.isShow = 3
            })
        }

        Row() {
          Button('selectionEnd+,' + this.selectionEnd)
            .width('40%')
            .onClick(() => {
              this.selectionEnd += 1
            })

          Button('selectionEnd-,' + this.selectionEnd)
            .width('40%')
            .onClick(() => {
              this.selectionEnd -= 1
            })
        }

        Row() {
          Button('setTextSelection')
            .width('40%')
            .onClick(() => {
              this.controller.setTextSelection(this.selectionStart, this.selectionEnd)
            })

          Button('caretWidth:' + this.caretWidthAll[this.caretWidth])
            .width('40%')
            .onClick(() => {
              this.caretWidth = (this.caretWidth + 1) % this.caretWidthAll.length
            })

        }

        Row() {
          Button('textOverflow:' + this.textOverflowStr[this.textOverflowIndex])
            .width('40%')
            .onClick(() => {
              this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
            })

          Button('type:' + this.typeStr[this.inputIndex])
            .width('40%')
            .onClick(() => {
              this.inputIndex = (this.inputIndex + 1) % this.type.length
            })
        }


        Row() {

          Button('textIndent:' + this.textIndent[this.textIndentIndex])
            .width('40%')
            .onClick(() => {
              this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
            })

          Button('wordBreak:' + this.wordBreakStr[this.wordBreakIndex])
            .width('40%')
            .onClick(() => {
              this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreakStr.length
            })
        }

        Row() {
          Button('padding+,' + this.paddingTest)
            .width('40%')
            .onClick(() => {
              this.paddingTest += 5
            })

          Button('padding-,' + this.paddingTest)
            .width('40%')
            .onClick(() => {
              this.paddingTest -= 5
            })
        }

        Row() {
          Button('letterSpacing:' + this.letterSpacing[this.letterSpacingIndex])
            .width('40%')
            .onClick(() => {
              this.letterSpacingIndex = (this.letterSpacingIndex + 1) % this.letterSpacing.length
            })

          Button('底板颜色:' + this.color[this.selectedBackgroundColor])
            .width('40%')
            .onClick(() => {
              this.selectedBackgroundColor++
              if (this.selectedBackgroundColor > (this.color.length - 1)) {
                this.selectedBackgroundColor = 0
              }
            })

        }

        Row() {
          Button('height+,' + this.heightTest)
            .width('40%')
            .onClick(() => {
              this.heightTest += 10
            })

          Button('height-,' + this.heightTest)
            .width('40%')
            .onClick(() => {
              this.heightTest -= 10
            })
        }

        Row() {
          Button('width+,' + this.widthTest)
            .width('40%')
            .onClick(() => {
              this.widthTest += 10
            })

          Button('width-,' + this.widthTest)
            .width('40%')
            .onClick(() => {
              this.widthTest -= 10
            })
        }

      }.padding({ bottom: 150 })
    }.height('40%')

    Search({ value: this.text, placeholder: '同步文本', controller: this.controller })
      .copyOption(this.copyOption[this.index])
      .maxLength(this.maxLength)
      .onChange((value: string) => {
        this.text = value
      }).width('80%')

    Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
      this.index++
      if (this.index > (this.copyOptionStr.length - 1)) {
        this.index = 0
      }
    }).margin({ top: 20 })
    Button('maxLength 9')
      .onClick(() => {
        this.maxLength = 9
      })
    Button('maxLength+,' + this.maxLength)
      .onClick(() => {
        this.maxLength += 1
      })
    Button('maxLength-,' + this.maxLength)
      .onClick(() => {
        this.maxLength -= 1
      })
    Button('添加文本')
      .onClick(() => {
        this.text = '蜀道之难，难于上青天'
      })
    Text('不设置maxLines')
    TextArea()
      .style(this.style)
      .textOverflow(this.textOverflow[this.textOverflowIndex])

    TextArea({ text: this.value, placeholder: 'input your word....', controller: this.controller })
      .textOverflow(this.textOverflow[this.textOverflowIndex])
      .maxLines(this.maxLines)
      .type(this.type[this.inputIndex])
      .style(this.style)
      .wordBreak(this.wordBreak[this.wordBreakIndex])
      .textIndent(this.textIndent[this.textIndentIndex])
      .selectedBackgroundColor(this.colorAll[this.selectedBackgroundColor])
      .padding(this.paddingTest)
      .width(this.widthTest)
      .height(this.heightTest)
      .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
      .caretStyle({
        width: this.caretWidthAll[this.caretWidth],
        color: this.colorAll[this.caretColor]
      })
      .onChange((value: string) => {
        this.value = value
      })


    Scroll() {
      Column() {

        Row() {
          Button('selectionEnd+,' + this.selectionEnd)
            .width('40%')
            .onClick(() => {
              this.selectionEnd += 1
            })

          Button('selectionEnd-,' + this.selectionEnd)
            .width('40%')
            .onClick(() => {
              this.selectionEnd -= 1
            })
        }

        Row() {
          Button('setTextSelection')
            .width('40%')
            .onClick(() => {
              this.controller.setTextSelection(this.selectionStart, this.selectionEnd)
            })

          Button('caretWidth:' + this.caretWidthAll[this.caretWidth])
            .width('40%')
            .onClick(() => {
              this.caretWidth = (this.caretWidth + 1) % this.caretWidthAll.length
            })

        }

        Row() {
          Button('textOverflow:' + this.textOverflowStr[this.textOverflowIndex])
            .width('40%')
            .onClick(() => {
              this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
            })

          Button('type:' + this.typeStr[this.inputIndex])
            .width('40%')
            .onClick(() => {
              this.inputIndex = (this.inputIndex + 1) % this.type.length
            })
        }

        Row() {
          Button('maxLines+,' + this.maxLines)
            .width('40%')
            .onClick(() => {
              this.maxLines += 1
            })

          Button('maxLines-,' + this.maxLines)
            .width('40%')
            .onClick(() => {
              this.maxLines -= 1
            })
        }

        Row() {
          Button('style:Default')
            .width('40%')
            .onClick(() => {
              this.style = TextContentStyle.DEFAULT
            })

          Button('style:Inline')
            .width('40%')
            .onClick(() => {
              this.style = TextContentStyle.INLINE
            })
        }

        Row() {

          Button('textIndent:' + this.textIndent[this.textIndentIndex])
            .width('40%')
            .onClick(() => {
              this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
            })

          Button('wordBreak:' + this.wordBreakStr[this.wordBreakIndex])
            .width('40%')
            .onClick(() => {
              this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreakStr.length
            })
        }

        Row() {
          Button('padding+,' + this.paddingTest)
            .width('40%')
            .onClick(() => {
              this.paddingTest += 10
            })

          Button('padding-,' + this.paddingTest)
            .width('40%')
            .onClick(() => {
              this.paddingTest -= 10
            })
        }

        Row() {

          Button('caretColor:' + this.color[this.caretColor])
            .width('40%')
            .onClick(() => {
              this.caretColor++
              if (this.caretColor > (this.color.length - 1)) {
                this.caretColor = 0
              }
            })

        }

        Row() {
          Button('letterSpacing:' + this.letterSpacing[this.letterSpacingIndex])
            .width('40%')
            .onClick(() => {
              this.letterSpacingIndex = (this.letterSpacingIndex + 1) % this.letterSpacing.length
            })

          Button('底板颜色:' + this.color[this.selectedBackgroundColor])
            .width('40%')
            .onClick(() => {
              this.selectedBackgroundColor++
              if (this.selectedBackgroundColor > (this.color.length - 1)) {
                this.selectedBackgroundColor = 0
              }
            })

        }

        Row() {
          Button('height+,' + this.heightTest)
            .width('40%')
            .onClick(() => {
              this.heightTest += 10
            })

          Button('height-,' + this.heightTest)
            .width('40%')
            .onClick(() => {
              this.heightTest -= 10
            })
        }

        Row() {
          Button('width+,' + this.widthTest)
            .width('40%')
            .onClick(() => {
              this.widthTest += 10
            })

          Button('width-,' + this.widthTest)
            .width('40%')
            .onClick(() => {
              this.widthTest -= 10
            })
        }

      }.padding({ bottom: 150 })
    }.height('40%')

    TextArea({
      text: this.text,
      placeholder: 'input your word...'
    })
      .width('80%')
      .margin(20)
      .copyOption(this.copyOption[this.index])
      .fontSize(16)
      .fontColor('#182431')
      .backgroundColor('#FFFFFF')
      .borderWidth(1)
      .onChange((value: string) => {
        this.text = value
      })

    Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
      this.index++
      if (this.index > (this.copyOptionStr.length - 1)) {
        this.index = 0
      }
    }).margin({ top: 20 })
  }
}