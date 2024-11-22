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

/**
 * ConfigureStateMgmt keeps track if V2 @ObservedV2 and @Trace are used. 
 * If yes, it enables object deep observation mechanisms need with @ObservedV2.
 */
class ConfigureStateMgmt {

    private static readonly HOW_TO_SAY = `Your application uses both state management V1 and V2 features! - It is strongly recommended not to mix V1 and V2. Consult the rules how state management V1 and V2 can be mixed in the same app.`;

    private static instance__?: ConfigureStateMgmt;

    private v2ObservedTrackInUse_: boolean = false;
    private puObservedTrackInUse_: boolean = false;

    public static get instance(): ConfigureStateMgmt {
        return ConfigureStateMgmt.instance__
            ? ConfigureStateMgmt.instance__
            : (ConfigureStateMgmt.instance__ = new ConfigureStateMgmt());
    }

    /**
     * framework code call this function when it sees use of a stateMgmt V2 @ObservedV2 @Trace
     * 
     * @param feature specify feature separately from context of use, so that in future decision can be made 
     *                for individual features, not use permit either use of V1 or V2.
     * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
     * @returns true if no mix of features detected, false if mix is detected
     */
    public usingV2ObservedTrack(feature: string, contextOfUse: string = ''): void {
        this.v2ObservedTrackInUse_ = true;
        stateMgmtConsole.debug(`ConfigureStateMgmt: Found use of stateMgmt V2 feature ${feature} ${contextOfUse} - enable V2 state observation.`);
    }

    /**
 * framework code call this function when it sees use of a stateMgmt PU Observed / @Track
 * 
 * @param feature specify feature separately from context of use, so that in future decision can be made 
 *                for individual features, not use permit either use of V1 or V2.
 * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
 * @returns true if no mix of features detected, false if mix is detected
 */
    public usingPUObservedTrack(feature: string, contextOfUse: string = ''): void {
        this.puObservedTrackInUse_ = true;
        stateMgmtConsole.debug(`ConfigureStateMgmt: Found use of stateMgmt PU feature ${feature} ${contextOfUse} - enable PU state observation.`);
    }

    /**
      * Return true if object deep observation mechanisms need to be enabled 
      * that is when seen V2 @ObservedV2, @Trace, or @Monitor decorator used in at least one class
      * (we could but we do not check for class object instance creation for performance reasons)
      * @returns 
      */
    public needsV2Observe(): boolean {
        return this.v2ObservedTrackInUse_;
    }
} // ConfigureStateMgmt