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
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  TextInput,
  TextInputController,
  TextArea,
  TextAreaController,
  Color,
  CopyOptions,
  InputType,
  UnderlineColor,
  IconOptions,
  CancelButtonOptions,
  CancelButtonStyle,
  FontWeight,
  TextMenuItem,
  Resource,
  EditMenuOptions,
  TextRange,
  TextMenuItemId,
  EllipsisMode,
  TextOverflow,
  TextAlign,
  LengthMetrics,
  TextDecorationType,
  TextDecorationOptions,
  TextDecorationStyle,
  DecorationStyleInterface,
  Font,
  FontStyle,
  ShadowOptions,
  Callback,
  TextCase,
  TextHeightAdaptivePolicy,
  WordBreak,
  TextSelectableMode,
  LineBreakStrategy,
  MarqueeState,
  MarqueeStartPolicy,
  TextMarqueeOptions,
  ObscuredReasons,
  TextDataDetectorType,
  Builder,
  Menu,
  Span,
  ImageSpan,
  TextSpanType,
  TextResponseType,
  MenuItemGroup,
  ImageFit,
  ImageSpanAlignment,
  TextController,
  TextOptions,
  MenuItem,
  MenuItemOptions,
  TextRange,
  StyledStringValue,
  DecorationStyle,
  StyleOptions,
  StyledString,
  StyledStringKey,
  TextStyle,
  TextContentControllerOptions,
  EditableTextChangeValue,
  Margin,
  Search,
  SearchOptions,
  Marquee,
  MarqueeUpdateStrategy,
  MarqueeOptions,
  TextMenuShowMode,
  SymbolGlyph,
  NavDestination,
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import { $r } from 'arkui.component.common'

@Component
export struct TextTest {
  textAreaController: TextAreaController = new TextAreaController()
  textInputController: TextInputController = new TextInputController()

  build() {
    NavDestination() {
      Column(undefined) {
        Text('Text测试')
          .fontSize(12)
          .textAlign(TextAlign.Center)
          .margin({
            bottom: 0,
            top: 30,
            left: 0,
            right: 0
          } as Margin)
        Text('Hello World!')
          .copyOption(CopyOptions.InApp)
          .fontSize(60)
      }
    }
    .title('Text文本框用例001')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
