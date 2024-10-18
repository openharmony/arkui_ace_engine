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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function alphabetIndexerPopupColorTest() {
  /*
* AlphabetIndexer组件  popupColor属性
* 找到画面id为alphabetIndexerPopupColor1,alphabetIndexerPopupColor2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupColor1,AlphabetIndexerPopupColor2的button组件
* 获取alphabetIndexer1的popupColor属性与期待值Color.Red比对
* 获取alphabetIndexer2的popupColor属性与期待值'#FF808080'比对
* 点击button1，变更alphabetIndexer2的popupColor属性值为'#ffa500'
* 获取alphabetIndexer2的popupColor属性与期待值'#FFFFA500'比对
* 点击button2，变更alphabetIndexer2的popupColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
* 获取alphabetIndexer2的popupColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
  defineTest('alphabetIndexerPopupColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupColorTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupColor1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupColor2').enabled(true))

    let popupColor1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupColor1).$attrs.popupColor.toLowerCase(), Color.Red)

    let popupColor2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupColor2).$attrs.popupColor, '#FF808080')

    await button1.tap()
    let popupColor3: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupColor3).$attrs.popupColor, '#FFFFA500')

    await button2.tap()
    let popupColor4: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupColor4).$attrs.popupColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}