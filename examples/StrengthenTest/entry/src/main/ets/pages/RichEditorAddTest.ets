import {
  memo,
  __memo_context_type,
  __memo_id_type,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  StyledStringChangeValue,
  StyledStringChangedListener,
  TextRange,
  Text,
  TextAttribute,
  Column,
  Row,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView ,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback,
  MenuOnAppearCallback,
  SelectionMenuOptions,
  ResponseType,
  RichEditorSpanType,
  RichEditorUpdateTextSpanStyleOptions,
  RichEditorParagraphStyle,
  RichEditorImageSpanOptions,
  RichEditorImageSpanStyle,
  RichEditorTextStyle,
  StyleOptions,
  LengthMetrics,
  StyledStringValue,
  StyledString,
  LetterSpacingStyle,
  BaselineOffsetStyle,
  TextShadowStyle,
  DecorationStyle,
  MutableStyledString,
  StyledStringKey,
  RichEditorStyledStringOptions,
  RichEditorInsertValue,
  RichEditorRange,
  CustomBuilder,
  Builder,
  RichEditorParagraphStyle,
  RichEditorTextSpanOptions,
  WordBreak,
  LayoutManager,
  MenuPolicy,
  $r,
  PasteEvent,
  RichEditorSelection,
  RichEditorTextSpanResult,
  Color,
  EnterKeyType,
  SubmitEvent,
  RichEditorChangeValue,
  RichEditorInsertValue,
  RichEditorDeleteValue,
  TextAlign,
  CopyEvent,
  RichEditor,
  RichEditorController,
  RichEditorStyledStringController,
  RichEditorAttribute,
  RichEditorOptions,
  RichEditorInsertValue
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'

@Component
export struct RichEditorAddTest {
  @State stateVar: string = 'state var';
  message: string = 'var';
  controller : RichEditorController = new RichEditorController()
  controller2 : RichEditorStyledStringController = new RichEditorStyledStringController()

  changeValue() {
    this.stateVar += '~'
  }

  build() {
    NavDestination() {
      Column(undefined) {
      Text('Hello World').fontSize(20)
      RichEditor({controller : this.controller} as RichEditorOptions)
        .height('100')
        .enablePreviewText(false)
        .backgroundColor('#FFFF00FF')
      Button('添加文本').backgroundColor('#FFFF00FF')
        .onClick((e: ClickEvent) => {
          this.controller.addTextSpan('hello world')
        })
      Text(this.stateVar).fontSize(20)
      Child({ stateVar: this.stateVar } as __Options_Child)
    }
    }
    .title('富文本输入框用例001')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';

  build() {
    Text(this.stateVar).fontSize(50)
  }
}
