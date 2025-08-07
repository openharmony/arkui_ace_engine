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
  UserView,
  Visibility,
  VisibleAreaEventOptions,
  VisibleAreaChangeCallback,
  Checkbox,
  cursorControl,
  PointerStyle,
  NavDestination,
  NavPathStack,
  NavDestinationContext
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins

import hilog from '@ohos.hilog'
import componentUtils from '@ohos.arkui.componentUtils'
import curves from '@ohos.curves';


@Component
export struct FocusTest {
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

        .stateStyles(undefined)
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
          .onKeyEventDispatch((event: KeyEvent): boolean => {
            hilog.info(0x0000, 'testTag', 'lisitao onKeyEvent');
            return true
          })
          .onFocus(() => {
            hilog.info(0x0000, 'testTag', 'lisitao onFocus');
          })
          .onBlur(() => {
            hilog.info(0x0000, 'testTag', 'lisitao onBlur');
          })
          .onAttach((): void => {
            hilog.info(0x0000, 'testTag', 'lisitao onAttach');
          })
          .onDetach((): void => {
            hilog.info(0x0000, 'testTag', 'lisitao onDetach');
          })
          .keyboardShortcut(FunctionKey.F5, [], () : void => {
            hilog.info(0x0000, 'testTag', 'lisitao keyboardShortcut');
          })
        .keyboardShortcut('w', [ModifierKey.CTRL], undefined)
        .backgroundImage('/comment/startIcon.png', ImageRepeat.X)
        .onKeyEventDispatch((event: KeyEvent): boolean => {
          hilog.info(0x0000, 'testTag', 'lisitao onKeyEventDispatch');

          return true
        })
        .onKeyEvent((event: KeyEvent): boolean => {
          hilog.info(0x0000, 'testTag', 'lisitao onKeyEvent 1');
          event.stopPropagation();
          hilog.info(0x0000, 'testTag', 'lisitao onKeyEvent 2');
          return false
        })
        .onKeyPreIme((event: KeyEvent): boolean => {
          hilog.info(0x0000, 'testTag', 'lisitao onKeyPreIme');
          return true
        })

        Button('First Button 2')
          .id('button2')
          .width(260)
          .height(70)

        Button('First Button 3')
          .id('button3')
          .width(260)
          .height(70)
          .backgroundImageSize({ width: 100, height: 100 } as SizeOptions)
          .backgroundImagePosition({ x: -10, y: -10 } as Position)
          .backgroundImage($r('app.media.startIcon'), ImageRepeat.X)
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

      Text(this.stateVar)
        .fontSize(20)
        .onVisibleAreaChange([0.0, 1.0], (isExpanding: boolean, currentRatio: number): void => {
          hilog.info(0x0000, 'testTag', 'lisitao onVisibleAreaChange');
        })
        .onAreaChange((oldValue: Area, newValue: Area) => {
          hilog.info(0x0000, 'testTag', 'lisitao onAreaChange');
        })
        .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions): void => {
          hilog.info(0x0000, 'testTag', 'lisitao onSizeChange');
        })
        .onVisibleAreaApproximateChange({ ratios: [0.0, 1.0], expectedUpdateInterval: 1000 } as VisibleAreaEventOptions,
          (isExpanding: boolean, currentRatio: number): void => {
            hilog.info(0x0000, 'testTag', 'Test Text isExpanding: ' + isExpanding + ', currentRatio:' + currentRatio);
        } as VisibleAreaChangeCallback)
    }
    }
    .title('焦点按键基础功能')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';

  build() {
    Text(this.stateVar).fontSize(50)
  }
}