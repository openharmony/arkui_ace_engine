import {
  memo,
  __memo_context_type,
  __memo_id_type,
  AppStorage,
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins

import hilog from '@ohos.hilog'
import {
  $r,
  Entry,
  Text,
  TextInput,
  Curve,
  ResourceColor,
  NavPathStack,
  NavDestination,
  Scroll,
  SheetMode,
  LengthMetrics,
  BlurStyle,
  HoverModeAreaType,
  TranslateOptions,
  SheetKeyboardAvoidMode,
  DismissContentCoverAction,
  ShadowType,
  EdgeColors,
  BorderStyle,
  EdgeStyles,
  LocalizedEdgeColors,
  CustomBuilder,
  SheetTitleOptions,
  EdgeWidths,
  LocalizedEdgeWidths,
  ScrollSizeMode,
  ShadowStyle,
  ShadowOptions,
  TextAttribute,
  Column,
  DismissReason,
  Component,
  Callback,
  Row,
  Button,
  SheetDismiss,
  SpringBackAction,
  ButtonAttribute,
  animateTo,
  Color,
  Dimension,
  Resource,
  ModalTransition,
  DismissSheetAction,
  ContentCoverOptions,
  SheetSize,
  Length,
  SheetType,
  SheetOptions,
  TransitionEffect,
  ClickEvent,
  UserView ,
  Builder,
  NavDestinationContext
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import { UIContext } from '@ohos.arkui.UIContext';


@Entry
@Component
export struct BindContentCoverTest {
  @State stateVar: string = 'state var';
  @State showVal: boolean =false;
  @State showVal1: boolean =false;
  @State showVal2: boolean =false;

  @State height: SheetSize|Length = SheetSize.LARGE
  @State width:Dimension = '80%'
  @State showDragBar:boolean = true
  @State sheetType: SheetType = SheetType.BOTTOM
  @State showClose:boolean|Resource = true


  @State scrollSizeMode: ScrollSizeMode = ScrollSizeMode.FOLLOW_DETENT
  @State mode:SheetMode = SheetMode.OVERLAY

  @State blurStyle: BlurStyle = BlurStyle.NONE
  @State maskColor: ResourceColor = Color.Red

  @State enableOutsideInteractive: boolean = true
  @State shadowStyle: ShadowStyle|ShadowOptions = ShadowStyle.OUTER_DEFAULT_SM

  @State borderStyle:	BorderStyle | EdgeStyles = BorderStyle.Dashed
  @State borderColor: ResourceColor | EdgeColors | LocalizedEdgeColors =  Color.Green
  @State borderWidth: undefined|EdgeWidths|LocalizedEdgeWidths|String|Resource|Double = '2vp'
  @State title:SheetTitleOptions | CustomBuilder = { title: $r('app.string.mytitle'), subtitle: $r('app.string.app_name') } as SheetTitleOptions
  @State hoverModeArea: HoverModeAreaType = HoverModeAreaType.BOTTOM_SCREEN
  @State keyboardAvoidMode: SheetKeyboardAvoidMode = SheetKeyboardAvoidMode.NONE
  @State modalTransition:ModalTransition =ModalTransition.DEFAULT

  @State fontSize:number = 20

  @Builder
  SheetBuilder() {
    Column(undefined) {
      Text('1111')
      Text('1111')
      Text('1111')
      Text('1111')
      Button('close bindContentCover').onClick((e: ClickEvent) => {
        this.showVal1 = false
        this.showVal = false
      })
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
      TextInput({text: ''})
    }
  }   

  build() {
    NavDestination() {
      Scroll() {
        Column(undefined) {
          Row() {
            Button('ModalTransition.ALPHA').onClick((e: ClickEvent) => {
              this.modalTransition = ModalTransition.ALPHA
            }).fontSize(10)
          }

          Button('bindContentCover')
            .onClick((e: ClickEvent) => {
              this.showVal1 = true
            })
            .backgroundColor('#FFFF00FF')
            .bindContentCover(this.showVal1, this.SheetBuilder,
              {
                modalTransition: this.modalTransition,
                backgroundColor: Color.Yellow,
                onAppear: () => {
                  hilog.info(0x0000, 'xhq', 'bindContentCover onAppear');
                },
                onWillAppear: () => {
                  hilog.info(0x0000, 'xhq', 'bindContentCover onWillAppear');
                },
                onWillDisappear: () => {
                  hilog.info(0x0000, 'xhq', 'bindContentCover onWillDisappear');
                },
                onDisappear: () => {
                  this.showVal1 = false
                  hilog.info(0x0000, 'xhq', 'bindContentCover onDisappear');
                }
              } as ContentCoverOptions)
        }.width('100%').height('100%')
      }.width('100%').height('100%')
    }
    .title('模态类组件测试001')
  }
}

@Component
struct Child {
  @State stateVar: string = 'Child';
  build() {
    Text(this.stateVar).fontSize(50)
  }
}
