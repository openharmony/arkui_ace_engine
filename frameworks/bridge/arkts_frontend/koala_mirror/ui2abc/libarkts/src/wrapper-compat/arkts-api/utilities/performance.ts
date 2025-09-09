/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

interface Event {
    name: string,
    startTime: number,
    endTime?: number,
    parentEvent?: string,
    duration?: number
}

function formatTime(ms: number): string {
    const milliseconds = Math.floor(ms % 1000);
    const seconds = Math.floor((ms / 1000) % 60);
    const minutes = Math.floor((ms / (1000 * 60)) % 60);
    const hours = Math.floor(ms / (1000 * 60 * 60));
  
    return `${pad(hours, 2)}:${pad(minutes, 2)}:${pad(seconds, 2)}:${pad(milliseconds, 3)}`;
}

function pad(value: number, length: number): string {
    return value.toString().padStart(length, '0');
}

function round(value: number, index: number = 2): number {
    const factor = Math.pow(10, index);
    return Math.round(value * factor) / factor;
}

export class Performance {
    private static instance: Performance;
    private events: Map<string, Event>;
    private historyEvents = new Map<string | null, Event[]>();
    private scopes: string[];
    private shouldSkip: boolean;
    private totalDuration: number;

    private constructor() {
        this.events = new Map();
        this.historyEvents = new Map();
        this.scopes = [];
        this.shouldSkip = true;
        this.totalDuration = 0;
    }

    public static getInstance(): Performance {
        if (!this.instance) {
            this.instance = new Performance();
        }
        return this.instance;
    }

    skip(shouldSkip: boolean = true): void {
        this.shouldSkip = shouldSkip;
    }

    createEvent(name: string): Event {
        if (this.shouldSkip) {
            return { name: '', startTime: 0 };
        }
        const startTime: number = performance.now();
        const newEvent: Event = { name, startTime };
        this.events.set(name, newEvent);
        this.scopes.push(name);
        return newEvent;
    }

    stopEvent(name: string, shouldLog: boolean = false): Event {
        if (this.shouldSkip) {
            return { name: '', startTime: 0 };
        }
        if (!this.events.has(name) || this.scopes.length === 0) {
            throw new Error(`Event ${name} is not created.`);
        }
        if (this.scopes[this.scopes.length - 1] !== name) {
            console.warn(`[PERFORMANCE WARNING] Event ${name} early exit.`);
        }
        this.scopes.pop();

        const event: Event = this.events.get(name)!;
        const endTime: number = performance.now();
        const parentEvent: string = this.scopes[this.scopes.length - 1];
        const duration: number = endTime - event.startTime;
        if (!parentEvent) {
            this.totalDuration += duration;
        }

        if (shouldLog) {
            console.log(
                `[PERFORMANCE] name: ${event.name}, parent: ${parentEvent}, duration: ${formatTime(duration)}(${round(duration)}), total: ${formatTime(this.totalDuration)}(${round(this.totalDuration)})`
            );
        }

        const newEvent = { ...event, endTime, parentEvent, duration };
        const history = this.historyEvents.get(parentEvent ?? null) || [];
        this.historyEvents.set(parentEvent ?? null, [...history, newEvent]);
        return newEvent;
    }

    stopLastEvent(shouldLog: boolean = false): Event {
        if (this.shouldSkip) {
            return { name: '', startTime: 0 };
        }
        if (this.scopes.length === 0) {
            throw new Error("No last event");
        }
        const name: string = this.scopes.pop()!;
        if (!this.events.has(name)) {
            throw new Error(`Event ${name} is not created.`);
        }

        const event: Event = this.events.get(name)!;
        const endTime: number = performance.now();
        const parentEvent: string = this.scopes[this.scopes.length - 1];
        const duration: number = endTime - event.startTime;
        if (!parentEvent) {
            this.totalDuration += duration;
        }

        if (shouldLog) {
            console.log(
                `[PERFORMANCE] name: ${event.name}, parent: ${parentEvent}, duration: ${formatTime(duration)}(${round(duration)}), total: ${formatTime(this.totalDuration)}(${round(this.totalDuration)})`
            );
        }

        const newEvent = { ...event, endTime, parentEvent, duration };
        const history = this.historyEvents.get(parentEvent ?? null) || [];
        this.historyEvents.set(parentEvent ?? null, [...history, newEvent]);
        return newEvent;
    }

    clearAllEvents(shouldLog: boolean = false): void {
        if (this.shouldSkip) {
            return;
        }
        for (let i = 0; i < this.scopes.length; i ++) {
            this.stopLastEvent(shouldLog);
        }
        this.events = new Map();
    }

    clearTotalDuration(): void {
        this.totalDuration = 0;
    }

    clearHistory(): void {
        this.historyEvents = new Map();
    }

    visualizeEvents(shouldLog: boolean = false): void {
        if (this.shouldSkip) {
            return;
        }
        const that = this;
        function buildVisualization(parentKey: string | null, indentLevel: number): [string, number] {
            const children = that.historyEvents.get(parentKey) || [];
            let result = '';
    
            children.forEach(child => {
                const indent = '  '.repeat(indentLevel);
                const duration = child.duration ?? 0;
                const [_result, count] = buildVisualization(child.name, indentLevel + 1);
                result += `${indent}- ${child.name}: ${formatTime(duration)}(${round(duration)}), ${count}\n`;
                result += _result;
            });
    
            return [result, children.length];
        }

        const [finalResult, _] = buildVisualization(null, 0);
        if (shouldLog) {
          console.log(`[PERFORMANCE] ===== FINAL RESULT ====`);
          console.log(`TOTAL: ${formatTime(this.totalDuration)}(${round(this.totalDuration)})`);
          console.log(finalResult.trimEnd());
          console.log(`[PERFORMANCE] ===== FINAL RESULT ====`);
        }
    }
}