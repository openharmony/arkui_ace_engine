/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"

export class WaterFlowSectionsInternal {
    public static fromPtr(ptr: KPointer): WaterFlowSections {
        const obj: WaterFlowSections = new WaterFlowSections()
        obj.peer = new Finalizable(ptr, WaterFlowSections.getFinalizer())
        return obj
    }
}
export interface SectionChangeInfo {
    start: number;
    deleteCount: number;
    sections?: Array<SectionOptions>;
}

export class WaterFlowSections implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public sectionArray: Array<SectionOptions> = new Array<SectionOptions>();
    public changeArray: Array<SectionChangeInfo> = new Array<SectionChangeInfo>();

    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_waterflowsections(): KPointer {
        const retval = ArkUIGeneratedNativeModule._WaterFlowSections_ctor()
        return retval
    }
    constructor() {
        const ctorPtr: KPointer = WaterFlowSections.ctor_waterflowsections()
        this.peer = new Finalizable(ctorPtr, WaterFlowSections.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WaterFlowSections_getFinalizer()
    }

    static isNonNegativeInt32(input: number) {
        return Number.isSafeInteger(input) && input >= 0 && input <= 2147483647;
    }

    static toArrayIndex(origin: number, limit: number) {
        // origin is truncated to an integer
        let result = Math.trunc(origin);
        if (result < 0) {
            // Negative index counts back from the end of the sectionArray.
            result += limit;
            // If origin < -sectionArray.length, 0 is used.
            if (result < 0) {
                result = 0;
            }
        } else if (result > limit) {
            result = limit;
        }
        return result;
    }
    public splice(start: number, deleteCount?: number, sections?: Array<SectionOptions>): boolean {
        const oldLength: number = this.sectionArray.length;
        // const paramCount = arguments.length;

        // 处理参数
        if (deleteCount === undefined && sections === undefined) {
            this.sectionArray.splice(start);
        } else if (deleteCount != undefined && sections === undefined) {
            this.sectionArray.splice(start, deleteCount);
        } else {
            // 检查 sections 中的 itemsCount 是否合法
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

        // 计算实际操作的 start 和 deleteCount
        const intStart: number = WaterFlowSections.toArrayIndex(start, oldLength);
        let intDeleteCount: number = 0;

        if (deleteCount === undefined && sections === undefined) {
            intDeleteCount = oldLength - intStart;
        }
        else if(deleteCount !== undefined) {
            intDeleteCount = Math.trunc(deleteCount);
            if (intDeleteCount > oldLength - intStart) {
                intDeleteCount = oldLength - intStart;
            }
        }

        intDeleteCount = intDeleteCount < 0 ? 0 : intDeleteCount;
        //记录变更
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
        let oldLength: number = this.sectionArray.length;
        this.sectionArray.push(section);
        this.changeArray.push({ start: oldLength, deleteCount: 0, sections: [section] });
        return true;
    }
    public update(sectionIndex: number, section: SectionOptions): boolean {
        if (!WaterFlowSections.isNonNegativeInt32(section.itemsCount)) {
            return false;
        }
        let oldLength: number = this.sectionArray.length;
        this.sectionArray.splice(sectionIndex, 1, section);
        let intStart: number = WaterFlowSections.toArrayIndex(sectionIndex, oldLength);
        this.changeArray.push({ start: intStart, deleteCount: 1, sections: [section] });
        return true;
    }
    public values(): Array<SectionOptions> {
        return this.sectionArray;
    }
    public length(): number {
        return this.sectionArray.length;
    }
}