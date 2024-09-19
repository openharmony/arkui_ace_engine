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

export default async function ratingStarStyleTest() {
  /*
   * Rating组件 StarStyle属性
   * 找到画面id为ratingStarStyle1，ratingStarStyle2，ratingStarStyle3的Rating组件
   * 找到画面文本为RatingStarStyle的Button组件
   * 获取ratingStarStyle1的StarStyle属性与期待值{backgroundUri: undefined,foregroundUri: undefined,secondaryUri: undefined}比对
   * 获取ratingStarStyle2的StarStyle属性与期待值
        {backgroundUri: '/pages/slider/StarYellow.png',foregroundUri: undefined,secondaryUri: undefined}比对
   * 获取ratingStarStyle3的StarStyle属性与期待值
        {backgroundUri: '/pages/rating/StarBlue.png',foregroundUri: '/pages/slider/StarYellow.png',secondaryUri: '/pages/rating/StarOrange.png'}比对
   * 点击button，变更ratingStarStyle2的StarStyle属性值为{backgroundUri: '/pages/slider/StarYellow.png'}
   * 获取ratingStarStyle2的StarStyle属性与期待值{backgroundUri: '/pages/slider/StarYellow.png'}比对
   */
  defineTest('ratingStarStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('ratingStarStyleTestDemo running')
    let driver: Tester = Tester.create()
    let ratingStarStyle1: Component = await driver.findComponent(Matcher.create().id('ratingStarStyle1').enabled(true))
    let ratingStarStyle2: Component = await driver.findComponent(Matcher.create().id('ratingStarStyle2').enabled(true))
    let ratingStarStyle3: Component = await driver.findComponent(Matcher.create().id('ratingStarStyle3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RatingStarStyle').enabled(true))

    let starStyle1: string = await ratingStarStyle1.getInspectorInfo()
    assertEqual(JSON.parse(starStyle1).$attrs.starStyle.backgroundUri, undefined)
    assertEqual(JSON.parse(starStyle1).$attrs.starStyle.foregroundUri, undefined)
    assertEqual(JSON.parse(starStyle1).$attrs.starStyle.secondaryUri, undefined)

    let starStyle2: string = await ratingStarStyle2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(starStyle2).$attrs.starStyle).backgroundUri, '/pages/slider/StarYellow.png')
    assertEqual(JSON.parse(starStyle2).$attrs.starStyle.foregroundUri, undefined)
    assertEqual(JSON.parse(starStyle2).$attrs.starStyle.secondaryUri, undefined)

    let starStyle3: string = await ratingStarStyle3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(starStyle3).$attrs.starStyle).backgroundUri, '/pages/rating/StarBlue.png')
    assertEqual(JSON.parse(JSON.parse(starStyle3).$attrs.starStyle).foregroundUri, '/pages/slider/StarYellow.png')
    assertEqual(JSON.parse(JSON.parse(starStyle3).$attrs.starStyle).secondaryUri, '/pages/rating/StarOrange.png')

    await button.tap()
    let starStyle4: string = await ratingStarStyle2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(starStyle4).$attrs.starStyle).backgroundUri, '/pages/slider/StarYellow.png')
  }, 0)
}