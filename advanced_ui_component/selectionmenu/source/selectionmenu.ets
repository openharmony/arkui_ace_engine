/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

import pasteboard from '@ohos.pasteboard'
import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';

const WITHOUT_BUILDER = -2

export interface EditorMenuOptions {
  icon: ResourceStr
  action?: () => void
  builder?: () => void
}

export interface ExpandedMenuOptions extends MenuItemOptions {
  action?: () => void;
}

export interface EditorEventInfo {
  content?: RichEditorSelection;
}

export interface SelectionMenuOptions {
  editorMenuOptions?: Array<EditorMenuOptions>
  expandedMenuOptions?: Array<ExpandedMenuOptions>
  controller?: RichEditorController
  onPaste?: (event?: EditorEventInfo) => void
  onCopy?: (event?: EditorEventInfo) => void
  onCut?: (event?: EditorEventInfo) => void;
  onSelectAll?: (event?: EditorEventInfo) => void;
}

interface SelectionMenuTheme {
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
}

const defaultTheme: SelectionMenuTheme = {
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
}

@Component
struct SelectionMenuComponent {
  editorMenuOptions?: Array<EditorMenuOptions>
  expandedMenuOptions?: Array<ExpandedMenuOptions>
  controller?: RichEditorController
  onPaste?: (event?: EditorEventInfo) => void
  onCopy?: (event?: EditorEventInfo) => void
  onCut?: (event?: EditorEventInfo) => void;
  onSelectAll?: (event?: EditorEventInfo) => void;
  private theme: SelectionMenuTheme = defaultTheme;

  @Builder
  CloserFun() {
  }

  @BuilderParam builder: CustomBuilder = this.CloserFun
  @State showExpandedMenuOptions: boolean = false
  @State showCustomerIndex: number = -1
  @State customerChange: boolean = false
  @State cutAndCopyEnable: boolean = false
  @State pasteEnable: boolean = false
  @State visibilityValue: Visibility = Visibility.Visible
  @State customMenuSize: string | number = '100%'
  private customMenuHeight: number = this.theme.menuSpacing
  private fontWeightTable: string[] = ["100", "200", "300", "400", "500", "600", "700", "800", "900", "bold", "normal", "bolder", "lighter", "medium", "regular"]

  aboutToAppear() {
    if (this.controller) {
      let richEditorSelection = this.controller.getSelection()
      let start = richEditorSelection.selection[0]
      let end = richEditorSelection.selection[1]
      if (start !== end) {
        this.cutAndCopyEnable = true
      }
      if (start === 0 && this.controller.getSpans({ start: end + 1, end: end + 1 }).length === 0) {
        this.visibilityValue = Visibility.None
      } else {
        this.visibilityValue = Visibility.Visible
      }
    } else if (this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
      this.showExpandedMenuOptions = true
    }
    let sysBoard = pasteboard.getSystemPasteboard()
    if (sysBoard && sysBoard.hasDataSync()) {
      this.pasteEnable = true
    }
    if (!(this.editorMenuOptions && this.editorMenuOptions.length > 0)) {
      this.customMenuHeight = 0
    }
  }

  build() {
    Column() {
      if (this.editorMenuOptions && this.editorMenuOptions.length > 0) {
        this.IconPanel()
      }
      Scroll() {
        this.SystemMenu()
      }
      .backgroundColor(this.theme.backGroundColor)
      .flexShrink(1)
      .shadow(this.theme.iconPanelShadowStyle)
      .borderRadius(this.theme.containerBorderRadius)
      .onAreaChange((oldValue: Area, newValue: Area) => {
        let newValueHeight = newValue.height as number
        let oldValueHeight = oldValue.height as number
        this.customMenuHeight += newValueHeight - oldValueHeight
        this.customMenuSize = this.customMenuHeight
      })
    }
    .useShadowBatching(true)
    .flexShrink(1)
    .height(this.customMenuSize)
  }

  pushDataToPasteboard(richEditorSelection: RichEditorSelection) {
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
      }
    }
    sysBoard.clearData()
    sysBoard.setData(pasteData).then(() => {
      hilog.info(0x3900, "Ace", 'SelectionMenu copy option, Succeeded in setting PasteData.');
    }).catch((err: BusinessError) => {
      hilog.info(0x3900, "Ace", 'SelectionMenu copy option, Failed to set PasteData. Cause:' + err.message);
    })
  }

  popDataFromPasteboard(richEditorSelection: RichEditorSelection) {
    let start = richEditorSelection.selection[0]
    let end = richEditorSelection.selection[1]
    if (start === end && this.controller) {
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
        let tex: RichEditorTextStyle = {
          fontSize: 16,
          fontColor: Color.Black,
          fontWeight: FontWeight.Normal,
          fontFamily: "HarmonyOS Sans",
          fontStyle: FontStyle.Normal,
          decoration: { type: TextDecorationType.None, color: "#FF000000" }
        }
        if (data.getProperty() && data.getProperty().additions[i]) {
          const tmp = data.getProperty().additions[i] as Record<string, Object | undefined>;
          if (tmp.color) {
            tex.fontColor = tmp.color as ResourceColor;
          }
          if (tmp.size) {
            tex.fontSize = tmp.size as Length | number;
          }
          if (tmp.style) {
            tex.fontStyle = tmp.style as FontStyle;
          }
          if (tmp.weight) {
            tex.fontWeight = tmp.weight as number | FontWeight | string;
          }
          if (tmp.fontFamily) {
            tex.fontFamily = tmp.fontFamily as ResourceStr;
          }
          if (tmp.decorationType && tex.decoration) {
            tex.decoration.type = tmp.decorationType as TextDecorationType;
          }
          if (tmp.decorationColor && tex.decoration) {
            tex.decoration.color = tmp.decorationColor as ResourceColor;
          }
          if (tex.decoration) {
            tex.decoration = { type: tex.decoration.type, color: tex.decoration.color }
          }
        }
        if (element && element.plainText && element.mimeType === pasteboard.MIMETYPE_TEXT_PLAIN && this.controller) {
          this.controller.addTextSpan(element.plainText,
            {
              style: tex,
              offset: start + moveOffset
            }
          )
          moveOffset += element.plainText.length
        }
      }
      if (this.controller) {
        this.controller.setCaretOffset(start + moveOffset)
      }
      if (start !== end && this.controller) {
        this.controller.deleteSpans({ start: start + moveOffset, end: end + moveOffset })
      }
    })
  }

  measureButtonWidth(): number {
    if (this.editorMenuOptions && this.editorMenuOptions.length < 5) {
      return (this.theme.defaultMenuWidth - this.theme.expandedOptionPadding * 2 -
        this.theme.editorOptionMargin * 2 * this.editorMenuOptions.length) / this.editorMenuOptions.length
    }
    return this.theme.buttonSize
  }

  @Builder
  IconPanel() {
    Flex({ wrap: FlexWrap.Wrap }) {
      if (this.editorMenuOptions) {
        ForEach(this.editorMenuOptions, (item: EditorMenuOptions, index: number) => {
          Button() {
            Image(item.icon)
              .width(this.theme.imageSize)
              .height(this.theme.imageSize)
              .fillColor(this.theme.imageFillColor)
              .focusable(true)
              .draggable(false)
          }
          .enabled(!(!item.action && !item.builder))
          .type(ButtonType.Normal)
          .margin(this.theme.editorOptionMargin)
          .backgroundColor(this.theme.backGroundColor)
          .onClick(() => {
            if (item.builder) {
              this.builder = item.builder
              this.showCustomerIndex = index
              this.showExpandedMenuOptions = false
              this.customerChange = !this.customerChange
            } else {
              this.showCustomerIndex = WITHOUT_BUILDER
              if (!this.controller) {
                this.showExpandedMenuOptions = true
              }
            }
            if (item.action) {
              item.action()
            }
          })
          .borderRadius(this.theme.iconBorderRadius)
          .width(this.measureButtonWidth())
          .height(this.theme.buttonSize)
        })
      }
    }
    .onAreaChange((oldValue: Area, newValue: Area) => {
      let newValueHeight = newValue.height as number
      let oldValueHeight = oldValue.height as number
      this.customMenuHeight += newValueHeight - oldValueHeight
      this.customMenuSize = this.customMenuHeight
    })
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
      if (this.showCustomerIndex === -1 &&
        (this.controller || (this.expandedMenuOptions && this.expandedMenuOptions.length > 0))) {
        Menu() {
          if (this.controller) {
            MenuItemGroup() {
              MenuItem({ startIcon: this.theme.cutIcon, content: "剪切", labelInfo: "Ctrl+X" })
                .enabled(this.cutAndCopyEnable)
                .onClick(() => {
                  if (!this.controller) {
                    return
                  }
                  let richEditorSelection = this.controller.getSelection()
                  if (this.onCut) {
                    this.onCut({ content: richEditorSelection })
                  } else {
                    this.pushDataToPasteboard(richEditorSelection);
                    this.controller.deleteSpans({
                      start: richEditorSelection.selection[0],
                      end: richEditorSelection.selection[1]
                    })
                  }
                })
              MenuItem({ startIcon: this.theme.copyIcon, content: "复制", labelInfo: "Ctrl+C" })
                .enabled(this.cutAndCopyEnable)
                .onClick(() => {
                  if (!this.controller) {
                    return
                  }
                  let richEditorSelection = this.controller.getSelection()
                  if (this.onCopy) {
                    this.onCopy({ content: richEditorSelection })
                  } else {
                    this.pushDataToPasteboard(richEditorSelection);
                    this.controller.closeSelectionMenu()
                  }
                })
              MenuItem({ startIcon: this.theme.pasteIcon, content: "粘贴", labelInfo: "Ctrl+V" })
                .enabled(this.pasteEnable)
                .onClick(() => {
                  if (!this.controller) {
                    return
                  }
                  let richEditorSelection = this.controller.getSelection()
                  if (this.onPaste) {
                    this.onPaste({ content: richEditorSelection })
                  } else {
                    this.popDataFromPasteboard(richEditorSelection)
                    this.controller.closeSelectionMenu()
                  }
                })
              MenuItem({ startIcon: this.theme.selectAllIcon, content: "全选", labelInfo: "Ctrl+A" })
                .visibility(this.visibilityValue)
                .onClick(() => {
                  if (!this.controller) {
                    return
                  }
                  if (this.onSelectAll) {
                    let richEditorSelection = this.controller.getSelection()
                    this.onSelectAll({ content: richEditorSelection })
                  } else {
                    this.controller.setSelection(-1, -1)
                    this.visibilityValue = Visibility.None
                  }
                  this.controller.closeSelectionMenu()
                })
            }
          }
          if (this.controller && !this.showExpandedMenuOptions &&
            this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
            MenuItem({ content: "更多", endIcon: this.theme.arrowDownIcon })
              .onClick(() => {
                this.showExpandedMenuOptions = true
                this.customMenuSize = '100%'
              })
          } else if (this.showExpandedMenuOptions && this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
            ForEach(this.expandedMenuOptions, (expandedMenuOptionItem: ExpandedMenuOptions, index) => {
              MenuItem({
                startIcon: expandedMenuOptionItem.startIcon,
                content: expandedMenuOptionItem.content,
                endIcon: expandedMenuOptionItem.endIcon,
                labelInfo: expandedMenuOptionItem.labelInfo,
                builder: expandedMenuOptionItem.builder
              })
                .onClick(() => {
                  if (expandedMenuOptionItem.action) {
                    expandedMenuOptionItem.action()
                  }
                })
            })
          }
        }
        .onVisibleAreaChange([0.0, 1.0], () => {
          if (!this.controller) {
            return
          }
          let richEditorSelection = this.controller.getSelection()
          let start = richEditorSelection.selection[0]
          let end = richEditorSelection.selection[1]
          if (start !== end) {
            this.cutAndCopyEnable = true
          }
          if (start === 0 && this.controller.getSpans({ start: end + 1, end: end + 1 }).length === 0) {
            this.visibilityValue = Visibility.None
          } else {
            this.visibilityValue = Visibility.Visible
          }
        })
        .radius(this.theme.containerBorderRadius)
        .clip(true)
        .width(this.theme.defaultMenuWidth)
      } else if (this.showCustomerIndex > -1 && this.builder) {
        if (this.customerChange) {
          this.builder()
        } else {
          this.builder()
        }
      }
    }
    .width(this.theme.defaultMenuWidth)
  }
}

@Builder
export function SelectionMenu(options: SelectionMenuOptions) {
  SelectionMenuComponent({
    editorMenuOptions: options.editorMenuOptions,
    expandedMenuOptions: options.expandedMenuOptions,
    controller: options.controller,
    onPaste: options.onPaste,
    onCopy: options.onCopy,
    onCut: options.onCut,
    onSelectAll: options.onSelectAll
  })
}