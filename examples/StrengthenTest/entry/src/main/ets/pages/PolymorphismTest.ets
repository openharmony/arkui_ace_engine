import {
  __memo_context_type,
  __memo_id_type,
  memo,
  MutableState,
  observableProxy,
  Require,
  State,
  StateDecoratedVariable,
  stateOf,
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import {
  $r,
  Alignment,
  Area,
  Builder,
  Button,
  ButtonAttribute,
  Callback,
  ClickEffect,
  ClickEffectLevel,
  ClickEvent,
  Color,
  ColorMetrics,
  Column,
  CommonMethod,
  Component,
  CustomBuilder,
  CustomStyles,
  focusControl,
  FocusPriority,
  FrameNode,
  FunctionKey,
  Image,
  ImageRepeat,
  KeyEvent,
  KeyProcessingMode,
  LengthMetrics,
  ModifierKey,
  NodeController,
  Position,
  Radio,
  SizeOptions,
  StateStyles,
  Text,
  TextAttribute,
  TextInput,
  UIContext,
  UserView,
  Visibility,
  VisibleAreaEventOptions,
  VisibleAreaChangeCallback,
  Checkbox,
  cursorControl,
  PointerStyle,
  NavDestination, 
  NavPathStack,
  NavDestinationContext,
  Callback
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import componentUtils from '@ohos.arkui.componentUtils'
import curves from '@ohos.curves';

@Component
export struct PolymorphismTest {
  @State stateVar: string = 'state var';
  message: string = 'var';
  @State isShow: boolean = true
  @State btColor: Color = Color.Black;

  normalStyles: CustomStyles = (instance: CommonMethod): void => {
    hilog.info(0x0000, 'testTag', 'normal' + instance);
    instance.backgroundColor('#FFFF0000');
  }
  pressedStyles: CustomStyles = (instance: CommonMethod): void => {
    hilog.info(0x0000, 'testTag', 'normal' + instance);
    instance.backgroundColor('#FF000000');
  }

  NormalStyles(instance: CommonMethod) {
    instance.backgroundColor('#FFFF0000');
  }

  changeValue() {
    this.stateVar += '~'
  }

  @Builder
  renderBackground() {
    Column() {
      Text('sssssssss').width(100).height(100).backgroundColor('#FFFF0000')
    }.backgroundColor('#FFFF0000')
  }

  build() {
    NavDestination() {
      Column(undefined) {
        Button(this.message)
        .backgroundColor('#FFFF00FF')
        .stateStyles({
          normal: this.NormalStyles,
          pressed: this.pressedStyles
        })
        .stateStyles({
          pressed: this.NormalStyles,
        })
        .onClick((e: ClickEvent) => {
          hilog.info(0x0000, 'testTag', 'lisitao On Click 0');
          this.getUIContext().getCursorController().setCursor(PointerStyle.NORTH_SOUTH)
          hilog.info(0x0000, 'testTag', 'lisitao On Click 1');

          this.isShow = !this.isShow
          this.changeValue()
        })
        Column() {
          Button('First Button 1')
          .id('button1')
          .background(this.renderBackground)
          .width(260)
          .height(70)
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'lisitao First Button 1 onClick');
            this.getUIContext().getCursorController().restoreDefault()
          })
          Button('First Button 2')
          .id('button2')
          .width(260)
          .height(70)

          Button('First Button 3')
          .id('button3')
          .width(260)
          .height(70)
      }
      .onKeyEvent((event: KeyEvent): boolean => {
        event.stopPropagation();
        hilog.info(0x0000, 'testTag', 'lisitao Column onKeyEvent');
        return true
      })
      .focusScopePriority('column1', FocusPriority.PRIOR)

        Column() {
          Button('First Button 1')
          .width(260)
          .height(70)
          Button('First Button 2')
          .width(260)
          .height(70)
          Button('First Button 3')
          .width(260)
          .height(70)
        }
      .focusScopeId('column1', false, false)
      }
    }
    .title('多态样式基础功能')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';

  build() {
    Text(this.stateVar).fontSize(50)
  }
}