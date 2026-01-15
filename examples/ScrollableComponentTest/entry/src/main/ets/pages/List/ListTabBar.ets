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
 * Description: List模拟页签与内容区域联动滑动
 * Writer: dailihuan
 */

class ClassifyModel {
  classifyId: number;
  classifyName: string;
  courseList: Array<string>;

  constructor(classifyId: number, classifyName: string, courseList: Array<string>) {
    this.classifyId = classifyId;
    this.classifyName = classifyName;
    this.courseList = courseList;
  }
}

@Component
struct CardItem {
  @Prop classifyItem: ClassifyModel

  build() {
    Column() {
      Column() {
        Text(this.classifyItem.classifyName).fontSize(40);
      }

      Flex({ wrap: FlexWrap.Wrap }) {
        ForEach(this.classifyItem.courseList, (courseItem: string, index: number) => {
          Button(courseItem).fontSize(30);
        });
      };
    }.alignItems(HorizontalAlign.Start)
  }
}


@Entry
@Component
struct IndexPage {
  @State currentClassify: number = 0; // selected classify index.
  @State requestSuccess: boolean = false; // is loading data.
  private classifyList: Array<ClassifyModel> = [];
  private classifyScroller: Scroller = new Scroller();
  private scroller: Scroller = new Scroller();

  aboutToAppear() {
    this.classifyList.push(new ClassifyModel(1, '热门',
      ['热门', '热门', '关注', '热门', '热门', '关注', '热门', '热门', '关注']));
    this.classifyList.push(new ClassifyModel(2, '体育', ['游戏', '动漫']));
    this.classifyList.push(new ClassifyModel(3, '轻松', ['八卦', '宠物', '八卦', '宠物', '八卦', '宠物']));
    this.classifyList.push(new ClassifyModel(4, '科技', ['星座', '宠物', '八卦', '宠物', '八卦', '宠物']));
    this.classifyList.push(new ClassifyModel(5, '生活', ['奢侈品', '数码', '八卦', '宠物', '八卦', '宠物']));
    this.classifyList.push(new ClassifyModel(6, '人文', ['航天', '宠物', '八卦', '宠物', '八卦', '宠物']));
  }

  //二级联动逻辑
  classifyChangeAction(startIndex: number, endIndex: number, isClassify: boolean) {
    if (this.currentClassify !== startIndex) {
      console.log("dlh", startIndex, isClassify);
      this.currentClassify = startIndex;
      if (isClassify) {
        this.scroller.scrollToIndex(startIndex);  // 通过点击标题移动内容区域
      } else {
        this.classifyScroller.scrollToIndex(startIndex - 2); //滑动内容区域时，同步实现tabBar的移动
      }
    }
  }

  build() {
    Scroll() {
      Column() {
        // 类似tabbar
        List({ scroller: this.classifyScroller }) {
          ForEach(this.classifyList, (item: ClassifyModel, index: number) => {
            ListItem() {
              Column() {
                Text(item.classifyName)
                Divider()
                  .color('#000000').strokeWidth(3)
                  .visibility(index == this.currentClassify ? Visibility.Visible : Visibility.Hidden) //在滑动时移动底边
              }.justifyContent(FlexAlign.Center).width('20%').height('100%')
            }
            .onClick(() => {
              this.classifyChangeAction(index, 0, true);
            })
          }, (item: ClassifyModel) => item.classifyName + this.currentClassify)
        }.height(50).listDirection(Axis.Horizontal).scrollBar(BarState.Off)

        List({ scroller: this.scroller }) {
          ForEach(this.classifyList, (classifyItem: ClassifyModel, index: number) => {
            if (index != this.classifyList.length - 1) {
              ListItem() {
                CardItem({ classifyItem: classifyItem })
              }
            } else {
              ListItem() {
                CardItem({ classifyItem: classifyItem }).height('100%')
              }
            }
          }, (item: ClassifyModel) => `${item.classifyId}`)
        }
        .nestedScroll({
          scrollForward: NestedScrollMode.PARENT_FIRST,
          scrollBackward: NestedScrollMode.SELF_FIRST
        })
        .height('calc(100% - 50vp)')
        .edgeEffect(EdgeEffect.Spring)
        .onScrollIndex((start: number, end: number) => this.classifyChangeAction(start, end, false))
      }
    }
  }
}