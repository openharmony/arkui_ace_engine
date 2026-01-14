/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * Description: List在扩展安全区的情况下支持展开指定ListItem的swipeAction
 * Writer: dailihuan
 */

@Builder
export function SubPageBuilder() {
  SubPage()
}

type ItemType = number | string;

@Entry
@ComponentV2
struct SubPage {
  @Local arr: ItemType[] = ['SpaceTop', 0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
  @Local enterEndDeleteAreaString: string = 'not enterEndDeleteArea';
  @Local exitEndDeleteAreaString: string = 'not exitEndDeleteArea';
  private scroller: ListScroller = new ListScroller();

  @Builder
  itemEnd() {
    Row() {
      Button('ShowToast').margin('4vp')
        .onClick(() => {
          this.getUIContext().getPromptAction().showToast({ message: '按钮被点击' });
        });
      Button('Set').margin('4vp').onClick(() => {
        this.scroller.closeAllSwipeActions();
      });
    }.padding('4vp').justifyContent(FlexAlign.SpaceEvenly);
  }

  // 侧滑删除按钮
  @Builder
  private SwipeBuilder(ri: RepeatItem<ItemType>) {
    Row({ space: 12 }) {
      // 重命名
      Button() {
        SymbolGlyph($r('sys.symbol.square_and_pencil'))
          .fontSize(16)
          .fontColor([Color.White])
      }
      .type(ButtonType.Circle)
      .width(40)
      .height(40)
      .backgroundColor('#3094FF')
      .onClick(() => {
        this.getUIContext().getPromptAction().showToast({ message: '编辑按钮被点击' });
      })

      // 删除
      Button() {
        SymbolGlyph($r('sys.symbol.trash'))
          .fontSize(16)
          .fontColor([Color.White])
      }
      .type(ButtonType.Circle)
      .width(40)
      .height(40)
      .backgroundColor('#FF3B30')
      .onClick(() => {
        this.getUIContext().getPromptAction().showToast({ message: '删除按钮被点击' });
      })
    }
    .margin({ left: 20, right: 20 })
    .height(68)
    .justifyContent(FlexAlign.Center)
    .alignItems(VerticalAlign.Center)
  }

  @Builder
  LabelItemBuilder(ri: RepeatItem<ItemType>) {
    Row({ space: 12 }) {
      // 标签名称
      Column() {
        Text(ri.item.toString())
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .maxLines(1)
          .ellipsisMode(EllipsisMode.END)
      }
      .layoutWeight(1)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Start)
    }
    .padding(16)
    .height(50)
    .borderRadius(16)
    .backgroundColor($r('sys.color.comp_background_primary'))
    .width('100%')
  }

  build() {
    NavDestination() {
      RelativeContainer() {
        List({ space: 10, scroller: this.scroller }) {
          Repeat<ItemType>(this.arr)
            .each((ri: RepeatItem<ItemType>) => {
            })
            .templateId((item: ItemType, index: number): string => {
              if (typeof item === 'number') {
                return 'number';
              } else if (typeof item === 'string') {
                return item;
              }
              return '';
            })
            .template('SpaceTop', (Ri: RepeatItem<ItemType>) => {
              ListItem() {
                Column()
                  .height(100)
              }
            })
            .template('number', (Ri: RepeatItem<ItemType>) => {
              ListItem() {
                if (typeof Ri.item === 'number') {
                  this.LabelItemBuilder(Ri as RepeatItem<ItemType>)
                }
              }
              .margin({
                top: 12,
                left: 16,
                right: 16
              })
              .borderRadius(16)
              .swipeAction({
                end: {
                  builder: () => this.SwipeBuilder(Ri),
                  actionAreaDistance: -1
                }
              })
            })
            .key((item: ItemType, index: number) => {
              return item.toString()
            })
            .virtualScroll()
        }
        .zIndex(0)
        .height('100%')
        .width('100%')
        .alignRules({
          top: { anchor: '__container__', align: VerticalAlign.Top },
          bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
          left: { anchor: '__container__', align: HorizontalAlign.Start },
          right: { anchor: '__container__', align: HorizontalAlign.End },
        })
        .contentEndOffset(48)
        .scrollBar(BarState.Off)
        .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true })
        .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM])
      }
      .width('100%')
      .height('100%')
      .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM])
    }
    .title("标签管理")
    .hideTitleBar(true)
    .backgroundColor($r('sys.color.background_secondary'))
  }
}