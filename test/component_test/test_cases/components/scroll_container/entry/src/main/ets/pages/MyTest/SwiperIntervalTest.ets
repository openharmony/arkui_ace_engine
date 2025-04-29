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

export default async function swiperIntervalTest() {
  /*
* Swiper组件 Interval属性
* 找到画面id为swiperIntervalTest1的Swiper组件
* 找到画面文本为SwiperInterval1的Button组件
* 获取swiperIntervalTest1的Interval属性与期待值1000比对
* 点击button1，变更swiperIntervalTest1的Interval属性值为4000
* 获取swiperIntervalTest1的Interval属性与期待值4000比对
*/
  defineTest('swipeIntervalTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperIntervalTestDemo running')
    let driver: Tester = Tester.create()
    let swiperIntervalTest1: Component =
      await driver.findComponent(Matcher.create().id('swiperInterval1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperInterval1').enabled(true))
    let interval1: string = await swiperIntervalTest1.getInspectorInfo()
    assertEqual(JSON.parse(interval1).$attrs.interval, '1000')
    await button1.tap()
    let interval2: string = await swiperIntervalTest1.getInspectorInfo()
    assertEqual(JSON.parse(interval2).$attrs.interval, '4000')
  }, 0)
}