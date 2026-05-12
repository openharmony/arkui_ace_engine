/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

const __smartGestureController__ = requireInternal('arkui.smartGestureController');
const ORIGINAL_MONITOR_CALLBACK_KEY = '__arkuiSmartGestureOriginalMonitorCallback__';

let SmartGestureAction;
(function (SmartGestureAction) {
    SmartGestureAction[SmartGestureAction.NONE = 0] = 'NONE';
    SmartGestureAction[SmartGestureAction.PAGE_FORWARD = 1] = 'PAGE_FORWARD';
    SmartGestureAction[SmartGestureAction.SCROLL_FORWARD = 2] = 'SCROLL_FORWARD';
    SmartGestureAction[SmartGestureAction.SELECT = 3] = 'SELECT';
    SmartGestureAction[SmartGestureAction.CLICK = 4] = 'CLICK';
    SmartGestureAction[SmartGestureAction.BACK_PRESS = 5] = 'BACK_PRESS';
})(SmartGestureAction || (SmartGestureAction = {}));
globalThis.SmartGestureAction = SmartGestureAction;

let OperateIntention;
(function (OperateIntention) {
    OperateIntention[OperateIntention.TAP = 0] = 'TAP';
    OperateIntention[OperateIntention.SLIDE_FORWARD = 1] = 'SLIDE_FORWARD';
    OperateIntention[OperateIntention.BACK_PRESS = 2] = 'BACK_PRESS';
})(OperateIntention || (OperateIntention = {}));
globalThis.OperateIntention = OperateIntention;

const DEFAULT_OPERATE_INTENTION = OperateIntention.TAP;

const proposalKindStore = new WeakMap();

function createAbstractClassError(className) {
    return new TypeError(`Cannot construct abstract class ${className}.`);
}

function isObject(value) {
    return typeof value === 'object' && value !== null;
}

function brandProposal(proposal, kind) {
    proposalKindStore.set(proposal, kind);
    return proposal;
}

function getProposalKind(proposal) {
    return proposalKindStore.get(proposal);
}

function hasOwnProperty(value, property) {
    return Object.prototype.hasOwnProperty.call(value, property);
}

function validateIsConsumed(isConsumed) {
    if (typeof isConsumed !== 'boolean') {
        throw new TypeError('The type of isConsumed is not boolean.');
    }
}

function createMonitorNativeWrapper(monitorCallback) {
    const nativeWrapper = (rawProposal) => {
        const proposal = createProposalFromRaw(rawProposal);
        const resolution = nativeWrapper[ORIGINAL_MONITOR_CALLBACK_KEY](proposal);
        return encodeResolutionForNative(validateResolution(resolution));
    };
    Object.defineProperty(nativeWrapper, ORIGINAL_MONITOR_CALLBACK_KEY, {
        value: monitorCallback,
        writable: false,
        enumerable: false,
        configurable: false,
    });
    return nativeWrapper;
}

class BaseGestureHandlingProposal {
    constructor(action, operateIntention) {
        if (new.target === BaseGestureHandlingProposal) {
            throw createAbstractClassError('BaseGestureHandlingProposal');
        }
        this.action = action;
        this.operateIntention = operateIntention;
    }
}
globalThis.BaseGestureHandlingProposal = BaseGestureHandlingProposal;

class TargetedGestureProposal extends BaseGestureHandlingProposal {
    constructor(action, operateIntention, node) {
        if (new.target === TargetedGestureProposal) {
            throw createAbstractClassError('TargetedGestureProposal');
        }
        super(action, operateIntention);
        this.node = node;
    }
}
globalThis.TargetedGestureProposal = TargetedGestureProposal;

class ClickActionProposal extends TargetedGestureProposal {
    constructor(node) {
        super(SmartGestureAction.CLICK, OperateIntention.TAP, node);
        brandProposal(this, SmartGestureAction.CLICK);
    }
}
globalThis.ClickActionProposal = ClickActionProposal;

class SelectActionProposal extends TargetedGestureProposal {
    constructor(node) {
        super(SmartGestureAction.SELECT, OperateIntention.TAP, node);
        brandProposal(this, SmartGestureAction.SELECT);
    }
}
globalThis.SelectActionProposal = SelectActionProposal;

class NoneActionProposal extends BaseGestureHandlingProposal {
    constructor() {
        super(SmartGestureAction.NONE, OperateIntention.TAP);
        brandProposal(this, SmartGestureAction.NONE);
    }
}
globalThis.NoneActionProposal = NoneActionProposal;

class BackPressActionProposal extends BaseGestureHandlingProposal {
    constructor() {
        super(SmartGestureAction.BACK_PRESS, OperateIntention.BACK_PRESS);
        brandProposal(this, SmartGestureAction.BACK_PRESS);
    }
}
globalThis.BackPressActionProposal = BackPressActionProposal;

class PageSwitchActionProposal extends TargetedGestureProposal {
    constructor(node, pageCount) {
        super(SmartGestureAction.PAGE_FORWARD, OperateIntention.SLIDE_FORWARD, node);
        this.pageCount = pageCount;
        brandProposal(this, SmartGestureAction.PAGE_FORWARD);
    }
}
globalThis.PageSwitchActionProposal = PageSwitchActionProposal;

class ScrollActionProposal extends TargetedGestureProposal {
    constructor(node, distance, pageCount) {
        super(SmartGestureAction.SCROLL_FORWARD, OperateIntention.SLIDE_FORWARD, node);
        this.distance = distance;
        if (pageCount !== undefined) {
            this.pageCount = pageCount;
        }
        brandProposal(this, SmartGestureAction.SCROLL_FORWARD);
    }
}
globalThis.ScrollActionProposal = ScrollActionProposal;

class GestureHandlingResolution {
    constructor(isConsumed) {
        validateIsConsumed(isConsumed);
        this.isConsumed = isConsumed;
    }
}
globalThis.GestureHandlingResolution = GestureHandlingResolution;

function normalizeOperateIntention(rawOperateIntention) {
    switch (rawOperateIntention) {
        case OperateIntention.TAP:
        case OperateIntention.SLIDE_FORWARD:
        case OperateIntention.BACK_PRESS:
            return rawOperateIntention;
        default:
            return DEFAULT_OPERATE_INTENTION;
    }
}

function applyRawOperateIntention(proposal, rawOperateIntention) {
    proposal.operateIntention = normalizeOperateIntention(rawOperateIntention);
    return proposal;
}

function createProposalFromRaw(rawProposal) {
    if (!isObject(rawProposal)) {
        throw new TypeError('Invalid smart gesture proposal.');
    }
    switch (rawProposal.action) {
        case SmartGestureAction.NONE:
            return applyRawOperateIntention(new NoneActionProposal(), rawProposal.operateIntention);
        case SmartGestureAction.BACK_PRESS:
            return applyRawOperateIntention(new BackPressActionProposal(), rawProposal.operateIntention);
        case SmartGestureAction.CLICK:
            return applyRawOperateIntention(new ClickActionProposal(rawProposal.node), rawProposal.operateIntention);
        case SmartGestureAction.SELECT:
            return applyRawOperateIntention(new SelectActionProposal(rawProposal.node), rawProposal.operateIntention);
        case SmartGestureAction.PAGE_FORWARD:
            return applyRawOperateIntention(
                new PageSwitchActionProposal(rawProposal.node, rawProposal.pageCount), rawProposal.operateIntention);
        case SmartGestureAction.SCROLL_FORWARD:
            return applyRawOperateIntention(
                new ScrollActionProposal(rawProposal.node, rawProposal.distance, rawProposal.pageCount),
                rawProposal.operateIntention);
        default:
            throw new TypeError('Unsupported smart gesture proposal action.');
    }
}

function encodeProposalForNative(proposal) {
    if (proposal === undefined || proposal === null) {
        throw new TypeError('selectedProposal must be one of built-in proposal classes or their subclasses.');
    }

    const action = getProposalKind(proposal);
    if (action === undefined) {
        throw new TypeError('selectedProposal must be one of built-in proposal classes or their subclasses.');
    }

    const rawProposal = {
        action,
        operateIntention: DEFAULT_OPERATE_INTENTION,
    };
    switch (action) {
        case SmartGestureAction.NONE:
        case SmartGestureAction.BACK_PRESS:
            return rawProposal;
        case SmartGestureAction.CLICK:
        case SmartGestureAction.SELECT:
            rawProposal.node = proposal.node;
            return rawProposal;
        case SmartGestureAction.PAGE_FORWARD:
            rawProposal.node = proposal.node;
            rawProposal.pageCount = proposal.pageCount;
            return rawProposal;
        case SmartGestureAction.SCROLL_FORWARD:
            rawProposal.node = proposal.node;
            rawProposal.distance = proposal.distance;
            if (hasOwnProperty(proposal, 'pageCount')) {
                rawProposal.pageCount = proposal.pageCount;
            }
            return rawProposal;
        default:
            throw new TypeError('Unsupported smart gesture proposal action.');
    }
}

function validateSelectedProposal(selectedProposal) {
    if (selectedProposal === undefined || selectedProposal === null) {
        throw new TypeError('selectedProposal must be one of built-in proposal classes or their subclasses.');
    }
    if (!(selectedProposal instanceof BaseGestureHandlingProposal) || getProposalKind(selectedProposal) === undefined) {
        throw new TypeError('selectedProposal must be one of built-in proposal classes or their subclasses.');
    }
}

function encodeResolutionForNative(resolution) {
    const rawResolution = {
        isConsumed: resolution.isConsumed,
    };
    if (hasOwnProperty(resolution, 'selectedProposal')) {
        rawResolution.selectedProposal = encodeProposalForNative(resolution.selectedProposal);
    }
    return rawResolution;
}

function validateResolution(resolution) {
    if (resolution === undefined || resolution === null) {
        throw new TypeError('registerMonitor callback must return GestureHandlingResolution.');
    }
    if (!(resolution instanceof GestureHandlingResolution)) {
        throw new TypeError('registerMonitor callback must return GestureHandlingResolution.');
    }
    validateIsConsumed(resolution.isConsumed);
    if (hasOwnProperty(resolution, 'selectedProposal')) {
        validateSelectedProposal(resolution.selectedProposal);
    }
    return resolution;
}

const enableSmartTapAndSlideGestures = function enableSmartTapAndSlideGestures(enabled) {
    return __smartGestureController__.enableSmartTapAndSlideGestures(enabled);
};

const registerMonitor = function registerMonitor(monitorCallback) {
    const nativeWrapper = createMonitorNativeWrapper(monitorCallback);
    return __smartGestureController__.registerMonitor(nativeWrapper);
};

const unregisterMonitor = function unregisterMonitor(monitorCallback) {
    return __smartGestureController__.unregisterMonitor(monitorCallback);
};

const clearMonitors = function clearMonitors() {
    return __smartGestureController__.clearMonitors();
};

const requestSelected = function requestSelected(id) {
    return __smartGestureController__.requestSelected(id);
};

const clearSelected = function clearSelected() {
    return __smartGestureController__.clearSelected();
};

export default {
    SmartGestureAction,
    OperateIntention,
    BaseGestureHandlingProposal,
    TargetedGestureProposal,
    ClickActionProposal,
    SelectActionProposal,
    NoneActionProposal,
    BackPressActionProposal,
    PageSwitchActionProposal,
    ScrollActionProposal,
    GestureHandlingResolution,
    enableSmartTapAndSlideGestures,
    registerMonitor,
    unregisterMonitor,
    clearMonitors,
    requestSelected,
    clearSelected
};
