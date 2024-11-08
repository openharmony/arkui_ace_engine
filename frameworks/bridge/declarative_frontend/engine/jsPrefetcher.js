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
        const itemsOnScreen = new ItemsOnScreenProvider();
        const fetchedRegistry = new FetchedRegistry();
        const fetchingRegistry = new FetchingRegistry();
        const prefetchRangeRatio = new PrefetchRangeRatio(itemsOnScreen, fetchedRegistry, fetchingRegistry);
        const prefetchCount = new PrefetchCount(itemsOnScreen, prefetchRangeRatio);
        const evaluator = new FetchingRangeEvaluator(itemsOnScreen, prefetchCount, prefetchRangeRatio, fetchedRegistry);
        this.fetchingDriver = new FetchingDriver(fetchedRegistry, fetchingRegistry, evaluator, new DefaultTimeProvider());
        this.fetchingDriver.setDataSource(ds);
    }
    setDataSource(ds) {
        this.fetchingDriver.setDataSource(ds);
    }
    visibleAreaChanged(minVisible, maxVisible) {
        this.fetchingDriver.visibleAreaChanged(minVisible, maxVisible);
    }
}
class DataSourceObserver {
    constructor(simpleChangeListener) {
        this.simpleChangeListener = simpleChangeListener;
    }
    onDataReloaded() {
        this.simpleChangeListener.batchUpdate([
            {
                kind: 'reloaded',
                totalCount: this.dataSource.totalCount(),
            },
        ]);
    }
    onDataAdded(index) {
        this.simpleChangeListener.batchUpdate([
            {
                kind: 'added',
                startIndex: index,
                count: 1,
            },
        ]);
    }
    onDataAdd(index) {
        this.onDataAdded(index);
    }
    onDataMoved(from, to) {
        this.simpleChangeListener.batchUpdate([
            {
                kind: 'swapped',
                a: from,
                b: to,
            },
        ]);
    }
    onDataMove(from, to) {
        this.onDataMoved(from, to);
    }
    onDataDeleted(index) {
        this.simpleChangeListener.batchUpdate([
            {
                kind: 'deleted',
                startIndex: index,
                count: 1,
            },
        ]);
    }
    onDataDelete(index) {
        this.onDataDeleted(index);
    }
    onDataChanged(index) {
        this.simpleChangeListener.batchUpdate([
            {
                kind: 'updated',
                index,
            },
        ]);
    }
    onDataChange(index) {
        this.onDataChanged(index);
    }
    onDatasetChange(dataOperations) {
        const operations = [];
        dataOperations.forEach((operation) => {
            switch (operation.type) {
                case 'add':
                case 'delete':
                    if (operation.count === undefined || operation.count > 0) {
                        operations.push({
                            kind: operation.type === 'add' ? 'added' : 'deleted',
                            startIndex: operation.index,
                            count: operation.count ?? 1,
                        });
                    }
                    break;
                case 'change':
                    operations.push({
                        kind: 'updated',
                        index: operation.index,
                    });
                    break;
                case 'reload':
                    operations.push({
                        kind: 'reloaded',
                        totalCount: this.dataSource.totalCount(),
                    });
                    break;
                case 'exchange':
                    operations.push({
                        kind: 'swapped',
                        a: operation.index.start,
                        b: operation.index.end,
                    });
                    break;
                case 'move':
                    operations.push({
                        kind: 'moved',
                        from: operation.index.from,
                        to: operation.index.to,
                    });
                    break;
                default:
                    assertNever(operation);
            }
        });
        this.simpleChangeListener.batchUpdate(operations);
    }
    setDataSource(dataSource) {
        if (this.dataSource) {
            this.dataSource.unregisterDataChangeListener(this);
        }
        this.dataSource = dataSource;
        this.dataSource.registerDataChangeListener(this);
        this.onDataReloaded();
    }
}
class FetchingRegistry {
    constructor() {
        this.fetches = new Map();
        this.fetching = new Map();
        this.fetchesBefore = new Map();
        this.fetchCounter = 0;
    }
    registerFetch(index) {
        let fetchId = this.fetching.get(index);
        if (fetchId !== undefined) {
            return fetchId;
        }
        fetchId = ++this.fetchCounter;
        this.fetching.set(index, fetchId);
        this.fetches.set(fetchId, index);
        this.fetchesBefore.set(index, this.fetches.size);
        return fetchId;
    }
    getItem(fetchId) {
        return this.fetches.get(fetchId);
    }
    deleteFetch(fetchId) {
        const index = this.fetches.get(fetchId);
        if (index !== undefined) {
            this.fetching.delete(index);
            this.fetches.delete(fetchId);
        }
    }
    deleteFetchByItem(index) {
        const fetchId = this.fetching.get(index);
        if (fetchId !== undefined) {
            this.fetching.delete(index);
            this.fetches.delete(fetchId);
        }
    }
    isFetchingItem(index) {
        return this.fetching.has(index);
    }
    incrementAllIndexesGreaterThen(value) {
        this.offsetAllIndexesGreaterThen(value, 1);
    }
    getAllIndexes() {
        const set = new Set();
        this.fetching.forEach((fetchId, itemIndex) => set.add(itemIndex));
        return set;
    }
    getFetchesCount() {
        return this.fetches.size;
    }
    isFetchLatecomer(index, threshold) {
        return this.fetchesBefore.get(index) > threshold;
    }
    offsetAllIndexesGreaterThen(value, offset) {
        const newFetching = new Map();
        this.fetches.forEach((index, fetchId) => {
            const toSet = index > value ? index + offset : index;
            newFetching.set(toSet, fetchId);
            this.fetches.set(fetchId, toSet);
        });
        this.fetching = newFetching;
    }
    decrementAllIndexesGreaterThen(value) {
        this.offsetAllIndexesGreaterThen(value, -1);
    }
}
class FetchedRegistry {
    constructor() {
        this.fetchedIndexes = new Set();
        this.rangeToFetchInternal = new IndexRange(0, 0);
        this.missedIndexes = new Set();
    }
    get rangeToFetch() {
        return this.rangeToFetchInternal;
    }
    addFetched(index) {
        if (this.rangeToFetch.contains(index)) {
            this.fetchedIndexes.add(index);
            this.missedIndexes.delete(index);
        }
    }
    removeFetched(index) {
        if (this.rangeToFetch.contains(index)) {
            this.fetchedIndexes.delete(index);
            this.missedIndexes.add(index);
        }
    }
    has(index) {
        return this.fetchedIndexes.has(index);
    }
    getFetchedInRange(range) {
        let fetched = 0;
        range.forEachIndex((index) => {
            fetched += this.fetchedIndexes.has(index) ? 1 : 0;
        });
        return fetched;
    }
    updateRangeToFetch(fetchRange) {
        this.rangeToFetch.subtract(fetchRange).forEachIndex((index) => {
            this.fetchedIndexes.delete(index);
        });
        this.rangeToFetchInternal = fetchRange;
        this.missedIndexes.clear();
        this.rangeToFetch.forEachIndex((index) => {
            if (!this.fetchedIndexes.has(index)) {
                this.missedIndexes.add(index);
            }
        });
    }
    getItemsToFetch() {
        return new Set(this.missedIndexes);
    }
    incrementFetchedGreaterThen(value, newFetchRange) {
        this.offsetAllGreaterThen(value, 1);
        this.updateRangeToFetch(newFetchRange);
    }
    decrementFetchedGreaterThen(value, newFetchRange) {
        this.offsetAllGreaterThen(value, -1);
        this.updateRangeToFetch(newFetchRange);
    }
    offsetAllGreaterThen(value, offset) {
        const updated = new Set();
        this.fetchedIndexes.forEach((index) => {
            updated.add(index > value ? index + offset : index);
        });
        this.fetchedIndexes = updated;
    }
    clearFetched(newFetchRange) {
        this.fetchedIndexes.clear();
        this.updateRangeToFetch(newFetchRange);
    }
}
class ItemsOnScreenProvider {
    constructor() {
        this.firstScreen = true;
        this.meanImagesOnScreen = 0;
        this.minVisible = 0;
        this.maxVisible = 0;
        this.directionInternal = 'UNKNOWN';
        this.speedInternal = 0;
        this.lastUpdateTimestamp = 0;
        this.visibleRangeInternal = new IndexRange(0, 0);
        this.callbacks = [];
    }
    register(callback) {
        this.callbacks.push(callback);
    }
    get visibleRange() {
        return this.visibleRangeInternal;
    }
    get meanValue() {
        return this.meanImagesOnScreen;
    }
    get direction() {
        return this.directionInternal;
    }
    get speed() {
        return this.speedInternal;
    }
    updateSpeed(minVisible, maxVisible) {
        const timeDifference = Date.now() - this.lastUpdateTimestamp;
        if (timeDifference > 0) {
            const speedTau = 100;
            const speedWeight = 1 - Math.exp(-timeDifference / speedTau);
            const distance = minVisible + (maxVisible - minVisible) / 2 - (this.minVisible + (this.maxVisible - this.minVisible) / 2);
            const rawSpeed = Math.abs(distance / timeDifference) * 1000;
            this.speedInternal = speedWeight * rawSpeed + (1 - speedWeight) * this.speedInternal;
        }
    }
    update(minVisible, maxVisible) {
        if (minVisible !== this.minVisible || maxVisible !== this.maxVisible) {
            if (Math.max(minVisible, this.minVisible) === minVisible &&
                Math.max(maxVisible, this.maxVisible) === maxVisible) {
                this.directionInternal = 'DOWN';
            }
            else if (Math.min(minVisible, this.minVisible) === minVisible &&
                Math.min(maxVisible, this.maxVisible) === maxVisible) {
                this.directionInternal = 'UP';
            }
        }
        let imagesOnScreen = maxVisible - minVisible + 1;
        let oldMeanImagesOnScreen = this.meanImagesOnScreen;
        if (this.firstScreen) {
            this.meanImagesOnScreen = imagesOnScreen;
            this.firstScreen = false;
            this.lastUpdateTimestamp = Date.now();
        }
        else {
            {
                const imagesWeight = 0.95;
                this.meanImagesOnScreen = this.meanImagesOnScreen * imagesWeight + (1 - imagesWeight) * imagesOnScreen;
            }
            this.updateSpeed(minVisible, maxVisible);
        }
        this.minVisible = minVisible;
        this.maxVisible = maxVisible;
        const visibleRangeSizeChanged = Math.ceil(oldMeanImagesOnScreen) !== Math.ceil(this.meanImagesOnScreen);
        this.visibleRangeInternal = new IndexRange(minVisible, maxVisible + 1);
        if (visibleRangeSizeChanged) {
            this.notifyObservers();
        }
        this.lastUpdateTimestamp = Date.now();
    }
    notifyObservers() {
        this.callbacks.forEach((callback) => callback());
    }
}
class PrefetchCount {
    constructor(itemsOnScreen, prefetchRangeRatio, logger = dummyLogger) {
        this.itemsOnScreen = itemsOnScreen;
        this.prefetchRangeRatio = prefetchRangeRatio;
        this.logger = logger;
        this.MAX_SCREENS = 4;
        this.speedCoef = 2.5;
        this.maxItems = 0;
        this.prefetchCountValueInternal = 0;
        this.currentMaxItemsInternal = 0;
        this.currentMinItemsInternal = 0;
        this.itemsOnScreen = itemsOnScreen;
        this.itemsOnScreen.register(() => {
            this.updateLimits();
        });
        this.prefetchRangeRatio.register(() => {
            this.updateLimits();
        });
    }
    get prefetchCountValue() {
        return this.prefetchCountValueInternal;
    }
    set prefetchCountValue(v) {
        this.prefetchCountValueInternal = v;
        this.logger.debug(`{"tm":${Date.now()},"prefetch_count":${v}}`);
    }
    get currentMaxItems() {
        return this.currentMaxItemsInternal;
    }
    get currentMinItems() {
        return this.currentMinItemsInternal;
    }
    getPrefetchCountByRatio(ratio) {
        this.itemsOnScreen.updateSpeed(this.itemsOnScreen.visibleRange.start, this.itemsOnScreen.visibleRange.end - 1);
        const minItems = Math.min(this.currentMaxItems, Math.ceil(this.speedCoef * this.itemsOnScreen.speed * this.currentMaxItems));
        const prefetchCount = minItems + Math.ceil(ratio * (this.currentMaxItems - minItems));
        this.logger.debug(`speed: ${this.itemsOnScreen.speed}, minItems: ${minItems}, ratio: ${ratio}, prefetchCount: ${prefetchCount}`);
        return prefetchCount;
    }
    getRangeToFetch(totalCount) {
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
        if (start > end) {
            start = end;
        }
        return new IndexRange(start, end);
    }
    updateLimits() {
        this.maxItems = Math.max(this.currentMinItems, Math.ceil(this.MAX_SCREENS * this.itemsOnScreen.meanValue));
        this.updateCurrentLimit();
    }
    updateCurrentLimit() {
        this.currentMaxItemsInternal = Math.max(this.currentMinItems, Math.ceil(this.maxItems * this.prefetchRangeRatio.maxRatio));
        this.currentMinItemsInternal = Math.ceil(this.maxItems * this.prefetchRangeRatio.minRatio);
    }
}
class FetchingRangeEvaluator {
    constructor(itemsOnScreen, prefetchCount, prefetchRangeRatio, fetchedRegistry, logger = dummyLogger) {
        this.itemsOnScreen = itemsOnScreen;
        this.prefetchCount = prefetchCount;
        this.prefetchRangeRatio = prefetchRangeRatio;
        this.fetchedRegistry = fetchedRegistry;
        this.logger = logger;
        this.totalItems = 0;
    }
    updateRangeToFetch(whatHappened) {
        switch (whatHappened.kind) {
            case 'visible-area-changed':
                this.onVisibleAreaChange(whatHappened.minVisible, whatHappened.maxVisible);
                break;
            case 'item-fetched':
                this.onItemFetched(whatHappened.itemIndex, whatHappened.fetchDuration);
                break;
            case 'collection-changed':
                this.onCollectionChanged(whatHappened.totalCount);
                break;
            case 'item-added':
                this.onItemAdded(whatHappened.itemIndex);
                break;
            case 'item-removed':
                this.onItemDeleted(whatHappened.itemIndex);
                break;
            default:
                assertNever(whatHappened);
        }
    }
    onVisibleAreaChange(minVisible, maxVisible) {
        const oldVisibleRange = this.itemsOnScreen.visibleRange;
        this.itemsOnScreen.update(minVisible, maxVisible);
        this.logger.debug(`visibleAreaChanged itemsOnScreen=${this.itemsOnScreen.visibleRange.length}, meanImagesOnScreen=${this.itemsOnScreen.meanValue}, prefetchCountCurrentLimit=${this.prefetchCount.currentMaxItems}, prefetchCountMaxRatio=${this.prefetchRangeRatio.maxRatio}`);
        if (!oldVisibleRange.equals(this.itemsOnScreen.visibleRange)) {
            this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('visible-area-changed');
            const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
            this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
        }
    }
    onItemFetched(index, fetchDuration) {
        if (!this.fetchedRegistry.rangeToFetch.contains(index)) {
            return;
        }
        this.logger.debug(`onItemFetched`);
        let maxRatioChanged = false;
        if (this.prefetchRangeRatio.update(index, fetchDuration) === 'ratio-changed') {
            maxRatioChanged = true;
            this.logger.debug(`choosePrefetchCountLimit prefetchCountMaxRatio=${this.prefetchRangeRatio.maxRatio}, prefetchCountMinRatio=${this.prefetchRangeRatio.minRatio}, prefetchCountCurrentLimit=${this.prefetchCount.currentMaxItems}`);
        }
        this.fetchedRegistry.addFetched(index);
        this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('resolved', maxRatioChanged);
        const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
        this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
    }
    evaluatePrefetchCount(event, maxRatioChanged) {
        let ratio = this.prefetchRangeRatio.calculateRatio(this.prefetchCount.prefetchCountValue, this.totalItems);
        let evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(ratio);
        if (maxRatioChanged) {
            ratio = this.prefetchRangeRatio.calculateRatio(evaluatedPrefetchCount, this.totalItems);
            evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(ratio);
        }
        if (!this.prefetchRangeRatio.hysteresisEnabled) {
            if (event === 'resolved') {
                this.prefetchRangeRatio.updateRatioRange(ratio);
                this.prefetchRangeRatio.hysteresisEnabled = true;
            }
            else if (event === 'visible-area-changed') {
                this.prefetchRangeRatio.oldRatio = ratio;
            }
        }
        else if (this.prefetchRangeRatio.range.contains(ratio)) {
            return this.prefetchCount.prefetchCountValue;
        }
        else {
            if (event === 'resolved') {
                this.prefetchRangeRatio.updateRatioRange(ratio);
            }
            else if (event === 'visible-area-changed') {
                this.prefetchRangeRatio.setEmptyRange();
                this.prefetchRangeRatio.oldRatio = ratio;
                this.prefetchRangeRatio.hysteresisEnabled = false;
            }
        }
        this.logger.debug(`evaluatePrefetchCount event=${event}, ${this.prefetchRangeRatio.hysteresisEnabled ? 'inHysteresis' : 'setHysteresis'} prefetchCount=${evaluatedPrefetchCount}, ratio=${ratio}, hysteresisRange=${this.prefetchRangeRatio.range}`);
        return evaluatedPrefetchCount;
    }
    onCollectionChanged(totalCount) {
        this.totalItems = Math.max(0, totalCount);
        let newRangeToFetch;
        if (this.fetchedRegistry.rangeToFetch.length > 0) {
            newRangeToFetch = this.itemsOnScreen.visibleRange;
        }
        else {
            newRangeToFetch = this.fetchedRegistry.rangeToFetch;
        }
        if (newRangeToFetch.end > this.totalItems) {
            const end = this.totalItems;
            const start = newRangeToFetch.start < end ? newRangeToFetch.start : end;
            newRangeToFetch = new IndexRange(start, end);
        }
        this.fetchedRegistry.clearFetched(newRangeToFetch);
    }
    onItemDeleted(itemIndex) {
        if (this.totalItems === 0) {
            return;
        }
        this.totalItems--;
        this.fetchedRegistry.removeFetched(itemIndex);
        const end = this.fetchedRegistry.rangeToFetch.end < this.totalItems ? this.fetchedRegistry.rangeToFetch.end : this.totalItems;
        const rangeToFetch = new IndexRange(this.fetchedRegistry.rangeToFetch.start, end);
        this.fetchedRegistry.decrementFetchedGreaterThen(itemIndex, rangeToFetch);
    }
    onItemAdded(itemIndex) {
        this.totalItems++;
        if (itemIndex > this.fetchedRegistry.rangeToFetch.end) {
            return;
        }
        const end = this.fetchedRegistry.rangeToFetch.end + 1;
        const rangeToFetch = new IndexRange(this.fetchedRegistry.rangeToFetch.start, end);
        this.fetchedRegistry.incrementFetchedGreaterThen(itemIndex - 1, rangeToFetch);
    }
}
class PrefetchRangeRatio {
    constructor(itemsOnScreen, fetchedRegistry, fetchingRegistry, logger = dummyLogger) {
        this.itemsOnScreen = itemsOnScreen;
        this.fetchedRegistry = fetchedRegistry;
        this.fetchingRegistry = fetchingRegistry;
        this.logger = logger;
        this.TOLERANCE_RANGES = [
            {
                leftToleranceEdge: 140,
                rightToleranceEdge: 290,
                prefetchCountMinRatioLeft: 0.5,
                prefetchCountMaxRatioLeft: 0.5,
                prefetchCountMinRatioRight: 0.25,
                prefetchCountMaxRatioRight: 1,
            },
            {
                leftToleranceEdge: 3000,
                rightToleranceEdge: 4000,
                prefetchCountMinRatioLeft: 0.25,
                prefetchCountMaxRatioLeft: 1,
                prefetchCountMinRatioRight: 0.25,
                prefetchCountMaxRatioRight: 0.25,
            },
        ];
        this.ACTIVE_DEGREE = 0;
        this.VISIBLE_DEGREE = 2.5;
        this.meanPrefetchTime = 0;
        this.leftToleranceEdge = Number.MIN_VALUE;
        this.rightToleranceEdge = 250;
        this.callbacks = [];
        this.rangeInternal = RatioRange.newEmpty();
        this.minRatioInternal = 0.25 * 0.6;
        this.maxRatioInternal = 0.5;
        this.hysteresisEnabledInternal = false;
        this.oldRatioInternal = 0;
    }
    register(callback) {
        this.callbacks.push(callback);
    }
    get range() {
        return this.rangeInternal;
    }
    setEmptyRange() {
        this.rangeInternal = RatioRange.newEmpty();
    }
    get maxRatio() {
        return this.maxRatioInternal;
    }
    get minRatio() {
        return this.minRatioInternal;
    }
    get hysteresisEnabled() {
        return this.hysteresisEnabledInternal;
    }
    set hysteresisEnabled(value) {
        this.hysteresisEnabledInternal = value;
    }
    set oldRatio(ratio) {
        this.oldRatioInternal = ratio;
    }
    get oldRatio() {
        return this.oldRatioInternal;
    }
    updateTiming(index, prefetchDuration) {
        const weight = 0.95;
        const localPrefetchDuration = 20;
        let isFetchLocal = prefetchDuration < localPrefetchDuration;
        let isFetchLatecomer = this.fetchingRegistry.isFetchLatecomer(index, this.itemsOnScreen.meanValue);
        if (!isFetchLocal && !isFetchLatecomer) {
            this.meanPrefetchTime = this.meanPrefetchTime * weight + (1 - weight) * prefetchDuration;
        }
        this.logger.debug(`prefetchDifference prefetchDur=${prefetchDuration}, meanPrefetchDur=${this.meanPrefetchTime}, ` +
            `isFetchLocal=${isFetchLocal}, isFetchLatecomer=${isFetchLatecomer}`);
    }
    update(index, prefetchDuration) {
        this.updateTiming(index, prefetchDuration);
        if (this.meanPrefetchTime >= this.leftToleranceEdge && this.meanPrefetchTime <= this.rightToleranceEdge) {
            return 'ratio-not-changed';
        }
        let ratioChanged = false;
        if (this.meanPrefetchTime > this.rightToleranceEdge) {
            ratioChanged = this.updateOnGreaterThanRight();
        }
        else if (this.meanPrefetchTime < this.leftToleranceEdge) {
            ratioChanged = this.updateOnLessThanLeft();
        }
        if (ratioChanged) {
            this.notifyObservers();
        }
        return ratioChanged ? 'ratio-changed' : 'ratio-not-changed';
    }
    updateOnLessThanLeft() {
        let ratioChanged = false;
        for (let i = this.TOLERANCE_RANGES.length - 1; i >= 0; i--) {
            const limit = this.TOLERANCE_RANGES[i];
            if (this.meanPrefetchTime < limit.leftToleranceEdge) {
                ratioChanged = true;
                this.maxRatioInternal = limit.prefetchCountMaxRatioLeft;
                this.minRatioInternal = limit.prefetchCountMinRatioLeft;
                this.rightToleranceEdge = limit.rightToleranceEdge;
                if (i !== 0) {
                    this.leftToleranceEdge = this.TOLERANCE_RANGES[i - 1].leftToleranceEdge;
                }
                else {
                    this.leftToleranceEdge = Number.MIN_VALUE;
                }
            }
        }
        return ratioChanged;
    }
    updateOnGreaterThanRight() {
        let ratioChanged = false;
        for (let i = 0; i < this.TOLERANCE_RANGES.length; i++) {
            const limit = this.TOLERANCE_RANGES[i];
            if (this.meanPrefetchTime > limit.rightToleranceEdge) {
                ratioChanged = true;
                this.maxRatioInternal = limit.prefetchCountMaxRatioRight;
                this.minRatioInternal = limit.prefetchCountMinRatioRight;
                this.leftToleranceEdge = limit.leftToleranceEdge;
                if (i + 1 !== this.TOLERANCE_RANGES.length) {
                    this.rightToleranceEdge = this.TOLERANCE_RANGES[i + 1].rightToleranceEdge;
                }
                else {
                    this.rightToleranceEdge = Number.MAX_VALUE;
                }
            }
        }
        return ratioChanged;
    }
    calculateRatio(prefetchCount, totalCount) {
        const visibleRange = this.itemsOnScreen.visibleRange;
        let start = 0;
        let end = 0;
        switch (this.itemsOnScreen.direction) {
            case 'UNKNOWN':
                start = Math.max(0, visibleRange.start - prefetchCount);
                end = Math.min(totalCount, visibleRange.end + prefetchCount);
                break;
            case 'UP':
                start = Math.max(0, visibleRange.start - prefetchCount);
                end = Math.min(totalCount, visibleRange.end + Math.round(0.5 * prefetchCount));
                break;
            case 'DOWN':
                start = Math.max(0, visibleRange.start - Math.round(0.5 * prefetchCount));
                end = Math.min(totalCount, visibleRange.end + prefetchCount);
                break;
        }
        const evaluatedPrefetchRange = new IndexRange(start, end);
        const completedActive = this.fetchedRegistry.getFetchedInRange(evaluatedPrefetchRange);
        const completedVisible = this.fetchedRegistry.getFetchedInRange(visibleRange);
        if (evaluatedPrefetchRange.length === 0 || visibleRange.length === 0) {
            return 0;
        }
        this.logger.debug(`active_degree=${this.ACTIVE_DEGREE}, visible_degree=${this.VISIBLE_DEGREE}`);
        this.logger.debug(`evaluatedPrefetchRange=${evaluatedPrefetchRange}, visibleRange=${visibleRange}, active_ratio=${Math.pow(completedActive / evaluatedPrefetchRange.length, this.ACTIVE_DEGREE)}, visible_ratio=${Math.pow(completedVisible / visibleRange.length, this.VISIBLE_DEGREE)}, completedActive=${completedActive}, evaluatedPrefetchRange.length=${evaluatedPrefetchRange.length}, visibleRange.length=${visibleRange.length}`);
        const ratio = Math.pow(completedActive / evaluatedPrefetchRange.length, this.ACTIVE_DEGREE) *
            Math.pow(completedVisible / visibleRange.length, this.VISIBLE_DEGREE);
        this.logger.debug(`calculateRatio ratio=${ratio}, completedActive=${completedActive}, evaluatedPrefetchRange.length=${evaluatedPrefetchRange.length}, ` +
            `completedVisible=${completedVisible}, visibleRange.length=${visibleRange.length}`);
        return Math.min(1, ratio);
    }
    updateRatioRange(ratio) {
        if (ratio > this.oldRatioInternal) {
            this.rangeInternal = new RatioRange(new RangeEdge(this.oldRatioInternal, false), new RangeEdge(ratio, true));
        }
        else {
            this.rangeInternal = new RatioRange(new RangeEdge(ratio, true), new RangeEdge(this.oldRatioInternal, false));
        }
        this.oldRatioInternal = ratio;
    }
    notifyObservers() {
        this.callbacks.forEach((callback) => callback());
    }
}
class DefaultTimeProvider {
    getCurrent() {
        return Date.now();
    }
}
const dummyDataSource = {
    prefetch: () => { },
    totalCount: () => {
        return 0;
    },
    getData: () => {
        return undefined;
    },
    registerDataChangeListener: () => { },
    unregisterDataChangeListener: () => { },
};
const DELAY_TO_REPEAT_FETCH_AFTER_ERROR = 500;
class FetchingDriver {
    constructor(fetchedRegistry, fetches, prefetchRangeEvaluator, timeProvider, logger = dummyLogger, autostart = true) {
        this.fetchedRegistry = fetchedRegistry;
        this.fetches = fetches;
        this.prefetchRangeEvaluator = prefetchRangeEvaluator;
        this.timeProvider = timeProvider;
        this.logger = logger;
        this.dataSource = dummyDataSource;
        this.dataSourceObserver = new DataSourceObserver(this);
        this.singleFetch = (itemIndex) => {
            if (this.fetches.isFetchingItem(itemIndex) || this.fetchedRegistry.has(itemIndex)) {
                return;
            }
            const prefetchStart = this.timeProvider.getCurrent();
            const fetchId = this.fetches.registerFetch(itemIndex);
            this.logger.info('to prefetch ' + itemIndex);
            try {
                const prefetchResponse = this.dataSource.prefetch(itemIndex);
                if (!(prefetchResponse instanceof Promise)) {
                    this.fetchedCallback(fetchId, prefetchStart);
                    return;
                }
                prefetchResponse
                    .then(() => this.fetchedCallback(fetchId, prefetchStart))
                    .catch((e) => {
                    this.errorOnFetchCallback(fetchId, e);
                });
            }
            catch (e) {
                this.errorOnFetchCallback(fetchId, e);
            }
        };
        this.isPaused = !autostart;
        this.prefetchRangeEvaluator = prefetchRangeEvaluator;
        this.timeProvider = timeProvider;
    }
    get afterErrorDelay() {
        return DELAY_TO_REPEAT_FETCH_AFTER_ERROR;
    }
    batchUpdate(operations) {
        this.logger.info('batchUpdate called with ' + JSON.stringify(operations));
        try {
            this.batchUpdateInternal(operations);
        }
        catch (e) {
            reportError(this.logger, 'batchUpdate', e);
            throw e;
        }
    }
    batchUpdateInternal(operations) {
        operations.forEach((operation) => {
            switch (operation.kind) {
                case 'deleted':
                    this.itemsDeleted(operation.startIndex, operation.count);
                    break;
                case 'added':
                    this.itemsAdded(operation.startIndex, operation.count);
                    break;
                case 'updated':
                    this.itemUpdated(operation.index);
                    break;
                case 'reloaded':
                    this.collectionChanged(operation.totalCount);
                    break;
                case 'swapped':
                    this.itemsSwapped(operation.a, operation.b);
                    break;
                case 'moved':
                    this.itemMoved(operation.from, operation.to);
                    break;
            }
        });
        this.prefetch(this.fetchedRegistry.getItemsToFetch());
    }
    collectionChanged(totalCount) {
        this.prefetchRangeEvaluator.updateRangeToFetch({
            kind: 'collection-changed',
            totalCount: totalCount,
        });
    }
    itemUpdated(index) {
        this.fetchedRegistry.removeFetched(index);
        this.fetches.deleteFetchByItem(index);
    }
    itemsDeleted(index, count) {
        for (let i = 0; i < count; i++) {
            this.fetches.decrementAllIndexesGreaterThen(index);
            this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'item-removed', itemIndex: index });
        }
    }
    itemsAdded(index, count) {
        for (let i = 0; i < count; i++) {
            this.fetches.incrementAllIndexesGreaterThen(index - 1);
            this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'item-added', itemIndex: index });
        }
    }
    itemsSwapped(a, b) {
        if (!this.fetchedRegistry.has(a) || !this.fetchedRegistry.has(b)) {
            this.fetchedRegistry.removeFetched(a);
            this.fetchedRegistry.removeFetched(b);
        }
    }
    itemMoved(from, to) {
        if (!this.fetchedRegistry.has(from) || !this.fetchedRegistry.has(to)) {
            const rangeToFetch = this.fetchedRegistry.rangeToFetch;
            this.itemsDeleted(from, 1);
            this.itemsAdded(to, 1);
            this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
        }
    }
    setDataSource(ds = dummyDataSource) {
        this.logger.info(`setDataSource called with ${ds !== dummyDataSource ? 'a data source' : 'null or undefined'}`);
        try {
            this.setDataSourceInternal(ds);
        }
        catch (e) {
            reportError(this.logger, 'setDataSource', e);
            throw e;
        }
    }
    setDataSourceInternal(ds) {
        this.dataSource = ds ?? dummyDataSource;
        this.dataSourceObserver.setDataSource(this.dataSource);
    }
    stop() {
        this.logger.info('Stop called');
        try {
            this.stopInternal();
        }
        catch (e) {
            reportError(this.logger, 'stop', e);
            throw e;
        }
    }
    stopInternal() {
        if (this.isPaused) {
            return;
        }
        this.isPaused = true;
        this.cancel(this.fetches.getAllIndexes());
    }
    start() {
        this.logger.info('Start called');
        try {
            this.startInternal();
        }
        catch (e) {
            reportError(this.logger, 'start', e);
            throw e;
        }
    }
    startInternal() {
        if (!this.isPaused) {
            return;
        }
        this.isPaused = false;
        this.prefetch(this.fetchedRegistry.getItemsToFetch());
    }
    visibleAreaChanged(minVisible, maxVisible) {
        this.logger.info(`visibleAreaChanged min: ${minVisible} max: ${maxVisible}`);
        try {
            this.visibleAreaChangedInternal(minVisible, maxVisible);
        }
        catch (e) {
            reportError(this.logger, 'visibleAreaChanged', e);
            throw e;
        }
    }
    visibleAreaChangedInternal(minVisible, maxVisible) {
        if (this.dataSource === dummyDataSource) {
            throw new Error('No data source');
        }
        const oldRangeToPrefetch = this.fetchedRegistry.rangeToFetch;
        this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'visible-area-changed', minVisible, maxVisible });
        this.prefetch(this.fetchedRegistry.getItemsToFetch());
        const toCancel = oldRangeToPrefetch.subtract(this.fetchedRegistry.rangeToFetch).toSet();
        this.cancel(toCancel);
    }
    prefetch(toPrefetch) {
        if (this.isPaused) {
            this.logger.debug('Prefetcher is paused. Do nothing.');
            return;
        }
        toPrefetch.forEach(this.singleFetch);
    }
    fetchedCallback(fetchId, prefetchStart) {
        const itemIndex = this.fetches.getItem(fetchId);
        this.fetches.deleteFetch(fetchId);
        if (itemIndex === undefined) {
            return;
        }
        this.prefetchRangeEvaluator.updateRangeToFetch({
            kind: 'item-fetched',
            itemIndex,
            fetchDuration: this.timeProvider.getCurrent() - prefetchStart,
        });
        this.prefetch(this.fetchedRegistry.getItemsToFetch());
    }
    errorOnFetchCallback(fetchId, error) {
        const itemIndex = this.fetches.getItem(fetchId);
        if (itemIndex !== undefined) {
            this.logger.warn(`failed to fetch item at ${itemIndex} ${JSON.stringify(error)}`);
        }
        this.fetches.deleteFetch(fetchId);
        setTimeout(() => {
            this.prefetch(this.fetchedRegistry.getItemsToFetch());
        }, this.afterErrorDelay);
    }
    cancel(toCancel) {
        toCancel.forEach((itemIndex) => {
            if (!this.fetches.isFetchingItem(itemIndex)) {
                return;
            }
            this.fetches.deleteFetchByItem(itemIndex);
            if (this.dataSource.cancel) {
                this.logger.info('to cancel ' + itemIndex);
                this.dataSource.cancel(itemIndex);
            }
        });
    }
}
const dummyLogger = {
    debug: () => { },
    info: () => { },
    warn: () => { },
};
function reportError(logger, methodName, e) {
    logger.warn(`Error in ${methodName}: ${e}\n${e.stack}`);
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
    toSet(target) {
        const set = target ?? new Set();
        for (let i = this.start; i < this.end; ++i) {
            set.add(i);
        }
        return set;
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
    equals(other) {
        return this.start === other.start && this.end === other.end;
    }
    toString() {
        return `[${this.start}, ${this.end})`;
    }
}
class IndexRangeArray extends Array {
    forEachIndex(callback) {
        this.forEach((range) => {
            range.forEachIndex(callback);
        });
    }
    toSet() {
        const set = new Set();
        this.forEach((range) => {
            range.toSet(set);
        });
        return set;
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
        if (point === this.start.value) {
            return this.start.inclusive;
        }
        if (point === this.end.value) {
            return this.end.inclusive;
        }
        return this.start.value < point && point < this.end.value;
    }
    toString() {
        return `${this.start.inclusive ? '[' : '('}${this.start.value}, ${this.end.value}${this.end.inclusive ? ']' : ')'}`;
    }
}
function assertNever(_) {
    throw _ + 'assertNever';
}

export default { BasicPrefetcher };
