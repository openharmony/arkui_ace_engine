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
import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function colorBlendTest() {
  /*
  * AlphabetIndexer组件colorBlend属性
  * 找到画面id为 alphabetIndexerColorBlend1 、textColorBlend2 的AlphabetIndexer和Text组件
  * 找到画面文本为ButtonColorBlend的Button组件
  * 获取alphabetIndexerColorBlend1的colorBlend属性与期待值Color.Green比对
  * 获取textColorBlend2的colorBlend属性与期待值 '#FFA52A2A' 比对
  * 点击button1，变更textColorBlend2的colorBlend属性值为$r('sys.color.ohos_id_color_text_hyperlink')
  * 获取textColorBlend2的colorBlend属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
  */
  defineTest('colorBlendTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("colorBlendTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexerColorBlend1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerColorBlend1').enabled(true))
    let textColorBlend2: Component = await driver.findComponent(Matcher.create().id('textColorBlend2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonColorBlend').enabled(true))
    let colorBlend1: string = await alphabetIndexerColorBlend1.getInspectorInfo()
    assertEqual(JSON.parse(colorBlend1).$attrs.colorBlend.toLowerCase(), Color.Green)
    let colorBlend2: string = await textColorBlend2.getInspectorInfo()
    assertEqual(JSON.parse(colorBlend2).$attrs.colorBlend, '#FFA52A2A')
    await button1.tap()
    let colorBlend3: string = await textColorBlend2.getInspectorInfo()
    assertEqual(JSON.parse(colorBlend3).$attrs.colorBlend, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}