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

const TAG = 'ChipBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function ChipBootcampTest() {
  describe('ChipBootcampTest', () => {
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
        console.info(TAG + 'ChipBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(4000);

        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(3000);

        let scrollSearch: Component = await driver.findComponent(ON.text('操作块/Chip'))
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
     * 测试组件options.size
     */
    it('ArkUI_Chip_0001', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.size')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.size',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0002', 0, async (done: Function) => {
      await Search('参数列表', 'options.size')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.size',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.enabled
     */
    it('ArkUI_Chip_0003', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.enabled')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.enabled',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0004', 0, async (done: Function) => {
      await Search('参数列表', 'options.enabled')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.enabled',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.activated
     */
    it('ArkUI_Chip_0005', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.activated')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.activated',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0006', 0, async (done: Function) => {
      await Search('参数列表', 'options.activated')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.activated',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.prefixIcon.src
     */
    it('ArkUI_Chip_0007', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.prefixIcon.src')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0008', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.src')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0009', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.src')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.src',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0010', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.src')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0011', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.src')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0012', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.src')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.src',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.prefixIcon.size.width
     */
    it('ArkUI_Chip_0013', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.prefixIcon.size.width')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.size.width',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.size.width',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.prefixIcon.size.height
     */
    it('ArkUI_Chip_0014', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.prefixIcon.size.height')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.size.height',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.size.height',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.prefixIcon.fillColor
     */
    it('ArkUI_Chip_0015', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.prefixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0016', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0017', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0018', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0019', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0020', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.fillColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.prefixIcon.activatedFillColor
     */
    it('ArkUI_Chip_0021', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.prefixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0022', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0023', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0024', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0025', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0026', 0, async (done: Function) => {
      await Search('参数列表', 'options.prefixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.prefixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.label.text
     */
    it('ArkUI_Chip_0027', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.text')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.label.text',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0028', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.text')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.label.text',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.label.fontSize
     */
    it('ArkUI_Chip_0029', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.fontSize')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.label.fontSize',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0030', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.fontSize')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.label.fontSize',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0031', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.fontSize')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.label.fontSize',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.label.fontColor
     */
    it('ArkUI_Chip_0032', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.fontColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.label.fontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0033', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.fontColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.label.fontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0034', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.fontColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.label.fontColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0035', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.fontColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.label.fontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0036', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.fontColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.label.fontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0037', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.fontColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.label.fontColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.label.activatedFontColor
     */
    it('ArkUI_Chip_0038', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.activatedFontColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.label.activatedFontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0039', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.activatedFontColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.label.activatedFontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0040', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.activatedFontColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.label.activatedFontColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0041', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.activatedFontColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.label.activatedFontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0042', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.activatedFontColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.label.activatedFontColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0043', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.activatedFontColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.label.activatedFontColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.label.labelMargin.left
     */
    it('ArkUI_Chip_0044', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.labelMargin.left')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.label.labelMargin.left',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.label.labelMargin.left',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.label.labelMargin.right
     */
    it('ArkUI_Chip_0045', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.labelMargin.right')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.label.labelMargin.right',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.label.labelMargin.right',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.label.localizedLabelMargin.start.value
     */
    it('ArkUI_Chip_0046', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.localizedLabelMargin.start.value')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.start.value',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.start.value',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.label.localizedLabelMargin.start.unit
     */
    it('ArkUI_Chip_0047', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.localizedLabelMargin.start.unit')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.start.unit',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0048', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.localizedLabelMargin.start.unit')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.start.unit',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0049', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.localizedLabelMargin.start.unit')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.start.unit',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0050', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.localizedLabelMargin.start.unit')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.start.unit',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.label.localizedLabelMargin.end.value
     */
    it('ArkUI_Chip_0051', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.localizedLabelMargin.end.value')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.end.value',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.end.value',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.label.localizedLabelMargin.end.unit
     */
    it('ArkUI_Chip_0052', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.label.localizedLabelMargin.end.unit')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.end.unit',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0053', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.localizedLabelMargin.end.unit')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.end.unit',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0054', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.localizedLabelMargin.end.unit')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.end.unit',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0055', 0, async (done: Function) => {
      await Search('参数列表', 'options.label.localizedLabelMargin.end.unit')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.label.localizedLabelMargin.end.unit',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.suffixIcon.src
     */
    it('ArkUI_Chip_0056', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.suffixIcon.src')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0057', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.src')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0058', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.src')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.src',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0059', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.src')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0060', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.src')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.src',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0061', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.src')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.src',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.suffixIcon.size.width
     */
    it('ArkUI_Chip_0062', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.suffixIcon.size.width')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.size.width',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.size.width',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.suffixIcon.size.height
     */
    it('ArkUI_Chip_0063', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.suffixIcon.size.height')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.size.height',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.size.height',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.suffixIcon.fillColor
     */
    it('ArkUI_Chip_0064', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.suffixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0065', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0066', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0067', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0068', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.fillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0069', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.fillColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.fillColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.suffixIcon.activatedFillColor
     */
    it('ArkUI_Chip_0070', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.suffixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0071', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0072', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0073', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0074', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0075', 0, async (done: Function) => {
      await Search('参数列表', 'options.suffixIcon.activatedFillColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.suffixIcon.activatedFillColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.backgroundColor
     */
    it('ArkUI_Chip_0076', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.backgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.backgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0077', 0, async (done: Function) => {
      await Search('参数列表', 'options.backgroundColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.backgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0078', 0, async (done: Function) => {
      await Search('参数列表', 'options.backgroundColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.backgroundColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0079', 0, async (done: Function) => {
      await Search('参数列表', 'options.backgroundColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.backgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0080', 0, async (done: Function) => {
      await Search('参数列表', 'options.backgroundColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.backgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0081', 0, async (done: Function) => {
      await Search('参数列表', 'options.backgroundColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.backgroundColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })

    /**
     * 测试组件options.activatedBackgroundColor
     */
    it('ArkUI_Chip_0082', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.activatedBackgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.activatedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0083', 0, async (done: Function) => {
      await Search('参数列表', 'options.activatedBackgroundColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.activatedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0084', 0, async (done: Function) => {
      await Search('参数列表', 'options.activatedBackgroundColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.activatedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        

      })

      done();
    })

    it('ArkUI_Chip_0085', 0, async (done: Function) => {
      await Search('参数列表', 'options.activatedBackgroundColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'options.activatedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0086', 0, async (done: Function) => {
      await Search('参数列表', 'options.activatedBackgroundColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'options.activatedBackgroundColor',
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })

    it('ArkUI_Chip_0087', 0, async (done: Function) => {
      await Search('参数列表', 'options.activatedBackgroundColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'options.activatedBackgroundColor',
          toggleClickType: ToggleClick.Close
        },

      })

      done();

    })
    /**
     * 测试组件options.borderRadius
     */
    it('ArkUI_Chip_0088', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.borderRadius')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'options.borderRadius',
          toggleClickType: ToggleClick.Open
        },

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'options.borderRadius',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.allowClose
     */
    it('ArkUI_Chip_0089', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.allowClose')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.allowClose',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0090', 0, async (done: Function) => {
      await Search('参数列表', 'options.allowClose')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.allowClose',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
    /**
     * 测试组件options.direction
     */
    it('ArkUI_Chip_0091', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'options.direction')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'options.direction',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0092', 0, async (done: Function) => {
      await Search('参数列表', 'options.direction')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'options.direction',
          toggleClickType: ToggleClick.Open
        },

      })

      done();
    })

    it('ArkUI_Chip_0093', 0, async (done: Function) => {
      await Search('参数列表', 'options.direction')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'options.direction',
          toggleClickType: ToggleClick.Close
        },

      })

      done();
    })
  })
}