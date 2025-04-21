import { describe, beforeAll, it} from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, Component } from '@kit.TestKit';
import { ON, Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
  Search,
  getToggle,
  searchToggle
} from '../utils';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()
const driver = Driver.create();

export default function SteeperItemBootcampTest() {
  describe('SteeperItemBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      try {
        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });
        
        await driver.delayMs(5000);

        let atomDisplays: Component = await driver.findComponent(ON.text('导航与切换'));
        await atomDisplays.click();
        await driver.delayMs(3500);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[2].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y)
        await driver.delayMs(3500);
        await driver.swipe(width.x, width2.y, width.x, width.y)
        await driver.delayMs(3500);

        let scrollSearch: Component = await driver.findComponent(ON.text('步骤导航项/StepperItem'))
        await scrollSearch.click()
        await driver.delayMs(3500);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(3500);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    /**
     * 测试组件'status'支持设置包含单个子组件为'Skip'且获取属性正确
     */
    it('ArkUI_StepperItem_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'status');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('status', JsonType.value)
        ],
        assertEqual: 'ItemState.Skip'
      })
      done();
    })

    /**
     * 测试组件'status'支持设置包含单个子组件为'Normal'且获取属性正确
     */
    it('ArkUI_StepperItem_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'status');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('status', JsonType.value)
        ],
        assertEqual: 'ItemState.Normal'
      })
      done();
    })

    /**
     * 测试组件'status'支持设置包含单个子组件为'Waiting'且获取属性正确
     */
    it('ArkUI_StepperItem_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'status');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('status', JsonType.value)
        ],
        assertEqual: 'ItemState.Waiting'
      })
      done();
    })

    /**
     * 测试组件'status'支持设置包含单个子组件为'Disabled'且获取属性正确
     */
    it('ArkUI_StepperItem_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'status');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('status', JsonType.value)
        ],
        assertEqual: 'ItemState.Disabled'
      })
      done();
    })

    /**
     * 测试组件'prevLabel'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_StepperItem_005', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'prevLabel');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'prevLabel'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('prevLabel', JsonType.value)
        ],
        assertEqual: 'prevLabel'
      })
      done();
    })

    /**
     * 测试组件'prevLabel'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_StepperItem_006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'prevLabel');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'prevLabel'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('prevLabel', JsonType.value)
        ],
        assertEqual: '返回'
      })
      done();
    })

    /**
     * 测试组件'nextLabel'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_StepperItem_007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nextLabel');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'nextLabel'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nextLabel', JsonType.value)
        ],
        assertEqual: 'nextLabel'
      })
      done();
    })

    /**
     * 测试组件'nextLabel'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_StepperItem_008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nextLabel');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'nextLabel'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nextLabel', JsonType.value)
        ],
        assertEqual: '下一步'
      })
      done();
    })

    /**
     * 测试组件'pixelRound'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_StepperItem_009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_StepperItem_010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'pixelRound'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.start'支持设置包含单个子组件为'NO_FORCE_ROUND'且获取属性正确
     */
    it('ArkUI_StepperItem_011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.start');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.start'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.start'支持设置包含单个子组件为'FORCE_CEIL'且获取属性正确
     */
    it('ArkUI_StepperItem_012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.start');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.start'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.FORCE_CEIL","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.start'支持设置包含单个子组件为'FORCE_FLOOR'且获取属性正确
     */
    it('ArkUI_StepperItem_013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.start');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'pixelRound.start'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.FORCE_FLOOR","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.bottom'支持设置包含单个子组件为'NO_FORCE_ROUND'且获取属性正确
     */
    it('ArkUI_StepperItem_014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.bottom');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.bottom'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.bottom'支持设置包含单个子组件为'FORCE_CEIL'且获取属性正确
     */
    it('ArkUI_StepperItem_015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.bottom');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.bottom'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.FORCE_CEIL"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.bottom'支持设置包含单个子组件为'FORCE_FLOOR'且获取属性正确
     */
    it('ArkUI_StepperItem_016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.bottom');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'pixelRound.bottom'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.FORCE_FLOOR"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.top'支持设置包含单个子组件为'NO_FORCE_ROUND'且获取属性正确
     */
    it('ArkUI_StepperItem_017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.top');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.top'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.top'支持设置包含单个子组件为'FORCE_CEIL'且获取属性正确
     */
    it('ArkUI_StepperItem_018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.top');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.top'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_CEIL","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.top'支持设置包含单个子组件为'FORCE_FLOOR'且获取属性正确
     */
    it('ArkUI_StepperItem_019', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.top');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'pixelRound.top'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_FLOOR","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.end'支持设置包含单个子组件为'NO_FORCE_ROUND'且获取属性正确
     */
    it('ArkUI_StepperItem_020', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.end');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.end'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.end'支持设置包含单个子组件为'FORCE_CEIL'且获取属性正确
     */
    it('ArkUI_StepperItem_021', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.end');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound.end'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.FORCE_CEIL","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.end'支持设置包含单个子组件为'FORCE_FLOOR'且获取属性正确
     */
    it('ArkUI_StepperItem_022', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        }
      })

      await titleSearch('参数列表', 'pixelRound.end');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'pixelRound.end'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.FORCE_FLOOR","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })

    /**
     * 测试组件'pixelRound.end'支持设置包含单个子组件为'FORCE_FLOOR'且获取属性正确
     */
    it('ArkUI_StepperItem_021', 0, async (done: Function) => {
      await titleSearch('参数列表', 'pixelRound');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'pixelRound'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'pixelRound.end');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'pixelRound.end'
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.obj),
          new KeyStruct('end', JsonType.value)
        ],
        assertEqual: 'PixelRoundCalcPolicy.FORCE_FLOOR'
      })
      done();
    })

    /**
     * 测试开启position
     */
    it('ArkUI_StepperItem_Comp_0001', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0002', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0003', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.right且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0005', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试关闭position
     */
    it('ArkUI_StepperItem_Comp_0006', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })
    /**
     * 测试开启markAnchor
     */
    it('ArkUI_StepperItem_Comp_0007', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试关闭markAnchor
     */
    it('ArkUI_StepperItem_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })
    /**
     * 测试开启offset
     */
    it('ArkUI_StepperItem_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0012', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件offset.y且获取属性正确
     */
    it('ArkUI_StepperItem_Comp_0013', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试关闭offset
     */
    it('ArkUI_StepperItem_Comp_0014', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })
    /**
     * 测试组件borderStyle
     */
    it('ArkUI_StepperItem_Comp_0015', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0016', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0017', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Solid'
      })
      done();
    })
    /**
     * 测试组件borderWidth
     */
    it('ArkUI_StepperItem_Comp_0018', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    /**
     * 测试组件borderColor
     */
    it('ArkUI_StepperItem_Comp_0019', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0020', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0021', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })
    it('ArkUI_StepperItem_Comp_0022', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0023', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0024', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件borderRadius
     */
    it('ArkUI_StepperItem_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件background.align
     */
    it('ArkUI_StepperItem_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'background.align');
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0027', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0028', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0029', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0030', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0031', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0032', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0033', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })
    it('ArkUI_StepperItem_Comp_0034', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    /**
     * 测试组件backgroundColor
     */
    it('ArkUI_StepperItem_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0036', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0037', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0038', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0039', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0040', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件backgroundImage.src
     */
    it('ArkUI_StepperItem_Comp_0041', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await driver.delayMs(3500)
      done();
    })
    it('ArkUI_StepperItem_Comp_0042', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      await driver.delayMs(3500)
      done();
    })
    /**
     * 测试组件backgroundImage.repeat
     */
    it('ArkUI_StepperItem_Comp_0043', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.NoRepeat'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0044', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.X'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0045', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.Y'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0046', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.XY'
      })

      done();

    })
    /**
     * 测试组件backgroundImageSize
     */
    it('ArkUI_StepperItem_Comp_0047', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Auto'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0048', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Cover'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0049', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Contain'
      })

      done();

    })
    it('ArkUI_StepperItem_Comp_0050', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'StepperItem',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.FILL'
      })
      done();
    })
  })
}
