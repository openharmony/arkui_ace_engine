/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

function probe(tag: string): number {
    return Date.now()
}

@Entry
@Component
export struct Perf1 {
    @State value: number = 1
    @State single: string = ""
    @State depend: string = ""
    data: Array<string> = []
    COUNT: number = 10000

    aboutToAppear() {
        for (let i = 0; i < this.COUNT; i++) {
            this.data.push("item" + i.toString())
        }
    }

    build() {
      let before = probe("build1")
      Column() {
        Button("Increase")
            .onClick(() => {
                this.value++
                console.log("Clicked, now", this.value)
                if (this.value == 2) {
                    console.log("large update")
                    this.depend = "changed"
                }
                // Test remove elements.
                if (this.value == 3) {
                    console.log("large remove")
                    this.data.splice(0, this.COUNT / 2)
                }
                // Test add elements
                if (this.value == 4) {
                    console.log("large add")
                    for (let i = 0; i < this.COUNT / 2; i++) {
                        this.data.push("new")
                    }
                }
                // Test single element
                if (this.value == 5) {
                    console.log("update single")
                    this.single = "updated"
                }
            })
        ForEach(this.data, (item, index) => {
            this.value
            if (index! % 2 == 0) {
                Text(item + " " + this.depend)
                    .width(200)
                    .height(20)
                    .fontColor(0xff0000)
            } else if (index! == 41) {
                Text(this.single)
                    .width(150)
                    .height(30)
                    .fontColor(0x0000ff)
            } else {
                Text(item)
                    .width(150)
                    .height(30)
                    .fontColor(0x00ff00)
            }
        })
      }
      let after = probe("build2")
      console.log(`Took ${after - before}ms`)
    }
}

// Test Create and Delete 421 components. (1 Grid + 20 GridItems(each have 10 items in it))
//@Entry
@Component
export struct Perf2 {
  @State currentIndex: number = 0
  scroller: Scroller = new Scroller()
  private controller: TabsController = new TabsController()
  @State goodData: Array<any> = [{
    boo: true,
    img:"http://123.60.114.106:8090/file/downloadLocal?name=img1.jpg",
    hei: 200,
    introduce: '全实木餐桌椅组合黑胡桃木一桌四六椅简约现代新',
    price: '3,000',
    numb: '37人付款'
  },
  {
    boo: true,
    webimg:"https://contentcenter-test-bj4-001.obs.cn-north-4.myhuaweicloud.cn/testapp_test_900_9/f7/v3/cdtTMbD7QP2tTxx2dDfVBA/2_8.jpg",
    img:"http://123.60.114.106:8090/file/downloadLocal?name=img2.jpg",
    hei: 200,
    introduce: 'SIEMENS/西门子WM12P 2602W全自动滚筒洗衣机',
    price: '3,299',
    numb: '6人付款'
  }]
  @State firstNumber: number = 97
  @State needShow: boolean = true
  controllerVideo: VideoController = new VideoController();
  @LocalStorageLink('storageSimpleProp') simpleVarName: string = ''

  aboutToAppear() {
    setTimeout(async () => {
      let frameCount = 1
      while (true) {
        this.needShow = !this.needShow
        frameCount++;
        if (frameCount > 30) {
          break;
        }
        await new Promise((resolve) => setTimeout(resolve, 32))
      }
    }, 32)
  }

  build() {
    let before = probe("build1")
    Row() {
      Column() {
        Column() {
          if (this.needShow) {
            Grid(this.scroller) {
            if (this.currentIndex == 0) {
              for (let i = 0; i < 10; i++) {
                ForEach(this.goodData, (item, index) => {
                GridItem() {
                  if (item.boo) {
                    Navigator({ target: 'pages/productDetail/Index', type: NavigationType.Push }) {
                      Column() {
                        if (this.simpleVarName == 'true' || this.simpleVarName == 'default') {
                          if ((index ?? 0) % 20 == 0) {
                            Video({
                              src: `https://contentcenter-test-bj4-001.obs.cn-north-4.myhwclouds.com/test_media/hw264/twopass/10513129109511410900490_tp.mp4`,
                              controller: this.controllerVideo
                            })
                            .height(item.hei)
                            .autoPlay(true)
                            .controls(false)
                            .loop(true)
                            .width('100%')
                            .objectFit(ImageFit.Fill)
                          } else {
                            Image(item.webimg)
                              .height(item.hei)
                              .width('100%')
                              .objectFit(ImageFit.Fill)
                          }
                        }
                        else {
                          Image(item.img)
                            .height(item.hei)
                            .width('100%')
                            .objectFit(ImageFit.Fill)
                        }

                        Text(item.introduce)
                          .fontSize(14)
                          .padding({ left: 5, right: 5 })
                          .margin({ top: 5 })
                        Row() {
                          Row() {
                            Text('￥')
                              .fontSize(10)
                              .fontColor(Color.Red)
                              .baselineOffset(-4)
                            Text(item.price)
                              .fontSize(16)
                              .fontColor(Color.Red)
                            Text(item.numb)
                              .fontSize(10)
                              .fontColor(Color.Gray)
                              .baselineOffset(-4)
                              .margin({ left: 5 })
                          }

                          Image('app.media.photo63')
                            .width(20)
                            .height(10)
                            .margin({ bottom: -8 })
                        }
                        .width('100%')
                        .justifyContent(FlexAlign.SpaceBetween)
                        .padding({ left: 5, right: 5 })
                        .margin({ top: 15 })
                      }
                      .borderRadius(10)
                      .backgroundColor(Color.White)
                      .clip(true)
                      .width('100%')
                      .height(290)
                    }
                  } else {
                    Navigator({ target: 'pages/productDetail/Index', type: NavigationType.Push }) {
                      Column() {
                        if (this.simpleVarName == 'true' || this.simpleVarName == 'default') {
                          Image(item.webimg)
                            .height(item.hei)
                            .width('100%')
                            .objectFit(ImageFit.Fill)
                        } else {
                          Image(item.img)
                            .height(item.hei)
                            .width('100%')
                            .objectFit(ImageFit.Fill)
                        }

                        Column() {
                          Row() {
                            Image('app.media.photo62')
                              .height(15)
                              .width(50)
                              .margin({ bottom: -3 })
                              .objectFit(ImageFit.Fill)
                            Text('科普干货！轻松')
                              .fontSize(14)
                              .padding({ left: 5, right: 5 })
                              .margin({ top: 5 })
                          }

                          Row() {
                            Text('搞定包包的头一口有机奶粉')
                              .fontSize(14)
                              .padding({ left: 5, right: 5 })
                              .margin({ top: 5 })
                              .textOverflow({ overflow: TextOverflow.Ellipsis })
                              .maxLines(1)
                          }
                        }

                        Row() {
                          Row() {
                            Stack({ alignContent: Alignment.BottomEnd }) {
                              Image('app.media.photo56')
                                .height(25)
                                .width(25)
                                .margin({ left: -3 })
                              Image('app.media.photo53')
                                .height(10)
                                .width(10)
                                .margin({ right: -3 })
                            }

                            Text('家有萌娃')
                              .fontSize(10)
                              .fontColor(Color.Gray)
                              .baselineOffset(-4)
                              .margin({ left: 5 })
                          }
                          .margin({ bottom: 10 })
                        }
                        .width('100%')
                        .justifyContent(FlexAlign.SpaceBetween)
                        .padding({ left: 5, right: 5 })
                        .margin({ top: 15 })
                      }
                      .borderRadius(10)
                      .backgroundColor(Color.White)
                      .clip(true)
                      .width('100%')
                      .height(380)
                    }
                  }
                }
                }, (item) => JSON.stringify(item))
              }
            }
            }
            .scrollBar(BarState.OFF)
            .columnsGap(15)
            .rowsGap(10)
            .columnsTemplate('1fr 1fr')
            .width('100%')
            .height('100%')
          }
        }
        .width('100%')
        .height('100%')
      }
      .width('100%')
    }
    let after = probe("build2")
    console.log(`Took ${after - before}ms in ${this.needShow} flag`)
  }
}

// Test ForEach Update Feature (push, pop, reverse). (each data item has 120 items)
class CallLogListItemParam {
  showTitle: boolean = true;
  dateDetail: string = '';
  timeDetail: string = '';
  imgRes: string = '';
  simImgRes: string = '';
  formatNumber: string = '';
  talkTime: string = '';
}

//@Entry
@Component
struct Perf3 {
  @State contentData: Array<CallLogListItemParam> = []
  flag: string = 'initial'

  aboutToAppear() {
    setTimeout(async () => {
      let frameCount = 1;
      // push case.
      while (true) {
        let data = new CallLogListItemParam();
        data.dateDetail = frameCount.toString();
        data.timeDetail = frameCount.toString();
        data.imgRes = frameCount.toString();
        data.simImgRes = frameCount.toString();
        data.formatNumber = frameCount.toString();
        data.talkTime = frameCount.toString();
        this.contentData.push(data);
        frameCount++;
        this.flag = 'push';
        if (frameCount > 10) {
          break;
        }
        await new Promise((resolve) => setTimeout(resolve, 32))
      }
      this.flag = 'reverse';
      // swap case
      this.contentData.reverse();
      await new Promise((resolve) => setTimeout(resolve, 32))

      // delete case.
      while (true) {
        this.contentData.pop();
        frameCount--;
        this.flag = 'delete';
        if (frameCount < 2) {
          break;
        }
        await new Promise((resolve) => setTimeout(resolve, 32))
      }
    }, 32)
  }

  @Builder
  callLogTitle() {
    Row() {
      Text('app.string.dialer_calllog')
        .fontSize(30)
        .fontColor(Color.BROWN)
        .margin({ left: "20vp" })

      Divider();

      Text('app.string.clear')
        .fontSize(30)
        .fontColor(Color.BLACK)
        .margin({ right: 30 })
        .onClick(() => {
          console.error('error')
        })
    }
    .width('100%')
    .height(30)
  }

  @Builder
  CallLogListItem(param: CallLogListItemParam) {
    Row() {
      Column() {
        Row() {
          Text(param.dateDetail)
            .fontWeight(FontWeight.Medium)
            .fontSize(20)
            .fontColor(Color.Brown)
          Text(param.timeDetail)
            .fontWeight(FontWeight.Medium)
            .fontSize("40px")
            .fontColor("#998877")
        }
        .height("22vp")

        Row() {
          Image(param.imgRes)
            .objectFit(ImageFit.FILL)
            .width("24vp")
            .height("24vp")
            .opacity(0.4)
          Image(param.simImgRes)
            .objectFit(ImageFit.FILL)
            .width("34vp")
            .height("34vp")
            .opacity(0.4)
          Text(param.formatNumber)
            .fontSize("56px")
            .fontWeight(FontWeight.REGULAR)
            .fontColor("#996657")
        }
        .height("19vp")
        .margin({ top: "24vp" })
      }
      .margin({ left: "12vp" })

      Divider();

      Row() {
        Text('app.string.Ringing')
          .fontWeight(FontWeight.REGULAR)
          .fontSize(36)
          .fontColor("#886712")

        Text(param.talkTime)
          .fontWeight(FontWeight.REGULAR)
          .fontSize(24)
          .fontColor("#FFFFFF")
      }
      .margin({ right: 24 })
      .height("19vp")
    }
    .width('100%')
    .height('26vp')
    .padding({ top: 5, bottom: 5 })
    .onClick(() => {
    })
  }

  build() {
    let before = probe("build3")
    Column() {
    List() {
      ForEach(this.contentData, (item: CallLogListItemParam, index) => {
        ListItem() {
          Column() {
            if (item.showTitle) {
              Divider()
                .strokeWidth(8)
                .color("#FFFFFF")
              this.callLogTitle()
            }
            this.CallLogListItem(item);
          }
        }
        .width("100%")
        ListItem() {
          Column() {
            if (item.showTitle) {
              Divider()
                .strokeWidth(8)
                .color("#FFFFFF")
              this.callLogTitle()
            }
            this.CallLogListItem(item);
          }
        }
        .width("100%")
        ListItem() {
          Column() {
            if (item.showTitle) {
              Divider()
                .strokeWidth(8)
                .color("#FFFFFF")
              this.callLogTitle()
            }
            this.CallLogListItem(item);
          }
        }
        .width("100%")
        ListItem() {
          Column() {
            if (item.showTitle) {
              Divider()
                .strokeWidth(8)
                .color("#FFFFFF")
              this.callLogTitle()
            }
            this.CallLogListItem(item);
          }
        }
        .width("100%")
        ListItem() {
          Column() {
            if (item.showTitle) {
              Divider()
                .strokeWidth(8)
                .color("#FFFFFF")
              this.callLogTitle()
            }
            this.CallLogListItem(item);
          }
        }
        .width("100%")
        ListItem() {
          Column() {
            if (item.showTitle) {
              Divider()
                .strokeWidth(8)
                .color("#FFFFFF")
              this.callLogTitle()
            }
            this.CallLogListItem(item);
          }
        }
        .width("100%")
      }, (item: CallLogListItemParam) => JSON.stringify(item))
    }
    .backgroundColor(Color.WHITE)
    .width("100%")
    }
    .width('100%')
    .height('100%')
    let after = probe("build3")
    console.log(`Took ${after - before}ms in ${this.flag} flag`)
  }
}

// Test Case For Attribute Update of 500 text.
// @Entry
@Component
struct Perf4 {
  @State colorTag: boolean = false
  @State textColor: Color = Color.RED
  private array: number[] = this.getArray(500)

  private getArray(max: number): number[] {
    let array: number[] = new Array()
    for (let i =0; i < max ; i++) {
      array.push(i)
    }
    return array
  }

  aboutToAppear() {
    setTimeout(async ()=>{
      for (let i = 0; i < 10; i++) {
        this.colorTag = !this.colorTag;
        this.textColor = this.colorTag ? Color.GREEN : Color.RED;
        await new Promise((resolve) => setTimeout(resolve, 32));
      }
    }, 32)
  }

  build() {
    let before = probe("build2")
    Column() {
      Row() {
        Button("change color").onClick(() => {
          this.colorTag = !this.colorTag
          this.textColor = this.colorTag ? Color.GREEN : Color.RED
        })
      }
      Scroll() {
        Column() {
          ForEach(this.array, (item: number) => {
            Text('Hello World')
              .fontColor(this.textColor)
              .fontWeight(FontWeight.BOLD)
              .textAlign(TextAlign.CENTER)
              .width(300)
              .height(200)
              .fontSize(50)
              .padding(10)
              .margin(10)
              .lineHeight(80)
              .textAlign(TextAlign.START)
              .backgroundColor(Color.BLUE)
              .border({
                style: BorderStyle.DASHED,
                color: Color.BLACK,
                width: 10
              })
              .borderRadius(50)
              .opacity(0.5)
          }, (item: string) => item)
        }.width('100%')
      }
    }
    let after = probe("build2")
    console.log(`Took ${after - before}ms`)
  }
}