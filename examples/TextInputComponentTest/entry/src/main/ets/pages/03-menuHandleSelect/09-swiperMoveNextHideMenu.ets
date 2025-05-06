/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct SwiperMoveNextHideMenu {
  private swiperController: SwiperController = new SwiperController();
  data: string[] = ['item1', 'item2', 'item3', 'item4', 'item5', 'item6', 'item7', 'item8', 'item9']

  build() {
    Column() {
      Text('==========操作==========\n' +
        '1、双击item2，展示【复制】菜单\n' +
        '2、向左移动item1、item2，item3到展示item4、item5，item6\n' +
        '==========期望==========\n' +
        '1、双击item2，展示【复制】菜单\n' +
        '2、移动完成后，隐藏【复制】菜单')
      Swiper(this.swiperController) {
        ForEach(this.data, (item: string) => {
          Text(item)
            .width('33%')
            .height(160)
            .backgroundColor(Color.Pink)
            .textAlign(TextAlign.Center)
            .fontSize(30)
            .copyOption(CopyOptions.LocalDevice)
        }, (item: string) => item)
      }
      .displayCount(3, true)
      .loop(true)
    }
  }
}