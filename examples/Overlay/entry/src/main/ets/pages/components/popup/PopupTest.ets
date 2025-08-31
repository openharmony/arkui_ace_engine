/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { MyComponent } from './MyComponenet'
import { extraParamsOption } from './model'

@Builder
export function PopupTestBuilder(name: string, param: Object) {
  PopupTestExample()
}

@Extend(Column)
function pinkColumnStyle() {
  .width(30).height(30)
  .borderWidth(1.0)
  .backgroundColor(Color.Pink)
}

@Extend(Text)
function textStyle() {
  .fontSize(9)
  .fontColor(0x000000)
  .width('100%')
}

@Extend(Row)
function rowStyle() {
  .width(200)
  .height(80)
  .padding(5)
  .backgroundColor(0xAFEEEE)
}

class MyDataSource implements IDataSource {
  private list: number[] = []

  constructor(list: number[]) {
    this.list = list
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): number {
    return this.list[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct PopupTestExample {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State customPopupList: boolean[] = [false, false, false, false, false, false, false,]
  @State showInSubWindow: boolean = false
  private swiperController: SwiperController = new SwiperController()
  private data: MyDataSource = new MyDataSource([])
  @State numbers: string[] = ['one', 'two', 'three', 'four', 'five', 'six']
  @State text: string = ''
  @State bool: boolean = true
  @State eventType: string = ''
  @State appleVisible: Visibility = Visibility.Visible
  @State orangeVisible: Visibility = Visibility.Visible
  @State bananaVisible: Visibility = Visibility.Visible
  private dragList: string[] = ['apple', 'orange', 'banana']
  @State fruitVisible: Visibility[] = [Visibility.Visible, Visibility.Visible, Visibility.Visible]
  @State idx: number = 0
  @State index: number = 0
  private scroller1: Scroller = new Scroller()
  @State gapHeight: number = 100
  @State info: string = 'Info: 初始值'
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State positionX: number = 0
  @State positionY: number = 0
  @State scaleValue: number = 1
  @State pinchValue: number = 1
  @State angle: number = 0
  @State rotateValue: number = 0
  @State rotateAngle: number = 0
  @State isShowSubWindow: boolean = false
  private panOption: PanGestureOptions = new PanGestureOptions({
    direction: PanDirection.All,
    distance: 1
  })

  aboutToAppear(): void {
    let list: number[] = []
    for (let i = 1; i <= 10; i++) {
      list.push(i);
    }
    this.data = new MyDataSource(list)
  }

  @Builder
  pixelMapBuilder() {
    Column() {
      Text(this.text)
        .width('50%')
        .height(60)
        .fontSize(16)
        .borderRadius(10)
        .textAlign(TextAlign.Center)
        .backgroundColor(Color.Red)
    }
  }

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
        .fontSize(16)
        .lineHeight(22)
        .margin({ top: 0, bottom: 5 })
    }
    .margin({ top: 10 })
    .borderWidth(1.0)
    .width('100%')
  }

  //设置Swiper的builder
  @Builder
  swiperInPopupBuilder() {
    Column({ space: 5 }) {
      Swiper(this.swiperController) {
        LazyForEach(this.data, (item: string) => {
          Text(item.toString())
            .width('90%')
            .height(160)
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }, (item: string) => item)
      }
      .index(1)
      .indicator(Indicator.digit())
      .displayArrow(true, false)

      Row({ space: 12 }) {
        Button('showNext')
          .fontSize(11)
          .backgroundColor(Color.Blue)
          .onClick(() => {
            this.swiperController.showNext()
          })
        Button('showPrevious')
          .fontSize(11)
          .backgroundColor(Color.Blue)
          .onClick(() => {
            this.swiperController.showPrevious()
          })
      }
    }
    .width('75%')
    .margin({ top: 10, bottom: 10 })
  }

  //设置List和拖拽的builder
  @Builder
  listAndDragInPopupBuilder() {
    Column() {
      Text('There are three Text elements here')
        .fontSize(12)
        .width('90%')
        .textAlign(TextAlign.Start)
        .margin(5)
      Row({ space: 15 }) {
        ForEach(this.dragList, (item: string, index) => {
          Text(item)
            .padding(5)
            .borderWidth(1.0)
            .backgroundColor(0xAFEEEE)
            .visibility(this.fruitVisible[index])
            .onDragStart(() => {
              this.bool = true
              this.text = item
              this.fruitVisible[index] = Visibility.None
              return this.pixelMapBuilder
            })
            .onTouch((event: TouchEvent) => {
              if (event.type === TouchType.Down) {
                this.eventType = 'Down'
                this.idx = index
              }
              if (event.type === TouchType.Up) {
                this.eventType = 'Up'
                if (this.bool) {
                  this.fruitVisible[index] = Visibility.Visible
                }
              }
            })
        })
      }.padding({ top: 10, bottom: 10 })

      Text('This is a List element')
        .fontSize(12)
        .width('90%')
        .textAlign(TextAlign.Start)
        .margin(5)
      List({ space: 20, scroller: this.scroller1 }) {
        ForEach(this.numbers, (item: string) => {
          ListItem() {
            Text(item)
              .width('100%')
              .height(80)
              .fontSize(16)
              .borderRadius(10)
              .textAlign(TextAlign.Center)
              .backgroundColor(0xAFEEEE)
          }
        }, (item: string) => item)
      }
      //.editMode(true)
      .height('65%')
      .width('90%')
      .padding(15)
      .divider({
        strokeWidth: 2,
        color: 0xFFFFFF,
        startMargin: 20,
        endMargin: 20
      })
      .onDragEnter((event: DragEvent, extraParams: string) => {
        console.log('List onDragEnter, ' + extraParams + 'X:' + event.getWindowX() + 'Y:' + event.getWindowY())
      })
      .onDragMove((event: DragEvent, extraParams: string) => {
        console.log('List onDragMove, ' + extraParams + 'X:' + event.getWindowX() + 'Y:' + event.getWindowY())
      })
      .onDragLeave((event: DragEvent, extraParams: string) => {
        console.log('List onDragLeave, ' + extraParams + 'X:' + event.getWindowX() + 'Y:' + event.getWindowY())
      })
      .onDrop((event: DragEvent, extraParams: string) => {
        let jsonString: extraParamsOption = JSON.parse(extraParams);
        if (this.bool) {
          // 通过splice方法插入元素
          this.numbers.splice(jsonString.insertIndex, 0, this.text)
          this.bool = false
        }
        this.fruitVisible[this.idx] = Visibility.None
      })
      .scrollBar(BarState.Off)
      .onAppear(() => {
        this.scroller1.scrollEdge(Edge.Bottom)
      })
    }
    .width('75%')
    .height(300)
    .margin({ top: 20 })
  }

  //设置Tabs的builder
  @Builder
  tabInPopupBuilder() {
    Tabs({ barPosition: BarPosition.Start }) {
      TabContent() {
        Column().width('100%').height('100%').backgroundColor('#00CB87')
      }.tabBar(this.tabBuilder(0, 'green'))

      TabContent() {
        Column().width('100%').height('100%').backgroundColor('#007DFF')
      }.tabBar(this.tabBuilder(1, 'blue'))

      TabContent() {
        Column().width('100%').height('100%').backgroundColor('#FFBF00')
      }.tabBar(this.tabBuilder(2, 'yellow'))

      TabContent() {
        Column().width('100%').height('100%').backgroundColor('#E67C92')
      }.tabBar(this.tabBuilder(3, 'pink'))
    }
    .width('80%')
    .backgroundColor(Color.Transparent)
    .vertical(false)
    .barMode(BarMode.Fixed)
    .barHeight(56)
    .animationDuration(400)
    .width(200)
    .height(100)
  }

  //设置文本输入的builder
  @Builder
  textInputInBuilder() {
    Column({ space: 5 }) {
      TextInput({ placeholder: '普通TextInput' }).enterKeyType(EnterKeyType.Send)
      TextArea({ placeholder: '普通TextArea' }).borderWidth(1)
    }.width('50%').padding(10)
  }

  //设置手势交互的builder
  @Builder
  gestureInPopupBuilder() {
    Column({ space: 10 }) {

      Row({ space: 2 }) {
        Text('双击/长按手势').fontSize(10)
      }
      .rowStyle()
      .gesture(
        TapGesture({ count: 2 })
          .onAction((event: GestureEvent) => {
            this.info = `Info: Doubleclick`
          })
      )
      .gesture(
        LongPressGesture({ repeat: true })// 由于repeat设置为true，长按动作存在时会连续触发，触发间隔为duration（默认值500ms）
          .onAction((event: GestureEvent) => {
            this.info = `Info: LongPressGesture`

          })
      )

      Row({ space: 2 }) {
        Text('平移手势').fontSize(10)
      }
      .rowStyle()
      .translate({ x: this.offsetX, y: this.offsetY, z: 0 })
      .gesture(
        PanGesture(this.panOption)
          .onActionStart((event: GestureEvent) => {
            this.info = `Info: Pan start`
          })
          .onActionUpdate((event: GestureEvent) => {
            console.info(`Info: x=${event.offsetX},y=${event.offsetY}`)
            this.offsetX = this.positionX + event.offsetX
            this.offsetY = this.positionY + event.offsetY
            this.info = `Info: pan offsetX=${this.offsetX} \n offsetY=${this.offsetY}`
          })
          .onActionEnd(() => {
            this.positionX = this.offsetX
            this.positionY = this.offsetY
            this.info = `Info: Pan end`
          })
      )

      Row({ space: 2 }) {
        Text('缩放手势').fontSize(10)
      }
      .rowStyle()
      .scale({ x: this.scaleValue, y: this.scaleValue, z: 1 })
      .gesture(
        PinchGesture({ fingers: 2 })
          .onActionStart((event: GestureEvent) => {
            this.info = `Info: Pinch start`
          })
          .onActionUpdate((event: GestureEvent) => {
            this.scaleValue = this.pinchValue * event.scale
            this.info = `Info: Pinch scaleValue=${this.scaleValue}`
          })
          .onActionEnd(() => {
            this.pinchValue = this.scaleValue
            this.info = `Info: Pinch end`
          })
      )

      Row({ space: 2 }) {
        Text('旋转手势').fontSize(10)
      }
      .rowStyle()
      .rotate({ angle: this.angle })
      .gesture(
        RotationGesture()
          .onActionStart((event: GestureEvent) => {
            this.info = `Info: Rotation start`
          })
          .onActionUpdate((event: GestureEvent) => {
            this.angle = this.rotateValue + event.angle
            this.info = `Info: Rotation angle=${this.angle}`
          })
          .onActionEnd(() => {
            this.rotateValue = this.angle
            this.info = `Info: Rotation end`
          })
      )

      Row({ space: 2 }) {
        Text('轻扫手势').fontSize(10)
      }
      .rowStyle()
      .rotate({ angle: this.rotateAngle })
      .gesture(
        SwipeGesture({ direction: SwipeDirection.All })
          .onAction((event: GestureEvent) => {
            this.rotateAngle = event.angle
            this.info = `Info: Swipe`
          })
      )

      Row({ space: 2 }) {
        Text('拖拽手势').fontSize(10)
      }
      .rowStyle()
      .onDragStart(() => {
        this.info = `Info: DragStart`
      })

      Text(this.info)
        .fontSize(10)
        .width(200)

    }
    .width('70%')
    .padding(10)
  }

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 5 }) {
          Text('设置Swiper的popup:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('componentSwiper')
          .onClick(() => {
            this.customPopupList[0] = !this.customPopupList[0]
          })
          .bindPopup(this.customPopupList[0], {
            builder: this.swiperInPopupBuilder(),

            showInSubWindow: this.showInSubWindow,
            mask: true,
            placement: Placement.RightTop,
            popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[0] = false
              }
            }
          })

          Text('设置List和拖拽的popup:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('componentList')
          .onClick(() => {
            this.customPopupList[1] = !this.customPopupList[1]
          })
          .bindPopup(this.customPopupList[1], {
            builder: this.listAndDragInPopupBuilder(),

            showInSubWindow: this.showInSubWindow,
            mask: true,
            placement: Placement.RightTop,
            popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[1] = false
              }
            }
          })

          Text('设置Tabs的popup:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('componentTab')
          .onClick(() => {
            this.customPopupList[2] = !this.customPopupList[2]
          })
          .bindPopup(this.customPopupList[2], {
            builder: this.tabInPopupBuilder(),

            showInSubWindow: this.showInSubWindow,
            mask: true,
            placement: Placement.RightTop,
            //popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[2] = false
              }
            }
          })
          Text('设置文本输入的popup:')
            .textStyle()
          Column({ space: 5 }) {
          Text('调整Popup避让输入法的位置')
          .textStyle()
          Row({ space: 10 }) {
          MyComponent({
          title: 'height+50', func: () => {
          this.gapHeight += 50
          }
          })
          MyComponent({
          title: 'height-50', func: () => {
          this.gapHeight -= 50

                      if (this.gapHeight <= 0) {
                        this.gapHeight = 50
                      }
                    }
                  })
                }
              }
              .height(this.gapHeight)
              .borderWidth(1.0)
              .backgroundColor(Color.Pink)

              Column() {
              }
              .pinkColumnStyle()
              .key('componentTextInput')
              .onClick(() => {
                this.customPopupList[3] = !this.customPopupList[3]
              })
              .bindPopup(this.customPopupList[3], {
                builder: this.textInputInBuilder(),

                showInSubWindow: this.showInSubWindow,
                mask: true,
                placement: Placement.Right,
                popupColor: Color.Orange,
                onStateChange: (e) => {
                  console.info(JSON.stringify(e.isVisible))
                  if (!e.isVisible) {
                    this.customPopupList[3] = false
                  }
                }
              })

          Text('设置手势事件的popup:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('eventGesture')
          .onClick(() => {
            this.customPopupList[4] = !this.customPopupList[4]
          })
          .bindPopup(this.customPopupList[4], {
            builder: this.gestureInPopupBuilder(),

            showInSubWindow: this.showInSubWindow,
            mask: true,
            placement: Placement.Right,
            popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[4] = false
              }
            }
          })
        }
        .alignItems(HorizontalAlign.Start)
        .width('100%').height('100%')
        .padding(10)
      }
      .width('100%').height('100%')
    }
    .title('PopupTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}