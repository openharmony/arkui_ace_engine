/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function searchCaretStyleTest() {
  /*
   * Search组件 CaretStyle属性
   * 找到画面id为searchCaretStyle1,searchCaretStyle2的Search组件
   * 找到画面文本为SearchCaretStyle1,SearchCaretStyle2的Button组件
   * 获取search1的CaretStyle属性CaretStyle.caretStyle.width与期待值'10.00px'比对
   * 获取search1的CaretStyle属性CaretStyle.caretStyle.color与期待值Color.Pink比对
   * 点击button1，变更search1的CaretStyle属性CaretStyle.caretStyle.width值为50
   * 点击button1，变更search1的CaretStyle属性CaretStyle.caretStyle.color值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取search1的CaretStyle属性CaretStyle.caretStyle.width与期待值50.00vp比对
   * 获取search1的CaretStyle属性CaretStyle.caretStyle.color与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   * 点击button2，变更search1的CaretStyle属性CaretStyle.caretStyle.width值为$r('app.string.vp_length')
   * 点击button2，变更search1的CaretStyle属性CaretStyle.caretStyle.color值为0xffffff
   * 获取search1的CaretStyle属性CaretStyle.caretStyle.width与期待值$r('app.string.vp_length')比对
   * 获取search1的CaretStyle属性CaretStyle.caretStyle.color与期待值#FFFFFFFF比对
   */
  defineTest('searchCaretStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchCaretStyleTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component = await driver.findComponent(Matcher.create().id('searchCaretStyle1').enabled(true))
    let search2: Component = await driver.findComponent(Matcher.create().id('searchCaretStyle2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SearchCaretStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SearchCaretStyle2').enabled(true))

    let caretStyle1: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(caretStyle1).$attrs.caretStyle.width, '10.00px')
    assertEqual(JSON.parse(caretStyle1)
      .$attrs
      .caretStyle
      .color
      .toLowerCase(), Color.Pink)
    let caretStyle2: string = await search2.getInspectorInfo()
    assertEqual(JSON.parse(caretStyle2).$attrs.caretStyle.color, '#FFFF64FF')

    await button1.tap()
    let caretStyle3: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(caretStyle3).$attrs.caretStyle.width, '50.00vp')
    assertEqual(JSON.parse(caretStyle3).$attrs.caretStyle.color, $r('sys.color.ohos_id_color_text_hyperlink'))
    await button2.tap()
    let caretStyle4: string = await search1.getInspectorInfo()
    assertEqual(JSON.parse(caretStyle4).$attrs.caretStyle.width, $r('app.string.vp_length'))
    assertEqual(JSON.parse(caretStyle4).$attrs.caretStyle.color, '#FFFFFFFF')
  }, 0)
}