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
  CustomBuilder,
  SheetTitleOptions,
  ScrollSizeMode,
  TextAttribute,
  Column,
  Component,
  Callback,
  Row,
  Button,
  animateTo,
  Color,
  Dimension,
  Resource,
  SheetSize,
  Length,
  SheetType,
  SheetOptions,
  ClickEvent,
  UserView ,
  Builder,
  NavDestinationContext
} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins

import { UIContext } from '@ohos.arkui.UIContext';


@Entry
@Component
export struct BindSheetTest {
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


  @State enableOutsideInteractive: boolean = true

  @State title:SheetTitleOptions | CustomBuilder = { title: $r('app.string.mytitle'), subtitle: $r('app.string.app_name') } as SheetTitleOptions

  @State fontSize:number = 20
  @Builder
  titleBuilder() {
    Text('demo')
  }
  @Builder
  SheetBuilder() {
    Column(undefined) {
      Text('1111')
      Text('1111')
      Text('1111')
      Text('1111')
      Button('close bindsheet').onClick((e: ClickEvent) => {
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
            Button('showDragBar').onClick((e: ClickEvent) => {
              this.showDragBar = !this.showDragBar
            }).fontSize(10)
            Button('CENTER').onClick((e: ClickEvent) => {
              this.sheetType = SheetType.CENTER
            }).fontSize(10)
            Button('POPUP').onClick((e: ClickEvent) => {
              this.sheetType = SheetType.POPUP
            }).fontSize(10)
          }

          Row() {
            Button('height MEDIUM').onClick((e: ClickEvent) => {
              this.height = SheetSize.MEDIUM
            }).fontSize(10)
            Button('height FIT_CONTENT').onClick((e: ClickEvent) => {
              this.height = SheetSize.FIT_CONTENT
            }).fontSize(10)
            Button('height str 500').onClick((e: ClickEvent) => {
              this.height = '500'
            }).fontSize(10)

          }

          Row() {
            Button('height0').onClick((e: ClickEvent) => {
              this.height = 0
            }).fontSize(10)

            Button('height-10').onClick((e: ClickEvent) => {
              this.height = -10
            }).fontSize(10)
          }

          Row() {
            Button('width0').onClick((e: ClickEvent) => {
              this.width = 0
            }).fontSize(10)
            Button('width1900').onClick((e: ClickEvent) => {
              this.width = 1900
            }).fontSize(10)

            Button('width-10').onClick((e: ClickEvent) => {
              this.width = -10
            }).fontSize(10)
          }

          Row() {
            Button('showClose false').onClick((e: ClickEvent) => {
              this.showClose = false
            }).fontSize(10)
            Button('titleBuilder').onClick((e: ClickEvent) => {
              this.title = this.titleBuilder
            }).fontSize(10)
          }

          Row() {
            Button('showClose res true').onClick((e: ClickEvent) => {
              this.showClose = $r('app.boolean.true')
            }).fontSize(10)
            Button('showClose res false').onClick((e: ClickEvent) => {
              this.showClose = $r('app.boolean.false')
            }).fontSize(10)
          }

          Row() {
            Button('mode EMBEDDED').onClick((e: ClickEvent) => {
              this.mode = SheetMode.EMBEDDED
            }).fontSize(10)
          }

          Row() {
            Button('enableOutsideInteractive').onClick((e: ClickEvent) => {
              this.enableOutsideInteractive = !this.enableOutsideInteractive
            }).fontSize(10)
          }

          Row() {
            Button('bindSheet')
              .backgroundColor('#FFFF00FF')
              .fontSize(10)
              .onClick((e: ClickEvent) => {
                this.showVal = true
              })
              .bindSheet(this.showVal, this.SheetBuilder,
                {
                  preferType: this.sheetType,
                  showClose: this.showClose,
                  detents: [200, $r('app.float.400'), 2900],
                  width: this.width,
                  dragBar: this.showDragBar,
                  onAppear: () => {
                    hilog.info(0x0000, 'xhq', 'bindSheet onAppear');
                  },
                  onDisappear: () => {
                    this.showVal = false
                    hilog.info(0x0000, 'xhq', 'bindSheet onDisappear');
                  },
                  onWillAppear: () => {
                    hilog.info(0x0000, 'xhq', 'bindSheet onWillAppear');
                  },
                  onWillDisappear: () => {
                    hilog.info(0x0000, 'xhq', 'bindSheet onWillDisappear');
                  },
                  onHeightDidChange: (val: number) => {
                    hilog.info(0x0000, 'xhq', 'bindSheet onHeightDidChange:' + val);
                  },
                  onWidthDidChange: (val: number) => {
                    hilog.info(0x0000, 'xhq', 'bindSheet onWidthDidChange:' + val);
                  },
                  onDetentsDidChange: (val: number) => {
                    hilog.info(0x0000, 'xhq', 'bindSheet onDetentsDidChange：' + val);
                  },
                  onTypeDidChange: (val: SheetType) => {
                    hilog.info(0x0000, 'xhq', 'bindSheet onTypeDidChange:' + val);
                  },
                  scrollSizeMode: this.scrollSizeMode,
                  title: this.title,
                  enableOutsideInteractive: this.enableOutsideInteractive,
                  mode: this.mode,
                  backgroundColor: Color.Yellow,
                } as SheetOptions)
          }
        }.width('100%').height('100%')
      }.width('100%').height('100%')
    }
    .title('模态类组件测试001')
  }
}

