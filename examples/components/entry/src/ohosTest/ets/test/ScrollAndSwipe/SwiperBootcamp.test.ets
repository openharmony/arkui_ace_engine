import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  ToggleClick
} from '../../utils';

const TAG = 'SwiperBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function SwiperBootcampTest() {

  describe('SwiperBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(10000);
        console.info(TAG + 'SwiperBootcamp001' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('滚动与滑动'));
        await atomDisplays.click();
        await driver.delayMs(6000);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('轮播容器/Swiper'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })
    /**
     * 测试组件Indicator.itemWidth且获取属性正确
     */
    it('ArkUI_Swiper_0001', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.itemWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'DotIndicator.itemWidth',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"30.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'DotIndicator.itemWidth',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"1.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })
    /**
     * 测试组件DotIndicator.itemHeight且获取属性正确
     */
    it('ArkUI_Swiper_0002', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.itemHeight')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'DotIndicator.itemHeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"30.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'DotIndicator.itemHeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"1.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })
    /**
     * 测试组件DotIndicator.selectedItemWidth且获取属性正确
     */
    it('ArkUI_Swiper_0003', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedItemWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedItemWidth',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"40.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedItemWidth',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"1.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })


      done();
    })
    /**
     * 测试组件DotIndicator.itemHeight且获取属性正确
     */
    it('ArkUI_Swiper_0004', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedItemHeight')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedItemHeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"30.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedItemHeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"1.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })
    /**
     * 测试组件DotIndicator.mask且获取属性正确
     */
    it('ArkUI_Swiper_0005', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'DotIndicator.mask',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"true","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0006', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.mask')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'DotIndicator.mask',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })
    /**
     * 测试组件DotIndicator.color且获取属性正确
     */
    it('ArkUI_Swiper_0007', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'DotIndicator.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#FF0A59F7","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0008', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'DotIndicator.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#FF646AFD","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0009', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'DotIndicator.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#FFFE7062","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0010', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.color')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'DotIndicator.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#FFE9E8ED","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0011', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.color')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'DotIndicator.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#FF1C1C1C","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0012', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'DotIndicator.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#FFFFFFFF","mask":"false","maxDisplayCount":0}'
      })

      done();
    })
    /**
     * 测试组件DotIndicator.selectedColor且获取属性正确
     */
    it('ArkUI_Swiper_0013', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF0A59F7","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0014', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF646AFD","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0015', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FFFE7062","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0016', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FFE9E8ED","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0017', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF1C1C1C","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })

    it('ArkUI_Swiper_0018', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.selectedColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'DotIndicator.selectedColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FFFFFFFF","color":"#19182431","mask":"false","maxDisplayCount":0}'
      })

      done();
    })
    /**
     * 测试组件DotIndicator.maxDisplayCount且获取属性正确
     */
    it('ArkUI_Swiper_0019', 0, async (done: Function) => {
      await searchParentBlock('isDot', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'DotIndicator.maxDisplayCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'DotIndicator.maxDisplayCount',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":9}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'DotIndicator.maxDisplayCount',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"0.00vp","right":"0.00vp","bottom":"0.00vp","itemWidth":"6.00vp","itemHeight":"6.00vp","selectedItemWidth":"6.00vp","selectedItemHeight":"6.00vp","selectedColor":"#FF007DFF","color":"#19182431","mask":"false","maxDisplayCount":6}'
      })
      await Search('参数列表', 'isDot',)
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    /**
     * 测试组件DigitIndicator.fontColor且获取属性正确
     */
    it('ArkUI_Swiper_0020', 0, async (done: Function) => {

      await Search('参数列表', 'DigitIndicator.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.fontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF0A59F7","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0021', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.fontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF646AFD","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0022', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.fontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FFFE7062","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0023', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.fontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FFE9E8ED","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0024', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.fontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF1C1C1C","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0025', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.fontColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FFFFFFFF","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })
    /**
     * 测试组件DigitIndicator.selectedFontColor且获取属性正确
     */
    it('ArkUI_Swiper_0026', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedFontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedFontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF0A59F7","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0027', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedFontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedFontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF646AFD","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0028', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedFontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedFontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FFFE7062","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0029', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedFontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedFontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FFE9E8ED","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0030', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedFontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedFontColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF1C1C1C","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Swiper_0031', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedFontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedFontColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FFFFFFFF","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();

    })
    /**
     * 测试组件DigitIndicator.digitFont.size且获取属性正确
     */
    it('ArkUI_Swiper_0032', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.digitFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.size',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"30.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.size',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"10.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

  })
}
