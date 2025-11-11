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

import { JSON } from '@kit.ArkTS';

interface ImageTextCardInput {
  img: string;
  txt: string;
}

@Entry
@Component
struct Index {
  header: DataSource<ImageTextCardInput> = new DataSource<ImageTextCardInput>()
  goods: DataSource<ImageTextCardInput> = new DataSource<ImageTextCardInput>()

  aboutToAppear(): void {
    for (let index = 0; index < 20; index++) {
      this.header.data.push({img: 'app.media.startIcon', txt: `选项${index + 1}`})
    }

    for (let index = 0; index < 200; index++) {
      this.goods.data.push({img: 'app.media.startIcon', txt: `物品${index + 1}`})
    }
  }

  @Builder
  tabBarBuilder(input: ImageTextCardInput)
  {
    ImageTextCard(input)
  }

  build() {
    Tabs() {
      TabContent() {
        Scroll() {
          Column() {
            Search({value: "12345"})
            Grid() {
              LazyForEach(this.header, (item: ImageTextCardInput, index: number)=>{
                GridItem() {
                  ImageTextCard(item)
                }
              }, (item: ImageTextCardInput, index: number)=>JSON.stringify(item))
            }
            .scrollBar(BarState.Off)
            .rowsGap(5)
            .columnsGap(5)
            .width('100%')
            .height(180)
            .rowsTemplate('1fr 1fr')
            WaterFlow() {
              LazyForEach(this.goods, (item: ImageTextCardInput, index: number)=>{
                FlowItem() {
                  ImageTextCard(item)
                    .width('calc(50% - 10vp)')
                }
                .height(`calc(50% - ${200 * Math.random()}vp)`)
                .borderWidth(2)
                .borderColor('#ff340b0b')
              }, (item: ImageTextCardInput, index: number)=>JSON.stringify(item))
            }
            .nestedScroll({scrollForward: NestedScrollMode.PARENT_FIRST, scrollBackward: NestedScrollMode.SELF_FIRST})
            .rowsGap(10)
            .columnsGap(10)
            .width('100%')
            .height('100%')
            .columnsTemplate('1fr 1fr')
          }
        }
        .height('100%')
        .width('100%')
      }
      .tabBar(this.tabBarBuilder({img: 'app.media.startIcon', txt: '首页'}))
      TabContent() {
        Text('直播')
      }
      .tabBar(this.tabBarBuilder({img: 'app.media.startIcon', txt: '直播'}))
      TabContent() {
        Text('消息')
      }
      .tabBar(this.tabBarBuilder({img: 'app.media.startIcon', txt: '消息'}))
      TabContent() {
        Text('我的')
      }
      .tabBar(this.tabBarBuilder({img: 'app.media.startIcon', txt: '我的'}))
      TabContent() {
        Text('设置')
      }
      .tabBar(this.tabBarBuilder({img: 'app.media.startIcon', txt: '设置'}))
    }
    .barPosition(BarPosition.End)
    .barHeight(80)
  }
}

@Reusable
@Component
struct ImageTextCard {
  @State img: string = ''
  @State txt: string = ''

  // 通过生命周期将节点更新成新节点的样式
  aboutToReuse(params: ESObject): void {
    this.img = params.img
    this.txt = params.txt
  }

  build() {
    Column() {
      Image($r(this.img))
        .objectFit(ImageFit.Contain)
        .autoResize(true)
        .height('calc(100% - 35vp)')
      Text(this.txt)
        .fontSize(15)
    }
  }
}

class DataSource<T> implements IDataSource
{
  public data: T[] = []
  listener: DataChangeListener | undefined = undefined

  totalCount(): number {
    return this.data.length
  }

  getData(index: number): T {
    return this.data[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    this.listener = listener
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    this.listener = undefined;
  }

}
