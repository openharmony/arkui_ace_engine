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

export default async function swiperNextMarginTest() {
  /*
* Swiper组件 NextMargin属性
* 找到画面id为swiperNextMargin1，swiperNextMargin2,swiperNextMargin3,swiper的Swiper组件
* 找到画面文本为SwiperNextMargin1的Button组件
* 获取swiperNextMargin1的NextMargin属性与期待值10.00vp比对
* 获取swiperNextMargin2的NextMargin属性与期待值$r('app.float.ListLanes_float')比对
* 获取swiperNextMargin3的NextMargin属性与期待值20.00vp比对
* 点击button1，变更swiperNextMargin3的NextMargin属性值为'40.00px'
* 获取swiperNextMargin3的NextMargin属性与期待值'40.00px'比对
*/
  defineTest('swiperNextMarginTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperNextMarginTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperNextMargin1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperNextMargin2').enabled(true))
    let swiper3: Component = await driver.findComponent(Matcher.create().id('swiperNextMargin3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperNextMargin1').enabled(true))
    let nextMargin1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(nextMargin1).$attrs.nextMargin, '10.00vp')
    let nextMargin2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(nextMargin2).$attrs.nextMargin, $r('app.float.ListLanes_float'))
    let nextMargin3: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(nextMargin3).$attrs.nextMargin, '20.00vp')
    await button1.tap()
    let nextMargin4: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(nextMargin4).$attrs.nextMargin, '40.00px')
  }, 0)
}