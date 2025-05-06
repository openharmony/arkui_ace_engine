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

/*用例描述
 通过RecycleView库文件实现Scroll组件自定义布局
*/

import {
  RecycleAdapter,
  LayoutManager,
  FixedHeightLayoutManager,
  RecycleViewController,
  RecycleView
} from './RecycleView'


class Param extends Object {
  title: string = '';
}

@Builder
function itemBuilder(obj: Object) {
  Row() {
    Image($r('app.media.startIcon'))
      .size({ height: 64, width: 64 })
    Column() {
      Text('title' + (obj as Param).title)
      Text('subtitle' + (obj as Param).title)
    }.alignItems(HorizontalAlign.Start)
    .margin({ left: 16 })

    Blank()
    Button('click')
  }
  .width('100%')
  .padding(12)
}

class MyAdapter extends RecycleAdapter {
  getCount(): number {
    return 200
  }

  getData(index: number): Object {
    let data: Param = new Param()
    data.title = index.toString()
    return data;
  }
}

@Entry
@Component
struct ListNodeTest {
  scroller: Scroller = new Scroller()
  adapterController: RecycleViewController = new RecycleViewController();

  aboutToAppear(): void {
    let builderVar: WrappedBuilder<[Object]> = wrapBuilder(itemBuilder)
    let layoutManager = new FixedHeightLayoutManager()
    layoutManager.SetItemHeight(vp2px(72))
    this.adapterController.layoutManager = layoutManager;
    this.adapterController.adapter = new MyAdapter(this.getUIContext(), builderVar)
  }

  build() {
    Column() {
      RecycleView({ adapterController: this.adapterController })
    }
  }
}