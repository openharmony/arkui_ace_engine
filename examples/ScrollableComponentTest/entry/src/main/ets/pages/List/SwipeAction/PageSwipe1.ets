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

 /*
  * Description: List支持展开指定ListItem的swipeAction
  * Writer: renxiaowen
  */

import { BusinessError } from '@ohos.base';
import { ListDataSource } from './ListDataSource/ListDataSource1';

@Entry
@Component
struct ListItemExample2 {

  /* 用例描述：动态控制列表项和列表项分组的展开/收起
   * 关键结构：
   * |-> List
   *    |-> LazyForEach
   *       |-> ListItem
   *          |-> Text
   *    |-> LazyForEach
   *       |-> ListItemGroup
   *          |-> Text
   */

  private arr: ListDataSource = new ListDataSource([]);
  @State arr2: number[] = [0, 1, 2, 3, 4];
  @State enterEndDeleteAreaString: string = 'not enterEndDeleteArea';
  @State exitEndDeleteAreaString: string = 'not exitEndDeleteArea';
  private scroller: ListScroller = new ListScroller();
  @State directions: (ListItemSwipeActionDirection | undefined | null)[] = [
    ListItemSwipeActionDirection.START,
    ListItemSwipeActionDirection.END,
    undefined,
    null,
  ];
  @State dirIndex: number = 0;
  @State text: ResourceStr | undefined = '0';
  @State listItemGroupIndex: number = 0;
  @State listChildrenSize: ChildrenMainSize = new ChildrenMainSize(100);

  @Builder
  itemEnd() {
    Row() {
      Button('Delete').margin('4vp')
      Button('Set').margin('4vp').onClick(() => {
        this.scroller.closeAllSwipeActions();
      })
    }.padding('4vp').justifyContent(FlexAlign.SpaceEvenly)
  }

  getList(): FrameNode | undefined | null {
    let node: FrameNode | null = this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId());
    let count: number = node?.getChildrenCount() ?? 0;
    for (let i = 0; i < count; i++) {
      let child: FrameNode | undefined | null = node?.getChild(i);
      if (child?.getNodeType() === "List") {
        return child;
      }
    }
    return undefined;
  }

  getListItemGroup(index: number, list: FrameNode | undefined): FrameNode | undefined | null {
    let count: number = list?.getChildrenCount() ?? 0;
    let listItemGroupCount: number = 0;
    for (let i = 0; i < count; i++) {
      let child: FrameNode | undefined | null = list?.getChild(i);
      if (child?.getNodeType() === "ListItemGroup") {
        if (listItemGroupCount === index) {
          return child;
        }
        listItemGroupCount++;
      }
    }
    return undefined;
  }

  aboutToAppear(): void {
    let array: number[] = [];
    for (let i = 0; i < 3; i++) {
      array.push(i);
    }
    this.arr.setData(array);
    this.listChildrenSize.splice(0, 5, [300, 300, 300, 300, 300]);
  }

  build() {
    Flex({ wrap: FlexWrap.Wrap }) {
      Flex({ wrap: FlexWrap.Wrap }) {
        TextInput({ placeholder: "请输入需要滑动item的索引", text: $$this.text }).width(80)
        Button("directions " + this.directions[this.dirIndex])
          .onClick(() => {
            this.dirIndex = (this.dirIndex + 1) % this.directions.length;
          })
        Button("listItemGroup " + this.listItemGroupIndex)
          .onClick(() => {
            this.listItemGroupIndex = (this.listItemGroupIndex + 1) % this.arr2.length;
          })
        Button("expand inList")
          .onClick(() => {
            try {
              // 测试点：观察指定列表项是否展开
              // 预期结果：指定列表项展开
              ListItemSwipeActionManager.expand(this.getList()?.getChild(Number(this.text)),
                this.directions[this.dirIndex])
            } catch (error) {
              console.error("CXN Error expanding item:", (error as BusinessError).code,
                (error as BusinessError).message);
            }
          })
        Button("collapse inList")
          .onClick(() => {
            try {
              // 测试点：观察指定列表项是否收起
              // 预期结果：指定列表项收起
              ListItemSwipeActionManager.collapse(this.getList()?.getChild(Number(this.text)))
            } catch (error) {
              console.error("CXN Error expanding item:", (error as BusinessError).code,
                (error as BusinessError).message);
            }
          })
        Button("expand inListItemGroup")
          .onClick(() => {
            try {
              let group = this.getListItemGroup(this.listItemGroupIndex, this.getList() ?? undefined);
              // 测试点：观察指定列表项分组是否展开
              // 预期结果：指定列表项分组展开
              ListItemSwipeActionManager.expand(group?.getChild(Number(this.text)), this.directions[this.dirIndex])
            } catch (error) {
              console.error("CXN Error expanding item:", (error as BusinessError).code,
                (error as BusinessError).message);
            }
          })
        Button("collapse inListItemGroup")
          .onClick(() => {
            try {
              let group = this.getListItemGroup(this.listItemGroupIndex, this.getList() ?? undefined);
              // 测试点：观察指定列表项分组是否收起
              // 预期结果：指定列表项分组收起
              ListItemSwipeActionManager.collapse(group?.getChild(Number(this.text)))
            } catch (error) {
              console.error("CXN Error expanding item:", (error as BusinessError).code,
                (error as BusinessError).message);
            }
          })
      }

      List({ space: 10, scroller: this.scroller }) {
        ListItem() {
          Button("生态场景expand inList")
            .width('50%')
            .height(40)
            .fontSize(16)
            .fontColor(Color.Black)
            .borderRadius(10)
            .backgroundColor('#ff6192f6')
            .onClick(() => {
              try {
                // 测试点：观察指定列表项是否展开
                // 预期结果：指定列表项展开
                ListItemSwipeActionManager.expand(this.getList()?.getChild(Number(this.text)),
                  this.directions[this.dirIndex])
              } catch (error) {
                console.error("CXN Error expanding ite m:", (error as BusinessError).code,
                  (error as BusinessError).message);
              }
            })
        }
        .backgroundColor(0xFFFFFF)
        .width('100%')
        .height(100)
        .transition({ type: TransitionType.Delete, opacity: 0 })
        .swipeAction({
          start: {
            builder: () => {
              this.itemEnd();
            },
            actionAreaDistance: 56,
            onEnterActionArea: () => {
              this.enterEndDeleteAreaString = 'enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
            },
            onExitActionArea: () => {
              this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'exitEndDeleteArea';
            }
          },
          end: {
            builder: () => {
              this.itemEnd();
            },
            actionAreaDistance: 56,
            onEnterActionArea: () => {
              this.enterEndDeleteAreaString = 'enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
            },
            onExitActionArea: () => {
              this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'exitEndDeleteArea';
            }
          }
        })

        LazyForEach(this.arr, (item: number) => {
          ListItem() {
            Text('item' + item)
              .width('100%')
              .height(100)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
          }
          .transition({ type: TransitionType.Delete, opacity: 0 })
          .swipeAction({
            start: {
              builder: () => {
                this.itemEnd();
              },
              onAction: () => {
                this.getUIContext()?.animateTo({ duration: 1000 }, () => {
                  this.arr.deleteItem(item);
                });
              },
              actionAreaDistance: 56,
              onEnterActionArea: () => {
                this.enterEndDeleteAreaString = 'enterEndDeleteArea';
                this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
              },
              onExitActionArea: () => {
                this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
                this.exitEndDeleteAreaString = 'exitEndDeleteArea';
              }
            },
            end: {
              builder: () => {
                this.itemEnd();
              },
              onAction: () => {
                this.arr.deleteItem(item);
              },
              actionAreaDistance: 56,
              onEnterActionArea: () => {
                this.enterEndDeleteAreaString = 'enterEndDeleteArea';
                this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
              },
              onExitActionArea: () => {
                this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
                this.exitEndDeleteAreaString = 'exitEndDeleteArea';
              }
            }
          })

        }, (item: number) => item.toString())
        ForEach(this.arr2, (item1: number) => {
          ListItemGroup() {
            ForEach(this.arr2, (item: number) => {
              ListItem() {
                Text('ListItemGroup ' + (this.arr2.length * item1 + this.arr.totalCount() + item) + ' item' + item)
                  .width('100%')
                  .height(100)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor(0xFFFFFF)
              }
              .transition({ type: TransitionType.Delete, opacity: 0 })
              .swipeAction({
                start: {
                  builder: () => {
                    this.itemEnd();
                  },
                  onAction: () => {
                    this.getUIContext()?.animateTo({ duration: 1000 }, () => {
                      let index = this.arr2.indexOf(item);
                      this.arr2.splice(index, 1);
                    });
                  },
                  actionAreaDistance: 56,
                  onEnterActionArea: () => {
                    this.enterEndDeleteAreaString = 'enterEndDeleteArea';
                    this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
                  },
                  onExitActionArea: () => {
                    this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
                    this.exitEndDeleteAreaString = 'exitEndDeleteArea';
                  }
                },
                end: {
                  builder: () => {
                    this.itemEnd();
                  },
                  onAction: () => {
                    this.getUIContext()?.animateTo({ duration: 1000 }, () => {
                      let index = this.arr2.indexOf(item);
                      this.arr2.splice(index, 1);
                    });
                  },
                  actionAreaDistance: 56,
                  onEnterActionArea: () => {
                    this.enterEndDeleteAreaString = 'enterEndDeleteArea';
                    this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
                  },
                  onExitActionArea: () => {
                    this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
                    this.exitEndDeleteAreaString = 'exitEndDeleteArea';
                  }
                }
              })
            }
            )
          }
        }, (item: number) => item.toString())
        ListItem() {
          Text("end")
            .width('100%')
            .height(100)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .borderRadius(10)
            .backgroundColor(0xFFFFFF)
        }
        .transition({ type: TransitionType.Delete, opacity: 0 })
        .swipeAction({
          start: {
            builder: () => {
              this.itemEnd();
            },
            actionAreaDistance: 56,
            onEnterActionArea: () => {
              this.enterEndDeleteAreaString = 'enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
            },
            onExitActionArea: () => {
              this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'exitEndDeleteArea';
            }
          },
          end: {
            builder: () => {
              this.itemEnd();
            },
            actionAreaDistance: 56,
            onEnterActionArea: () => {
              this.enterEndDeleteAreaString = 'enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'not exitEndDeleteArea';
            },
            onExitActionArea: () => {
              this.enterEndDeleteAreaString = 'not enterEndDeleteArea';
              this.exitEndDeleteAreaString = 'exitEndDeleteArea';
            }
          }
        })
      }
      .childrenMainSize(this.listChildrenSize)
      .cachedCount(1)
      .height('80%')
    }
    .padding(10)
    .backgroundColor(0xDCDCDC)
    .width('100%')
    .height('100%')
  }
}