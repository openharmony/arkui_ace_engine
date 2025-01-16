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
import common from '@ohos.app.ability.common';
import { SymbolGlyphModifier } from '@kit.ArkUI';

const WITHOUT_BUILDER = -2
const MAX_FONT_STANDARD = 1.0
const MAX_FONT_SCALE = 2.0
const SYMBOL_SIZE: number = 24;

export interface EditorMenuOptions {
  icon: ResourceStr
  symbolStyle?: SymbolGlyphModifier
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

interface SelectionMenuSymbolTheme {
  fontSize: string;
  fontColor: Array<ResourceColor>;
  symbolCutIcon: SymbolGlyphModifier;
  symbolCopyIcon: SymbolGlyphModifier;
  symbolPasteIcon: SymbolGlyphModifier;
  symbolSelectAllIcon: SymbolGlyphModifier;
  symbolShareIcon: SymbolGlyphModifier;
  symbolTranslateIcon: SymbolGlyphModifier;
  symbolSearchIcon: SymbolGlyphModifier;
  symbolArrowDownIcon: SymbolGlyphModifier;
}

interface SelectionMenuTheme {
  imageSize: number;
  buttonSize: number;
  menuSpacing: number;
  expandedOptionPadding: number;
  defaultMenuWidth: number;
  menuItemPadding: Resource;
  imageFillColor: Resource;
  backGroundColor: Resource;
  iconBorderRadius: Resource;
  containerBorderRadius: Resource;
  borderWidth: Resource;
  borderColor: Resource;
  outlineWidth: Resource;
  outlineColor: Resource;
  cutIcon: Resource;
  copyIcon: Resource;
  pasteIcon: Resource;
  selectAllIcon: Resource;
  shareIcon: Resource;
  translateIcon: Resource;
  searchIcon: Resource;
  arrowDownIcon: Resource;
  iconPanelShadowStyle: ShadowStyle;
  defaultSymbolTheme: SelectionMenuSymbolTheme;
}

const defaultTheme: SelectionMenuTheme = {
  imageSize: 24,
  buttonSize: 40,
  menuSpacing: 8,
  expandedOptionPadding: 4,
  defaultMenuWidth: 224,
  menuItemPadding: $r('sys.float.padding_level1'),
  imageFillColor: $r('sys.color.ohos_id_color_primary'),
  backGroundColor: $r('sys.color.ohos_id_color_dialog_bg'),
  iconBorderRadius: $r('sys.float.corner_radius_level2'),
  containerBorderRadius: $r('sys.float.corner_radius_level4'),
  borderWidth: $r('sys.float.ohos_id_menu_inner_border_width'),
  borderColor: $r('sys.color.ohos_id_menu_inner_border_color'),
  outlineWidth: $r('sys.float.ohos_id_menu_outer_border_width'),
  outlineColor: $r('sys.color.ohos_id_menu_outer_border_color'),
  cutIcon: $r("sys.media.ohos_ic_public_cut"),
  copyIcon: $r("sys.media.ohos_ic_public_copy"),
  pasteIcon: $r("sys.media.ohos_ic_public_paste"),
  selectAllIcon: $r("sys.media.ohos_ic_public_select_all"),
  shareIcon: $r("sys.media.ohos_ic_public_share"),
  translateIcon: $r("sys.media.ohos_ic_public_translate_c2e"),
  searchIcon: $r("sys.media.ohos_ic_public_search_filled"),
  arrowDownIcon: $r("sys.media.ohos_ic_public_arrow_down"),
  iconPanelShadowStyle: ShadowStyle.OUTER_DEFAULT_SM,
  defaultSymbolTheme: {
    fontSize: `${SYMBOL_SIZE}vp`,
    fontColor: [$r('sys.color.ohos_id_color_primary')],
    symbolCutIcon: new SymbolGlyphModifier($r('sys.symbol.cut')),
    symbolCopyIcon: new SymbolGlyphModifier($r('sys.symbol.plus_square_on_square')),
    symbolPasteIcon: new SymbolGlyphModifier($r('sys.symbol.plus_square_dashed_on_square')),
    symbolSelectAllIcon: new SymbolGlyphModifier($r('sys.symbol.checkmark_square_on_square')),
    symbolShareIcon: new SymbolGlyphModifier($r('sys.symbol.share')),
    symbolTranslateIcon: new SymbolGlyphModifier($r('sys.symbol.translate_c2e')),
    symbolSearchIcon: new SymbolGlyphModifier($r('sys.symbol.magnifyingglass')),
    symbolArrowDownIcon: new SymbolGlyphModifier($r('sys.symbol.chevron_down')),
  },
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
  @State fontScale: number = 1
  @State customMenuWidth: number = this.theme.defaultMenuWidth
  @State horizontalMenuHeight: number = 0
  @State horizontalMenuWidth: number = this.theme.defaultMenuWidth
  private fontWeightTable: string[] =
    ["100", "200", "300", "400", "500", "600", "700", "800", "900", "bold", "normal", "bolder", "lighter", "medium",
      "regular"]
  private isFollowingSystemFontScale: boolean = false
  private appMaxFontScale: number = 3.2

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
    let uiContext: UIContext = this.getUIContext()
    if (uiContext) {
      this.isFollowingSystemFontScale = uiContext.isFollowingSystemFontScale()
      this.appMaxFontScale = uiContext.getMaxFontScale()
    }
    this.fontScale = this.getFontScale()
  }

  hasSystemMenu(): boolean {
    let showMenuOption = this.showCustomerIndex === -1 &&
        (this.controller || (this.expandedMenuOptions && this.expandedMenuOptions.length > 0))
    let showBuilder = this.showCustomerIndex > -1 && this.builder
    return Boolean(showMenuOption || showBuilder)
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
      .shadow(this.theme.iconPanelShadowStyle)
      .borderRadius(this.theme.containerBorderRadius)
      .outline(this.hasSystemMenu() ? { width: this.theme.outlineWidth, color: this.theme.outlineColor,
        radius: this.theme.containerBorderRadius } : undefined)
      .constraintSize({
        maxHeight: `calc(100% - ${this.horizontalMenuHeight > 0 ? this.horizontalMenuHeight + this.theme.menuSpacing : 0}vp)`,
        minWidth: this.theme.defaultMenuWidth
      })
    }
    .useShadowBatching(true)
    .constraintSize({
      maxHeight: '100%',
      minWidth: this.theme.defaultMenuWidth
    })
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
    let numOfBtnPerRow = 5
    let width = this.fontScale > MAX_FONT_SCALE ? this.customMenuWidth : this.theme.defaultMenuWidth;
    if (this.editorMenuOptions && this.editorMenuOptions.length <= numOfBtnPerRow) {
      return (width - this.theme.expandedOptionPadding * 2) / this.editorMenuOptions.length
    }
    return (width - this.theme.expandedOptionPadding * 2) / numOfBtnPerRow
  }

  measureFlexPadding(): number {
    return Math.floor((this.theme.expandedOptionPadding - px2vp(2.0)) * 10) / 10
  }

  getFontScale(): number {
    try {
      let uiContext: UIContext = this.getUIContext();
      let systemFontScale = (uiContext.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(systemFontScale, this.appMaxFontScale);
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    this.fontScale = this.getFontScale();
    let sizeResult: SizeResult = { height: 0, width: 0 };
    children.forEach((child) => {
      let childMeasureResult: MeasureResult = child.measure(constraint);
      sizeResult.width = childMeasureResult.width;
      sizeResult.height = childMeasureResult.height;
    });
    return sizeResult;
  }

  @Builder
  IconPanel() {
    Flex({ wrap: FlexWrap.Wrap }) {
      if (this.editorMenuOptions) {
        ForEach(this.editorMenuOptions, (item: EditorMenuOptions, index: number) => {
          Button() {
            if (item.symbolStyle !== undefined) {
              SymbolGlyph()
                .fontColor(this.theme.defaultSymbolTheme.fontColor)
                .attributeModifier(item.symbolStyle)
                .focusable(true)
                .draggable(false)
                .effectStrategy(SymbolEffectStrategy.NONE)
                .symbolEffect(new SymbolEffect(), false)
                .fontSize(this.theme.defaultSymbolTheme.fontSize)
            } else {
              if (Util.isSymbolResource(item.icon)) {
                SymbolGlyph(item.icon as Resource)
                  .fontColor(this.theme.defaultSymbolTheme.fontColor)
                  .focusable(true)
                  .draggable(false)
                  .fontSize(this.theme.defaultSymbolTheme.fontSize)
              } else {
                Image(item.icon)
                  .width(this.theme.imageSize)
                  .height(this.theme.imageSize)
                  .fillColor(this.theme.imageFillColor)
                  .focusable(true)
                  .draggable(false)
              }

            }
          }
          .enabled(!(!item.action && !item.builder))
          .type(ButtonType.Normal)
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
      let newValueWidth = newValue.width as number
      this.horizontalMenuHeight = newValueHeight
      this.horizontalMenuWidth = newValueWidth
    })
    .clip(true)
    .width(this.fontScale > MAX_FONT_SCALE ? this.customMenuWidth : this.theme.defaultMenuWidth)
    .padding({ top: this.measureFlexPadding(), bottom: this.measureFlexPadding(),
      left: this.measureFlexPadding() - 0.1, right: this.measureFlexPadding() - 0.1 })
    .borderRadius(this.theme.containerBorderRadius)
    .margin({ bottom: this.theme.menuSpacing })
    .backgroundColor(this.theme.backGroundColor)
    .shadow(this.theme.iconPanelShadowStyle)
    .border({ width: this.theme.borderWidth, color: this.theme.borderColor,
      radius: this.theme.containerBorderRadius })
    .outline({ width: this.theme.outlineWidth, color: this.theme.outlineColor,
      radius: this.theme.containerBorderRadius })
  }

  @Builder
  SystemMenu() {
    Column() {
      if (this.showCustomerIndex === -1 &&
        (this.controller || (this.expandedMenuOptions && this.expandedMenuOptions.length > 0))) {
        Menu() {
          if (this.controller) {
            MenuItemGroup() {
              MenuItem({
                startIcon: this.theme.cutIcon,
                symbolStartIcon: this.theme.defaultSymbolTheme.symbolCutIcon,
                content: '剪切',
                labelInfo: 'Ctrl+X'
              })
                .enabled(this.cutAndCopyEnable)
                .height(this.fontScale > MAX_FONT_STANDARD ? 'auto' : this.theme.buttonSize)
                .borderRadius(this.theme.iconBorderRadius)
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
              MenuItem({
                startIcon: this.theme.copyIcon,
                symbolStartIcon: this.theme.defaultSymbolTheme.symbolCopyIcon,
                content: '复制',
                labelInfo: 'Ctrl+C'
              })
                .enabled(this.cutAndCopyEnable)
                .height(this.fontScale > MAX_FONT_STANDARD ? 'auto' : this.theme.buttonSize)
                .borderRadius(this.theme.iconBorderRadius)
                .margin({ top: this.theme.menuItemPadding })
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
              MenuItem({
                startIcon: this.theme.pasteIcon,
                symbolStartIcon: this.theme.defaultSymbolTheme.symbolPasteIcon,
                content: '粘贴',
                labelInfo: 'Ctrl+V'
              })
                .enabled(this.pasteEnable)
                .height(this.fontScale > MAX_FONT_STANDARD ? 'auto' : this.theme.buttonSize)
                .borderRadius(this.theme.iconBorderRadius)
                .margin({ top: this.theme.menuItemPadding })
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
              MenuItem({
                startIcon: this.theme.selectAllIcon,
                symbolStartIcon: this.theme.defaultSymbolTheme.symbolSelectAllIcon,
                content: '全选',
                labelInfo: 'Ctrl+A'
              })
                .visibility(this.visibilityValue)
                .height(this.fontScale > MAX_FONT_STANDARD ? 'auto' : this.theme.buttonSize)
                .borderRadius(this.theme.iconBorderRadius)
                .margin({ top: this.theme.menuItemPadding })
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
            MenuItem({
              content: '更多',
              endIcon: this.theme.arrowDownIcon,
              symbolEndIcon: this.theme.defaultSymbolTheme.symbolArrowDownIcon
            })
              .height(this.fontScale > MAX_FONT_STANDARD ? 'auto' : this.theme.buttonSize)
              .borderRadius(this.theme.iconBorderRadius)
              .margin({ top: this.theme.menuItemPadding })
              .onClick(() => {
                this.showExpandedMenuOptions = true
              })
          } else if (this.showExpandedMenuOptions && this.expandedMenuOptions && this.expandedMenuOptions.length > 0) {
            ForEach(this.expandedMenuOptions, (expandedMenuOptionItem: ExpandedMenuOptions, index) => {
              MenuItem({
                startIcon: expandedMenuOptionItem.startIcon,
                symbolStartIcon: expandedMenuOptionItem.symbolStartIcon,
                content: expandedMenuOptionItem.content,
                endIcon: expandedMenuOptionItem.endIcon,
                symbolEndIcon: expandedMenuOptionItem.symbolEndIcon,
                labelInfo: expandedMenuOptionItem.labelInfo,
                builder: expandedMenuOptionItem.builder
              })
                .height(this.fontScale > MAX_FONT_STANDARD ? 'auto' : this.theme.buttonSize)
                .borderRadius(this.theme.iconBorderRadius)
                .margin({ top: this.theme.menuItemPadding })
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
        .width(this.fontScale > MAX_FONT_SCALE ? 'auto' : this.theme.defaultMenuWidth)
        .constraintSize({
          minWidth: this.theme.defaultMenuWidth
        })
        .onAreaChange((oldValue: Area, newValue: Area) => {
          let newValueWidth = newValue.width as number
          this.customMenuWidth =
            this.fontScale > MAX_FONT_SCALE && newValueWidth > this.theme.defaultMenuWidth ? newValueWidth :
            this.theme.defaultMenuWidth
        })
      } else if (this.showCustomerIndex > -1 && this.builder) {
        Column() {
          if (this.customerChange) {
            this.builder()
          } else {
            this.builder()
          }
        }
        .width(this.horizontalMenuWidth)
      }
    }
    .width(this.fontScale > MAX_FONT_SCALE ? 'auto' : this.theme.defaultMenuWidth)
    .shadow(this.theme.iconPanelShadowStyle)
    .border({ width: this.theme.borderWidth, color: this.theme.borderColor,
      radius: this.theme.containerBorderRadius })
    .constraintSize({
      minWidth: this.theme.defaultMenuWidth
    })
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

class Util {
  private static RESOURCE_TYPE_SYMBOL = 40000;

  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === Util.RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr | Resource | undefined): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}