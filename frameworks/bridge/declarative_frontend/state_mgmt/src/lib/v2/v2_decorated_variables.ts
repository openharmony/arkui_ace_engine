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

/**
 * 
 * This file includes only framework internal classes and functions 
 * non are part of SDK. Do not access from app.
 */

/**
 * Helper class for handling V3 decorated variables
 */
class VariableUtilV3 {
    /**
       * setReadOnlyAttr - helper function used to update @param
       * from parent @Component. Not allowed for @param @once .
       * @param target  - the object, usually the ViewV2
       * @param attrName - @param variable name
       * @param newValue - update to new value
       */
    public static initParam<Z>(target: object, attrName: string, newValue: Z): void {
      const meta = target[ObserveV2.V2_DECO_META]?.[attrName];
      if (!meta || meta.deco !== '@param') {
        const error = `Use initParam(${attrName}) only to init @param. Internal error!`;
        stateMgmtConsole.error(error);
        throw new Error(error);
      }
      // prevent update for @param @once
      const storeProp = ObserveV2.OB_PREFIX + attrName;
      stateMgmtConsole.propertyAccess(`initParam '@param ${attrName}' - setting backing store`);
      target[storeProp] = newValue;
      ObserveV2.getObserve().addRef(target, attrName);
    }
  
      /**
       * setReadOnlyAttr - helper function used to update @param
       * from parent @Component. Not allowed for @param @once .
       * @param target  - the object, usually the ViewV2
       * @param attrName - @param variable name
       * @param newValue - update to new value
       */
    public static updateParam<Z>(target: object, attrName: string, newValue: Z): void {
      // prevent update for @param @once
      const meta = target[ObserveV2.V2_DECO_META]?.[attrName];
      if (!meta || meta.deco !== '@param') {
        const error = `Use updateParm(${attrName}) only to update @param. Internal error!`;
        stateMgmtConsole.error(error);
        throw new Error(error);
      }
  
      const storeProp = ObserveV2.OB_PREFIX + attrName;
      // @observed class and @track attrName
      if (newValue === target[storeProp]) {
        stateMgmtConsole.propertyAccess(`updateParm '@param ${attrName}' unchanged. Doing nothing.`);
        return;
      }
      if (meta.deco2 === '@once') {
        // @param @once - init but no update
        stateMgmtConsole.log(`updateParm: '@param @once ${attrName}' - Skip updating.`);
      } else {
        stateMgmtConsole.propertyAccess(`updateParm '@param ${attrName}' - updating backing store and fireChange.`);
        target[storeProp] = newValue;
        ObserveV2.getObserve().fireChange(target, attrName);
      }
    }
  }
  
  class ProvideConsumeUtilV3 {
    private static readonly ALIAS_PREFIX = '___pc_alias_';
  
  
    /**
     * Helper function to add meta data about @provide and @consume decorators to ViewV2
     * similar to @see addVariableDecoMeta, but adds the alias to allow search from @consume for @provide counterpart
     * @param proto prototype object of application class derived from ViewV2
     * @param varName decorated variable
     * @param deco '@state', '@event', etc (note '@model' gets transpiled in '@param' and '@event')
     */
    public static addProvideConsumeVariableDecoMeta(proto: Object, varName: string, aliasName: string, deco: '@provide' | '@consume'): void {
      // add decorator meta data to prototype
      const meta = proto[ObserveV2.V2_DECO_META] ??= {};
      // note: aliasName is the actual alias not the prefixed version
      meta[varName] = { 'deco': deco, 'aliasName': aliasName };
  
      // prefix to avoid name collisions with variable of same name as the alias!
      const aliasProp = ProvideConsumeUtilV3.ALIAS_PREFIX + aliasName;
      meta[aliasProp] = { 'varName': varName, 'deco': deco };
  
      // FIXME 
      // when splitting ViewPU and ViewV2
      // use instanceOf. Until then, this is a workaround.
      // any @state, @track, etc V3 event handles this function to return false
      Reflect.defineProperty(proto, 'isViewV3', {
        get() { return true; },
        enumerable: false
      }
      );
    }
  
    public static setupConsumeVarsV3(view: ViewV2): boolean {
      const meta = view && view[ObserveV2.V2_DECO_META];
      if (!meta) {
        return;
      }
  
      for (const [key, value] of Object.entries(meta)) {
        if ((value as any).deco === '@consume' && (value as any).varName) {
          const prefixedAliasName = key;
          let result = ProvideConsumeUtilV3.findProvide(view, prefixedAliasName);
          if (result && result[0] && result[1]) {
            ProvideConsumeUtilV3.connectConsume2Provide(view, (value as any).varName, result[0], result[1]);
          } else {
            ProvideConsumeUtilV3.defineConsumeWithoutProvide(view, (value as any).varName);
          }
        }
      }
    }
  
    /**
    * v3: find a @provide'ed variable from its nearest ancestor ViewV2.
    * @param searchingAliasName The key name to search for.
    * @returns A tuple containing the ViewPU instance where the provider is found
    * and the provider name
    * If root @Component reached without finding, returns undefined.
    */
    private static findProvide(view: ViewV2, searchingPrefixedAliasName: string): [ViewV2, string] | undefined {
      let checkView : IView | undefined = view?.getParent();
      while (checkView) {
        const meta = checkView.constructor?.prototype[ObserveV2.V2_DECO_META];
        if (checkView instanceof ViewV2 && meta && meta[searchingPrefixedAliasName]) {
          const aliasMeta = meta[searchingPrefixedAliasName];
          const providedVarName: string | undefined = aliasMeta && (aliasMeta.deco === '@provide' ? aliasMeta.varName : undefined);
  
          if (providedVarName) {
            stateMgmtConsole.debug(`findProvide: success: ${checkView.debugInfo__()} has matching @provide('${searchingPrefixedAliasName.substring(ProvideConsumeUtilV3.ALIAS_PREFIX.length)}') ${providedVarName}`);
            return [checkView, providedVarName];
          }
        }
        checkView = checkView.getParent(); // FIXME IView
      }; // while
      stateMgmtConsole.debug(`findProvide:  ${view.debugInfo__()} @consume('${searchingPrefixedAliasName.substring(ProvideConsumeUtilV3.ALIAS_PREFIX.length)}'), no matching @provide found amongst ancestor @Components`);
      return undefined;
    }
  
    private static connectConsume2Provide(consumeView: ViewV2, consumeVarName: string, provideView: ViewV2, provideVarName: string): void {
      stateMgmtConsole.debug(`connectConsume2PRovide: Connect ${consumeView.debugInfo__()} '@consume ${consumeVarName}' to ${provideView.debugInfo__()} '@provide ${provideVarName}'`);
  
      const weakView = new WeakRef<ViewV2>(provideView);
      const provideViewName = provideView.constructor?.name;
      Reflect.defineProperty(consumeView, consumeVarName, {
        get() {
          stateMgmtConsole.propertyAccess(`@consume ${consumeVarName} get`);
          ObserveV2.getObserve().addRef(this, consumeVarName);
          const view = weakView.deref();
          if (!view) {
            const error = `${this.debugInfo__()}: get() on @consume ${consumeVarName}: providing @ComponentV2 ${provideViewName} no longer exists. Application error.`;
            stateMgmtConsole.error(error);
            throw new Error(error);
          }
          return view[provideVarName];
        },
        set(val) {
          // If the object has not been observed, you can directly assign a value to it. This improves performance.
          stateMgmtConsole.propertyAccess(`@consume ${consumeVarName} set`);
          const view = weakView.deref();
          if (!view) {
            const error = `${this.debugInfo__()}: set() on @consume ${consumeVarName}: providing @ComponentV2 ${provideViewName} no longer exists. Application error.`;
            stateMgmtConsole.error(error);
            throw new Error(error);
          }
  
          if (val !== view[provideVarName]) {
            stateMgmtConsole.propertyAccess(`@consume ${consumeVarName} valueChanged`);
            view[provideVarName] = val;
            if (this[ObserveV2.SYMBOL_REFS]) { // This condition can improve performance.
              ObserveV2.getObserve().fireChange(this, consumeVarName);
            }
          }
        },
        enumerable: true
      });
    }
  
    private static defineConsumeWithoutProvide(consumeView: ViewV2, consumeVarName: string): void {
      stateMgmtConsole.debug(`defineConsumeWithoutProvide: ${consumeView.debugInfo__()} @consume ${consumeVarName} does not have @provide counter part, uses local init value`);
  
      const storeProp = ObserveV2.OB_PREFIX + consumeVarName;
      consumeView[storeProp] = consumeView[consumeVarName]; // use local init value, also as backing store
      Reflect.defineProperty(consumeView, consumeVarName, {
        get() {
          ObserveV2.getObserve().addRef(this, consumeVarName);
          return ObserveV2.autoProxyObject(this, ObserveV2.OB_PREFIX + consumeVarName);
        },
        set(val) {
          if (val !== this[storeProp]) {
            this[storeProp] = val;
            if (this[ObserveV2.SYMBOL_REFS]) { // This condition can improve performance.
              ObserveV2.getObserve().fireChange(this, consumeVarName);
            }
          }
        },
        enumerable: true
      });
    }
  }
  
  // The prop parameter is not carried when the component is updated.
  // FIXME what is the purpose of this ?
  /*
  let updateChild = ViewPU.prototype["updateStateVarsOfChildByElmtId"];
  ViewPU.prototype["updateStateVarsOfChildByElmtId"] = function (elmtId, params) {
    updateChild?.call(this, elmtId, params);
    let child = this.getChildById(elmtId);
    if (child) {
      let realParams = child.paramsGenerator_ ? child.paramsGenerator_() : params
      for (let k in realParams) {
        if (ObserveV2.OB_PREFIX + k in child) {
          child[k] = realParams[k];
        }
      }
    }
  }
  */
  