/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function scrollEnablePagingTest() {
  /*
   * Scroll组件 EnablePaging属性
   * 找到画面id为scrollEnablePaging1,scrollEnablePaging2的Scroll组件
   * 找到画面文本为scrollEnablePaging的Button组件
   * 获取scrollEnablePaging1的EnablePaging属性与期待值true比对
   * 点击button，变更scrollEnablePaging1的EnablePaging属性值为false
   * 获取scrollEnablePaging1的EnablePaging属性与期待值false比对
   * 获取scrollEnablePaging2的EnablePaging属性与期待值false比对
   */
  defineTest('scrollEnablePagingTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollEnablePagingTestDemo running')
    let driver: Tester = Tester.create()
    let scrollEnablePaging1: Component =
      await driver.findComponent(Matcher.create().id('scrollEnablePaging1').enabled(true))
    let scrollEnablePaging2: Component =
      await driver.findComponent(Matcher.create().id('scrollEnablePaging2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollEnablePaging').enabled(true))

    let enablePaging1: string = await scrollEnablePaging1.getInspectorInfo()
    assertFalse(JSON.parse(enablePaging1).$attrs.enablePaging == undefined)
    assertTrue(JSON.parse(enablePaging1).$attrs.enablePaging)
    await button.tap()
    let enablePaging2: string = await scrollEnablePaging1.getInspectorInfo()
    assertFalse(JSON.parse(enablePaging2).$attrs.enablePaging)
    let edgeEffect3: string = await scrollEnablePaging2.getInspectorInfo()
    assertFalse(JSON.parse(edgeEffect3).$attrs.enablePaging)
  }, 0)
}