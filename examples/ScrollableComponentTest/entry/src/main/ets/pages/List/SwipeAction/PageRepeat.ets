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

class DemoListItemInfo {
  name: string;
  icon: Resource;

  constructor(name: string, icon: Resource) {
    this.name = name;
    this.icon = icon;
  }
}

@Entry
@Component
struct DemoList {

  /* 用例描述：动态控制列表项的展开/收起，使用Repeat组件来优化列表渲染
   * 关键结构：
   * |-> List
   *    |-> Repeat
   */

  @State arr2: number[] = [0, 1, 2, 3, 4];
  @State enterEndDeleteAreaString: string = 'not enterEndDeleteArea';
  @State exitEndDeleteAreaString: string = 'not exitEndDeleteArea';
  private scroller: ListScroller = new ListScroller();
  @State directions: (ListItemSwipeActionDirection | undefined | null)[] = [
    ListItemSwipeActionDirection.START,
    ListItemSwipeActionDirection.END,
    undefined,
    null,
  ]
  @State dirIndex: number = 0;
  @State text: ResourceStr | undefined = '0';
  @State listItemGroupIndex: number = 0;
  @State listChildrenSize: ChildrenMainSize = new ChildrenMainSize(100);
  @State videoList: Array<DemoListItemInfo> = [];

  aboutToAppear(): void {
    for (let i = 0; i < 10; i++) {
      // 此处app.media.listItem0、app.media.listItem1、app.media.listItem2仅作示例，请开发者自行替换
      this.videoList.push(new DemoListItemInfo('视频' + i,
        i % 3 == 0 ? $r("app.media.app_icon") :
          i % 3 == 1 ? $r("app.media.layered_image") : $r("app.media.startIcon")));
    }
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

  @Builder
  itemEnd() {
    Row() {
      Button('Delete').margin('4vp')
      Button('Set').margin('4vp').onClick(() => {
        this.scroller.closeAllSwipeActions();
      })
    }.padding('4vp').justifyContent(FlexAlign.SpaceEvenly)
  }

  build() {
    Column({ space: 10 }) {
      Text('List容器组件中包含Repeat组件')
        .fontSize(15)
        .fontColor(Color.Gray)
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
      }

      List({ space: 5 }) {
        Repeat<DemoListItemInfo>(this.videoList)
          .each((obj: RepeatItem<DemoListItemInfo>) => {
            ListItem() {
              Column() {
                Image(obj.item.icon)
                  .width('80%')
                  .margin(10)
                Text(obj.item.name)
                  .fontSize(20)
              }
            }
            .swipeAction({
              start: {
                builder: () => {
                  this.itemEnd()
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
            .onAppear(() => {
              console.info('AceTag', obj.item.name);
            })
          })
          .key((item: DemoListItemInfo) => item.name)
          .virtualScroll()
      }
      .cachedCount(2)
      .height('90%')
      .border({ width: 1 })
      .listDirection(Axis.Vertical)
      .alignListItem(ListItemAlign.Center)
      .divider({
        strokeWidth: 1,
        startMargin: 60,
        endMargin: 60,
        color: '#ffe9f0f0'
      })

      Row({ space: 10 }) {

      }
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }
}
