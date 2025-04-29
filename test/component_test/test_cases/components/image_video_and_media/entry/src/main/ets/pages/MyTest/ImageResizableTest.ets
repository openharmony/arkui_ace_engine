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

/*
* Image组件 Resizable属性
* 找到画面id为imageResizeable的Image组件
* 获取image的Resizable.slice.top属性与期待值50比对
* 获取image的Resizable.slice.left属性与期待值50比对
* 获取image的Resizable.slice.bottom属性与期待值50比对
* 获取image的Resizable.slice.right属性与期待值50比对
*/

export default async function imageResizableTest() {
  defineTest('imageResizableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageResizableTestDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageResizeable').enabled(true))
    let resizable: string = await image.getInspectorInfo()
    assertFalse(JSON.parse(resizable).$attrs.resizable == undefined)
    assertEqual(JSON.parse(resizable)
      .$attrs
      .resizable
      .slice
      .top, 30)
    assertEqual(JSON.parse(resizable)
      .$attrs
      .resizable
      .slice
      .left, 30)
    assertEqual(JSON.parse(resizable)
      .$attrs
      .resizable
      .slice
      .bottom, 30)
    assertEqual(JSON.parse(resizable)
      .$attrs
      .resizable
      .slice
      .right, 30)
  }, 0)
}