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
import { Box } from "@koalaui/arkoala-extension-component"

class BasicDataSource implements IDataSource {
  private listeners: DataChangeListener[] = []

  public totalCount(): number {
    return 0
  }
  public getData(index: number): any {
    return undefined
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      console.info('add listener')
      this.listeners.push(listener)
    }
  }
  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      console.info('remove listener')
      this.listeners.splice(pos, 1)
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded()
    })
  }
  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index)
    })
  }
  notifyDataChange(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataChange(index)
    })
  }
  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index)
    })
  }
  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to)
    })
  }
}

class MyDataSource extends BasicDataSource {
  private data = [ "foo", "bar", "zoo", "koo", "soo" ]

  public totalCount(): number {
    return this.data.length * 100
  }
  public getData(index: number): any {
    console.log("getData", index)
    return this.data[index % 5]
  }
}

let resources: Resource[] = [
  // $r("app.string.text_label_1"),
]

@Entry
@Component
export struct MyStack {
    private data: MyDataSource = new MyDataSource()

    @State count: number = 17
    @State other: number = 42

    build() {
      Column() {
        Box({ width: 300, height: 295, color: 0xe6e6e6 }, () => {
          Button("TopStart").align(Alignment.TopStart)
          Button("Center").align(Alignment.Center)
          Button("BottomEnd").align(Alignment.BottomEnd)
        })
        Text(resources.length > 0 ? resources[0] : "Default")
        Column() {
          Grid() {
            GridItem() {
              Text("Item1")
            }
            LazyForEach(this.data, item => {
              GridItem() {
                Text("Lazy1 " + (item?.toString() ?? "<empty>"))
              }
            })
            GridItem() {
              Text("Item2")
            }
            LazyForEach(this.data, item => {
              GridItem() {
                Text("Lazy2 " + (item?.toString() ?? "<empty>"))
              }
            })
          }.width('100%')
          .columnsTemplate('1fr 1fr')
          .height('40%')
          Child()
          Stack() {
            Text('1, zIndex(2)')
              .width("40%")
              .height("30%")
              .backgroundColor(0xbbb2cb)
              .zIndex(2)
            Text('2, default zIndex(1)')
              .width("70%")
              .height("50%")
              .backgroundColor(0xd2cab3)
              .zIndex(1)
              .onClick(e => {
                console.log("OnClick in text", e)
                this.count++
              })
            Text('3, zIndex(0)')
              .width("90%")
              .height("80%")
              .backgroundColor(0xc1cbac)
            List() {
              ListItem() {
                Text("Item1")
              }
              LazyForEach(this.data, item => {
                ListItem() {
                  Text("Lazy1 " + (item?.toString() ?? "<empty>"))
                }
              })
              ListItem() {
                Text("Item2")
              }
              LazyForEach(this.data, item => {
                ListItem() {
                  Text("Lazy2 " + (item?.toString() ?? "<empty>"))
                }
              })
            }.listDirection(Axis.Vertical)
          }.width('100%').height(200)

          Row() {
            Text($r("app.string.MainAbility_desc"))
          }
        }.width('100%').height(600)

        Blank(10)
          .color(0xbbb2cb)
      }
    }

    pageTransition() {
      console.log("stack page transition")
      /* todo
      PageTransitionEnter({ duration: 120 })
        .slide(SlideEffect.Right)
        .onEnter((type: RouteType, progress: number) => {
          console.log("Progress", progress)
        })
      PageTransitionExit({ delay: 100 })
        .translate({ x: 200.0, y: 200.0 })
      */
    }
}

@Component
struct Child {
    @State myProp1: number = 40
    @State myProp2: number = 100
    @State color: Color = Color.Green

    build() {
      Text("Child1")
            .width(this.myProp1 + 20)
            .animation({duration: 1000})
            .onClick(e => {
                this.myProp1 = this.myProp1 == 40 ? 80 : 40
                this.color = this.color == Color.Green ? Color.Red : Color.Green
                console.log("ARK CHILD", this.myProp1)
            })
            .height(this.myProp1 + 100)
            .animation({duration: 2000})
            .backgroundColor(this.color)
            .animation({duration: 6000})
      Text("Child2")
            .width(this.myProp2 + 20)
            .onClick(() => {
              console.log("ARK CHILD2", this.myProp2)
              animateTo({duration: 100}, () => { this.myProp2 = this.myProp2 == 100 ? 20 : 100 })
            })
            .height(this.myProp2 + 100)
    }
}
