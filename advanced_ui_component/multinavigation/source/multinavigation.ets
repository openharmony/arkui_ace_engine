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

import { hilog } from '@kit.PerformanceAnalysisKit';
import deviceInfo from '@ohos.deviceInfo';
import { display, mediaquery } from '@kit.ArkUI';
import base from '@ohos.base';

const TAG = 'DeviceHelper';

/**
 * device info util
 *
 */
export class DeviceHelper {
  static readonly TYPE_DEFAULT = 'default';
  static readonly TYPE_PHONE = 'phone';
  static readonly TYPE_TABLET = 'tablet';
  static readonly DEVICE_TYPE = deviceInfo.deviceType;

  /**
   * whether the device type is phone
   *
   * @returns true if is phone
   */
  static isPhone(): boolean {
    return (DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_PHONE ||
      DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_DEFAULT);
  }

  /**
   * whether the device type is tablet
   *
   * @returns true if is tablet
   */
  public static isTablet(): boolean {
    return DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_TABLET;
  }

  /**
   * Check if is foldable
   *
   * @returns true if is foldable
   */
  static isFold(): boolean {
    let isFold: boolean = false;
    try {
      isFold = display.isFoldable();
    } catch (e) {
      hilog.error(0x0000, TAG, 'isFold -> isFoldable try error:', e);
    }
    return isFold;
  }

  /**
   * Check if is expanded
   *
   * @returns true if is expanded
   */
  static isExpanded(): boolean {
    let isExpanded: boolean = false;
    try {
      isExpanded = display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_EXPANDED;
    } catch (e) {
      hilog.error(0x0000, TAG, 'isExpanded -> try error:', e);
    }
    return isExpanded;
  }

  /**
   * Check if is column
   *
   * @returns true if is column
   */
  static isColumn(): boolean {
    let isColumn: boolean = false;
    try {
      isColumn = display.isFoldable() && (display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_EXPANDED ||
        display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_HALF_FOLDED);
    } catch (e) {
      hilog.error(0x0000, TAG, 'isColumn -> try error:', e);
    }
    return isColumn;
  }

  /**
   * Check if is straight product
   *
   * @returns true if is straight product
   */
  public static isStraightProduct(): boolean {
    return DeviceHelper.isPhone() && !DeviceHelper.isFold();
  }
}

export class DeviceListenerManager {
  private static instance: DeviceListenerManager | undefined;
  private portraitListener = mediaquery.matchMediaSync('(orientation: portrait)');
  private drawableWidthLargeListener = mediaquery.matchMediaSync('(width >= 600vp)');
  private isPortrait: boolean | undefined = undefined;
  private onOrientationChange: Function | undefined = undefined;
  private isLarge: boolean | undefined = undefined;
  private onDrawableWidthChange: Function | undefined = undefined;

  public static getInstance(): DeviceListenerManager {
    if (DeviceListenerManager.instance === undefined) {
      DeviceListenerManager.instance = new DeviceListenerManager();
    }
    return DeviceListenerManager.instance;
  }

  private onPortraitChange(result: mediaquery.MediaQueryResult) {
    let isChanged: boolean = false;
    if (DeviceListenerManager.getInstance().isPortrait === undefined) {
      DeviceListenerManager.getInstance().isPortrait = result.matches;
      isChanged = true;
    } else {
      if (result.matches) {
        if (!DeviceListenerManager.getInstance().isPortrait) {
          DeviceListenerManager.getInstance().isPortrait = true;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display portrait');
        }
      } else {
        if (DeviceListenerManager.getInstance().isPortrait) {
          DeviceListenerManager.getInstance().isPortrait = false;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display landscape');
        }
      }
    }
    if (isChanged) {
      DeviceListenerManager.getInstance().notifyOrientationChange();
    }
  }

  private notifyOrientationChange() {
    this.onOrientationChange && this.onOrientationChange(this.isPortrait);
  }

  private onDrawableWidthLargeChange(result: mediaquery.MediaQueryResult) {
    let isChanged: boolean = false;
    if (DeviceListenerManager.getInstance().isLarge === undefined) {
      DeviceListenerManager.getInstance().isLarge = result.matches;
      isChanged = true;
    } else {
      if (result.matches) {
        if (!DeviceListenerManager.getInstance().isLarge) {
          DeviceListenerManager.getInstance().isLarge = true;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display isLarge');
        }
      } else {
        if (DeviceListenerManager.getInstance().isLarge) {
          DeviceListenerManager.getInstance().isLarge = false;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display not large');
        }
      }
    }

    if (isChanged) {
      DeviceListenerManager.getInstance().notifyWidthChange();
    }
  }

  private notifyWidthChange() {
    this.onDrawableWidthChange && this.onDrawableWidthChange(this.isLarge);
  }

  public registerOrientationLister(func: Function): void {
    this.onOrientationChange = func;
    this.onOrientationChange && this.isPortrait && this.onOrientationChange(this.isPortrait);
  }

  public unregisterOrientationLister(): void {
    this.onOrientationChange = undefined;
  }

  public registerDrawableWidthLister(func: Function): void {
    this.onDrawableWidthChange = func;
    this.onDrawableWidthChange && this.isLarge && this.onDrawableWidthChange(this.isLarge);
  }

  public unregisterDrawableWidthLister(): void {
    this.onDrawableWidthChange = undefined;
  }

  public initListener(): void {
    this.portraitListener.on('change', this.onPortraitChange);
    this.drawableWidthLargeListener.on('change', this.onDrawableWidthLargeChange);
  }

  public finalizeListener() {
    this.portraitListener.off('change', this.onPortraitChange);
    this.drawableWidthLargeListener.off('change', this.onDrawableWidthLargeChange);
  }
}

@Observed
export class NavWidthRangeAttrModifier implements AttributeModifier<NavigationAttribute> {
  isApplicationSet: boolean = false;
  minHomeWidth: Percentage = '50%';
  maxHomeWidth: Percentage = '50%';

  applyNormalAttribute(instance: NavigationAttribute): void {
    if (this.isApplicationSet) {
      instance.navBarWidthRange([this.minHomeWidth, this.maxHomeWidth]);
    }
  }
}

@Component
export struct SubNavigation {
  @Link isPortrait: boolean;
  @State displayMode: number = 0;
  @ObjectLink multiStack: MultiNavPathStack
  @BuilderParam navDestination: NavDestinationBuildFunction;
  primaryStack: MyNavPathStack = new MyNavPathStack();
  @State secondaryStack: MyNavPathStack = new MyNavPathStack();
  @State primaryWidth: number | string = '50%';
  @ObjectLink needRenderIsFullScreen: NeedRenderIsFullScreen;
  @ObjectLink needRenderLeftClickCount: NeedRenderLeftClickCount;
  @ObjectLink navWidthRangeModifier: NavWidthRangeAttrModifier;
  @ObjectLink needRenderDisplayMode: NeedRenderDisplayMode;
  onNavigationModeChange?: OnNavigationModeChangeCallback = (mode: NavigationMode) => {};

  @Builder
  SubNavDestination(name: string, param?: object) {
    this.navDestination(name, param);
  }

  getMode(): NavigationMode {
    this.displayMode = this.needRenderDisplayMode.displayMode;
    if (DeviceHelper.isPhone() && DeviceHelper.isStraightProduct()) {
      return NavigationMode.Stack;
    }
    if (this.displayMode === display.FoldStatus.FOLD_STATUS_UNKNOWN) {
      try {
        this.displayMode = display.getFoldStatus();
      } catch (err) {
        hilog.warn(0x0000, 'MultiNavigation', 'Failed to get fold status. error:' + JSON.stringify(err));
      }
    }
    if (DeviceHelper.isTablet() && this.isPortrait) {
      hilog.info(0x0000, 'MultiNavigation', 'SubNavigation getMode tablet portrait');
      return NavigationMode.Stack;
    }
    if (this.needRenderIsFullScreen.isFullScreen == undefined) {
      if (DeviceHelper.isPhone()) {
        return this.secondaryStack.size() > 0 && DeviceHelper.isColumn() ? NavigationMode.Auto : NavigationMode.Stack;
      }
      return this.secondaryStack.size() > 0 ? NavigationMode.Auto : NavigationMode.Stack;
    }
    return this.needRenderIsFullScreen.isFullScreen ? NavigationMode.Stack : NavigationMode.Auto;
  }

  aboutToAppear(): void {
    hilog.debug(0x0000, 'MultiNavigation', 'SubNavigation aboutToAppear param = ' + JSON.stringify(this.primaryStack));
  }

  build() {
    NavDestination() {
      Navigation(this.secondaryStack) {
        Navigation(this.primaryStack) {
        }
        .hideNavBar(true)
        .mode(NavigationMode.Stack)
        .navDestination(this.SubNavDestination)
        .hideTitleBar(true)
        .hideToolBar(true)
        .hideBackButton(true)
        .onTouch((event) => {
          if (event.type === TouchType.Down) {
            this.needRenderLeftClickCount.leftClickCount = 2;
          }
        })
      }
      .mode(this.getMode())
      .onNavigationModeChange(this?.onNavigationModeChange)
      .hideBackButton(true)
      .hideTitleBar(true)
      .navDestination(this.SubNavDestination)
      .navBarWidth(this.primaryWidth)
      .attributeModifier(this.navWidthRangeModifier)
      .onTouch((event) => {
        if (event.type === TouchType.Down) {
          hilog.info(0x0000, 'MultiNavigation', 'outer navigation this.outerStack.leftClickCount ' +
          this.needRenderLeftClickCount.leftClickCount);
          this.needRenderLeftClickCount.leftClickCount--;
        }
      })
    }
    .onBackPressed(() => {
      hilog.debug(0x0000, 'MultiNavigation', 'subNavigation NavDestination onBackPressed');
      if (this.multiStack && this.secondaryStack.size() === 1) {
        hilog.info(0x0000, 'MultiNavigation', 'subNavigation NavDestination onBackPressed multiStack.pop');
        this.multiStack.pop();
        return true;
      }
      return false;
    })
    .hideTitleBar(true)
  }
}

export enum SplitPolicy {
  HOME_PAGE = 0,
  DETAIL_PAGE = 1,
  FULL_PAGE = 2,
  // PlACE_HOLDER_PAGE is not declared in SDK
  PlACE_HOLDER_PAGE = 3,
}

let that: MultiNavigation;

@Component
export struct MultiNavigation {
  private foldStatusCallback: Callback<display.FoldStatus> = (data: display.FoldStatus) => {
    hilog.info(0x0000, 'MultiNavigation', 'foldStatusCallback data.valueOf()=' + data.valueOf());
    this.multiStack.needRenderDisplayMode.displayMode = data.valueOf();
    this.multiStack.handleRefreshPlaceHolderIfNeeded();
  };
  @State multiStack: MultiNavPathStack = new MultiNavPathStack();
  @BuilderParam navDestination: (name: string, param?: object) => void;
  mode: NavigationMode | undefined = undefined;
  onNavigationModeChangeCallback?: (mode: NavigationMode) => void = (mode: NavigationMode) => {
  };
  onHomeShowOnTop?: OnHomeShowOnTopCallback = (name: string) => {};
  @State isPortrait: boolean = false;

  @Builder
  MultiNavDestination(name: string, param?: object) {
    if (name === 'SubNavigation') {
      SubNavigation({
        isPortrait: this.isPortrait,
        multiStack: this.multiStack,
        navDestination: this.navDestination,
        primaryStack: (param as SubNavigationStack).primaryStack,
        secondaryStack: (param as SubNavigationStack).secondaryStack,
        needRenderIsFullScreen: (param as SubNavigationStack).needRenderIsFullScreen,
        needRenderLeftClickCount: this.multiStack.needRenderLeftClickCount,
        navWidthRangeModifier: this.multiStack.navWidthRangeModifier,
        onNavigationModeChange: this?.callback,
        needRenderDisplayMode: this.multiStack.needRenderDisplayMode,
      });
    } else {
      this.navDestination(name, param);
    }
  }

  callback(mode: NavigationMode): void {
    if (that.onNavigationModeChangeCallback !== undefined) {
      if (mode !== that.mode || that.mode === undefined) {
        that?.onNavigationModeChangeCallback(mode);
      }
      that.mode = mode;
    }
  }

  aboutToAppear(): void {
    that = this;
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavigation aboutToAppear');
    try {
      display.on('foldStatusChange', this.foldStatusCallback);
    } catch (exception) {
      console.error('Failed to register callback. Code: ' + JSON.stringify(exception));
    }
    DeviceListenerManager.getInstance().registerOrientationLister((isPortrait: boolean) => {
      hilog.info(0x0000, 'MultiNavigation', 'MultiNavigation orientation change ' + isPortrait);
      this.isPortrait = isPortrait;
      this.multiStack.isPortrait = isPortrait;
      this.multiStack.handleRefreshPlaceHolderIfNeeded();
    });
    DeviceListenerManager.getInstance().registerDrawableWidthLister((isLarge: boolean) => {
      hilog.debug(0x0000, 'MultiNavigation', 'MultiNavigation Drawable width change ' + isLarge);
      this.multiStack.isLarge = isLarge;
      this.multiStack.handleRefreshPlaceHolderIfNeeded();
    });
    try {
      this.multiStack.needRenderDisplayMode.displayMode = display.getFoldStatus();
    } catch (err) {
      hilog.warn(0x0000, 'MultiNavigation', 'Failed to get fold status. error:' + JSON.stringify(err));
    }
    DeviceListenerManager.getInstance().initListener();
    this.multiStack.registerHomeChangeListener({
      onHomeShowOnTop: (name) => {
        this.onHomeShowOnTop?.(name);
      },
    })
  }

  aboutToDisappear(): void {
    try {
      display.off('foldStatusChange');
    } catch (exception) {
      console.error('Failed to unregister callback. Code: ' + JSON.stringify(exception));
    }
    DeviceListenerManager.getInstance().unregisterOrientationLister();
    DeviceListenerManager.getInstance().unregisterDrawableWidthLister();
    DeviceListenerManager.getInstance().finalizeListener();
    this.multiStack.unregisterHomeChangeListener();
  }

  build() {
    Navigation(this.multiStack.outerStack) {
    }
    .mode(NavigationMode.Stack)
    .navDestination(this.MultiNavDestination)
    .hideBackButton(true)
    .hideTitleBar(true)
    .hideToolBar(true)
    .hideNavBar(true)
  }
}

@Observed
export class MultiNavPathStack extends NavPathStack {
  outerStack: MyNavPathStack = new MyNavPathStack();
  totalStack: MultiNavPolicyInfo[] = [];
  subStackList: Array<SubNavigationStack> = new Array<SubNavigationStack>();
  needRenderLeftClickCount: NeedRenderLeftClickCount = new NeedRenderLeftClickCount();
  needRenderDisplayMode: NeedRenderDisplayMode = new NeedRenderDisplayMode();
  disableAllAnimation: boolean = false;
  private mPolicyMap = new Map<string, SplitPolicy>();
  navWidthRangeModifier: NavWidthRangeAttrModifier = new NavWidthRangeAttrModifier();
  homeWidthPercents: number[] = [50, 50];
  keepBottomPageFlag = false;
  homeChangeListener: HomeChangeListener | undefined = undefined;
  placeHolderPolicyInfo: MultiNavPolicyInfo | undefined = undefined;
  isPortrait: boolean = false;
  isLarge: boolean = false;

  navPathStackOperate:MultiNavPathStackOperate = {
    onPrimaryPop:() => {
      hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack onPrimaryPop');
      this.totalStack.pop();
      this.subStackList.pop();
      this.outerStack.popInner(false);
    },
    onSecondaryPop:() => {
      hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack onSecondaryPop');
      this.totalStack.pop();
      this.checkAndNotifyHomeChange();
    }
  };

  outerStackOperate: NavPathStackOperate = {
    onSystemPop:() => {
      hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack onOuterPop');
      this.totalStack.pop();
      this.subStackList.pop();
      this.checkAndNotifyHomeChange();
    }
  };

  constructor() {
    super();
    this.outerStack.registerStackOperateCallback(this.outerStackOperate);
  }

  pushPath(info: NavPathInfo, animated?: boolean, policy?: SplitPolicy): void;
  pushPath(info: NavPathInfo, options?: NavigationOptions, policy?: SplitPolicy): void;
  pushPath(info: NavPathInfo, optionParam?: boolean | NavigationOptions, policy?: SplitPolicy): void {
    hilog.info(0x0000, 'MultiNavigation', 'pushPath policy = ' + policy + ', info.name = ' + info.name);
    let animated: boolean = true;
    if (optionParam !== undefined) {
      if (typeof optionParam === 'boolean') {
        animated = optionParam;
      } else if (optionParam.animated !== undefined) {
        animated = optionParam.animated;
      } else {

      }
    }
    policy = (policy === undefined) ? SplitPolicy.DETAIL_PAGE : policy;
    const subStackLength = this.subStackList.length;
    const multiPolicyStack = new MultiNavPolicyInfo(policy, info);
    hilog.info(0x0000, 'MultiNavigation', 'pushPath subStackLength = ' + subStackLength);
    if (subStackLength > 0) {
      hilog.info(0x0000, 'MultiNavigation', 'pushPath currentTopPrimaryPolicy = ' +
      this.subStackList[subStackLength - 1].getPrimaryPolicy());
    }
    if (policy === SplitPolicy.DETAIL_PAGE && subStackLength > 0 &&
      this.subStackList[subStackLength - 1].getPrimaryPolicy() === SplitPolicy.HOME_PAGE) {
      let detailSize = this.subStackList[subStackLength - 1].getSecondaryInfoList().length;
      hilog.info(0x0000, 'MultiNavigation', 'pushPath detailSize = ' + detailSize );
      if (detailSize === 0) {
        this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
      } else {
        if (this.needRenderLeftClickCount.leftClickCount > 0) {
          // click on home, so we need to clear detail
          if (this.placeHolderPolicyInfo === undefined) {
            this.subStackList[subStackLength - 1].clearSecondary(false);
            this.totalStack.splice(this.totalStack.length - detailSize);
            this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
          } else {
            const firstSecondaryPolicy = this.subStackList[subStackLength - 1].getSecondaryInfoList()[0].policy;
            if (firstSecondaryPolicy === SplitPolicy.PlACE_HOLDER_PAGE) {
              if (detailSize === 1 ) {
                // detail has only place holder, so just push
                this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
              } else {
                this.subStackList[subStackLength - 1].clearSecondaryKeepPlaceHolder(false);
                this.totalStack.splice(this.totalStack.length - detailSize + 1);
                this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
              }
            } else {
              this.subStackList[subStackLength - 1].clearSecondary(false);
              this.totalStack.splice(this.totalStack.length - detailSize);
              this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
            }
          }
        } else {
          // click on detail, so just push
          this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
        }
      }
    } else {
      let subStack = new SubNavigationStack();
      subStack.registerMultiStackOperateCallback(this.navPathStackOperate);
      subStack.disableAnimation(this.disableAllAnimation);
      subStack.pushPrimaryPath(multiPolicyStack, false);
      this.subStackList.push(subStack);
      this.outerStack.pushPath({ name: 'SubNavigation', param: subStack }, animated);
    }

    this.totalStack.push(multiPolicyStack);
    if (policy === SplitPolicy.HOME_PAGE && this.placeHolderPolicyInfo !== undefined &&
    this.needShowPlaceHolder()) {
      this.pushPlaceHolder(subStackLength);
    }
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pushPath policy = ' + policy +
      ' stackSize = ' + this.totalStack.length +
      ' this.leftClickCount = ' + this.needRenderLeftClickCount.leftClickCount);
    this.needRenderLeftClickCount.leftClickCount = 0;
  }

  pushPathByName(name: string, param: Object, animated?: boolean, policy?: SplitPolicy): void;
  pushPathByName(name: string, param: Object, onPop?: base.Callback<PopInfo>, animated?: boolean,
    policy?: SplitPolicy): void;
  pushPathByName(name: string, param: Object, onPop?: base.Callback<PopInfo> | boolean,
    animated?: boolean | SplitPolicy, policy?: SplitPolicy): void {
    if (onPop !== undefined && typeof onPop !== 'boolean') {
      this.pushPath({ name: name, param: param, onPop: onPop as base.Callback<PopInfo> }, animated as boolean, policy);
      return;
    }
    if (typeof onPop === 'boolean') {
      this.pushPath({ name: name, param: param }, onPop as boolean, animated as SplitPolicy);
      return;
    }
    // here onpop is undefined
    if (animated !== undefined && typeof animated !== 'boolean') {
      this.pushPath({ name: name, param: param}, undefined, animated as SplitPolicy);
      return;
    }
    if (typeof animated === 'boolean') {
      this.pushPath({ name: name, param: param}, animated as boolean, policy);
      return;
    }
    this.pushPath({ name: name, param: param}, undefined, policy);
  }

  pushDestination(info: NavPathInfo, animated?: boolean, policy?: SplitPolicy): Promise<void>;
  pushDestination(info: NavPathInfo, options?: NavigationOptions, policy?: SplitPolicy): Promise<void>;
  pushDestination(info: NavPathInfo, animated?: boolean | NavigationOptions, policy?: SplitPolicy): Promise<void> {
    hilog.error(0x0000, 'MultiNavigation', 'pushDestination is not support');
    let promise: Promise<void> = Promise.reject({message: 'not support'});
    return promise;
  }

  pushDestinationByName(name: string, param: Object, animated?: boolean, policy?: SplitPolicy): Promise<void>;
  pushDestinationByName(name: string, param: Object, onPop: base.Callback<PopInfo>, animated?: boolean,
    policy?: SplitPolicy): Promise<void>;
  pushDestinationByName(name: string, param: Object, onPop?: boolean | base.Callback<PopInfo>,
    animated?: boolean | SplitPolicy, policy?: SplitPolicy): Promise<void> {
    hilog.error(0x0000, 'MultiNavigation', 'pushDestinationByName is not support');
    let promise: Promise<void> = Promise.reject({message: 'not support'});
    return promise;
  }

  replacePath(info: NavPathInfo, animated?: boolean): void;
  replacePath(info: NavPathInfo, options?: NavigationOptions): void;
  replacePath(info: NavPathInfo, optionParam?: boolean | NavigationOptions): void {
    let animated: boolean = true;
    if (optionParam !== undefined) {
      if (typeof optionParam === 'boolean') {
        animated = optionParam;
      } else if (optionParam.animated !== undefined) {
        animated = optionParam.animated;
      } else {

      }
    }

    let totalSize = this.totalStack.length;
    let subStackSize = this.subStackList.length;
    if (totalSize < 1 || subStackSize < 1) {
      hilog.error(0x0000, 'MultiNavigation', 'replacePath fail stack is empty');
      return;
    }
    let currentTopPolicy = this.totalStack[totalSize - 1].policy;
    if (currentTopPolicy === SplitPolicy.PlACE_HOLDER_PAGE) {
      hilog.warn(0x0000, 'MultiNavigation', 'replacePath fail, not support replace placeHolder');
      return;
    }
    const newPolicyInfo = new MultiNavPolicyInfo(currentTopPolicy, info);
    this.subStackList[subStackSize - 1].replacePath(newPolicyInfo, animated);
    this.totalStack.pop();
    this.totalStack.push(newPolicyInfo);
  }

  replacePathByName(name: string, param: Object, animated?: boolean): void {
    this.replacePath({ name: name, param: param }, animated);
  }

  removeByIndexes(indexes: number[]): number {
    let indexesLength = indexes.length;
    hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes indexesLength=' + indexesLength);
    if (indexesLength <= 0) {
      return 0;
    }
    let oriStackSize = this.totalStack.length;
    hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes oriStackSize=' + oriStackSize);
    indexes.sort((a, b) => a - b);
    let i: number = 0;
    let currentStackInfoLength: number = 0;
    let outerIndexes: number[] = [];
    hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes this.subStackList.length=' + this.subStackList.length +
      ', oriStackSize=' + oriStackSize);
    this.subStackList.forEach((subStack, subStackIndex) => {
      let stepStartIndex = currentStackInfoLength;
      currentStackInfoLength += subStack.getAllInfoLength();
      const subIndexes: number[] = [];
      for (; i < indexes.length; ) {
        if (indexes[i] < currentStackInfoLength) {
          subIndexes.push(indexes[i] - stepStartIndex);
          i++;
        } else {
          break;
        }
      }
      subStack.removeByIndexes(subIndexes);
      if (!subStack.hasPrimaryInfo()) {
        outerIndexes.push(subStackIndex);
      }
    });
    hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes outerIndexes.length=' + outerIndexes.length);
    this.outerStack.removeByIndexes(outerIndexes);
    this.subStackList = this.subStackList.filter((subStack) => {
      return subStack.hasPrimaryInfo()
    });

    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    })
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    let size = oriStackSize - this.totalStack.length;
    hilog.info(0x0000, 'MultiNavigation', 'removeByIndexes size=' + size);
    return size;
  }

  removeByName(name: string): number {
    let oriStackSize = this.totalStack.length;
    hilog.info(0x0000, 'MultiNavigation', 'removeByName name=' + name + ', oriStackSize=' + oriStackSize);
    let outerIndexes: number[] = [];
    this.subStackList.forEach((subStack, index) => {
      subStack.removeByName(name);
      if (!subStack.hasPrimaryInfo()) {
        outerIndexes.push(index);
      }
    });
    this.outerStack.removeByIndexes(outerIndexes);
    hilog.info(0x0000, 'MultiNavigation', 'removeByName outerIndexes.length=' + outerIndexes.length);
    this.subStackList = this.subStackList.filter((subStack) => {
      return subStack.hasPrimaryInfo()
    });

    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    })
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    let size = oriStackSize - this.totalStack.length;
    hilog.info(0x0000, 'MultiNavigation', 'removeByName size=' + size);
    return size;
  }


  pop(animated?: boolean): NavPathInfo | undefined;
  pop(result?: Object, animated?: boolean): NavPathInfo | undefined;
  pop(result?: Object | boolean, animated?: boolean): NavPathInfo | undefined {
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      hilog.error(0x0000, 'MultiNavigation', 'MultiNavPathStack pop fail stack is empty!');
      return undefined;
    }
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop totalSize=' + totalSize +
      ', subStackLength' + subStackLength);

    if (this.keepBottomPageFlag && (totalSize === 1 ||
      (this.placeHolderPolicyInfo !== undefined && totalSize === 2 &&
        this.totalStack[1].policy === SplitPolicy.PlACE_HOLDER_PAGE))) {
      hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop fail for keep bottom');
      return undefined;
    }
    let currentPath = this.totalStack[totalSize - 1].navInfo;
    let allInfoLength = this.subStackList[subStackLength - 1].getAllInfoLength();
    if (allInfoLength < 1) {
      hilog.error(0x0000, 'MultiNavigation', 'MultiNavPathStack pop fail sub stack is empty');
      return undefined;
    }
    let secondaryStackFirstPolice: SplitPolicy | undefined = undefined;
    if (allInfoLength > 1) {
      secondaryStackFirstPolice = this.subStackList[subStackLength - 1].getSecondaryInfoList()[0].policy;
    }
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop allInfoLength=' + allInfoLength +
      ', secondaryStackFirstPolice' + secondaryStackFirstPolice);
    this.totalStack.pop();
    if (allInfoLength === 1) {
      // pop home
      this.outerStack.popInner(animated);
      let subStack = this.subStackList.pop();
      setTimeout(() => {
        subStack?.pop(false);
        subStack = undefined;
      }, 300);
    } else {
      if (allInfoLength === 2) {
        if (this.placeHolderPolicyInfo !== undefined) {
          if (secondaryStackFirstPolice === SplitPolicy.PlACE_HOLDER_PAGE) {
            this.outerStack.popInner(animated);
            let subStack = this.subStackList.pop();
            setTimeout(() => {
              subStack?.clear(false);
              subStack = undefined;
            }, 300);
            currentPath = this.totalStack.pop()?.navInfo;
          } else {
            if (this.needShowPlaceHolder()) {
              this.subStackList[subStackLength - 1].pop(animated);
              this.pushPlaceHolder(subStackLength - 1)
            } else {
              this.subStackList[subStackLength - 1].pop(animated);
            }
          }
        } else {
          this.subStackList[subStackLength - 1].pop(animated);
        }
      } else {
        this.subStackList[subStackLength - 1].pop(animated);
      }
    }
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop currentPath.name = ' + currentPath?.name);

    if (result !== undefined && typeof result !== 'boolean' &&
      currentPath !== undefined && currentPath.onPop !== undefined) {
      let popInfo: PopInfo = {
        info: currentPath,
        result: result,
      };
      currentPath.onPop(popInfo);
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack pop stackSize = ' + this.totalStack.length);
    return currentPath;
  }

  popToName(name: string, animated?: boolean): number;
  popToName(name: string, result: Object, animated?: boolean): number;
  popToName(name: string, result?: Object | boolean, animated?: boolean): number {
    let index = this.totalStack.findIndex((value: MultiNavPolicyInfo) => {
      return value.navInfo?.name === name;
    })
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      hilog.error(0x0000, 'MultiNavigation', 'popToName fail stack is empty!');
      return -1;
    }
    if (index !== -1) {
      let currentPath = this.totalStack[totalSize - 1].navInfo;
      let secondaryStackSize: number[] = [];
      this.subStackList.forEach((subStack, index) => {
        secondaryStackSize.push(this.subStackList[index].secondaryStack.size());
      });
      let removeIndex = 0;
      for (let i = 0; i < subStackLength; i++) {
        removeIndex++;
        if (index === removeIndex - 1) {
          this.subStackList[i]?.secondaryStack.clear();
          this.subStackList[i].secondaryStack.policyInfoList.splice(0);
          this.totalStack.splice(index + 1);
          this.clearTrashStack(i + 1, result, animated);
          break;
        } else if (index > removeIndex - 1 && index < removeIndex + secondaryStackSize[i]) {
          this.subStackList[i].secondaryStack.popToIndex(index - removeIndex);
          this.subStackList[i].secondaryStack.policyInfoList.splice(index - removeIndex + 1);
          this.totalStack.splice(index + 1);
          this.clearTrashStack(i + 1, result, animated);
        }
        removeIndex += secondaryStackSize[i];
      }
      if (result !== undefined && typeof result !== 'boolean' &&
        currentPath !== undefined && currentPath.onPop !== undefined) {
        let popInfo: PopInfo = {
          info: currentPath,
          result: result,
        };
        currentPath.onPop(popInfo);
      }
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    return index;
  }

  popToIndex(index: number, animated?: boolean): void;
  popToIndex(index: number, result: Object, animated?: boolean): void;
  popToIndex(index: number, result?: Object | boolean, animated?: boolean): void {
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex index = ' + index);
    if (index > this.totalStack.length || index < 0) {
      hilog.error(0x0000, 'MultiNavigation', 'popToIndex fail wrong index');
      return;
    }
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      hilog.error(0x0000, 'MultiNavigation', 'popToIndex fail stack is empty!');
      return;
    }
    let currentPath = this.totalStack[totalSize - 1].navInfo;
    let secondaryStackSize: number[] = [];
    this.subStackList.forEach((subStack, index) => {
      secondaryStackSize.push(this.subStackList[index].secondaryStack.size());
    });
    let removeIndex = 0;
    for (let i = 0; i < subStackLength; i++) {
      removeIndex++;
      if (index === removeIndex - 1) {
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex home' + i);
        this.subStackList[i]?.secondaryStack.clear();
        this.subStackList[i].secondaryStack.policyInfoList.splice(0);
        this.totalStack.splice(index + 1);
        this.clearTrashStack(i + 1, result, animated);
        hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex totalStack=' + this.totalStack.length);
        break;
      } else if (index > removeIndex - 1 && index < removeIndex + secondaryStackSize[i]) {
        this.subStackList[i].secondaryStack.popToIndex(index - removeIndex);
        this.subStackList[i].secondaryStack.policyInfoList.splice(index - removeIndex + 1);
        this.totalStack.splice(index + 1);
        this.clearTrashStack(i + 1, result, animated);
      }
      removeIndex += secondaryStackSize[i];
    }

    if (result !== undefined && typeof result !== 'boolean' &&
      currentPath !== undefined && currentPath.onPop !== undefined) {
      let popInfo: PopInfo = {
        info: currentPath,
        result: result,
      };
      currentPath.onPop(popInfo);
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
  }

  private clearTrashStack(index: number, result?: Object | boolean, animated?: boolean): void {
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex clearTrashStack' + index);
    for (let i = index; i < this.subStackList.length; i++) {
      hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex subStackList' + index);
      this.subStackList[i].primaryStack.clear();
      this.subStackList[i].secondaryStack.clear();
      this.subStackList[i].primaryStack.policyInfoList.splice(0);
      this.subStackList[i].secondaryStack.policyInfoList.splice(0);
    }
    this.subStackList.splice(index);
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex subStackList.length=' + this.subStackList.length);
    this.outerStack.popToIndex(index - 1, result, animated);
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack popToIndex outerStack.size=' + this.outerStack.size());
  }

  moveToTop(name: string, animated?: boolean): number {
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack moveToTop name=' + name);
    let index = this.totalStack.findIndex((value) => {
      return value.navInfo?.name === name;
    });
    if (index !== -1) {
      this.moveIndexToTop(index, animated);
    }

    return index;
  }

  moveIndexToTop(index: number, animated?: boolean): void {
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack moveIndexToTop index=' + index);
    if (index < 0 || index > this.totalStack.length) {
      hilog.error(0x0000, 'MultiNavigation', 'MultiNavPathStack moveIndexToTop wrong index');
      return;
    }
    let subStackLength = this.subStackList.length;
    let currentStackInfoLength: number = 0;
    let outerIndex: number = -1;
    for (let subIndex = 0; subIndex < subStackLength; subIndex++) {
      let stepStartIndex = currentStackInfoLength;
      currentStackInfoLength += this.subStackList[subIndex].getAllInfoLength();
      if (index < currentStackInfoLength) {
        outerIndex = subIndex;
        if (this.subStackList[subIndex].getPrimaryPolicy() === SplitPolicy.HOME_PAGE) {
          let innerIndex = index - stepStartIndex;
          if (innerIndex !== 0) {
            this.subStackList[subIndex].secondaryStack.moveIndexToTop(innerIndex - 1, animated);
            const subInfo = this.subStackList[subIndex].secondaryStack.policyInfoList.splice(innerIndex - 1, 1);
            this.subStackList[subIndex].secondaryStack.policyInfoList.push(...subInfo);
          }
        }
        break;
      }
    }
    if (outerIndex !== -1) {
      let subStack = this.subStackList.splice(outerIndex, 1);
      this.subStackList.push(...subStack);
      this.outerStack.moveIndexToTop(outerIndex, animated);
    }

    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    });
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
  }

  clear(animated?: boolean): void {
    hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack clear animated = ' + animated + ', keepBottomPage=' +
    this.keepBottomPageFlag);

    if (this.subStackList.length === 0 || this.totalStack.length === 0) {
      hilog.info(0x0000, 'MultiNavigation', 'MultiNavPathStack clear return size is 0');
      return;
    }
    if (this.keepBottomPageFlag) {
      let subStackLength = this.subStackList.length;
      for (let i = 1; i < subStackLength; i++) {
        this.subStackList[i].clear(animated);
      }
      this.outerStack.popToIndex(0, animated);
      this.subStackList.splice(1);
      if (this.placeHolderPolicyInfo !== undefined) {
        if (this.subStackList[0].getSecondaryInfoList().length > 1 &&
          this.subStackList[0].secondaryStack.policyInfoList[0].policy === SplitPolicy.PlACE_HOLDER_PAGE) {
          this.subStackList[0].clearSecondaryKeepPlaceHolder(animated);
          this.totalStack.splice(2);
        } else {
          this.subStackList[0].clearSecondary(animated);
          this.totalStack.splice(1);
          if (this.needShowPlaceHolder()) {
            this.subStackList[0].pushSecondaryPath(this.placeHolderPolicyInfo, animated);
            this.totalStack.push(this.placeHolderPolicyInfo);
          }
        }
      } else {
        this.subStackList[0].clearSecondary(animated);
        this.totalStack.splice(1);
      }

      this.checkAndNotifyHomeChange();
      return;
    }
    this.subStackList.forEach((subStack) => {
      subStack.clear(animated);
    })
    this.outerStack.clear(animated);
    this.subStackList.splice(0);
    this.totalStack.splice(0)
  }

  getAllPathName(): string[] {
    let result: string[] = [];
    this.totalStack.forEach((value) => {
      if (value.navInfo !== undefined) {
        result.push(value.navInfo.name);
      }
    })
    return result;
  }

  getParamByIndex(index: number): Object | undefined {
    let result: Object | undefined = undefined;
    if (index >= 0 && index < this.totalStack.length) {
      result = this.totalStack[index].navInfo?.param as Object;
    }
    return result;
  }

  getParamByName(name: string): Object[] {
    let result: Object[] = [];
    this.totalStack.forEach((value) => {
      if (value.navInfo !== undefined && value.navInfo.name == name) {
        result.push(value.navInfo.param as Object);
      }
    })
    return result;
  }

  getIndexByName(name: string): number[] {
    let result: number[] = [];
    for (let i = 0; i < this.totalStack.length; i++) {
      if (this.totalStack[i].navInfo?.name === name) {
        result.push(i);
      }
    }
    return result;
  }

  getParent(): NavPathStack {
    hilog.error(0x0000, 'MultiNavigation', 'getParent is not support!');
    throw new Error('getParent is not support in multi navigation');
  }

  size(): number {
    return this.totalStack.length;
  }

  disableAnimation(value: boolean): void {
    for (const subStack of this.subStackList) {
      subStack.disableAnimation(value);
    }
    this.outerStack.disableAnimation(value);
    this.disableAllAnimation = value;
  }

  setInterception(interception: NavigationInterception): void {
    hilog.error(0x0000, 'MultiNavigation', 'setInterception is not support!');
    throw new Error('setInterception is not support in multi navigation');
  }

  setPagePolicy(policyMap: Map<string, SplitPolicy>): void {
    this.mPolicyMap = policyMap;
  }

  switchFullScreenState(isFullScreen?: boolean): boolean {
    let totalStackSize = this.totalStack.length;
    let subStackListLength = this.subStackList.length;
    if (subStackListLength < 1 || totalStackSize < 1) {
      return false;
    }
    if (this.subStackList[subStackListLength - 1].getPrimaryPolicy() !== SplitPolicy.HOME_PAGE) {
      return false;
    }
    if (this.totalStack[totalStackSize - 1].policy === SplitPolicy.PlACE_HOLDER_PAGE) {
      return false;
    }
    if (this.totalStack[totalStackSize - 1].isFullScreen === isFullScreen) {
      hilog.info(0x0000, 'MultiNavigation', 'switchFullScreen is same:' + isFullScreen);
      return true;
    }
    hilog.info(0x0000, 'MultiNavigation', 'switchFullScreen name=' +
      this.totalStack[totalStackSize - 1].navInfo?.name +
      ', from ' + this.totalStack[totalStackSize - 1].isFullScreen + ' to ' + isFullScreen);
    this.totalStack[totalStackSize - 1].isFullScreen = isFullScreen;
    this.subStackList[subStackListLength - 1].refreshFullScreen();
    return true;
  }

  setHomeWidthRange(minPercent: number, maxPercent: number): void {
    if (!this.checkInputPercent(minPercent) || !this.checkInputPercent(maxPercent)) {
      hilog.error(0x0000, 'MultiNavigation', 'setHomeWidthRange failed, wrong param:' +
        ', ' + minPercent + ', ' + maxPercent)
      return;
    }
    this.homeWidthPercents = [minPercent, maxPercent];
    this.refreshHomeWidth();
  }

  keepBottomPage(keepBottom: boolean): void {
    this.keepBottomPageFlag = keepBottom;
  }

  registerHomeChangeListener(lister: HomeChangeListener): void {
    if (this.homeChangeListener === undefined) {
      this.homeChangeListener = lister;
    }
  }

  unregisterHomeChangeListener(): void {
    this.homeChangeListener = undefined;
  }

  setPlaceholderPage(info: NavPathInfo): void {
    this.placeHolderPolicyInfo = new MultiNavPolicyInfo(SplitPolicy.PlACE_HOLDER_PAGE, info);
  }

  handleRefreshPlaceHolderIfNeeded() {
    if (this.placeHolderPolicyInfo === undefined) {
      return;
    }
    const subStackListLength = this.subStackList.length;
    if (subStackListLength < 1) {
      return;
    }
    const topStackPrimaryPolicy = this.subStackList[subStackListLength - 1].getPrimaryPolicy();
    if (topStackPrimaryPolicy !== SplitPolicy.HOME_PAGE) {
      return;
    }
    const subStackAllInfoLength = this.subStackList[subStackListLength - 1].getAllInfoLength();
    let secondaryStackFirstPolice: SplitPolicy | undefined = undefined;
    if (subStackAllInfoLength > 1) {
      secondaryStackFirstPolice = this.subStackList[subStackListLength - 1].getSecondaryInfoList()[0].policy;
    }
    if (this.needShowPlaceHolder()) {
      if (subStackAllInfoLength === 1) {
        this.pushPlaceHolder(subStackListLength - 1);
      }
    } else {
      if (secondaryStackFirstPolice === SplitPolicy.PlACE_HOLDER_PAGE) {
        if (subStackAllInfoLength === 2) {
          this.popPlaceHolder(subStackListLength - 1);
        } else {
          this.removeFirstPlaceHolder(subStackListLength - 1);
        }
      }
    }
  }

  private removeFirstPlaceHolder(subIndex: number): void {
    this.subStackList[subIndex].removeByIndexes([1]);
    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    })
  }

  private pushPlaceHolder(subIndex: number): void {
    this.subStackList[subIndex].pushSecondaryPath(this.placeHolderPolicyInfo!, false);
    this.totalStack.push(this.placeHolderPolicyInfo!);
  }

  private popPlaceHolder(subIndex: number): void {
    this.subStackList[subIndex].pop(false);
    this.totalStack.pop();
    this.checkAndNotifyHomeChange();
  }

  private needShowPlaceHolder(): boolean {
    if (!this.isLarge) {
      hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for drawable width is less then breakpoint');
      return false;
    }
    if (DeviceHelper.isStraightProduct()) {
      hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for straight product');
      return false;
    }
    if (DeviceHelper.isPhone() && DeviceHelper.isFold() &&
      this.needRenderDisplayMode.displayMode === display.FoldStatus.FOLD_STATUS_FOLDED) {
      hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for fold status');
      return false;
    }
    if (DeviceHelper.isTablet() && this.isPortrait) {
      hilog.info(0x0000, 'MultiNavigation', 'do not show placeHolder for portrait tablet');
      return false;
    }
    return true;
  }

  private checkAndNotifyHomeChange(): void {
    if (this.totalStack.length === 0) {
      return;
    }
    let topPolicyInfo = this.totalStack[this.totalStack.length - 1];
    if (topPolicyInfo === undefined) {
      return;
    }
    if (topPolicyInfo.policy === SplitPolicy.HOME_PAGE && topPolicyInfo.navInfo !== undefined) {
      this.homeChangeListener && this.homeChangeListener.onHomeShowOnTop(topPolicyInfo.navInfo.name);
    }
    if (this.totalStack.length <= 1) {
      return;
    }
    let secondPolicyInfo = this.totalStack[this.totalStack.length - 2];
    if (secondPolicyInfo === undefined) {
      return;
    }
    if (topPolicyInfo.policy === SplitPolicy.PlACE_HOLDER_PAGE &&
      secondPolicyInfo.policy === SplitPolicy.HOME_PAGE && secondPolicyInfo.navInfo !== undefined) {
      this.homeChangeListener && this.homeChangeListener.onHomeShowOnTop(secondPolicyInfo.navInfo.name);
    }
  }

  private refreshHomeWidth(): void {
    this.navWidthRangeModifier.minHomeWidth = `${this.homeWidthPercents[0]}%`;
    this.navWidthRangeModifier.maxHomeWidth = `${this.homeWidthPercents[1]}%`;
    this.navWidthRangeModifier.isApplicationSet = true;
  }

  private checkInputPercent(inputPercent: number): boolean {
    return (0 <= inputPercent && inputPercent <= 100);
  }
}

interface HomeChangeListener {
  onHomeShowOnTop: OnHomeShowOnTopCallback;
}

@Observed
export class NeedRenderIsFullScreen {
  isFullScreen: boolean | undefined = undefined;
}

@Observed
export class NeedRenderLeftClickCount {
  leftClickCount: number = 0;
}

@Observed
export class NeedRenderDisplayMode {
  displayMode: number = 0;
}

class MultiNavPolicyInfo {
  policy: SplitPolicy = SplitPolicy.DETAIL_PAGE;
  navInfo: NavPathInfo | undefined = undefined;
  isFullScreen: boolean | undefined = undefined;

  constructor(policy: SplitPolicy, navInfo: NavPathInfo) {
    this.policy = policy;
    this.navInfo = navInfo;
  }
}


export class MyNavPathStack extends NavPathStack {
  operates:NavPathStackOperate[] = [];
  type = 'NavPathStack';
  policyInfoList: MultiNavPolicyInfo[] = [];

  registerStackOperateCallback(operate: NavPathStackOperate) {
    let index = this.operates.findIndex((item) => { return item === operate});
    if (index === -1) {
      this.operates.push(operate);
    }
  }

  unregisterStackOperateCallback(operate: NavPathStackOperate) {
    let index = this.operates.findIndex((item) => { return item === operate});
    if (index !== -1) {
      this.operates.splice(index, 1);
    }
  }

  popInner(result?: Object | boolean, animated?: boolean): NavPathInfo | undefined {
    hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack pop from inner:');
    return super.pop(result, animated);
  }


  pop(animated?: boolean): NavPathInfo | undefined
  pop(result?: Object, animated?: boolean): NavPathInfo | undefined
  pop(result?: Object | boolean, animated?: boolean): NavPathInfo | undefined {
    hilog.info(0x0000, 'MultiNavigation', 'MyNavPathStack pop from system:');
    let ret: NavPathInfo | undefined = undefined;
    if (typeof animated === 'boolean') {
      ret = super.pop(animated);
    } else {
      ret = super.pop(result, animated);
    }
    this.policyInfoList.pop();
    this.operates.forEach((item) => {
      item.onSystemPop?.();
    })
    return ret;
  }
}

interface NavPathStackOperate {
  onSystemPop: Function;
}

interface MultiNavPathStackOperate {
  onPrimaryPop: Function;
  onSecondaryPop: Function;
}


class SubNavigationStack {
  primaryStack: MyNavPathStack = new MyNavPathStack();
  secondaryStack: MyNavPathStack = new MyNavPathStack();
  needRenderIsFullScreen: NeedRenderIsFullScreen = new NeedRenderIsFullScreen();
  multiOperates:MultiNavPathStackOperate[] = [];

  primaryNavPathStackOperate:NavPathStackOperate = {
    onSystemPop:() => {
      this.multiOperates.forEach((item) => {
        item.onPrimaryPop?.();
      })
    }
  }

  secondaryNavPathStackOperate:NavPathStackOperate = {
    onSystemPop:() => {
      this.multiOperates.forEach((item) => {
        item.onSecondaryPop?.();
      })
      this.refreshFullScreen();
    }
  }

  constructor() {
    this.primaryStack.registerStackOperateCallback(this.primaryNavPathStackOperate);
    this.secondaryStack.registerStackOperateCallback(this.secondaryNavPathStackOperate);
  }

  registerMultiStackOperateCallback(operate: MultiNavPathStackOperate) {
    let index = this.multiOperates.findIndex((item) => { return item === operate});
    if (index === -1) {
      this.multiOperates.push(operate);
    }
  }

  unregisterMultiStackOperateCallback(operate: MultiNavPathStackOperate) {
    let index = this.multiOperates.findIndex((item) => { return item === operate});
    if (index !== -1) {
      this.multiOperates.splice(index, 1);
    }
  }

  getPrimaryPolicy(): SplitPolicy | undefined {
    if (this.primaryStack.policyInfoList.length < 1) {
      return undefined;
    }
    return this.primaryStack.policyInfoList[0].policy;
  }

  getPrimaryInfoList(): MultiNavPolicyInfo[] {
    return this.primaryStack.policyInfoList.slice();
  }

  getSecondaryInfoList(): MultiNavPolicyInfo[] {
    return this.secondaryStack.policyInfoList.slice();
  }

  getAllInfoLength(): number {
    return this.primaryStack.size() + this.secondaryStack.size();
  }

  hasPrimaryInfo(): boolean {
    return this.primaryStack.size() !== 0;
  }

  hasSecondaryInfo(): boolean {
    return this.secondaryStack.size() !== 0;
  }

  pushPrimaryPath(policyStack: MultiNavPolicyInfo, animated?: boolean) {
    this.primaryStack.policyInfoList.push(policyStack);
    this.primaryStack.pushPath(policyStack.navInfo, animated);
    this.refreshFullScreen();
  }

  pushSecondaryPath(policyStack: MultiNavPolicyInfo, animated?: boolean) {
    this.secondaryStack.policyInfoList.push(policyStack);
    this.secondaryStack.pushPath(policyStack.navInfo, animated);
    this.refreshFullScreen();
  }

  removeByIndexes(indexes: number[]): void {
    if (indexes.length < 1) {
      return;
    }
    if (indexes[0] === 0) {
      hilog.info(0x0000, 'MultiNavigation', 'SubNavigationStack removeByIndexes primaryStack');
      this.primaryStack.removeByIndexes([0]);
      this.primaryStack.policyInfoList.pop();
      this.clear(false);
      return;
    }
    if (indexes.length !== 0) {
      let slaveIndexes: number[] = [];
      indexes.forEach((value: number) => {
        slaveIndexes.push(value - 1);
      });
      this.secondaryStack.removeByIndexes(slaveIndexes);
      this.secondaryStack.policyInfoList = this.secondaryStack.policyInfoList.filter((value, index) => {
        return value && !slaveIndexes.includes(index);
      })
    }
    this.refreshFullScreen();
  }

  removeByName(name: string): void {
    this.primaryStack.removeByName(name);
    this.primaryStack.policyInfoList = this.primaryStack.policyInfoList.filter((value) => {
      return value.navInfo?.name !== name
    });
    if (!this.hasPrimaryInfo()) {
      this.clear(false);
      return;
    }
    this.secondaryStack.removeByName(name);
    this.secondaryStack.policyInfoList = this.secondaryStack.policyInfoList.filter((value) => {
      return value.navInfo?.name !== name
    });
    this.refreshFullScreen();
  }

  pop(result?: Object | boolean, animated?: boolean): NavPathInfo | undefined {
    let ret: NavPathInfo | undefined = undefined
    if (this.secondaryStack.policyInfoList.length > 0) {
      ret = this.popSecondary(result, animated);
    } else {
      ret = this.popPrimary(result, animated);
    }
    this.refreshFullScreen();
    return ret;
  }

  clearSecondary(animated?: boolean) {
    this.secondaryStack.clear(animated);
    this.secondaryStack.policyInfoList.splice(0);
    this.refreshFullScreen();
  }

  clearSecondaryKeepPlaceHolder(animated?: boolean) {
    this.secondaryStack.popToIndex(0, animated);
    this.secondaryStack.policyInfoList.splice(1);
    this.refreshFullScreen();
  }

  clear(animated?: boolean) {
    this.secondaryStack.clear(animated);
    this.primaryStack.clear(animated);
    this.secondaryStack.policyInfoList.splice(0);
    this.primaryStack.policyInfoList.splice(0);
  }

  disableAnimation(value: boolean): void {
    this.primaryStack.disableAnimation(value);
    this.secondaryStack.disableAnimation(value);
  }

  replacePath(info: MultiNavPolicyInfo, animated?: boolean): void {
    if (this.secondaryStack.policyInfoList.length > 0) {
      this.replaceSecond(info, animated);
    } else {
      this.replacePrimary(info, animated);
    }
    this.refreshFullScreen();
  }

  refreshFullScreen() {
    let secondInfoListLength = this.secondaryStack.policyInfoList.length
    if (secondInfoListLength > 0) {
      this.needRenderIsFullScreen.isFullScreen =
        this.secondaryStack.policyInfoList[secondInfoListLength - 1].isFullScreen;
      return;
    }
    let primaryInfoListLength = this.primaryStack.policyInfoList.length
    if (primaryInfoListLength > 0) {
      this.needRenderIsFullScreen.isFullScreen =
        this.primaryStack.policyInfoList[primaryInfoListLength - 1].isFullScreen;
    }
  }

  private replacePrimary(info: MultiNavPolicyInfo, animated?: boolean): void {
    this.primaryStack.policyInfoList.pop();
    this.primaryStack.policyInfoList.push(info)
    return this.primaryStack.replacePath(info.navInfo, animated);
  }

  private replaceSecond(info: MultiNavPolicyInfo, animated?: boolean): void {
    this.secondaryStack.policyInfoList.pop();
    this.secondaryStack.policyInfoList.push(info)
    return this.secondaryStack.replacePath(info.navInfo, animated);
  }

  private popPrimary(result?: Object | boolean, animated?: boolean): NavPathInfo | undefined {
    this.primaryStack.policyInfoList.pop();
    return this.primaryStack.popInner(result, animated);
  }

  private popSecondary(result?: Object | boolean, animated?: boolean): NavPathInfo | undefined {
    this.secondaryStack.policyInfoList.pop();
    return this.secondaryStack.popInner(result, animated);
  }
}

declare type NavDestinationBuildFunction = (name: string, param?: object) => void;

declare type OnNavigationModeChangeCallback = (mode: NavigationMode) => void;

declare type OnHomeShowOnTopCallback = (name: string) => void;