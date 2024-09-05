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

export default async function swiperVerticalTest() {
  /*
* Swiper组件 Vertical属性
* 找到画面id为swiperVertical1的Swiper组件
* 找到画面文本为SwiperVertical1的Button组件
* 获取swiperVertical1的Vertical属性与期待值true比对
* 点击button1，变更swiperVertical1的Vertical属性值为true
* 获取swiperVertical1的Vertical属性与期待值false比对
*/
  defineTest('swiperVerticalTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperVerticalTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperVertical1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperVertical1').enabled(true))
    let vertical1: string = await swiper1.getInspectorInfo()
    assertTrue(JSON.parse(vertical1).$attrs.vertical)
    await button1.tap()
    let vertical2: string = await swiper1.getInspectorInfo()
    assertFalse(JSON.parse(vertical2).$attrs.vertical)
  }, 0)
}