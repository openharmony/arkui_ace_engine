/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { TypeChecker, ArkUIGeneratedNativeModule } from '#components';
import { Finalizable, KPointer, MaterializedBase } from '@koalaui/interop';
import { unsafeCast, int32, int64, float32 } from '@koalaui/common';

export class WaterFlowSectionsInternal {
    public static fromPtr(ptr: KPointer): WaterFlowSections {
        return new WaterFlowSections(ptr)
    }
}

export interface SectionChangeInfo {
    start: int32;
    deleteCount: int32;
    sections?: Array<SectionOptions>;
}

export class WaterFlowSections implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined;
    public sectionArray: Array<SectionOptions> = [];
    public changeArray: Array<SectionChangeInfo> = [];

    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WaterFlowSections.getFinalizer())
    }
    constructor() {
        this(WaterFlowSections.construct())
    }

    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WaterFlowSections_construct();
        return retval;
    }

    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WaterFlowSections_getFinalizer();
    }

    static isNonNegativeInt32(input: int32): boolean {
        return Number.isSafeInteger(input) && input >= 0 && input <= 2147483647;
    }

    static toArrayIndex(origin: int32, limit: int32): int32 {
        let result: int32 = Math.trunc(origin) as int32;
        if (result < 0) {
            // Negative index counts from the end of the sectionArray
            result += limit;
            // If origin < -sectionArray.length, use 0
            if (result < 0) {
                result = 0;
            }
        } else if (result > limit) {
            result = limit;
        }
        return result;
    }

    public splice(start: int32, deleteCount?: int32, sections?: Array<SectionOptions>): boolean {
        const oldLength: int32 = this.sectionArray.length;

        // Handle parameters
        if (deleteCount === undefined && sections === undefined) {
            this.sectionArray.splice(start);
        } else if (deleteCount != undefined && sections === undefined) {
            this.sectionArray.splice(start, deleteCount);
        } else {
            // Validate itemsCount in sections
            if (sections) {
                for (const section of sections) {
                    if (!WaterFlowSections.isNonNegativeInt32(section.itemsCount)) {
                        return false;
                    }
                }
            }
            if (sections) {
                this.sectionArray.splice(start, deleteCount ?? 0, ...sections)
            } else {
                this.sectionArray.splice(start, deleteCount ?? 0);
            }
        }

        const intStart: int32 = WaterFlowSections.toArrayIndex(start, oldLength);
        let intDeleteCount: int32 = 0;

        if (deleteCount === undefined && sections === undefined) {
            intDeleteCount = oldLength - intStart;
        } else if (deleteCount !== undefined) {
            intDeleteCount = Math.trunc(deleteCount) as int32;
            if (intDeleteCount > oldLength - intStart) {
                intDeleteCount = oldLength - intStart;
            }
        }

        intDeleteCount = intDeleteCount < 0 ? 0 : intDeleteCount;

        // Record the change
        this.changeArray.push({
            start: intStart,
            deleteCount: intDeleteCount,
            sections: sections,
        });

        return true;
    }

    public push(section: SectionOptions): boolean {
        if (!WaterFlowSections.isNonNegativeInt32(section.itemsCount)) {
            return false;
        }
        const oldLength: int32 = this.sectionArray.length;
        this.sectionArray.push(section);
        this.changeArray.push({ start: oldLength, deleteCount: 0, sections: [section] });
        return true;
    }

    public update(sectionIndex: int32, section: SectionOptions): boolean {
        if (!WaterFlowSections.isNonNegativeInt32(section.itemsCount)) {
            return false;
        }
        const oldLength: int32 = this.sectionArray.length;
        this.sectionArray.splice(sectionIndex, 1, section);
        const intStart: int32 = WaterFlowSections.toArrayIndex(sectionIndex, oldLength);
        this.changeArray.push({ start: intStart, deleteCount: 1, sections: [section] });
        return true;
    }

    public values(): Array<SectionOptions> {
        return this.sectionArray;
    }

    public length(): int32 {
        return this.sectionArray.length;
    }
}