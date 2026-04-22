/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { PageClass } from '../../common/PageClass'


const testList1: PageClass[] = [
  new PageClass('自定义全量Case', 'pages/MenuUX/SDFArrow/totalCase', 'totalCase'),
  new PageClass('避让软键盘', 'pages/MenuUX/SDFArrow/avoidKeyboardCase', 'avoidKeyboard'),
  new PageClass('隐式动画场景', 'pages/MenuUX/SDFArrow/animationCase', 'animationCase'),
  new PageClass('边界检测场景', 'pages/MenuUX/SDFArrow/boundaryCase', 'boundaryCase'),
  new PageClass('响应式布局场景', 'pages/MenuUX/SDFArrow/responsiveCase', 'responsiveCase'),
  new PageClass('多菜单场景', 'pages/MenuUX/SDFArrow/multiMenuCase', 'multiMenuCase'),
  new PageClass('交互事件场景', 'pages/MenuUX/SDFArrow/interactionCase', 'interactionCase'),
  new PageClass('深色/浅色模式场景', 'pages/MenuUX/SDFArrow/themeCase', 'themeCase'),
]

@Entry
@Component
struct MenuKeyboardAvoid {
  build() {
    Scroll() {
      Column({ space: 10 }) {
        List({ space: 8 }) {
          ForEach(testList1, (item: PageClass) => {
            ListItem() {
              Button(item.title)
                .width('85%')
                .fontSize(20)
                .onClick(() => {
                  this.getUIContext().getRouter().pushUrl({
                    url: item.url
                  }).catch(() => {
                  })
                })
                .key(item.key)
            }.align(Alignment.Center).margin({
              bottom: 10
            })
          }, (item: PageClass) => item.title)
        }.padding(5).alignListItem(ListItemAlign.Center)
      }.width('100%').height('100%').align(Alignment.Top)
    }.width('100%').height('100%').align(Alignment.Top)
  }
}