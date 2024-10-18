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

export default async function alphabetIndexerAlphabetIndexerAttributeTest() {
  /*
* AlphabetIndexer组件  alphabetIndexerAttribute属性
* 找到画面id为alphabetIndexerAlphabetIndexerAttribute的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerAlphabetIndexerAttribute的button组件
* 获取alphabetIndexer的color属性与期待值Color.Red比对
* 点击button，变更alphabetIndexer1的.color属性值为Color.Black
* 获取alphabetIndexer1的color属性与期待值Color.Black比对
*/
  defineTest('alphabetIndexerAlphabetIndexerAttributeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerAlphabetIndexerAttributeTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAlphabetIndexerAttribute').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerAlphabetIndexerAttribute').enabled(true))
    let alphabetIndexerAttribute1: string = await alphabetIndexer.getInspectorInfo()
    assertEqual(JSON.parse(alphabetIndexerAttribute1).$attrs.color.toLowerCase(), Color.Red)
    await button.tap()
    let alphabetIndexerAttribute2: string = await alphabetIndexer.getInspectorInfo()
    assertEqual(JSON.parse(alphabetIndexerAttribute2).$attrs.color.toLowerCase(), Color.Black)
  }, 0)
}