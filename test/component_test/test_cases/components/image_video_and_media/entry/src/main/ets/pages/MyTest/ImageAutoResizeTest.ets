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
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function imageAutoResizeTest() {
  /*
* Image组件 AutoResize属性
* 找到画面id为imageAutoResize的Image组件
* 找到画面文本为ImageAutoResize1的Button组件
* 获取image的AutoResize属性与期待值true比对
* 点击button，变更image的AutoResize属性值为false
* 获取image的AutoResize属性与期待值false比对
*/
  defineTest('imageAutoTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageAutoTestDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageAutoResize').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ImageAutoResize1').enabled(true))
    let autoResize1: string = await image.getInspectorInfo()
    assertTrue(JSON.parse(autoResize1).$attrs.autoResize)
    await button.tap()
    let autoResize2: string = await image.getInspectorInfo()
    assertFalse(JSON.parse(autoResize2).$attrs.autoResize)
  }, 0)
}