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

class BasicPrefetcher {
    constructor(ds) {
        this.prefetcher = new Prefetcher(new PrefetchRangeEvaluator(), new DefaultTimeProvider());
        if (ds) {
            this.prefetcher.setDataSource(ds);
        }
    }
    setDataSource(ds) {
        this.prefetcher.setDataSource(ds);
    }
    visibleAreaChanged(minVisible, maxVisible) {
        this.prefetcher.visibleAreaChanged(minVisible, maxVisible);
    }
}
class FetchedRegistry {
    constructor() {
        this.fetchedIndicies = new Set();
        this.rangeToPrefetch = new IndexRange(0, 0);
    }
    addFetched(index) {
        this.fetchedIndicies.add(index);
    }
    getFetchedInRange(range) {
        let fetched = 0;
        range.forEachIndex((index) => {
            fetched += this.fetchedIndicies.has(index) ? 1 : 0;
        });
        return fetched;
    }
    updateRangeToPrefetch(prefetchRange) {
        this.rangeToPrefetch.subtract(prefetchRange).forEachIndex((index) => {
            this.fetchedIndicies.delete(index);
        });
        this.rangeToPrefetch = prefetchRange;
    }
}
class ItemsOnScreenProvider {
    constructor() {
        this.firstScreen = true;
        this.meanImagesOnScreen = 0;
        this.minVisible = 0;
        this.maxVisible = 0;
        this._direction = 'UNKNOWN';
        this._visibleRange = new IndexRange(0, 0);
        this.callbacks = [];
    }
    register(callback) {
        this.callbacks.push(callback);
    }
    get visibleRange() {
        return this._visibleRange;
    }
    get meanValue() {
        return this.meanImagesOnScreen;
    }
    get direction() {
        return this._direction;
    }
    update(minVisible, maxVisible) {
        if (minVisible == this.minVisible && maxVisible == this.maxVisible) {
        }
        else if (Math.max(minVisible, this.minVisible) == minVisible &&
            Math.max(maxVisible, this.maxVisible) == maxVisible) {
            this._direction = 'DOWN';
        }
        else if (Math.min(minVisible, this.minVisible) == minVisible &&
            Math.min(maxVisible, this.maxVisible) == maxVisible) {
            this._direction = 'UP';
        }
        this.minVisible = minVisible;
        this.maxVisible = maxVisible;
        let imagesOnScreen = maxVisible - minVisible + 1;
        if (this.firstScreen) {
            this.meanImagesOnScreen = imagesOnScreen;
            this.firstScreen = false;
        }
        else {
            const weight = 0.95;
            this.meanImagesOnScreen = this.meanImagesOnScreen * weight + (1 - weight) * imagesOnScreen;
            imagesOnScreen = Math.ceil(this.meanImagesOnScreen);
        }
        const visibleRangeSizeChanged = this.visibleRange.length !== imagesOnScreen;
        this._visibleRange = new IndexRange(minVisible, maxVisible + 1);
        if (visibleRangeSizeChanged) {
            this.notifyObservers();
        }
    }
    notifyObservers() {
        this.callbacks.forEach((callback) => callback());
    }
}
class PrefetchCount {
    constructor(itemsOnScreen) {
        this.MAX_SCREENS = 4;
        this.MIN_SCREENS = 0.6;
        this.min = 0;
        this.max = 0;
        this._prefetchCountValue = 0;
        this._currentLimit = 0;
        this._maxRatio = 0.5;
        this.itemsOnScreen = itemsOnScreen;
        this.itemsOnScreen.register(() => {
            this.updateLimits();
        });
    }
    get prefetchCountValue() {
        return this._prefetchCountValue;
    }
    set prefetchCountValue(v) {
        this._prefetchCountValue = v;
        Logger.log(`{"tm":${Date.now()},"prefetch_count":${v}}`);
    }
    get currentLimit() {
        return this._currentLimit;
    }
    get maxRatio() {
        return this._maxRatio;
    }
    set maxRatio(value) {
        this._maxRatio = value;
        this.updateCurrentLimit();
    }
    getPrefetchCountByRatio(ratio) {
        return this.min + Math.ceil(ratio * (this.currentLimit - this.min));
    }
    getRangeToPrefetch(totalCount) {
        const visibleRange = this.itemsOnScreen.visibleRange;
        let start = 0;
        let end = 0;
        switch (this.itemsOnScreen.direction) {
            case 'UNKNOWN':
                start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue));
                end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue));
                break;
            case 'UP':
                start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue));
                end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue * 0.5));
                break;
            case 'DOWN':
                start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue * 0.5));
                end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue));
                break;
        }
        return new IndexRange(start, end);
    }
    updateLimits() {
        this.min = Math.ceil(this.itemsOnScreen.meanValue * this.MIN_SCREENS);
        this.max = Math.max(this.min, Math.ceil(this.MAX_SCREENS * this.itemsOnScreen.meanValue));
        this.updateCurrentLimit();
    }
    updateCurrentLimit() {
        this._currentLimit = Math.max(this.min, Math.ceil(this.max * this._maxRatio));
    }
}
class PrefetchRangeEvaluator {
    constructor() {
        this.itemsOnScreen = new ItemsOnScreenProvider();
        this.prefetchCount = new PrefetchCount(this.itemsOnScreen);
        this.fetchedRegistry = new FetchedRegistry();
        this.prefetchRangeRatio = new PrefetchRangeRatio(this.itemsOnScreen, this.fetchedRegistry);
        this.totalItems = 0;
        this.rangeToPrefetch_ = new IndexRange(0, 0);
    }
    get rangeToPrefetch() {
        return this.rangeToPrefetch_;
    }
    setTotal(totalItems) {
        this.totalItems = totalItems;
    }
    visibleRangeChanged(minVisible, maxVisible) {
        this.itemsOnScreen.update(minVisible, maxVisible);
        Logger.log(`visibleAreaChanged itemsOnScreen=${Math.abs(maxVisible - minVisible) + 1}, meanImagesOnScreen=${this.itemsOnScreen.meanValue}, prefetchCountCurrentLimit=${this.prefetchCount.currentLimit}, prefetchCountMaxRatio=${this.prefetchCount.maxRatio}`);
        this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('visible-area-changed');
        this.rangeToPrefetch_ = this.prefetchCount.getRangeToPrefetch(this.totalItems);
        this.fetchedRegistry.updateRangeToPrefetch(this.rangeToPrefetch_);
    }
    itemPrefetched(index, fetchDuration) {
        let maxRatioChanged = false;
        if (this.prefetchRangeRatio.update(fetchDuration) === 'ratio-changed') {
            this.prefetchCount.maxRatio = this.prefetchRangeRatio.maxRatio;
            maxRatioChanged = true;
            Logger.log(`choosePrefetchCountLimit prefetchCountMaxRatio=${this.prefetchCount.maxRatio}, prefetchCountCurrentLimit=${this.prefetchCount.currentLimit}`);
        }
        this.fetchedRegistry.addFetched(index);
        this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('resolved', maxRatioChanged);
        this.rangeToPrefetch_ = this.prefetchCount.getRangeToPrefetch(this.totalItems);
        this.fetchedRegistry.updateRangeToPrefetch(this.rangeToPrefetch_);
    }
    evaluatePrefetchCount(event, maxRatioChanged) {
        const ratio = this.prefetchRangeRatio.calculateRatio(this.prefetchCount.prefetchCountValue, this.totalItems);
        let evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(ratio);
        let nextRatio;
        if (maxRatioChanged) {
            nextRatio = this.prefetchRangeRatio.calculateRatio(evaluatedPrefetchCount, this.totalItems);
            evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(nextRatio);
        }
        if (this.prefetchRangeRatio.range.contains(ratio) ||
            (event === 'resolved' && evaluatedPrefetchCount <= this.prefetchCount.prefetchCountValue)) {
            return this.prefetchCount.prefetchCountValue;
        }
        this.prefetchRangeRatio.updateRatioRange(ratio);
        Logger.log(`evaluatePrefetchCount prefetchCount=${evaluatedPrefetchCount}, ratio=${ratio}, nextRatio=${nextRatio}, hysteresisRange=${this.prefetchRangeRatio.range}`);
        return evaluatedPrefetchCount;
    }
}
class PrefetchRangeRatio {
    constructor(itemsOnScreen, fetchedRegistry) {
        this.TOLERANCE_RANGES = [
            {
                leftToleranceEdge: 180,
                rightToleranceEdge: 250,
                prefetchCountMaxRatioLeft: 0.5,
                prefetchCountMaxRatioRight: 1,
            },
            {
                leftToleranceEdge: 3000,
                rightToleranceEdge: 4000,
                prefetchCountMaxRatioLeft: 1,
                prefetchCountMaxRatioRight: 0.25,
            },
        ];
        this.ACTIVE_DEGREE = 0.5;
        this.VISIBLE_DEGREE = 2.5;
        this.meanPrefetchTime = 0;
        this.leftToleranceEdge = Number.MIN_VALUE;
        this.rightToleranceEdge = 250;
        this.oldRatio = 0;
        this._range = RatioRange.newEmpty();
        this._maxRatio = 0.5;
        this.itemsOnScreen = itemsOnScreen;
        this.fetchedRegistry = fetchedRegistry;
    }
    get range() {
        return this._range;
    }
    get maxRatio() {
        return this._maxRatio;
    }
    updateTiming(prefetchDuration) {
        if (prefetchDuration > 20) {
            const weight = 0.95;
            this.meanPrefetchTime = this.meanPrefetchTime * weight + (1 - weight) * prefetchDuration;
        }
        Logger.log(`prefetchDifference prefetchDur=${prefetchDuration}, meanPrefetchDur=${this.meanPrefetchTime}`);
    }
    update(prefetchDuration) {
        this.updateTiming(prefetchDuration);
        if (this.meanPrefetchTime >= this.leftToleranceEdge && this.meanPrefetchTime <= this.rightToleranceEdge) {
            return 'ratio-not-changed';
        }
        let ratioChanged = false;
        if (this.meanPrefetchTime > this.rightToleranceEdge) {
            for (let i = 0; i < this.TOLERANCE_RANGES.length; i++) {
                const limit = this.TOLERANCE_RANGES[i];
                if (this.meanPrefetchTime > limit.rightToleranceEdge) {
                    ratioChanged = true;
                    this._maxRatio = limit.prefetchCountMaxRatioRight;
                    this.leftToleranceEdge = limit.leftToleranceEdge;
                    if (i + 1 != this.TOLERANCE_RANGES.length) {
                        this.rightToleranceEdge = this.TOLERANCE_RANGES[i + 1].rightToleranceEdge;
                    }
                    else {
                        this.rightToleranceEdge = Number.MAX_VALUE;
                    }
                }
            }
        }
        else if (this.meanPrefetchTime < this.leftToleranceEdge) {
            for (let i = this.TOLERANCE_RANGES.length - 1; i >= 0; i--) {
                const limit = this.TOLERANCE_RANGES[i];
                if (this.meanPrefetchTime < limit.leftToleranceEdge) {
                    ratioChanged = true;
                    this._maxRatio = limit.prefetchCountMaxRatioLeft;
                    this.rightToleranceEdge = limit.rightToleranceEdge;
                    if (i != 0) {
                        this.leftToleranceEdge = this.TOLERANCE_RANGES[i - 1].leftToleranceEdge;
                    }
                    else {
                        this.leftToleranceEdge = Number.MIN_VALUE;
                    }
                }
            }
        }
        return ratioChanged ? 'ratio-changed' : 'ratio-not-changed';
    }
    calculateRatio(prefetchCount, totalCount) {
        const visibleRange = this.itemsOnScreen.visibleRange;
        const start = Math.max(0, visibleRange.start - prefetchCount);
        const end = Math.min(totalCount, visibleRange.end + prefetchCount);
        const evaluatedPrefetchRange = new IndexRange(start, end);
        const completedActive = this.fetchedRegistry.getFetchedInRange(evaluatedPrefetchRange);
        const completedVisible = this.fetchedRegistry.getFetchedInRange(visibleRange);
        return Math.min(1, Math.pow(completedActive / evaluatedPrefetchRange.length, this.ACTIVE_DEGREE) *
            Math.pow(completedVisible / visibleRange.length, this.VISIBLE_DEGREE));
    }
    updateRatioRange(ratio) {
        if (ratio > this.oldRatio) {
            this._range = new RatioRange(new RangeEdge(this.oldRatio, false), new RangeEdge(ratio, true));
        }
        else {
            this._range = new RatioRange(new RangeEdge(ratio, true), new RangeEdge(this.oldRatio, false));
        }
        this.oldRatio = ratio;
    }
}
class DefaultTimeProvider {
    getCurrent() {
        return Date.now();
    }
}
class Prefetcher {
    constructor(prefetchRangeEvaluator, timeProvider) {
        this.datasource = null;
        this.prefetchRangeEvaluator = prefetchRangeEvaluator;
        this.timeProvider = timeProvider;
    }
    setDataSource(ds) {
        this.datasource = ds;
        this.prefetchRangeEvaluator.setTotal(ds.totalCount());
    }
    visibleAreaChanged(minVisible, maxVisible) {
        if (!this.datasource) {
            throw new Error('No data source');
        }
        const oldRangeToPrefetch = this.prefetchRangeEvaluator.rangeToPrefetch;
        this.prefetchRangeEvaluator.visibleRangeChanged(minVisible, maxVisible);
        this.prefetchDifference(oldRangeToPrefetch);
        this.cancelDifference(oldRangeToPrefetch);
    }
    prefetchDifference(oldRange) {
        this.prefetchRangeEvaluator.rangeToPrefetch.subtract(oldRange).forEachIndex((index) => {
            const prefetchStart = this.timeProvider.getCurrent();
            const prefetchedCallback = () => {
                if (!this.prefetchRangeEvaluator.rangeToPrefetch.contains(index)) {
                    return;
                }
                const oldRangeToPrefetch = this.prefetchRangeEvaluator.rangeToPrefetch;
                const prefetchDuration = this.timeProvider.getCurrent() - prefetchStart;
                this.prefetchRangeEvaluator.itemPrefetched(index, prefetchDuration);
                this.prefetchDifference(oldRangeToPrefetch);
            };
            const prefetchResponse = this.datasource.prefetch(index);
            if (prefetchResponse instanceof Promise) {
                prefetchResponse.then(prefetchedCallback);
            }
            else {
                prefetchedCallback();
            }
        });
    }
    cancelDifference(oldRangeToPrefetch) {
        if (!this.datasource.cancel || this.prefetchRangeEvaluator.rangeToPrefetch.length > oldRangeToPrefetch.length) {
            return;
        }
        oldRangeToPrefetch.subtract(this.prefetchRangeEvaluator.rangeToPrefetch).forEachIndex((index) => {
            this.datasource.cancel(index);
        });
    }
}
class Logger {
    static log(message) { }
}
class IndexRange {
    constructor(start, end) {
        this.start = start;
        this.end = end;
        if (this.start > this.end) {
            throw new Error('Invalid range');
        }
    }
    get length() {
        return this.end - this.start;
    }
    contains(value) {
        if (typeof value === 'object') {
            return this.start <= value.start && value.end <= this.end;
        }
        else {
            return this.start <= value && value < this.end;
        }
    }
    subtract(other) {
        const result = new IndexRangeArray();
        if (other.start > this.start) {
            result.push(new IndexRange(this.start, Math.min(this.end, other.start)));
        }
        if (other.end < this.end) {
            result.push(new IndexRange(Math.max(other.end, this.start), this.end));
        }
        return result;
    }
    expandedWith(other) {
        return new IndexRange(Math.min(this.start, other.start), Math.max(this.end, other.end));
    }
    forEachIndex(callback) {
        for (let i = this.start; i < this.end; ++i) {
            callback(i);
        }
    }
    format() {
        return `[${this.start}..${this.end})`;
    }
}
class IndexRangeArray extends Array {
    forEachIndex(callback) {
        this.forEach((range) => {
            range.forEachIndex(callback);
        });
    }
}
class RangeEdge {
    constructor(value, inclusive) {
        this.value = value;
        this.inclusive = inclusive;
    }
}
class RatioRange {
    constructor(start, end) {
        this.start = start;
        this.end = end;
        if (this.start.value > this.end.value) {
            throw new Error(`RatioRange: ${this.start.value} > ${this.end.value}`);
        }
    }
    static newEmpty() {
        return new RatioRange(new RangeEdge(0, false), new RangeEdge(0, false));
    }
    contains(point) {
        if (point == this.start.value) {
            return this.start.inclusive;
        }
        if (point == this.end.value) {
            return this.end.inclusive;
        }
        return this.start.value < point && point < this.end.value;
    }
    toString() {
        return `${this.start.inclusive ? '[' : '('}${this.start.value}, ${this.end.value}${this.end.inclusive ? ']' : ')'}`;
    }
}

export default { BasicPrefetcher };
