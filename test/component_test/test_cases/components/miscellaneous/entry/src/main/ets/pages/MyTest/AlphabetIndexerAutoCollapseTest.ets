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
import {
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function alphabetIndexerAutoCollapseTest() {
  /*
* AlphabetIndexer组件  autoCollapse属性
* 找到画面id为alphabetIndexerAutoCollapse1,alphabetIndexerAutoCollapse2,alphabetIndexerAutoCollapse3,alphabetIndexerAutoCollapse4,alphabetIndexerAutoCollapse5,alphabetIndexerAutoCollapse6的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerAutoCollapse的button组件
* 获取alphabetIndexer1的autoCollapse属性与期待值true比对
* 获取alphabetIndexer2的autoCollapse属性与期待值true比对
* 获取alphabetIndexer3的autoCollapse属性与期待值true比对
* 获取alphabetIndexer4的autoCollapse属性与期待值true比对
* 获取alphabetIndexer5的autoCollapse属性与期待值true比对
* 获取alphabetIndexer6的autoCollapse属性与期待值true比对
* 点击button，变更alphabetIndexer1的autoCollapse属性值为false
* 获取alphabetIndexer1的autoCollapse属性与期待值false比对
*/
  defineTest('alphabetIndexerAutoCollapseTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerAutoCollapseTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse2').enabled(true))
    let alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse3').enabled(true))
    let alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse4').enabled(true))
    let alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse5').enabled(true))
    let alphabetIndexer6: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAutoCollapse6').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerAutoCollapse').enabled(true))

    let autoCollapse1: string = await alphabetIndexer2.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse1).$attrs.autoCollapse)
    let autoCollapse2: string = await alphabetIndexer3.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse2).$attrs.autoCollapse)
    let autoCollapse3: string = await alphabetIndexer4.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse3).$attrs.autoCollapse)
    let autoCollapse4: string = await alphabetIndexer5.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse4).$attrs.autoCollapse)
    let autoCollapse5: string = await alphabetIndexer6.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse5).$attrs.autoCollapse)

    let autoCollapse6: string = await alphabetIndexer1.getInspectorInfo()
    assertTrue(JSON.parse(autoCollapse6).$attrs.autoCollapse)

    await button.tap()
    let autoCollapse7: string = await alphabetIndexer1.getInspectorInfo()
    assertFalse(JSON.parse(autoCollapse7).$attrs.autoCollapse)
  }, 0)
}
