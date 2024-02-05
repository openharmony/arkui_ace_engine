/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

class ConfigureStateMgmt {
    
    private static readonly HOW_TO_SAY = `Older state management features such as @State, @Link, @ObjectLink, @Observed, or @Track,
    can not be used on the same ArkUI page as state management v3 features such as @observe, @track, @state, or @param
    Please correct your application to use either!";`;

    private v2InUse_ : boolean = false;
    private v3InUse_ : boolean = false;
    private static instance__? : ConfigureStateMgmt;

    public static get instance() : ConfigureStateMgmt {
        return ConfigureStateMgmt.instance__
            ? ConfigureStateMgmt.instance__ 
            : (ConfigureStateMgmt.instance__ = new ConfigureStateMgmt());
    }

    /**
     * framework code call this function when it sees use of a stateMgmt V3 feature
     * 
     * @param feature specify feature separately from context of use, so that in future decision can be made 
     *                for individual features, not use permit either use of V2 or V3.
     * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
     * @returns true if use is permitted
     * @throws Error exception if use is not permitted.
     */
    public intentUsingV3(feature : string, contextOfUse : string = "") : boolean {
        this.v3InUse_ = true;
        const ret= !this.v2InUse_ && this.v3InUse_;
        if (!ret) {
            stateMgmtConsole.featureCombinationError(`Found ${feature} ${contextOfUse} - ${ConfigureStateMgmt.HOW_TO_SAY}`);
        }
        stateMgmtConsole.debug(`ConfigureStateMgmt: Found use of ${feature} ${contextOfUse} - configure to use stateMgmt v3`);
        return ret;
    }

    /**
     * framework code call this function when it sees use of a stateMgmt V2 feature
     * 
     * @param feature specify feature separately from context of use, so that in future decision can be made 
     *                for individual features, not use permit either use of V2 or V3.
     * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
     * @returns true if use is permitted
     * @throws Error exception if use is not permitted.
     */
    public intentUsingV2(feature : string, contextOfUse : string = "") : boolean {
        this.v2InUse_ = true;
        const ret= this.v2InUse_ && !this.v3InUse_;
        if (!ret) {
            stateMgmtConsole.featureCombinationError(`Found ${feature} ${contextOfUse} - ${ConfigureStateMgmt.HOW_TO_SAY}`);
        }
        stateMgmtConsole.debug(`ConfigureStateMgmt: Found use of ${feature} ${contextOfUse} - configure to use stateMgmt v2`);
        return ret;
    }

    /**
     * Return true if object deep observation mechanisms need to be enabled 
     * that is when seen V3 @observe, @track, or @monitor decorator used in at least one class
     * (we could but we do not check for class object instance creation for performance reasons)
     * @returns 
     */
    public needsV3Observe() : boolean {
        return this.v3InUse_;
    }
} // ConfigureStateMgmt