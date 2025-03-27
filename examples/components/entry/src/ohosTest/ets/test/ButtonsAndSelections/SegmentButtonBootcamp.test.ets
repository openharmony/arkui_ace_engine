import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver } from '@kit.TestKit';
import { Point, Component, ON } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  Slide,
  sliderDrag,
  ToggleClick
} from '../../utils';

const TAG = 'TextInputBootcamp'
/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SegmentButtonBootcampTest() {
  describe('SegmentButtonBootcampTest', () => {
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
        await driver.delayMs(1500);
        console.info(TAG + 'SelectBootcamp001' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('操作类'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[7].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('分段按钮'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })
    //SegmentButton组件所以特有属性无法获取属性值进行断言
    // SegmentButtonOptions.type
    /*
     *测试组件SegmentButtonOptions.type支持设置tab且获取属性正确
     * */
    it('ArkUI_SegmentButton_001 ', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'SegmentButtonOptions.type')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     *测试组件SegmentButtonOptions.type支持设置capsule且获取属性正确
     * */
    it('ArkUI_SegmentButton_002 ', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'SegmentButtonOptions.type')
      await driver.delayMs(1000)
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    // Multiply
    /*
     *测试组件Multiply支持设置true且获取属性正确
     * */
    it('ArkUI_SegmentButton_003 ', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'Multiply')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     *测试组件Multiply支持设置false且获取属性正确
     * */
    it('ArkUI_SegmentButton_004 ', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'Multiply')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    // buttons
    /*
     *测试组件buttons支持设置SegmentButtonTextItem且获取属性正确
     * */
    it('ArkUI_SegmentButton_005 ', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'buttons')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     *测试组件buttons支持设置SegmentButtonIconItem且获取属性正确
     * */
    it('ArkUI_SegmentButton_006 ', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'buttons')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     *测试组件buttons支持设置SegmentButtonIconTextItem且获取属性正确
     * */
    it('ArkUI_SegmentButton_007 ', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'buttons')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //fontColor
    /*
    *测试组件fontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_SegmentButton_008', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_009', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_010', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_011', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_012', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_013', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //selectedFontColor
    /*
    *测试组件selectedFontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_SegmentButton_014', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /**
     * 测试组件selectedFontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_015', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件selectedFontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_016', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /**
     * 测试组件selectedFontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_017', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件selectedFontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_018', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件selectedFontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_019', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //fontWeight
    /*
     测试组件fontWeight支持设置FontWeight.Lighter且获取属性正确
     * */
    it('ArkUI_SegmentButton_020', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /**
     * 测试组件fontWeight支持设置FontWeight.Normal且获取属性正确
     * */
    it('ArkUI_SegmentButton_021', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /**
     * 测试组件fontWeight支持设置FontWeight.Regular且获取属性正确
     **/
    it('ArkUI_SegmentButton_022', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /**
     * 测试组件fontWeight支持设置FontWeight.Medium且获取属性正确
     **/
    it('ArkUI_SegmentButton_023', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /**
     * 测试组件fontWeight支持设置FontWeight.Bold且获取属性正确
     **/
    it('ArkUI_SegmentButton_024', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /**
     * 测试组件fontWeight支持设置FontWeight.Bolder且获取属性正确
     * */
    it('ArkUI_SegmentButton_025', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //selectedFontWeight
    /*
     测试组件selectedFontWeight支持设置selectedFontWeight.Lighter且获取属性正确
     * */
    it('ArkUI_SegmentButton_026', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /**
     * 测试组件selectedFontWeight支持设置selectedFontWeight.Normal且获取属性正确
     * */
    it('ArkUI_SegmentButton_027', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /**
     * 测试组件selectedFontWeight支持设置selectedFontWeight.Regular且获取属性正确
     **/
    it('ArkUI_SegmentButton_028', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /**
     * 测试组件selectedFontWeight支持设置selectedFontWeight.Medium且获取属性正确
     **/
    it('ArkUI_SegmentButton_029', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /**
     * 测试组件selectedFontWeight支持设置selectedFontWeight.Bold且获取属性正确
     **/
    it('ArkUI_SegmentButton_030', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /**
     * 测试组件selectedFontWeight支持设置selectedFontWeight.Bolder且获取属性正确
     * */
    it('ArkUI_SegmentButton_031', 0, async (done: Function) => {
      await Search('参数列表', 'selectedFontWeight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //backgroundColor
    /*
    *测试组件backgroundColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_SegmentButton_032', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /**
     * 测试组件backgroundColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_033', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件backgroundColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_034', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /**
     * 测试组件backgroundColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_035', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件backgroundColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_036', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件backgroundColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_037', 0, async (done: Function) => {
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //selectedBackgroundColor
    /*
    *测试组件selectedBackgroundColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_SegmentButton_038', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_039', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_040', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_041', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_042', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_SegmentButton_043', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //imageSize.width
    it('ArkUI_SegmentButton_044', 0, async (done: Function) => {
      await Search('参数列表', 'imageSize.width')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //imageSize.height
    it('ArkUI_SegmentButton_045', 0, async (done: Function) => {
      await Search('参数列表', 'imageSize.height')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //buttonPadding.top
    it('ArkUI_SegmentButton_046', 0, async (done: Function) => {
      await Search('参数列表', 'buttonPadding.top')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //buttonPadding.right
    it('ArkUI_SegmentButton_047', 0, async (done: Function) => {
      await Search('参数列表', 'buttonPadding.right')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //buttonPadding.bottom
    it('ArkUI_SegmentButton_048', 0, async (done: Function) => {
      await Search('参数列表', 'buttonPadding.bottom')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //buttonPadding.left
    it('ArkUI_SegmentButton_049', 0, async (done: Function) => {
      await Search('参数列表', 'buttonPadding.left')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //textPadding.top
    it('ArkUI_SegmentButton_050', 0, async (done: Function) => {
      await Search('参数列表', 'textPadding.top')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //textPadding.right
    it('ArkUI_SegmentButton_051', 0, async (done: Function) => {
      await Search('参数列表', 'textPadding.right')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //textPadding.bottom
    it('ArkUI_SegmentButton_052', 0, async (done: Function) => {
      await Search('参数列表', 'textPadding.bottom')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //textPadding.left
    it('ArkUI_SegmentButton_053', 0, async (done: Function) => {
      await Search('参数列表', 'textPadding.left')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //localizedButtonPadding.top.unit
    /*
     测试组件localizedButtonPadding.top.unit支持设置PX且获取属性正确
     * */
    it('ArkUI_SegmentButton_054', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.top.unit')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.top.unit支持设置VP且获取属性正确
     * */
    it('ArkUI_SegmentButton_055', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.top.unit')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.top.unit支持设置FP且获取属性正确
     **/
    it('ArkUI_SegmentButton_056', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.top.unit')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.top.unit支持设置PERCENT且获取属性正确
     **/
    it('ArkUI_SegmentButton_057', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.top.unit')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.top.unit支持设置LPX且获取属性正确
     **/
    it('ArkUI_SegmentButton_058', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.top.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //localizedButtonPadding.top.value
    it('ArkUI_SegmentButton_059', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.top.value')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //localizedButtonPadding.end.unit
    /*
     测试组件localizedButtonPadding.end.unit支持设置PX且获取属性正确
     * */
    it('ArkUI_SegmentButton_060', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.end.unit')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.end.unit支持设置VP且获取属性正确
     * */
    it('ArkUI_SegmentButton_061', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.end.unit')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.end.unit支持设置FP且获取属性正确
     **/
    it('ArkUI_SegmentButton_062', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.end.unit')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.end.unit支持设置PERCENT且获取属性正确
     **/
    it('ArkUI_SegmentButton_063', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.end.unit')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.end.unit支持设置LPX且获取属性正确
     **/
    it('ArkUI_SegmentButton_064', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.end.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //localizedButtonPadding.end.value
    it('ArkUI_SegmentButton_065', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.end.value')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //localizedButtonPadding.bottom.unit
    /*
     测试组件localizedButtonPadding.bottom.unit支持设置PX且获取属性正确
     * */
    it('ArkUI_SegmentButton_066', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.bottom.unit')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.bottom.unit支持设置VP且获取属性正确
     * */
    it('ArkUI_SegmentButton_067', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.bottom.unit')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.bottom.unit支持设置FP且获取属性正确
     **/
    it('ArkUI_SegmentButton_068', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.bottom.unit')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.bottom.unit支持设置PERCENT且获取属性正确
     **/
    it('ArkUI_SegmentButton_069', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.bottom.unit')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.bottom.unit支持设置LPX且获取属性正确
     **/
    it('ArkUI_SegmentButton_070', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.bottom.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //localizedButtonPadding.bottom.value
    it('ArkUI_SegmentButton_071', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.bottom.value')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //localizedButtonPadding.start.unit
    /*
     测试组件localizedButtonPadding.start.unit支持设置PX且获取属性正确
     * */
    it('ArkUI_SegmentButton_072', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.start.unit')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.start.unit支持设置VP且获取属性正确
     * */
    it('ArkUI_SegmentButton_073', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.start.unit')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.start.unit支持设置FP且获取属性正确
     **/
    it('ArkUI_SegmentButton_074', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.start.unit')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.start.unit支持设置PERCENT且获取属性正确
     **/
    it('ArkUI_SegmentButton_075', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.start.unit')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /**
     * 测试组件localizedButtonPadding.start.unit支持设置LPX且获取属性正确
     **/
    it('ArkUI_SegmentButton_076', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.start.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //localizedButtonPadding.start.value
    it('ArkUI_SegmentButton_077', 0, async (done: Function) => {
      await Search('参数列表', 'localizedButtonPadding.start.value')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //localizedTextPadding.top.unit
    /*
     测试组件localizedTextPadding.top.unit支持设置PX且获取属性正确
     * */
    it('ArkUI_SegmentButton_078', 0, async (done: Function) => {
      await Search('参数列表', 'localizedTextPadding.top.unit')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /**
     * 测试组件localizedTextPadding.top.unit支持设置VP且获取属性正确
     * */
    it('ArkUI_SegmentButton_079', 0, async (done: Function) => {
      await Search('参数列表', 'localizedTextPadding.top.unit')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /**
     * 测试组件localizedTextPadding.top.unit支持设置FP且获取属性正确
     **/
    it('ArkUI_SegmentButton_080', 0, async (done: Function) => {
      await Search('参数列表', 'localizedTextPadding.top.unit')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /**
     * 测试组件localizedTextPadding.top.unit支持设置PERCENT且获取属性正确
     **/
    it('ArkUI_SegmentButton_081', 0, async (done: Function) => {
      await Search('参数列表', 'localizedTextPadding.top.unit')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /**
     * 测试组件localizedTextPadding.top.unit支持设置LPX且获取属性正确
     **/
    it('ArkUI_SegmentButton_082', 0, async (done: Function) => {
      await Search('参数列表', 'localizedTextPadding.top.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
  })
}