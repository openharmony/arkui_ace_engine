/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

interface ObservedResult {
  /**
   * Whether the object data of class/Array/Map/Set/Date type is observable.
   * if true, the object data can be observed.
   * if false, the object data can not be not observed.
   */
  isObserved: boolean;

  /**
   * Reasons why the object data of class/Array/Map/Set/Date type can not be not observed.
   * 1 The object data is not an observable object.
   * 2 The object data is observed data for the following reasons:
   * 2.1 The object data is decorated with @Observed or wrapped by makeV1Observed.
   * 2.2 The object data is decorated with V2 @ObservedV2 and @Trace.
   * 2.3 The object data is wrapped by V2's makeObserved.
   * 2.4 The object data is built-in type proxy data (Array/Map/Set/Date) decorated with @Trace.
   * 2.5 The V1 Observed object data is wrapped by enableV2Compatibility and used in @ComponentV2.
   * 2.6 The object data is decorated with @Observed or wrapped by makeV1Observed, but not used in UI.
   * 2.7 The object data is decorated with V2 @ObservedV2 and @Trace, but not used in UI.
   * 2.8 The object data is wrapped by V2's makeObserved, but not used in UI.
   * 2.9 The object data is built-in type proxy data (Array/Map/Set/Date) decorated with @Trace, but not used in UI.
   * 2.10 The V1 Observed object data is wrapped by enableV2Compatibility, but not used in @ComponentV2.
   */
  reason: string;

  /**
   * The UI component information associated with the object data.
   * If the data object can not be observed, will return empty array.
   */
  decoratorInfo: Array<DecoratorInfo>;
}

/**
 * The UI component information associated with the object data.
 */
interface DecoratorInfo {
  /**
   * Decorator name of the object data.
   */
  decoratorName: string;

  /**
   * State Variable name of the object data.
   */
  stateVariableName: string;

  /**
   * The custom component name that the object data belongs to.
   * In the V1 scenario, return the custom component name, in the V2 @ObservedV2 scenario, return class name.
   */
  owningComponentOrClassName: string;

  /**
   * The custom component id that the object data belongs to.
   * In the V1 scenario, return the custom component id， in the V2 @ObservedV2 scenario, return -1.
   */
  owningComponentId: number;

  /**
   * Dependent component information including custom component and UI component (Text, Image)
   * for the object data.
   * For the V2 @Monitor or @Computed scenario, will return the id and decorated function name by @Monitor or @Computed.
   * For V2 scenario, if it is not used in the UI, nor on @Monitor or @Computed, return an empty array.
   * For V1 scenario, if it is not used in the UI, will return an empty array.
   */
  dependentInfo: Array<ElementInfo>;
}

/**
 * The custom component and UI component information.
 * For the V2 @Monitor or @Computed scenario, The id and decorated function name by @Monitor
 * or @Computed will be returned.
 */
interface ElementInfo {
  /**
   * Dependent custom component and UI component name.
   * For the V2 @Monitor or @Computed scenario, elementName refers to the name of the decorator and
   * the function name decorated with @Monitor or @Computed (eg: @Monitor onChange).
   */
  elementName: string;

  /**
   * Dependent custom component and UI component id.
   * For the V2 @Monitor or @Computed scenario, elementId refers to the id of
   * the @Monitor or @Computed.
   */
  elementId: number;
}

enum ObservedReason {
  V2_UI = 'The object data is decorated with V2 @ObservedV2 and @Trace',
  V2_NO_UI = 'The object data is decorated with V2 @ObservedV2 and @Trace, but not used in UI',
  V2_MAKE_UI = 'The object data is wrapped by V2\'s makeObserved',
  V2_MAKE_NO_UI = 'The object data is wrapped by V2\'s makeObserved, but not used in UI',
  V2_PROXY_UI = 'The object data is built-in type proxy data (Array/Map/Set/Date) decorated with @Trace',
  V2_PROXY_NO_UI = 'The object data is built-in type proxy data (Array/Map/Set/Date) decorated with @Trace, ' +
    'but not used in UI',
  V1_UI = 'The object data is decorated with @Observed or wrapped by makeV1Observed',
  V1_NO_UI = 'The object data is decorated with @Observed or wrapped by makeV1Observed, but not used in UI',
  V1_TO_V2_UI = 'The V1 Observed object data is wrapped by enableV2Compatibility and used in @ComponentV2',
  V1_TO_V2_NO_UI = 'The V1 Observed object data is wrapped by enableV2Compatibility, but not used in @ComponentV2',
  NOT_OBSERVED = 'The object data is not an observable object'
}

class ObservedUtil {
  public static canBeObserved<T extends Object>(source: T): ObservedResult {
    const ret: ObservedResult = {
      isObserved: true,
      reason: '',
      decoratorInfo: []
    };
    if (ObserveV2.IsObservedObjectV2(source)) {
      const decoMeta = source[ObserveV2.V2_DECO_META];
      const symbolRefs = source[ObserveV2.SYMBOL_REFS];
      ret.decoratorInfo = this.getV2Result(source, symbolRefs, '', decoMeta);
      const flag = this.hasDependentElement(ret.decoratorInfo);
      ret.reason = flag ? ObservedReason.V2_UI : ObservedReason.V2_NO_UI;
    } else if (ObserveV2.IsMakeObserved(source)) {
      const target = this.getV2MakeObservedTarget(source);
      const symbolRefs = target ? target[ObserveV2.SYMBOL_REFS] : undefined;
      ret.decoratorInfo = this.getV2Result(source, symbolRefs, 'MakeObserved');
      const flag = this.hasDependentElement(ret.decoratorInfo);
      ret.reason = flag ? ObservedReason.V2_MAKE_UI: ObservedReason.V2_MAKE_NO_UI;
    } else if (ObserveV2.IsProxiedObservedV2(source)) {
      const target = UIUtilsImpl.instance().getTarget(source);
      const symbolRefs = target ? target[ObserveV2.SYMBOL_REFS] : undefined;
      ret.decoratorInfo = this.getV2Result(source, symbolRefs, 'ProxyObservedV2');
      const flag = this.hasDependentElement(ret.decoratorInfo);
      ret.reason = flag ? ObservedReason.V2_PROXY_UI : ObservedReason.V2_PROXY_NO_UI;
    } else if (ObservedObject.IsObservedObject(source)) {
      ret.decoratorInfo = this.getV1Result<Object>(source);
      const flag = this.hasDependentElement(ret.decoratorInfo);
      ret.reason = flag ? ObservedReason.V1_UI : ObservedReason.V1_NO_UI;
      if (source[SubscribableHandler.ENABLE_V2_COMPATIBLE]) {
        const compatible = this.getEnableV2Compatible(source);
        const flag = this.hasDependentElement(compatible);
        ret.reason = flag ? ObservedReason.V1_TO_V2_UI : ObservedReason.V1_TO_V2_NO_UI;
        ret.decoratorInfo.push(...compatible);
      }
    } else {
      ret.isObserved = false;
      ret.reason = ObservedReason.NOT_OBSERVED;
    }
    return ret;
  }

  private static getEnableV2Compatible(source: any): Array<DecoratorInfo> {
    const decoratorInfos: Array<DecoratorInfo> = [];
    const target = UIUtilsImpl.instance().getTarget(source);
    if (!Utils.isNull(target)) {
      const symRefs = target[ObserveV2.SYMBOL_REFS];
      Object.getOwnPropertyNames(symRefs).forEach((name: string) => {
        const owningName = target.constructor.name;
        const eleIdSet = symRefs[name];
        if (!Utils.isNull(eleIdSet) && eleIdSet.size > 0) {
          const decoratorInfo: DecoratorInfo = {
            decoratorName: 'EnableV2Compatible',
            stateVariableName: name,
            owningComponentOrClassName: owningName,
            owningComponentId: -1, // For V2 decorators, component id is not collected, default is -1
            dependentInfo: stateMgmtDFX.dumpDepenetElementV2(eleIdSet, true) as Array<ElementInfo>
          };
          decoratorInfos.push(decoratorInfo);
        }
      });
    }
    return decoratorInfos;
  }

  private static hasDependentElement(decorators: Array<DecoratorInfo>): boolean {
    if (decorators.length === 0) {
      return false;
    }
    for (const deco of decorators) {
      if (deco.dependentInfo.length !== 0) {
        return true;
      }
    }
    return false;
  }

  /**
   * @param source original data source
   * @param symbolRefs dependent info get from the SymbolRefs
   * @param decoratorName if makeObserved decoratorName is 'MakeObserved',
   *  if proxyObservedV2 decoratorName is 'ProxyObservedV2',
   *  else decoratorName get from source,
   * @param decoMeta is ObsrevedV2 get from the ObservedV2 class, if is exist,
   *  the decorator name will get from the decoMeta
   * @returns DecoratorInfo array
   */
  private static getV2Result(source: object, symbolRefs: object, decoratorName: string,
    decoMeta?: object): Array<DecoratorInfo> {
    const decoratorInfos: Array<DecoratorInfo> = [];
    if (Utils.isNull(source) || Utils.isNull(symbolRefs)) {
      return decoratorInfos;
    }
    // if ObservedV2 use decoMeta for property not used in ui, else use symbolRefs
    Object.getOwnPropertyNames(decoMeta ?? symbolRefs).forEach((name: string) => {
      const decorator: DecoratorInfo = {
        decoratorName: decoratorName === '' ?
          ObserveV2.getObserve().getDecoratorInfo(source, name) : decoratorName,
        stateVariableName: name,
        owningComponentOrClassName: decoMeta ? source.constructor.name :
          UIUtilsImpl.instance().getTarget(source).constructor.name,
        owningComponentId: -1, // For V2 decorators, component id is not collected, default is -1
        dependentInfo: []
      };
      const eleIdSet = symbolRefs[name];
      if (!Utils.isNull(eleIdSet) && eleIdSet.size > 0) {
        decorator.dependentInfo = stateMgmtDFX.dumpDepenetElementV2(eleIdSet, true) as Array<ElementInfo>;
      }
      decoratorInfos.push(decorator);
    });
    return decoratorInfos;
  }

  private static getV2MakeObservedTarget(source: Object): any { 
    let origin;
    let target;
    if ((origin = UIUtilsImpl.instance().getTarget(source)) &&  (target = RefInfo.obj2ref.get(origin))) {
      return target;
    }
    return undefined;
  }

  private static getV1Result<T extends Object>(source: T): Array<DecoratorInfo> {
    let decoratorInfos: Array<DecoratorInfo> = [];
    const observedSource = source as ObservedObject<Object>;
    if (Utils.isNull(observedSource)) {
      return decoratorInfos;
    }
    const properties = observedSource[SubscribableHandler.OWNING_PROPERTIES];
    if (Utils.isNull(properties) || properties.size === 0) {
      return decoratorInfos;
    }
    properties.forEach((id: number) => {
      const proSubs = SubscriberManager.Find(id);
      if (!Utils.isNull(proSubs)) {
        if (!TrackedObject.isCompatibilityMode(source)) {
          let className = '';
          // first get prototype for source proxy
          const sourceProto = Object.getPrototypeOf(source);
          if (!Utils.isNull(sourceProto)) {
            // second get prototype for source target
            const sourceTarget = Object.getPrototypeOf(sourceProto);
            className = sourceTarget ? sourceProto.constructor.name : '';
          }
          decoratorInfos = this.getV1TrackDecorator(proSubs, decoratorInfos, className);
        } else {
          const decoratorInfo = this.getV1DecoratorInfo(proSubs);
          if (decoratorInfo) {
            decoratorInfos.push(...decoratorInfo);
          }
        }
      }
    });
    return decoratorInfos;
  }

  private static getV1TrackDecorator(proSubs: any, decorators: Array<DecoratorInfo>,
    className: string): Array<DecoratorInfo> {
    const decos: Array<DecoratorInfo> = decorators;
    const elmntMap = (proSubs as ObservedPropertyAbstractPU<Object>).getPropertyElementInfo();
    elmntMap?.forEach((value, name) => {
      if (!name.includes('OPTI_TRACKED_ASSIGNMENT_FAKE_OBJLINK_PROPERTY')) {
        const index = decorators.findIndex((item) => item.stateVariableName === name);
        if (index !== -1) {
          decos[index].dependentInfo.push(... value);
        } else {
          const dec = {
            decoratorName: '@Track',
            stateVariableName: name,
            owningComponentOrClassName: className,
            owningComponentId: -1,
            dependentInfo: value
          };
          decos.push(dec);
        }
      }
    });
    return decos;
  }

  private static getV1DecoratorInfo(proSubs: any): Array<DecoratorInfo> {
    const decoratorInfos: Array<DecoratorInfo> = [];
    const decoratorInfo = this.parseV1Decorator(proSubs);
    if (decoratorInfo) {
      decoratorInfos.push(decoratorInfo);
    }
    const puProSubs = proSubs as ObservedPropertyAbstractPU<Object>;
    const subsRefs = puProSubs.getSubscriberRefs();
    if (!Utils.isNull(subsRefs) && subsRefs.size > 0) {
      subsRefs.forEach((subRef: any) => {
        decoratorInfos.push(... this.getV1DecoratorInfo(subRef));
      });
    }
    return decoratorInfos;
  }

  private static parseV1Decorator(proSubs: any): DecoratorInfo | undefined {
    const decoratorInfo: DecoratorInfo = {
      decoratorName: '',
      stateVariableName: '',
      owningComponentOrClassName: '',
      owningComponentId: -1,
      dependentInfo: []
    };
    const puProSubs = proSubs as ObservedPropertyAbstractPU<Object>;
    const stateVariableName = puProSubs.info();
    if (stateVariableName && stateVariableName.includes('prop_fake_state_source')) {
      return undefined;
    }
    decoratorInfo.stateVariableName = stateVariableName;
    decoratorInfo.decoratorName = puProSubs.debugInfoDecorator();
    const owningView = puProSubs.getOwningView() as TargetInfo;
    decoratorInfo.owningComponentOrClassName = owningView?.componentName ?? '';
    decoratorInfo.owningComponentId = owningView?.id;
    const elementProperty = puProSubs.getDependencies();
    if (!Utils.isNull(elementProperty) && elementProperty?.size !== 0) {
      const dependentInfo: Array<ElementInfo> = [];
      elementProperty?.forEach((elmtId: number) => {
        dependentInfo.push(puProSubs.getElementById(elmtId));
      });
      decoratorInfo.dependentInfo = dependentInfo;
    }
    return decoratorInfo;
  }
}