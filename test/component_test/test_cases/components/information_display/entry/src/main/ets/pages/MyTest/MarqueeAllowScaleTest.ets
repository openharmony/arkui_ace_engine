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

export default async function marqueeAllowScaleTest() {
  /*
* Marquee组件 AllowScale属性
* 找到画面id为marqueeAllowScale的Marquee组件
* 找到画面文本为MarqueeAllowScale的Button组件
* 获取marquee的AllowScale属性与期待值false比对
* 点击button，变更marquee的AllowScale属性值为true
* 获取marquee的AllowScale属性与期待值true比对
*/
  defineTest('marqueeAllowScaleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marqueeAllowScaleTestDemo running')
    let driver: Tester = Tester.create()
    let marquee: Component = await driver.findComponent(Matcher.create().id('marqueeAllowScale').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('MarqueeAllowScale').enabled(true))
    let allowScale1: string = await marquee.getInspectorInfo()
    assertFalse(JSON.parse(allowScale1).$attrs.allowScale)
    await button.tap()
    let allowScale2: string = await marquee.getInspectorInfo()
    assertTrue(JSON.parse(allowScale2).$attrs.allowScale)
  }, 0)
}