import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  searchParentBlock,
  Slide,
  sliderDrag,
  Search,
  ToggleClick
} from '../../utils';

const TAG = 'BadgeBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function BadgeBootcampTest() {
  describe('BadgeBootcampTest', () => {
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

        await driver.delayMs(6000);
        console.info(TAG + 'BadgeBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('信息标记/Badge'))
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
     * 测试组件BadgeParamWithNumber.count且获取属性正确
     */
    it('ArkUI_Badge_0001', 0, async (done: Function) => {
      await searchParentBlock('badgeType', true, '参数列表')
      await Search('参数列表', 'BadgeParamWithNumber.count')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithNumber.count',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('count', JsonType.value),
        ],
        assertEqual: '100'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithNumber.count',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('count', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();
    })
    /**
     * 测试组件BadgeParamWithNumber.maxCount且获取属性正确
     */
    it('ArkUI_Badge_0002', 0, async (done: Function) => {
      await searchParentBlock('badgeType', true, '参数列表')
      await Search('参数列表', 'BadgeParamWithNumber.maxCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithNumber.maxCount',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxCount', JsonType.value),
        ],
        assertEqual: '1000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithNumber.maxCount',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxCount', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();
    })
    /**
     * 测试组件BadgeParamWithString.value且获取属性正确
     */
    it('ArkUI_Badge_0003', 0, async (done: Function) => {
      await searchParentBlock('badgeType', true, '参数列表')
      await radioClick({
        radioClickObj: 1
      })
      await Search('参数列表', 'BadgeParamWithString.value')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithString.value',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: 'new'
      })

      done();
    })

    it('ArkUI_Badge_0004', 0, async (done: Function) => {
      await searchParentBlock('badgeType', true, '参数列表')
      await radioClick({
        radioClickObj: 1
      })
      await Search('参数列表', 'BadgeParamWithString.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithString.value',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: 'text'
      })

      done();
    })

    it('ArkUI_Badge_0005', 0, async (done: Function) => {
      await searchParentBlock('badgeType', true, '参数列表')
      await radioClick({
        radioClickObj: 1
      })
      await Search('参数列表', 'BadgeParamWithString.value')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithString.value',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: 'number'
      })

      done();
    })

    it('ArkUI_Badge_0006', 0, async (done: Function) => {
      await searchParentBlock('badgeType', true, '参数列表')
      await radioClick({
        radioClickObj: 1
      })
      await Search('参数列表', 'BadgeParamWithString.value')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'BadgeParamWithString.value',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: 'string'
      })
      await searchParentBlock('badgeType', false, '参数列表')
      done();
    })
    /**
     * 测试组件BadgeStyle.color且获取属性正确
     */
    it('ArkUI_Badge_0007', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FF0A59F7","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0008', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FF646AFD","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0009', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFE7062","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Badge_0010', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.color')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFE9E8ED","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0011', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.color')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.color',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FF1C1C1C","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0012', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();
    })
    /**
     * 测试组件BadgeStyle.fontSize且获取属性正确
     */
    it('ArkUI_Badge_0013', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"20.00fp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"0.00fp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })


      done();
    })
    /**
     * 测试组件BadgeStyle.badgeSize且获取属性正确
     */
    it('ArkUI_Badge_0014', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.badgeSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"32.00fp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"0.00fp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })


      done();
    })
    /**
     * 测试组件BadgeStyle.badgeColor且获取属性正确
     */
    it('ArkUI_Badge_0015', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.badgeColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FF0A59F7","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0016', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.badgeColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FF646AFD","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0017', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.badgeColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFE7062","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Badge_0018', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.badgeColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFE9E8ED","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0019', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.badgeColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FF1C1C1C","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0020', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.badgeColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.badgeColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFFFFFF","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();
    })
    /**
     * 测试组件BadgeStyle.fontWeight且获取属性正确
     */
    it('ArkUI_Badge_0021', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.fontWeight')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: "{\"x\":\"0.00vp\",\"y\":\"0.00vp\",\"color\":\"#FFFFFFFF\",\"fontSize\":\"-1.00vp\",\"badgeColor\":\"#FFFA2A2D\",\"badgeSize\":\"16.00vp\",\"borderColor\":\"#FFFA2A2D\",\"borderWidth\":\"1.00vp\",\"fontWeight\":\"FontWeight.Lighter\"}"
      })

      done();
    })

    it('ArkUI_Badge_0022', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.fontWeight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: "{\"x\":\"0.00vp\",\"y\":\"0.00vp\",\"color\":\"#FFFFFFFF\",\"fontSize\":\"-1.00vp\",\"badgeColor\":\"#FFFA2A2D\",\"badgeSize\":\"16.00vp\",\"borderColor\":\"#FFFA2A2D\",\"borderWidth\":\"1.00vp\",\"fontWeight\":\"FontWeight.Normal\"}"
      })

      done();
    })

    it('ArkUI_Badge_0023', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.fontWeight')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: "{\"x\":\"0.00vp\",\"y\":\"0.00vp\",\"color\":\"#FFFFFFFF\",\"fontSize\":\"-1.00vp\",\"badgeColor\":\"#FFFA2A2D\",\"badgeSize\":\"16.00vp\",\"borderColor\":\"#FFFA2A2D\",\"borderWidth\":\"1.00vp\",\"fontWeight\":\"FontWeight.Regular\"}"
      })

      done();
    })

    it('ArkUI_Badge_0024', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.fontWeight')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: "{\"x\":\"0.00vp\",\"y\":\"0.00vp\",\"color\":\"#FFFFFFFF\",\"fontSize\":\"-1.00vp\",\"badgeColor\":\"#FFFA2A2D\",\"badgeSize\":\"16.00vp\",\"borderColor\":\"#FFFA2A2D\",\"borderWidth\":\"1.00vp\",\"fontWeight\":\"FontWeight.Medium\"}"
      })

      done();
    })

    it('ArkUI_Badge_0025', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.fontWeight')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: "{\"x\":\"0.00vp\",\"y\":\"0.00vp\",\"color\":\"#FFFFFFFF\",\"fontSize\":\"-1.00vp\",\"badgeColor\":\"#FFFA2A2D\",\"badgeSize\":\"16.00vp\",\"borderColor\":\"#FFFA2A2D\",\"borderWidth\":\"1.00vp\",\"fontWeight\":\"FontWeight.Bold\"}"
      })

      done();
    })

    it('ArkUI_Badge_0026', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.fontWeight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.fontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: "{\"x\":\"0.00vp\",\"y\":\"0.00vp\",\"color\":\"#FFFFFFFF\",\"fontSize\":\"-1.00vp\",\"badgeColor\":\"#FFFA2A2D\",\"badgeSize\":\"16.00vp\",\"borderColor\":\"#FFFA2A2D\",\"borderWidth\":\"1.00vp\",\"fontWeight\":\"FontWeight.Bolder\"}"
      })

      done();
    })
    /**
     * 测试组件BadgeStyle.borderColor且获取属性正确
     */
    it('ArkUI_Badge_0027', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.borderColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FF0A59F7","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0028', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.borderColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FF646AFD","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0029', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.borderColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFE7062","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Badge_0030', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.borderColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFE9E8ED","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0031', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.borderColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FF1C1C1C","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();

    })

    it('ArkUI_Badge_0032', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.borderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFFFFFF","borderWidth":"1.00vp","fontWeight":"FontWeight.Normal"}'
      })

      done();
    })
    /**
     * 测试组件BadgeStyle.borderWidth且获取属性正确
     */
    it('ArkUI_Badge_0033', 0, async (done: Function) => {
      await Search('参数列表', 'BadgeStyle.borderWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderWidth',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"10.00vp","fontWeight":"FontWeight.Normal"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'BadgeStyle.borderWidth',
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.obj),
        ],
        assertEqual: '{"x":"0.00vp","y":"0.00vp","color":"#FFFFFFFF","fontSize":"-1.00vp","badgeColor":"#FFFA2A2D","badgeSize":"16.00vp","borderColor":"#FFFA2A2D","borderWidth":"0.00vp","fontWeight":"FontWeight.Normal"}'
      })


      done();
    })
    /**
     * 测试组件BadgePosition且获取属性正确
     */
    it('ArkUI_Badge_0034', 0, async (done: Function) => {
      await Search('参数列表', 'BadgePosition')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'BadgePosition',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('position', JsonType.value),
        ],
        assertEqual: 'BadgePosition.RightTop'
      })

      done();
    })

    it('ArkUI_Badge_0035', 0, async (done: Function) => {
      await Search('参数列表', 'BadgePosition')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'BadgePosition',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('position', JsonType.value),
        ],
        assertEqual: 'BadgePosition.Right'
      })

      done();
    })

    it('ArkUI_Badge_0036', 0, async (done: Function) => {
      await Search('参数列表', 'BadgePosition')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'BadgePosition',
          toggleClickType: ToggleClick.Open
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('position', JsonType.value),
        ],
        assertEqual: 'BadgePosition.Left'
      })

      done();
    })

  })
}

