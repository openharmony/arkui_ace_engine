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

export default async function alphabetIndexerColorTest() {
  /*
* AlphabetIndexer组件  color属性
* 找到画面id为alphabetIndexerColor1,alphabetIndexerColor2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerColor1,AlphabetIndexerColor2的button组件
* 获取alphabetIndexer1的color属性与期待值Color.Gray比对
* 获取alphabetIndexer2的color属性与期待值'#FF808080'比对
* 点击button1，变更alphabetIndexer2的color属性值为'#FFFFA500'
* 获取alphabetIndexer2的color属性与期待值'#FFFFA500'比对
* 点击button2，变更alphabetIndexer2的color属性值为$r('sys.color.ohos_id_color_text_hyperlink')
* 获取alphabetIndexer2的color属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
  defineTest('alphabetIndexerColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerColorTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerColor1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerColor2').enabled(true))

    let color1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(color1).$attrs.color.toLowerCase(), Color.Gray)

    let color2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(color2).$attrs.color, '#FF808080')
    await button1.tap()
    let color3: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(color3).$attrs.color, '#FFFFA500')
    await button2.tap()
    let color4: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(color4).$attrs.color, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}